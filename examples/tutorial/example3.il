(* Toggle LED on Raspberry Pi 1 PiFace Digital I/O *)

function_block blink
var_input cycle: time; end_var
var_output q: bool; end_var
var t1, t2: ton; end_var

ldn t2.q
st q
cal t1(
    in := q,
    pt := cycle
)
cal t2(
    in := t1.q,
    pt := cycle
)

end_function_block

program tutorial
var output: byte := false; end_var
var fb: blink; end_var

cal fb(
    cycle := t#500ms
)

bool_to_byte fb.q
st output
dbg output (* piface_write output *)

end_program

configuration config1
task task1 (interval := t#50ms, priority := 1);
program program1 with task1: tutorial;
end_configuration

