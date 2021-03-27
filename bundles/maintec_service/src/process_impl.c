#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    printf("Input: %s\n", input);
    char result[] = "Result: echo: ";
    *output = malloc(sizeof(result) + 1);
    strcpy(*output, result);
    printf("Maintec: %s\n", *output);
    return status;
}
