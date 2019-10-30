PROGRAM test
VAR val: BYTE := 1; END_VAR
VAR dir: BOOL := true; END_VAR

piface_write val

ld dir
jmpcn rshift
lshift: shl val, 1
st val
eq 128
r dir
ret

rshift: shr val, 1
st val
eq 1
s dir
ret

END_PROGRAM

CONFIGURATION config1
TASK task1 (INTERVAL := t#80ms, PRIORITY := 1);
PROGRAM program1 WITH task1: test;
END_CONFIGURATION

