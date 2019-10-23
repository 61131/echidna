/* grammar.y */
/*  bison -Wall -v grammar.y -o grammar.c */

%{
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <time.h>
#include <limits.h>

#include <echidna.h>
#include <lexer.h>

#define YYPRINT(File, Type, Value)

_FUNCTION_BLOCK * yyfunction_create(const char *Name, TOKEN_LIST *Parameters);

void yyfunction_destroy(void *Arg);

int yyliteralzero(TOKEN *Token);

void yyerror(ECHIDNA *Context, const char *Str);

int yylex(void);

%}

%defines
%token-table

%code requires {

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <assert.h>

#include <cast.h>
#include <echidna.h>
#include <grammar.h>
#include <log.h>
#include <symbol.h>
#include <token.h>

#include <json.h>

void yyrestart(FILE *File);

const char * yytokenname(int Id);

int yystrtoid(const char *Str);

extern FILE *yyin;

}

%parse-param { ECHIDNA *Context }

%union {
    struct _TOKEN_LIST *List;

    struct _TOKEN *Token;
}

%start library;

%token END_OF_INPUT 0

%token <Token> _function_block_type_name
%token <Token> _function_name
%token <Token> _program_type_name
%token <Token> _program_name
%token <Token> _resource_name
%token <Token> _task_name
%token <Token> _variable_name


/* B.0 Programming model */

/* B.1 Common elements */

/* B.1.1 Letters, digits and identifiers */

%token <Token> integer
%token <Token> identifier

/* B.1.2 Constants */

/* B.1.2.1 Numeric literals */

%token <Token> binary_integer
%token <Token> octal_integer
%token <Token> decimal_integer
%token <Token> hex_integer
%token <Token> real
%token <Token> TRUE
%token <Token> FALSE

/* B.1.2.2 Character strings */

%token <Token> single_byte_character_string
%token <Token> double_byte_character_string
    
/* B.1.2.3 Time literals */

/* B.1.2.3.1 Duration */

%token <Token> fixed_point

%token _duration_days
%token _duration_hours
%token _duration_minutes
%token _duration_seconds
%token _duration_milliseconds
%token _t_sharp

/* B.1.2.3.2 Time of day and date */

%token <Token> _d_sharp
%token <Token> _dt_sharp
%token <Token> _tod_sharp

/* B.1.3 Data types */

/* B.1.3.1 Elementary data types */

%token <Token> STRING
/* %token <Token> WSTRING */
%token <Token> TIME
%token <Token> SINT
%token <Token> INT
%token <Token> DINT
%token <Token> LINT
%token <Token> USINT
%token <Token> UINT
%token <Token> UDINT
%token <Token> ULINT
%token <Token> REAL
%token <Token> LREAL
%token <Token> DATE
%token <Token> TIME_OF_DAY
%token <Token> TOD
%token <Token> DATE_AND_TIME
%token <Token> DT
%token <Token> BOOL
%token <Token> BYTE
%token <Token> WORD
%token <Token> DWORD
%token <Token> LWORD    

/* B.1.3.2 Generic data types */

/* B.1.3.3 Derived data types */

%token <Token> simple_type_name
%token <Token> subrange_type_name
%token <Token> enumerated_type_name
%token <Token> array_type_name
%token <Token> structure_type_name
%token <Token> string_type_name
%token TYPE
%token END_TYPE
%token ARRAY
%token OF
%token STRUCT
%token END_STRUCT

%token _assign
%token _range
%token _sendto

/* B.1.4 Variables */

/* B.1.4.1 Directly represented variables */

%token <Token> direct_variable

/* B.1.4.2 Multi-element variables */

/* B.1.4.3 Declaration and initialization */

%token VAR_INPUT
%token RETAIN
%token NON_RETAIN
%token END_VAR
%token R_EDGE
%token F_EDGE
%token VAR_OUTPUT
%token VAR_IN_OUT
%token VAR
%token CONSTANT
%token VAR_EXTERNAL
%token VAR_GLOBAL
%token AT

/* B.1.5 Program organization units */

/* B.1.5.1 Functions */

%token <Token> FUNCTION
%token END_FUNCTION

/* B.1.5.2 Function blocks */

%token <Token> FUNCTION_BLOCK
%token END_FUNCTION_BLOCK
%token VAR_TEMP 

/* B.1.5.3 Programs */

%token <Token> PROGRAM
%token END_PROGRAM
%token VAR_ACCESS

/* B.1.6 Sequential function chart elements */

/* B.1.7 Configuration elements */

%token <Token> CONFIGURATION
%token END_CONFIGURATION
%token RESOURCE
%token ON
%token END_RESOURCE
%token <Token> READ_WRITE
%token <Token> READ_ONLY
%token TASK
%token SINGLE
%token INTERVAL
%token PRIORITY
%token WITH
%token <List> VAR_CONFIG

/* B.2 Language IL (Instruction List) */

/* B.2.1 Instructions and operands */

%token EOL

%token <Token> _label

/* B.2.2 Operators */

%token <Token> NOP      /* No operation */
%token <Token> LD
%token <Token> LDN
%token <Token> ST
%token <Token> STN
%token <Token> NOT
%token <Token> S
%token <Token> R
%token <Token> S1
%token <Token> R1
%token <Token> CLK
%token <Token> CU
%token <Token> CD
%token <Token> IN
%token <Token> PT
%token <Token> PV
%token <List> AND
%token <List> OR
%token <List> XOR
%token <List> ANDN
%token <List> ORN
%token <List> XORN
%token <List> ADD
%token <List> SUB
%token <List> MUL
%token <List> DIV
%token <List> MOD
/* %token <Token> EXP */
%token <List> GT
%token <List> GE
%token <List> EQ
%token <List> LT
%token <List> LE
%token <List> NE
%token <Token> CAL
%token <Token> CALC
%token <Token> CALCN
%token <Token> RET
%token <Token> RETC
%token <Token> RETCN
%token <Token> JMP
%token <Token> JMPC
%token <Token> JMPCN

%token <Token> EN
%token <Token> ENO

/* B.3 Language ST (Structured Text) */

/* B.3.1 Expressions */

/* B.3.2 Statements */

/* B.3.2.1 Assignment statements */

/* B.3.2.2 Subprogram control statements */

/* %token <Token> RETURN */

/* B.3.2.3 Selection statements */

/* %token <Token> IF */
/* %token <Token> THEN */
/* %token <Token> ELSIF */
/* %token <Token> ELSE */
/* %token <Token> END_IF */
/* %token <Token> CASE */
/* %token <Token> END_CASE */

/* B.3.2.4 Iteration statements */

/* %token <Token> FOR */
/* %token <Token> TO */
/* %token <Token> BY */
/* %token <Token> DO */
/* %token <Token> END_FOR */
/* %token <Token> WHILE */
/* %token <Token> END_WHILE */
/* %token <Token> REPEAT */
/* %token <Token> UNTIL */
/* %token <Token> END_REPEAT */
/* %token <Token> EXIT */

%type <List> library

/* B.0 Programming model */

%type <List> library_element_declaration

/* B.1 Common elements */

/* B.1.1 Letters, digits and identifiers */

/* B.1.2 Constants */

%type <Token> constant

/* B.1.2.1 Numeric literals */

%type <Token> numeric_literal
%type <Token> integer_literal
%type <Token> signed_integer
%type <Token> real_literal
%type <Token> bit_string_literal
%type <Token> boolean_literal

/* B.1.2.2 Character strings */

%type <Token> character_string

/* B.1.2.3 Time literals */

%type <Token> time_literal

/* B.1.2.3.1 Duration */

%type <Token> duration
%type <Token> interval
%type <Token> days
%type <Token> hours
%type <Token> minutes
%type <Token> seconds
%type <Token> milliseconds

/* B.1.2.3.2 Time of day and date */

%type <Token> time_of_day
%type <Token> daytime
%type <Token> date
%type <Token> date_literal
%type <Token> date_and_time
    
/* B.1.3 Data types */

/* %type <Token> data_type_name */
%type <Token> non_generic_type_name
/* %type <Token> generic_type_name */
%type <Token> elementary_type_name

/* B.1.3.1 Elementary data types */

%type <Token> numeric_type_name
%type <Token> integer_type_name
%type <Token> signed_integer_type_name
%type <Token> unsigned_integer_type_name
%type <Token> real_type_name
%type <Token> date_type_name
%type <Token> bit_string_type_name    

/* B.1.3.2 Generic data types */

/* B.1.3.3 Derived data types */

%type <Token> derived_type_name
%type <Token> single_element_type_name
%type <List> data_type_declaration
%type <Token> type_declaration
%type <Token> single_element_type_declaration
%type <Token> simple_type_declaration
%type <Token> array_type_declaration
%type <Token> subrange_type_declaration
%type <Token> enumerated_type_declaration
%type <Token> simple_spec_init
%type <Token> simple_specification
%type <Token> subrange_spec_init
%type <Token> subrange_specification
%type <Token> subrange
%type <Token> enumerated_spec_init
%type <Token> enumerated_specification
%type <Token> enumerated_value
%type <Token> array_spec_init
%type <Token> array_specification
%type <Token> array_initialization
%type <List> array_initial_elements
%type <Token> array_initial_element
%type <Token> structure_type_declaration
%type <Token> structure_specification
%type <Token> structure_declaration
%type <Token> initialized_structure
%type <Token> structure_initialization
%type <Token> structure_element_declaration
%type <Token> structure_element_initialization
%type <Token> string_type_declaration

%type <List> _array_initial_elements
%type <List> _enumerated_value
%type <List> _structure_element_declaration
%type <List> _structure_element_initialization
%type <List> _type_declaration

/* B.1.4 Variables */

/* B.1.4.1 Directly represented variables */

/* B.1.4.2 Multi-element variables */

/* B.1.4.3 Declaration and initialization */

%type <List> input_declarations
%type <List> input_declaration
%type <List> edge_declaration
%type <List> var_init_decl
%type <List> var1_init_decl
%type <List> var1_list
%type <List> array_var_init_decl
%type <List> structured_var_init_decl
%type <List> fb_name_decl
%type <List> output_declarations
%type <List> input_var_init_decls
%type <List> var_declaration
%type <List> temp_var_decl
%type <List> var1_declaration
%type <List> array_var_declaration
%type <List> structured_var_declaration
%type <List> var_declarations
%type <List> retentive_var_declarations
%type <List> located_var_declarations
%type <Token> located_var_decl
%type <List> external_var_declarations
%type <Token> external_declaration
%type <Token> global_var_name
%type <List> global_var_declarations
%type <List> global_var_decl
%type <List> global_var_spec
%type <List> global_var_list
%type <List> string_var_declaration
%type <List> single_byte_string_var_declaration
%type <Token> single_byte_string_spec
/* %type <List> double_byte_string_var_declaration */
/* %type <Token> double_byte_string_spec */
%type <Token> located_var_spec_init
%type <Token> location

%type <List> _external_declaration
%type <List> _global_var_declarations
%type <List> _global_var_decl
%type <List> _input_declaration
%type <List> _located_var_decl
%type <List> _var_declaration
%type <List> _var_init_decl

/* B.1.5 Program organization units */

/* B.1.5.1 Functions */

%type <Token> function_name
%type <List> function_declaration
%type <List> io_var_declarations
%type <List> function_var_decls
%type <List> function_body
%type <List> var2_init_decl

%type <Token> _function_type_name
%type <List> _io_function_var_decls
%type <List> _var2_init_decl

/* B.1.5.2 Function blocks */

%type <List> function_block_declaration
%type <Token> function_block_type_name
%type <List> other_var_declarations
%type <List> temp_var_decls
%type <List> non_retentive_var_decls
%type <List> function_block_body

%type <List> _fb_var_declarations

/* B.1.5.3 Programs */

%type <List> program_declaration
%type <Token> program_type_name
%type <List> program_access_decls
%type <Token> program_access_decl

%type <List> _program_access_decls
%type <List> _program_var_access_decls

/* B.1.6 Sequential function blocks */

/* B.1.7 Configuration elements */

%type <List> configuration_declaration
%type <Token> configuration_name
%type <List> resource_declaration
%type <List> single_resource_declaration
%type <Token> resource_name
%type <Token> direction
%type <List> task_configuration
%type <Token> task_name
%type <List> task_initialization
%type <List> program_configuration
%type <Token> program_name
%type <Token> data_source
%type <List> _program_configuration
%type <Token> _program_configuration_retention
%type <Token> _program_configuration_task
%type <List> _resource_declaration
%type <List> _task_configuration
%type <Token> _task_initialization_interval
%type <Token> _task_initialization_single
%type <Token> _task_initialization_limit

/* B.2 Language IL (Instruction List) */

/* B.2.1 Instructions and operands */

%type <List> instruction_list
%type <Token> il_instruction
%type <Token> il_simple_operation
%type <Token> il_expression
%type <Token> il_jump_operation
%type <Token> il_fb_call
%type <Token> il_formal_funct_call
%type <Token> il_operand
%type <List> il_operand_list
%type <List> simple_instr_list
%type <Token> il_simple_instruction
%type <List> il_param_list
%type <List> il_param_instruction
%type <List> il_param_last_instruction
%type <List> il_param_assignment
%type <List> il_param_out_assignment

%type <Token> _il_instruction
%type <List> _il_param_list

/* B.2.2 Operators */

%type <Token> il_simple_operator
%type <List> il_expr_operator
%type <List> il_assign_operator
%type <List> il_assign_out_operator
%type <Token> il_call_operator
%type <Token> il_return_operator
%type <Token> il_jump_operator

%type <List> _il_expr_function

/* B.3 Language ST (Structured Text) */

/* B.3.1 Expressions */

/* %type <Token> expression */
/* %type <Token> xor_expression */
/* %type <Token> and_expression */
/* %type <Token> comparison */
/* %type <Token> equ_expression */
/* %type <Token> add_expression */
/* %type <Token> term */
/* %type <Token> power_expression */
/* %type <Token> unary_expression */
/* %type <Token> primary_expression */

/* B.3.2 Statements */

/* %type <List> statement_list */
/* %type <Token> statement */

/* B.3.2.1 Assignment statements */

/* %type <Token> assignment_statement */

/* B.3.2.2 Subprogram control statements */

/* %type <Token> subprogram_control_statement */
/* %type <Token> fb_invocation */
/* %type <Token> param_assignment */

/* B.3.2.3 Selection statements */

/* %type <Token> selection_statement */
/* %type <Token> if_statement */
/* %type <Token> case_statement */
/* %type <Token> selection_statement */

/* B.3.2.4 Iteration statements */


%%


/* B.0 Programming model */

/*  library_element_name ::= data_type_name | function_name
        | function_block_type_name | program_type_name
        | resource_type_name | configuration_name
    
    library_element_declaration ::= data_type_declaration
        | function_declaration | function_block_declaration
        | program_declaration | configuration_declaration */
        
library: %empty {
            PARSE *pParse;

            pParse = &Context->Parse;
            lexer_start(pParse);
            pParse->Configuration = NULL;
            pParse->Resource = NULL;
            pParse->POU = NULL;
            $$ = &pParse->Parse;
        }
    | library library_element_declaration {
            token_list_insert($1, $library_element_declaration); 
            $$ = $1;
        };

library_element_declaration: data_type_declaration
    | function_declaration 
    | function_block_declaration
    | program_declaration
    | configuration_declaration;
    

/* B.1 Common elements */

/* B.1.1 Letters, digits and identifiers */

/*  letter ::= 'A' | 'B' | <...> | 'Z' | 'a' | 'b' | <...> | 'z'

    digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

    octal_digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'

    hex_digit ::= digit | 'A'|'B'|'C'|'D'|'E'|'F'

    identifier ::= (letter | ('_' (letter | digit))) {['_'] (letter | digit)} */

    
/* B.1.2 Constants */

/*  constant ::= numeric_literal | character_string | time_literal
        | bit_string_literal | boolean_literal */
        
constant: numeric_literal
    | character_string
    | time_literal
    | bit_string_literal
    | boolean_literal;
    

/* B.1.2.1 Numeric literals */

/*  numeric_literal ::= integer_literal | real_literal

    integer_literal ::= [ integer_type_name '#' ]
        ( signed_integer | binary_integer | octal_integer | decimal_integer | hex_integer)

    signed_integer ::= ['+' |'-'] integer

    integer ::= digit {['_'] digit}

    binary_integer ::= '2#' bit {['_'] bit}

    bit ::= '1' | '0'

    octal_integer ::= '8#' octal_digit {['_'] octal_digit}

    decimal_integer ::= '10#' integer

    hex_integer ::= '16#' hex_digit {['_'] hex_digit}

    real_literal ::= [ real_type_name '#' ]
        signed_integer '.' integer [exponent]

    exponent ::= ('E' | 'e') ['+'|'-'] integer

    bit_string_literal ::=
        [ ('BYTE' | 'WORD' | 'DWORD' | 'LWORD') '#' ]
        ( unsigned_integer | binary_integer | octal_integer | decimal_integer | hex_integer)

    boolean_literal ::=
        ( [ 'BOOL#' ] ( '1' | '0' ) )| 'TRUE' | 'FALSE' */
        
numeric_literal: integer_literal
    | real_literal;

integer_literal: integer_type_name '#' signed_integer {
            value_cast(&$signed_integer->Value, $integer_type_name->Value.Type);
            token_destroy($integer_type_name);
            $$ = $signed_integer;
        }
    | integer_type_name '#' binary_integer {
            value_cast(&$binary_integer->Value, $integer_type_name->Value.Type);
            token_destroy($integer_type_name);
            $$ = $binary_integer;
        }
    | integer_type_name '#' octal_integer {
            value_cast(&$octal_integer->Value, $integer_type_name->Value.Type);
            token_destroy($integer_type_name);
            $$ = $octal_integer;
        }
    | integer_type_name '#' decimal_integer {
            value_cast(&$decimal_integer->Value, $integer_type_name->Value.Type);
            token_destroy($integer_type_name);
            $$ = $decimal_integer;
        }
    | integer_type_name '#' hex_integer {
            value_cast(&$hex_integer->Value, $integer_type_name->Value.Type);
            token_destroy($integer_type_name);
            $$ = $hex_integer;
        }
    | signed_integer 
    | binary_integer 
    | octal_integer
    | decimal_integer
    | hex_integer;

