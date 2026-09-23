// The declarations here deliberately use the audited argument types. The
// central assembly-symbol header still has the old untyped entry declaration.
struct CommitFileEntry {
    int os_handle;
    unsigned char flags;
    unsigned char padding[31];
};

extern "C" unsigned int data_004991e4;
extern "C" CommitFileEntry* data_00499200[];
extern "C" unsigned int (__stdcall *data_0046610c)();

extern "C" void __cdecl asm_lock_fhandle_0045f715(int fd);
extern "C" int __cdecl asm_get_osfhandle_0045f6d4(int fd);
extern "C" void __cdecl asm_FUN_0045f7b5_0045f7b5(int fd);
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb();
extern "C" unsigned int __stdcall import_FlushFileBuffers_004626be(
    unsigned int handle);
extern "C" void __cdecl asm_SEH_epilog_00454bf7();

// 0x004614A9..0x00461550: __commit
// The retail function accepts one descriptor on the stack and returns its
// status in EAX. Its finally state releases the descriptor lock on exceptions.
extern "C" int __cdecl asm_commit_004614a9(int fd) {
    if (static_cast<unsigned int>(fd) >= data_004991e4) {
        *asm_FUN_00456af2_00456af2() = 9;
        return -1;
    }

    const unsigned int descriptor = static_cast<unsigned int>(fd);
    CommitFileEntry* const entry =
        &data_00499200[descriptor >> 5][descriptor & 0x1f];
    if ((entry->flags & 1) == 0) {
        *asm_FUN_00456af2_00456af2() = 9;
        return -1;
    }

    asm_lock_fhandle_0045f715(fd);

    int result = -1;
    __try {
        if ((entry->flags & 1) == 0) {
            *asm_FUN_00456af2_00456af2() = 9;
        } else {
            const int os_handle = asm_get_osfhandle_0045f6d4(fd);
            unsigned int win32_error = 0;
            if (import_FlushFileBuffers_004626be(
                    static_cast<unsigned int>(os_handle)) == 0) {
                win32_error = data_0046610c();
            }

            if (win32_error == 0) {
                result = 0;
            } else {
                *asm_FUN_00456afb_00456afb() = win32_error;
                *asm_FUN_00456af2_00456af2() = 9;
            }
        }
    } __finally {
        // 0x00461549 releases the same per-descriptor critical section.
        asm_FUN_0045f7b5_0045f7b5(fd);
    }

    return result;
}

// 0x00461551..0x00461564: __commit error/SEH tail
// Keep the retail entry and epilog sequence intact for its own address range.
extern "C" __declspec(naked) void __cdecl asm_commit_part_00461551() {
    __asm {
    L_00461551:
        call asm_FUN_00456af2_00456af2
    L_00461556:
        mov dword ptr [eax],9
    L_0046155c:
        or eax,0FFFFFFFFh
    L_0046155f:
        call asm_SEH_epilog_00454bf7
    L_00461564:
        ret
    }
}
