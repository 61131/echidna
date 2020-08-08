(* 
    This is a non-functional instruction list application which is the subject 
    of further echidna virtual machine development.
*)

function_block toggle
var_input run: bool; end_var
var_input cycle: time; end_var
var_output q: bool; end_var

ld run
st q

end_function_block


program test
var blink: toggle; end_var
var count: uint := 0; end_var

cal blink(
    run := true,
    cycle := t#500ms
)
dbg blink.q

add count, 1
st count
eq 5
retcn
_exit

end_program


configuration config1

task task1 (interval := t#1s, priority := 1);
program program1 with task1: test;

end_configuration

