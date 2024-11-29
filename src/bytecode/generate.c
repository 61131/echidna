#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include <block.h>
#include <bytecode.h>
#include <echidna.h>
#include <grammar.h>
#include <json.h>
#include <log.h>
#include <macros.h>
#include <symbol.h>
#include <token.h>
#include <tree.h>
#include <unit.h>


#define BYTECODE_STACK_MAX      (32)


#define bytecode_generate_label(...) _bytecode_generate_label(_NARG(__VA_ARGS__), __VA_ARGS__)


static int _bytecode_generate(ECHIDNA *Context, char *Config, char *Resource, char *Name, TOKEN_LIST *Tokens);

static BYTECODE_LABEL * _bytecode_generate_label(size_t Arg, TREE *Scope, char *Name, ...);

static int _bytecode_generate_function(ECHIDNA *Context, char *Config, char *Resource, char *Name, BLOCK *Block, TOKEN_LIST *List);

static int _bytecode_generate_parameter(ECHIDNA *Context, char *Config, char *Resource, char *Name, BLOCK *Block, TOKEN_LIST *List);

static int _bytecode_generate_value(ECHIDNA *Context, char *Config, char *Resource, char *Name, BLOCK *Block, VALUE *Value);


static int
_bytecode_generate(ECHIDNA *Context, char *Config, char *Resource, char *Name, TOKEN_LIST *Tokens) {
    BLOCK *pBlock;
    BYTECODE_LABEL *pLabel;
    BYTECODE_STACK *pPrevious, *pStack;
    BYTECODE_STACK sStack[BYTECODE_STACK_MAX];
    FUNCTION_REGISTER *pFunction;
    SYMBOL *pSymbol;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    TREE sLabels;
    TREE_ITER sIter;
    UNIT *pPOU;
    uint32_t uValue;
    int nIndex, nPosition, nResult, nSize, nStack;

    tree_initialise(&sLabels, bytecode_label_compare);
    if((pPOU = unit_create(Config, Resource, Name)) == NULL)
        return errno;
    assert(&pPOU->Block == (BLOCK *) pPOU); //  NB: This is _very_ important!
    pBlock = ( BLOCK * ) pPOU;

//json_token_dump( ( TOKEN * ) Tokens );
    nSize = BYTECODE_STACK_MAX;
    bytecode_stack_initialise(&sStack[0], Tokens);
    for(nStack = 0; nStack >= 0; --nStack) {

        pStack = &sStack[ nStack ];        
        while((pToken = token_list_iterate(pStack->List)) != NULL) {
            bytecode_stack_set(pStack, pToken);

            /*
                The following implements support for il_expr_operator operators as defined 
                within the IEC 61131-3 standard which support the use of simple instruction 
                list within parenthesis as an operand to the operator.
            */

            switch(pToken->Id) {
                case AND:       pStack->BC = BYTECODE_AND; break;
                case ANDN:      pStack->BC = BYTECODE_ANDN; break;
                case OR:        pStack->BC = BYTECODE_OR; break;
                case ORN:       pStack->BC = BYTECODE_ORN; break;
                case XOR:       pStack->BC = BYTECODE_XOR; break;
                case XORN:      pStack->BC = BYTECODE_XORN; break;
                case ADD:       pStack->BC = BYTECODE_ADD; break;
                case SUB:       pStack->BC = BYTECODE_SUB; break;
                case MUL:       pStack->BC = BYTECODE_MUL; break;
                case DIV:       pStack->BC = BYTECODE_DIV; break;
                case MOD:       pStack->BC = BYTECODE_MOD; break;
                case GT:        pStack->BC = BYTECODE_GT; break;
                case GE:        pStack->BC = BYTECODE_GE; break;
                case EQ:        pStack->BC = BYTECODE_EQ; break;
                case LT:        pStack->BC = BYTECODE_LT; break;
                case LE:        pStack->BC = BYTECODE_LE; break;
                case NE:        pStack->BC = BYTECODE_NE; break;
                case VAR:       continue;
                case 0:
                    if(nStack >= (nSize - 1)) {
                        nResult = -ENOMEM;
                        goto finish;
                    }
                    bytecode_stack_initialise(&sStack[++nStack], (TOKEN_LIST *) pToken);
                    pStack = &sStack[nStack];
                    continue;

                default:
                    pStack->BC = 0;
                    break;
            }

            /*
                If there is a label associated with the current operator, this location is 
                recorded for population in association with jump operations. This location 
                will be populated upon the completion of bytecode generation for the current 
                program organisation unit.
            */

            if(pToken->Name) {
                if((pLabel = bytecode_generate_label(&sLabels, pToken->Name)) == NULL) {
                    nResult = errno;
                    goto finish;
                }
                pLabel->PC = pBlock->End;
            }

            pList = (TOKEN_LIST *) pToken;

            if(pStack->BC != 0) {     //  True for expression operators

                /*
                    If the operand to the expression operator is a simple instruction list, the 
                    location of the current byte code is recorded and the stack incremented for 
                    the processing of this operand.
                */

                if(pList->List.Size > 0 ) {
                    pStack->BC |= S_MODIFIER(MODIFIER_PARENTHESIS);
                    if((nResult = bytecode_write(Context, pBlock, sizeof(pStack->BC), (char *) &pStack->BC)) != 0)
                        goto finish;
                    uValue = 0;
                    nPosition = pBlock->End;
                    if((nResult = bytecode_write(Context, pBlock, sizeof(uValue), (char *) &uValue)) != 0)
                        goto finish;

                    if(nStack >= (nSize - 1)) {
                        nResult = -ENOMEM;
                        goto finish;
                    }
                    bytecode_stack_initialise(&sStack[++nStack], pList, TYPE_NONE, pStack->BC, nPosition);
                    pStack = &sStack[nStack];
                    continue;
                }
            }
            else {
                switch(pToken->Id) {
                    case NOP:       pStack->BC = BYTECODE_NOP; break;
                    case LD:        pStack->BC = BYTECODE_LD; break;
                    case LDN:       pStack->BC = BYTECODE_LDN; break;
                    case ST:        pStack->BC = BYTECODE_ST; break;
                    case STN:       pStack->BC = BYTECODE_STN; break;
                    case NOT:       pStack->BC = BYTECODE_NOT; break;
                    case S:         pStack->BC = BYTECODE_S; break;
                    case R:         pStack->BC = BYTECODE_R; break;
                    case CD:        pStack->BC = BYTECODE_CD; break;
                    case CLK:       pStack->BC = BYTECODE_CLK; break;
                    case CU:        pStack->BC = BYTECODE_CU; break;
                    case IN:        pStack->BC = BYTECODE_IN; break;
                    case PT:        pStack->BC = BYTECODE_PT; break;
                    case PV:        pStack->BC = BYTECODE_PV; break;
                    case CAL:       
                        pStack->BC = BYTECODE_CAL;
                        pStack->BC |= S_VALUE(pList->List.Size);
                        break;

                    case CALC:      
                        pStack->BC = BYTECODE_CALC;
                        pStack->BC |= S_VALUE(pList->List.Size);
                        break;

                    case CALCN:     
                        pStack->BC = BYTECODE_CALCN;
                        pStack->BC |= S_VALUE(pList->List.Size);
                        break;

                    case JMP:           
                        pStack->BC = BYTECODE_JMP;
                        if(0) {
                        /* break; */
                    case JMPC:          
                            pStack->BC = BYTECODE_JMPC; 
                        } 
                        if(0) {
                        /* break; */
                    case JMPCN:         
                            pStack->BC = BYTECODE_JMPCN; 
                        }
                        assert(pToken->Value.Type == TYPE_LABEL);
                        assert(pToken->Value.Meta != NULL);
                        if((pLabel = bytecode_generate_label(&sLabels,
                                pToken->Value.Meta,
                                pBlock->End + sizeof(BYTECODE) + sizeof(VALUE_TYPE))) == NULL) {
                            nResult = errno;
                            goto finish;
                        }
                        break;

                    case RET:       pStack->BC = BYTECODE_RET; break;
                    case RETC:      pStack->BC = BYTECODE_RETC; break;
                    case RETCN:     pStack->BC = BYTECODE_RETCN; break;
                    case VAR:
                    case VAR_INPUT:
                    case VAR_IN_OUT:
                    case VAR_OUTPUT:
                        pStack->BC = BYTECODE_PARAMETER;
                        pStack->BC |= S_VALUE(pList->List.Size);
                        break;

                    default:
#ifndef JSON_DISABLED
                        json_token_dump(pToken);
#endif
                        assert(0);
                }
            }

            pFunction = NULL;
            pSymbol = NULL;

            switch(pStack->Type = pToken->Value.Type) {
                case TYPE_INPUT:
                case TYPE_IN_OUT:
                case TYPE_OUTPUT:
                case TYPE_LABEL:
                case TYPE_NONE:                
                    break;

                case TYPE_FUNCTION:
                    //  {CAL[CN]}{TYPE_FUNCTION}{uint32_t,function identifier}
                    if((pFunction = function_search(&Context->Functions, pToken->Value.Meta)) == NULL) {
                        log_error("Undefined function: %s [%u:%u]",
                                pToken->Value.Meta,
                                pToken->Line,
                                pToken->Column);
                        nResult = ENOENT;
                        goto finish;
                    }
                    break;

                case TYPE_FUNCTION_BLOCK:
                    //  {CAL[CN]}{TYPE_FUNCTION_BLOCK}{uint32_t,symbol identifier}
                    if((pSymbol = symbol_search(Context, Config, Resource, Name, (char *) pToken->Value.Meta)) == NULL) {
                        log_error("Undefined variable: %s [%u:%u]",
                                pToken->Value.Meta,
                                pToken->Line,
                                pToken->Column);
                        nResult = ENOENT;
                        goto finish;
                    }
                    assert(pSymbol->Value.Type == TYPE_FUNCTION_BLOCK);
                    if((pFunction = function_search(&Context->Functions, pSymbol->Value.Meta)) == NULL) {
                        log_error("Undefined function block: %s [%u:%u]",
                                (char *) pSymbol->Value.Meta,
                                pToken->Line,
                                pToken->Column);
                        nResult = ENOENT;
                        goto finish;
                    }
                    break;

                case TYPE_VARIABLE:
                    //  {...}{TYPE_VARIABLE}{uint32_t,symbol identifier}
                    if((pSymbol = symbol_search(Context, Config, Resource, Name, (char *) pToken->Value.Meta)) == NULL) {
                        log_error("Undefined variable: %s [%u:%u]",
                                pToken->Value.Meta,
                                pToken->Line,
                                pToken->Column);
                        nResult = ENOENT;
                        goto finish;
                    }
                    pStack->Type = (TYPE_VARIABLE | pSymbol->Value.Type);
                    /* break; */
                default:
                    if(bytecode_stack_cast(pStack, pToken) != 0)
                        goto finish;
                    break;
            }

            /*
                The following will write the operator bytecode that has been constructed and 
                optionally, the operand type and corresponding parameter. It should be noted 
                that bytecode generation for some operations could be optimised to remove the 
                writing of the operand type, as this may be of a fixed type for some operators.
                However for the generalisation of bytecode generation and interpretation, this 
                optimisation has been omitted.
            */

            //  {uint32_t,operator}{uint32_t,operand type}{value}
            if((nResult = bytecode_write(Context, pBlock, sizeof(pStack->BC), (char *) &pStack->BC)) != 0)
                goto finish;
            switch(pToken->Id) {
                case NOP:
                case RET:
                case RETC:
                case RETCN:
                    continue;
                default:
                    break;
            }

            if((nResult = bytecode_write(Context, pBlock, sizeof(pStack->Type), (char *) &pStack->Type)) != 0)
                goto finish;

            switch(pToken->Value.Type) {
                case TYPE_FUNCTION_BLOCK:
                    assert(pSymbol != NULL);
                    ++pSymbol->Ref;
                    /* break; */
                case TYPE_FUNCTION:
                    assert(pFunction != NULL);
                    uValue = (pToken->Value.Type == TYPE_FUNCTION_BLOCK) ? pSymbol->Id : pFunction->Id;
                    if((nResult = bytecode_write(Context, pBlock, sizeof(uValue), (char *) &uValue)) != 0)
                        goto finish;
                    _bytecode_generate_function(Context, Config, Resource, Name, pBlock, (TOKEN_LIST *) pToken);
                    break;

                case TYPE_VARIABLE:
                    assert(pSymbol != NULL);
                    uValue = pSymbol->Id;
                    if((nResult = bytecode_write(Context, pBlock, sizeof(uValue), (char *) &uValue)) != 0)
                        goto finish;
                    ++pSymbol->Ref;
                    break;

                case TYPE_INPUT:
                case TYPE_IN_OUT:
                case TYPE_OUTPUT:
                    _bytecode_generate_parameter(Context, Config, Resource, Name, pBlock, (TOKEN_LIST *) pToken);
                    continue;

                default:
                    if((nResult = _bytecode_generate_value(Context, Config, Resource, Name, pBlock, &pToken->Value)) != 0)
                        goto finish;
                    break;
            }
//block_dump( pBlock );
            bytecode_stack_type(pStack, pToken);
        }

        /*
            If the current frame has been generated by way of the processing of a simple 
            instruction list passed in parentheses to an expression operator, the 
            accumulator type at the completion of the processing of this simple 
            instruction list is populated into the value field of the expression operator 
            byte code. Note that the associated byte width is _not_ populated in the 
            byte code as this length is directly used within the run-time for the parsing 
            of operands to operators. There is no such literal operand for expression 
            operators which have simple instruction lists as parameters.
        */

        if( pStack->Position >= 0 ) {
            /* assert( nStack > 0 ); */
            pPrevious = &sStack[ nStack - 1 ];
            if( pPrevious->CR.Type != pStack->CR.Type ) {
                log_warn( "Expect run-time cast of %s operand from %s to %s [%u:%u]",
                        yytokenname( pPrevious->Id ),
                        value_typetostr( pStack->CR.Type ),
                        value_typetostr( pPrevious->CR.Type ),
                        pPrevious->Line,
                        pPrevious->Column );
            }

            pStack->BC = BYTECODE_PARENTHESIS;
            if( ( nResult = bytecode_write( Context, pBlock, sizeof( pStack->BC ), ( char * ) &pStack->BC ) ) != 0 )
                goto finish;
            uValue = pStack->CR.Type;
            memcpy( &pBlock->Data[ pStack->Position ], &uValue, sizeof( uValue ) );
        }
    }

    for( pLabel = tree_iterate_first( &sIter, &sLabels ); pLabel; pLabel = tree_iterate_next( &sIter ) ) {
        for( nIndex = 0; nIndex < pLabel->Count; ++nIndex ) {
            memcpy( &pBlock->Data[ pLabel->Position[ nIndex ] ], &pLabel->PC, sizeof( pLabel->PC ) );
        }
    }

    if(Context->Verbose > 0) {
        block_dump(pBlock);
        log_debug("%s: %u bytes", pBlock->Name, pBlock->End);
    }

    assert((void *)pBlock == (void *)pPOU);
    nResult = tree_insert(&Context->POU, pPOU);

finish:
    tree_destroy(&sLabels, bytecode_label_destroy);
    if(nResult != 0) 
        unit_destroy(pPOU);

    return nResult;
}


