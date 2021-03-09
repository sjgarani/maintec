#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include <nlohmann/json-schema.hpp>
#include "processor/IProcessor.h"
#include "ChainProcessor.h"

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
        "oneOf": [
            {
                "properties": {
                    "uri": { "$ref": "#/definitions/uri_pointer" },
                    "method": { "const": "get" },
                    "data": { "$ref": "#/definitions/database" }
                },
                "required": ["uri", "method", "data"]
            },
            {
                "properties": {
                    "uri": { "$ref": "#/definitions/uri_pointer" },
                    "method": { "const": "put" },
                    "data": { "$ref": "#/definitions/database" },
                    "payload": { "$ref": "#/definitions/database" }
                },
                "required": ["uri", "method", "data", "payload"]
            },
            {
                "properties": {
                    "uri": { "$ref": "#/definitions/uri_pointer" },
                    "method": { "const": "patch" },
                    "data": { "$ref": "#/definitions/database" },
                    "payload": { "$ref": "#/definitions/database" }
                },
                "required": ["uri", "method", "data", "payload"]
            }
        ]
    }
    )"_json;

    class ValidatorProcessor : public processor::ChainProcessor {
        json processImplementation(json input) {
            json_validator validator;
            try {
                validator.set_root_schema(maintec_schema);
            } catch (const std::exception &e) {
                std::cerr << "Validation of schema failed, here is why: " << e.what();
                return R"([])"_json;
            }
            try {
                validator.validate(input);
            } catch (const std::exception &e) {
                std::cerr << "Validation failed, here is why: " << e.what();
                return R"([])"_json;
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

    class PutProcessor : public processor::ChainProcessor {
    protected:
        json processImplementation(json input) {
            json::json_pointer uri = json::json_pointer(input["uri"]);
            if (input["data"].contains(uri)) {
                input["data"].at(uri) = input["payload"];
            }
            return input["data"];
        }
    };

    class PatchProcessor : public processor::ChainProcessor {
    protected:
        json processImplementation(json input) {
            json::json_pointer uri = json::json_pointer(input["uri"]);
            if (input["data"].contains(uri)) {
                input["data"].at(uri).update(input["payload"]);
            }
            return input["data"];
        }
    };

    class SetDataProcessor : public processor::ChainProcessor {
    protected:
        json processImplementation(json input) {
            auto redis = Redis("tcp://127.0.0.1:6379");

            redis.set("maintec", input.dump());
            return input;
        }
    };

    // Http Processor
    class HttpGetProcessor : public processor::ChainProcessor {
    public:
        HttpGetProcessor() {
            setNextProcessor(&getData);
            getData.setNextProcessor(&validator);
            validator.setNextProcessor(&uriProcessor);
        }
    protected:
        json processImplementation(json input) {
            input["method"] = "get";
            return input;
        }
    private:
        processor::GetDataProcessor getData;
        processor::ValidatorProcessor validator;
        processor::UriProcessor uriProcessor;
    };

    class HttpPutProcessor : public processor::ChainProcessor {
    public:
        HttpPutProcessor() {
            setNextProcessor(&getData);
            getData.setNextProcessor(&validator);
            validator.setNextProcessor(&putProcessor);
            putProcessor.setNextProcessor(&setData);
        }
    protected:
        json processImplementation(json input) {
            input["method"] = "put";
            return input;
        }
    private:
        processor::GetDataProcessor getData;
        processor::ValidatorProcessor validator;
        processor::PutProcessor putProcessor;
        processor::SetDataProcessor setData;
    };

    class HttpPatchProcessor : public processor::ChainProcessor {
    public:
        HttpPatchProcessor() {
            setNextProcessor(&getData);
            getData.setNextProcessor(&validator);
            validator.setNextProcessor(&patchProcessor);
            patchProcessor.setNextProcessor(&setData);
        }
    protected:
        json processImplementation(json input) {
            input["method"] = "patch";
            return input;
        }
    private:
        processor::GetDataProcessor getData;
        processor::ValidatorProcessor validator;
        processor::PatchProcessor patchProcessor;
        processor::SetDataProcessor setData;
    };
}