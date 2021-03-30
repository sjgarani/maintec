#ifndef LASER_SERVICE_H_
#define LASER_SERVICE_H_

#include <stdbool.h>

#define LASER_SERVICE              "com.garani.maintec.api.Laser"
#define LASER_CONFIGURATION_TYPE   "org.amdatu.remote.admin.http"

typedef struct laser_service laser_service_t;

struct laser_service {
    void *handle;
    void (*setState)(void *handle, bool state);
    bool (*getState)(void *handle);
};

#endif /* LASER_SERVICE_H_ */