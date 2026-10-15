#include "../../build_support/include/asm_symbols.hpp"

typedef void (__cdecl *ImportThunkTarget)();

// Structural ownership is exactly forty independent six-byte import slots:
// 0x00452332..0x00452421. The preceding 0x0045232C..0x00452331 bytes
// are foreign-owned (WINNLSEnableIME), and 0x00452422 starts free().
// Each body is a compiler-emitted tail jump through its fixed import slot.

// 0x00452332: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452332() {
    ((ImportThunkTarget)(*(void **)(&imp_DialogBoxParamA)))();
}

// 0x00452338: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452338() {
    ((ImportThunkTarget)(*(void **)(&imp_LoadCursorA)))();
}

// 0x0045233E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045233e() {
    ((ImportThunkTarget)(*(void **)(&imp_GetSystemMetrics)))();
}

// 0x00452344: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452344() {
    ((ImportThunkTarget)(*(void **)(&imp_SystemParametersInfoA)))();
}

// 0x0045234A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045234a() {
    ((ImportThunkTarget)(*(void **)(&imp_DispatchMessageA)))();
}

// 0x00452350: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452350() {
    ((ImportThunkTarget)(*(void **)(&imp_IsDlgButtonChecked)))();
}

// 0x00452356: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452356() {
    ((ImportThunkTarget)(*(void **)(&imp_ShowWindow)))();
}

// 0x0045235C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045235c() {
    ((ImportThunkTarget)(*(void **)(&imp_DefWindowProcA)))();
}

// 0x00452362: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452362() {
    ((ImportThunkTarget)(*(void **)(&imp_EndDialog)))();
}

// 0x00452368: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452368() {
    ((ImportThunkTarget)(*(void **)(&imp_GetDlgItem)))();
}

// 0x0045236E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045236e() {
    ((ImportThunkTarget)(*(void **)(&imp_PeekMessageA)))();
}

// 0x00452374: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452374() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateWindowExA)))();
}

// 0x0045237A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045237a() {
    ((ImportThunkTarget)(*(void **)(&imp_MessageBoxA)))();
}

// 0x00452380: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452380() {
    ((ImportThunkTarget)(*(void **)(&imp_ShowCursor)))();
}

// 0x00452386: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452386() {
    ((ImportThunkTarget)(*(void **)(&imp_TranslateMessage)))();
}

// 0x0045238C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045238c() {
    ((ImportThunkTarget)(*(void **)(&imp_SendMessageA)))();
}

// 0x00452392: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452392() {
    ((ImportThunkTarget)(*(void **)(&imp_SetForegroundWindow)))();
}

// 0x00452398: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452398() {
    ((ImportThunkTarget)(*(void **)(&imp_SetCursor)))();
}

// 0x0045239E: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045239e() {
    ((ImportThunkTarget)(*(void **)(&imp_DestroyWindow)))();
}

// 0x004523A4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523a4() {
    ((ImportThunkTarget)(*(void **)(&imp_GetWindowLongA)))();
}

// 0x004523AA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523aa() {
    ((ImportThunkTarget)(*(void **)(&imp_SetTimer)))();
}

// 0x004523B0: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523b0() {
    ((ImportThunkTarget)(*(void **)(&imp_KillTimer)))();
}

// 0x004523B6: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523b6() {
    ((ImportThunkTarget)(*(void **)(&imp_PostThreadMessageA)))();
}

// 0x004523BC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523bc() {
    ((ImportThunkTarget)(*(void **)(&imp_MsgWaitForMultipleObjects)))();
}

// 0x004523C2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523c2() {
    ((ImportThunkTarget)(*(void **)(&imp_GetKeyboardState)))();
}

// 0x004523C8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523c8() {
    ((ImportThunkTarget)(*(void **)(&imp_SetKeyboardState)))();
}

// 0x004523CE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523ce() {
    ((ImportThunkTarget)(*(void **)(&imp_FindWindowA)))();
}

// 0x004523D4: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523d4() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateFontA)))();
}

// 0x004523DA: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523da() {
    ((ImportThunkTarget)(*(void **)(&imp_DeleteObject)))();
}

// 0x004523E0: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523e0() {
    ((ImportThunkTarget)(*(void **)(&imp_SelectObject)))();
}

// 0x004523E6: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523e6() {
    ((ImportThunkTarget)(*(void **)(&imp_DeleteDC)))();
}

// 0x004523EC: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523ec() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateDIBSection)))();
}

// 0x004523F2: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523f2() {
    ((ImportThunkTarget)(*(void **)(&imp_CreateCompatibleDC)))();
}

// 0x004523F8: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523f8() {
    ((ImportThunkTarget)(*(void **)(&imp_SetBkMode)))();
}

// 0x004523FE: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_004523fe() {
    ((ImportThunkTarget)(*(void **)(&imp_SetTextColor)))();
}

// 0x00452404: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452404() {
    ((ImportThunkTarget)(*(void **)(&imp_TextOutA)))();
}

// 0x0045240A: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045240a() {
    ((ImportThunkTarget)(*(void **)(&imp_GetStockObject)))();
}

// 0x00452410: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452410() {
    ((ImportThunkTarget)(*(void **)(&imp_CoCreateInstance)))();
}

// 0x00452416: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_00452416() {
    ((ImportThunkTarget)(*(void **)(&imp_CoUninitialize)))();
}

// 0x0045241C: import jump thunk.
extern "C" __declspec(noinline) void __cdecl semantic_import_thunk_0045241c() {
    ((ImportThunkTarget)(*(void **)(&imp_CoInitialize)))();
}
