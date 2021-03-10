#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace processor {
    class ChainProcessor : public processor::IProcessor {
    public:
        ChainProcessor() : mNextProcessor(0) {}
        virtual ~ChainProcessor() = default;

        void setNextProcessor(ChainProcessor *processor) {
            mNextProcessor = processor;
        }

        std::vector<char> process(std::vector<char> input) {
            try {
                json inputJson = json::parse(input);
                json resultJson = process(inputJson);
                std::string result = resultJson.dump();
                return std::vector<char>(result.begin(), result.end());
            } catch (const std::exception &e) {
                std::cerr << "Json Parse failed, here is why: " << e.what();
                return std::vector<char>();
            }
        }

        json process(json input) {
            json resultJson = processImplementation(input);
            if (mNextProcessor != 0) {
                resultJson = mNextProcessor->process(resultJson);
            }
            return resultJson;
        }

    protected:
        virtual json processImplementation(json input) = 0;
        ChainProcessor *mNextProcessor;
    };
}