global _start
str: db "Hello world!", 10

section .text
_start:

mov rdi,10
_loop:
mov rdx,13 ;; taille
mov rcx,str ;; str
mov rbx,1 ;; fd
mov rax,4
int 0x80
dec rdi
cmp rdi,0
jne _loop

mov rax,1
int 0x80
