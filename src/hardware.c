#include <hardware.h>


void
hardware_destroy(ECHIDNA *Context) {
}


int
hardware_initialise(ECHIDNA *Context) {
    int nResult;

    nResult = 0;
#ifdef HARDWARE_PIFACE
    nResult = piface_initialise(Context);
#endif
    return nResult;
}

