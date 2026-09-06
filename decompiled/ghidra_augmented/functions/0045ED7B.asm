; Ghidra function 0045ED7B __clrfp
; body ranges: 0045ed7b-0045ed86
0045ed7b	51	PUSH ECX
0045ed7c	DD3C24	FNSTSW word ptr [ESP]
; ref	0045ed7c	Stack[-0x4]	DATA
0045ed7f	DBE2	FNCLEX
0045ed81	0FBF0424	MOVSX EAX,word ptr [ESP]
; ref	0045ed81	Stack[-0x4]	DATA
0045ed85	59	POP ECX
0045ed86	C3	RET
