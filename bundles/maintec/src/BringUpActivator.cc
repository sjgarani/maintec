#include <iostream>
#include "celix/BundleActivator.h"
#include "celix/IShellCommand.h"

class BringUpShellCommand : public celix::IShellCommand {
public:
    void executeCommand(const std::string&, const std::vector<std::string>& commandArgs, FILE* outStream, FILE* /*errorStream*/) {
        fprintf(outStream, "Command Args Size: %i\n", commandArgs.size());
        for (auto arg : commandArgs) {
            fprintf(outStream, "Arg: %s\n", arg.c_str());
        }
    }
};

class BringUpActivator {
public:
    explicit BringUpActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Hello world from bundle with id " << ctx->getBundleId() << std::endl;
        auto reg = ctx->registerService<celix::IShellCommand>(std::make_shared<BringUpShellCommand>())
                .addProperty(celix::IShellCommand::COMMAND_NAME, "bringup")
                .build();
        regs.push_back(reg);
    }

    ~BringUpActivator() noexcept {
        std::cout << "Goodbye world" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(BringUpActivator)