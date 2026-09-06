; Ghidra function 0045EBBA __frnd
; body ranges: 0045ebba-0045ebca
0045ebba	51	PUSH ECX
0045ebbb	51	PUSH ECX
0045ebbc	DD44240C	FLD double ptr [ESP + 0xc]
; ref	0045ebbc	Stack[0x4]	READ
0045ebc0	D9FC	FRNDINT
0045ebc2	DD1C24	FSTP double ptr [ESP]
; ref	0045ebc2	Stack[-0x8]	DATA
0045ebc5	DD0424	FLD double ptr [ESP]
; ref	0045ebc5	Stack[-0x8]	DATA
0045ebc8	59	POP ECX
0045ebc9	59	POP ECX
0045ebca	C3	RET
