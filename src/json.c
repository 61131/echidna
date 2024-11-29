#ifndef JSON_DISABLED
#include <stdio.h>
#include <limits.h>
#include <jansson.h>

#include <grammar.h>
#include <json.h>
#include <symbol.h>
#include <value.h>


static json_t * _json_flags(VALUE_FLAG Flags);

static json_t * _json_token(TOKEN *Token);

static json_t * _json_type(VALUE_TYPE Type);

static json_t * _json_union(VALUE_TYPE Type, size_t Length, VALUE_UNION *Union);

static json_t * _json_value(VALUE *Value);


static json_t *
_json_flags(VALUE_FLAG Flags) {
    VALUE_FLAG sFlags[] = {
            FLAG_ARRAY,
            FLAG_ASSIGN,
            FLAG_CONSTANT,
            FLAG_NON_RETAIN,
            FLAG_RETAIN,
            FLAG_SUBRANGE,
            FLAG_F_EDGE,
            FLAG_R_EDGE,
    };
    char sLine[LINE_MAX];
    int nCount, nIndex;

    sLine[0] = '\0';
    nCount = (sizeof(sFlags) / sizeof(sFlags[0]));
    for(nIndex = 0; nIndex < nCount; ++nIndex) {
        if((Flags & sFlags[nIndex]) != sFlags[nIndex]) 
            continue;
        if(strlen(sLine) > 0)
            strcat(sLine, ",");
        switch(nIndex) {
            case 0:     strcat(sLine, "ARRAY"); break;
            case 1:     strcat(sLine, "ASSIGN"); break;
            case 2:     strcat(sLine, "CONSTANT"); break;
            case 3:     strcat(sLine, "NON_RETAIN"); break;
            case 4:     strcat(sLine, "RETAIN"); break;
            case 5:     strcat(sLine, "SUBRANGE"); break;
            case 6:     strcat(sLine, "F_EDGE"); break;
            case 7:     strcat(sLine, "R_EDGE"); break;
            default:
                break;
        }
    }
    if(strlen(sLine) == 0)
        strcat(sLine, "NONE");

    return json_string(sLine);
}


static json_t *
_json_token(TOKEN *Token) {
    TOKEN_LIST *pList;
    json_t *pArray, *pObj;
    char sLine[LINE_MAX];

    if(!Token)
        return NULL;
    if((pObj = json_object()) == NULL)
        return NULL;
    snprintf(sLine, sizeof(sLine), "%s(%u), %p",
            yytokenname(Token->Id),
            Token->Id,
            Token);
    json_object_set(pObj, "Id", json_string(sLine));
    if(Token->Name)
        json_object_set(pObj, "Name", json_string(Token->Name));
    json_object_set(pObj, "Value", _json_value(&Token->Value));

    switch(Token->Type) {
        case TYPE_LIST:
            pList = (TOKEN_LIST *) Token;
            json_object_set(pObj, "Size", json_integer(pList->List.Size));
            if((pArray = json_array()) == NULL) 
                return NULL;
            ll_reset(&pList->List);
            while((Token = ll_iterate(&pList->List)) != NULL)
                json_array_append(pArray, _json_token(Token));
            json_object_set(pObj, "Elements", pArray);
            /* break; */
        case TYPE_TOKEN:
        default:
            break;
    }
    return pObj;
}


static json_t *
_json_type(VALUE_TYPE Type) {
    char sStr[9];

    switch(Type) {
		case TYPE_NONE:         return json_string("NONE");
        case TYPE_REAL:         return json_string("REAL");
        case TYPE_LREAL:        return json_string("LREAL");
        case TYPE_LINT:         return json_string("LINT");
        case TYPE_DINT:         return json_string("DINT");
        case TYPE_INT:          return json_string("INT");
        case TYPE_SINT:         return json_string("SINT");
        case TYPE_ULINT:        return json_string("ULINT");
        case TYPE_UDINT:        return json_string("UDINT");
        case TYPE_UINT:         return json_string("UINT");
        case TYPE_USINT:        return json_string("USINT");
        case TYPE_LWORD:        return json_string("LWORD");
        case TYPE_DWORD:        return json_string("DWORD");
        case TYPE_WORD:         return json_string("WORD");
        case TYPE_BYTE:         return json_string("BYTE");
        case TYPE_BOOL:         return json_string("BOOL");
        case TYPE_STRING:       return json_string("STRING");
        case TYPE_WSTRING:      return json_string("WSTRING");
        case TYPE_TIME:         return json_string("TIME");
        case TYPE_DATE:         return json_string("DATE");
        case TYPE_DT:           return json_string("DT");
        case TYPE_TOD:          return json_string("TOD");
        case TYPE_DERIVED:      return json_string("DERIVED");
        case TYPE_ENUMERATED:   return json_string("ENUMERATED");
        case TYPE_SUBRANGE:     return json_string("SUBRANGE");
        case TYPE_STRUCTURED:   return json_string("STRUCTURED");
        case TYPE_FUNCTION:     return json_string("FUNCTION");
        case TYPE_FUNCTION_BLOCK:   return json_string("FUNCTION_BLOCK");
        case TYPE_LABEL:        return json_string("LABEL");
        case _TYPE_PROGRAM:     return json_string("PROGRAM");
        case TYPE_VARIABLE:     return json_string("VARIABLE");
        default:
            snprintf(sStr, sizeof(sStr), "%08x", Type);
            return json_string(sStr);
    }
}


