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
    class InputValidatorProcessorStep : public processor::ProcessorStep {
        json processImplementation(json input) {
            const json input_schema = R"(
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
                    "payload": { "$ref": "#/definitions/database" }
                },
                "additionalProperties": false
            }
            )"_json;

            json_validator validator;
            try {
                validator.set_root_schema(input_schema);
                validator.validate(input);
            } catch (const std::exception &e) {
                std::cerr << "Validation failed, here is why: " << e.what();
                return R"([])"_json;
            }
            return input;
        }
    };

    class GetDataProcessorStep : public processor::ProcessorStep {
    protected:
        json processImplementation(json input) {
            auto redis = Redis("tcp://127.0.0.1:6379");

            try {
                input["data"] = json::parse(redis.get("maintec:database").value());
            } catch (const std::exception &e) {
                std::cerr << "Json Parse failed, here is why: " << e.what();
            }
            return input;
        }
    };

    class UriProcessorStep : public processor::ProcessorStep {
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

    class PutProcessor : public processor::ProcessorStep {
    protected:
        json processImplementation(json input) {
            json::json_pointer uri = json::json_pointer(input["uri"]);
            if (input["data"].contains(uri)) {
                input["data"].at(uri) = input["payload"];
            }
            return input["data"];
        }
    };

    class PatchProcessor : public processor::ProcessorStep {
    protected:
        json processImplementation(json input) {
            json::json_pointer uri = json::json_pointer(input["uri"]);
            if (input["data"].contains(uri)) {
                input["data"].at(uri).update(input["payload"]);
            }
            return input["data"];
        }
    };

    class SetDataProcessor : public processor::ProcessorStep {
    protected:
        json processImplementation(json input) {
            auto redis = Redis("tcp://127.0.0.1:6379");

            json_validator validator;
            try {
                validator.set_root_schema(json::parse(redis.get("maintec:schema").value()));
                validator.validate(input);
            } catch (const std::exception &e) {
                std::cerr << "Validation failed, here is why: " << e.what();
                return R"([])"_json;
            }

            redis.set("maintec:database", input.dump());
            return input;
        }
    };

    // Http Processor
    class HttpGetProcessor : public processor::ChainProcessor {
    public:
        HttpGetProcessor() {
            setNextProcessorStep(&inputValidator);
            inputValidator.setNextProcessorStep(&getData);
            getData.setNextProcessorStep(&uriProcessor);
        }
    private:
        processor::InputValidatorProcessorStep inputValidator;
        processor::GetDataProcessorStep getData;
        processor::UriProcessorStep uriProcessor;
    };

    class HttpPutProcessor : public processor::ChainProcessor {
    public:
        HttpPutProcessor() {
            setNextProcessorStep(&inputValidator);
            inputValidator.setNextProcessorStep(&getData);
            getData.setNextProcessorStep(&putProcessor);
            putProcessor.setNextProcessorStep(&setData);
        }
    private:
        processor::InputValidatorProcessorStep inputValidator;
        processor::GetDataProcessorStep getData;
        processor::PutProcessor putProcessor;
        processor::SetDataProcessor setData;
    };

    class HttpPatchProcessor : public processor::ChainProcessor {
    public:
        HttpPatchProcessor() {
            setNextProcessorStep(&inputValidator);
            inputValidator.setNextProcessorStep(&getData);
            getData.setNextProcessorStep(&patchProcessor);
            patchProcessor.setNextProcessorStep(&setData);
        }
    private:
        processor::InputValidatorProcessorStep inputValidator;
        processor::GetDataProcessorStep getData;
        processor::PatchProcessor patchProcessor;
        processor::SetDataProcessor setData;
    };
}