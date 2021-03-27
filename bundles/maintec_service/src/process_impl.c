#include <math.h>

#include <stdlib.h>
#include <stdio.h>

#include "process_impl.h"

process_t* process_create(void) {
    struct process *tmp = calloc(1, sizeof(*tmp));
    return tmp;
}

void process_destroy(process_t *process) {
    free(process);
}

int process_impl(process_t *process __attribute__((unused)), char *input, char **output) {
    int status = CELIX_SUCCESS;

    output = malloc(strlen(input));
    strcpy(output, input);
    printf("Maintec: %s\n", *output);

    return status;
}
