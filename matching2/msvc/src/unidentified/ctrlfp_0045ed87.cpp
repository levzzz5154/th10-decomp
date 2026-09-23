// 0x0045ED87..0x0045EDAA: __ctrlfp
// This helper edits the raw 16-bit x87 control word. The standard _control87
// API uses a translated control-word representation, so it cannot replace
// this operation without changing the meaning of the arguments.
// cdecl arguments are (new_control_word, mask); EAX returns the old word
// sign-extended from 16 bits. The caller removes both arguments.
extern "C" __declspec(naked) int __cdecl asm_ctrlfp_0045ed87(
    unsigned int new_control_word,
    unsigned int mask) {
    __asm {
    L_0045ed87:
        push ebp
    L_0045ed88:
        mov ebp,esp
    L_0045ed8a:
        push ecx
    L_0045ed8b:
        wait
        fnstcw word ptr [ebp-4]
    L_0045ed8f:
        mov eax,dword ptr [ebp+0Ch]
    L_0045ed92:
        mov ecx,dword ptr [ebp+8]
    L_0045ed95:
        and ecx,dword ptr [ebp+0Ch]
    L_0045ed98:
        not eax
    L_0045ed9a:
        and eax,dword ptr [ebp-4]
    L_0045ed9d:
        or eax,ecx
    L_0045ed9f:
        mov dword ptr [ebp+0Ch],eax
    L_0045eda2:
        fldcw word ptr [ebp+0Ch]
    L_0045eda5:
        movsx eax,word ptr [ebp-4]
    L_0045eda9:
        leave
    L_0045edaa:
        ret
    }
}
