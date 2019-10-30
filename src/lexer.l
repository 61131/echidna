/* %option debug */

%option case-insensitive
%option never-interactive
%option noinput
%option noyy_top_state
%option noyywrap
%option stack
%option yylineno
%pointer

%s Body
%s Comment
%s Configuration
%s Declaration
%s Duration
%s IL
%s Operand

%{
#include <stdio.h>
#include <strings.h>

#include <grammar.h>
#include <lexer.h>
#include <parse.h>
#include <tree.h>

/*
    The following action is called for all tokens matched by the flex scanner. 
    This action is used to track the start and end position of the current 
    token within the current file.
*/

#define YY_USER_ACTION          { \
    yylloc.first_line = _yyrow;    \
    yylloc.first_column = _yycol;  \
    _lexer_position(yytext);       \
    yylloc.last_line = _yyrow;     \
    yylloc.last_column = _yycol;   \
}

static void _lexer_position(const char *pText);

static int _lexer_token(const char *pText);

static void _lexer_unput(int nCount);

static int _yystate = 0;

static int _yycol = 1;

static int _yyrow = 1;

static void * _yycontext = NULL;

static const char * const _yytext[] = {
        "CONFIGURATION",
        "FUNCTION",
        "FUNCTION_BLOCK",
        "PROGRAM",
        "TYPE",
        "NOP",
        "LD",
        "LDN",
        "ST",
        "STN",
        "NOT",
        "S",
        "R",
        "S1",
        "R1",
        "CLK",
        "CU",
        "CD",
        "PV",
        "IN",
        "PT",
        "AND",
        "OR",
        "XOR",
        "ANDN",
        "ORN",
        "XORN",
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "MOD",
        "GT",
        "GE",
        "EQ",
        "LT",
        "LE",
        "NE",
        "CAL",
        "CALC",
        "CALCN",
        "RET",
        "RETC",
        "RETCN",
        "JMP",
        "JMPC",
        "JMPCN",
        "SINT",
        "INT",
        "DINT",
        "LINT",
        "USINT",
        "UINT",
        "UDINT",
        "ULINT",
        "REAL",
        "LREAL",
        "BOOL",
        "BYTE",
        "WORD",
        "DWORD",
        "LWORD",
        "STRING",
        "TIME",
        "DATE",
        "TIME_OF_DAY",
        "TOD",
        "EN",
        "ENO",
        NULL
};

static const int _yytoken[] = {
        CONFIGURATION,
        FUNCTION,
        FUNCTION_BLOCK,
        PROGRAM,
        TYPE,
        NOP,
        LD,
        LDN,
        ST,
        STN,
        NOT,
        S,
        R,
        S1,
        R1,
        CLK,
        CU,
        CD,
        PV,
        IN,
        PT,
        AND,
        OR,
        XOR,
        ANDN,
        ORN,
        XORN,
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        GT,
        GE,
        EQ,
        LT,
        LE,
        NE,
        CAL,
        CALC,
        CALCN,
        RET,
        RETC,
        RETCN,
        JMP,
        JMPC,
        JMPCN,
        SINT,
        INT,
        DINT,
        LINT,
        USINT,
        UINT,
        UDINT,
        ULINT,
        REAL,
        LREAL,
        BOOL,
        BYTE,
        WORD,
        DWORD,
        LWORD,
        STRING,
        TIME,
        DATE,
        TOD,
        TOD,
        EN,
        ENO,
        0
};

%}

eol                             [\n\r]+
whitespace_il                   [ \r\t]*
whitespace                      [ \n\r\t]*

comment_open                    "(*"
comment_close                   "*)"


/* 
    B.1.1 Letters, digits and identifiers

    letter  ::=  'A' | 'B' | <...> | 'Z' | 'a' | 'b' | <...> | 'z' 
    digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' 
    octal_digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
    hex_digit ::= digit | 'A'|'B'|'C'|'D'|'E'|'F'
    identifier ::= (letter | ('_' (letter | digit))) {['_'] (letter | digit)}
*/

