;;
;; Print Hello World! 10 times with a loop in ASM
;; nasm -f elf64 helloLoop.asm
;; ld helloLoop.o
;;

global _start

section .text
_start:
	mov     rsi, 10				; The counter of the 10 loops

_loop:
	mov     ebx, 1				; Argument one: file descriptor, in this case stdout
	mov     ecx, str 			; Argument two: the address of the string
	mov     edx, 14 			; Argument three: the length of the string

	mov     eax, 4				; Syscall number, in this case the write(2) syscall:
	int     0x80					; Interrupt 0x80

	dec 	rsi							; decrease rsi
	cmp 	rsi,0						; compare rsi and 0
	jne	_loop							; jumping if TEMP (from cmp) is not equal

	mov     ebx, 0				; Arg one: the status
	mov     eax, 0				; Syscall number : exit()
	int     0x80					; call the kernel

section .data
	str:	     db 'Hello, world!',0xA,0
