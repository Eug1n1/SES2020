.586
.model flat, stdcall
includelib libucrt.lib
includelib libucrt.lib
includelib SES2020StaticLib.lib
includelib kernel32.lib
ExitProcess PROTO :DWORD
.stack 4096

printi PROTO : DWORD
prints PROTO : DWORD
octat PROTO : DWORD, : DWORD
elevate PROTO : DWORD, : DWORD

.const
		lit0 sdword 	8
		lit1 sdword 	3
		lit2 sdword 	1
		lit3 sdword 	5
		lit4 sdword 	2
		lit5 byte 	'1234567890', 0
		lit6 byte 	'complete', 0
		lit7 sdword 	10
		lit8 sdword 	20
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
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop ebx
	mov z, ebx

	mov eax, z
	ret
functio ENDP

nct PROC b:DWORD, a:DWORD
	push offset a
	pop ebx
	mov c, ebx

	mov eax, offset c
	ret
nct ENDP

main PROC
	push lit0
	push lit1
	call octat
	push eax
	pop ebx
	mov g, ebx

	push lit2
	pop ebx
	mov x, ebx

	push lit3
	push lit4
	call elevate
	push eax
	pop ebx
	mov y, ebx

	push offset lit5
	pop ebx
	mov sa, ebx

	push offset lit5
	pop ebx
	mov sb, ebx

	push x
	push y
	call functio
	push eax
	pop ebx
	mov z, ebx

	push offset sa
	push offset sb
	call nct
	push eax
	pop ebx
	mov sc, ebx

	push offset lit6
	call prints
	push lit7
	pop ebx
	mov ab, ebx

	push lit8
	pop ebx
	mov vv, ebx

twirl_start0:
	cmp ab, vv
	jg twirl_end0
	push ab
	push lit4
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop ebx
	mov ab, ebx

	push ab
	call printi
	jmp twirl_start0
twirl_end0:
	push z
	call printi
	push sc
	call prints
	push 0
	call ExitProcess
	main ENDP
	end main