letter                          [A-Za-z]
digit                           [0-9]
octal_digit                     [0-7]
hex_digit                       {digit}|[A-Fa-f]
identifier                      ({letter}|(_({letter}|{digit})))((_?({letter}|{digit}))*)


/*
    B.1.2 Constants

    B.1.2.1 Numeric literals

    integer ::= digit {['_'] digit}
    binary_integer ::= '2#' bit {['_'] bit}
    bit ::= '1' | '0'
    octal_integer ::= '8#' octal_digit {['_'] octal_digit}
    hex_integer ::= '16#' hex_digit {['_'] hex_digit}
    real_literal ::= [ real_type_name '#' ]
            signed_integer '.' integer [exponent]
    exponent ::= ('E' | 'e') ['+'|'-'] integer
*/

integer                         {digit}((_?{digit})*)
binary_integer                  2#{bit}((_?{bit})*)
bit                             [0-1]
octal_integer                   8#{octal_digit}((_?{octal_digit})*)
hex_integer                     16#{hex_digit}((_?{hex_digit})*)
real                            ([+-]?){integer}\.{integer}{exponent}?
exponent                        [Ee]([+-]?){integer}


/*
    B.1.2.2 Character strings

    single_byte_character_string ::= "'" {single_byte_character_representation} "'"
    double_byte_character_string ::= '"' {double_byte_character_representation} '"'
    single_byte_character_representation ::= common_character_representation 
            | "$'" | '"' | '$' hex_digit hex_digit
    double_byte_character_representation ::= common_character_representation 
            | '$"' | "'"| '$' hex_digit hex_digit hex_digit hex_digit
    common_character_representation ::= 
            <any printable character except '$', '"' or "'"> 
            | '$$' | '$L' | '$N' | '$P' | '$R' | '$T' 
            | '$l' | '$n' | '$p' | '$r' | '$t' 
*/

single_byte_character_string            '({single_byte_character_representation}*)'
double_byte_character_string            \"({double_byte_character_representation}*)\"
single_byte_character_representation    {common_character_representation}|$'|\"|(${hex_digit}{hex_digit})
double_byte_character_representation    {common_character_representation}|$\"|'|(${hex_digit}{hex_digit}{hex_digit}{hex_digit})
common_character_representation         [\x20\x21\x23\x25\x26\x28-\x7e]|{escape_character}
escape_character                        $$|$L|$N|$P|$R|$T|$l|$n|$p|$r|$t


/*
    B.1.2.3.1 Duration

    duration ::= ('T' | 'TIME') '#' ['-'] interval
    interval ::= days | hours | minutes | seconds | milliseconds
    days ::= fixed_point ('d') | integer ('d') ['_'] hours
    fixed_point ::= integer [ '.' integer]
    hours ::= fixed_point ('h') | integer ('h') ['_'] minutes
    minutes ::= fixed_point ('m')  | integer ('m') ['_'] seconds
    seconds ::= fixed_point ('s') | integer ('s') ['_'] milliseconds
    milliseconds ::= fixed_point ('ms')
*/

duration                        ((T)|(TIME))#(-)?{interval}
interval                        {days}?{hours}?{minutes}?{seconds}?{milliseconds}?
days                            {integer}d(_?{hours})?
fixed_point                     {integer}\.{integer}
hours                           {integer}h(_?{minutes})?
minutes                         {integer}m(_?{seconds})?
seconds                         {integer}s(_?{milliseconds})?
milliseconds                    ({integer}ms)


/*
    B.1.2.3.2 Time of day and date

    time_of_day ::= ('TIME_OF_DAY' | 'TOD')  '#' daytime
    daytime ::= day_hour ':' day_minute ':' day_second
    day_hour ::= integer
    day_minute ::= integer
    day_second ::= fixed_point
    date ::= ('DATE' | 'D') '#' date_literal
    date_literal ::= year '-' month '-' day
    year ::= integer
    month ::= integer
    day ::= integer
    date_and_time ::= ('DATE_AND_TIME' | 'DT') '#' date_literal '-' daytime
*/

