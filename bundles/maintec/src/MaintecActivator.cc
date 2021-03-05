#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "celix/BundleActivator.h"

using json = nlohmann::json;

class MaintecActivator {
public:
    explicit MaintecActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started Maintec from bundle with id " << ctx->getBundleId() << std::endl;
    }

    ~MaintecActivator() noexcept {
        std::cout << "Finished Maintec" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(MaintecActivator)