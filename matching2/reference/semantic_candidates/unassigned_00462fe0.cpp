#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462FE0..0x004630CD: retained assembly entry fragments.
// Naked body preserves their retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462fe0() {
    __asm {
    L_00462fe0:
        call asm_getptd_00456357
    L_00462fe5:
        xor ecx,ecx
    L_00462fe7:
        cmp dword ptr [eax+84h],ecx
    L_00462fed:
        setne cl
    L_00462ff0:
        mov al,cl
    L_00462ff2:
        ret
    L_00462ff3:
        mov eax,dword ptr [esp+4]
    L_00462ff7:
        test eax,eax
    L_00462ff9:
        push esi
    L_00462ffa:
        push edi
    L_00462ffb:
        mov edi,dword ptr [esp+10h]
    L_00462fff:
        je short L_00463062
    L_00463001:
        mov esi,dword ptr [eax]
    L_00463003:
        test esi,esi
    L_00463005:
        je short L_00463062
    L_00463007:
        cmp dword ptr [esi],0E06D7363h
    L_0046300d:
        jne short L_00463034
    L_0046300f:
        cmp dword ptr [esi+10h],3
    L_00463013:
        jne short L_00463034
    L_00463015:
        mov eax,dword ptr [esi+14h]
    L_00463018:
        cmp eax,19930520h
    L_0046301d:
        je short L_00463026
    L_0046301f:
        cmp eax,19930521h
    L_00463024:
        jne short L_00463034
    L_00463026:
        cmp dword ptr [esi+1Ch],0
    L_0046302a:
        jne short L_00463034
    L_0046302c:
        call asm_getptd_00456357
    L_00463031:
        mov esi,dword ptr [eax+7Ch]
    L_00463034:
        push dword ptr [esi+18h]
    L_00463037:
        push edi
    L_00463038:
        call asm_CreateFrameInfo_004629eb
    L_0046303d:
        pop ecx
    L_0046303e:
        pop ecx
    L_0046303f:
        call asm_getptd_00456357
    L_00463044:
        mov eax,dword ptr [eax+7Ch]
    L_00463047:
        mov dword ptr [edi+8],eax
    L_0046304a:
        call asm_getptd_00456357
    L_0046304f:
        mov eax,dword ptr [eax+80h]
    L_00463055:
        mov dword ptr [edi+0Ch],eax
    L_00463058:
        call asm_getptd_00456357
    L_0046305d:
        mov dword ptr [eax+7Ch],esi
    L_00463060:
        jmp short L_0046306a
    L_00463062:
        or dword ptr [edi+8],0FFFFFFFFh
    L_00463066:
        or dword ptr [edi+0Ch],0FFFFFFFFh
    L_0046306a:
        call asm_getptd_00456357
    L_0046306f:
        add eax,84h
    L_00463074:
        dec dword ptr [eax]
    L_00463076:
        call asm_getptd_00456357
    L_0046307b:
        cmp dword ptr [eax+84h],0
    L_00463082:
        pop edi
    L_00463083:
        pop esi
    L_00463084:
        jge short L_00463092
    L_00463086:
        call asm_getptd_00456357
    L_0046308b:
        and dword ptr [eax+84h],0
    L_00463092:
        xor eax,eax
    L_00463094:
        inc eax
    L_00463095:
        ret
    L_00463096:
        mov eax,dword ptr [esp+4]
    L_0046309a:
        test eax,eax
    L_0046309c:
        je short L_004630cb
    L_0046309e:
        mov eax,dword ptr [eax]
    L_004630a0:
        cmp dword ptr [eax],0E06D7363h
    L_004630a6:
        jne short L_004630cb
    L_004630a8:
        cmp dword ptr [eax+10h],3
    L_004630ac:
        jne short L_004630cb
    L_004630ae:
        mov ecx,dword ptr [eax+14h]
    L_004630b1:
        cmp ecx,19930520h
    L_004630b7:
        je short L_004630c1
    L_004630b9:
        cmp ecx,19930521h
    L_004630bf:
        jne short L_004630cb
    L_004630c1:
        cmp dword ptr [eax+1Ch],0
    L_004630c5:
        jne short L_004630cb
    L_004630c7:
        xor eax,eax
    L_004630c9:
        inc eax
    L_004630ca:
        ret
    L_004630cb:
        xor eax,eax
    L_004630cd:
        ret
    }
}

struct CxxUnregisterFrame_004630ce {
    void* object;
    void* previous;
    void* saved_exception;
    void* saved_translator;
};

struct CxxExceptionRecord_004630ce {
    unsigned int code;
    unsigned int flags;
    void* nested_record;
    void* address;
    unsigned int parameter_count;
    unsigned int magic;
    void* object;
    void* throw_information;
};

static CxxExceptionRecord_004630ce* CurrentExceptionRecord_004630ce() {
    unsigned char* thread_data =
        reinterpret_cast<unsigned char*>(asm_getptd_00456357());
    return *reinterpret_cast<CxxExceptionRecord_004630ce**>(thread_data + 0x7c);
}

static void* CurrentTranslator_004630ce() {
    unsigned char* thread_data =
        reinterpret_cast<unsigned char*>(asm_getptd_00456357());
    return *reinterpret_cast<void**>(thread_data + 0x80);
}

extern "C" void __cdecl CxxUnregisterExceptionObject_004630ce(
    CxxUnregisterFrame_004630ce* frame, int unwind) {
    if (frame->saved_exception == reinterpret_cast<void*>(0xffffffffu))
        return;

    asm_FindAndUnlinkFrame_00462a34(reinterpret_cast<FrameInfo*>(frame));

    if (unwind == 0) {
        CxxExceptionRecord_004630ce* exception = CurrentExceptionRecord_004630ce();
        if (exception->code == 0xe06d7363u &&
            CurrentExceptionRecord_004630ce()->parameter_count == 3 &&
            (CurrentExceptionRecord_004630ce()->magic == 0x19930520u ||
             CurrentExceptionRecord_004630ce()->magic == 0x19930521u) &&
            asm_IsExceptionObjectToBeDestroyed_00462a13(
                CurrentExceptionRecord_004630ce()->object)) {
            typedef void (__cdecl *DestroyExceptionObject_004630ce)(void*, int);
            DestroyExceptionObject_004630ce destroy_exception_object =
                reinterpret_cast<DestroyExceptionObject_004630ce>(
                    &asm_DestructExceptionObject_00462f7c);
            destroy_exception_object(CurrentExceptionRecord_004630ce(), 1);
        }
    }

    frame->saved_exception = CurrentExceptionRecord_004630ce();
    frame->saved_translator = CurrentTranslator_004630ce();
}
