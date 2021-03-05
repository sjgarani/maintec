#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "processor/IProcessor.h"
#include "processor/ChainProcessor.h"

using json = nlohmann::json;

namespace processor {
    class Validator : public processor::ChainProcessor {
        std::vector<char> processImplementation(std::vector<char> input) {
            return input;
        }
        std::vector<char> posProcessImplementation(std::vector<char> input) {
            return input;
        }
    };

    class HttpPutProcessor : public processor::ChainProcessor {
    public:
        HttpPutProcessor() {
            setNextProcessor(&validator);
        }
    protected:
        std::vector<char> processImplementation(std::vector<char> input) {
            return input;
        }
        std::vector<char> posProcessImplementation(std::vector<char> input) {
            return input;
        }
    private:
        processor::Validator validator;
    };

    class HttpGetProcessor : public processor::ChainProcessor {
    protected:
        std::vector<char> processImplementation(std::vector<char> input) {
            json result = R"([])"_json;
            std::string text(input.begin(), input.end());
            json data =  R"(
                {
                    "dataA": "dataA",
                    "dataB": 1,
                    "dataC": { 
                        "data1": "data1", 
                        "data2": 2
                    },
                    "dataD": ["datax"]
                }
            )"_json;
            json::json_pointer pointer = json::json_pointer(text);
            if (pointer.empty()) {
                result = data;
            } else if (data.contains(pointer)) {
                result = data.at(pointer);
            }
            std::string resultText = result.dump();
            return std::vector<char>(resultText.begin(), resultText.end());
        }
        std::vector<char> posProcessImplementation(std::vector<char> input) {
            return input;
        }
    private:
        processor::Validator validator;
    };
}