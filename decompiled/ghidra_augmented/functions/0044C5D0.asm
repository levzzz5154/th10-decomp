; Ghidra function 0044C5D0 FUN_0044c5d0
; body ranges: 0044c5d0-0044c5ed
0044c5d0	51	PUSH ECX
0044c5d1	890C24	MOV dword ptr [ESP],ECX
; ref	0044c5d1	Stack[-0x4]	DATA
0044c5d4	8B0424	MOV EAX,dword ptr [ESP]
; ref	0044c5d4	Stack[-0x4]	DATA
0044c5d7	D9442408	FLD float ptr [ESP + 0x8]
; ref	0044c5d7	Stack[0x4]	READ
0044c5db	D9FB	FSINCOS
0044c5dd	D84C240C	FMUL float ptr [ESP + 0xc]
; ref	0044c5dd	Stack[0x8]	READ
0044c5e1	D918	FSTP float ptr [EAX]
0044c5e3	D84C240C	FMUL float ptr [ESP + 0xc]
; ref	0044c5e3	Stack[0x8]	READ
0044c5e7	D95804	FSTP float ptr [EAX + 0x4]
0044c5ea	59	POP ECX
0044c5eb	C20800	RET 0x8
