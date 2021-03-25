#ifndef PROCESSOR_SERVICE_H_
#define PROCESSOR_SERVICE_H_

#define PROCESSOR_SERVICE              "com.garani.maintec.api.Processor"
#define PROCESSOR_CONFIGURATION_TYPE   "org.amdatu.remote.admin.http"

typedef struct processor_service processor_service_t;

struct processor_service {
    void *handle;
    int (*process)(void *handle, char *input, char **output);
};

#endif /* PROCESSOR_SERVICE_H_ */