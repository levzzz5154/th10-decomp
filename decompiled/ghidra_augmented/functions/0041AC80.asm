; Ghidra function 0041AC80 FUN_0041ac80
; body ranges: 0041ac80-0041ac8f
0041ac80	8B4C2404	MOV ECX,dword ptr [ESP + 0x4]
; ref	0041ac80	Stack[0x4]	READ
0041ac84	8B542408	MOV EDX,dword ptr [ESP + 0x8]
; ref	0041ac84	Stack[0x8]	READ
0041ac88	8908	MOV dword ptr [EAX],ECX
0041ac8a	895004	MOV dword ptr [EAX + 0x4],EDX
0041ac8d	C20800	RET 0x8