static int
_bytecode_generate_function( ECHIDNA *Context, char *pConfig, char *pResource, char *pName, BLOCK *pBlock, TOKEN_LIST *pList ) {
    TOKEN *pToken;
    uint32_t uValue;
    int nResult, nStyle;

    if( pList->List.Size == 0 )
        return 0;
#ifndef JSON_DISABLED
//json_token_dump( ( TOKEN * ) pList );
#endif

    /*
        The following code structure incorporates a for-loop within the iteration of 
        POU parameters. This is so that the encoding mechanism for POU parameters can 
        be determined from the first iteration without necessitating the separate 
        iteration and interrogration of the first POU parameter.
    */

    nStyle = 0;
    token_list_reset( pList );
    while( ( pToken = token_list_iterate( pList ) ) != NULL ) {
        for( ;; ) {
            switch( nStyle ) {
                case 2:     //  Named parameters
                    if( pToken->Name == NULL )
                        return EFAULT;
                    uValue = TYPE_PARAMETER;
                    if( ( nResult = bytecode_write( Context, pBlock, sizeof( uValue ), ( char * ) &uValue ) ) != 0 )
                        return nResult;
                    uValue = strlen( pToken->Name );
                    if( ( nResult = bytecode_write( Context, pBlock, sizeof( uValue ), ( char * ) &uValue ) ) != 0 )
                        return nResult;
                    if( ( nResult = bytecode_write( Context, pBlock, uValue, ( char * ) pToken->Name ) ) != 0 )
                        return nResult;
                    if(0) {
                case 1:     //  Ordered parameters
                        if( ( pToken->Name != NULL ) &&
                                ( ( pToken->Value.Type & TYPE_IN_OUT ) != 0 ) )
                            return EFAULT;
                    }
                    uValue = pToken->Value.Type;
                    if( ( nResult = bytecode_write( Context, pBlock, sizeof( uValue ), ( char * ) &uValue ) ) != 0 )
                        return nResult;
                    if( ( nResult = _bytecode_generate_value( Context, pConfig, pResource, pName, pBlock, &pToken->Value ) ) != 0 )
                        return nResult;
                    break;

                case 0:
                    nStyle = 1;
                    if( ( pToken->Name != NULL ) &&
                            ( ( pToken->Value.Type & TYPE_IN_OUT ) != 0 ) )
                        nStyle = 2;
                    continue;   //  Jump execution back to switch statement

                default:
                    assert(0);
            }
            break;
        }
    }

    return 0;
}


