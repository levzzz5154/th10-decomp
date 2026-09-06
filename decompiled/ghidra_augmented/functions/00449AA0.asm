; Ghidra function 00449AA0 FUN_00449aa0
; body ranges: 00449aa0-00449ada
00449aa0	8B4804	MOV ECX,dword ptr [EAX + 0x4]
00449aa3	33D2	XOR EDX,EDX
00449aa5	895008	MOV dword ptr [EAX + 0x8],EDX
00449aa8	89500C	MOV dword ptr [EAX + 0xc],EDX
00449aab	895010	MOV dword ptr [EAX + 0x10],EDX
00449aae	8910	MOV dword ptr [EAX],EDX
00449ab0	83E1FE	AND ECX,0xfffffffe
00449ab3	894804	MOV dword ptr [EAX + 0x4],ECX
00449ab6	8D4824	LEA ECX,[EAX + 0x24]
00449ab9	894014	MOV dword ptr [EAX + 0x14],EAX
00449abc	895018	MOV dword ptr [EAX + 0x18],EDX
00449abf	89501C	MOV dword ptr [EAX + 0x1c],EDX
00449ac2	836104FE	AND dword ptr [ECX + 0x4],0xfffffffe
00449ac6	895108	MOV dword ptr [ECX + 0x8],EDX
00449ac9	89510C	MOV dword ptr [ECX + 0xc],EDX
00449acc	895110	MOV dword ptr [ECX + 0x10],EDX
00449acf	8911	MOV dword ptr [ECX],EDX
00449ad1	894914	MOV dword ptr [ECX + 0x14],ECX
00449ad4	895118	MOV dword ptr [ECX + 0x18],EDX
00449ad7	89511C	MOV dword ptr [ECX + 0x1c],EDX
00449ada	C3	RET
