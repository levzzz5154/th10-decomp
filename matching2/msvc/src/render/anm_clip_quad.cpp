// BLOCKED (D3807): closest_byte_count=24/472; first_diff=0x004462F0;
// residual_class=private EAX host receiver, D3D device/buffer vtable calls,
// and the retail 20-dword copy into the fixed render buffer. Live Ghidra
// decompilation confirms the host offsets and global mirror stores, but an
// ordinary readable candidate under MSVC 13.10 emitted a 481-byte body
// (24 comparable bytes), so it was not a production-valid replacement.
// variants_tested=live Ghidra decompile at 0x004462F0; archived readable
// ClipQuadHost/ClipQuadEnv model; standalone MSVC 13.10 candidate with raw
// host offsets and RenderDevice vtable declarations (481-byte extent).
// next_lever=caller-inclusive schema-2 native-LTCG cluster over real caller
// 0x0042025B, this body, and the D3D device/vertex-buffer callees, with the
// 0x3ADA74 buffer and 0x00491C30 device layouts bound; promote only after
// the complete 472-byte region is exact.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004462F0..0x004464C7: FUN_004462f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004462f0_004462f0() {
    __asm {
    L_004462f0:
        push ecx
    L_004462f1:
        push ebx
    L_004462f2:
        push ebp
    L_004462f3:
        push esi
    L_004462f4:
        push edi
    L_004462f5:
        xor ebp,ebp
    L_004462f7:
        mov dword ptr [eax+3ADA80h],ebp
    L_004462fd:
        mov dword ptr [eax+3ADABCh],ebp
    L_00446303:
        mov dword ptr [eax+3ADAA8h],ebp
    L_00446309:
        mov dword ptr [eax+3ADA94h],ebp
    L_0044630f:
        mov dword ptr [eax+3ADAACh],ebp
    L_00446315:
        mov dword ptr [eax+3ADA84h],ebp
    L_0044631b:
        mov dword ptr [eax+3ADA9Ch],ebp
    L_00446321:
        mov dword ptr [eax+3ADA88h],ebp
    L_00446327:
        mov ecx,43000000h
    L_0044632c:
        mov dword ptr [eax+3ADAB4h],ecx
    L_00446332:
        mov dword ptr [eax+3ADA8Ch],ecx
    L_00446338:
        mov dword ptr [eax+3ADAB8h],ecx
    L_0044633e:
        mov dword ptr [eax+3ADAA4h],ecx
    L_00446344:
        mov ecx,3F800000h
    L_00446349:
        mov dword ptr [eax+3ADAC4h],ecx
    L_0044634f:
        mov dword ptr [eax+3ADAB0h],ecx
    L_00446355:
        mov dword ptr [eax+3ADAC0h],ecx
    L_0044635b:
        mov dword ptr [eax+3ADA98h],ecx
    L_00446361:
        mov edx,0C3000000h
    L_00446366:
        mov dword ptr [eax+3ADAA0h],edx
    L_0044636c:
        mov dword ptr [eax+3ADA78h],edx
    L_00446372:
        mov dword ptr [eax+3ADA90h],edx
    L_00446378:
        mov dword ptr [eax+3ADA7Ch],edx
    L_0044637e:
        lea esi,[eax+3ADA78h]
    L_00446384:
        mov ecx,esi
    L_00446386:
        mov edx,dword ptr [ecx]
    L_00446388:
        mov dword ptr [data_00497930],edx
    L_0044638e:
        mov edx,dword ptr [ecx+4]
    L_00446391:
        mov dword ptr [data_00497934],edx
    L_00446397:
        mov ecx,dword ptr [ecx+8]
    L_0044639a:
        mov dword ptr [data_00497938],ecx
    L_004463a0:
        mov edx,dword ptr [eax+3ADA8Ch]
    L_004463a6:
        mov dword ptr [data_00497948],edx
    L_004463ac:
        mov ecx,dword ptr [eax+3ADA90h]
    L_004463b2:
        mov dword ptr [data_0049794c],ecx
    L_004463b8:
        mov edx,dword ptr [eax+3ADA94h]
    L_004463be:
        mov dword ptr [data_00497950],edx
    L_004463c4:
        mov ecx,dword ptr [eax+3ADAA0h]
    L_004463ca:
        mov dword ptr [data_00497960],ecx
    L_004463d0:
        mov edx,dword ptr [eax+3ADAA4h]
    L_004463d6:
        mov dword ptr [data_00497964],edx
    L_004463dc:
        mov ecx,dword ptr [eax+3ADAA8h]
    L_004463e2:
        mov dword ptr [data_00497968],ecx
    L_004463e8:
        mov edx,dword ptr [eax+3ADAB4h]
    L_004463ee:
        mov dword ptr [data_00497978],edx
    L_004463f4:
        mov ecx,dword ptr [eax+3ADAB8h]
    L_004463fa:
        mov dword ptr [data_0049797c],ecx
    L_00446400:
        mov edx,dword ptr [eax+3ADABCh]
    L_00446406:
        mov dword ptr [data_00497980],edx
    L_0044640c:
        mov ecx,dword ptr [eax+3ADA84h]
    L_00446412:
        mov dword ptr [data_00497940],ecx
    L_00446418:
        mov edx,dword ptr [eax+3ADA88h]
    L_0044641e:
        mov dword ptr [data_00497944],edx
    L_00446424:
        mov ecx,dword ptr [eax+3ADA98h]
    L_0044642a:
        mov dword ptr [data_00497958],ecx
    L_00446430:
        mov edx,dword ptr [eax+3ADA9Ch]
    L_00446436:
        mov dword ptr [data_0049795c],edx
    L_0044643c:
        mov ecx,dword ptr [eax+3ADAACh]
    L_00446442:
        push ebp
    L_00446443:
        mov dword ptr [data_00497970],ecx
    L_00446449:
        mov edx,dword ptr [eax+3ADAB0h]
    L_0044644f:
        lea ebx,[eax+3ADA74h]
    L_00446455:
        push ebx
    L_00446456:
        push 1
    L_00446458:
        mov dword ptr [data_00497974],edx
    L_0044645e:
        mov ecx,dword ptr [eax+3ADAC0h]
    L_00446464:
        push 102h
    L_00446469:
        mov dword ptr [data_00497988],ecx
    L_0044646f:
        mov edx,dword ptr [eax+3ADAC4h]
    L_00446475:
        mov ecx,dword ptr [data_00491c30]
    L_0044647b:
        push ebp
    L_0044647c:
        push 50h
    L_0044647e:
        mov dword ptr [data_0049798c],edx
    L_00446484:
        mov eax,dword ptr [ecx]
    L_00446486:
        push ecx
    L_00446487:
        call dword ptr [eax+68h]
    L_0044648a:
        mov eax,dword ptr [ebx]
    L_0044648c:
        mov ecx,dword ptr [eax]
    L_0044648e:
        push ebp
    L_0044648f:
        lea edx,[esp+14h]
    L_00446493:
        push edx
    L_00446494:
        push ebp
    L_00446495:
        push ebp
    L_00446496:
        push eax
    L_00446497:
        call dword ptr [ecx+2Ch]
    L_0044649a:
        mov edi,dword ptr [esp+10h]
    L_0044649e:
        mov ecx,14h
    L_004464a3:
        rep movsd
    L_004464a5:
        mov eax,dword ptr [ebx]
    L_004464a7:
        mov ecx,dword ptr [eax]
    L_004464a9:
        push eax
    L_004464aa:
        call dword ptr [ecx+30h]
    L_004464ad:
        mov ecx,dword ptr [ebx]
    L_004464af:
        mov eax,dword ptr [data_00491c30]
    L_004464b4:
        mov edx,dword ptr [eax]
    L_004464b6:
        push 14h
    L_004464b8:
        push ebp
    L_004464b9:
        push ecx
    L_004464ba:
        push ebp
    L_004464bb:
        push eax
    L_004464bc:
        call dword ptr [edx+190h]
    L_004464c2:
        pop edi
    L_004464c3:
        pop esi
    L_004464c4:
        pop ebp
    L_004464c5:
        pop ebx
    L_004464c6:
        pop ecx
    L_004464c7:
        ret
    }
}
