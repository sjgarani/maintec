#include <iostream>
#include "celix/BundleActivator.h"
#include "processor/IProcessor.h"

class ProcessorActivator {
public:
    explicit ProcessorActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started Processor from bundle with id " << ctx->getBundleId() << std::endl;
        auto reg = ctx->registerService<processor::IProcessor>(std::make_shared<EchoProcessor>())
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "echo")
                .build();
        regs.push_back(reg);
    }

    ~ProcessorActivator() noexcept {
        std::cout << "Finished Processor" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};

    class EchoProcessor : public processor::IProcessor {
    public:
        std::vector<unsigned char> processor(std::vector<unsigned char> input) {
            return input;
        }
    };
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(ProcessorActivator)