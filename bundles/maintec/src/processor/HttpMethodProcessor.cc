#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include <nlohmann/json-schema.hpp>
#include "processor/IProcessor.h"
#include "JsonHelperProcessor.h"

using json = nlohmann::json;
using json_validator = nlohmann::json_schema::json_validator;
using namespace sw::redis;

namespace processor {

    // Chain Processor
    class GetDataProcessor : public processor::ChainProcessor {
    protected:
        json processImplementation(json input) {
            auto redis = Redis("tcp://127.0.0.1:6379");

            std::string value = redis.get("maintec").value();
            input["data"] = json::parse(value);
            return input;
        }
    };

    static json maintec_schema = R"(
    {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "title": "Maintec",
        "definitions": {
            "uri_pointer": {
                "type": "string"
            },
            "database": {
                "type": "object"
            }
        },
        "properties": {
            "uri": { "$ref": "#/definitions/uri_pointer" },
            "data": { "$ref": "#/definitions/database" }
        },
        "required": ["uri", "data"]
    }
    )"_json;

    class ValidatorProcessor : public processor::ChainProcessor {
        json processImplementation(json input) {
            json_validator validator;
            try {
                validator.set_root_schema(maintec_schema);
            } catch (const std::exception &e) {
                std::cerr << "Validation of schema failed, here is why: " << e.what() << "\n";
                return json();
            }
            try {
                validator.validate(input);
            } catch (const std::exception &e) {
                std::cerr << "Validation failed, here is why: " << e.what() << "\n";
                return json();
            }
            return input;
        }
    };

    class UriProcessor : public processor::ChainProcessor {
    protected:
        json processImplementation(json input) {
            json result = R"([])"_json;
            json data = input["data"];
            json::json_pointer uri = json::json_pointer(input["uri"]);
            if (data.contains(uri)) {
                result = data.at(uri);
            }
            return result;
        }
    };

    // Http Processor
    class HttpGetProcessor : public processor::StartProcessor {
    public:
        HttpGetProcessor() {
            setNextProcessor(&getData);
            getData.setNextProcessor(&validator);
            getData.setNextProcessor(&uriProcessor);
        }
    private:
        processor::GetDataProcessor getData;
        processor::ValidatorProcessor validator;
        processor::UriProcessor uriProcessor;
    };

    class HttpPutProcessor : public processor::StartProcessor {
    public:
        HttpPutProcessor() {
            setNextProcessor(&getData);
            getData.setNextProcessor(&validator);
        }
    private:
        processor::GetDataProcessor getData;
        processor::ValidatorProcessor validator;
    };
}