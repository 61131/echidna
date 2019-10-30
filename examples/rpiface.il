PROGRAM test
VAR inp, val: BYTE := 1; END_VAR
VAR res: BOOL; END_VAR

piface_read
ST inp
EQ 0
JMPC roll

LD inp
AND val
EQ val
JMPCN roll
piface_write inp        (* Mirror inputs if asserted *)
RET

roll: piface_write val  (* Otherwise roll outputs *)
rol val, 1
ST val

END_PROGRAM

CONFIGURATION config1
TASK task1 (INTERVAL := t#100ms, PRIORITY := 1);
PROGRAM program1 WITH task1: test;
END_CONFIGURATION

