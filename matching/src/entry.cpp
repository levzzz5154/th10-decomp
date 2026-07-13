/* ================================================================
 * th10.exe Matching Decompilation - CRT Entry Point
 * Address: 0x004537DC  Size: 0x1D4 bytes
 *
 * This is the MSVC 7.1 CRT startup entry point from libcmt.
 * Compile with: cl /Gz /O2 /MT /G6 /Gy /entry:entry
 * ================================================================ */

#include "common.h"

/* ---- CRT function prototypes (provided by libcmt.lib) ---- */
extern "C" {
    int   __cdecl _heap_init(void);
    int   __cdecl _mtinit(void);
    void  __cdecl _RTC_Initialize(void);
    int   __cdecl _ioinit(void);
    void  __cdecl _amsg_exit(int);
    void  __cdecl _cexit(void);
    void  __cdecl _exit(int);
    int   __cdecl _setargv(void);
    int   __cdecl _setenvp(void);
    int   __cdecl _cinit(int);
    void  __cdecl _fast_error_exit(int);
    LPSTR __cdecl __crtGetEnvironmentStringsA(void);
    LPSTR __cdecl __wincmdln(void);
}

/* ---- PE header structures matching original offset-based access ---- */
#pragma pack(push, 1)
struct IMAGE_DOS_HEADER_POD {
    unsigned short e_magic;
    unsigned short e_cblp;
    unsigned short e_cp;
    unsigned short e_crlc;
    unsigned short e_cparhdr;
    unsigned short e_minalloc;
    unsigned short e_maxalloc;
    unsigned short e_ss;
    unsigned short e_sp;
    unsigned short e_csum;
    unsigned short e_ip;
    unsigned short e_cs;
    unsigned short e_lfarlc;
    unsigned short e_ovno;
    unsigned short e_res[4];
    unsigned short e_oemid;
    unsigned short e_oeminfo;
    unsigned short e_res2[10];
    long e_lfanew;
};

struct IMAGE_NT_HEADERS_RAW {
    unsigned long Signature;
    struct {
        unsigned short Machine;
        unsigned short NumberOfSections;
        unsigned long  TimeDateStamp;
        unsigned long  PointerToSymbolTable;
        unsigned long  NumberOfSymbols;
        unsigned short SizeOfOptionalHeader;
        unsigned short Characteristics;
    } FileHeader;
    struct {
        unsigned short Magic;
        unsigned char  MajorLinkerVersion;
        unsigned char  MinorLinkerVersion;
        unsigned long  SizeOfCode;
        unsigned long  SizeOfInitializedData;
        unsigned long  SizeOfUninitializedData;
        unsigned long  AddressOfEntryPoint;
        unsigned long  BaseOfCode;
        unsigned long  BaseOfData;
        unsigned long  ImageBase;
        unsigned long  SectionAlignment;
        unsigned long  FileAlignment;
        unsigned short MajorOperatingSystemVersion;
        unsigned short MinorOperatingSystemVersion;
        unsigned short MajorImageVersion;
        unsigned short MinorImageVersion;
        unsigned short MajorSubsystemVersion;
        unsigned short MinorSubsystemVersion;
        unsigned long  Win32VersionValue;
        unsigned long  SizeOfImage;
        unsigned long  SizeOfHeaders;
        unsigned long  CheckSum;
        unsigned short Subsystem;
        unsigned short DllCharacteristics;
        unsigned long  SizeOfStackReserve;
        unsigned long  SizeOfStackCommit;
        unsigned long  SizeOfHeapReserve;
        unsigned long  SizeOfHeapCommit;
        unsigned long  LoaderFlags;
        unsigned long  NumberOfRvaAndSizes;
    } OptionalHeader;
};
#pragma pack(pop)

/* ---- Global variable storage (matches original BSS layout) ---- */

