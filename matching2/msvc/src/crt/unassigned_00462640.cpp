// Win32 import forwarding thunks. Each wrapper preserves the retail stdcall tail jump.

// InterlockedExchange: 0x00462640 -> IAT 0x00466078
extern "C" unsigned int (__stdcall *imp_InterlockedExchange)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_InterlockedExchange_00462640(unsigned int a0, unsigned int a1) {
    return imp_InterlockedExchange(a0, a1);
}

// GetStringTypeA: 0x00462646 -> IAT 0x00466074
extern "C" unsigned int (__stdcall *imp_GetStringTypeA)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
extern "C" unsigned int __stdcall import_GetStringTypeA_00462646(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4) {
    return imp_GetStringTypeA(a0, a1, a2, a3, a4);
}

// GetStringTypeW: 0x0046264C -> IAT 0x00466070
extern "C" unsigned int (__stdcall *imp_GetStringTypeW)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" unsigned int __stdcall import_GetStringTypeW_0046264c(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    return imp_GetStringTypeW(a0, a1, a2, a3);
}

// GetTimeFormatA: 0x00462652 -> IAT 0x0046606C
extern "C" unsigned int (__stdcall *imp_GetTimeFormatA)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
extern "C" unsigned int __stdcall import_GetTimeFormatA_00462652(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5) {
    return imp_GetTimeFormatA(a0, a1, a2, a3, a4, a5);
}

// GetDateFormatA: 0x00462658 -> IAT 0x00466068
extern "C" unsigned int (__stdcall *imp_GetDateFormatA)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
extern "C" unsigned int __stdcall import_GetDateFormatA_00462658(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5) {
    return imp_GetDateFormatA(a0, a1, a2, a3, a4, a5);
}

// GetCPInfo: 0x0046265E -> IAT 0x00466064
extern "C" unsigned int (__stdcall *imp_GetCPInfo)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_GetCPInfo_0046265e(unsigned int a0, unsigned int a1) {
    return imp_GetCPInfo(a0, a1);
}

// GetUserDefaultLCID: 0x00462664 -> IAT 0x00466060
extern "C" unsigned int (__stdcall *imp_GetUserDefaultLCID)();
extern "C" unsigned int __stdcall import_GetUserDefaultLCID_00462664() {
    return imp_GetUserDefaultLCID();
}

// GetLocaleInfoA: 0x0046266A -> IAT 0x0046605C
extern "C" unsigned int (__stdcall *imp_GetLocaleInfoA)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" unsigned int __stdcall import_GetLocaleInfoA_0046266a(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    return imp_GetLocaleInfoA(a0, a1, a2, a3);
}

// EnumSystemLocalesA: 0x00462670 -> IAT 0x00466058
extern "C" unsigned int (__stdcall *imp_EnumSystemLocalesA)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_EnumSystemLocalesA_00462670(unsigned int a0, unsigned int a1) {
    return imp_EnumSystemLocalesA(a0, a1);
}

// IsValidLocale: 0x00462676 -> IAT 0x00466054
extern "C" unsigned int (__stdcall *imp_IsValidLocale)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_IsValidLocale_00462676(unsigned int a0, unsigned int a1) {
    return imp_IsValidLocale(a0, a1);
}

// IsValidCodePage: 0x0046267C -> IAT 0x00466050
extern "C" unsigned int (__stdcall *imp_IsValidCodePage)(unsigned int a0);
extern "C" unsigned int __stdcall import_IsValidCodePage_0046267c(unsigned int a0) {
    return imp_IsValidCodePage(a0);
}

// GetACP: 0x00462682 -> IAT 0x0046604C
extern "C" unsigned int (__stdcall *imp_GetACP)();
extern "C" unsigned int __stdcall import_GetACP_00462682() {
    return imp_GetACP();
}

