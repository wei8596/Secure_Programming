	SECTION .text		
        global _start		
_start:				

	jmp	callback	

dowork:
	pop	esi		

	xor	edx,edx		
	push	edx		
	push	esi		

	mov	ecx,esp		
	mov	ebx,esi		
	xor	eax,eax		
	mov	al,0xb		
	int	0x80		

	xor	ebx,ebx		
	xor	eax,eax		
	inc	eax		
	int	0x80		

callback:
	call	dowork		
	db "/usr/bin/cal",0