#pragma data_seg(".data$matching")
/* OS version globals */
DWORD  g_dwPlatformId   = 0;  /* 0x00477470 */
DWORD  g_dwBuildNumber  = 0;  /* 0x00477474 */
DWORD  g_dwVersion      = 0;  /* 0x00477478 */
DWORD  g_dwMajorVersion = 0;  /* 0x0047747c */
DWORD  g_dwMinorVersion = 0;  /* 0x00477480 */
LPSTR  g_pCmdLine       = 0;  /* 0x00499348 */
LPSTR  g_pEnvStrings    = 0;  /* 0x00477204 */
/* These will be allocated at link time to match original addresses */

/* ================================================================
 * CRT Entry Point
 * ================================================================ */

int entry(void)
{
    IMAGE_DOS_HEADER_POD      *pDos;
    IMAGE_NT_HEADERS_RAW      *pNt;
    int                         iVar2;
    int                         local_30;
    int                         local_2c;
    unsigned int                local_20;
    _OSVERSIONINFOA             osvi;
    _STARTUPINFOA               si;

    /* Version check */
    osvi.szCSDVersion[0x7c] = (char)0xF4;
    osvi.szCSDVersion[0x7d] = '7';
    osvi.szCSDVersion[0x7e] = 'E';
    osvi.szCSDVersion[0x7f] = '\0';
    osvi.dwOSVersionInfoSize = sizeof(_OSVERSIONINFOA);
    GetVersionExA(&osvi);

    *(DWORD *)0x00477470 = osvi.dwPlatformId;
    *(DWORD *)0x0047747c = osvi.dwMajorVersion;
    *(DWORD *)0x00477480 = osvi.dwMinorVersion;
    *(DWORD *)0x00477474 = osvi.dwBuildNumber & 0x7FFF;
    if (osvi.dwPlatformId != 2) {
        *(DWORD *)0x00477474 |= 0x8000;
    }
    *(DWORD *)0x00477478 = osvi.dwMajorVersion * 0x100 + osvi.dwMinorVersion;

    /* SafeSEH check */
    local_20 = 0;
    pDos = (IMAGE_DOS_HEADER_POD *)GetModuleHandleA(NULL);
    if (pDos != NULL && pDos->e_magic == 0x5A4D) {
        pNt = (IMAGE_NT_HEADERS_RAW *)((char *)pDos + pDos->e_lfanew);
        if (pNt->Signature == 0x00004550) {
            if (pNt->OptionalHeader.Magic == 0x010B) {
                if (pNt->OptionalHeader.NumberOfRvaAndSizes > 14) {
                    long *pDir = (long *)((char *)pNt + 0x78);
                    if (pDir[7] != 0) {
                        local_20 = 1;
                    }
                }
            } else if (pNt->OptionalHeader.Magic == 0x020B) {
                if (pNt->OptionalHeader.NumberOfRvaAndSizes > 14) {
                    long *pDir = (long *)((char *)pNt + 0x88);
                    if (pDir[7] != 0) {
                        local_20 = 1;
                    }
                }
            }
        }
    }

    /* CRT init (SEH-protected in original) */
    iVar2 = _heap_init();
    if (iVar2 == 0) {
        _fast_error_exit(0x1C);
    }
    iVar2 = _mtinit();
    if (iVar2 == 0) {
        _fast_error_exit(0x10);
    }
    _RTC_Initialize();

    /* Post-SEH CRT init */
    iVar2 = _ioinit();
    if (iVar2 < 0) {
        _amsg_exit(0x1B);
    }
    *(LPSTR *)0x00499348 = GetCommandLineA();
    *(LPSTR *)0x00477204 = __crtGetEnvironmentStringsA();
    iVar2 = _setargv();
    if (iVar2 < 0) {
        _amsg_exit(8);
    }
    iVar2 = _setenvp();
    if (iVar2 < 0) {
        _amsg_exit(9);
    }
    local_2c = _cinit(1);
    if (local_2c != 0) {
        _amsg_exit(local_2c);
    }

    /* Startup info */
    si.dwFlags = 0;
    GetStartupInfoA(&si);

    /* Call GameMain */
    {
        HINSTANCE hInst = (HINSTANCE)GetModuleHandleA(NULL);
        iVar2 = GameMain(hInst);
        local_30 = iVar2;
    }

    if (local_20 == 0) {
        _exit(iVar2);
    }
    _cexit();
    return iVar2;
}
