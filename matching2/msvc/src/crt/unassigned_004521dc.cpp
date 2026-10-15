#include "../../build_support/include/asm_symbols.hpp"
typedef void (__cdecl *ImportThunkTarget)();

// Structural ownership is intentionally one retail import thunk per six-byte
// slot: 0x004521DC..0x0045232B. The preceding slots at 0x004521D0 and
// 0x004521D6 belong to foreign functions, while 0x0045232C..0x00452331 is
// unclaimed and the next owned slot begins in unassigned_00452332.cpp.
// Each body is a compiler-emitted tail jump through its fixed import slot.

// 0x004521DC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521dc() {
    ((ImportThunkTarget)(*(void **)(&imp_timeGetTime)))();
}

// 0x004521E2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521e2() {
    ((ImportThunkTarget)(*(void **)(&imp_timeEndPeriod)))();
}

// 0x004521E8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521e8() {
    ((ImportThunkTarget)(*(void **)(&imp_timeBeginPeriod)))();
}

// 0x004521EE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521ee() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutOpen)))();
}

// 0x004521F4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521f4() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutReset)))();
}

// 0x004521FA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004521fa() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutClose)))();
}

// 0x00452200: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452200() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutPrepareHeader)))();
}

// 0x00452206: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452206() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutLongMsg)))();
}

// 0x0045220C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045220c() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutShortMsg)))();
}

// 0x00452212: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452212() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutGetDevCapsA)))();
}

// 0x00452218: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452218() {
    ((ImportThunkTarget)(*(void **)(&imp_timeGetDevCaps)))();
}

// 0x0045221E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045221e() {
    ((ImportThunkTarget)(*(void **)(&imp_timeSetEvent)))();
}

// 0x00452224: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452224() {
    ((ImportThunkTarget)(*(void **)(&imp_timeKillEvent)))();
}

// 0x0045222A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045222a() {
    ((ImportThunkTarget)(*(void **)(&imp_midiOutUnprepareHeader)))();
}

// 0x00452230: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452230() {
    ((ImportThunkTarget)(*(void **)(&imp_joyGetPosEx)))();
}

// 0x00452236: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452236() {
    ((ImportThunkTarget)(*(void **)(&imp_joyGetDevCapsA)))();
}

// 0x0045223C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045223c() {
    ((ImportThunkTarget)(*(void **)(&imp_FindFirstFileA)))();
}

// 0x00452242: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452242() {
    ((ImportThunkTarget)(*(void **)(&imp_FindNextFileA)))();
}

// 0x00452248: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452248() {
    ((ImportThunkTarget)(*(void **)(&imp_FindClose)))();
}

// 0x0045224E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045224e() {
    ((ImportThunkTarget)(*(void **)(&imp_Sleep)))();
}

// 0x00452254: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452254() {
    ((ImportThunkTarget)(*(void **)(&imp_EnterCriticalSection)))();
}

// 0x0045225A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045225a() {
    ((ImportThunkTarget)(*(void **)(&imp_LeaveCriticalSection)))();
}

// 0x00452260: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452260() {
    ((ImportThunkTarget)(*(void **)(&imp_InitializeCriticalSection)))();
}

// 0x00452266: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452266() {
    ((ImportThunkTarget)(*(void **)(&imp_DeleteCriticalSection)))();
}

// 0x0045226C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045226c() {
    ((ImportThunkTarget)(*(void **)(&imp_DeleteFileA)))();
}

// 0x00452272: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452272() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateFileA)))();
}

// 0x00452278: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452278() {
    ((ImportThunkTarget)(*(void **)(&imp_SetFilePointer)))();
}

// 0x0045227E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045227e() {
    ((ImportThunkTarget)(*(void **)(&imp_CloseHandle)))();
}

// 0x00452284: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452284() {
    ((ImportThunkTarget)(*(void **)(&imp_ReadFile)))();
}

// 0x0045228A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045228a() {
    ((ImportThunkTarget)(*(void **)(&imp_WriteFile)))();
}

// 0x00452290: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452290() {
    ((ImportThunkTarget)(*(void **)(&imp_GetFileSize)))();
}

// 0x00452296: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452296() {
    ((ImportThunkTarget)(*(void **)(&imp_GetModuleFileNameA)))();
}

// 0x0045229C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045229c() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateProcessA)))();
}

// 0x004522A2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522a2() {
    ((ImportThunkTarget)(*(void **)(&imp_GetExitCodeProcess)))();
}

// 0x004522A8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522a8() {
    ((ImportThunkTarget)(*(void **)(&imp_FindResourceA)))();
}

// 0x004522AE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522ae() {
    ((ImportThunkTarget)(*(void **)(&imp_LoadResource)))();
}

// 0x004522B4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522b4() {
    ((ImportThunkTarget)(*(void **)(&imp_LockResource)))();
}

// 0x004522BA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522ba() {
    ((ImportThunkTarget)(*(void **)(&imp_FreeResource)))();
}

// 0x004522C0: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522c0() {
    ((ImportThunkTarget)(*(void **)(&imp_SizeofResource)))();
}

// 0x004522C6: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522c6() {
    ((ImportThunkTarget)(*(void **)(&imp_QueryPerformanceCounter)))();
}

// 0x004522CC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522cc() {
    ((ImportThunkTarget)(*(void **)(&imp_GetConsoleTitleA)))();
}

// 0x004522D2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522d2() {
    ((ImportThunkTarget)(*(void **)(&imp_MultiByteToWideChar)))();
}

// 0x004522D8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522d8() {
    ((ImportThunkTarget)(*(void **)(&imp_GetStartupInfoA)))();
}

// 0x004522DE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522de() {
    ((ImportThunkTarget)(*(void **)(&imp_GetLastError)))();
}

// 0x004522E4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522e4() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateMutexA)))();
}

// 0x004522EA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522ea() {
    ((ImportThunkTarget)(*(void **)(&imp_QueryPerformanceFrequency)))();
}

// 0x004522F0: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522f0() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateThread)))();
}

// 0x004522F6: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522f6() {
    ((ImportThunkTarget)(*(void **)(&imp_WaitForSingleObject)))();
}

// 0x004522FC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004522fc() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateEventA)))();
}

// 0x00452302: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452302() {
    ((ImportThunkTarget)(*(void **)(&imp_FormatMessageA)))();
}

// 0x00452308: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452308() {
    ((ImportThunkTarget)(*(void **)(&imp_LocalFree)))();
}

// 0x0045230E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045230e() {
    ((ImportThunkTarget)(*(void **)(&imp_GetVersionExA)))();
}

// 0x00452314: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452314() {
    ((ImportThunkTarget)(*(void **)(&imp_ResumeThread)))();
}

// 0x0045231A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045231a() {
    ((ImportThunkTarget)(*(void **)(&imp_DrawTextA)))();
}

// 0x00452320: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452320() {
    ((ImportThunkTarget)(*(void **)(&imp_MoveWindow)))();
}

// 0x00452326: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452326() {
    ((ImportThunkTarget)(*(void **)(&imp_RegisterClassA)))();
}
