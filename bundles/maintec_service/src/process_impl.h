#ifndef MAINTEC_IMPL_H_
#define MAINTEC_IMPL_H_

#include "celix_errno.h"
#include "processor_service.h"

typedef struct process {
} process_t;

process_t* process_create(void);
void process_destroy(process_t *maintec);
int process_impl(process_t *maintec, char *input, char **output);

#endif /* MAINTEC_IMPL_H_ */
