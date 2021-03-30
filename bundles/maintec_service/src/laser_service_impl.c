#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "laser_service_impl.h"

bool laser_state = false;

laser_t* laser_create(void) {
    struct laser *tmp = calloc(1, sizeof(*tmp));
    return tmp;
}

void laser_destroy(laser_t *laser) {
    free(laser);
}

int laser_setState(laser_t *laser __attribute__((unused)), bool input) {
    int status = CELIX_SUCCESS;

    laser_state = input;
    printf("Laser state: %d\n", laser_state);

    return status;
}

int laser_getState(laser_t *laser __attribute__((unused)), bool *output) {
    int status = CELIX_SUCCESS;

    *output = laser_state;
    printf("Laser state: %d\n", *output);

    return status;
}