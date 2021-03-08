#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace processor {
    class JsonProcessor : public processor::IProcessor {
    public:
        virtual ~JsonProcessor() = default;

        std::vector<char> process(std::vector<char> input) {
            try {
                json inputJson = json::parse(input);
                json resultJson = process(inputJson);
                std::string result = resultJson.dump();
                return std::vector<char>(result.begin(), result.end());
            } catch (const std::exception &e) {
                std::cerr << "Parse failed, here is why: " << e.what() << "\n";
                return std::vector<char>();
            }
        }

        virtual json process(json) = 0;
    };

    class ChainProcessor : public processor::JsonProcessor {
    public:
        ChainProcessor() : mNextProcessor(0) {}
        virtual ~ChainProcessor() = default;

        void setNextProcessor(ChainProcessor *processor) {
            mNextProcessor = processor;
        }

        json process(json input) {
            json processed = processImplementation(input);
            if (mNextProcessor != 0) {
                processed = mNextProcessor->process(processed);
            }
            return processed;
        }
    protected:
        virtual json processImplementation(json input) = 0;
        ChainProcessor *mNextProcessor;
    };

    class StartProcessor : public processor::ChainProcessor {
    public:
        virtual ~StartProcessor() = default;

        json process(json input) {
            json processed = processImplementation(input);
            if (mNextProcessor != 0) {
                processed = mNextProcessor->process(processed);
            }
            return processed;
        }
    protected:
        json processImplementation(json input) {
            return input;
        }
    };
}