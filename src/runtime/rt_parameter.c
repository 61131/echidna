#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <log.h>
#include <runtime.h>
#include <runtime/parameter.h>
#include <value.h>


void
runtime_parameter_destroy(void *Arg) {
    RUNTIME_PARAMETER *pParameter;

    if((pParameter = (RUNTIME_PARAMETER *) Arg) == NULL)
        return;
    value_destroy(&pParameter->Parameter.Value);
    value_destroy(&pParameter->Value);
    if(pParameter->Parameter.Name != NULL)
        free((char *) pParameter->Parameter.Name);
    free(pParameter);
}


RUNTIME_PARAMETER *
runtime_parameter_new(void) {
    RUNTIME_PARAMETER *pParameter;

    errno = 0;
    if((pParameter = calloc(1, sizeof(RUNTIME_PARAMETER))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pParameter->Id = pParameter->Internal = -1;
    pParameter->Type = TYPE_NONE;
    value_initialise(&pParameter->Value);
    value_initialise(&pParameter->Parameter.Value);
    pParameter->Parameter.Name = NULL;

    return pParameter;
}