time_of_day                     ((TIME_OF_DAY)|(TOD))#{daytime}
daytime                         {day_hour}:{day_hour}:{day_second}
day_hour                        {integer}
day_minute                      {integer}
day_second                      {integer}
date                            ((DATE)|(D))#{date_literal}
date_literal                    {year}-{month}-{day}
year                            {integer}
month                           {integer}
day                             {integer}


/*
    B.1.4.1 Directly represented variables

    direct_variable ::= '%' location_prefix size_prefix integer {'.' integer}
    location_prefix ::= 'I' | 'Q' | 'M'
    size_prefix ::= NIL | 'X' | 'B' | 'W' | 'D' | 'L'
*/

direct_variable                 %{location_prefix}({size_prefix}?){integer}((.{integer})*)
location_prefix                 [IQM]
size_prefix                     [XBWDL]

%%

<Operand>{
{eol}                           {
    PARSE *pParse;

    pParse = (PARSE *) _yycontext;
    switch(pParse->State) {
        case 0: break;
        case 1:
            yy_pop_state();
        default:
            --pParse->State;
            break;
    }
    return EOL;
}

}

<IL,Operand>{
{eol}                           { return EOL; }
{whitespace_il}

}

<Body,Comment,Configuration,Declaration,Duration>{whitespace}

<INITIAL>{
CONFIGURATION                   {
    BEGIN(_yystate = Configuration);
    return CONFIGURATION;
}
FUNCTION                        |
FUNCTION_BLOCK                  |
PROGRAM                         |
TYPE                            {
    BEGIN(_yystate = Body);
    return _lexer_token(yytext);
}
.|\n

}

<Comment>{
{comment_close}                 yy_pop_state();
{comment_open}                  return yytext[0];
.
}

<Body,IL>{
END_FUNCTION                    BEGIN(INITIAL); return END_FUNCTION;
END_FUNCTION_BLOCK              BEGIN(INITIAL); return END_FUNCTION_BLOCK;
END_PROGRAM                     BEGIN(INITIAL); return END_PROGRAM;
END_TYPE                        BEGIN(INITIAL); return END_TYPE;
VAR{whitespace}                 |
VAR_INPUT{whitespace}           |
VAR_IN_OUT{whitespace}          |
VAR_OUTPUT{whitespace}          { _lexer_unput(0); yy_push_state(Declaration); }
}

{comment_open}                  { yy_push_state(Comment); }

<Configuration>{
END_CONFIGURATION               BEGIN(INITIAL); return END_CONFIGURATION;
VAR_ACCESS                      |
VAR_CONFIG                      |
VAR_GLOBAL                      { _lexer_unput(0); yy_push_state(Declaration); }

TASK                            return TASK;
SINGLE                          return SINGLE;
INTERVAL                        return INTERVAL;
PRIORITY                        return PRIORITY; 
PROGRAM                         return PROGRAM;
WITH                            return WITH;

:=                              return _assign;
=>                              return _sendto;

}

<Declaration>{
VAR_ACCESS{whitespace}          return VAR_ACCESS;
VAR_CONFIG{whitespace}          return VAR_CONFIG;
VAR_GLOBAL{whitespace}          return VAR_GLOBAL;
VAR_INPUT{whitespace}           return VAR_INPUT;
VAR_IN_OUT{whitespace}          return VAR_IN_OUT;
VAR_OUTPUT{whitespace}          return VAR_OUTPUT;
VAR{whitespace}                 return VAR;

AT                              return AT;
CONSTANT                        return CONSTANT;
NON_RETAIN                      return NON_RETAIN;
RETAIN                          return RETAIN;

R_EDGE                          return R_EDGE;
F_EDGE                          return F_EDGE;

END_VAR{whitespace}             { 

    /*
        The following code is a "hack" to appropriate set the scanner state where 
        the first instruction of a program organisation unit (POU) is a formal 
        function block call (and the scanner state has not been transitioned from 
        Body to IL as a result of the encountering of an instruction list operator). 
        This is important due to the significance that end-of-line characters within 
        the instruction list grammar.
    */

    yy_pop_state();
    if(_yystate == Body)
        BEGIN(IL);
    return END_VAR; }
}

