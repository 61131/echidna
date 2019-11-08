function fact: udint
var_input inp: udint; end_var
var_output out: udint; end_var
var local: udint; end_var

ld inp
ge 1
jmpc nonzero
ld 1
ret
nonzero: ld inp
sub 1
st local
fact local
mul inp
st out
ret

end_function

program test
var cycle, result: udint := 0; end_var

fact cycle
st result
dbg cycle, result

add cycle, 1
st cycle
le 10  (* Limit execution to 11 cycles *)
retc
_exit

end_program

configuration config1
task task1 (interval := t#50ms, priority := 1);
program program1 with task1: test;
end_configuration

