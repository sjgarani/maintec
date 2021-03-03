#pragma once

namespace processor {
    class IProcessor {
    public:
        static constexpr const char * const PROCESSOR_NAME = "name";
        virtual ~IProcessor() = default;
        virtual std::vector<unsigned char> processor(std::vector<unsigned char> input) = 0;
    };
}