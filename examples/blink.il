(* Incrementally toggling 0/1 output driven by ton/ton/f_trig/r_trig *)

program test
var inp: bool; end_var
var cycle: time := t#500ms; end_var
var t1, t2: ton; end_var
var redge: r_trig; end_var
var fedge: f_trig; end_var

ldn t2.q
st inp
cal t1(
    in := inp,
    pt := cycle
)
cal t2(
    in := t1.q,
    pt := cycle
)

cal redge(
    clk := t1.q
)
ld redge.q
jmpcn down
dbg 1   (* Print 1 *)
down: cal fedge(
    clk := t1.q
)
ld fedge.q
retcn
dbg 0   (* Print 0 *)

end_program

configuration config1
task task1 (interval := t#10ms, priority := 1);
program program1 with task1: test;
end_configuration

