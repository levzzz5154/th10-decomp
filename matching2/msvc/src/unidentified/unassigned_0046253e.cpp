// Win32 import forwarding thunks. Each wrapper preserves the retail stdcall tail jump.

// HeapFree: 0x0046253E -> IAT 0x004661E8
extern "C" unsigned int (__stdcall *data_004661e8)(unsigned int a0, unsigned int a1, unsigned int a2);
extern "C" unsigned int __stdcall import_HeapFree_0046253e(unsigned int a0, unsigned int a1, unsigned int a2) {
    return data_004661e8(a0, a1, a2);
}

// HeapAlloc: 0x00462544 -> IAT 0x004661E4
extern "C" unsigned int (__stdcall *data_004661e4)(unsigned int a0, unsigned int a1, unsigned int a2);
extern "C" unsigned int __stdcall import_HeapAlloc_00462544(unsigned int a0, unsigned int a1, unsigned int a2) {
    return data_004661e4(a0, a1, a2);
}

// CreateDirectoryA: 0x0046254A -> IAT 0x004661E0
extern "C" unsigned int (__stdcall *data_004661e0)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_CreateDirectoryA_0046254a(unsigned int a0, unsigned int a1) {
    return data_004661e0(a0, a1);
}

// GetSystemTimeAsFileTime: 0x00462550 -> IAT 0x004661B0
extern "C" void (__stdcall *data_004661b0)(unsigned int a0);
extern "C" void __stdcall import_GetSystemTimeAsFileTime_00462550(unsigned int a0) {
    data_004661b0(a0);
}

// ExitThread: 0x00462556 -> IAT 0x004661AC
extern "C" void (__stdcall *data_004661ac)(unsigned int a0);
extern "C" void __stdcall import_ExitThread_00462556(unsigned int a0) {
    data_004661ac(a0);
}

// SetEnvironmentVariableA: 0x0046255C -> IAT 0x004661A8
extern "C" unsigned int (__stdcall *data_004661a8)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_SetEnvironmentVariableA_0046255c(unsigned int a0, unsigned int a1) {
    return data_004661a8(a0, a1);
}

// GetCurrentDirectoryA: 0x00462562 -> IAT 0x004661A4
extern "C" unsigned int (__stdcall *data_004661a4)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_GetCurrentDirectoryA_00462562(unsigned int a0, unsigned int a1) {
    return data_004661a4(a0, a1);
}

// SetCurrentDirectoryA: 0x00462568 -> IAT 0x004661A0
extern "C" unsigned int (__stdcall *data_004661a0)(unsigned int a0);
extern "C" unsigned int __stdcall import_SetCurrentDirectoryA_00462568(unsigned int a0) {
    return data_004661a0(a0);
}

// GetCurrentThreadId: 0x0046256E -> IAT 0x0046619C
extern "C" unsigned int (__stdcall *data_0046619c)();
extern "C" unsigned int __stdcall import_GetCurrentThreadId_0046256e() {
    return data_0046619c();
}

// GetModuleHandleA: 0x00462574 -> IAT 0x00466198
extern "C" unsigned int (__stdcall *data_00466198)(unsigned int a0);
extern "C" unsigned int __stdcall import_GetModuleHandleA_00462574(unsigned int a0) {
    return data_00466198(a0);
}

// GetCommandLineA: 0x0046257A -> IAT 0x00466194
extern "C" unsigned int (__stdcall *data_00466194)();
extern "C" unsigned int __stdcall import_GetCommandLineA_0046257a() {
    return data_00466194();
}

// HeapDestroy: 0x00462580 -> IAT 0x00466190
extern "C" unsigned int (__stdcall *data_00466190)(unsigned int a0);
extern "C" unsigned int __stdcall import_HeapDestroy_00462580(unsigned int a0) {
    return data_00466190(a0);
}

// HeapCreate: 0x00462586 -> IAT 0x0046618C
extern "C" unsigned int (__stdcall *data_0046618c)(unsigned int a0, unsigned int a1, unsigned int a2);
extern "C" unsigned int __stdcall import_HeapCreate_00462586(unsigned int a0, unsigned int a1, unsigned int a2) {
    return data_0046618c(a0, a1, a2);
}

