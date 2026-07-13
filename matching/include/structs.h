// structs.h - Reconstructed types for th10.exe (GameThread, text system, etc.)
// Matches layout verified from Ghidra decompilation

#pragma once
#include "common.h"

// Text line entry: 0x68 bytes per string
struct TextLine {
    char    text[64];   // +0x00: null-terminated string (max 63 chars + null)
    float   x;          // +0x40: screen x position
    float   y;          // +0x44: screen y position
    float   scale_y;    // +0x48: vertical scale
    DWORD   color;      // +0x4C: ARGB color
    float   scale_x;    // +0x50: horizontal scale
    float   line_height; // +0x54: line spacing
    int     texture_idx; // +0x5C: 0=ascii, 1=text?
    int     flags;       // +0x60: render flags
};

// ANM sprite/animation reference
struct AnmRef {
    int     anm_handle;   // +0x00
    void*   anm_data;     // +0x04
    int     field_08;     // +0x08
    int     field_0C;     // +0x0C
    int     field_10;     // +0x10
    int     field_14;     // +0x14
    int     field_18;     // +0x18
    int     field_1C;     // +0x1C
};

// GameThread: 0x89AC byte structure at center of the game
// Base address passed via ESI/EAX in most functions
struct GameThread {
    void*   vtable;           // +0x0000
    DWORD   field_004;        // +0x0004
    // ... many fields ...
    // Text rendering fields
    float   text_x;           // +0x0348: current text x
    float   text_y;           // +0x034C: current text y
    float   text_z;           // +0x0350: current text z?
    DWORD   field_354;        // +0x0354
    DWORD   field_358;        // +0x0358
    DWORD   field_35C;        // +0x035C
    DWORD   field_360;        // +0x0360
    DWORD   field_364;        // +0x0364
    DWORD   field_368;        // +0x0368
    DWORD   field_36C;        // +0x036C
    DWORD   render_flags;     // +0x0370: D3D render state flags
    DWORD   field_374;        // +0x0374
    DWORD   field_378;        // +0x0378
    DWORD   field_37C;        // +0x037C
    DWORD   field_380;        // +0x0380
    DWORD   field_384;        // +0x0384
    DWORD   field_388;        // +0x0388
    DWORD   field_38C;        // +0x038C
    DWORD   field_390;        // +0x0390
    DWORD   field_394;        // +0x0394
    DWORD   field_398;        // +0x0398
    DWORD   field_39C;        // +0x039C
    DWORD   field_3A0;        // +0x03A0
    DWORD   field_3A4;        // +0x03A4
    int     glyph_index;      // +0x03A8: current glyph table index
    DWORD   field_3AC;        // +0x03AC
    DWORD   field_3B0;        // +0x03B0
    DWORD   field_3B4;        // +0x03B4
    DWORD   field_3B8;        // +0x03B8
    DWORD   field_3BC;        // +0x03BC
    AnmRef  ascii_anm_ref;    // +0x03C0: reference to ascii anm data
    DWORD   field_3E0[0x04];  // +0x03E0
    DWORD   field_3F0;        // +0x03F0
    DWORD   field_3F4;        // +0x03F4
    DWORD   field_3F8;        // +0x03F8
    DWORD   field_3FC;        // +0x03FC
    DWORD   field_400;        // +0x0400
    DWORD   field_404;        // +0x0404
    DWORD   field_408;        // +0x0408
    DWORD   field_40C;        // +0x040C
    DWORD   field_410;        // +0x0410
    DWORD   field_414;        // +0x0414
    DWORD   field_418;        // +0x0418
    DWORD   field_41C;        // +0x041C
    DWORD   field_420;        // +0x0420
    DWORD   field_424;        // +0x0424
    DWORD   field_428;        // +0x0428
    DWORD   field_42C;        // +0x042C
    DWORD   field_430;        // +0x0430: used by FUN_0040cf60
    DWORD   field_434;        // +0x0434
    DWORD   field_438;        // +0x0438
    // ... padding to text system ...
    DWORD   pad_to_76C[0x76C/4 - 67]; // filler to reach +0x76C
    TextLine text_lines[256];  // +0x76C: text string ring buffer (256 * 0x68 = 0x6800)
    // ... more padding ...
    DWORD   field_896C;        // +0x896C: text line count (ring buffer index)
    DWORD   field_8970;        // +0x8970: another text line count
    DWORD   field_8974;        // +0x8974: spacing/param
    DWORD   field_8978;        // +0x8978
    DWORD   field_897C;        // +0x897C
    DWORD   field_8980;        // +0x8980
    DWORD   field_8984;        // +0x8984
    DWORD   field_8988;        // +0x8988: extra param for text
    int     field_898C;        // +0x898C: font scale/width param
    int*    ascii_anm;         // +0x8994: pointer to ascii ANM data
    int*    capture_anm;       // +0x8998: pointer to capture ANM data
    int*    text_anm;          // +0x899C: pointer to text ANM data
    DWORD   field_89A0;        // +0x89A0
    DWORD   field_89A4;        // +0x89A4
    int*    field_89A8;        // +0x89A8: another anm pointer
};

// void* FUN_00449ed0(CallbackType callback) - creates a wrapper/scheduler object
extern void* FUN_00449ed0(void* callback);

// void FUN_00449ae0(int) - schedule/execute
extern void FUN_00449ae0(int);

// void FUN_00449b70(int) - schedule/execute (different variant)
extern void FUN_00449b70(int);

// void* FUN_00447280(int mode, int mgr, const char* filename) - load ANM file
extern void* FUN_00447280(int, int, const char*);

// void FUN_0043e5a0(int anm_handle, int index) - set ANM frame
extern void FUN_0043e5a0(int, int);

// void FUN_00401de0(ECX, void* dest) - initialize AnmRef
extern void FUN_00401de0(int ecx, void* dest);

// void FUN_00447810(int) - texture release helper
extern void FUN_00447810(int);

// void FUN_00442f50() - D3D render state begin
extern void FUN_00442f50(void);

// void FUN_004215a0() - D3D render state setup
extern void FUN_004215a0(void);

// void FUN_00443080(void*) - render sprite/texture
extern void FUN_00443080(void*);

// void FUN_00443290(void*) - render sprite with shadow
extern void FUN_00443290(void*);

// ---- Globals ----
extern void* g_pGameThread;           // 0x004919F4?
extern void* g_pGameStateManager;     // 0x00492508
extern void* g_pD3DDevice;            // 0x00491C30
extern int   DAT_00491be4;            // 0x00491BE4
extern DWORD DAT_0049231c;            // 0x0049231C - critical section counter
extern float _DAT_00470b08;           // 0x00470B08 - shadow offset constant
extern float _DAT_00470afc;           // 0x00470AFC - comparison constant
extern float _DAT_00470c88;           // 0x00470C88 - line spacing constant
extern DWORD* DAT_00491fac;           // 0x00491FAC - current render target desc
extern DWORD  _DAT_00491fb0;          // 0x00491FB0 - render mode flag
extern int    DAT_00491e94;           // 0x00491E94 - first render desc
extern DWORD  DAT_00491d7c;           // 0x00491D7C - second render desc

extern char   DAT_00474f70[];         // 0x00474F70 - log buffer
extern char   DAT_0046cb68[];         // error message string
extern char   DAT_0046cb14[];         // vtable string/data
