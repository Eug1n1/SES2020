.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib libucrt.lib
	includelib kernel32.lib
	ExitProcess PROTO :DWORD

.stack 4096

.const
		lit0 byte 	'jasdhj', 0
		lit1 sdword 	8
		lit2 sdword 	1
		lit3 sdword 	5
		lit4 byte 	'1234567890', 0
		lit5 byte 	'complete', 0
		lit6 sdword 	10
		lit7 sdword 	20
		lit8 sdword 	2
		lit9 sdword 	0


.data
		z 	sdword 	0
		c 	dword 	?
		x 	sdword 	0
		y 	sdword 	0
		z 	sdword 	0
		g 	sdword 	0
		sa 	dword 	?
		sb 	dword 	?
		sc 	dword 	?
		ab 	sdword 	0
		vv 	sdword 	0

.code
functio PROC y:DWORD, x:DWORD
	push x
	push y
	pop z

	mov eax, z
	ret
functio ENDP

nct PROC b:DWORD, a:DWORD
	push offset lit0
	pop c

	mov eax, offset c
	ret
nct ENDP

main PROC
	push lit1
	pop g

	push lit2
	pop x

	push lit3
	pop y

	push offset lit4
	pop sa

	push offset lit4
	pop sb

	push x
	push y
	call functio
	push eax
	push functio
	pop z

	push offset sa
	push offset sb
	call nct
	push eax
	push offset nct
	pop sc

	push offset lit5
	call prints
	push lit6
	pop ab

	push lit7
	pop vv

	push ab
	push lit8
	pop ab

	push ab
	call printi
	push z
	call printi
	push sc
	call prints
push 0
nct ENDP

