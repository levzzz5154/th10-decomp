# Calibration packet: 0x0042B9C0

Baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`.

Review the exact address and each supplied C++ implementation independently. Compare valid-state behavior, branches, constants, side effects, ownership, return values and ABI adapters. Distinguish an actual mismatch from an unmeasured precision boundary or a justified host contract. Source comments and annotations are claims to check. No prior reviewer verdict is supplied.

Report one row per implementation, exact evidence lines, a minimal counterexample when possible, production reachability evidence, and what remains unknown. Assembly resolves decompiler disagreements. This packet does not establish the live retail floating-point environment or gameplay reachability. Request additional dependencies by path/address when needed; do not fill gaps with assumptions.

### [matching2/src/game/score_popup.cpp:1–52](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/score_popup.cpp#L1-L52)

Whole-file SHA-256: `9d057f407ccd34abbf4a1e2df91b9cb5f718341f5daf030e74c858315470e363`

```text
1: #include "th10/game/score_popup.hpp"
2: 
3: // 0x0042B9C0 - Populate the next entry in the 720-record floating-score ring.
4: // Retail receives the value and position through registers. The readable ABI
5: // exposes them explicitly while retaining digit order, minus glyph, lazy timer
6: // initialization, position/color publication, and ring wrap behavior.
7: ScorePopupRecord* ScorePopup_Enqueue(ScorePopupQueue* queue, int value,
8:                                      std::uint32_t color,
9:                                      const float position[3],
10:                                      const float* default_speed) {
11:     if (queue->next_index >= SCORE_POPUP_CAPACITY || queue->next_index < 0) {
12:         queue->next_index = 0;
13:     }
14: 
15:     ScorePopupRecord* record = &queue->records[queue->next_index];
16:     record->active = 1;
17: 
18:     int count = 0;
19:     if (value < 0) {
20:         record->digits[0] = 10;
21:         count = 1;
22:     } else if (value == 0) {
23:         record->digits[0] = 0;
24:         count = 1;
25:     } else {
26:         do {
27:             record->digits[count++] =
28:                 static_cast<std::uint8_t>(value % 10);
29:             value /= 10;
30:         } while (value != 0);
31:     }
32:     record->digit_count = static_cast<std::uint8_t>(count);
33:     record->color = color;
34: 
35:     if ((record->timer.flags & 1u) == 0) {
36:         record->timer.current = 0;
37:         record->timer.target = static_cast<int>(0xfff0bdc1u);
38:         record->timer.previous = 0;
39:         record->timer.speed = default_speed;
40:         record->timer.flags |= 1u;
41:     }
42:     record->timer.current = 0;
43:     record->timer.previous = 0;
44:     record->timer.target = -1;
45: 
46:     record->position[0] = position[0];
47:     record->position[1] = position[1];
48:     record->position[2] = position[2];
49: 
50:     ++queue->next_index;
51:     return record;
52: }
```

### [matching2/include/th10/game/score_popup.hpp:1–29](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/game/score_popup.hpp#L1-L29)

Whole-file SHA-256: `2659c7310ee98f07723d176d0995ecc9fe69c6144a9630b63aacab6df2f8d341`

```text
1: #pragma once
2: 
3: #include <cstdint>
4: 
5: #include "th10/math/timer.hpp"
6: 
7: enum { SCORE_POPUP_CAPACITY = 720, SCORE_POPUP_DIGIT_CAPACITY = 12 };
8: 
9: struct ScorePopupRecord {
10:     std::uint8_t digits[SCORE_POPUP_DIGIT_CAPACITY];
11:     float position[3];
12:     std::uint32_t color;
13:     EmbeddedTimerState timer;
14:     std::uint8_t active;
15:     std::uint8_t digit_count;
16: };
17: 
18: struct ScorePopupQueue {
19:     int next_index;
20:     ScorePopupRecord records[SCORE_POPUP_CAPACITY];
21: };
22: 
23: // Queue a colored integer at a world position. Decimal digits are stored
24: // least-significant first, as consumed by the retail renderer; 10 is the
25: // dedicated minus-sign glyph.
26: ScorePopupRecord* ScorePopup_Enqueue(ScorePopupQueue* queue, int value,
27:                                      std::uint32_t color,
28:                                      const float position[3],
29:                                      const float* default_speed);
```

### [matching2/include/th10/math/timer.hpp:1–33](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/math/timer.hpp#L1-L33)

Whole-file SHA-256: `b9e6c73ced3096d4e0ff591377d9f26aaf5b87f145c19be3f2e43405c3a9ea88`

```text
1: // =============================================================================
2: // timer.hpp - Retail five-word frame timer
3: // =============================================================================
4: #pragma once
5: 
6: struct FrameTimer {
7:     int previous;                 // +0x00
8:     int current;                  // +0x04
9:     float elapsed;                // +0x08
10:     const float* speed;           // +0x0C
11:     unsigned int flags;           // +0x10
12: };
13: 
14: struct EmbeddedTimerState {
15:     int target;
16:     int current;
17:     int previous;
18:     const float* speed;
19:     unsigned int flags;
20: };
21: 
22: void FrameTimer_Tick(FrameTimer* timer);
23: void FrameTimer_Advance(FrameTimer* timer, float delta);
24: 
25: // Defined in src/math/math_utils.cpp. Both install the shared time scale and
26: // the initialized bit on first use, then overwrite the sentinel they just
27: // wrote; callers such as 0x0040D280 and 0x00415B00 reuse them directly.
28: void Timer_Set(FrameTimer* timer, int target);
29: void Timer_Reset(FrameTimer* timer);
30: void GameState_SetTimerTarget(unsigned char* state, int owner_value,
31:                               int target, const float* speed);
32: void GameState_DisableTimerWithOwner(void* state, int owner);
33: void EmbeddedTimer_Reset(EmbeddedTimerState* timer, const float* speed);
```

### [ida/th10.exe.c:42029–42089](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.c#L42029-L42089)

Whole-file SHA-256: `61481fa38c3e5695794ef5f5dd439c7e2af4126514b508af0a83400bfb481163`

```text
42029: //----- (0042B9C0) --------------------------------------------------------
42030: int __userpurge sub_42B9C0@<eax>(int a1@<eax>, _DWORD *a2@<edi>, int a3@<esi>, int a4)
42031: {
42032:   int v4; // ecx
42033:   int v5; // ebx
42034:   int v6; // et2
42035:   int v7; // eax
42036:   _DWORD *v8; // ecx
42037:   int result; // eax
42038: 
42039:   if ( *(int *)(a3 + 20) >= 720 )
42040:     *(_DWORD *)(a3 + 20) = 0;
42041:   v4 = (*(_DWORD *)(a3 + 20) << 6) + a3 + 964;
42042:   v5 = 0;
42043:   *(_BYTE *)((*(_DWORD *)(a3 + 20) << 6) + a3 + 1020) = 1;
42044:   if ( a1 < 0 )
42045:   {
42046:     *(_BYTE *)v4 = 10;
42047:   }
42048:   else
42049:   {
42050:     if ( a1 )
42051:     {
42052:       do
42053:       {
42054:         v6 = a1 % 10;
42055:         a1 /= 10;
42056:         *(_BYTE *)(++v5 + v4 - 1) = v6;
42057:       }
42058:       while ( a1 );
42059:       if ( v5 )
42060:         goto LABEL_9;
42061:     }
42062:     *(_BYTE *)v4 = 0;
42063:   }
42064:   LOBYTE(v5) = 1;
42065: LABEL_9:
42066:   *(_BYTE *)(v4 + 57) = v5;
42067:   *(_DWORD *)(v4 + 24) = a4;
42068:   v7 = *(_DWORD *)(v4 + 44);
42069:   if ( (v7 & 1) == 0 )
42070:   {
42071:     *(_DWORD *)(v4 + 32) = 0;
42072:     *(_DWORD *)(v4 + 28) = -999999;
42073:     *(_DWORD *)(v4 + 36) = 0;
42074:     *(_DWORD *)(v4 + 40) = &flt_476F78;
42075:     *(_DWORD *)(v4 + 44) = v7 | 1;
42076:   }
42077:   *(_DWORD *)(v4 + 32) = 0;
42078:   *(_DWORD *)(v4 + 36) = 0;
42079:   *(_DWORD *)(v4 + 28) = -1;
42080:   v8 = (_DWORD *)(v4 + 12);
42081:   *v8 = *a2;
42082:   result = a2[1];
42083:   v8[1] = result;
42084:   v8[2] = a2[2];
42085:   ++*(_DWORD *)(a3 + 20);
42086:   return result;
42087: }
42088: // 476F78: using guessed type float flt_476F78;
42089: 
```

### [ida/th10.exe.asm:61502–61577](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L61502-L61577)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
61502: sub_42B9C0 proc near
61503: 
61504: arg_0= dword ptr  4
61505: 
61506: mov     ecx, [esi+14h]
61507: xor     edx, edx
61508: cmp     ecx, 2D0h
61509: jl      short loc_42B9D0
61510: mov     [esi+14h], edx
61511: 
61512: loc_42B9D0:
61513: mov     ecx, [esi+14h]
61514: shl     ecx, 6
61515: push    ebx
61516: lea     ecx, [ecx+esi+3C4h]
61517: xor     ebx, ebx
61518: cmp     eax, edx
61519: mov     byte ptr [ecx+38h], 1
61520: jl      short loc_42BA62
61521: jz      short loc_42BA08
61522: push    ebp
61523: jmp     short loc_42B9F0
61524: align 10h
61525: 
61526: loc_42B9F0:
61527: cdq
61528: mov     ebp, 0Ah
61529: idiv    ebp
61530: inc     ebx
61531: test    eax, eax
61532: mov     [ebx+ecx-1], dl
61533: jnz     short loc_42B9F0
61534: xor     edx, edx
61535: test    ebx, ebx
61536: pop     ebp
61537: jnz     short loc_42BA10
61538: 
61539: loc_42BA08:
61540: mov     byte ptr [ecx], 0
61541: 
61542: loc_42BA0B:
61543: mov     ebx, 1
61544: 
61545: loc_42BA10:
61546: mov     eax, [esp+4+arg_0]
61547: mov     [ecx+39h], bl
61548: mov     [ecx+18h], eax
61549: mov     eax, [ecx+2Ch]
61550: test    al, 1
61551: pop     ebx
61552: jnz     short loc_42BA3C
61553: or      eax, 1
61554: mov     [ecx+20h], edx
61555: mov     dword ptr [ecx+1Ch], 0FFF0BDC1h
61556: mov     [ecx+24h], edx
61557: mov     dword ptr [ecx+28h], offset flt_476F78
61558: mov     [ecx+2Ch], eax
61559: 
61560: loc_42BA3C:
61561: mov     [ecx+20h], edx
61562: mov     [ecx+24h], edx
61563: mov     dword ptr [ecx+1Ch], 0FFFFFFFFh
61564: mov     edx, [edi]
61565: add     ecx, 0Ch
61566: mov     [ecx], edx
61567: mov     eax, [edi+4]
61568: mov     [ecx+4], eax
61569: mov     edx, [edi+8]
61570: mov     [ecx+8], edx
61571: inc     dword ptr [esi+14h]
61572: retn    4
61573: 
61574: loc_42BA62:
61575: mov     byte ptr [ecx], 0Ah
61576: jmp     short loc_42BA0B
61577: sub_42B9C0 endp
```

