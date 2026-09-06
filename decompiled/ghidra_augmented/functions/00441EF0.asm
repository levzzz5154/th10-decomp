; Ghidra function 00441EF0 SetAnimationPolarVector
; body ranges: 00441ef0-00441f0d
00441ef0	51	PUSH ECX
00441ef1	890C24	MOV dword ptr [ESP],ECX
; ref	00441ef1	Stack[-0x4]	DATA
00441ef4	8B0424	MOV EAX,dword ptr [ESP]
; ref	00441ef4	Stack[-0x4]	DATA
00441ef7	D9442408	FLD float ptr [ESP + 0x8]
; ref	00441ef7	Stack[0x4]	READ
00441efb	D9FB	FSINCOS
00441efd	D84C240C	FMUL float ptr [ESP + 0xc]
; ref	00441efd	Stack[0x8]	READ
00441f01	D918	FSTP float ptr [EAX]
00441f03	D84C240C	FMUL float ptr [ESP + 0xc]
; ref	00441f03	Stack[0x8]	READ
00441f07	D95804	FSTP float ptr [EAX + 0x4]
00441f0a	59	POP ECX
00441f0b	C20800	RET 0x8
