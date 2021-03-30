#include <stdlib.h>
#include <celix_api.h>
#include "laser_service_impl.h"
#include "remote_constants.h"

struct activator {
    laser_t *laser;
    laser_service_t laser_service;
    long svcId;
};

celix_status_t maintecBndStart(struct activator *act, celix_bundle_context_t *ctx) {
    act->svcId = -1L;
    act->laser = laser_create();
    if (act->laser != NULL) {
        act->laser_service.handle = act->laser;
        act->laser_service.setState = (void*)laser_setState;
        act->laser_service.getState = (void*)laser_getState;

        celix_properties_t *properties = celix_properties_create();
        celix_properties_set(properties, OSGI_RSA_SERVICE_EXPORTED_INTERFACES, LASER_SERVICE);
        celix_properties_set(properties, OSGI_RSA_SERVICE_EXPORTED_CONFIGS, LASER_CONFIGURATION_TYPE);

        act->svcId = celix_bundleContext_registerService(ctx, &act->laser_service, LASER_SERVICE, properties);
    }
    return CELIX_SUCCESS;
}

celix_status_t maintecBndStop(struct activator *act, celix_bundle_context_t *ctx) {
    celix_bundleContext_unregisterService(ctx, act->svcId);
    if (act->laser != NULL) {
        laser_destroy(act->laser);
    }
    return CELIX_SUCCESS;
}

CELIX_GEN_BUNDLE_ACTIVATOR(struct activator, maintecBndStart, maintecBndStop);