signed_integer: '+' integer {
            $$ = $integer;
        }
    | '-' integer {
            $integer->Value.Value.S64 *= -1ULL;
            $$ = $integer;
        }
    | integer;
    
real_literal: real_type_name '#' real {
            TOKEN *pToken;
            
            pToken = token_cast($real, $real_type_name->Value.Type, $real_type_name->Line, $real_type_name->Column);
            token_destroy($real_type_name);
            $$ = pToken;
        }
    | real;
    
bit_string_literal: bit_string_type_name '#' integer {
            TOKEN *pToken;
            
            pToken = token_cast($integer, $bit_string_type_name->Value.Type, $bit_string_type_name->Line, $bit_string_type_name->Column);
            token_destroy($bit_string_type_name);
            $$ = pToken;
        }
    | bit_string_type_name '#' binary_integer {
            TOKEN *pToken;
            
            pToken = token_cast($binary_integer, $bit_string_type_name->Value.Type, $bit_string_type_name->Line, $bit_string_type_name->Column);
            token_destroy($bit_string_type_name);
            $$ = pToken;
        }
    | bit_string_type_name '#' octal_integer {
            TOKEN *pToken;
            
            pToken = token_cast($octal_integer, $bit_string_type_name->Value.Type, $bit_string_type_name->Line, $bit_string_type_name->Column);
            token_destroy($bit_string_type_name);
            $$ = pToken;
        }
    | bit_string_type_name '#' decimal_integer {
            TOKEN *pToken;
            
            pToken = token_cast($decimal_integer, $bit_string_type_name->Value.Type, $bit_string_type_name->Line, $bit_string_type_name->Column);
            token_destroy($bit_string_type_name);
            $$ = pToken;
        }
    | bit_string_type_name '#' hex_integer {
            TOKEN *pToken;
            
            pToken = token_cast($hex_integer, $bit_string_type_name->Value.Type, $bit_string_type_name->Line, $bit_string_type_name->Column);
            token_destroy($bit_string_type_name);
            $$ = pToken;
        };
    
boolean_literal: TRUE
    | FALSE;
   
    
/* B.1.2.2 Character strings */

/*  character_string ::=
        single_byte_character_string | double_byte_character_string

    single_byte_character_string ::=
        "'" {single_byte_character_representation} "'"

    double_byte_character_string ::=
        '"' {double_byte_character_representation} '"'

    single_byte_character_representation ::= common_character_representation
        | "$'" | '"' | '$' hex_digit hex_digit

    double_byte_character_representation ::= common_character_representation
        | '$"' | "'"| '$' hex_digit hex_digit hex_digit hex_digit

    common_character_representation ::=
        <any printable character except '$', '"' or "'">
        | '$$' | '$L' | '$N' | '$P' | '$R' | '$T'
        | '$l' | '$n' | '$p' | '$r' | '$t' */

character_string: single_byte_character_string
    | double_byte_character_string;

        
/* B.1.2.3 Time literals */

/*  time_literal ::= duration | time_of_day | date | date_and_time */

time_literal: duration 
    | time_of_day
    | date
    | date_and_time;

    
/* B.1.2.3.1 Duration */

/*  duration ::= ('T' | 'TIME') '#' ['-'] interval

    interval ::= days | hours | minutes | seconds | milliseconds

    days ::= fixed_point ('d') | integer ('d') ['_'] hours

    fixed_point ::= integer [ '.' integer]

    hours ::= fixed_point ('h') | integer ('h') ['_'] minutes

    minutes ::= fixed_point ('m') | integer ('m') ['_'] seconds

    seconds ::= fixed_point ('s') | integer ('s') ['_'] milliseconds

    milliseconds ::= fixed_point ('ms') */

duration: TIME '#' interval {
            cast_time(&$interval->Value);
            $$ = $interval; 
        }
    | _t_sharp interval {
            cast_time(&$interval->Value);
            $$ = $interval; 
        };

interval: days
    | hours
    | minutes
    | seconds
    | milliseconds;
    
days: fixed_point _duration_days {
            cast_time(&$fixed_point->Value);
            $fixed_point->Value.Value.Time *= /* (1000 * 60 * 60 * 24) */ 8.64e+7f;
            $$ = $fixed_point;
        }
    | integer _duration_days hours {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($hours->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $hours);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60 * 24) */ 8.64e+7f;
            $integer->Value.Value.Time += ($hours->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($hours);
            $$ = $integer;
        }
    | integer _duration_days minutes {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($minutes->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $minutes);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60 * 24) */ 8.64e+7f;
            $integer->Value.Value.Time += ($minutes->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($minutes);
            $$ = $integer;
        }
    | integer _duration_days seconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($seconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $seconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60 * 24) */ 8.64e+7f;
            $integer->Value.Value.Time += ($seconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($seconds);
            $$ = $integer;
        }
    | integer _duration_days milliseconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($milliseconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $milliseconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60 * 24) */ 8.64e+7f;
            $integer->Value.Value.Time += ($milliseconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($milliseconds);
            $$ = $integer;
        }
    | integer _duration_days {
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60 * 24) */ 8.64e+7f;
            $$ = $integer;
        };
    
hours: fixed_point _duration_hours {
            cast_time(&$fixed_point->Value);
            $fixed_point->Value.Value.Time *= /* (1000 * 60 * 60) */ 3.6e+6f;
            $$ = $fixed_point;
        }
    | integer _duration_hours minutes {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($minutes->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $minutes);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60) */ 3.6e+6f;
            $integer->Value.Value.Time += ($minutes->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($minutes);
            $$ = $integer;
        }
    | integer _duration_hours seconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($seconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $seconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60) */ 3.6e+6f;
            $integer->Value.Value.Time += ($seconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($seconds);
            $$ = $integer;
        }
    | integer _duration_hours milliseconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($milliseconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $milliseconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60) */ 3.6e+6f;
            $integer->Value.Value.Time += ($milliseconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($milliseconds);
            $$ = $integer;
        }
    | integer _duration_hours {
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60 * 60) */ 3.6e+6f;
            $$ = $integer;
        };
    
minutes: fixed_point _duration_minutes {
            cast_time(&$fixed_point->Value);
            $fixed_point->Value.Value.Time *= /* (1000 * 60) */ 60000.0f;
            $$ = $fixed_point;
        }
    | integer _duration_minutes seconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($seconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $seconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60) */ 60000.0f;
            $integer->Value.Value.Time += ($seconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($seconds);
            $$ = $integer;
        }
    | integer _duration_minutes milliseconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($milliseconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $milliseconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60) */ 60000.0f;
            $integer->Value.Value.Time += ($milliseconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($milliseconds);
            $$ = $integer;
        }
    | integer _duration_minutes {
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= /* (1000 * 60) */ 60000.0f;
            $$ = $integer;
        };
    