<Duration>{

-?{fixed_point}                 {
    yylval.Token = token_new(fixed_point, yylloc.first_line, yylloc.first_column);
    value_strtoval(&yylval.Token->Value, TYPE_REAL, yytext);
    return yylval.Token->Id;
}
				
-?{integer}                     {
    yylval.Token = token_new(integer, yylloc.first_line, yylloc.first_column);
    value_strtoval(&yylval.Token->Value, TYPE_LINT, yytext);
    return yylval.Token->Id;
}

d                               return _duration_days;
h                               return _duration_hours;
m                               return _duration_minutes;
s                               return _duration_seconds;
ms                              return _duration_milliseconds;
_
.                               {
    yy_pop_state(); 
    return yytext[0]; 
}

}

<Body,Configuration,IL>{

    /* B.2.2 Operators */

NOP                             |
LD                              |
LDN                             |
ST                              |
STN                             |
S                               |
R                               |
S1                              |
R1                              |
CLK                             |
CU                              |
CD                              |
IN                              |
PV                              |
PT                              |
EN                              |
ENO                             |
CAL                             |
CALC                            |
CALCN                           |
RET                             |
RETC                            |
RETCN                           |
JMP                             |
JMPC                            |
JMPCN                           {
    PARSE *pParse;

    BEGIN(IL);
    pParse = (PARSE *) _yycontext;
    if(!pParse->Parameters) {
        pParse->State = 1;
        yylval.Token = token_new(_lexer_token(yytext), yylloc.first_line, yylloc.first_column);
        switch(yylval.Token->Id) {
            case CAL:
            case CALC:
            case CALCN:
                ++pParse->State;
                break;

            default:
                break;
        }
        yy_push_state(Operand);
    }
    else
        yylval.Token = token_new(identifier, yylloc.first_line, yylloc.first_column, yytext);

    return yylval.Token->Id;
}

AND                             |
OR                              |
XOR                             |
ANDN                            |
ORN                             |
XORN                            |
ADD                             |
SUB                             |
MUL                             |
DIV                             |
MOD                             |
GT                              |
GE                              |
EQ                              |
LT                              |
LE                              |
NE                              {
    PARSE *pParse;

    BEGIN(IL);
    pParse = (PARSE *) _yycontext;
    if(!pParse->Parameters) {
        pParse->State = 1;
        yylval.List = token_list_new(_lexer_token(yytext), yylloc.first_line, yylloc.first_column);
        yylval.List->Token.Name = strdup(yytext);
        yy_push_state(Operand);
    }
    else 
        yylval.Token = token_new(identifier, yylloc.first_line, yylloc.first_column, yytext);

    return yylval.List->Token.Id;
}

}


<Body,Configuration,Declaration,IL,Operand>{

T#                              |
TIME#                           {
    yy_push_state(Duration);
    return _t_sharp;
}

SINT                            |
INT                             |
DINT                            |
LINT                            |
USINT                           |
UINT                            |
UDINT                           |
ULINT                           |
REAL                            |
LREAL                           |
BOOL                            |
BYTE                            |
WORD                            |
DWORD                           |
LWORD                           |
STRING                          |
TIME                            |
DATE                            |
TIME_OF_DAY                     |
TOD                             {
        yylval.Token = token_new(_lexer_token(yytext), yylloc.first_line, yylloc.first_column);
        value_strtotype(&yylval.Token->Value, yytext);
        return yylval.Token->Id;
    }

ARRAY                           return ARRAY;
OF                              return OF;
STRUCT                          return STRUCT;
END_STRUCT                      return END_STRUCT;