static BYTECODE_LABEL * 
_bytecode_generate_label(size_t Arg, TREE *Scope, char *Name, ...) {
    BYTECODE_LABEL sLabel, *pLabel;
    va_list sArg;
    size_t uCount;

    if(!Name)
        return NULL;
    for(;;) {
        bytecode_label_initialise(&sLabel, Name);
        if((pLabel = tree_search(Scope, &sLabel)) != NULL)
            break;
        
        if((pLabel = bytecode_label_new(Name)) != NULL) {
            if(tree_insert(Scope, pLabel) == 0)
                break;
            bytecode_label_destroy(pLabel);
        }
        return NULL;
    }

    if(Arg > 2) {
        uCount = (pLabel->Count + 1) * sizeof(uint32_t);
        if((pLabel->Position = realloc(pLabel->Position, uCount)) == NULL) {
            bytecode_label_destroy(pLabel);
            return NULL;
        }

        va_start(sArg, Name);
        pLabel->Position[pLabel->Count++] = (uint32_t) va_arg(sArg, int);
        va_end(sArg);
    }
    return pLabel;
}


static int 
_bytecode_generate_parameter(ECHIDNA *Context, char *Config, char *Resource, char *Name, BLOCK *Block, TOKEN_LIST *List) {
    SYMBOL *pSymbol;
    TOKEN *pToken;
    uint32_t uId;
    int nResult;

    assert(List->List.Size > 0);
    token_list_reset(List);
    while((pToken = token_list_iterate(List)) != NULL) {
        if((pSymbol = symbol_search(Context, Config, Resource, Name, pToken->Name)) == NULL)
            return ENOENT;
        uId = pSymbol->Id;
        if((nResult = bytecode_write(Context, Block, sizeof(uId), (char *) &uId)) != 0)
            return nResult;
        ++pSymbol->Ref;
    }
    return 0;
}


