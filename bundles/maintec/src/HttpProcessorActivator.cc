#include <iostream>
#include <vector>
#include "celix/BundleActivator.h"
#include "processor/IProcessor.h"
#include "processor/HttpMethodProcessor.cc"

class HttpProcessorActivator {
public:
    explicit HttpProcessorActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started HTTP Processor from bundle with id " << ctx->getBundleId() << std::endl;
        auto put = std::make_shared<processor::HttpPutProcessor>();
        auto reg = ctx->registerService<processor::IProcessor>(put)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "put")
                .build();
        regs.push_back(reg);
        auto get = std::make_shared<processor::HttpGetProcessor>();
        reg = ctx->registerService<processor::IProcessor>(get)
                .addProperty(processor::IProcessor::PROCESSOR_NAME, "get")
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