:=                              {
    PARSE *pParse;

    pParse = (PARSE *) _yycontext;
    ++pParse->State;
    return _assign;
}
=>                              {
    PARSE *pParse;

    pParse = (PARSE *) _yycontext;
    ++pParse->State;
    return _sendto;
}
".."                            return _range;

    /*
        Note that while the typed boolean literals BOOL#TRUE and BOOL#FALSE are 
        provided as examples within Table 4 - Numeric literals, their specification 
        is _not_ included in the formal specification of language elements. While 
        this is likely an omission within the language specification, attempting to 
        include these within the language grammar as it presently stands introduces 
        a shift/reduce error - This could be addressed, but would likely introduce 
        further complexity to the grammar. As such, these literals are defined here 
        within the lexer, at the cost of flexibility in whitespace between literal 
        elements.
    */

BOOL#1                          |
BOOL#TRUE                       |
TRUE                            {
        yylval.Token = token_new(TRUE, yylloc.first_line, yylloc.first_column);
        value_assign(&yylval.Token->Value, TYPE_BOOL, 1);
        return yylval.Token->Id;
    }
BOOL#0                          |
BOOL#FALSE                      |
FALSE                           {
        yylval.Token = token_new(FALSE, yylloc.first_line, yylloc.first_column);
        value_assign(&yylval.Token->Value, TYPE_BOOL, 0);
        return yylval.Token->Id;
    }


{real}                          {
    yylval.Token = token_new(real, yylloc.first_line, yylloc.first_column);
    value_strtoval(&yylval.Token->Value, TYPE_LREAL, yytext);
    return yylval.Token->Id;
}

{binary_integer}                |
{octal_integer}                 |
{hex_integer}                   |
{integer}                       {
    yylval.Token = token_new(integer, yylloc.first_line, yylloc.first_column);
    value_strtoval(&yylval.Token->Value, TYPE_LINT, yytext);
    return yylval.Token->Id;
}

{identifier}                    { 
    PARSE *pParse;
    LEXER_TOKEN *pToken;
    int nId;

    /*
        The following code performs a search to see if the identifier encountered 
        has been previously identified as a configuration, function, function block, 
        program or type token. This is so as to provide specificity within the 
        grammar where these identifiers may be employed. 
    */

    pParse = (PARSE *) _yycontext;
    if((pToken = parse_search(pParse, yytext)) != NULL)
        nId = pToken->Id;
    else 
        nId = identifier;

    yylval.Token = token_new(nId, yylloc.first_line, yylloc.first_column, yytext); 
    return yylval.Token->Id;
}

}

.                               { return yytext[0]; }


%%

static void 
_lexer_position(const char *pText) {
    const char *pEnd, *pPtr;

    pPtr = pText;
    while((pEnd = strchr(pPtr, '\n')) != NULL) {
        pPtr = pEnd + 1;
        ++_yyrow;
        _yycol = 1;
    }
    _yycol += strlen(pPtr);
}


static int
_lexer_token(const char *pText) {
    int nIndex;

    for(nIndex = 0; _yytext[nIndex]; ++nIndex) {
        if(strcasecmp(pText, _yytext[nIndex]) == 0) 
            return _yytoken[nIndex];
    }
    log_error("Missing token mapping: %s [%s:%u]", pText, __FILE__, __LINE__);
    return 0;
}


static void 
_lexer_unput(int nCount) {
    char *yycopy;
    int nIndex;

    yycopy = strdup(yytext);
    for(nIndex = yyleng - 1; nIndex >= nCount; --nIndex) 
        unput(yycopy[nIndex]);
    free(yycopy);
}


void
lexer_destroy(LEXER_TOKEN *Token) {
    if(!Token)
        return;
    if(Token->Text)
        free((char *) Token->Text);
    free(Token);
}


LEXER_TOKEN *
lexer_new(int Id, const char *Str) {
    LEXER_TOKEN *pToken;

    if((pToken = (LEXER_TOKEN *) calloc(1, sizeof(*pToken))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pToken->Id = Id;
    pToken->Text = (const char *) strdup(Str);
    return pToken;
}


void
lexer_start( void *pContext ) {
    while(yy_start_stack_ptr > 0)
        yy_pop_state();

    _yystate = INITIAL;
    _yyrow = 1;
    _yycol = 1;
    _yycontext = pContext;
}


