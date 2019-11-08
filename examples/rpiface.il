program test
var inp, val: byte := 1; end_var
var res: bool; end_var

piface_read
st inp
eq 0
jmpc roll

ld inp
and val
eq val
jmpcn roll
piface_write inp        (* Mirror inputs if asserted *)
ret

roll: piface_write val  (* Otherwise roll outputs *)
rol val, 1
st val

end_program

configuration config1
task task1 (interval := t#100ms, priority := 1);
program program1 with task1: test;
end_configuration

