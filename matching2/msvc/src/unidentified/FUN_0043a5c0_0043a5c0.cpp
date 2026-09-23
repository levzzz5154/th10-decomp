#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (H2901): the live Ghidra program has no Function at 0x0043A5C0, but
// disassembles the owned 63-byte range 0x0043A5C0..0x0043A5FE exactly. No
// reference enters any byte in the range; the only in-range control-flow xref
// is the loop back-edge from 0x0043A5EE to 0x0043A5E6. Outgoing references are
// the cookie read at 0x0043A5C3, the import slot at 0x00466294 from 0x0043A5D6,
// and __security_check_cookie at 0x00458EA5 from 0x0043A5F6. Ghidra identifies
// that slot as midiOutGetDevCapsA. Its arguments are the device ID from ECX,
// a local 0x34-byte MIDIOUTCAPSA record, and the size 0x34; the code copies its
// szPname field (offset 8) including the terminator to the destination pointer
// live in ESI. The API result is ignored. The epilogue verifies the stack cookie
// against 0x00473660; __security_check_cookie returns on a match and transfers
// to the failure routine on mismatch. This behavior is inferred from the import
// xref and the retail instructions.
// A normal MSVC x86 C++ prototype cannot bind the destination input to ESI:
// __fastcall binds its second argument to EDX, while the other standard C++
// conventions use stack arguments. Keep this exact naked body until a real
// caller/native LTCG cluster supplies the private ECX/ESI contract.
// Boundary evidence: the preceding sequence returns at 0x0043A5BC and has an
// INT3 at 0x0043A5BF; this body returns at 0x0043A5FE, with an INT3 at
// 0x0043A5FF and the next manifest-owned semantic function at 0x0043A600.
// The manifest/linker canonical symbol remains _asm_FUN_0043a5c0_0043a5c0;
// Ghidra has no entry function or static callers here requiring a second raw
// alias. variants_tested=live boundary/xref/ABI inspection; no candidate source
// retained because the required ESI live-in is not expressible as a standard
// C++ parameter. next_lever=inspect an actual register-preserving caller or
// native LTCG cluster if one becomes available. closest_byte_count=63/63;
// first_diff=N/A for overlay; residual_class=private-ABI ECX/ESI live-ins.
// Raw body retained under the manifest's asm_FUN entry symbol.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a5c0_0043a5c0() {
    __asm {
    L_0043a5c0:
        sub esp,38h
    L_0043a5c3:
        mov eax,dword ptr [data_00473660]
    L_0043a5c8:
        xor eax,esp
    L_0043a5ca:
        mov dword ptr [esp+34h],eax
    L_0043a5ce:
        push 34h
    L_0043a5d0:
        lea eax,[esp+4]
    L_0043a5d4:
        push eax
    L_0043a5d5:
        push ecx
    L_0043a5d6:
        call dword ptr [data_00466294]
    L_0043a5dc:
        lea eax,[esp+8]
    L_0043a5e0:
        mov edx,esi
    L_0043a5e2:
        mov ecx,eax
    L_0043a5e4:
        sub edx,ecx
    L_0043a5e6:
        mov cl,byte ptr [eax]
    L_0043a5e8:
        mov byte ptr [edx+eax],cl
    L_0043a5eb:
        inc eax
    L_0043a5ec:
        test cl,cl
    L_0043a5ee:
        jne short L_0043a5e6
    L_0043a5f0:
        mov ecx,dword ptr [esp+34h]
    L_0043a5f4:
        xor ecx,esp
    L_0043a5f6:
        call asm_security_check_cookie_00458ea5
    L_0043a5fb:
        add esp,38h
    L_0043a5fe:
        ret
    }
}
