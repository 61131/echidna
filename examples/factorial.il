FUNCTION fact : UDINT
VAR_INPUT inp: UDINT; END_VAR
VAR_OUTPUT out: UDINT; END_VAR
VAR local: UDINT; END_VAR

LD inp
GE 1
JMPC nonzero
LD 1
RET
nonzero: LD inp
SUB 1
ST local
fact local
MUL inp
ST out
RET

END_FUNCTION


PROGRAM myprogram
VAR cycle, result: UDINT := 0; END_VAR

fact cycle
ST result
dbg cycle, result

LD cycle
ADD 1
ST cycle
LE 10  (* Limit execution to 11 cycles *)
RETC
_exit

END_PROGRAM


CONFIGURATION config1
TASK task1 (INTERVAL := t#50ms, PRIORITY := 1);
PROGRAM program1 WITH task1: myprogram;
END_CONFIGURATION