static int
_bytecode_generate_value(ECHIDNA *Context, char *Config, char *Resource, char *Name, BLOCK *Block, VALUE *Value) {
    SYMBOL *pSymbol;
    uint32_t uValue;
    int nResult;

    switch(Value->Type & ~TYPE_IN_OUT) {
        case TYPE_LREAL:
            assert(Value->Length == sizeof(Value->Value.Double));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.Double);

        case TYPE_REAL:
            assert(Value->Length == sizeof(Value->Value.Single));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.Single);

        case TYPE_LINT:
            assert(Value->Length == sizeof(Value->Value.S64));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.S64);

        case TYPE_DINT:
            assert(Value->Length == sizeof(Value->Value.S32));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.S32);

        case TYPE_INT:
            assert(Value->Length == sizeof(Value->Value.S16));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.S16);

        case TYPE_SINT:
            assert(Value->Length == sizeof(Value->Value.S8));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.S8);

        case TYPE_ULINT:
            assert(Value->Length == sizeof(Value->Value.U64));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.U64);

        case TYPE_UDINT:
            assert(Value->Length == sizeof(Value->Value.U32));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.U32);

        case TYPE_UINT:
            assert(Value->Length == sizeof(Value->Value.U16));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.U16);

        case TYPE_USINT:
            assert(Value->Length == sizeof(Value->Value.U8));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.U8);

        case TYPE_LWORD:
            assert(Value->Length == sizeof(Value->Value.B64));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.B64);

        case TYPE_DWORD:
            assert(Value->Length == sizeof(Value->Value.B32));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.B32);

        case TYPE_WORD:
            assert(Value->Length == sizeof(Value->Value.B16));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.B16);

        case TYPE_BYTE:
            assert(Value->Length == sizeof(Value->Value.B8));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.B8);

        case TYPE_BOOL:
            assert(Value->Length == sizeof(Value->Value.B1));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.B1);

        case TYPE_TIME:
            assert(Value->Length == sizeof(Value->Value.Time));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.Time);

        case TYPE_DATE:
        case TYPE_DT:
        case TYPE_TOD:
            assert(Value->Length == sizeof(Value->Value.DateTime));
            return bytecode_write(Context, Block, Value->Length, (char *) &Value->Value.DateTime);

        case TYPE_LABEL:
            uValue = 0;
			return bytecode_write(Context, Block, sizeof(uValue), (char *) &uValue);

        case TYPE_VARIABLE:
            if((pSymbol = symbol_search(Context, Config, Resource, Name, (char *) Value->Meta)) == NULL)
                return ENOENT;
            uValue = pSymbol->Id;
            if((nResult = bytecode_write(Context, Block, sizeof(uValue), (char *) &uValue)) != 0)
                return nResult;
            ++pSymbol->Ref;
            return 0;

        case TYPE_FUNCTION:
        case TYPE_FUNCTION_BLOCK:
        case TYPE_NONE:
            return 0;

        default:
            log_debug("%s: %08x", __func__, Value->Type & ~TYPE_IN_OUT);
            assert(0);
    }

    return 0;
}


