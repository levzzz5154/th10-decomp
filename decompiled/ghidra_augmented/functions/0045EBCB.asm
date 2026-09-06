; Ghidra function 0045EBCB __set_exp
; body ranges: 0045ebcb-0045ebf4
0045ebcb	55	PUSH EBP
0045ebcc	8BEC	MOV EBP,ESP
0045ebce	51	PUSH ECX
0045ebcf	51	PUSH ECX
0045ebd0	8B4510	MOV EAX,dword ptr [EBP + 0x10]
; ref	0045ebd0	Stack[0xc]	READ
0045ebd3	DD4508	FLD double ptr [EBP + 0x8]
; ref	0045ebd3	Stack[0x4]	READ
0045ebd6	8B4D0E	MOV ECX,dword ptr [EBP + 0xe]
; ref	0045ebd6	Stack[0xa]	READ
0045ebd9	DD5DF8	FSTP double ptr [EBP + -0x8]
; ref	0045ebd9	Stack[-0xc]	WRITE
0045ebdc	05FE030000	ADD EAX,0x3fe
0045ebe1	C1E004	SHL EAX,0x4
0045ebe4	81E10F80FFFF	AND ECX,0xffff800f
0045ebea	0BC1	OR EAX,ECX
0045ebec	668945FE	MOV word ptr [EBP + -0x2],AX
; ref	0045ebec	Stack[-0x6]	WRITE
0045ebf0	DD45F8	FLD double ptr [EBP + -0x8]
; ref	0045ebf0	Stack[-0xc]	READ
0045ebf3	C9	LEAVE
0045ebf4	C3	RET
