# Calibration packet: 0x004135D0

Baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`.

Review the exact address and each supplied C++ implementation independently. Compare valid-state behavior, branches, constants, side effects, ownership, return values and ABI adapters. Distinguish an actual mismatch from an unmeasured precision boundary or a justified host contract. Source comments and annotations are claims to check. No prior reviewer verdict is supplied.

Report one row per implementation, exact evidence lines, a minimal counterexample when possible, production reachability evidence, and what remains unknown. Assembly resolves decompiler disagreements. This packet does not establish the live retail floating-point environment or gameplay reachability. Request additional dependencies by path/address when needed; do not fill gaps with assumptions.

### [matching2/src/app/fps_counter.cpp:1–96](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/app/fps_counter.cpp#L1-L96)

Whole-file SHA-256: `03bae5a5c93e9723c40a158316b652a6151b8b4ed4f5d122c9eafae6498f7092`

```text
1: #include "th10/app/fps_counter.hpp"
2: #include "th10/game/player_motion.hpp"
3: #include "th10/game/registered_clock.hpp"
4: #include "th10/util/scalars.hpp"
5: 
6: #include <cstdarg>
7: #include <cstdio>
8: #include <cstring>
9: 
10: 
11: // Each routine mirrors one retail function; the comment above each body
12: // names the retail address it was recovered from.
13: 
14: 
15: #include <cmath>
16: #include <cstring>
17: 
18: namespace {
19: 
20: 
21: 
22: } // namespace
23: 
24: // 0x004135D0 - FPS counter draw callback: refresh the rolling average, and
25: // unless the game is in state 0xE (shutdown) or the game thread is gone,
26: // print "%2.1ffps" tinted by the frame rate (red below the low threshold,
27: // pink below the mid threshold, white otherwise), restoring white after.
28: // The frame accumulator then absorbs the skipped-frame count plus one.
29: int FpsCounter_Render(void (*update_average)(void), int game_state,
30:                       void* game_thread, float fps, float low_threshold,
31:                       float mid_threshold, Word* overlay_color,
32:                       void (*print_overlay)(const char* format),
33:                       int* accumulator, int skipped_frames) {
34: 	update_average();
35: 	if (game_state != 0xE && game_thread != 0) {
36: 		Word color;
37: 		if (fps < low_threshold) {
38: 			color = 0xFF5050FF;
39: 		} else if (fps < mid_threshold) {
40: 			color = 0xFFA0A0FF;
41: 		} else {
42: 			color = 0xFFFFFFFF;
43: 		}
44: 		*overlay_color = color;
45: 		print_overlay("%2.1ffps");
46: 		*overlay_color = 0xFFFFFFFF;
47: 	}
48: 	*accumulator += skipped_frames + 1;
49: 	return 1;
50: }
51: 
52: // 0x004134B0 - frame-rate counter update: measures fps over the elapsed
53: // window, resynchronizes the global frame stamps after repeated timer
54: // stalls, and accumulates played time while the game is not paused/skipping.
55: 
56: int FrameRateCounter_Update(FrameRateCounter* counter,
57:                             FrameRateEnv* env) {
58: 	double now = env->read_seconds();
59: 	if (now < counter->last_stamp) counter->last_stamp = now;
60: 	double delta = now - counter->last_stamp;
61: 	if (delta < env->min_interval) return 1;
62: 	counter->last_stamp += delta;
63: 
64: 	double frames = (double)counter->frame_count;
65: 	if (counter->frame_count < 0) frames += env->negative_wrap;
66: 	counter->fps = (float)(frames / delta);
67: 
68: 	if (env->stall_threshold < frames / delta) {
69: 		counter->stall_count += 1;
70: 		if (counter->stall_count == 2) {
71: 			double stamp = env->read_seconds();
72: 			for (int i = 0; i < 4; ++i) *env->sync_stamps[i] = stamp;
73: 		} else if (counter->stall_count == 4) {
74: 			*env->skip_accumulator = 0.0;
75: 			double stamp = env->read_seconds();
76: 			for (int i = 0; i < 4; ++i) *env->sync_stamps[i] = stamp;
77: 			counter->stall_count = 0;
78: 		}
79: 	} else {
80: 		counter->stall_count = 0;
81: 	}
82: 
83: 	if (env->input_flags != 0) {
84: 		if ((*env->input_flags & 0x14) == 0) {
85: 			counter->total_seconds += env->second_unit;
86: 			if ((double)counter->fps <= env->fps_cap) {
87: 				counter->active_seconds += (double)counter->fps;
88: 			} else {
89: 				counter->active_seconds += env->second_unit;
90: 			}
91: 		}
92: 		*env->input_flags &= ~0x80u;
93: 	}
94: 	counter->frame_count = 0;
95: 	return 1;
96: }
```

### [matching2/include/th10/app/fps_counter.hpp:1–35](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/app/fps_counter.hpp#L1-L35)

Whole-file SHA-256: `5e3bf4a8c25306437cea58516eb757377260fcf627d70407f0b63c29c03b0af5`

```text
1: #pragma once
2: 
3: // FPS counter render and frame-rate counter update (retail 0x004135D0, 0x004134B0).
4: #include "th10/util/scalars.hpp"
5: 
6: // --- 0x004135D0 --------------------------------------------------------------
7: int FpsCounter_Render(void (*update_average)(void), int game_state,
8:                       void* game_thread, float fps, float low_threshold,
9:                       float mid_threshold, Word* overlay_color,
10:                       void (*print_overlay)(const char* format),
11:                       int* accumulator, int skipped_frames);
12: 
13: struct FrameRateCounter {
14: 	double last_stamp;     // +0x14
15: 	int stall_count;       // +0x1c
16: 	int frame_count;       // +0x20
17: 	double active_seconds; // +0x24
18: 	double total_seconds;  // +0x2c
19: 	float fps;             // +0x34
20: };
21: 
22: struct FrameRateEnv {
23: 	double (*read_seconds)(void);
24: 	double min_interval;    // minimum measurement window
25: 	double negative_wrap;   // added when the frame counter wrapped negative
26: 	double stall_threshold; // fps above this counts as a timer stall
27: 	double fps_cap;         // fps at/below this is accumulated as-is
28: 	double second_unit;     // 1.0 second
29: 	Word* input_flags;   // pause/skip flag word, may be null
30: 	double* sync_stamps[4];    // global resync stamps rewritten on stalls
31: 	double* skip_accumulator;  // cleared on the second stall in a row pair
32: };
33: 
34: int FrameRateCounter_Update(FrameRateCounter* counter,
35:                             FrameRateEnv* env);
```

### [matching2/include/th10/util/scalars.hpp:1–7](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/util/scalars.hpp#L1-L7)

Whole-file SHA-256: `7ad11076fcac126d57294dcf0f40acdf29e299d27028c653a937cffeeb7c5122`

```text
1: #pragma once
2: 
3: // Shared fixed-width scalar aliases used by recovered translation units.
4: 
5: typedef unsigned char Byte;
6: typedef unsigned short Half;
7: typedef unsigned int Word;
```

### [ida/th10.exe.c:23026–23065](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.c#L23026-L23065)

Whole-file SHA-256: `61481fa38c3e5695794ef5f5dd439c7e2af4126514b508af0a83400bfb481163`

```text
23026: //----- (004135D0) --------------------------------------------------------
23027: int __usercall sub_4135D0@<eax>(int a1@<edi>)
23028: {
23029:   _DWORD *v1; // esi
23030:   double v2; // st7
23031:   int v3; // eax
23032:   _DWORD v5[3]; // [esp+10h] [ebp-Ch] BYREF
23033: 
23034:   sub_4134B0(a1);
23035:   if ( dword_491FB8 != 14 )
23036:   {
23037:     v1 = dword_4776E0;
23038:     v2 = *(float *)(a1 + 52);
23039:     if ( dword_4776E0 )
23040:     {
23041:       if ( v2 >= 30.0 )
23042:       {
23043:         if ( v2 >= 40.0 )
23044:           v3 = -1;
23045:         else
23046:           v3 = -6250241;
23047:       }
23048:       else
23049:       {
23050:         v3 = -11513601;
23051:       }
23052:       *((_DWORD *)dword_4776E0 + 8797) = v3;
23053:       v5[0] = 1142128640;
23054:       v5[1] = 1139474432;
23055:       v5[2] = 0;
23056:       sub_401690(v5, v1, "%2.1ffps", v2);
23057:       *((_DWORD *)dword_4776E0 + 8797) = -1;
23058:     }
23059:   }
23060:   *(_DWORD *)(a1 + 32) += (unsigned __int8)byte_491D66 + 1;
23061:   return 1;
23062: }
23063: // 491D66: using guessed type char byte_491D66;
23064: // 491FB8: using guessed type int dword_491FB8;
23065: 
```

### [ida/th10.exe.asm:26477–26542](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L26477-L26542)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
26477: sub_4135D0 proc near
26478: 
26479: ArgList= byte ptr -1Ch
26480: var_C= dword ptr -0Ch
26481: var_8= dword ptr -8
26482: var_4= dword ptr -4
26483: 
26484: sub     esp, 0Ch
26485: push    esi
26486: mov     esi, edi
26487: call    sub_4134B0
26488: cmp     dword_491FB8, 0Eh
26489: jz      loc_41366A
26490: mov     esi, dword_4776E0
26491: fld     dword ptr [edi+34h]
26492: test    esi, esi
26493: jz      short loc_413668
26494: fcom    ds:flt_470C30
26495: fnstsw  ax
26496: test    ah, 5
26497: jp      short loc_413609
26498: mov     eax, 0FF5050FFh
26499: jmp     short loc_413620
26500: 
26501: loc_413609:
26502: fcom    ds:flt_470C64
26503: fnstsw  ax
26504: test    ah, 5
26505: jp      short loc_41361D
26506: mov     eax, 0FFA0A0FFh
26507: jmp     short loc_413620
26508: 
26509: loc_41361D:
26510: or      eax, 0FFFFFFFFh
26511: 
26512: loc_413620:
26513: push    ebx
26514: sub     esp, 8
26515: fstp    qword ptr [esp+1Ch+ArgList] ; ArgList
26516: push    offset a21ffps  ; "%2.1ffps"
26517: lea     ebx, [esp+20h+var_C]
26518: mov     [esi+8974h], eax
26519: mov     [esp+20h+var_C], 44138000h
26520: mov     [esp+20h+var_8], 43EB0000h
26521: mov     [esp+20h+var_4], 0
26522: call    sub_401690
26523: mov     eax, dword_4776E0
26524: add     esp, 0Ch
26525: mov     dword ptr [eax+8974h], 0FFFFFFFFh
26526: pop     ebx
26527: jmp     short loc_41366A
26528: 
26529: loc_413668:
26530: fstp    st
26531: 
26532: loc_41366A:
26533: movzx   ecx, byte_491D66
26534: mov     eax, [edi+20h]
26535: inc     ecx
26536: add     eax, ecx
26537: mov     [edi+20h], eax
26538: mov     eax, 1
26539: pop     esi
26540: add     esp, 0Ch
26541: retn
26542: sub_4135D0 endp
```

