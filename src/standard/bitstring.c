#include <string.h>
#include <strings.h>

#include <cast.h>
#include <echidna.h>
#include <function.h>
#include <parameter.h>
#include <runtime.h>
#include <standard.h>
#include <ll.h>
#include <value.h>


static int _standard_bitstring_roll(int Op, LL *Parameters, VALUE *Result);

static int _standard_bitstring_shift(int Op, LL *Parameters, VALUE *Result);


static int
_standard_bitstring_roll(int Op, LL *Parameters, VALUE *Result) {
    PARAMETER *pParameter;
    VALUE sCount, sValue;
    uint64_t uCount, uValue;
    size_t uParameter;

    Result->Type = TYPE_NONE;
    value_initialise(&sCount);
    value_initialise(&sValue);

    uParameter = 0;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(pParameter->Name) {
            if(strcasecmp(pParameter->Name, "IN") == 0) {
                if((pParameter->Value.Type & ANY_BIT) == 0)
                    return ERROR_PARAMETER_TYPE;
                value_copy(&sValue, &pParameter->Value);
            }
            else if(strcasecmp(pParameter->Name, "N") == 0) {
                if((pParameter->Value.Type & ANY_INT) == 0)
                    return ERROR_PARAMETER_TYPE;
                value_copy(&sCount, &pParameter->Value);
            }
        }
        else {
            //  Unnamed function parameters - ANY_BIT, ANY_INT
            switch(uParameter++) {
                case 0:
                    if((pParameter->Value.Type & ANY_BIT) == 0)
                        return ERROR_PARAMETER_TYPE;
                    value_copy(&sValue, &pParameter->Value);
                    break;

                case 1:
                    if((pParameter->Value.Type & ANY_INT) == 0)
                        return ERROR_PARAMETER_TYPE;
                    value_copy(&sCount, &pParameter->Value);
                    break;

                default:
                    return ERROR_PARAMETER_COUNT;
            }
        }
    }

    if(cast_ulint(&sCount) != 0)
        return ERROR_PARAMETER_TYPE;
    uCount = sCount.Value.U64;

    switch(sValue.Type & ~ANY_INTERNAL) {
        case TYPE_LWORD:
            while(uCount-- > 0) {
                if(Op) {
                    uValue = ((sValue.Value.B64 & 1) != 0);
                    sValue.Value.B64 >>= 1;
                    sValue.Value.B64 |= (uValue<<63);
                }
                else {
                    uValue = ((sValue.Value.B64 & (1ull<<63)) != 0);
                    sValue.Value.B64 <<= 1;
                    sValue.Value.B64 |= uValue;
                }
            }
            break;

        case TYPE_DWORD:
            while(uCount-- > 0) {
                if(Op) {
                    uValue = ((sValue.Value.B32 & 1) != 0);
                    sValue.Value.B32 >>= 1;
                    sValue.Value.B32 |= (uValue<<31);
                }
                else {
                    uValue = ((sValue.Value.B32 & (1ul<<31)) != 0);
                    sValue.Value.B32 <<= 1;
                    sValue.Value.B32 |= uValue;
                }
            }
            break;

        case TYPE_WORD:
            while(uCount-- > 0) {
                if(Op) {
                    uValue = ((sValue.Value.B16 & 1) != 0);
                    sValue.Value.B16 >>= 1;
                    sValue.Value.B16 |= (uValue<<15);
                }
                else {
                    uValue = ((sValue.Value.B16 & (1u<<15)) != 0);
                    sValue.Value.B16 <<= 1;
                    sValue.Value.B16 |= uValue;
                }
            }
            break;

        case TYPE_BYTE:
            while(uCount-- > 0) {
                if(Op) {
                    uValue = ((sValue.Value.B8 & 1) != 0);
                    sValue.Value.B8 >>= 1;
                    sValue.Value.B8 |= (uValue<<7);
                }
                else {
                    uValue = ((sValue.Value.B8 & (1u << 7)) != 0);
                    sValue.Value.B8 <<= 1;
                    sValue.Value.B8 |= uValue;
                }
            }
            break;
            
        case TYPE_BOOL:
            break;

        default:
            return ERROR_PARAMETER_TYPE;
    }
    value_copy(Result, &sValue);
    return 0;
}


static int
_standard_bitstring_shift(int Op, LL *Parameters, VALUE *Result) {
    PARAMETER *pParameter;
    VALUE sCount, sValue;
    size_t uParameter;
    int nResult;

    Result->Type = TYPE_NONE;

    uParameter = 0;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(pParameter->Name) {
            if(strcasecmp(pParameter->Name, "IN") == 0) {
                if((pParameter->Value.Type & ANY_BIT) == 0)
                    return ERROR_PARAMETER_TYPE;
                value_copy(&sValue, &pParameter->Value);
            }
            else if(strcasecmp(pParameter->Name, "N") == 0) {
                if((pParameter->Value.Type & ANY_INT) == 0)
                    return ERROR_PARAMETER_TYPE;
                value_copy(&sCount, &pParameter->Value);
                if((nResult = cast_usint(&sCount)) != 0)
                    return nResult;
            }
        }
        else {
            //  Unnamed function parameters - ANY_BIT, ANY_INT
            switch(uParameter++) {
                case 0:
                    if((pParameter->Value.Type & ANY_BIT) == 0)
                        return ERROR_PARAMETER_TYPE;
                    value_copy(&sValue, &pParameter->Value);
                    break;

                case 1:
                    if((pParameter->Value.Type & ANY_INT) == 0)
                        return ERROR_PARAMETER_TYPE;
                    value_copy(&sCount, &pParameter->Value);
                    if((nResult = cast_usint(&sCount)) != 0)
                        return nResult;
                    break;

                default:
                    return ERROR_PARAMETER_COUNT;
            }
        }
    }

    switch(sValue.Type & ~ANY_INTERNAL) {
        case TYPE_LWORD:
            if(sCount.Value.U8 > 63) {
                sValue.Value.B64 = 0;
                break;
            }
            if(Op) 
                sValue.Value.B64 >>= sCount.Value.U8;
            else
                sValue.Value.B64 <<= sCount.Value.U8;
            break;

        case TYPE_DWORD:
            if(sCount.Value.U8 > 31) {
                sValue.Value.B32 = 0;
                break;
            }
            if(Op) 
                sValue.Value.B32 >>= sCount.Value.U8; 
            else
                sValue.Value.B32 <<= sCount.Value.U8;
            break;

        case TYPE_WORD:
            if(sCount.Value.U8 > 15) {
                sValue.Value.B16 = 0;
                break;
            }
            if(Op)
                sValue.Value.B16 >>= sCount.Value.U8;
            else
                sValue.Value.B16 <<= sCount.Value.U8;
            break;

        case TYPE_BYTE:
            if(sCount.Value.U8 > 7) {
                sValue.Value.B8 = 0;
                break;
            }
            if(Op)
                sValue.Value.B8 >>= sCount.Value.U8;
            else
                sValue.Value.B8 <<= sCount.Value.U8; 
            break;

        case TYPE_BOOL:
            sValue.Value.B1 = 0;
            break;

        default:
            return ERROR_PARAMETER_TYPE;
    }
    value_copy(Result, &sValue);
    return 0;
}


int
standard_rol(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_bitstring_roll(0, Parameters, Result);
}


int
standard_ror(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_bitstring_roll(1, Parameters, Result);
}


int
standard_shl(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_bitstring_shift(0, Parameters, Result);
}


int
standard_shr(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_bitstring_shift(1, Parameters, Result);
}


