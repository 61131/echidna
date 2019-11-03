(* Toggle LED on Raspberry Pi 1 PiFace Digital I/O *)

program tutorial
var output: byte := false; end_var

ld output
xor 1
st output
piface_write output

end_program

configuration config1
task task1 (interval := t#500ms, priority := 1);
program program1 with task1: tutorial;
end_configuration

