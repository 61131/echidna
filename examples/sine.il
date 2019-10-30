PROGRAM prog1
VAR cycle: UINT := 0; END_VAR
VAR bias: REAL := 0; END_VAR
VAR magnitude: REAL := 100; END_VAR
VAR samples: REAL := 200; END_VAR
VAR value: REAL; END_VAR

LD cycle
ADD 1
ST cycle
uint_to_real cycle
MUL 6.2831854 (* 2pi *)
DIV samples
ST value
sin value
MUL magnitude
ADD bias
ST value
dbg value

END_PROGRAM

CONFIGURATION config1
TASK task1 (INTERVAL := t#50ms, PRIORITY := 1);
PROGRAM program1 WITH task1: prog1;
END_CONFIGURATION

