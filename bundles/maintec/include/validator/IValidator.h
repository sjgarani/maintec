#pragma once

namespace validator {
    class IValidator {
    public:
        static constexpr const char * const PROCESSOR_NAME = "name";
        virtual ~IValidator() = default;

        virtual bool validate(std::vector<char>) = 0;
    };
}