seconds: fixed_point _duration_seconds {
            cast_time(&$fixed_point->Value);
            $fixed_point->Value.Value.Time *= 1000.0f;
            $$ = $fixed_point;
        }
    | integer _duration_seconds milliseconds {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($milliseconds->Value.Value.Time < 0.0) {
                log_error("%s: Invalid format for duration literal [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                token_destroy($integer, $milliseconds);
                YYERROR;
            }
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= 1000.0f;
            $integer->Value.Value.Time += ($milliseconds->Value.Value.Time * copysign(1.0, $integer->Value.Value.Time));
            token_destroy($milliseconds);
            $$ = $integer;
        }
    | integer _duration_seconds {
            cast_time(&$integer->Value);
            $integer->Value.Value.Time *= 1000.0f;
            $$ = $integer;
        };
    
milliseconds: fixed_point _duration_milliseconds {
            cast_time(&$fixed_point->Value);
            $$ = $fixed_point;
        }
    | integer _duration_milliseconds {
            cast_time(&$integer->Value);
            $$ = $integer;
        }; 
    

/* B.1.2.3.2 Time of day and date */

/*  time_of_day ::= ('TIME_OF_DAY' | 'TOD') '#' daytime

    daytime ::= day_hour ':' day_minute ':' day_second

    day_hour ::= integer

    day_minute ::= integer

    day_second ::= fixed_point

    date ::= ('DATE' | 'D') '#' date_literal

    date_literal ::= year '-' month '-' day

    year ::= integer

    month ::= integer

    day ::= integer

    date_and_time ::= ('DATE_AND_TIME' | 'DT') '#' date_literal '-' daytime */

time_of_day: TIME_OF_DAY '#' daytime {
            $$ = $daytime;
        }
    | TOD '#' daytime {
            $$ = $daytime;
        }
    | daytime;
    
daytime: integer ':' integer ':' integer {
            PARSE *pParse;
            TOKEN *pToken;
            struct tm sTime;            

            pParse = &Context->Parse;
            if($1->Value.Value.U32 > 23) {
                log_error("%s: Invalid value for hour (%lu) in time of day literal [%u:%u]",
                        pParse->File,
                        $1->Value.Value.U32,
                        @1.first_line,
                        @1.first_column);
                token_destroy($1, $3, $5);
                YYERROR;
            }
            if($3->Value.Value.U32 > 59) {
                log_error("%s: Invalid value for minute (%lu) in time of day literal [%u:%u]",
                        pParse->File,
                        $3->Value.Value.U32,
                        @3.first_line,
                        @3.first_column);
                token_destroy($1, $3, $5);
                YYERROR;
            }
            if($5->Value.Value.U32 > /* 60 */ 59) {
                log_error("%s: Invalid value for second (%lu) in time of day literal [%u:%u]",
                        pParse->File,
                        $5->Value.Value.U32,
                        @5.first_line,
                        @5.first_column);
                token_destroy($1, $3, $5);
                YYERROR;
            }

            memset(&sTime, 0, sizeof(sTime));
            sTime.tm_sec = $1->Value.Value.U32;
            sTime.tm_min = $3->Value.Value.U32;
            sTime.tm_hour = $5->Value.Value.U32;

            pToken = token_new(TOD, @1.first_line, @1.first_column);
            value_assign(&pToken->Value, TYPE_TOD, mktime(&sTime));
            token_destroy($1, $3, $5);
            $$ = pToken;
        };

date: DATE '#' date_literal { 
            $$ = $date_literal; 
        }
    | _d_sharp date_literal { 
            $$ = $date_literal; 
        }
    | date_literal;
    
date_literal: integer '-' integer '-' integer {
            PARSE *pParse;
            TOKEN *pToken;
            struct tm sTime;

            pParse = &Context->Parse;
            if($1->Value.Value.U32 < 1900) {
                log_error("%s: Invalid value for year (%lu) in date literal [%u:%u]",
                        pParse->File,
                        $1->Value.Value.U32,
                        @1.first_line,
                        @1.first_column);
                token_destroy($1, $3, $5);
                YYERROR;
            }
            if(($3->Value.Value.U32 < 1) ||
                    ($3->Value.Value.U32 > 12)) {
                log_error("%s: Invalid value for month (%lu) in date literal [%u:%u]",
                        pParse->File,
                        $3->Value.Value.U32,
                        @3.first_line,
                        @3.first_column);
                token_destroy($1, $3, $5);
                YYERROR;
            }
            if(($5->Value.Value.U32 < 1) ||
                    ($5->Value.Value.U32 > 31)) {
                log_error("%s: Invalid value for day (%lu) in date literal [%u:%u]",
                        pParse->File,
                        $5->Value.Value.U32,
                        @5.first_line,
                        @5.first_column);
                token_destroy($1, $3, $5);
                YYERROR;
            }

            memset(&sTime, 0, sizeof(sTime));
            sTime.tm_year = $1->Value.Value.U32 - 1900;
            sTime.tm_mon = $3->Value.Value.U32 - 1;
            sTime.tm_mday = $5->Value.Value.U32;

            pToken = token_new(DATE, @1.first_line, @1.first_column);
            value_assign(&pToken->Value, TYPE_DATE, mktime(&sTime));
            token_destroy($1, $3, $5);
            $$ = pToken;
        };

date_and_time: DATE_AND_TIME '#' date_literal '-' daytime {
            TOKEN *pToken;
            struct tm sDate, sResult, sTime;

            localtime_r((const time_t *) &$date_literal->Value.Value.U32, &sDate);
            localtime_r((const time_t *) &$daytime->Value.Value.U32, &sTime);
            memset(&sResult, 0, sizeof(sResult));
            sResult.tm_year = sDate.tm_year;
            sResult.tm_mon = sDate.tm_mon;
            sResult.tm_mday = sDate.tm_mday;
            sResult.tm_hour = sTime.tm_hour;
            sResult.tm_min = sTime.tm_min;
            sResult.tm_sec = sTime.tm_sec;

            pToken = token_new(DT, @1.first_line, @1.first_column);
            value_assign(&pToken->Value, TYPE_DT, mktime(&sResult));
            token_destroy($date_literal, $daytime);
            $$ = pToken;
        }
    | _dt_sharp date_literal '-' daytime {
            TOKEN *pToken;
            struct tm sDate, sResult, sTime;

            localtime_r((const time_t *) &$date_literal->Value.Value.U32, &sDate);
            localtime_r((const time_t *) &$daytime->Value.Value.U32, &sTime);
            memset(&sResult, 0, sizeof(sResult));
            sResult.tm_year = sDate.tm_year;
            sResult.tm_mon = sDate.tm_mon;
            sResult.tm_mday = sDate.tm_mday;
            sResult.tm_hour = sTime.tm_hour;
            sResult.tm_min = sTime.tm_min;
            sResult.tm_sec = sTime.tm_sec;

            pToken = token_new(DT, @1.first_line, @1.first_column);
            value_assign(&pToken->Value , TYPE_DT, mktime(&sResult));
            token_destroy($date_literal, $daytime);
            $$ = pToken;
        };
    
    
/* B.1.3 Data types */

/*  data_type_name ::= non_generic_type_name | generic_type_name

    non_generic_type_name ::= elementary_type_name | derived_type_name */

non_generic_type_name: elementary_type_name
    | derived_type_name {
            $derived_type_name->Value.Type = TYPE_DERIVED;
            $derived_type_name->Value.Meta = strdup($derived_type_name->Name);
            /* $derived_type_name->Name = NULL; */
            $$ = token_cast($derived_type_name, TYPE);
        };


/* B.1.3.1 Elementary data types */

/*  elementary_type_name ::= numeric_type_name | date_type_name
        | bit_string_type_name | 'STRING' | 'WSTRING' | 'TIME'
        
    numeric_type_name ::= integer_type_name | real_type_name
    
    integer_type_name ::= signed_integer_type_name
        | unsigned_integer_type_name
        
    signed_integer_type_name ::= 'SINT' | 'INT' | 'DINT' | 'LINT'
    
    unsigned_integer_type_name ::= 'USINT' | 'UINT' | 'UDINT' | 'ULINT'
    
    real_type_name ::= 'REAL' | 'LREAL'
    
    date_type_name ::= 'DATE' | 'TIME_OF_DAY' | 'TOD' | 'DATE_AND_TIME'
        | 'DT'
        
    bit_string_type_name ::= 'BOOL' | 'BYTE' | 'WORD' | 'DWORD' | 'LWORD' */

elementary_type_name: numeric_type_name
    | date_type_name
    | bit_string_type_name
    | STRING {
            TOKEN *pToken;

            pToken = token_new(STRING, @STRING.first_line, @STRING.first_column);
            pToken->Value.Type = TYPE_STRING;
            $$ = pToken;
        }
    /* | WSTRING {
            TOKEN *pToken;

            pToken = token_new(WSTRING, @WSTRING.first_line, @WSTRING.first_column);
            pToken->Value.Type = TYPE_WSTRING;
            $$ = pToken;
        } */
    | TIME {
            TOKEN *pToken;
            
            pToken = token_new(TIME, @TIME.first_line, @TIME.first_column);
            value_assign(&pToken->Value, TYPE_TIME);
            $$ = pToken;
        };
    
numeric_type_name: integer_type_name
    | real_type_name;
    
integer_type_name: signed_integer_type_name
    | unsigned_integer_type_name;
    
signed_integer_type_name: SINT {
            value_assign(&$SINT->Value, TYPE_SINT, 0);
            $$ = $SINT;
        }
    | INT {
            value_assign(&$INT->Value, TYPE_INT, 0);
            $$ = $INT;
        }
    | DINT {
            value_assign(&$DINT->Value, TYPE_DINT, 0);
            $$ = $DINT;
        }
    | LINT {
            value_assign(&$LINT->Value, TYPE_LINT, 0);
            $$ = $LINT;
        };
    
unsigned_integer_type_name: USINT {
            value_assign(&$USINT->Value, TYPE_USINT, 0);
            $$ = $USINT;
        }
    | UINT {
            value_assign(&$UINT->Value, TYPE_UINT, 0);
            $$ = $UINT;
        }
    | UDINT {
            value_assign(&$UDINT->Value, TYPE_UDINT, 0);
            $$ = $UDINT;
        }
    | ULINT {
            value_assign(&$ULINT->Value, TYPE_ULINT, 0);
            $$ = $ULINT;
        };
    
real_type_name: REAL {
            value_assign(&$REAL->Value, TYPE_REAL, 0.0f);
            $$ = $REAL;
        }
    | LREAL {
            value_assign(&$LREAL->Value, TYPE_LREAL, 0.0d);
            $$ = $LREAL;
        };
    
date_type_name: DATE {
            value_assign(&$DATE->Value, TYPE_DATE, 0);
            $$ = $DATE;
        }
    | TIME_OF_DAY {
            value_assign(&$TIME_OF_DAY->Value, TYPE_TOD, 0);
            $$ = $TIME_OF_DAY;
        }
    | TOD {
            value_assign(&$TOD->Value, TYPE_TOD, 0);
            $$ = $TOD;
        }
    | DATE_AND_TIME {
            value_assign(&$DATE_AND_TIME->Value, TYPE_DT, 0);
            $$ = $DATE_AND_TIME;
        }
    | DT {
            value_assign(&$DT->Value, TYPE_DT, 0);
            $$ = $DT;
        };
    
bit_string_type_name: BOOL {
            value_assign(&$BOOL->Value, TYPE_BOOL, 0);
            $$ = $BOOL;
        }
    | BYTE {
            value_assign(&$BYTE->Value, TYPE_BYTE, 0);
            $$ = $BYTE;
        }
    | WORD {
            value_assign(&$WORD->Value, TYPE_WORD, 0);
            $$ = $WORD;
        }
    | DWORD {
            value_assign(&$DWORD->Value, TYPE_DWORD, 0);
            $$ = $DWORD;
        }
    | LWORD {
            value_assign(&$LWORD->Value, TYPE_LWORD, 0);
            $$ = $LWORD;
        };

    
/* B.1.3.2 Generic data types */

/*  generic_type_name ::= 'ANY' | 'ANY_DERIVED' | 'ANY_ELEMENTARY'
        | 'ANY_MAGNITUDE' | 'ANY_NUM' | 'ANY_REAL' | 'ANY_INT' | 'ANY_BIT'
        | 'ANY_STRING' | 'ANY_DATE' */

/* generic_type_name: ANY
    | ANY_DERIVED
    | ANY_ELEMENTARY
    | ANY_MAGNITUDE
    | ANY_NUM
    | ANY_REAL
    | ANY_INT
    | ANY_BIT
    | ANY_STRING
    | ANY_DATE; */

    
/* B.1.3.3 Derived data types */

/*  derived_type_name ::= single_element_type_name | array_type_name
        | structure_type_name | string_type_name
    
    single_element_type_name ::= simple_type_name | subrange_type_name
        | enumerated_type_name

    simple_type_name ::= identifier
    
    subrange_type_name ::= identifier
    
    enumerated_type_name ::= identifier
    
    array_type_name ::= identifier
    
    structure_type_name ::= identifier
    
    data_type_declaration ::=
        'TYPE' type_declaration ';'
        {type_declaration ';'}
        'END_TYPE'

    type_declaration ::= single_element_type_declaration
        | array_type_declaration
        | structure_type_declaration | string_type_declaration
        
    single_element_type_declaration ::= simple_type_declaration
        | subrange_type_declaration | enumerated_type_declaration
        
    simple_type_declaration ::= simple_type_name ':' simple_spec_init
    
    simple_spec_init := simple_specification [':=' constant]
    
    simple_specification ::= elementary_type_name | simple_type_name
    
    subrange_type_declaration ::= subrange_type_name ':' subrange_spec_init
    
    subrange_spec_init ::= subrange_specification [':=' signed_integer]
    
    subrange_specification ::= integer_type_name '(' subrange ')'
        | subrange_type_name
        
    subrange ::= signed_integer '..' signed_integer
    
    enumerated_type_declaration ::=
        enumerated_type_name ':' enumerated_spec_init
        
    enumerated_spec_init ::= enumerated_specification [':=' enumerated_value]
    
    enumerated_specification ::=
        ( '(' enumerated_value {',' enumerated_value} ')' )
        | enumerated_type_name

    enumerated_value ::= [enumerated_type_name '#'] identifier

    array_type_declaration ::= array_type_name ':' array_spec_init

    array_spec_init ::= array_specification [':=' array_initialization]

    array_specification ::= array_type_name
        | 'ARRAY' '[' subrange {',' subrange} ']' 'OF' non_generic_type_name

    array_initialization ::=
        '[' array_initial_elements {',' array_initial_elements} ']'
        
    array_initial_elements ::=
        array_initial_element | integer '(' [array_initial_element] ')'
        
    array_initial_element ::= constant | enumerated_value
        | structure_initialization | array_initialization

    structure_type_declaration ::=
        structure_type_name ':' structure_specification
        
    structure_specification ::= structure_declaration | initialized_structure

    initialized_structure ::=
        structure_type_name [':=' structure_initialization]
        
    structure_declaration ::=
        'STRUCT' structure_element_declaration ';'
        {structure_element_declaration ';'}
        'END_STRUCT'
        
    structure_element_declaration ::= structure_element_name ':'
        (simple_spec_init | subrange_spec_init | enumerated_spec_init
        | array_spec_init | initialized_structure)
        
    structure_element_name ::= identifier
    
    structure_initialization ::=
        '(' structure_element_initialization
        {',' structure_element_initialization} ')'

    structure_element_initialization ::=
        structure_element_name ':=' (constant | enumerated_value
        | array_initialization | structure_initialization)
        
    string_type_name ::= identifier

    string_type_declaration ::= string_type_name ':'
        ('STRING'|'WSTRING') ['[' integer ']'] [':=' character_string]
*/

derived_type_name: single_element_type_name
    | array_type_name
    | structure_type_name
    | string_type_name;

single_element_type_name: simple_type_name
    | subrange_type_name
    | enumerated_type_name;

data_type_declaration: TYPE _type_declaration END_TYPE {
            $$ = $_type_declaration;
        }
    | TYPE END_TYPE {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing type declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            YYERROR;
            $$ = NULL;
        };

type_declaration: single_element_type_declaration
    | array_type_declaration 
    | structure_type_declaration
    | string_type_declaration;
    
single_element_type_declaration: simple_type_declaration
    | subrange_type_declaration
    | enumerated_type_declaration;
    
simple_type_declaration: simple_type_name ':' simple_spec_init {
            value_copy(&$simple_type_name->Value, &$simple_spec_init->Value);
            token_destroy($simple_spec_init);
            $$ = token_cast($simple_type_name, TYPE);
        }
    | identifier ':' simple_spec_init {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(nResult = EFAULT;;) {
                    if((pToken = lexer_new(simple_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {
                log_error("%s: Unknown data type in simple type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;            
            }
            token_destroy($identifier, $simple_spec_init);
            $$ = NULL;
        }
    | simple_type_name simple_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in simple type declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($simple_type_name, $simple_spec_init);
            YYERROR;
            $$ = NULL;
        };

simple_spec_init: 
    simple_specification _assign constant {
            value_cast(&$simple_specification->Value, $simple_specification->Value.Type, &$constant->Value);
            token_destroy($constant);
            $$ = $simple_specification;
        } 
    | simple_specification;

simple_specification: elementary_type_name
    | simple_type_name {
            $simple_type_name->Value.Type = TYPE_DERIVED;
            $simple_type_name->Value.Meta = strdup($simple_type_name->Name);
            /* $simple_type_name->Name = NULL; */
            $$ = token_cast($simple_type_name, TYPE);
        };

subrange_type_declaration: subrange_type_name ':' subrange_spec_init {
            value_copy(&$subrange_type_name->Value, &$subrange_spec_init->Value);
            token_destroy($subrange_spec_init);
            $$ = token_cast($subrange_type_name, TYPE);
        }
    | identifier ':' subrange_spec_init {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(nResult = EFAULT;;) {
                    if((pToken = lexer_new(subrange_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {
                log_error("%s: Unknown data type in subrange type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $subrange_spec_init);
            $$ = NULL;
        }
    | subrange_type_name subrange_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in subrange type declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($subrange_type_name, $subrange_spec_init);
            YYERROR;
            $$ = NULL;
        };

subrange_spec_init: subrange_specification
    | subrange_specification _assign signed_integer {
            /* It is an error if the value of a value of a subrange type falls outside the specified range of values. */
            PARSE *pParse;

            /*
                According to Annex E (Error conditions), the following error messages should 
                be modified to read "Value of a variable exceeds the specified subrange" 
                (Table E.1 - Error conditions).
            */

            pParse = &Context->Parse;
            /* assert($subrange_specification->Flags & FLAG_SUBRANGE); */
            switch($subrange_specification->Value.Type) {
                case TYPE_LINT:
                    if($signed_integer->Value.Value.S64 > $subrange_specification->Value.Maximum.S64) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%lld..%lld) in type declaration [%u:%u]",
                                pParse->File, 
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S64,
                                $subrange_specification->Value.Maximum.S64,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < $subrange_specification->Value.Minimum.S32) {
                        log_error("%s: Assigned value (%lld) less than subrange (%lld..%lld) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S64,
                                $subrange_specification->Value.Maximum.S64,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.S64 = $signed_integer->Value.Value.S64;
                    break;

                case TYPE_DINT:
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.S32) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S32,
                                $subrange_specification->Value.Maximum.S32,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.S32) {
                        log_error("%s: Assigned value (%lld) less than subrange (%ld..%ld) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S32,
                                $subrange_specification->Value.Maximum.S32,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.S32 = (int32_t) $signed_integer->Value.Value.S64;
                    break;

                case TYPE_INT:
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.S16) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S16,
                                $subrange_specification->Value.Maximum.S16,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.S16) {
                        log_error("%s: Assigned value (%lld) less than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S16,
                                $subrange_specification->Value.Maximum.S16,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.S16 = (int16_t) $signed_integer->Value.Value.S64;
                    break;
                    
                case TYPE_SINT:                    
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.S8) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S8,
                                $subrange_specification->Value.Maximum.S8,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.S8) {
                        log_error("%s: Assigned value (%lld) less than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.S8,
                                $subrange_specification->Value.Maximum.S8,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.S8 = (int8_t) $signed_integer->Value.Value.S64;
                    break;

                case TYPE_ULINT:
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.U64) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File, 
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U64,
                                $subrange_specification->Value.Maximum.U64,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.U64) {
                        log_error("%s: Assigned value (%lld) less than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U64,
                                $subrange_specification->Value.Maximum.U64,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.U64 = (uint64_t) $signed_integer->Value.Value.S64;
                    break;
                                
                case TYPE_UDINT:
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.U32) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U32,
                                $subrange_specification->Value.Maximum.U32,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.U32) {
                        log_error("%s: Assigned value (%lld) less than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File, 
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U32,
                                $subrange_specification->Value.Maximum.U32,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.U32 = (uint32_t) $signed_integer->Value.Value.S64;
                    break;
                
                case TYPE_UINT:
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.U16) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U16,
                                $subrange_specification->Value.Maximum.U16,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.U16) {
                        log_error("%s: Assigned value (%lld) less than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U16,
                                $subrange_specification->Value.Maximum.U16,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.U16 = (uint16_t) $signed_integer->Value.Value.S64;
                    break;
                
                case TYPE_USINT:
                    if($signed_integer->Value.Value.S64 > (int64_t) $subrange_specification->Value.Maximum.U8) {
                        log_error("%s: Assigned value (%lld) greater than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U8,
                                $subrange_specification->Value.Maximum.U8,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;
                    }
                    if($signed_integer->Value.Value.S64 < (int64_t) $subrange_specification->Value.Minimum.U8) {
                        log_error("%s: Assigned value (%lld) less than subrange (%d..%d) in type declaration [%u:%u]",
                                pParse->File,
                                $signed_integer->Value.Value.S64,
                                $subrange_specification->Value.Minimum.U8,
                                $subrange_specification->Value.Maximum.U8,
                                @signed_integer.first_line,
                                @signed_integer.first_column);
                        token_destroy($subrange_specification, $signed_integer);
                        YYERROR;                                
                    }
                    $subrange_specification->Value.Value.U8 = (uint8_t) $signed_integer->Value.Value.S64;
                    break;
                
                default:
                    token_destroy($subrange_specification, $signed_integer);
                    YYERROR;
            }
            token_destroy($signed_integer);
            $$ = $subrange_specification;
        };
    
subrange_specification: integer_type_name '(' subrange ')' {
            switch($integer_type_name->Value.Type) {
                case TYPE_LINT:
                    $integer_type_name->Value.Value.S64 = (int64_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.S64 = (int64_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.S64 = (int64_t) $subrange->Value.Minimum.S64;
                    break;
                
                case TYPE_DINT:
                    $integer_type_name->Value.Value.S32 = (int32_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.S32 = (int32_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.S32 = (int32_t) $subrange->Value.Minimum.S64;
                    break;

                case TYPE_INT:
                    $integer_type_name->Value.Value.S16 = (int16_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.S16 = (int16_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.S16 = (int16_t) $subrange->Value.Minimum.S64;
                    break;

                case TYPE_SINT:
                    $integer_type_name->Value.Value.S8 = (int8_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.S8 = (int8_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.S8 = (int8_t) $subrange->Value.Minimum.S64;
                    break;

                case TYPE_ULINT:
                    $integer_type_name->Value.Value.U64 = (uint64_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.U64 = (uint64_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.U64 = (uint64_t) $subrange->Value.Minimum.S64;
                    break;
                
                case TYPE_UDINT:
                    $integer_type_name->Value.Value.U32 = (uint32_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.U32 = (uint32_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.U32 = (uint32_t) $subrange->Value.Minimum.S64;
                    break;

                case TYPE_UINT:
                    $integer_type_name->Value.Value.U16 = (uint16_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.U16 = (uint16_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.U16 = (uint16_t) $subrange->Value.Minimum.S64;
                    break;

                case TYPE_USINT:
                    $integer_type_name->Value.Value.U8 = (uint8_t) $subrange->Value.Value.S64;
                    $integer_type_name->Value.Maximum.U8 = (uint8_t) $subrange->Value.Maximum.S64;
                    $integer_type_name->Value.Minimum.U8 = (uint8_t) $subrange->Value.Minimum.S64;
                    break;

                default:
                    YYERROR;
            }
            $integer_type_name->Value.Flags = $subrange->Value.Flags;
            token_destroy($subrange);
            $$ = $integer_type_name;
        }
    | subrange_type_name  {
            $subrange_type_name->Value.Type = TYPE_DERIVED;
            $subrange_type_name->Value.Meta = strdup($subrange_type_name->Name);
            $$ = token_cast($subrange_type_name, TYPE);
        }
    | integer_type_name subrange ')' {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing '(' in subrange type declaration [%u:%u]",
                    pParse->File,
                    @subrange.first_line,
                    @subrange.first_column);
            token_destroy($integer_type_name, $subrange);
            YYERROR;
            $$ = NULL;
        }
    | integer_type_name '(' subrange {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ')' in subrange type declaration [%u:%u]",
                    pParse->File,
                    @subrange.last_line,
                    @subrange.last_column);
            token_destroy($integer_type_name, $subrange);
            YYERROR;
            $$ = NULL;
        }
    | integer_type_name subrange {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing brackets in subrange type declaration [%u:%u]",
                    pParse->File,
                    @subrange.first_line,
                    @subrange.first_column);
            token_destroy($integer_type_name, $subrange);
            YYERROR;
            $$ = NULL;
        };
    
subrange: signed_integer _range signed_integer {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            if($1->Value.Value.S64 > $3->Value.Value.S64) {
                log_error("%s: Incorrect order for subrange specification [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                YYERROR;
            }
            pToken = token_new(integer);
            pToken->Value.Type = pToken->Value.Cast = TYPE_LINT;
            pToken->Value.Maximum.S64 = $3->Value.Value.S64;
            pToken->Value.Minimum.S64 = $1->Value.Value.S64;
            pToken->Value.Value.S64 = pToken->Value.Minimum.S64;
            pToken->Value.Flags |= FLAG_SUBRANGE;
            token_destroy($1, $3);
            $$ = pToken;
        };

enumerated_type_declaration: enumerated_type_name ':' enumerated_spec_init {
            if($enumerated_spec_init) {
                $enumerated_spec_init->Name = strdup($enumerated_type_name->Name);
                $enumerated_spec_init->Line = $enumerated_type_name->Line;
                $enumerated_spec_init->Column = $enumerated_type_name->Column;
            }
            token_destroy($enumerated_type_name);
            $$ = $enumerated_spec_init;
        }
    | identifier ':' enumerated_spec_init {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(nResult = EFAULT;;) {
                    if((pToken = lexer_new(enumerated_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {
                log_error("%s: Unknown data type in enumerated type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $enumerated_spec_init);
            $$ = NULL;
        }
    | enumerated_type_name enumerated_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in enumerated type declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($enumerated_type_name, $enumerated_spec_init);
            YYERROR;
            $$ = NULL;
        };

enumerated_spec_init: enumerated_specification _assign enumerated_value {
            PARSE *pParse;
            TOKEN_LIST *pList;
            TOKEN *pToken;
            int nResult;

            nResult = -ENOENT;
            pParse = &Context->Parse;
            pList = (TOKEN_LIST *) $enumerated_specification;
            token_list_reset(pList);
            while((pToken = token_list_iterate(pList)) != NULL) {
                if(strcmp(pToken->Name, $enumerated_value->Name) != 0)
                    continue;
                nResult = 0;
                break;
            }
            if(nResult != 0) {
                log_error("%s: Invalid value for assignment (%s) in enumerated type declaration [%u:%u]",
                        pParse->File,
                        $enumerated_value->Name,
                        @enumerated_value.first_line,
                        @enumerated_value.first_column);
                token_destroy($enumerated_specification, $enumerated_value);
                YYERROR;
            }
            value_assign(&pList->Token.Value, TYPE_ENUMERATED, strdup($enumerated_value->Name));
            token_destroy($enumerated_value);
            $$ = (TOKEN *) pList;
        }
    | enumerated_specification;

enumerated_specification: '(' _enumerated_value ')' {
            $$ = (TOKEN *) $_enumerated_value;
        } 
    | enumerated_type_name {
            $enumerated_type_name->Value.Type = TYPE_DERIVED;
            $enumerated_type_name->Value.Meta = strdup($enumerated_type_name->Name);
            $$ = token_cast($enumerated_type_name, TYPE);
        }
    | _enumerated_value ')' {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing '(' in enumerated type declaration [%u:%u]",
                    pParse->File,
                    @_enumerated_value.first_line,
                    @_enumerated_value.first_column);
            token_destroy($_enumerated_value);
            YYERROR;
            $$ = NULL;
        }
    | '(' _enumerated_value {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ')' in enumerated type declaration [%u:%u]",
                    pParse->File,
                    @_enumerated_value.last_line,
                    @_enumerated_value.last_column);
            token_destroy($_enumerated_value);
            YYERROR;
            $$ = NULL;
        };

enumerated_value: /* identifier '#' identifier
    | */ identifier {
            value_assign(&$identifier->Value, TYPE_ENUMERATED, NULL);
            $$ = $identifier;
        };

array_type_declaration: array_type_name ':' array_spec_init {
            $array_spec_init->Name = strdup($array_type_name->Name);
            $array_spec_init->Line = $array_type_name->Line;
            $array_spec_init->Column = $array_type_name->Column;
            token_destroy($array_type_name);
            $$ = $array_spec_init;
        }
    | identifier ':' array_spec_init {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(nResult = EFAULT;;) {
                    if((pToken = lexer_new(array_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else 
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {    
                log_error("%s: Unknown data type in array type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $array_spec_init);
            $$ = NULL;
        }
    | identifier array_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in array type declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($identifier, $array_spec_init);
            YYERROR;
            $$ = NULL;
        };

array_spec_init: array_specification _assign array_initialization {
            PARSE *pParse;
            TOKEN_LIST *pList;
            int nCount;

            pParse = &Context->Parse;
            if(! pParse->Preparse) {
                pList = (TOKEN_LIST *) $array_initialization;
                nCount = $array_specification->Value.Index.Upper - $array_specification->Value.Index.Lower + 1;
                if(pList->List.Size < (unsigned) nCount) {
                    log_warn("%s: Number of elements less than array size in array initialization [%u:%u]",
                            pParse->File,
                            @array_initialization.first_line,
                            @array_initialization.first_column);
                }
                else if(pList->List.Size > (unsigned) nCount) {
                    log_warn("%s: Number of elements greater than array size in array initialization [%u:%u]",
                            pParse->File,
                            @array_initialization.first_line,
                            @array_initialization.first_column);
                }
                $array_specification->Value.Value.Pointer = pList;
            }
            $$ = $array_specification;
        }
    | array_specification;

array_specification: ARRAY '[' subrange ']' OF non_generic_type_name {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                $non_generic_type_name->Value.Value.Pointer = NULL;
                $non_generic_type_name->Value.Index.Upper = $subrange->Value.Maximum.S64;
                $non_generic_type_name->Value.Index.Lower = $subrange->Value.Minimum.S64;
                $non_generic_type_name->Value.Flags |= FLAG_ARRAY;

                if($non_generic_type_name->Value.Type == TYPE_NONE) {
                    $non_generic_type_name->Value.Type = TYPE_DERIVED;
                    $non_generic_type_name->Value.Meta = strdup($non_generic_type_name->Name);
                }
                token_destroy($subrange);
                pToken = token_cast($non_generic_type_name, TYPE);
            }
            else
                token_destroy($subrange, $non_generic_type_name);

            $$ = pToken;
        } 
    | ARRAY '[' subrange ']' OF identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Invalid data type in array specification [%u:%u]",                
                        pParse->File,
                        @identifier.first_line, 
                        @identifier.first_column);
                token_destroy($subrange, $identifier);
                YYERROR;
            }
            token_destroy($subrange, $identifier);
            $$ = NULL;
        };

array_initialization: '[' _array_initial_elements ']' {
            $$ = (TOKEN *) $_array_initial_elements;
        };

array_initial_elements: array_initial_element {
            TOKEN_LIST *pList;

            pList = token_list_new(TYPE);
            token_list_insert(pList, $array_initial_element);
            $$ = pList;
        }
    | integer '(' array_initial_element ')' {
            TOKEN_LIST *pList;
            int nIndex;

            pList = token_list_new(TYPE);
            for(nIndex = 0; nIndex < $integer->Value.Value.S64; ++nIndex) {
                token_list_insert(pList, $array_initial_element);
            }
            token_destroy($integer);
            $$ = pList;
        };

array_initial_element: constant 
    | enumerated_value
    | structure_initialization
    | array_initialization;

structure_type_declaration: structure_type_name ':' structure_specification {
            if($structure_specification) {
                $structure_specification->Name = strdup($structure_type_name->Name);
                $structure_specification->Line = $structure_type_name->Line;
                $structure_specification->Column = $structure_type_name->Column;
                $structure_specification->Value.Type = TYPE_STRUCTURED;
            }
            token_destroy($structure_type_name);
            $$ = $structure_specification;
        }
    | identifier ':' structure_specification {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(nResult = EFAULT;;) {
                    if((pToken = lexer_new(structure_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {
                log_error("%s: Unknown data type in structure type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $structure_specification);
            $$ = NULL;
        };

structure_specification: structure_declaration 
    | initialized_structure;

initialized_structure: structure_type_name {
            $structure_type_name->Value.Type = TYPE_DERIVED;
            $structure_type_name->Value.Meta = strdup($structure_type_name->Name);
            $$ = token_cast($structure_type_name, TYPE);
        }
    | structure_type_name _assign structure_initialization {
            $structure_type_name->Value.Type = TYPE_DERIVED;
            $structure_type_name->Value.Meta = strdup($structure_type_name->Name);
            $$ = token_cast($structure_type_name, TYPE);
        };

structure_declaration: STRUCT _structure_element_declaration END_STRUCT {
            $$ = (TOKEN *) $_structure_element_declaration;
        }
    | STRUCT END_STRUCT {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing structure declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            YYERROR;
            $$ = NULL;
        };

structure_element_declaration: identifier ':' simple_spec_init {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                $simple_spec_init->Name = strdup($identifier->Name);
                $simple_spec_init->Line = $identifier->Line;
                $simple_spec_init->Column = $identifier->Column;
                pToken = $simple_spec_init;
            }
            token_destroy($identifier);
            $$ = pToken;
        }
    | identifier ':' subrange_spec_init {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                $subrange_spec_init->Name = strdup($identifier->Name);
                $subrange_spec_init->Line = $identifier->Line;
                $subrange_spec_init->Column = $identifier->Column;
                pToken = $subrange_spec_init;
            }
            token_destroy($identifier);
            $$ = pToken;
        }
    | identifier ':' enumerated_spec_init {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                $enumerated_spec_init->Name = strdup($identifier->Name);
                $enumerated_spec_init->Line = $identifier->Line;
                $enumerated_spec_init->Column = $identifier->Column;
                pToken = $enumerated_spec_init;
            }
            token_destroy($identifier);
            $$ = pToken;
        }
    | identifier ':' array_spec_init {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                $array_spec_init->Name = strdup($identifier->Name);
                $array_spec_init->Line = $identifier->Line;
                $array_spec_init->Column = $identifier->Column;
                pToken = $array_spec_init;
            }
            token_destroy($identifier);
            $$ = pToken;
        }
    | identifier ':' identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown data type in structure element declaration [%u:%u]",
                        pParse->File,
                        @3.first_line,
                        @3.first_column);
                YYERROR;
            }
            token_destroy($1, $3);
            $$ = NULL;
        }
    /* | identifier ':' initialized_structure */;

structure_initialization: '(' _structure_element_initialization ')' {
            $$ = (TOKEN *) $_structure_element_initialization;
        };

structure_element_initialization: identifier _assign constant {
            if($constant) {
                $constant->Name = strdup($identifier->Name);
                $constant->Line = $identifier->Line;
                $constant->Column = $identifier->Column;
            }
            token_destroy($identifier);
            $$ = $constant;
        }
    | identifier _assign enumerated_value {
            if($enumerated_value) {
                $enumerated_value->Name = strdup($identifier->Name);
                $enumerated_value->Line = $identifier->Line;
                $enumerated_value->Column = $identifier->Column;
            }
            token_destroy($identifier);
            $$ = $enumerated_value;
        }
    | identifier _assign array_initialization {
            if($array_initialization) {
                $array_initialization->Name = strdup($identifier->Name);
                $array_initialization->Line = $identifier->Line;
                $array_initialization->Column = $identifier->Column;
            }
            token_destroy($identifier);
            $$ = $array_initialization;
        }
    | identifier _assign structure_initialization {
            if($structure_initialization) {
                $structure_initialization->Name = strdup($identifier->Name);
                $structure_initialization->Line = $identifier->Line;
                $structure_initialization->Column = $identifier->Column;
            }
            token_destroy($identifier);
            $$ = $structure_initialization;
        };

string_type_declaration: string_type_name ':' STRING '[' integer ']' _assign character_string {
            PARSE *pParse;
            size_t uLength;

            pParse = &Context->Parse;
            uLength = $integer->Value.Value.S64;
            value_allocate(&$string_type_name->Value, TYPE_STRING, uLength);
            if($character_string->Value.Length > uLength) {
                log_warn("%s: Character string length (%d) exceeds string type declaration (%lld) [%u:%u]",
                        pParse->File,
                        $character_string->Value.Length,
                        uLength,
                        @character_string.first_line,
                        @character_string.first_column);
            }
            if($character_string->Value.Length < uLength) {
                uLength = $character_string->Value.Length;
            }
            memcpy($string_type_name->Value.Value.Pointer, $character_string->Value.Value.Pointer, uLength);
            token_destroy($integer, $character_string);
            $$ = $string_type_name;
        }
    | string_type_name ':' STRING '[' integer ']' {
            value_allocate(&$string_type_name->Value, TYPE_STRING, $integer->Value.Value.S64);
            token_destroy($integer);
            $$ = $string_type_name;
        }
    | identifier ':' STRING '[' integer ']' _assign character_string {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(;;) {
                    if((pToken = lexer_new(string_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {
                log_error("%s: Unknown data type in string type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $integer, $character_string);
            $$ = NULL;
        }
    | identifier ':' STRING '[' integer ']' {
            PARSE *pParse;
            LEXER_TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(;;) {
                    if((pToken = lexer_new(string_type_name, $identifier->Name)) != NULL) {
                        if((nResult = tree_insert(&pParse->Identifiers, pToken)) == 0)
                            break;
                        lexer_destroy(pToken);
                    }
                    else
                        nResult = errno;

                    if(nResult == EEXIST) {
                        log_error("%s: Duplicate type declaration: %s [%u:%u]",
                                pParse->File,
                                $identifier->Name,
                                $identifier->Line,
                                $identifier->Column);
                        YYERROR;
                        break;
                    }
                
                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else {
                log_error("%s: Unknown data type in string type declaration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $integer);
            $$ = NULL;
        };

_array_initial_elements: array_initial_elements
    | _array_initial_elements ',' array_initial_elements {
            token_list_merge($1, $array_initial_elements);
            token_destroy($array_initial_elements);
            $$ = $1;
        };

_enumerated_value: enumerated_value {
            TOKEN_LIST *pList;

            pList = token_list_new(TYPE);
            value_assign(&pList->Token.Value, TYPE_ENUMERATED, NULL);
            token_list_insert(pList, $enumerated_value);
            $$ = pList;
        }
    | _enumerated_value ',' enumerated_value {
            token_list_insert($1, $enumerated_value);
            $$ = $1;
        };

_structure_element_declaration: structure_element_declaration ';' {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_new(TYPE);
                if($structure_element_declaration)
                    token_list_insert(pList, $structure_element_declaration);
            }
            $$ = pList;
        }
    | _structure_element_declaration structure_element_declaration ';' {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) 
                token_list_insert($1, $structure_element_declaration);
            $$ = $1;
        }
    | structure_element_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after type declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($structure_element_declaration);
            YYERROR;
            $$ = NULL;
        }
    | _structure_element_declaration structure_element_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after type declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            token_destroy($structure_element_declaration);
            YYERROR;
            $$ = NULL;
        };

_structure_element_initialization: structure_element_initialization {
            TOKEN_LIST *pList;

            pList = token_list_new(STRUCT);
            token_list_insert(pList, $structure_element_initialization);
            $$ = pList;
        }
    | _structure_element_initialization ',' structure_element_initialization {
            token_list_insert($1, $structure_element_initialization);
            $$ = $1;
        };

_type_declaration: type_declaration ';' {
            TOKEN_LIST *pList;

            pList = token_list_new(TYPE);
            if($type_declaration)
                token_list_insert(pList, $type_declaration);
            $$ = pList;
        }
    | _type_declaration type_declaration ';' {
            if($type_declaration)
                token_list_insert($1, $type_declaration);
            $$ = $1;
        }
    | type_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after type declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($type_declaration);
            YYERROR;
            $$ = NULL;
        }
    | _type_declaration type_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after type declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            token_destroy($type_declaration);
            YYERROR;
            $$ = NULL;
        };


/* B.1.4 Variables */

/*  variable ::= direct_variable | symbolic_variable

    symbolic_variable ::= variable_name | multi_element_variable
    
    variable_name ::= identifier */


/* B.1.4.1 Directly represented variables */

/*  direct_variable ::= '%' location_prefix size_prefix integer {'.' integer}

    location_prefix ::= 'I' | 'Q' | 'M'

    size_prefix ::= NIL | 'X' | 'B' | 'W' | 'D' | 'L' */


/* B.1.4.2 Multi-element variables */ 

/*  multi_element_variable ::= array_variable | structured_variable

    array_variable ::= subscripted_variable subscript_list

    subscripted_variable ::= symbolic_variable

    subscript_list ::= '[' subscript {',' subscript} ']'

    subscript ::= expression

    structured_variable ::= record_variable '.' field_selector

    record_variable ::= symbolic_variable

    field_selector ::= identifier */


/* B.1.4.3 Declaration and initialization */

/*  input_declarations ::=
        'VAR_INPUT' ['RETAIN' | 'NON_RETAIN']
        input_declaration ';'
        {input_declaration ';'}
        'END_VAR'

    input_declaration ::= var_init_decl | edge_declaration

    edge_declaration ::= var1_list ':' 'BOOL' ('R_EDGE' | 'F_EDGE')

    var_init_decl ::= var1_init_decl | array_var_init_decl
        | structured_var_init_decl | fb_name_decl | string_var_declaration

    var1_init_decl ::= var1_list ':'
        (simple_spec_init | subrange_spec_init | enumerated_spec_init)

    var1_list ::= variable_name {',' variable_name}

    array_var_init_decl ::= var1_list ':' array_spec_init

    structured_var_init_decl ::= var1_list ':' initialized_structure

    fb_name_decl ::= fb_name_list ':' function_block_type_name
        [ ':=' structure_initialization ]

    fb_name_list ::= fb_name {',' fb_name}

    fb_name ::= identifier

    output_declarations ::=
        'VAR_OUTPUT' ['RETAIN' | 'NON_RETAIN']
         var_init_decl ';'
         {var_init_decl ';'}
        'END_VAR'

    input_var_init_decls ::=
        'VAR_IN_OUT'
        var_declaration ';'
        {var_declaration ';'}
        'END_VAR'

    var_declaration ::= temp_var_decl | fb_name_decl

    temp_var_decl ::= var1_declaration | array_var_declaration
        | structured_var_declaration | string_var_declaration

    var1_declaration ::= var1_list ':' (simple_specification
        | subrange_specification | enumerated_specification) 

    array_var_declaration ::= var1_list ':' array_specification

    structured_var_declaration ::= var1_list ':' structure_type_name

    var_declarations ::=
        'VAR' ['CONSTANT']
        var_init_decl ';'
        {(var_init_decl ';')}
        'END_VAR'

    retentive_var_declarations ::=
        'VAR' 'RETAIN'
        var_init_decl ';'
        {var_init_decl ';'}
        'END_VAR'

    located_var_declarations ::=
        'VAR' ['CONSTANT' | 'RETAIN' | 'NON_RETAIN']
         located_var_decl ';'
         {located_var_decl ';'}
        'END_VAR'

    located_var_decl ::= [variable_name] location ':' located_var_spec_init

    external_var_declarations :=
        'VAR_EXTERNAL' ['CONSTANT']
        external_declaration ';'
        {external_declaration ';'}
        'END_VAR'

    external_declaration ::= global_var_name ':'
        (simple_specification | subrange_specification
        | enumerated_specification | array_specification
        | structure_type_name | function_block_type_name)

    global_var_name ::= identifier

    global_var_declarations :=
        'VAR_GLOBAL' ['CONSTANT' | 'RETAIN']
        global_var_decl ';'
        {global_var_decl ';'}
        'END_VAR'

    global_var_decl ::= global_var_spec ':'
        [ located_var_spec_init | function_block_type_name ]

    global_var_spec ::= global_var_list | [global_var_name] location

    located_var_spec_init ::= simple_spec_init | subrange_spec_init
        | enumerated_spec_init | array_spec_init | initialized_structure
        | single_byte_string_spec | double_byte_string_spec

    location ::= 'AT' direct_variable

    global_var_list ::= global_var_name {',' global_var_name}

    string_var_declaration ::= single_byte_string_var_declaration
        | double_byte_string_var_declaration

    single_byte_string_var_declaration ::=
        var1_list ':' single_byte_string_spec

    single_byte_string_spec ::=
        'STRING' ['[' integer ']'] [':=' single_byte_character_string] 

    double_byte_string_var_declaration ::=
        var1_list ':' double_byte_string_spec

    double_byte_string_spec ::=
        'WSTRING' ['[' integer ']'] [':=' double_byte_character_string]

    incompl_located_var_declarations ::=
        'VAR' ['RETAIN'|'NON_RETAIN']
         incompl_located_var_decl ';'
         {incompl_located_var_decl ';'}
        'END_VAR'

    incompl_located_var_decl ::= variable_name incompl_location ':' var_spec

    incompl_location ::= 'AT' '%' ('I' | 'Q' | 'M') '*'

    var_spec ::= simple_specification
        | subrange_specification | enumerated_specification
        | array_specification | structure_type_name
        | 'STRING' ['[' integer ']'] | 'WSTRING' ['[' integer ']'] */

input_declarations:
    VAR_INPUT RETAIN _input_declaration END_VAR {
            TOKEN *pToken;

            token_list_reset($_input_declaration);
            while((pToken = token_list_iterate($_input_declaration)) != NULL) {
                pToken->Value.Flags |= FLAG_RETAIN;
            }
            $$ = $_input_declaration;
        }
    | VAR_INPUT NON_RETAIN _input_declaration END_VAR {
            TOKEN *pToken;

            token_list_reset($_input_declaration);
            while((pToken = token_list_iterate($_input_declaration)) != NULL) {
                pToken->Value.Flags |= FLAG_NON_RETAIN;
            }
            $$ = $_input_declaration;
        }
    | VAR_INPUT _input_declaration END_VAR {
            $$ = $_input_declaration;
        };

input_declaration: var_init_decl {
            $$ = token_list_cast($var_init_decl, VAR_INPUT);
            $$->Token.Value.Type = TYPE_INPUT;
        }
    | edge_declaration {
            $$ = token_list_cast($edge_declaration, VAR_INPUT);
            $$->Token.Value.Type = TYPE_INPUT;
        };

edge_declaration: var1_list ':' BOOL R_EDGE {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$BOOL->Value);
                pToken->Value.Flags |= FLAG_R_EDGE;
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($BOOL);
            $$ = $var1_list;
        }
    | var1_list ':' BOOL F_EDGE {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$BOOL->Value);
                pToken->Value.Flags |= FLAG_F_EDGE;
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($BOOL);
            $$ = $var1_list;
        }
    | var1_list BOOL R_EDGE {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in rising edge declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($var1_list, $BOOL);
            YYERROR;
            $$ = NULL;
        }
    | var1_list BOOL F_EDGE {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in falling edge declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($var1_list, $BOOL);
            YYERROR;
            $$ = NULL;
        };

var_init_decl: var1_init_decl 
    | array_var_init_decl 
    | structured_var_init_decl
    | fb_name_decl
    | string_var_declaration;

var1_init_decl: var1_list ':' simple_spec_init {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$simple_spec_init->Value);
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($simple_spec_init);
            $$ = $var1_list;
        } 
    | var1_list ':' subrange_spec_init {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$subrange_spec_init->Value);
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($subrange_spec_init);
            $$ = $var1_list;
        }
    | var1_list ':' enumerated_spec_init {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$enumerated_spec_init->Value);
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($enumerated_spec_init);
            $$ = $var1_list;
        }
    | var1_list simple_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in variable initialization declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($var1_list, $simple_spec_init);
            YYERROR;
            $$ = NULL;
        } 
    | var1_list subrange_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in variable initialization declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($var1_list, $subrange_spec_init);
            YYERROR;
            $$ = NULL;
        }
    | var1_list enumerated_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in variable initialization declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($var1_list, $enumerated_spec_init);
            YYERROR;
            $$ = NULL;
        };

var1_list: _variable_name {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $_variable_name);
            $$ = pList;
        }
    | identifier {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(strlen($identifier->Name) <= SYMBOL_NAME_MAX) {
                if(parse_register(pParse, _variable_name, $identifier->Name) != 0)
                    YYABORT;
                pList = token_list_new(0);
                token_list_insert(pList, $identifier);
            }
            else {
                log_error("%s: Variable name longer than implementation limit (%u) [%u:%u]",
                        pParse->File,
                        SYMBOL_NAME_MAX,
                        @identifier.first_line,
                        @identifier.first_column);
                token_destroy($identifier);
                YYERROR;
            }
            $$ = pList;
        }
    | var1_list ',' _variable_name {
            token_list_insert($1, $_variable_name);
            $$ = $1;
        }
    | var1_list ',' identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(strlen($identifier->Name) <= SYMBOL_NAME_MAX) {
                if(parse_register(pParse, _variable_name, $identifier->Name) != 0)
                    YYABORT;
                token_list_insert($1, $identifier);
            }
            else {
                log_error("%s: Variable name longer than implementation limit (%u) [%u:%u]", 
                        pParse->File,
                        /* $identifier->Name, */
                        SYMBOL_NAME_MAX,
                        @identifier.first_line,
                        @identifier.first_column);
                token_destroy($identifier);
                YYERROR;
            }
            $$ = $1;
        };

array_var_init_decl: var1_list ':' array_spec_init {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$array_spec_init->Value);
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($array_spec_init);
            $$ = $var1_list;
        };

structured_var_init_decl: var1_list ':' initialized_structure {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$initialized_structure->Value);
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($initialized_structure);
            $$ = $var1_list;            
        };

fb_name_decl: var1_list ':' function_block_type_name {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$function_block_type_name->Value);
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate variable declaration: %s [%u:%u]", 
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($function_block_type_name);
            $$ = $var1_list;
        };

output_declarations:
    VAR_OUTPUT RETAIN _var_init_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_var_init_decl);
            while((pToken = token_list_iterate($_var_init_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_RETAIN;
            }
            $$ = token_list_cast($_var_init_decl, VAR_OUTPUT);
            $$->Token.Value.Type = TYPE_OUTPUT;
        }
    | VAR_OUTPUT NON_RETAIN _var_init_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_var_init_decl);
            while((pToken = token_list_iterate($_var_init_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_NON_RETAIN;
            }
            $$ = token_list_cast($_var_init_decl, VAR_OUTPUT);
            $$->Token.Value.Type = TYPE_OUTPUT;
        }
    | VAR_OUTPUT _var_init_decl END_VAR {
            $$ = token_list_cast($_var_init_decl, VAR_OUTPUT);
            $$->Token.Value.Type = TYPE_OUTPUT;
        };


input_var_init_decls:
    VAR_IN_OUT _var_declaration END_VAR {
            $$ = token_list_cast($_var_declaration, VAR_IN_OUT);
            $$->Token.Value.Type = TYPE_IN_OUT;
        };

var_declaration: temp_var_decl
    | fb_name_decl;

temp_var_decl: var1_declaration 
    | array_var_declaration
    | structured_var_declaration
    | string_var_declaration;

var1_declaration: var1_list ':' simple_specification {
            TOKEN *pToken;

            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$simple_specification->Value);
            }
            token_destroy($simple_specification);
            $$ = $var1_list;
        } 
    | var1_list ':' subrange_specification {
            TOKEN *pToken;

            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &($subrange_specification->Value));
            }
            token_destroy($subrange_specification);
            $$ = $var1_list;
        } 
    | var1_list ':' enumerated_specification {
            TOKEN *pToken;

            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$enumerated_specification->Value);
            }
            token_destroy($enumerated_specification);
            $$ = $var1_list;
        }
    | var1_list simple_specification {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in variable declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($simple_specification);
            YYERROR;
            $$ = NULL;
        } 
    | var1_list subrange_specification {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in variable declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($subrange_specification);
            YYERROR;
            $$ = NULL;
        }
    | var1_list enumerated_specification {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in variable declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($enumerated_specification);
            YYERROR;  
            $$ = NULL;      
        };

array_var_declaration: var1_list ':' array_specification {
            TOKEN *pToken;

            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$array_specification->Value);
            }
            token_destroy($array_specification);
            $$ = $var1_list;
        };

structured_var_declaration: var1_list ':' structure_type_name {
            TOKEN *pToken;

            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$structure_type_name->Value);
            }
            token_destroy($structure_type_name);
            $$ = $var1_list;
        };

var_declarations: VAR CONSTANT _var_init_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_var_init_decl);
            while((pToken = token_list_iterate($_var_init_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_CONSTANT;
            }
            $$ = token_list_cast($_var_init_decl, VAR);
        }
    | VAR _var_init_decl END_VAR {
            $$ = token_list_cast($_var_init_decl, VAR);
        };

retentive_var_declarations: VAR RETAIN _var_init_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_var_init_decl);
            while((pToken = token_list_iterate($_var_init_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_RETAIN;
            }
            $$ = token_list_cast($_var_init_decl, VAR);
        };

located_var_declarations:
    VAR CONSTANT _located_var_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_located_var_decl);
            while((pToken = token_list_iterate($_located_var_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_CONSTANT;
            }
            $$ = token_list_cast($_located_var_decl, VAR);
        }
    | VAR RETAIN _located_var_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_located_var_decl);
            while((pToken = token_list_iterate($_located_var_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_RETAIN;
            }
            $$ = token_list_cast($_located_var_decl, VAR);
        }
    | VAR NON_RETAIN _located_var_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_located_var_decl);
            while((pToken = token_list_iterate($_located_var_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_NON_RETAIN;
            }
            $$ = token_list_cast($_located_var_decl, VAR);
        }
    | VAR _located_var_decl END_VAR {
            $$ = token_list_cast($_located_var_decl, VAR);
        };

located_var_decl: _variable_name location ':' located_var_spec_init 
    | location ':' located_var_spec_init;

external_var_declarations: VAR_EXTERNAL CONSTANT _external_declaration END_VAR {
            TOKEN *pToken;

            token_list_reset($_external_declaration);
            while((pToken = token_list_iterate($_external_declaration)) != NULL) {
                pToken->Value.Flags |= FLAG_CONSTANT;
            }
            $$ = token_list_cast($_external_declaration, VAR_EXTERNAL);
        }
    | VAR_EXTERNAL _external_declaration END_VAR {
            $$ = token_list_cast($_external_declaration, VAR_EXTERNAL);
        };

external_declaration: global_var_name ':' simple_specification {
            value_copy(&$global_var_name->Value, &$simple_specification->Value);
            token_destroy($simple_specification);
            $$ = $global_var_name;
        }
    | global_var_name ':' subrange_specification {
            value_copy(&$global_var_name->Value, &$subrange_specification->Value);
            token_destroy($subrange_specification);
            $$ = $global_var_name;
        }
    | global_var_name ':' enumerated_specification {
            value_copy(&$global_var_name->Value, &$enumerated_specification->Value);
            token_destroy($enumerated_specification);
            $$ = $global_var_name;
        }
    | global_var_name ':' array_specification {
            value_copy(&$global_var_name->Value, &$array_specification->Value);
            token_destroy($array_specification);
            $$ = $global_var_name;
        }
    | global_var_name ':' structure_type_name {
            value_copy(&$global_var_name->Value, &$structure_type_name ->Value);
            token_destroy($structure_type_name);
            $$ = $global_var_name;
        }
    | global_var_name ':' function_block_type_name {
            value_copy(&$global_var_name->Value, &$function_block_type_name->Value);
            token_destroy($function_block_type_name);
            $$ = $global_var_name;
        };

global_var_name: _variable_name
    | identifier {
            PARSE *pParse;

            //  TODO: Review once VAR_ACCESS is implemented
            pParse = &Context->Parse;
            if(parse_register(pParse, _variable_name, $identifier->Name) != 0)
                YYABORT;
            $$ = $identifier;
        };

global_var_declarations:
    VAR_GLOBAL CONSTANT _global_var_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_global_var_decl);
            while((pToken = token_list_iterate($_global_var_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_CONSTANT;
            }
            $$ = token_list_cast($_global_var_decl, VAR_GLOBAL);
        }
    | VAR_GLOBAL RETAIN _global_var_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_global_var_decl);
            while((pToken = token_list_iterate($_global_var_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_RETAIN;
            }
            $$ = token_list_cast($_global_var_decl, VAR_GLOBAL);
        }
    | VAR_GLOBAL _global_var_decl END_VAR {
            $$ = token_list_cast($_global_var_decl, VAR_GLOBAL);
        };

global_var_decl: 
    global_var_spec ':' located_var_spec_init {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($global_var_spec);
            while((pToken = token_list_iterate($global_var_spec)) != NULL) {
                value_copy(&pToken->Value, &($located_var_spec_init->Value));
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate declaration of global variable: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($located_var_spec_init);
            $$ = $global_var_spec;
        }
    | global_var_spec ':' _function_block_type_name {
            PARSE *pParse;
            TOKEN *pToken;
            int nResult;

            pParse = &Context->Parse;
            token_list_reset($global_var_spec);
            while((pToken = token_list_iterate($global_var_spec)) != NULL) {
                value_copy(&pToken->Value, &($_function_block_type_name->Value));
                if(pParse->Preparse) {
                    if((nResult = symbol_insert(Context, TOKEN_NAME(pParse->Configuration),
                            TOKEN_NAME(pParse->Resource),
                            TOKEN_NAME(pParse->POU),
                            pToken->Name, &pToken->Value)) != 0) {

                        if(nResult == EEXIST) {
                            log_error("%s: Duplicate declaration of global variable: %s [%u:%u]",
                                    pParse->File,
                                    pToken->Name,
                                    pToken->Line,
                                    pToken->Column);
                            YYERROR;
                            break;
                        }

                        log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                        YYABORT;
                    }
                }
            }
            token_destroy($_function_block_type_name);
            $$ = $global_var_spec;
        }
    | global_var_spec located_var_spec_init {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in global variable declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($global_var_spec, $located_var_spec_init);
            YYERROR;            
        }
    | global_var_spec _function_block_type_name {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in global variable declaration [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            token_destroy($global_var_spec, $_function_block_type_name);
            YYERROR;
        };

global_var_spec: global_var_list 
    | location {
            TOKEN_LIST *pList;

            pList = token_list_new(VAR_GLOBAL, @location.first_line, @location.first_column);
            token_list_insert(pList, $location);
            $$ = pList;
        };
    /* | global_var_name location; */

located_var_spec_init: simple_spec_init
    | subrange_spec_init 
    | enumerated_spec_init
    | array_spec_init
    | initialized_structure
    | single_byte_string_spec /*
    | double_byte_string_spec */;

location: AT direct_variable {
            $$ = $direct_variable;
        };

global_var_list:
    global_var_name {
            TOKEN_LIST *pList;

            pList = token_list_new(VAR_GLOBAL, @global_var_name.first_line, @global_var_name.first_column);
            token_list_insert(pList, $global_var_name);
            $$ = pList;
        }
    | global_var_list ',' global_var_name {
            token_list_insert($1, $global_var_name);
            $$ = $1;
        };

string_var_declaration: single_byte_string_var_declaration
    /* | double_byte_string_var_declaration */;

single_byte_string_var_declaration: var1_list ':' single_byte_string_spec {
            TOKEN *pToken;

            token_list_reset($var1_list);
            while((pToken = token_list_iterate($var1_list)) != NULL) {
                value_copy(&pToken->Value, &$single_byte_string_spec->Value);
            }
            token_destroy($single_byte_string_spec);
            $$ = $var1_list;
        };

single_byte_string_spec: STRING '[' integer ']' _assign single_byte_character_string {
            PARSE *pParse;
            size_t uLength;

            pParse = &Context->Parse;
            uLength = $integer->Value.Value.S64;
            value_allocate(&$STRING->Value, TYPE_STRING, uLength);
            if($single_byte_character_string->Value.Length > uLength) {
                log_warn("%s: Character string length (%d) exceeds string specification (%lld) [%u:%u]",
                        pParse->File,
                        $single_byte_character_string->Value.Length,
                        uLength,
                        @single_byte_character_string.first_line,
                        @single_byte_character_string.first_column);
            }
            if($single_byte_character_string->Value.Length < uLength) {
                uLength = $single_byte_character_string->Value.Length;
            }
            memcpy($STRING->Value.Value.Pointer, $single_byte_character_string->Value.Value.Pointer, uLength);
            token_destroy($integer, $single_byte_character_string);
            $$ = $STRING;
        }
    | STRING '[' integer ']' {
            value_allocate(&$STRING->Value, TYPE_STRING, $integer->Value.Value.S64);
            token_destroy($integer);
            $$ = $STRING;
        };

/* double_byte_string_var_declaration */
/* double_byte_string_spec */
/* incompl_located_var_declarations */
/* incompl_located_var_decl */
/* incompl_location */
/* var_spec */

_external_declaration: external_declaration ';' {
            TOKEN_LIST *pList;

            pList = token_list_new(VAR_EXTERNAL, @external_declaration.first_line, @external_declaration.first_column);
            token_list_insert(pList, $external_declaration);
            $$ = pList;
        }
    | _external_declaration external_declaration ';' {
            token_list_insert($1, $external_declaration);
            $$ = $1;
        };

_global_var_decl: global_var_decl ';'
    | _global_var_decl global_var_decl ';' {
            token_list_insert($1, $global_var_decl);
            $$ = $1;
        }
    | global_var_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after global variable declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($global_var_decl);
            YYERROR;
        }
    | _global_var_decl global_var_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after global variable declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            token_destroy($global_var_decl);
            YYERROR;
        };

_global_var_declarations: %empty {
            $$ = token_list_new(VAR_GLOBAL);
        }
    | _global_var_declarations global_var_declarations {
            token_list_merge($1, $global_var_declarations);
            token_destroy($global_var_declarations);
            $$ = $1;
        };

_input_declaration: input_declaration ';' {
            $$ = $input_declaration;
        }
    | _input_declaration input_declaration ';' {
            token_list_merge($1, $input_declaration);
            token_destroy($input_declaration);
            $$ = $1;
        }
    | input_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after input variable declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($input_declaration);
            YYERROR;
        }
    | _input_declaration input_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after input variable declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            YYERROR;
        };

_located_var_decl: located_var_decl ';' {
            TOKEN_LIST *pList;

            pList = token_list_new(VAR);
            token_list_insert(pList, $located_var_decl);
            $$ = pList;
        }
    | _located_var_decl located_var_decl ';' {
            token_list_merge($1, $located_var_decl);  
            token_destroy($located_var_decl);
            $$ = $1;
        }
    | located_var_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after variable declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($located_var_decl);
            YYERROR;
        }
    | _located_var_decl located_var_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after variable declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            token_destroy($located_var_decl);
            YYERROR;
        };

_var_declaration: var_declaration ';' {
            $$ = token_list_cast($var_declaration, VAR_IN_OUT);
        }
    | _var_declaration var_declaration ';' {
            token_list_merge($1, $var_declaration);
            token_destroy($var_declaration);
            $$ = $1;
        } 
    | var_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after variable declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($var_declaration);
            YYERROR;
        }
    | _var_declaration var_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after variable declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            token_destroy($var_declaration);
            YYERROR;
        };

