/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "celix_api.h"
#include "process_command.h"
#include "processor_service.h"
#include "celix_utils.h"


struct process_callback_data {
    char *input;
    char *output;
    int rc;
};

static void processCallback(void *handle, void *svc) {
    struct process_callback_data *data = handle;
    processor_service_t *processor = svc;
    data->rc = processor->process(processor->handle, data->input, &data->output);
}

bool processCommand_execute(void *handle, const char *const_line, FILE *out, FILE *err) {
    bool ok = true;
    celix_bundle_context_t *context = handle;

    char *line = celix_utils_strdup(const_line);

    char *token = line;
    strtok_r(line, " ", &token);
    char *inputStr = strtok_r(NULL, " ", &token);

    struct process_callback_data data;
    data.input = inputStr;
    data.output = NULL;
    data.rc = 0;
    bool called = celix_bundleContext_useService(context, PROCESSOR_SERVICE, &data, processCallback);
    if (called && data.rc == 0) {
        fprintf(out, "Processor response: %s\n", data.output);
    } else if (!called) {
        fprintf(err, "Processor service not available\n");
        ok = false;
    } else {
        fprintf(err, "Unexpected exception in Processor service\n");
        ok = false;
    }

    free(line);
    return ok;
}
