global _start
str: db "Hello world!", 10
section .text
_start:
mov rdi, 10 ;;

_loop:
mov rbx,1 ;; arg 1 : file descriptor
mov rcx,str ;; arg 2 : string pointer
mov rdx,13 ;; arg 3 : string length

mov rax,4 ;; rax contain 4 = write syscall
int 0x80 ;; call kernel

dec rdi
cmp rdi, 0

jne _loop

mov rax, 1
int 0x80 ;; call kernel
