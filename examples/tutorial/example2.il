(* Toggle LED on Raspberry Pi 1 PiFace Digital I/O *)

program tutorial
var cycle: time := t#500ms; end_var
var q: bool; end_var
var output: byte := false; end_var
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
bool_to_byte t1.q
st output
piface_write output

end_program

configuration config1
task task1 (interval := t#50ms, priority := 1);
program program1 with task1: tutorial;
end_configuration

