#include <iostream>
#include <vector>
#include "celix/BundleActivator.h"
#include "processor/IProcessor.h"
#include "processor/HttpMethodProcessor.cc"

class HttpProcessorActivator {
public:
    explicit HttpProcessorActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started HTTP Processor from bundle with id " << ctx->getBundleId() << std::endl;
        auto get = std::make_shared<processor::HttpGetProcessor>();
        auto reg = ctx->registerService<processor::IProcessor>(get)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "get")
                .build();
        regs.push_back(reg);
        auto put = std::make_shared<processor::HttpPutProcessor>();
        reg = ctx->registerService<processor::IProcessor>(put)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "put")
                .build();
        regs.push_back(reg);
        auto patch = std::make_shared<processor::HttpPatchProcessor>();
        reg = ctx->registerService<processor::IProcessor>(patch)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "patch")
                .build();
        regs.push_back(reg);
    }

    ~HttpProcessorActivator() noexcept {
        std::cout << "Finished HTTP Processor" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(HttpProcessorActivator)