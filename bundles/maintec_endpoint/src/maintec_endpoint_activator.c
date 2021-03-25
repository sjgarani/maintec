#include <stdlib.h>
#include <string.h>


#include "celix_shell_command.h"
#include "celix_api.h"

#include "process_command.h"

typedef struct maintec_endpoint_activator {
    long processCmdSvcId;
    celix_shell_command_t processCmd;
} maintec_endpoint_activator_t;

static celix_status_t maintecShell_start(maintec_endpoint_activator_t *activator, celix_bundle_context_t *ctx) {
    activator->processCmd.handle = ctx;
    activator->processCmd.executeCommand = processCommand_execute;
    celix_properties_t *props = celix_properties_create();
    celix_properties_set(props, CELIX_SHELL_COMMAND_NAME, "process");
    activator->processCmdSvcId = celix_bundleContext_registerService(ctx, &activator->processCmd, CELIX_SHELL_COMMAND_SERVICE_NAME, props);

    return CELIX_SUCCESS;
}

static celix_status_t maintecShell_stop(maintec_endpoint_activator_t *activator, celix_bundle_context_t *ctx) {
    celix_bundleContext_unregisterService(ctx, activator->processCmdSvcId);
    return CELIX_SUCCESS;
}

CELIX_GEN_BUNDLE_ACTIVATOR(maintec_endpoint_activator_t, maintecShell_start, maintecShell_stop);