static json_t * 
_json_union(VALUE_TYPE Type, size_t Length, VALUE_UNION *Union) {
    json_t *pObj;

    if((pObj = json_object()) == NULL) 
        return NULL;

    switch(Type) {
        case TYPE_LREAL:    json_object_set(pObj, "Double", json_real(Union->Double)); break;
        case TYPE_REAL:     json_object_set(pObj, "Single", json_real(Union->Single)); break;
        case TYPE_LINT:     json_object_set(pObj, "S64", json_integer(Union->S64)); break;
        case TYPE_DINT:     json_object_set(pObj, "S32", json_integer(Union->S32)); break;
        case TYPE_INT:      json_object_set(pObj, "S16", json_integer(Union->S16)); break;
        case TYPE_SINT:     json_object_set(pObj, "S8", json_integer(Union->S8)); break;
        case TYPE_ULINT:    json_object_set(pObj, "U64", json_integer(Union->U64)); break;
        case TYPE_UDINT:    json_object_set(pObj, "U32", json_integer(Union->U32)); break;
        case TYPE_UINT:     json_object_set(pObj, "U16", json_integer(Union->U16)); break;
        case TYPE_USINT:    json_object_set(pObj, "U8", json_integer(Union->U8)); break;
        case TYPE_LWORD:    json_object_set(pObj, "B64", json_integer(Union->B64)); break;
        case TYPE_DWORD:    json_object_set(pObj, "B32", json_integer(Union->B32)); break;
        case TYPE_WORD:     json_object_set(pObj, "B16", json_integer(Union->B16)); break;
        case TYPE_BYTE:     json_object_set(pObj, "B8", json_integer(Union->B8)); break;
        case TYPE_BOOL:     json_object_set(pObj, "B1", json_integer(Union->B1)); break;
        case TYPE_TIME:     json_object_set(pObj, "Time", json_real(Union->Time)); break;
        case TYPE_STRING:   json_object_set(pObj, "Pointer", json_string(Union->Pointer)); break;
        default:
            free(pObj);
            pObj = NULL;
    }

    return pObj;
}


static json_t * 
_json_value(VALUE *Value) {
    json_t *pObj, *pVal;

    if((pObj = json_object()) == NULL)
        return NULL;

    json_object_set(pObj, "Type", _json_type(Value->Type));
    json_object_set(pObj, "Length", json_integer(Value->Length));
    json_object_set(pObj, "Flags", _json_flags(Value->Flags));

    if((Value->Flags & FLAG_ARRAY) == 0) {
        if((pVal = _json_union(Value->Type, Value->Length, &Value->Value)) != NULL)
            json_object_set(pObj, "Value", pVal);
    }

    switch(Value->Type) {
        case TYPE_DERIVED:
        case TYPE_FUNCTION:
        case TYPE_FUNCTION_BLOCK:
        case _TYPE_PROGRAM:
        case TYPE_VARIABLE:
            json_object_set(pObj, "Meta", json_string((char *) Value->Meta));
            break;

        default:
            break;
    }

    return pObj;
}


void
json_symbol_dump(ECHIDNA *Context) {
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol;
    json_t *pArray, *pObj;
    uint32_t uIndex;
    char *pOut;

    if((pArray = json_array()) == NULL)
        return;

    pSymbols = &Context->Symbols;
    for(uIndex = 0; uIndex < pSymbols->Count; ++uIndex) {

        if((pObj = json_object()) == NULL)
            return;

        pSymbol = pSymbols->Symbol[uIndex];
        json_object_set(pObj, "Id", json_integer(pSymbol->Id));
        json_object_set(pObj, "Offset", json_integer(pSymbol->Offset));
        json_object_set(pObj, "Name", json_string(pSymbol->Name));
        json_object_set(pObj, "Path", json_string(pSymbol->Path));

        if(pSymbol->POU)
            json_object_set(pObj, "POU", json_string(pSymbol->POU));
        if(pSymbol->Resource)
            json_object_set(pObj, "Resource", json_string(pSymbol->Resource));
        if(pSymbol->POU)
            json_object_set(pObj, "Configuration", json_string(pSymbol->Configuration));

        json_object_set(pObj, "Ref", json_integer(pSymbol->Ref));
        json_object_set(pObj, "Value", _json_value(&pSymbol->Value));
        json_array_append(pArray, pObj);
    }

    if((pOut = json_dumps(pArray, JSON_INDENT(2) | JSON_PRESERVE_ORDER)) != NULL) {
        fprintf(stdout, "%s\n", pOut);
        fflush(stdout);
        free(pOut);
    }
}


void
json_token_dump(TOKEN *Token) {
    json_t *pObj;
    char *pOut;

    if((pObj = _json_token(Token)) == NULL)
        return;
    if((pOut = json_dumps(pObj, JSON_INDENT(2) | JSON_PRESERVE_ORDER)) != NULL) {
        fprintf(stdout, "%s\n", pOut);
        fflush(stdout);
        free(pOut);
    }
}


void
json_value_dump(VALUE *Value) {
    json_t *pValue;
    char *pOut;

    pValue = _json_value(Value);
    if((pOut = json_dumps(pValue, JSON_INDENT(2) | JSON_PRESERVE_ORDER)) == NULL)
        return;
    fprintf(stdout, "%s\n", pOut);
    fflush(stdout);
    free(pOut);
}


#endif