// VirtualFree: 0x0046258C -> IAT 0x00466188
extern "C" unsigned int (__stdcall *data_00466188)(unsigned int a0, unsigned int a1, unsigned int a2);
extern "C" unsigned int __stdcall import_VirtualFree_0046258c(unsigned int a0, unsigned int a1, unsigned int a2) {
    return data_00466188(a0, a1, a2);
}

// FatalAppExitA: 0x00462592 -> IAT 0x00466180
extern "C" void (__stdcall *data_00466180)(unsigned int a0, unsigned int a1);
extern "C" void __stdcall import_FatalAppExitA_00462592(unsigned int a0, unsigned int a1) {
    data_00466180(a0, a1);
}

// VirtualAlloc: 0x00462598 -> IAT 0x0046617C
extern "C" unsigned int (__stdcall *data_0046617c)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" unsigned int __stdcall import_VirtualAlloc_00462598(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    return data_0046617c(a0, a1, a2, a3);
}

// HeapReAlloc: 0x0046259E -> IAT 0x00466178
extern "C" unsigned int (__stdcall *data_00466178)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" unsigned int __stdcall import_HeapReAlloc_0046259e(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    return data_00466178(a0, a1, a2, a3);
}

// IsBadWritePtr: 0x004625A4 -> IAT 0x00466174
extern "C" unsigned int (__stdcall *data_00466174)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_IsBadWritePtr_004625a4(unsigned int a0, unsigned int a1) {
    return data_00466174(a0, a1);
}

// TlsAlloc: 0x004625AA -> IAT 0x00466170
extern "C" unsigned int (__stdcall *data_00466170)();
extern "C" unsigned int __stdcall import_TlsAlloc_004625aa() {
    return data_00466170();
}

// SetLastError: 0x004625B0 -> IAT 0x0046616C
extern "C" void (__stdcall *data_0046616c)(unsigned int a0);
extern "C" void __stdcall import_SetLastError_004625b0(unsigned int a0) {
    data_0046616c(a0);
}

// GetCurrentThread: 0x004625B6 -> IAT 0x00466168
extern "C" unsigned int (__stdcall *data_00466168)();
extern "C" unsigned int __stdcall import_GetCurrentThread_004625b6() {
    return data_00466168();
}

// TlsFree: 0x004625BC -> IAT 0x00466164
extern "C" unsigned int (__stdcall *data_00466164)(unsigned int a0);
extern "C" unsigned int __stdcall import_TlsFree_004625bc(unsigned int a0) {
    return data_00466164(a0);
}

// TlsSetValue: 0x004625C2 -> IAT 0x00466160
extern "C" unsigned int (__stdcall *data_00466160)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_TlsSetValue_004625c2(unsigned int a0, unsigned int a1) {
    return data_00466160(a0, a1);
}

// TlsGetValue: 0x004625C8 -> IAT 0x0046615C
extern "C" unsigned int (__stdcall *data_0046615c)(unsigned int a0);
extern "C" unsigned int __stdcall import_TlsGetValue_004625c8(unsigned int a0) {
    return data_0046615c(a0);
}

// GetProcAddress: 0x004625CE -> IAT 0x00466158
extern "C" unsigned int (__stdcall *data_00466158)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_GetProcAddress_004625ce(unsigned int a0, unsigned int a1) {
    return data_00466158(a0, a1);
}

// WideCharToMultiByte: 0x004625D4 -> IAT 0x00466154
extern "C" unsigned int (__stdcall *data_00466154)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7);
extern "C" unsigned int __stdcall import_WideCharToMultiByte_004625d4(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7) {
    return data_00466154(a0, a1, a2, a3, a4, a5, a6, a7);
}

// GetTimeZoneInformation: 0x004625DA -> IAT 0x00466150
extern "C" unsigned int (__stdcall *data_00466150)(unsigned int a0);
extern "C" unsigned int __stdcall import_GetTimeZoneInformation_004625da(unsigned int a0) {
    return data_00466150(a0);
}

// ExitProcess: 0x004625E0 -> IAT 0x0046614C
extern "C" void (__stdcall *data_0046614c)(unsigned int a0);
extern "C" void __stdcall import_ExitProcess_004625e0(unsigned int a0) {
    data_0046614c(a0);
}

