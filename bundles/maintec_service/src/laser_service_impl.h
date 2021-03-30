#ifndef LASER_IMPL_H_
#define LASER_IMPL_H_

#include <stdbool.h>
#include "celix_errno.h"
#include "laser_service.h"

typedef struct laser {
} laser_t;

laser_t* laser_create(void);
void laser_destroy(laser_t *maintec);

int laser_setState(laser_t *maintec, bool input);
int laser_getState(laser_t *maintec, bool *output);

#endif /* LASER_IMPL_H_ */
