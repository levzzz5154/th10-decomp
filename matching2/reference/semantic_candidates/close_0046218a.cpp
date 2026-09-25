#include "asm_encoding.hpp"

struct CloseFileEntry {
    unsigned int os_handle;
    unsigned char flags;
    unsigned char padding[31];
};

extern "C" unsigned int data_004991e4;
extern "C" CloseFileEntry* data_00499200[];

extern "C" void __cdecl asm_lock_fhandle_0045f715(int file);
extern "C" int __cdecl asm_close_lk_00462107(unsigned int file);
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb();
extern "C" void __cdecl asm_FUN_0045f7b5_0045f7b5(int file);
extern "C" void __cdecl asm_SEH_epilog_00454bf7();

static bool close_descriptor_is_open(unsigned int file) {
    CloseFileEntry* block = data_00499200[file >> 5];
    return (block[file & 0x1f].flags & 1) != 0;
}

static int close_invalid_descriptor() {
    *asm_FUN_00456af2_00456af2() = 9;
    *asm_FUN_00456afb_00456afb() = 0;
    return -1;
}

struct CloseUnlockGuard {
    int file;

    explicit CloseUnlockGuard(int descriptor) : file(descriptor) {}
    ~CloseUnlockGuard() { asm_FUN_0045f7b5_0045f7b5(file); }
};

// 0x0046218A..0x004621FD: __close
// One cdecl descriptor argument; the caller cleans the stack.
extern "C" int __cdecl Close_0046218A(unsigned int file) {
    if (file >= data_004991e4 || !close_descriptor_is_open(file))
        return close_invalid_descriptor();

    asm_lock_fhandle_0045f715(static_cast<int>(file));
    CloseUnlockGuard unlock(static_cast<int>(file));

    // The open bit is re-read after acquiring the descriptor lock.
    if (!close_descriptor_is_open(file)) {
        *asm_FUN_00456af2_00456af2() = 9;
        return -1;
    }

    return asm_close_lk_00462107(file);
}

// 0x00462209..0x00462224: __close
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_close_part_00462209() {
    __asm {
    L_00462209:
        call asm_FUN_00456af2_00456af2
    L_0046220e:
        mov dword ptr [eax],9
    L_00462214:
        call asm_FUN_00456afb_00456afb
    L_00462219:
        and dword ptr [eax],0
    L_0046221c:
        or eax,0FFFFFFFFh
    L_0046221f:
        call asm_SEH_epilog_00454bf7
    L_00462224:
        ret
    }
}
