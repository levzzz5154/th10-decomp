/* ================================================================
 * common.h - Master include for th10.exe matching decompilation
 * 
 * Includes all type stubs and declares global externs at their
 * original addresses in th10.exe (image base 0x00400000).
 * ================================================================ */

#ifndef COMMON_H
#define COMMON_H

#include "windows_types.h"
#include "d3d_stubs.h"
#include "dsound_stubs.h"
#include "dinput_stubs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================
 * Game Engine Globals (verified against Ghidra analysis)
 * ================================================================ */

/* D3D interfaces */
extern IDirect3D9        *g_pD3D9;              /* 0x00491c2c */
extern IDirect3DDevice9  *g_pD3DDevice;          /* 0x00491c30 */

/* Window handle (main HWND) */
extern HWND               g_pWnd;                /* 0x004924f0 */

/* Game state manager (0x732460 byte allocation) */
extern void              *g_pGameStateManager;   /* 0x00491c10 */

/* HINSTANCE from WinMain/entry */
extern HINSTANCE          g_hInstance;           /* 0x004924f8 */

/* Pointer array (0x2801 entries, allocated 0xA004 bytes) */
extern void             **g_pObjectPool;         /* 0x00491be0 */

/* Renderer/engine object (0x48 bytes) */
extern void              *g_pRenderer;           /* 0x00491be4 */

/* ================================================================
 * Other Globals (referenced by entry point)
 * ================================================================ */

/* Command line string */
extern LPSTR              g_pCmdLine;            /* 0x00499348 */

/* Environment strings */
extern LPSTR              g_pEnvStrings;         /* 0x00477204 */

/* OS Version globals */
extern DWORD              g_dwPlatformId;        /* 0x00477470 */
extern DWORD              g_dwMajorVersion;      /* 0x0047747c */
extern DWORD              g_dwMinorVersion;      /* 0x00477480 */
extern DWORD              g_dwBuildNumber;       /* 0x00477474 */
extern DWORD              g_dwVersion;           /* 0x00477478 */

/* ================================================================
 * Forward declarations for cross-file functions
 * ================================================================ */

int WINAPI GameMain(HINSTANCE hInstance);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */
