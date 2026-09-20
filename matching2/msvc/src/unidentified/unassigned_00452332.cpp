#include "asm_symbols.hpp"
// Structural ownership is exactly forty independent six-byte import slots:
// 0x00452332..0x00452421. The preceding 0x0045232C..0x00452331 bytes
// are foreign-owned (WINNLSEnableIME), and 0x00452422 starts free().
// Keep each slot as its own naked wrapper; do not merge across boundaries.

// 0x00452332: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452332() {
    __asm {
        jmp dword ptr [data_00466264]
    }
}

// 0x00452338: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452338() {
    __asm {
        jmp dword ptr [data_00466260]
    }
}

// 0x0045233E: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045233e() {
    __asm {
        jmp dword ptr [data_0046625c]
    }
}

// 0x00452344: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452344() {
    __asm {
        jmp dword ptr [data_00466258]
    }
}

// 0x0045234A: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045234a() {
    __asm {
        jmp dword ptr [data_00466254]
    }
}

// 0x00452350: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452350() {
    __asm {
        jmp dword ptr [data_00466250]
    }
}

// 0x00452356: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452356() {
    __asm {
        jmp dword ptr [data_0046624c]
    }
}

// 0x0045235C: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045235c() {
    __asm {
        jmp dword ptr [data_00466248]
    }
}

// 0x00452362: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452362() {
    __asm {
        jmp dword ptr [data_00466244]
    }
}

// 0x00452368: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452368() {
    __asm {
        jmp dword ptr [data_00466240]
    }
}

// 0x0045236E: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045236e() {
    __asm {
        jmp dword ptr [data_0046623c]
    }
}

// 0x00452374: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452374() {
    __asm {
        jmp dword ptr [data_00466238]
    }
}

// 0x0045237A: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045237a() {
    __asm {
        jmp dword ptr [data_00466234]
    }
}

// 0x00452380: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452380() {
    __asm {
        jmp dword ptr [data_00466230]
    }
}

// 0x00452386: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452386() {
    __asm {
        jmp dword ptr [data_0046622c]
    }
}

// 0x0045238C: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045238c() {
    __asm {
        jmp dword ptr [data_00466228]
    }
}

// 0x00452392: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452392() {
    __asm {
        jmp dword ptr [data_004661f0]
    }
}

// 0x00452398: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452398() {
    __asm {
        jmp dword ptr [data_00466224]
    }
}

// 0x0045239E: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045239e() {
    __asm {
        jmp dword ptr [data_00466220]
    }
}

// 0x004523A4: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523a4() {
    __asm {
        jmp dword ptr [data_0046621c]
    }
}

// 0x004523AA: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523aa() {
    __asm {
        jmp dword ptr [data_00466218]
    }
}

// 0x004523B0: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523b0() {
    __asm {
        jmp dword ptr [data_00466214]
    }
}

// 0x004523B6: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523b6() {
    __asm {
        jmp dword ptr [data_00466210]
    }
}

// 0x004523BC: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523bc() {
    __asm {
        jmp dword ptr [data_0046620c]
    }
}

// 0x004523C2: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523c2() {
    __asm {
        jmp dword ptr [data_00466208]
    }
}

// 0x004523C8: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523c8() {
    __asm {
        jmp dword ptr [data_00466204]
    }
}

// 0x004523CE: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523ce() {
    __asm {
        jmp dword ptr [data_00466200]
    }
}

// 0x004523D4: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523d4() {
    __asm {
        jmp dword ptr [data_00466034]
    }
}

// 0x004523DA: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523da() {
    __asm {
        jmp dword ptr [data_00466030]
    }
}

// 0x004523E0: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523e0() {
    __asm {
        jmp dword ptr [data_0046602c]
    }
}

// 0x004523E6: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523e6() {
    __asm {
        jmp dword ptr [data_00466028]
    }
}

// 0x004523EC: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523ec() {
    __asm {
        jmp dword ptr [data_00466024]
    }
}

// 0x004523F2: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523f2() {
    __asm {
        jmp dword ptr [data_00466020]
    }
}

// 0x004523F8: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523f8() {
    __asm {
        jmp dword ptr [data_0046601c]
    }
}

// 0x004523FE: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_004523fe() {
    __asm {
        jmp dword ptr [data_00466018]
    }
}

// 0x00452404: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452404() {
    __asm {
        jmp dword ptr [data_00466014]
    }
}

// 0x0045240A: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045240a() {
    __asm {
        jmp dword ptr [data_00466010]
    }
}

// 0x00452410: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452410() {
    __asm {
        jmp dword ptr [data_00466304]
    }
}

// 0x00452416: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_00452416() {
    __asm {
        jmp dword ptr [data_00466300]
    }
}

// 0x0045241C: import jump thunk.
extern "C" __declspec(naked) void __cdecl asm_import_thunk_0045241c() {
    __asm {
        jmp dword ptr [data_00466308]
    }
}
