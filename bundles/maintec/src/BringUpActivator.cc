#include <iostream>
#include <sstream>
#include "celix/BundleActivator.h"
#include "celix/IShellCommand.h"
#include "processor/IProcessor.h"

class ProcessorConsumer : public celix::IShellCommand {
public:
    static std::shared_ptr<ProcessorConsumer> create() {
        std::shared_ptr<ProcessorConsumer> instance{new ProcessorConsumer{}, [](ProcessorConsumer *consumer) {
           delete consumer;
        }};
        return instance;
    }

    void addProcessor(std::shared_ptr<processor::IProcessor> _processor) {
        std::lock_guard<std::mutex> lck{mutex};
        processors[_processor->getName()] = std::move(_processor);
    }

    void executeCommand(const std::string&, const std::vector<std::string>& commandArgs, FILE* outStream, FILE* /*errorStream*/) {
        auto it = commandArgs.begin();
        auto processor = processors.find(*it);
        if (processor != processors.end()) {
            std::ostringstream textStream;
            while (++it != commandArgs.end()) {
                textStream << *it << " ";
            }
            std::string text = textStream.str();
            auto input = std::vector<char>(text.begin(), text.end());
            auto output = processor->second->process(input);
            std::string s(output.begin(), output.end());
            fprintf(outStream, "%s\n", s.c_str());
        }
    }
private:
    ProcessorConsumer() = default;

    std::mutex mutex{}; //protects below
    std::map<std::string, std::shared_ptr<processor::IProcessor>> processors{};
};

class BringUpActivator {
public:
    explicit BringUpActivator(const std::shared_ptr<celix::BundleContext>& ctx) :
        processorConsumer{ProcessorConsumer::create()}, tracker{createTracker(ctx)} {
        std::cout << "Started Bring Up from bundle with id " << ctx->getBundleId() << std::endl;
        auto reg = ctx->registerService<celix::IShellCommand>(processorConsumer)
                .addProperty(celix::IShellCommand::COMMAND_NAME, "bringup")
                .build();
        regs.push_back(reg);
    }

    ~BringUpActivator() noexcept {
        std::cout << "Finished Bring Up" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};
    std::shared_ptr<celix::GenericServiceTracker> createTracker(const std::shared_ptr<celix::BundleContext>& ctx) {
        return ctx->trackServices<processor::IProcessor>()
                .addSetCallback(std::bind(&ProcessorConsumer::addProcessor, processorConsumer, std::placeholders::_1))
                .build();
    }

    const std::shared_ptr<ProcessorConsumer> processorConsumer;
    const std::shared_ptr<celix::GenericServiceTracker> tracker;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(BringUpActivator)