#include <vector>
#include "processor/IProcessor.h"
#include "ChainProcessor.h"

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
}