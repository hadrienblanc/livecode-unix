global _start

_data:
str:db "Hello World!", 10

_start:
mov rsi, 42

_loop:
mov rdx, 13 ;
mov rcx, str ; string
mov rbx, 1; fd

mov rax, 4 ;; call write 4
int 0x80 ;; kernel call

dec rsi
cmp rsi,0 ;; flag TEST
jne _loop

mov rax, 1 ;; exit
int 0x80
