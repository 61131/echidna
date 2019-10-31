(* Output current time once per second *)

program test
var cycle: lint := 0; end_var
var clock: rtc; end_var

add cycle, 1
st cycle
mod 10
eq 0
retcn

cal clock
dbg clock.cdt

end_program

configuration config1
task task1 (interval := t#100ms, priority := 1);
program program1 with task1: test;
end_configuration

