in
pop ax
in
pop bx
in
pop cx
push bx
push bx
mul
push 4
push ax
push cx
mul
mul
pop dx
push 0
push dx
jb zero
push dx
sqrt
sub
pop dx

push ax
push 0
je azero
push bx
push 0
je bzero
push 0
push dx
je one
push dx
push 0
ja two
push dx
push 0
jb zero
azero:
push bx
push 0
je azerobzero
push -1
push cx
mul
push bx
div
out
jmp end
azerobzero:
push cx
push 0
je ABC
push 0
out
jmp end
ABC:
push 999
out
jmp end
bzero:
push 2
out
push -1
push cx
mul
push ax
div
sqrt
out
push -1
push cx
mul
push ax
div
sqrt
push -1
mul
out
jmp end
one:
push -1
push bx
mul
push 2
push ax
mul
div
push 1
out
out
jmp end
two:
push 2
out
push -1
push bx
mul
push dx
add
push 2
push ax
mul
div
out
push -1
push bx
mul
push dx
sub
push 2
push ax
mul
div
out
jmp end
zero:
push 0
out
end:
end