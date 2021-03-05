#pragma once

namespace processor {
    class ChainProcessor : public processor::IProcessor {
    public:
        ChainProcessor() : mNextProcessor(0) {}
        virtual ~ChainProcessor() = default;

        void setNextProcessor(ChainProcessor *processor) {
            mNextProcessor = processor;
        }

        std::vector<char> process(std::vector<char> input) {
            std::vector<char> processed = processImplementation(input);
            if (mNextProcessor != 0) {
                processed = mNextProcessor->process(processed);
            }
            processed = posProcessImplementation(processed);
            return processed;
        }
    protected:
        virtual std::vector<char> processImplementation(std::vector<char> input) = 0;
        virtual std::vector<char> posProcessImplementation(std::vector<char> input) = 0;
    private:
        ChainProcessor *mNextProcessor;
    };
}