; Ghidra function 0045ED87 __ctrlfp
; body ranges: 0045ed87-0045edaa
0045ed87	55	PUSH EBP
0045ed88	8BEC	MOV EBP,ESP
0045ed8a	51	PUSH ECX
0045ed8b	9BD97DFC	FSTCW word ptr [EBP + -0x4]
; ref	0045ed8b	Stack[-0x8]	WRITE
0045ed8f	8B450C	MOV EAX,dword ptr [EBP + 0xc]
; ref	0045ed8f	Stack[0x8]	READ
0045ed92	8B4D08	MOV ECX,dword ptr [EBP + 0x8]
; ref	0045ed92	Stack[0x4]	READ
0045ed95	234D0C	AND ECX,dword ptr [EBP + 0xc]
; ref	0045ed95	Stack[0x8]	READ
0045ed98	F7D0	NOT EAX
0045ed9a	2345FC	AND EAX,dword ptr [EBP + -0x4]
; ref	0045ed9a	Stack[-0x8]	READ
0045ed9d	0BC1	OR EAX,ECX
0045ed9f	89450C	MOV dword ptr [EBP + 0xc],EAX
; ref	0045ed9f	Stack[0x8]	WRITE
0045eda2	D96D0C	FLDCW word ptr [EBP + 0xc]
; ref	0045eda2	Stack[0x8]	READ
0045eda5	0FBF45FC	MOVSX EAX,word ptr [EBP + -0x4]
; ref	0045eda5	Stack[-0x8]	READ
0045eda9	C9	LEAVE
0045edaa	C3	RET