## Referenced retail constants

### [ida/th10.exe.asm:179651–179651](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L179651-L179651)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
179651: flt_476F78 dd 1.0
```

### [decompiled/ghidra_raw/0042B9C0_FUN_0042b9c0.c:1–63](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/decompiled/ghidra_raw/0042B9C0_FUN_0042b9c0.c#L1-L63)

Whole-file SHA-256: `a66c277a79ba855a0c428df96e191aa797546872a12f62373024c36c38f59902`

```text
1: /*
2:  * Raw Ghidra pseudocode reference; not directly compilable.
3:  * Address: 0x0042B9C0
4:  * Tracking name: FUN_0042b9c0
5:  * Ghidra name: FUN_0042b9c0
6:  * Tracked span: 2464 bytes
7:  */
8: 
9: 
10: void FUN_0042b9c0(undefined4 param_1)
11: 
12: {
13:   undefined1 *puVar1;
14:   int in_EAX;
15:   int iVar2;
16:   int iVar3;
17:   int iVar4;
18:   int unaff_ESI;
19:   undefined4 *unaff_EDI;
20:   
21:   if (0x2cf < *(int *)(unaff_ESI + 0x14)) {
22:     *(undefined4 *)(unaff_ESI + 0x14) = 0;
23:   }
24:   puVar1 = (undefined1 *)(*(int *)(unaff_ESI + 0x14) * 0x40 + 0x3c4 + unaff_ESI);
25:   iVar3 = 0;
26:   puVar1[0x38] = 1;
27:   if (in_EAX < 0) {
28:     *puVar1 = 10;
29:   }
30:   else {
31:     if (in_EAX != 0) {
32:       do {
33:         iVar2 = in_EAX / 10;
34:         iVar4 = iVar3 + 1;
35:         puVar1[iVar3] = (char)(in_EAX % 10);
36:         in_EAX = iVar2;
37:         iVar3 = iVar4;
38:       } while (iVar2 != 0);
39:       if (iVar4 != 0) goto LAB_0042ba10;
40:     }
41:     *puVar1 = 0;
42:   }
43:   iVar4 = 1;
44: LAB_0042ba10:
45:   puVar1[0x39] = (char)iVar4;
46:   *(undefined4 *)(puVar1 + 0x18) = param_1;
47:   if ((*(uint *)(puVar1 + 0x2c) & 1) == 0) {
48:     *(undefined4 *)(puVar1 + 0x20) = 0;
49:     *(undefined4 *)(puVar1 + 0x1c) = 0xfff0bdc1;
50:     *(undefined4 *)(puVar1 + 0x24) = 0;
51:     *(undefined4 **)(puVar1 + 0x28) = &DAT_00476f78;
52:     *(uint *)(puVar1 + 0x2c) = *(uint *)(puVar1 + 0x2c) | 1;
53:   }
54:   *(undefined4 *)(puVar1 + 0x20) = 0;
55:   *(undefined4 *)(puVar1 + 0x24) = 0;
56:   *(undefined4 *)(puVar1 + 0x1c) = 0xffffffff;
57:   *(undefined4 *)(puVar1 + 0xc) = *unaff_EDI;
58:   *(undefined4 *)(puVar1 + 0x10) = unaff_EDI[1];
59:   *(undefined4 *)(puVar1 + 0x14) = unaff_EDI[2];
60:   *(int *)(unaff_ESI + 0x14) = *(int *)(unaff_ESI + 0x14) + 1;
61:   return;
62: }
63: 
```

## Production textual cross-references

All token occurrences in versioned `src/` and `standalone/` C++/headers are listed below, including definitions and comments. These are navigation aids; indirect calls and differently named adapters require further inspection. Tests are deliberately excluded from this production search.

- [matching2/src/game/score_popup.cpp:7](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/score_popup.cpp#L7): `ScorePopupRecord* ScorePopup_Enqueue(ScorePopupQueue* queue, int value,`
