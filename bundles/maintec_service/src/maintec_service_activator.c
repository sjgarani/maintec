#include <stdlib.h>
#include <celix_api.h>
#include "process_impl.h"
#include "remote_constants.h"

struct activator {
    process_t *maintec;
    processor_service_t service;
    long svcId;
};

celix_status_t maintecBndStart(struct activator *act, celix_bundle_context_t *ctx) {
    act->svcId = -1L;
    act->maintec = process_create();
    if (act->maintec != NULL) {
        act->service.handle = act->maintec;
        act->service.process = (void*)process_impl;

        celix_properties_t *properties = celix_properties_create();
        celix_properties_set(properties, OSGI_RSA_SERVICE_EXPORTED_INTERFACES, PROCESSOR_SERVICE);
        celix_properties_set(properties, OSGI_RSA_SERVICE_EXPORTED_CONFIGS, PROCESSOR_CONFIGURATION_TYPE);

        act->svcId = celix_bundleContext_registerService(ctx, &act->service, PROCESSOR_SERVICE, properties);
    }
    return CELIX_SUCCESS;
}

celix_status_t maintecBndStop(struct activator *act, celix_bundle_context_t *ctx) {
    celix_bundleContext_unregisterService(ctx, act->svcId);
    if (act->maintec != NULL) {
        process_destroy(act->maintec);
    }
    return CELIX_SUCCESS;
}

CELIX_GEN_BUNDLE_ACTIVATOR(struct activator, maintecBndStart, maintecBndStop);
