#include <runtime.h>


static char * _Error[] = {
    "None",
    "Internal",
    "Internal allocation",
    "Internal read",
    "Internal write",
    "Invalid bytecode",
    "Invalid symbol",
    "Invalid function",
    "Invalid length",
    "Divide by zero",
    "Modulus by zero",
    "Math overflow",
    "Operand type",
    "Parameter count",
    "Parameter mismatch",
    "Parameter range",
    "Parameter type",
    "Parameter unknown",
    "Stack overflow",
    "Unimplemented",

    NULL
};


const char *
runtime_errortostr(int Error) {
    int nCount;

    nCount = sizeof(_Error) / sizeof(_Error[0]);
    if((Error < 0) ||
            (Error >= nCount))
        return NULL;
    return _Error[Error];
}

