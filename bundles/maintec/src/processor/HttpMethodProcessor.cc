#include <vector>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include "processor/IProcessor.h"
#include "processor/ChainProcessor.h"

using json = nlohmann::json;
using namespace sw::redis;

namespace processor {

    class GetProcessor : public processor::ChainProcessor {
    protected:
        std::vector<char> processImplementation(std::vector<char> input) {
            auto redis = Redis("tcp://127.0.0.1:6379");

            std::string value = redis.get("maintec").value();
            json result = R"([])"_json;
            json data = json::parse(value);

            std::string text(input.begin(), input.end());
            text = text.erase(text.find_last_not_of("\t\n\v\f\r ") + 1);
            json::json_pointer pointer;
            if (text.size() > 0 && text.at(0) == '/') {
                pointer = json::json_pointer(text);
                if (data.contains(pointer)) {
                    result = data.at(pointer);
                }
            } else if (text.empty()) {
                result = data;
            }
            std::string resultText = result.dump();
            return std::vector<char>(resultText.begin(), resultText.end());
        }
        std::vector<char> posProcessImplementation(std::vector<char> input) {
            return input;
        }
    };

    class ValidatorProcessor : public processor::ChainProcessor {
        std::vector<char> processImplementation(std::vector<char> input) {
            return input;
        }
        std::vector<char> posProcessImplementation(std::vector<char> input) {
            return input;
        }
    };

    class HttpGetProcessor : public processor::StartProcessor {
    public:
        HttpGetProcessor() {
            setNextProcessor(&get);
        }
    private:
        processor::GetProcessor get;
    };

    class HttpPutProcessor : public processor::StartProcessor {
    public:
        HttpPutProcessor() {
            setNextProcessor(&validator);
        }
    private:
        processor::ValidatorProcessor validator;
    };
}