// TerminateProcess: 0x004625E6 -> IAT 0x00466148
extern "C" unsigned int (__stdcall *data_00466148)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_TerminateProcess_004625e6(unsigned int a0, unsigned int a1) {
    return data_00466148(a0, a1);
}

// GetCurrentProcess: 0x004625EC -> IAT 0x00466144
extern "C" unsigned int (__stdcall *data_00466144)();
extern "C" unsigned int __stdcall import_GetCurrentProcess_004625ec() {
    return data_00466144();
}

// HeapSize: 0x004625F2 -> IAT 0x00466140
extern "C" unsigned int (__stdcall *data_00466140)(unsigned int a0, unsigned int a1, unsigned int a2);
extern "C" unsigned int __stdcall import_HeapSize_004625f2(unsigned int a0, unsigned int a1, unsigned int a2) {
    return data_00466140(a0, a1, a2);
}

// UnhandledExceptionFilter: 0x004625F8 -> IAT 0x0046613C
extern "C" unsigned int (__stdcall *data_0046613c)(unsigned int a0);
extern "C" unsigned int __stdcall import_UnhandledExceptionFilter_004625f8(unsigned int a0) {
    return data_0046613c(a0);
}

// VirtualProtect: 0x004625FE -> IAT 0x00466138
extern "C" unsigned int (__stdcall *data_00466138)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" unsigned int __stdcall import_VirtualProtect_004625fe(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    return data_00466138(a0, a1, a2, a3);
}

// GetSystemInfo: 0x00462604 -> IAT 0x00466134
extern "C" void (__stdcall *data_00466134)(unsigned int a0);
extern "C" void __stdcall import_GetSystemInfo_00462604(unsigned int a0) {
    data_00466134(a0);
}

// VirtualQuery: 0x0046260A -> IAT 0x0046609C
extern "C" unsigned int (__stdcall *data_0046609c)(unsigned int a0, unsigned int a1, unsigned int a2);
extern "C" unsigned int __stdcall import_VirtualQuery_0046260a(unsigned int a0, unsigned int a1, unsigned int a2) {
    return data_0046609c(a0, a1, a2);
}

// GetStdHandle: 0x00462610 -> IAT 0x00466098
extern "C" unsigned int (__stdcall *data_00466098)(unsigned int a0);
extern "C" unsigned int __stdcall import_GetStdHandle_00462610(unsigned int a0) {
    return data_00466098(a0);
}

// FreeEnvironmentStringsA: 0x00462616 -> IAT 0x00466094
extern "C" unsigned int (__stdcall *data_00466094)(unsigned int a0);
extern "C" unsigned int __stdcall import_FreeEnvironmentStringsA_00462616(unsigned int a0) {
    return data_00466094(a0);
}

// GetEnvironmentStrings: 0x0046261C -> IAT 0x00466090
extern "C" unsigned int (__stdcall *data_00466090)();
extern "C" unsigned int __stdcall import_GetEnvironmentStrings_0046261c() {
    return data_00466090();
}

// FreeEnvironmentStringsW: 0x00462622 -> IAT 0x0046608C
extern "C" unsigned int (__stdcall *data_0046608c)(unsigned int a0);
extern "C" unsigned int __stdcall import_FreeEnvironmentStringsW_00462622(unsigned int a0) {
    return data_0046608c(a0);
}

// GetEnvironmentStringsW: 0x00462628 -> IAT 0x00466088
extern "C" unsigned int (__stdcall *data_00466088)();
extern "C" unsigned int __stdcall import_GetEnvironmentStringsW_00462628() {
    return data_00466088();
}

// SetHandleCount: 0x0046262E -> IAT 0x00466084
extern "C" unsigned int (__stdcall *data_00466084)(unsigned int a0);
extern "C" unsigned int __stdcall import_SetHandleCount_0046262e(unsigned int a0) {
    return data_00466084(a0);
}

// GetFileType: 0x00462634 -> IAT 0x00466080
extern "C" unsigned int (__stdcall *data_00466080)(unsigned int a0);
extern "C" unsigned int __stdcall import_GetFileType_00462634(unsigned int a0) {
    return data_00466080(a0);
}
