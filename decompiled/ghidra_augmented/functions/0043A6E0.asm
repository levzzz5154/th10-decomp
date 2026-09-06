; Ghidra function 0043A6E0 FUN_0043a6e0
; body ranges: 0043a6e0-0043a6ea
0043a6e0	8B4C240C	MOV ECX,dword ptr [ESP + 0xc]
; ref	0043a6e0	Stack[0xc]	READ
0043a6e4	8B01	MOV EAX,dword ptr [ECX]
0043a6e6	FF10	CALL dword ptr [EAX]
0043a6e8	C21400	RET 0x14