_var_init_decl: var_init_decl ';' {
            $$ = token_list_cast($var_init_decl, VAR);
        }
    | _var_init_decl var_init_decl ';' {
            token_list_merge($1, $var_init_decl);
            token_destroy($var_init_decl);
            $$ = $1;
        }
    | var_init_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after output variable declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            token_destroy($var_init_decl);
            YYERROR;
        }
    | _var_init_decl var_init_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after output variable declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            token_destroy($var_init_decl);
            YYERROR;
        };



/* B.1.5 Program organization units */

/* B.1.5.1 Functions */

/*  function_name ::= standard_function_name | derived_function_name

    standard_function_name ::= <as defined in 2.5.1.5>

    derived_function_name ::= identifier

    function_declaration ::=
        'FUNCTION' derived_function_name ':'
        (elementary_type_name | derived_type_name)
        { io_var_declarations | function_var_decls }
        function_body
        'END_FUNCTION'

    io_var_declarations ::= input_declarations | output_declarations |
        input_var_init_decls

    function_var_decls ::= 'VAR' ['CONSTANT']
        var2_init_decl ';' {var2_init_decl ';'} 'END_VAR'

    function_body ::= ladder_diagram | function_block_diagram
        | instruction_list | statement_list | <other languages>

    var2_init_decl ::= var1_init_decl | array_var_init_decl
        | structured_var_init_decl | string_var_declaration */