// GetOEMCP: 0x00462688 -> IAT 0x00466048
extern "C" unsigned int (__stdcall *imp_GetOEMCP)();
extern "C" unsigned int __stdcall import_GetOEMCP_00462688() {
    return imp_GetOEMCP();
}

// RaiseException: 0x0046268E -> IAT 0x00466044
extern "C" void (__stdcall *imp_RaiseException)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" void __stdcall import_RaiseException_0046268e(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    imp_RaiseException(a0, a1, a2, a3);
}

// LCMapStringA: 0x00462694 -> IAT 0x00466040
extern "C" unsigned int (__stdcall *imp_LCMapStringA)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
extern "C" unsigned int __stdcall import_LCMapStringA_00462694(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5) {
    return imp_LCMapStringA(a0, a1, a2, a3, a4, a5);
}

// LCMapStringW: 0x0046269A -> IAT 0x0046603C
extern "C" unsigned int (__stdcall *imp_LCMapStringW)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
extern "C" unsigned int __stdcall import_LCMapStringW_0046269a(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5) {
    return imp_LCMapStringW(a0, a1, a2, a3, a4, a5);
}

// GetTickCount: 0x004626A0 -> IAT 0x004660F0
extern "C" unsigned int (__stdcall *imp_GetTickCount)();
extern "C" unsigned int __stdcall import_GetTickCount_004626a0() {
    return imp_GetTickCount();
}

// GetCurrentProcessId: 0x004626A6 -> IAT 0x004661B4
extern "C" unsigned int (__stdcall *imp_GetCurrentProcessId)();
extern "C" unsigned int __stdcall import_GetCurrentProcessId_004626a6() {
    return imp_GetCurrentProcessId();
}

// LoadLibraryA: 0x004626AC -> IAT 0x004661B8
extern "C" unsigned int (__stdcall *imp_LoadLibraryA)(unsigned int a0);
extern "C" unsigned int __stdcall import_LoadLibraryA_004626ac(unsigned int a0) {
    return imp_LoadLibraryA(a0);
}

// SetStdHandle: 0x004626B2 -> IAT 0x004661BC
extern "C" unsigned int (__stdcall *imp_SetStdHandle)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_SetStdHandle_004626b2(unsigned int a0, unsigned int a1) {
    return imp_SetStdHandle(a0, a1);
}

// SetConsoleCtrlHandler: 0x004626B8 -> IAT 0x004661C0
extern "C" unsigned int (__stdcall *imp_SetConsoleCtrlHandler)(unsigned int a0, unsigned int a1);
extern "C" unsigned int __stdcall import_SetConsoleCtrlHandler_004626b8(unsigned int a0, unsigned int a1) {
    return imp_SetConsoleCtrlHandler(a0, a1);
}

// FlushFileBuffers: 0x004626BE -> IAT 0x004661C4
extern "C" unsigned int (__stdcall *imp_FlushFileBuffers)(unsigned int a0);
extern "C" unsigned int __stdcall import_FlushFileBuffers_004626be(unsigned int a0) {
    return imp_FlushFileBuffers(a0);
}

// GetLocaleInfoW: 0x004626C4 -> IAT 0x004661C8
extern "C" unsigned int (__stdcall *imp_GetLocaleInfoW)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern "C" unsigned int __stdcall import_GetLocaleInfoW_004626c4(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    return imp_GetLocaleInfoW(a0, a1, a2, a3);
}

// CompareStringA: 0x004626CA -> IAT 0x004661CC
extern "C" unsigned int (__stdcall *imp_CompareStringA)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
extern "C" unsigned int __stdcall import_CompareStringA_004626ca(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5) {
    return imp_CompareStringA(a0, a1, a2, a3, a4, a5);
}

// CompareStringW: 0x004626D0 -> IAT 0x004661D0
extern "C" unsigned int (__stdcall *imp_CompareStringW)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
extern "C" unsigned int __stdcall import_CompareStringW_004626d0(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5) {
    return imp_CompareStringW(a0, a1, a2, a3, a4, a5);
}
