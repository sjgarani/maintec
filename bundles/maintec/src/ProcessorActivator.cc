#include <iostream>
#include <vector>
#include "celix/BundleActivator.h"
#include "processor/IProcessor.h"

class EchoProcessor : public processor::IProcessor {
public:
    std::vector<char> process(std::vector<char> input) {
        return input;
    }
};

class ProcessorActivator {
public:
    explicit ProcessorActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started Processor from bundle with id " << ctx->getBundleId() << std::endl;
        auto echo = std::make_shared<EchoProcessor>();
        auto reg = ctx->registerService<processor::IProcessor>(echo)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "echo")
                .build();
        regs.push_back(reg);
    }

    ~ProcessorActivator() noexcept {
        std::cout << "Finished Processor" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(ProcessorActivator)