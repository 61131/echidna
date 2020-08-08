(* Output current time once per second *)

program test
var clock: rtc; end_var

cal clock
dbg clock.cdt

end_program

configuration config1
task task1 (interval := t#1s, priority := 1);
program program1 with task1: test;
end_configuration

