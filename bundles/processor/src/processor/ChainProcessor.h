#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace processor {
    class ProcessorStep {
    public:
        ProcessorStep() : mNextStepProcessor(0) {}
        virtual ~ProcessorStep() = default;

        void setNextProcessorStep(ProcessorStep *processor) {
            mNextStepProcessor = processor;
        }

        json process(json input) {
            json resultJson = processImplementation(input);
            if (mNextStepProcessor != 0) {
                resultJson = mNextStepProcessor->process(resultJson);
            }
            return resultJson;
        }

    protected:
        virtual json processImplementation(json input) = 0;
        ProcessorStep *mNextStepProcessor;
    };

    class ChainProcessor : public processor::IProcessor {
    public:
        ChainProcessor() : mNextStepProcessor(0) {}
        virtual ~ChainProcessor() = default;

        void setNextProcessorStep(ProcessorStep *processor) {
            mNextStepProcessor = processor;
        }

        std::vector<char> process(std::vector<char> input) {
            try {
                json inputJson = json::parse(input);
                json resultJson = R"([])"_json;
                if (mNextStepProcessor != 0) {
                    resultJson = mNextStepProcessor->process(inputJson);
                }
                std::string result = resultJson.dump();
                return std::vector<char>(result.begin(), result.end());
            } catch (const std::exception &e) {
                std::cerr << "Json Parse failed, here is why: " << e.what();
                return std::vector<char>();
            }
        }

    protected:
        ProcessorStep *mNextStepProcessor;
    };
}