#include <iostream>
#include "celix/BundleActivator.h"
#include "processor/IProcessor.h"

class ProcessorActivator {
public:
    explicit ProcessorActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started Processor from bundle with id " << ctx->getBundleId() << std::endl;
        auto echo = std::make_shared<EchoProcessor>();
        auto reg = ctx->registerService<processor::IProcessor>(echo)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, echo->getName())
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

        std::string getName() {
            return "echo";
        }

        std::vector<char> process(std::vector<char> input) {
            return input;
        }
    };
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(ProcessorActivator)