int
bytecode_generate(ECHIDNA *Context) {
    BLOCK *pBlock, sBlock;
    TOKEN_LIST *pStack[3];
    TOKEN *pToken;
    TREE sPOUs;
    UNIT *pPOU;
    int nId[3] = {
            CONFIGURATION,
            RESOURCE,
            PROGRAM,
    };
    int nResult, nSize, nStack;

    /*
        The following iterates through the top-level list of library elements and
        creates a named cache of pointers to the corresponding parse tokens. This 
        cache makes use of the ability to set a textual "name" and a pointer to 
        external data in association with a BLOCK data structure. This named cache
        is ephemeral and only maintained for the scope of this function.
    */

    assert(Context != NULL);

    nResult = 0;
    tree_initialise(&sPOUs, unit_compare);
    token_list_reset(&Context->Parse.Tokens);
    while((pToken = token_list_iterate(&Context->Parse.Tokens)) != NULL) {
        switch(pToken->Id) {
            case FUNCTION:
            case FUNCTION_BLOCK:
            case PROGRAM:
                break;
            default:
                continue;
        }

        if((pPOU = unit_create(NULL, NULL, pToken->Name)) == NULL) {
            nResult = -errno;
            goto finish;
        }
        assert(&pPOU->Block == (BLOCK *) pPOU); //  NB: This is _very_ important!
        pBlock = (BLOCK *) pPOU;
        block_pointer(pBlock, pToken);

        if((nResult = tree_insert(&sPOUs, pPOU)) != 0) 
            goto finish;

        /*
            This generation of bytecode associated with user-defined functions and 
            function blocks should rightly be moved to a separate loop, but is executed 
            here for brevity.
        */

        switch(pToken->Id) {
            case FUNCTION:
            case FUNCTION_BLOCK:
                if((nResult = _bytecode_generate(Context, NULL, NULL, pToken->Name, (TOKEN_LIST *) block_pointer(pBlock))) != 0)
                    goto finish;
                break;

            default:
                break;
        }
    }

    /*
        The following will iterate through the parse tree of tokens looking for 
        program instances defined in association with tasks, resources and 
        configurations. Where such instances are found, a corresponding bytecode block 
        is generated.
    */

    nSize = (sizeof(nId) / sizeof(nId[0]));
    pStack[0] = &Context->Parse.Tokens;
    token_list_reset( pStack[0] );
    for( nStack = 0; nStack >= 0; --nStack ) {
        while( ( pToken = token_list_iterate( pStack[ nStack ] ) ) != NULL ) {
            if( pToken->Id != nId[ nStack ] )
                continue;
            if( nStack < ( nSize - 1 ) ) {
                pStack[ ++nStack ] = ( TOKEN_LIST * ) pToken;
                token_list_reset( pStack[ nStack++ ] );
                break;
            }

            sBlock.Name = ( char * ) pToken->Value.Meta;
            if( ( pBlock = tree_search( &sPOUs, &sBlock ) ) == NULL ) {
                nResult = -ENOENT;
                goto finish;
            }

            /*
                The following generates separate bytecode for each instance of a given POU - 
                An alternative approach to consider may be to have a single instance with 
                relative references to the symbol table.
            */
           
           switch( pToken->Id ) {
                case FUNCTION_BLOCK:
                case PROGRAM:
                    break;
                default:
                    goto finish;           
           }

            if( ( nResult = _bytecode_generate( Context, 
                    pStack[1]->Token.Name, 
                    pStack[2]->Token.Name, 
                    pToken->Name,
                    ( TOKEN_LIST * ) block_pointer( pBlock ) ) ) != 0 ) 
                goto finish;
        }
    }

finish:
    tree_destroy(&sPOUs, unit_destroy);
    return nResult;
}

