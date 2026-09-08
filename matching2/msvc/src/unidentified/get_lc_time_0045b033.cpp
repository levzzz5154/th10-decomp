#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B033..0x0045B399: __get_lc_time
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_get_lc_time_0045b033() {
    __asm {
    L_0045b033:
        push ebp
    L_0045b034:
        mov ebp,esp
    L_0045b036:
        push ecx
    L_0045b037:
        push ecx
    L_0045b038:
        test esi,esi
    L_0045b03a:
        movzx eax,word ptr [data_0047768a]
    L_0045b041:
        movzx ecx,word ptr [data_0047768c]
    L_0045b048:
        mov dword ptr [ebp-4],eax
    L_0045b04b:
        mov dword ptr [ebp-8],ecx
    L_0045b04e:
        jne short L_0045b055
    L_0045b050:
        or eax,0FFFFFFFFh
    L_0045b053:
        leave
    L_0045b054:
        ret
    L_0045b055:
        push ebx
    L_0045b056:
        push edi
    L_0045b057:
        lea ecx,[esi+4]
    L_0045b05a:
        push ecx
    L_0045b05b:
        push 31h
    L_0045b05d:
        xor ebx,ebx
    L_0045b05f:
        push eax
    L_0045b060:
        inc ebx
    L_0045b061:
        push ebx
    L_0045b062:
        call asm_FUN_0046041e_0046041e
    L_0045b067:
        mov edi,eax
    L_0045b069:
        lea eax,[esi+8]
    L_0045b06c:
        push eax
    L_0045b06d:
        push 32h
    L_0045b06f:
        push dword ptr [ebp-4]
    L_0045b072:
        push ebx
    L_0045b073:
        call asm_FUN_0046041e_0046041e
    L_0045b078:
        or edi,eax
    L_0045b07a:
        lea eax,[esi+0Ch]
    L_0045b07d:
        push eax
    L_0045b07e:
        push 33h
    L_0045b080:
        push dword ptr [ebp-4]
    L_0045b083:
        push ebx
    L_0045b084:
        call asm_FUN_0046041e_0046041e
    L_0045b089:
        or edi,eax
    L_0045b08b:
        lea eax,[esi+10h]
    L_0045b08e:
        push eax
    L_0045b08f:
        push 34h
    L_0045b091:
        push dword ptr [ebp-4]
    L_0045b094:
        push ebx
    L_0045b095:
        call asm_FUN_0046041e_0046041e
    L_0045b09a:
        add esp,40h
    L_0045b09d:
        or edi,eax
    L_0045b09f:
        lea eax,[esi+14h]
    L_0045b0a2:
        push eax
    L_0045b0a3:
        push 35h
    L_0045b0a5:
        push dword ptr [ebp-4]
    L_0045b0a8:
        push ebx
    L_0045b0a9:
        call asm_FUN_0046041e_0046041e
    L_0045b0ae:
        or edi,eax
    L_0045b0b0:
        lea eax,[esi+18h]
    L_0045b0b3:
        push eax
    L_0045b0b4:
        push 36h
    L_0045b0b6:
        push dword ptr [ebp-4]
    L_0045b0b9:
        push ebx
    L_0045b0ba:
        call asm_FUN_0046041e_0046041e
    L_0045b0bf:
        push esi
    L_0045b0c0:
        push 37h
    L_0045b0c2:
        push dword ptr [ebp-4]
    L_0045b0c5:
        or edi,eax
    L_0045b0c7:
        push ebx
    L_0045b0c8:
        call asm_FUN_0046041e_0046041e
    L_0045b0cd:
        or edi,eax
    L_0045b0cf:
        lea eax,[esi+20h]
    L_0045b0d2:
        push eax
    L_0045b0d3:
        push 2Ah
    L_0045b0d5:
        push dword ptr [ebp-4]
    L_0045b0d8:
        push ebx
    L_0045b0d9:
        call asm_FUN_0046041e_0046041e
    L_0045b0de:
        add esp,40h
    L_0045b0e1:
        or edi,eax
    L_0045b0e3:
        lea eax,[esi+24h]
    L_0045b0e6:
        push eax
    L_0045b0e7:
        push 2Bh
    L_0045b0e9:
        push dword ptr [ebp-4]
    L_0045b0ec:
        push ebx
    L_0045b0ed:
        call asm_FUN_0046041e_0046041e
    L_0045b0f2:
        or edi,eax
    L_0045b0f4:
        lea eax,[esi+28h]
    L_0045b0f7:
        push eax
    L_0045b0f8:
        push 2Ch
    L_0045b0fa:
        push dword ptr [ebp-4]
    L_0045b0fd:
        push ebx
    L_0045b0fe:
        call asm_FUN_0046041e_0046041e
    L_0045b103:
        or edi,eax
    L_0045b105:
        lea eax,[esi+2Ch]
    L_0045b108:
        push eax
    L_0045b109:
        push 2Dh
    L_0045b10b:
        push dword ptr [ebp-4]
    L_0045b10e:
        push ebx
    L_0045b10f:
        call asm_FUN_0046041e_0046041e
    L_0045b114:
        or edi,eax
    L_0045b116:
        lea eax,[esi+30h]
    L_0045b119:
        push eax
    L_0045b11a:
        push 2Eh
    L_0045b11c:
        push dword ptr [ebp-4]
    L_0045b11f:
        push ebx
    L_0045b120:
        call asm_FUN_0046041e_0046041e
    L_0045b125:
        add esp,40h
    L_0045b128:
        or edi,eax
    L_0045b12a:
        lea eax,[esi+34h]
    L_0045b12d:
        push eax
    L_0045b12e:
        push 2Fh
    L_0045b130:
        push dword ptr [ebp-4]
    L_0045b133:
        push ebx
    L_0045b134:
        call asm_FUN_0046041e_0046041e
    L_0045b139:
        or edi,eax
    L_0045b13b:
        lea eax,[esi+1Ch]
    L_0045b13e:
        push eax
    L_0045b13f:
        push 30h
    L_0045b141:
        push dword ptr [ebp-4]
    L_0045b144:
        push ebx
    L_0045b145:
        call asm_FUN_0046041e_0046041e
    L_0045b14a:
        or edi,eax
    L_0045b14c:
        lea eax,[esi+38h]
    L_0045b14f:
        push eax
    L_0045b150:
        push 44h
    L_0045b152:
        push dword ptr [ebp-4]
    L_0045b155:
        push ebx
    L_0045b156:
        call asm_FUN_0046041e_0046041e
    L_0045b15b:
        or edi,eax
    L_0045b15d:
        lea eax,[esi+3Ch]
    L_0045b160:
        push eax
    L_0045b161:
        push 45h
    L_0045b163:
        push dword ptr [ebp-4]
    L_0045b166:
        push ebx
    L_0045b167:
        call asm_FUN_0046041e_0046041e
    L_0045b16c:
        add esp,40h
    L_0045b16f:
        or edi,eax
    L_0045b171:
        lea eax,[esi+40h]
    L_0045b174:
        push eax
    L_0045b175:
        push 46h
    L_0045b177:
        push dword ptr [ebp-4]
    L_0045b17a:
        push ebx
    L_0045b17b:
        call asm_FUN_0046041e_0046041e
    L_0045b180:
        or edi,eax
    L_0045b182:
        lea eax,[esi+44h]
    L_0045b185:
        push eax
    L_0045b186:
        push 47h
    L_0045b188:
        push dword ptr [ebp-4]
    L_0045b18b:
        push ebx
    L_0045b18c:
        call asm_FUN_0046041e_0046041e
    L_0045b191:
        or edi,eax
    L_0045b193:
        lea eax,[esi+48h]
    L_0045b196:
        push eax
    L_0045b197:
        push 48h
    L_0045b199:
        push dword ptr [ebp-4]
    L_0045b19c:
        push ebx
    L_0045b19d:
        call asm_FUN_0046041e_0046041e
    L_0045b1a2:
        or edi,eax
    L_0045b1a4:
        lea eax,[esi+4Ch]
    L_0045b1a7:
        push eax
    L_0045b1a8:
        push 49h
    L_0045b1aa:
        push dword ptr [ebp-4]
    L_0045b1ad:
        push ebx
    L_0045b1ae:
        call asm_FUN_0046041e_0046041e
    L_0045b1b3:
        add esp,40h
    L_0045b1b6:
        or edi,eax
    L_0045b1b8:
        lea eax,[esi+50h]
    L_0045b1bb:
        push eax
    L_0045b1bc:
        push 4Ah
    L_0045b1be:
        push dword ptr [ebp-4]
    L_0045b1c1:
        push ebx
    L_0045b1c2:
        call asm_FUN_0046041e_0046041e
    L_0045b1c7:
        or edi,eax
    L_0045b1c9:
        lea eax,[esi+54h]
    L_0045b1cc:
        push eax
    L_0045b1cd:
        push 4Bh
    L_0045b1cf:
        push dword ptr [ebp-4]
    L_0045b1d2:
        push ebx
    L_0045b1d3:
        call asm_FUN_0046041e_0046041e
    L_0045b1d8:
        or edi,eax
    L_0045b1da:
        lea eax,[esi+58h]
    L_0045b1dd:
        push eax
    L_0045b1de:
        push 4Ch
    L_0045b1e0:
        push dword ptr [ebp-4]
    L_0045b1e3:
        push ebx
    L_0045b1e4:
        call asm_FUN_0046041e_0046041e
    L_0045b1e9:
        or edi,eax
    L_0045b1eb:
        lea eax,[esi+5Ch]
    L_0045b1ee:
        push eax
    L_0045b1ef:
        push 4Dh
    L_0045b1f1:
        push dword ptr [ebp-4]
    L_0045b1f4:
        push ebx
    L_0045b1f5:
        call asm_FUN_0046041e_0046041e
    L_0045b1fa:
        add esp,40h
    L_0045b1fd:
        or edi,eax
    L_0045b1ff:
        lea eax,[esi+60h]
    L_0045b202:
        push eax
    L_0045b203:
        push 4Eh
    L_0045b205:
        push dword ptr [ebp-4]
    L_0045b208:
        push ebx
    L_0045b209:
        call asm_FUN_0046041e_0046041e
    L_0045b20e:
        or edi,eax
    L_0045b210:
        lea eax,[esi+64h]
    L_0045b213:
        push eax
    L_0045b214:
        push 4Fh
    L_0045b216:
        push dword ptr [ebp-4]
    L_0045b219:
        push ebx
    L_0045b21a:
        call asm_FUN_0046041e_0046041e
    L_0045b21f:
        or edi,eax
    L_0045b221:
        lea eax,[esi+68h]
    L_0045b224:
        push eax
    L_0045b225:
        push 38h
    L_0045b227:
        push dword ptr [ebp-4]
    L_0045b22a:
        push ebx
    L_0045b22b:
        call asm_FUN_0046041e_0046041e
    L_0045b230:
        or edi,eax
    L_0045b232:
        lea eax,[esi+6Ch]
    L_0045b235:
        push eax
    L_0045b236:
        push 39h
    L_0045b238:
        push dword ptr [ebp-4]
    L_0045b23b:
        push ebx
    L_0045b23c:
        call asm_FUN_0046041e_0046041e
    L_0045b241:
        add esp,40h
    L_0045b244:
        or edi,eax
    L_0045b246:
        lea eax,[esi+70h]
    L_0045b249:
        push eax
    L_0045b24a:
        push 3Ah
    L_0045b24c:
        push dword ptr [ebp-4]
    L_0045b24f:
        push ebx
    L_0045b250:
        call asm_FUN_0046041e_0046041e
    L_0045b255:
        or edi,eax
    L_0045b257:
        lea eax,[esi+74h]
    L_0045b25a:
        push eax
    L_0045b25b:
        push 3Bh
    L_0045b25d:
        push dword ptr [ebp-4]
    L_0045b260:
        push ebx
    L_0045b261:
        call asm_FUN_0046041e_0046041e
    L_0045b266:
        or edi,eax
    L_0045b268:
        lea eax,[esi+78h]
    L_0045b26b:
        push eax
    L_0045b26c:
        push 3Ch
    L_0045b26e:
        push dword ptr [ebp-4]
    L_0045b271:
        push ebx
    L_0045b272:
        call asm_FUN_0046041e_0046041e
    L_0045b277:
        or edi,eax
    L_0045b279:
        lea eax,[esi+7Ch]
    L_0045b27c:
        push eax
    L_0045b27d:
        push 3Dh
    L_0045b27f:
        push dword ptr [ebp-4]
    L_0045b282:
        push ebx
    L_0045b283:
        call asm_FUN_0046041e_0046041e
    L_0045b288:
        add esp,40h
    L_0045b28b:
        or edi,eax
    L_0045b28d:
        lea eax,[esi+80h]
    L_0045b293:
        push eax
    L_0045b294:
        push 3Eh
    L_0045b296:
        push dword ptr [ebp-4]
    L_0045b299:
        push ebx
    L_0045b29a:
        call asm_FUN_0046041e_0046041e
    L_0045b29f:
        or edi,eax
    L_0045b2a1:
        lea eax,[esi+84h]
    L_0045b2a7:
        push eax
    L_0045b2a8:
        push 3Fh
    L_0045b2aa:
        push dword ptr [ebp-4]
    L_0045b2ad:
        push ebx
    L_0045b2ae:
        call asm_FUN_0046041e_0046041e
    L_0045b2b3:
        or edi,eax
    L_0045b2b5:
        lea eax,[esi+88h]
    L_0045b2bb:
        push eax
    L_0045b2bc:
        push 40h
    L_0045b2be:
        push dword ptr [ebp-4]
    L_0045b2c1:
        push ebx
    L_0045b2c2:
        call asm_FUN_0046041e_0046041e
    L_0045b2c7:
        or edi,eax
    L_0045b2c9:
        lea eax,[esi+8Ch]
    L_0045b2cf:
        push eax
    L_0045b2d0:
        push 41h
    L_0045b2d2:
        push dword ptr [ebp-4]
    L_0045b2d5:
        push ebx
    L_0045b2d6:
        call asm_FUN_0046041e_0046041e
    L_0045b2db:
        add esp,40h
    L_0045b2de:
        or edi,eax
    L_0045b2e0:
        lea eax,[esi+90h]
    L_0045b2e6:
        push eax
    L_0045b2e7:
        push 42h
    L_0045b2e9:
        push dword ptr [ebp-4]
    L_0045b2ec:
        push ebx
    L_0045b2ed:
        call asm_FUN_0046041e_0046041e
    L_0045b2f2:
        or edi,eax
    L_0045b2f4:
        lea eax,[esi+94h]
    L_0045b2fa:
        push eax
    L_0045b2fb:
        push 43h
    L_0045b2fd:
        push dword ptr [ebp-4]
    L_0045b300:
        push ebx
    L_0045b301:
        call asm_FUN_0046041e_0046041e
    L_0045b306:
        or edi,eax
    L_0045b308:
        lea eax,[esi+98h]
    L_0045b30e:
        push eax
    L_0045b30f:
        push 28h
    L_0045b311:
        push dword ptr [ebp-4]
    L_0045b314:
        push ebx
    L_0045b315:
        call asm_FUN_0046041e_0046041e
    L_0045b31a:
        or edi,eax
    L_0045b31c:
        lea eax,[esi+9Ch]
    L_0045b322:
        push eax
    L_0045b323:
        push 29h
    L_0045b325:
        push dword ptr [ebp-4]
    L_0045b328:
        push ebx
    L_0045b329:
        call asm_FUN_0046041e_0046041e
    L_0045b32e:
        add esp,40h
    L_0045b331:
        or edi,eax
    L_0045b333:
        lea eax,[esi+0A0h]
    L_0045b339:
        push eax
    L_0045b33a:
        push 1Fh
    L_0045b33c:
        push dword ptr [ebp-8]
    L_0045b33f:
        push ebx
    L_0045b340:
        call asm_FUN_0046041e_0046041e
    L_0045b345:
        or edi,eax
    L_0045b347:
        lea eax,[esi+0A4h]
    L_0045b34d:
        push eax
    L_0045b34e:
        push 20h
    L_0045b350:
        push dword ptr [ebp-8]
    L_0045b353:
        push ebx
    L_0045b354:
        call asm_FUN_0046041e_0046041e
    L_0045b359:
        or edi,eax
    L_0045b35b:
        lea eax,[esi+0A8h]
    L_0045b361:
        push eax
    L_0045b362:
        push 1003h
    L_0045b367:
        push dword ptr [ebp-8]
    L_0045b36a:
        push ebx
    L_0045b36b:
        call asm_FUN_0046041e_0046041e
    L_0045b370:
        mov ebx,dword ptr [ebp-8]
    L_0045b373:
        or edi,eax
    L_0045b375:
        lea eax,[esi+0B0h]
    L_0045b37b:
        push eax
    L_0045b37c:
        push 1009h
    L_0045b381:
        push ebx
    L_0045b382:
        push 0
    L_0045b384:
        call asm_FUN_0046041e_0046041e
    L_0045b389:
        add esp,40h
    L_0045b38c:
        or edi,eax
    L_0045b38e:
        mov dword ptr [esi+0ACh],ebx
    L_0045b394:
        mov eax,edi
    L_0045b396:
        pop edi
    L_0045b397:
        pop ebx
    L_0045b398:
        leave
    L_0045b399:
        ret
    }
}