## Referenced retail constants

### [ida/th10.exe.asm:157361–157361](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L157361-L157361)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
157361: a21ffps db '%2.1ffps',0
```

### [ida/th10.exe.asm:163349–163349](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163349-L163349)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163349: flt_470C30 dd 30.0
```

### [ida/th10.exe.asm:163361–163361](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163361-L163361)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163361: flt_470C64 dd 40.0
```

### [decompiled/ghidra_raw/004135D0_FUN_004135d0.c:1–38](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/decompiled/ghidra_raw/004135D0_FUN_004135d0.c#L1-L38)

Whole-file SHA-256: `ad2562a3ac01607aa7bb9aefaa1d90132dbf5a1720016bbfd5f2a4a6adb21ec8`

```text
1: /*
2:  * Raw Ghidra pseudocode reference; not directly compilable.
3:  * Address: 0x004135D0
4:  * Tracking name: FUN_004135d0
5:  * Ghidra name: FUN_004135d0
6:  * Tracked span: 240 bytes
7:  */
8: 
9: 
10: /* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
11: 
12: undefined4 FUN_004135d0(void)
13: 
14: {
15:   undefined4 uVar1;
16:   int unaff_EDI;
17:   
18:   FUN_004134b0();
19:   if ((DAT_00491fb8 != 0xe) && (g_pGameThread != (void *)0x0)) {
20:     if (_DAT_00470c30 <= *(float *)(unaff_EDI + 0x34)) {
21:       if (_DAT_00470c64 <= *(float *)(unaff_EDI + 0x34)) {
22:         uVar1 = 0xffffffff;
23:       }
24:       else {
25:         uVar1 = 0xffa0a0ff;
26:       }
27:     }
28:     else {
29:       uVar1 = 0xff5050ff;
30:     }
31:     *(undefined4 *)((int)g_pGameThread + 0x8974) = uVar1;
32:     FUN_00401690("%2.1ffps");
33:     *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
34:   }
35:   *(uint *)(unaff_EDI + 0x20) = *(int *)(unaff_EDI + 0x20) + DAT_00491d66 + 1;
36:   return 1;
37: }
38: 
```

## Production textual cross-references

All token occurrences in versioned `src/` and `standalone/` C++/headers are listed below, including definitions and comments. These are navigation aids; indirect calls and differently named adapters require further inspection. Tests are deliberately excluded from this production search.

- [matching2/src/app/fps_counter.cpp:29](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/app/fps_counter.cpp#L29): `int FpsCounter_Render(void (*update_average)(void), int game_state,`