function_name: _function_name 
    | identifier {
            PARSE *pParse;
            LEXER_TOKEN *pToken;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(;;) {
                    if((pToken = lexer_new(_function_name, $identifier->Name)) != NULL) {
                        if(tree_insert(&pParse->Identifiers, pToken) == 0)
                            break;
                        lexer_destroy(pToken);
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else
                YYABORT;

            $$ = $identifier;
        };

function_declaration:
    FUNCTION function_name ':' _function_type_name { 
            PARSE *pParse;

            pParse = &Context->Parse;
            if(function_search(&Context->Functions, $function_name->Name) != NULL) {
                log_error("%s: Duplicate function declaration: %s [%u:%u]",
                        pParse->File,
                        $function_name->Name,
                        @function_name.first_line,
                        @function_name.first_column);
                YYERROR;
            }
            pParse->POU = $function_name; 
        }
        _io_function_var_decls
        function_body
        END_FUNCTION {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            for(pList = NULL;;) {
                if(pParse->Preparse)
                    break;

                pList = token_list_new(FUNCTION, @FUNCTION.first_line, @FUNCTION.first_column, $function_name->Name);
                value_copy(&pList->Token.Value, &$_function_type_name->Value);
                token_list_insert(pList, $_io_function_var_decls, $function_body);

                if(echidna_register(Context, $function_name->Name, TYPE_FUNCTION, runtime_function) != 0) {
                    log_error("%s: Failed to register function: %s [%u:%u]", 
                            pParse->File,
                            $function_name->Name,
                            @function_name.first_line,
                            @function_name.first_column);
                    YYERROR;
                }

                token_destroy($function_name, $_function_type_name);
                break;
            }

            pParse->POU = NULL;
            $$ = pList;
        }
    | FUNCTION function_name ':' _function_type_name { 
            PARSE *pParse;

            pParse = &Context->Parse;
            if(function_search(&Context->Functions, $function_name->Name) != NULL) {
                log_error("%s: Duplicate function declaration: %s [%u:%u]",
                        pParse->File,
                        $function_name->Name,
                        @function_name.first_line,
                        @function_name.first_column);
                YYERROR;
            }
            pParse->POU = $function_name; 
        }
        function_body
        END_FUNCTION {
            PARSE *pParse;
            TOKEN_LIST *pList;
            char *pName;

            pParse = &Context->Parse;
            for(pList = NULL;;) {
                if(pParse->Preparse) 
                    break;

                pList = token_list_new(FUNCTION, @FUNCTION.first_line, @FUNCTION.first_column, $function_name->Name);
                value_copy(&pList->Token.Value, &$_function_type_name->Value);
                token_list_insert(pList, $function_body);

                pName = TOKEN_NAME(pParse->POU);
                if(echidna_register(Context, pName, TYPE_FUNCTION, runtime_function) != 0) {
                    log_error("%s: Failed to register function: %s [%u:%u]", 
                            pParse->File,
                            pName,
                            @function_name.first_line,
                            @function_name.first_column);
                    YYERROR;
                }

                token_destroy($function_name, $_function_type_name);
                break;
            }

            pParse->POU = NULL;
            $$ = pList;
        }
    | FUNCTION identifier _function_type_name
        _io_function_var_decls
        function_body
        END_FUNCTION {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in function declaration [%u:%u]",
                    pParse->File,
                    @3.first_line,
                    @3.first_column);
            YYERROR;
        }
    | FUNCTION identifier _function_type_name
        function_body
        END_FUNCTION {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ':' in function declaration [%u:%u]",
                    pParse->File,
                    @3.first_line,
                    @3.first_column);
            YYERROR;
        };

