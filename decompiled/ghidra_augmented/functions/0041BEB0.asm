; Ghidra function 0041BEB0 FUN_0041beb0
; body ranges: 0041beb0-0041becd
0041beb0	51	PUSH ECX
0041beb1	890C24	MOV dword ptr [ESP],ECX
; ref	0041beb1	Stack[-0x4]	DATA
0041beb4	8B0424	MOV EAX,dword ptr [ESP]
; ref	0041beb4	Stack[-0x4]	DATA
0041beb7	D9442408	FLD float ptr [ESP + 0x8]
; ref	0041beb7	Stack[0x4]	READ
0041bebb	D9FB	FSINCOS
0041bebd	D84C240C	FMUL float ptr [ESP + 0xc]
; ref	0041bebd	Stack[0x8]	READ
0041bec1	D918	FSTP float ptr [EAX]
0041bec3	D84C240C	FMUL float ptr [ESP + 0xc]
; ref	0041bec3	Stack[0x8]	READ
0041bec7	D95804	FSTP float ptr [EAX + 0x4]
0041beca	59	POP ECX
0041becb	C20800	RET 0x8
