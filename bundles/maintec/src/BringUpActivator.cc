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

    void removeProcessor(std::shared_ptr<processor::IProcessor> _processor) {
        std::lock_guard<std::mutex> lck{mutex};
        processors.erase(_processor->getName());
    }

    void executeCommand(const std::string&, const std::vector<std::string>& commandArgs, FILE* outStream, FILE* /*errorStream*/) {
        auto it = commandArgs.begin();

        std::unique_lock<std::mutex> lck{mutex,  std::defer_lock};
        lck.lock();
        auto localProcessor = processors.find(*it);
        lck.unlock();

        if (localProcessor != processors.end()) {
            std::ostringstream textStream;
            while (++it != commandArgs.end()) {
                textStream << *it << " ";
            }
            std::string text = textStream.str();
            auto input = std::vector<char>(text.begin(), text.end());
            auto output = localProcessor->second->process(input);
            std::string s(output.begin(), output.end());
            fprintf(outStream, "%s\n", s.c_str());
        } else {
            fprintf(outStream, "Bring Up not available.\n");
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
                .addAddCallback(std::bind(&ProcessorConsumer::addProcessor, processorConsumer, std::placeholders::_1))
                .addRemCallback(std::bind(&ProcessorConsumer::removeProcessor, processorConsumer, std::placeholders::_1))
                .build();
    }

    const std::shared_ptr<ProcessorConsumer> processorConsumer;
    const std::shared_ptr<celix::GenericServiceTracker> tracker;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(BringUpActivator)