io_var_declarations: input_declarations
    | output_declarations
    | input_var_init_decls;

function_var_decls:
    VAR CONSTANT _var2_init_decl END_VAR {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                token_list_reset($_var2_init_decl);
                while((pToken = token_list_iterate($_var2_init_decl)) != NULL) {
                    pToken->Value.Flags |= FLAG_CONSTANT;
                }
            }
            $$ = token_list_cast($_var2_init_decl, VAR);
        }
    | VAR _var2_init_decl END_VAR {
            $$ = token_list_cast($_var2_init_decl, VAR);
        };

function_body: instruction_list
    /* | statement_list */;

var2_init_decl: var1_init_decl
    | array_var_init_decl
    | structured_var_init_decl
    | string_var_declaration;

_function_type_name: elementary_type_name
    | identifier;

_io_function_var_decls: io_var_declarations {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $io_var_declarations);
            $$ = pList;
        }
    | function_var_decls {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $function_var_decls);
            $$ = pList;
        }
    | _io_function_var_decls io_var_declarations {
            token_list_insert($1, $io_var_declarations);
            $$ = $1;
        }
    | _io_function_var_decls function_var_decls {
            token_list_insert($1, $function_var_decls);
            $$ = $1;
        };

_var2_init_decl: var2_init_decl ';'
    | _var2_init_decl var2_init_decl ';' {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse)
                token_list_merge($1, $var2_init_decl);
            token_destroy($var2_init_decl);
            $$ = $1;
        }
    | var2_init_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after function variable declaration [%u:%u]",
                    pParse->File,
                    @1.last_line,
                    @1.last_column);
            YYERROR;
        }
    | _var2_init_decl var2_init_decl {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing ';' after function variable declaration [%u:%u]",
                    pParse->File,
                    @2.last_line,
                    @2.last_column);
            YYERROR;
        };

/* B.1.5.2 Function blocks */

/*  function_block_type_name ::= standard_function_block_type_name
        | derived_function_block_type_name

    standard_function_block_type_name ::= <as defined in 2.5.2.3>

    derived_function_block_type_name ::= identifier

    function_block_declaration ::=
        'FUNCTION_BLOCK' derived_function_block_type_name
         { io_var_declarations | other_var_declarations }
         function_block_body
        'END_FUNCTION_BLOCK'

    other_var_declarations ::= external_var_declarations | var_declarations
        | retentive_var_declarations | non_retentive_var_declarations
        | temp_var_decls | incompl_located_var_declarations

    temp_var_decls ::=
        'VAR_TEMP'
         temp_var_decl ';'
         {temp_var_decl ';'}
        'END_VAR'

    non_retentive_var_decls ::=
        'VAR' 'NON_RETAIN'
         var_init_decl ';'
         {var_init_decl ';'}
        'END_VAR'

    function_block_body ::= sequential_function_chart | ladder_diagram
        | function_block_diagram | instruction_list | statement_list
        | <other languages> */

function_block_type_name: _function_block_type_name {
            value_assign(&$_function_block_type_name->Value, TYPE_FUNCTION_BLOCK, $_function_block_type_name->Name);
            $$ = $_function_block_type_name;
        }
    | identifier {
            PARSE *pParse;
            LEXER_TOKEN *pToken;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                for(;;) {
                    if((pToken = lexer_new(_function_block_type_name, $identifier->Name)) != NULL) {
                        if(tree_insert(&pParse->Identifiers, pToken) == 0)
                            break;
                        lexer_destroy(pToken);
                    }

                    log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                    YYABORT;
                }
            }
            else
                YYABORT;

            value_assign(&$identifier->Value, TYPE_FUNCTION_BLOCK, $identifier->Name);
            $$ = $identifier;
        };

function_block_declaration: 
    FUNCTION_BLOCK function_block_type_name { 
            PARSE *pParse;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                if(function_search(&Context->Functions, $function_block_type_name->Name) != NULL) {
                    log_error("%s: Duplicate function block declaration: %s [%u:%u]",
                            pParse->File,
                            $function_block_type_name->Name,
                            @function_block_type_name.first_line,
                            @function_block_type_name.first_column);
                    YYERROR;
                }
            }
            pParse->POU = $function_block_type_name; 
        }
        _fb_var_declarations
        function_block_body
        END_FUNCTION_BLOCK {
            _FUNCTION_BLOCK *pBlock;
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(pParse->Preparse) {
                if((pBlock = yyfunction_create($function_block_type_name->Name, $_fb_var_declarations)) == NULL)
                    YYABORT;
                if(echidna_register(Context, $function_block_type_name->Name, TYPE_FUNCTION_BLOCK, pBlock) != 0) {
                    log_error("%s: Failed to register function: %s [%u:%u]", 
                            pParse->File,
                            $function_block_type_name->Name,
                            @function_block_type_name.first_line,
                            @function_block_type_name.first_column);
                    yyfunction_destroy(pBlock);
                    YYERROR;
                }
                token_destroy($_fb_var_declarations, $function_block_body);
            }
            else {
                pList = token_list_new(FUNCTION_BLOCK, @FUNCTION_BLOCK.first_line, @FUNCTION_BLOCK.first_column, $function_block_type_name->Name);
                value_copy(&pList->Token.Value, &$function_block_type_name->Value);
                token_list_insert(pList, $_fb_var_declarations, $function_block_body);
            }
            token_destroy($function_block_type_name);

            pParse->POU = NULL;
            $$ = pList;
        }
    | FUNCTION_BLOCK function_block_type_name 
        function_block_body 
        END_FUNCTION_BLOCK {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing variables in function block declaration: %s [%u:%u]",
                    pParse->File,
                    $function_block_type_name->Name,
                    @function_block_body.first_line,
                    @function_block_body.first_column);
            YYERROR;
        };

other_var_declarations: external_var_declarations
    | var_declarations 
    | retentive_var_declarations 
    | non_retentive_var_decls 
    | temp_var_decls
    /* | incompl_located_var_declarations */;

temp_var_decls: VAR_TEMP _var_init_decl END_VAR {
            $$ = token_list_cast($_var_init_decl, VAR_TEMP);
        };

non_retentive_var_decls: VAR NON_RETAIN _var_init_decl END_VAR {
            TOKEN *pToken;

            token_list_reset($_var_init_decl);
            while((pToken = token_list_iterate($_var_init_decl)) != NULL) {
                pToken->Value.Flags |= FLAG_NON_RETAIN;
            }
            $$ = token_list_cast($_var_init_decl, VAR);
        };

function_block_body: instruction_list
    /* | statement_list {
        } */;

_fb_var_declarations: io_var_declarations {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $io_var_declarations);
            $$ = pList;
        }
    | other_var_declarations {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $other_var_declarations);
            $$ = pList;
        }
    | _fb_var_declarations io_var_declarations {
            token_list_insert($1, $io_var_declarations);
            $$ = $1;
        }
    | _fb_var_declarations other_var_declarations {
            token_list_insert($1, $other_var_declarations);
            $$ = $1;
        };


/* B.1.5.3 Programs */

/*  program_type_name :: = identifier

    program_declaration ::=
        'PROGRAM' program_type_name
        { io_var_declarations | other_var_declarations
            | located_var_declarations | program_access_decls }
        function_block_body
        'END_PROGRAM'

    program_access_decls ::=
        'VAR_ACCESS' program_access_decl ';'
            {program_access_decl ';' }
        'END_VAR'

    program_access_decl ::= access_name ':' symbolic_variable ':'
        non_generic_type_name [direction] */

program_type_name: _program_type_name {
            PARSE *pParse;
            LEXER_TOKEN sToken;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                sToken.Text = parse_scope(pParse, $_program_type_name->Name);
                if(tree_search(&pParse->Identifiers, &sToken) != NULL) {
                    log_error("%s: Duplicate program type declaration: %s [%u:%u]",
                            pParse->File,
                            $_program_type_name->Name,
                            $_program_type_name->Line,
                            $_program_type_name->Column);
                    YYERROR;
                }
            }
            $$ = $_program_type_name;
        }
    | identifier {
            PARSE *pParse;
            LEXER_TOKEN *pToken;

            for(pParse = &Context->Parse;;) {
                if((pToken = lexer_new(_program_type_name, $identifier->Name)) != NULL) {
                    if(tree_insert(&pParse->Identifiers, pToken) == 0) 
                        break;
                    lexer_destroy(pToken);
                }

                log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                YYABORT;
            }
            $$ = $identifier;
        };

program_declaration: 
    PROGRAM program_type_name { 
            PARSE *pParse;

            pParse = &Context->Parse;
            pParse->POU = $program_type_name; 
        }
        function_block_body
        END_PROGRAM {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = token_list_new(PROGRAM, @PROGRAM.first_line, @PROGRAM.first_column, $program_type_name->Name);
            token_destroy($program_type_name);
            token_list_insert(pList, $function_block_body);

            pParse->POU = NULL;
            $$ = pList;
        }
    | PROGRAM program_type_name { 
            PARSE *pParse;

            pParse = &Context->Parse;
            pParse->POU = $program_type_name; 
        }
        _program_var_access_decls
        function_block_body
        END_PROGRAM {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = token_list_new(PROGRAM, @PROGRAM.first_line, @PROGRAM.first_column, $program_type_name->Name);
            token_destroy($program_type_name);
            token_list_insert(pList, $_program_var_access_decls, $function_block_body);

            pParse->POU = NULL;
            $$ = pList;
        };

program_access_decls: VAR_ACCESS _program_access_decls END_VAR {
            $$ = $_program_access_decls;
        };

program_access_decl: identifier ':' _variable_name ':' non_generic_type_name direction {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($_variable_name->Value.Type != $non_generic_type_name->Value.Type) {
                log_warn("%s: Mismatch between variable and program access declaration type [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
            }
            $identifier->Value.Type = TYPE_VARIABLE;
            $identifier->Value.Meta = strdup($_variable_name->Name);
            if($direction->Id == READ_ONLY)
                $identifier->Value.Flags |= FLAG_READ_ONLY;
            token_destroy($_variable_name, $non_generic_type_name);
            $$ = $identifier;
        }
    | identifier ':' _variable_name ':' non_generic_type_name {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($_variable_name->Value.Type != $non_generic_type_name->Value.Type) {
                log_warn("%s: Mismatch between variable and program access declaration type [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
            }
            $identifier->Value.Type = TYPE_VARIABLE;
            $identifier->Value.Meta = strdup($_variable_name->Name);
            token_destroy($_variable_name, $non_generic_type_name);
            $$ = $identifier;
        };

_program_access_decls: program_access_decl ';' {
            TOKEN_LIST *pList;

            pList = token_list_new(VAR_ACCESS, @program_access_decl.first_line, @program_access_decl.first_column);
            token_list_insert(pList, $program_access_decl);
            $$ = pList;
        }
    | _program_access_decls program_access_decl ';' {
            token_list_insert($1, $program_access_decl);
            $$ = $1;
        };

_program_var_access_decls: io_var_declarations {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $io_var_declarations);
            $$ = pList;
        }
    | other_var_declarations {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $other_var_declarations);
            $$ = pList;
        }
    | located_var_declarations {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $located_var_declarations);
            $$ = pList;
        }
    | program_access_decls {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $program_access_decls);
            $$ = pList;
        }
    | _program_var_access_decls io_var_declarations {
            token_list_insert($1, $io_var_declarations);
            $$ = $1;
        } 
    | _program_var_access_decls other_var_declarations {
            token_list_insert($1, $other_var_declarations);
            $$ = $1;
        }
    | _program_var_access_decls located_var_declarations {
            token_list_insert($1, $located_var_declarations);
            $$ = $1;
        } 
    | _program_var_access_decls program_access_decls {
            token_list_insert( $1, $program_access_decls);
            $$ = $1;
        };


/* B.1.6 Sequential function chart elements */

/* B.1.7 Configuration elements */

/*  configuration_name ::= identifier

    resource_type_name ::= identifier

    configuration_declaration ::=
        'CONFIGURATION' configuration_name
            [global_var_declarations]
            (single_resource_declaration
                | (resource_declaration {resource_declaration}))
            [access_declarations]
            [instance_specific_initializations]
        'END_CONFIGURATION'
        
    resource_declaration ::=
        'RESOURCE' resource_name 'ON' resource_type_name
            [global_var_declarations]
            single_resource_declaration
        'END_RESOURCE'
        
    single_resource_declaration ::=
        {task_configuration ';'}
        program_configuration ';'
        {program_configuration ';'}

    resource_name ::= identifier

    access_declarations ::=
        'VAR_ACCESS'
        access_declaration ';'
        {access_declaration ';'}
    'END_VAR'
    
    access_declaration ::= access_name ':' access_path ':'
        non_generic_type_name [direction]
        
    access_path ::= [resource_name '.'] direct_variable
        | [resource_name '.'] [program_name '.']
            {fb_name'.'} symbolic_variable
            
    global_var_reference ::=
        [resource_name '.'] global_var_name ['.' structure_element_name]
        
    access_name ::= identifier

    program_output_reference ::= program_name '.' symbolic_variable
    
    program_name ::= identifier

    direction ::= 'READ_WRITE' | 'READ_ONLY'

    task_configuration ::= 'TASK' task_name task_initialization

    task_name := identifier

    task_initialization ::=
        '(' ['SINGLE' ':=' data_source ',']
            ['INTERVAL' ':=' data_source ',']
            'PRIORITY' ':=' integer ')'
            
    data_source ::= constant | global_var_reference
        | program_output_reference | direct_variable
        
    program_configuration ::=
        'PROGRAM' [RETAIN | NON_RETAIN]
        program_name ['WITH' task_name] ':' program_type_name
        ['(' prog_conf_elements ')']
        
    prog_conf_elements ::= prog_conf_element {',' prog_conf_element}

    prog_conf_element ::= fb_task | prog_cnxn

    fb_task ::= fb_name 'WITH' task_name

    prog_cnxn ::= symbolic_variable ':=' prog_data_source
        | symbolic_variable '=>' data_sink
        
    prog_data_source ::=
        constant | enumerated_value | global_var_reference | direct_variable
        
    data_sink ::= global_var_reference | direct_variable
    
    instance_specific_initializations ::=
        'VAR_CONFIG'
        instance_specific_init ';'
        {instance_specific_init ';'}
        'END_VAR'
        
    instance_specific_init ::=
        resource_name '.' program_name '.' {fb_name '.'}
        ((variable_name [location] ':' located_var_spec_init) |
        (fb_name ':' function_block_type_name ':='
        structure_initialization)) */

