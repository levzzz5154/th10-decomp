.globl _th10_00461003
_th10_00461003:
    ret  # c3
.globl _th10_00461004
_th10_00461004:
    {disp8} {load} mov cl, [esp+4]  # 8a4c2404
.globl _th10_00461008
_th10_00461008:
    {load} xor eax, eax  # 33c0
.globl _th10_0046100a
_th10_0046100a:
    test cl, 1  # f6c101
.globl _th10_0046100d
_th10_0046100d:
    {disp8} je _th10_00461012  # 7403
.globl _th10_0046100f
_th10_0046100f:
    push 16  # 6a10
.globl _th10_00461011
_th10_00461011:
    pop eax  # 58
.globl _th10_00461012
_th10_00461012:
    test cl, 4  # f6c104
.globl _th10_00461015
_th10_00461015:
    {disp8} je _th10_0046101a  # 7403
.globl _th10_00461017
_th10_00461017:
    or eax, 8  # 83c808
.globl _th10_0046101a
_th10_0046101a:
    test cl, 8  # f6c108
.globl _th10_0046101d
_th10_0046101d:
    {disp8} je _th10_00461022  # 7403
.globl _th10_0046101f
_th10_0046101f:
    or eax, 4  # 83c804
.globl _th10_00461022
_th10_00461022:
    test cl, 0x10  # f6c110
.globl _th10_00461025
_th10_00461025:
    {disp8} je _th10_0046102a  # 7403
.globl _th10_00461027
_th10_00461027:
    or eax, 2  # 83c802
.globl _th10_0046102a
_th10_0046102a:
    test cl, 0x20  # f6c120
.globl _th10_0046102d
_th10_0046102d:
    {disp8} je _th10_00461032  # 7403
.globl _th10_0046102f
_th10_0046102f:
    or eax, 1  # 83c801
.globl _th10_00461032
_th10_00461032:
    test cl, 2  # f6c102
.globl _th10_00461035
_th10_00461035:
    {disp8} je _th10_0046103c  # 7405
.globl _th10_00461037
_th10_00461037:
    {noimm8s} or eax, 0x80000  # 0d00000800
.globl _th10_0046103c
_th10_0046103c:
    ret  # c3
.globl _th10_0046103d
_th10_0046103d:
    push ecx  # 51
.globl _th10_0046103e
_th10_0046103e:
    fwait
fnstsw [esp]  # 9bdd3c24
.globl _th10_00461042
_th10_00461042:
    push dword ptr [esp]  # ff3424
.globl _th10_00461045
_th10_00461045:
    {disp32} call _th10_00461004  # e8baffffff
.globl _th10_0046104a
_th10_0046104a:
    pop ecx  # 59
.globl _th10_0046104b
_th10_0046104b:
    pop ecx  # 59
.globl _th10_0046104c
_th10_0046104c:
    ret  # c3
.globl _th10_0046104d
_th10_0046104d:
    push ecx  # 51
.globl _th10_0046104e
_th10_0046104e:
    fnstsw [esp]  # dd3c24
.globl _th10_00461051
_th10_00461051:
    fnclex  # dbe2
.globl _th10_00461053
_th10_00461053:
    push dword ptr [esp]  # ff3424
.globl _th10_00461056
_th10_00461056:
    {disp32} call _th10_00461004  # e8a9ffffff
.globl _th10_0046105b
_th10_0046105b:
    pop ecx  # 59
.globl _th10_0046105c
_th10_0046105c:
    pop ecx  # 59
.globl _th10_0046105d
_th10_0046105d:
    ret  # c3
.globl _th10_0046105e
_th10_0046105e:
    push ebp  # 55
.globl _th10_0046105f
_th10_0046105f:
    {load} mov ebp, esp  # 8bec
.globl _th10_00461061
_th10_00461061:
    push ecx  # 51
.globl _th10_00461062
_th10_00461062:
    push ebx  # 53
.globl _th10_00461063
_th10_00461063:
    fwait
{disp8} fnstcw [ebp-4]  # 9bd97dfc
.globl _th10_00461067
_th10_00461067:
    {disp8} {load} mov ebx, [ebp-4]  # 8b5dfc
.globl _th10_0046106a
_th10_0046106a:
    {disp32} call _th10_00460ee4  # e875feffff
.globl _th10_0046106f
_th10_0046106f:
    {load} mov ebx, eax  # 8bd8
.globl _th10_00461071
_th10_00461071:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00461074
_th10_00461074:
    not eax  # f7d0
.globl _th10_00461076
_th10_00461076:
    {load} and ebx, eax  # 23d8
.globl _th10_00461078
_th10_00461078:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_0046107b
_th10_0046107b:
    {disp8} {load} and eax, [ebp+0x0C]  # 23450c
.globl _th10_0046107e
_th10_0046107e:
    {load} or ebx, eax  # 0bd8
.globl _th10_00461080
_th10_00461080:
    {disp32} call _th10_00460f76  # e8f1feffff
.globl _th10_00461085
_th10_00461085:
    {disp8} {store} mov [ebp+0x0C], eax  # 89450c
.globl _th10_00461088
_th10_00461088:
    {disp8} fldcw [ebp+0x0C]  # d96d0c
.globl _th10_0046108b
_th10_0046108b:
    {load} mov eax, ebx  # 8bc3
.globl _th10_0046108d
_th10_0046108d:
    pop ebx  # 5b
.globl _th10_0046108e
_th10_0046108e:
    leave  # c9
.globl _th10_0046108f
_th10_0046108f:
    ret  # c3
.globl _th10_00461090
_th10_00461090:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_00461094
_th10_00461094:
    {noimm8s} and eax, 0x0FFF7FFFF  # 25fffff7ff
.globl _th10_00461099
_th10_00461099:
    push eax  # 50
.globl _th10_0046109a
_th10_0046109a:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_0046109e
_th10_0046109e:
    {disp32} call _th10_0046105e  # e8bbffffff
.globl _th10_004610a3
_th10_004610a3:
    pop ecx  # 59
.globl _th10_004610a4
_th10_004610a4:
    pop ecx  # 59
.globl _th10_004610a5
_th10_004610a5:
    ret  # c3
.globl _th10_004610a6
_th10_004610a6:
    push ebp  # 55
.globl _th10_004610a7
_th10_004610a7:
    {load} mov ebp, esp  # 8bec
.globl _th10_004610a9
_th10_004610a9:
    {disp32} call _th10_00456357  # e8a952ffff
.globl _th10_004610ae
_th10_004610ae:
    {disp8} {load} mov eax, [eax+0x60]  # 8b4060
.globl _th10_004610b1
_th10_004610b1:
    {load} cmp eax, [_th10_00497f94]  # 3b05947f4900
.globl _th10_004610b7
_th10_004610b7:
    {disp8} je _th10_004610be  # 7405
.globl _th10_004610b9
_th10_004610b9:
    {disp32} call _th10_0045cf49  # e88bbeffff
.globl _th10_004610be
_th10_004610be:
    {disp8} cmp dword ptr [ebp+0x10], 0  # 837d1000
.globl _th10_004610c2
_th10_004610c2:
    {disp8} jne _th10_004610c8  # 7504
.globl _th10_004610c4
_th10_004610c4:
    {load} xor eax, eax  # 33c0
.globl _th10_004610c6
_th10_004610c6:
    pop ebp  # 5d
.globl _th10_004610c7
_th10_004610c7:
    ret  # c3
.globl _th10_004610c8
_th10_004610c8:
    {disp8} push dword ptr [eax+4]  # ff7004
.globl _th10_004610cb
_th10_004610cb:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004610ce
_th10_004610ce:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004610d1
_th10_004610d1:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004610d4
_th10_004610d4:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_004610d7
_th10_004610d7:
    push 1  # 6a01
.globl _th10_004610d9
_th10_004610d9:
    {disp8} push dword ptr [eax+0x0C]  # ff700c
.globl _th10_004610dc
_th10_004610dc:
    {disp32} call _th10_00461af9  # e8180a0000
.globl _th10_004610e1
_th10_004610e1:
    add esp, 28  # 83c41c
.globl _th10_004610e4
_th10_004610e4:
    test eax, eax  # 85c0
.globl _th10_004610e6
_th10_004610e6:
    {disp8} jne _th10_004610ef  # 7507
.globl _th10_004610e8
_th10_004610e8:
    {noimm8s} mov eax, 0x7FFFFFFF  # b8ffffff7f
.globl _th10_004610ed
_th10_004610ed:
    pop ebp  # 5d
.globl _th10_004610ee
_th10_004610ee:
    ret  # c3
.globl _th10_004610ef
_th10_004610ef:
    add eax, -2  # 83c0fe
.globl _th10_004610f2
_th10_004610f2:
    pop ebp  # 5d
.globl _th10_004610f3
_th10_004610f3:
    ret  # c3
.globl _th10_004610f4
_th10_004610f4:
    push ebp  # 55
.globl _th10_004610f5
_th10_004610f5:
    {load} mov ebp, esp  # 8bec
.globl _th10_004610f7
_th10_004610f7:
    push ecx  # 51
.globl _th10_004610f8
_th10_004610f8:
    push ecx  # 51
.globl _th10_004610f9
_th10_004610f9:
    push ebx  # 53
.globl _th10_004610fa
_th10_004610fa:
    push esi  # 56
.globl _th10_004610fb
_th10_004610fb:
    {load} xor esi, esi  # 33f6
.globl _th10_004610fd
_th10_004610fd:
    push edi  # 57
.globl _th10_004610fe
_th10_004610fe:
    {load} mov edi, [_th10_00477498]  # 8b3d98744700
.globl _th10_00461104
_th10_00461104:
    {disp8} {store} mov [ebp-4], esi  # 8975fc
.globl _th10_00461107
_th10_00461107:
    {load} mov eax, [edi]  # 8b07
.globl _th10_00461109
_th10_00461109:
    {load} cmp eax, esi  # 3bc6
.globl _th10_0046110b
_th10_0046110b:
    {disp8} je _th10_0046116f  # 7462
.globl _th10_0046110d
_th10_0046110d:
    {load} mov ebx, [_th10_00466154]  # 8b1d54614600
.globl _th10_00461113
_th10_00461113:
    push esi  # 56
.globl _th10_00461114
_th10_00461114:
    push esi  # 56
.globl _th10_00461115
_th10_00461115:
    push esi  # 56
.globl _th10_00461116
_th10_00461116:
    push esi  # 56
.globl _th10_00461117
_th10_00461117:
    push -1  # 6aff
.globl _th10_00461119
_th10_00461119:
    push eax  # 50
.globl _th10_0046111a
_th10_0046111a:
    push esi  # 56
.globl _th10_0046111b
_th10_0046111b:
    push esi  # 56
.globl _th10_0046111c
_th10_0046111c:
    call ebx  # ffd3
.globl _th10_0046111e
_th10_0046111e:
    {load} cmp eax, esi  # 3bc6
.globl _th10_00461120
_th10_00461120:
    {disp8} {store} mov [ebp-8], eax  # 8945f8
.globl _th10_00461123
_th10_00461123:
    {disp8} je _th10_0046117f  # 745a
.globl _th10_00461125
_th10_00461125:
    push eax  # 50
.globl _th10_00461126
_th10_00461126:
    {disp32} call _th10_00452706  # e8db15ffff
.globl _th10_0046112b
_th10_0046112b:
    {load} cmp eax, esi  # 3bc6
.globl _th10_0046112d
_th10_0046112d:
    pop ecx  # 59
.globl _th10_0046112e
_th10_0046112e:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_00461131
_th10_00461131:
    {disp8} je _th10_0046117f  # 744c
.globl _th10_00461133
_th10_00461133:
    push esi  # 56
.globl _th10_00461134
_th10_00461134:
    push esi  # 56
.globl _th10_00461135
_th10_00461135:
    {disp8} push dword ptr [ebp-8]  # ff75f8
.globl _th10_00461138
_th10_00461138:
    push eax  # 50
.globl _th10_00461139
_th10_00461139:
    push -1  # 6aff
.globl _th10_0046113b
_th10_0046113b:
    push dword ptr [edi]  # ff37
.globl _th10_0046113d
_th10_0046113d:
    push esi  # 56
.globl _th10_0046113e
_th10_0046113e:
    push esi  # 56
.globl _th10_0046113f
_th10_0046113f:
    call ebx  # ffd3
.globl _th10_00461141
_th10_00461141:
    test eax, eax  # 85c0
.globl _th10_00461143
_th10_00461143:
    {disp8} je _th10_00461176  # 7431
.globl _th10_00461145
_th10_00461145:
    {disp8} lea eax, [ebp-4]  # 8d45fc
.globl _th10_00461148
_th10_00461148:
    push esi  # 56
.globl _th10_00461149
_th10_00461149:
    push eax  # 50
.globl _th10_0046114a
_th10_0046114a:
    {disp32} call _th10_00461f31  # e8e20d0000
.globl _th10_0046114f
_th10_0046114f:
    test eax, eax  # 85c0
.globl _th10_00461151
_th10_00461151:
    pop ecx  # 59
.globl _th10_00461152
_th10_00461152:
    pop ecx  # 59
.globl _th10_00461153
_th10_00461153:
    {disp8} jge _th10_00461166  # 7d11
.globl _th10_00461155
_th10_00461155:
    {disp8} {store} cmp [ebp-4], esi  # 3975fc
.globl _th10_00461158
_th10_00461158:
    {disp8} je _th10_00461166  # 740c
.globl _th10_0046115a
_th10_0046115a:
    {disp8} push dword ptr [ebp-4]  # ff75fc
.globl _th10_0046115d
_th10_0046115d:
    {disp32} call _th10_00452422  # e8c012ffff
.globl _th10_00461162
_th10_00461162:
    pop ecx  # 59
.globl _th10_00461163
_th10_00461163:
    {disp8} {store} mov [ebp-4], esi  # 8975fc
.globl _th10_00461166
_th10_00461166:
    add edi, 4  # 83c704
.globl _th10_00461169
_th10_00461169:
    {load} mov eax, [edi]  # 8b07
.globl _th10_0046116b
_th10_0046116b:
    {load} cmp eax, esi  # 3bc6
.globl _th10_0046116d
_th10_0046116d:
    {disp8} jne _th10_00461113  # 75a4
.globl _th10_0046116f
_th10_0046116f:
    {load} xor eax, eax  # 33c0
.globl _th10_00461171
_th10_00461171:
    pop edi  # 5f
.globl _th10_00461172
_th10_00461172:
    pop esi  # 5e
.globl _th10_00461173
_th10_00461173:
    pop ebx  # 5b
.globl _th10_00461174
_th10_00461174:
    leave  # c9
.globl _th10_00461175
_th10_00461175:
    ret  # c3
.globl _th10_00461176
_th10_00461176:
    {disp8} push dword ptr [ebp-4]  # ff75fc
.globl _th10_00461179
_th10_00461179:
    {disp32} call _th10_00452422  # e8a412ffff
.globl _th10_0046117e
_th10_0046117e:
    pop ecx  # 59
.globl _th10_0046117f
_th10_0046117f:
    or eax, -1  # 83c8ff
.globl _th10_00461182
_th10_00461182:
    {disp8} jmp _th10_00461171  # ebed
.globl _th10_00461184
_th10_00461184:
    push ebp  # 55
.globl _th10_00461185
_th10_00461185:
    {load} mov ebp, esp  # 8bec
.globl _th10_00461187
_th10_00461187:
    sub esp, 12  # 83ec0c
.globl _th10_0046118a
_th10_0046118a:
    {disp8} and dword ptr [ebp-8], 0  # 8365f800
.globl _th10_0046118e
_th10_0046118e:
    {disp8} cmp dword ptr [ebp+0x10], 0  # 837d1000
.globl _th10_00461192
_th10_00461192:
    push ebx  # 53
.globl _th10_00461193
_th10_00461193:
    {disp8} {load} mov ebx, [ebp+0x0C]  # 8b5d0c
.globl _th10_00461196
_th10_00461196:
    push esi  # 56
.globl _th10_00461197
_th10_00461197:
    push edi  # 57
.globl _th10_00461198
_th10_00461198:
    {load} mov edx, ebx  # 8bd3
.globl _th10_0046119a
_th10_0046119a:
    {disp32} je _th10_0046135a  # 0f84ba010000
.globl _th10_004611a0
_th10_004611a0:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004611a3
_th10_004611a3:
    {load} mov ecx, eax  # 8bc8
.globl _th10_004611a5
_th10_004611a5:
    and eax, 31  # 83e01f
.globl _th10_004611a8
_th10_004611a8:
    sar ecx, 5  # c1f905
.globl _th10_004611ab
_th10_004611ab:
    lea esi, [eax+eax*8]  # 8d34c0
.globl _th10_004611ae
_th10_004611ae:
    lea edi, [ecx*4+0x499200]  # 8d3c8d00924900
.globl _th10_004611b5
_th10_004611b5:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004611b7
_th10_004611b7:
    shl esi, 2  # c1e602
.globl _th10_004611ba
_th10_004611ba:
    {load} add eax, esi  # 03c6
.globl _th10_004611bc
_th10_004611bc:
    {disp8} {load} mov cl, [eax+4]  # 8a4804
.globl _th10_004611bf
_th10_004611bf:
    test cl, 2  # f6c102
.globl _th10_004611c2
_th10_004611c2:
    {disp32} jne _th10_0046135a  # 0f8592010000
.globl _th10_004611c8
_th10_004611c8:
    test cl, 0x48  # f6c148
.globl _th10_004611cb
_th10_004611cb:
    {disp8} je _th10_004611ef  # 7422
.globl _th10_004611cd
_th10_004611cd:
    {disp8} cmp byte ptr [eax+5], 0x0A  # 8078050a
.globl _th10_004611d1
_th10_004611d1:
    {disp8} je _th10_004611ef  # 741c
.globl _th10_004611d3
_th10_004611d3:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004611d5
_th10_004611d5:
    {disp8} {load} mov al, [eax+esi+5]  # 8a443005
.globl _th10_004611d9
_th10_004611d9:
    {disp8} dec dword ptr [ebp+0x10]  # ff4d10
.globl _th10_004611dc
_th10_004611dc:
    {store} mov [ebx], al  # 8803
.globl _th10_004611de
_th10_004611de:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004611e0
_th10_004611e0:
    {disp8} lea edx, [ebx+1]  # 8d5301
.globl _th10_004611e3
_th10_004611e3:
    {disp8} {noimm8s} mov dword ptr [ebp-8], 1  # c745f801000000
.globl _th10_004611ea
_th10_004611ea:
    {disp8} mov byte ptr [eax+esi+5], 0x0A  # c64430050a
.globl _th10_004611ef
_th10_004611ef:
    push 0  # 6a00
.globl _th10_004611f1
_th10_004611f1:
    {disp8} lea eax, [ebp-0x0C]  # 8d45f4
.globl _th10_004611f4
_th10_004611f4:
    push eax  # 50
.globl _th10_004611f5
_th10_004611f5:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004611f8
_th10_004611f8:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004611fa
_th10_004611fa:
    push edx  # 52
.globl _th10_004611fb
_th10_004611fb:
    push dword ptr [eax+esi]  # ff3430
.globl _th10_004611fe
_th10_004611fe:
    call dword ptr [_th10_004660d0]  # ff15d0604600
.globl _th10_00461204
_th10_00461204:
    test eax, eax  # 85c0
.globl _th10_00461206
_th10_00461206:
    {disp8} jne _th10_00461241  # 7539
.globl _th10_00461208
_th10_00461208:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_0046120e
_th10_0046120e:
    push 5  # 6a05
.globl _th10_00461210
_th10_00461210:
    pop esi  # 5e
.globl _th10_00461211
_th10_00461211:
    {load} cmp eax, esi  # 3bc6
.globl _th10_00461213
_th10_00461213:
    {disp8} jne _th10_00461229  # 7514
.globl _th10_00461215
_th10_00461215:
    {disp32} call _th10_00456af2  # e8d858ffff
.globl _th10_0046121a
_th10_0046121a:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_00461220
_th10_00461220:
    {disp32} call _th10_00456afb  # e8d658ffff
.globl _th10_00461225
_th10_00461225:
    {store} mov [eax], esi  # 8930
.globl _th10_00461227
_th10_00461227:
    {disp8} jmp _th10_00461239  # eb10
.globl _th10_00461229
_th10_00461229:
    cmp eax, 109  # 83f86d
.globl _th10_0046122c
_th10_0046122c:
    {disp32} je _th10_0046135a  # 0f8428010000
.globl _th10_00461232
_th10_00461232:
    push eax  # 50
.globl _th10_00461233
_th10_00461233:
    {disp32} call _th10_00456b04  # e8cc58ffff
.globl _th10_00461238
_th10_00461238:
    pop ecx  # 59
.globl _th10_00461239
_th10_00461239:
    or eax, -1  # 83c8ff
.globl _th10_0046123c
_th10_0046123c:
    {disp32} jmp _th10_0046135c  # e91b010000
.globl _th10_00461241
_th10_00461241:
    {disp8} {load} mov eax, [ebp-0x0C]  # 8b45f4
.globl _th10_00461244
_th10_00461244:
    {load} mov ecx, [edi]  # 8b0f
.globl _th10_00461246
_th10_00461246:
    {disp8} {store} add [ebp-8], eax  # 0145f8
.globl _th10_00461249
_th10_00461249:
    {disp8} test byte ptr [ecx+esi+4], 0x80  # f644310480
.globl _th10_0046124e
_th10_0046124e:
    {disp32} je _th10_00461355  # 0f8401010000
.globl _th10_00461254
_th10_00461254:
    test eax, eax  # 85c0
.globl _th10_00461256
_th10_00461256:
    {disp8} je _th10_00461268  # 7410
.globl _th10_00461258
_th10_00461258:
    cmp byte ptr [ebx], 0x0A  # 803b0a
.globl _th10_0046125b
_th10_0046125b:
    {disp8} jne _th10_00461268  # 750b
.globl _th10_0046125d
_th10_0046125d:
    {load} mov eax, ecx  # 8bc1
.globl _th10_0046125f
_th10_0046125f:
    {disp8} lea eax, [eax+esi+4]  # 8d443004
.globl _th10_00461263
_th10_00461263:
    or byte ptr [eax], 4  # 800804
.globl _th10_00461266
_th10_00461266:
    {disp8} jmp _th10_00461271  # eb09
.globl _th10_00461268
_th10_00461268:
    {load} mov eax, [edi]  # 8b07
.globl _th10_0046126a
_th10_0046126a:
    {disp8} lea eax, [eax+esi+4]  # 8d443004
.globl _th10_0046126e
_th10_0046126e:
    and byte ptr [eax], 0x0FB  # 8020fb
.globl _th10_00461271
_th10_00461271:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00461274
_th10_00461274:
    {disp8} {load} mov ecx, [ebp-8]  # 8b4df8
.globl _th10_00461277
_th10_00461277:
    {load} add ecx, eax  # 03c8
.globl _th10_00461279
_th10_00461279:
    {load} cmp eax, ecx  # 3bc1
.globl _th10_0046127b
_th10_0046127b:
    {disp8} {store} mov [ebp+0x10], eax  # 894510
.globl _th10_0046127e
_th10_0046127e:
    {disp8} {store} mov [ebp-8], ecx  # 894df8
.globl _th10_00461281
_th10_00461281:
    {disp32} jae _th10_0046134f  # 0f83c8000000
.globl _th10_00461287
_th10_00461287:
    {disp8} {load} mov eax, [ebp+0x10]  # 8b4510
.globl _th10_0046128a
_th10_0046128a:
    {load} mov al, [eax]  # 8a00
.globl _th10_0046128c
_th10_0046128c:
    cmp al, 0x1A  # 3c1a
.globl _th10_0046128e
_th10_0046128e:
    {disp32} je _th10_0046133f  # 0f84ab000000
.globl _th10_00461294
_th10_00461294:
    cmp al, 0x0D  # 3c0d
.globl _th10_00461296
_th10_00461296:
    {disp8} je _th10_004612a3  # 740b
.globl _th10_00461298
_th10_00461298:
    {store} mov [ebx], al  # 8803
.globl _th10_0046129a
_th10_0046129a:
    inc ebx  # 43
.globl _th10_0046129b
_th10_0046129b:
    {disp8} inc dword ptr [ebp+0x10]  # ff4510
.globl _th10_0046129e
_th10_0046129e:
    {disp32} jmp _th10_00461331  # e98e000000
.globl _th10_004612a3
_th10_004612a3:
    dec ecx  # 49
.globl _th10_004612a4
_th10_004612a4:
    {disp8} {store} cmp [ebp+0x10], ecx  # 394d10
.globl _th10_004612a7
_th10_004612a7:
    {disp8} jae _th10_004612bd  # 7314
.globl _th10_004612a9
_th10_004612a9:
    {disp8} {load} mov eax, [ebp+0x10]  # 8b4510
.globl _th10_004612ac
_th10_004612ac:
    inc eax  # 40
.globl _th10_004612ad
_th10_004612ad:
    cmp byte ptr [eax], 0x0A  # 80380a
.globl _th10_004612b0
_th10_004612b0:
    {disp8} jne _th10_004612b8  # 7506
.globl _th10_004612b2
_th10_004612b2:
    {disp8} add dword ptr [ebp+0x10], 2  # 83451002
.globl _th10_004612b6
_th10_004612b6:
    {disp8} jmp _th10_00461311  # eb59
.globl _th10_004612b8
_th10_004612b8:
    {disp8} {store} mov [ebp+0x10], eax  # 894510
.globl _th10_004612bb
_th10_004612bb:
    {disp8} jmp _th10_0046132d  # eb70
.globl _th10_004612bd
_th10_004612bd:
    {disp8} inc dword ptr [ebp+0x10]  # ff4510
.globl _th10_004612c0
_th10_004612c0:
    push 0  # 6a00
.globl _th10_004612c2
_th10_004612c2:
    {disp8} lea eax, [ebp-0x0C]  # 8d45f4
.globl _th10_004612c5
_th10_004612c5:
    push eax  # 50
.globl _th10_004612c6
_th10_004612c6:
    push 1  # 6a01
.globl _th10_004612c8
_th10_004612c8:
    {disp8} lea eax, [ebp-1]  # 8d45ff
.globl _th10_004612cb
_th10_004612cb:
    push eax  # 50
.globl _th10_004612cc
_th10_004612cc:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004612ce
_th10_004612ce:
    push dword ptr [eax+esi]  # ff3430
.globl _th10_004612d1
_th10_004612d1:
    call dword ptr [_th10_004660d0]  # ff15d0604600
.globl _th10_004612d7
_th10_004612d7:
    test eax, eax  # 85c0
.globl _th10_004612d9
_th10_004612d9:
    {disp8} jne _th10_004612e5  # 750a
.globl _th10_004612db
_th10_004612db:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_004612e1
_th10_004612e1:
    test eax, eax  # 85c0
.globl _th10_004612e3
_th10_004612e3:
    {disp8} jne _th10_0046132d  # 7548
.globl _th10_004612e5
_th10_004612e5:
    {disp8} cmp dword ptr [ebp-0x0C], 0  # 837df400
.globl _th10_004612e9
_th10_004612e9:
    {disp8} je _th10_0046132d  # 7442
.globl _th10_004612eb
_th10_004612eb:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004612ed
_th10_004612ed:
    {disp8} test byte ptr [eax+esi+4], 0x48  # f644300448
.globl _th10_004612f2
_th10_004612f2:
    {disp8} je _th10_00461306  # 7412
.globl _th10_004612f4
_th10_004612f4:
    {disp8} {load} mov al, [ebp-1]  # 8a45ff
.globl _th10_004612f7
_th10_004612f7:
    cmp al, 0x0A  # 3c0a
.globl _th10_004612f9
_th10_004612f9:
    {disp8} je _th10_00461311  # 7416
.globl _th10_004612fb
_th10_004612fb:
    mov byte ptr [ebx], 0x0D  # c6030d
.globl _th10_004612fe
_th10_004612fe:
    {load} mov ecx, [edi]  # 8b0f
.globl _th10_00461300
_th10_00461300:
    {disp8} {store} mov [ecx+esi+5], al  # 88443105
.globl _th10_00461304
_th10_00461304:
    {disp8} jmp _th10_00461330  # eb2a
.globl _th10_00461306
_th10_00461306:
    {disp8} {load} cmp ebx, [ebp+0x0C]  # 3b5d0c
.globl _th10_00461309
_th10_00461309:
    {disp8} jne _th10_00461316  # 750b
.globl _th10_0046130b
_th10_0046130b:
    {disp8} cmp byte ptr [ebp-1], 0x0A  # 807dff0a
.globl _th10_0046130f
_th10_0046130f:
    {disp8} jne _th10_00461316  # 7505
.globl _th10_00461311
_th10_00461311:
    mov byte ptr [ebx], 0x0A  # c6030a
.globl _th10_00461314
_th10_00461314:
    {disp8} jmp _th10_00461330  # eb1a
.globl _th10_00461316
_th10_00461316:
    push 1  # 6a01
.globl _th10_00461318
_th10_00461318:
    push -1  # 6aff
.globl _th10_0046131a
_th10_0046131a:
    push -1  # 6aff
.globl _th10_0046131c
_th10_0046131c:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046131f
_th10_0046131f:
    {disp32} call _th10_0045fa1a  # e8f6e6ffff
.globl _th10_00461324
_th10_00461324:
    add esp, 16  # 83c410
.globl _th10_00461327
_th10_00461327:
    {disp8} cmp byte ptr [ebp-1], 0x0A  # 807dff0a
.globl _th10_0046132b
_th10_0046132b:
    {disp8} je _th10_00461331  # 7404
.globl _th10_0046132d
_th10_0046132d:
    mov byte ptr [ebx], 0x0D  # c6030d
.globl _th10_00461330
_th10_00461330:
    inc ebx  # 43
.globl _th10_00461331
_th10_00461331:
    {disp8} {load} mov ecx, [ebp-8]  # 8b4df8
.globl _th10_00461334
_th10_00461334:
    {disp8} {store} cmp [ebp+0x10], ecx  # 394d10
.globl _th10_00461337
_th10_00461337:
    {disp32} jb _th10_00461287  # 0f824affffff
.globl _th10_0046133d
_th10_0046133d:
    {disp8} jmp _th10_0046134f  # eb10
.globl _th10_0046133f
_th10_0046133f:
    {load} mov eax, [edi]  # 8b07
.globl _th10_00461341
_th10_00461341:
    {disp8} test byte ptr [eax+esi+4], 0x40  # f644300440
.globl _th10_00461346
_th10_00461346:
    {disp8} jne _th10_0046134f  # 7507
.globl _th10_00461348
_th10_00461348:
    {disp8} lea esi, [eax+esi+4]  # 8d743004
.globl _th10_0046134c
_th10_0046134c:
    or byte ptr [esi], 2  # 800e02
.globl _th10_0046134f
_th10_0046134f:
    {disp8} {load} sub ebx, [ebp+0x0C]  # 2b5d0c
.globl _th10_00461352
_th10_00461352:
    {disp8} {store} mov [ebp-8], ebx  # 895df8
.globl _th10_00461355
_th10_00461355:
    {disp8} {load} mov eax, [ebp-8]  # 8b45f8
.globl _th10_00461358
_th10_00461358:
    {disp8} jmp _th10_0046135c  # eb02
.globl _th10_0046135a
_th10_0046135a:
    {load} xor eax, eax  # 33c0
.globl _th10_0046135c
_th10_0046135c:
    pop edi  # 5f
.globl _th10_0046135d
_th10_0046135d:
    pop esi  # 5e
.globl _th10_0046135e
_th10_0046135e:
    pop ebx  # 5b
.globl _th10_0046135f
_th10_0046135f:
    leave  # c9
.globl _th10_00461360
_th10_00461360:
    ret  # c3
.globl _th10_00461361
_th10_00461361:
    push 12  # 6a0c
.globl _th10_00461363
_th10_00461363:
    {noimm8s} push 0x46C950  # 6850c94600
.globl _th10_00461368
_th10_00461368:
    {disp32} call _th10_00454bbc  # e84f38ffff
.globl _th10_0046136d
_th10_0046136d:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00461370
_th10_00461370:
    {load} cmp ebx, [_th10_004991e4]  # 3b1de4914900
.globl _th10_00461376
_th10_00461376:
    {disp8} jae _th10_004613f0  # 7378
.globl _th10_00461378
_th10_00461378:
    {load} mov eax, ebx  # 8bc3
.globl _th10_0046137a
_th10_0046137a:
    sar eax, 5  # c1f805
.globl _th10_0046137d
_th10_0046137d:
    lea edi, [eax*4+0x499200]  # 8d3c8500924900
.globl _th10_00461384
_th10_00461384:
    {load} mov eax, ebx  # 8bc3
.globl _th10_00461386
_th10_00461386:
    and eax, 31  # 83e01f
.globl _th10_00461389
_th10_00461389:
    lea esi, [eax+eax*8]  # 8d34c0
.globl _th10_0046138c
_th10_0046138c:
    shl esi, 2  # c1e602
.globl _th10_0046138f
_th10_0046138f:
    {load} mov eax, [edi]  # 8b07
.globl _th10_00461391
_th10_00461391:
    {disp8} test byte ptr [eax+esi+4], 1  # f644300401
.globl _th10_00461396
_th10_00461396:
    {disp8} je _th10_004613f0  # 7458
.globl _th10_00461398
_th10_00461398:
    push ebx  # 53
.globl _th10_00461399
_th10_00461399:
    {disp32} call _th10_0045f715  # e877e3ffff
.globl _th10_0046139e
_th10_0046139e:
    pop ecx  # 59
.globl _th10_0046139f
_th10_0046139f:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_004613a3
_th10_004613a3:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004613a5
_th10_004613a5:
    {disp8} test byte ptr [eax+esi+4], 1  # f644300401
.globl _th10_004613aa
_th10_004613aa:
    {disp8} je _th10_004613c0  # 7414
.globl _th10_004613ac
_th10_004613ac:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004613af
_th10_004613af:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004613b2
_th10_004613b2:
    push ebx  # 53
.globl _th10_004613b3
_th10_004613b3:
    {disp32} call _th10_00461184  # e8ccfdffff
.globl _th10_004613b8
_th10_004613b8:
    add esp, 12  # 83c40c
.globl _th10_004613bb
_th10_004613bb:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_004613be
_th10_004613be:
    {disp8} jmp _th10_004613d7  # eb17
.globl _th10_004613c0
_th10_004613c0:
    {disp32} call _th10_00456af2  # e82d57ffff
.globl _th10_004613c5
_th10_004613c5:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_004613cb
_th10_004613cb:
    {disp32} call _th10_00456afb  # e82b57ffff
.globl _th10_004613d0
_th10_004613d0:
    and dword ptr [eax], 0  # 832000
.globl _th10_004613d3
_th10_004613d3:
    {disp8} or dword ptr [ebp-0x1C], -1  # 834de4ff
.globl _th10_004613d7
_th10_004613d7:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_004613db
_th10_004613db:
    {disp32} call _th10_004613e8  # e808000000
.globl _th10_004613e0
_th10_004613e0:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_004613e3
_th10_004613e3:
    {disp8} jmp _th10_00461406  # eb21
.globl _th10_004613e5
_th10_004613e5:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_004613e8
_th10_004613e8:
    push ebx  # 53
.globl _th10_004613e9
_th10_004613e9:
    {disp32} call _th10_0045f7b5  # e8c7e3ffff
.globl _th10_004613ee
_th10_004613ee:
    pop ecx  # 59
.globl _th10_004613ef
_th10_004613ef:
    ret  # c3
.globl _th10_004613f0
_th10_004613f0:
    {disp32} call _th10_00456af2  # e8fd56ffff
.globl _th10_004613f5
_th10_004613f5:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_004613fb
_th10_004613fb:
    {disp32} call _th10_00456afb  # e8fb56ffff
.globl _th10_00461400
_th10_00461400:
    and dword ptr [eax], 0  # 832000
.globl _th10_00461403
_th10_00461403:
    or eax, -1  # 83c8ff
.globl _th10_00461406
_th10_00461406:
    {disp32} call _th10_00454bf7  # e8ec37ffff
.globl _th10_0046140b
_th10_0046140b:
    ret  # c3
.globl _th10_0046140c
_th10_0046140c:
    push esi  # 56
.globl _th10_0046140d
_th10_0046140d:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_00461411
_th10_00461411:
    push edi  # 57
.globl _th10_00461412
_th10_00461412:
    or edi, -1  # 83cfff
.globl _th10_00461415
_th10_00461415:
    {disp8} test byte ptr [esi+0x0C], 0x83  # f6460c83
.globl _th10_00461419
_th10_00461419:
    {disp8} je _th10_0046144f  # 7434
.globl _th10_0046141b
_th10_0046141b:
    push esi  # 56
.globl _th10_0046141c
_th10_0046141c:
    {disp32} call _th10_0045fbf6  # e8d5e7ffff
.globl _th10_00461421
_th10_00461421:
    push esi  # 56
.globl _th10_00461422
_th10_00461422:
    {load} mov edi, eax  # 8bf8
.globl _th10_00461424
_th10_00461424:
    {disp32} call _th10_00462225  # e8fc0d0000
.globl _th10_00461429
_th10_00461429:
    {disp8} push dword ptr [esi+0x10]  # ff7610
.globl _th10_0046142c
_th10_0046142c:
    {disp32} call _th10_0046218a  # e8590d0000
.globl _th10_00461431
_th10_00461431:
    add esp, 12  # 83c40c
.globl _th10_00461434
_th10_00461434:
    test eax, eax  # 85c0
.globl _th10_00461436
_th10_00461436:
    {disp8} jge _th10_0046143d  # 7d05
.globl _th10_00461438
_th10_00461438:
    or edi, -1  # 83cfff
.globl _th10_0046143b
_th10_0046143b:
    {disp8} jmp _th10_0046144f  # eb12
.globl _th10_0046143d
_th10_0046143d:
    {disp8} {load} mov eax, [esi+0x1C]  # 8b461c
.globl _th10_00461440
_th10_00461440:
    test eax, eax  # 85c0
.globl _th10_00461442
_th10_00461442:
    {disp8} je _th10_0046144f  # 740b
.globl _th10_00461444
_th10_00461444:
    push eax  # 50
.globl _th10_00461445
_th10_00461445:
    {disp32} call _th10_00452422  # e8d80fffff
.globl _th10_0046144a
_th10_0046144a:
    {disp8} and dword ptr [esi+0x1C], 0  # 83661c00
.globl _th10_0046144e
_th10_0046144e:
    pop ecx  # 59
.globl _th10_0046144f
_th10_0046144f:
    {disp8} and dword ptr [esi+0x0C], 0  # 83660c00
.globl _th10_00461453
_th10_00461453:
    {load} mov eax, edi  # 8bc7
.globl _th10_00461455
_th10_00461455:
    pop edi  # 5f
.globl _th10_00461456
_th10_00461456:
    pop esi  # 5e
.globl _th10_00461457
_th10_00461457:
    ret  # c3
.globl _th10_00461458
_th10_00461458:
    push 12  # 6a0c
.globl _th10_0046145a
_th10_0046145a:
    {noimm8s} push 0x46C960  # 6860c94600
.globl _th10_0046145f
_th10_0046145f:
    {disp32} call _th10_00454bbc  # e85837ffff
.globl _th10_00461464
_th10_00461464:
    {disp8} or dword ptr [ebp-0x1C], -1  # 834de4ff
.globl _th10_00461468
_th10_00461468:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_0046146b
_th10_0046146b:
    {disp8} test byte ptr [esi+0x0C], 0x40  # f6460c40
.globl _th10_0046146f
_th10_0046146f:
    {disp8} je _th10_0046147e  # 740d
.globl _th10_00461471
_th10_00461471:
    {disp8} and dword ptr [esi+0x0C], 0  # 83660c00
.globl _th10_00461475
_th10_00461475:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_00461478
_th10_00461478:
    {disp32} call _th10_00454bf7  # e87a37ffff
.globl _th10_0046147d
_th10_0046147d:
    ret  # c3
.globl _th10_0046147e
_th10_0046147e:
    push esi  # 56
.globl _th10_0046147f
_th10_0046147f:
    {disp32} call _th10_0045a06a  # e8e68bffff
.globl _th10_00461484
_th10_00461484:
    pop ecx  # 59
.globl _th10_00461485
_th10_00461485:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00461489
_th10_00461489:
    push esi  # 56
.globl _th10_0046148a
_th10_0046148a:
    {disp32} call _th10_0046140c  # e87dffffff
.globl _th10_0046148f
_th10_0046148f:
    pop ecx  # 59
.globl _th10_00461490
_th10_00461490:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_00461493
_th10_00461493:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461497
_th10_00461497:
    {disp32} call _th10_004614a1  # e805000000
.globl _th10_0046149c
_th10_0046149c:
    {disp8} jmp _th10_00461475  # ebd7
.globl _th10_0046149e
_th10_0046149e:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_004614a1
_th10_004614a1:
    push esi  # 56
.globl _th10_004614a2
_th10_004614a2:
    {disp32} call _th10_0045a0bc  # e8158cffff
.globl _th10_004614a7
_th10_004614a7:
    pop ecx  # 59
.globl _th10_004614a8
_th10_004614a8:
    ret  # c3
.globl _th10_004614a9
_th10_004614a9:
    push 12  # 6a0c
.globl _th10_004614ab
_th10_004614ab:
    {noimm8s} push 0x46C970  # 6870c94600
.globl _th10_004614b0
_th10_004614b0:
    {disp32} call _th10_00454bbc  # e80737ffff
.globl _th10_004614b5
_th10_004614b5:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_004614b8
_th10_004614b8:
    {load} cmp ebx, [_th10_004991e4]  # 3b1de4914900
.globl _th10_004614be
_th10_004614be:
    {disp32} jae _th10_00461551  # 0f838d000000
.globl _th10_004614c4
_th10_004614c4:
    {load} mov eax, ebx  # 8bc3
.globl _th10_004614c6
_th10_004614c6:
    sar eax, 5  # c1f805
.globl _th10_004614c9
_th10_004614c9:
    lea edi, [eax*4+0x499200]  # 8d3c8500924900
.globl _th10_004614d0
_th10_004614d0:
    {load} mov eax, ebx  # 8bc3
.globl _th10_004614d2
_th10_004614d2:
    and eax, 31  # 83e01f
.globl _th10_004614d5
_th10_004614d5:
    lea esi, [eax+eax*8]  # 8d34c0
.globl _th10_004614d8
_th10_004614d8:
    shl esi, 2  # c1e602
.globl _th10_004614db
_th10_004614db:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004614dd
_th10_004614dd:
    {disp8} test byte ptr [eax+esi+4], 1  # f644300401
.globl _th10_004614e2
_th10_004614e2:
    {disp8} je _th10_00461551  # 746d
.globl _th10_004614e4
_th10_004614e4:
    push ebx  # 53
.globl _th10_004614e5
_th10_004614e5:
    {disp32} call _th10_0045f715  # e82be2ffff
.globl _th10_004614ea
_th10_004614ea:
    pop ecx  # 59
.globl _th10_004614eb
_th10_004614eb:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_004614ef
_th10_004614ef:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004614f1
_th10_004614f1:
    {disp8} test byte ptr [eax+esi+4], 1  # f644300401
.globl _th10_004614f6
_th10_004614f6:
    {disp8} je _th10_00461529  # 7431
.globl _th10_004614f8
_th10_004614f8:
    push ebx  # 53
.globl _th10_004614f9
_th10_004614f9:
    {disp32} call _th10_0045f6d4  # e8d6e1ffff
.globl _th10_004614fe
_th10_004614fe:
    pop ecx  # 59
.globl _th10_004614ff
_th10_004614ff:
    push eax  # 50
.globl _th10_00461500
_th10_00461500:
    call dword ptr [_th10_004661c4]  # ff15c4614600
.globl _th10_00461506
_th10_00461506:
    test eax, eax  # 85c0
.globl _th10_00461508
_th10_00461508:
    {disp8} jne _th10_00461515  # 750b
.globl _th10_0046150a
_th10_0046150a:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_00461510
_th10_00461510:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_00461513
_th10_00461513:
    {disp8} jmp _th10_00461519  # eb04
.globl _th10_00461515
_th10_00461515:
    {disp8} and dword ptr [ebp-0x1C], 0  # 8365e400
.globl _th10_00461519
_th10_00461519:
    {disp8} cmp dword ptr [ebp-0x1C], 0  # 837de400
.globl _th10_0046151d
_th10_0046151d:
    {disp8} je _th10_00461538  # 7419
.globl _th10_0046151f
_th10_0046151f:
    {disp32} call _th10_00456afb  # e8d755ffff
.globl _th10_00461524
_th10_00461524:
    {disp8} {load} mov ecx, [ebp-0x1C]  # 8b4de4
.globl _th10_00461527
_th10_00461527:
    {store} mov [eax], ecx  # 8908
.globl _th10_00461529
_th10_00461529:
    {disp32} call _th10_00456af2  # e8c455ffff
.globl _th10_0046152e
_th10_0046152e:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_00461534
_th10_00461534:
    {disp8} or dword ptr [ebp-0x1C], -1  # 834de4ff
.globl _th10_00461538
_th10_00461538:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_0046153c
_th10_0046153c:
    {disp32} call _th10_00461549  # e808000000
.globl _th10_00461541
_th10_00461541:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_00461544
_th10_00461544:
    {disp8} jmp _th10_0046155f  # eb19
.globl _th10_00461546
_th10_00461546:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00461549
_th10_00461549:
    push ebx  # 53
.globl _th10_0046154a
_th10_0046154a:
    {disp32} call _th10_0045f7b5  # e866e2ffff
.globl _th10_0046154f
_th10_0046154f:
    pop ecx  # 59
.globl _th10_00461550
_th10_00461550:
    ret  # c3
.globl _th10_00461551
_th10_00461551:
    {disp32} call _th10_00456af2  # e89c55ffff
.globl _th10_00461556
_th10_00461556:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_0046155c
_th10_0046155c:
    or eax, -1  # 83c8ff
.globl _th10_0046155f
_th10_0046155f:
    {disp32} call _th10_00454bf7  # e89336ffff
.globl _th10_00461564
_th10_00461564:
    ret  # c3
.globl _th10_00461565
_th10_00461565:
    push 24  # 6a18
.globl _th10_00461567
_th10_00461567:
    {noimm8s} push 0x46C980  # 6880c94600
.globl _th10_0046156c
_th10_0046156c:
    {disp32} call _th10_00454bbc  # e84b36ffff
.globl _th10_00461571
_th10_00461571:
    {load} xor edi, edi  # 33ff
.globl _th10_00461573
_th10_00461573:
    {load} xor ebx, ebx  # 33db
.globl _th10_00461575
_th10_00461575:
    inc ebx  # 43
.globl _th10_00461576
_th10_00461576:
    {store} cmp [_th10_004776cc], edi  # 393dcc764700
.globl _th10_0046157c
_th10_0046157c:
    {disp8} jne _th10_004615a9  # 752b
.globl _th10_0046157e
_th10_0046157e:
    push edi  # 57
.globl _th10_0046157f
_th10_0046157f:
    push edi  # 57
.globl _th10_00461580
_th10_00461580:
    push ebx  # 53
.globl _th10_00461581
_th10_00461581:
    push edi  # 57
.globl _th10_00461582
_th10_00461582:
    call dword ptr [_th10_004661c8]  # ff15c8614600
.globl _th10_00461588
_th10_00461588:
    test eax, eax  # 85c0
.globl _th10_0046158a
_th10_0046158a:
    {disp8} je _th10_00461594  # 7408
.globl _th10_0046158c
_th10_0046158c:
    {store} mov [_th10_004776cc], ebx  # 891dcc764700
.globl _th10_00461592
_th10_00461592:
    {disp8} jmp _th10_004615a9  # eb15
.globl _th10_00461594
_th10_00461594:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_0046159a
_th10_0046159a:
    cmp eax, 120  # 83f878
.globl _th10_0046159d
_th10_0046159d:
    {disp8} jne _th10_004615a9  # 750a
.globl _th10_0046159f
_th10_0046159f:
    {noimm8s} mov dword ptr [_th10_004776cc], 2  # c705cc76470002000000
.globl _th10_004615a9
_th10_004615a9:
    mov eax, [_th10_004776cc]  # a1cc764700
.globl _th10_004615ae
_th10_004615ae:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_004615b0
_th10_004615b0:
    {disp8} jne _th10_004615c9  # 7517
.globl _th10_004615b2
_th10_004615b2:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004615b5
_th10_004615b5:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004615b8
_th10_004615b8:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004615bb
_th10_004615bb:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_004615be
_th10_004615be:
    call dword ptr [_th10_004661c8]  # ff15c8614600
.globl _th10_004615c4
_th10_004615c4:
    {disp32} jmp _th10_0046168c  # e9c3000000
.globl _th10_004615c9
_th10_004615c9:
    cmp eax, 2  # 83f802
.globl _th10_004615cc
_th10_004615cc:
    {disp8} je _th10_004615d2  # 7404
.globl _th10_004615ce
_th10_004615ce:
    {load} cmp eax, edi  # 3bc7
.globl _th10_004615d0
_th10_004615d0:
    {disp8} jne _th10_004615fa  # 7528
.globl _th10_004615d2
_th10_004615d2:
    {disp8} {store} mov [ebp-0x1C], edi  # 897de4
.globl _th10_004615d5
_th10_004615d5:
    {disp8} {store} mov [ebp-0x24], edi  # 897ddc
.globl _th10_004615d8
_th10_004615d8:
    {disp8} {store} cmp [ebp+0x18], edi  # 397d18
.globl _th10_004615db
_th10_004615db:
    {disp8} jne _th10_004615e5  # 7508
.globl _th10_004615dd
_th10_004615dd:
    mov eax, [_th10_00477664]  # a164764700
.globl _th10_004615e2
_th10_004615e2:
    {disp8} {store} mov [ebp+0x18], eax  # 894518
.globl _th10_004615e5
_th10_004615e5:
    push edi  # 57
.globl _th10_004615e6
_th10_004615e6:
    push edi  # 57
.globl _th10_004615e7
_th10_004615e7:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004615ea
_th10_004615ea:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_004615ed
_th10_004615ed:
    call dword ptr [_th10_0046605c]  # ff155c604600
.globl _th10_004615f3
_th10_004615f3:
    {disp8} {store} mov [ebp-0x20], eax  # 8945e0
.globl _th10_004615f6
_th10_004615f6:
    {load} cmp eax, edi  # 3bc7
.globl _th10_004615f8
_th10_004615f8:
    {disp8} jne _th10_00461601  # 7507
.globl _th10_004615fa
_th10_004615fa:
    {load} xor eax, eax  # 33c0
.globl _th10_004615fc
_th10_004615fc:
    {disp32} jmp _th10_0046168c  # e98b000000
.globl _th10_00461601
_th10_00461601:
    {disp8} {store} mov [ebp-4], edi  # 897dfc
.globl _th10_00461604
_th10_00461604:
    add eax, 3  # 83c003
.globl _th10_00461607
_th10_00461607:
    and eax, -4  # 83e0fc
.globl _th10_0046160a
_th10_0046160a:
    {disp32} call _th10_00458ec0  # e8b178ffff
.globl _th10_0046160f
_th10_0046160f:
    {disp8} {store} mov [ebp-0x18], esp  # 8965e8
.globl _th10_00461612
_th10_00461612:
    {load} mov esi, esp  # 8bf4
.globl _th10_00461614
_th10_00461614:
    {disp8} {store} mov [ebp-0x28], esi  # 8975d8
.globl _th10_00461617
_th10_00461617:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_0046161b
_th10_0046161b:
    {disp8} jmp _th10_00461634  # eb17
.globl _th10_0046161d
_th10_0046161d:
    {load} xor eax, eax  # 33c0
.globl _th10_0046161f
_th10_0046161f:
    inc eax  # 40
.globl _th10_00461620
_th10_00461620:
    ret  # c3
.globl _th10_00461621
_th10_00461621:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00461624
_th10_00461624:
    {disp32} call _th10_00458d91  # e86877ffff
.globl _th10_00461629
_th10_00461629:
    {load} xor edi, edi  # 33ff
.globl _th10_0046162b
_th10_0046162b:
    {load} xor esi, esi  # 33f6
.globl _th10_0046162d
_th10_0046162d:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461631
_th10_00461631:
    {load} xor ebx, ebx  # 33db
.globl _th10_00461633
_th10_00461633:
    inc ebx  # 43
.globl _th10_00461634
_th10_00461634:
    {load} cmp esi, edi  # 3bf7
.globl _th10_00461636
_th10_00461636:
    {disp8} jne _th10_0046164a  # 7512
.globl _th10_00461638
_th10_00461638:
    {disp8} push dword ptr [ebp-0x20]  # ff75e0
.globl _th10_0046163b
_th10_0046163b:
    {disp32} call _th10_00452706  # e8c610ffff
.globl _th10_00461640
_th10_00461640:
    pop ecx  # 59
.globl _th10_00461641
_th10_00461641:
    {load} mov esi, eax  # 8bf0
.globl _th10_00461643
_th10_00461643:
    {load} cmp esi, edi  # 3bf7
.globl _th10_00461645
_th10_00461645:
    {disp8} je _th10_004615fa  # 74b3
.globl _th10_00461647
_th10_00461647:
    {disp8} {store} mov [ebp-0x24], ebx  # 895ddc
.globl _th10_0046164a
_th10_0046164a:
    {disp8} push dword ptr [ebp-0x20]  # ff75e0
.globl _th10_0046164d
_th10_0046164d:
    push esi  # 56
.globl _th10_0046164e
_th10_0046164e:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00461651
_th10_00461651:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00461654
_th10_00461654:
    call dword ptr [_th10_0046605c]  # ff155c604600
.globl _th10_0046165a
_th10_0046165a:
    test eax, eax  # 85c0
.globl _th10_0046165c
_th10_0046165c:
    {disp8} je _th10_0046167d  # 741f
.globl _th10_0046165e
_th10_0046165e:
    {disp8} {store} cmp [ebp+0x14], edi  # 397d14
.globl _th10_00461661
_th10_00461661:
    {disp8} jne _th10_00461667  # 7504
.globl _th10_00461663
_th10_00461663:
    push edi  # 57
.globl _th10_00461664
_th10_00461664:
    push edi  # 57
.globl _th10_00461665
_th10_00461665:
    {disp8} jmp _th10_0046166d  # eb06
.globl _th10_00461667
_th10_00461667:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_0046166a
_th10_0046166a:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_0046166d
_th10_0046166d:
    push -1  # 6aff
.globl _th10_0046166f
_th10_0046166f:
    push esi  # 56
.globl _th10_00461670
_th10_00461670:
    push ebx  # 53
.globl _th10_00461671
_th10_00461671:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_00461674
_th10_00461674:
    call dword ptr [_th10_00466104]  # ff1504614600
.globl _th10_0046167a
_th10_0046167a:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_0046167d
_th10_0046167d:
    {disp8} {store} cmp [ebp-0x24], edi  # 397ddc
.globl _th10_00461680
_th10_00461680:
    {disp8} je _th10_00461689  # 7407
.globl _th10_00461682
_th10_00461682:
    push esi  # 56
.globl _th10_00461683
_th10_00461683:
    {disp32} call _th10_00452422  # e89a0dffff
.globl _th10_00461688
_th10_00461688:
    pop ecx  # 59
.globl _th10_00461689
_th10_00461689:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_0046168c
_th10_0046168c:
    {disp8} lea esp, [ebp-0x34]  # 8d65cc
.globl _th10_0046168f
_th10_0046168f:
    {disp32} call _th10_00454bf7  # e86335ffff
.globl _th10_00461694
_th10_00461694:
    ret  # c3
.globl _th10_00461695
_th10_00461695:
    push 24  # 6a18
.globl _th10_00461697
_th10_00461697:
    {noimm8s} push 0x46C990  # 6890c94600
.globl _th10_0046169c
_th10_0046169c:
    {disp32} call _th10_00454bbc  # e81b35ffff
.globl _th10_004616a1
_th10_004616a1:
    {load} xor esi, esi  # 33f6
.globl _th10_004616a3
_th10_004616a3:
    {store} cmp [_th10_004776d0], esi  # 3935d0764700
.globl _th10_004616a9
_th10_004616a9:
    {disp8} jne _th10_004616d9  # 752e
.globl _th10_004616ab
_th10_004616ab:
    push esi  # 56
.globl _th10_004616ac
_th10_004616ac:
    push esi  # 56
.globl _th10_004616ad
_th10_004616ad:
    {load} xor edi, edi  # 33ff
.globl _th10_004616af
_th10_004616af:
    inc edi  # 47
.globl _th10_004616b0
_th10_004616b0:
    push edi  # 57
.globl _th10_004616b1
_th10_004616b1:
    push esi  # 56
.globl _th10_004616b2
_th10_004616b2:
    call dword ptr [_th10_004661c8]  # ff15c8614600
.globl _th10_004616b8
_th10_004616b8:
    test eax, eax  # 85c0
.globl _th10_004616ba
_th10_004616ba:
    {disp8} je _th10_004616c4  # 7408
.globl _th10_004616bc
_th10_004616bc:
    {store} mov [_th10_004776d0], edi  # 893dd0764700
.globl _th10_004616c2
_th10_004616c2:
    {disp8} jmp _th10_004616d9  # eb15
.globl _th10_004616c4
_th10_004616c4:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_004616ca
_th10_004616ca:
    cmp eax, 120  # 83f878
.globl _th10_004616cd
_th10_004616cd:
    {disp8} jne _th10_004616d9  # 750a
.globl _th10_004616cf
_th10_004616cf:
    {noimm8s} mov dword ptr [_th10_004776d0], 2  # c705d076470002000000
.globl _th10_004616d9
_th10_004616d9:
    mov eax, [_th10_004776d0]  # a1d0764700
.globl _th10_004616de
_th10_004616de:
    cmp eax, 2  # 83f802
.globl _th10_004616e1
_th10_004616e1:
    {disp32} je _th10_004617ba  # 0f84d3000000
.globl _th10_004616e7
_th10_004616e7:
    {load} cmp eax, esi  # 3bc6
.globl _th10_004616e9
_th10_004616e9:
    {disp32} je _th10_004617ba  # 0f84cb000000
.globl _th10_004616ef
_th10_004616ef:
    cmp eax, 1  # 83f801
.globl _th10_004616f2
_th10_004616f2:
    {disp8} jne _th10_0046171e  # 752a
.globl _th10_004616f4
_th10_004616f4:
    {disp8} {store} mov [ebp-0x1C], esi  # 8975e4
.globl _th10_004616f7
_th10_004616f7:
    {disp8} {store} mov [ebp-0x20], esi  # 8975e0
.globl _th10_004616fa
_th10_004616fa:
    {disp8} {store} cmp [ebp+0x18], esi  # 397518
.globl _th10_004616fd
_th10_004616fd:
    {disp8} jne _th10_00461707  # 7508
.globl _th10_004616ff
_th10_004616ff:
    mov eax, [_th10_00477664]  # a164764700
.globl _th10_00461704
_th10_00461704:
    {disp8} {store} mov [ebp+0x18], eax  # 894518
.globl _th10_00461707
_th10_00461707:
    push esi  # 56
.globl _th10_00461708
_th10_00461708:
    push esi  # 56
.globl _th10_00461709
_th10_00461709:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_0046170c
_th10_0046170c:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046170f
_th10_0046170f:
    call dword ptr [_th10_004661c8]  # ff15c8614600
.globl _th10_00461715
_th10_00461715:
    {load} mov ebx, eax  # 8bd8
.globl _th10_00461717
_th10_00461717:
    {disp8} {store} mov [ebp-0x24], ebx  # 895ddc
.globl _th10_0046171a
_th10_0046171a:
    {load} cmp ebx, esi  # 3bde
.globl _th10_0046171c
_th10_0046171c:
    {disp8} jne _th10_00461725  # 7507
.globl _th10_0046171e
_th10_0046171e:
    {load} xor eax, eax  # 33c0
.globl _th10_00461720
_th10_00461720:
    {disp32} jmp _th10_004617cc  # e9a7000000
.globl _th10_00461725
_th10_00461725:
    {disp8} {store} mov [ebp-4], esi  # 8975fc
.globl _th10_00461728
_th10_00461728:
    lea eax, [ebx+ebx]  # 8d041b
.globl _th10_0046172b
_th10_0046172b:
    add eax, 3  # 83c003
.globl _th10_0046172e
_th10_0046172e:
    and eax, -4  # 83e0fc
.globl _th10_00461731
_th10_00461731:
    {disp32} call _th10_00458ec0  # e88a77ffff
.globl _th10_00461736
_th10_00461736:
    {disp8} {store} mov [ebp-0x18], esp  # 8965e8
.globl _th10_00461739
_th10_00461739:
    {load} mov edi, esp  # 8bfc
.globl _th10_0046173b
_th10_0046173b:
    {disp8} {store} mov [ebp-0x28], edi  # 897dd8
.globl _th10_0046173e
_th10_0046173e:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461742
_th10_00461742:
    {disp8} jmp _th10_0046175b  # eb17
.globl _th10_00461744
_th10_00461744:
    {load} xor eax, eax  # 33c0
.globl _th10_00461746
_th10_00461746:
    inc eax  # 40
.globl _th10_00461747
_th10_00461747:
    ret  # c3
.globl _th10_00461748
_th10_00461748:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_0046174b
_th10_0046174b:
    {disp32} call _th10_00458d91  # e84176ffff
.globl _th10_00461750
_th10_00461750:
    {load} xor esi, esi  # 33f6
.globl _th10_00461752
_th10_00461752:
    {load} xor edi, edi  # 33ff
.globl _th10_00461754
_th10_00461754:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461758
_th10_00461758:
    {disp8} {load} mov ebx, [ebp-0x24]  # 8b5ddc
.globl _th10_0046175b
_th10_0046175b:
    {load} cmp edi, esi  # 3bfe
.globl _th10_0046175d
_th10_0046175d:
    {disp8} jne _th10_00461776  # 7517
.globl _th10_0046175f
_th10_0046175f:
    lea eax, [ebx+ebx]  # 8d041b
.globl _th10_00461762
_th10_00461762:
    push eax  # 50
.globl _th10_00461763
_th10_00461763:
    {disp32} call _th10_00452706  # e89e0fffff
.globl _th10_00461768
_th10_00461768:
    pop ecx  # 59
.globl _th10_00461769
_th10_00461769:
    {load} mov edi, eax  # 8bf8
.globl _th10_0046176b
_th10_0046176b:
    {load} cmp edi, esi  # 3bfe
.globl _th10_0046176d
_th10_0046176d:
    {disp8} je _th10_0046171e  # 74af
.globl _th10_0046176f
_th10_0046176f:
    {disp8} {noimm8s} mov dword ptr [ebp-0x20], 1  # c745e001000000
.globl _th10_00461776
_th10_00461776:
    push ebx  # 53
.globl _th10_00461777
_th10_00461777:
    push edi  # 57
.globl _th10_00461778
_th10_00461778:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_0046177b
_th10_0046177b:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046177e
_th10_0046177e:
    call dword ptr [_th10_004661c8]  # ff15c8614600
.globl _th10_00461784
_th10_00461784:
    test eax, eax  # 85c0
.globl _th10_00461786
_th10_00461786:
    {disp8} je _th10_004617a9  # 7421
.globl _th10_00461788
_th10_00461788:
    push esi  # 56
.globl _th10_00461789
_th10_00461789:
    push esi  # 56
.globl _th10_0046178a
_th10_0046178a:
    {disp8} {store} cmp [ebp+0x14], esi  # 397514
.globl _th10_0046178d
_th10_0046178d:
    {disp8} jne _th10_00461793  # 7504
.globl _th10_0046178f
_th10_0046178f:
    push esi  # 56
.globl _th10_00461790
_th10_00461790:
    push esi  # 56
.globl _th10_00461791
_th10_00461791:
    {disp8} jmp _th10_00461799  # eb06
.globl _th10_00461793
_th10_00461793:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00461796
_th10_00461796:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_00461799
_th10_00461799:
    push -1  # 6aff
.globl _th10_0046179b
_th10_0046179b:
    push edi  # 57
.globl _th10_0046179c
_th10_0046179c:
    push esi  # 56
.globl _th10_0046179d
_th10_0046179d:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_004617a0
_th10_004617a0:
    call dword ptr [_th10_00466154]  # ff1554614600
.globl _th10_004617a6
_th10_004617a6:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_004617a9
_th10_004617a9:
    {disp8} {store} cmp [ebp-0x20], esi  # 3975e0
.globl _th10_004617ac
_th10_004617ac:
    {disp8} je _th10_004617b5  # 7407
.globl _th10_004617ae
_th10_004617ae:
    push edi  # 57
.globl _th10_004617af
_th10_004617af:
    {disp32} call _th10_00452422  # e86e0cffff
.globl _th10_004617b4
_th10_004617b4:
    pop ecx  # 59
.globl _th10_004617b5
_th10_004617b5:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_004617b8
_th10_004617b8:
    {disp8} jmp _th10_004617cc  # eb12
.globl _th10_004617ba
_th10_004617ba:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004617bd
_th10_004617bd:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004617c0
_th10_004617c0:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004617c3
_th10_004617c3:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_004617c6
_th10_004617c6:
    call dword ptr [_th10_0046605c]  # ff155c604600
.globl _th10_004617cc
_th10_004617cc:
    {disp8} lea esp, [ebp-0x34]  # 8d65cc
.globl _th10_004617cf
_th10_004617cf:
    {disp32} call _th10_00454bf7  # e82334ffff
.globl _th10_004617d4
_th10_004617d4:
    ret  # c3
# padding 004617d5..004617df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004617e0
_th10_004617e0:
    push ebp  # 55
.globl _th10_004617e1
_th10_004617e1:
    {load} mov ebp, esp  # 8bec
.globl _th10_004617e3
_th10_004617e3:
    push edi  # 57
.globl _th10_004617e4
_th10_004617e4:
    push esi  # 56
.globl _th10_004617e5
_th10_004617e5:
    push ebx  # 53
.globl _th10_004617e6
_th10_004617e6:
    {disp8} {load} mov ecx, [ebp+0x10]  # 8b4d10
.globl _th10_004617e9
_th10_004617e9:
    {load} or ecx, ecx  # 0bc9
.globl _th10_004617eb
_th10_004617eb:
    {disp8} je _th10_0046183a  # 744d
.globl _th10_004617ed
_th10_004617ed:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_004617f0
_th10_004617f0:
    {disp8} {load} mov edi, [ebp+0x0C]  # 8b7d0c
.globl _th10_004617f3
_th10_004617f3:
    mov bh, 0x41  # b741
.globl _th10_004617f5
_th10_004617f5:
    mov bl, 0x5A  # b35a
.globl _th10_004617f7
_th10_004617f7:
    mov dh, 0x20  # b620
.globl _th10_004617f9
_th10_004617f9:
    {disp8} lea ecx, [ecx]  # 8d4900
.globl _th10_004617fc
_th10_004617fc:
    {load} mov ah, [esi]  # 8a26
.globl _th10_004617fe
_th10_004617fe:
    {load} or ah, ah  # 0ae4
.globl _th10_00461800
_th10_00461800:
    {load} mov al, [edi]  # 8a07
.globl _th10_00461802
_th10_00461802:
    {disp8} je _th10_0046182b  # 7427
.globl _th10_00461804
_th10_00461804:
    {load} or al, al  # 0ac0
.globl _th10_00461806
_th10_00461806:
    {disp8} je _th10_0046182b  # 7423
.globl _th10_00461808
_th10_00461808:
    add esi, 1  # 83c601
.globl _th10_0046180b
_th10_0046180b:
    add edi, 1  # 83c701
.globl _th10_0046180e
_th10_0046180e:
    {store} cmp ah, bh  # 38fc
.globl _th10_00461810
_th10_00461810:
    {disp8} jb _th10_00461818  # 7206
.globl _th10_00461812
_th10_00461812:
    {store} cmp ah, bl  # 38dc
.globl _th10_00461814
_th10_00461814:
    {disp8} ja _th10_00461818  # 7702
.globl _th10_00461816
_th10_00461816:
    {load} add ah, dh  # 02e6
.globl _th10_00461818
_th10_00461818:
    {store} cmp al, bh  # 38f8
.globl _th10_0046181a
_th10_0046181a:
    {disp8} jb _th10_00461822  # 7206
.globl _th10_0046181c
_th10_0046181c:
    {store} cmp al, bl  # 38d8
.globl _th10_0046181e
_th10_0046181e:
    {disp8} ja _th10_00461822  # 7702
.globl _th10_00461820
_th10_00461820:
    {load} add al, dh  # 02c6
.globl _th10_00461822
_th10_00461822:
    {store} cmp ah, al  # 38c4
.globl _th10_00461824
_th10_00461824:
    {disp8} jne _th10_00461831  # 750b
.globl _th10_00461826
_th10_00461826:
    sub ecx, 1  # 83e901
.globl _th10_00461829
_th10_00461829:
    {disp8} jne _th10_004617fc  # 75d1
.globl _th10_0046182b
_th10_0046182b:
    {load} xor ecx, ecx  # 33c9
.globl _th10_0046182d
_th10_0046182d:
    {store} cmp ah, al  # 38c4
.globl _th10_0046182f
_th10_0046182f:
    {disp8} je _th10_0046183a  # 7409
.globl _th10_00461831
_th10_00461831:
    {noimm8s} mov ecx, 0x0FFFFFFFF  # b9ffffffff
.globl _th10_00461836
_th10_00461836:
    {disp8} jb _th10_0046183a  # 7202
.globl _th10_00461838
_th10_00461838:
    neg ecx  # f7d9
.globl _th10_0046183a
_th10_0046183a:
    {load} mov eax, ecx  # 8bc1
.globl _th10_0046183c
_th10_0046183c:
    pop ebx  # 5b
.globl _th10_0046183d
_th10_0046183d:
    pop esi  # 5e
.globl _th10_0046183e
_th10_0046183e:
    pop edi  # 5f
.globl _th10_0046183f
_th10_0046183f:
    leave  # c9
.globl _th10_00461840
_th10_00461840:
    ret  # c3
.globl _th10_00461841
_th10_00461841:
    push ebp  # 55
.globl _th10_00461842
_th10_00461842:
    {load} mov ebp, esp  # 8bec
.globl _th10_00461844
_th10_00461844:
    sub esp, 52  # 83ec34
.globl _th10_00461847
_th10_00461847:
    mov eax, [_th10_00473660]  # a160364700
.globl _th10_0046184c
_th10_0046184c:
    push ebx  # 53
.globl _th10_0046184d
_th10_0046184d:
    {disp8} {load} mov ebx, [ebp+0x1C]  # 8b5d1c
.globl _th10_00461850
_th10_00461850:
    push esi  # 56
.globl _th10_00461851
_th10_00461851:
    push edi  # 57
.globl _th10_00461852
_th10_00461852:
    {disp8} lea esi, [ebp+8]  # 8d7508
.globl _th10_00461855
_th10_00461855:
    {disp8} lea edi, [ebp-0x28]  # 8d7dd8
.globl _th10_00461858
_th10_00461858:
    movsd  # a5
.globl _th10_00461859
_th10_00461859:
    movsd  # a5
.globl _th10_0046185a
_th10_0046185a:
    {load} xor eax, ebp  # 33c5
.globl _th10_0046185c
_th10_0046185c:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_0046185f
_th10_0046185f:
    movsw  # 66a5
.globl _th10_00461861
_th10_00461861:
    {disp8} {load} mov eax, [ebp-0x20]  # 8b45e0
.globl _th10_00461864
_th10_00461864:
    {load} mov ecx, eax  # 8bc8
.globl _th10_00461866
_th10_00461866:
    {noimm8s} mov esi, 0x7FFF  # beff7f0000
.globl _th10_0046186b
_th10_0046186b:
    {noimm8s} and ecx, 0x8000  # 81e100800000
.globl _th10_00461871
_th10_00461871:
    {load} and eax, esi  # 23c6
.globl _th10_00461873
_th10_00461873:
    test cx, cx  # 6685c9
.globl _th10_00461876
_th10_00461876:
    {disp8} mov byte ptr [ebp-0x1C], 0x0CC  # c645e4cc
.globl _th10_0046187a
_th10_0046187a:
    {disp8} mov byte ptr [ebp-0x1B], 0x0CC  # c645e5cc
.globl _th10_0046187e
_th10_0046187e:
    {disp8} mov byte ptr [ebp-0x1A], 0x0CC  # c645e6cc
.globl _th10_00461882
_th10_00461882:
    {disp8} mov byte ptr [ebp-0x19], 0x0CC  # c645e7cc
.globl _th10_00461886
_th10_00461886:
    {disp8} mov byte ptr [ebp-0x18], 0x0CC  # c645e8cc
.globl _th10_0046188a
_th10_0046188a:
    {disp8} mov byte ptr [ebp-0x17], 0x0CC  # c645e9cc
.globl _th10_0046188e
_th10_0046188e:
    {disp8} mov byte ptr [ebp-0x16], 0x0CC  # c645eacc
.globl _th10_00461892
_th10_00461892:
    {disp8} mov byte ptr [ebp-0x15], 0x0CC  # c645ebcc
.globl _th10_00461896
_th10_00461896:
    {disp8} mov byte ptr [ebp-0x14], 0x0CC  # c645eccc
.globl _th10_0046189a
_th10_0046189a:
    {disp8} mov byte ptr [ebp-0x13], 0x0CC  # c645edcc
.globl _th10_0046189e
_th10_0046189e:
    {disp8} mov byte ptr [ebp-0x12], 0x0FB  # c645eefb
.globl _th10_004618a2
_th10_004618a2:
    {disp8} mov byte ptr [ebp-0x11], 0x3F  # c645ef3f
.globl _th10_004618a6
_th10_004618a6:
    {disp8} {noimm8s} mov dword ptr [ebp-0x30], 1  # c745d001000000
.globl _th10_004618ad
_th10_004618ad:
    {load} mov edx, eax  # 8bd0
.globl _th10_004618af
_th10_004618af:
    {disp8} je _th10_004618b7  # 7406
.globl _th10_004618b1
_th10_004618b1:
    {disp8} mov byte ptr [ebx+2], 0x2D  # c643022d
.globl _th10_004618b5
_th10_004618b5:
    {disp8} jmp _th10_004618bb  # eb04
.globl _th10_004618b7
_th10_004618b7:
    {disp8} mov byte ptr [ebx+2], 0x20  # c6430220
.globl _th10_004618bb
_th10_004618bb:
    test dx, dx  # 6685d2
.globl _th10_004618be
_th10_004618be:
    {disp8} {load} mov edi, [ebp-0x24]  # 8b7ddc
.globl _th10_004618c1
_th10_004618c1:
    {disp8} jne _th10_004618d0  # 750d
.globl _th10_004618c3
_th10_004618c3:
    test edi, edi  # 85ff
.globl _th10_004618c5
_th10_004618c5:
    {disp8} jne _th10_004618d0  # 7509
.globl _th10_004618c7
_th10_004618c7:
    {disp8} {store} cmp [ebp-0x28], edi  # 397dd8
.globl _th10_004618ca
_th10_004618ca:
    {disp32} je _th10_004619c3  # 0f84f3000000
.globl _th10_004618d0
_th10_004618d0:
    {load} cmp dx, si  # 663bd6
.globl _th10_004618d3
_th10_004618d3:
    {disp8} jne _th10_0046194d  # 7578
.globl _th10_004618d5
_th10_004618d5:
    {noimm8s} mov eax, 0x80000000  # b800000080
.globl _th10_004618da
_th10_004618da:
    {load} cmp edi, eax  # 3bf8
.globl _th10_004618dc
_th10_004618dc:
    {noimm8s} mov word ptr [ebx], 1  # 66c7030100
.globl _th10_004618e1
_th10_004618e1:
    {disp8} jne _th10_004618e9  # 7506
.globl _th10_004618e3
_th10_004618e3:
    {disp8} cmp dword ptr [ebp-0x28], 0  # 837dd800
.globl _th10_004618e7
_th10_004618e7:
    {disp8} je _th10_004618f8  # 740f
.globl _th10_004618e9
_th10_004618e9:
    {noimm8s} test edi, 0x40000000  # f7c700000040
.globl _th10_004618ef
_th10_004618ef:
    {disp8} jne _th10_004618f8  # 7507
.globl _th10_004618f1
_th10_004618f1:
    {noimm8s} push 0x46C9B4  # 68b4c94600
.globl _th10_004618f6
_th10_004618f6:
    {disp8} jmp _th10_0046193e  # eb46
.globl _th10_004618f8
_th10_004618f8:
    test cx, cx  # 6685c9
.globl _th10_004618fb
_th10_004618fb:
    {disp8} je _th10_00461912  # 7415
.globl _th10_004618fd
_th10_004618fd:
    {noimm8s} cmp edi, 0x0C0000000  # 81ff000000c0
.globl _th10_00461903
_th10_00461903:
    {disp8} jne _th10_00461912  # 750d
.globl _th10_00461905
_th10_00461905:
    {disp8} cmp dword ptr [ebp-0x28], 0  # 837dd800
.globl _th10_00461909
_th10_00461909:
    {disp8} jne _th10_00461939  # 752e
.globl _th10_0046190b
_th10_0046190b:
    {noimm8s} push 0x46C9AC  # 68acc94600
.globl _th10_00461910
_th10_00461910:
    {disp8} jmp _th10_00461921  # eb0f
.globl _th10_00461912
_th10_00461912:
    {load} cmp edi, eax  # 3bf8
.globl _th10_00461914
_th10_00461914:
    {disp8} jne _th10_00461939  # 7523
.globl _th10_00461916
_th10_00461916:
    {disp8} cmp dword ptr [ebp-0x28], 0  # 837dd800
.globl _th10_0046191a
_th10_0046191a:
    {disp8} jne _th10_00461939  # 751d
.globl _th10_0046191c
_th10_0046191c:
    {noimm8s} push 0x46C9A4  # 68a4c94600
.globl _th10_00461921
_th10_00461921:
    {disp8} lea eax, [ebx+4]  # 8d4304
.globl _th10_00461924
_th10_00461924:
    push eax  # 50
.globl _th10_00461925
_th10_00461925:
    {disp32} call _th10_0045bd80  # e856a4ffff
.globl _th10_0046192a
_th10_0046192a:
    {disp8} mov byte ptr [ebx+3], 5  # c6430305
.globl _th10_0046192e
_th10_0046192e:
    {disp8} and dword ptr [ebp-0x30], 0  # 8365d000
.globl _th10_00461932
_th10_00461932:
    pop ecx  # 59
.globl _th10_00461933
_th10_00461933:
    pop ecx  # 59
.globl _th10_00461934
_th10_00461934:
    {disp32} jmp _th10_00461aa5  # e96c010000
.globl _th10_00461939
_th10_00461939:
    {noimm8s} push 0x46C99C  # 689cc94600
.globl _th10_0046193e
_th10_0046193e:
    {disp8} lea eax, [ebx+4]  # 8d4304
.globl _th10_00461941
_th10_00461941:
    push eax  # 50
.globl _th10_00461942
_th10_00461942:
    {disp32} call _th10_0045bd80  # e839a4ffff
.globl _th10_00461947
_th10_00461947:
    {disp8} mov byte ptr [ebx+3], 6  # c6430306
.globl _th10_0046194b
_th10_0046194b:
    {disp8} jmp _th10_0046192e  # ebe1
.globl _th10_0046194d
_th10_0046194d:
    movzx eax, dx  # 0fb7c2
.globl _th10_00461950
_th10_00461950:
    {load} mov esi, eax  # 8bf0
.globl _th10_00461952
_th10_00461952:
    {noimm8s} imul eax, 0x4D10  # 69c0104d0000
.globl _th10_00461958
_th10_00461958:
    {disp8} and word ptr [ebp-0x10], 0  # 668365f000
.globl _th10_0046195d
_th10_0046195d:
    {load} mov ecx, edi  # 8bcf
.globl _th10_0046195f
_th10_0046195f:
    shr ecx, 0x18  # c1e918
.globl _th10_00461962
_th10_00461962:
    shr esi, 8  # c1ee08
.globl _th10_00461965
_th10_00461965:
    lea ecx, [esi+ecx*2]  # 8d0c4e
.globl _th10_00461968
_th10_00461968:
    imul ecx, 0x4D  # 6bc94d
.globl _th10_0046196b
_th10_0046196b:
    lea esi, [ecx+eax-0x134312F4]  # 8db4010cedbcec
.globl _th10_00461972
_th10_00461972:
    {disp8} {load} mov eax, [ebp-0x28]  # 8b45d8
.globl _th10_00461975
_th10_00461975:
    {disp8} {store} mov [ebp-0x0E], eax  # 8945f2
.globl _th10_00461978
_th10_00461978:
    sar esi, 0x10  # c1fe10
.globl _th10_0046197b
_th10_0046197b:
    movsx eax, si  # 0fbfc6
.globl _th10_0046197e
_th10_0046197e:
    neg eax  # f7d8
.globl _th10_00461980
_th10_00461980:
    push 1  # 6a01
.globl _th10_00461982
_th10_00461982:
    push eax  # 50
.globl _th10_00461983
_th10_00461983:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_00461986
_th10_00461986:
    push eax  # 50
.globl _th10_00461987
_th10_00461987:
    {disp8} {store} mov [ebp-6], dx  # 668955fa
.globl _th10_0046198b
_th10_0046198b:
    {disp8} {store} mov [ebp-0x0A], edi  # 897df6
.globl _th10_0046198e
_th10_0046198e:
    {disp32} call _th10_00460b90  # e8fdf1ffff
.globl _th10_00461993
_th10_00461993:
    add esp, 12  # 83c40c
.globl _th10_00461996
_th10_00461996:
    {disp8} {noimm8s} cmp word ptr [ebp-6], 0x3FFF  # 66817dfaff3f
.globl _th10_0046199c
_th10_0046199c:
    {disp8} jb _th10_004619ae  # 7210
.globl _th10_0046199e
_th10_0046199e:
    {disp8} lea eax, [ebp-0x1C]  # 8d45e4
.globl _th10_004619a1
_th10_004619a1:
    push eax  # 50
.globl _th10_004619a2
_th10_004619a2:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_004619a5
_th10_004619a5:
    push eax  # 50
.globl _th10_004619a6
_th10_004619a6:
    inc esi  # 46
.globl _th10_004619a7
_th10_004619a7:
    {disp32} call _th10_0046095a  # e8aeefffff
.globl _th10_004619ac
_th10_004619ac:
    pop ecx  # 59
.globl _th10_004619ad
_th10_004619ad:
    pop ecx  # 59
.globl _th10_004619ae
_th10_004619ae:
    {disp8} test byte ptr [ebp+0x18], 1  # f6451801
.globl _th10_004619b2
_th10_004619b2:
    {disp8} {load} mov edi, [ebp+0x14]  # 8b7d14
.globl _th10_004619b5
_th10_004619b5:
    {store} mov [ebx], si  # 668933
.globl _th10_004619b8
_th10_004619b8:
    {disp8} je _th10_004619cc  # 7412
.globl _th10_004619ba
_th10_004619ba:
    movsx eax, si  # 0fbfc6
.globl _th10_004619bd
_th10_004619bd:
    {load} add edi, eax  # 03f8
.globl _th10_004619bf
_th10_004619bf:
    test edi, edi  # 85ff
.globl _th10_004619c1
_th10_004619c1:
    {disp8} jg _th10_004619cc  # 7f09
.globl _th10_004619c3
_th10_004619c3:
    {disp8} mov byte ptr [ebx+4], 0x30  # c6430430
.globl _th10_004619c7
_th10_004619c7:
    {disp32} jmp _th10_00461ac8  # e9fc000000
.globl _th10_004619cc
_th10_004619cc:
    cmp edi, 21  # 83ff15
.globl _th10_004619cf
_th10_004619cf:
    {disp8} jle _th10_004619d4  # 7e03
.globl _th10_004619d1
_th10_004619d1:
    push 21  # 6a15
.globl _th10_004619d3
_th10_004619d3:
    pop edi  # 5f
.globl _th10_004619d4
_th10_004619d4:
    {disp8} movzx esi, word ptr [ebp-6]  # 0fb775fa
.globl _th10_004619d8
_th10_004619d8:
    {noimm8s} sub esi, 0x3FFE  # 81eefe3f0000
.globl _th10_004619de
_th10_004619de:
    {disp8} and word ptr [ebp-6], 0  # 668365fa00
.globl _th10_004619e3
_th10_004619e3:
    {disp8} {noimm8s} mov dword ptr [ebp-0x2C], 8  # c745d408000000
.globl _th10_004619ea
_th10_004619ea:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_004619ed
_th10_004619ed:
    push eax  # 50
.globl _th10_004619ee
_th10_004619ee:
    {disp32} call _th10_00460817  # e824eeffff
.globl _th10_004619f3
_th10_004619f3:
    {disp8} dec dword ptr [ebp-0x2C]  # ff4dd4
.globl _th10_004619f6
_th10_004619f6:
    pop ecx  # 59
.globl _th10_004619f7
_th10_004619f7:
    {disp8} jne _th10_004619ea  # 75f1
.globl _th10_004619f9
_th10_004619f9:
    test esi, esi  # 85f6
.globl _th10_004619fb
_th10_004619fb:
    {disp8} jge _th10_00461a14  # 7d17
.globl _th10_004619fd
_th10_004619fd:
    neg esi  # f7de
.globl _th10_004619ff
_th10_004619ff:
    {noimm8s} and esi, 0x0FF  # 81e6ff000000
.globl _th10_00461a05
_th10_00461a05:
    {disp8} jle _th10_00461a14  # 7e0d
.globl _th10_00461a07
_th10_00461a07:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_00461a0a
_th10_00461a0a:
    push eax  # 50
.globl _th10_00461a0b
_th10_00461a0b:
    {disp32} call _th10_00460845  # e835eeffff
.globl _th10_00461a10
_th10_00461a10:
    dec esi  # 4e
.globl _th10_00461a11
_th10_00461a11:
    pop ecx  # 59
.globl _th10_00461a12
_th10_00461a12:
    {disp8} jne _th10_00461a07  # 75f3
.globl _th10_00461a14
_th10_00461a14:
    {disp8} lea ecx, [edi+1]  # 8d4f01
.globl _th10_00461a17
_th10_00461a17:
    test ecx, ecx  # 85c9
.globl _th10_00461a19
_th10_00461a19:
    {disp8} lea eax, [ebx+4]  # 8d4304
.globl _th10_00461a1c
_th10_00461a1c:
    {disp8} {store} mov [ebp-0x2C], eax  # 8945d4
.globl _th10_00461a1f
_th10_00461a1f:
    {disp8} jle _th10_00461a71  # 7e50
.globl _th10_00461a21
_th10_00461a21:
    {disp8} {store} mov [ebp-0x34], ecx  # 894dcc
.globl _th10_00461a24
_th10_00461a24:
    {disp8} lea esi, [ebp-0x10]  # 8d75f0
.globl _th10_00461a27
_th10_00461a27:
    {disp8} lea edi, [ebp-0x28]  # 8d7dd8
.globl _th10_00461a2a
_th10_00461a2a:
    movsd  # a5
.globl _th10_00461a2b
_th10_00461a2b:
    movsd  # a5
.globl _th10_00461a2c
_th10_00461a2c:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_00461a2f
_th10_00461a2f:
    push eax  # 50
.globl _th10_00461a30
_th10_00461a30:
    movsd  # a5
.globl _th10_00461a31
_th10_00461a31:
    {disp32} call _th10_00460817  # e8e1edffff
.globl _th10_00461a36
_th10_00461a36:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_00461a39
_th10_00461a39:
    push eax  # 50
.globl _th10_00461a3a
_th10_00461a3a:
    {disp32} call _th10_00460817  # e8d8edffff
.globl _th10_00461a3f
_th10_00461a3f:
    {disp8} lea eax, [ebp-0x28]  # 8d45d8
.globl _th10_00461a42
_th10_00461a42:
    push eax  # 50
.globl _th10_00461a43
_th10_00461a43:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_00461a46
_th10_00461a46:
    push eax  # 50
.globl _th10_00461a47
_th10_00461a47:
    {disp32} call _th10_004607b9  # e86dedffff
.globl _th10_00461a4c
_th10_00461a4c:
    {disp8} lea eax, [ebp-0x10]  # 8d45f0
.globl _th10_00461a4f
_th10_00461a4f:
    push eax  # 50
.globl _th10_00461a50
_th10_00461a50:
    {disp32} call _th10_00460817  # e8c2edffff
.globl _th10_00461a55
_th10_00461a55:
    {disp8} {load} mov al, [ebp-5]  # 8a45fb
.globl _th10_00461a58
_th10_00461a58:
    {disp8} {load} mov ecx, [ebp-0x2C]  # 8b4dd4
.globl _th10_00461a5b
_th10_00461a5b:
    add al, 0x30  # 0430
.globl _th10_00461a5d
_th10_00461a5d:
    add esp, 20  # 83c414
.globl _th10_00461a60
_th10_00461a60:
    {disp8} inc dword ptr [ebp-0x2C]  # ff45d4
.globl _th10_00461a63
_th10_00461a63:
    {disp8} dec dword ptr [ebp-0x34]  # ff4dcc
.globl _th10_00461a66
_th10_00461a66:
    {store} mov [ecx], al  # 8801
.globl _th10_00461a68
_th10_00461a68:
    {disp8} mov byte ptr [ebp-5], 0  # c645fb00
.globl _th10_00461a6c
_th10_00461a6c:
    {disp8} jne _th10_00461a24  # 75b6
.globl _th10_00461a6e
_th10_00461a6e:
    {disp8} {load} mov eax, [ebp-0x2C]  # 8b45d4
.globl _th10_00461a71
_th10_00461a71:
    dec eax  # 48
.globl _th10_00461a72
_th10_00461a72:
    {load} mov cl, [eax]  # 8a08
.globl _th10_00461a74
_th10_00461a74:
    dec eax  # 48
.globl _th10_00461a75
_th10_00461a75:
    cmp cl, 0x35  # 80f935
.globl _th10_00461a78
_th10_00461a78:
    {disp8} lea ecx, [ebx+4]  # 8d4b04
.globl _th10_00461a7b
_th10_00461a7b:
    {disp8} jl _th10_00461abd  # 7c40
.globl _th10_00461a7d
_th10_00461a7d:
    {disp8} jmp _th10_00461a88  # eb09
.globl _th10_00461a7f
_th10_00461a7f:
    cmp byte ptr [eax], 0x39  # 803839
.globl _th10_00461a82
_th10_00461a82:
    {disp8} jne _th10_00461a8c  # 7508
.globl _th10_00461a84
_th10_00461a84:
    mov byte ptr [eax], 0x30  # c60030
.globl _th10_00461a87
_th10_00461a87:
    dec eax  # 48
.globl _th10_00461a88
_th10_00461a88:
    {load} cmp eax, ecx  # 3bc1
.globl _th10_00461a8a
_th10_00461a8a:
    {disp8} jae _th10_00461a7f  # 73f3
.globl _th10_00461a8c
_th10_00461a8c:
    {load} cmp eax, ecx  # 3bc1
.globl _th10_00461a8e
_th10_00461a8e:
    {disp8} jae _th10_00461a94  # 7304
.globl _th10_00461a90
_th10_00461a90:
    inc eax  # 40
.globl _th10_00461a91
_th10_00461a91:
    inc word ptr [ebx]  # 66ff03
.globl _th10_00461a94
_th10_00461a94:
    inc byte ptr [eax]  # fe00
.globl _th10_00461a96
_th10_00461a96:
    {load} sub al, bl  # 2ac3
.globl _th10_00461a98
_th10_00461a98:
    sub al, 3  # 2c03
.globl _th10_00461a9a
_th10_00461a9a:
    {disp8} {store} mov [ebx+3], al  # 884303
.globl _th10_00461a9d
_th10_00461a9d:
    movsx eax, al  # 0fbec0
.globl _th10_00461aa0
_th10_00461aa0:
    {disp8} mov byte ptr [eax+ebx+4], 0  # c644180400
.globl _th10_00461aa5
_th10_00461aa5:
    {disp8} {load} mov eax, [ebp-0x30]  # 8b45d0
.globl _th10_00461aa8
_th10_00461aa8:
    {disp8} {load} mov ecx, [ebp-4]  # 8b4dfc
.globl _th10_00461aab
_th10_00461aab:
    pop edi  # 5f
.globl _th10_00461aac
_th10_00461aac:
    pop esi  # 5e
.globl _th10_00461aad
_th10_00461aad:
    {load} xor ecx, ebp  # 33cd
.globl _th10_00461aaf
_th10_00461aaf:
    pop ebx  # 5b
.globl _th10_00461ab0
_th10_00461ab0:
    {disp32} call _th10_00458ea5  # e8f073ffff
.globl _th10_00461ab5
_th10_00461ab5:
    leave  # c9
.globl _th10_00461ab6
_th10_00461ab6:
    ret  # c3
.globl _th10_00461ab7
_th10_00461ab7:
    cmp byte ptr [eax], 0x30  # 803830
.globl _th10_00461aba
_th10_00461aba:
    {disp8} jne _th10_00461ac1  # 7505
.globl _th10_00461abc
_th10_00461abc:
    dec eax  # 48
.globl _th10_00461abd
_th10_00461abd:
    {load} cmp eax, ecx  # 3bc1
.globl _th10_00461abf
_th10_00461abf:
    {disp8} jae _th10_00461ab7  # 73f6
.globl _th10_00461ac1
_th10_00461ac1:
    {load} cmp eax, ecx  # 3bc1
.globl _th10_00461ac3
_th10_00461ac3:
    {disp8} jae _th10_00461a96  # 73d1
.globl _th10_00461ac5
_th10_00461ac5:
    mov byte ptr [ecx], 0x30  # c60130
.globl _th10_00461ac8
_th10_00461ac8:
    and word ptr [ebx], 0  # 66832300
.globl _th10_00461acc
_th10_00461acc:
    {load} xor eax, eax  # 33c0
.globl _th10_00461ace
_th10_00461ace:
    {disp8} mov byte ptr [ebx+2], 0x20  # c6430220
.globl _th10_00461ad2
_th10_00461ad2:
    {disp8} mov byte ptr [ebx+3], 1  # c6430301
.globl _th10_00461ad6
_th10_00461ad6:
    {disp8} mov byte ptr [ebx+5], 0  # c6430500
.globl _th10_00461ada
_th10_00461ada:
    inc eax  # 40
.globl _th10_00461adb
_th10_00461adb:
    {disp8} jmp _th10_00461aa8  # ebcb
.globl _th10_00461add
_th10_00461add:
    {disp8} {load} mov ecx, [esp+4]  # 8b4c2404
.globl _th10_00461ae1
_th10_00461ae1:
    test ecx, ecx  # 85c9
.globl _th10_00461ae3
_th10_00461ae3:
    {disp8} je _th10_00461af0  # 740b
.globl _th10_00461ae5
_th10_00461ae5:
    dec ecx  # 49
.globl _th10_00461ae6
_th10_00461ae6:
    cmp byte ptr [eax], 0  # 803800
.globl _th10_00461ae9
_th10_00461ae9:
    {disp8} je _th10_00461af1  # 7406
.globl _th10_00461aeb
_th10_00461aeb:
    inc eax  # 40
.globl _th10_00461aec
_th10_00461aec:
    test ecx, ecx  # 85c9
.globl _th10_00461aee
_th10_00461aee:
    {disp8} jne _th10_00461ae5  # 75f5
.globl _th10_00461af0
_th10_00461af0:
    dec ecx  # 49
.globl _th10_00461af1
_th10_00461af1:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00461af5
_th10_00461af5:
    {load} sub eax, ecx  # 2bc1
.globl _th10_00461af7
_th10_00461af7:
    dec eax  # 48
.globl _th10_00461af8
_th10_00461af8:
    ret  # c3
.globl _th10_00461af9
_th10_00461af9:
    push 72  # 6a48
.globl _th10_00461afb
_th10_00461afb:
    {noimm8s} push 0x46C9C0  # 68c0c94600
.globl _th10_00461b00
_th10_00461b00:
    {disp32} call _th10_00454bbc  # e8b730ffff
.globl _th10_00461b05
_th10_00461b05:
    mov eax, [_th10_00473660]  # a160364700
.globl _th10_00461b0a
_th10_00461b0a:
    {load} xor eax, ebp  # 33c5
.globl _th10_00461b0c
_th10_00461b0c:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_00461b0f
_th10_00461b0f:
    {disp8} {load} mov esi, [ebp+0x10]  # 8b7510
.globl _th10_00461b12
_th10_00461b12:
    {disp8} {store} mov [ebp-0x3C], esi  # 8975c4
.globl _th10_00461b15
_th10_00461b15:
    {disp8} {load} mov ebx, [ebp+0x18]  # 8b5d18
.globl _th10_00461b18
_th10_00461b18:
    {disp8} {store} mov [ebp-0x34], ebx  # 895dcc
.globl _th10_00461b1b
_th10_00461b1b:
    {load} xor edi, edi  # 33ff
.globl _th10_00461b1d
_th10_00461b1d:
    {store} cmp [_th10_004776d4], edi  # 393dd4764700
.globl _th10_00461b23
_th10_00461b23:
    {disp8} jne _th10_00461b5d  # 7538
.globl _th10_00461b25
_th10_00461b25:
    push 1  # 6a01
.globl _th10_00461b27
_th10_00461b27:
    {noimm8s} mov eax, 0x46B5C4  # b8c4b54600
.globl _th10_00461b2c
_th10_00461b2c:
    push eax  # 50
.globl _th10_00461b2d
_th10_00461b2d:
    push 1  # 6a01
.globl _th10_00461b2f
_th10_00461b2f:
    push eax  # 50
.globl _th10_00461b30
_th10_00461b30:
    push edi  # 57
.globl _th10_00461b31
_th10_00461b31:
    push edi  # 57
.globl _th10_00461b32
_th10_00461b32:
    call dword ptr [_th10_004661d0]  # ff15d0614600
.globl _th10_00461b38
_th10_00461b38:
    test eax, eax  # 85c0
.globl _th10_00461b3a
_th10_00461b3a:
    {disp8} je _th10_00461b48  # 740c
.globl _th10_00461b3c
_th10_00461b3c:
    {noimm8s} mov dword ptr [_th10_004776d4], 1  # c705d476470001000000
.globl _th10_00461b46
_th10_00461b46:
    {disp8} jmp _th10_00461b5d  # eb15
.globl _th10_00461b48
_th10_00461b48:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_00461b4e
_th10_00461b4e:
    cmp eax, 120  # 83f878
.globl _th10_00461b51
_th10_00461b51:
    {disp8} jne _th10_00461b5d  # 750a
.globl _th10_00461b53
_th10_00461b53:
    {noimm8s} mov dword ptr [_th10_004776d4], 2  # c705d476470002000000
.globl _th10_00461b5d
_th10_00461b5d:
    {disp8} {store} cmp [ebp+0x14], edi  # 397d14
.globl _th10_00461b60
_th10_00461b60:
    {disp8} jle _th10_00461b70  # 7e0e
.globl _th10_00461b62
_th10_00461b62:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00461b65
_th10_00461b65:
    {load} mov eax, esi  # 8bc6
.globl _th10_00461b67
_th10_00461b67:
    {disp32} call _th10_00461add  # e871ffffff
.globl _th10_00461b6c
_th10_00461b6c:
    pop ecx  # 59
.globl _th10_00461b6d
_th10_00461b6d:
    {disp8} {store} mov [ebp+0x14], eax  # 894514
.globl _th10_00461b70
_th10_00461b70:
    {disp8} {load} mov eax, [ebp+0x1C]  # 8b451c
.globl _th10_00461b73
_th10_00461b73:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00461b75
_th10_00461b75:
    {disp8} jle _th10_00461b83  # 7e0c
.globl _th10_00461b77
_th10_00461b77:
    push eax  # 50
.globl _th10_00461b78
_th10_00461b78:
    {load} mov eax, ebx  # 8bc3
.globl _th10_00461b7a
_th10_00461b7a:
    {disp32} call _th10_00461add  # e85effffff
.globl _th10_00461b7f
_th10_00461b7f:
    pop ecx  # 59
.globl _th10_00461b80
_th10_00461b80:
    {disp8} {store} mov [ebp+0x1C], eax  # 89451c
.globl _th10_00461b83
_th10_00461b83:
    {load} mov ecx, [_th10_004776d4]  # 8b0dd4764700
.globl _th10_00461b89
_th10_00461b89:
    cmp ecx, 2  # 83f902
.globl _th10_00461b8c
_th10_00461b8c:
    {disp32} je _th10_00461dc2  # 0f8430020000
.globl _th10_00461b92
_th10_00461b92:
    {load} cmp ecx, edi  # 3bcf
.globl _th10_00461b94
_th10_00461b94:
    {disp32} je _th10_00461dc2  # 0f8428020000
.globl _th10_00461b9a
_th10_00461b9a:
    {load} xor edx, edx  # 33d2
.globl _th10_00461b9c
_th10_00461b9c:
    inc edx  # 42
.globl _th10_00461b9d
_th10_00461b9d:
    {load} cmp ecx, edx  # 3bca
.globl _th10_00461b9f
_th10_00461b9f:
    {disp32} jne _th10_00461def  # 0f854a020000
.globl _th10_00461ba5
_th10_00461ba5:
    {disp8} {store} mov [ebp-0x50], edi  # 897db0
.globl _th10_00461ba8
_th10_00461ba8:
    {disp8} {store} mov [ebp-0x44], edi  # 897dbc
.globl _th10_00461bab
_th10_00461bab:
    {disp8} {store} mov [ebp-0x48], edi  # 897db8
.globl _th10_00461bae
_th10_00461bae:
    {disp8} {store} cmp [ebp+0x20], edi  # 397d20
.globl _th10_00461bb1
_th10_00461bb1:
    {disp8} jne _th10_00461bbc  # 7509
.globl _th10_00461bb3
_th10_00461bb3:
    {load} mov ecx, [_th10_00477664]  # 8b0d64764700
.globl _th10_00461bb9
_th10_00461bb9:
    {disp8} {store} mov [ebp+0x20], ecx  # 894d20
.globl _th10_00461bbc
_th10_00461bbc:
    {disp8} {store} cmp [ebp+0x14], edi  # 397d14
.globl _th10_00461bbf
_th10_00461bbf:
    {disp8} je _th10_00461bc9  # 7408
.globl _th10_00461bc1
_th10_00461bc1:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00461bc3
_th10_00461bc3:
    {disp32} jne _th10_00461c65  # 0f859c000000
.globl _th10_00461bc9
_th10_00461bc9:
    {disp8} {store} cmp [ebp+0x14], eax  # 394514
.globl _th10_00461bcc
_th10_00461bcc:
    {disp8} jne _th10_00461bd6  # 7508
.globl _th10_00461bce
_th10_00461bce:
    push 2  # 6a02
.globl _th10_00461bd0
_th10_00461bd0:
    pop eax  # 58
.globl _th10_00461bd1
_th10_00461bd1:
    {disp32} jmp _th10_00461e70  # e99a020000
.globl _th10_00461bd6
_th10_00461bd6:
    {load} cmp eax, edx  # 3bc2
.globl _th10_00461bd8
_th10_00461bd8:
    {disp8} jle _th10_00461be1  # 7e07
.globl _th10_00461bda
_th10_00461bda:
    {load} mov eax, edx  # 8bc2
.globl _th10_00461bdc
_th10_00461bdc:
    {disp32} jmp _th10_00461e70  # e98f020000
.globl _th10_00461be1
_th10_00461be1:
    {disp8} {store} cmp [ebp+0x14], edx  # 395514
.globl _th10_00461be4
_th10_00461be4:
    {disp8} jg _th10_00461c27  # 7f41
.globl _th10_00461be6
_th10_00461be6:
    {disp8} lea eax, [ebp-0x30]  # 8d45d0
.globl _th10_00461be9
_th10_00461be9:
    push eax  # 50
.globl _th10_00461bea
_th10_00461bea:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00461bed
_th10_00461bed:
    call dword ptr [_th10_00466064]  # ff1564604600
.globl _th10_00461bf3
_th10_00461bf3:
    test eax, eax  # 85c0
.globl _th10_00461bf5
_th10_00461bf5:
    {disp32} je _th10_00461def  # 0f84f4010000
.globl _th10_00461bfb
_th10_00461bfb:
    {disp8} {store} cmp [ebp+0x14], edi  # 397d14
.globl _th10_00461bfe
_th10_00461bfe:
    {disp8} jle _th10_00461c2b  # 7e2b
.globl _th10_00461c00
_th10_00461c00:
    {disp8} cmp dword ptr [ebp-0x30], 2  # 837dd002
.globl _th10_00461c04
_th10_00461c04:
    {disp8} jb _th10_00461c27  # 7221
.globl _th10_00461c06
_th10_00461c06:
    {disp8} lea eax, [ebp-0x2A]  # 8d45d6
.globl _th10_00461c09
_th10_00461c09:
    {disp8} cmp byte ptr [ebp-0x2A], 0  # 807dd600
.globl _th10_00461c0d
_th10_00461c0d:
    {disp8} je _th10_00461c27  # 7418
.globl _th10_00461c0f
_th10_00461c0f:
    {disp8} {load} mov dl, [eax+1]  # 8a5001
.globl _th10_00461c12
_th10_00461c12:
    test dl, dl  # 84d2
.globl _th10_00461c14
_th10_00461c14:
    {disp8} je _th10_00461c27  # 7411
.globl _th10_00461c16
_th10_00461c16:
    {load} mov cl, [esi]  # 8a0e
.globl _th10_00461c18
_th10_00461c18:
    {load} cmp cl, [eax]  # 3a08
.globl _th10_00461c1a
_th10_00461c1a:
    {disp8} jb _th10_00461c20  # 7204
.globl _th10_00461c1c
_th10_00461c1c:
    {load} cmp cl, dl  # 3aca
.globl _th10_00461c1e
_th10_00461c1e:
    {disp8} jbe _th10_00461bce  # 76ae
.globl _th10_00461c20
_th10_00461c20:
    inc eax  # 40
.globl _th10_00461c21
_th10_00461c21:
    inc eax  # 40
.globl _th10_00461c22
_th10_00461c22:
    cmp byte ptr [eax], 0  # 803800
.globl _th10_00461c25
_th10_00461c25:
    {disp8} jne _th10_00461c0f  # 75e8
.globl _th10_00461c27
_th10_00461c27:
    push 3  # 6a03
.globl _th10_00461c29
_th10_00461c29:
    {disp8} jmp _th10_00461bd0  # eba5
.globl _th10_00461c2b
_th10_00461c2b:
    {disp8} {store} cmp [ebp+0x1C], edi  # 397d1c
.globl _th10_00461c2e
_th10_00461c2e:
    {disp8} jle _th10_00461c65  # 7e35
.globl _th10_00461c30
_th10_00461c30:
    {disp8} cmp dword ptr [ebp-0x30], 2  # 837dd002
.globl _th10_00461c34
_th10_00461c34:
    {disp8} jae _th10_00461c3e  # 7308
.globl _th10_00461c36
_th10_00461c36:
    {load} xor eax, eax  # 33c0
.globl _th10_00461c38
_th10_00461c38:
    inc eax  # 40
.globl _th10_00461c39
_th10_00461c39:
    {disp32} jmp _th10_00461e70  # e932020000
.globl _th10_00461c3e
_th10_00461c3e:
    {disp8} lea eax, [ebp-0x2A]  # 8d45d6
.globl _th10_00461c41
_th10_00461c41:
    {disp8} cmp byte ptr [ebp-0x2A], 0  # 807dd600
.globl _th10_00461c45
_th10_00461c45:
    {disp8} je _th10_00461c36  # 74ef
.globl _th10_00461c47
_th10_00461c47:
    {disp8} {load} mov dl, [eax+1]  # 8a5001
.globl _th10_00461c4a
_th10_00461c4a:
    test dl, dl  # 84d2
.globl _th10_00461c4c
_th10_00461c4c:
    {disp8} je _th10_00461c36  # 74e8
.globl _th10_00461c4e
_th10_00461c4e:
    {load} mov cl, [ebx]  # 8a0b
.globl _th10_00461c50
_th10_00461c50:
    {load} cmp cl, [eax]  # 3a08
.globl _th10_00461c52
_th10_00461c52:
    {disp8} jb _th10_00461c5c  # 7208
.globl _th10_00461c54
_th10_00461c54:
    {load} cmp cl, dl  # 3aca
.globl _th10_00461c56
_th10_00461c56:
    {disp32} jbe _th10_00461bce  # 0f8672ffffff
.globl _th10_00461c5c
_th10_00461c5c:
    inc eax  # 40
.globl _th10_00461c5d
_th10_00461c5d:
    inc eax  # 40
.globl _th10_00461c5e
_th10_00461c5e:
    cmp byte ptr [eax], 0  # 803800
.globl _th10_00461c61
_th10_00461c61:
    {disp8} jne _th10_00461c47  # 75e4
.globl _th10_00461c63
_th10_00461c63:
    {disp8} jmp _th10_00461c36  # ebd1
.globl _th10_00461c65
_th10_00461c65:
    push edi  # 57
.globl _th10_00461c66
_th10_00461c66:
    push edi  # 57
.globl _th10_00461c67
_th10_00461c67:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00461c6a
_th10_00461c6a:
    push esi  # 56
.globl _th10_00461c6b
_th10_00461c6b:
    push 9  # 6a09
.globl _th10_00461c6d
_th10_00461c6d:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00461c70
_th10_00461c70:
    call dword ptr [_th10_00466104]  # ff1504614600
.globl _th10_00461c76
_th10_00461c76:
    {load} mov ebx, eax  # 8bd8
.globl _th10_00461c78
_th10_00461c78:
    {disp8} {store} mov [ebp-0x4C], ebx  # 895db4
.globl _th10_00461c7b
_th10_00461c7b:
    {load} cmp ebx, edi  # 3bdf
.globl _th10_00461c7d
_th10_00461c7d:
    {disp32} je _th10_00461def  # 0f846c010000
.globl _th10_00461c83
_th10_00461c83:
    {disp8} {store} mov [ebp-4], edi  # 897dfc
.globl _th10_00461c86
_th10_00461c86:
    lea eax, [ebx+ebx]  # 8d041b
.globl _th10_00461c89
_th10_00461c89:
    add eax, 3  # 83c003
.globl _th10_00461c8c
_th10_00461c8c:
    and eax, -4  # 83e0fc
.globl _th10_00461c8f
_th10_00461c8f:
    {disp32} call _th10_00458ec0  # e82c72ffff
.globl _th10_00461c94
_th10_00461c94:
    {disp8} {store} mov [ebp-0x18], esp  # 8965e8
.globl _th10_00461c97
_th10_00461c97:
    {load} mov eax, esp  # 8bc4
.globl _th10_00461c99
_th10_00461c99:
    {disp8} {store} mov [ebp-0x38], eax  # 8945c8
.globl _th10_00461c9c
_th10_00461c9c:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461ca0
_th10_00461ca0:
    {disp8} jmp _th10_00461cbe  # eb1c
.globl _th10_00461ca2
_th10_00461ca2:
    {load} xor eax, eax  # 33c0
.globl _th10_00461ca4
_th10_00461ca4:
    inc eax  # 40
.globl _th10_00461ca5
_th10_00461ca5:
    ret  # c3
.globl _th10_00461ca6
_th10_00461ca6:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00461ca9
_th10_00461ca9:
    {disp32} call _th10_00458d91  # e8e370ffff
.globl _th10_00461cae
_th10_00461cae:
    {disp8} and dword ptr [ebp-0x38], 0  # 8365c800
.globl _th10_00461cb2
_th10_00461cb2:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461cb6
_th10_00461cb6:
    {disp8} {load} mov ebx, [ebp-0x4C]  # 8b5db4
.globl _th10_00461cb9
_th10_00461cb9:
    {load} xor edi, edi  # 33ff
.globl _th10_00461cbb
_th10_00461cbb:
    {disp8} {load} mov esi, [ebp-0x3C]  # 8b75c4
.globl _th10_00461cbe
_th10_00461cbe:
    {disp8} {load} mov eax, [ebp-0x38]  # 8b45c8
.globl _th10_00461cc1
_th10_00461cc1:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00461cc3
_th10_00461cc3:
    {disp8} jne _th10_00461ce1  # 751c
.globl _th10_00461cc5
_th10_00461cc5:
    lea eax, [ebx+ebx]  # 8d041b
.globl _th10_00461cc8
_th10_00461cc8:
    push eax  # 50
.globl _th10_00461cc9
_th10_00461cc9:
    {disp32} call _th10_00452706  # e8380affff
.globl _th10_00461cce
_th10_00461cce:
    pop ecx  # 59
.globl _th10_00461ccf
_th10_00461ccf:
    {disp8} {store} mov [ebp-0x38], eax  # 8945c8
.globl _th10_00461cd2
_th10_00461cd2:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00461cd4
_th10_00461cd4:
    {disp32} je _th10_00461def  # 0f8415010000
.globl _th10_00461cda
_th10_00461cda:
    {disp8} {noimm8s} mov dword ptr [ebp-0x50], 1  # c745b001000000
.globl _th10_00461ce1
_th10_00461ce1:
    push ebx  # 53
.globl _th10_00461ce2
_th10_00461ce2:
    push eax  # 50
.globl _th10_00461ce3
_th10_00461ce3:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00461ce6
_th10_00461ce6:
    push esi  # 56
.globl _th10_00461ce7
_th10_00461ce7:
    push 1  # 6a01
.globl _th10_00461ce9
_th10_00461ce9:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00461cec
_th10_00461cec:
    call dword ptr [_th10_00466104]  # ff1504614600
.globl _th10_00461cf2
_th10_00461cf2:
    test eax, eax  # 85c0
.globl _th10_00461cf4
_th10_00461cf4:
    {disp32} je _th10_00461dab  # 0f84b1000000
.globl _th10_00461cfa
_th10_00461cfa:
    push 0  # 6a00
.globl _th10_00461cfc
_th10_00461cfc:
    push 0  # 6a00
.globl _th10_00461cfe
_th10_00461cfe:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_00461d01
_th10_00461d01:
    {disp8} push dword ptr [ebp-0x34]  # ff75cc
.globl _th10_00461d04
_th10_00461d04:
    push 9  # 6a09
.globl _th10_00461d06
_th10_00461d06:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00461d09
_th10_00461d09:
    call dword ptr [_th10_00466104]  # ff1504614600
.globl _th10_00461d0f
_th10_00461d0f:
    {load} mov esi, eax  # 8bf0
.globl _th10_00461d11
_th10_00461d11:
    {disp8} {store} mov [ebp-0x54], esi  # 8975ac
.globl _th10_00461d14
_th10_00461d14:
    test esi, esi  # 85f6
.globl _th10_00461d16
_th10_00461d16:
    {disp32} je _th10_00461dab  # 0f848f000000
.globl _th10_00461d1c
_th10_00461d1c:
    {disp8} {noimm8s} mov dword ptr [ebp-4], 1  # c745fc01000000
.globl _th10_00461d23
_th10_00461d23:
    lea eax, [esi+esi]  # 8d0436
.globl _th10_00461d26
_th10_00461d26:
    add eax, 3  # 83c003
.globl _th10_00461d29
_th10_00461d29:
    and eax, -4  # 83e0fc
.globl _th10_00461d2c
_th10_00461d2c:
    {disp32} call _th10_00458ec0  # e88f71ffff
.globl _th10_00461d31
_th10_00461d31:
    {disp8} {store} mov [ebp-0x18], esp  # 8965e8
.globl _th10_00461d34
_th10_00461d34:
    {load} mov edi, esp  # 8bfc
.globl _th10_00461d36
_th10_00461d36:
    {disp8} {store} mov [ebp-0x58], edi  # 897da8
.globl _th10_00461d39
_th10_00461d39:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461d3d
_th10_00461d3d:
    {disp8} jmp _th10_00461d57  # eb18
.globl _th10_00461d3f
_th10_00461d3f:
    {load} xor eax, eax  # 33c0
.globl _th10_00461d41
_th10_00461d41:
    inc eax  # 40
.globl _th10_00461d42
_th10_00461d42:
    ret  # c3
.globl _th10_00461d43
_th10_00461d43:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00461d46
_th10_00461d46:
    {disp32} call _th10_00458d91  # e84670ffff
.globl _th10_00461d4b
_th10_00461d4b:
    {load} xor edi, edi  # 33ff
.globl _th10_00461d4d
_th10_00461d4d:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00461d51
_th10_00461d51:
    {disp8} {load} mov ebx, [ebp-0x4C]  # 8b5db4
.globl _th10_00461d54
_th10_00461d54:
    {disp8} {load} mov esi, [ebp-0x54]  # 8b75ac
.globl _th10_00461d57
_th10_00461d57:
    test edi, edi  # 85ff
.globl _th10_00461d59
_th10_00461d59:
    {disp8} jne _th10_00461d72  # 7517
.globl _th10_00461d5b
_th10_00461d5b:
    lea eax, [esi+esi]  # 8d0436
.globl _th10_00461d5e
_th10_00461d5e:
    push eax  # 50
.globl _th10_00461d5f
_th10_00461d5f:
    {disp32} call _th10_00452706  # e8a209ffff
.globl _th10_00461d64
_th10_00461d64:
    pop ecx  # 59
.globl _th10_00461d65
_th10_00461d65:
    {load} mov edi, eax  # 8bf8
.globl _th10_00461d67
_th10_00461d67:
    test edi, edi  # 85ff
.globl _th10_00461d69
_th10_00461d69:
    {disp8} je _th10_00461dab  # 7440
.globl _th10_00461d6b
_th10_00461d6b:
    {disp8} {noimm8s} mov dword ptr [ebp-0x44], 1  # c745bc01000000
.globl _th10_00461d72
_th10_00461d72:
    push esi  # 56
.globl _th10_00461d73
_th10_00461d73:
    push edi  # 57
.globl _th10_00461d74
_th10_00461d74:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_00461d77
_th10_00461d77:
    {disp8} push dword ptr [ebp-0x34]  # ff75cc
.globl _th10_00461d7a
_th10_00461d7a:
    push 1  # 6a01
.globl _th10_00461d7c
_th10_00461d7c:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00461d7f
_th10_00461d7f:
    call dword ptr [_th10_00466104]  # ff1504614600
.globl _th10_00461d85
_th10_00461d85:
    test eax, eax  # 85c0
.globl _th10_00461d87
_th10_00461d87:
    {disp8} je _th10_00461d9e  # 7415
.globl _th10_00461d89
_th10_00461d89:
    push esi  # 56
.globl _th10_00461d8a
_th10_00461d8a:
    push edi  # 57
.globl _th10_00461d8b
_th10_00461d8b:
    push ebx  # 53
.globl _th10_00461d8c
_th10_00461d8c:
    {disp8} push dword ptr [ebp-0x38]  # ff75c8
.globl _th10_00461d8f
_th10_00461d8f:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00461d92
_th10_00461d92:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00461d95
_th10_00461d95:
    call dword ptr [_th10_004661d0]  # ff15d0614600
.globl _th10_00461d9b
_th10_00461d9b:
    {disp8} {store} mov [ebp-0x48], eax  # 8945b8
.globl _th10_00461d9e
_th10_00461d9e:
    {disp8} cmp dword ptr [ebp-0x44], 0  # 837dbc00
.globl _th10_00461da2
_th10_00461da2:
    {disp8} je _th10_00461dab  # 7407
.globl _th10_00461da4
_th10_00461da4:
    push edi  # 57
.globl _th10_00461da5
_th10_00461da5:
    {disp32} call _th10_00452422  # e87806ffff
.globl _th10_00461daa
_th10_00461daa:
    pop ecx  # 59
.globl _th10_00461dab
_th10_00461dab:
    {disp8} cmp dword ptr [ebp-0x50], 0  # 837db000
.globl _th10_00461daf
_th10_00461daf:
    {disp8} je _th10_00461dba  # 7409
.globl _th10_00461db1
_th10_00461db1:
    {disp8} push dword ptr [ebp-0x38]  # ff75c8
.globl _th10_00461db4
_th10_00461db4:
    {disp32} call _th10_00452422  # e86906ffff
.globl _th10_00461db9
_th10_00461db9:
    pop ecx  # 59
.globl _th10_00461dba
_th10_00461dba:
    {disp8} {load} mov eax, [ebp-0x48]  # 8b45b8
.globl _th10_00461dbd
_th10_00461dbd:
    {disp32} jmp _th10_00461e70  # e9ae000000
.globl _th10_00461dc2
_th10_00461dc2:
    {disp8} {store} mov [ebp-0x40], edi  # 897dc0
.globl _th10_00461dc5
_th10_00461dc5:
    {disp8} {store} cmp [ebp+8], edi  # 397d08
.globl _th10_00461dc8
_th10_00461dc8:
    {disp8} jne _th10_00461dd2  # 7508
.globl _th10_00461dca
_th10_00461dca:
    mov eax, [_th10_00477654]  # a154764700
.globl _th10_00461dcf
_th10_00461dcf:
    {disp8} {store} mov [ebp+8], eax  # 894508
.globl _th10_00461dd2
_th10_00461dd2:
    {disp8} {load} mov ebx, [ebp+0x20]  # 8b5d20
.globl _th10_00461dd5
_th10_00461dd5:
    {load} cmp ebx, edi  # 3bdf
.globl _th10_00461dd7
_th10_00461dd7:
    {disp8} jne _th10_00461ddf  # 7506
.globl _th10_00461dd9
_th10_00461dd9:
    {load} mov ebx, [_th10_00477664]  # 8b1d64764700
.globl _th10_00461ddf
_th10_00461ddf:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00461de2
_th10_00461de2:
    {disp32} call _th10_004601a1  # e8bae3ffff
.globl _th10_00461de7
_th10_00461de7:
    pop ecx  # 59
.globl _th10_00461de8
_th10_00461de8:
    {load} mov esi, eax  # 8bf0
.globl _th10_00461dea
_th10_00461dea:
    cmp esi, -1  # 83feff
.globl _th10_00461ded
_th10_00461ded:
    {disp8} jne _th10_00461df3  # 7504
.globl _th10_00461def
_th10_00461def:
    {load} xor eax, eax  # 33c0
.globl _th10_00461df1
_th10_00461df1:
    {disp8} jmp _th10_00461e70  # eb7d
.globl _th10_00461df3
_th10_00461df3:
    {load} cmp esi, ebx  # 3bf3
.globl _th10_00461df5
_th10_00461df5:
    {disp8} je _th10_00461e40  # 7449
.globl _th10_00461df7
_th10_00461df7:
    push 0  # 6a00
.globl _th10_00461df9
_th10_00461df9:
    push 0  # 6a00
.globl _th10_00461dfb
_th10_00461dfb:
    {disp8} lea eax, [ebp+0x14]  # 8d4514
.globl _th10_00461dfe
_th10_00461dfe:
    push eax  # 50
.globl _th10_00461dff
_th10_00461dff:
    {disp8} push dword ptr [ebp-0x3C]  # ff75c4
.globl _th10_00461e02
_th10_00461e02:
    push esi  # 56
.globl _th10_00461e03
_th10_00461e03:
    push ebx  # 53
.globl _th10_00461e04
_th10_00461e04:
    {disp32} call _th10_004601e8  # e8dfe3ffff
.globl _th10_00461e09
_th10_00461e09:
    add esp, 24  # 83c418
.globl _th10_00461e0c
_th10_00461e0c:
    {load} mov edi, eax  # 8bf8
.globl _th10_00461e0e
_th10_00461e0e:
    test edi, edi  # 85ff
.globl _th10_00461e10
_th10_00461e10:
    {disp8} je _th10_00461def  # 74dd
.globl _th10_00461e12
_th10_00461e12:
    push 0  # 6a00
.globl _th10_00461e14
_th10_00461e14:
    push 0  # 6a00
.globl _th10_00461e16
_th10_00461e16:
    {disp8} lea eax, [ebp+0x1C]  # 8d451c
.globl _th10_00461e19
_th10_00461e19:
    push eax  # 50
.globl _th10_00461e1a
_th10_00461e1a:
    {disp8} push dword ptr [ebp-0x34]  # ff75cc
.globl _th10_00461e1d
_th10_00461e1d:
    push esi  # 56
.globl _th10_00461e1e
_th10_00461e1e:
    push ebx  # 53
.globl _th10_00461e1f
_th10_00461e1f:
    {disp32} call _th10_004601e8  # e8c4e3ffff
.globl _th10_00461e24
_th10_00461e24:
    add esp, 24  # 83c418
.globl _th10_00461e27
_th10_00461e27:
    {disp8} {store} mov [ebp-0x40], eax  # 8945c0
.globl _th10_00461e2a
_th10_00461e2a:
    test eax, eax  # 85c0
.globl _th10_00461e2c
_th10_00461e2c:
    {disp8} jne _th10_00461e37  # 7509
.globl _th10_00461e2e
_th10_00461e2e:
    push edi  # 57
.globl _th10_00461e2f
_th10_00461e2f:
    {disp32} call _th10_00452422  # e8ee05ffff
.globl _th10_00461e34
_th10_00461e34:
    pop ecx  # 59
.globl _th10_00461e35
_th10_00461e35:
    {disp8} jmp _th10_00461def  # ebb8
.globl _th10_00461e37
_th10_00461e37:
    {disp8} {store} mov [ebp-0x3C], edi  # 897dc4
.globl _th10_00461e3a
_th10_00461e3a:
    {disp8} {load} mov eax, [ebp-0x40]  # 8b45c0
.globl _th10_00461e3d
_th10_00461e3d:
    {disp8} {store} mov [ebp-0x34], eax  # 8945cc
.globl _th10_00461e40
_th10_00461e40:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_00461e43
_th10_00461e43:
    {disp8} push dword ptr [ebp-0x34]  # ff75cc
.globl _th10_00461e46
_th10_00461e46:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00461e49
_th10_00461e49:
    {disp8} push dword ptr [ebp-0x3C]  # ff75c4
.globl _th10_00461e4c
_th10_00461e4c:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00461e4f
_th10_00461e4f:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00461e52
_th10_00461e52:
    call dword ptr [_th10_004661cc]  # ff15cc614600
.globl _th10_00461e58
_th10_00461e58:
    {load} mov esi, eax  # 8bf0
.globl _th10_00461e5a
_th10_00461e5a:
    test edi, edi  # 85ff
.globl _th10_00461e5c
_th10_00461e5c:
    {disp8} je _th10_00461e6e  # 7410
.globl _th10_00461e5e
_th10_00461e5e:
    push edi  # 57
.globl _th10_00461e5f
_th10_00461e5f:
    {disp32} call _th10_00452422  # e8be05ffff
.globl _th10_00461e64
_th10_00461e64:
    {disp8} push dword ptr [ebp-0x40]  # ff75c0
.globl _th10_00461e67
_th10_00461e67:
    {disp32} call _th10_00452422  # e8b605ffff
.globl _th10_00461e6c
_th10_00461e6c:
    pop ecx  # 59
.globl _th10_00461e6d
_th10_00461e6d:
    pop ecx  # 59
.globl _th10_00461e6e
_th10_00461e6e:
    {load} mov eax, esi  # 8bc6
.globl _th10_00461e70
_th10_00461e70:
    {disp8} lea esp, [ebp-0x64]  # 8d659c
.globl _th10_00461e73
_th10_00461e73:
    {disp8} {load} mov ecx, [ebp-0x1C]  # 8b4de4
.globl _th10_00461e76
_th10_00461e76:
    {load} xor ecx, ebp  # 33cd
.globl _th10_00461e78
_th10_00461e78:
    {disp32} call _th10_00458ea5  # e82870ffff
.globl _th10_00461e7d
_th10_00461e7d:
    {disp32} call _th10_00454bf7  # e8752dffff
.globl _th10_00461e82
_th10_00461e82:
    ret  # c3
.globl _th10_00461e83
_th10_00461e83:
    push esi  # 56
.globl _th10_00461e84
_th10_00461e84:
    {load} mov esi, [_th10_00477490]  # 8b3590744700
.globl _th10_00461e8a
_th10_00461e8a:
    {disp8} jmp _th10_00461eae  # eb22
.globl _th10_00461e8c
_th10_00461e8c:
    push edi  # 57
.globl _th10_00461e8d
_th10_00461e8d:
    push eax  # 50
.globl _th10_00461e8e
_th10_00461e8e:
    {disp8} push dword ptr [esp+0x10]  # ff742410
.globl _th10_00461e92
_th10_00461e92:
    {disp32} call _th10_004610a6  # e80ff2ffff
.globl _th10_00461e97
_th10_00461e97:
    add esp, 12  # 83c40c
.globl _th10_00461e9a
_th10_00461e9a:
    test eax, eax  # 85c0
.globl _th10_00461e9c
_th10_00461e9c:
    {disp8} jne _th10_00461eab  # 750d
.globl _th10_00461e9e
_th10_00461e9e:
    {load} mov eax, [esi]  # 8b06
.globl _th10_00461ea0
_th10_00461ea0:
    {load} mov al, [edi+eax]  # 8a0407
.globl _th10_00461ea3
_th10_00461ea3:
    cmp al, 0x3D  # 3c3d
.globl _th10_00461ea5
_th10_00461ea5:
    {disp8} je _th10_00461ec3  # 741c
.globl _th10_00461ea7
_th10_00461ea7:
    test al, al  # 84c0
.globl _th10_00461ea9
_th10_00461ea9:
    {disp8} je _th10_00461ec3  # 7418
.globl _th10_00461eab
_th10_00461eab:
    add esi, 4  # 83c604
.globl _th10_00461eae
_th10_00461eae:
    {load} mov eax, [esi]  # 8b06
.globl _th10_00461eb0
_th10_00461eb0:
    test eax, eax  # 85c0
.globl _th10_00461eb2
_th10_00461eb2:
    {disp8} jne _th10_00461e8c  # 75d8
.globl _th10_00461eb4
_th10_00461eb4:
    {load} mov eax, esi  # 8bc6
.globl _th10_00461eb6
_th10_00461eb6:
    {load} sub eax, [_th10_00477490]  # 2b0590744700
.globl _th10_00461ebc
_th10_00461ebc:
    pop esi  # 5e
.globl _th10_00461ebd
_th10_00461ebd:
    sar eax, 2  # c1f802
.globl _th10_00461ec0
_th10_00461ec0:
    neg eax  # f7d8
.globl _th10_00461ec2
_th10_00461ec2:
    ret  # c3
.globl _th10_00461ec3
_th10_00461ec3:
    {load} mov eax, esi  # 8bc6
.globl _th10_00461ec5
_th10_00461ec5:
    {load} sub eax, [_th10_00477490]  # 2b0590744700
.globl _th10_00461ecb
_th10_00461ecb:
    pop esi  # 5e
.globl _th10_00461ecc
_th10_00461ecc:
    sar eax, 2  # c1f802
.globl _th10_00461ecf
_th10_00461ecf:
    ret  # c3
.globl _th10_00461ed0
_th10_00461ed0:
    push ebp  # 55
.globl _th10_00461ed1
_th10_00461ed1:
    {load} mov ebp, esp  # 8bec
.globl _th10_00461ed3
_th10_00461ed3:
    push ecx  # 51
.globl _th10_00461ed4
_th10_00461ed4:
    {load} xor ecx, ecx  # 33c9
.globl _th10_00461ed6
_th10_00461ed6:
    test edi, edi  # 85ff
.globl _th10_00461ed8
_th10_00461ed8:
    {load} mov eax, edi  # 8bc7
.globl _th10_00461eda
_th10_00461eda:
    {disp8} jne _th10_00461ede  # 7502
.globl _th10_00461edc
_th10_00461edc:
    leave  # c9
.globl _th10_00461edd
_th10_00461edd:
    ret  # c3
.globl _th10_00461ede
_th10_00461ede:
    cmp dword ptr [edi], 0  # 833f00
.globl _th10_00461ee1
_th10_00461ee1:
    {disp8} je _th10_00461eec  # 7409
.globl _th10_00461ee3
_th10_00461ee3:
    add eax, 4  # 83c004
.globl _th10_00461ee6
_th10_00461ee6:
    inc ecx  # 41
.globl _th10_00461ee7
_th10_00461ee7:
    cmp dword ptr [eax], 0  # 833800
.globl _th10_00461eea
_th10_00461eea:
    {disp8} jne _th10_00461ee3  # 75f7
.globl _th10_00461eec
_th10_00461eec:
    push ebx  # 53
.globl _th10_00461eed
_th10_00461eed:
    lea eax, [ecx*4+4]  # 8d048d04000000
.globl _th10_00461ef4
_th10_00461ef4:
    push esi  # 56
.globl _th10_00461ef5
_th10_00461ef5:
    push eax  # 50
.globl _th10_00461ef6
_th10_00461ef6:
    {disp32} call _th10_00452706  # e80b08ffff
.globl _th10_00461efb
_th10_00461efb:
    {load} mov esi, eax  # 8bf0
.globl _th10_00461efd
_th10_00461efd:
    test esi, esi  # 85f6
.globl _th10_00461eff
_th10_00461eff:
    pop ecx  # 59
.globl _th10_00461f00
_th10_00461f00:
    {disp8} {store} mov [ebp-4], esi  # 8975fc
.globl _th10_00461f03
_th10_00461f03:
    {disp8} jne _th10_00461f0d  # 7508
.globl _th10_00461f05
_th10_00461f05:
    push 9  # 6a09
.globl _th10_00461f07
_th10_00461f07:
    {disp32} call _th10_0045373d  # e83118ffff
.globl _th10_00461f0c
_th10_00461f0c:
    pop ecx  # 59
.globl _th10_00461f0d
_th10_00461f0d:
    {load} mov eax, [edi]  # 8b07
.globl _th10_00461f0f
_th10_00461f0f:
    {load} mov ebx, edi  # 8bdf
.globl _th10_00461f11
_th10_00461f11:
    {disp8} jmp _th10_00461f24  # eb11
.globl _th10_00461f13
_th10_00461f13:
    push eax  # 50
.globl _th10_00461f14
_th10_00461f14:
    {disp32} call _th10_00462250  # e837030000
.globl _th10_00461f19
_th10_00461f19:
    {store} mov [esi], eax  # 8906
.globl _th10_00461f1b
_th10_00461f1b:
    add esi, 4  # 83c604
.globl _th10_00461f1e
_th10_00461f1e:
    add ebx, 4  # 83c304
.globl _th10_00461f21
_th10_00461f21:
    {load} mov eax, [ebx]  # 8b03
.globl _th10_00461f23
_th10_00461f23:
    pop ecx  # 59
.globl _th10_00461f24
_th10_00461f24:
    test eax, eax  # 85c0
.globl _th10_00461f26
_th10_00461f26:
    {disp8} jne _th10_00461f13  # 75eb
.globl _th10_00461f28
_th10_00461f28:
    {store} and [esi], eax  # 2106
.globl _th10_00461f2a
_th10_00461f2a:
    {disp8} {load} mov eax, [ebp-4]  # 8b45fc
.globl _th10_00461f2d
_th10_00461f2d:
    pop esi  # 5e
.globl _th10_00461f2e
_th10_00461f2e:
    pop ebx  # 5b
.globl _th10_00461f2f
_th10_00461f2f:
    leave  # c9
.globl _th10_00461f30
_th10_00461f30:
    ret  # c3
.globl _th10_00461f31
_th10_00461f31:
    push ebp  # 55
.globl _th10_00461f32
_th10_00461f32:
    {load} mov ebp, esp  # 8bec
.globl _th10_00461f34
_th10_00461f34:
    sub esp, 16  # 83ec10
.globl _th10_00461f37
_th10_00461f37:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00461f3a
_th10_00461f3a:
    push ebx  # 53
.globl _th10_00461f3b
_th10_00461f3b:
    {load} xor ebx, ebx  # 33db
.globl _th10_00461f3d
_th10_00461f3d:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_00461f3f
_th10_00461f3f:
    push edi  # 57
.globl _th10_00461f40
_th10_00461f40:
    {disp8} {store} mov [ebp-0x10], ebx  # 895df0
.globl _th10_00461f43
_th10_00461f43:
    {disp8} jne _th10_00461f4a  # 7505
.globl _th10_00461f45
_th10_00461f45:
    or eax, -1  # 83c8ff
.globl _th10_00461f48
_th10_00461f48:
    {disp8} jmp _th10_00461fab  # eb61
.globl _th10_00461f4a
_th10_00461f4a:
    push esi  # 56
.globl _th10_00461f4b
_th10_00461f4b:
    {load} mov esi, [eax]  # 8b30
.globl _th10_00461f4d
_th10_00461f4d:
    {load} cmp esi, ebx  # 3bf3
.globl _th10_00461f4f
_th10_00461f4f:
    {disp8} {store} mov [ebp-8], esi  # 8975f8
.globl _th10_00461f52
_th10_00461f52:
    {disp8} je _th10_00461fa7  # 7453
.globl _th10_00461f54
_th10_00461f54:
    push 61  # 6a3d
.globl _th10_00461f56
_th10_00461f56:
    push esi  # 56
.globl _th10_00461f57
_th10_00461f57:
    {disp32} call _th10_0046227b  # e81f030000
.globl _th10_00461f5c
_th10_00461f5c:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_00461f5e
_th10_00461f5e:
    pop ecx  # 59
.globl _th10_00461f5f
_th10_00461f5f:
    pop ecx  # 59
.globl _th10_00461f60
_th10_00461f60:
    {disp8} {store} mov [ebp-0x0C], eax  # 8945f4
.globl _th10_00461f63
_th10_00461f63:
    {disp8} je _th10_00461fa7  # 7442
.globl _th10_00461f65
_th10_00461f65:
    {load} cmp esi, eax  # 3bf0
.globl _th10_00461f67
_th10_00461f67:
    {disp8} je _th10_00461fa7  # 743e
.globl _th10_00461f69
_th10_00461f69:
    {load} xor ecx, ecx  # 33c9
.globl _th10_00461f6b
_th10_00461f6b:
    {disp8} {store} cmp [eax+1], cl  # 384801
.globl _th10_00461f6e
_th10_00461f6e:
    mov eax, [_th10_00477490]  # a190744700
.globl _th10_00461f73
_th10_00461f73:
    sete cl  # 0f94c1
.globl _th10_00461f76
_th10_00461f76:
    {load} cmp eax, [_th10_00477494]  # 3b0594744700
.globl _th10_00461f7c
_th10_00461f7c:
    {disp8} {store} mov [ebp-4], ecx  # 894dfc
.globl _th10_00461f7f
_th10_00461f7f:
    {disp8} jne _th10_00461f8d  # 750c
.globl _th10_00461f81
_th10_00461f81:
    {load} mov edi, eax  # 8bf8
.globl _th10_00461f83
_th10_00461f83:
    {disp32} call _th10_00461ed0  # e848ffffff
.globl _th10_00461f88
_th10_00461f88:
    mov [_th10_00477490], eax  # a390744700
.globl _th10_00461f8d
_th10_00461f8d:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_00461f8f
_th10_00461f8f:
    {disp8} jne _th10_00461fe6  # 7555
.globl _th10_00461f91
_th10_00461f91:
    {disp8} {store} cmp [ebp+0x0C], ebx  # 395d0c
.globl _th10_00461f94
_th10_00461f94:
    {disp8} je _th10_00461faf  # 7419
.globl _th10_00461f96
_th10_00461f96:
    {store} cmp [_th10_00477498], ebx  # 391d98744700
.globl _th10_00461f9c
_th10_00461f9c:
    {disp8} je _th10_00461faf  # 7411
.globl _th10_00461f9e
_th10_00461f9e:
    {disp32} call _th10_004610f4  # e851f1ffff
.globl _th10_00461fa3
_th10_00461fa3:
    test eax, eax  # 85c0
.globl _th10_00461fa5
_th10_00461fa5:
    {disp8} je _th10_00461fe6  # 743f
.globl _th10_00461fa7
_th10_00461fa7:
    or eax, -1  # 83c8ff
.globl _th10_00461faa
_th10_00461faa:
    pop esi  # 5e
.globl _th10_00461fab
_th10_00461fab:
    pop edi  # 5f
.globl _th10_00461fac
_th10_00461fac:
    pop ebx  # 5b
.globl _th10_00461fad
_th10_00461fad:
    leave  # c9
.globl _th10_00461fae
_th10_00461fae:
    ret  # c3
.globl _th10_00461faf
_th10_00461faf:
    {disp8} {store} cmp [ebp-4], ebx  # 395dfc
.globl _th10_00461fb2
_th10_00461fb2:
    {disp8} je _th10_00461fb8  # 7404
.globl _th10_00461fb4
_th10_00461fb4:
    {load} xor eax, eax  # 33c0
.globl _th10_00461fb6
_th10_00461fb6:
    {disp8} jmp _th10_00461faa  # ebf2
.globl _th10_00461fb8
_th10_00461fb8:
    push 4  # 6a04
.globl _th10_00461fba
_th10_00461fba:
    {disp32} call _th10_00452706  # e84707ffff
.globl _th10_00461fbf
_th10_00461fbf:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_00461fc1
_th10_00461fc1:
    pop ecx  # 59
.globl _th10_00461fc2
_th10_00461fc2:
    mov [_th10_00477490], eax  # a390744700
.globl _th10_00461fc7
_th10_00461fc7:
    {disp8} je _th10_00461fa7  # 74de
.globl _th10_00461fc9
_th10_00461fc9:
    {store} mov [eax], ebx  # 8918
.globl _th10_00461fcb
_th10_00461fcb:
    {store} cmp [_th10_00477498], ebx  # 391d98744700
.globl _th10_00461fd1
_th10_00461fd1:
    {disp8} jne _th10_00461fe6  # 7513
.globl _th10_00461fd3
_th10_00461fd3:
    push 4  # 6a04
.globl _th10_00461fd5
_th10_00461fd5:
    {disp32} call _th10_00452706  # e82c07ffff
.globl _th10_00461fda
_th10_00461fda:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_00461fdc
_th10_00461fdc:
    pop ecx  # 59
.globl _th10_00461fdd
_th10_00461fdd:
    mov [_th10_00477498], eax  # a398744700
.globl _th10_00461fe2
_th10_00461fe2:
    {disp8} je _th10_00461fa7  # 74c3
.globl _th10_00461fe4
_th10_00461fe4:
    {store} mov [eax], ebx  # 8918
.globl _th10_00461fe6
_th10_00461fe6:
    {disp8} {load} mov edi, [ebp-0x0C]  # 8b7df4
.globl _th10_00461fe9
_th10_00461fe9:
    {load} mov ebx, [_th10_00477490]  # 8b1d90744700
.globl _th10_00461fef
_th10_00461fef:
    {load} sub edi, esi  # 2bfe
.globl _th10_00461ff1
_th10_00461ff1:
    push esi  # 56
.globl _th10_00461ff2
_th10_00461ff2:
    {disp32} call _th10_00461e83  # e88cfeffff
.globl _th10_00461ff7
_th10_00461ff7:
    {load} mov edi, eax  # 8bf8
.globl _th10_00461ff9
_th10_00461ff9:
    test edi, edi  # 85ff
.globl _th10_00461ffb
_th10_00461ffb:
    pop ecx  # 59
.globl _th10_00461ffc
_th10_00461ffc:
    {disp8} jl _th10_0046204d  # 7c4f
.globl _th10_00461ffe
_th10_00461ffe:
    cmp dword ptr [ebx], 0  # 833b00
.globl _th10_00462001
_th10_00462001:
    {disp8} je _th10_0046204d  # 744a
.globl _th10_00462003
_th10_00462003:
    lea esi, [ebx+edi*4]  # 8d34bb
.globl _th10_00462006
_th10_00462006:
    push dword ptr [esi]  # ff36
.globl _th10_00462008
_th10_00462008:
    {disp32} call _th10_00452422  # e81504ffff
.globl _th10_0046200d
_th10_0046200d:
    {load} xor eax, eax  # 33c0
.globl _th10_0046200f
_th10_0046200f:
    {disp8} {store} cmp [ebp-4], eax  # 3945fc
.globl _th10_00462012
_th10_00462012:
    pop ecx  # 59
.globl _th10_00462013
_th10_00462013:
    {disp8} jne _th10_0046202d  # 7518
.globl _th10_00462015
_th10_00462015:
    {disp8} {load} mov ecx, [ebp-8]  # 8b4df8
.globl _th10_00462018
_th10_00462018:
    {store} mov [esi], ecx  # 890e
.globl _th10_0046201a
_th10_0046201a:
    {disp8} {load} mov ecx, [ebp+8]  # 8b4d08
.globl _th10_0046201d
_th10_0046201d:
    {disp8} {load} mov esi, [ebp-8]  # 8b75f8
.globl _th10_00462020
_th10_00462020:
    {store} mov [ecx], eax  # 8901
.globl _th10_00462022
_th10_00462022:
    {disp8} jmp _th10_0046208e  # eb6a
.globl _th10_00462024
_th10_00462024:
    {disp8} {load} mov ecx, [esi+4]  # 8b4e04
.globl _th10_00462027
_th10_00462027:
    inc edi  # 47
.globl _th10_00462028
_th10_00462028:
    {store} mov [esi], ecx  # 890e
.globl _th10_0046202a
_th10_0046202a:
    lea esi, [ebx+edi*4]  # 8d34bb
.globl _th10_0046202d
_th10_0046202d:
    {store} cmp [esi], eax  # 3906
.globl _th10_0046202f
_th10_0046202f:
    {disp8} jne _th10_00462024  # 75f3
.globl _th10_00462031
_th10_00462031:
    {load} mov eax, edi  # 8bc7
.globl _th10_00462033
_th10_00462033:
    shl eax, 2  # c1e002
.globl _th10_00462036
_th10_00462036:
    push eax  # 50
.globl _th10_00462037
_th10_00462037:
    push dword ptr [_th10_00477490]  # ff3590744700
.globl _th10_0046203d
_th10_0046203d:
    {disp32} call _th10_00457395  # e85353ffff
.globl _th10_00462042
_th10_00462042:
    test eax, eax  # 85c0
.globl _th10_00462044
_th10_00462044:
    {disp8} {load} mov esi, [ebp-8]  # 8b75f8
.globl _th10_00462047
_th10_00462047:
    pop ecx  # 59
.globl _th10_00462048
_th10_00462048:
    pop ecx  # 59
.globl _th10_00462049
_th10_00462049:
    {disp8} je _th10_0046208e  # 7443
.globl _th10_0046204b
_th10_0046204b:
    {disp8} jmp _th10_00462089  # eb3c
.globl _th10_0046204d
_th10_0046204d:
    {disp8} cmp dword ptr [ebp-4], 0  # 837dfc00
.globl _th10_00462051
_th10_00462051:
    {disp32} jne _th10_004620f5  # 0f859e000000
.globl _th10_00462057
_th10_00462057:
    test edi, edi  # 85ff
.globl _th10_00462059
_th10_00462059:
    {disp8} jge _th10_0046205d  # 7d02
.globl _th10_0046205b
_th10_0046205b:
    neg edi  # f7df
.globl _th10_0046205d
_th10_0046205d:
    lea eax, [edi*4+8]  # 8d04bd08000000
.globl _th10_00462064
_th10_00462064:
    push eax  # 50
.globl _th10_00462065
_th10_00462065:
    push dword ptr [_th10_00477490]  # ff3590744700
.globl _th10_0046206b
_th10_0046206b:
    {disp32} call _th10_00457395  # e82553ffff
.globl _th10_00462070
_th10_00462070:
    test eax, eax  # 85c0
.globl _th10_00462072
_th10_00462072:
    pop ecx  # 59
.globl _th10_00462073
_th10_00462073:
    pop ecx  # 59
.globl _th10_00462074
_th10_00462074:
    {disp32} je _th10_00461fa7  # 0f842dffffff
.globl _th10_0046207a
_th10_0046207a:
    lea ecx, [eax+edi*4]  # 8d0cb8
.globl _th10_0046207d
_th10_0046207d:
    {disp8} and dword ptr [ecx+4], 0  # 83610400
.globl _th10_00462081
_th10_00462081:
    {store} mov [ecx], esi  # 8931
.globl _th10_00462083
_th10_00462083:
    {disp8} {load} mov ecx, [ebp+8]  # 8b4d08
.globl _th10_00462086
_th10_00462086:
    and dword ptr [ecx], 0  # 832100
.globl _th10_00462089
_th10_00462089:
    mov [_th10_00477490], eax  # a390744700
.globl _th10_0046208e
_th10_0046208e:
    {disp8} cmp dword ptr [ebp+0x0C], 0  # 837d0c00
.globl _th10_00462092
_th10_00462092:
    {disp8} je _th10_004620e0  # 744c
.globl _th10_00462094
_th10_00462094:
    push esi  # 56
.globl _th10_00462095
_th10_00462095:
    {disp32} call _th10_00456720  # e88646ffff
.globl _th10_0046209a
_th10_0046209a:
    inc eax  # 40
.globl _th10_0046209b
_th10_0046209b:
    inc eax  # 40
.globl _th10_0046209c
_th10_0046209c:
    push eax  # 50
.globl _th10_0046209d
_th10_0046209d:
    {disp32} call _th10_00452706  # e86406ffff
.globl _th10_004620a2
_th10_004620a2:
    {load} mov edi, eax  # 8bf8
.globl _th10_004620a4
_th10_004620a4:
    test edi, edi  # 85ff
.globl _th10_004620a6
_th10_004620a6:
    pop ecx  # 59
.globl _th10_004620a7
_th10_004620a7:
    pop ecx  # 59
.globl _th10_004620a8
_th10_004620a8:
    {disp8} je _th10_004620e0  # 7436
.globl _th10_004620aa
_th10_004620aa:
    push esi  # 56
.globl _th10_004620ab
_th10_004620ab:
    push edi  # 57
.globl _th10_004620ac
_th10_004620ac:
    {disp32} call _th10_0045bd80  # e8cf9cffff
.globl _th10_004620b1
_th10_004620b1:
    {load} mov eax, edi  # 8bc7
.globl _th10_004620b3
_th10_004620b3:
    {load} sub eax, esi  # 2bc6
.globl _th10_004620b5
_th10_004620b5:
    {disp8} {load} add eax, [ebp-0x0C]  # 0345f4
.globl _th10_004620b8
_th10_004620b8:
    pop ecx  # 59
.globl _th10_004620b9
_th10_004620b9:
    pop ecx  # 59
.globl _th10_004620ba
_th10_004620ba:
    {disp8} {load} mov ecx, [ebp-4]  # 8b4dfc
.globl _th10_004620bd
_th10_004620bd:
    mov byte ptr [eax], 0  # c60000
.globl _th10_004620c0
_th10_004620c0:
    inc eax  # 40
.globl _th10_004620c1
_th10_004620c1:
    neg ecx  # f7d9
.globl _th10_004620c3
_th10_004620c3:
    {load} sbb ecx, ecx  # 1bc9
.globl _th10_004620c5
_th10_004620c5:
    not ecx  # f7d1
.globl _th10_004620c7
_th10_004620c7:
    {load} and ecx, eax  # 23c8
.globl _th10_004620c9
_th10_004620c9:
    push ecx  # 51
.globl _th10_004620ca
_th10_004620ca:
    push edi  # 57
.globl _th10_004620cb
_th10_004620cb:
    call dword ptr [_th10_004661a8]  # ff15a8614600
.globl _th10_004620d1
_th10_004620d1:
    test eax, eax  # 85c0
.globl _th10_004620d3
_th10_004620d3:
    {disp8} jne _th10_004620d9  # 7504
.globl _th10_004620d5
_th10_004620d5:
    {disp8} or dword ptr [ebp-0x10], -1  # 834df0ff
.globl _th10_004620d9
_th10_004620d9:
    push edi  # 57
.globl _th10_004620da
_th10_004620da:
    {disp32} call _th10_00452422  # e84303ffff
.globl _th10_004620df
_th10_004620df:
    pop ecx  # 59
.globl _th10_004620e0
_th10_004620e0:
    {disp8} cmp dword ptr [ebp-4], 0  # 837dfc00
.globl _th10_004620e4
_th10_004620e4:
    {disp8} je _th10_004620ed  # 7407
.globl _th10_004620e6
_th10_004620e6:
    push esi  # 56
.globl _th10_004620e7
_th10_004620e7:
    {disp32} call _th10_00452422  # e83603ffff
.globl _th10_004620ec
_th10_004620ec:
    pop ecx  # 59
.globl _th10_004620ed
_th10_004620ed:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_004620f0
_th10_004620f0:
    {disp32} jmp _th10_00461faa  # e9b5feffff
.globl _th10_004620f5
_th10_004620f5:
    push esi  # 56
.globl _th10_004620f6
_th10_004620f6:
    {disp32} call _th10_00452422  # e82703ffff
.globl _th10_004620fb
_th10_004620fb:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004620fe
_th10_004620fe:
    and dword ptr [eax], 0  # 832000
.globl _th10_00462101
_th10_00462101:
    pop ecx  # 59
.globl _th10_00462102
_th10_00462102:
    {disp32} jmp _th10_00461fb4  # e9adfeffff
.globl _th10_00462107
_th10_00462107:
    push esi  # 56
.globl _th10_00462108
_th10_00462108:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_0046210c
_th10_0046210c:
    push edi  # 57
.globl _th10_0046210d
_th10_0046210d:
    push esi  # 56
.globl _th10_0046210e
_th10_0046210e:
    {disp32} call _th10_0045f6d4  # e8c1d5ffff
.globl _th10_00462113
_th10_00462113:
    cmp eax, -1  # 83f8ff
.globl _th10_00462116
_th10_00462116:
    pop ecx  # 59
.globl _th10_00462117
_th10_00462117:
    {disp8} je _th10_00462155  # 743c
.globl _th10_00462119
_th10_00462119:
    cmp esi, 1  # 83fe01
.globl _th10_0046211c
_th10_0046211c:
    {disp8} je _th10_00462123  # 7405
.globl _th10_0046211e
_th10_0046211e:
    cmp esi, 2  # 83fe02
.globl _th10_00462121
_th10_00462121:
    {disp8} jne _th10_00462139  # 7516
.globl _th10_00462123
_th10_00462123:
    push 2  # 6a02
.globl _th10_00462125
_th10_00462125:
    {disp32} call _th10_0045f6d4  # e8aad5ffff
.globl _th10_0046212a
_th10_0046212a:
    push 1  # 6a01
.globl _th10_0046212c
_th10_0046212c:
    {load} mov edi, eax  # 8bf8
.globl _th10_0046212e
_th10_0046212e:
    {disp32} call _th10_0045f6d4  # e8a1d5ffff
.globl _th10_00462133
_th10_00462133:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00462135
_th10_00462135:
    pop ecx  # 59
.globl _th10_00462136
_th10_00462136:
    pop ecx  # 59
.globl _th10_00462137
_th10_00462137:
    {disp8} je _th10_00462155  # 741c
.globl _th10_00462139
_th10_00462139:
    push esi  # 56
.globl _th10_0046213a
_th10_0046213a:
    {disp32} call _th10_0045f6d4  # e895d5ffff
.globl _th10_0046213f
_th10_0046213f:
    pop ecx  # 59
.globl _th10_00462140
_th10_00462140:
    push eax  # 50
.globl _th10_00462141
_th10_00462141:
    call dword ptr [_th10_004660cc]  # ff15cc604600
.globl _th10_00462147
_th10_00462147:
    test eax, eax  # 85c0
.globl _th10_00462149
_th10_00462149:
    {disp8} jne _th10_00462155  # 750a
.globl _th10_0046214b
_th10_0046214b:
    call dword ptr [_th10_0046610c]  # ff150c614600
.globl _th10_00462151
_th10_00462151:
    {load} mov edi, eax  # 8bf8
.globl _th10_00462153
_th10_00462153:
    {disp8} jmp _th10_00462157  # eb02
.globl _th10_00462155
_th10_00462155:
    {load} xor edi, edi  # 33ff
.globl _th10_00462157
_th10_00462157:
    push esi  # 56
.globl _th10_00462158
_th10_00462158:
    {disp32} call _th10_0045f655  # e8f8d4ffff
.globl _th10_0046215d
_th10_0046215d:
    {load} mov eax, esi  # 8bc6
.globl _th10_0046215f
_th10_0046215f:
    sar eax, 5  # c1f805
.globl _th10_00462162
_th10_00462162:
    {load} mov eax, [eax*4+0x499200]  # 8b048500924900
.globl _th10_00462169
_th10_00462169:
    and esi, 31  # 83e61f
.globl _th10_0046216c
_th10_0046216c:
    test edi, edi  # 85ff
.globl _th10_0046216e
_th10_0046216e:
    pop ecx  # 59
.globl _th10_0046216f
_th10_0046216f:
    lea ecx, [esi+esi*8]  # 8d0cf6
.globl _th10_00462172
_th10_00462172:
    {disp8} mov byte ptr [eax+ecx*4+4], 0  # c644880400
.globl _th10_00462177
_th10_00462177:
    {disp8} je _th10_00462185  # 740c
.globl _th10_00462179
_th10_00462179:
    push edi  # 57
.globl _th10_0046217a
_th10_0046217a:
    {disp32} call _th10_00456b04  # e88549ffff
.globl _th10_0046217f
_th10_0046217f:
    pop ecx  # 59
.globl _th10_00462180
_th10_00462180:
    or eax, -1  # 83c8ff
.globl _th10_00462183
_th10_00462183:
    {disp8} jmp _th10_00462187  # eb02
.globl _th10_00462185
_th10_00462185:
    {load} xor eax, eax  # 33c0
.globl _th10_00462187
_th10_00462187:
    pop edi  # 5f
.globl _th10_00462188
_th10_00462188:
    pop esi  # 5e
.globl _th10_00462189
_th10_00462189:
    ret  # c3
.globl _th10_0046218a
_th10_0046218a:
    push 12  # 6a0c
.globl _th10_0046218c
_th10_0046218c:
    {noimm8s} push 0x46C9D8  # 68d8c94600
.globl _th10_00462191
_th10_00462191:
    {disp32} call _th10_00454bbc  # e8262affff
.globl _th10_00462196
_th10_00462196:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00462199
_th10_00462199:
    {load} cmp ebx, [_th10_004991e4]  # 3b1de4914900
.globl _th10_0046219f
_th10_0046219f:
    {disp8} jae _th10_00462209  # 7368
.globl _th10_004621a1
_th10_004621a1:
    {load} mov eax, ebx  # 8bc3
.globl _th10_004621a3
_th10_004621a3:
    sar eax, 5  # c1f805
.globl _th10_004621a6
_th10_004621a6:
    lea edi, [eax*4+0x499200]  # 8d3c8500924900
.globl _th10_004621ad
_th10_004621ad:
    {load} mov eax, ebx  # 8bc3
.globl _th10_004621af
_th10_004621af:
    and eax, 31  # 83e01f
.globl _th10_004621b2
_th10_004621b2:
    lea esi, [eax+eax*8]  # 8d34c0
.globl _th10_004621b5
_th10_004621b5:
    shl esi, 2  # c1e602
.globl _th10_004621b8
_th10_004621b8:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004621ba
_th10_004621ba:
    {disp8} test byte ptr [eax+esi+4], 1  # f644300401
.globl _th10_004621bf
_th10_004621bf:
    {disp8} je _th10_00462209  # 7448
.globl _th10_004621c1
_th10_004621c1:
    push ebx  # 53
.globl _th10_004621c2
_th10_004621c2:
    {disp32} call _th10_0045f715  # e84ed5ffff
.globl _th10_004621c7
_th10_004621c7:
    pop ecx  # 59
.globl _th10_004621c8
_th10_004621c8:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_004621cc
_th10_004621cc:
    {load} mov eax, [edi]  # 8b07
.globl _th10_004621ce
_th10_004621ce:
    {disp8} test byte ptr [eax+esi+4], 1  # f644300401
.globl _th10_004621d3
_th10_004621d3:
    {disp8} je _th10_004621e1  # 740c
.globl _th10_004621d5
_th10_004621d5:
    push ebx  # 53
.globl _th10_004621d6
_th10_004621d6:
    {disp32} call _th10_00462107  # e82cffffff
.globl _th10_004621db
_th10_004621db:
    pop ecx  # 59
.globl _th10_004621dc
_th10_004621dc:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_004621df
_th10_004621df:
    {disp8} jmp _th10_004621f0  # eb0f
.globl _th10_004621e1
_th10_004621e1:
    {disp32} call _th10_00456af2  # e80c49ffff
.globl _th10_004621e6
_th10_004621e6:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_004621ec
_th10_004621ec:
    {disp8} or dword ptr [ebp-0x1C], -1  # 834de4ff
.globl _th10_004621f0
_th10_004621f0:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_004621f4
_th10_004621f4:
    {disp32} call _th10_00462201  # e808000000
.globl _th10_004621f9
_th10_004621f9:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_004621fc
_th10_004621fc:
    {disp8} jmp _th10_0046221f  # eb21
.globl _th10_004621fe
_th10_004621fe:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00462201
_th10_00462201:
    push ebx  # 53
.globl _th10_00462202
_th10_00462202:
    {disp32} call _th10_0045f7b5  # e8aed5ffff
.globl _th10_00462207
_th10_00462207:
    pop ecx  # 59
.globl _th10_00462208
_th10_00462208:
    ret  # c3
.globl _th10_00462209
_th10_00462209:
    {disp32} call _th10_00456af2  # e8e448ffff
.globl _th10_0046220e
_th10_0046220e:
    {noimm8s} mov dword ptr [eax], 9  # c70009000000
.globl _th10_00462214
_th10_00462214:
    {disp32} call _th10_00456afb  # e8e248ffff
.globl _th10_00462219
_th10_00462219:
    and dword ptr [eax], 0  # 832000
.globl _th10_0046221c
_th10_0046221c:
    or eax, -1  # 83c8ff
.globl _th10_0046221f
_th10_0046221f:
    {disp32} call _th10_00454bf7  # e8d329ffff
.globl _th10_00462224
_th10_00462224:
    ret  # c3
.globl _th10_00462225
_th10_00462225:
    push esi  # 56
.globl _th10_00462226
_th10_00462226:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_0046222a
_th10_0046222a:
    {disp8} {load} mov eax, [esi+0x0C]  # 8b460c
.globl _th10_0046222d
_th10_0046222d:
    test al, 0x83  # a883
.globl _th10_0046222f
_th10_0046222f:
    {disp8} je _th10_0046224e  # 741d
.globl _th10_00462231
_th10_00462231:
    test al, 8  # a808
.globl _th10_00462233
_th10_00462233:
    {disp8} je _th10_0046224e  # 7419
.globl _th10_00462235
_th10_00462235:
    {disp8} push dword ptr [esi+8]  # ff7608
.globl _th10_00462238
_th10_00462238:
    {disp32} call _th10_00452422  # e8e501ffff
.globl _th10_0046223d
_th10_0046223d:
    {disp8} {noimm8s} and word ptr [esi+0x0C], 0x0FBF7  # 6681660cf7fb
.globl _th10_00462243
_th10_00462243:
    {load} xor eax, eax  # 33c0
.globl _th10_00462245
_th10_00462245:
    pop ecx  # 59
.globl _th10_00462246
_th10_00462246:
    {store} mov [esi], eax  # 8906
.globl _th10_00462248
_th10_00462248:
    {disp8} {store} mov [esi+8], eax  # 894608
.globl _th10_0046224b
_th10_0046224b:
    {disp8} {store} mov [esi+4], eax  # 894604
.globl _th10_0046224e
_th10_0046224e:
    pop esi  # 5e
.globl _th10_0046224f
_th10_0046224f:
    ret  # c3
.globl _th10_00462250
_th10_00462250:
    push esi  # 56
.globl _th10_00462251
_th10_00462251:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_00462255
_th10_00462255:
    test esi, esi  # 85f6
.globl _th10_00462257
_th10_00462257:
    {disp8} je _th10_00462277  # 741e
.globl _th10_00462259
_th10_00462259:
    push esi  # 56
.globl _th10_0046225a
_th10_0046225a:
    {disp32} call _th10_00456720  # e8c144ffff
.globl _th10_0046225f
_th10_0046225f:
    inc eax  # 40
.globl _th10_00462260
_th10_00462260:
    push eax  # 50
.globl _th10_00462261
_th10_00462261:
    {disp32} call _th10_00452706  # e8a004ffff
.globl _th10_00462266
_th10_00462266:
    test eax, eax  # 85c0
.globl _th10_00462268
_th10_00462268:
    pop ecx  # 59
.globl _th10_00462269
_th10_00462269:
    pop ecx  # 59
.globl _th10_0046226a
_th10_0046226a:
    {disp8} je _th10_00462277  # 740b
.globl _th10_0046226c
_th10_0046226c:
    push esi  # 56
.globl _th10_0046226d
_th10_0046226d:
    push eax  # 50
.globl _th10_0046226e
_th10_0046226e:
    {disp32} call _th10_0045bd80  # e80d9bffff
.globl _th10_00462273
_th10_00462273:
    pop ecx  # 59
.globl _th10_00462274
_th10_00462274:
    pop ecx  # 59
.globl _th10_00462275
_th10_00462275:
    pop esi  # 5e
.globl _th10_00462276
_th10_00462276:
    ret  # c3
.globl _th10_00462277
_th10_00462277:
    {load} xor eax, eax  # 33c0
.globl _th10_00462279
_th10_00462279:
    pop esi  # 5e
.globl _th10_0046227a
_th10_0046227a:
    ret  # c3
.globl _th10_0046227b
_th10_0046227b:
    push ebp  # 55
.globl _th10_0046227c
_th10_0046227c:
    {load} mov ebp, esp  # 8bec
.globl _th10_0046227e
_th10_0046227e:
    {disp32} call _th10_00456357  # e8d440ffff
.globl _th10_00462283
_th10_00462283:
    {disp8} {load} mov eax, [eax+0x60]  # 8b4060
.globl _th10_00462286
_th10_00462286:
    {load} cmp eax, [_th10_00497f94]  # 3b05947f4900
.globl _th10_0046228c
_th10_0046228c:
    {disp8} je _th10_00462293  # 7405
.globl _th10_0046228e
_th10_0046228e:
    {disp32} call _th10_0045cf49  # e8b6acffff
.globl _th10_00462293
_th10_00462293:
    {disp8} cmp dword ptr [eax+8], 0  # 83780800
.globl _th10_00462297
_th10_00462297:
    {disp8} jne _th10_0046229f  # 7506
.globl _th10_00462299
_th10_00462299:
    pop ebp  # 5d
.globl _th10_0046229a
_th10_0046229a:
    {disp32} jmp _th10_00452730  # e99104ffff
.globl _th10_0046229f
_th10_0046229f:
    {disp8} {load} mov ecx, [ebp+8]  # 8b4d08
.globl _th10_004622a2
_th10_004622a2:
    push ebx  # 53
.globl _th10_004622a3
_th10_004622a3:
    push esi  # 56
.globl _th10_004622a4
_th10_004622a4:
    {disp8} jmp _th10_004622d5  # eb2f
.globl _th10_004622a6
_th10_004622a6:
    movzx esi, dl  # 0fb6f2
.globl _th10_004622a9
_th10_004622a9:
    {disp8} test byte ptr [esi+eax+0x1D], 4  # f644061d04
.globl _th10_004622ae
_th10_004622ae:
    {disp8} je _th10_004622cc  # 741c
.globl _th10_004622b0
_th10_004622b0:
    inc ecx  # 41
.globl _th10_004622b1
_th10_004622b1:
    {load} mov bl, [ecx]  # 8a19
.globl _th10_004622b3
_th10_004622b3:
    test bl, bl  # 84db
.globl _th10_004622b5
_th10_004622b5:
    {disp8} je _th10_004622f2  # 743b
.globl _th10_004622b7
_th10_004622b7:
    movzx edx, dx  # 0fb7d2
.globl _th10_004622ba
_th10_004622ba:
    movzx esi, bl  # 0fb6f3
.globl _th10_004622bd
_th10_004622bd:
    shl edx, 8  # c1e208
.globl _th10_004622c0
_th10_004622c0:
    {load} or edx, esi  # 0bd6
.globl _th10_004622c2
_th10_004622c2:
    {disp8} {store} cmp [ebp+0x0C], edx  # 39550c
.globl _th10_004622c5
_th10_004622c5:
    {disp8} jne _th10_004622d4  # 750d
.globl _th10_004622c7
_th10_004622c7:
    {disp8} lea eax, [ecx-1]  # 8d41ff
.globl _th10_004622ca
_th10_004622ca:
    {disp8} jmp _th10_004622ee  # eb22
.globl _th10_004622cc
_th10_004622cc:
    movzx esi, dx  # 0fb7f2
.globl _th10_004622cf
_th10_004622cf:
    {disp8} {store} cmp [ebp+0x0C], esi  # 39750c
.globl _th10_004622d2
_th10_004622d2:
    {disp8} je _th10_004622de  # 740a
.globl _th10_004622d4
_th10_004622d4:
    inc ecx  # 41
.globl _th10_004622d5
_th10_004622d5:
    movzx dx, byte ptr [ecx]  # 660fb611
.globl _th10_004622d9
_th10_004622d9:
    test dx, dx  # 6685d2
.globl _th10_004622dc
_th10_004622dc:
    {disp8} jne _th10_004622a6  # 75c8
.globl _th10_004622de
_th10_004622de:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_004622e1
_th10_004622e1:
    movzx edx, dx  # 0fb7d2
.globl _th10_004622e4
_th10_004622e4:
    {load} sub eax, edx  # 2bc2
.globl _th10_004622e6
_th10_004622e6:
    neg eax  # f7d8
.globl _th10_004622e8
_th10_004622e8:
    {load} sbb eax, eax  # 1bc0
.globl _th10_004622ea
_th10_004622ea:
    not eax  # f7d0
.globl _th10_004622ec
_th10_004622ec:
    {load} and eax, ecx  # 23c1
.globl _th10_004622ee
_th10_004622ee:
    pop esi  # 5e
.globl _th10_004622ef
_th10_004622ef:
    pop ebx  # 5b
.globl _th10_004622f0
_th10_004622f0:
    pop ebp  # 5d
.globl _th10_004622f1
_th10_004622f1:
    ret  # c3
.globl _th10_004622f2
_th10_004622f2:
    {load} xor eax, eax  # 33c0
.globl _th10_004622f4
_th10_004622f4:
    {disp8} jmp _th10_004622ee  # ebf8
.globl _th10_004622f6
_th10_004622f6:
    {disp8} push dword ptr [esp+4]  # ff742404
.globl _th10_004622fa
_th10_004622fa:
    {disp32} call _th10_00452493  # e89401ffff
.globl _th10_004622ff
_th10_004622ff:
    pop ecx  # 59
.globl _th10_00462300
_th10_00462300:
    ret  # c3
.globl _th10_00462301
_th10_00462301:
    push esi  # 56
.globl _th10_00462302
_th10_00462302:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462304
_th10_00462304:
    push 0  # 6a00
.globl _th10_00462306
_th10_00462306:
    {disp8} {noimm8s} mov dword ptr [esi+0x18], 0x0F  # c746180f000000
.globl _th10_0046230d
_th10_0046230d:
    {disp32} call _th10_00438590  # e87e62fdff
.globl _th10_00462312
_th10_00462312:
    push -1  # 6aff
.globl _th10_00462314
_th10_00462314:
    push 0  # 6a00
.globl _th10_00462316
_th10_00462316:
    {disp8} push dword ptr [esp+0x10]  # ff742410
.globl _th10_0046231a
_th10_0046231a:
    {load} mov ecx, esi  # 8bce
.globl _th10_0046231c
_th10_0046231c:
    {disp32} call _th10_00438260  # e83f5ffdff
.globl _th10_00462321
_th10_00462321:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462323
_th10_00462323:
    pop esi  # 5e
.globl _th10_00462324
_th10_00462324:
    {noimm8s} ret 4  # c20400
.globl _th10_00462327
_th10_00462327:
    {noimm8s} mov eax, 0x465198  # b898514600
.globl _th10_0046232c
_th10_0046232c:
    {disp32} call _th10_00462adc  # e8ab070000
.globl _th10_00462331
_th10_00462331:
    push ecx  # 51
.globl _th10_00462332
_th10_00462332:
    push esi  # 56
.globl _th10_00462333
_th10_00462333:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462335
_th10_00462335:
    {disp8} {store} mov [ebp-0x10], esi  # 8975f0
.globl _th10_00462338
_th10_00462338:
    {disp32} call _th10_00462c01  # e8c4080000
.globl _th10_0046233d
_th10_0046233d:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00462340
_th10_00462340:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462344
_th10_00462344:
    {disp8} lea ecx, [esi+0x0C]  # 8d4e0c
.globl _th10_00462347
_th10_00462347:
    {noimm8s} mov dword ptr [esi], 0x46C9E8  # c706e8c94600
.globl _th10_0046234d
_th10_0046234d:
    {disp32} call _th10_00462301  # e8afffffff
.globl _th10_00462352
_th10_00462352:
    {disp8} {load} mov ecx, [ebp-0x0C]  # 8b4df4
.globl _th10_00462355
_th10_00462355:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462357
_th10_00462357:
    pop esi  # 5e
.globl _th10_00462358
_th10_00462358:
    {store} mov fs:[0], ecx  # 64890d00000000
.globl _th10_0046235f
_th10_0046235f:
    leave  # c9
.globl _th10_00462360
_th10_00462360:
    {noimm8s} ret 4  # c20400
.globl _th10_00462363
_th10_00462363:
    {disp8} cmp dword ptr [ecx+0x24], 16  # 83792410
.globl _th10_00462367
_th10_00462367:
    {disp8} jb _th10_0046236d  # 7204
.globl _th10_00462369
_th10_00462369:
    {disp8} {load} mov eax, [ecx+0x10]  # 8b4110
.globl _th10_0046236c
_th10_0046236c:
    ret  # c3
.globl _th10_0046236d
_th10_0046236d:
    {disp8} lea eax, [ecx+0x10]  # 8d4110
.globl _th10_00462370
_th10_00462370:
    ret  # c3
.globl _th10_00462371
_th10_00462371:
    push esi  # 56
.globl _th10_00462372
_th10_00462372:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462374
_th10_00462374:
    push 0  # 6a00
.globl _th10_00462376
_th10_00462376:
    push 1  # 6a01
.globl _th10_00462378
_th10_00462378:
    {disp8} lea ecx, [esi+0x0C]  # 8d4e0c
.globl _th10_0046237b
_th10_0046237b:
    {noimm8s} mov dword ptr [esi], 0x46C9E8  # c706e8c94600
.globl _th10_00462381
_th10_00462381:
    {disp32} call _th10_00438380  # e8fa5ffdff
.globl _th10_00462386
_th10_00462386:
    {load} mov ecx, esi  # 8bce
.globl _th10_00462388
_th10_00462388:
    pop esi  # 5e
.globl _th10_00462389
_th10_00462389:
    {disp32} jmp _th10_00462cac  # e91e090000
.globl _th10_0046238e
_th10_0046238e:
    push esi  # 56
.globl _th10_0046238f
_th10_0046238f:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462391
_th10_00462391:
    {disp32} call _th10_00462371  # e8dbffffff
.globl _th10_00462396
_th10_00462396:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_0046239b
_th10_0046239b:
    {disp8} je _th10_004623a4  # 7407
.globl _th10_0046239d
_th10_0046239d:
    push esi  # 56
.globl _th10_0046239e
_th10_0046239e:
    {disp32} call _th10_004524a1  # e8fe00ffff
.globl _th10_004623a3
_th10_004623a3:
    pop ecx  # 59
.globl _th10_004623a4
_th10_004623a4:
    {load} mov eax, esi  # 8bc6
.globl _th10_004623a6
_th10_004623a6:
    pop esi  # 5e
.globl _th10_004623a7
_th10_004623a7:
    {noimm8s} ret 4  # c20400
.globl _th10_004623aa
_th10_004623aa:
    push esi  # 56
.globl _th10_004623ab
_th10_004623ab:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_004623af
_th10_004623af:
    {load} mov esi, ecx  # 8bf1
.globl _th10_004623b1
_th10_004623b1:
    {disp32} call _th10_00462327  # e871ffffff
.globl _th10_004623b6
_th10_004623b6:
    {noimm8s} mov dword ptr [esi], 0x46C9F4  # c706f4c94600
.globl _th10_004623bc
_th10_004623bc:
    {load} mov eax, esi  # 8bc6
.globl _th10_004623be
_th10_004623be:
    pop esi  # 5e
.globl _th10_004623bf
_th10_004623bf:
    {noimm8s} ret 4  # c20400
.globl _th10_004623c2
_th10_004623c2:
    push esi  # 56
.globl _th10_004623c3
_th10_004623c3:
    {load} mov esi, ecx  # 8bf1
.globl _th10_004623c5
_th10_004623c5:
    {disp32} call _th10_004623de  # e814000000
.globl _th10_004623ca
_th10_004623ca:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_004623cf
_th10_004623cf:
    {disp8} je _th10_004623d8  # 7407
.globl _th10_004623d1
_th10_004623d1:
    push esi  # 56
.globl _th10_004623d2
_th10_004623d2:
    {disp32} call _th10_004524a1  # e8ca00ffff
.globl _th10_004623d7
_th10_004623d7:
    pop ecx  # 59
.globl _th10_004623d8
_th10_004623d8:
    {load} mov eax, esi  # 8bc6
.globl _th10_004623da
_th10_004623da:
    pop esi  # 5e
.globl _th10_004623db
_th10_004623db:
    {noimm8s} ret 4  # c20400
.globl _th10_004623de
_th10_004623de:
    {noimm8s} mov dword ptr [ecx], 0x46C9F4  # c701f4c94600
.globl _th10_004623e4
_th10_004623e4:
    {disp32} jmp _th10_00462371  # e988ffffff
.globl _th10_004623e9
_th10_004623e9:
    push esi  # 56
.globl _th10_004623ea
_th10_004623ea:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_004623ee
_th10_004623ee:
    {load} mov esi, ecx  # 8bf1
.globl _th10_004623f0
_th10_004623f0:
    {disp32} call _th10_00462327  # e832ffffff
.globl _th10_004623f5
_th10_004623f5:
    {noimm8s} mov dword ptr [esi], 0x46CA00  # c70600ca4600
.globl _th10_004623fb
_th10_004623fb:
    {load} mov eax, esi  # 8bc6
.globl _th10_004623fd
_th10_004623fd:
    pop esi  # 5e
.globl _th10_004623fe
_th10_004623fe:
    {noimm8s} ret 4  # c20400
.globl _th10_00462401
_th10_00462401:
    push esi  # 56
.globl _th10_00462402
_th10_00462402:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462404
_th10_00462404:
    {disp32} call _th10_0046241d  # e814000000
.globl _th10_00462409
_th10_00462409:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_0046240e
_th10_0046240e:
    {disp8} je _th10_00462417  # 7407
.globl _th10_00462410
_th10_00462410:
    push esi  # 56
.globl _th10_00462411
_th10_00462411:
    {disp32} call _th10_004524a1  # e88b00ffff
.globl _th10_00462416
_th10_00462416:
    pop ecx  # 59
.globl _th10_00462417
_th10_00462417:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462419
_th10_00462419:
    pop esi  # 5e
.globl _th10_0046241a
_th10_0046241a:
    {noimm8s} ret 4  # c20400
.globl _th10_0046241d
_th10_0046241d:
    {noimm8s} mov dword ptr [ecx], 0x46CA00  # c70100ca4600
.globl _th10_00462423
_th10_00462423:
    {disp32} jmp _th10_00462371  # e949ffffff
.globl _th10_00462428
_th10_00462428:
    {noimm8s} mov eax, 0x4651AA  # b8aa514600
.globl _th10_0046242d
_th10_0046242d:
    {disp32} call _th10_00462adc  # e8aa060000
.globl _th10_00462432
_th10_00462432:
    sub esp, 68  # 83ec44
.globl _th10_00462435
_th10_00462435:
    {noimm8s} push 0x46CA08  # 6808ca4600
.globl _th10_0046243a
_th10_0046243a:
    {disp8} lea ecx, [ebp-0x28]  # 8d4dd8
.globl _th10_0046243d
_th10_0046243d:
    {disp32} call _th10_004624c3  # e881000000
.globl _th10_00462442
_th10_00462442:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462446
_th10_00462446:
    {disp8} lea eax, [ebp-0x28]  # 8d45d8
.globl _th10_00462449
_th10_00462449:
    push eax  # 50
.globl _th10_0046244a
_th10_0046244a:
    {disp8} lea ecx, [ebp-0x50]  # 8d4db0
.globl _th10_0046244d
_th10_0046244d:
    {disp32} call _th10_00462327  # e8d5feffff
.globl _th10_00462452
_th10_00462452:
    {noimm8s} push 0x4711BC  # 68bc114700
.globl _th10_00462457
_th10_00462457:
    {disp8} lea eax, [ebp-0x50]  # 8d45b0
.globl _th10_0046245a
_th10_0046245a:
    push eax  # 50
.globl _th10_0046245b
_th10_0046245b:
    {disp8} {noimm8s} mov dword ptr [ebp-0x50], 0x46CA00  # c745b000ca4600
.globl _th10_00462462
_th10_00462462:
    {disp32} call _th10_00462afb  # e894060000
# padding 00462467..00462467: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 1, 1, 0xcc
.globl _th10_00462468
_th10_00462468:
    {noimm8s} mov eax, 0x4651BC  # b8bc514600
.globl _th10_0046246d
_th10_0046246d:
    {disp32} call _th10_00462adc  # e86a060000
.globl _th10_00462472
_th10_00462472:
    push ecx  # 51
.globl _th10_00462473
_th10_00462473:
    push esi  # 56
.globl _th10_00462474
_th10_00462474:
    push edi  # 57
.globl _th10_00462475
_th10_00462475:
    {disp8} {load} mov edi, [ebp+8]  # 8b7d08
.globl _th10_00462478
_th10_00462478:
    {load} mov esi, ecx  # 8bf1
.globl _th10_0046247a
_th10_0046247a:
    push edi  # 57
.globl _th10_0046247b
_th10_0046247b:
    {disp8} {store} mov [ebp-0x10], esi  # 8975f0
.globl _th10_0046247e
_th10_0046247e:
    {disp32} call _th10_00462c5a  # e8d7070000
.globl _th10_00462483
_th10_00462483:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462487
_th10_00462487:
    add edi, 12  # 83c70c
.globl _th10_0046248a
_th10_0046248a:
    push edi  # 57
.globl _th10_0046248b
_th10_0046248b:
    {disp8} lea ecx, [esi+0x0C]  # 8d4e0c
.globl _th10_0046248e
_th10_0046248e:
    {noimm8s} mov dword ptr [esi], 0x46C9E8  # c706e8c94600
.globl _th10_00462494
_th10_00462494:
    {disp32} call _th10_00462301  # e868feffff
.globl _th10_00462499
_th10_00462499:
    {disp8} {load} mov ecx, [ebp-0x0C]  # 8b4df4
.globl _th10_0046249c
_th10_0046249c:
    pop edi  # 5f
.globl _th10_0046249d
_th10_0046249d:
    {load} mov eax, esi  # 8bc6
.globl _th10_0046249f
_th10_0046249f:
    pop esi  # 5e
.globl _th10_004624a0
_th10_004624a0:
    {store} mov fs:[0], ecx  # 64890d00000000
.globl _th10_004624a7
_th10_004624a7:
    leave  # c9
.globl _th10_004624a8
_th10_004624a8:
    {noimm8s} ret 4  # c20400
.globl _th10_004624ab
_th10_004624ab:
    push esi  # 56
.globl _th10_004624ac
_th10_004624ac:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_004624b0
_th10_004624b0:
    {load} mov esi, ecx  # 8bf1
.globl _th10_004624b2
_th10_004624b2:
    {disp32} call _th10_00462468  # e8b1ffffff
.globl _th10_004624b7
_th10_004624b7:
    {noimm8s} mov dword ptr [esi], 0x46CA00  # c70600ca4600
.globl _th10_004624bd
_th10_004624bd:
    {load} mov eax, esi  # 8bc6
.globl _th10_004624bf
_th10_004624bf:
    pop esi  # 5e
.globl _th10_004624c0
_th10_004624c0:
    {noimm8s} ret 4  # c20400
.globl _th10_004624c3
_th10_004624c3:
    push esi  # 56
.globl _th10_004624c4
_th10_004624c4:
    {load} mov esi, ecx  # 8bf1
.globl _th10_004624c6
_th10_004624c6:
    push 0  # 6a00
.globl _th10_004624c8
_th10_004624c8:
    {disp8} {noimm8s} mov dword ptr [esi+0x18], 0x0F  # c746180f000000
.globl _th10_004624cf
_th10_004624cf:
    {disp32} call _th10_00438590  # e8bc60fdff
.globl _th10_004624d4
_th10_004624d4:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_004624d8
_th10_004624d8:
    {load} mov ecx, esi  # 8bce
.globl _th10_004624da
_th10_004624da:
    {disp32} call _th10_00438350  # e8715efdff
.globl _th10_004624df
_th10_004624df:
    {load} mov eax, esi  # 8bc6
.globl _th10_004624e1
_th10_004624e1:
    pop esi  # 5e
.globl _th10_004624e2
_th10_004624e2:
    {noimm8s} ret 4  # c20400
.globl _th10_004624e5
_th10_004624e5:
    {noimm8s} mov eax, 0x4651CE  # b8ce514600
.globl _th10_004624ea
_th10_004624ea:
    {disp32} call _th10_00462adc  # e8ed050000
.globl _th10_004624ef
_th10_004624ef:
    sub esp, 68  # 83ec44
.globl _th10_004624f2
_th10_004624f2:
    {noimm8s} push 0x46CA20  # 6820ca4600
.globl _th10_004624f7
_th10_004624f7:
    {disp8} lea ecx, [ebp-0x28]  # 8d4dd8
.globl _th10_004624fa
_th10_004624fa:
    {disp32} call _th10_004624c3  # e8c4ffffff
.globl _th10_004624ff
_th10_004624ff:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462503
_th10_00462503:
    {disp8} lea eax, [ebp-0x28]  # 8d45d8
.globl _th10_00462506
_th10_00462506:
    push eax  # 50
.globl _th10_00462507
_th10_00462507:
    {disp8} lea ecx, [ebp-0x50]  # 8d4db0
.globl _th10_0046250a
_th10_0046250a:
    {disp32} call _th10_00462327  # e818feffff
.globl _th10_0046250f
_th10_0046250f:
    {noimm8s} push 0x471240  # 6840124700
.globl _th10_00462514
_th10_00462514:
    {disp8} lea eax, [ebp-0x50]  # 8d45b0
.globl _th10_00462517
_th10_00462517:
    push eax  # 50
.globl _th10_00462518
_th10_00462518:
    {disp8} {noimm8s} mov dword ptr [ebp-0x50], 0x46C9F4  # c745b0f4c94600
.globl _th10_0046251f
_th10_0046251f:
    {disp32} call _th10_00462afb  # e8d7050000
# padding 00462524..00462524: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 1, 1, 0xcc
.globl _th10_00462525
_th10_00462525:
    push esi  # 56
.globl _th10_00462526
_th10_00462526:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_0046252a
_th10_0046252a:
    {load} mov esi, ecx  # 8bf1
.globl _th10_0046252c
_th10_0046252c:
    {disp32} call _th10_00462468  # e837ffffff
.globl _th10_00462531
_th10_00462531:
    {noimm8s} mov dword ptr [esi], 0x46C9F4  # c706f4c94600
.globl _th10_00462537
_th10_00462537:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462539
_th10_00462539:
    pop esi  # 5e
.globl _th10_0046253a
_th10_0046253a:
    {noimm8s} ret 4  # c20400
# padding 0046253d..0046253d: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 1, 1, 0xcc
.globl _th10_0046253e
_th10_0046253e:
    jmp dword ptr [_th10_004661e8]  # ff25e8614600
.globl _th10_00462544
_th10_00462544:
    jmp dword ptr [_th10_004661e4]  # ff25e4614600
.globl _th10_0046254a
_th10_0046254a:
    jmp dword ptr [_th10_004661e0]  # ff25e0614600
.globl _th10_00462550
_th10_00462550:
    jmp dword ptr [_th10_004661b0]  # ff25b0614600
.globl _th10_00462556
_th10_00462556:
    jmp dword ptr [_th10_004661ac]  # ff25ac614600
.globl _th10_0046255c
_th10_0046255c:
    jmp dword ptr [_th10_004661a8]  # ff25a8614600
.globl _th10_00462562
_th10_00462562:
    jmp dword ptr [_th10_004661a4]  # ff25a4614600
.globl _th10_00462568
_th10_00462568:
    jmp dword ptr [_th10_004661a0]  # ff25a0614600
.globl _th10_0046256e
_th10_0046256e:
    jmp dword ptr [_th10_0046619c]  # ff259c614600
.globl _th10_00462574
_th10_00462574:
    jmp dword ptr [_th10_00466198]  # ff2598614600
.globl _th10_0046257a
_th10_0046257a:
    jmp dword ptr [_th10_00466194]  # ff2594614600
.globl _th10_00462580
_th10_00462580:
    jmp dword ptr [_th10_00466190]  # ff2590614600
.globl _th10_00462586
_th10_00462586:
    jmp dword ptr [_th10_0046618c]  # ff258c614600
.globl _th10_0046258c
_th10_0046258c:
    jmp dword ptr [_th10_00466188]  # ff2588614600
.globl _th10_00462592
_th10_00462592:
    jmp dword ptr [_th10_00466180]  # ff2580614600
.globl _th10_00462598
_th10_00462598:
    jmp dword ptr [_th10_0046617c]  # ff257c614600
.globl _th10_0046259e
_th10_0046259e:
    jmp dword ptr [_th10_00466178]  # ff2578614600
.globl _th10_004625a4
_th10_004625a4:
    jmp dword ptr [_th10_00466174]  # ff2574614600
.globl _th10_004625aa
_th10_004625aa:
    jmp dword ptr [_th10_00466170]  # ff2570614600
.globl _th10_004625b0
_th10_004625b0:
    jmp dword ptr [_th10_0046616c]  # ff256c614600
.globl _th10_004625b6
_th10_004625b6:
    jmp dword ptr [_th10_00466168]  # ff2568614600
.globl _th10_004625bc
_th10_004625bc:
    jmp dword ptr [_th10_00466164]  # ff2564614600
.globl _th10_004625c2
_th10_004625c2:
    jmp dword ptr [_th10_00466160]  # ff2560614600
.globl _th10_004625c8
_th10_004625c8:
    jmp dword ptr [_th10_0046615c]  # ff255c614600
.globl _th10_004625ce
_th10_004625ce:
    jmp dword ptr [_th10_00466158]  # ff2558614600
.globl _th10_004625d4
_th10_004625d4:
    jmp dword ptr [_th10_00466154]  # ff2554614600
.globl _th10_004625da
_th10_004625da:
    jmp dword ptr [_th10_00466150]  # ff2550614600
.globl _th10_004625e0
_th10_004625e0:
    jmp dword ptr [_th10_0046614c]  # ff254c614600
.globl _th10_004625e6
_th10_004625e6:
    jmp dword ptr [_th10_00466148]  # ff2548614600
.globl _th10_004625ec
_th10_004625ec:
    jmp dword ptr [_th10_00466144]  # ff2544614600
.globl _th10_004625f2
_th10_004625f2:
    jmp dword ptr [_th10_00466140]  # ff2540614600
.globl _th10_004625f8
_th10_004625f8:
    jmp dword ptr [_th10_0046613c]  # ff253c614600
.globl _th10_004625fe
_th10_004625fe:
    jmp dword ptr [_th10_00466138]  # ff2538614600
.globl _th10_00462604
_th10_00462604:
    jmp dword ptr [_th10_00466134]  # ff2534614600
.globl _th10_0046260a
_th10_0046260a:
    jmp dword ptr [_th10_0046609c]  # ff259c604600
.globl _th10_00462610
_th10_00462610:
    jmp dword ptr [_th10_00466098]  # ff2598604600
.globl _th10_00462616
_th10_00462616:
    jmp dword ptr [_th10_00466094]  # ff2594604600
.globl _th10_0046261c
_th10_0046261c:
    jmp dword ptr [_th10_00466090]  # ff2590604600
.globl _th10_00462622
_th10_00462622:
    jmp dword ptr [_th10_0046608c]  # ff258c604600
.globl _th10_00462628
_th10_00462628:
    jmp dword ptr [_th10_00466088]  # ff2588604600
.globl _th10_0046262e
_th10_0046262e:
    jmp dword ptr [_th10_00466084]  # ff2584604600
.globl _th10_00462634
_th10_00462634:
    jmp dword ptr [_th10_00466080]  # ff2580604600
.globl _th10_0046263a
_th10_0046263a:
    jmp dword ptr [_th10_0046607c]  # ff257c604600
.globl _th10_00462640
_th10_00462640:
    jmp dword ptr [_th10_00466078]  # ff2578604600
.globl _th10_00462646
_th10_00462646:
    jmp dword ptr [_th10_00466074]  # ff2574604600
.globl _th10_0046264c
_th10_0046264c:
    jmp dword ptr [_th10_00466070]  # ff2570604600
.globl _th10_00462652
_th10_00462652:
    jmp dword ptr [_th10_0046606c]  # ff256c604600
.globl _th10_00462658
_th10_00462658:
    jmp dword ptr [_th10_00466068]  # ff2568604600
.globl _th10_0046265e
_th10_0046265e:
    jmp dword ptr [_th10_00466064]  # ff2564604600
.globl _th10_00462664
_th10_00462664:
    jmp dword ptr [_th10_00466060]  # ff2560604600
.globl _th10_0046266a
_th10_0046266a:
    jmp dword ptr [_th10_0046605c]  # ff255c604600
.globl _th10_00462670
_th10_00462670:
    jmp dword ptr [_th10_00466058]  # ff2558604600
.globl _th10_00462676
_th10_00462676:
    jmp dword ptr [_th10_00466054]  # ff2554604600
.globl _th10_0046267c
_th10_0046267c:
    jmp dword ptr [_th10_00466050]  # ff2550604600
.globl _th10_00462682
_th10_00462682:
    jmp dword ptr [_th10_0046604c]  # ff254c604600
.globl _th10_00462688
_th10_00462688:
    jmp dword ptr [_th10_00466048]  # ff2548604600
.globl _th10_0046268e
_th10_0046268e:
    jmp dword ptr [_th10_00466044]  # ff2544604600
.globl _th10_00462694
_th10_00462694:
    jmp dword ptr [_th10_00466040]  # ff2540604600
.globl _th10_0046269a
_th10_0046269a:
    jmp dword ptr [_th10_0046603c]  # ff253c604600
.globl _th10_004626a0
_th10_004626a0:
    jmp dword ptr [_th10_004660f0]  # ff25f0604600
.globl _th10_004626a6
_th10_004626a6:
    jmp dword ptr [_th10_004661b4]  # ff25b4614600
.globl _th10_004626ac
_th10_004626ac:
    jmp dword ptr [_th10_004661b8]  # ff25b8614600
.globl _th10_004626b2
_th10_004626b2:
    jmp dword ptr [_th10_004661bc]  # ff25bc614600
.globl _th10_004626b8
_th10_004626b8:
    jmp dword ptr [_th10_004661c0]  # ff25c0614600
.globl _th10_004626be
_th10_004626be:
    jmp dword ptr [_th10_004661c4]  # ff25c4614600
.globl _th10_004626c4
_th10_004626c4:
    jmp dword ptr [_th10_004661c8]  # ff25c8614600
.globl _th10_004626ca
_th10_004626ca:
    jmp dword ptr [_th10_004661cc]  # ff25cc614600
.globl _th10_004626d0
_th10_004626d0:
    jmp dword ptr [_th10_004661d0]  # ff25d0614600
.globl _th10_004626d6
_th10_004626d6:
    push ebp  # 55
.globl _th10_004626d7
_th10_004626d7:
    {load} mov ebp, esp  # 8bec
.globl _th10_004626d9
_th10_004626d9:
    push ecx  # 51
.globl _th10_004626da
_th10_004626da:
    push ebx  # 53
.globl _th10_004626db
_th10_004626db:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_004626de
_th10_004626de:
    add eax, 12  # 83c00c
.globl _th10_004626e1
_th10_004626e1:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_004626e4
_th10_004626e4:
    {load} mov ebx, fs:[0]  # 648b1d00000000
.globl _th10_004626eb
_th10_004626eb:
    {load} mov eax, [ebx]  # 8b03
.globl _th10_004626ed
_th10_004626ed:
    mov fs:[0], eax  # 64a300000000
.globl _th10_004626f3
_th10_004626f3:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004626f6
_th10_004626f6:
    {disp8} {load} mov ebx, [ebp+0x0C]  # 8b5d0c
.globl _th10_004626f9
_th10_004626f9:
    {disp8} {load} mov esp, [ebx-4]  # 8b63fc
.globl _th10_004626fc
_th10_004626fc:
    {disp8} {load} mov ebp, [ebp-4]  # 8b6dfc
.globl _th10_004626ff
_th10_004626ff:
    jmp eax  # ffe0
.globl _th10_00462701
_th10_00462701:
    pop ebx  # 5b
.globl _th10_00462702
_th10_00462702:
    leave  # c9
.globl _th10_00462703
_th10_00462703:
    {noimm8s} ret 8  # c20800
.globl _th10_00462706
_th10_00462706:
    pop eax  # 58
.globl _th10_00462707
_th10_00462707:
    pop ecx  # 59
.globl _th10_00462708
_th10_00462708:
    xchg [esp], eax  # 870424
.globl _th10_0046270b
_th10_0046270b:
    jmp eax  # ffe0
.globl _th10_0046270d
_th10_0046270d:
    pop eax  # 58
.globl _th10_0046270e
_th10_0046270e:
    pop ecx  # 59
.globl _th10_0046270f
_th10_0046270f:
    xchg [esp], eax  # 870424
.globl _th10_00462712
_th10_00462712:
    jmp eax  # ffe0
.globl _th10_00462714
_th10_00462714:
    pop eax  # 58
.globl _th10_00462715
_th10_00462715:
    pop ecx  # 59
.globl _th10_00462716
_th10_00462716:
    xchg [esp], eax  # 870424
.globl _th10_00462719
_th10_00462719:
    jmp eax  # ffe0
.globl _th10_0046271b
_th10_0046271b:
    push ebp  # 55
.globl _th10_0046271c
_th10_0046271c:
    {load} mov ebp, esp  # 8bec
.globl _th10_0046271e
_th10_0046271e:
    push ecx  # 51
.globl _th10_0046271f
_th10_0046271f:
    push ecx  # 51
.globl _th10_00462720
_th10_00462720:
    push ebx  # 53
.globl _th10_00462721
_th10_00462721:
    push esi  # 56
.globl _th10_00462722
_th10_00462722:
    push edi  # 57
.globl _th10_00462723
_th10_00462723:
    {load} mov esi, fs:[0]  # 648b3500000000
.globl _th10_0046272a
_th10_0046272a:
    {disp8} {store} mov [ebp-4], esi  # 8975fc
.globl _th10_0046272d
_th10_0046272d:
    {disp8} {noimm8s} mov dword ptr [ebp-8], 0x462744  # c745f844274600
.globl _th10_00462734
_th10_00462734:
    push 0  # 6a00
.globl _th10_00462736
_th10_00462736:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00462739
_th10_00462739:
    {disp8} push dword ptr [ebp-8]  # ff75f8
.globl _th10_0046273c
_th10_0046273c:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046273f
_th10_0046273f:
    {disp32} call _th10_0046263a  # e8f6feffff
.globl _th10_00462744
_th10_00462744:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462747
_th10_00462747:
    {disp8} {load} mov eax, [eax+4]  # 8b4004
.globl _th10_0046274a
_th10_0046274a:
    and eax, -3  # 83e0fd
.globl _th10_0046274d
_th10_0046274d:
    {disp8} {load} mov ecx, [ebp+0x0C]  # 8b4d0c
.globl _th10_00462750
_th10_00462750:
    {disp8} {store} mov [ecx+4], eax  # 894104
.globl _th10_00462753
_th10_00462753:
    {load} mov edi, fs:[0]  # 648b3d00000000
.globl _th10_0046275a
_th10_0046275a:
    {disp8} {load} mov ebx, [ebp-4]  # 8b5dfc
.globl _th10_0046275d
_th10_0046275d:
    {store} mov [ebx], edi  # 893b
.globl _th10_0046275f
_th10_0046275f:
    {store} mov fs:[0], ebx  # 64891d00000000
.globl _th10_00462766
_th10_00462766:
    pop edi  # 5f
.globl _th10_00462767
_th10_00462767:
    pop esi  # 5e
.globl _th10_00462768
_th10_00462768:
    pop ebx  # 5b
.globl _th10_00462769
_th10_00462769:
    leave  # c9
.globl _th10_0046276a
_th10_0046276a:
    {noimm8s} ret 8  # c20800
.globl _th10_0046276d
_th10_0046276d:
    push ebp  # 55
.globl _th10_0046276e
_th10_0046276e:
    {load} mov ebp, esp  # 8bec
.globl _th10_00462770
_th10_00462770:
    sub esp, 4  # 83ec04
.globl _th10_00462773
_th10_00462773:
    push ebx  # 53
.globl _th10_00462774
_th10_00462774:
    push esi  # 56
.globl _th10_00462775
_th10_00462775:
    push edi  # 57
.globl _th10_00462776
_th10_00462776:
    cld  # fc
.globl _th10_00462777
_th10_00462777:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_0046277a
_th10_0046277a:
    {load} xor eax, eax  # 33c0
.globl _th10_0046277c
_th10_0046277c:
    push eax  # 50
.globl _th10_0046277d
_th10_0046277d:
    push eax  # 50
.globl _th10_0046277e
_th10_0046277e:
    push eax  # 50
.globl _th10_0046277f
_th10_0046277f:
    {disp8} push dword ptr [ebp-4]  # ff75fc
.globl _th10_00462782
_th10_00462782:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00462785
_th10_00462785:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_00462788
_th10_00462788:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_0046278b
_th10_0046278b:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046278e
_th10_0046278e:
    {disp32} call _th10_00463963  # e8d0110000
.globl _th10_00462793
_th10_00462793:
    add esp, 32  # 83c420
.globl _th10_00462796
_th10_00462796:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_00462799
_th10_00462799:
    pop edi  # 5f
.globl _th10_0046279a
_th10_0046279a:
    pop esi  # 5e
.globl _th10_0046279b
_th10_0046279b:
    pop ebx  # 5b
.globl _th10_0046279c
_th10_0046279c:
    {disp8} {load} mov eax, [ebp-4]  # 8b45fc
.globl _th10_0046279f
_th10_0046279f:
    {load} mov esp, ebp  # 8be5
.globl _th10_004627a1
_th10_004627a1:
    pop ebp  # 5d
.globl _th10_004627a2
_th10_004627a2:
    ret  # c3
.globl _th10_004627a3
_th10_004627a3:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_004627a7
_th10_004627a7:
    {disp8} push dword ptr [eax+0x1C]  # ff701c
.globl _th10_004627aa
_th10_004627aa:
    {disp8} push dword ptr [eax+0x28]  # ff7028
.globl _th10_004627ad
_th10_004627ad:
    push 0  # 6a00
.globl _th10_004627af
_th10_004627af:
    {disp8} push dword ptr [eax+0x18]  # ff7018
.globl _th10_004627b2
_th10_004627b2:
    {disp32} call _th10_00462e7e  # e8c7060000
.globl _th10_004627b7
_th10_004627b7:
    add esp, 16  # 83c410
.globl _th10_004627ba
_th10_004627ba:
    {noimm8s} ret 4  # c20400
.globl _th10_004627bd
_th10_004627bd:
    cld  # fc
.globl _th10_004627be
_th10_004627be:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_004627c2
_th10_004627c2:
    {disp8} {load} mov ecx, [eax+8]  # 8b4808
.globl _th10_004627c5
_th10_004627c5:
    {load} cmp ecx, [_th10_00473660]  # 3b0d60364700
.globl _th10_004627cb
_th10_004627cb:
    {disp8} je _th10_004627d9  # 740c
.globl _th10_004627cd
_th10_004627cd:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_004627d1
_th10_004627d1:
    {disp8} or dword ptr [eax+4], 8  # 83480408
.globl _th10_004627d5
_th10_004627d5:
    {load} xor eax, eax  # 33c0
.globl _th10_004627d7
_th10_004627d7:
    inc eax  # 40
.globl _th10_004627d8
_th10_004627d8:
    ret  # c3
.globl _th10_004627d9
_th10_004627d9:
    push 0  # 6a00
.globl _th10_004627db
_th10_004627db:
    push eax  # 50
.globl _th10_004627dc
_th10_004627dc:
    {disp8} push dword ptr [eax+0x14]  # ff7014
.globl _th10_004627df
_th10_004627df:
    {disp8} push dword ptr [eax+0x0C]  # ff700c
.globl _th10_004627e2
_th10_004627e2:
    push 0  # 6a00
.globl _th10_004627e4
_th10_004627e4:
    {disp8} push dword ptr [esp+0x20]  # ff742420
.globl _th10_004627e8
_th10_004627e8:
    {disp8} push dword ptr [eax+0x10]  # ff7010
.globl _th10_004627eb
_th10_004627eb:
    {disp8} push dword ptr [esp+0x20]  # ff742420
.globl _th10_004627ef
_th10_004627ef:
    {disp32} call _th10_00463963  # e86f110000
.globl _th10_004627f4
_th10_004627f4:
    add esp, 32  # 83c420
.globl _th10_004627f7
_th10_004627f7:
    ret  # c3
.globl _th10_004627f8
_th10_004627f8:
    push ebp  # 55
.globl _th10_004627f9
_th10_004627f9:
    {load} mov ebp, esp  # 8bec
.globl _th10_004627fb
_th10_004627fb:
    sub esp, 52  # 83ec34
.globl _th10_004627fe
_th10_004627fe:
    push ebx  # 53
.globl _th10_004627ff
_th10_004627ff:
    {disp8} {noimm8s} cmp dword ptr [ebp+8], 0x123  # 817d0823010000
.globl _th10_00462806
_th10_00462806:
    {disp8} jne _th10_0046281a  # 7512
.globl _th10_00462808
_th10_00462808:
    {noimm8s} mov eax, 0x462893  # b893284600
.globl _th10_0046280d
_th10_0046280d:
    {disp8} {load} mov ecx, [ebp+0x0C]  # 8b4d0c
.globl _th10_00462810
_th10_00462810:
    {store} mov [ecx], eax  # 8901
.globl _th10_00462812
_th10_00462812:
    {load} xor eax, eax  # 33c0
.globl _th10_00462814
_th10_00462814:
    inc eax  # 40
.globl _th10_00462815
_th10_00462815:
    {disp32} jmp _th10_004628bc  # e9a2000000
.globl _th10_0046281a
_th10_0046281a:
    {disp8} and dword ptr [ebp-0x28], 0  # 8365d800
.globl _th10_0046281e
_th10_0046281e:
    {disp8} {noimm8s} mov dword ptr [ebp-0x24], 0x4628BF  # c745dcbf284600
.globl _th10_00462825
_th10_00462825:
    mov eax, [_th10_00473660]  # a160364700
.globl _th10_0046282a
_th10_0046282a:
    {disp8} {store} mov [ebp-0x20], eax  # 8945e0
.globl _th10_0046282d
_th10_0046282d:
    {disp8} {load} mov eax, [ebp+0x18]  # 8b4518
.globl _th10_00462830
_th10_00462830:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_00462833
_th10_00462833:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462836
_th10_00462836:
    {disp8} {store} mov [ebp-0x18], eax  # 8945e8
.globl _th10_00462839
_th10_00462839:
    {disp8} {load} mov eax, [ebp+0x1C]  # 8b451c
.globl _th10_0046283c
_th10_0046283c:
    {disp8} {store} mov [ebp-0x14], eax  # 8945ec
.globl _th10_0046283f
_th10_0046283f:
    {disp8} {load} mov eax, [ebp+0x20]  # 8b4520
.globl _th10_00462842
_th10_00462842:
    {disp8} {store} mov [ebp-0x10], eax  # 8945f0
.globl _th10_00462845
_th10_00462845:
    {disp8} and dword ptr [ebp-0x0C], 0  # 8365f400
.globl _th10_00462849
_th10_00462849:
    {disp8} and dword ptr [ebp-8], 0  # 8365f800
.globl _th10_0046284d
_th10_0046284d:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462851
_th10_00462851:
    {disp8} {store} mov [ebp-0x0C], esp  # 8965f4
.globl _th10_00462854
_th10_00462854:
    {disp8} {store} mov [ebp-8], ebp  # 896df8
.globl _th10_00462857
_th10_00462857:
    mov eax, fs:[0]  # 64a100000000
.globl _th10_0046285d
_th10_0046285d:
    {disp8} {store} mov [ebp-0x28], eax  # 8945d8
.globl _th10_00462860
_th10_00462860:
    {disp8} lea eax, [ebp-0x28]  # 8d45d8
.globl _th10_00462863
_th10_00462863:
    mov fs:[0], eax  # 64a300000000
.globl _th10_00462869
_th10_00462869:
    {disp8} {noimm8s} mov dword ptr [ebp-0x34], 1  # c745cc01000000
.globl _th10_00462870
_th10_00462870:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00462873
_th10_00462873:
    {disp8} {store} mov [ebp-0x30], eax  # 8945d0
.globl _th10_00462876
_th10_00462876:
    {disp8} {load} mov eax, [ebp+0x10]  # 8b4510
.globl _th10_00462879
_th10_00462879:
    {disp8} {store} mov [ebp-0x2C], eax  # 8945d4
.globl _th10_0046287c
_th10_0046287c:
    {disp8} lea eax, [ebp-0x30]  # 8d45d0
.globl _th10_0046287f
_th10_0046287f:
    push eax  # 50
.globl _th10_00462880
_th10_00462880:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00462883
_th10_00462883:
    push dword ptr [eax]  # ff30
.globl _th10_00462885
_th10_00462885:
    {disp32} call _th10_00456357  # e8cd3affff
.globl _th10_0046288a
_th10_0046288a:
    {disp8} call dword ptr [eax+0x74]  # ff5074
.globl _th10_0046288d
_th10_0046288d:
    pop ecx  # 59
.globl _th10_0046288e
_th10_0046288e:
    pop ecx  # 59
.globl _th10_0046288f
_th10_0046288f:
    {disp8} and dword ptr [ebp-0x34], 0  # 8365cc00
.globl _th10_00462893
_th10_00462893:
    {disp8} cmp dword ptr [ebp-4], 0  # 837dfc00
.globl _th10_00462897
_th10_00462897:
    {disp8} je _th10_004628b0  # 7417
.globl _th10_00462899
_th10_00462899:
    {load} mov ebx, fs:[0]  # 648b1d00000000
.globl _th10_004628a0
_th10_004628a0:
    {load} mov eax, [ebx]  # 8b03
.globl _th10_004628a2
_th10_004628a2:
    {disp8} {load} mov ebx, [ebp-0x28]  # 8b5dd8
.globl _th10_004628a5
_th10_004628a5:
    {store} mov [ebx], eax  # 8903
.globl _th10_004628a7
_th10_004628a7:
    {store} mov fs:[0], ebx  # 64891d00000000
.globl _th10_004628ae
_th10_004628ae:
    {disp8} jmp _th10_004628b9  # eb09
.globl _th10_004628b0
_th10_004628b0:
    {disp8} {load} mov eax, [ebp-0x28]  # 8b45d8
.globl _th10_004628b3
_th10_004628b3:
    mov fs:[0], eax  # 64a300000000
.globl _th10_004628b9
_th10_004628b9:
    {disp8} {load} mov eax, [ebp-0x34]  # 8b45cc
.globl _th10_004628bc
_th10_004628bc:
    pop ebx  # 5b
.globl _th10_004628bd
_th10_004628bd:
    leave  # c9
.globl _th10_004628be
_th10_004628be:
    ret  # c3
.globl _th10_004628bf
_th10_004628bf:
    push ebp  # 55
.globl _th10_004628c0
_th10_004628c0:
    {load} mov ebp, esp  # 8bec
.globl _th10_004628c2
_th10_004628c2:
    push ecx  # 51
.globl _th10_004628c3
_th10_004628c3:
    push ebx  # 53
.globl _th10_004628c4
_th10_004628c4:
    cld  # fc
.globl _th10_004628c5
_th10_004628c5:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_004628c8
_th10_004628c8:
    {disp8} {load} mov eax, [eax+8]  # 8b4008
.globl _th10_004628cb
_th10_004628cb:
    {load} cmp eax, [_th10_00473660]  # 3b0560364700
.globl _th10_004628d1
_th10_004628d1:
    {disp8} je _th10_004628ea  # 7417
.globl _th10_004628d3
_th10_004628d3:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004628d6
_th10_004628d6:
    {disp8} {load} mov eax, [eax+4]  # 8b4004
.globl _th10_004628d9
_th10_004628d9:
    or eax, 8  # 83c808
.globl _th10_004628dc
_th10_004628dc:
    {disp8} {load} mov ecx, [ebp+8]  # 8b4d08
.globl _th10_004628df
_th10_004628df:
    {disp8} {store} mov [ecx+4], eax  # 894104
.globl _th10_004628e2
_th10_004628e2:
    {load} xor eax, eax  # 33c0
.globl _th10_004628e4
_th10_004628e4:
    inc eax  # 40
.globl _th10_004628e5
_th10_004628e5:
    {disp32} jmp _th10_0046296e  # e984000000
.globl _th10_004628ea
_th10_004628ea:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004628ed
_th10_004628ed:
    {disp8} {load} mov eax, [eax+4]  # 8b4004
.globl _th10_004628f0
_th10_004628f0:
    and eax, 102  # 83e066
.globl _th10_004628f3
_th10_004628f3:
    {disp8} je _th10_00462904  # 740f
.globl _th10_004628f5
_th10_004628f5:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_004628f8
_th10_004628f8:
    {disp8} {noimm8s} mov dword ptr [eax+0x24], 1  # c7402401000000
.globl _th10_004628ff
_th10_004628ff:
    {load} xor eax, eax  # 33c0
.globl _th10_00462901
_th10_00462901:
    inc eax  # 40
.globl _th10_00462902
_th10_00462902:
    {disp8} jmp _th10_0046296e  # eb6a
.globl _th10_00462904
_th10_00462904:
    push 1  # 6a01
.globl _th10_00462906
_th10_00462906:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462909
_th10_00462909:
    {disp8} push dword ptr [eax+0x18]  # ff7018
.globl _th10_0046290c
_th10_0046290c:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_0046290f
_th10_0046290f:
    {disp8} push dword ptr [eax+0x14]  # ff7014
.globl _th10_00462912
_th10_00462912:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462915
_th10_00462915:
    {disp8} push dword ptr [eax+0x0C]  # ff700c
.globl _th10_00462918
_th10_00462918:
    push 0  # 6a00
.globl _th10_0046291a
_th10_0046291a:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_0046291d
_th10_0046291d:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462920
_th10_00462920:
    {disp8} push dword ptr [eax+0x10]  # ff7010
.globl _th10_00462923
_th10_00462923:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00462926
_th10_00462926:
    {disp32} call _th10_00463963  # e838100000
.globl _th10_0046292b
_th10_0046292b:
    add esp, 32  # 83c420
.globl _th10_0046292e
_th10_0046292e:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462931
_th10_00462931:
    {disp8} cmp dword ptr [eax+0x24], 0  # 83782400
.globl _th10_00462935
_th10_00462935:
    {disp8} jne _th10_00462942  # 750b
.globl _th10_00462937
_th10_00462937:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046293a
_th10_0046293a:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_0046293d
_th10_0046293d:
    {disp32} call _th10_0046271b  # e8d9fdffff
.globl _th10_00462942
_th10_00462942:
    push 0  # 6a00
.globl _th10_00462944
_th10_00462944:
    push 0  # 6a00
.globl _th10_00462946
_th10_00462946:
    push 0  # 6a00
.globl _th10_00462948
_th10_00462948:
    push 0  # 6a00
.globl _th10_0046294a
_th10_0046294a:
    push 0  # 6a00
.globl _th10_0046294c
_th10_0046294c:
    {disp8} lea eax, [ebp-4]  # 8d45fc
.globl _th10_0046294f
_th10_0046294f:
    push eax  # 50
.globl _th10_00462950
_th10_00462950:
    {noimm8s} push 0x123  # 6823010000
.globl _th10_00462955
_th10_00462955:
    {disp32} call _th10_004627f8  # e89efeffff
.globl _th10_0046295a
_th10_0046295a:
    add esp, 28  # 83c41c
.globl _th10_0046295d
_th10_0046295d:
    {disp8} {load} mov eax, [ebp-4]  # 8b45fc
.globl _th10_00462960
_th10_00462960:
    {disp8} {load} mov ebx, [ebp+0x0C]  # 8b5d0c
.globl _th10_00462963
_th10_00462963:
    {disp8} {load} mov esp, [ebx+0x1C]  # 8b631c
.globl _th10_00462966
_th10_00462966:
    {disp8} {load} mov ebp, [ebx+0x20]  # 8b6b20
.globl _th10_00462969
_th10_00462969:
    jmp eax  # ffe0
.globl _th10_0046296b
_th10_0046296b:
    {load} xor eax, eax  # 33c0
.globl _th10_0046296d
_th10_0046296d:
    inc eax  # 40
.globl _th10_0046296e
_th10_0046296e:
    pop ebx  # 5b
.globl _th10_0046296f
_th10_0046296f:
    leave  # c9
.globl _th10_00462970
_th10_00462970:
    ret  # c3
.globl _th10_00462971
_th10_00462971:
    push ebp  # 55
.globl _th10_00462972
_th10_00462972:
    {load} mov ebp, esp  # 8bec
.globl _th10_00462974
_th10_00462974:
    push ecx  # 51
.globl _th10_00462975
_th10_00462975:
    {disp8} cmp dword ptr [ebp+0x0C], 0  # 837d0c00
.globl _th10_00462979
_th10_00462979:
    push ebx  # 53
.globl _th10_0046297a
_th10_0046297a:
    push esi  # 56
.globl _th10_0046297b
_th10_0046297b:
    push edi  # 57
.globl _th10_0046297c
_th10_0046297c:
    {disp8} {load} mov edi, [ebp+8]  # 8b7d08
.globl _th10_0046297f
_th10_0046297f:
    {disp8} {load} mov esi, [edi+0x0C]  # 8b770c
.globl _th10_00462982
_th10_00462982:
    {disp8} {load} mov ebx, [edi+0x10]  # 8b5f10
.globl _th10_00462985
_th10_00462985:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462987
_th10_00462987:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_0046298a
_th10_0046298a:
    {disp8} {store} mov [ebp+8], esi  # 897508
.globl _th10_0046298d
_th10_0046298d:
    {disp8} jl _th10_004629c7  # 7c38
.globl _th10_0046298f
_th10_0046298f:
    cmp esi, -1  # 83feff
.globl _th10_00462992
_th10_00462992:
    {disp8} jne _th10_00462999  # 7505
.globl _th10_00462994
_th10_00462994:
    {disp32} call _th10_004556e0  # e8472dffff
.globl _th10_00462999
_th10_00462999:
    {disp8} {load} mov ecx, [ebp+0x10]  # 8b4d10
.globl _th10_0046299c
_th10_0046299c:
    dec esi  # 4e
.globl _th10_0046299d
_th10_0046299d:
    lea eax, [esi+esi*4]  # 8d04b6
.globl _th10_004629a0
_th10_004629a0:
    lea eax, [ebx+eax*4]  # 8d0483
.globl _th10_004629a3
_th10_004629a3:
    {disp8} {store} cmp [eax+4], ecx  # 394804
.globl _th10_004629a6
_th10_004629a6:
    {disp8} jge _th10_004629ad  # 7d05
.globl _th10_004629a8
_th10_004629a8:
    {disp8} {load} cmp ecx, [eax+8]  # 3b4808
.globl _th10_004629ab
_th10_004629ab:
    {disp8} jle _th10_004629b2  # 7e05
.globl _th10_004629ad
_th10_004629ad:
    cmp esi, -1  # 83feff
.globl _th10_004629b0
_th10_004629b0:
    {disp8} jne _th10_004629be  # 750c
.globl _th10_004629b2
_th10_004629b2:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004629b5
_th10_004629b5:
    {disp8} dec dword ptr [ebp+0x0C]  # ff4d0c
.globl _th10_004629b8
_th10_004629b8:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_004629bb
_th10_004629bb:
    {disp8} {store} mov [ebp+8], esi  # 897508
.globl _th10_004629be
_th10_004629be:
    {disp8} cmp dword ptr [ebp+0x0C], 0  # 837d0c00
.globl _th10_004629c2
_th10_004629c2:
    {disp8} jge _th10_0046298f  # 7dcb
.globl _th10_004629c4
_th10_004629c4:
    {disp8} {load} mov eax, [ebp-4]  # 8b45fc
.globl _th10_004629c7
_th10_004629c7:
    {disp8} {load} mov ecx, [ebp+0x14]  # 8b4d14
.globl _th10_004629ca
_th10_004629ca:
    inc esi  # 46
.globl _th10_004629cb
_th10_004629cb:
    {store} mov [ecx], esi  # 8931
.globl _th10_004629cd
_th10_004629cd:
    {disp8} {load} mov ecx, [ebp+0x18]  # 8b4d18
.globl _th10_004629d0
_th10_004629d0:
    {store} mov [ecx], eax  # 8901
.globl _th10_004629d2
_th10_004629d2:
    {disp8} {load} cmp eax, [edi+0x0C]  # 3b470c
.globl _th10_004629d5
_th10_004629d5:
    {disp8} ja _th10_004629db  # 7704
.globl _th10_004629d7
_th10_004629d7:
    {load} cmp esi, eax  # 3bf0
.globl _th10_004629d9
_th10_004629d9:
    {disp8} jbe _th10_004629e0  # 7605
.globl _th10_004629db
_th10_004629db:
    {disp32} call _th10_004556e0  # e8002dffff
.globl _th10_004629e0
_th10_004629e0:
    pop edi  # 5f
.globl _th10_004629e1
_th10_004629e1:
    lea eax, [esi+esi*4]  # 8d04b6
.globl _th10_004629e4
_th10_004629e4:
    pop esi  # 5e
.globl _th10_004629e5
_th10_004629e5:
    lea eax, [ebx+eax*4]  # 8d0483
.globl _th10_004629e8
_th10_004629e8:
    pop ebx  # 5b
.globl _th10_004629e9
_th10_004629e9:
    leave  # c9
.globl _th10_004629ea
_th10_004629ea:
    ret  # c3
.globl _th10_004629eb
_th10_004629eb:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_004629ef
_th10_004629ef:
    push esi  # 56
.globl _th10_004629f0
_th10_004629f0:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_004629f4
_th10_004629f4:
    {store} mov [esi], eax  # 8906
.globl _th10_004629f6
_th10_004629f6:
    {disp32} call _th10_00456357  # e85c39ffff
.globl _th10_004629fb
_th10_004629fb:
    {load} mov eax, [eax+0x88]  # 8b8088000000
.globl _th10_00462a01
_th10_00462a01:
    {disp8} {store} mov [esi+4], eax  # 894604
.globl _th10_00462a04
_th10_00462a04:
    {disp32} call _th10_00456357  # e84e39ffff
.globl _th10_00462a09
_th10_00462a09:
    {store} mov [eax+0x88], esi  # 89b088000000
.globl _th10_00462a0f
_th10_00462a0f:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462a11
_th10_00462a11:
    pop esi  # 5e
.globl _th10_00462a12
_th10_00462a12:
    ret  # c3
.globl _th10_00462a13
_th10_00462a13:
    {disp32} call _th10_00456357  # e83f39ffff
.globl _th10_00462a18
_th10_00462a18:
    {load} mov eax, [eax+0x88]  # 8b8088000000
.globl _th10_00462a1e
_th10_00462a1e:
    {disp8} jmp _th10_00462a2b  # eb0b
.globl _th10_00462a20
_th10_00462a20:
    {load} mov ecx, [eax]  # 8b08
.globl _th10_00462a22
_th10_00462a22:
    {disp8} {load} cmp ecx, [esp+4]  # 3b4c2404
.globl _th10_00462a26
_th10_00462a26:
    {disp8} je _th10_00462a31  # 7409
.globl _th10_00462a28
_th10_00462a28:
    {disp8} {load} mov eax, [eax+4]  # 8b4004
.globl _th10_00462a2b
_th10_00462a2b:
    test eax, eax  # 85c0
.globl _th10_00462a2d
_th10_00462a2d:
    {disp8} jne _th10_00462a20  # 75f1
.globl _th10_00462a2f
_th10_00462a2f:
    inc eax  # 40
.globl _th10_00462a30
_th10_00462a30:
    ret  # c3
.globl _th10_00462a31
_th10_00462a31:
    {load} xor eax, eax  # 33c0
.globl _th10_00462a33
_th10_00462a33:
    ret  # c3
.globl _th10_00462a34
_th10_00462a34:
    push esi  # 56
.globl _th10_00462a35
_th10_00462a35:
    {disp32} call _th10_00456357  # e81d39ffff
.globl _th10_00462a3a
_th10_00462a3a:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_00462a3e
_th10_00462a3e:
    {load} cmp esi, [eax+0x88]  # 3bb088000000
.globl _th10_00462a44
_th10_00462a44:
    {disp8} jne _th10_00462a56  # 7510
.globl _th10_00462a46
_th10_00462a46:
    {disp32} call _th10_00456357  # e80c39ffff
.globl _th10_00462a4b
_th10_00462a4b:
    {disp8} {load} mov ecx, [esi+4]  # 8b4e04
.globl _th10_00462a4e
_th10_00462a4e:
    {store} mov [eax+0x88], ecx  # 898888000000
.globl _th10_00462a54
_th10_00462a54:
    pop esi  # 5e
.globl _th10_00462a55
_th10_00462a55:
    ret  # c3
.globl _th10_00462a56
_th10_00462a56:
    {disp32} call _th10_00456357  # e8fc38ffff
.globl _th10_00462a5b
_th10_00462a5b:
    {load} mov eax, [eax+0x88]  # 8b8088000000
.globl _th10_00462a61
_th10_00462a61:
    {disp8} jmp _th10_00462a6c  # eb09
.globl _th10_00462a63
_th10_00462a63:
    {disp8} {load} mov ecx, [eax+4]  # 8b4804
.globl _th10_00462a66
_th10_00462a66:
    {load} cmp esi, ecx  # 3bf1
.globl _th10_00462a68
_th10_00462a68:
    {disp8} je _th10_00462a78  # 740e
.globl _th10_00462a6a
_th10_00462a6a:
    {load} mov eax, ecx  # 8bc1
.globl _th10_00462a6c
_th10_00462a6c:
    {disp8} cmp dword ptr [eax+4], 0  # 83780400
.globl _th10_00462a70
_th10_00462a70:
    {disp8} jne _th10_00462a63  # 75f1
.globl _th10_00462a72
_th10_00462a72:
    pop esi  # 5e
.globl _th10_00462a73
_th10_00462a73:
    {disp32} jmp _th10_004556e0  # e9682cffff
.globl _th10_00462a78
_th10_00462a78:
    {disp8} {load} mov ecx, [esi+4]  # 8b4e04
.globl _th10_00462a7b
_th10_00462a7b:
    {disp8} {store} mov [eax+4], ecx  # 894804
.globl _th10_00462a7e
_th10_00462a7e:
    pop esi  # 5e
.globl _th10_00462a7f
_th10_00462a7f:
    ret  # c3
.globl _th10_00462a80
_th10_00462a80:
    push ebp  # 55
.globl _th10_00462a81
_th10_00462a81:
    {load} mov ebp, esp  # 8bec
.globl _th10_00462a83
_th10_00462a83:
    sub esp, 24  # 83ec18
.globl _th10_00462a86
_th10_00462a86:
    mov eax, [_th10_00473660]  # a160364700
.globl _th10_00462a8b
_th10_00462a8b:
    {disp8} and dword ptr [ebp-0x18], 0  # 8365e800
.globl _th10_00462a8f
_th10_00462a8f:
    {disp8} {load} mov ecx, [ebp+8]  # 8b4d08
.globl _th10_00462a92
_th10_00462a92:
    {disp8} {store} mov [ebp-0x10], eax  # 8945f0
.globl _th10_00462a95
_th10_00462a95:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462a98
_th10_00462a98:
    {disp8} {store} mov [ebp-0x0C], eax  # 8945f4
.globl _th10_00462a9b
_th10_00462a9b:
    {disp8} {load} mov eax, [ebp+0x14]  # 8b4514
.globl _th10_00462a9e
_th10_00462a9e:
    inc eax  # 40
.globl _th10_00462a9f
_th10_00462a9f:
    {disp8} {noimm8s} mov dword ptr [ebp-0x14], 0x4627BD  # c745ecbd274600
.globl _th10_00462aa6
_th10_00462aa6:
    {disp8} {store} mov [ebp-8], ecx  # 894df8
.globl _th10_00462aa9
_th10_00462aa9:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_00462aac
_th10_00462aac:
    mov eax, fs:[0]  # 64a100000000
.globl _th10_00462ab2
_th10_00462ab2:
    {disp8} {store} mov [ebp-0x18], eax  # 8945e8
.globl _th10_00462ab5
_th10_00462ab5:
    {disp8} lea eax, [ebp-0x18]  # 8d45e8
.globl _th10_00462ab8
_th10_00462ab8:
    mov fs:[0], eax  # 64a300000000
.globl _th10_00462abe
_th10_00462abe:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_00462ac1
_th10_00462ac1:
    push ecx  # 51
.globl _th10_00462ac2
_th10_00462ac2:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_00462ac5
_th10_00462ac5:
    {disp32} call _th10_00463a10  # e8460f0000
.globl _th10_00462aca
_th10_00462aca:
    {load} mov ecx, eax  # 8bc8
.globl _th10_00462acc
_th10_00462acc:
    {disp8} {load} mov eax, [ebp-0x18]  # 8b45e8
.globl _th10_00462acf
_th10_00462acf:
    mov fs:[0], eax  # 64a300000000
.globl _th10_00462ad5
_th10_00462ad5:
    {load} mov eax, ecx  # 8bc1
.globl _th10_00462ad7
_th10_00462ad7:
    leave  # c9
.globl _th10_00462ad8
_th10_00462ad8:
    ret  # c3
# padding 00462ad9..00462adb: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 3, 1, 0xcc
.globl _th10_00462adc
_th10_00462adc:
    push -1  # 6aff
.globl _th10_00462ade
_th10_00462ade:
    push eax  # 50
.globl _th10_00462adf
_th10_00462adf:
    mov eax, fs:[0]  # 64a100000000
.globl _th10_00462ae5
_th10_00462ae5:
    push eax  # 50
.globl _th10_00462ae6
_th10_00462ae6:
    {disp8} {load} mov eax, [esp+0x0C]  # 8b44240c
.globl _th10_00462aea
_th10_00462aea:
    {store} mov fs:[0], esp  # 64892500000000
.globl _th10_00462af1
_th10_00462af1:
    {disp8} {store} mov [esp+0x0C], ebp  # 896c240c
.globl _th10_00462af5
_th10_00462af5:
    {disp8} lea ebp, [esp+0x0C]  # 8d6c240c
.globl _th10_00462af9
_th10_00462af9:
    push eax  # 50
.globl _th10_00462afa
_th10_00462afa:
    ret  # c3
.globl _th10_00462afb
_th10_00462afb:
    push ebp  # 55
.globl _th10_00462afc
_th10_00462afc:
    {load} mov ebp, esp  # 8bec
.globl _th10_00462afe
_th10_00462afe:
    sub esp, 32  # 83ec20
.globl _th10_00462b01
_th10_00462b01:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00462b04
_th10_00462b04:
    push esi  # 56
.globl _th10_00462b05
_th10_00462b05:
    push edi  # 57
.globl _th10_00462b06
_th10_00462b06:
    push 8  # 6a08
.globl _th10_00462b08
_th10_00462b08:
    pop ecx  # 59
.globl _th10_00462b09
_th10_00462b09:
    {noimm8s} mov esi, 0x46CA30  # be30ca4600
.globl _th10_00462b0e
_th10_00462b0e:
    {disp8} lea edi, [ebp-0x20]  # 8d7de0
.globl _th10_00462b11
_th10_00462b11:
    rep movsd  # f3a5
.globl _th10_00462b13
_th10_00462b13:
    {disp8} {store} mov [ebp-8], eax  # 8945f8
.globl _th10_00462b16
_th10_00462b16:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00462b19
_th10_00462b19:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_00462b1c
_th10_00462b1c:
    {disp8} lea eax, [ebp-0x0C]  # 8d45f4
.globl _th10_00462b1f
_th10_00462b1f:
    push eax  # 50
.globl _th10_00462b20
_th10_00462b20:
    {disp8} push dword ptr [ebp-0x10]  # ff75f0
.globl _th10_00462b23
_th10_00462b23:
    {disp8} push dword ptr [ebp-0x1C]  # ff75e4
.globl _th10_00462b26
_th10_00462b26:
    {disp8} push dword ptr [ebp-0x20]  # ff75e0
.globl _th10_00462b29
_th10_00462b29:
    call dword ptr [_th10_00466044]  # ff1544604600
.globl _th10_00462b2f
_th10_00462b2f:
    pop edi  # 5f
.globl _th10_00462b30
_th10_00462b30:
    pop esi  # 5e
.globl _th10_00462b31
_th10_00462b31:
    leave  # c9
.globl _th10_00462b32
_th10_00462b32:
    {noimm8s} ret 8  # c20800
.globl _th10_00462b35
_th10_00462b35:
    push 8  # 6a08
.globl _th10_00462b37
_th10_00462b37:
    {noimm8s} push 0x46CA58  # 6858ca4600
.globl _th10_00462b3c
_th10_00462b3c:
    {disp32} call _th10_00454bbc  # e87b20ffff
.globl _th10_00462b41
_th10_00462b41:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462b43
_th10_00462b43:
    {noimm8s} mov dword ptr [esi], 0x46CA54  # c70654ca4600
.globl _th10_00462b49
_th10_00462b49:
    push 14  # 6a0e
.globl _th10_00462b4b
_th10_00462b4b:
    {disp32} call _th10_00453c0c  # e8bc10ffff
.globl _th10_00462b50
_th10_00462b50:
    pop ecx  # 59
.globl _th10_00462b51
_th10_00462b51:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462b55
_th10_00462b55:
    {disp8} {load} mov esi, [esi+4]  # 8b7604
.globl _th10_00462b58
_th10_00462b58:
    test esi, esi  # 85f6
.globl _th10_00462b5a
_th10_00462b5a:
    {disp8} je _th10_00462b63  # 7407
.globl _th10_00462b5c
_th10_00462b5c:
    push esi  # 56
.globl _th10_00462b5d
_th10_00462b5d:
    {disp32} call _th10_00452422  # e8c0f8feff
.globl _th10_00462b62
_th10_00462b62:
    pop ecx  # 59
.globl _th10_00462b63
_th10_00462b63:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00462b67
_th10_00462b67:
    {disp32} call _th10_00462b72  # e806000000
.globl _th10_00462b6c
_th10_00462b6c:
    {disp32} call _th10_00454bf7  # e88620ffff
.globl _th10_00462b71
_th10_00462b71:
    ret  # c3
.globl _th10_00462b72
_th10_00462b72:
    push 14  # 6a0e
.globl _th10_00462b74
_th10_00462b74:
    {disp32} call _th10_00453b3f  # e8c60fffff
.globl _th10_00462b79
_th10_00462b79:
    pop ecx  # 59
.globl _th10_00462b7a
_th10_00462b7a:
    ret  # c3
.globl _th10_00462b7b
_th10_00462b7b:
    push esi  # 56
.globl _th10_00462b7c
_th10_00462b7c:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462b7e
_th10_00462b7e:
    {disp32} call _th10_00462b35  # e8b2ffffff
.globl _th10_00462b83
_th10_00462b83:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_00462b88
_th10_00462b88:
    {disp8} je _th10_00462b91  # 7407
.globl _th10_00462b8a
_th10_00462b8a:
    push esi  # 56
.globl _th10_00462b8b
_th10_00462b8b:
    {disp32} call _th10_004524a1  # e811f9feff
.globl _th10_00462b90
_th10_00462b90:
    pop ecx  # 59
.globl _th10_00462b91
_th10_00462b91:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462b93
_th10_00462b93:
    pop esi  # 5e
.globl _th10_00462b94
_th10_00462b94:
    {noimm8s} ret 4  # c20400
.globl _th10_00462b97
_th10_00462b97:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00462b9b
_th10_00462b9b:
    add ecx, 9  # 83c109
.globl _th10_00462b9e
_th10_00462b9e:
    push ecx  # 51
.globl _th10_00462b9f
_th10_00462b9f:
    add eax, 9  # 83c009
.globl _th10_00462ba2
_th10_00462ba2:
    push eax  # 50
.globl _th10_00462ba3
_th10_00462ba3:
    {disp32} call _th10_0045bf30  # e88893ffff
.globl _th10_00462ba8
_th10_00462ba8:
    neg eax  # f7d8
.globl _th10_00462baa
_th10_00462baa:
    pop ecx  # 59
.globl _th10_00462bab
_th10_00462bab:
    {load} sbb eax, eax  # 1bc0
.globl _th10_00462bad
_th10_00462bad:
    pop ecx  # 59
.globl _th10_00462bae
_th10_00462bae:
    inc eax  # 40
.globl _th10_00462baf
_th10_00462baf:
    {noimm8s} ret 4  # c20400
.globl _th10_00462bb2
_th10_00462bb2:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00462bb6
_th10_00462bb6:
    add ecx, 9  # 83c109
.globl _th10_00462bb9
_th10_00462bb9:
    push ecx  # 51
.globl _th10_00462bba
_th10_00462bba:
    add eax, 9  # 83c009
.globl _th10_00462bbd
_th10_00462bbd:
    push eax  # 50
.globl _th10_00462bbe
_th10_00462bbe:
    {disp32} call _th10_0045bf30  # e86d93ffff
.globl _th10_00462bc3
_th10_00462bc3:
    neg eax  # f7d8
.globl _th10_00462bc5
_th10_00462bc5:
    pop ecx  # 59
.globl _th10_00462bc6
_th10_00462bc6:
    {load} sbb eax, eax  # 1bc0
.globl _th10_00462bc8
_th10_00462bc8:
    pop ecx  # 59
.globl _th10_00462bc9
_th10_00462bc9:
    neg eax  # f7d8
.globl _th10_00462bcb
_th10_00462bcb:
    {noimm8s} ret 4  # c20400
.globl _th10_00462bce
_th10_00462bce:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00462bd2
_th10_00462bd2:
    add ecx, 9  # 83c109
.globl _th10_00462bd5
_th10_00462bd5:
    push ecx  # 51
.globl _th10_00462bd6
_th10_00462bd6:
    add eax, 9  # 83c009
.globl _th10_00462bd9
_th10_00462bd9:
    push eax  # 50
.globl _th10_00462bda
_th10_00462bda:
    {disp32} call _th10_0045bf30  # e85193ffff
.globl _th10_00462bdf
_th10_00462bdf:
    pop ecx  # 59
.globl _th10_00462be0
_th10_00462be0:
    pop ecx  # 59
.globl _th10_00462be1
_th10_00462be1:
    {load} xor ecx, ecx  # 33c9
.globl _th10_00462be3
_th10_00462be3:
    test eax, eax  # 85c0
.globl _th10_00462be5
_th10_00462be5:
    setg cl  # 0f9fc1
.globl _th10_00462be8
_th10_00462be8:
    {load} mov eax, ecx  # 8bc1
.globl _th10_00462bea
_th10_00462bea:
    {noimm8s} ret 4  # c20400
.globl _th10_00462bed
_th10_00462bed:
    {disp8} lea eax, [ecx+8]  # 8d4108
.globl _th10_00462bf0
_th10_00462bf0:
    ret  # c3
.globl _th10_00462bf1
_th10_00462bf1:
    {load} mov eax, ecx  # 8bc1
.globl _th10_00462bf3
_th10_00462bf3:
    {noimm8s} mov dword ptr [eax], 0x46CA54  # c70054ca4600
.globl _th10_00462bf9
_th10_00462bf9:
    {noimm8s} ret 4  # c20400
.globl _th10_00462bfc
_th10_00462bfc:
    {load} mov eax, ecx  # 8bc1
.globl _th10_00462bfe
_th10_00462bfe:
    {noimm8s} ret 4  # c20400
.globl _th10_00462c01
_th10_00462c01:
    {load} mov eax, ecx  # 8bc1
.globl _th10_00462c03
_th10_00462c03:
    {disp8} and dword ptr [eax+4], 0  # 83600400
.globl _th10_00462c07
_th10_00462c07:
    {disp8} and dword ptr [eax+8], 0  # 83600800
.globl _th10_00462c0b
_th10_00462c0b:
    {noimm8s} mov dword ptr [eax], 0x46CA68  # c70068ca4600
.globl _th10_00462c11
_th10_00462c11:
    ret  # c3
.globl _th10_00462c12
_th10_00462c12:
    push esi  # 56
.globl _th10_00462c13
_th10_00462c13:
    push edi  # 57
.globl _th10_00462c14
_th10_00462c14:
    {disp8} {load} mov edi, [esp+0x0C]  # 8b7c240c
.globl _th10_00462c18
_th10_00462c18:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462c1a
_th10_00462c1a:
    {noimm8s} mov dword ptr [esi], 0x46CA68  # c70668ca4600
.globl _th10_00462c20
_th10_00462c20:
    {load} mov eax, [edi]  # 8b07
.globl _th10_00462c22
_th10_00462c22:
    test eax, eax  # 85c0
.globl _th10_00462c24
_th10_00462c24:
    {disp8} je _th10_00462c48  # 7422
.globl _th10_00462c26
_th10_00462c26:
    push eax  # 50
.globl _th10_00462c27
_th10_00462c27:
    {disp32} call _th10_00456720  # e8f43affff
.globl _th10_00462c2c
_th10_00462c2c:
    inc eax  # 40
.globl _th10_00462c2d
_th10_00462c2d:
    push eax  # 50
.globl _th10_00462c2e
_th10_00462c2e:
    {disp32} call _th10_00452706  # e8d3fafeff
.globl _th10_00462c33
_th10_00462c33:
    test eax, eax  # 85c0
.globl _th10_00462c35
_th10_00462c35:
    pop ecx  # 59
.globl _th10_00462c36
_th10_00462c36:
    pop ecx  # 59
.globl _th10_00462c37
_th10_00462c37:
    {disp8} {store} mov [esi+4], eax  # 894604
.globl _th10_00462c3a
_th10_00462c3a:
    {disp8} je _th10_00462c4c  # 7410
.globl _th10_00462c3c
_th10_00462c3c:
    push dword ptr [edi]  # ff37
.globl _th10_00462c3e
_th10_00462c3e:
    push eax  # 50
.globl _th10_00462c3f
_th10_00462c3f:
    {disp32} call _th10_0045bd80  # e83c91ffff
.globl _th10_00462c44
_th10_00462c44:
    pop ecx  # 59
.globl _th10_00462c45
_th10_00462c45:
    pop ecx  # 59
.globl _th10_00462c46
_th10_00462c46:
    {disp8} jmp _th10_00462c4c  # eb04
.globl _th10_00462c48
_th10_00462c48:
    {disp8} and dword ptr [esi+4], 0  # 83660400
.globl _th10_00462c4c
_th10_00462c4c:
    pop edi  # 5f
.globl _th10_00462c4d
_th10_00462c4d:
    {disp8} {noimm8s} mov dword ptr [esi+8], 1  # c7460801000000
.globl _th10_00462c54
_th10_00462c54:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462c56
_th10_00462c56:
    pop esi  # 5e
.globl _th10_00462c57
_th10_00462c57:
    {noimm8s} ret 4  # c20400
.globl _th10_00462c5a
_th10_00462c5a:
    push esi  # 56
.globl _th10_00462c5b
_th10_00462c5b:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462c5d
_th10_00462c5d:
    push edi  # 57
.globl _th10_00462c5e
_th10_00462c5e:
    {disp8} {load} mov edi, [esp+0x0C]  # 8b7c240c
.globl _th10_00462c62
_th10_00462c62:
    {noimm8s} mov dword ptr [esi], 0x46CA68  # c70668ca4600
.globl _th10_00462c68
_th10_00462c68:
    {disp8} {load} mov eax, [edi+8]  # 8b4708
.globl _th10_00462c6b
_th10_00462c6b:
    {disp8} {store} mov [esi+8], eax  # 894608
.globl _th10_00462c6e
_th10_00462c6e:
    test eax, eax  # 85c0
.globl _th10_00462c70
_th10_00462c70:
    {disp8} {load} mov eax, [edi+4]  # 8b4704
.globl _th10_00462c73
_th10_00462c73:
    {disp8} je _th10_00462ca2  # 742d
.globl _th10_00462c75
_th10_00462c75:
    test eax, eax  # 85c0
.globl _th10_00462c77
_th10_00462c77:
    {disp8} je _th10_00462c9c  # 7423
.globl _th10_00462c79
_th10_00462c79:
    push eax  # 50
.globl _th10_00462c7a
_th10_00462c7a:
    {disp32} call _th10_00456720  # e8a13affff
.globl _th10_00462c7f
_th10_00462c7f:
    inc eax  # 40
.globl _th10_00462c80
_th10_00462c80:
    push eax  # 50
.globl _th10_00462c81
_th10_00462c81:
    {disp32} call _th10_00452706  # e880fafeff
.globl _th10_00462c86
_th10_00462c86:
    test eax, eax  # 85c0
.globl _th10_00462c88
_th10_00462c88:
    pop ecx  # 59
.globl _th10_00462c89
_th10_00462c89:
    pop ecx  # 59
.globl _th10_00462c8a
_th10_00462c8a:
    {disp8} {store} mov [esi+4], eax  # 894604
.globl _th10_00462c8d
_th10_00462c8d:
    {disp8} je _th10_00462ca5  # 7416
.globl _th10_00462c8f
_th10_00462c8f:
    {disp8} push dword ptr [edi+4]  # ff7704
.globl _th10_00462c92
_th10_00462c92:
    push eax  # 50
.globl _th10_00462c93
_th10_00462c93:
    {disp32} call _th10_0045bd80  # e8e890ffff
.globl _th10_00462c98
_th10_00462c98:
    pop ecx  # 59
.globl _th10_00462c99
_th10_00462c99:
    pop ecx  # 59
.globl _th10_00462c9a
_th10_00462c9a:
    {disp8} jmp _th10_00462ca5  # eb09
.globl _th10_00462c9c
_th10_00462c9c:
    {disp8} and dword ptr [esi+4], 0  # 83660400
.globl _th10_00462ca0
_th10_00462ca0:
    {disp8} jmp _th10_00462ca5  # eb03
.globl _th10_00462ca2
_th10_00462ca2:
    {disp8} {store} mov [esi+4], eax  # 894604
.globl _th10_00462ca5
_th10_00462ca5:
    pop edi  # 5f
.globl _th10_00462ca6
_th10_00462ca6:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462ca8
_th10_00462ca8:
    pop esi  # 5e
.globl _th10_00462ca9
_th10_00462ca9:
    {noimm8s} ret 4  # c20400
.globl _th10_00462cac
_th10_00462cac:
    {disp8} cmp dword ptr [ecx+8], 0  # 83790800
.globl _th10_00462cb0
_th10_00462cb0:
    {noimm8s} mov dword ptr [ecx], 0x46CA68  # c70168ca4600
.globl _th10_00462cb6
_th10_00462cb6:
    {disp8} je _th10_00462cc1  # 7409
.globl _th10_00462cb8
_th10_00462cb8:
    {disp8} push dword ptr [ecx+4]  # ff7104
.globl _th10_00462cbb
_th10_00462cbb:
    {disp32} call _th10_00452422  # e862f7feff
.globl _th10_00462cc0
_th10_00462cc0:
    pop ecx  # 59
.globl _th10_00462cc1
_th10_00462cc1:
    ret  # c3
.globl _th10_00462cc2
_th10_00462cc2:
    {disp8} {load} mov eax, [ecx+4]  # 8b4104
.globl _th10_00462cc5
_th10_00462cc5:
    test eax, eax  # 85c0
.globl _th10_00462cc7
_th10_00462cc7:
    {disp8} jne _th10_00462cce  # 7505
.globl _th10_00462cc9
_th10_00462cc9:
    {noimm8s} mov eax, 0x46CA70  # b870ca4600
.globl _th10_00462cce
_th10_00462cce:
    ret  # c3
.globl _th10_00462ccf
_th10_00462ccf:
    push esi  # 56
.globl _th10_00462cd0
_th10_00462cd0:
    {disp8} lea eax, [esp+8]  # 8d442408
.globl _th10_00462cd4
_th10_00462cd4:
    push eax  # 50
.globl _th10_00462cd5
_th10_00462cd5:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462cd7
_th10_00462cd7:
    {disp32} call _th10_00462c12  # e836ffffff
.globl _th10_00462cdc
_th10_00462cdc:
    {noimm8s} mov dword ptr [esi], 0x46CA88  # c70688ca4600
.globl _th10_00462ce2
_th10_00462ce2:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462ce4
_th10_00462ce4:
    pop esi  # 5e
.globl _th10_00462ce5
_th10_00462ce5:
    {noimm8s} ret 4  # c20400
.globl _th10_00462ce8
_th10_00462ce8:
    push esi  # 56
.globl _th10_00462ce9
_th10_00462ce9:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_00462ced
_th10_00462ced:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462cef
_th10_00462cef:
    {disp32} call _th10_00462c5a  # e866ffffff
.globl _th10_00462cf4
_th10_00462cf4:
    {noimm8s} mov dword ptr [esi], 0x46CA88  # c70688ca4600
.globl _th10_00462cfa
_th10_00462cfa:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462cfc
_th10_00462cfc:
    pop esi  # 5e
.globl _th10_00462cfd
_th10_00462cfd:
    {noimm8s} ret 4  # c20400
.globl _th10_00462d00
_th10_00462d00:
    {noimm8s} mov dword ptr [ecx], 0x46CA88  # c70188ca4600
.globl _th10_00462d06
_th10_00462d06:
    {disp32} jmp _th10_00462cac  # e9a1ffffff
.globl _th10_00462d0b
_th10_00462d0b:
    push esi  # 56
.globl _th10_00462d0c
_th10_00462d0c:
    {disp8} lea eax, [esp+8]  # 8d442408
.globl _th10_00462d10
_th10_00462d10:
    push eax  # 50
.globl _th10_00462d11
_th10_00462d11:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462d13
_th10_00462d13:
    {disp32} call _th10_00462c12  # e8fafeffff
.globl _th10_00462d18
_th10_00462d18:
    {noimm8s} mov dword ptr [esi], 0x46CA94  # c70694ca4600
.globl _th10_00462d1e
_th10_00462d1e:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462d20
_th10_00462d20:
    pop esi  # 5e
.globl _th10_00462d21
_th10_00462d21:
    {noimm8s} ret 4  # c20400
.globl _th10_00462d24
_th10_00462d24:
    push esi  # 56
.globl _th10_00462d25
_th10_00462d25:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_00462d29
_th10_00462d29:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462d2b
_th10_00462d2b:
    {disp32} call _th10_00462c5a  # e82affffff
.globl _th10_00462d30
_th10_00462d30:
    {noimm8s} mov dword ptr [esi], 0x46CA94  # c70694ca4600
.globl _th10_00462d36
_th10_00462d36:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462d38
_th10_00462d38:
    pop esi  # 5e
.globl _th10_00462d39
_th10_00462d39:
    {noimm8s} ret 4  # c20400
.globl _th10_00462d3c
_th10_00462d3c:
    {noimm8s} mov dword ptr [ecx], 0x46CA94  # c70194ca4600
.globl _th10_00462d42
_th10_00462d42:
    {disp32} jmp _th10_00462cac  # e965ffffff
.globl _th10_00462d47
_th10_00462d47:
    push esi  # 56
.globl _th10_00462d48
_th10_00462d48:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_00462d4c
_th10_00462d4c:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462d4e
_th10_00462d4e:
    {disp32} call _th10_00462d0b  # e8b8ffffff
.globl _th10_00462d53
_th10_00462d53:
    {noimm8s} mov dword ptr [esi], 0x46CAA0  # c706a0ca4600
.globl _th10_00462d59
_th10_00462d59:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462d5b
_th10_00462d5b:
    pop esi  # 5e
.globl _th10_00462d5c
_th10_00462d5c:
    {noimm8s} ret 4  # c20400
.globl _th10_00462d5f
_th10_00462d5f:
    push esi  # 56
.globl _th10_00462d60
_th10_00462d60:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_00462d64
_th10_00462d64:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462d66
_th10_00462d66:
    {disp32} call _th10_00462d24  # e8b9ffffff
.globl _th10_00462d6b
_th10_00462d6b:
    {noimm8s} mov dword ptr [esi], 0x46CAA0  # c706a0ca4600
.globl _th10_00462d71
_th10_00462d71:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462d73
_th10_00462d73:
    pop esi  # 5e
.globl _th10_00462d74
_th10_00462d74:
    {noimm8s} ret 4  # c20400
.globl _th10_00462d77
_th10_00462d77:
    {noimm8s} mov dword ptr [ecx], 0x46CA94  # c70194ca4600
.globl _th10_00462d7d
_th10_00462d7d:
    {disp32} jmp _th10_00462cac  # e92affffff
.globl _th10_00462d82
_th10_00462d82:
    push esi  # 56
.globl _th10_00462d83
_th10_00462d83:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462d85
_th10_00462d85:
    {disp32} call _th10_00462cac  # e822ffffff
.globl _th10_00462d8a
_th10_00462d8a:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_00462d8f
_th10_00462d8f:
    {disp8} je _th10_00462d98  # 7407
.globl _th10_00462d91
_th10_00462d91:
    push esi  # 56
.globl _th10_00462d92
_th10_00462d92:
    {disp32} call _th10_004524a1  # e80af7feff
.globl _th10_00462d97
_th10_00462d97:
    pop ecx  # 59
.globl _th10_00462d98
_th10_00462d98:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462d9a
_th10_00462d9a:
    pop esi  # 5e
.globl _th10_00462d9b
_th10_00462d9b:
    {noimm8s} ret 4  # c20400
.globl _th10_00462d9e
_th10_00462d9e:
    push esi  # 56
.globl _th10_00462d9f
_th10_00462d9f:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462da1
_th10_00462da1:
    {disp8} {load} cmp esi, [esp+8]  # 3b742408
.globl _th10_00462da5
_th10_00462da5:
    {disp8} je _th10_00462db7  # 7410
.globl _th10_00462da7
_th10_00462da7:
    {disp32} call _th10_00462cac  # e800ffffff
.globl _th10_00462dac
_th10_00462dac:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_00462db0
_th10_00462db0:
    {load} mov ecx, esi  # 8bce
.globl _th10_00462db2
_th10_00462db2:
    {disp32} call _th10_00462c5a  # e8a3feffff
.globl _th10_00462db7
_th10_00462db7:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462db9
_th10_00462db9:
    pop esi  # 5e
.globl _th10_00462dba
_th10_00462dba:
    {noimm8s} ret 4  # c20400
.globl _th10_00462dbd
_th10_00462dbd:
    push esi  # 56
.globl _th10_00462dbe
_th10_00462dbe:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462dc0
_th10_00462dc0:
    {disp32} call _th10_00462d00  # e83bffffff
.globl _th10_00462dc5
_th10_00462dc5:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_00462dca
_th10_00462dca:
    {disp8} je _th10_00462dd3  # 7407
.globl _th10_00462dcc
_th10_00462dcc:
    push esi  # 56
.globl _th10_00462dcd
_th10_00462dcd:
    {disp32} call _th10_004524a1  # e8cff6feff
.globl _th10_00462dd2
_th10_00462dd2:
    pop ecx  # 59
.globl _th10_00462dd3
_th10_00462dd3:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462dd5
_th10_00462dd5:
    pop esi  # 5e
.globl _th10_00462dd6
_th10_00462dd6:
    {noimm8s} ret 4  # c20400
.globl _th10_00462dd9
_th10_00462dd9:
    push esi  # 56
.globl _th10_00462dda
_th10_00462dda:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462ddc
_th10_00462ddc:
    {disp32} call _th10_00462d3c  # e85bffffff
.globl _th10_00462de1
_th10_00462de1:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_00462de6
_th10_00462de6:
    {disp8} je _th10_00462def  # 7407
.globl _th10_00462de8
_th10_00462de8:
    push esi  # 56
.globl _th10_00462de9
_th10_00462de9:
    {disp32} call _th10_004524a1  # e8b3f6feff
.globl _th10_00462dee
_th10_00462dee:
    pop ecx  # 59
.globl _th10_00462def
_th10_00462def:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462df1
_th10_00462df1:
    pop esi  # 5e
.globl _th10_00462df2
_th10_00462df2:
    {noimm8s} ret 4  # c20400
.globl _th10_00462df5
_th10_00462df5:
    push esi  # 56
.globl _th10_00462df6
_th10_00462df6:
    {load} mov esi, ecx  # 8bf1
.globl _th10_00462df8
_th10_00462df8:
    {disp32} call _th10_00462d77  # e87affffff
.globl _th10_00462dfd
_th10_00462dfd:
    {disp8} test byte ptr [esp+8], 1  # f644240801
.globl _th10_00462e02
_th10_00462e02:
    {disp8} je _th10_00462e0b  # 7407
.globl _th10_00462e04
_th10_00462e04:
    push esi  # 56
.globl _th10_00462e05
_th10_00462e05:
    {disp32} call _th10_004524a1  # e897f6feff
.globl _th10_00462e0a
_th10_00462e0a:
    pop ecx  # 59
.globl _th10_00462e0b
_th10_00462e0b:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462e0d
_th10_00462e0d:
    pop esi  # 5e
.globl _th10_00462e0e
_th10_00462e0e:
    {noimm8s} ret 4  # c20400
.globl _th10_00462e11
_th10_00462e11:
    {disp8} {load} mov eax, [esi+4]  # 8b4604
.globl _th10_00462e14
_th10_00462e14:
    test eax, eax  # 85c0
.globl _th10_00462e16
_th10_00462e16:
    {disp8} je _th10_00462e5c  # 7444
.globl _th10_00462e18
_th10_00462e18:
    {disp8} lea edx, [eax+8]  # 8d5008
.globl _th10_00462e1b
_th10_00462e1b:
    cmp byte ptr [edx], 0  # 803a00
.globl _th10_00462e1e
_th10_00462e1e:
    {disp8} je _th10_00462e5c  # 743c
.globl _th10_00462e20
_th10_00462e20:
    {disp8} {load} mov ecx, [edi+4]  # 8b4f04
.globl _th10_00462e23
_th10_00462e23:
    {load} cmp eax, ecx  # 3bc1
.globl _th10_00462e25
_th10_00462e25:
    {disp8} je _th10_00462e37  # 7410
.globl _th10_00462e27
_th10_00462e27:
    add ecx, 8  # 83c108
.globl _th10_00462e2a
_th10_00462e2a:
    push ecx  # 51
.globl _th10_00462e2b
_th10_00462e2b:
    push edx  # 52
.globl _th10_00462e2c
_th10_00462e2c:
    {disp32} call _th10_0045bf30  # e8ff90ffff
.globl _th10_00462e31
_th10_00462e31:
    test eax, eax  # 85c0
.globl _th10_00462e33
_th10_00462e33:
    pop ecx  # 59
.globl _th10_00462e34
_th10_00462e34:
    pop ecx  # 59
.globl _th10_00462e35
_th10_00462e35:
    {disp8} jne _th10_00462e59  # 7522
.globl _th10_00462e37
_th10_00462e37:
    test byte ptr [edi], 2  # f60702
.globl _th10_00462e3a
_th10_00462e3a:
    {disp8} je _th10_00462e41  # 7405
.globl _th10_00462e3c
_th10_00462e3c:
    test byte ptr [esi], 8  # f60608
.globl _th10_00462e3f
_th10_00462e3f:
    {disp8} je _th10_00462e59  # 7418
.globl _th10_00462e41
_th10_00462e41:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00462e45
_th10_00462e45:
    {load} mov eax, [eax]  # 8b00
.globl _th10_00462e47
_th10_00462e47:
    test al, 1  # a801
.globl _th10_00462e49
_th10_00462e49:
    {disp8} je _th10_00462e50  # 7405
.globl _th10_00462e4b
_th10_00462e4b:
    test byte ptr [esi], 1  # f60601
.globl _th10_00462e4e
_th10_00462e4e:
    {disp8} je _th10_00462e59  # 7409
.globl _th10_00462e50
_th10_00462e50:
    test al, 2  # a802
.globl _th10_00462e52
_th10_00462e52:
    {disp8} je _th10_00462e5c  # 7408
.globl _th10_00462e54
_th10_00462e54:
    test byte ptr [esi], 2  # f60602
.globl _th10_00462e57
_th10_00462e57:
    {disp8} jne _th10_00462e5c  # 7503
.globl _th10_00462e59
_th10_00462e59:
    {load} xor eax, eax  # 33c0
.globl _th10_00462e5b
_th10_00462e5b:
    ret  # c3
.globl _th10_00462e5c
_th10_00462e5c:
    {load} xor eax, eax  # 33c0
.globl _th10_00462e5e
_th10_00462e5e:
    inc eax  # 40
.globl _th10_00462e5f
_th10_00462e5f:
    ret  # c3
.globl _th10_00462e60
_th10_00462e60:
    {load} mov eax, [eax]  # 8b00
.globl _th10_00462e62
_th10_00462e62:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_00462e68
_th10_00462e68:
    {disp8} je _th10_00462e6d  # 7403
.globl _th10_00462e6a
_th10_00462e6a:
    {load} xor eax, eax  # 33c0
.globl _th10_00462e6c
_th10_00462e6c:
    ret  # c3
.globl _th10_00462e6d
_th10_00462e6d:
    {disp32} call _th10_00456357  # e8e534ffff
.globl _th10_00462e72
_th10_00462e72:
    and dword ptr [eax+0x84], 0  # 83a08400000000
.globl _th10_00462e79
_th10_00462e79:
    {disp32} jmp _th10_00455693  # e91528ffff
.globl _th10_00462e7e
_th10_00462e7e:
    push 16  # 6a10
.globl _th10_00462e80
_th10_00462e80:
    {noimm8s} push 0x46CAA8  # 68a8ca4600
.globl _th10_00462e85
_th10_00462e85:
    {disp32} call _th10_00454bbc  # e8321dffff
.globl _th10_00462e8a
_th10_00462e8a:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00462e8d
_th10_00462e8d:
    {disp8} {load} mov esi, [ebx+8]  # 8b7308
.globl _th10_00462e90
_th10_00462e90:
    {disp8} {store} mov [ebp-0x1C], esi  # 8975e4
.globl _th10_00462e93
_th10_00462e93:
    {disp32} call _th10_00456357  # e8bf34ffff
.globl _th10_00462e98
_th10_00462e98:
    {noimm8s} add eax, 0x84  # 0584000000
.globl _th10_00462e9d
_th10_00462e9d:
    inc dword ptr [eax]  # ff00
.globl _th10_00462e9f
_th10_00462e9f:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462ea3
_th10_00462ea3:
    {disp8} {load} mov edi, [ebp+0x10]  # 8b7d10
.globl _th10_00462ea6
_th10_00462ea6:
    {disp8} {load} cmp esi, [ebp+0x14]  # 3b7514
.globl _th10_00462ea9
_th10_00462ea9:
    {disp8} je _th10_00462f0f  # 7464
.globl _th10_00462eab
_th10_00462eab:
    cmp esi, -1  # 83feff
.globl _th10_00462eae
_th10_00462eae:
    {disp8} jle _th10_00462eb5  # 7e05
.globl _th10_00462eb0
_th10_00462eb0:
    {disp8} {load} cmp esi, [edi+4]  # 3b7704
.globl _th10_00462eb3
_th10_00462eb3:
    {disp8} jl _th10_00462eba  # 7c05
.globl _th10_00462eb5
_th10_00462eb5:
    {disp32} call _th10_004556e0  # e82628ffff
.globl _th10_00462eba
_th10_00462eba:
    {load} mov eax, esi  # 8bc6
.globl _th10_00462ebc
_th10_00462ebc:
    shl eax, 3  # c1e003
.globl _th10_00462ebf
_th10_00462ebf:
    {disp8} {load} mov ecx, [edi+8]  # 8b4f08
.globl _th10_00462ec2
_th10_00462ec2:
    {load} add ecx, eax  # 03c8
.globl _th10_00462ec4
_th10_00462ec4:
    {load} mov esi, [ecx]  # 8b31
.globl _th10_00462ec6
_th10_00462ec6:
    {disp8} {store} mov [ebp-0x20], esi  # 8975e0
.globl _th10_00462ec9
_th10_00462ec9:
    {disp8} {noimm8s} mov dword ptr [ebp-4], 1  # c745fc01000000
.globl _th10_00462ed0
_th10_00462ed0:
    {disp8} cmp dword ptr [ecx+4], 0  # 83790400
.globl _th10_00462ed4
_th10_00462ed4:
    {disp8} je _th10_00462eeb  # 7415
.globl _th10_00462ed6
_th10_00462ed6:
    {disp8} {store} mov [ebx+8], esi  # 897308
.globl _th10_00462ed9
_th10_00462ed9:
    {noimm8s} push 0x103  # 6803010000
.globl _th10_00462ede
_th10_00462ede:
    push ebx  # 53
.globl _th10_00462edf
_th10_00462edf:
    {disp8} {load} mov ecx, [edi+8]  # 8b4f08
.globl _th10_00462ee2
_th10_00462ee2:
    {disp8} push dword ptr [ecx+eax+4]  # ff740104
.globl _th10_00462ee6
_th10_00462ee6:
    {disp32} call _th10_00463a10  # e8250b0000
.globl _th10_00462eeb
_th10_00462eeb:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462eef
_th10_00462eef:
    {disp8} jmp _th10_00462f0a  # eb19
.globl _th10_00462ef1
_th10_00462ef1:
    {disp8} {load} mov eax, [ebp-0x14]  # 8b45ec
.globl _th10_00462ef4
_th10_00462ef4:
    {disp32} call _th10_00462e60  # e867ffffff
.globl _th10_00462ef9
_th10_00462ef9:
    ret  # c3
.globl _th10_00462efa
_th10_00462efa:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00462efd
_th10_00462efd:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462f01
_th10_00462f01:
    {disp8} {load} mov edi, [ebp+0x10]  # 8b7d10
.globl _th10_00462f04
_th10_00462f04:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00462f07
_th10_00462f07:
    {disp8} {load} mov esi, [ebp-0x20]  # 8b75e0
.globl _th10_00462f0a
_th10_00462f0a:
    {disp8} {store} mov [ebp-0x1C], esi  # 8975e4
.globl _th10_00462f0d
_th10_00462f0d:
    {disp8} jmp _th10_00462ea6  # eb97
.globl _th10_00462f0f
_th10_00462f0f:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00462f13
_th10_00462f13:
    {disp32} call _th10_00462f31  # e819000000
.globl _th10_00462f18
_th10_00462f18:
    {disp8} {load} cmp esi, [ebp+0x14]  # 3b7514
.globl _th10_00462f1b
_th10_00462f1b:
    {disp8} je _th10_00462f22  # 7405
.globl _th10_00462f1d
_th10_00462f1d:
    {disp32} call _th10_004556e0  # e8be27ffff
.globl _th10_00462f22
_th10_00462f22:
    {disp8} {store} mov [ebx+8], esi  # 897308
.globl _th10_00462f25
_th10_00462f25:
    {disp32} call _th10_00454bf7  # e8cd1cffff
.globl _th10_00462f2a
_th10_00462f2a:
    ret  # c3
.globl _th10_00462f2b
_th10_00462f2b:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00462f2e
_th10_00462f2e:
    {disp8} {load} mov esi, [ebp-0x1C]  # 8b75e4
.globl _th10_00462f31
_th10_00462f31:
    {disp32} call _th10_00456357  # e82134ffff
.globl _th10_00462f36
_th10_00462f36:
    cmp dword ptr [eax+0x84], 0  # 83b88400000000
.globl _th10_00462f3d
_th10_00462f3d:
    {disp8} jle _th10_00462f4b  # 7e0c
.globl _th10_00462f3f
_th10_00462f3f:
    {disp32} call _th10_00456357  # e81334ffff
.globl _th10_00462f44
_th10_00462f44:
    {noimm8s} add eax, 0x84  # 0584000000
.globl _th10_00462f49
_th10_00462f49:
    dec dword ptr [eax]  # ff08
.globl _th10_00462f4b
_th10_00462f4b:
    ret  # c3
.globl _th10_00462f4c
_th10_00462f4c:
    {load} mov eax, [eax]  # 8b00
.globl _th10_00462f4e
_th10_00462f4e:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_00462f54
_th10_00462f54:
    {disp8} jne _th10_00462f79  # 7523
.globl _th10_00462f56
_th10_00462f56:
    {disp8} cmp dword ptr [eax+0x10], 3  # 83781003
.globl _th10_00462f5a
_th10_00462f5a:
    {disp8} jne _th10_00462f79  # 751d
.globl _th10_00462f5c
_th10_00462f5c:
    {disp8} {load} mov ecx, [eax+0x14]  # 8b4814
.globl _th10_00462f5f
_th10_00462f5f:
    {noimm8s} cmp ecx, 0x19930520  # 81f920059319
.globl _th10_00462f65
_th10_00462f65:
    {disp8} je _th10_00462f6f  # 7408
.globl _th10_00462f67
_th10_00462f67:
    {noimm8s} cmp ecx, 0x19930521  # 81f921059319
.globl _th10_00462f6d
_th10_00462f6d:
    {disp8} jne _th10_00462f79  # 750a
.globl _th10_00462f6f
_th10_00462f6f:
    {disp8} cmp dword ptr [eax+0x1C], 0  # 83781c00
.globl _th10_00462f73
_th10_00462f73:
    {disp8} jne _th10_00462f79  # 7504
.globl _th10_00462f75
_th10_00462f75:
    {load} xor eax, eax  # 33c0
.globl _th10_00462f77
_th10_00462f77:
    inc eax  # 40
.globl _th10_00462f78
_th10_00462f78:
    ret  # c3
.globl _th10_00462f79
_th10_00462f79:
    {load} xor eax, eax  # 33c0
.globl _th10_00462f7b
_th10_00462f7b:
    ret  # c3
.globl _th10_00462f7c
_th10_00462f7c:
    push 8  # 6a08
.globl _th10_00462f7e
_th10_00462f7e:
    {noimm8s} push 0x46CAC0  # 68c0ca4600
.globl _th10_00462f83
_th10_00462f83:
    {disp32} call _th10_00454bbc  # e8341cffff
.globl _th10_00462f88
_th10_00462f88:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00462f8b
_th10_00462f8b:
    test eax, eax  # 85c0
.globl _th10_00462f8d
_th10_00462f8d:
    {disp8} je _th10_00462faa  # 741b
.globl _th10_00462f8f
_th10_00462f8f:
    {disp8} {load} mov ecx, [eax+0x1C]  # 8b481c
.globl _th10_00462f92
_th10_00462f92:
    {disp8} {load} mov ecx, [ecx+4]  # 8b4904
.globl _th10_00462f95
_th10_00462f95:
    test ecx, ecx  # 85c9
.globl _th10_00462f97
_th10_00462f97:
    {disp8} je _th10_00462faa  # 7411
.globl _th10_00462f99
_th10_00462f99:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00462f9d
_th10_00462f9d:
    push ecx  # 51
.globl _th10_00462f9e
_th10_00462f9e:
    {disp8} push dword ptr [eax+0x18]  # ff7018
.globl _th10_00462fa1
_th10_00462fa1:
    {disp32} call _th10_00462706  # e860f7ffff
.globl _th10_00462fa6
_th10_00462fa6:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00462faa
_th10_00462faa:
    {disp32} call _th10_00454bf7  # e8481cffff
.globl _th10_00462faf
_th10_00462faf:
    ret  # c3
.globl _th10_00462fb0
_th10_00462fb0:
    {load} xor eax, eax  # 33c0
.globl _th10_00462fb2
_th10_00462fb2:
    {disp8} {store} cmp [ebp+0x0C], al  # 38450c
.globl _th10_00462fb5
_th10_00462fb5:
    setne al  # 0f95c0
.globl _th10_00462fb8
_th10_00462fb8:
    ret  # c3
.globl _th10_00462fb9
_th10_00462fb9:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00462fbc
_th10_00462fbc:
    {disp32} jmp _th10_00455693  # e9d226ffff
.globl _th10_00462fc1
_th10_00462fc1:
    push esi  # 56
.globl _th10_00462fc2
_th10_00462fc2:
    {load} mov esi, eax  # 8bf0
.globl _th10_00462fc4
_th10_00462fc4:
    {load} mov eax, [ecx]  # 8b01
.globl _th10_00462fc6
_th10_00462fc6:
    {load} add eax, esi  # 03c6
.globl _th10_00462fc8
_th10_00462fc8:
    {disp8} cmp dword ptr [ecx+4], 0  # 83790400
.globl _th10_00462fcc
_th10_00462fcc:
    {disp8} jl _th10_00462fde  # 7c10
.globl _th10_00462fce
_th10_00462fce:
    {disp8} {load} mov edx, [ecx+4]  # 8b5104
.globl _th10_00462fd1
_th10_00462fd1:
    {disp8} {load} mov ecx, [ecx+8]  # 8b4908
.globl _th10_00462fd4
_th10_00462fd4:
    {load} mov esi, [edx+esi]  # 8b3432
.globl _th10_00462fd7
_th10_00462fd7:
    {load} mov ecx, [esi+ecx]  # 8b0c0e
.globl _th10_00462fda
_th10_00462fda:
    {load} add ecx, edx  # 03ca
.globl _th10_00462fdc
_th10_00462fdc:
    {load} add eax, ecx  # 03c1
.globl _th10_00462fde
_th10_00462fde:
    pop esi  # 5e
.globl _th10_00462fdf
_th10_00462fdf:
    ret  # c3
.globl _th10_00462fe0
_th10_00462fe0:
    {disp32} call _th10_00456357  # e87233ffff
.globl _th10_00462fe5
_th10_00462fe5:
    {load} xor ecx, ecx  # 33c9
.globl _th10_00462fe7
_th10_00462fe7:
    {store} cmp [eax+0x84], ecx  # 398884000000
.globl _th10_00462fed
_th10_00462fed:
    setne cl  # 0f95c1
.globl _th10_00462ff0
_th10_00462ff0:
    {load} mov al, cl  # 8ac1
.globl _th10_00462ff2
_th10_00462ff2:
    ret  # c3
.globl _th10_00462ff3
_th10_00462ff3:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00462ff7
_th10_00462ff7:
    test eax, eax  # 85c0
.globl _th10_00462ff9
_th10_00462ff9:
    push esi  # 56
.globl _th10_00462ffa
_th10_00462ffa:
    push edi  # 57
.globl _th10_00462ffb
_th10_00462ffb:
    {disp8} {load} mov edi, [esp+0x10]  # 8b7c2410
.globl _th10_00462fff
_th10_00462fff:
    {disp8} je _th10_00463062  # 7461
.globl _th10_00463001
_th10_00463001:
    {load} mov esi, [eax]  # 8b30
.globl _th10_00463003
_th10_00463003:
    test esi, esi  # 85f6
.globl _th10_00463005
_th10_00463005:
    {disp8} je _th10_00463062  # 745b
.globl _th10_00463007
_th10_00463007:
    {noimm8s} cmp dword ptr [esi], 0x0E06D7363  # 813e63736de0
.globl _th10_0046300d
_th10_0046300d:
    {disp8} jne _th10_00463034  # 7525
.globl _th10_0046300f
_th10_0046300f:
    {disp8} cmp dword ptr [esi+0x10], 3  # 837e1003
.globl _th10_00463013
_th10_00463013:
    {disp8} jne _th10_00463034  # 751f
.globl _th10_00463015
_th10_00463015:
    {disp8} {load} mov eax, [esi+0x14]  # 8b4614
.globl _th10_00463018
_th10_00463018:
    {noimm8s} cmp eax, 0x19930520  # 3d20059319
.globl _th10_0046301d
_th10_0046301d:
    {disp8} je _th10_00463026  # 7407
.globl _th10_0046301f
_th10_0046301f:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_00463024
_th10_00463024:
    {disp8} jne _th10_00463034  # 750e
.globl _th10_00463026
_th10_00463026:
    {disp8} cmp dword ptr [esi+0x1C], 0  # 837e1c00
.globl _th10_0046302a
_th10_0046302a:
    {disp8} jne _th10_00463034  # 7508
.globl _th10_0046302c
_th10_0046302c:
    {disp32} call _th10_00456357  # e82633ffff
.globl _th10_00463031
_th10_00463031:
    {disp8} {load} mov esi, [eax+0x7C]  # 8b707c
.globl _th10_00463034
_th10_00463034:
    {disp8} push dword ptr [esi+0x18]  # ff7618
.globl _th10_00463037
_th10_00463037:
    push edi  # 57
.globl _th10_00463038
_th10_00463038:
    {disp32} call _th10_004629eb  # e8aef9ffff
.globl _th10_0046303d
_th10_0046303d:
    pop ecx  # 59
.globl _th10_0046303e
_th10_0046303e:
    pop ecx  # 59
.globl _th10_0046303f
_th10_0046303f:
    {disp32} call _th10_00456357  # e81333ffff
.globl _th10_00463044
_th10_00463044:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_00463047
_th10_00463047:
    {disp8} {store} mov [edi+8], eax  # 894708
.globl _th10_0046304a
_th10_0046304a:
    {disp32} call _th10_00456357  # e80833ffff
.globl _th10_0046304f
_th10_0046304f:
    {load} mov eax, [eax+0x80]  # 8b8080000000
.globl _th10_00463055
_th10_00463055:
    {disp8} {store} mov [edi+0x0C], eax  # 89470c
.globl _th10_00463058
_th10_00463058:
    {disp32} call _th10_00456357  # e8fa32ffff
.globl _th10_0046305d
_th10_0046305d:
    {disp8} {store} mov [eax+0x7C], esi  # 89707c
.globl _th10_00463060
_th10_00463060:
    {disp8} jmp _th10_0046306a  # eb08
.globl _th10_00463062
_th10_00463062:
    {disp8} or dword ptr [edi+8], -1  # 834f08ff
.globl _th10_00463066
_th10_00463066:
    {disp8} or dword ptr [edi+0x0C], -1  # 834f0cff
.globl _th10_0046306a
_th10_0046306a:
    {disp32} call _th10_00456357  # e8e832ffff
.globl _th10_0046306f
_th10_0046306f:
    {noimm8s} add eax, 0x84  # 0584000000
.globl _th10_00463074
_th10_00463074:
    dec dword ptr [eax]  # ff08
.globl _th10_00463076
_th10_00463076:
    {disp32} call _th10_00456357  # e8dc32ffff
.globl _th10_0046307b
_th10_0046307b:
    cmp dword ptr [eax+0x84], 0  # 83b88400000000
.globl _th10_00463082
_th10_00463082:
    pop edi  # 5f
.globl _th10_00463083
_th10_00463083:
    pop esi  # 5e
.globl _th10_00463084
_th10_00463084:
    {disp8} jge _th10_00463092  # 7d0c
.globl _th10_00463086
_th10_00463086:
    {disp32} call _th10_00456357  # e8cc32ffff
.globl _th10_0046308b
_th10_0046308b:
    and dword ptr [eax+0x84], 0  # 83a08400000000
.globl _th10_00463092
_th10_00463092:
    {load} xor eax, eax  # 33c0
.globl _th10_00463094
_th10_00463094:
    inc eax  # 40
.globl _th10_00463095
_th10_00463095:
    ret  # c3
.globl _th10_00463096
_th10_00463096:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_0046309a
_th10_0046309a:
    test eax, eax  # 85c0
.globl _th10_0046309c
_th10_0046309c:
    {disp8} je _th10_004630cb  # 742d
.globl _th10_0046309e
_th10_0046309e:
    {load} mov eax, [eax]  # 8b00
.globl _th10_004630a0
_th10_004630a0:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_004630a6
_th10_004630a6:
    {disp8} jne _th10_004630cb  # 7523
.globl _th10_004630a8
_th10_004630a8:
    {disp8} cmp dword ptr [eax+0x10], 3  # 83781003
.globl _th10_004630ac
_th10_004630ac:
    {disp8} jne _th10_004630cb  # 751d
.globl _th10_004630ae
_th10_004630ae:
    {disp8} {load} mov ecx, [eax+0x14]  # 8b4814
.globl _th10_004630b1
_th10_004630b1:
    {noimm8s} cmp ecx, 0x19930520  # 81f920059319
.globl _th10_004630b7
_th10_004630b7:
    {disp8} je _th10_004630c1  # 7408
.globl _th10_004630b9
_th10_004630b9:
    {noimm8s} cmp ecx, 0x19930521  # 81f921059319
.globl _th10_004630bf
_th10_004630bf:
    {disp8} jne _th10_004630cb  # 750a
.globl _th10_004630c1
_th10_004630c1:
    {disp8} cmp dword ptr [eax+0x1C], 0  # 83781c00
.globl _th10_004630c5
_th10_004630c5:
    {disp8} jne _th10_004630cb  # 7504
.globl _th10_004630c7
_th10_004630c7:
    {load} xor eax, eax  # 33c0
.globl _th10_004630c9
_th10_004630c9:
    inc eax  # 40
.globl _th10_004630ca
_th10_004630ca:
    ret  # c3
.globl _th10_004630cb
_th10_004630cb:
    {load} xor eax, eax  # 33c0
.globl _th10_004630cd
_th10_004630cd:
    ret  # c3
.globl _th10_004630ce
_th10_004630ce:
    push esi  # 56
.globl _th10_004630cf
_th10_004630cf:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_004630d3
_th10_004630d3:
    {disp8} cmp dword ptr [esi+8], -1  # 837e08ff
.globl _th10_004630d7
_th10_004630d7:
    {disp32} je _th10_0046316a  # 0f848d000000
.globl _th10_004630dd
_th10_004630dd:
    push esi  # 56
.globl _th10_004630de
_th10_004630de:
    {disp32} call _th10_00462a34  # e851f9ffff
.globl _th10_004630e3
_th10_004630e3:
    {disp8} cmp dword ptr [esp+0x10], 0  # 837c241000
.globl _th10_004630e8
_th10_004630e8:
    pop ecx  # 59
.globl _th10_004630e9
_th10_004630e9:
    {disp8} jne _th10_00463151  # 7566
.globl _th10_004630eb
_th10_004630eb:
    {disp32} call _th10_00456357  # e86732ffff
.globl _th10_004630f0
_th10_004630f0:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_004630f3
_th10_004630f3:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_004630f9
_th10_004630f9:
    {disp8} jne _th10_00463151  # 7556
.globl _th10_004630fb
_th10_004630fb:
    {disp32} call _th10_00456357  # e85732ffff
.globl _th10_00463100
_th10_00463100:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_00463103
_th10_00463103:
    {disp8} cmp dword ptr [eax+0x10], 3  # 83781003
.globl _th10_00463107
_th10_00463107:
    {disp8} jne _th10_00463151  # 7548
.globl _th10_00463109
_th10_00463109:
    {disp32} call _th10_00456357  # e84932ffff
.globl _th10_0046310e
_th10_0046310e:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_00463111
_th10_00463111:
    {disp8} {noimm8s} cmp dword ptr [eax+0x14], 0x19930520  # 81781420059319
.globl _th10_00463118
_th10_00463118:
    {disp8} je _th10_0046312b  # 7411
.globl _th10_0046311a
_th10_0046311a:
    {disp32} call _th10_00456357  # e83832ffff
.globl _th10_0046311f
_th10_0046311f:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_00463122
_th10_00463122:
    {disp8} {noimm8s} cmp dword ptr [eax+0x14], 0x19930521  # 81781421059319
.globl _th10_00463129
_th10_00463129:
    {disp8} jne _th10_00463151  # 7526
.globl _th10_0046312b
_th10_0046312b:
    {disp32} call _th10_00456357  # e82732ffff
.globl _th10_00463130
_th10_00463130:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_00463133
_th10_00463133:
    {disp8} push dword ptr [eax+0x18]  # ff7018
.globl _th10_00463136
_th10_00463136:
    {disp32} call _th10_00462a13  # e8d8f8ffff
.globl _th10_0046313b
_th10_0046313b:
    test eax, eax  # 85c0
.globl _th10_0046313d
_th10_0046313d:
    pop ecx  # 59
.globl _th10_0046313e
_th10_0046313e:
    {disp8} je _th10_00463151  # 7411
.globl _th10_00463140
_th10_00463140:
    push 1  # 6a01
.globl _th10_00463142
_th10_00463142:
    {disp32} call _th10_00456357  # e81032ffff
.globl _th10_00463147
_th10_00463147:
    {disp8} push dword ptr [eax+0x7C]  # ff707c
.globl _th10_0046314a
_th10_0046314a:
    {disp32} call _th10_00462f7c  # e82dfeffff
.globl _th10_0046314f
_th10_0046314f:
    pop ecx  # 59
.globl _th10_00463150
_th10_00463150:
    pop ecx  # 59
.globl _th10_00463151
_th10_00463151:
    {disp32} call _th10_00456357  # e80132ffff
.globl _th10_00463156
_th10_00463156:
    {disp8} {load} mov ecx, [esi+8]  # 8b4e08
.globl _th10_00463159
_th10_00463159:
    {disp8} {store} mov [eax+0x7C], ecx  # 89487c
.globl _th10_0046315c
_th10_0046315c:
    {disp32} call _th10_00456357  # e8f631ffff
.globl _th10_00463161
_th10_00463161:
    {disp8} {load} mov ecx, [esi+0x0C]  # 8b4e0c
.globl _th10_00463164
_th10_00463164:
    {store} mov [eax+0x80], ecx  # 898880000000
.globl _th10_0046316a
_th10_0046316a:
    pop esi  # 5e
.globl _th10_0046316b
_th10_0046316b:
    ret  # c3
.globl _th10_0046316c
_th10_0046316c:
    push 16  # 6a10
.globl _th10_0046316e
_th10_0046316e:
    pop eax  # 58
.globl _th10_0046316f
_th10_0046316f:
    ret  # c3
.globl _th10_00463170
_th10_00463170:
    push 8  # 6a08
.globl _th10_00463172
_th10_00463172:
    {noimm8s} push 0x46CAD0  # 68d0ca4600
.globl _th10_00463177
_th10_00463177:
    {disp32} call _th10_00454bbc  # e8401affff
.globl _th10_0046317c
_th10_0046317c:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_00463180
_th10_00463180:
    {disp8} {load} mov ecx, [ebp+0x0C]  # 8b4d0c
.globl _th10_00463183
_th10_00463183:
    {disp8} call dword ptr [ebp+8]  # ff5508
.globl _th10_00463186
_th10_00463186:
    {disp8} jmp _th10_00463194  # eb0c
.globl _th10_00463188
_th10_00463188:
    {disp8} {load} mov eax, [ebp-0x14]  # 8b45ec
.globl _th10_0046318b
_th10_0046318b:
    {disp32} call _th10_00462e60  # e8d0fcffff
.globl _th10_00463190
_th10_00463190:
    ret  # c3
.globl _th10_00463191
_th10_00463191:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00463194
_th10_00463194:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00463198
_th10_00463198:
    {disp32} call _th10_00454bf7  # e85a1affff
.globl _th10_0046319d
_th10_0046319d:
    ret  # c3
.globl _th10_0046319e
_th10_0046319e:
    push 8  # 6a08
.globl _th10_004631a0
_th10_004631a0:
    {noimm8s} push 0x46CAE0  # 68e0ca4600
.globl _th10_004631a5
_th10_004631a5:
    {disp32} call _th10_00454bbc  # e8121affff
.globl _th10_004631aa
_th10_004631aa:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_004631ae
_th10_004631ae:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_004631b1
_th10_004631b1:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004631b4
_th10_004631b4:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004631b7
_th10_004631b7:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004631ba
_th10_004631ba:
    {disp8} call dword ptr [ebp+8]  # ff5508
.globl _th10_004631bd
_th10_004631bd:
    {disp8} jmp _th10_004631cb  # eb0c
.globl _th10_004631bf
_th10_004631bf:
    {disp8} {load} mov eax, [ebp-0x14]  # 8b45ec
.globl _th10_004631c2
_th10_004631c2:
    {disp32} call _th10_00462e60  # e899fcffff
.globl _th10_004631c7
_th10_004631c7:
    ret  # c3
.globl _th10_004631c8
_th10_004631c8:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_004631cb
_th10_004631cb:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_004631cf
_th10_004631cf:
    {disp32} call _th10_00454bf7  # e8231affff
.globl _th10_004631d4
_th10_004631d4:
    ret  # c3
.globl _th10_004631d5
_th10_004631d5:
    push 64  # 6a40
.globl _th10_004631d7
_th10_004631d7:
    {noimm8s} push 0x46CAF0  # 68f0ca4600
.globl _th10_004631dc
_th10_004631dc:
    {disp32} call _th10_00454bbc  # e8db19ffff
.globl _th10_004631e1
_th10_004631e1:
    {load} mov ebx, ecx  # 8bd9
.globl _th10_004631e3
_th10_004631e3:
    {disp8} {load} mov edi, [ebp+0x0C]  # 8b7d0c
.globl _th10_004631e6
_th10_004631e6:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_004631e9
_th10_004631e9:
    {disp8} {store} mov [ebp-0x20], ebx  # 895de0
.globl _th10_004631ec
_th10_004631ec:
    {disp8} and dword ptr [ebp-0x48], 0  # 8365b800
.globl _th10_004631f0
_th10_004631f0:
    {disp8} {load} mov eax, [edi-4]  # 8b47fc
.globl _th10_004631f3
_th10_004631f3:
    {disp8} {store} mov [ebp-0x38], eax  # 8945c8
.globl _th10_004631f6
_th10_004631f6:
    {disp8} push dword ptr [esi+0x18]  # ff7618
.globl _th10_004631f9
_th10_004631f9:
    {disp8} lea eax, [ebp-0x50]  # 8d45b0
.globl _th10_004631fc
_th10_004631fc:
    push eax  # 50
.globl _th10_004631fd
_th10_004631fd:
    {disp32} call _th10_004629eb  # e8e9f7ffff
.globl _th10_00463202
_th10_00463202:
    pop ecx  # 59
.globl _th10_00463203
_th10_00463203:
    pop ecx  # 59
.globl _th10_00463204
_th10_00463204:
    {disp8} {store} mov [ebp-0x3C], eax  # 8945c4
.globl _th10_00463207
_th10_00463207:
    {disp32} call _th10_00456357  # e84b31ffff
.globl _th10_0046320c
_th10_0046320c:
    {disp8} {load} mov eax, [eax+0x7C]  # 8b407c
.globl _th10_0046320f
_th10_0046320f:
    {disp8} {store} mov [ebp-0x40], eax  # 8945c0
.globl _th10_00463212
_th10_00463212:
    {disp32} call _th10_00456357  # e84031ffff
.globl _th10_00463217
_th10_00463217:
    {load} mov eax, [eax+0x80]  # 8b8080000000
.globl _th10_0046321d
_th10_0046321d:
    {disp8} {store} mov [ebp-0x44], eax  # 8945bc
.globl _th10_00463220
_th10_00463220:
    {disp32} call _th10_00456357  # e83231ffff
.globl _th10_00463225
_th10_00463225:
    {disp8} {store} mov [eax+0x7C], esi  # 89707c
.globl _th10_00463228
_th10_00463228:
    {disp32} call _th10_00456357  # e82a31ffff
.globl _th10_0046322d
_th10_0046322d:
    {disp8} {load} mov ecx, [ebp+0x10]  # 8b4d10
.globl _th10_00463230
_th10_00463230:
    {store} mov [eax+0x80], ecx  # 898880000000
.globl _th10_00463236
_th10_00463236:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_0046323a
_th10_0046323a:
    {disp8} {noimm8s} mov dword ptr [ebp-4], 1  # c745fc01000000
.globl _th10_00463241
_th10_00463241:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_00463244
_th10_00463244:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_00463247
_th10_00463247:
    push ebx  # 53
.globl _th10_00463248
_th10_00463248:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_0046324b
_th10_0046324b:
    push edi  # 57
.globl _th10_0046324c
_th10_0046324c:
    {disp32} call _th10_00462a80  # e82ff8ffff
.globl _th10_00463251
_th10_00463251:
    add esp, 20  # 83c414
.globl _th10_00463254
_th10_00463254:
    {disp8} {store} mov [ebp-0x20], eax  # 8945e0
.globl _th10_00463257
_th10_00463257:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_0046325b
_th10_0046325b:
    {disp32} jmp _th10_0046330f  # e9af000000
.globl _th10_00463260
_th10_00463260:
    {disp8} {load} mov eax, [ebp-0x14]  # 8b45ec
.globl _th10_00463263
_th10_00463263:
    {load} mov eax, [eax]  # 8b00
.globl _th10_00463265
_th10_00463265:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_00463268
_th10_00463268:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_0046326b
_th10_0046326b:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_00463271
_th10_00463271:
    {disp8} jne _th10_004632a4  # 7531
.globl _th10_00463273
_th10_00463273:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_00463276
_th10_00463276:
    {disp8} cmp dword ptr [eax+0x10], 3  # 83781003
.globl _th10_0046327a
_th10_0046327a:
    {disp8} jne _th10_004632a4  # 7528
.globl _th10_0046327c
_th10_0046327c:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_0046327f
_th10_0046327f:
    {disp8} {noimm8s} cmp dword ptr [eax+0x14], 0x19930520  # 81781420059319
.globl _th10_00463286
_th10_00463286:
    {disp8} je _th10_00463294  # 740c
.globl _th10_00463288
_th10_00463288:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_0046328b
_th10_0046328b:
    {disp8} {noimm8s} cmp dword ptr [eax+0x14], 0x19930521  # 81781421059319
.globl _th10_00463292
_th10_00463292:
    {disp8} jne _th10_004632a4  # 7510
.globl _th10_00463294
_th10_00463294:
    {disp8} {load} mov eax, [ebp-0x1C]  # 8b45e4
.globl _th10_00463297
_th10_00463297:
    {disp8} cmp dword ptr [eax+0x1C], 0  # 83781c00
.globl _th10_0046329b
_th10_0046329b:
    {disp8} {noimm8s} mov dword ptr [ebp-0x24], 1  # c745dc01000000
.globl _th10_004632a2
_th10_004632a2:
    {disp8} je _th10_004632ab  # 7407
.globl _th10_004632a4
_th10_004632a4:
    {disp8} {noimm8s} mov dword ptr [ebp-0x24], 0  # c745dc00000000
.globl _th10_004632ab
_th10_004632ab:
    {disp8} {load} mov eax, [ebp-0x24]  # 8b45dc
.globl _th10_004632ae
_th10_004632ae:
    ret  # c3
.globl _th10_004632af
_th10_004632af:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_004632b2
_th10_004632b2:
    {disp8} {load} mov ecx, [ebp+0x14]  # 8b4d14
.globl _th10_004632b5
_th10_004632b5:
    {disp8} {load} mov eax, [ecx+8]  # 8b4108
.globl _th10_004632b8
_th10_004632b8:
    {disp8} {store} mov [ebp-0x30], eax  # 8945d0
.globl _th10_004632bb
_th10_004632bb:
    {disp8} {load} mov edi, [ebp+0x0C]  # 8b7d0c
.globl _th10_004632be
_th10_004632be:
    {disp8} {load} mov eax, [edi+8]  # 8b4708
.globl _th10_004632c1
_th10_004632c1:
    {disp8} {store} mov [ebp-0x28], eax  # 8945d8
.globl _th10_004632c4
_th10_004632c4:
    {disp8} {load} mov edx, [ecx+0x10]  # 8b5110
.globl _th10_004632c7
_th10_004632c7:
    {disp8} {store} mov [ebp-0x2C], edx  # 8955d4
.globl _th10_004632ca
_th10_004632ca:
    {load} xor edx, edx  # 33d2
.globl _th10_004632cc
_th10_004632cc:
    {disp8} {store} mov [ebp-0x34], edx  # 8955cc
.globl _th10_004632cf
_th10_004632cf:
    {disp8} {load} cmp edx, [ecx+0x0C]  # 3b510c
.globl _th10_004632d2
_th10_004632d2:
    {disp8} jae _th10_004632f8  # 7324
.globl _th10_004632d4
_th10_004632d4:
    lea esi, [edx+edx*4]  # 8d3492
.globl _th10_004632d7
_th10_004632d7:
    {disp8} {load} mov ebx, [ebp-0x2C]  # 8b5dd4
.globl _th10_004632da
_th10_004632da:
    lea esi, [ebx+esi*4]  # 8d34b3
.globl _th10_004632dd
_th10_004632dd:
    {disp8} {load} mov ebx, [esi+4]  # 8b5e04
.globl _th10_004632e0
_th10_004632e0:
    {load} cmp eax, ebx  # 3bc3
.globl _th10_004632e2
_th10_004632e2:
    {disp8} jle _th10_00463321  # 7e3d
.globl _th10_004632e4
_th10_004632e4:
    {disp8} {load} cmp eax, [esi+8]  # 3b4608
.globl _th10_004632e7
_th10_004632e7:
    {disp8} jg _th10_00463321  # 7f38
.globl _th10_004632e9
_th10_004632e9:
    {disp8} lea eax, [ebx+1]  # 8d4301
.globl _th10_004632ec
_th10_004632ec:
    {disp8} {store} mov [ebp-0x28], eax  # 8945d8
.globl _th10_004632ef
_th10_004632ef:
    {disp8} {load} mov edx, [ebp-0x30]  # 8b55d0
.globl _th10_004632f2
_th10_004632f2:
    {load} mov eax, [edx+eax*8]  # 8b04c2
.globl _th10_004632f5
_th10_004632f5:
    {disp8} {store} mov [ebp-0x28], eax  # 8945d8
.globl _th10_004632f8
_th10_004632f8:
    push eax  # 50
.globl _th10_004632f9
_th10_004632f9:
    push ecx  # 51
.globl _th10_004632fa
_th10_004632fa:
    {load} xor esi, esi  # 33f6
.globl _th10_004632fc
_th10_004632fc:
    push esi  # 56
.globl _th10_004632fd
_th10_004632fd:
    push edi  # 57
.globl _th10_004632fe
_th10_004632fe:
    {disp32} call _th10_00462e7e  # e87bfbffff
.globl _th10_00463303
_th10_00463303:
    add esp, 16  # 83c410
.globl _th10_00463306
_th10_00463306:
    {disp8} {store} mov [ebp-0x20], esi  # 8975e0
.globl _th10_00463309
_th10_00463309:
    {disp8} {store} mov [ebp-4], esi  # 8975fc
.globl _th10_0046330c
_th10_0046330c:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_0046330f
_th10_0046330f:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00463313
_th10_00463313:
    {disp32} call _th10_0046332a  # e812000000
.globl _th10_00463318
_th10_00463318:
    {disp8} {load} mov eax, [ebp-0x20]  # 8b45e0
.globl _th10_0046331b
_th10_0046331b:
    {disp32} call _th10_00454bf7  # e8d718ffff
.globl _th10_00463320
_th10_00463320:
    ret  # c3
.globl _th10_00463321
_th10_00463321:
    inc edx  # 42
.globl _th10_00463322
_th10_00463322:
    {disp8} jmp _th10_004632cc  # eba8
.globl _th10_00463324
_th10_00463324:
    {disp8} {load} mov edi, [ebp+0x0C]  # 8b7d0c
.globl _th10_00463327
_th10_00463327:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_0046332a
_th10_0046332a:
    {disp8} {load} mov eax, [ebp-0x38]  # 8b45c8
.globl _th10_0046332d
_th10_0046332d:
    {disp8} {store} mov [edi-4], eax  # 8947fc
.globl _th10_00463330
_th10_00463330:
    {disp8} push dword ptr [ebp-0x3C]  # ff75c4
.globl _th10_00463333
_th10_00463333:
    {disp32} call _th10_00462a34  # e8fcf6ffff
.globl _th10_00463338
_th10_00463338:
    pop ecx  # 59
.globl _th10_00463339
_th10_00463339:
    {disp32} call _th10_00456357  # e81930ffff
.globl _th10_0046333e
_th10_0046333e:
    {disp8} {load} mov ecx, [ebp-0x40]  # 8b4dc0
.globl _th10_00463341
_th10_00463341:
    {disp8} {store} mov [eax+0x7C], ecx  # 89487c
.globl _th10_00463344
_th10_00463344:
    {disp32} call _th10_00456357  # e80e30ffff
.globl _th10_00463349
_th10_00463349:
    {disp8} {load} mov ecx, [ebp-0x44]  # 8b4dbc
.globl _th10_0046334c
_th10_0046334c:
    {store} mov [eax+0x80], ecx  # 898880000000
.globl _th10_00463352
_th10_00463352:
    {noimm8s} cmp dword ptr [esi], 0x0E06D7363  # 813e63736de0
.globl _th10_00463358
_th10_00463358:
    {disp8} jne _th10_00463398  # 753e
.globl _th10_0046335a
_th10_0046335a:
    {disp8} cmp dword ptr [esi+0x10], 3  # 837e1003
.globl _th10_0046335e
_th10_0046335e:
    {disp8} jne _th10_00463398  # 7538
.globl _th10_00463360
_th10_00463360:
    {disp8} {load} mov eax, [esi+0x14]  # 8b4614
.globl _th10_00463363
_th10_00463363:
    {noimm8s} cmp eax, 0x19930520  # 3d20059319
.globl _th10_00463368
_th10_00463368:
    {disp8} je _th10_00463371  # 7407
.globl _th10_0046336a
_th10_0046336a:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_0046336f
_th10_0046336f:
    {disp8} jne _th10_00463398  # 7527
.globl _th10_00463371
_th10_00463371:
    {disp8} cmp dword ptr [ebp-0x48], 0  # 837db800
.globl _th10_00463375
_th10_00463375:
    {disp8} jne _th10_00463398  # 7521
.globl _th10_00463377
_th10_00463377:
    {disp8} cmp dword ptr [ebp-0x20], 0  # 837de000
.globl _th10_0046337b
_th10_0046337b:
    {disp8} je _th10_00463398  # 741b
.globl _th10_0046337d
_th10_0046337d:
    {disp8} push dword ptr [esi+0x18]  # ff7618
.globl _th10_00463380
_th10_00463380:
    {disp32} call _th10_00462a13  # e88ef6ffff
.globl _th10_00463385
_th10_00463385:
    pop ecx  # 59
.globl _th10_00463386
_th10_00463386:
    test eax, eax  # 85c0
.globl _th10_00463388
_th10_00463388:
    {disp8} je _th10_00463398  # 740e
.globl _th10_0046338a
_th10_0046338a:
    {disp32} call _th10_00459946  # e8b765ffff
.globl _th10_0046338f
_th10_0046338f:
    push eax  # 50
.globl _th10_00463390
_th10_00463390:
    push esi  # 56
.globl _th10_00463391
_th10_00463391:
    {disp32} call _th10_00462f7c  # e8e6fbffff
.globl _th10_00463396
_th10_00463396:
    pop ecx  # 59
.globl _th10_00463397
_th10_00463397:
    pop ecx  # 59
.globl _th10_00463398
_th10_00463398:
    ret  # c3
.globl _th10_00463399
_th10_00463399:
    push 8  # 6a08
.globl _th10_0046339b
_th10_0046339b:
    {noimm8s} push 0x46CB08  # 6808cb4600
.globl _th10_004633a0
_th10_004633a0:
    {disp32} call _th10_00454bbc  # e81718ffff
.globl _th10_004633a5
_th10_004633a5:
    {load} mov esi, ecx  # 8bf1
.globl _th10_004633a7
_th10_004633a7:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_004633aa
_th10_004633aa:
    {load} mov edi, edx  # 8bfa
.globl _th10_004633ac
_th10_004633ac:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_004633af
_th10_004633af:
    {disp8} {load} mov ecx, [eax+4]  # 8b4804
.globl _th10_004633b2
_th10_004633b2:
    test ecx, ecx  # 85c9
.globl _th10_004633b4
_th10_004633b4:
    {disp32} je _th10_00463503  # 0f8449010000
.globl _th10_004633ba
_th10_004633ba:
    {disp8} cmp byte ptr [ecx+8], 0  # 80790800
.globl _th10_004633be
_th10_004633be:
    {disp32} je _th10_00463503  # 0f843f010000
.globl _th10_004633c4
_th10_004633c4:
    {disp8} {load} mov ecx, [eax+8]  # 8b4808
.globl _th10_004633c7
_th10_004633c7:
    test ecx, ecx  # 85c9
.globl _th10_004633c9
_th10_004633c9:
    {disp8} jne _th10_004633d5  # 750a
.globl _th10_004633cb
_th10_004633cb:
    {disp8} test byte ptr [eax+3], 0x80  # f6400380
.globl _th10_004633cf
_th10_004633cf:
    {disp32} je _th10_00463503  # 0f842e010000
.globl _th10_004633d5
_th10_004633d5:
    {load} mov eax, [eax]  # 8b00
.globl _th10_004633d7
_th10_004633d7:
    test eax, eax  # 85c0
.globl _th10_004633d9
_th10_004633d9:
    {disp8} js _th10_004633df  # 7804
.globl _th10_004633db
_th10_004633db:
    {disp8} lea edi, [ecx+edi+0x0C]  # 8d7c390c
.globl _th10_004633df
_th10_004633df:
    {disp8} and dword ptr [ebp-4], 0  # 8365fc00
.globl _th10_004633e3
_th10_004633e3:
    push 1  # 6a01
.globl _th10_004633e5
_th10_004633e5:
    {disp8} push dword ptr [ebx+0x18]  # ff7318
.globl _th10_004633e8
_th10_004633e8:
    test al, 8  # a808
.globl _th10_004633ea
_th10_004633ea:
    {disp8} je _th10_00463421  # 7435
.globl _th10_004633ec
_th10_004633ec:
    {disp32} call _th10_00463aca  # e8d9060000
.globl _th10_004633f1
_th10_004633f1:
    pop ecx  # 59
.globl _th10_004633f2
_th10_004633f2:
    pop ecx  # 59
.globl _th10_004633f3
_th10_004633f3:
    test eax, eax  # 85c0
.globl _th10_004633f5
_th10_004633f5:
    {disp32} je _th10_004634fa  # 0f84ff000000
.globl _th10_004633fb
_th10_004633fb:
    push 1  # 6a01
.globl _th10_004633fd
_th10_004633fd:
    push edi  # 57
.globl _th10_004633fe
_th10_004633fe:
    {disp32} call _th10_00463ae6  # e8e3060000
.globl _th10_00463403
_th10_00463403:
    pop ecx  # 59
.globl _th10_00463404
_th10_00463404:
    pop ecx  # 59
.globl _th10_00463405
_th10_00463405:
    test eax, eax  # 85c0
.globl _th10_00463407
_th10_00463407:
    {disp32} je _th10_004634fa  # 0f84ed000000
.globl _th10_0046340d
_th10_0046340d:
    {disp8} {load} mov eax, [ebx+0x18]  # 8b4318
.globl _th10_00463410
_th10_00463410:
    {store} mov [edi], eax  # 8907
.globl _th10_00463412
_th10_00463412:
    {disp8} lea ecx, [esi+8]  # 8d4e08
.globl _th10_00463415
_th10_00463415:
    {disp32} call _th10_00462fc1  # e8a7fbffff
.globl _th10_0046341a
_th10_0046341a:
    {store} mov [edi], eax  # 8907
.globl _th10_0046341c
_th10_0046341c:
    {disp32} jmp _th10_004634ff  # e9de000000
.globl _th10_00463421
_th10_00463421:
    test byte ptr [esi], 1  # f60601
.globl _th10_00463424
_th10_00463424:
    {disp8} je _th10_0046346c  # 7446
.globl _th10_00463426
_th10_00463426:
    {disp32} call _th10_00463aca  # e89f060000
.globl _th10_0046342b
_th10_0046342b:
    pop ecx  # 59
.globl _th10_0046342c
_th10_0046342c:
    pop ecx  # 59
.globl _th10_0046342d
_th10_0046342d:
    test eax, eax  # 85c0
.globl _th10_0046342f
_th10_0046342f:
    {disp32} je _th10_004634fa  # 0f84c5000000
.globl _th10_00463435
_th10_00463435:
    push 1  # 6a01
.globl _th10_00463437
_th10_00463437:
    push edi  # 57
.globl _th10_00463438
_th10_00463438:
    {disp32} call _th10_00463ae6  # e8a9060000
.globl _th10_0046343d
_th10_0046343d:
    pop ecx  # 59
.globl _th10_0046343e
_th10_0046343e:
    pop ecx  # 59
.globl _th10_0046343f
_th10_0046343f:
    test eax, eax  # 85c0
.globl _th10_00463441
_th10_00463441:
    {disp32} je _th10_004634fa  # 0f84b3000000
.globl _th10_00463447
_th10_00463447:
    {disp8} push dword ptr [esi+0x14]  # ff7614
.globl _th10_0046344a
_th10_0046344a:
    {disp8} push dword ptr [ebx+0x18]  # ff7318
.globl _th10_0046344d
_th10_0046344d:
    push edi  # 57
.globl _th10_0046344e
_th10_0046344e:
    {disp32} call _th10_00453280  # e82dfefeff
.globl _th10_00463453
_th10_00463453:
    add esp, 12  # 83c40c
.globl _th10_00463456
_th10_00463456:
    {disp8} cmp dword ptr [esi+0x14], 4  # 837e1404
.globl _th10_0046345a
_th10_0046345a:
    {disp32} jne _th10_004634ff  # 0f859f000000
.globl _th10_00463460
_th10_00463460:
    {load} mov eax, [edi]  # 8b07
.globl _th10_00463462
_th10_00463462:
    test eax, eax  # 85c0
.globl _th10_00463464
_th10_00463464:
    {disp32} je _th10_004634ff  # 0f8495000000
.globl _th10_0046346a
_th10_0046346a:
    {disp8} jmp _th10_00463412  # eba6
.globl _th10_0046346c
_th10_0046346c:
    {disp8} cmp dword ptr [esi+0x18], 0  # 837e1800
.globl _th10_00463470
_th10_00463470:
    {disp8} jne _th10_004634a5  # 7533
.globl _th10_00463472
_th10_00463472:
    {disp32} call _th10_00463aca  # e853060000
.globl _th10_00463477
_th10_00463477:
    pop ecx  # 59
.globl _th10_00463478
_th10_00463478:
    pop ecx  # 59
.globl _th10_00463479
_th10_00463479:
    test eax, eax  # 85c0
.globl _th10_0046347b
_th10_0046347b:
    {disp8} je _th10_004634fa  # 747d
.globl _th10_0046347d
_th10_0046347d:
    push 1  # 6a01
.globl _th10_0046347f
_th10_0046347f:
    push edi  # 57
.globl _th10_00463480
_th10_00463480:
    {disp32} call _th10_00463ae6  # e861060000
.globl _th10_00463485
_th10_00463485:
    pop ecx  # 59
.globl _th10_00463486
_th10_00463486:
    pop ecx  # 59
.globl _th10_00463487
_th10_00463487:
    test eax, eax  # 85c0
.globl _th10_00463489
_th10_00463489:
    {disp8} je _th10_004634fa  # 746f
.globl _th10_0046348b
_th10_0046348b:
    {disp8} push dword ptr [esi+0x14]  # ff7614
.globl _th10_0046348e
_th10_0046348e:
    {disp8} lea ecx, [esi+8]  # 8d4e08
.globl _th10_00463491
_th10_00463491:
    {disp8} {load} mov eax, [ebx+0x18]  # 8b4318
.globl _th10_00463494
_th10_00463494:
    {disp32} call _th10_00462fc1  # e828fbffff
.globl _th10_00463499
_th10_00463499:
    push eax  # 50
.globl _th10_0046349a
_th10_0046349a:
    push edi  # 57
.globl _th10_0046349b
_th10_0046349b:
    {disp32} call _th10_00453280  # e8e0fdfeff
.globl _th10_004634a0
_th10_004634a0:
    add esp, 12  # 83c40c
.globl _th10_004634a3
_th10_004634a3:
    {disp8} jmp _th10_004634ff  # eb5a
.globl _th10_004634a5
_th10_004634a5:
    {disp32} call _th10_00463aca  # e820060000
.globl _th10_004634aa
_th10_004634aa:
    pop ecx  # 59
.globl _th10_004634ab
_th10_004634ab:
    pop ecx  # 59
.globl _th10_004634ac
_th10_004634ac:
    test eax, eax  # 85c0
.globl _th10_004634ae
_th10_004634ae:
    {disp8} je _th10_004634fa  # 744a
.globl _th10_004634b0
_th10_004634b0:
    push 1  # 6a01
.globl _th10_004634b2
_th10_004634b2:
    push edi  # 57
.globl _th10_004634b3
_th10_004634b3:
    {disp32} call _th10_00463ae6  # e82e060000
.globl _th10_004634b8
_th10_004634b8:
    pop ecx  # 59
.globl _th10_004634b9
_th10_004634b9:
    pop ecx  # 59
.globl _th10_004634ba
_th10_004634ba:
    test eax, eax  # 85c0
.globl _th10_004634bc
_th10_004634bc:
    {disp8} je _th10_004634fa  # 743c
.globl _th10_004634be
_th10_004634be:
    {disp8} push dword ptr [esi+0x18]  # ff7618
.globl _th10_004634c1
_th10_004634c1:
    {disp32} call _th10_00463b02  # e83c060000
.globl _th10_004634c6
_th10_004634c6:
    pop ecx  # 59
.globl _th10_004634c7
_th10_004634c7:
    test eax, eax  # 85c0
.globl _th10_004634c9
_th10_004634c9:
    {disp8} je _th10_004634fa  # 742f
.globl _th10_004634cb
_th10_004634cb:
    {disp8} {load} mov eax, [ebx+0x18]  # 8b4318
.globl _th10_004634ce
_th10_004634ce:
    {disp8} lea ecx, [esi+8]  # 8d4e08
.globl _th10_004634d1
_th10_004634d1:
    test byte ptr [esi], 4  # f60604
.globl _th10_004634d4
_th10_004634d4:
    {disp8} je _th10_004634e9  # 7413
.globl _th10_004634d6
_th10_004634d6:
    push 1  # 6a01
.globl _th10_004634d8
_th10_004634d8:
    {disp32} call _th10_00462fc1  # e8e4faffff
.globl _th10_004634dd
_th10_004634dd:
    push eax  # 50
.globl _th10_004634de
_th10_004634de:
    {disp8} push dword ptr [esi+0x18]  # ff7618
.globl _th10_004634e1
_th10_004634e1:
    push edi  # 57
.globl _th10_004634e2
_th10_004634e2:
    {disp32} call _th10_00462714  # e82df2ffff
.globl _th10_004634e7
_th10_004634e7:
    {disp8} jmp _th10_004634ff  # eb16
.globl _th10_004634e9
_th10_004634e9:
    {disp32} call _th10_00462fc1  # e8d3faffff
.globl _th10_004634ee
_th10_004634ee:
    push eax  # 50
.globl _th10_004634ef
_th10_004634ef:
    {disp8} push dword ptr [esi+0x18]  # ff7618
.globl _th10_004634f2
_th10_004634f2:
    push edi  # 57
.globl _th10_004634f3
_th10_004634f3:
    {disp32} call _th10_0046270d  # e815f2ffff
.globl _th10_004634f8
_th10_004634f8:
    {disp8} jmp _th10_004634ff  # eb05
.globl _th10_004634fa
_th10_004634fa:
    {disp32} call _th10_004556e0  # e8e121ffff
.globl _th10_004634ff
_th10_004634ff:
    {disp8} or dword ptr [ebp-4], -1  # 834dfcff
.globl _th10_00463503
_th10_00463503:
    {disp32} call _th10_00454bf7  # e8ef16ffff
.globl _th10_00463508
_th10_00463508:
    ret  # c3
.globl _th10_00463509
_th10_00463509:
    {load} xor eax, eax  # 33c0
.globl _th10_0046350b
_th10_0046350b:
    inc eax  # 40
.globl _th10_0046350c
_th10_0046350c:
    ret  # c3
.globl _th10_0046350d
_th10_0046350d:
    {disp8} {load} mov esp, [ebp-0x18]  # 8b65e8
.globl _th10_00463510
_th10_00463510:
    {disp32} jmp _th10_00455693  # e97e21ffff
.globl _th10_00463515
_th10_00463515:
    push ebp  # 55
.globl _th10_00463516
_th10_00463516:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463518
_th10_00463518:
    sub esp, 20  # 83ec14
.globl _th10_0046351b
_th10_0046351b:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_0046351e
_th10_0046351e:
    push edi  # 57
.globl _th10_0046351f
_th10_0046351f:
    {load} xor edi, edi  # 33ff
.globl _th10_00463521
_th10_00463521:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00463523
_th10_00463523:
    {disp8} jne _th10_0046352c  # 7507
.globl _th10_00463525
_th10_00463525:
    {load} xor eax, eax  # 33c0
.globl _th10_00463527
_th10_00463527:
    {disp32} jmp _th10_00463637  # e90b010000
.globl _th10_0046352c
_th10_0046352c:
    push ebx  # 53
.globl _th10_0046352d
_th10_0046352d:
    {load} mov ebx, [eax]  # 8b18
.globl _th10_0046352f
_th10_0046352f:
    push esi  # 56
.globl _th10_00463530
_th10_00463530:
    {disp8} {load} mov esi, [ebp+0x0C]  # 8b750c
.globl _th10_00463533
_th10_00463533:
    {load} cmp esi, edi  # 3bf7
.globl _th10_00463535
_th10_00463535:
    {disp32} je _th10_004635f4  # 0f84b9000000
.globl _th10_0046353b
_th10_0046353b:
    {disp8} cmp byte ptr [esi+8], 0  # 807e0800
.globl _th10_0046353f
_th10_0046353f:
    {disp32} je _th10_004635f4  # 0f84af000000
.globl _th10_00463545
_th10_00463545:
    {noimm8s} cmp dword ptr [ebx], 0x0E06D7363  # 813b63736de0
.globl _th10_0046354b
_th10_0046354b:
    {disp32} jne _th10_00463622  # 0f85d1000000
.globl _th10_00463551
_th10_00463551:
    {disp8} cmp dword ptr [ebx+0x10], 3  # 837b1003
.globl _th10_00463555
_th10_00463555:
    {disp32} jne _th10_00463622  # 0f85c7000000
.globl _th10_0046355b
_th10_0046355b:
    {disp8} {load} mov eax, [ebx+0x14]  # 8b4314
.globl _th10_0046355e
_th10_0046355e:
    {noimm8s} cmp eax, 0x19930520  # 3d20059319
.globl _th10_00463563
_th10_00463563:
    {disp8} je _th10_00463570  # 740b
.globl _th10_00463565
_th10_00463565:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_0046356a
_th10_0046356a:
    {disp32} jne _th10_00463622  # 0f85b2000000
.globl _th10_00463570
_th10_00463570:
    {disp8} {store} cmp [ebx+0x1C], edi  # 397b1c
.globl _th10_00463573
_th10_00463573:
    {disp8} jne _th10_0046358b  # 7516
.globl _th10_00463575
_th10_00463575:
    {disp32} call _th10_00456357  # e8dd2dffff
.globl _th10_0046357a
_th10_0046357a:
    {disp8} {store} cmp [eax+0x7C], edi  # 39787c
.globl _th10_0046357d
_th10_0046357d:
    {disp32} je _th10_00463622  # 0f849f000000
.globl _th10_00463583
_th10_00463583:
    {disp32} call _th10_00456357  # e8cf2dffff
.globl _th10_00463588
_th10_00463588:
    {disp8} {load} mov ebx, [eax+0x7C]  # 8b587c
.globl _th10_0046358b
_th10_0046358b:
    {disp8} {load} mov eax, [ebp+0x10]  # 8b4510
.globl _th10_0046358e
_th10_0046358e:
    {noimm8s} or eax, 0x80000000  # 0d00000080
.globl _th10_00463593
_th10_00463593:
    {disp8} {store} mov [ebp-0x14], eax  # 8945ec
.globl _th10_00463596
_th10_00463596:
    {disp8} {load} mov eax, [ebx+0x1C]  # 8b431c
.globl _th10_00463599
_th10_00463599:
    {disp8} {load} mov eax, [eax+0x0C]  # 8b400c
.globl _th10_0046359c
_th10_0046359c:
    {disp8} lea ecx, [eax+4]  # 8d4804
.globl _th10_0046359f
_th10_0046359f:
    {load} mov eax, [eax]  # 8b00
.globl _th10_004635a1
_th10_004635a1:
    {load} cmp eax, edi  # 3bc7
.globl _th10_004635a3
_th10_004635a3:
    {disp8} {store} mov [ebp-0x10], esi  # 8975f0
.globl _th10_004635a6
_th10_004635a6:
    {disp8} {store} mov [ebp+8], ecx  # 894d08
.globl _th10_004635a9
_th10_004635a9:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_004635ac
_th10_004635ac:
    {disp8} jle _th10_00463622  # 7e74
.globl _th10_004635ae
_th10_004635ae:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004635b1
_th10_004635b1:
    {disp8} push dword ptr [ebx+0x1C]  # ff731c
.globl _th10_004635b4
_th10_004635b4:
    {load} mov edi, [eax]  # 8b38
.globl _th10_004635b6
_th10_004635b6:
    {disp8} lea esi, [ebp-0x14]  # 8d75ec
.globl _th10_004635b9
_th10_004635b9:
    {disp32} call _th10_00462e11  # e853f8ffff
.globl _th10_004635be
_th10_004635be:
    test eax, eax  # 85c0
.globl _th10_004635c0
_th10_004635c0:
    pop ecx  # 59
.globl _th10_004635c1
_th10_004635c1:
    {disp8} jne _th10_004635d1  # 750e
.globl _th10_004635c3
_th10_004635c3:
    {disp8} dec dword ptr [ebp-4]  # ff4dfc
.globl _th10_004635c6
_th10_004635c6:
    {disp8} add dword ptr [ebp+8], 4  # 83450804
.globl _th10_004635ca
_th10_004635ca:
    {disp8} {store} cmp [ebp-4], eax  # 3945fc
.globl _th10_004635cd
_th10_004635cd:
    {disp8} jg _th10_004635ae  # 7fdf
.globl _th10_004635cf
_th10_004635cf:
    {disp8} jmp _th10_00463622  # eb51
.globl _th10_004635d1
_th10_004635d1:
    {disp32} call _th10_00456357  # e8812dffff
.globl _th10_004635d6
_th10_004635d6:
    {disp8} {load} mov edx, [ebp+0x14]  # 8b5514
.globl _th10_004635d9
_th10_004635d9:
    {noimm8s} add eax, 0x84  # 0584000000
.globl _th10_004635de
_th10_004635de:
    inc dword ptr [eax]  # ff00
.globl _th10_004635e0
_th10_004635e0:
    test edx, edx  # 85d2
.globl _th10_004635e2
_th10_004635e2:
    {disp8} je _th10_00463632  # 744e
.globl _th10_004635e4
_th10_004635e4:
    {disp8} lea eax, [ebp-0x14]  # 8d45ec
.globl _th10_004635e7
_th10_004635e7:
    push eax  # 50
.globl _th10_004635e8
_th10_004635e8:
    push ebx  # 53
.globl _th10_004635e9
_th10_004635e9:
    {load} mov ecx, edi  # 8bcf
.globl _th10_004635eb
_th10_004635eb:
    {disp32} call _th10_00463399  # e8a9fdffff
.globl _th10_004635f0
_th10_004635f0:
    pop ecx  # 59
.globl _th10_004635f1
_th10_004635f1:
    pop ecx  # 59
.globl _th10_004635f2
_th10_004635f2:
    {disp8} jmp _th10_00463632  # eb3e
.globl _th10_004635f4
_th10_004635f4:
    {noimm8s} cmp dword ptr [ebx], 0x0E06D7363  # 813b63736de0
.globl _th10_004635fa
_th10_004635fa:
    {disp8} jne _th10_00463626  # 752a
.globl _th10_004635fc
_th10_004635fc:
    {disp8} cmp dword ptr [ebx+0x10], 3  # 837b1003
.globl _th10_00463600
_th10_00463600:
    {disp8} jne _th10_00463626  # 7524
.globl _th10_00463602
_th10_00463602:
    {disp8} {load} mov eax, [ebx+0x14]  # 8b4314
.globl _th10_00463605
_th10_00463605:
    {noimm8s} cmp eax, 0x19930520  # 3d20059319
.globl _th10_0046360a
_th10_0046360a:
    {disp8} je _th10_00463613  # 7407
.globl _th10_0046360c
_th10_0046360c:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_00463611
_th10_00463611:
    {disp8} jne _th10_00463626  # 7513
.globl _th10_00463613
_th10_00463613:
    {disp8} {store} cmp [ebx+0x1C], edi  # 397b1c
.globl _th10_00463616
_th10_00463616:
    {disp8} jne _th10_00463626  # 750e
.globl _th10_00463618
_th10_00463618:
    {disp32} call _th10_00456357  # e83a2dffff
.globl _th10_0046361d
_th10_0046361d:
    {disp8} {store} cmp [eax+0x7C], edi  # 39787c
.globl _th10_00463620
_th10_00463620:
    {disp8} jne _th10_00463626  # 7504
.globl _th10_00463622
_th10_00463622:
    {load} xor eax, eax  # 33c0
.globl _th10_00463624
_th10_00463624:
    {disp8} jmp _th10_00463635  # eb0f
.globl _th10_00463626
_th10_00463626:
    {disp32} call _th10_00456357  # e82c2dffff
.globl _th10_0046362b
_th10_0046362b:
    {noimm8s} add eax, 0x84  # 0584000000
.globl _th10_00463630
_th10_00463630:
    inc dword ptr [eax]  # ff00
.globl _th10_00463632
_th10_00463632:
    {load} xor eax, eax  # 33c0
.globl _th10_00463634
_th10_00463634:
    inc eax  # 40
.globl _th10_00463635
_th10_00463635:
    pop esi  # 5e
.globl _th10_00463636
_th10_00463636:
    pop ebx  # 5b
.globl _th10_00463637
_th10_00463637:
    pop edi  # 5f
.globl _th10_00463638
_th10_00463638:
    leave  # c9
.globl _th10_00463639
_th10_00463639:
    ret  # c3
.globl _th10_0046363a
_th10_0046363a:
    push ebp  # 55
.globl _th10_0046363b
_th10_0046363b:
    {load} mov ebp, esp  # 8bec
.globl _th10_0046363d
_th10_0046363d:
    test ecx, ecx  # 85c9
.globl _th10_0046363f
_th10_0046363f:
    {disp8} je _th10_0046364e  # 740d
.globl _th10_00463641
_th10_00463641:
    push ebx  # 53
.globl _th10_00463642
_th10_00463642:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00463645
_th10_00463645:
    {load} mov edx, esi  # 8bd6
.globl _th10_00463647
_th10_00463647:
    {disp32} call _th10_00463399  # e84dfdffff
.globl _th10_0046364c
_th10_0046364c:
    pop ecx  # 59
.globl _th10_0046364d
_th10_0046364d:
    pop ecx  # 59
.globl _th10_0046364e
_th10_0046364e:
    {disp8} cmp dword ptr [ebp+0x1C], 0  # 837d1c00
.globl _th10_00463652
_th10_00463652:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00463655
_th10_00463655:
    {disp8} jne _th10_0046365a  # 7503
.globl _th10_00463657
_th10_00463657:
    push esi  # 56
.globl _th10_00463658
_th10_00463658:
    {disp8} jmp _th10_0046365d  # eb03
.globl _th10_0046365a
_th10_0046365a:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_0046365d
_th10_0046365d:
    {disp32} call _th10_0046271b  # e8b9f0ffff
.globl _th10_00463662
_th10_00463662:
    push dword ptr [edi]  # ff37
.globl _th10_00463664
_th10_00463664:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00463667
_th10_00463667:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_0046366a
_th10_0046366a:
    push esi  # 56
.globl _th10_0046366b
_th10_0046366b:
    {disp32} call _th10_00462e7e  # e80ef8ffff
.globl _th10_00463670
_th10_00463670:
    {disp8} {load} mov eax, [edi+4]  # 8b4704
.globl _th10_00463673
_th10_00463673:
    {noimm8s} push 0x100  # 6800010000
.globl _th10_00463678
_th10_00463678:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_0046367b
_th10_0046367b:
    inc eax  # 40
.globl _th10_0046367c
_th10_0046367c:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_0046367f
_th10_0046367f:
    {disp8} {store} mov [esi+8], eax  # 894608
.globl _th10_00463682
_th10_00463682:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00463685
_th10_00463685:
    {disp8} {load} mov ecx, [ebx+0x0C]  # 8b4b0c
.globl _th10_00463688
_th10_00463688:
    push esi  # 56
.globl _th10_00463689
_th10_00463689:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_0046368c
_th10_0046368c:
    {disp32} call _th10_004631d5  # e844fbffff
.globl _th10_00463691
_th10_00463691:
    add esp, 40  # 83c428
.globl _th10_00463694
_th10_00463694:
    test eax, eax  # 85c0
.globl _th10_00463696
_th10_00463696:
    {disp8} je _th10_0046369f  # 7407
.globl _th10_00463698
_th10_00463698:
    push esi  # 56
.globl _th10_00463699
_th10_00463699:
    push eax  # 50
.globl _th10_0046369a
_th10_0046369a:
    {disp32} call _th10_004626d6  # e837f0ffff
.globl _th10_0046369f
_th10_0046369f:
    pop ebp  # 5d
.globl _th10_004636a0
_th10_004636a0:
    ret  # c3
.globl _th10_004636a1
_th10_004636a1:
    push ebp  # 55
.globl _th10_004636a2
_th10_004636a2:
    {load} mov ebp, esp  # 8bec
.globl _th10_004636a4
_th10_004636a4:
    push ecx  # 51
.globl _th10_004636a5
_th10_004636a5:
    push ecx  # 51
.globl _th10_004636a6
_th10_004636a6:
    push esi  # 56
.globl _th10_004636a7
_th10_004636a7:
    {disp8} {load} mov esi, [ebp+8]  # 8b7508
.globl _th10_004636aa
_th10_004636aa:
    {noimm8s} cmp dword ptr [esi], 0x80000003  # 813e03000080
.globl _th10_004636b0
_th10_004636b0:
    {disp32} je _th10_0046375c  # 0f84a6000000
.globl _th10_004636b6
_th10_004636b6:
    {disp32} call _th10_00456357  # e89c2cffff
.globl _th10_004636bb
_th10_004636bb:
    {disp8} cmp dword ptr [eax+0x74], 0  # 83787400
.globl _th10_004636bf
_th10_004636bf:
    {disp8} je _th10_004636e0  # 741f
.globl _th10_004636c1
_th10_004636c1:
    {disp8} push dword ptr [ebp+0x24]  # ff7524
.globl _th10_004636c4
_th10_004636c4:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_004636c7
_th10_004636c7:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_004636ca
_th10_004636ca:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004636cd
_th10_004636cd:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004636d0
_th10_004636d0:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004636d3
_th10_004636d3:
    push esi  # 56
.globl _th10_004636d4
_th10_004636d4:
    {disp32} call _th10_004627f8  # e81ff1ffff
.globl _th10_004636d9
_th10_004636d9:
    add esp, 28  # 83c41c
.globl _th10_004636dc
_th10_004636dc:
    test eax, eax  # 85c0
.globl _th10_004636de
_th10_004636de:
    {disp8} jne _th10_0046375c  # 757c
.globl _th10_004636e0
_th10_004636e0:
    {disp8} {load} mov esi, [ebp+0x1C]  # 8b751c
.globl _th10_004636e3
_th10_004636e3:
    push edi  # 57
.globl _th10_004636e4
_th10_004636e4:
    {disp8} lea eax, [ebp-8]  # 8d45f8
.globl _th10_004636e7
_th10_004636e7:
    push eax  # 50
.globl _th10_004636e8
_th10_004636e8:
    {disp8} lea eax, [ebp-4]  # 8d45fc
.globl _th10_004636eb
_th10_004636eb:
    push eax  # 50
.globl _th10_004636ec
_th10_004636ec:
    push esi  # 56
.globl _th10_004636ed
_th10_004636ed:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_004636f0
_th10_004636f0:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_004636f3
_th10_004636f3:
    {disp32} call _th10_00462971  # e879f2ffff
.globl _th10_004636f8
_th10_004636f8:
    {load} mov edi, eax  # 8bf8
.globl _th10_004636fa
_th10_004636fa:
    {disp8} {load} mov eax, [ebp-4]  # 8b45fc
.globl _th10_004636fd
_th10_004636fd:
    add esp, 20  # 83c414
.globl _th10_00463700
_th10_00463700:
    {disp8} {load} cmp eax, [ebp-8]  # 3b45f8
.globl _th10_00463703
_th10_00463703:
    {disp8} jae _th10_0046375b  # 7356
.globl _th10_00463705
_th10_00463705:
    push ebx  # 53
.globl _th10_00463706
_th10_00463706:
    {load} cmp esi, [edi]  # 3b37
.globl _th10_00463708
_th10_00463708:
    {disp8} jl _th10_0046374c  # 7c42
.globl _th10_0046370a
_th10_0046370a:
    {disp8} {load} cmp esi, [edi+4]  # 3b7704
.globl _th10_0046370d
_th10_0046370d:
    {disp8} jg _th10_0046374c  # 7f3d
.globl _th10_0046370f
_th10_0046370f:
    {disp8} {load} mov eax, [edi+0x0C]  # 8b470c
.globl _th10_00463712
_th10_00463712:
    {disp8} {load} mov ecx, [edi+0x10]  # 8b4f10
.globl _th10_00463715
_th10_00463715:
    shl eax, 4  # c1e004
.globl _th10_00463718
_th10_00463718:
    {load} add eax, ecx  # 03c1
.globl _th10_0046371a
_th10_0046371a:
    {disp8} {load} mov ecx, [eax-0x0C]  # 8b48f4
.globl _th10_0046371d
_th10_0046371d:
    test ecx, ecx  # 85c9
.globl _th10_0046371f
_th10_0046371f:
    {disp8} je _th10_00463727  # 7406
.globl _th10_00463721
_th10_00463721:
    {disp8} cmp byte ptr [ecx+8], 0  # 80790800
.globl _th10_00463725
_th10_00463725:
    {disp8} jne _th10_0046374c  # 7525
.globl _th10_00463727
_th10_00463727:
    {disp8} push dword ptr [ebp+0x24]  # ff7524
.globl _th10_0046372a
_th10_0046372a:
    {disp8} {load} mov esi, [ebp+0x0C]  # 8b750c
.globl _th10_0046372d
_th10_0046372d:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00463730
_th10_00463730:
    {disp8} lea ebx, [eax-0x10]  # 8d58f0
.globl _th10_00463733
_th10_00463733:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_00463736
_th10_00463736:
    {load} xor ecx, ecx  # 33c9
.globl _th10_00463738
_th10_00463738:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_0046373b
_th10_0046373b:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_0046373e
_th10_0046373e:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00463741
_th10_00463741:
    {disp32} call _th10_0046363a  # e8f4feffff
.globl _th10_00463746
_th10_00463746:
    {disp8} {load} mov esi, [ebp+0x1C]  # 8b751c
.globl _th10_00463749
_th10_00463749:
    add esp, 24  # 83c418
.globl _th10_0046374c
_th10_0046374c:
    {disp8} inc dword ptr [ebp-4]  # ff45fc
.globl _th10_0046374f
_th10_0046374f:
    {disp8} {load} mov eax, [ebp-4]  # 8b45fc
.globl _th10_00463752
_th10_00463752:
    add edi, 20  # 83c714
.globl _th10_00463755
_th10_00463755:
    {disp8} {load} cmp eax, [ebp-8]  # 3b45f8
.globl _th10_00463758
_th10_00463758:
    {disp8} jb _th10_00463706  # 72ac
.globl _th10_0046375a
_th10_0046375a:
    pop ebx  # 5b
.globl _th10_0046375b
_th10_0046375b:
    pop edi  # 5f
.globl _th10_0046375c
_th10_0046375c:
    pop esi  # 5e
.globl _th10_0046375d
_th10_0046375d:
    leave  # c9
.globl _th10_0046375e
_th10_0046375e:
    ret  # c3
.globl _th10_0046375f
_th10_0046375f:
    push ebp  # 55
.globl _th10_00463760
_th10_00463760:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463762
_th10_00463762:
    sub esp, 36  # 83ec24
.globl _th10_00463765
_th10_00463765:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00463768
_th10_00463768:
    {disp8} {load} mov eax, [eax+8]  # 8b4008
.globl _th10_0046376b
_th10_0046376b:
    cmp eax, -1  # 83f8ff
.globl _th10_0046376e
_th10_0046376e:
    {disp8} mov byte ptr [ebp-1], 0  # c645ff00
.globl _th10_00463772
_th10_00463772:
    {disp8} {store} mov [ebp-0x1C], eax  # 8945e4
.globl _th10_00463775
_th10_00463775:
    {disp8} jl _th10_0046377f  # 7c08
.globl _th10_00463777
_th10_00463777:
    {disp8} {load} mov ecx, [ebp+0x18]  # 8b4d18
.globl _th10_0046377a
_th10_0046377a:
    {disp8} {load} cmp eax, [ecx+4]  # 3b4104
.globl _th10_0046377d
_th10_0046377d:
    {disp8} jl _th10_00463784  # 7c05
.globl _th10_0046377f
_th10_0046377f:
    {disp32} call _th10_004556e0  # e85c1fffff
.globl _th10_00463784
_th10_00463784:
    push ebx  # 53
.globl _th10_00463785
_th10_00463785:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00463788
_th10_00463788:
    {noimm8s} cmp dword ptr [ebx], 0x0E06D7363  # 813b63736de0
.globl _th10_0046378e
_th10_0046378e:
    push esi  # 56
.globl _th10_0046378f
_th10_0046378f:
    push edi  # 57
.globl _th10_00463790
_th10_00463790:
    {disp32} jne _th10_00463938  # 0f85a2010000
.globl _th10_00463796
_th10_00463796:
    {disp8} cmp dword ptr [ebx+0x10], 3  # 837b1003
.globl _th10_0046379a
_th10_0046379a:
    {noimm8s} mov edi, 0x19930520  # bf20059319
.globl _th10_0046379f
_th10_0046379f:
    {disp32} jne _th10_0046382c  # 0f8587000000
.globl _th10_004637a5
_th10_004637a5:
    {disp8} {load} mov eax, [ebx+0x14]  # 8b4314
.globl _th10_004637a8
_th10_004637a8:
    {load} cmp eax, edi  # 3bc7
.globl _th10_004637aa
_th10_004637aa:
    {disp8} je _th10_004637b3  # 7407
.globl _th10_004637ac
_th10_004637ac:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_004637b1
_th10_004637b1:
    {disp8} jne _th10_0046382c  # 7579
.globl _th10_004637b3
_th10_004637b3:
    {disp8} cmp dword ptr [ebx+0x1C], 0  # 837b1c00
.globl _th10_004637b7
_th10_004637b7:
    {disp8} jne _th10_0046382c  # 7573
.globl _th10_004637b9
_th10_004637b9:
    {disp32} call _th10_00456357  # e8992bffff
.globl _th10_004637be
_th10_004637be:
    {disp8} cmp dword ptr [eax+0x7C], 0  # 83787c00
.globl _th10_004637c2
_th10_004637c2:
    {disp32} je _th10_00463930  # 0f8468010000
.globl _th10_004637c8
_th10_004637c8:
    {disp32} call _th10_00456357  # e88a2bffff
.globl _th10_004637cd
_th10_004637cd:
    {disp8} {load} mov esi, [eax+0x7C]  # 8b707c
.globl _th10_004637d0
_th10_004637d0:
    {disp8} {store} mov [ebp+8], esi  # 897508
.globl _th10_004637d3
_th10_004637d3:
    {disp32} call _th10_00456357  # e87f2bffff
.globl _th10_004637d8
_th10_004637d8:
    {load} mov eax, [eax+0x80]  # 8b8080000000
.globl _th10_004637de
_th10_004637de:
    push 1  # 6a01
.globl _th10_004637e0
_th10_004637e0:
    push esi  # 56
.globl _th10_004637e1
_th10_004637e1:
    {disp8} {store} mov [ebp+0x10], eax  # 894510
.globl _th10_004637e4
_th10_004637e4:
    {disp8} mov byte ptr [ebp-1], 1  # c645ff01
.globl _th10_004637e8
_th10_004637e8:
    {disp32} call _th10_00463aca  # e8dd020000
.globl _th10_004637ed
_th10_004637ed:
    test eax, eax  # 85c0
.globl _th10_004637ef
_th10_004637ef:
    pop ecx  # 59
.globl _th10_004637f0
_th10_004637f0:
    pop ecx  # 59
.globl _th10_004637f1
_th10_004637f1:
    {disp8} jne _th10_004637f8  # 7505
.globl _th10_004637f3
_th10_004637f3:
    {disp32} call _th10_004556e0  # e8e81effff
.globl _th10_004637f8
_th10_004637f8:
    {noimm8s} cmp dword ptr [esi], 0x0E06D7363  # 813e63736de0
.globl _th10_004637fe
_th10_004637fe:
    {disp32} jne _th10_00463935  # 0f8531010000
.globl _th10_00463804
_th10_00463804:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00463807
_th10_00463807:
    {disp8} cmp dword ptr [eax+0x10], 3  # 83781003
.globl _th10_0046380b
_th10_0046380b:
    {disp8} jne _th10_00463829  # 751c
.globl _th10_0046380d
_th10_0046380d:
    {disp8} {load} mov eax, [eax+0x14]  # 8b4014
.globl _th10_00463810
_th10_00463810:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00463812
_th10_00463812:
    {disp8} je _th10_0046381b  # 7407
.globl _th10_00463814
_th10_00463814:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_00463819
_th10_00463819:
    {disp8} jne _th10_00463829  # 750e
.globl _th10_0046381b
_th10_0046381b:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_0046381e
_th10_0046381e:
    {disp8} cmp dword ptr [eax+0x1C], 0  # 83781c00
.globl _th10_00463822
_th10_00463822:
    {disp8} jne _th10_00463829  # 7505
.globl _th10_00463824
_th10_00463824:
    {disp32} call _th10_004556e0  # e8b71effff
.globl _th10_00463829
_th10_00463829:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_0046382c
_th10_0046382c:
    {noimm8s} cmp dword ptr [ebx], 0x0E06D7363  # 813b63736de0
.globl _th10_00463832
_th10_00463832:
    {disp32} jne _th10_00463938  # 0f8500010000
.globl _th10_00463838
_th10_00463838:
    {disp8} cmp dword ptr [ebx+0x10], 3  # 837b1003
.globl _th10_0046383c
_th10_0046383c:
    {disp32} jne _th10_00463938  # 0f85f6000000
.globl _th10_00463842
_th10_00463842:
    {disp8} {load} mov eax, [ebx+0x14]  # 8b4314
.globl _th10_00463845
_th10_00463845:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00463847
_th10_00463847:
    {disp8} je _th10_00463854  # 740b
.globl _th10_00463849
_th10_00463849:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_0046384e
_th10_0046384e:
    {disp32} jne _th10_00463938  # 0f85e4000000
.globl _th10_00463854
_th10_00463854:
    {disp8} {load} mov esi, [ebp-0x1C]  # 8b75e4
.globl _th10_00463857
_th10_00463857:
    {disp8} lea eax, [ebp-0x20]  # 8d45e0
.globl _th10_0046385a
_th10_0046385a:
    push eax  # 50
.globl _th10_0046385b
_th10_0046385b:
    {disp8} lea eax, [ebp-0x0C]  # 8d45f4
.globl _th10_0046385e
_th10_0046385e:
    push eax  # 50
.globl _th10_0046385f
_th10_0046385f:
    push esi  # 56
.globl _th10_00463860
_th10_00463860:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00463863
_th10_00463863:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_00463866
_th10_00463866:
    {disp32} call _th10_00462971  # e806f1ffff
.globl _th10_0046386b
_th10_0046386b:
    {disp8} {load} mov ecx, [ebp-0x0C]  # 8b4df4
.globl _th10_0046386e
_th10_0046386e:
    add esp, 20  # 83c414
.globl _th10_00463871
_th10_00463871:
    {disp8} {load} cmp ecx, [ebp-0x20]  # 3b4de0
.globl _th10_00463874
_th10_00463874:
    {disp8} {store} mov [ebp-8], eax  # 8945f8
.globl _th10_00463877
_th10_00463877:
    {disp32} jae _th10_00463920  # 0f83a3000000
.globl _th10_0046387d
_th10_0046387d:
    {disp8} jmp _th10_00463882  # eb03
.globl _th10_0046387f
_th10_0046387f:
    {disp8} {load} mov esi, [ebp-0x1C]  # 8b75e4
.globl _th10_00463882
_th10_00463882:
    {store} cmp [eax], esi  # 3930
.globl _th10_00463884
_th10_00463884:
    {disp32} jg _th10_0046390b  # 0f8f81000000
.globl _th10_0046388a
_th10_0046388a:
    {disp8} {load} cmp esi, [eax+4]  # 3b7004
.globl _th10_0046388d
_th10_0046388d:
    {disp8} jg _th10_0046390b  # 7f7c
.globl _th10_0046388f
_th10_0046388f:
    {disp8} {load} mov ecx, [eax+0x0C]  # 8b480c
.globl _th10_00463892
_th10_00463892:
    test ecx, ecx  # 85c9
.globl _th10_00463894
_th10_00463894:
    {disp8} {load} mov esi, [eax+0x10]  # 8b7010
.globl _th10_00463897
_th10_00463897:
    {disp8} {store} mov [ebp-0x18], ecx  # 894de8
.globl _th10_0046389a
_th10_0046389a:
    {disp8} jle _th10_0046390b  # 7e6f
.globl _th10_0046389c
_th10_0046389c:
    {disp8} {load} mov ecx, [ebx+0x1C]  # 8b4b1c
.globl _th10_0046389f
_th10_0046389f:
    {disp8} {load} mov ecx, [ecx+0x0C]  # 8b490c
.globl _th10_004638a2
_th10_004638a2:
    {disp8} lea edx, [ecx+4]  # 8d5104
.globl _th10_004638a5
_th10_004638a5:
    {load} mov ecx, [ecx]  # 8b09
.globl _th10_004638a7
_th10_004638a7:
    test ecx, ecx  # 85c9
.globl _th10_004638a9
_th10_004638a9:
    {disp8} {store} mov [ebp-0x10], edx  # 8955f0
.globl _th10_004638ac
_th10_004638ac:
    {disp8} {store} mov [ebp-0x14], ecx  # 894dec
.globl _th10_004638af
_th10_004638af:
    {disp8} jle _th10_004638d5  # 7e24
.globl _th10_004638b1
_th10_004638b1:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_004638b4
_th10_004638b4:
    {load} mov edi, [eax]  # 8b38
.globl _th10_004638b6
_th10_004638b6:
    {disp8} push dword ptr [ebx+0x1C]  # ff731c
.globl _th10_004638b9
_th10_004638b9:
    {disp8} {store} mov [ebp-0x24], edi  # 897ddc
.globl _th10_004638bc
_th10_004638bc:
    {disp32} call _th10_00462e11  # e850f5ffff
.globl _th10_004638c1
_th10_004638c1:
    test eax, eax  # 85c0
.globl _th10_004638c3
_th10_004638c3:
    pop ecx  # 59
.globl _th10_004638c4
_th10_004638c4:
    {disp8} jne _th10_004638e3  # 751d
.globl _th10_004638c6
_th10_004638c6:
    {disp8} dec dword ptr [ebp-0x14]  # ff4dec
.globl _th10_004638c9
_th10_004638c9:
    {disp8} add dword ptr [ebp-0x10], 4  # 8345f004
.globl _th10_004638cd
_th10_004638cd:
    {disp8} {store} cmp [ebp-0x14], eax  # 3945ec
.globl _th10_004638d0
_th10_004638d0:
    {disp8} jg _th10_004638b1  # 7fdf
.globl _th10_004638d2
_th10_004638d2:
    {disp8} {load} mov eax, [ebp-8]  # 8b45f8
.globl _th10_004638d5
_th10_004638d5:
    {disp8} dec dword ptr [ebp-0x18]  # ff4de8
.globl _th10_004638d8
_th10_004638d8:
    add esi, 16  # 83c610
.globl _th10_004638db
_th10_004638db:
    {disp8} cmp dword ptr [ebp-0x18], 0  # 837de800
.globl _th10_004638df
_th10_004638df:
    {disp8} jg _th10_0046389c  # 7fbb
.globl _th10_004638e1
_th10_004638e1:
    {disp8} jmp _th10_0046390b  # eb28
.globl _th10_004638e3
_th10_004638e3:
    {disp8} push dword ptr [ebp+0x24]  # ff7524
.globl _th10_004638e6
_th10_004638e6:
    {disp8} {load} mov edi, [ebp-8]  # 8b7df8
.globl _th10_004638e9
_th10_004638e9:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_004638ec
_th10_004638ec:
    {disp8} {load} mov ecx, [ebp-0x24]  # 8b4ddc
.globl _th10_004638ef
_th10_004638ef:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_004638f2
_th10_004638f2:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004638f5
_th10_004638f5:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004638f8
_th10_004638f8:
    push ebx  # 53
.globl _th10_004638f9
_th10_004638f9:
    {load} mov ebx, esi  # 8bde
.globl _th10_004638fb
_th10_004638fb:
    {disp8} {load} mov esi, [ebp+0x0C]  # 8b750c
.globl _th10_004638fe
_th10_004638fe:
    {disp32} call _th10_0046363a  # e837fdffff
.globl _th10_00463903
_th10_00463903:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00463906
_th10_00463906:
    add esp, 24  # 83c418
.globl _th10_00463909
_th10_00463909:
    {load} mov eax, edi  # 8bc7
.globl _th10_0046390b
_th10_0046390b:
    {disp8} inc dword ptr [ebp-0x0C]  # ff45f4
.globl _th10_0046390e
_th10_0046390e:
    {disp8} {load} mov ecx, [ebp-0x0C]  # 8b4df4
.globl _th10_00463911
_th10_00463911:
    add eax, 20  # 83c014
.globl _th10_00463914
_th10_00463914:
    {disp8} {load} cmp ecx, [ebp-0x20]  # 3b4de0
.globl _th10_00463917
_th10_00463917:
    {disp8} {store} mov [ebp-8], eax  # 8945f8
.globl _th10_0046391a
_th10_0046391a:
    {disp32} jb _th10_0046387f  # 0f825fffffff
.globl _th10_00463920
_th10_00463920:
    {disp8} cmp byte ptr [ebp+0x1C], 0  # 807d1c00
.globl _th10_00463924
_th10_00463924:
    {disp8} je _th10_00463930  # 740a
.globl _th10_00463926
_th10_00463926:
    push 1  # 6a01
.globl _th10_00463928
_th10_00463928:
    push ebx  # 53
.globl _th10_00463929
_th10_00463929:
    {disp32} call _th10_00462f7c  # e84ef6ffff
.globl _th10_0046392e
_th10_0046392e:
    pop ecx  # 59
.globl _th10_0046392f
_th10_0046392f:
    pop ecx  # 59
.globl _th10_00463930
_th10_00463930:
    pop edi  # 5f
.globl _th10_00463931
_th10_00463931:
    pop esi  # 5e
.globl _th10_00463932
_th10_00463932:
    pop ebx  # 5b
.globl _th10_00463933
_th10_00463933:
    leave  # c9
.globl _th10_00463934
_th10_00463934:
    ret  # c3
.globl _th10_00463935
_th10_00463935:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00463938
_th10_00463938:
    {disp8} cmp byte ptr [ebp+0x1C], 0  # 807d1c00
.globl _th10_0046393c
_th10_0046393c:
    {disp8} jne _th10_0046395e  # 7520
.globl _th10_0046393e
_th10_0046393e:
    {disp8} push dword ptr [ebp+0x24]  # ff7524
.globl _th10_00463941
_th10_00463941:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_00463944
_th10_00463944:
    {disp8} push dword ptr [ebp-0x1C]  # ff75e4
.globl _th10_00463947
_th10_00463947:
    {disp8} push dword ptr [ebp+0x18]  # ff7518
.globl _th10_0046394a
_th10_0046394a:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_0046394d
_th10_0046394d:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_00463950
_th10_00463950:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00463953
_th10_00463953:
    push ebx  # 53
.globl _th10_00463954
_th10_00463954:
    {disp32} call _th10_004636a1  # e848fdffff
.globl _th10_00463959
_th10_00463959:
    add esp, 32  # 83c420
.globl _th10_0046395c
_th10_0046395c:
    {disp8} jmp _th10_00463930  # ebd2
.globl _th10_0046395e
_th10_0046395e:
    {disp32} jmp _th10_00455693  # e9301dffff
.globl _th10_00463963
_th10_00463963:
    push ebp  # 55
.globl _th10_00463964
_th10_00463964:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463966
_th10_00463966:
    push esi  # 56
.globl _th10_00463967
_th10_00463967:
    {disp8} {load} mov esi, [ebp+0x18]  # 8b7518
.globl _th10_0046396a
_th10_0046396a:
    {load} mov eax, [esi]  # 8b06
.globl _th10_0046396c
_th10_0046396c:
    push edi  # 57
.globl _th10_0046396d
_th10_0046396d:
    {noimm8s} and eax, 0x1FFFFFFF  # 25ffffff1f
.globl _th10_00463972
_th10_00463972:
    {noimm8s} mov edi, 0x19930520  # bf20059319
.globl _th10_00463977
_th10_00463977:
    {load} cmp eax, edi  # 3bc7
.globl _th10_00463979
_th10_00463979:
    {disp8} je _th10_00463980  # 7405
.globl _th10_0046397b
_th10_0046397b:
    {disp32} call _th10_004556e0  # e8601dffff
.globl _th10_00463980
_th10_00463980:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00463983
_th10_00463983:
    {disp8} test byte ptr [eax+4], 0x66  # f6400466
.globl _th10_00463987
_th10_00463987:
    {disp8} je _th10_004639a8  # 741f
.globl _th10_00463989
_th10_00463989:
    {disp8} cmp dword ptr [esi+4], 0  # 837e0400
.globl _th10_0046398d
_th10_0046398d:
    {disp8} je _th10_004639fe  # 746f
.globl _th10_0046398f
_th10_0046398f:
    {disp8} cmp dword ptr [ebp+0x1C], 0  # 837d1c00
.globl _th10_00463993
_th10_00463993:
    {disp8} jne _th10_004639fe  # 7569
.globl _th10_00463995
_th10_00463995:
    push -1  # 6aff
.globl _th10_00463997
_th10_00463997:
    push esi  # 56
.globl _th10_00463998
_th10_00463998:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_0046399b
_th10_0046399b:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_0046399e
_th10_0046399e:
    {disp32} call _th10_00462e7e  # e8dbf4ffff
.globl _th10_004639a3
_th10_004639a3:
    add esp, 16  # 83c410
.globl _th10_004639a6
_th10_004639a6:
    {disp8} jmp _th10_004639fe  # eb56
.globl _th10_004639a8
_th10_004639a8:
    {disp8} cmp dword ptr [esi+0x0C], 0  # 837e0c00
.globl _th10_004639ac
_th10_004639ac:
    {disp8} je _th10_004639fe  # 7450
.globl _th10_004639ae
_th10_004639ae:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_004639b4
_th10_004639b4:
    {disp8} jne _th10_004639e2  # 752c
.globl _th10_004639b6
_th10_004639b6:
    {disp8} {store} cmp [eax+0x14], edi  # 397814
.globl _th10_004639b9
_th10_004639b9:
    {disp8} jbe _th10_004639e2  # 7627
.globl _th10_004639bb
_th10_004639bb:
    {disp8} {load} mov ecx, [eax+0x1C]  # 8b481c
.globl _th10_004639be
_th10_004639be:
    {disp8} {load} mov ecx, [ecx+8]  # 8b4908
.globl _th10_004639c1
_th10_004639c1:
    test ecx, ecx  # 85c9
.globl _th10_004639c3
_th10_004639c3:
    {disp8} je _th10_004639e2  # 741d
.globl _th10_004639c5
_th10_004639c5:
    {disp8} movzx edx, byte ptr [ebp+0x24]  # 0fb65524
.globl _th10_004639c9
_th10_004639c9:
    push edx  # 52
.globl _th10_004639ca
_th10_004639ca:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_004639cd
_th10_004639cd:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_004639d0
_th10_004639d0:
    push esi  # 56
.globl _th10_004639d1
_th10_004639d1:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004639d4
_th10_004639d4:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004639d7
_th10_004639d7:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004639da
_th10_004639da:
    push eax  # 50
.globl _th10_004639db
_th10_004639db:
    call ecx  # ffd1
.globl _th10_004639dd
_th10_004639dd:
    add esp, 32  # 83c420
.globl _th10_004639e0
_th10_004639e0:
    {disp8} jmp _th10_00463a01  # eb1f
.globl _th10_004639e2
_th10_004639e2:
    {disp8} push dword ptr [ebp+0x20]  # ff7520
.globl _th10_004639e5
_th10_004639e5:
    {disp8} push dword ptr [ebp+0x1C]  # ff751c
.globl _th10_004639e8
_th10_004639e8:
    {disp8} push dword ptr [ebp+0x24]  # ff7524
.globl _th10_004639eb
_th10_004639eb:
    push esi  # 56
.globl _th10_004639ec
_th10_004639ec:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_004639ef
_th10_004639ef:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_004639f2
_th10_004639f2:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_004639f5
_th10_004639f5:
    push eax  # 50
.globl _th10_004639f6
_th10_004639f6:
    {disp32} call _th10_0046375f  # e864fdffff
.globl _th10_004639fb
_th10_004639fb:
    add esp, 32  # 83c420
.globl _th10_004639fe
_th10_004639fe:
    {load} xor eax, eax  # 33c0
.globl _th10_00463a00
_th10_00463a00:
    inc eax  # 40
.globl _th10_00463a01
_th10_00463a01:
    pop edi  # 5f
.globl _th10_00463a02
_th10_00463a02:
    pop esi  # 5e
.globl _th10_00463a03
_th10_00463a03:
    pop ebp  # 5d
.globl _th10_00463a04
_th10_00463a04:
    ret  # c3
# padding 00463a05..00463a0f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00463a10
_th10_00463a10:
    push ebp  # 55
.globl _th10_00463a11
_th10_00463a11:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463a13
_th10_00463a13:
    sub esp, 4  # 83ec04
.globl _th10_00463a16
_th10_00463a16:
    push ebx  # 53
.globl _th10_00463a17
_th10_00463a17:
    push ecx  # 51
.globl _th10_00463a18
_th10_00463a18:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00463a1b
_th10_00463a1b:
    add eax, 12  # 83c00c
.globl _th10_00463a1e
_th10_00463a1e:
    {disp8} {store} mov [ebp-4], eax  # 8945fc
.globl _th10_00463a21
_th10_00463a21:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_00463a24
_th10_00463a24:
    push ebp  # 55
.globl _th10_00463a25
_th10_00463a25:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_00463a28
_th10_00463a28:
    {disp8} {load} mov ecx, [ebp+0x10]  # 8b4d10
.globl _th10_00463a2b
_th10_00463a2b:
    {disp8} {load} mov ebp, [ebp-4]  # 8b6dfc
.globl _th10_00463a2e
_th10_00463a2e:
    {disp32} call _th10_00459969  # e8365fffff
.globl _th10_00463a33
_th10_00463a33:
    push esi  # 56
.globl _th10_00463a34
_th10_00463a34:
    push edi  # 57
.globl _th10_00463a35
_th10_00463a35:
    call eax  # ffd0
.globl _th10_00463a37
_th10_00463a37:
    pop edi  # 5f
.globl _th10_00463a38
_th10_00463a38:
    pop esi  # 5e
.globl _th10_00463a39
_th10_00463a39:
    {load} mov ebx, ebp  # 8bdd
.globl _th10_00463a3b
_th10_00463a3b:
    pop ebp  # 5d
.globl _th10_00463a3c
_th10_00463a3c:
    {disp8} {load} mov ecx, [ebp+0x10]  # 8b4d10
.globl _th10_00463a3f
_th10_00463a3f:
    push ebp  # 55
.globl _th10_00463a40
_th10_00463a40:
    {load} mov ebp, ebx  # 8beb
.globl _th10_00463a42
_th10_00463a42:
    {noimm8s} cmp ecx, 0x100  # 81f900010000
.globl _th10_00463a48
_th10_00463a48:
    {disp8} jne _th10_00463a4f  # 7505
.globl _th10_00463a4a
_th10_00463a4a:
    {noimm8s} mov ecx, 2  # b902000000
.globl _th10_00463a4f
_th10_00463a4f:
    push ecx  # 51
.globl _th10_00463a50
_th10_00463a50:
    {disp32} call _th10_00459969  # e8145fffff
.globl _th10_00463a55
_th10_00463a55:
    pop ebp  # 5d
.globl _th10_00463a56
_th10_00463a56:
    pop ecx  # 59
.globl _th10_00463a57
_th10_00463a57:
    pop ebx  # 5b
.globl _th10_00463a58
_th10_00463a58:
    leave  # c9
.globl _th10_00463a59
_th10_00463a59:
    {noimm8s} ret 0x0C  # c20c00
.globl _th10_00463a5c
_th10_00463a5c:
    push esi  # 56
.globl _th10_00463a5d
_th10_00463a5d:
    {disp8} {load} mov esi, [esp+8]  # 8b742408
.globl _th10_00463a61
_th10_00463a61:
    {load} mov eax, [esi]  # 8b06
.globl _th10_00463a63
_th10_00463a63:
    {noimm8s} cmp dword ptr [eax], 0x0E06D7363  # 813863736de0
.globl _th10_00463a69
_th10_00463a69:
    {disp8} jne _th10_00463a87  # 751c
.globl _th10_00463a6b
_th10_00463a6b:
    {disp8} cmp dword ptr [eax+0x10], 3  # 83781003
.globl _th10_00463a6f
_th10_00463a6f:
    {disp8} jne _th10_00463a87  # 7516
.globl _th10_00463a71
_th10_00463a71:
    {disp8} {load} mov eax, [eax+0x14]  # 8b4014
.globl _th10_00463a74
_th10_00463a74:
    {noimm8s} cmp eax, 0x19930520  # 3d20059319
.globl _th10_00463a79
_th10_00463a79:
    {disp8} je _th10_00463a82  # 7407
.globl _th10_00463a7b
_th10_00463a7b:
    {noimm8s} cmp eax, 0x19930521  # 3d21059319
.globl _th10_00463a80
_th10_00463a80:
    {disp8} jne _th10_00463a87  # 7505
.globl _th10_00463a82
_th10_00463a82:
    {disp32} call _th10_00455693  # e80c1cffff
.globl _th10_00463a87
_th10_00463a87:
    mov eax, [_th10_004776d8]  # a1d8764700
.globl _th10_00463a8c
_th10_00463a8c:
    test eax, eax  # 85c0
.globl _th10_00463a8e
_th10_00463a8e:
    {disp8} je _th10_00463aa4  # 7414
.globl _th10_00463a90
_th10_00463a90:
    push eax  # 50
.globl _th10_00463a91
_th10_00463a91:
    {disp32} call _th10_00463b02  # e86c000000
.globl _th10_00463a96
_th10_00463a96:
    test eax, eax  # 85c0
.globl _th10_00463a98
_th10_00463a98:
    pop ecx  # 59
.globl _th10_00463a99
_th10_00463a99:
    {disp8} je _th10_00463aa4  # 7409
.globl _th10_00463a9b
_th10_00463a9b:
    push esi  # 56
.globl _th10_00463a9c
_th10_00463a9c:
    call dword ptr [_th10_004776d8]  # ff15d8764700
.globl _th10_00463aa2
_th10_00463aa2:
    {disp8} jmp _th10_00463aa6  # eb02
.globl _th10_00463aa4
_th10_00463aa4:
    {load} xor eax, eax  # 33c0
.globl _th10_00463aa6
_th10_00463aa6:
    pop esi  # 5e
.globl _th10_00463aa7
_th10_00463aa7:
    {noimm8s} ret 4  # c20400
.globl _th10_00463aaa
_th10_00463aaa:
    {noimm8s} push 0x463A5C  # 685c3a4600
.globl _th10_00463aaf
_th10_00463aaf:
    call dword ptr [_th10_004661d4]  # ff15d4614600
.globl _th10_00463ab5
_th10_00463ab5:
    mov [_th10_004776d8], eax  # a3d8764700
.globl _th10_00463aba
_th10_00463aba:
    {load} xor eax, eax  # 33c0
.globl _th10_00463abc
_th10_00463abc:
    ret  # c3
.globl _th10_00463abd
_th10_00463abd:
    push dword ptr [_th10_004776d8]  # ff35d8764700
.globl _th10_00463ac3
_th10_00463ac3:
    call dword ptr [_th10_004661d4]  # ff15d4614600
.globl _th10_00463ac9
_th10_00463ac9:
    ret  # c3
.globl _th10_00463aca
_th10_00463aca:
    push esi  # 56
.globl _th10_00463acb
_th10_00463acb:
    {disp8} push dword ptr [esp+0x0C]  # ff74240c
.globl _th10_00463acf
_th10_00463acf:
    {load} xor esi, esi  # 33f6
.globl _th10_00463ad1
_th10_00463ad1:
    {disp8} push dword ptr [esp+0x0C]  # ff74240c
.globl _th10_00463ad5
_th10_00463ad5:
    inc esi  # 46
.globl _th10_00463ad6
_th10_00463ad6:
    call dword ptr [_th10_004661d8]  # ff15d8614600
.globl _th10_00463adc
_th10_00463adc:
    test eax, eax  # 85c0
.globl _th10_00463ade
_th10_00463ade:
    {disp8} je _th10_00463ae2  # 7402
.globl _th10_00463ae0
_th10_00463ae0:
    {load} xor esi, esi  # 33f6
.globl _th10_00463ae2
_th10_00463ae2:
    {load} mov eax, esi  # 8bc6
.globl _th10_00463ae4
_th10_00463ae4:
    pop esi  # 5e
.globl _th10_00463ae5
_th10_00463ae5:
    ret  # c3
.globl _th10_00463ae6
_th10_00463ae6:
    push esi  # 56
.globl _th10_00463ae7
_th10_00463ae7:
    {disp8} push dword ptr [esp+0x0C]  # ff74240c
.globl _th10_00463aeb
_th10_00463aeb:
    {load} xor esi, esi  # 33f6
.globl _th10_00463aed
_th10_00463aed:
    {disp8} push dword ptr [esp+0x0C]  # ff74240c
.globl _th10_00463af1
_th10_00463af1:
    inc esi  # 46
.globl _th10_00463af2
_th10_00463af2:
    call dword ptr [_th10_00466174]  # ff1574614600
.globl _th10_00463af8
_th10_00463af8:
    test eax, eax  # 85c0
.globl _th10_00463afa
_th10_00463afa:
    {disp8} je _th10_00463afe  # 7402
.globl _th10_00463afc
_th10_00463afc:
    {load} xor esi, esi  # 33f6
.globl _th10_00463afe
_th10_00463afe:
    {load} mov eax, esi  # 8bc6
.globl _th10_00463b00
_th10_00463b00:
    pop esi  # 5e
.globl _th10_00463b01
_th10_00463b01:
    ret  # c3
.globl _th10_00463b02
_th10_00463b02:
    push esi  # 56
.globl _th10_00463b03
_th10_00463b03:
    {disp8} push dword ptr [esp+8]  # ff742408
.globl _th10_00463b07
_th10_00463b07:
    {load} xor esi, esi  # 33f6
.globl _th10_00463b09
_th10_00463b09:
    inc esi  # 46
.globl _th10_00463b0a
_th10_00463b0a:
    call dword ptr [_th10_00466184]  # ff1584614600
.globl _th10_00463b10
_th10_00463b10:
    test eax, eax  # 85c0
.globl _th10_00463b12
_th10_00463b12:
    {disp8} je _th10_00463b16  # 7402
.globl _th10_00463b14
_th10_00463b14:
    {load} xor esi, esi  # 33f6
.globl _th10_00463b16
_th10_00463b16:
    {load} mov eax, esi  # 8bc6
.globl _th10_00463b18
_th10_00463b18:
    pop esi  # 5e
.globl _th10_00463b19
_th10_00463b19:
    ret  # c3
.globl _th10_00463b1a
_th10_00463b1a:
    jmp dword ptr [_th10_004661d4]  # ff25d4614600
.globl _th10_00463b20
_th10_00463b20:
    jmp dword ptr [_th10_004661d8]  # ff25d8614600
.globl _th10_00463b26
_th10_00463b26:
    jmp dword ptr [_th10_00466184]  # ff2584614600
.globl _th10_00463b2c
_th10_00463b2c:
    push ebp  # 55
.globl _th10_00463b2d
_th10_00463b2d:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463b2f
_th10_00463b2f:
    sub esp, 32  # 83ec20
.globl _th10_00463b32
_th10_00463b32:
    and esp, -16  # 83e4f0
.globl _th10_00463b35
_th10_00463b35:
    fld st(0)  # d9c0
.globl _th10_00463b37
_th10_00463b37:
    {disp8} fst dword ptr [esp+0x18]  # d9542418
.globl _th10_00463b3b
_th10_00463b3b:
    {disp8} fistp qword ptr [esp+0x10]  # df7c2410
.globl _th10_00463b3f
_th10_00463b3f:
    {disp8} fild qword ptr [esp+0x10]  # df6c2410
.globl _th10_00463b43
_th10_00463b43:
    {disp8} {load} mov edx, [esp+0x18]  # 8b542418
.globl _th10_00463b47
_th10_00463b47:
    {disp8} {load} mov eax, [esp+0x10]  # 8b442410
.globl _th10_00463b4b
_th10_00463b4b:
    test eax, eax  # 85c0
.globl _th10_00463b4d
_th10_00463b4d:
    {disp8} je _th10_00463b8b  # 743c
.globl _th10_00463b4f
_th10_00463b4f:
    fsubp  # dee9
.globl _th10_00463b51
_th10_00463b51:
    test edx, edx  # 85d2
.globl _th10_00463b53
_th10_00463b53:
    {disp8} jns _th10_00463b73  # 791e
.globl _th10_00463b55
_th10_00463b55:
    fstp dword ptr [esp]  # d91c24
.globl _th10_00463b58
_th10_00463b58:
    {load} mov ecx, [esp]  # 8b0c24
.globl _th10_00463b5b
_th10_00463b5b:
    {noimm8s} xor ecx, 0x80000000  # 81f100000080
.globl _th10_00463b61
_th10_00463b61:
    {noimm8s} add ecx, 0x7FFFFFFF  # 81c1ffffff7f
.globl _th10_00463b67
_th10_00463b67:
    adc eax, 0  # 83d000
.globl _th10_00463b6a
_th10_00463b6a:
    {disp8} {load} mov edx, [esp+0x14]  # 8b542414
.globl _th10_00463b6e
_th10_00463b6e:
    adc edx, 0  # 83d200
.globl _th10_00463b71
_th10_00463b71:
    {disp8} jmp _th10_00463b9f  # eb2c
.globl _th10_00463b73
_th10_00463b73:
    fstp dword ptr [esp]  # d91c24
.globl _th10_00463b76
_th10_00463b76:
    {load} mov ecx, [esp]  # 8b0c24
.globl _th10_00463b79
_th10_00463b79:
    {noimm8s} add ecx, 0x7FFFFFFF  # 81c1ffffff7f
.globl _th10_00463b7f
_th10_00463b7f:
    sbb eax, 0  # 83d800
.globl _th10_00463b82
_th10_00463b82:
    {disp8} {load} mov edx, [esp+0x14]  # 8b542414
.globl _th10_00463b86
_th10_00463b86:
    sbb edx, 0  # 83da00
.globl _th10_00463b89
_th10_00463b89:
    {disp8} jmp _th10_00463b9f  # eb14
.globl _th10_00463b8b
_th10_00463b8b:
    {disp8} {load} mov edx, [esp+0x14]  # 8b542414
.globl _th10_00463b8f
_th10_00463b8f:
    {noimm8s} test edx, 0x7FFFFFFF  # f7c2ffffff7f
.globl _th10_00463b95
_th10_00463b95:
    {disp8} jne _th10_00463b4f  # 75b8
.globl _th10_00463b97
_th10_00463b97:
    {disp8} fstp dword ptr [esp+0x18]  # d95c2418
.globl _th10_00463b9b
_th10_00463b9b:
    {disp8} fstp dword ptr [esp+0x18]  # d95c2418
.globl _th10_00463b9f
_th10_00463b9f:
    leave  # c9
.globl _th10_00463ba0
_th10_00463ba0:
    ret  # c3
# padding 00463ba1..00463baf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 15, 1, 0xcc
.globl _th10_00463bb0
_th10_00463bb0:
    {noimm8s} mov edx, 0x477010  # ba10704700
.globl _th10_00463bb5
_th10_00463bb5:
    {disp32} jmp _th10_00463d3b  # e981010000
.globl _th10_00463bba
_th10_00463bba:
    {noimm8s} mov edx, 0x477010  # ba10704700
.globl _th10_00463bbf
_th10_00463bbf:
    {disp32} jmp _th10_00463cc0  # e9fc000000
.globl _th10_00463bc4
_th10_00463bc4:
    fxch  # d9c9
.globl _th10_00463bc6
_th10_00463bc6:
    cmp dword ptr [_th10_00477388], 1  # 833d8873470001
.globl _th10_00463bcd
_th10_00463bcd:
    {disp8} je _th10_00463bd3  # 7404
.globl _th10_00463bcf
_th10_00463bcf:
    fprem  # d9f8
.globl _th10_00463bd1
_th10_00463bd1:
    {disp8} jmp _th10_00463bd8  # eb05
.globl _th10_00463bd3
_th10_00463bd3:
    {disp32} call _th10_00464b1c  # e8440f0000
.globl _th10_00463bd8
_th10_00463bd8:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00463bdb
_th10_00463bdb:
    fwait  # 9b
.globl _th10_00463bdc
_th10_00463bdc:
    sahf  # 9e
.globl _th10_00463bdd
_th10_00463bdd:
    {disp8} jp _th10_00463bc6  # 7ae7
.globl _th10_00463bdf
_th10_00463bdf:
    fstp st(1)  # ddd9
.globl _th10_00463be1
_th10_00463be1:
    ret  # c3
# padding 00463be2..00463bef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 14, 1, 0xcc
.globl _th10_00463bf0
_th10_00463bf0:
    sub esp, 12  # 83ec0c
.globl _th10_00463bf3
_th10_00463bf3:
    fst qword ptr [esp]  # dd1424
.globl _th10_00463bf6
_th10_00463bf6:
    {disp32} call _th10_00464f88  # e88d130000
.globl _th10_00463bfb
_th10_00463bfb:
    {disp32} call _th10_00463c0d  # e80d000000
.globl _th10_00463c00
_th10_00463c00:
    add esp, 12  # 83c40c
.globl _th10_00463c03
_th10_00463c03:
    ret  # c3
.globl _th10_00463c04
_th10_00463c04:
    {disp8} lea edx, [esp+4]  # 8d542404
.globl _th10_00463c08
_th10_00463c08:
    {disp32} call _th10_00464f45  # e838130000
.globl _th10_00463c0d
_th10_00463c0d:
    push edx  # 52
.globl _th10_00463c0e
_th10_00463c0e:
    fwait
fnstcw [esp]  # 9bd93c24
.globl _th10_00463c12
_th10_00463c12:
    {disp8} je _th10_00463c81  # 746d
.globl _th10_00463c14
_th10_00463c14:
    {noimm8s} cmp word ptr [esp], 0x27F  # 66813c247f02
.globl _th10_00463c1a
_th10_00463c1a:
    {disp8} je _th10_00463c21  # 7405
.globl _th10_00463c1c
_th10_00463c1c:
    {disp32} call _th10_00464f15  # e8f4120000
.globl _th10_00463c21
_th10_00463c21:
    {noimm8s} cmp eax, 0x3FF00000  # 3d0000f03f
.globl _th10_00463c26
_th10_00463c26:
    {disp8} jae _th10_00463c55  # 732d
.globl _th10_00463c28
_th10_00463c28:
    fld1  # d9e8
.globl _th10_00463c2a
_th10_00463c2a:
    fadd st(1)  # d8c1
.globl _th10_00463c2c
_th10_00463c2c:
    fld1  # d9e8
.globl _th10_00463c2e
_th10_00463c2e:
    fsub st(2)  # d8e2
.globl _th10_00463c30
_th10_00463c30:
    fmulp  # dec9
.globl _th10_00463c32
_th10_00463c32:
    fsqrt  # d9fa
.globl _th10_00463c34
_th10_00463c34:
    fxch  # d9c9
.globl _th10_00463c36
_th10_00463c36:
    fpatan  # d9f3
.globl _th10_00463c38
_th10_00463c38:
    cmp dword ptr [_th10_00477384], 0  # 833d8473470000
.globl _th10_00463c3f
_th10_00463c3f:
    {disp32} jne _th10_00464f9e  # 0f8559130000
.globl _th10_00463c45
_th10_00463c45:
    {noimm8s} mov edx, 0x0D  # ba0d000000
.globl _th10_00463c4a
_th10_00463c4a:
    lea ecx, [_th10_00477060]  # 8d0d60704700
.globl _th10_00463c50
_th10_00463c50:
    {disp32} jmp _th10_00464fab  # e956130000
.globl _th10_00463c55
_th10_00463c55:
    {disp8} ja _th10_00463c8f  # 7738
.globl _th10_00463c57
_th10_00463c57:
    {disp8} {load} mov eax, [esp+0x0C]  # 8b44240c
.globl _th10_00463c5b
_th10_00463c5b:
    {load} mov ecx, eax  # 8bc8
.globl _th10_00463c5d
_th10_00463c5d:
    {noimm8s} and eax, 0x0FFFFF  # 25ffff0f00
.globl _th10_00463c62
_th10_00463c62:
    {disp8} {load} or eax, [esp+8]  # 0b442408
.globl _th10_00463c66
_th10_00463c66:
    {disp8} jne _th10_00463c8f  # 7527
.globl _th10_00463c68
_th10_00463c68:
    {noimm8s} and ecx, 0x80000000  # 81e100000080
.globl _th10_00463c6e
_th10_00463c6e:
    fstp st(0)  # ddd8
.globl _th10_00463c70
_th10_00463c70:
    {disp8} je _th10_00463c76  # 7404
.globl _th10_00463c72
_th10_00463c72:
    fldpi  # d9eb
.globl _th10_00463c74
_th10_00463c74:
    {disp8} jmp _th10_00463c38  # ebc2
.globl _th10_00463c76
_th10_00463c76:
    fldz  # d9ee
.globl _th10_00463c78
_th10_00463c78:
    {disp8} jmp _th10_00463c38  # ebbe
.globl _th10_00463c7a
_th10_00463c7a:
    {disp32} call _th10_00464f2c  # e8ad120000
.globl _th10_00463c7f
_th10_00463c7f:
    {disp8} jmp _th10_00463c9c  # eb1b
.globl _th10_00463c81
_th10_00463c81:
    {noimm8s} test eax, 0x0FFFFF  # a9ffff0f00
.globl _th10_00463c86
_th10_00463c86:
    {disp8} jne _th10_00463c7a  # 75f2
.globl _th10_00463c88
_th10_00463c88:
    {disp8} cmp dword ptr [esp+8], 0  # 837c240800
.globl _th10_00463c8d
_th10_00463c8d:
    {disp8} jne _th10_00463c7a  # 75eb
.globl _th10_00463c8f
_th10_00463c8f:
    fstp st(0)  # ddd8
.globl _th10_00463c91
_th10_00463c91:
    fld tbyte ptr [_th10_00477070]  # db2d70704700
.globl _th10_00463c97
_th10_00463c97:
    {noimm8s} mov eax, 1  # b801000000
.globl _th10_00463c9c
_th10_00463c9c:
    cmp dword ptr [_th10_00477384], 0  # 833d8473470000
.globl _th10_00463ca3
_th10_00463ca3:
    {disp32} jne _th10_00464f9e  # 0f85f5120000
.globl _th10_00463ca9
_th10_00463ca9:
    {noimm8s} mov edx, 0x0D  # ba0d000000
.globl _th10_00463cae
_th10_00463cae:
    lea ecx, [_th10_00477060]  # 8d0d60704700
.globl _th10_00463cb4
_th10_00463cb4:
    {disp32} call _th10_00464eb7  # e8fe110000
.globl _th10_00463cb9
_th10_00463cb9:
    pop edx  # 5a
.globl _th10_00463cba
_th10_00463cba:
    ret  # c3
# padding 00463cbb..00463cbf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 5, 1, 0xcc
.globl _th10_00463cc0
_th10_00463cc0:
    push ebp  # 55
.globl _th10_00463cc1
_th10_00463cc1:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463cc3
_th10_00463cc3:
    {noimm8s} add esp, 0x0FFFFFD30  # 81c430fdffff
.globl _th10_00463cc9
_th10_00463cc9:
    push ebx  # 53
.globl _th10_00463cca
_th10_00463cca:
    fwait
fnstcw [ebp-0x0A4]  # 9bd9bd5cffffff
.globl _th10_00463cd1
_th10_00463cd1:
    fwait  # 9b
.globl _th10_00463cd2
_th10_00463cd2:
    cmp dword ptr [_th10_00473c90], 0  # 833d903c470000
.globl _th10_00463cd9
_th10_00463cd9:
    {disp8} je _th10_00463cef  # 7414
.globl _th10_00463cdb
_th10_00463cdb:
    {disp32} call _th10_00463fa7  # e8c7020000
.globl _th10_00463ce0
_th10_00463ce0:
    or byte ptr [ebp-0x2C8], 3  # 808d38fdffff03
.globl _th10_00463ce7
_th10_00463ce7:
    {disp32} call _th10_00463d8a  # e89e000000
.globl _th10_00463cec
_th10_00463cec:
    pop ebx  # 5b
.globl _th10_00463ced
_th10_00463ced:
    leave  # c9
.globl _th10_00463cee
_th10_00463cee:
    ret  # c3
.globl _th10_00463cef
_th10_00463cef:
    fxch  # d9c9
.globl _th10_00463cf1
_th10_00463cf1:
    fst qword ptr [ebp-0x86]  # dd957affffff
.globl _th10_00463cf7
_th10_00463cf7:
    fxch  # d9c9
.globl _th10_00463cf9
_th10_00463cf9:
    {disp8} fst qword ptr [ebp-0x7E]  # dd5582
.globl _th10_00463cfc
_th10_00463cfc:
    {disp8} jmp _th10_00463cdb  # ebdd
.globl _th10_00463cfe
_th10_00463cfe:
    push ebp  # 55
.globl _th10_00463cff
_th10_00463cff:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463d01
_th10_00463d01:
    {noimm8s} add esp, 0x0FFFFFD30  # 81c430fdffff
.globl _th10_00463d07
_th10_00463d07:
    push ebx  # 53
.globl _th10_00463d08
_th10_00463d08:
    fwait
fnstcw [ebp-0x0A4]  # 9bd9bd5cffffff
.globl _th10_00463d0f
_th10_00463d0f:
    cmp dword ptr [_th10_00473c90], 0  # 833d903c470000
.globl _th10_00463d16
_th10_00463d16:
    {disp8} je _th10_00463d33  # 741b
.globl _th10_00463d18
_th10_00463d18:
    {disp32} call _th10_00463f40  # e823020000
.globl _th10_00463d1d
_th10_00463d1d:
    or byte ptr [ebp-0x2C8], 1  # 808d38fdffff01
.globl _th10_00463d24
_th10_00463d24:
    and byte ptr [ebp-0x2C8], 0x0FD  # 80a538fdfffffd
.globl _th10_00463d2b
_th10_00463d2b:
    {disp32} call _th10_00463d8a  # e85a000000
.globl _th10_00463d30
_th10_00463d30:
    pop ebx  # 5b
.globl _th10_00463d31
_th10_00463d31:
    leave  # c9
.globl _th10_00463d32
_th10_00463d32:
    ret  # c3
.globl _th10_00463d33
_th10_00463d33:
    fst qword ptr [ebp-0x86]  # dd957affffff
.globl _th10_00463d39
_th10_00463d39:
    {disp8} jmp _th10_00463d18  # ebdd
.globl _th10_00463d3b
_th10_00463d3b:
    push ebp  # 55
.globl _th10_00463d3c
_th10_00463d3c:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463d3e
_th10_00463d3e:
    {noimm8s} add esp, 0x0FFFFFD30  # 81c430fdffff
.globl _th10_00463d44
_th10_00463d44:
    push ebx  # 53
.globl _th10_00463d45
_th10_00463d45:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00463d48
_th10_00463d48:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00463d4b
_th10_00463d4b:
    {disp32} call _th10_00463f04  # e8b4010000
.globl _th10_00463d50
_th10_00463d50:
    add esp, 8  # 83c408
.globl _th10_00463d53
_th10_00463d53:
    {disp8} push dword ptr [ebp+0x14]  # ff7514
.globl _th10_00463d56
_th10_00463d56:
    {disp8} push dword ptr [ebp+0x10]  # ff7510
.globl _th10_00463d59
_th10_00463d59:
    {disp32} call _th10_00463f04  # e8a6010000
.globl _th10_00463d5e
_th10_00463d5e:
    add esp, 8  # 83c408
.globl _th10_00463d61
_th10_00463d61:
    fwait
fnstcw [ebp-0x0A4]  # 9bd9bd5cffffff
.globl _th10_00463d68
_th10_00463d68:
    or byte ptr [ebp-0x2C8], 2  # 808d38fdffff02
.globl _th10_00463d6f
_th10_00463d6f:
    mov byte ptr [ebp-0x8F], 1  # c68571ffffff01
.globl _th10_00463d76
_th10_00463d76:
    {disp32} call _th10_00463fa7  # e82c020000
.globl _th10_00463d7b
_th10_00463d7b:
    {disp32} call _th10_00463d83  # e803000000
.globl _th10_00463d80
_th10_00463d80:
    pop ebx  # 5b
.globl _th10_00463d81
_th10_00463d81:
    leave  # c9
.globl _th10_00463d82
_th10_00463d82:
    ret  # c3
.globl _th10_00463d83
_th10_00463d83:
    and byte ptr [ebp-0x2C8], 0x0FE  # 80a538fdfffffe
.globl _th10_00463d8a
_th10_00463d8a:
    cmp dword ptr [_th10_00477384], 0  # 833d8473470000
.globl _th10_00463d91
_th10_00463d91:
    {disp8} jne _th10_00463de2  # 754f
.globl _th10_00463d93
_th10_00463d93:
    fst qword ptr [ebp-0x2D0]  # dd9530fdffff
.globl _th10_00463d99
_th10_00463d99:
    {load} mov al, [ebp-0x90]  # 8a8570ffffff
.globl _th10_00463d9f
_th10_00463d9f:
    {load} or al, al  # 0ac0
.globl _th10_00463da1
_th10_00463da1:
    {disp8} je _th10_00463dbd  # 741a
.globl _th10_00463da3
_th10_00463da3:
    cmp al, 0x0FF  # 3cff
.globl _th10_00463da5
_th10_00463da5:
    {disp8} je _th10_00463e02  # 745b
.globl _th10_00463da7
_th10_00463da7:
    cmp al, 0x0FE  # 3cfe
.globl _th10_00463da9
_th10_00463da9:
    {disp8} je _th10_00463dea  # 743f
.globl _th10_00463dab
_th10_00463dab:
    {load} or al, al  # 0ac0
.globl _th10_00463dad
_th10_00463dad:
    {disp8} je _th10_00463de2  # 7433
.globl _th10_00463daf
_th10_00463daf:
    movsx eax, al  # 0fbec0
.globl _th10_00463db2
_th10_00463db2:
    {store} mov [ebp-0x8E], eax  # 898572ffffff
.globl _th10_00463db8
_th10_00463db8:
    {disp32} jmp _th10_00463e6f  # e9b2000000
.globl _th10_00463dbd
_th10_00463dbd:
    {load} mov ax, [ebp-0x0A4]  # 668b855cffffff
.globl _th10_00463dc4
_th10_00463dc4:
    and ax, 32  # 6683e020
.globl _th10_00463dc8
_th10_00463dc8:
    {disp8} jne _th10_00463de2  # 7518
.globl _th10_00463dca
_th10_00463dca:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00463dcd
_th10_00463dcd:
    and ax, 32  # 6683e020
.globl _th10_00463dd1
_th10_00463dd1:
    {disp8} je _th10_00463de2  # 740f
.globl _th10_00463dd3
_th10_00463dd3:
    {noimm8s} mov dword ptr [ebp-0x8E], 8  # c78572ffffff08000000
.globl _th10_00463ddd
_th10_00463ddd:
    {disp32} jmp _th10_00463e6f  # e98d000000
.globl _th10_00463de2
_th10_00463de2:
    fldcw [ebp-0x0A4]  # d9ad5cffffff
.globl _th10_00463de8
_th10_00463de8:
    fwait  # 9b
.globl _th10_00463de9
_th10_00463de9:
    ret  # c3
.globl _th10_00463dea
_th10_00463dea:
    {load} mov ax, [ebp-0x2CA]  # 668b8536fdffff
.globl _th10_00463df1
_th10_00463df1:
    {noimm8s} and ax, 0x7FF0  # 6625f07f
.globl _th10_00463df5
_th10_00463df5:
    {load} or ax, ax  # 660bc0
.globl _th10_00463df8
_th10_00463df8:
    {disp8} je _th10_00463e15  # 741b
.globl _th10_00463dfa
_th10_00463dfa:
    {noimm8s} cmp ax, 0x7FF0  # 663df07f
.globl _th10_00463dfe
_th10_00463dfe:
    {disp8} je _th10_00463e43  # 7443
.globl _th10_00463e00
_th10_00463e00:
    {disp8} jmp _th10_00463dbd  # ebbb
.globl _th10_00463e02
_th10_00463e02:
    {load} mov ax, [ebp-0x2CA]  # 668b8536fdffff
.globl _th10_00463e09
_th10_00463e09:
    {noimm8s} and ax, 0x7FF0  # 6625f07f
.globl _th10_00463e0d
_th10_00463e0d:
    {noimm8s} cmp ax, 0x7FF0  # 663df07f
.globl _th10_00463e11
_th10_00463e11:
    {disp8} je _th10_00463e43  # 7430
.globl _th10_00463e13
_th10_00463e13:
    {disp8} jmp _th10_00463dbd  # eba8
.globl _th10_00463e15
_th10_00463e15:
    {noimm8s} mov dword ptr [ebp-0x8E], 4  # c78572ffffff04000000
.globl _th10_00463e1f
_th10_00463e1f:
    fld qword ptr [_th10_00470d78]  # dd05780d4700
.globl _th10_00463e25
_th10_00463e25:
    fxch  # d9c9
.globl _th10_00463e27
_th10_00463e27:
    fscale  # d9fd
.globl _th10_00463e29
_th10_00463e29:
    fstp st(1)  # ddd9
.globl _th10_00463e2b
_th10_00463e2b:
    fld st(0)  # d9c0
.globl _th10_00463e2d
_th10_00463e2d:
    fabs  # d9e1
.globl _th10_00463e2f
_th10_00463e2f:
    fcomp qword ptr [_th10_00470d68]  # dc1d680d4700
.globl _th10_00463e35
_th10_00463e35:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00463e38
_th10_00463e38:
    sahf  # 9e
.globl _th10_00463e39
_th10_00463e39:
    {disp8} jae _th10_00463e6f  # 7334
.globl _th10_00463e3b
_th10_00463e3b:
    fmul qword ptr [_th10_00470d88]  # dc0d880d4700
.globl _th10_00463e41
_th10_00463e41:
    {disp8} jmp _th10_00463e6f  # eb2c
.globl _th10_00463e43
_th10_00463e43:
    {noimm8s} mov dword ptr [ebp-0x8E], 3  # c78572ffffff03000000
.globl _th10_00463e4d
_th10_00463e4d:
    fld qword ptr [_th10_00470d70]  # dd05700d4700
.globl _th10_00463e53
_th10_00463e53:
    fxch  # d9c9
.globl _th10_00463e55
_th10_00463e55:
    fscale  # d9fd
.globl _th10_00463e57
_th10_00463e57:
    fstp st(1)  # ddd9
.globl _th10_00463e59
_th10_00463e59:
    fld st(0)  # d9c0
.globl _th10_00463e5b
_th10_00463e5b:
    fabs  # d9e1
.globl _th10_00463e5d
_th10_00463e5d:
    fcomp qword ptr [_th10_00470d60]  # dc1d600d4700
.globl _th10_00463e63
_th10_00463e63:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00463e66
_th10_00463e66:
    sahf  # 9e
.globl _th10_00463e67
_th10_00463e67:
    {disp8} jbe _th10_00463e6f  # 7606
.globl _th10_00463e69
_th10_00463e69:
    fmul qword ptr [_th10_00470d80]  # dc0d800d4700
.globl _th10_00463e6f
_th10_00463e6f:
    push esi  # 56
.globl _th10_00463e70
_th10_00463e70:
    push edi  # 57
.globl _th10_00463e71
_th10_00463e71:
    {load} mov ebx, [ebp-0x94]  # 8b9d6cffffff
.globl _th10_00463e77
_th10_00463e77:
    inc ebx  # 43
.globl _th10_00463e78
_th10_00463e78:
    {store} mov [ebp-0x8A], ebx  # 899d76ffffff
.globl _th10_00463e7e
_th10_00463e7e:
    test byte ptr [ebp-0x2C8], 1  # f68538fdffff01
.globl _th10_00463e85
_th10_00463e85:
    {disp8} jne _th10_00463ea1  # 751a
.globl _th10_00463e87
_th10_00463e87:
    cld  # fc
.globl _th10_00463e88
_th10_00463e88:
    {disp8} lea esi, [ebp+8]  # 8d7508
.globl _th10_00463e8b
_th10_00463e8b:
    lea edi, [ebp-0x86]  # 8dbd7affffff
.globl _th10_00463e91
_th10_00463e91:
    movsd  # a5
.globl _th10_00463e92
_th10_00463e92:
    movsd  # a5
.globl _th10_00463e93
_th10_00463e93:
    {disp8} cmp byte ptr [ebx+0x0C], 1  # 807b0c01
.globl _th10_00463e97
_th10_00463e97:
    {disp8} je _th10_00463ea1  # 7408
.globl _th10_00463e99
_th10_00463e99:
    {disp8} lea esi, [ebp+0x10]  # 8d7510
.globl _th10_00463e9c
_th10_00463e9c:
    {disp8} lea edi, [ebp-0x7E]  # 8d7d82
.globl _th10_00463e9f
_th10_00463e9f:
    movsd  # a5
.globl _th10_00463ea0
_th10_00463ea0:
    movsd  # a5
.globl _th10_00463ea1
_th10_00463ea1:
    {disp8} fstp qword ptr [ebp-0x76]  # dd5d8a
.globl _th10_00463ea4
_th10_00463ea4:
    lea eax, [ebp-0x8E]  # 8d8572ffffff
.globl _th10_00463eaa
_th10_00463eaa:
    lea ebx, [ebp-0x0A4]  # 8d9d5cffffff
.globl _th10_00463eb0
_th10_00463eb0:
    push ebx  # 53
.globl _th10_00463eb1
_th10_00463eb1:
    push eax  # 50
.globl _th10_00463eb2
_th10_00463eb2:
    {load} mov ebx, [ebp-0x94]  # 8b9d6cffffff
.globl _th10_00463eb8
_th10_00463eb8:
    {disp8} {load} mov al, [ebx+0x0E]  # 8a430e
.globl _th10_00463ebb
_th10_00463ebb:
    movsx eax, al  # 0fbec0
.globl _th10_00463ebe
_th10_00463ebe:
    push eax  # 50
.globl _th10_00463ebf
_th10_00463ebf:
    {disp32} call _th10_0046508c  # e8c8110000
.globl _th10_00463ec4
_th10_00463ec4:
    add esp, 12  # 83c40c
.globl _th10_00463ec7
_th10_00463ec7:
    pop edi  # 5f
.globl _th10_00463ec8
_th10_00463ec8:
    pop esi  # 5e
.globl _th10_00463ec9
_th10_00463ec9:
    {disp8} fld qword ptr [ebp-0x76]  # dd458a
.globl _th10_00463ecc
_th10_00463ecc:
    {disp32} jmp _th10_00463de2  # e911ffffff
.globl _th10_00463ed1
_th10_00463ed1:
    push ebp  # 55
.globl _th10_00463ed2
_th10_00463ed2:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463ed4
_th10_00463ed4:
    {noimm8s} add esp, 0x0FFFFFD30  # 81c430fdffff
.globl _th10_00463eda
_th10_00463eda:
    push ebx  # 53
.globl _th10_00463edb
_th10_00463edb:
    {disp8} push dword ptr [ebp+0x0C]  # ff750c
.globl _th10_00463ede
_th10_00463ede:
    {disp8} push dword ptr [ebp+8]  # ff7508
.globl _th10_00463ee1
_th10_00463ee1:
    {disp32} call _th10_00463f04  # e81e000000
.globl _th10_00463ee6
_th10_00463ee6:
    add esp, 8  # 83c408
.globl _th10_00463ee9
_th10_00463ee9:
    fwait
fnstcw [ebp-0x0A4]  # 9bd9bd5cffffff
.globl _th10_00463ef0
_th10_00463ef0:
    and byte ptr [ebp-0x2C8], 0x0FD  # 80a538fdfffffd
.globl _th10_00463ef7
_th10_00463ef7:
    {disp32} call _th10_00463f40  # e844000000
.globl _th10_00463efc
_th10_00463efc:
    {disp32} call _th10_00463d83  # e882feffff
.globl _th10_00463f01
_th10_00463f01:
    pop ebx  # 5b
.globl _th10_00463f02
_th10_00463f02:
    leave  # c9
.globl _th10_00463f03
_th10_00463f03:
    ret  # c3
.globl _th10_00463f04
_th10_00463f04:
    push ebp  # 55
.globl _th10_00463f05
_th10_00463f05:
    {load} mov ebp, esp  # 8bec
.globl _th10_00463f07
_th10_00463f07:
    add esp, -12  # 83c4f4
.globl _th10_00463f0a
_th10_00463f0a:
    push ebx  # 53
.globl _th10_00463f0b
_th10_00463f0b:
    {disp8} {load} mov ax, [ebp+0x0E]  # 668b450e
.globl _th10_00463f0f
_th10_00463f0f:
    {load} mov bx, ax  # 668bd8
.globl _th10_00463f12
_th10_00463f12:
    {noimm8s} and ax, 0x7FF0  # 6625f07f
.globl _th10_00463f16
_th10_00463f16:
    {noimm8s} cmp ax, 0x7FF0  # 663df07f
.globl _th10_00463f1a
_th10_00463f1a:
    {disp8} jne _th10_00463f3a  # 751e
.globl _th10_00463f1c
_th10_00463f1c:
    {noimm8s} or bx, 0x7FFF  # 6681cbff7f
.globl _th10_00463f21
_th10_00463f21:
    {disp8} {store} mov [ebp-2], bx  # 66895dfe
.globl _th10_00463f25
_th10_00463f25:
    {disp8} {load} mov eax, [ebp+0x0C]  # 8b450c
.globl _th10_00463f28
_th10_00463f28:
    {disp8} {load} mov ebx, [ebp+8]  # 8b5d08
.globl _th10_00463f2b
_th10_00463f2b:
    shld eax, ebx, 0x0B  # 0fa4d80b
.globl _th10_00463f2f
_th10_00463f2f:
    {disp8} {store} mov [ebp-6], eax  # 8945fa
.globl _th10_00463f32
_th10_00463f32:
    {disp8} {store} mov [ebp-0x0A], ebx  # 895df6
.globl _th10_00463f35
_th10_00463f35:
    {disp8} fld tbyte ptr [ebp-0x0A]  # db6df6
.globl _th10_00463f38
_th10_00463f38:
    {disp8} jmp _th10_00463f3d  # eb03
.globl _th10_00463f3a
_th10_00463f3a:
    {disp8} fld qword ptr [ebp+8]  # dd4508
.globl _th10_00463f3d
_th10_00463f3d:
    pop ebx  # 5b
.globl _th10_00463f3e
_th10_00463f3e:
    leave  # c9
.globl _th10_00463f3f
_th10_00463f3f:
    ret  # c3
.globl _th10_00463f40
_th10_00463f40:
    {disp8} cmp byte ptr [edx+0x0E], 5  # 807a0e05
.globl _th10_00463f44
_th10_00463f44:
    {disp8} jne _th10_00463f57  # 7511
.globl _th10_00463f46
_th10_00463f46:
    {load} mov bx, [ebp-0x0A4]  # 668b9d5cffffff
.globl _th10_00463f4d
_th10_00463f4d:
    or bh, 2  # 80cf02
.globl _th10_00463f50
_th10_00463f50:
    and bh, 0x0FE  # 80e7fe
.globl _th10_00463f53
_th10_00463f53:
    mov bl, 0x3F  # b33f
.globl _th10_00463f55
_th10_00463f55:
    {disp8} jmp _th10_00463f5b  # eb04
.globl _th10_00463f57
_th10_00463f57:
    {noimm8s} mov bx, 0x133F  # 66bb3f13
.globl _th10_00463f5b
_th10_00463f5b:
    {store} mov [ebp-0x0A2], bx  # 66899d5effffff
.globl _th10_00463f62
_th10_00463f62:
    fldcw [ebp-0x0A2]  # d9ad5effffff
.globl _th10_00463f68
_th10_00463f68:
    {noimm8s} mov ebx, 0x47708C  # bb8c704700
.globl _th10_00463f6d
_th10_00463f6d:
    fxam  # d9e5
.globl _th10_00463f6f
_th10_00463f6f:
    {store} mov [ebp-0x94], edx  # 89956cffffff
.globl _th10_00463f75
_th10_00463f75:
    fwait
fnstsw [ebp-0x0A0]  # 9bddbd60ffffff
.globl _th10_00463f7c
_th10_00463f7c:
    mov byte ptr [ebp-0x90], 0  # c68570ffffff00
.globl _th10_00463f83
_th10_00463f83:
    fwait  # 9b
.globl _th10_00463f84
_th10_00463f84:
    {load} mov cl, [ebp-0x9F]  # 8a8d61ffffff
.globl _th10_00463f8a
_th10_00463f8a:
    shl cl, 1  # d0e1
.globl _th10_00463f8c
_th10_00463f8c:
    sar cl, 1  # d0f9
.globl _th10_00463f8e
_th10_00463f8e:
    rol cl, 1  # d0c1
.globl _th10_00463f90
_th10_00463f90:
    {load} mov al, cl  # 8ac1
.globl _th10_00463f92
_th10_00463f92:
    and al, 0x0F  # 240f
.globl _th10_00463f94
_th10_00463f94:
    xlat [ebx]  # d7
.globl _th10_00463f95
_th10_00463f95:
    movsx eax, al  # 0fbec0
.globl _th10_00463f98
_th10_00463f98:
    {noimm8s} and ecx, 0x404  # 81e104040000
.globl _th10_00463f9e
_th10_00463f9e:
    {load} mov ebx, edx  # 8bda
.globl _th10_00463fa0
_th10_00463fa0:
    {load} add ebx, eax  # 03d8
.globl _th10_00463fa2
_th10_00463fa2:
    add ebx, 16  # 83c310
.globl _th10_00463fa5
_th10_00463fa5:
    jmp dword ptr [ebx]  # ff23
.globl _th10_00463fa7
_th10_00463fa7:
    {disp8} cmp byte ptr [edx+0x0E], 5  # 807a0e05
.globl _th10_00463fab
_th10_00463fab:
    {disp8} jne _th10_00463fbe  # 7511
.globl _th10_00463fad
_th10_00463fad:
    {load} mov bx, [ebp-0x0A4]  # 668b9d5cffffff
.globl _th10_00463fb4
_th10_00463fb4:
    or bh, 2  # 80cf02
.globl _th10_00463fb7
_th10_00463fb7:
    and bh, 0x0FE  # 80e7fe
.globl _th10_00463fba
_th10_00463fba:
    mov bl, 0x3F  # b33f
.globl _th10_00463fbc
_th10_00463fbc:
    {disp8} jmp _th10_00463fc2  # eb04
.globl _th10_00463fbe
_th10_00463fbe:
    {noimm8s} mov bx, 0x133F  # 66bb3f13
.globl _th10_00463fc2
_th10_00463fc2:
    {store} mov [ebp-0x0A2], bx  # 66899d5effffff
.globl _th10_00463fc9
_th10_00463fc9:
    fldcw [ebp-0x0A2]  # d9ad5effffff
.globl _th10_00463fcf
_th10_00463fcf:
    {noimm8s} mov ebx, 0x47708C  # bb8c704700
.globl _th10_00463fd4
_th10_00463fd4:
    fxam  # d9e5
.globl _th10_00463fd6
_th10_00463fd6:
    {store} mov [ebp-0x94], edx  # 89956cffffff
.globl _th10_00463fdc
_th10_00463fdc:
    fwait
fnstsw [ebp-0x0A0]  # 9bddbd60ffffff
.globl _th10_00463fe3
_th10_00463fe3:
    mov byte ptr [ebp-0x90], 0  # c68570ffffff00
.globl _th10_00463fea
_th10_00463fea:
    fxch  # d9c9
.globl _th10_00463fec
_th10_00463fec:
    {load} mov cl, [ebp-0x9F]  # 8a8d61ffffff
.globl _th10_00463ff2
_th10_00463ff2:
    fxam  # d9e5
.globl _th10_00463ff4
_th10_00463ff4:
    fwait
fnstsw [ebp-0x0A0]  # 9bddbd60ffffff
.globl _th10_00463ffb
_th10_00463ffb:
    fxch  # d9c9
.globl _th10_00463ffd
_th10_00463ffd:
    {load} mov ch, [ebp-0x9F]  # 8aad61ffffff
.globl _th10_00464003
_th10_00464003:
    shl ch, 1  # d0e5
.globl _th10_00464005
_th10_00464005:
    sar ch, 1  # d0fd
.globl _th10_00464007
_th10_00464007:
    rol ch, 1  # d0c5
.globl _th10_00464009
_th10_00464009:
    {load} mov al, ch  # 8ac5
.globl _th10_0046400b
_th10_0046400b:
    and al, 0x0F  # 240f
.globl _th10_0046400d
_th10_0046400d:
    xlat [ebx]  # d7
.globl _th10_0046400e
_th10_0046400e:
    {load} mov ah, al  # 8ae0
.globl _th10_00464010
_th10_00464010:
    shl cl, 1  # d0e1
.globl _th10_00464012
_th10_00464012:
    sar cl, 1  # d0f9
.globl _th10_00464014
_th10_00464014:
    rol cl, 1  # d0c1
.globl _th10_00464016
_th10_00464016:
    {load} mov al, cl  # 8ac1
.globl _th10_00464018
_th10_00464018:
    and al, 0x0F  # 240f
.globl _th10_0046401a
_th10_0046401a:
    xlat [ebx]  # d7
.globl _th10_0046401b
_th10_0046401b:
    shl ah, 1  # d0e4
.globl _th10_0046401d
_th10_0046401d:
    shl ah, 1  # d0e4
.globl _th10_0046401f
_th10_0046401f:
    {load} or al, ah  # 0ac4
.globl _th10_00464021
_th10_00464021:
    movsx eax, al  # 0fbec0
.globl _th10_00464024
_th10_00464024:
    {noimm8s} and ecx, 0x404  # 81e104040000
.globl _th10_0046402a
_th10_0046402a:
    {load} mov ebx, edx  # 8bda
.globl _th10_0046402c
_th10_0046402c:
    {load} add ebx, eax  # 03d8
.globl _th10_0046402e
_th10_0046402e:
    add ebx, 16  # 83c310
.globl _th10_00464031
_th10_00464031:
    jmp dword ptr [ebx]  # ff23
.globl _th10_00464033
_th10_00464033:
    {disp32} call _th10_004640f9  # e8c1000000
.globl _th10_00464038
_th10_00464038:
    fxch  # d9c9
.globl _th10_0046403a
_th10_0046403a:
    fstp st(0)  # ddd8
.globl _th10_0046403c
_th10_0046403c:
    ret  # c3
.globl _th10_0046403d
_th10_0046403d:
    {disp32} call _th10_004640f9  # e8b7000000
.globl _th10_00464042
_th10_00464042:
    {disp8} jmp _th10_0046403a  # ebf6
.globl _th10_00464044
_th10_00464044:
    fstp st(0)  # ddd8
.globl _th10_00464046
_th10_00464046:
    fstp st(0)  # ddd8
.globl _th10_00464048
_th10_00464048:
    fldz  # d9ee
.globl _th10_0046404a
_th10_0046404a:
    ret  # c3
.globl _th10_0046404b
_th10_0046404b:
    fstp st(0)  # ddd8
.globl _th10_0046404d
_th10_0046404d:
    fstp st(0)  # ddd8
.globl _th10_0046404f
_th10_0046404f:
    fld1  # d9e8
.globl _th10_00464051
_th10_00464051:
    ret  # c3
.globl _th10_00464052
_th10_00464052:
    fstp tbyte ptr [ebp-0x9E]  # dbbd62ffffff
.globl _th10_00464058
_th10_00464058:
    fld tbyte ptr [ebp-0x9E]  # dbad62ffffff
.globl _th10_0046405e
_th10_0046405e:
    test byte ptr [ebp-0x97], 0x40  # f68569ffffff40
.globl _th10_00464065
_th10_00464065:
    {disp8} je _th10_0046406f  # 7408
.globl _th10_00464067
_th10_00464067:
    mov byte ptr [ebp-0x90], 7  # c68570ffffff07
.globl _th10_0046406e
_th10_0046406e:
    ret  # c3
.globl _th10_0046406f
_th10_0046406f:
    mov byte ptr [ebp-0x90], 1  # c68570ffffff01
.globl _th10_00464076
_th10_00464076:
    fadd qword ptr [_th10_00477084]  # dc0584704700
.globl _th10_0046407c
_th10_0046407c:
    ret  # c3
.globl _th10_0046407d
_th10_0046407d:
    fxch  # d9c9
.globl _th10_0046407f
_th10_0046407f:
    fstp tbyte ptr [ebp-0x9E]  # dbbd62ffffff
.globl _th10_00464085
_th10_00464085:
    fld tbyte ptr [ebp-0x9E]  # dbad62ffffff
.globl _th10_0046408b
_th10_0046408b:
    test byte ptr [ebp-0x97], 0x40  # f68569ffffff40
.globl _th10_00464092
_th10_00464092:
    {disp8} je _th10_0046409d  # 7409
.globl _th10_00464094
_th10_00464094:
    mov byte ptr [ebp-0x90], 7  # c68570ffffff07
.globl _th10_0046409b
_th10_0046409b:
    {disp8} jmp _th10_004640a4  # eb07
.globl _th10_0046409d
_th10_0046409d:
    mov byte ptr [ebp-0x90], 1  # c68570ffffff01
.globl _th10_004640a4
_th10_004640a4:
    faddp  # dec1
.globl _th10_004640a6
_th10_004640a6:
    ret  # c3
.globl _th10_004640a7
_th10_004640a7:
    fstp tbyte ptr [ebp-0x9E]  # dbbd62ffffff
.globl _th10_004640ad
_th10_004640ad:
    fld tbyte ptr [ebp-0x9E]  # dbad62ffffff
.globl _th10_004640b3
_th10_004640b3:
    test byte ptr [ebp-0x97], 0x40  # f68569ffffff40
.globl _th10_004640ba
_th10_004640ba:
    {disp8} je _th10_004640dc  # 7420
.globl _th10_004640bc
_th10_004640bc:
    fxch  # d9c9
.globl _th10_004640be
_th10_004640be:
    fstp tbyte ptr [ebp-0x9E]  # dbbd62ffffff
.globl _th10_004640c4
_th10_004640c4:
    fld tbyte ptr [ebp-0x9E]  # dbad62ffffff
.globl _th10_004640ca
_th10_004640ca:
    test byte ptr [ebp-0x97], 0x40  # f68569ffffff40
.globl _th10_004640d1
_th10_004640d1:
    {disp8} je _th10_004640dc  # 7409
.globl _th10_004640d3
_th10_004640d3:
    mov byte ptr [ebp-0x90], 7  # c68570ffffff07
.globl _th10_004640da
_th10_004640da:
    {disp8} jmp _th10_004640e3  # eb07
.globl _th10_004640dc
_th10_004640dc:
    mov byte ptr [ebp-0x90], 1  # c68570ffffff01
.globl _th10_004640e3
_th10_004640e3:
    faddp  # dec1
.globl _th10_004640e5
_th10_004640e5:
    ret  # c3
.globl _th10_004640e6
_th10_004640e6:
    fstp st(0)  # ddd8
.globl _th10_004640e8
_th10_004640e8:
    fstp st(0)  # ddd8
.globl _th10_004640ea
_th10_004640ea:
    fld tbyte ptr [_th10_00477070]  # db2d70704700
.globl _th10_004640f0
_th10_004640f0:
    cmp byte ptr [ebp-0x90], 0  # 80bd70ffffff00
.globl _th10_004640f7
_th10_004640f7:
    {disp8} jg _th10_00464100  # 7f07
.globl _th10_004640f9
_th10_004640f9:
    mov byte ptr [ebp-0x90], 1  # c68570ffffff01
.globl _th10_00464100
_th10_00464100:
    {load} or cl, cl  # 0ac9
.globl _th10_00464102
_th10_00464102:
    ret  # c3
.globl _th10_00464103
_th10_00464103:
    {load} or cl, cl  # 0ac9
.globl _th10_00464105
_th10_00464105:
    {disp8} je _th10_00464109  # 7402
.globl _th10_00464107
_th10_00464107:
    fchs  # d9e0
.globl _th10_00464109
_th10_00464109:
    ret  # c3
# padding 0046410a..0046410f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 6, 1, 0xcc
.globl _th10_00464110
_th10_00464110:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464114
_th10_00464114:
    {disp8} fld tbyte ptr [esp+4]  # db6c2404
.globl _th10_00464118
_th10_00464118:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_0046411c
_th10_0046411c:
    {load} add eax, eax  # 03c0
.globl _th10_0046411e
_th10_0046411e:
    {disp32} jae _th10_004641aa  # 0f8386000000
.globl _th10_00464124
_th10_00464124:
    {noimm8s} xor eax, 0x0E000000  # 350000000e
.globl _th10_00464129
_th10_00464129:
    {noimm8s} test eax, 0x0E000000  # a90000000e
.globl _th10_0046412e
_th10_0046412e:
    {disp8} je _th10_00464133  # 7403
.globl _th10_00464130
_th10_00464130:
    fdivp  # def9
.globl _th10_00464132
_th10_00464132:
    ret  # c3
.globl _th10_00464133
_th10_00464133:
    shr eax, 0x1C  # c1e81c
.globl _th10_00464136
_th10_00464136:
    cmp byte ptr [eax+0x4770A0], 0  # 80b8a070470000
.globl _th10_0046413d
_th10_0046413d:
    {disp8} jne _th10_00464142  # 7503
.globl _th10_0046413f
_th10_0046413f:
    fdivp  # def9
.globl _th10_00464141
_th10_00464141:
    ret  # c3
.globl _th10_00464142
_th10_00464142:
    {disp8} {load} mov eax, [esp+0x0C]  # 8b44240c
.globl _th10_00464146
_th10_00464146:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_0046414b
_th10_0046414b:
    {disp8} je _th10_004641b4  # 7467
.globl _th10_0046414d
_th10_0046414d:
    {noimm8s} cmp eax, 0x7FFF  # 3dff7f0000
.globl _th10_00464152
_th10_00464152:
    {disp8} je _th10_004641b4  # 7460
.globl _th10_00464154
_th10_00464154:
    {disp8} fnstcw [esp+0x1C]  # d97c241c
.globl _th10_00464158
_th10_00464158:
    {disp8} {load} mov eax, [esp+0x1C]  # 8b44241c
.globl _th10_0046415c
_th10_0046415c:
    {noimm8s} or eax, 0x33F  # 0d3f030000
.globl _th10_00464161
_th10_00464161:
    {noimm8s} and eax, 0x0F3FF  # 25fff30000
.globl _th10_00464166
_th10_00464166:
    {disp8} {store} mov [esp+0x20], eax  # 89442420
.globl _th10_0046416a
_th10_0046416a:
    {disp8} fldcw [esp+0x20]  # d96c2420
.globl _th10_0046416e
_th10_0046416e:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464172
_th10_00464172:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464177
_th10_00464177:
    cmp eax, 1  # 83f801
.globl _th10_0046417a
_th10_0046417a:
    {disp8} je _th10_00464193  # 7417
.globl _th10_0046417c
_th10_0046417c:
    fmul dword ptr [_th10_004770b0]  # d80db0704700
.globl _th10_00464182
_th10_00464182:
    fxch  # d9c9
.globl _th10_00464184
_th10_00464184:
    fmul dword ptr [_th10_004770b0]  # d80db0704700
.globl _th10_0046418a
_th10_0046418a:
    fxch  # d9c9
.globl _th10_0046418c
_th10_0046418c:
    {disp8} fldcw [esp+0x1C]  # d96c241c
.globl _th10_00464190
_th10_00464190:
    fdivp  # def9
.globl _th10_00464192
_th10_00464192:
    ret  # c3
.globl _th10_00464193
_th10_00464193:
    fmul dword ptr [_th10_004770b4]  # d80db4704700
.globl _th10_00464199
_th10_00464199:
    fxch  # d9c9
.globl _th10_0046419b
_th10_0046419b:
    fmul dword ptr [_th10_004770b4]  # d80db4704700
.globl _th10_004641a1
_th10_004641a1:
    fxch  # d9c9
.globl _th10_004641a3
_th10_004641a3:
    {disp8} fldcw [esp+0x1C]  # d96c241c
.globl _th10_004641a7
_th10_004641a7:
    fdivp  # def9
.globl _th10_004641a9
_th10_004641a9:
    ret  # c3
.globl _th10_004641aa
_th10_004641aa:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_004641ae
_th10_004641ae:
    {disp8} {load} or eax, [esp+8]  # 0b442408
.globl _th10_004641b2
_th10_004641b2:
    {disp8} jne _th10_004641b7  # 7503
.globl _th10_004641b4
_th10_004641b4:
    fdivp  # def9
.globl _th10_004641b6
_th10_004641b6:
    ret  # c3
.globl _th10_004641b7
_th10_004641b7:
    {disp8} {load} mov eax, [esp+0x0C]  # 8b44240c
.globl _th10_004641bb
_th10_004641bb:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_004641c0
_th10_004641c0:
    {disp8} jne _th10_004641b4  # 75f2
.globl _th10_004641c2
_th10_004641c2:
    {disp8} fnstcw [esp+0x1C]  # d97c241c
.globl _th10_004641c6
_th10_004641c6:
    {disp8} {load} mov eax, [esp+0x1C]  # 8b44241c
.globl _th10_004641ca
_th10_004641ca:
    {noimm8s} or eax, 0x33F  # 0d3f030000
.globl _th10_004641cf
_th10_004641cf:
    {noimm8s} and eax, 0x0F3FF  # 25fff30000
.globl _th10_004641d4
_th10_004641d4:
    {disp8} {store} mov [esp+0x20], eax  # 89442420
.globl _th10_004641d8
_th10_004641d8:
    {disp8} fldcw [esp+0x20]  # d96c2420
.globl _th10_004641dc
_th10_004641dc:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_004641e0
_th10_004641e0:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_004641e5
_th10_004641e5:
    {disp8} je _th10_004641f8  # 7411
.globl _th10_004641e7
_th10_004641e7:
    {noimm8s} cmp eax, 0x7FFF  # 3dff7f0000
.globl _th10_004641ec
_th10_004641ec:
    {disp8} je _th10_00464220  # 7432
.globl _th10_004641ee
_th10_004641ee:
    {disp8} {load} mov eax, [esp+0x14]  # 8b442414
.globl _th10_004641f2
_th10_004641f2:
    {load} add eax, eax  # 03c0
.globl _th10_004641f4
_th10_004641f4:
    {disp8} jae _th10_00464220  # 732a
.globl _th10_004641f6
_th10_004641f6:
    {disp8} jmp _th10_00464200  # eb08
.globl _th10_004641f8
_th10_004641f8:
    {disp8} {load} mov eax, [esp+0x14]  # 8b442414
.globl _th10_004641fc
_th10_004641fc:
    {load} add eax, eax  # 03c0
.globl _th10_004641fe
_th10_004641fe:
    {disp8} jb _th10_00464220  # 7220
.globl _th10_00464200
_th10_00464200:
    fxch  # d9c9
.globl _th10_00464202
_th10_00464202:
    fstp st(0)  # ddd8
.globl _th10_00464204
_th10_00464204:
    fld st(0)  # d9c0
.globl _th10_00464206
_th10_00464206:
    fmul dword ptr [_th10_004770b8]  # d80db8704700
.globl _th10_0046420c
_th10_0046420c:
    {disp8} fstp tbyte ptr [esp+4]  # db7c2404
.globl _th10_00464210
_th10_00464210:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464214
_th10_00464214:
    fxch  # d9c9
.globl _th10_00464216
_th10_00464216:
    fwait  # 9b
.globl _th10_00464217
_th10_00464217:
    {disp8} fldcw [esp+0x1C]  # d96c241c
.globl _th10_0046421b
_th10_0046421b:
    {disp32} jmp _th10_00464118  # e9f8feffff
.globl _th10_00464220
_th10_00464220:
    {disp8} fldcw [esp+0x1C]  # d96c241c
.globl _th10_00464224
_th10_00464224:
    fdivp  # def9
.globl _th10_00464226
_th10_00464226:
    ret  # c3
.globl _th10_00464227
_th10_00464227:
    sub esp, 44  # 83ec2c
.globl _th10_0046422a
_th10_0046422a:
    and eax, 63  # 83e03f
.globl _th10_0046422d
_th10_0046422d:
    jmp dword ptr [eax*4+0x4770FE]  # ff2485fe704700
.globl _th10_00464234
_th10_00464234:
    fdiv st(0)  # d8f0
.globl _th10_00464236
_th10_00464236:
    add esp, 44  # 83c42c
.globl _th10_00464239
_th10_00464239:
    ret  # c3
.globl _th10_0046423a
_th10_0046423a:
    add esp, 44  # 83c42c
.globl _th10_0046423d
_th10_0046423d:
    int 6  # cd06
.globl _th10_0046423f
_th10_0046423f:
    fdivr st(0)  # d8f8
.globl _th10_00464241
_th10_00464241:
    add esp, 44  # 83c42c
.globl _th10_00464244
_th10_00464244:
    ret  # c3
.globl _th10_00464245
_th10_00464245:
    add esp, 44  # 83c42c
.globl _th10_00464248
_th10_00464248:
    int 6  # cd06
.globl _th10_0046424a
_th10_0046424a:
    fdiv st(0)  # d8f0
.globl _th10_0046424c
_th10_0046424c:
    add esp, 44  # 83c42c
.globl _th10_0046424f
_th10_0046424f:
    ret  # c3
.globl _th10_00464250
_th10_00464250:
    fdivp st(0), st  # def8
.globl _th10_00464252
_th10_00464252:
    add esp, 44  # 83c42c
.globl _th10_00464255
_th10_00464255:
    ret  # c3
.globl _th10_00464256
_th10_00464256:
    fdivr st(0)  # d8f8
.globl _th10_00464258
_th10_00464258:
    add esp, 44  # 83c42c
.globl _th10_0046425b
_th10_0046425b:
    ret  # c3
.globl _th10_0046425c
_th10_0046425c:
    fdivrp st(0), st  # def0
.globl _th10_0046425e
_th10_0046425e:
    add esp, 44  # 83c42c
.globl _th10_00464261
_th10_00464261:
    ret  # c3
.globl _th10_00464262
_th10_00464262:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464266
_th10_00464266:
    fld st(0)  # d9c0
.globl _th10_00464268
_th10_00464268:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046426b
_th10_0046426b:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_0046426f
_th10_0046426f:
    {disp32} call _th10_00464110  # e89cfeffff
.globl _th10_00464274
_th10_00464274:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_00464278
_th10_00464278:
    fxch  # d9c9
.globl _th10_0046427a
_th10_0046427a:
    add esp, 44  # 83c42c
.globl _th10_0046427d
_th10_0046427d:
    ret  # c3
.globl _th10_0046427e
_th10_0046427e:
    add esp, 44  # 83c42c
.globl _th10_00464281
_th10_00464281:
    int 6  # cd06
.globl _th10_00464283
_th10_00464283:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464286
_th10_00464286:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046428a
_th10_0046428a:
    {disp32} call _th10_00464110  # e881feffff
.globl _th10_0046428f
_th10_0046428f:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_00464293
_th10_00464293:
    fxch  # d9c9
.globl _th10_00464295
_th10_00464295:
    add esp, 44  # 83c42c
.globl _th10_00464298
_th10_00464298:
    ret  # c3
.globl _th10_00464299
_th10_00464299:
    add esp, 44  # 83c42c
.globl _th10_0046429c
_th10_0046429c:
    int 6  # cd06
.globl _th10_0046429e
_th10_0046429e:
    fxch  # d9c9
.globl _th10_004642a0
_th10_004642a0:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004642a4
_th10_004642a4:
    fld st(0)  # d9c0
.globl _th10_004642a6
_th10_004642a6:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004642a9
_th10_004642a9:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_004642ad
_th10_004642ad:
    {disp32} call _th10_00464110  # e85efeffff
.globl _th10_004642b2
_th10_004642b2:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_004642b6
_th10_004642b6:
    add esp, 44  # 83c42c
.globl _th10_004642b9
_th10_004642b9:
    ret  # c3
.globl _th10_004642ba
_th10_004642ba:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004642bd
_th10_004642bd:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004642c1
_th10_004642c1:
    {disp32} call _th10_00464110  # e84afeffff
.globl _th10_004642c6
_th10_004642c6:
    add esp, 44  # 83c42c
.globl _th10_004642c9
_th10_004642c9:
    ret  # c3
.globl _th10_004642ca
_th10_004642ca:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004642ce
_th10_004642ce:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004642d1
_th10_004642d1:
    {disp32} call _th10_00464110  # e83afeffff
.globl _th10_004642d6
_th10_004642d6:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_004642da
_th10_004642da:
    add esp, 44  # 83c42c
.globl _th10_004642dd
_th10_004642dd:
    ret  # c3
.globl _th10_004642de
_th10_004642de:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004642e2
_th10_004642e2:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004642e5
_th10_004642e5:
    {disp32} call _th10_00464110  # e826feffff
.globl _th10_004642ea
_th10_004642ea:
    add esp, 44  # 83c42c
.globl _th10_004642ed
_th10_004642ed:
    ret  # c3
.globl _th10_004642ee
_th10_004642ee:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004642f2
_th10_004642f2:
    fxch  # d9c9
.globl _th10_004642f4
_th10_004642f4:
    fld st(0)  # d9c0
.globl _th10_004642f6
_th10_004642f6:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004642f9
_th10_004642f9:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_004642fd
_th10_004642fd:
    {disp32} call _th10_00464110  # e80efeffff
.globl _th10_00464302
_th10_00464302:
    fxch  # d9c9
.globl _th10_00464304
_th10_00464304:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_00464308
_th10_00464308:
    fxch st(2)  # d9ca
.globl _th10_0046430a
_th10_0046430a:
    add esp, 44  # 83c42c
.globl _th10_0046430d
_th10_0046430d:
    ret  # c3
.globl _th10_0046430e
_th10_0046430e:
    add esp, 44  # 83c42c
.globl _th10_00464311
_th10_00464311:
    int 6  # cd06
.globl _th10_00464313
_th10_00464313:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464316
_th10_00464316:
    fxch  # d9c9
.globl _th10_00464318
_th10_00464318:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046431c
_th10_0046431c:
    {disp32} call _th10_00464110  # e8effdffff
.globl _th10_00464321
_th10_00464321:
    fxch  # d9c9
.globl _th10_00464323
_th10_00464323:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_00464327
_th10_00464327:
    fxch st(2)  # d9ca
.globl _th10_00464329
_th10_00464329:
    add esp, 44  # 83c42c
.globl _th10_0046432c
_th10_0046432c:
    ret  # c3
.globl _th10_0046432d
_th10_0046432d:
    add esp, 44  # 83c42c
.globl _th10_00464330
_th10_00464330:
    int 6  # cd06
.globl _th10_00464332
_th10_00464332:
    fxch st(2)  # d9ca
.globl _th10_00464334
_th10_00464334:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464338
_th10_00464338:
    fxch  # d9c9
.globl _th10_0046433a
_th10_0046433a:
    fld st(0)  # d9c0
.globl _th10_0046433c
_th10_0046433c:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046433f
_th10_0046433f:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_00464343
_th10_00464343:
    {disp32} call _th10_00464110  # e8c8fdffff
.globl _th10_00464348
_th10_00464348:
    fxch  # d9c9
.globl _th10_0046434a
_th10_0046434a:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_0046434e
_th10_0046434e:
    add esp, 44  # 83c42c
.globl _th10_00464351
_th10_00464351:
    ret  # c3
.globl _th10_00464352
_th10_00464352:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464355
_th10_00464355:
    fxch  # d9c9
.globl _th10_00464357
_th10_00464357:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046435b
_th10_0046435b:
    {disp32} call _th10_00464110  # e8b0fdffff
.globl _th10_00464360
_th10_00464360:
    fxch  # d9c9
.globl _th10_00464362
_th10_00464362:
    add esp, 44  # 83c42c
.globl _th10_00464365
_th10_00464365:
    ret  # c3
.globl _th10_00464366
_th10_00464366:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046436a
_th10_0046436a:
    fxch  # d9c9
.globl _th10_0046436c
_th10_0046436c:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046436f
_th10_0046436f:
    {disp32} call _th10_00464110  # e89cfdffff
.globl _th10_00464374
_th10_00464374:
    fxch  # d9c9
.globl _th10_00464376
_th10_00464376:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_0046437a
_th10_0046437a:
    add esp, 44  # 83c42c
.globl _th10_0046437d
_th10_0046437d:
    ret  # c3
.globl _th10_0046437e
_th10_0046437e:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464382
_th10_00464382:
    fxch  # d9c9
.globl _th10_00464384
_th10_00464384:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464387
_th10_00464387:
    {disp32} call _th10_00464110  # e884fdffff
.globl _th10_0046438c
_th10_0046438c:
    fxch  # d9c9
.globl _th10_0046438e
_th10_0046438e:
    add esp, 44  # 83c42c
.globl _th10_00464391
_th10_00464391:
    ret  # c3
.globl _th10_00464392
_th10_00464392:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464396
_th10_00464396:
    fxch st(2)  # d9ca
.globl _th10_00464398
_th10_00464398:
    fld st(0)  # d9c0
.globl _th10_0046439a
_th10_0046439a:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046439d
_th10_0046439d:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_004643a1
_th10_004643a1:
    {disp32} call _th10_00464110  # e86afdffff
.globl _th10_004643a6
_th10_004643a6:
    fxch st(2)  # d9ca
.globl _th10_004643a8
_th10_004643a8:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_004643ac
_th10_004643ac:
    fxch st(3)  # d9cb
.globl _th10_004643ae
_th10_004643ae:
    add esp, 44  # 83c42c
.globl _th10_004643b1
_th10_004643b1:
    ret  # c3
.globl _th10_004643b2
_th10_004643b2:
    add esp, 44  # 83c42c
.globl _th10_004643b5
_th10_004643b5:
    int 6  # cd06
.globl _th10_004643b7
_th10_004643b7:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004643ba
_th10_004643ba:
    fxch st(2)  # d9ca
.globl _th10_004643bc
_th10_004643bc:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004643c0
_th10_004643c0:
    {disp32} call _th10_00464110  # e84bfdffff
.globl _th10_004643c5
_th10_004643c5:
    fxch st(2)  # d9ca
.globl _th10_004643c7
_th10_004643c7:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_004643cb
_th10_004643cb:
    fxch st(3)  # d9cb
.globl _th10_004643cd
_th10_004643cd:
    add esp, 44  # 83c42c
.globl _th10_004643d0
_th10_004643d0:
    ret  # c3
.globl _th10_004643d1
_th10_004643d1:
    add esp, 44  # 83c42c
.globl _th10_004643d4
_th10_004643d4:
    int 6  # cd06
.globl _th10_004643d6
_th10_004643d6:
    fxch st(3)  # d9cb
.globl _th10_004643d8
_th10_004643d8:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004643dc
_th10_004643dc:
    fxch st(2)  # d9ca
.globl _th10_004643de
_th10_004643de:
    fld st(0)  # d9c0
.globl _th10_004643e0
_th10_004643e0:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004643e3
_th10_004643e3:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_004643e7
_th10_004643e7:
    {disp32} call _th10_00464110  # e824fdffff
.globl _th10_004643ec
_th10_004643ec:
    fxch st(2)  # d9ca
.globl _th10_004643ee
_th10_004643ee:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_004643f2
_th10_004643f2:
    add esp, 44  # 83c42c
.globl _th10_004643f5
_th10_004643f5:
    ret  # c3
.globl _th10_004643f6
_th10_004643f6:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004643f9
_th10_004643f9:
    fxch st(2)  # d9ca
.globl _th10_004643fb
_th10_004643fb:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004643ff
_th10_004643ff:
    {disp32} call _th10_00464110  # e80cfdffff
.globl _th10_00464404
_th10_00464404:
    fxch st(2)  # d9ca
.globl _th10_00464406
_th10_00464406:
    add esp, 44  # 83c42c
.globl _th10_00464409
_th10_00464409:
    ret  # c3
.globl _th10_0046440a
_th10_0046440a:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046440e
_th10_0046440e:
    fxch st(2)  # d9ca
.globl _th10_00464410
_th10_00464410:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464413
_th10_00464413:
    {disp32} call _th10_00464110  # e8f8fcffff
.globl _th10_00464418
_th10_00464418:
    fxch st(2)  # d9ca
.globl _th10_0046441a
_th10_0046441a:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_0046441e
_th10_0046441e:
    add esp, 44  # 83c42c
.globl _th10_00464421
_th10_00464421:
    ret  # c3
.globl _th10_00464422
_th10_00464422:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464426
_th10_00464426:
    fxch st(2)  # d9ca
.globl _th10_00464428
_th10_00464428:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046442b
_th10_0046442b:
    {disp32} call _th10_00464110  # e8e0fcffff
.globl _th10_00464430
_th10_00464430:
    fxch st(2)  # d9ca
.globl _th10_00464432
_th10_00464432:
    add esp, 44  # 83c42c
.globl _th10_00464435
_th10_00464435:
    ret  # c3
.globl _th10_00464436
_th10_00464436:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046443a
_th10_0046443a:
    fxch st(3)  # d9cb
.globl _th10_0046443c
_th10_0046443c:
    fld st(0)  # d9c0
.globl _th10_0046443e
_th10_0046443e:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464441
_th10_00464441:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_00464445
_th10_00464445:
    {disp32} call _th10_00464110  # e8c6fcffff
.globl _th10_0046444a
_th10_0046444a:
    fxch st(3)  # d9cb
.globl _th10_0046444c
_th10_0046444c:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_00464450
_th10_00464450:
    fxch st(4)  # d9cc
.globl _th10_00464452
_th10_00464452:
    add esp, 44  # 83c42c
.globl _th10_00464455
_th10_00464455:
    ret  # c3
.globl _th10_00464456
_th10_00464456:
    add esp, 44  # 83c42c
.globl _th10_00464459
_th10_00464459:
    int 6  # cd06
.globl _th10_0046445b
_th10_0046445b:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046445e
_th10_0046445e:
    fxch st(3)  # d9cb
.globl _th10_00464460
_th10_00464460:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464464
_th10_00464464:
    {disp32} call _th10_00464110  # e8a7fcffff
.globl _th10_00464469
_th10_00464469:
    fxch st(3)  # d9cb
.globl _th10_0046446b
_th10_0046446b:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_0046446f
_th10_0046446f:
    fxch st(4)  # d9cc
.globl _th10_00464471
_th10_00464471:
    add esp, 44  # 83c42c
.globl _th10_00464474
_th10_00464474:
    ret  # c3
.globl _th10_00464475
_th10_00464475:
    add esp, 44  # 83c42c
.globl _th10_00464478
_th10_00464478:
    int 6  # cd06
.globl _th10_0046447a
_th10_0046447a:
    fxch st(4)  # d9cc
.globl _th10_0046447c
_th10_0046447c:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464480
_th10_00464480:
    fxch st(3)  # d9cb
.globl _th10_00464482
_th10_00464482:
    fld st(0)  # d9c0
.globl _th10_00464484
_th10_00464484:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464487
_th10_00464487:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_0046448b
_th10_0046448b:
    {disp32} call _th10_00464110  # e880fcffff
.globl _th10_00464490
_th10_00464490:
    fxch st(3)  # d9cb
.globl _th10_00464492
_th10_00464492:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_00464496
_th10_00464496:
    add esp, 44  # 83c42c
.globl _th10_00464499
_th10_00464499:
    ret  # c3
.globl _th10_0046449a
_th10_0046449a:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046449d
_th10_0046449d:
    fxch st(3)  # d9cb
.globl _th10_0046449f
_th10_0046449f:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004644a3
_th10_004644a3:
    {disp32} call _th10_00464110  # e868fcffff
.globl _th10_004644a8
_th10_004644a8:
    fxch st(3)  # d9cb
.globl _th10_004644aa
_th10_004644aa:
    add esp, 44  # 83c42c
.globl _th10_004644ad
_th10_004644ad:
    ret  # c3
.globl _th10_004644ae
_th10_004644ae:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004644b2
_th10_004644b2:
    fxch st(3)  # d9cb
.globl _th10_004644b4
_th10_004644b4:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004644b7
_th10_004644b7:
    {disp32} call _th10_00464110  # e854fcffff
.globl _th10_004644bc
_th10_004644bc:
    fxch st(3)  # d9cb
.globl _th10_004644be
_th10_004644be:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_004644c2
_th10_004644c2:
    add esp, 44  # 83c42c
.globl _th10_004644c5
_th10_004644c5:
    ret  # c3
.globl _th10_004644c6
_th10_004644c6:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004644ca
_th10_004644ca:
    fxch st(3)  # d9cb
.globl _th10_004644cc
_th10_004644cc:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004644cf
_th10_004644cf:
    {disp32} call _th10_00464110  # e83cfcffff
.globl _th10_004644d4
_th10_004644d4:
    fxch st(3)  # d9cb
.globl _th10_004644d6
_th10_004644d6:
    add esp, 44  # 83c42c
.globl _th10_004644d9
_th10_004644d9:
    ret  # c3
.globl _th10_004644da
_th10_004644da:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004644de
_th10_004644de:
    fxch st(4)  # d9cc
.globl _th10_004644e0
_th10_004644e0:
    fld st(0)  # d9c0
.globl _th10_004644e2
_th10_004644e2:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004644e5
_th10_004644e5:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_004644e9
_th10_004644e9:
    {disp32} call _th10_00464110  # e822fcffff
.globl _th10_004644ee
_th10_004644ee:
    fxch st(4)  # d9cc
.globl _th10_004644f0
_th10_004644f0:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_004644f4
_th10_004644f4:
    fxch st(5)  # d9cd
.globl _th10_004644f6
_th10_004644f6:
    add esp, 44  # 83c42c
.globl _th10_004644f9
_th10_004644f9:
    ret  # c3
.globl _th10_004644fa
_th10_004644fa:
    add esp, 44  # 83c42c
.globl _th10_004644fd
_th10_004644fd:
    int 6  # cd06
.globl _th10_004644ff
_th10_004644ff:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464502
_th10_00464502:
    fxch st(4)  # d9cc
.globl _th10_00464504
_th10_00464504:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464508
_th10_00464508:
    {disp32} call _th10_00464110  # e803fcffff
.globl _th10_0046450d
_th10_0046450d:
    fxch st(4)  # d9cc
.globl _th10_0046450f
_th10_0046450f:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_00464513
_th10_00464513:
    fxch st(5)  # d9cd
.globl _th10_00464515
_th10_00464515:
    add esp, 44  # 83c42c
.globl _th10_00464518
_th10_00464518:
    ret  # c3
.globl _th10_00464519
_th10_00464519:
    add esp, 44  # 83c42c
.globl _th10_0046451c
_th10_0046451c:
    int 6  # cd06
.globl _th10_0046451e
_th10_0046451e:
    fxch st(5)  # d9cd
.globl _th10_00464520
_th10_00464520:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464524
_th10_00464524:
    fxch st(4)  # d9cc
.globl _th10_00464526
_th10_00464526:
    fld st(0)  # d9c0
.globl _th10_00464528
_th10_00464528:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046452b
_th10_0046452b:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_0046452f
_th10_0046452f:
    {disp32} call _th10_00464110  # e8dcfbffff
.globl _th10_00464534
_th10_00464534:
    fxch st(4)  # d9cc
.globl _th10_00464536
_th10_00464536:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_0046453a
_th10_0046453a:
    add esp, 44  # 83c42c
.globl _th10_0046453d
_th10_0046453d:
    ret  # c3
.globl _th10_0046453e
_th10_0046453e:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464541
_th10_00464541:
    fxch st(4)  # d9cc
.globl _th10_00464543
_th10_00464543:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464547
_th10_00464547:
    {disp32} call _th10_00464110  # e8c4fbffff
.globl _th10_0046454c
_th10_0046454c:
    fxch st(4)  # d9cc
.globl _th10_0046454e
_th10_0046454e:
    add esp, 44  # 83c42c
.globl _th10_00464551
_th10_00464551:
    ret  # c3
.globl _th10_00464552
_th10_00464552:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464556
_th10_00464556:
    fxch st(4)  # d9cc
.globl _th10_00464558
_th10_00464558:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046455b
_th10_0046455b:
    {disp32} call _th10_00464110  # e8b0fbffff
.globl _th10_00464560
_th10_00464560:
    fxch st(4)  # d9cc
.globl _th10_00464562
_th10_00464562:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_00464566
_th10_00464566:
    add esp, 44  # 83c42c
.globl _th10_00464569
_th10_00464569:
    ret  # c3
.globl _th10_0046456a
_th10_0046456a:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046456e
_th10_0046456e:
    fxch st(4)  # d9cc
.globl _th10_00464570
_th10_00464570:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464573
_th10_00464573:
    {disp32} call _th10_00464110  # e898fbffff
.globl _th10_00464578
_th10_00464578:
    fxch st(4)  # d9cc
.globl _th10_0046457a
_th10_0046457a:
    add esp, 44  # 83c42c
.globl _th10_0046457d
_th10_0046457d:
    ret  # c3
.globl _th10_0046457e
_th10_0046457e:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464582
_th10_00464582:
    fxch st(5)  # d9cd
.globl _th10_00464584
_th10_00464584:
    fld st(0)  # d9c0
.globl _th10_00464586
_th10_00464586:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464589
_th10_00464589:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_0046458d
_th10_0046458d:
    {disp32} call _th10_00464110  # e87efbffff
.globl _th10_00464592
_th10_00464592:
    fxch st(5)  # d9cd
.globl _th10_00464594
_th10_00464594:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_00464598
_th10_00464598:
    fxch st(6)  # d9ce
.globl _th10_0046459a
_th10_0046459a:
    add esp, 44  # 83c42c
.globl _th10_0046459d
_th10_0046459d:
    ret  # c3
.globl _th10_0046459e
_th10_0046459e:
    add esp, 44  # 83c42c
.globl _th10_004645a1
_th10_004645a1:
    int 6  # cd06
.globl _th10_004645a3
_th10_004645a3:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004645a6
_th10_004645a6:
    fxch st(5)  # d9cd
.globl _th10_004645a8
_th10_004645a8:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004645ac
_th10_004645ac:
    {disp32} call _th10_00464110  # e85ffbffff
.globl _th10_004645b1
_th10_004645b1:
    fxch st(5)  # d9cd
.globl _th10_004645b3
_th10_004645b3:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_004645b7
_th10_004645b7:
    fxch st(6)  # d9ce
.globl _th10_004645b9
_th10_004645b9:
    add esp, 44  # 83c42c
.globl _th10_004645bc
_th10_004645bc:
    ret  # c3
.globl _th10_004645bd
_th10_004645bd:
    add esp, 44  # 83c42c
.globl _th10_004645c0
_th10_004645c0:
    int 6  # cd06
.globl _th10_004645c2
_th10_004645c2:
    fxch st(6)  # d9ce
.globl _th10_004645c4
_th10_004645c4:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004645c8
_th10_004645c8:
    fxch st(5)  # d9cd
.globl _th10_004645ca
_th10_004645ca:
    fld st(0)  # d9c0
.globl _th10_004645cc
_th10_004645cc:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004645cf
_th10_004645cf:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_004645d3
_th10_004645d3:
    {disp32} call _th10_00464110  # e838fbffff
.globl _th10_004645d8
_th10_004645d8:
    fxch st(5)  # d9cd
.globl _th10_004645da
_th10_004645da:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_004645de
_th10_004645de:
    add esp, 44  # 83c42c
.globl _th10_004645e1
_th10_004645e1:
    ret  # c3
.globl _th10_004645e2
_th10_004645e2:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004645e5
_th10_004645e5:
    fxch st(5)  # d9cd
.globl _th10_004645e7
_th10_004645e7:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004645eb
_th10_004645eb:
    {disp32} call _th10_00464110  # e820fbffff
.globl _th10_004645f0
_th10_004645f0:
    fxch st(5)  # d9cd
.globl _th10_004645f2
_th10_004645f2:
    add esp, 44  # 83c42c
.globl _th10_004645f5
_th10_004645f5:
    ret  # c3
.globl _th10_004645f6
_th10_004645f6:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004645fa
_th10_004645fa:
    fxch st(5)  # d9cd
.globl _th10_004645fc
_th10_004645fc:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004645ff
_th10_004645ff:
    {disp32} call _th10_00464110  # e80cfbffff
.globl _th10_00464604
_th10_00464604:
    fxch st(5)  # d9cd
.globl _th10_00464606
_th10_00464606:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_0046460a
_th10_0046460a:
    add esp, 44  # 83c42c
.globl _th10_0046460d
_th10_0046460d:
    ret  # c3
.globl _th10_0046460e
_th10_0046460e:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464612
_th10_00464612:
    fxch st(5)  # d9cd
.globl _th10_00464614
_th10_00464614:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464617
_th10_00464617:
    {disp32} call _th10_00464110  # e8f4faffff
.globl _th10_0046461c
_th10_0046461c:
    fxch st(5)  # d9cd
.globl _th10_0046461e
_th10_0046461e:
    add esp, 44  # 83c42c
.globl _th10_00464621
_th10_00464621:
    ret  # c3
.globl _th10_00464622
_th10_00464622:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464626
_th10_00464626:
    fxch st(6)  # d9ce
.globl _th10_00464628
_th10_00464628:
    fld st(0)  # d9c0
.globl _th10_0046462a
_th10_0046462a:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046462d
_th10_0046462d:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_00464631
_th10_00464631:
    {disp32} call _th10_00464110  # e8dafaffff
.globl _th10_00464636
_th10_00464636:
    fxch st(6)  # d9ce
.globl _th10_00464638
_th10_00464638:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_0046463c
_th10_0046463c:
    fxch st(7)  # d9cf
.globl _th10_0046463e
_th10_0046463e:
    add esp, 44  # 83c42c
.globl _th10_00464641
_th10_00464641:
    ret  # c3
.globl _th10_00464642
_th10_00464642:
    add esp, 44  # 83c42c
.globl _th10_00464645
_th10_00464645:
    int 6  # cd06
.globl _th10_00464647
_th10_00464647:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046464a
_th10_0046464a:
    fxch st(6)  # d9ce
.globl _th10_0046464c
_th10_0046464c:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464650
_th10_00464650:
    {disp32} call _th10_00464110  # e8bbfaffff
.globl _th10_00464655
_th10_00464655:
    fxch st(6)  # d9ce
.globl _th10_00464657
_th10_00464657:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_0046465b
_th10_0046465b:
    fxch st(7)  # d9cf
.globl _th10_0046465d
_th10_0046465d:
    add esp, 44  # 83c42c
.globl _th10_00464660
_th10_00464660:
    ret  # c3
.globl _th10_00464661
_th10_00464661:
    add esp, 44  # 83c42c
.globl _th10_00464664
_th10_00464664:
    int 6  # cd06
.globl _th10_00464666
_th10_00464666:
    fxch st(7)  # d9cf
.globl _th10_00464668
_th10_00464668:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046466c
_th10_0046466c:
    fxch st(6)  # d9ce
.globl _th10_0046466e
_th10_0046466e:
    fld st(0)  # d9c0
.globl _th10_00464670
_th10_00464670:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464673
_th10_00464673:
    {disp8} fstp tbyte ptr [esp+0x20]  # db7c2420
.globl _th10_00464677
_th10_00464677:
    {disp32} call _th10_00464110  # e894faffff
.globl _th10_0046467c
_th10_0046467c:
    fxch st(6)  # d9ce
.globl _th10_0046467e
_th10_0046467e:
    {disp8} fld tbyte ptr [esp+0x20]  # db6c2420
.globl _th10_00464682
_th10_00464682:
    add esp, 44  # 83c42c
.globl _th10_00464685
_th10_00464685:
    ret  # c3
.globl _th10_00464686
_th10_00464686:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464689
_th10_00464689:
    fxch st(6)  # d9ce
.globl _th10_0046468b
_th10_0046468b:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046468f
_th10_0046468f:
    {disp32} call _th10_00464110  # e87cfaffff
.globl _th10_00464694
_th10_00464694:
    fxch st(6)  # d9ce
.globl _th10_00464696
_th10_00464696:
    add esp, 44  # 83c42c
.globl _th10_00464699
_th10_00464699:
    ret  # c3
.globl _th10_0046469a
_th10_0046469a:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_0046469e
_th10_0046469e:
    fxch st(6)  # d9ce
.globl _th10_004646a0
_th10_004646a0:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004646a3
_th10_004646a3:
    {disp32} call _th10_00464110  # e868faffff
.globl _th10_004646a8
_th10_004646a8:
    fxch st(6)  # d9ce
.globl _th10_004646aa
_th10_004646aa:
    {disp8} fld tbyte ptr [esp+0x0C]  # db6c240c
.globl _th10_004646ae
_th10_004646ae:
    add esp, 44  # 83c42c
.globl _th10_004646b1
_th10_004646b1:
    ret  # c3
.globl _th10_004646b2
_th10_004646b2:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004646b6
_th10_004646b6:
    fxch st(6)  # d9ce
.globl _th10_004646b8
_th10_004646b8:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004646bb
_th10_004646bb:
    {disp32} call _th10_00464110  # e850faffff
.globl _th10_004646c0
_th10_004646c0:
    fxch st(6)  # d9ce
.globl _th10_004646c2
_th10_004646c2:
    add esp, 44  # 83c42c
.globl _th10_004646c5
_th10_004646c5:
    ret  # c3
.globl _th10_004646c6
_th10_004646c6:
    sub esp, 44  # 83ec2c
.globl _th10_004646c9
_th10_004646c9:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004646cc
_th10_004646cc:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004646d0
_th10_004646d0:
    {disp32} call _th10_00464110  # e83bfaffff
.globl _th10_004646d5
_th10_004646d5:
    add esp, 44  # 83c42c
.globl _th10_004646d8
_th10_004646d8:
    ret  # c3
.globl _th10_004646d9
_th10_004646d9:
    sub esp, 44  # 83ec2c
.globl _th10_004646dc
_th10_004646dc:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004646e0
_th10_004646e0:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004646e3
_th10_004646e3:
    {disp32} call _th10_00464110  # e828faffff
.globl _th10_004646e8
_th10_004646e8:
    add esp, 44  # 83c42c
.globl _th10_004646eb
_th10_004646eb:
    ret  # c3
.globl _th10_004646ec
_th10_004646ec:
    push eax  # 50
.globl _th10_004646ed
_th10_004646ed:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_004646f1
_th10_004646f1:
    {noimm8s} and eax, 0x7F800000  # 250000807f
.globl _th10_004646f6
_th10_004646f6:
    {noimm8s} cmp eax, 0x7F800000  # 3d0000807f
.globl _th10_004646fb
_th10_004646fb:
    {disp8} je _th10_00464730  # 7433
.globl _th10_004646fd
_th10_004646fd:
    fnstsw ax  # dfe0
.globl _th10_004646ff
_th10_004646ff:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_00464704
_th10_00464704:
    {disp8} je _th10_00464713  # 740d
.globl _th10_00464706
_th10_00464706:
    {disp8} fld dword ptr [esp+8]  # d9442408
.globl _th10_0046470a
_th10_0046470a:
    {disp32} call _th10_004646c6  # e8b7ffffff
.globl _th10_0046470f
_th10_0046470f:
    pop eax  # 58
.globl _th10_00464710
_th10_00464710:
    {noimm8s} ret 4  # c20400
.globl _th10_00464713
_th10_00464713:
    fxch  # d9c9
.globl _th10_00464715
_th10_00464715:
    sub esp, 12  # 83ec0c
.globl _th10_00464718
_th10_00464718:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046471b
_th10_0046471b:
    {disp8} fld dword ptr [esp+0x14]  # d9442414
.globl _th10_0046471f
_th10_0046471f:
    {disp32} call _th10_004646c6  # e8a2ffffff
.globl _th10_00464724
_th10_00464724:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464727
_th10_00464727:
    fxch  # d9c9
.globl _th10_00464729
_th10_00464729:
    add esp, 12  # 83c40c
.globl _th10_0046472c
_th10_0046472c:
    pop eax  # 58
.globl _th10_0046472d
_th10_0046472d:
    {noimm8s} ret 4  # c20400
.globl _th10_00464730
_th10_00464730:
    {disp8} fdiv dword ptr [esp+8]  # d8742408
.globl _th10_00464734
_th10_00464734:
    pop eax  # 58
.globl _th10_00464735
_th10_00464735:
    {noimm8s} ret 4  # c20400
.globl _th10_00464738
_th10_00464738:
    push eax  # 50
.globl _th10_00464739
_th10_00464739:
    {disp8} {load} mov eax, [esp+0x0C]  # 8b44240c
.globl _th10_0046473d
_th10_0046473d:
    {noimm8s} and eax, 0x7FF00000  # 250000f07f
.globl _th10_00464742
_th10_00464742:
    {noimm8s} cmp eax, 0x7FF00000  # 3d0000f07f
.globl _th10_00464747
_th10_00464747:
    {disp8} je _th10_0046477c  # 7433
.globl _th10_00464749
_th10_00464749:
    fnstsw ax  # dfe0
.globl _th10_0046474b
_th10_0046474b:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_00464750
_th10_00464750:
    {disp8} je _th10_0046475f  # 740d
.globl _th10_00464752
_th10_00464752:
    {disp8} fld qword ptr [esp+8]  # dd442408
.globl _th10_00464756
_th10_00464756:
    {disp32} call _th10_004646c6  # e86bffffff
.globl _th10_0046475b
_th10_0046475b:
    pop eax  # 58
.globl _th10_0046475c
_th10_0046475c:
    {noimm8s} ret 8  # c20800
.globl _th10_0046475f
_th10_0046475f:
    fxch  # d9c9
.globl _th10_00464761
_th10_00464761:
    sub esp, 12  # 83ec0c
.globl _th10_00464764
_th10_00464764:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464767
_th10_00464767:
    {disp8} fld qword ptr [esp+0x14]  # dd442414
.globl _th10_0046476b
_th10_0046476b:
    {disp32} call _th10_004646c6  # e856ffffff
.globl _th10_00464770
_th10_00464770:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464773
_th10_00464773:
    fxch  # d9c9
.globl _th10_00464775
_th10_00464775:
    add esp, 12  # 83c40c
.globl _th10_00464778
_th10_00464778:
    pop eax  # 58
.globl _th10_00464779
_th10_00464779:
    {noimm8s} ret 8  # c20800
.globl _th10_0046477c
_th10_0046477c:
    {disp8} fdiv qword ptr [esp+8]  # dc742408
.globl _th10_00464780
_th10_00464780:
    pop eax  # 58
.globl _th10_00464781
_th10_00464781:
    {noimm8s} ret 8  # c20800
.globl _th10_00464784
_th10_00464784:
    push eax  # 50
.globl _th10_00464785
_th10_00464785:
    fnstsw ax  # dfe0
.globl _th10_00464787
_th10_00464787:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_0046478c
_th10_0046478c:
    {disp8} je _th10_0046479b  # 740d
.globl _th10_0046478e
_th10_0046478e:
    {disp8} fild word ptr [esp+8]  # df442408
.globl _th10_00464792
_th10_00464792:
    {disp32} call _th10_004646c6  # e82fffffff
.globl _th10_00464797
_th10_00464797:
    pop eax  # 58
.globl _th10_00464798
_th10_00464798:
    {noimm8s} ret 4  # c20400
.globl _th10_0046479b
_th10_0046479b:
    fxch  # d9c9
.globl _th10_0046479d
_th10_0046479d:
    sub esp, 12  # 83ec0c
.globl _th10_004647a0
_th10_004647a0:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004647a3
_th10_004647a3:
    {disp8} fild word ptr [esp+0x14]  # df442414
.globl _th10_004647a7
_th10_004647a7:
    {disp32} call _th10_004646c6  # e81affffff
.globl _th10_004647ac
_th10_004647ac:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_004647af
_th10_004647af:
    fxch  # d9c9
.globl _th10_004647b1
_th10_004647b1:
    add esp, 12  # 83c40c
.globl _th10_004647b4
_th10_004647b4:
    pop eax  # 58
.globl _th10_004647b5
_th10_004647b5:
    {noimm8s} ret 4  # c20400
.globl _th10_004647b8
_th10_004647b8:
    push eax  # 50
.globl _th10_004647b9
_th10_004647b9:
    fnstsw ax  # dfe0
.globl _th10_004647bb
_th10_004647bb:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_004647c0
_th10_004647c0:
    {disp8} je _th10_004647cf  # 740d
.globl _th10_004647c2
_th10_004647c2:
    {disp8} fild dword ptr [esp+8]  # db442408
.globl _th10_004647c6
_th10_004647c6:
    {disp32} call _th10_004646c6  # e8fbfeffff
.globl _th10_004647cb
_th10_004647cb:
    pop eax  # 58
.globl _th10_004647cc
_th10_004647cc:
    {noimm8s} ret 4  # c20400
.globl _th10_004647cf
_th10_004647cf:
    fxch  # d9c9
.globl _th10_004647d1
_th10_004647d1:
    sub esp, 12  # 83ec0c
.globl _th10_004647d4
_th10_004647d4:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004647d7
_th10_004647d7:
    {disp8} fild dword ptr [esp+0x14]  # db442414
.globl _th10_004647db
_th10_004647db:
    {disp32} call _th10_004646c6  # e8e6feffff
.globl _th10_004647e0
_th10_004647e0:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_004647e3
_th10_004647e3:
    fxch  # d9c9
.globl _th10_004647e5
_th10_004647e5:
    add esp, 12  # 83c40c
.globl _th10_004647e8
_th10_004647e8:
    pop eax  # 58
.globl _th10_004647e9
_th10_004647e9:
    {noimm8s} ret 4  # c20400
.globl _th10_004647ec
_th10_004647ec:
    push eax  # 50
.globl _th10_004647ed
_th10_004647ed:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_004647f1
_th10_004647f1:
    {noimm8s} and eax, 0x7F800000  # 250000807f
.globl _th10_004647f6
_th10_004647f6:
    {noimm8s} cmp eax, 0x7F800000  # 3d0000807f
.globl _th10_004647fb
_th10_004647fb:
    {disp8} je _th10_00464830  # 7433
.globl _th10_004647fd
_th10_004647fd:
    fnstsw ax  # dfe0
.globl _th10_004647ff
_th10_004647ff:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_00464804
_th10_00464804:
    {disp8} je _th10_00464813  # 740d
.globl _th10_00464806
_th10_00464806:
    {disp8} fld dword ptr [esp+8]  # d9442408
.globl _th10_0046480a
_th10_0046480a:
    {disp32} call _th10_004646d9  # e8cafeffff
.globl _th10_0046480f
_th10_0046480f:
    pop eax  # 58
.globl _th10_00464810
_th10_00464810:
    {noimm8s} ret 4  # c20400
.globl _th10_00464813
_th10_00464813:
    fxch  # d9c9
.globl _th10_00464815
_th10_00464815:
    sub esp, 12  # 83ec0c
.globl _th10_00464818
_th10_00464818:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046481b
_th10_0046481b:
    {disp8} fld dword ptr [esp+0x14]  # d9442414
.globl _th10_0046481f
_th10_0046481f:
    {disp32} call _th10_004646d9  # e8b5feffff
.globl _th10_00464824
_th10_00464824:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464827
_th10_00464827:
    fxch  # d9c9
.globl _th10_00464829
_th10_00464829:
    add esp, 12  # 83c40c
.globl _th10_0046482c
_th10_0046482c:
    pop eax  # 58
.globl _th10_0046482d
_th10_0046482d:
    {noimm8s} ret 4  # c20400
.globl _th10_00464830
_th10_00464830:
    {disp8} fdivr dword ptr [esp+8]  # d87c2408
.globl _th10_00464834
_th10_00464834:
    pop eax  # 58
.globl _th10_00464835
_th10_00464835:
    {noimm8s} ret 4  # c20400
.globl _th10_00464838
_th10_00464838:
    push eax  # 50
.globl _th10_00464839
_th10_00464839:
    {disp8} {load} mov eax, [esp+0x0C]  # 8b44240c
.globl _th10_0046483d
_th10_0046483d:
    {noimm8s} and eax, 0x7FF00000  # 250000f07f
.globl _th10_00464842
_th10_00464842:
    {noimm8s} cmp eax, 0x7FF00000  # 3d0000f07f
.globl _th10_00464847
_th10_00464847:
    {disp8} je _th10_0046487c  # 7433
.globl _th10_00464849
_th10_00464849:
    fnstsw ax  # dfe0
.globl _th10_0046484b
_th10_0046484b:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_00464850
_th10_00464850:
    {disp8} je _th10_0046485f  # 740d
.globl _th10_00464852
_th10_00464852:
    {disp8} fld qword ptr [esp+8]  # dd442408
.globl _th10_00464856
_th10_00464856:
    {disp32} call _th10_004646d9  # e87efeffff
.globl _th10_0046485b
_th10_0046485b:
    pop eax  # 58
.globl _th10_0046485c
_th10_0046485c:
    {noimm8s} ret 8  # c20800
.globl _th10_0046485f
_th10_0046485f:
    fxch  # d9c9
.globl _th10_00464861
_th10_00464861:
    sub esp, 12  # 83ec0c
.globl _th10_00464864
_th10_00464864:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464867
_th10_00464867:
    {disp8} fld qword ptr [esp+0x14]  # dd442414
.globl _th10_0046486b
_th10_0046486b:
    {disp32} call _th10_004646d9  # e869feffff
.globl _th10_00464870
_th10_00464870:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464873
_th10_00464873:
    fxch  # d9c9
.globl _th10_00464875
_th10_00464875:
    add esp, 12  # 83c40c
.globl _th10_00464878
_th10_00464878:
    pop eax  # 58
.globl _th10_00464879
_th10_00464879:
    {noimm8s} ret 8  # c20800
.globl _th10_0046487c
_th10_0046487c:
    {disp8} fdivr qword ptr [esp+8]  # dc7c2408
.globl _th10_00464880
_th10_00464880:
    pop eax  # 58
.globl _th10_00464881
_th10_00464881:
    {noimm8s} ret 8  # c20800
.globl _th10_00464884
_th10_00464884:
    push eax  # 50
.globl _th10_00464885
_th10_00464885:
    fnstsw ax  # dfe0
.globl _th10_00464887
_th10_00464887:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_0046488c
_th10_0046488c:
    {disp8} je _th10_0046489b  # 740d
.globl _th10_0046488e
_th10_0046488e:
    {disp8} fild word ptr [esp+8]  # df442408
.globl _th10_00464892
_th10_00464892:
    {disp32} call _th10_004646d9  # e842feffff
.globl _th10_00464897
_th10_00464897:
    pop eax  # 58
.globl _th10_00464898
_th10_00464898:
    {noimm8s} ret 4  # c20400
.globl _th10_0046489b
_th10_0046489b:
    fxch  # d9c9
.globl _th10_0046489d
_th10_0046489d:
    sub esp, 12  # 83ec0c
.globl _th10_004648a0
_th10_004648a0:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004648a3
_th10_004648a3:
    {disp8} fild word ptr [esp+0x14]  # df442414
.globl _th10_004648a7
_th10_004648a7:
    {disp32} call _th10_004646d9  # e82dfeffff
.globl _th10_004648ac
_th10_004648ac:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_004648af
_th10_004648af:
    fxch  # d9c9
.globl _th10_004648b1
_th10_004648b1:
    add esp, 12  # 83c40c
.globl _th10_004648b4
_th10_004648b4:
    pop eax  # 58
.globl _th10_004648b5
_th10_004648b5:
    {noimm8s} ret 4  # c20400
.globl _th10_004648b8
_th10_004648b8:
    push eax  # 50
.globl _th10_004648b9
_th10_004648b9:
    fnstsw ax  # dfe0
.globl _th10_004648bb
_th10_004648bb:
    {noimm8s} and eax, 0x3800  # 2500380000
.globl _th10_004648c0
_th10_004648c0:
    {disp8} je _th10_004648cf  # 740d
.globl _th10_004648c2
_th10_004648c2:
    {disp8} fild dword ptr [esp+8]  # db442408
.globl _th10_004648c6
_th10_004648c6:
    {disp32} call _th10_004646d9  # e80efeffff
.globl _th10_004648cb
_th10_004648cb:
    pop eax  # 58
.globl _th10_004648cc
_th10_004648cc:
    {noimm8s} ret 4  # c20400
.globl _th10_004648cf
_th10_004648cf:
    fxch  # d9c9
.globl _th10_004648d1
_th10_004648d1:
    sub esp, 12  # 83ec0c
.globl _th10_004648d4
_th10_004648d4:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004648d7
_th10_004648d7:
    {disp8} fild dword ptr [esp+0x14]  # db442414
.globl _th10_004648db
_th10_004648db:
    {disp32} call _th10_004646d9  # e8f9fdffff
.globl _th10_004648e0
_th10_004648e0:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_004648e3
_th10_004648e3:
    fxch  # d9c9
.globl _th10_004648e5
_th10_004648e5:
    add esp, 12  # 83c40c
.globl _th10_004648e8
_th10_004648e8:
    pop eax  # 58
.globl _th10_004648e9
_th10_004648e9:
    {noimm8s} ret 4  # c20400
.globl _th10_004648ec
_th10_004648ec:
    push eax  # 50
.globl _th10_004648ed
_th10_004648ed:
    sub esp, 44  # 83ec2c
.globl _th10_004648f0
_th10_004648f0:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_004648f3
_th10_004648f3:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_004648f7
_th10_004648f7:
    {disp32} call _th10_00464110  # e814f8ffff
.globl _th10_004648fc
_th10_004648fc:
    add esp, 44  # 83c42c
.globl _th10_004648ff
_th10_004648ff:
    pop eax  # 58
.globl _th10_00464900
_th10_00464900:
    ret  # c3
.globl _th10_00464901
_th10_00464901:
    push eax  # 50
.globl _th10_00464902
_th10_00464902:
    sub esp, 44  # 83ec2c
.globl _th10_00464905
_th10_00464905:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464909
_th10_00464909:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_0046490c
_th10_0046490c:
    {disp32} call _th10_00464110  # e8fff7ffff
.globl _th10_00464911
_th10_00464911:
    add esp, 44  # 83c42c
.globl _th10_00464914
_th10_00464914:
    pop eax  # 58
.globl _th10_00464915
_th10_00464915:
    ret  # c3
.globl _th10_00464916
_th10_00464916:
    push eax  # 50
.globl _th10_00464917
_th10_00464917:
    push ebx  # 53
.globl _th10_00464918
_th10_00464918:
    push ecx  # 51
.globl _th10_00464919
_th10_00464919:
    {disp8} {load} mov eax, [esp+0x16]  # 8b442416
.globl _th10_0046491d
_th10_0046491d:
    {noimm8s} xor eax, 0x700  # 3500070000
.globl _th10_00464922
_th10_00464922:
    {noimm8s} test eax, 0x700  # a900070000
.globl _th10_00464927
_th10_00464927:
    {disp32} jne _th10_00464ab0  # 0f8583010000
.globl _th10_0046492d
_th10_0046492d:
    shr eax, 0x0B  # c1e80b
.globl _th10_00464930
_th10_00464930:
    and eax, 15  # 83e00f
.globl _th10_00464933
_th10_00464933:
    cmp byte ptr [eax+0x4770BC], 0  # 80b8bc70470000
.globl _th10_0046493a
_th10_0046493a:
    {disp32} je _th10_00464ab0  # 0f8470010000
.globl _th10_00464940
_th10_00464940:
    {disp8} {load} mov eax, [esp+0x16]  # 8b442416
.globl _th10_00464944
_th10_00464944:
    {noimm8s} and eax, 0x7FFF0000  # 250000ff7f
.globl _th10_00464949
_th10_00464949:
    {noimm8s} cmp eax, 0x7FFF0000  # 3d0000ff7f
.globl _th10_0046494e
_th10_0046494e:
    {disp32} je _th10_00464ab0  # 0f845c010000
.globl _th10_00464954
_th10_00464954:
    {disp8} {load} mov eax, [esp+0x2E]  # 8b44242e
.globl _th10_00464958
_th10_00464958:
    {noimm8s} and eax, 0x7FFF0000  # 250000ff7f
.globl _th10_0046495d
_th10_0046495d:
    {disp32} je _th10_00464ab0  # 0f844d010000
.globl _th10_00464963
_th10_00464963:
    {noimm8s} cmp eax, 0x7FFF0000  # 3d0000ff7f
.globl _th10_00464968
_th10_00464968:
    {disp32} je _th10_00464ab0  # 0f8442010000
.globl _th10_0046496e
_th10_0046496e:
    {disp8} {load} mov eax, [esp+0x2C]  # 8b44242c
.globl _th10_00464972
_th10_00464972:
    {load} add eax, eax  # 03c0
.globl _th10_00464974
_th10_00464974:
    {disp32} jne _th10_00464ab0  # 0f8536010000
.globl _th10_0046497a
_th10_0046497a:
    {disp8} {load} mov eax, [esp+0x14]  # 8b442414
.globl _th10_0046497e
_th10_0046497e:
    {load} add eax, eax  # 03c0
.globl _th10_00464980
_th10_00464980:
    {disp32} jne _th10_00464ab0  # 0f852a010000
.globl _th10_00464986
_th10_00464986:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_0046498a
_th10_0046498a:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_0046498f
_th10_0046498f:
    add eax, 63  # 83c03f
.globl _th10_00464992
_th10_00464992:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464996
_th10_00464996:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_0046499c
_th10_0046499c:
    {load} sub ebx, eax  # 2bd8
.globl _th10_0046499e
_th10_0046499e:
    {disp8} ja _th10_004649fe  # 775e
.globl _th10_004649a0
_th10_004649a0:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_004649a4
_th10_004649a4:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_004649a9
_th10_004649a9:
    add eax, 10  # 83c00a
.globl _th10_004649ac
_th10_004649ac:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_004649b0
_th10_004649b0:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_004649b6
_th10_004649b6:
    {load} sub ebx, eax  # 2bd8
.globl _th10_004649b8
_th10_004649b8:
    {disp32} js _th10_00464ab0  # 0f88f2000000
.globl _th10_004649be
_th10_004649be:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_004649c2
_th10_004649c2:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_004649c6
_th10_004649c6:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_004649ca
_th10_004649ca:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_004649d0
_th10_004649d0:
    {load} mov ecx, ebx  # 8bcb
.globl _th10_004649d2
_th10_004649d2:
    {load} sub ebx, eax  # 2bd8
.globl _th10_004649d4
_th10_004649d4:
    and ebx, 7  # 83e307
.globl _th10_004649d7
_th10_004649d7:
    or ebx, 4  # 83cb04
.globl _th10_004649da
_th10_004649da:
    {load} sub ecx, ebx  # 2bcb
.globl _th10_004649dc
_th10_004649dc:
    {load} mov ebx, eax  # 8bd8
.globl _th10_004649de
_th10_004649de:
    {noimm8s} and ebx, 0x8000  # 81e300800000
.globl _th10_004649e4
_th10_004649e4:
    {load} or ecx, ebx  # 0bcb
.globl _th10_004649e6
_th10_004649e6:
    {disp8} {store} mov [esp+0x18], ecx  # 894c2418
.globl _th10_004649ea
_th10_004649ea:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_004649ee
_th10_004649ee:
    {disp8} {store} mov [esp+0x18], eax  # 89442418
.globl _th10_004649f2
_th10_004649f2:
    fxch  # d9c9
.globl _th10_004649f4
_th10_004649f4:
    fprem  # d9f8
.globl _th10_004649f6
_th10_004649f6:
    {disp8} fstp tbyte ptr [esp+0x28]  # db7c2428
.globl _th10_004649fa
_th10_004649fa:
    fstp st(0)  # ddd8
.globl _th10_004649fc
_th10_004649fc:
    {disp8} jmp _th10_004649a0  # eba2
.globl _th10_004649fe
_th10_004649fe:
    {noimm8s} test edx, 2  # f7c202000000
.globl _th10_00464a04
_th10_00464a04:
    {disp8} jne _th10_00464a0e  # 7508
.globl _th10_00464a06
_th10_00464a06:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464a0a
_th10_00464a0a:
    {disp8} fstp tbyte ptr [esp+0x1C]  # db7c241c
.globl _th10_00464a0e
_th10_00464a0e:
    {disp8} fnstcw [esp+0x34]  # d97c2434
.globl _th10_00464a12
_th10_00464a12:
    {disp8} {load} mov eax, [esp+0x34]  # 8b442434
.globl _th10_00464a16
_th10_00464a16:
    {noimm8s} or eax, 0x33F  # 0d3f030000
.globl _th10_00464a1b
_th10_00464a1b:
    {disp8} {store} mov [esp+0x38], eax  # 89442438
.globl _th10_00464a1f
_th10_00464a1f:
    {disp8} fldcw [esp+0x38]  # d96c2438
.globl _th10_00464a23
_th10_00464a23:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464a27
_th10_00464a27:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464a2c
_th10_00464a2c:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464a30
_th10_00464a30:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464a36
_th10_00464a36:
    {load} sub ebx, eax  # 2bd8
.globl _th10_00464a38
_th10_00464a38:
    and ebx, 63  # 83e33f
.globl _th10_00464a3b
_th10_00464a3b:
    or ebx, 32  # 83cb20
.globl _th10_00464a3e
_th10_00464a3e:
    add ebx, 1  # 83c301
.globl _th10_00464a41
_th10_00464a41:
    {load} mov ecx, ebx  # 8bcb
.globl _th10_00464a43
_th10_00464a43:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464a47
_th10_00464a47:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464a4b
_th10_00464a4b:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464a51
_th10_00464a51:
    {noimm8s} and eax, 0x8000  # 2500800000
.globl _th10_00464a56
_th10_00464a56:
    {load} or ebx, eax  # 0bd8
.globl _th10_00464a58
_th10_00464a58:
    {disp8} {store} mov [esp+0x18], ebx  # 895c2418
.globl _th10_00464a5c
_th10_00464a5c:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464a60
_th10_00464a60:
    fabs  # d9e1
.globl _th10_00464a62
_th10_00464a62:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464a66
_th10_00464a66:
    fabs  # d9e1
.globl _th10_00464a68
_th10_00464a68:
    fcom  # d8d1
.globl _th10_00464a6a
_th10_00464a6a:
    fnstsw ax  # dfe0
.globl _th10_00464a6c
_th10_00464a6c:
    {noimm8s} and eax, 0x100  # 2500010000
.globl _th10_00464a71
_th10_00464a71:
    {disp8} jne _th10_00464a75  # 7502
.globl _th10_00464a73
_th10_00464a73:
    fsub st(1)  # d8e1
.globl _th10_00464a75
_th10_00464a75:
    fxch  # d9c9
.globl _th10_00464a77
_th10_00464a77:
    fmul qword ptr [_th10_004770ec]  # dc0dec704700
.globl _th10_00464a7d
_th10_00464a7d:
    fxch  # d9c9
.globl _th10_00464a7f
_th10_00464a7f:
    sub ecx, 1  # 83e901
.globl _th10_00464a82
_th10_00464a82:
    {disp8} jne _th10_00464a68  # 75e4
.globl _th10_00464a84
_th10_00464a84:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464a88
_th10_00464a88:
    {disp8} fstp tbyte ptr [esp+0x28]  # db7c2428
.globl _th10_00464a8c
_th10_00464a8c:
    fstp st(0)  # ddd8
.globl _th10_00464a8e
_th10_00464a8e:
    {disp8} fld tbyte ptr [esp+0x1C]  # db6c241c
.globl _th10_00464a92
_th10_00464a92:
    fld tbyte ptr [_th10_004770f4]  # db2df4704700
.globl _th10_00464a98
_th10_00464a98:
    fprem  # d9f8
.globl _th10_00464a9a
_th10_00464a9a:
    fstp st(0)  # ddd8
.globl _th10_00464a9c
_th10_00464a9c:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464aa0
_th10_00464aa0:
    {disp8} fldcw [esp+0x34]  # d96c2434
.globl _th10_00464aa4
_th10_00464aa4:
    {noimm8s} and ebx, 0x8000  # 81e300800000
.globl _th10_00464aaa
_th10_00464aaa:
    {disp8} je _th10_00464aba  # 740e
.globl _th10_00464aac
_th10_00464aac:
    fchs  # d9e0
.globl _th10_00464aae
_th10_00464aae:
    {disp8} jmp _th10_00464aba  # eb0a
.globl _th10_00464ab0
_th10_00464ab0:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464ab4
_th10_00464ab4:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464ab8
_th10_00464ab8:
    fprem  # d9f8
.globl _th10_00464aba
_th10_00464aba:
    {noimm8s} test edx, 3  # f7c203000000
.globl _th10_00464ac0
_th10_00464ac0:
    {disp8} je _th10_00464b18  # 7456
.globl _th10_00464ac2
_th10_00464ac2:
    {disp8} fnstsw [esp+0x3C]  # dd7c243c
.globl _th10_00464ac6
_th10_00464ac6:
    {noimm8s} test edx, 1  # f7c201000000
.globl _th10_00464acc
_th10_00464acc:
    {disp8} je _th10_00464aed  # 741f
.globl _th10_00464ace
_th10_00464ace:
    {disp8} fnstcw [esp+0x34]  # d97c2434
.globl _th10_00464ad2
_th10_00464ad2:
    {disp8} {load} mov eax, [esp+0x34]  # 8b442434
.globl _th10_00464ad6
_th10_00464ad6:
    {noimm8s} or eax, 0x300  # 0d00030000
.globl _th10_00464adb
_th10_00464adb:
    {disp8} {store} mov [esp+0x38], eax  # 89442438
.globl _th10_00464adf
_th10_00464adf:
    {disp8} fldcw [esp+0x38]  # d96c2438
.globl _th10_00464ae3
_th10_00464ae3:
    fmul qword ptr [_th10_004770dc]  # dc0ddc704700
.globl _th10_00464ae9
_th10_00464ae9:
    {disp8} fldcw [esp+0x34]  # d96c2434
.globl _th10_00464aed
_th10_00464aed:
    {disp8} {load} mov eax, [esp+0x3C]  # 8b44243c
.globl _th10_00464af1
_th10_00464af1:
    fxch  # d9c9
.globl _th10_00464af3
_th10_00464af3:
    fstp st(0)  # ddd8
.globl _th10_00464af5
_th10_00464af5:
    {disp8} fld tbyte ptr [esp+0x1C]  # db6c241c
.globl _th10_00464af9
_th10_00464af9:
    fxch  # d9c9
.globl _th10_00464afb
_th10_00464afb:
    {noimm8s} and eax, 0x4300  # 2500430000
.globl _th10_00464b00
_th10_00464b00:
    sub esp, 28  # 83ec1c
.globl _th10_00464b03
_th10_00464b03:
    fnstenv [esp]  # d93424
.globl _th10_00464b06
_th10_00464b06:
    {disp8} {noimm8s} and dword ptr [esp+4], 0x0BCFF  # 81642404ffbc0000
.globl _th10_00464b0e
_th10_00464b0e:
    {disp8} {store} or [esp+4], eax  # 09442404
.globl _th10_00464b12
_th10_00464b12:
    fldenv [esp]  # d92424
.globl _th10_00464b15
_th10_00464b15:
    add esp, 28  # 83c41c
.globl _th10_00464b18
_th10_00464b18:
    pop ecx  # 59
.globl _th10_00464b19
_th10_00464b19:
    pop ebx  # 5b
.globl _th10_00464b1a
_th10_00464b1a:
    pop eax  # 58
.globl _th10_00464b1b
_th10_00464b1b:
    ret  # c3
.globl _th10_00464b1c
_th10_00464b1c:
    push edx  # 52
.globl _th10_00464b1d
_th10_00464b1d:
    sub esp, 48  # 83ec30
.globl _th10_00464b20
_th10_00464b20:
    {disp8} fstp tbyte ptr [esp+0x18]  # db7c2418
.globl _th10_00464b24
_th10_00464b24:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464b27
_th10_00464b27:
    {load} xor edx, edx  # 33d2
.globl _th10_00464b29
_th10_00464b29:
    {disp8} {load} mov eax, [esp+6]  # 8b442406
.globl _th10_00464b2d
_th10_00464b2d:
    {noimm8s} test eax, 0x7FFF0000  # a90000ff7f
.globl _th10_00464b32
_th10_00464b32:
    {disp8} je _th10_00464b3e  # 740a
.globl _th10_00464b34
_th10_00464b34:
    {disp32} call _th10_00464916  # e8ddfdffff
.globl _th10_00464b39
_th10_00464b39:
    add esp, 48  # 83c430
.globl _th10_00464b3c
_th10_00464b3c:
    pop edx  # 5a
.globl _th10_00464b3d
_th10_00464b3d:
    ret  # c3
.globl _th10_00464b3e
_th10_00464b3e:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464b41
_th10_00464b41:
    {disp8} fld tbyte ptr [esp+0x18]  # db6c2418
.globl _th10_00464b45
_th10_00464b45:
    {load} mov eax, [esp]  # 8b0424
.globl _th10_00464b48
_th10_00464b48:
    {disp8} {load} or eax, [esp+4]  # 0b442404
.globl _th10_00464b4c
_th10_00464b4c:
    {disp8} je _th10_00464bc7  # 7479
.globl _th10_00464b4e
_th10_00464b4e:
    fxch  # d9c9
.globl _th10_00464b50
_th10_00464b50:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464b54
_th10_00464b54:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464b57
_th10_00464b57:
    fxch  # d9c9
.globl _th10_00464b59
_th10_00464b59:
    or edx, 2  # 83ca02
.globl _th10_00464b5c
_th10_00464b5c:
    {disp8} fnstcw [esp+0x24]  # d97c2424
.globl _th10_00464b60
_th10_00464b60:
    {disp8} {load} mov eax, [esp+0x24]  # 8b442424
.globl _th10_00464b64
_th10_00464b64:
    {noimm8s} or eax, 0x33F  # 0d3f030000
.globl _th10_00464b69
_th10_00464b69:
    {disp8} {store} mov [esp+0x28], eax  # 89442428
.globl _th10_00464b6d
_th10_00464b6d:
    {disp8} fldcw [esp+0x28]  # d96c2428
.globl _th10_00464b71
_th10_00464b71:
    {disp8} {load} mov eax, [esp+0x20]  # 8b442420
.globl _th10_00464b75
_th10_00464b75:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464b7a
_th10_00464b7a:
    {noimm8s} cmp eax, 0x7FBE  # 3dbe7f0000
.globl _th10_00464b7f
_th10_00464b7f:
    {disp8} ja _th10_00464b99  # 7718
.globl _th10_00464b81
_th10_00464b81:
    or edx, 1  # 83ca01
.globl _th10_00464b84
_th10_00464b84:
    fmul qword ptr [_th10_004770d4]  # dc0dd4704700
.globl _th10_00464b8a
_th10_00464b8a:
    {disp8} fstp tbyte ptr [esp+0x18]  # db7c2418
.globl _th10_00464b8e
_th10_00464b8e:
    fmul qword ptr [_th10_004770d4]  # dc0dd4704700
.globl _th10_00464b94
_th10_00464b94:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464b97
_th10_00464b97:
    {disp8} jmp _th10_00464bb9  # eb20
.globl _th10_00464b99
_th10_00464b99:
    {disp8} fnstcw [esp+0x24]  # d97c2424
.globl _th10_00464b9d
_th10_00464b9d:
    {disp8} {load} mov eax, [esp+0x24]  # 8b442424
.globl _th10_00464ba1
_th10_00464ba1:
    {noimm8s} or eax, 0x300  # 0d00030000
.globl _th10_00464ba6
_th10_00464ba6:
    {disp8} {store} mov [esp+0x28], eax  # 89442428
.globl _th10_00464baa
_th10_00464baa:
    {disp8} fldcw [esp+0x28]  # d96c2428
.globl _th10_00464bae
_th10_00464bae:
    fstp st(0)  # ddd8
.globl _th10_00464bb0
_th10_00464bb0:
    fmul qword ptr [_th10_004770d4]  # dc0dd4704700
.globl _th10_00464bb6
_th10_00464bb6:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464bb9
_th10_00464bb9:
    {disp8} fldcw [esp+0x24]  # d96c2424
.globl _th10_00464bbd
_th10_00464bbd:
    {disp32} call _th10_00464916  # e854fdffff
.globl _th10_00464bc2
_th10_00464bc2:
    add esp, 48  # 83c430
.globl _th10_00464bc5
_th10_00464bc5:
    pop edx  # 5a
.globl _th10_00464bc6
_th10_00464bc6:
    ret  # c3
.globl _th10_00464bc7
_th10_00464bc7:
    fprem  # d9f8
.globl _th10_00464bc9
_th10_00464bc9:
    add esp, 48  # 83c430
.globl _th10_00464bcc
_th10_00464bcc:
    pop edx  # 5a
.globl _th10_00464bcd
_th10_00464bcd:
    ret  # c3
.globl _th10_00464bce
_th10_00464bce:
    push eax  # 50
.globl _th10_00464bcf
_th10_00464bcf:
    push ebx  # 53
.globl _th10_00464bd0
_th10_00464bd0:
    push ecx  # 51
.globl _th10_00464bd1
_th10_00464bd1:
    {disp8} {load} mov eax, [esp+0x16]  # 8b442416
.globl _th10_00464bd5
_th10_00464bd5:
    {noimm8s} xor eax, 0x700  # 3500070000
.globl _th10_00464bda
_th10_00464bda:
    {noimm8s} test eax, 0x700  # a900070000
.globl _th10_00464bdf
_th10_00464bdf:
    {disp32} jne _th10_00464d68  # 0f8583010000
.globl _th10_00464be5
_th10_00464be5:
    shr eax, 0x0B  # c1e80b
.globl _th10_00464be8
_th10_00464be8:
    and eax, 15  # 83e00f
.globl _th10_00464beb
_th10_00464beb:
    cmp byte ptr [eax+0x4770BC], 0  # 80b8bc70470000
.globl _th10_00464bf2
_th10_00464bf2:
    {disp32} je _th10_00464d68  # 0f8470010000
.globl _th10_00464bf8
_th10_00464bf8:
    {disp8} {load} mov eax, [esp+0x16]  # 8b442416
.globl _th10_00464bfc
_th10_00464bfc:
    {noimm8s} and eax, 0x7FFF0000  # 250000ff7f
.globl _th10_00464c01
_th10_00464c01:
    {noimm8s} cmp eax, 0x7FFF0000  # 3d0000ff7f
.globl _th10_00464c06
_th10_00464c06:
    {disp32} je _th10_00464d68  # 0f845c010000
.globl _th10_00464c0c
_th10_00464c0c:
    {disp8} {load} mov eax, [esp+0x2E]  # 8b44242e
.globl _th10_00464c10
_th10_00464c10:
    {noimm8s} and eax, 0x7FFF0000  # 250000ff7f
.globl _th10_00464c15
_th10_00464c15:
    {disp32} je _th10_00464d68  # 0f844d010000
.globl _th10_00464c1b
_th10_00464c1b:
    {noimm8s} cmp eax, 0x7FFF0000  # 3d0000ff7f
.globl _th10_00464c20
_th10_00464c20:
    {disp32} je _th10_00464d68  # 0f8442010000
.globl _th10_00464c26
_th10_00464c26:
    {disp8} {load} mov eax, [esp+0x2C]  # 8b44242c
.globl _th10_00464c2a
_th10_00464c2a:
    {load} add eax, eax  # 03c0
.globl _th10_00464c2c
_th10_00464c2c:
    {disp32} jne _th10_00464d68  # 0f8536010000
.globl _th10_00464c32
_th10_00464c32:
    {disp8} {load} mov eax, [esp+0x14]  # 8b442414
.globl _th10_00464c36
_th10_00464c36:
    {load} add eax, eax  # 03c0
.globl _th10_00464c38
_th10_00464c38:
    {disp32} jne _th10_00464d68  # 0f852a010000
.globl _th10_00464c3e
_th10_00464c3e:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464c42
_th10_00464c42:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464c47
_th10_00464c47:
    add eax, 63  # 83c03f
.globl _th10_00464c4a
_th10_00464c4a:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464c4e
_th10_00464c4e:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464c54
_th10_00464c54:
    {load} sub ebx, eax  # 2bd8
.globl _th10_00464c56
_th10_00464c56:
    {disp8} ja _th10_00464cb6  # 775e
.globl _th10_00464c58
_th10_00464c58:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464c5c
_th10_00464c5c:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464c61
_th10_00464c61:
    add eax, 10  # 83c00a
.globl _th10_00464c64
_th10_00464c64:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464c68
_th10_00464c68:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464c6e
_th10_00464c6e:
    {load} sub ebx, eax  # 2bd8
.globl _th10_00464c70
_th10_00464c70:
    {disp32} js _th10_00464d68  # 0f88f2000000
.globl _th10_00464c76
_th10_00464c76:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464c7a
_th10_00464c7a:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464c7e
_th10_00464c7e:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464c82
_th10_00464c82:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464c88
_th10_00464c88:
    {load} mov ecx, ebx  # 8bcb
.globl _th10_00464c8a
_th10_00464c8a:
    {load} sub ebx, eax  # 2bd8
.globl _th10_00464c8c
_th10_00464c8c:
    and ebx, 7  # 83e307
.globl _th10_00464c8f
_th10_00464c8f:
    or ebx, 4  # 83cb04
.globl _th10_00464c92
_th10_00464c92:
    {load} sub ecx, ebx  # 2bcb
.globl _th10_00464c94
_th10_00464c94:
    {load} mov ebx, eax  # 8bd8
.globl _th10_00464c96
_th10_00464c96:
    {noimm8s} and ebx, 0x8000  # 81e300800000
.globl _th10_00464c9c
_th10_00464c9c:
    {load} or ecx, ebx  # 0bcb
.globl _th10_00464c9e
_th10_00464c9e:
    {disp8} {store} mov [esp+0x18], ecx  # 894c2418
.globl _th10_00464ca2
_th10_00464ca2:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464ca6
_th10_00464ca6:
    {disp8} {store} mov [esp+0x18], eax  # 89442418
.globl _th10_00464caa
_th10_00464caa:
    fxch  # d9c9
.globl _th10_00464cac
_th10_00464cac:
    fprem  # d9f8
.globl _th10_00464cae
_th10_00464cae:
    {disp8} fstp tbyte ptr [esp+0x28]  # db7c2428
.globl _th10_00464cb2
_th10_00464cb2:
    fstp st(0)  # ddd8
.globl _th10_00464cb4
_th10_00464cb4:
    {disp8} jmp _th10_00464c58  # eba2
.globl _th10_00464cb6
_th10_00464cb6:
    {noimm8s} test ebx, 2  # f7c302000000
.globl _th10_00464cbc
_th10_00464cbc:
    {disp8} jne _th10_00464cc6  # 7508
.globl _th10_00464cbe
_th10_00464cbe:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464cc2
_th10_00464cc2:
    {disp8} fstp tbyte ptr [esp+0x1C]  # db7c241c
.globl _th10_00464cc6
_th10_00464cc6:
    {disp8} fnstcw [esp+0x34]  # d97c2434
.globl _th10_00464cca
_th10_00464cca:
    {disp8} {load} mov eax, [esp+0x34]  # 8b442434
.globl _th10_00464cce
_th10_00464cce:
    {noimm8s} or eax, 0x33F  # 0d3f030000
.globl _th10_00464cd3
_th10_00464cd3:
    {disp8} {store} mov [esp+0x38], eax  # 89442438
.globl _th10_00464cd7
_th10_00464cd7:
    {disp8} fldcw [esp+0x38]  # d96c2438
.globl _th10_00464cdb
_th10_00464cdb:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464cdf
_th10_00464cdf:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464ce4
_th10_00464ce4:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464ce8
_th10_00464ce8:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464cee
_th10_00464cee:
    {load} sub ebx, eax  # 2bd8
.globl _th10_00464cf0
_th10_00464cf0:
    and ebx, 63  # 83e33f
.globl _th10_00464cf3
_th10_00464cf3:
    or ebx, 32  # 83cb20
.globl _th10_00464cf6
_th10_00464cf6:
    add ebx, 1  # 83c301
.globl _th10_00464cf9
_th10_00464cf9:
    {load} mov ecx, ebx  # 8bcb
.globl _th10_00464cfb
_th10_00464cfb:
    {disp8} {load} mov eax, [esp+0x18]  # 8b442418
.globl _th10_00464cff
_th10_00464cff:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464d03
_th10_00464d03:
    {noimm8s} and ebx, 0x7FFF  # 81e3ff7f0000
.globl _th10_00464d09
_th10_00464d09:
    {noimm8s} and eax, 0x8000  # 2500800000
.globl _th10_00464d0e
_th10_00464d0e:
    {load} or ebx, eax  # 0bd8
.globl _th10_00464d10
_th10_00464d10:
    {disp8} {store} mov [esp+0x18], ebx  # 895c2418
.globl _th10_00464d14
_th10_00464d14:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464d18
_th10_00464d18:
    fabs  # d9e1
.globl _th10_00464d1a
_th10_00464d1a:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464d1e
_th10_00464d1e:
    fabs  # d9e1
.globl _th10_00464d20
_th10_00464d20:
    fcom  # d8d1
.globl _th10_00464d22
_th10_00464d22:
    fnstsw ax  # dfe0
.globl _th10_00464d24
_th10_00464d24:
    {noimm8s} and eax, 0x100  # 2500010000
.globl _th10_00464d29
_th10_00464d29:
    {disp8} jne _th10_00464d2d  # 7502
.globl _th10_00464d2b
_th10_00464d2b:
    fsub st(1)  # d8e1
.globl _th10_00464d2d
_th10_00464d2d:
    fxch  # d9c9
.globl _th10_00464d2f
_th10_00464d2f:
    fmul qword ptr [_th10_004770ec]  # dc0dec704700
.globl _th10_00464d35
_th10_00464d35:
    fxch  # d9c9
.globl _th10_00464d37
_th10_00464d37:
    sub ecx, 1  # 83e901
.globl _th10_00464d3a
_th10_00464d3a:
    {disp8} jne _th10_00464d20  # 75e4
.globl _th10_00464d3c
_th10_00464d3c:
    {disp8} {load} mov ebx, [esp+0x30]  # 8b5c2430
.globl _th10_00464d40
_th10_00464d40:
    {disp8} fstp tbyte ptr [esp+0x28]  # db7c2428
.globl _th10_00464d44
_th10_00464d44:
    fstp st(0)  # ddd8
.globl _th10_00464d46
_th10_00464d46:
    {disp8} fld tbyte ptr [esp+0x1C]  # db6c241c
.globl _th10_00464d4a
_th10_00464d4a:
    fld tbyte ptr [_th10_004770f4]  # db2df4704700
.globl _th10_00464d50
_th10_00464d50:
    fprem1  # d9f5
.globl _th10_00464d52
_th10_00464d52:
    fstp st(0)  # ddd8
.globl _th10_00464d54
_th10_00464d54:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464d58
_th10_00464d58:
    {disp8} fldcw [esp+0x34]  # d96c2434
.globl _th10_00464d5c
_th10_00464d5c:
    {noimm8s} and ebx, 0x8000  # 81e300800000
.globl _th10_00464d62
_th10_00464d62:
    {disp8} je _th10_00464d72  # 740e
.globl _th10_00464d64
_th10_00464d64:
    fchs  # d9e0
.globl _th10_00464d66
_th10_00464d66:
    {disp8} jmp _th10_00464d72  # eb0a
.globl _th10_00464d68
_th10_00464d68:
    {disp8} fld tbyte ptr [esp+0x10]  # db6c2410
.globl _th10_00464d6c
_th10_00464d6c:
    {disp8} fld tbyte ptr [esp+0x28]  # db6c2428
.globl _th10_00464d70
_th10_00464d70:
    fprem1  # d9f5
.globl _th10_00464d72
_th10_00464d72:
    {noimm8s} test edx, 3  # f7c203000000
.globl _th10_00464d78
_th10_00464d78:
    {disp8} je _th10_00464dd0  # 7456
.globl _th10_00464d7a
_th10_00464d7a:
    {disp8} fnstsw [esp+0x3C]  # dd7c243c
.globl _th10_00464d7e
_th10_00464d7e:
    {noimm8s} test edx, 1  # f7c201000000
.globl _th10_00464d84
_th10_00464d84:
    {disp8} je _th10_00464da5  # 741f
.globl _th10_00464d86
_th10_00464d86:
    {disp8} fnstcw [esp+0x34]  # d97c2434
.globl _th10_00464d8a
_th10_00464d8a:
    {disp8} {load} mov eax, [esp+0x34]  # 8b442434
.globl _th10_00464d8e
_th10_00464d8e:
    {noimm8s} or eax, 0x300  # 0d00030000
.globl _th10_00464d93
_th10_00464d93:
    {disp8} {store} mov [esp+0x38], eax  # 89442438
.globl _th10_00464d97
_th10_00464d97:
    {disp8} fldcw [esp+0x38]  # d96c2438
.globl _th10_00464d9b
_th10_00464d9b:
    fmul qword ptr [_th10_004770dc]  # dc0ddc704700
.globl _th10_00464da1
_th10_00464da1:
    {disp8} fldcw [esp+0x34]  # d96c2434
.globl _th10_00464da5
_th10_00464da5:
    {disp8} {load} mov eax, [esp+0x3C]  # 8b44243c
.globl _th10_00464da9
_th10_00464da9:
    fxch  # d9c9
.globl _th10_00464dab
_th10_00464dab:
    fstp st(0)  # ddd8
.globl _th10_00464dad
_th10_00464dad:
    {disp8} fld tbyte ptr [esp+0x1C]  # db6c241c
.globl _th10_00464db1
_th10_00464db1:
    fxch  # d9c9
.globl _th10_00464db3
_th10_00464db3:
    {noimm8s} and eax, 0x4300  # 2500430000
.globl _th10_00464db8
_th10_00464db8:
    sub esp, 28  # 83ec1c
.globl _th10_00464dbb
_th10_00464dbb:
    fnstenv [esp]  # d93424
.globl _th10_00464dbe
_th10_00464dbe:
    {disp8} {noimm8s} and dword ptr [esp+4], 0x0BCFF  # 81642404ffbc0000
.globl _th10_00464dc6
_th10_00464dc6:
    {disp8} {store} or [esp+4], eax  # 09442404
.globl _th10_00464dca
_th10_00464dca:
    fldenv [esp]  # d92424
.globl _th10_00464dcd
_th10_00464dcd:
    add esp, 28  # 83c41c
.globl _th10_00464dd0
_th10_00464dd0:
    pop ecx  # 59
.globl _th10_00464dd1
_th10_00464dd1:
    pop ebx  # 5b
.globl _th10_00464dd2
_th10_00464dd2:
    pop eax  # 58
.globl _th10_00464dd3
_th10_00464dd3:
    ret  # c3
.globl _th10_00464dd4
_th10_00464dd4:
    push edx  # 52
.globl _th10_00464dd5
_th10_00464dd5:
    sub esp, 48  # 83ec30
.globl _th10_00464dd8
_th10_00464dd8:
    {disp8} fstp tbyte ptr [esp+0x18]  # db7c2418
.globl _th10_00464ddc
_th10_00464ddc:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464ddf
_th10_00464ddf:
    {noimm8s} mov edx, 0  # ba00000000
.globl _th10_00464de4
_th10_00464de4:
    {disp8} {load} mov eax, [esp+6]  # 8b442406
.globl _th10_00464de8
_th10_00464de8:
    {noimm8s} test eax, 0x7FFF0000  # a90000ff7f
.globl _th10_00464ded
_th10_00464ded:
    {disp8} je _th10_00464df9  # 740a
.globl _th10_00464def
_th10_00464def:
    {disp32} call _th10_00464bce  # e8dafdffff
.globl _th10_00464df4
_th10_00464df4:
    add esp, 48  # 83c430
.globl _th10_00464df7
_th10_00464df7:
    pop edx  # 5a
.globl _th10_00464df8
_th10_00464df8:
    ret  # c3
.globl _th10_00464df9
_th10_00464df9:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464dfc
_th10_00464dfc:
    {disp8} fld tbyte ptr [esp+0x18]  # db6c2418
.globl _th10_00464e00
_th10_00464e00:
    {load} mov eax, [esp]  # 8b0424
.globl _th10_00464e03
_th10_00464e03:
    {disp8} {load} or eax, [esp+4]  # 0b442404
.globl _th10_00464e07
_th10_00464e07:
    {disp8} je _th10_00464e82  # 7479
.globl _th10_00464e09
_th10_00464e09:
    fxch  # d9c9
.globl _th10_00464e0b
_th10_00464e0b:
    {disp8} fstp tbyte ptr [esp+0x0C]  # db7c240c
.globl _th10_00464e0f
_th10_00464e0f:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464e12
_th10_00464e12:
    fxch  # d9c9
.globl _th10_00464e14
_th10_00464e14:
    or edx, 2  # 83ca02
.globl _th10_00464e17
_th10_00464e17:
    {disp8} fnstcw [esp+0x24]  # d97c2424
.globl _th10_00464e1b
_th10_00464e1b:
    {disp8} {load} mov eax, [esp+0x24]  # 8b442424
.globl _th10_00464e1f
_th10_00464e1f:
    {noimm8s} or eax, 0x33F  # 0d3f030000
.globl _th10_00464e24
_th10_00464e24:
    {disp8} {store} mov [esp+0x28], eax  # 89442428
.globl _th10_00464e28
_th10_00464e28:
    {disp8} fldcw [esp+0x28]  # d96c2428
.globl _th10_00464e2c
_th10_00464e2c:
    {disp8} {load} mov eax, [esp+0x20]  # 8b442420
.globl _th10_00464e30
_th10_00464e30:
    {noimm8s} and eax, 0x7FFF  # 25ff7f0000
.globl _th10_00464e35
_th10_00464e35:
    {noimm8s} cmp eax, 0x7FBE  # 3dbe7f0000
.globl _th10_00464e3a
_th10_00464e3a:
    {disp8} ja _th10_00464e54  # 7718
.globl _th10_00464e3c
_th10_00464e3c:
    or edx, 1  # 83ca01
.globl _th10_00464e3f
_th10_00464e3f:
    fmul qword ptr [_th10_004770d4]  # dc0dd4704700
.globl _th10_00464e45
_th10_00464e45:
    {disp8} fstp tbyte ptr [esp+0x18]  # db7c2418
.globl _th10_00464e49
_th10_00464e49:
    fmul qword ptr [_th10_004770d4]  # dc0dd4704700
.globl _th10_00464e4f
_th10_00464e4f:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464e52
_th10_00464e52:
    {disp8} jmp _th10_00464e74  # eb20
.globl _th10_00464e54
_th10_00464e54:
    {disp8} fnstcw [esp+0x24]  # d97c2424
.globl _th10_00464e58
_th10_00464e58:
    {disp8} {load} mov eax, [esp+0x24]  # 8b442424
.globl _th10_00464e5c
_th10_00464e5c:
    {noimm8s} or eax, 0x300  # 0d00030000
.globl _th10_00464e61
_th10_00464e61:
    {disp8} {store} mov [esp+0x28], eax  # 89442428
.globl _th10_00464e65
_th10_00464e65:
    {disp8} fldcw [esp+0x28]  # d96c2428
.globl _th10_00464e69
_th10_00464e69:
    fstp st(0)  # ddd8
.globl _th10_00464e6b
_th10_00464e6b:
    fmul qword ptr [_th10_004770d4]  # dc0dd4704700
.globl _th10_00464e71
_th10_00464e71:
    fstp tbyte ptr [esp]  # db3c24
.globl _th10_00464e74
_th10_00464e74:
    {disp8} fldcw [esp+0x24]  # d96c2424
.globl _th10_00464e78
_th10_00464e78:
    {disp32} call _th10_00464bce  # e851fdffff
.globl _th10_00464e7d
_th10_00464e7d:
    add esp, 48  # 83c430
.globl _th10_00464e80
_th10_00464e80:
    pop edx  # 5a
.globl _th10_00464e81
_th10_00464e81:
    ret  # c3
.globl _th10_00464e82
_th10_00464e82:
    fprem  # d9f8
.globl _th10_00464e84
_th10_00464e84:
    add esp, 48  # 83c430
.globl _th10_00464e87
_th10_00464e87:
    pop edx  # 5a
.globl _th10_00464e88
_th10_00464e88:
    ret  # c3
.globl _th10_00464e89
_th10_00464e89:
    {disp32} call _th10_00464b1c  # e88efcffff
.globl _th10_00464e8e
_th10_00464e8e:
    ret  # c3
.globl _th10_00464e8f
_th10_00464e8f:
    {disp32} call _th10_00464dd4  # e840ffffff
.globl _th10_00464e94
_th10_00464e94:
    ret  # c3
.globl _th10_00464e95
_th10_00464e95:
    fpatan  # d9f3
.globl _th10_00464e97
_th10_00464e97:
    ret  # c3
.globl _th10_00464e98
_th10_00464e98:
    fptan  # d9f2
.globl _th10_00464e9a
_th10_00464e9a:
    ret  # c3
# padding 00464e9b..00464e9f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 5, 1, 0xcc
.globl _th10_00464ea0
_th10_00464ea0:
    push ebp  # 55
.globl _th10_00464ea1
_th10_00464ea1:
    {load} mov ebp, esp  # 8bec
.globl _th10_00464ea3
_th10_00464ea3:
    add esp, -32  # 83c4e0
.globl _th10_00464ea6
_th10_00464ea6:
    {disp8} {store} mov [ebp-0x20], eax  # 8945e0
.globl _th10_00464ea9
_th10_00464ea9:
    {disp8} {load} mov eax, [ebp+0x18]  # 8b4518
.globl _th10_00464eac
_th10_00464eac:
    {disp8} {store} mov [ebp-0x10], eax  # 8945f0
.globl _th10_00464eaf
_th10_00464eaf:
    {disp8} {load} mov eax, [ebp+0x1C]  # 8b451c
.globl _th10_00464eb2
_th10_00464eb2:
    {disp8} {store} mov [ebp-0x0C], eax  # 8945f4
.globl _th10_00464eb5
_th10_00464eb5:
    {disp8} jmp _th10_00464ec0  # eb09
.globl _th10_00464eb7
_th10_00464eb7:
    push ebp  # 55
.globl _th10_00464eb8
_th10_00464eb8:
    {load} mov ebp, esp  # 8bec
.globl _th10_00464eba
_th10_00464eba:
    add esp, -32  # 83c4e0
.globl _th10_00464ebd
_th10_00464ebd:
    {disp8} {store} mov [ebp-0x20], eax  # 8945e0
.globl _th10_00464ec0
_th10_00464ec0:
    {disp8} fstp qword ptr [ebp-8]  # dd5df8
.globl _th10_00464ec3
_th10_00464ec3:
    {disp8} {store} mov [ebp-0x1C], ecx  # 894de4
.globl _th10_00464ec6
_th10_00464ec6:
    {disp8} {load} mov eax, [ebp+0x10]  # 8b4510
.globl _th10_00464ec9
_th10_00464ec9:
    {disp8} {load} mov ecx, [ebp+0x14]  # 8b4d14
.globl _th10_00464ecc
_th10_00464ecc:
    {disp8} {store} mov [ebp-0x18], eax  # 8945e8
.globl _th10_00464ecf
_th10_00464ecf:
    {disp8} {store} mov [ebp-0x14], ecx  # 894dec
.globl _th10_00464ed2
_th10_00464ed2:
    {disp8} lea eax, [ebp+8]  # 8d4508
.globl _th10_00464ed5
_th10_00464ed5:
    {disp8} lea ecx, [ebp-0x20]  # 8d4de0
.globl _th10_00464ed8
_th10_00464ed8:
    push eax  # 50
.globl _th10_00464ed9
_th10_00464ed9:
    push ecx  # 51
.globl _th10_00464eda
_th10_00464eda:
    push edx  # 52
.globl _th10_00464edb
_th10_00464edb:
    {disp32} call _th10_0046508c  # e8ac010000
.globl _th10_00464ee0
_th10_00464ee0:
    add esp, 12  # 83c40c
.globl _th10_00464ee3
_th10_00464ee3:
    {disp8} fld qword ptr [ebp-8]  # dd45f8
.globl _th10_00464ee6
_th10_00464ee6:
    {disp8} {noimm8s} cmp word ptr [ebp+8], 0x27F  # 66817d087f02
.globl _th10_00464eec
_th10_00464eec:
    {disp8} je _th10_00464ef1  # 7403
.globl _th10_00464eee
_th10_00464eee:
    {disp8} fldcw [ebp+8]  # d96d08
.globl _th10_00464ef1
_th10_00464ef1:
    leave  # c9
.globl _th10_00464ef2
_th10_00464ef2:
    ret  # c3
# padding 00464ef3..00464eff: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 13, 1, 0xcc
.globl _th10_00464f00
_th10_00464f00:
    fld st(0)  # d9c0
.globl _th10_00464f02
_th10_00464f02:
    frndint  # d9fc
.globl _th10_00464f04
_th10_00464f04:
    fsubr st(1), st  # dce1
.globl _th10_00464f06
_th10_00464f06:
    fxch  # d9c9
.globl _th10_00464f08
_th10_00464f08:
    fchs  # d9e0
.globl _th10_00464f0a
_th10_00464f0a:
    f2xm1  # d9f0
.globl _th10_00464f0c
_th10_00464f0c:
    fld1  # d9e8
.globl _th10_00464f0e
_th10_00464f0e:
    faddp  # dec1
.globl _th10_00464f10
_th10_00464f10:
    fscale  # d9fd
.globl _th10_00464f12
_th10_00464f12:
    fstp st(1)  # ddd9
.globl _th10_00464f14
_th10_00464f14:
    ret  # c3
.globl _th10_00464f15
_th10_00464f15:
    {disp8} {load} mov edx, [esp+4]  # 8b542404
.globl _th10_00464f19
_th10_00464f19:
    {noimm8s} and edx, 0x300  # 81e200030000
.globl _th10_00464f1f
_th10_00464f1f:
    or edx, 127  # 83ca7f
.globl _th10_00464f22
_th10_00464f22:
    {disp8} {store} mov [esp+6], dx  # 6689542406
.globl _th10_00464f27
_th10_00464f27:
    {disp8} fldcw [esp+6]  # d96c2406
.globl _th10_00464f2b
_th10_00464f2b:
    ret  # c3
.globl _th10_00464f2c
_th10_00464f2c:
    {noimm8s} test eax, 0x80000  # a900000800
.globl _th10_00464f31
_th10_00464f31:
    {disp8} je _th10_00464f39  # 7406
.globl _th10_00464f33
_th10_00464f33:
    {noimm8s} mov eax, 7  # b807000000
.globl _th10_00464f38
_th10_00464f38:
    ret  # c3
.globl _th10_00464f39
_th10_00464f39:
    fadd qword ptr [_th10_00470d90]  # dc05900d4700
.globl _th10_00464f3f
_th10_00464f3f:
    {noimm8s} mov eax, 1  # b801000000
.globl _th10_00464f44
_th10_00464f44:
    ret  # c3
.globl _th10_00464f45
_th10_00464f45:
    {disp8} {load} mov eax, [edx+4]  # 8b4204
.globl _th10_00464f48
_th10_00464f48:
    {noimm8s} and eax, 0x7FF00000  # 250000f07f
.globl _th10_00464f4d
_th10_00464f4d:
    {noimm8s} cmp eax, 0x7FF00000  # 3d0000f07f
.globl _th10_00464f52
_th10_00464f52:
    {disp8} je _th10_00464f57  # 7403
.globl _th10_00464f54
_th10_00464f54:
    fld qword ptr [edx]  # dd02
.globl _th10_00464f56
_th10_00464f56:
    ret  # c3
.globl _th10_00464f57
_th10_00464f57:
    {disp8} {load} mov eax, [edx+4]  # 8b4204
.globl _th10_00464f5a
_th10_00464f5a:
    sub esp, 10  # 83ec0a
.globl _th10_00464f5d
_th10_00464f5d:
    {noimm8s} or eax, 0x7FFF0000  # 0d0000ff7f
.globl _th10_00464f62
_th10_00464f62:
    {disp8} {store} mov [esp+6], eax  # 89442406
.globl _th10_00464f66
_th10_00464f66:
    {disp8} {load} mov eax, [edx+4]  # 8b4204
.globl _th10_00464f69
_th10_00464f69:
    {load} mov ecx, [edx]  # 8b0a
.globl _th10_00464f6b
_th10_00464f6b:
    shld eax, ecx, 0x0B  # 0fa4c80b
.globl _th10_00464f6f
_th10_00464f6f:
    shl ecx, 0x0B  # c1e10b
.globl _th10_00464f72
_th10_00464f72:
    {disp8} {store} mov [esp+4], eax  # 89442404
.globl _th10_00464f76
_th10_00464f76:
    {store} mov [esp], ecx  # 890c24
.globl _th10_00464f79
_th10_00464f79:
    fld tbyte ptr [esp]  # db2c24
.globl _th10_00464f7c
_th10_00464f7c:
    add esp, 10  # 83c40a
.globl _th10_00464f7f
_th10_00464f7f:
    {noimm8s} test eax, 0  # a900000000
.globl _th10_00464f84
_th10_00464f84:
    {disp8} {load} mov eax, [edx+4]  # 8b4204
.globl _th10_00464f87
_th10_00464f87:
    ret  # c3
.globl _th10_00464f88
_th10_00464f88:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_00464f8c
_th10_00464f8c:
    {noimm8s} and eax, 0x7FF00000  # 250000f07f
.globl _th10_00464f91
_th10_00464f91:
    {noimm8s} cmp eax, 0x7FF00000  # 3d0000f07f
.globl _th10_00464f96
_th10_00464f96:
    {disp8} je _th10_00464f99  # 7401
.globl _th10_00464f98
_th10_00464f98:
    ret  # c3
.globl _th10_00464f99
_th10_00464f99:
    {disp8} {load} mov eax, [esp+8]  # 8b442408
.globl _th10_00464f9d
_th10_00464f9d:
    ret  # c3
.globl _th10_00464f9e
_th10_00464f9e:
    {noimm8s} cmp word ptr [esp], 0x27F  # 66813c247f02
.globl _th10_00464fa4
_th10_00464fa4:
    {disp8} je _th10_00464fa9  # 7403
.globl _th10_00464fa6
_th10_00464fa6:
    fldcw [esp]  # d92c24
.globl _th10_00464fa9
_th10_00464fa9:
    pop edx  # 5a
.globl _th10_00464faa
_th10_00464faa:
    ret  # c3
.globl _th10_00464fab
_th10_00464fab:
    {load} mov ax, [esp]  # 668b0424
.globl _th10_00464faf
_th10_00464faf:
    {noimm8s} cmp ax, 0x27F  # 663d7f02
.globl _th10_00464fb3
_th10_00464fb3:
    {disp8} je _th10_00464fd3  # 741e
.globl _th10_00464fb5
_th10_00464fb5:
    and ax, 32  # 6683e020
.globl _th10_00464fb9
_th10_00464fb9:
    {disp8} je _th10_00464fd0  # 7415
.globl _th10_00464fbb
_th10_00464fbb:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00464fbe
_th10_00464fbe:
    and ax, 32  # 6683e020
.globl _th10_00464fc2
_th10_00464fc2:
    {disp8} je _th10_00464fd0  # 740c
.globl _th10_00464fc4
_th10_00464fc4:
    {noimm8s} mov eax, 8  # b808000000
.globl _th10_00464fc9
_th10_00464fc9:
    {disp32} call _th10_00464eb7  # e8e9feffff
.globl _th10_00464fce
_th10_00464fce:
    pop edx  # 5a
.globl _th10_00464fcf
_th10_00464fcf:
    ret  # c3
.globl _th10_00464fd0
_th10_00464fd0:
    fldcw [esp]  # d92c24
.globl _th10_00464fd3
_th10_00464fd3:
    pop edx  # 5a
.globl _th10_00464fd4
_th10_00464fd4:
    ret  # c3
.globl _th10_00464fd5
_th10_00464fd5:
    sub esp, 8  # 83ec08
.globl _th10_00464fd8
_th10_00464fd8:
    fst qword ptr [esp]  # dd1424
.globl _th10_00464fdb
_th10_00464fdb:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00464fdf
_th10_00464fdf:
    add esp, 8  # 83c408
.globl _th10_00464fe2
_th10_00464fe2:
    {noimm8s} and eax, 0x7FF00000  # 250000f07f
.globl _th10_00464fe7
_th10_00464fe7:
    {disp8} jmp _th10_00464ffd  # eb14
.globl _th10_00464fe9
_th10_00464fe9:
    sub esp, 8  # 83ec08
.globl _th10_00464fec
_th10_00464fec:
    fst qword ptr [esp]  # dd1424
.globl _th10_00464fef
_th10_00464fef:
    {disp8} {load} mov eax, [esp+4]  # 8b442404
.globl _th10_00464ff3
_th10_00464ff3:
    add esp, 8  # 83c408
.globl _th10_00464ff6
_th10_00464ff6:
    {noimm8s} and eax, 0x7FF00000  # 250000f07f
.globl _th10_00464ffb
_th10_00464ffb:
    {disp8} je _th10_0046503a  # 743d
.globl _th10_00464ffd
_th10_00464ffd:
    {noimm8s} cmp eax, 0x7FF00000  # 3d0000f07f
.globl _th10_00465002
_th10_00465002:
    {disp8} je _th10_00465063  # 745f
.globl _th10_00465004
_th10_00465004:
    {load} mov ax, [esp]  # 668b0424
.globl _th10_00465008
_th10_00465008:
    {noimm8s} cmp ax, 0x27F  # 663d7f02
.globl _th10_0046500c
_th10_0046500c:
    {disp8} je _th10_00465038  # 742a
.globl _th10_0046500e
_th10_0046500e:
    and ax, 32  # 6683e020
.globl _th10_00465012
_th10_00465012:
    {disp8} jne _th10_00465035  # 7521
.globl _th10_00465014
_th10_00465014:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00465017
_th10_00465017:
    and ax, 32  # 6683e020
.globl _th10_0046501b
_th10_0046501b:
    {disp8} je _th10_00465035  # 7418
.globl _th10_0046501d
_th10_0046501d:
    {noimm8s} mov eax, 8  # b808000000
.globl _th10_00465022
_th10_00465022:
    cmp edx, 29  # 83fa1d
.globl _th10_00465025
_th10_00465025:
    {disp8} je _th10_0046502e  # 7407
.globl _th10_00465027
_th10_00465027:
    {disp32} call _th10_00464eb7  # e88bfeffff
.globl _th10_0046502c
_th10_0046502c:
    pop edx  # 5a
.globl _th10_0046502d
_th10_0046502d:
    ret  # c3
.globl _th10_0046502e
_th10_0046502e:
    {disp32} call _th10_00464ea0  # e86dfeffff
.globl _th10_00465033
_th10_00465033:
    pop edx  # 5a
.globl _th10_00465034
_th10_00465034:
    ret  # c3
.globl _th10_00465035
_th10_00465035:
    fldcw [esp]  # d92c24
.globl _th10_00465038
_th10_00465038:
    pop edx  # 5a
.globl _th10_00465039
_th10_00465039:
    ret  # c3
.globl _th10_0046503a
_th10_0046503a:
    fld qword ptr [_th10_00470dbc]  # dd05bc0d4700
.globl _th10_00465040
_th10_00465040:
    fxch  # d9c9
.globl _th10_00465042
_th10_00465042:
    fscale  # d9fd
.globl _th10_00465044
_th10_00465044:
    fstp st(1)  # ddd9
.globl _th10_00465046
_th10_00465046:
    fld st(0)  # d9c0
.globl _th10_00465048
_th10_00465048:
    fabs  # d9e1
.globl _th10_0046504a
_th10_0046504a:
    fcomp qword ptr [_th10_00470dac]  # dc1dac0d4700
.globl _th10_00465050
_th10_00465050:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_00465053
_th10_00465053:
    sahf  # 9e
.globl _th10_00465054
_th10_00465054:
    {noimm8s} mov eax, 4  # b804000000
.globl _th10_00465059
_th10_00465059:
    {disp8} jae _th10_00465022  # 73c7
.globl _th10_0046505b
_th10_0046505b:
    fmul qword ptr [_th10_00470dcc]  # dc0dcc0d4700
.globl _th10_00465061
_th10_00465061:
    {disp8} jmp _th10_00465022  # ebbf
.globl _th10_00465063
_th10_00465063:
    fld qword ptr [_th10_00470db4]  # dd05b40d4700
.globl _th10_00465069
_th10_00465069:
    fxch  # d9c9
.globl _th10_0046506b
_th10_0046506b:
    fscale  # d9fd
.globl _th10_0046506d
_th10_0046506d:
    fstp st(1)  # ddd9
.globl _th10_0046506f
_th10_0046506f:
    fld st(0)  # d9c0
.globl _th10_00465071
_th10_00465071:
    fabs  # d9e1
.globl _th10_00465073
_th10_00465073:
    fcomp qword ptr [_th10_00470da4]  # dc1da40d4700
.globl _th10_00465079
_th10_00465079:
    fwait
fnstsw ax  # 9bdfe0
.globl _th10_0046507c
_th10_0046507c:
    sahf  # 9e
.globl _th10_0046507d
_th10_0046507d:
    {noimm8s} mov eax, 3  # b803000000
.globl _th10_00465082
_th10_00465082:
    {disp8} jbe _th10_00465022  # 769e
.globl _th10_00465084
_th10_00465084:
    fmul qword ptr [_th10_00470dc4]  # dc0dc40d4700
.globl _th10_0046508a
_th10_0046508a:
    {disp8} jmp _th10_00465022  # eb96
.globl _th10_0046508c
_th10_0046508c:
    push ebp  # 55
.globl _th10_0046508d
_th10_0046508d:
    {load} mov ebp, esp  # 8bec
.globl _th10_0046508f
_th10_0046508f:
    and esp, -16  # 83e4f0
.globl _th10_00465092
_th10_00465092:
    {noimm8s} sub esp, 0x84  # 81ec84000000
.globl _th10_00465098
_th10_00465098:
    mov eax, [_th10_00473660]  # a160364700
.globl _th10_0046509d
_th10_0046509d:
    {load} xor eax, ebp  # 33c5
.globl _th10_0046509f
_th10_0046509f:
    {store} mov [esp+0x80], eax  # 89842480000000
.globl _th10_004650a6
_th10_004650a6:
    {disp8} {load} mov eax, [ebp+0x10]  # 8b4510
.globl _th10_004650a9
_th10_004650a9:
    movzx ecx, word ptr [eax]  # 0fb708
.globl _th10_004650ac
_th10_004650ac:
    push ebx  # 53
.globl _th10_004650ad
_th10_004650ad:
    push esi  # 56
.globl _th10_004650ae
_th10_004650ae:
    {disp8} {load} mov esi, [ebp+0x0C]  # 8b750c
.globl _th10_004650b1
_th10_004650b1:
    {load} mov eax, [esi]  # 8b06
.globl _th10_004650b3
_th10_004650b3:
    dec eax  # 48
.globl _th10_004650b4
_th10_004650b4:
    push edi  # 57
.globl _th10_004650b5
_th10_004650b5:
    {disp8} {store} mov [esp+0x0C], ecx  # 894c240c
.globl _th10_004650b9
_th10_004650b9:
    {disp8} je _th10_004650e6  # 742b
.globl _th10_004650bb
_th10_004650bb:
    dec eax  # 48
.globl _th10_004650bc
_th10_004650bc:
    {disp8} je _th10_004650e2  # 7424
.globl _th10_004650be
_th10_004650be:
    dec eax  # 48
.globl _th10_004650bf
_th10_004650bf:
    {disp8} je _th10_004650de  # 741d
.globl _th10_004650c1
_th10_004650c1:
    dec eax  # 48
.globl _th10_004650c2
_th10_004650c2:
    {disp8} je _th10_004650da  # 7416
.globl _th10_004650c4
_th10_004650c4:
    dec eax  # 48
.globl _th10_004650c5
_th10_004650c5:
    {disp8} je _th10_004650e6  # 741f
.globl _th10_004650c7
_th10_004650c7:
    dec eax  # 48
.globl _th10_004650c8
_th10_004650c8:
    dec eax  # 48
.globl _th10_004650c9
_th10_004650c9:
    {disp8} je _th10_004650d2  # 7407
.globl _th10_004650cb
_th10_004650cb:
    dec eax  # 48
.globl _th10_004650cc
_th10_004650cc:
    {disp8} jne _th10_00465142  # 7574
.globl _th10_004650ce
_th10_004650ce:
    push 16  # 6a10
.globl _th10_004650d0
_th10_004650d0:
    {disp8} jmp _th10_004650e8  # eb16
.globl _th10_004650d2
_th10_004650d2:
    {noimm8s} mov dword ptr [esi], 1  # c70601000000
.globl _th10_004650d8
_th10_004650d8:
    {disp8} jmp _th10_00465142  # eb68
.globl _th10_004650da
_th10_004650da:
    push 18  # 6a12
.globl _th10_004650dc
_th10_004650dc:
    {disp8} jmp _th10_004650e8  # eb0a
.globl _th10_004650de
_th10_004650de:
    push 17  # 6a11
.globl _th10_004650e0
_th10_004650e0:
    {disp8} jmp _th10_004650e8  # eb06
.globl _th10_004650e2
_th10_004650e2:
    push 4  # 6a04
.globl _th10_004650e4
_th10_004650e4:
    {disp8} jmp _th10_004650e8  # eb02
.globl _th10_004650e6
_th10_004650e6:
    push 8  # 6a08
.globl _th10_004650e8
_th10_004650e8:
    pop ebx  # 5b
.globl _th10_004650e9
_th10_004650e9:
    push ecx  # 51
.globl _th10_004650ea
_th10_004650ea:
    {disp8} lea edi, [esi+0x18]  # 8d7e18
.globl _th10_004650ed
_th10_004650ed:
    push edi  # 57
.globl _th10_004650ee
_th10_004650ee:
    push ebx  # 53
.globl _th10_004650ef
_th10_004650ef:
    {disp32} call _th10_0045e648  # e85495ffff
.globl _th10_004650f4
_th10_004650f4:
    add esp, 12  # 83c40c
.globl _th10_004650f7
_th10_004650f7:
    test eax, eax  # 85c0
.globl _th10_004650f9
_th10_004650f9:
    {disp8} jne _th10_00465142  # 7547
.globl _th10_004650fb
_th10_004650fb:
    {disp8} {load} mov eax, [ebp+8]  # 8b4508
.globl _th10_004650fe
_th10_004650fe:
    cmp eax, 16  # 83f810
.globl _th10_00465101
_th10_00465101:
    {disp8} je _th10_00465114  # 7411
.globl _th10_00465103
_th10_00465103:
    cmp eax, 22  # 83f816
.globl _th10_00465106
_th10_00465106:
    {disp8} je _th10_00465114  # 740c
.globl _th10_00465108
_th10_00465108:
    cmp eax, 29  # 83f81d
.globl _th10_0046510b
_th10_0046510b:
    {disp8} je _th10_00465114  # 7407
.globl _th10_0046510d
_th10_0046510d:
    {disp8} and dword ptr [esp+0x50], -2  # 83642450fe
.globl _th10_00465112
_th10_00465112:
    {disp8} jmp _th10_00465129  # eb15
.globl _th10_00465114
_th10_00465114:
    {disp8} {load} mov ecx, [esp+0x50]  # 8b4c2450
.globl _th10_00465118
_th10_00465118:
    {disp8} fld qword ptr [esi+0x10]  # dd4610
.globl _th10_0046511b
_th10_0046511b:
    and ecx, -29  # 83e1e3
.globl _th10_0046511e
_th10_0046511e:
    {disp8} fstp qword ptr [esp+0x40]  # dd5c2440
.globl _th10_00465122
_th10_00465122:
    or ecx, 3  # 83c903
.globl _th10_00465125
_th10_00465125:
    {disp8} {store} mov [esp+0x50], ecx  # 894c2450
.globl _th10_00465129
_th10_00465129:
    push edi  # 57
.globl _th10_0046512a
_th10_0046512a:
    {disp8} lea ecx, [esi+8]  # 8d4e08
.globl _th10_0046512d
_th10_0046512d:
    push ecx  # 51
.globl _th10_0046512e
_th10_0046512e:
    push eax  # 50
.globl _th10_0046512f
_th10_0046512f:
    push ebx  # 53
.globl _th10_00465130
_th10_00465130:
    {disp8} lea eax, [esp+0x1C]  # 8d44241c
.globl _th10_00465134
_th10_00465134:
    push eax  # 50
.globl _th10_00465135
_th10_00465135:
    {disp8} lea eax, [esp+0x24]  # 8d442424
.globl _th10_00465139
_th10_00465139:
    push eax  # 50
.globl _th10_0046513a
_th10_0046513a:
    {disp32} call _th10_0045e3a3  # e86492ffff
.globl _th10_0046513f
_th10_0046513f:
    add esp, 24  # 83c418
.globl _th10_00465142
_th10_00465142:
    {noimm8s} push 0x0FFFF  # 68ffff0000
.globl _th10_00465147
_th10_00465147:
    {disp8} push dword ptr [esp+0x10]  # ff742410
.globl _th10_0046514b
_th10_0046514b:
    {disp32} call _th10_0045ed87  # e8379cffff
.globl _th10_00465150
_th10_00465150:
    cmp dword ptr [esi], 8  # 833e08
.globl _th10_00465153
_th10_00465153:
    pop ecx  # 59
.globl _th10_00465154
_th10_00465154:
    pop ecx  # 59
.globl _th10_00465155
_th10_00465155:
    {disp8} je _th10_0046516b  # 7414
.globl _th10_00465157
_th10_00465157:
    cmp dword ptr [_th10_00473c90], 0  # 833d903c470000
.globl _th10_0046515e
_th10_0046515e:
    {disp8} jne _th10_0046516b  # 750b
.globl _th10_00465160
_th10_00465160:
    push esi  # 56
.globl _th10_00465161
_th10_00465161:
    {disp32} call _th10_0045e3a0  # e83a92ffff
.globl _th10_00465166
_th10_00465166:
    test eax, eax  # 85c0
.globl _th10_00465168
_th10_00465168:
    pop ecx  # 59
.globl _th10_00465169
_th10_00465169:
    {disp8} jne _th10_00465173  # 7508
.globl _th10_0046516b
_th10_0046516b:
    push dword ptr [esi]  # ff36
.globl _th10_0046516d
_th10_0046516d:
    {disp32} call _th10_0045e86c  # e8fa96ffff
.globl _th10_00465172
_th10_00465172:
    pop ecx  # 59
.globl _th10_00465173
_th10_00465173:
    {load} mov ecx, [esp+0x8C]  # 8b8c248c000000
.globl _th10_0046517a
_th10_0046517a:
    pop edi  # 5f
.globl _th10_0046517b
_th10_0046517b:
    pop esi  # 5e
.globl _th10_0046517c
_th10_0046517c:
    {load} xor ecx, ebp  # 33cd
.globl _th10_0046517e
_th10_0046517e:
    pop ebx  # 5b
.globl _th10_0046517f
_th10_0046517f:
    {disp32} call _th10_00458ea5  # e8213dffff
.globl _th10_00465184
_th10_00465184:
    {load} mov esp, ebp  # 8be5
.globl _th10_00465186
_th10_00465186:
    pop ebp  # 5d
.globl _th10_00465187
_th10_00465187:
    ret  # c3
# padding 00465188..0046518f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 8, 1, 0xcc
.globl _th10_00465190
_th10_00465190:
    {disp8} {load} mov ecx, [ebp-0x10]  # 8b4df0
.globl _th10_00465193
_th10_00465193:
    {disp32} jmp _th10_00462cac  # e914dbffff
.globl _th10_00465198
_th10_00465198:
    {noimm8s} mov eax, 0x47113C  # b83c114700
.globl _th10_0046519d
_th10_0046519d:
    {disp32} jmp _th10_0046276d  # e9cbd5ffff
.globl _th10_004651a2
_th10_004651a2:
    {disp8} lea ecx, [ebp-0x28]  # 8d4dd8
.globl _th10_004651a5
_th10_004651a5:
    {disp32} jmp _th10_004381f0  # e94630fdff
.globl _th10_004651aa
_th10_004651aa:
    {noimm8s} mov eax, 0x4711D4  # b8d4114700
.globl _th10_004651af
_th10_004651af:
    {disp32} jmp _th10_0046276d  # e9b9d5ffff
.globl _th10_004651b4
_th10_004651b4:
    {disp8} {load} mov ecx, [ebp-0x10]  # 8b4df0
.globl _th10_004651b7
_th10_004651b7:
    {disp32} jmp _th10_00462cac  # e9f0daffff
.globl _th10_004651bc
_th10_004651bc:
    {noimm8s} mov eax, 0x4711F8  # b8f8114700
.globl _th10_004651c1
_th10_004651c1:
    {disp32} jmp _th10_0046276d  # e9a7d5ffff
.globl _th10_004651c6
_th10_004651c6:
    {disp8} lea ecx, [ebp-0x28]  # 8d4dd8
.globl _th10_004651c9
_th10_004651c9:
    {disp32} jmp _th10_004381f0  # e92230fdff
.globl _th10_004651ce
_th10_004651ce:
    {noimm8s} mov eax, 0x471258  # b858124700
.globl _th10_004651d3
_th10_004651d3:
    {disp32} jmp _th10_0046276d  # e995d5ffff
# padding 004651d8..004651df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 8, 1, 0xcc
.globl _th10_004651e0
_th10_004651e0:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004651e5
_th10_004651e5:
    {noimm8s} push 0x1000  # 6800100000
.globl _th10_004651ea
_th10_004651ea:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004651ef
_th10_004651ef:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004651f2
_th10_004651f2:
    add eax, 104  # 83c068
.globl _th10_004651f5
_th10_004651f5:
    push eax  # 50
.globl _th10_004651f6
_th10_004651f6:
    {disp32} call _th10_004525ff  # e804d4feff
.globl _th10_004651fb
_th10_004651fb:
    ret  # c3
.globl _th10_004651fc
_th10_004651fc:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004651ff
_th10_004651ff:
    {noimm8s} add ecx, 0x3AD130  # 81c130d13a00
.globl _th10_00465205
_th10_00465205:
    {disp32} jmp _th10_00401ff0  # e9e6cdf9ff
.globl _th10_0046520a
_th10_0046520a:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_0046520f
_th10_0046520f:
    push 20  # 6a14
.globl _th10_00465211
_th10_00465211:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465216
_th10_00465216:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465219
_th10_00465219:
    {noimm8s} add eax, 0x72DAE4  # 05e4da7200
.globl _th10_0046521e
_th10_0046521e:
    push eax  # 50
.globl _th10_0046521f
_th10_0046521f:
    {disp32} call _th10_004525ff  # e8dbd3feff
.globl _th10_00465224
_th10_00465224:
    ret  # c3
.globl _th10_00465225
_th10_00465225:
    {noimm8s} mov eax, 0x47128C  # b88c124700
.globl _th10_0046522a
_th10_0046522a:
    {disp32} jmp _th10_0046276d  # e93ed5ffff
# padding 0046522f..0046522f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 1, 1, 0xcc
.globl _th10_00465230
_th10_00465230:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_00465233
_th10_00465233:
    add ecx, 24  # 83c118
.globl _th10_00465236
_th10_00465236:
    {disp32} jmp _th10_00401ff0  # e9b5cdf9ff
.globl _th10_0046523b
_th10_0046523b:
    {noimm8s} mov eax, 0x4712B0  # b8b0124700
.globl _th10_00465240
_th10_00465240:
    {disp32} jmp _th10_0046276d  # e928d5ffff
# padding 00465245..0046524f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465250
_th10_00465250:
    {noimm8s} push 0x42AC60  # 6860ac4200
.globl _th10_00465255
_th10_00465255:
    push 8  # 6a08
.globl _th10_00465257
_th10_00465257:
    push 36  # 6a24
.globl _th10_00465259
_th10_00465259:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_0046525c
_th10_0046525c:
    {noimm8s} add eax, 0x0A0  # 05a0000000
.globl _th10_00465261
_th10_00465261:
    push eax  # 50
.globl _th10_00465262
_th10_00465262:
    {disp32} call _th10_004525ff  # e898d3feff
.globl _th10_00465267
_th10_00465267:
    ret  # c3
.globl _th10_00465268
_th10_00465268:
    {noimm8s} mov eax, 0x4712D4  # b8d4124700
.globl _th10_0046526d
_th10_0046526d:
    {disp32} jmp _th10_0046276d  # e9fbd4ffff
# padding 00465272..0046527f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 14, 1, 0xcc
.globl _th10_00465280
_th10_00465280:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_00465283
_th10_00465283:
    add ecx, 20  # 83c114
.globl _th10_00465286
_th10_00465286:
    {disp32} jmp _th10_00401ff0  # e965cdf9ff
.globl _th10_0046528b
_th10_0046528b:
    {noimm8s} mov eax, 0x4712F8  # b8f8124700
.globl _th10_00465290
_th10_00465290:
    {disp32} jmp _th10_0046276d  # e9d8d4ffff
# padding 00465295..0046529f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004652a0
_th10_004652a0:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004652a5
_th10_004652a5:
    push 8  # 6a08
.globl _th10_004652a7
_th10_004652a7:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004652ac
_th10_004652ac:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004652af
_th10_004652af:
    {noimm8s} add eax, 0x180  # 0580010000
.globl _th10_004652b4
_th10_004652b4:
    push eax  # 50
.globl _th10_004652b5
_th10_004652b5:
    {disp32} call _th10_004525ff  # e845d3feff
.globl _th10_004652ba
_th10_004652ba:
    ret  # c3
.globl _th10_004652bb
_th10_004652bb:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004652c0
_th10_004652c0:
    push 3  # 6a03
.globl _th10_004652c2
_th10_004652c2:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004652c7
_th10_004652c7:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004652ca
_th10_004652ca:
    {noimm8s} add eax, 0x1F08  # 05081f0000
.globl _th10_004652cf
_th10_004652cf:
    push eax  # 50
.globl _th10_004652d0
_th10_004652d0:
    {disp32} call _th10_004525ff  # e82ad3feff
.globl _th10_004652d5
_th10_004652d5:
    ret  # c3
.globl _th10_004652d6
_th10_004652d6:
    {noimm8s} mov eax, 0x471324  # b824134700
.globl _th10_004652db
_th10_004652db:
    {disp32} jmp _th10_0046276d  # e98dd4ffff
.globl _th10_004652e0
_th10_004652e0:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004652e3
_th10_004652e3:
    add ecx, 20  # 83c114
.globl _th10_004652e6
_th10_004652e6:
    {disp32} jmp _th10_00401ff0  # e905cdf9ff
.globl _th10_004652eb
_th10_004652eb:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004652ee
_th10_004652ee:
    {noimm8s} add ecx, 0x3C0  # 81c1c0030000
.globl _th10_004652f4
_th10_004652f4:
    {disp32} jmp _th10_00401ff0  # e9f7ccf9ff
.globl _th10_004652f9
_th10_004652f9:
    {noimm8s} mov eax, 0x471350  # b850134700
.globl _th10_004652fe
_th10_004652fe:
    {disp32} jmp _th10_0046276d  # e96ad4ffff
# padding 00465303..0046530f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 13, 1, 0xcc
.globl _th10_00465310
_th10_00465310:
    {disp8} {load} mov eax, [ebp-0x48]  # 8b45b8
.globl _th10_00465313
_th10_00465313:
    push eax  # 50
.globl _th10_00465314
_th10_00465314:
    {disp32} call _th10_004524a1  # e888d1feff
.globl _th10_00465319
_th10_00465319:
    pop ecx  # 59
.globl _th10_0046531a
_th10_0046531a:
    ret  # c3
.globl _th10_0046531b
_th10_0046531b:
    {noimm8s} mov eax, 0x471374  # b874134700
.globl _th10_00465320
_th10_00465320:
    {disp32} jmp _th10_0046276d  # e948d4ffff
# padding 00465325..0046532f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465330
_th10_00465330:
    {disp8} {load} mov eax, [ebp-0x48]  # 8b45b8
.globl _th10_00465333
_th10_00465333:
    push eax  # 50
.globl _th10_00465334
_th10_00465334:
    {disp32} call _th10_004524a1  # e868d1feff
.globl _th10_00465339
_th10_00465339:
    pop ecx  # 59
.globl _th10_0046533a
_th10_0046533a:
    ret  # c3
.globl _th10_0046533b
_th10_0046533b:
    {noimm8s} mov eax, 0x471398  # b898134700
.globl _th10_00465340
_th10_00465340:
    {disp32} jmp _th10_0046276d  # e928d4ffff
.globl _th10_00465345
_th10_00465345:
    int3  # cc
# padding 00465346..0046534f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 10, 1, 0xcc
.globl _th10_00465350
_th10_00465350:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465353
_th10_00465353:
    {disp32} jmp _th10_00449a90  # e93847feff
.globl _th10_00465358
_th10_00465358:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_0046535b
_th10_0046535b:
    add eax, 36  # 83c024
.globl _th10_0046535e
_th10_0046535e:
    {disp32} jmp _th10_00449a90  # e92d47feff
.globl _th10_00465363
_th10_00465363:
    {noimm8s} mov eax, 0x4713C4  # b8c4134700
.globl _th10_00465368
_th10_00465368:
    {disp32} jmp _th10_0046276d  # e900d4ffff
# padding 0046536d..0046536f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 3, 1, 0xcc
.globl _th10_00465370
_th10_00465370:
    {noimm8s} mov eax, 0x471448  # b848144700
.globl _th10_00465375
_th10_00465375:
    {disp32} jmp _th10_0046276d  # e9f3d3ffff
# padding 0046537a..0046537f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 6, 1, 0xcc
.globl _th10_00465380
_th10_00465380:
    {disp8} lea ecx, [ebp-0x18]  # 8d4de8
.globl _th10_00465383
_th10_00465383:
    {disp32} jmp _th10_00435340  # e9b8fffcff
.globl _th10_00465388
_th10_00465388:
    {noimm8s} mov eax, 0x47146C  # b86c144700
.globl _th10_0046538d
_th10_0046538d:
    {disp32} jmp _th10_0046276d  # e9dbd3ffff
# padding 00465392..0046539f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 14, 1, 0xcc
.globl _th10_004653a0
_th10_004653a0:
    {disp8} lea ecx, [ebp-0x18]  # 8d4de8
.globl _th10_004653a3
_th10_004653a3:
    {disp32} jmp _th10_00435340  # e998fffcff
.globl _th10_004653a8
_th10_004653a8:
    {noimm8s} mov eax, 0x471490  # b890144700
.globl _th10_004653ad
_th10_004653ad:
    {disp32} jmp _th10_0046276d  # e9bbd3ffff
# padding 004653b2..004653bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 14, 1, 0xcc
.globl _th10_004653c0
_th10_004653c0:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_004653c3
_th10_004653c3:
    push eax  # 50
.globl _th10_004653c4
_th10_004653c4:
    {disp32} call _th10_004524a1  # e8d8d0feff
.globl _th10_004653c9
_th10_004653c9:
    pop ecx  # 59
.globl _th10_004653ca
_th10_004653ca:
    ret  # c3
.globl _th10_004653cb
_th10_004653cb:
    {noimm8s} mov eax, 0x4714B4  # b8b4144700
.globl _th10_004653d0
_th10_004653d0:
    {disp32} jmp _th10_0046276d  # e998d3ffff
# padding 004653d5..004653df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004653e0
_th10_004653e0:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004653e3
_th10_004653e3:
    add ecx, 16  # 83c110
.globl _th10_004653e6
_th10_004653e6:
    {disp32} jmp _th10_0044c130  # e9456dfeff
.globl _th10_004653eb
_th10_004653eb:
    {noimm8s} mov eax, 0x4714D8  # b8d8144700
.globl _th10_004653f0
_th10_004653f0:
    {disp32} jmp _th10_0046276d  # e978d3ffff
# padding 004653f5..004653ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465400
_th10_00465400:
    {noimm8s} push 0x41AD60  # 6860ad4100
.globl _th10_00465405
_th10_00465405:
    {noimm8s} push 0x896  # 6896080000
.globl _th10_0046540a
_th10_0046540a:
    {noimm8s} push 0x3F0  # 68f0030000
.globl _th10_0046540f
_th10_0046540f:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465412
_th10_00465412:
    add eax, 20  # 83c014
.globl _th10_00465415
_th10_00465415:
    push eax  # 50
.globl _th10_00465416
_th10_00465416:
    {disp32} call _th10_004525ff  # e8e4d1feff
.globl _th10_0046541b
_th10_0046541b:
    ret  # c3
.globl _th10_0046541c
_th10_0046541c:
    {noimm8s} mov eax, 0x4714FC  # b8fc144700
.globl _th10_00465421
_th10_00465421:
    {disp32} jmp _th10_0046276d  # e947d3ffff
# padding 00465426..0046542f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 10, 1, 0xcc
.globl _th10_00465430
_th10_00465430:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_00465435
_th10_00465435:
    push 10  # 6a0a
.globl _th10_00465437
_th10_00465437:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_0046543c
_th10_0046543c:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_0046543f
_th10_0046543f:
    add eax, 16  # 83c010
.globl _th10_00465442
_th10_00465442:
    push eax  # 50
.globl _th10_00465443
_th10_00465443:
    {disp32} call _th10_004525ff  # e8b7d1feff
.globl _th10_00465448
_th10_00465448:
    ret  # c3
.globl _th10_00465449
_th10_00465449:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_0046544e
_th10_0046544e:
    push 10  # 6a0a
.globl _th10_00465450
_th10_00465450:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465455
_th10_00465455:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465458
_th10_00465458:
    {noimm8s} add eax, 0x24C8  # 05c8240000
.globl _th10_0046545d
_th10_0046545d:
    push eax  # 50
.globl _th10_0046545e
_th10_0046545e:
    {disp32} call _th10_004525ff  # e89cd1feff
.globl _th10_00465463
_th10_00465463:
    ret  # c3
.globl _th10_00465464
_th10_00465464:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_00465469
_th10_00465469:
    push 9  # 6a09
.globl _th10_0046546b
_th10_0046546b:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465470
_th10_00465470:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465473
_th10_00465473:
    {noimm8s} add eax, 0x4980  # 0580490000
.globl _th10_00465478
_th10_00465478:
    push eax  # 50
.globl _th10_00465479
_th10_00465479:
    {disp32} call _th10_004525ff  # e881d1feff
.globl _th10_0046547e
_th10_0046547e:
    ret  # c3
.globl _th10_0046547f
_th10_0046547f:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_00465484
_th10_00465484:
    push 4  # 6a04
.globl _th10_00465486
_th10_00465486:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_0046548b
_th10_0046548b:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_0046548e
_th10_0046548e:
    {noimm8s} add eax, 0x6A8C  # 058c6a0000
.globl _th10_00465493
_th10_00465493:
    push eax  # 50
.globl _th10_00465494
_th10_00465494:
    {disp32} call _th10_004525ff  # e866d1feff
.globl _th10_00465499
_th10_00465499:
    ret  # c3
.globl _th10_0046549a
_th10_0046549a:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_0046549f
_th10_0046549f:
    push 2  # 6a02
.globl _th10_004654a1
_th10_004654a1:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004654a6
_th10_004654a6:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004654a9
_th10_004654a9:
    {noimm8s} add eax, 0x793C  # 053c790000
.globl _th10_004654ae
_th10_004654ae:
    push eax  # 50
.globl _th10_004654af
_th10_004654af:
    {disp32} call _th10_004525ff  # e84bd1feff
.globl _th10_004654b4
_th10_004654b4:
    ret  # c3
.globl _th10_004654b5
_th10_004654b5:
    {noimm8s} mov eax, 0x471540  # b840154700
.globl _th10_004654ba
_th10_004654ba:
    {disp32} jmp _th10_0046276d  # e9aed2ffff
# padding 004654bf..004654bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 1, 1, 0xcc
.globl _th10_004654c0
_th10_004654c0:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004654c3
_th10_004654c3:
    {noimm8s} add ecx, 0x0D0  # 81c1d0000000
.globl _th10_004654c9
_th10_004654c9:
    {disp32} jmp _th10_0044c130  # e9626cfeff
.globl _th10_004654ce
_th10_004654ce:
    {noimm8s} mov eax, 0x471564  # b864154700
.globl _th10_004654d3
_th10_004654d3:
    {disp32} jmp _th10_0046276d  # e995d2ffff
# padding 004654d8..004654df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 8, 1, 0xcc
.globl _th10_004654e0
_th10_004654e0:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004654e5
_th10_004654e5:
    push 2  # 6a02
.globl _th10_004654e7
_th10_004654e7:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004654ec
_th10_004654ec:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004654ef
_th10_004654ef:
    add eax, 16  # 83c010
.globl _th10_004654f2
_th10_004654f2:
    push eax  # 50
.globl _th10_004654f3
_th10_004654f3:
    {disp32} call _th10_004525ff  # e807d1feff
.globl _th10_004654f8
_th10_004654f8:
    ret  # c3
.globl _th10_004654f9
_th10_004654f9:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004654fe
_th10_004654fe:
    push 8  # 6a08
.globl _th10_00465500
_th10_00465500:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465505
_th10_00465505:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465508
_th10_00465508:
    {noimm8s} add eax, 0x778  # 0578070000
.globl _th10_0046550d
_th10_0046550d:
    push eax  # 50
.globl _th10_0046550e
_th10_0046550e:
    {disp32} call _th10_004525ff  # e8ecd0feff
.globl _th10_00465513
_th10_00465513:
    ret  # c3
.globl _th10_00465514
_th10_00465514:
    {noimm8s} mov eax, 0x471590  # b890154700
.globl _th10_00465519
_th10_00465519:
    {disp32} jmp _th10_0046276d  # e94fd2ffff
# padding 0046551e..0046551f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 2, 1, 0xcc
.globl _th10_00465520
_th10_00465520:
    {noimm8s} push 0x405DE0  # 68e05d4000
.globl _th10_00465525
_th10_00465525:
    {noimm8s} push 0x7D1  # 68d1070000
.globl _th10_0046552a
_th10_0046552a:
    {noimm8s} push 0x7F0  # 68f0070000
.globl _th10_0046552f
_th10_0046552f:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465532
_th10_00465532:
    add eax, 96  # 83c060
.globl _th10_00465535
_th10_00465535:
    push eax  # 50
.globl _th10_00465536
_th10_00465536:
    {disp32} call _th10_004525ff  # e8c4d0feff
.globl _th10_0046553b
_th10_0046553b:
    ret  # c3
.globl _th10_0046553c
_th10_0046553c:
    {noimm8s} mov eax, 0x4715B4  # b8b4154700
.globl _th10_00465541
_th10_00465541:
    {disp32} jmp _th10_0046276d  # e927d2ffff
# padding 00465546..0046554f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 10, 1, 0xcc
.globl _th10_00465550
_th10_00465550:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_00465555
_th10_00465555:
    push 8  # 6a08
.globl _th10_00465557
_th10_00465557:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_0046555c
_th10_0046555c:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_0046555f
_th10_0046555f:
    {noimm8s} add eax, 0x180  # 0580010000
.globl _th10_00465564
_th10_00465564:
    push eax  # 50
.globl _th10_00465565
_th10_00465565:
    {disp32} call _th10_004525ff  # e895d0feff
.globl _th10_0046556a
_th10_0046556a:
    ret  # c3
.globl _th10_0046556b
_th10_0046556b:
    {noimm8s} mov eax, 0x4715D8  # b8d8154700
.globl _th10_00465570
_th10_00465570:
    {disp32} jmp _th10_0046276d  # e9f8d1ffff
# padding 00465575..0046557f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465580
_th10_00465580:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_00465583
_th10_00465583:
    add ecx, 12  # 83c10c
.globl _th10_00465586
_th10_00465586:
    {disp32} jmp _th10_004381f0  # e9652cfdff
.globl _th10_0046558b
_th10_0046558b:
    {noimm8s} mov eax, 0x4715FC  # b8fc154700
.globl _th10_00465590
_th10_00465590:
    {disp32} jmp _th10_0046276d  # e9d8d1ffff
# padding 00465595..0046559f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004655a0
_th10_004655a0:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_004655a3
_th10_004655a3:
    push eax  # 50
.globl _th10_004655a4
_th10_004655a4:
    {disp32} call _th10_004524a1  # e8f8cefeff
.globl _th10_004655a9
_th10_004655a9:
    pop ecx  # 59
.globl _th10_004655aa
_th10_004655aa:
    ret  # c3
.globl _th10_004655ab
_th10_004655ab:
    {noimm8s} mov eax, 0x471620  # b820164700
.globl _th10_004655b0
_th10_004655b0:
    {disp32} jmp _th10_0046276d  # e9b8d1ffff
# padding 004655b5..004655bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004655c0
_th10_004655c0:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004655c5
_th10_004655c5:
    push 2  # 6a02
.globl _th10_004655c7
_th10_004655c7:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004655cc
_th10_004655cc:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004655cf
_th10_004655cf:
    add eax, 16  # 83c010
.globl _th10_004655d2
_th10_004655d2:
    push eax  # 50
.globl _th10_004655d3
_th10_004655d3:
    {disp32} call _th10_004525ff  # e827d0feff
.globl _th10_004655d8
_th10_004655d8:
    ret  # c3
.globl _th10_004655d9
_th10_004655d9:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004655de
_th10_004655de:
    push 8  # 6a08
.globl _th10_004655e0
_th10_004655e0:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004655e5
_th10_004655e5:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004655e8
_th10_004655e8:
    {noimm8s} add eax, 0x778  # 0578070000
.globl _th10_004655ed
_th10_004655ed:
    push eax  # 50
.globl _th10_004655ee
_th10_004655ee:
    {disp32} call _th10_004525ff  # e80cd0feff
.globl _th10_004655f3
_th10_004655f3:
    ret  # c3
.globl _th10_004655f4
_th10_004655f4:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004655f9
_th10_004655f9:
    push 5  # 6a05
.globl _th10_004655fb
_th10_004655fb:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465600
_th10_00465600:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465603
_th10_00465603:
    {noimm8s} add eax, 0x24D8  # 05d8240000
.globl _th10_00465608
_th10_00465608:
    push eax  # 50
.globl _th10_00465609
_th10_00465609:
    {disp32} call _th10_004525ff  # e8f1cffeff
.globl _th10_0046560e
_th10_0046560e:
    ret  # c3
.globl _th10_0046560f
_th10_0046560f:
    {noimm8s} mov eax, 0x471654  # b854164700
.globl _th10_00465614
_th10_00465614:
    {disp32} jmp _th10_0046276d  # e954d1ffff
# padding 00465619..0046561f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 7, 1, 0xcc
.globl _th10_00465620
_th10_00465620:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_00465623
_th10_00465623:
    {noimm8s} add ecx, 0x5AB0  # 81c1b05a0000
.globl _th10_00465629
_th10_00465629:
    {disp32} jmp _th10_0044c130  # e9026bfeff
.globl _th10_0046562e
_th10_0046562e:
    {noimm8s} mov eax, 0x471678  # b878164700
.globl _th10_00465633
_th10_00465633:
    {disp32} jmp _th10_0046276d  # e935d1ffff
# padding 00465638..0046563f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 8, 1, 0xcc
.globl _th10_00465640
_th10_00465640:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465643
_th10_00465643:
    push eax  # 50
.globl _th10_00465644
_th10_00465644:
    {disp32} call _th10_004524a1  # e858cefeff
.globl _th10_00465649
_th10_00465649:
    pop ecx  # 59
.globl _th10_0046564a
_th10_0046564a:
    ret  # c3
.globl _th10_0046564b
_th10_0046564b:
    {noimm8s} mov eax, 0x47169C  # b89c164700
.globl _th10_00465650
_th10_00465650:
    {disp32} jmp _th10_0046276d  # e918d1ffff
# padding 00465655..0046565f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465660
_th10_00465660:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465663
_th10_00465663:
    push eax  # 50
.globl _th10_00465664
_th10_00465664:
    {disp32} call _th10_004524a1  # e838cefeff
.globl _th10_00465669
_th10_00465669:
    pop ecx  # 59
.globl _th10_0046566a
_th10_0046566a:
    ret  # c3
.globl _th10_0046566b
_th10_0046566b:
    {noimm8s} mov eax, 0x4716C0  # b8c0164700
.globl _th10_00465670
_th10_00465670:
    {disp32} jmp _th10_0046276d  # e9f8d0ffff
# padding 00465675..0046567f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465680
_th10_00465680:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_00465683
_th10_00465683:
    add ecx, 16  # 83c110
.globl _th10_00465686
_th10_00465686:
    {disp32} jmp _th10_0044c130  # e9a56afeff
.globl _th10_0046568b
_th10_0046568b:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_0046568e
_th10_0046568e:
    add ecx, 48  # 83c130
.globl _th10_00465691
_th10_00465691:
    {disp32} jmp _th10_00401ff0  # e95ac9f9ff
.globl _th10_00465696
_th10_00465696:
    {noimm8s} mov eax, 0x4716EC  # b8ec164700
.globl _th10_0046569b
_th10_0046569b:
    {disp32} jmp _th10_0046276d  # e9cdd0ffff
.globl _th10_004656a0
_th10_004656a0:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004656a5
_th10_004656a5:
    push 10  # 6a0a
.globl _th10_004656a7
_th10_004656a7:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004656ac
_th10_004656ac:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004656af
_th10_004656af:
    add eax, 16  # 83c010
.globl _th10_004656b2
_th10_004656b2:
    push eax  # 50
.globl _th10_004656b3
_th10_004656b3:
    {disp32} call _th10_004525ff  # e847cffeff
.globl _th10_004656b8
_th10_004656b8:
    ret  # c3
.globl _th10_004656b9
_th10_004656b9:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004656be
_th10_004656be:
    push 10  # 6a0a
.globl _th10_004656c0
_th10_004656c0:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004656c5
_th10_004656c5:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004656c8
_th10_004656c8:
    {noimm8s} add eax, 0x24C8  # 05c8240000
.globl _th10_004656cd
_th10_004656cd:
    push eax  # 50
.globl _th10_004656ce
_th10_004656ce:
    {disp32} call _th10_004525ff  # e82ccffeff
.globl _th10_004656d3
_th10_004656d3:
    ret  # c3
.globl _th10_004656d4
_th10_004656d4:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004656d9
_th10_004656d9:
    push 9  # 6a09
.globl _th10_004656db
_th10_004656db:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004656e0
_th10_004656e0:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004656e3
_th10_004656e3:
    {noimm8s} add eax, 0x4980  # 0580490000
.globl _th10_004656e8
_th10_004656e8:
    push eax  # 50
.globl _th10_004656e9
_th10_004656e9:
    {disp32} call _th10_004525ff  # e811cffeff
.globl _th10_004656ee
_th10_004656ee:
    ret  # c3
.globl _th10_004656ef
_th10_004656ef:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_004656f4
_th10_004656f4:
    push 4  # 6a04
.globl _th10_004656f6
_th10_004656f6:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_004656fb
_th10_004656fb:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004656fe
_th10_004656fe:
    {noimm8s} add eax, 0x6A8C  # 058c6a0000
.globl _th10_00465703
_th10_00465703:
    push eax  # 50
.globl _th10_00465704
_th10_00465704:
    {disp32} call _th10_004525ff  # e8f6cefeff
.globl _th10_00465709
_th10_00465709:
    ret  # c3
.globl _th10_0046570a
_th10_0046570a:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_0046570f
_th10_0046570f:
    push 2  # 6a02
.globl _th10_00465711
_th10_00465711:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465716
_th10_00465716:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465719
_th10_00465719:
    {noimm8s} add eax, 0x793C  # 053c790000
.globl _th10_0046571e
_th10_0046571e:
    push eax  # 50
.globl _th10_0046571f
_th10_0046571f:
    {disp32} call _th10_004525ff  # e8dbcefeff
.globl _th10_00465724
_th10_00465724:
    ret  # c3
.globl _th10_00465725
_th10_00465725:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_0046572a
_th10_0046572a:
    push 7  # 6a07
.globl _th10_0046572c
_th10_0046572c:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465731
_th10_00465731:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465734
_th10_00465734:
    {noimm8s} add eax, 0x8094  # 0594800000
.globl _th10_00465739
_th10_00465739:
    push eax  # 50
.globl _th10_0046573a
_th10_0046573a:
    {disp32} call _th10_004525ff  # e8c0cefeff
.globl _th10_0046573f
_th10_0046573f:
    ret  # c3
.globl _th10_00465740
_th10_00465740:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_00465743
_th10_00465743:
    {noimm8s} add ecx, 0x9A48  # 81c1489a0000
.globl _th10_00465749
_th10_00465749:
    {disp32} jmp _th10_00401ff0  # e9a2c8f9ff
.globl _th10_0046574e
_th10_0046574e:
    {noimm8s} mov eax, 0x471740  # b840174700
.globl _th10_00465753
_th10_00465753:
    {disp32} jmp _th10_0046276d  # e915d0ffff
# padding 00465758..0046575f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 8, 1, 0xcc
.globl _th10_00465760
_th10_00465760:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_00465765
_th10_00465765:
    {noimm8s} push 0x1000  # 6800100000
.globl _th10_0046576a
_th10_0046576a:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_0046576f
_th10_0046576f:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465772
_th10_00465772:
    add eax, 104  # 83c068
.globl _th10_00465775
_th10_00465775:
    push eax  # 50
.globl _th10_00465776
_th10_00465776:
    {disp32} call _th10_004525ff  # e884cefeff
.globl _th10_0046577b
_th10_0046577b:
    ret  # c3
.globl _th10_0046577c
_th10_0046577c:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_0046577f
_th10_0046577f:
    {noimm8s} add ecx, 0x3AD130  # 81c130d13a00
.globl _th10_00465785
_th10_00465785:
    {disp32} jmp _th10_00401ff0  # e966c8f9ff
.globl _th10_0046578a
_th10_0046578a:
    {noimm8s} push 0x401FF0  # 68f01f4000
.globl _th10_0046578f
_th10_0046578f:
    push 20  # 6a14
.globl _th10_00465791
_th10_00465791:
    {noimm8s} push 0x3AC  # 68ac030000
.globl _th10_00465796
_th10_00465796:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_00465799
_th10_00465799:
    {noimm8s} add eax, 0x72DAE4  # 05e4da7200
.globl _th10_0046579e
_th10_0046579e:
    push eax  # 50
.globl _th10_0046579f
_th10_0046579f:
    {disp32} call _th10_004525ff  # e85bcefeff
.globl _th10_004657a4
_th10_004657a4:
    ret  # c3
.globl _th10_004657a5
_th10_004657a5:
    {noimm8s} mov eax, 0x471774  # b874174700
.globl _th10_004657aa
_th10_004657aa:
    {disp32} jmp _th10_0046276d  # e9becfffff
# padding 004657af..004657af: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
.fill 1, 1, 0xcc
.globl _th10_004657b0
_th10_004657b0:
    {disp8} {load} mov eax, [ebp+4]  # 8b4504
.globl _th10_004657b3
_th10_004657b3:
    push eax  # 50
.globl _th10_004657b4
_th10_004657b4:
    {disp32} call _th10_004524a1  # e8e8ccfeff
.globl _th10_004657b9
_th10_004657b9:
    pop ecx  # 59
.globl _th10_004657ba
_th10_004657ba:
    ret  # c3
.globl _th10_004657bb
_th10_004657bb:
    {noimm8s} mov eax, 0x471798  # b898174700
.globl _th10_004657c0
_th10_004657c0:
    {disp32} jmp _th10_0046276d  # e9a8cfffff
# padding 004657c5..004657cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004657d0
_th10_004657d0:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004657d3
_th10_004657d3:
    add ecx, 16  # 83c110
.globl _th10_004657d6
_th10_004657d6:
    {disp32} jmp _th10_0044c130  # e95569feff
.globl _th10_004657db
_th10_004657db:
    {disp8} {load} mov ecx, [ebp+4]  # 8b4d04
.globl _th10_004657de
_th10_004657de:
    {noimm8s} add ecx, 0x2C8  # 81c1c8020000
.globl _th10_004657e4
_th10_004657e4:
    {disp32} jmp _th10_00401ff0  # e907c8f9ff
.globl _th10_004657e9
_th10_004657e9:
    {noimm8s} mov eax, 0x4717C4  # b8c4174700
.globl _th10_004657ee
_th10_004657ee:
    {disp32} jmp _th10_0046276d  # e97acfffff
# padding 004657f3..004657ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 13, 1, 0xcc
.globl _th10_00465800
_th10_00465800:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465803
_th10_00465803:
    push eax  # 50
.globl _th10_00465804
_th10_00465804:
    {disp32} call _th10_004524a1  # e898ccfeff
.globl _th10_00465809
_th10_00465809:
    pop ecx  # 59
.globl _th10_0046580a
_th10_0046580a:
    ret  # c3
.globl _th10_0046580b
_th10_0046580b:
    {noimm8s} mov eax, 0x4717E8  # b8e8174700
.globl _th10_00465810
_th10_00465810:
    {disp32} jmp _th10_0046276d  # e958cfffff
# padding 00465815..0046581f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465820
_th10_00465820:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465823
_th10_00465823:
    push eax  # 50
.globl _th10_00465824
_th10_00465824:
    {disp32} call _th10_004524a1  # e878ccfeff
.globl _th10_00465829
_th10_00465829:
    pop ecx  # 59
.globl _th10_0046582a
_th10_0046582a:
    ret  # c3
.globl _th10_0046582b
_th10_0046582b:
    {noimm8s} mov eax, 0x47180C  # b80c184700
.globl _th10_00465830
_th10_00465830:
    {disp32} jmp _th10_0046276d  # e938cfffff
# padding 00465835..0046583f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465840
_th10_00465840:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465843
_th10_00465843:
    push eax  # 50
.globl _th10_00465844
_th10_00465844:
    {disp32} call _th10_004524a1  # e858ccfeff
.globl _th10_00465849
_th10_00465849:
    pop ecx  # 59
.globl _th10_0046584a
_th10_0046584a:
    ret  # c3
.globl _th10_0046584b
_th10_0046584b:
    {noimm8s} mov eax, 0x471830  # b830184700
.globl _th10_00465850
_th10_00465850:
    {disp32} jmp _th10_0046276d  # e918cfffff
# padding 00465855..0046585f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465860
_th10_00465860:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465863
_th10_00465863:
    push eax  # 50
.globl _th10_00465864
_th10_00465864:
    {disp32} call _th10_004524a1  # e838ccfeff
.globl _th10_00465869
_th10_00465869:
    pop ecx  # 59
.globl _th10_0046586a
_th10_0046586a:
    ret  # c3
.globl _th10_0046586b
_th10_0046586b:
    {noimm8s} mov eax, 0x471854  # b854184700
.globl _th10_00465870
_th10_00465870:
    {disp32} jmp _th10_0046276d  # e9f8ceffff
# padding 00465875..0046587f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_00465880
_th10_00465880:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_00465883
_th10_00465883:
    push eax  # 50
.globl _th10_00465884
_th10_00465884:
    {disp32} call _th10_004524a1  # e818ccfeff
.globl _th10_00465889
_th10_00465889:
    pop ecx  # 59
.globl _th10_0046588a
_th10_0046588a:
    ret  # c3
.globl _th10_0046588b
_th10_0046588b:
    {noimm8s} mov eax, 0x471878  # b878184700
.globl _th10_00465890
_th10_00465890:
    {disp32} jmp _th10_0046276d  # e9d8ceffff
# padding 00465895..0046589f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004658a0
_th10_004658a0:
    {disp8} {load} mov eax, [ebp-0x10]  # 8b45f0
.globl _th10_004658a3
_th10_004658a3:
    push eax  # 50
.globl _th10_004658a4
_th10_004658a4:
    {disp32} call _th10_004524a1  # e8f8cbfeff
.globl _th10_004658a9
_th10_004658a9:
    pop ecx  # 59
.globl _th10_004658aa
_th10_004658aa:
    ret  # c3
.globl _th10_004658ab
_th10_004658ab:
    {noimm8s} mov eax, 0x47189C  # b89c184700
.globl _th10_004658b0
_th10_004658b0:
    {disp32} jmp _th10_0046276d  # e9b8ceffff
# padding 004658b5..004658bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 11, 1, 0xcc
.globl _th10_004658c0
_th10_004658c0:
    mov eax, [_th10_00474c64]  # a1644c4700
.globl _th10_004658c5
_th10_004658c5:
    and eax, -2  # 83e0fe
.globl _th10_004658c8
_th10_004658c8:
    test al, 1  # a801
.globl _th10_004658ca
_th10_004658ca:
    mov [_th10_00474c64], eax  # a3644c4700
.globl _th10_004658cf
_th10_004658cf:
    {disp8} jne _th10_004658e3  # 7512
.globl _th10_004658d1
_th10_004658d1:
    or eax, 1  # 83c801
.globl _th10_004658d4
_th10_004658d4:
    {noimm8s} mov dword ptr [_th10_00474c60], 0x476F78  # c705604c4700786f4700
.globl _th10_004658de
_th10_004658de:
    mov [_th10_00474c64], eax  # a3644c4700
.globl _th10_004658e3
_th10_004658e3:
    ret  # c3
# padding 004658e4..004658ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 12, 1, 0xcc
.globl _th10_004658f0
_th10_004658f0:
    push esi  # 56
.globl _th10_004658f1
_th10_004658f1:
    {noimm8s} mov esi, 0x491C28  # be281c4900
.globl _th10_004658f6
_th10_004658f6:
    {disp32} call _th10_00421f00  # e805c6fbff
.globl _th10_004658fb
_th10_004658fb:
    {noimm8s} push 0x4659F0  # 68f0594600
.globl _th10_00465900
_th10_00465900:
    {disp32} call _th10_00452e0a  # e805d5feff
.globl _th10_00465905
_th10_00465905:
    add esp, 4  # 83c404
.globl _th10_00465908
_th10_00465908:
    pop esi  # 5e
.globl _th10_00465909
_th10_00465909:
    ret  # c3
# padding 0046590a..0046590f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 6, 1, 0xcc
.globl _th10_00465910
_th10_00465910:
    {noimm8s} push 0x434C20  # 68204c4300
.globl _th10_00465915
_th10_00465915:
    {noimm8s} push 0x434C10  # 68104c4300
.globl _th10_0046591a
_th10_0046591a:
    push 20  # 6a14
.globl _th10_0046591c
_th10_0046591c:
    push 16  # 6a10
.globl _th10_0046591e
_th10_0046591e:
    {noimm8s} push 0x4923B0  # 68b0234900
.globl _th10_00465923
_th10_00465923:
    {disp32} call _th10_0045252d  # e805ccfeff
.globl _th10_00465928
_th10_00465928:
    {noimm8s} push 0x465A00  # 68005a4600
.globl _th10_0046592d
_th10_0046592d:
    {disp32} call _th10_00452e0a  # e8d8d4feff
.globl _th10_00465932
_th10_00465932:
    pop ecx  # 59
.globl _th10_00465933
_th10_00465933:
    ret  # c3
# padding 00465934..0046593f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 12, 1, 0xcc
.globl _th10_00465940
_th10_00465940:
    {noimm8s} push 0x465A20  # 68205a4600
.globl _th10_00465945
_th10_00465945:
    {disp32} call _th10_00452e0a  # e8c0d4feff
.globl _th10_0046594a
_th10_0046594a:
    pop ecx  # 59
.globl _th10_0046594b
_th10_0046594b:
    ret  # c3
# padding 0046594c..0046594f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 4, 1, 0xcc
.globl _th10_00465950
_th10_00465950:
    {noimm8s} push 0x465A30  # 68305a4600
.globl _th10_00465955
_th10_00465955:
    {disp32} call _th10_00452e0a  # e8b0d4feff
.globl _th10_0046595a
_th10_0046595a:
    pop ecx  # 59
.globl _th10_0046595b
_th10_0046595b:
    ret  # c3
# padding 0046595c..0046595f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 4, 1, 0xcc
.globl _th10_00465960
_th10_00465960:
    push edi  # 57
.globl _th10_00465961
_th10_00465961:
    and dword ptr [_th10_00492588], -2  # 832588254900fe
.globl _th10_00465968
_th10_00465968:
    {load} xor eax, eax  # 33c0
.globl _th10_0046596a
_th10_0046596a:
    {noimm8s} mov ecx, 0x11  # b911000000
.globl _th10_0046596f
_th10_0046596f:
    {noimm8s} mov edi, 0x492548  # bf48254900
.globl _th10_00465974
_th10_00465974:
    rep stosd  # f3ab
.globl _th10_00465976
_th10_00465976:
    {load} mov edx, [_th10_00492548]  # 8b1548254900
.globl _th10_0046597c
_th10_0046597c:
    or edx, 2  # 83ca02
.globl _th10_0046597f
_th10_0046597f:
    {noimm8s} push 0x465A50  # 68505a4600
.globl _th10_00465984
_th10_00465984:
    {store} mov [_th10_00492548], edx  # 891548254900
.globl _th10_0046598a
_th10_0046598a:
    {disp32} call _th10_00452e0a  # e87bd4feff
.globl _th10_0046598f
_th10_0046598f:
    add esp, 4  # 83c404
.globl _th10_00465992
_th10_00465992:
    pop edi  # 5f
.globl _th10_00465993
_th10_00465993:
    ret  # c3
# padding 00465994..0046599f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 12, 1, 0xcc
.globl _th10_004659a0
_th10_004659a0:
    push edi  # 57
.globl _th10_004659a1
_th10_004659a1:
    {noimm8s} mov ecx, 0x80  # b980000000
.globl _th10_004659a6
_th10_004659a6:
    or eax, -1  # 83c8ff
.globl _th10_004659a9
_th10_004659a9:
    {noimm8s} mov edi, 0x492998  # bf98294900
.globl _th10_004659ae
_th10_004659ae:
    rep stosd  # f3ab
.globl _th10_004659b0
_th10_004659b0:
    pop edi  # 5f
.globl _th10_004659b1
_th10_004659b1:
    ret  # c3
# padding 004659b2..004659bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 14, 1, 0xcc
.globl _th10_004659c0
_th10_004659c0:
    {noimm8s} push 0x465A60  # 68605a4600
.globl _th10_004659c5
_th10_004659c5:
    {disp32} call _th10_00452e0a  # e840d4feff
.globl _th10_004659ca
_th10_004659ca:
    pop ecx  # 59
.globl _th10_004659cb
_th10_004659cb:
    ret  # c3
# padding 004659cc..004659cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 4, 1, 0xcc
.globl _th10_004659d0
_th10_004659d0:
    {noimm8s} push 0x465A70  # 68705a4600
.globl _th10_004659d5
_th10_004659d5:
    {disp32} call _th10_00452e0a  # e830d4feff
.globl _th10_004659da
_th10_004659da:
    pop ecx  # 59
.globl _th10_004659db
_th10_004659db:
    ret  # c3
# padding 004659dc..004659df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 4, 1, 0xcc
.globl _th10_004659e0
_th10_004659e0:
    {noimm8s} push 0x465A80  # 68805a4600
.globl _th10_004659e5
_th10_004659e5:
    {disp32} call _th10_00452e0a  # e820d4feff
.globl _th10_004659ea
_th10_004659ea:
    pop ecx  # 59
.globl _th10_004659eb
_th10_004659eb:
    ret  # c3
# padding 004659ec..004659ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 4, 1, 0xcc
.globl _th10_004659f0
_th10_004659f0:
    {noimm8s} mov eax, 0x491C28  # b8281c4900
.globl _th10_004659f5
_th10_004659f5:
    {disp32} jmp _th10_0041ff60  # e966a5fbff
# padding 004659fa..004659ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 6, 1, 0xcc
.globl _th10_00465a00
_th10_00465a00:
    {noimm8s} push 0x434C20  # 68204c4300
.globl _th10_00465a05
_th10_00465a05:
    push 20  # 6a14
.globl _th10_00465a07
_th10_00465a07:
    push 16  # 6a10
.globl _th10_00465a09
_th10_00465a09:
    {noimm8s} push 0x4923B0  # 68b0234900
.globl _th10_00465a0e
_th10_00465a0e:
    {disp32} call _th10_004525ff  # e8eccbfeff
.globl _th10_00465a13
_th10_00465a13:
    ret  # c3
# padding 00465a14..00465a1f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 12, 1, 0xcc
.globl _th10_00465a20
_th10_00465a20:
    push esi  # 56
.globl _th10_00465a21
_th10_00465a21:
    {noimm8s} mov esi, 0x474CB0  # beb04c4700
.globl _th10_00465a26
_th10_00465a26:
    {disp32} call _th10_00436a30  # e80510fdff
.globl _th10_00465a2b
_th10_00465a2b:
    pop esi  # 5e
.globl _th10_00465a2c
_th10_00465a2c:
    ret  # c3
# padding 00465a2d..00465a2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 3, 1, 0xcc
.globl _th10_00465a30
_th10_00465a30:
    push esi  # 56
.globl _th10_00465a31
_th10_00465a31:
    {noimm8s} mov esi, 0x474DD4  # bed44d4700
.globl _th10_00465a36
_th10_00465a36:
    {noimm8s} mov dword ptr [_th10_00474dd4], 0x4703E4  # c705d44d4700e4034700
.globl _th10_00465a40
_th10_00465a40:
    {disp32} call _th10_0044c150  # e80b67feff
.globl _th10_00465a45
_th10_00465a45:
    pop esi  # 5e
.globl _th10_00465a46
_th10_00465a46:
    ret  # c3
# padding 00465a47..00465a4f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 9, 1, 0xcc
.globl _th10_00465a50
_th10_00465a50:
    {noimm8s} push 0x492548  # 6848254900
.globl _th10_00465a55
_th10_00465a55:
    {disp32} call _th10_0043cb00  # e8a670fdff
.globl _th10_00465a5a
_th10_00465a5a:
    ret  # c3
# padding 00465a5b..00465a5f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 5, 1, 0xcc
.globl _th10_00465a60
_th10_00465a60:
    push esi  # 56
.globl _th10_00465a61
_th10_00465a61:
    {noimm8s} mov esi, 0x497990  # be90794900
.globl _th10_00465a66
_th10_00465a66:
    {disp32} call _th10_00434d10  # e8a5f2fcff
.globl _th10_00465a6b
_th10_00465a6b:
    pop esi  # 5e
.globl _th10_00465a6c
_th10_00465a6c:
    ret  # c3
# padding 00465a6d..00465a6f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 3, 1, 0xcc
.globl _th10_00465a70
_th10_00465a70:
    ret  # c3
# padding 00465a71..00465a7f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
.fill 15, 1, 0xcc
.globl _th10_00465a80
_th10_00465a80:
    ret  # c3
# padding 00465a81..00465bff: ["PE .text raw tail beyond virtual_size 0x00465A80"]
.fill 383, 1, 0x00
