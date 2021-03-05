#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include "celix/BundleActivator.h"

using json = nlohmann::json;
using namespace sw::redis;

class MaintecActivator {
public:
    explicit MaintecActivator(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Started Maintec from bundle with id " << ctx->getBundleId() << std::endl;
        auto redis = Redis("tcp://127.0.0.1:6379");

        std::string project = "maintec";
        if (redis.exists(project) == 0) {
            json data =  R"(
                {
                    "dataA": "dataA",
                    "dataB": 1,
                    "dataC": {
                        "data1": "data1",
                        "data2": 2
                    },
                    "dataD": ["datax"]
                }
            )"_json;
            redis.set(project, data.dump());
        }
    }

    ~MaintecActivator() noexcept {
        std::cout << "Finished Maintec" << std::endl;
    }
private:
    std::vector<std::shared_ptr<celix::ServiceRegistration>> regs{};
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(MaintecActivator)