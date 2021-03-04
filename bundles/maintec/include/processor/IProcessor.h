#pragma once

namespace processor {
    class IProcessor {
    public:
        static constexpr const char * const PROCESSOR_NAME = "name";
        virtual ~IProcessor() = default;

        virtual std::vector<char> process(std::vector<char> input) = 0;
    };
}