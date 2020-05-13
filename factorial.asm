jmp begin
fact:
push bx
push ax
mul
pop bx
push ax
push 1
sub
pop ax
push ax
push 1
ja fact
ret
begin:
in
pop ax
push ax
push 0
push 1
pop bx
je answer
push 1
pop bx
call fact
answer:
push bx
out
end