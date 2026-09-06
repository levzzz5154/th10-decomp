; Ghidra function 0045ED70 __statfp
; body ranges: 0045ed70-0045ed7a
0045ed70	51	PUSH ECX
0045ed71	9BDD3C24	FSTSW word ptr [ESP]
; ref	0045ed71	Stack[-0x4]	DATA
0045ed75	0FBF0424	MOVSX EAX,word ptr [ESP]
; ref	0045ed75	Stack[-0x4]	DATA
0045ed79	59	POP ECX
0045ed7a	C3	RET
