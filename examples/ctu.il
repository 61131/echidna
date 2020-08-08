program test
var count: ctu; end_var
var maxval: sint := 10; end_var

cal count(
    cu := true,
    pv := maxval,
    r := count.q
)
dbg count.q

end_program


configuration config1

task task1 (interval := t#100ms, priority := 1);
program program1 with task1: test;

end_configuration
