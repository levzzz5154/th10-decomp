#include "asm_symbols.hpp"
typedef void (__cdecl *ImportThunkTarget)();

// Structural ownership is intentionally one retail import thunk per six-byte
// slot: 0x004521DC..0x0045232B. The preceding slots at 0x004521D0 and
// 0x004521D6 belong to foreign functions, while 0x0045232C..0x00452331 is
// unclaimed and the next owned slot begins in unassigned_00452332.cpp.
// Each body is a compiler-emitted tail jump through its fixed import slot.

// 0x004521DC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521dc() {
    ((ImportThunkTarget)(*(void **)(&data_00466270)))();
}

// 0x004521E2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521e2() {
    ((ImportThunkTarget)(*(void **)(&data_00466274)))();
}

// 0x004521E8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521e8() {
    ((ImportThunkTarget)(*(void **)(&data_00466278)))();
}

// 0x004521EE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521ee() {
    ((ImportThunkTarget)(*(void **)(&data_004662ac)))();
}

// 0x004521F4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521f4() {
    ((ImportThunkTarget)(*(void **)(&data_004662a8)))();
}

// 0x004521FA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521fa() {
    ((ImportThunkTarget)(*(void **)(&data_004662a4)))();
}

// 0x00452200: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452200() {
    ((ImportThunkTarget)(*(void **)(&data_004662a0)))();
}

// 0x00452206: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452206() {
    ((ImportThunkTarget)(*(void **)(&data_0046629c)))();
}

// 0x0045220C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045220c() {
    ((ImportThunkTarget)(*(void **)(&data_00466298)))();
}

// 0x00452212: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452212() {
    ((ImportThunkTarget)(*(void **)(&data_00466294)))();
}

// 0x00452218: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452218() {
    ((ImportThunkTarget)(*(void **)(&data_00466290)))();
}

// 0x0045221E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045221e() {
    ((ImportThunkTarget)(*(void **)(&data_0046628c)))();
}

// 0x00452224: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452224() {
    ((ImportThunkTarget)(*(void **)(&data_00466288)))();
}

// 0x0045222A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045222a() {
    ((ImportThunkTarget)(*(void **)(&data_00466284)))();
}

// 0x00452230: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452230() {
    ((ImportThunkTarget)(*(void **)(&data_00466280)))();
}

// 0x00452236: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452236() {
    ((ImportThunkTarget)(*(void **)(&data_0046627c)))();
}

// 0x0045223C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045223c() {
    ((ImportThunkTarget)(*(void **)(&data_004660a0)))();
}

// 0x00452242: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452242() {
    ((ImportThunkTarget)(*(void **)(&data_004660a4)))();
}

// 0x00452248: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452248() {
    ((ImportThunkTarget)(*(void **)(&data_004660a8)))();
}

// 0x0045224E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045224e() {
    ((ImportThunkTarget)(*(void **)(&data_004660ac)))();
}

// 0x00452254: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452254() {
    ((ImportThunkTarget)(*(void **)(&data_004660b0)))();
}

// 0x0045225A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045225a() {
    ((ImportThunkTarget)(*(void **)(&data_004660b4)))();
}

// 0x00452260: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452260() {
    ((ImportThunkTarget)(*(void **)(&data_004660b8)))();
}

// 0x00452266: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452266() {
    ((ImportThunkTarget)(*(void **)(&data_004660bc)))();
}

// 0x0045226C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045226c() {
    ((ImportThunkTarget)(*(void **)(&data_004660c0)))();
}

// 0x00452272: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452272() {
    ((ImportThunkTarget)(*(void **)(&data_004660c4)))();
}

// 0x00452278: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452278() {
    ((ImportThunkTarget)(*(void **)(&data_004660c8)))();
}

// 0x0045227E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045227e() {
    ((ImportThunkTarget)(*(void **)(&data_004660cc)))();
}

// 0x00452284: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452284() {
    ((ImportThunkTarget)(*(void **)(&data_004660d0)))();
}

// 0x0045228A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045228a() {
    ((ImportThunkTarget)(*(void **)(&data_004660d4)))();
}

// 0x00452290: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452290() {
    ((ImportThunkTarget)(*(void **)(&data_004660d8)))();
}

// 0x00452296: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452296() {
    ((ImportThunkTarget)(*(void **)(&data_004660dc)))();
}

// 0x0045229C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045229c() {
    ((ImportThunkTarget)(*(void **)(&data_004660e0)))();
}

// 0x004522A2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522a2() {
    ((ImportThunkTarget)(*(void **)(&data_004660e4)))();
}

// 0x004522A8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522a8() {
    ((ImportThunkTarget)(*(void **)(&data_004660e8)))();
}

// 0x004522AE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522ae() {
    ((ImportThunkTarget)(*(void **)(&data_004660ec)))();
}

// 0x004522B4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522b4() {
    ((ImportThunkTarget)(*(void **)(&data_004661dc)))();
}

// 0x004522BA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522ba() {
    ((ImportThunkTarget)(*(void **)(&data_004660f4)))();
}

// 0x004522C0: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522c0() {
    ((ImportThunkTarget)(*(void **)(&data_004660f8)))();
}

// 0x004522C6: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522c6() {
    ((ImportThunkTarget)(*(void **)(&data_004660fc)))();
}

// 0x004522CC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522cc() {
    ((ImportThunkTarget)(*(void **)(&data_00466100)))();
}

// 0x004522D2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522d2() {
    ((ImportThunkTarget)(*(void **)(&data_00466104)))();
}

// 0x004522D8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522d8() {
    ((ImportThunkTarget)(*(void **)(&data_00466108)))();
}

// 0x004522DE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522de() {
    ((ImportThunkTarget)(*(void **)(&data_0046610c)))();
}

// 0x004522E4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522e4() {
    ((ImportThunkTarget)(*(void **)(&data_00466110)))();
}

// 0x004522EA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522ea() {
    ((ImportThunkTarget)(*(void **)(&data_00466114)))();
}

// 0x004522F0: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522f0() {
    ((ImportThunkTarget)(*(void **)(&data_00466118)))();
}

// 0x004522F6: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522f6() {
    ((ImportThunkTarget)(*(void **)(&data_0046611c)))();
}

// 0x004522FC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522fc() {
    ((ImportThunkTarget)(*(void **)(&data_00466120)))();
}

// 0x00452302: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452302() {
    ((ImportThunkTarget)(*(void **)(&data_00466124)))();
}

// 0x00452308: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452308() {
    ((ImportThunkTarget)(*(void **)(&data_00466128)))();
}

// 0x0045230E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045230e() {
    ((ImportThunkTarget)(*(void **)(&data_0046612c)))();
}

// 0x00452314: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452314() {
    ((ImportThunkTarget)(*(void **)(&data_00466130)))();
}

// 0x0045231A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045231a() {
    ((ImportThunkTarget)(*(void **)(&data_00466268)))();
}

// 0x00452320: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452320() {
    ((ImportThunkTarget)(*(void **)(&data_004661f4)))();
}

// 0x00452326: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452326() {
    ((ImportThunkTarget)(*(void **)(&data_004661f8)))();
}
