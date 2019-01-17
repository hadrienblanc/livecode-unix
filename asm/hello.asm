global main

	section .data
	str:	     db 'Hello, world!',0xA,0

section .text
_start:
	mov     edx, 14 	; Arg three: the length of the string
	mov     ecx, str 	; Arg two: the address of the string
	mov     ebx, 1		; Arg one: file descriptor, in this case stdout
	mov     eax, 4		; Syscall number, in this case the write(2) syscall:
	int     0x80			; Interrupt 0x80

  mov     ebx, 0         ; Arg one: the status
  mov     eax, 0         ; Syscall number:
  int     0x80 					 ; call the kernel
