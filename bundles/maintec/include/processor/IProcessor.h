#pragma once

namespace processor {
    class IProcessor {
    public:
        static constexpr const char * const PROCESSOR_NAME = "name";
        static constexpr const char * const PROCESSOR_NODE = "node";
        virtual ~IProcessor() = default;

        virtual std::vector<char> process(std::vector<char>) = 0;
    };
}