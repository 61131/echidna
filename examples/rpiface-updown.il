program test
var val: byte := 1; end_var
var dir: bool := true; end_var

piface_write val

ld dir
jmpcn rshift

lshift: shl val, 1
st val
eq 128
r dir
ret

rshift: shr val, 1
st val
eq 1
s dir
ret

end_program

configuration config1
task task1 (interval := t#80ms, priority := 1);
program program1 with task1: test;
end_configuration

