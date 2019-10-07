#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>

#include <bytecode.h>
#include <bytecode/label.h>
#include <log.h>


int 
bytecode_label_compare(void *A, void *B) {
    BYTECODE_LABEL *pA, *pB;

    pA = (BYTECODE_LABEL *) A;
    assert(pA != NULL);
    pB = (BYTECODE_LABEL *) B;
    assert(pB != NULL);
    return strcasecmp(pA->Name, pB->Name);
}


void
bytecode_label_destroy(void *Arg) {
    BYTECODE_LABEL *pLabel;

    if((pLabel = (BYTECODE_LABEL *) Arg) == NULL)
        return;
    free(pLabel->Position);
    free(pLabel);
}


void
bytecode_label_initialise(BYTECODE_LABEL *Label, char *Name) {
    Label->Name = Name;
    Label->PC = 0;
    Label->Count = 0;
    Label->Position = NULL;
}


BYTECODE_LABEL * 
bytecode_label_new(char *Name) {
    BYTECODE_LABEL *pLabel;

    if((pLabel = (BYTECODE_LABEL *) calloc(1, sizeof(BYTECODE_LABEL))) == NULL) {
        log_critical( "Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    bytecode_label_initialise(pLabel, Name);
    return pLabel;
}