configuration_name: identifier;

configuration_declaration: 
    CONFIGURATION configuration_name { 
            PARSE *pParse;

            pParse = &Context->Parse;
            pParse->Configuration = $configuration_name; 
        }
        _global_var_declarations
        _resource_declaration
        /* access_declarations */
        /* instance_specific_initializations */
        END_CONFIGURATION {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = token_list_new(CONFIGURATION, @CONFIGURATION.first_line, @CONFIGURATION.first_column, $configuration_name->Name);

            if($_global_var_declarations->List.Size > 0)
                token_list_insert(pList, $_global_var_declarations);
            else
                token_destroy($_global_var_declarations);

            switch($_resource_declaration->Token.Id) {
                case RESOURCE:  /* single_resource_declaration */
                    token_list_insert(pList, $_resource_declaration);
                    break;

                default:        /* resource_declaration {resource_declaration} */
                    token_list_merge(pList, $_resource_declaration);
                    token_destroy($_resource_declaration);
                    break;
            }
            token_destroy($configuration_name);
            pParse->Configuration = NULL;
            $$ = pList;
        };

resource_declaration: 
    RESOURCE resource_name ON identifier { 
            PARSE *pParse;

            pParse = &Context->Parse;
            pParse->Resource = $resource_name; 
        }
        _global_var_declarations
        single_resource_declaration
        END_RESOURCE {
            PARSE *pParse;
            TOKEN_LIST *pList;

            //  TODO: Handle underlying resource ($identifier)
            pParse = &Context->Parse;
            pList = token_list_new(RESOURCE, @RESOURCE.first_line, @RESOURCE.first_column, $resource_name->Name);

            if($_global_var_declarations->List.Size > 0) 
                token_list_insert(pList, $_global_var_declarations);
            else
                token_destroy($_global_var_declarations);

            token_list_merge(pList, $single_resource_declaration);
            token_destroy($resource_name, $single_resource_declaration, $identifier);
            pParse->Resource = NULL;
            $$ = pList;
        };

single_resource_declaration: _task_configuration _program_configuration {
            TOKEN_LIST *pList;

            pList = token_list_new(RESOURCE, @1.first_line, @1.first_column, "__Single");
            token_list_merge(pList, $_task_configuration, $_program_configuration);
            token_destroy($_task_configuration, $_program_configuration);
            $$ = pList;
        };

resource_name: _resource_name {
            PARSE *pParse;
            LEXER_TOKEN sToken;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                sToken.Text = parse_scope(pParse, $_resource_name->Name);
                if(tree_search(&pParse->Identifiers, &sToken) != NULL) {
                    log_error("%s: Duplicate resource declaration: %s [%u:%u]",
                            pParse->File,
                            $_resource_name->Name,
                            $_resource_name->Line,
                            $_resource_name->Column);
                    YYERROR;
                }
            }
            $$ = $_resource_name;
         }
    | identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(parse_register_scope(pParse, _resource_name, $identifier->Name) != 0)
                YYABORT;
            $$ = $identifier;
        };

/* access_declarations: */
/* access_declaration: */
/* access_path: */

direction: READ_ONLY
    | READ_WRITE;

task_configuration: TASK task_name task_initialization ';' {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_cast($task_initialization, TASK, @TASK.first_line, @TASK.first_column);
                pList->Token.Name = strdup($task_name->Name);
            }
            token_destroy($task_name);
            $$ = pList;
        };

task_name: _task_name {
            PARSE *pParse;
            LEXER_TOKEN sToken;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                sToken.Text = parse_scope(pParse, $_task_name->Name);
                if(tree_search(&pParse->Identifiers, &sToken) != NULL) {
                    log_error("%s: Duplicate task declaration: %s [%u:%u]",
                            pParse->File,
                            $_task_name->Name,
                            $_task_name->Line,
                            $_task_name->Column);
                    YYERROR;
                }
            }
            $$ = $_task_name;
         }
    | identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                if(parse_register_scope(pParse, _task_name, $identifier->Name) != 0)
                    YYABORT;
            }
            $$ = $identifier;
        };

task_initialization: 
    '(' _task_initialization_single 
        _task_initialization_interval 
        _task_initialization_limit
        PRIORITY _assign integer ')' {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_new(TASK, @1.first_line, @1.first_column);
                if($_task_initialization_single)
                    token_list_insert(pList, $_task_initialization_single);
                if($_task_initialization_interval)
                    token_list_insert(pList, $_task_initialization_interval);
                if($_task_initialization_limit)
                    token_list_insert(pList, $_task_initialization_limit);

                token_list_insert(pList, token_cast($integer, PRIORITY, @PRIORITY.first_line, @PRIORITY.first_column));
            }
            else
                token_destroy($_task_initialization_single, $_task_initialization_interval, $_task_initialization_limit, $integer);

            $$ = pList;
        };

program_name: _program_name {
            PARSE *pParse;
            LEXER_TOKEN sToken;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                sToken.Text = parse_scope(pParse, $_program_name->Name);
                if(tree_search(&pParse->Identifiers, &sToken) != NULL) {
                    log_error("%s: Duplicate program declaration: %s [%u:%u]",
                            pParse->File,
                            $_program_name->Name,
                            $_program_name->Line,
                            $_program_name->Column);
                    YYERROR;
                }
            }
            $$ = $_program_name;
        }
    | identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                if(parse_register_scope(pParse, _program_name, $identifier->Name) != 0)
                    YYABORT;
            }
            $$ = $identifier;
        };

data_source: constant 
    | global_var_name {
            $global_var_name->Value.Type = TYPE_VARIABLE;
            $$ = $global_var_name;
        } /*
    | program_output_reference
    | direct_variable */;

program_configuration: PROGRAM _program_configuration_retention program_name 
        _program_configuration_task ':' _program_type_name ';' {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_new(PROGRAM, @PROGRAM.first_line, @PROGRAM.first_column, $program_name->Name);
                value_assign(&pList->Token.Value, _TYPE_PROGRAM, $_program_type_name->Name);
                
                if($_program_configuration_retention) {
                    switch($_program_configuration_retention->Id) {
                        case NON_RETAIN:
                            pList->Token.Value.Flags |= FLAG_NON_RETAIN;
                            break;

                        case RETAIN:
                            pList->Token.Value.Flags |= FLAG_RETAIN;
                            break;
                            
                        default:
                            break;
                    }
                }            
                if($_program_configuration_task)
                    token_list_insert(pList, $_program_configuration_task);
            }
            token_destroy($program_name, $_program_type_name);
            $$ = pList;
        }
    | PROGRAM _program_configuration_retention program_name 
        _program_configuration_task ':' identifier ';' {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown program type in configuration program declaration [%u:%u]",
                        pParse->File,
                        @5.first_line,
                        @5.first_column);
                token_destroy($_program_configuration_retention, $program_name, $_program_configuration_task, $identifier);
                YYERROR;
            }
        };

_program_configuration: program_configuration {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $program_configuration);
            $$ = pList;
        }
    | _program_configuration program_configuration {
            token_list_insert($1, $program_configuration);
            $$ = $1;
        };

_program_configuration_retention: %empty { 
            $$ = NULL; 
        }
    | NON_RETAIN {
            $$ = token_new(NON_RETAIN, @NON_RETAIN.first_line, @NON_RETAIN.first_column);
        }
    | RETAIN {
            $$ = token_new(RETAIN, @RETAIN.first_line, @RETAIN.first_column);
        };

_program_configuration_task: %empty {
            $$ = NULL;
        }
    | WITH _task_name {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;
            if(!pParse->Preparse)
                pToken = token_cast($_task_name, TASK);
            else
                token_destroy($_task_name);

            $$ = pToken;
        }
    | WITH identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown task name in program configuration [%u:%u]",
                        pParse->File,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier);
            $$ = NULL;
        };

_resource_declaration: single_resource_declaration
    | resource_declaration {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $resource_declaration);
            $$ = pList;
        }
    | _resource_declaration resource_declaration {
            PARSE *pParse;

            pParse = &Context->Parse;
            if($1->Token.Id == RESOURCE) {
                log_error("%s: Cannot combine single and multiple resource declarations [%u:%u]",
                        pParse->File,
                        @1.first_line,
                        @1.first_column);
                YYERROR;
            }
            else 
                token_list_insert($1, $resource_declaration);

            $$ = $1;
        };

_task_configuration: task_configuration {
            TOKEN_LIST *pList;

            pList = token_list_new(0);
            token_list_insert(pList, $task_configuration);
            $$ = pList;
        }
    | _task_configuration task_configuration {
            token_list_insert($1, $task_configuration);
            $$ = $1;
        };

_task_initialization_single: %empty {
            $$ = NULL; 
        }
    | SINGLE _assign data_source ',' {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                if($data_source->Value.Type != TYPE_BOOL) {
                    log_error("%s: Invalid data source for single parameter in task initialization [%u:%u]",
                            pParse->File,
                            @data_source.first_line,
                            @data_source.first_column);
                    YYERROR;
                }
                pToken = token_cast($data_source, SINGLE, @SINGLE.first_line, @SINGLE.first_column);
            }
            else
                token_destroy($data_source);

            $$ = pToken;
        }
    | SINGLE data_source ',' {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing assignment operator for single parameter in task initialization [%u:%u]",
                    pParse->File,
                    @data_source.first_line,
                    @data_source.first_column);
            YYERROR;
        }
    | SINGLE _assign data_source {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing comma after single parameter in task initialization [%u:%u]",
                    pParse->File,
                    @data_source.last_line,
                    @data_source.last_column);
            YYERROR;
        };

_task_initialization_interval: %empty { 
            $$ = NULL; 
        }
    | INTERVAL _assign data_source ',' {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                switch($data_source->Value.Type) {
                    case TYPE_TIME:
                    case TYPE_VARIABLE:
                        break;

                    default:
                        log_error("%s: Invalid data source for interval parameter in task initialization [%u:%u]",
                                pParse->File,
                                @data_source.first_line,
                                @data_source.first_column);
                        YYERROR;
                }
                pToken = token_cast($data_source, INTERVAL, @INTERVAL.first_line, @INTERVAL.first_column);
                cast_time(&pToken->Value);
            }
            else
                token_destroy($data_source);

            $$ = pToken;
        }
    | INTERVAL data_source ',' {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing assignment operator for interval parameter in task initialization [%u:%u]",
                    pParse->File,
                    @2.first_line,
                    @2.first_column);
            YYERROR;   
        }
    | INTERVAL _assign data_source {
            PARSE *pParse;

            pParse = &Context->Parse;
            log_error("%s: Missing comma after interval parameter in task initialization [%u:%u]",
                    pParse->File,
                    @3.last_line,
                    @3.last_column);
            YYERROR;
        };

_task_initialization_limit: %empty {
            $$ = NULL;
        };

/* B.2 Language IL (Instruction List) */

/* B.2.1 Instructions and operands */

/*  instruction_list ::= il_instruction {il_instruction}

    il_instruction ::= [label':'] [ il_simple_operation
        | il_expression
        | il_jump_operation
        | il_fb_call
        | il_formal_funct_call
        | il_return_operator ] EOL {EOL}

    label ::= identifier

    il_simple_operation ::= ( il_simple_operator [il_operand] )
        | ( function_name [il_operand_list] )

    il_expression ::= il_expr_operator '(' [il_operand] EOL {EOL}
            [simple_instr_list] ')'

    il_jump_operation ::= il_jump_operator label

    il_fb_call ::= il_call_operator fb_name ['('
            (EOL {EOL} [ il_param_list ]) | [ il_operand_list ] ')']

    il_formal_funct_call ::= function_name '(' EOL {EOL} [il_param_list] ')'

    il_operand ::= constant | variable | enumerated_value

    il_operand_list ::= il_operand {',' il_operand}

    simple_instr_list ::= il_simple_instruction {il_simple_instruction}

    il_simple_instruction ::=
            (il_simple_operation | il_expression | il_formal_funct_call)
            EOL {EOL}

    il_param_list ::= {il_param_instruction} il_param_last_instruction

    il_param_instruction ::= (il_param_assignment | il_param_out_assignment)
            ',' EOL {EOL}

    il_param_last_instruction ::=
            ( il_param_assignment | il_param_out_assignment ) EOL {EOL}

    il_param_assignment ::= il_assign_operator ( il_operand | ( '(' EOL {EOL}
            simple_instr_list ')' ) )

    il_param_out_assignment ::= il_assign_out_operator variable */

instruction_list: il_instruction {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_new(0);
                token_list_insert(pList, $il_instruction);
            }
            /* else 
                token_destroy($il_instruction); */

            $$ = pList;
        }
    | instruction_list il_instruction {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse)
                token_list_insert($1, $il_instruction);
            /* else
                token_destroy($il_instruction); */

            $$ = $1;
        };

il_instruction: _label ':' _il_instruction EOL {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            pToken = NULL;

            if(!pParse->Preparse) {
                $_il_instruction->Name = strdup($_label->Name);
                token_destroy($_label);
                pToken = $_il_instruction;
            }
            else
                token_destroy($_label, $_il_instruction);

            $$ = pToken;
        }
    | identifier ':' _il_instruction EOL {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse)
                YYABORT;
            if(parse_register_scope(pParse, _label, $identifier->Name) != 0) 
                YYABORT;
            token_destroy($identifier);
            $$ = $_il_instruction;
        }
    | _il_instruction EOL;

il_simple_operation: il_simple_operator il_operand {
            PARSE *pParse;
            SYMBOL *pSymbol;
            int nResult;

            pParse = &Context->Parse;
            switch($il_simple_operator->Id) {
                case R:
                case S:
                    nResult = 0;
                    if($il_operand->Value.Type != TYPE_VARIABLE) 
                        ++nResult;
                    else if(!pParse->Preparse) {
                        if((pSymbol = symbol_search(Context,
                                TOKEN_NAME(pParse->Configuration),
                                TOKEN_NAME(pParse->Resource),
                                TOKEN_NAME(pParse->POU),
                                $il_operand->Name)) == NULL) 
                            ++nResult;
                        if((pSymbol != NULL) &&
                                (pSymbol->Value.Type != TYPE_FUNCTION_BLOCK) &&
                                (pSymbol->Value.Type != TYPE_BOOL)) 
                            ++nResult;
                    }
                    if(nResult != 0) {
                        log_error("%s: Invalid operand to %s operator [%u:%u]",
                                pParse->File,
                                ($il_simple_operator->Id == R) ? "R" : "S",
                                @il_operand.first_line,
                                @il_operand.first_column);
                        YYERROR;
                    }
                    break;

                default:
                    break;
            }

            value_copy(&$il_simple_operator->Value, &$il_operand->Value);
            token_destroy($il_operand);
            $$ = $il_simple_operator;
        }
    | _il_expr_function il_operand_list {
            PARSE *pParse;
            TOKEN_LIST *pList;
            TOKEN *pToken;
            int nId;

            /*
                The handling of _il_expr_function tokens is challenging as these may be interpreted 
                either as operators or functions. The manner by which this is handled is by 
                examining the number of operands associated with the _il_expr_function - If 
                there is only one operand, the token is interpreted as an operator, otherwise 
                it is interpreted as a function call.
            */

            pToken = NULL;
            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                switch($il_operand_list->List.Size) {
                    case 1:
                        token_list_reset($il_operand_list);
                        if(((pToken = token_list_iterate($il_operand_list)) == NULL) ||
                                ((nId = yystrtoid($_il_expr_function->Token.Name)) < 0)) {
                            log_critical("Internal error [%s:%u]", __FILE__, __LINE__);
                            YYABORT;
                        }
                        pList = token_list_new(nId, @_il_expr_function.first_line, @_il_expr_function.first_column);
                        value_copy(&pList->Token.Value, &pToken->Value);
                        switch(nId) {
                            case DIV:
                                if(yyliteralzero((TOKEN *) pList)) {
                                    log_error("%s: Invalid divide by zero operation [%u:%u]",
                                            pParse->File,
                                            @il_operand_list.first_line,
                                            @il_operand_list.first_column);
                                    YYERROR;
                                }
                                break;
                                
                            case MOD:
                                if(yyliteralzero((TOKEN *) pList)) {
                                    log_error("%s: Invalid modulus by zero operation [%u:%u]",
                                            pParse->File,
                                            @il_operand_list.first_line,
                                            @il_operand_list.first_column);
                                    YYERROR;
                                }
                                break;

                            default:
                                break;
                        }
                        break;

                    default:
                        pList = token_list_new(CAL, @_il_expr_function.first_line, @_il_expr_function.first_column);
                        token_list_merge(pList, $il_operand_list);
                        value_assign(&pList->Token.Value, TYPE_FUNCTION, $_il_expr_function->Token.Name);
                        break;
                }
            }
            token_destroy($_il_expr_function, $il_operand_list);
            $$ = (TOKEN *) pList;
        }
    | il_simple_operator
    | _function_name il_operand_list {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pList = NULL;
            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pList = token_list_new(CAL, @_function_name.first_line, @_function_name.first_column);
                token_list_merge(pList, $il_operand_list);
                value_assign(&pList->Token.Value, TYPE_FUNCTION, $_function_name->Name);
            }
            token_destroy($_function_name, $il_operand_list);
            $$ = (TOKEN *) pList;
        }
    | _function_name {
            TOKEN_LIST *pList;

            pList = token_list_new(CAL, @_function_name.first_line, @_function_name.first_column);
            value_assign(&pList->Token.Value, TYPE_FUNCTION, $_function_name->Name);
            token_destroy($_function_name);
            $$ = (TOKEN *) pList;
        }
    | identifier il_operand_list {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown function or function block: %s [%u:%u]",
                        pParse->File,
                        $identifier->Name,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($il_operand_list, $identifier);
            $$ = NULL;
        }
    | identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown function or function block: %s [%u:%u]",
                        pParse->File,
                        $identifier->Name,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier);
            $$ = NULL;
        };

