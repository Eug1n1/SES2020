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
newline PROTO

.const
		lit0 sdword 	8
		lit1 sdword 	3
		lit2 sdword 	1
		lit3 sdword 	4
		lit4 sdword 	5
		lit5 sdword 	2
		lit6 byte 	'1234567890', 0
		lit7 byte 	'complete', 0
		lit8 sdword 	10
		lit9 sdword 	20
		lit10 sdword 	0


.data
		zfunctio 	sdword 	0
		cnnct 	dword 	?
		xmain 	sdword 	0
		ymain 	sdword 	0
		zmain 	sdword 	0
		gmain 	sdword 	0
		samain 	dword 	?
		sbmain 	dword 	?
		scmain 	dword 	?
		abmain 	sdword 	0
		vvmain 	sdword 	0

.code
functio0 PROC yfunctio:DWORD, xfunctio:DWORD
	push xfunctio
	push yfunctio
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop ebx
	mov zfunctio, ebx

	mov eax, zfunctio
	ret
functio0 ENDP

nct1 PROC bnct:DWORD, anct:DWORD
	push anct
	pop ebx
	mov cnnct, ebx

	mov eax,  cnnct
	ret
nct1 ENDP

main PROC
	push lit0
	push lit1
	call octat
	push eax
	pop ebx
	mov gmain, ebx

	push lit2
	push lit0
	push lit1
	call functio0
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push lit3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop ebx
	mov xmain, ebx

	push lit4
	push lit5
	call elevate
	push eax
	pop ebx
	mov ymain, ebx

	push offset lit6
	pop ebx
	mov samain, ebx

	push offset lit6
	pop ebx
	mov sbmain, ebx

	push xmain
	push ymain
	call functio0
	push eax
	pop ebx
	mov zmain, ebx

	push samain
	push sbmain
	call nct1
	push eax
	pop ebx
	mov scmain, ebx

	push offset lit7
	call prints
	push lit8
	pop ebx
	mov abmain, ebx

	push lit9
	pop ebx
	mov vvmain, ebx

twirl_start0:
	mov eax, abmain
	mov ebx, vvmain
	cmp eax, ebx
	jg twirl_end0
	call newline
	push abmain
	push lit5
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop ebx
	mov abmain, ebx

	push abmain
	call printi
	jmp twirl_start0
twirl_end0:
	call newline
	push zmain
	call printi
	call newline
	push scmain
	call prints
	push 0
	call ExitProcess
main ENDP
end main
