//${WS}/maintec/bundles/maintec/src/HelloWorldActivator.cc
#include <memory>
#include <iostream>

#include <celix_api.h>

namespace /*anon*/ {

    class MaintecActivator {
    public:
        MaintecActivator(std::shared_ptr<celix::dm::DependencyManager> _mng) : mng{_mng} {
            std::cout << "Maintec bundle with id " << bndId() << std::endl;
        }
        ~MaintecActivator() {
            std::cout << "Goodbye Maintec bundle with id " << bndId() << std::endl;
        }
    private:
        long bndId() const {
            return celix_bundle_getId(celix_bundleContext_getBundle(mng->bundleContext()));
        }

        std::shared_ptr<celix::dm::DependencyManager> mng;
    };

}

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(MaintecActivator)