il_expression: il_expr_operator '(' il_operand EOL simple_instr_list ')' {
            PARSE *pParse;
            TOKEN *pToken;

            /*
                If an operand and simple instruction list is specified as the operand to an 
                expression operator, this is converted to a more complete list of operations 
                for the runtime. This is performed by associating the operand with a load 
                operator instruction and when this is converted into byte code, an operand
                added to the end of the instruction list to consolidate the current register 
                at the end of the instruction list into the previous (deferred) operation.
            */

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pToken = token_new(LD, @il_operand.first_line, @il_operand.first_column);
                value_copy(&pToken->Value, &$il_operand->Value);
                token_list_insert($il_expr_operator, pToken);
                token_list_merge($il_expr_operator, $simple_instr_list);
            }
            token_destroy($il_operand, $simple_instr_list);
            $$ = (TOKEN *) $il_expr_operator;
        }
    | il_expr_operator '(' il_operand EOL ')' {
            TOKEN *pToken;

            pToken = (TOKEN *) $il_expr_operator;
            value_copy(&pToken->Value, &$il_operand->Value);
            token_destroy($il_operand);
            $$ = pToken;
        }
    | il_expr_operator '(' EOL simple_instr_list ')' {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                token_list_merge($il_expr_operator, $simple_instr_list);
            }
            $$ = (TOKEN *) $il_expr_operator;
        }
    | _il_expr_function '(' il_operand EOL simple_instr_list ')' {
            PARSE *pParse;
            TOKEN *pToken;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pToken = token_new(LD, @il_operand.first_line, @il_operand.first_column);
                value_copy(&pToken->Value, &$il_operand->Value);
                token_list_insert($_il_expr_function, pToken);
                token_list_merge($_il_expr_function, $simple_instr_list);
            }
            token_destroy($il_operand, $simple_instr_list);
            $$ = (TOKEN *) $_il_expr_function;
        }
    | _il_expr_function '(' il_operand EOL ')' {
            TOKEN *pToken;

            pToken = (TOKEN *) $_il_expr_function;
            value_copy(&pToken->Value, &$il_operand->Value);
            token_destroy($il_operand);
            $$ = pToken;
        }
    | _il_expr_function '(' EOL simple_instr_list ')' {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) 
                token_list_merge($_il_expr_function, $simple_instr_list);
            $$ = (TOKEN *) $_il_expr_function;
        };

il_jump_operation: il_jump_operator _label {
            value_assign(&$il_jump_operator->Value, TYPE_LABEL, $_label->Name);
            token_destroy($_label);
            $$ = $il_jump_operator;
        }
    | il_jump_operator identifier {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown label in jump operation: %s [%u:%u]",
                        pParse->File,
                        $identifier->Name,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($il_jump_operator, $identifier);
            $$ = NULL;
        };

il_fb_call: il_call_operator _variable_name '(' EOL il_param_list ')' {
            TOKEN_LIST *pList;
            PARSE *pParse;

            pList = NULL;
            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pList = token_list_convert($il_call_operator);
                value_assign(&pList->Token.Value, TYPE_FUNCTION_BLOCK, $_variable_name->Name);
                token_list_merge(pList, $il_param_list);
                if(token_list_unique(pList) != pList->List.Size) {
                    log_error("%s: Duplicate parameters to function block: %s [%u:%u]",
                            pParse->File,
                            $_variable_name->Name,
                            @_variable_name.first_line,
                            @_variable_name.first_column);
                    YYERROR;
                }
            }
            token_destroy($_variable_name, $il_param_list);
            $$ = (TOKEN *) pList;
        }
    | il_call_operator _variable_name '(' il_operand_list ')' {
            TOKEN_LIST *pList;
            PARSE *pParse;

            pList = NULL;
            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pList = token_list_convert($il_call_operator);
                value_assign(&pList->Token.Value, TYPE_FUNCTION_BLOCK, $_variable_name->Name);
                token_list_merge(pList, $il_operand_list);
            }
            token_destroy($_variable_name, $il_operand_list);
            $$ = (TOKEN *) pList;
        }
    | il_call_operator _variable_name {
            TOKEN_LIST *pList;
            PARSE *pParse;

            pList = NULL;
            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pList = token_list_convert($il_call_operator);
                value_assign(&pList->Token.Value, TYPE_FUNCTION_BLOCK, $_variable_name->Name);
            }
            token_destroy($_variable_name);
            $$ = (TOKEN *) pList;
        };

il_formal_funct_call: _function_name '(' EOL il_param_list ')' {
            TOKEN_LIST *pList;
            PARSE *pParse;

            pList = NULL;
            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                pList = token_list_cast($il_param_list, CAL);
                value_assign(&pList->Token.Value, TYPE_FUNCTION, $_function_name->Name);
                if(token_list_unique(pList) != pList->List.Size) {
                    log_error("%s: Duplicate parameters to function: %s [%u:%u]",
                            pParse->File,
                            $_function_name->Name,
                            @_function_name.first_line,
                            @_function_name.first_column);
                    YYERROR;
                }
            }
            token_destroy($_function_name);
            $$ = (TOKEN *) pList;
        }
    | identifier '(' EOL il_param_list ')' {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                log_error("%s: Unknown function or function block: %s [%u:%u]",
                        pParse->File,
                        $identifier->Name,
                        @identifier.first_line,
                        @identifier.first_column);
                YYERROR;
            }
            token_destroy($identifier, $il_param_list);
            $$ = NULL;
        };

il_operand: _function_name
    | _variable_name {
            $_variable_name->Value.Type = TYPE_VARIABLE;
            $_variable_name->Value.Meta = strdup($_variable_name->Name);
            $$ = $_variable_name;
        }
    | _variable_name '.' _variable_name {
            char sName[SYMBOL_NAME_MAX];

            snprintf(sName, sizeof(sName), "%s.%s", $1->Name, $3->Name);
            //value_destroy(&$_variable_name->Value);
            $1->Value.Type = TYPE_VARIABLE;
            $1->Value.Meta = strdup(sName);
            token_destroy($3);
            $$ = $1;
        }
    | _variable_name '.' identifier {
            char sName[SYMBOL_NAME_MAX];

            snprintf(sName, sizeof(sName), "%s.%s", $_variable_name->Name, $identifier->Name);
            //value_destroy(&$_variable_name->Value);
            $_variable_name->Value.Type = TYPE_VARIABLE;
            $_variable_name->Value.Meta = strdup(sName);
            token_destroy($identifier);
            $$ = $_variable_name;
        }
    | enumerated_value 
    | constant;

il_operand_list: il_operand {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_new(0);
                token_list_insert(pList, $il_operand);
            }
            else
                token_destroy($il_operand);
            $$ = pList;
        }
    | il_operand_list ',' il_operand {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse)
                token_list_insert($1, $il_operand);
            else
                token_destroy($il_operand);
            $$ = $1;
        };

simple_instr_list: il_simple_instruction {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;

            if(!pParse->Preparse) {
                pList = token_list_new(0);
                token_list_insert(pList, $il_simple_instruction);
            }
            $$ = pList;
        }
    | simple_instr_list il_simple_instruction {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse)
                token_list_insert($1, $il_simple_instruction);
            $$ = $1;
        };

il_simple_instruction: il_simple_operation EOL
    | il_expression EOL
    | il_formal_funct_call EOL;

il_param_list: il_param_last_instruction {
            PARSE *pParse;
            TOKEN_LIST *pList;

            pParse = &Context->Parse;
            pList = NULL;
            if(!pParse->Preparse) {
                pList = token_list_new(0);
                token_list_insert(pList, $il_param_last_instruction);
            }
            else
                token_destroy($il_param_last_instruction);

            $$ = pList;
        }
    | _il_param_list il_param_last_instruction {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse) {
                token_list_insert($_il_param_list, $il_param_last_instruction);
            }
            else 
                token_destroy($il_param_last_instruction);

            $$ = $_il_param_list;
        };

il_param_instruction: il_param_assignment ',' EOL 
    | il_param_out_assignment ',' EOL;

il_param_last_instruction: il_param_assignment EOL
    | il_param_out_assignment EOL;

il_param_assignment: il_assign_operator '(' EOL simple_instr_list ')' {
            token_list_merge($il_assign_operator, $simple_instr_list);
            token_destroy($simple_instr_list);
            $$ = $il_assign_operator;
        }
    | il_assign_operator il_operand {
            TOKEN *pToken;

            pToken = (TOKEN *) $il_assign_operator;
            value_copy(&pToken->Value, &$il_operand->Value);
            pToken->Value.Type |= TYPE_INPUT;
            token_destroy($il_operand);
            $$ = (TOKEN_LIST *) pToken;
        };

il_param_out_assignment: il_assign_out_operator _variable_name {
            TOKEN *pToken;

            pToken = (TOKEN *) $il_assign_out_operator;
            pToken->Value.Type = (TYPE_VARIABLE | TYPE_OUTPUT);
            pToken->Value.Meta = strdup($_variable_name->Name);
            token_destroy($_variable_name);
            $$ = (TOKEN_LIST *) pToken;
        };

_il_instruction: il_simple_operation
    | il_expression
    | il_jump_operation
    | il_fb_call
    | il_formal_funct_call
    | il_return_operator;

_il_param_list: il_param_instruction {
            PARSE *pParse;
            TOKEN_LIST *pList;
            
            pParse = &Context->Parse;
            pList = NULL;
            if(!pParse->Preparse) {
                pList = token_list_new(0);
                token_list_insert(pList, $il_param_instruction);
            }
            else
                token_destroy($il_param_instruction);
            $$ = pList;
        }
    | _il_param_list il_param_instruction {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(!pParse->Preparse)
                token_list_insert($1, $il_param_instruction);
            else
                token_destroy($il_param_instruction);

            $$ = $1;
        };


/* B.2.2 Operators */

/*  il_simple_operator ::= 'LD' | 'LDN' | 'ST' | 'STN' | 'NOT' | 'S'
        | 'R' | 'S1' | 'R1' | 'CLK' | 'CU' | 'CD' | 'PV'
        | 'IN' | 'PT' | il_expr_operator

    il_expr_operator ::= 'AND' | '&' | 'OR' | 'XOR' | 'ANDN' | '&N' | 'ORN'
        | 'XORN' | 'ADD' | 'SUB' | 'MUL' | 'DIV' | 'MOD' | 'GT' | 'GE' | 'EQ' 
        | 'LT' | 'LE' | 'NE'

    il_assign_operator ::= variable_name ':='

    il_assign_out_operator ::= ['NOT'] variable_name '=>'

    il_call_operator ::= 'CAL' | 'CALC' | 'CALCN'

    il_return_operator ::= 'RET' | 'RETC' | 'RETCN'

    il_jump_operator ::= 'JMP' | 'JMPC' | 'JMPCN' */

il_simple_operator: NOP
    | LD
    | LDN
    | ST
    | STN
    | NOT
    | S
    | R
    | S1
    | R1
    | CLK
    | CU
    | CD
    | PV
    | IN
    | PT
    | il_expr_operator {
            $$ = (TOKEN *) $il_expr_operator;
        };

il_expr_operator: ANDN
    | ORN
    | XORN;

il_assign_operator: _variable_name _assign {
            $_variable_name->Value.Type |= TYPE_INPUT;
            $$ = token_list_convert($_variable_name);
        } 
    | identifier _assign {
            $identifier->Value.Type |= TYPE_INPUT;
            $$ = token_list_convert($identifier);
        };

il_assign_out_operator: NOT ENO _sendto {
            TOKEN_LIST *pList;

            $ENO->Value.Type |= (TYPE_OUTPUT | TYPE_NEGATED);
            pList = token_list_convert($ENO);
            pList->Token.Name = strdup("ENO");
            token_list_insert(pList, $NOT);
            $$ = pList;
        }
    | NOT _variable_name _sendto {
            TOKEN_LIST *pList;

            $_variable_name->Value.Type |= (TYPE_OUTPUT | TYPE_NEGATED);
            pList = token_list_convert($_variable_name);
            token_list_insert(pList, $NOT);
            $$ = pList;
        }
    | ENO _sendto {
            TOKEN_LIST *pList;

            $ENO->Value.Type |= TYPE_OUTPUT;
            pList = token_list_convert($ENO);
            pList->Token.Name = strdup("ENO");
            $$ = pList;
        }
    | _variable_name _sendto {
            $_variable_name->Value.Type |= TYPE_OUTPUT;
            $$ = token_list_convert($_variable_name);
        }; 

il_call_operator: CAL
    | CALC
    | CALCN;

il_return_operator: RET
    | RETC
    | RETCN;

il_jump_operator: JMP {
            PARSE *pParse;

            pParse = &Context->Parse;
            if(pParse->Preparse) {
                log_warn("%s: Unconditional jump operation may result in endless loop [%u:%u]",
                        pParse->File,
                        @JMP.first_line,
                        @JMP.first_column);
            }
            $$ = $JMP;
        }
    | JMPC
    | JMPCN;
    
_il_expr_function: ADD
    | SUB
    | MUL
    | DIV
    | MOD
    | AND
    | OR
    | XOR
    | GT
    | GE
    | EQ
    | LT
    | LE
    | NE;


/* B.3 Language ST (Structured Text) */

/* B.3.1 Expressions */

/* B.3.2 Statements */

/* B.3.2.1 Assignment statements */

/* B.3.2.2 Subprogram control statements */

/* B.3.2.3 Selection statements */

/* B.3.2.4 Iteration statements */


%%


_FUNCTION_BLOCK *
yyfunction_create(const char *Name, TOKEN_LIST *Parameters) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    TOKEN *pToken;
    TOKEN_LIST *pStack[3];
    VALUE_TYPE uType;
    size_t uSize;
    int nSize, nStack;

    assert(Name != NULL);
    assert(Parameters != NULL);
    if((pBlock = calloc(1, sizeof(_FUNCTION_BLOCK))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pBlock->Count = 0;
    pBlock->Fields = NULL;
    pBlock->Initialise = NULL;
    pBlock->Execute = runtime_function_block;
    pBlock->Destroy = NULL;

    if((pBlock->Name = strdup(Name)) == NULL)
        goto error;

    nSize = (sizeof(pStack) / sizeof(pStack[0]));
    pStack[0] = Parameters;
    token_list_reset(pStack[0]);
    for(nStack = 0; nStack >= 0; --nStack) {
        while((pToken = token_list_iterate(pStack[nStack])) != NULL) {
            switch(pToken->Id) {
                case VAR:           uType = 0; if(0) {
                case VAR_IN_OUT:    uType = TYPE_INPUT|TYPE_OUTPUT; } if(0) {
                case VAR_INPUT:     uType = TYPE_INPUT; } if(0) {
                case VAR_OUTPUT:    uType = TYPE_OUTPUT; }
                    assert(pToken->Type == TYPE_LIST);
                    assert(nStack < (nSize - 1));
                    if(nStack >= (nSize - 1))
                        goto error;
                    pStack[++nStack] = (TOKEN_LIST *) pToken;
                    token_list_reset(pStack[nStack]);
                    break;

                case identifier:
                case _variable_name:
                default:    //  What else?!
                    uSize = ((pBlock->Count + 1) * sizeof(FUNCTION_BLOCK_FIELD));
                    if((pBlock->Fields = realloc(pBlock->Fields, uSize)) == NULL)
                        goto error;
                    pField = &pBlock->Fields[pBlock->Count++];
                    if((pField->Name = strdup(pToken->Name)) == NULL)
                        goto error;
                    pField->Type = (pToken->Value.Type | uType);
                    break;
            }
        }
    }
    return pBlock;

error:
    yyfunction_destroy(pBlock);
    return NULL;
}


void 
yyfunction_destroy(void *Arg) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    int nIndex;

    if((pBlock = (_FUNCTION_BLOCK *) Arg) == NULL)
        return;
    if(pBlock->Fields) {
        for(nIndex = 0; nIndex < pBlock->Count; ++nIndex) {
            pField = &pBlock->Fields[nIndex];
            if(pField->Name)
                free((char *) pField->Name);
        }
        free(pBlock->Fields);
    }
    if(pBlock->Name)
        free((char *) pBlock->Name);
    free(pBlock);
}


int
yyliteralzero(TOKEN *Token) {
    switch(Token->Id) {
        case LREAL:             return (fabs(Token->Value.Value.Double) < DBL_EPSILON);
        case REAL:              /* break; */
        case real:              return (fabs(Token->Value.Value.Single) < FLT_EPSILON);
        case LINT:              /* break; */
        case integer:           return (Token->Value.Value.S64 == 0ll);
        case DINT:              return (Token->Value.Value.S32 == 0);
        case INT:               return (Token->Value.Value.S16 == 0);
        case SINT:              return (Token->Value.Value.S8 == 0);
        case ULINT:             return (Token->Value.Value.U64 == 0ull);
        case UDINT:             return (Token->Value.Value.U32 == 0ul);
        case USINT:             return (Token->Value.Value.U8 == 0u);
        case UINT:              return (Token->Value.Value.U16 == 0u);
        case LWORD:             return (Token->Value.Value.B64 == 0ull);
        case DWORD:             return (Token->Value.Value.B32 == 0ul);
        case WORD:              return (Token->Value.Value.B16 == 0u);
        case BYTE:              return (Token->Value.Value.B8 == 0u);
        default:
            break;
    }
    return 0;
}


void
yyerror(__attribute__((unused)) ECHIDNA *Context, __attribute__((unused)) const char *Str) {
}


int
yystrtoid(const char *Str) {
    const char *pStr;
    int nIndex;

    for(nIndex = 0; (pStr = yytname[nIndex]) != YY_NULLPTR; ++nIndex) {
        if(strcasecmp(pStr, Str) == 0)
            return yytoknum[nIndex];
    }
    return -1;
}


const char *
yytokenname(int Id) {
    return yytname[YYTRANSLATE(Id)];
}

