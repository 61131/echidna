#define _DEFAULT_SOURCE         //  Required for timegm since glibc 2.19

#include <strings.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <value.h>


enum _TIME_OP { OP_ADD, OP_SUB, OP_MUL, OP_DIV };


static int
_standard_time(int Operation, VALUE_TYPE Pri, VALUE_TYPE Sec, LL *Parameters, VALUE *Result) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    VALUE_TYPE uType;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    if(Parameters->Size < 2)
        return ERROR_PARAMETER_COUNT;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        uType = pParameter->Value.Type;
        if(sValue.Type == TYPE_NONE) {
            if((uType & Pri) != uType)
                return ERROR_PARAMETER_TYPE;
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        if((uType & Sec) != uType)
            return ERROR_PARAMETER_TYPE;
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_TIME:
                switch(Operation) {
                    case OP_ADD:    sValue.Value.Time += sIn.Value.Time; break;
                    case OP_SUB:    sValue.Value.Time -= sIn.Value.Time; break;
                    case OP_MUL:    sValue.Value.Time *= sIn.Value.Time; break;
                    case OP_DIV:    
                        if(sIn.Value.Time == 0.0f)
                            return ERROR_DIVIDE_ZERO;
                        sValue.Value.Time /= sIn.Value.Time;
                        break;

                    default:
                        break;
                }
                break;

            case TYPE_DATE:
                assert(Operation == OP_SUB);
                if(Parameters->Size != 2)
                    return ERROR_PARAMETER_COUNT;
                sValue.Value.DateTime -= sIn.Value.DateTime;
                value_cast(&sValue, TYPE_TIME);
                goto finish;

            case TYPE_DT:
                switch(Operation) {
                    case OP_ADD:
                        sValue.Value.DateTime += sIn.Value.DateTime;
                        break;

                    case OP_SUB:    //  SUB_DT_DT, SUB_DT_TIME
                        if(uType == TYPE_DT) {
                            if(Parameters->Size != 2)
                                return ERROR_PARAMETER_COUNT;
                            sValue.Value.DateTime -= sIn.Value.DateTime;
                            value_cast(&sValue, TYPE_TIME);
                            goto finish;
                        }
                        sValue.Value.DateTime -= sIn.Value.DateTime;
                        break;

                    default:
                        break;
                }
                break;

            case TYPE_TOD:
                switch(Operation) {
                    case OP_ADD:
                        sValue.Value.DateTime += sIn.Value.DateTime;
                        break;

                    case OP_SUB:    //  SUB_TOD_TIME, SUB_TOD_TOD
                        if(uType == TYPE_TOD) {
                            if(Parameters->Size != 2)
                                return ERROR_PARAMETER_COUNT;
                            sValue.Value.DateTime -= sIn.Value.DateTime;
                            value_cast(&sValue, TYPE_TIME);
                            goto finish;
                        }
                        sValue.Value.DateTime -= sIn.Value.DateTime;
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }

finish:
    value_copy(Result, &sValue);
    return 0;
}


int
standard_add_dttime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_ADD, TYPE_DT, TYPE_TIME, Parameters, Result);
}


int
standard_add_time(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_ADD, TYPE_TIME, TYPE_TIME, Parameters, Result);
}


int
standard_add_todtime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_ADD, TYPE_TOD, TYPE_TIME, Parameters, Result);
}


int
standard_concat_datetod(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    struct tm sResult, sTime;
    int nIndex;

    Result->Type = TYPE_NONE;
    memset(&sResult, 0, sizeof(sResult));
    nIndex = 0;

    if(Parameters->Size != 2)
        return ERROR_PARAMETER_COUNT;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        switch(nIndex++) {
            case 0:
                if(pParameter->Value.Type != TYPE_DATE)
                    return ERROR_PARAMETER_TYPE;
                gmtime_r((const time_t *) &pParameter->Value.Value.DateTime, &sTime);
                sResult.tm_year = sTime.tm_year;
                sResult.tm_mon = sTime.tm_mon;
                sResult.tm_mday = sTime.tm_mday;
                break;

            case 1:
                if(pParameter->Value.Type != TYPE_TOD)
                    return ERROR_PARAMETER_TYPE;
                gmtime_r((const time_t *) &pParameter->Value.Value.DateTime, &sTime);
                sResult.tm_hour = sTime.tm_hour;
                sResult.tm_min = sTime.tm_min;
                sResult.tm_sec = sTime.tm_sec;
                break;

            default:
                break;
        }
    }

    value_assign(Result, TYPE_DT, timegm(&sResult));
    return 0;
}


int
standard_divtime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_DIV, TYPE_TIME, ANY_NUM, Parameters, Result);
}


int
standard_multime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_MUL, TYPE_TIME, ANY_NUM, Parameters, Result);
}


int
standard_sub_datedate(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_SUB, TYPE_DATE, TYPE_DATE, Parameters, Result);
}


int
standard_sub_dtdt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_SUB, TYPE_DT, TYPE_DT, Parameters, Result);
}


int
standard_sub_dttime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_SUB, TYPE_DT, TYPE_TIME, Parameters, Result);
}


int
standard_sub_time(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_SUB, TYPE_TIME, TYPE_TIME, Parameters, Result);
}


int
standard_sub_todtime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_SUB, TYPE_TOD, TYPE_TIME, Parameters, Result);
}


int
standard_sub_todtod(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    return _standard_time(OP_SUB, TYPE_TOD, TYPE_TOD, Parameters, Result);
}


