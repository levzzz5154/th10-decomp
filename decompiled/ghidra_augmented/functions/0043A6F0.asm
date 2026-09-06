; Ghidra function 0043A6F0 FUN_0043a6f0
; body ranges: 0043a6f0-0043a6fd
0043a6f0	51	PUSH ECX
0043a6f1	882424	MOV byte ptr [ESP],AH
; ref	0043a6f1	Stack[-0x4]	DATA
0043a6f4	88442401	MOV byte ptr [ESP + 0x1],AL
; ref	0043a6f4	Stack[-0x3]	WRITE
0043a6f8	668B0424	MOV AX,word ptr [ESP]
; ref	0043a6f8	Stack[-0x4]	DATA
0043a6fc	59	POP ECX
0043a6fd	C3	RET
