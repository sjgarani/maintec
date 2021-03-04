#pragma once

namespace processor {
    class IData {
    public:
        static constexpr const char * const PROCESSOR_NAME = "name";
        virtual ~IData() = default;

        virtual std::vector<char> get(void) = 0;
        virtual void set(std::vector<char>) = 0;
    };
}