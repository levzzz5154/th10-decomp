# Calibration packet: 0x00412AC0

Baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`.

Review the exact address and each supplied C++ implementation independently. Compare valid-state behavior, branches, constants, side effects, ownership, return values and ABI adapters. Distinguish an actual mismatch from an unmeasured precision boundary or a justified host contract. Source comments and annotations are claims to check. No prior reviewer verdict is supplied.

Report one row per implementation, exact evidence lines, a minimal counterexample when possible, production reachability evidence, and what remains unknown. Assembly resolves decompiler disagreements. This packet does not establish the live retail floating-point environment or gameplay reachability. Request additional dependencies by path/address when needed; do not fill gaps with assumptions.

### [matching2/src/game/trajectory_evaluate.cpp:1–237](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/trajectory_evaluate.cpp#L1-L237)

Whole-file SHA-256: `72026f80589c7532d9bfe9370705b4dec165f48f6d4e5bbceccbd76c6807be7b`

```text
1: #include "th10/game/trajectory_evaluate.hpp"
2: 
3: namespace {
4: 
5: const float kNormalSpeedLow = 0.99000001f;
6: const float kNormalSpeedHigh = 1.01f;
7: const int kLinearIncrementMode = 7;
8: const int kAcceleratingIncrementMode = 17;
9: const int kHermiteMode = 8;
10: 
11: void FinishTrajectory(Trajectory2D* state, float output[2],
12:                       const TrajectoryEnv* env, int duration) {
13:     if (!(state->timer_flags & 1)) {
14:         state->current = 0;
15:         state->previous = -999999;
16:         state->elapsed = 0.0f;
17:         state->speed = env->default_speed;
18:         state->timer_flags |= 1;
19:     }
20: 
21:     state->current = duration;
22:     state->previous = duration - 1;
23:     state->elapsed = static_cast<float>(duration);
24:     state->duration = 0;
25: 
26:     float* final_value = state->mode == kLinearIncrementMode
27:         ? state->p0 : state->velocity;
28:     output[0] = final_value[0];
29:     output[1] = final_value[1];
30: }
31: 
32: }  // namespace
33: 
34: // 0x00412AC0 - Advance the embedded timer and evaluate one of the retail
35: // trajectory modes. Completion publishes the terminal value and disables the
36: // active duration while preserving the timer's sentinel initialization.
37: void Trajectory_Evaluate2D(Trajectory2D* state, float output[2],
38:                            const TrajectoryEnv* env) {
39:     const int duration = state->duration;
40:     if (duration > 0) {
41:         state->previous = state->current;
42:         const float speed = *state->speed;
43:         if (speed <= kNormalSpeedLow || speed >= kNormalSpeedHigh) {
44:             state->elapsed += speed;
45:             state->current = static_cast<int>(state->elapsed);
46:         } else {
47:             state->elapsed += 1.0f;
48:             ++state->current;
49:         }
50: 
51:         if (duration <= state->current) {
52:             FinishTrajectory(state, output, env, duration);
53:             return;
54:         }
55:     }
56: 
57:     if (state->mode == kLinearIncrementMode) {
58:         for (int axis = 0; axis < 2; ++axis) {
59:             state->p0[axis] += state->velocity[axis];
60:             output[axis] = state->p0[axis];
61:         }
62:     } else if (state->mode == kAcceleratingIncrementMode) {
63:         for (int axis = 0; axis < 2; ++axis) {
64:             state->p0[axis] += state->acceleration[axis];
65:             output[axis] = state->p0[axis];
66:             state->acceleration[axis] += state->velocity[axis];
67:         }
68:     } else if (state->mode == kHermiteMode) {
69:         const float time = state->elapsed / duration;
70:         const float time_minus_one = time - 1.0f;
71:         const float h00 = (1.0f + 2.0f * time) *
72:                           time_minus_one * time_minus_one;
73:         const float h01 = (3.0f - 2.0f * time) * time * time;
74:         const float h10 = (1.0f - time) * (1.0f - time) * time;
75:         const float h11 = time_minus_one * time * time;
76:         for (int axis = 0; axis < 2; ++axis) {
77:             output[axis] = h00 * state->p0[axis] +
78:                            h01 * state->velocity[axis] +
79:                            h10 * state->p2[axis] +
80:                            h11 * state->acceleration[axis];
81:         }
82:     } else {
83:         const float factor =
84:             env->ease(state->elapsed, static_cast<float>(duration),
85:                       state->mode);
86:         for (int axis = 0; axis < 2; ++axis) {
87:             output[axis] =
88:                 (state->velocity[axis] - state->p0[axis]) * factor +
89:                 state->p0[axis];
90:         }
91:     }
92: }
93: 
94: // 0x0044C350 - the retail ease curve table.  t = elapsed/duration; modes
95: // 1-3 are accelerating powers, 4-6 decelerating powers, 9-14 the 2t
96: // smooth-step pairs, 15 the zero curve, 16 the hold curve, and everything
97: // else (0, 7, ...) the linear default.
98: float Trajectory_EaseFraction(float elapsed, float duration, int mode) {
99:     const float t = elapsed / duration;
100:     switch (mode) {
101:     case 1: return t * t;
102:     case 2: return t * t * t;
103:     case 3: return t * t * t * t;
104:     case 4: {
105:         const float u = 1.0f - t;
106:         return 1.0f - u * u;
107:     }
108:     case 5: {
109:         const float u = 1.0f - t;
110:         return 1.0f - u * u * u;
111:     }
112:     case 6: {
113:         const float u = 1.0f - t;
114:         return 1.0f - u * u * u * u;
115:     }
116:     case 9: {
117:         const float u = t + t;
118:         if (u < 1.0f)
119:             return u * u * 0.5f;
120:         const float v = 2.0f - u;
121:         return (2.0f - v * v) * 0.5f;
122:     }
123:     case 10: {
124:         const float u = t + t;
125:         if (u < 1.0f)
126:             return u * u * u * 0.5f;
127:         const float v = 2.0f - u;
128:         return (2.0f - v * v * v) * 0.5f;
129:     }
130:     case 11: {
131:         const float u = t + t;
132:         const float v = (u < 1.0f) ? (1.0f - u) : (u - 1.0f);
133:         return (2.0f - v * v * v) * 0.5f;
134:     }
135:     case 12:
136:     case 13: {
137:         const float u = t + t;
138:         if (u < 1.0f) {
139:             const float v = 1.0f - u;
140:             return 0.5f - v * v * v * 0.5f;
141:         }
142:         const float v = u - 1.0f;
143:         return v * v * v * 0.5f + 0.5f;
144:     }
145:     case 14: {
146:         const float u = t + t;
147:         if (u < 1.0f) {
148:             const float v = 1.0f - u;
149:             return 0.5f - v * v * v * v * 0.5f;
150:         }
151:         const float v = u - 1.0f;
152:         return v * v * v * v * 0.5f + 0.5f;
153:     }
154:     case 15: return 0.0f;
155:     case 16: return 1.0f;
156:     default: return t;
157:     }
158: }
159: 
160: // 0x00404610 - advance the embedded timer and evaluate a three-component
161: // trajectory record (the 0x119/0x11b per-axis sub-records).  Mode 7 adds
162: // the target row every frame, mode 0x11 integrates the control-B row, mode
163: // 8 evaluates the cubic bezier through both control rows, and every other
164: // mode eases between the start and target rows.  Completion publishes the
165: // terminal value and disarms the duration.
166: void Trajectory_Evaluate3D(Trajectory3D* state, float output[3],
167:                            const TrajectoryEnv* env) {
168:     const int duration = state->duration;
169:     if (duration > 0) {
170:         state->previous = state->current;
171:         const float speed = *state->speed;
172:         if (speed <= kNormalSpeedLow || speed >= kNormalSpeedHigh) {
173:             state->elapsed += speed;
174:             state->current = static_cast<int>(state->elapsed);
175:         } else {
176:             state->elapsed += 1.0f;
177:             ++state->current;
178:         }
179: 
180:         if (duration <= state->current) {
181:             if (!(state->timer_flags & 1)) {
182:                 state->current = 0;
183:                 state->previous = -999999;
184:                 state->elapsed = 0.0f;
185:                 state->speed = env->default_speed;
186:                 state->timer_flags |= 1;
187:             }
188:             state->current = duration;
189:             state->previous = duration - 1;
190:             state->elapsed = static_cast<float>(duration);
191:             state->duration = 0;
192: 
193:             const float* final_value =
194:                 state->mode == kLinearIncrementMode ? state->p0
195:                                                     : state->velocity;
196:             for (int axis = 0; axis < 3; ++axis)
197:                 output[axis] = final_value[axis];
198:             return;
199:         }
200:     }
201: 
202:     if (state->mode == kLinearIncrementMode) {
203:         for (int axis = 0; axis < 3; ++axis) {
204:             state->p0[axis] += state->velocity[axis];
205:             output[axis] = state->p0[axis];
206:         }
207:     } else if (state->mode == kAcceleratingIncrementMode) {
208:         for (int axis = 0; axis < 3; ++axis) {
209:             state->p0[axis] += state->control_b[axis];
210:             output[axis] = state->p0[axis];
211:             state->control_b[axis] += state->velocity[axis];
212:         }
213:     } else if (state->mode == kHermiteMode) {
214:         const float time = state->elapsed / duration;
215:         const float time_minus_one = time - 1.0f;
216:         const float h00 = (1.0f + 2.0f * time) *
217:                           time_minus_one * time_minus_one;
218:         const float h01 = (3.0f - 2.0f * time) * time * time;
219:         const float h10 = (1.0f - time) * (1.0f - time) * time;
220:         const float h11 = time_minus_one * time * time;
221:         for (int axis = 0; axis < 3; ++axis) {
222:             output[axis] = h00 * state->p0[axis] +
223:                            h01 * state->velocity[axis] +
224:                            h10 * state->control_a[axis] +
225:                            h11 * state->control_b[axis];
226:         }
227:     } else {
228:         const float factor =
229:             env->ease(state->elapsed, static_cast<float>(duration),
230:                       state->mode);
231:         for (int axis = 0; axis < 3; ++axis) {
232:             output[axis] = (state->velocity[axis] - state->p0[axis]) *
233:                                factor +
234:                            state->p0[axis];
235:         }
236:     }
237: }
```

### [matching2/include/th10/game/trajectory_evaluate.hpp:1–47](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/game/trajectory_evaluate.hpp#L1-L47)

Whole-file SHA-256: `421bd3837f09bc41e579052290576fb8d42faf8eb81cf69460bb115009c90932`

```text
1: #pragma once
2: 
3: // Embedded-timer trajectory mode evaluation (retail 0x00412AC0 / 0x00404610).
4: // The ease callback receives the record's mode so it can dispatch through
5: // the full retail 0x0044C350 curve table.
6: struct TrajectoryEnv {
7:     const float* default_speed;
8:     float (*ease)(float elapsed, float duration, int mode);
9: };
10: 
11: // Retail function 0x00412AC0.  Record layout is byte-identical to the
12: // per-axis ECL movement records (entity transform +0x1D4/+0x210/+0x24C/
13: // +0x288): [0..1] p0, [2..3] velocity, [4..5] p2, [6..7] acceleration,
14: // [8] previous, [9] current, [10] elapsed, [11] speed pointer, [12] flags,
15: // [13] duration, [14] mode.
16: struct Trajectory2D {
17:     float p0[2], velocity[2], p2[2], acceleration[2];
18:     int previous, current;
19:     float elapsed;
20:     const float* speed;
21:     unsigned timer_flags;
22:     int duration, mode;
23: };
24: void Trajectory_Evaluate2D(Trajectory2D*, float[2], const TrajectoryEnv*);
25: 
26: // Retail function 0x00404610.  Record layout is byte-identical to the
27: // 0x119/0x11b per-axis sub-records (entity transform +0x13C/+0x188):
28: // [0..2] start triple, [3..5] target triple, [6..8] and [9..11] bezier
29: // control rows, [12] previous, [13] current, [14] elapsed, [15] speed
30: // pointer, [16] flags, [17] duration, [18] mode.
31: struct Trajectory3D {
32:     float p0[3];
33:     float velocity[3];
34:     float control_a[3];
35:     float control_b[3];
36:     int previous;
37:     int current;
38:     float elapsed;
39:     const float* speed;
40:     unsigned timer_flags;
41:     int duration;
42:     int mode;
43: };
44: void Trajectory_Evaluate3D(Trajectory3D*, float[3], const TrajectoryEnv*);
45: 
46: // Retail function 0x0044C350: mode-curve table over t = elapsed/duration.
47: float Trajectory_EaseFraction(float elapsed, float duration, int mode);
```

### [ida/th10.exe.c:22407–22574](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.c#L22407-L22574)

Whole-file SHA-256: `61481fa38c3e5695794ef5f5dd439c7e2af4126514b508af0a83400bfb481163`

```text
22407: //----- (00412AC0) --------------------------------------------------------
22408: float *__usercall sub_412AC0@<eax>(float *a1@<edi>, int a2@<esi>)
22409: {
22410:   int v2; // edx
22411:   float *v3; // ecx
22412:   double v4; // st7
22413:   double v5; // st7
22414:   int v6; // ecx
22415:   int v7; // eax
22416:   int v8; // eax
22417:   float *result; // eax
22418:   int v10; // eax
22419:   double v11; // st7
22420:   double v12; // st7
22421:   double v13; // st7
22422:   double v14; // st7
22423:   double v15; // st7
22424:   double v16; // st6
22425:   double v17; // st5
22426:   double v18; // st4
22427:   double v19; // st7
22428:   double v20; // st7
22429:   float v21; // [esp+0h] [ebp-24h]
22430:   int v22; // [esp+4h] [ebp-20h]
22431:   float v23; // [esp+4h] [ebp-20h]
22432:   float v24; // [esp+4h] [ebp-20h]
22433:   float v25; // [esp+4h] [ebp-20h]
22434:   float v26; // [esp+4h] [ebp-20h]
22435:   float v27; // [esp+8h] [ebp-1Ch]
22436:   float v28; // [esp+8h] [ebp-1Ch]
22437:   float v29; // [esp+8h] [ebp-1Ch]
22438:   float v30; // [esp+Ch] [ebp-18h]
22439:   float v31; // [esp+Ch] [ebp-18h]
22440:   float v32; // [esp+Ch] [ebp-18h]
22441:   float v33; // [esp+10h] [ebp-14h]
22442:   float v34; // [esp+10h] [ebp-14h]
22443:   float v35; // [esp+10h] [ebp-14h]
22444:   float v36; // [esp+14h] [ebp-10h]
22445:   float v37; // [esp+14h] [ebp-10h]
22446:   float v38; // [esp+18h] [ebp-Ch]
22447:   float v39; // [esp+18h] [ebp-Ch]
22448:   float v40; // [esp+1Ch] [ebp-8h]
22449:   float v41; // [esp+20h] [ebp-4h]
22450:   float v42; // [esp+20h] [ebp-4h]
22451:   float v43; // [esp+20h] [ebp-4h]
22452: 
22453:   v22 = *(_DWORD *)(a2 + 52);
22454:   if ( v22 <= 0 )
22455:     goto LABEL_13;
22456:   v2 = *(_DWORD *)(a2 + 36);
22457:   v3 = *(float **)(a2 + 44);
22458:   *(_DWORD *)(a2 + 32) = v2;
22459:   if ( *v3 <= 0.99000001 || *v3 >= 1.01 )
22460:   {
22461:     v5 = *v3 + *(float *)(a2 + 40);
22462:     *(float *)(a2 + 40) = v5;
22463:     *(_DWORD *)(a2 + 36) = (unsigned __int64)v5;
22464:   }
22465:   else
22466:   {
22467:     v4 = *(float *)(a2 + 40) + 1.0;
22468:     *(_DWORD *)(a2 + 36) = v2 + 1;
22469:     *(float *)(a2 + 40) = v4;
22470:   }
22471:   v6 = *(_DWORD *)(a2 + 52);
22472:   v22 = v6;
22473:   if ( *(_DWORD *)(a2 + 36) < v6 )
22474:   {
22475: LABEL_13:
22476:     v10 = *(_DWORD *)(a2 + 56);
22477:     if ( v10 == 7 )
22478:     {
22479:       v23 = *(float *)a2 + *(float *)(a2 + 8);
22480:       v11 = *(float *)(a2 + 4) + *(float *)(a2 + 12);
22481:       *(float *)a2 = v23;
22482:       v27 = v11;
22483:       *(float *)(a2 + 4) = v27;
22484:       *a1 = v23;
22485:       a1[1] = v27;
22486:       return a1;
22487:     }
22488:     else if ( v10 == 17 )
22489:     {
22490:       v24 = *(float *)a2 + *(float *)(a2 + 24);
22491:       v12 = *(float *)(a2 + 4) + *(float *)(a2 + 28);
22492:       *(float *)a2 = v24;
22493:       v28 = v12;
22494:       *(float *)(a2 + 4) = v28;
22495:       v30 = *(float *)(a2 + 24) + *(float *)(a2 + 8);
22496:       v13 = *(float *)(a2 + 12) + *(float *)(a2 + 28);
22497:       *(float *)(a2 + 24) = v30;
22498:       v33 = v13;
22499:       *(float *)(a2 + 28) = v33;
22500:       *a1 = v24;
22501:       a1[1] = v28;
22502:       return a1;
22503:     }
22504:     else
22505:     {
22506:       v14 = (double)v22;
22507:       if ( v10 == 8 )
22508:       {
22509:         v15 = *(float *)(a2 + 40) / v14;
22510:         v25 = v15 - 1.0;
22511:         v31 = (v15 + v15 + 1.0) * v25 * v25;
22512:         v16 = (3.0 - (v15 + v15)) * v15 * v15;
22513:         v17 = (1.0 - v15) * (1.0 - v15) * v15;
22514:         v18 = v25 * v15 * v15;
22515:         v36 = v18 * *(float *)(a2 + 24);
22516:         v38 = v18 * *(float *)(a2 + 28);
22517:         v26 = v17 * *(float *)(a2 + 16);
22518:         v29 = v17 * *(float *)(a2 + 20);
22519:         v40 = v16 * *(float *)(a2 + 8);
22520:         v34 = v31 * *(float *)(a2 + 4);
22521:         v41 = v34 + v16 * *(float *)(a2 + 12);
22522:         v32 = v31 * *(float *)a2 + v40 + v26 + v36;
22523:         *a1 = v32;
22524:         result = a1;
22525:         v35 = v41 + v29 + v38;
22526:         a1[1] = v35;
22527:       }
22528:       else
22529:       {
22530:         v21 = v14;
22531:         v19 = sub_44C350(v10, *(float *)(a2 + 40), v21);
22532:         v42 = *(float *)(a2 + 12) - *(float *)(a2 + 4);
22533:         v43 = v42 * v19;
22534:         v37 = (*(float *)(a2 + 8) - *(float *)a2) * v19 + *(float *)a2;
22535:         v20 = v43 + *(float *)(a2 + 4);
22536:         *a1 = v37;
22537:         result = a1;
22538:         v39 = v20;
22539:         a1[1] = v39;
22540:       }
22541:     }
22542:   }
22543:   else
22544:   {
22545:     v7 = *(_DWORD *)(a2 + 48);
22546:     if ( (v7 & 1) == 0 )
22547:     {
22548:       *(_DWORD *)(a2 + 36) = 0;
22549:       *(_DWORD *)(a2 + 32) = -999999;
22550:       *(_DWORD *)(a2 + 40) = 0;
22551:       *(_DWORD *)(a2 + 44) = &flt_476F78;
22552:       *(_DWORD *)(a2 + 48) = v7 | 1;
22553:     }
22554:     *(_DWORD *)(a2 + 36) = v6;
22555:     *(_DWORD *)(a2 + 32) = v6 - 1;
22556:     *(float *)(a2 + 40) = (float)v6;
22557:     v8 = *(_DWORD *)(a2 + 56);
22558:     *(_DWORD *)(a2 + 52) = 0;
22559:     if ( v8 == 7 )
22560:     {
22561:       *a1 = *(float *)a2;
22562:       a1[1] = *(float *)(a2 + 4);
22563:     }
22564:     else
22565:     {
22566:       *a1 = *(float *)(a2 + 8);
22567:       a1[1] = *(float *)(a2 + 12);
22568:     }
22569:     return a1;
22570:   }
22571:   return result;
22572: }
22573: // 476F78: using guessed type float flt_476F78;
22574: 
```

### [ida/th10.exe.asm:25302–25541](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L25302-L25541)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
25302: sub_412AC0 proc near
25303: 
25304: var_24= dword ptr -24h
25305: var_20= dword ptr -20h
25306: var_1C= dword ptr -1Ch
25307: var_18= dword ptr -18h
25308: var_14= dword ptr -14h
25309: var_10= dword ptr -10h
25310: var_C= dword ptr -0Ch
25311: var_8= dword ptr -8
25312: var_4= dword ptr -4
25313: 
25314: sub     esp, 20h
25315: mov     eax, [esi+34h]
25316: test    eax, eax
25317: mov     [esp+20h+var_20], eax
25318: jle     loc_412B90
25319: mov     edx, [esi+24h]
25320: mov     ecx, [esi+2Ch]
25321: mov     [esi+20h], edx
25322: fld     dword ptr [ecx]
25323: fcomp   ds:flt_470B68
25324: fnstsw  ax
25325: test    ah, 41h
25326: jnz     short loc_412B0A
25327: fld     dword ptr [ecx]
25328: fcomp   ds:flt_470B64
25329: fnstsw  ax
25330: test    ah, 5
25331: jp      short loc_412B0A
25332: fld     dword ptr [esi+28h]
25333: inc     edx
25334: fadd    ds:flt_470AFC
25335: mov     [esi+24h], edx
25336: fstp    dword ptr [esi+28h]
25337: jmp     short loc_412B1A
25338: 
25339: loc_412B0A:
25340: fld     dword ptr [ecx]
25341: fadd    dword ptr [esi+28h]
25342: fst     dword ptr [esi+28h]
25343: call    __ftol2
25344: mov     [esi+24h], eax
25345: 
25346: loc_412B1A:
25347: mov     ecx, [esi+34h]
25348: cmp     [esi+24h], ecx
25349: mov     [esp+20h+var_20], ecx
25350: jl      short loc_412B90
25351: mov     eax, [esi+30h]
25352: test    al, 1
25353: mov     [esp+20h+var_18], ecx
25354: jnz     short loc_412B52
25355: or      eax, 1
25356: mov     dword ptr [esi+24h], 0
25357: mov     dword ptr [esi+20h], 0FFF0BDC1h
25358: mov     dword ptr [esi+28h], 0
25359: mov     dword ptr [esi+2Ch], offset flt_476F78
25360: mov     [esi+30h], eax
25361: 
25362: loc_412B52:
25363: fild    [esp+20h+var_18]
25364: mov     [esi+24h], ecx
25365: dec     ecx
25366: mov     [esi+20h], ecx
25367: fstp    dword ptr [esi+28h]
25368: mov     eax, [esi+38h]
25369: cmp     eax, 7
25370: mov     dword ptr [esi+34h], 0
25371: jz      short loc_412B80
25372: mov     eax, [esi+8]
25373: mov     [edi], eax
25374: mov     ecx, [esi+0Ch]
25375: mov     [edi+4], ecx
25376: mov     eax, edi
25377: add     esp, 20h
25378: retn
25379: 
25380: loc_412B80:
25381: mov     edx, [esi]
25382: mov     [edi], edx
25383: mov     eax, [esi+4]
25384: mov     [edi+4], eax
25385: mov     eax, edi
25386: add     esp, 20h
25387: retn
25388: 
25389: loc_412B90:
25390: mov     eax, [esi+38h]
25391: cmp     eax, 7
25392: jnz     short loc_412BD1
25393: mov     ecx, [esi]
25394: mov     edx, [esi+4]
25395: mov     [esp+20h+var_18], ecx
25396: fld     [esp+20h+var_18]
25397: fadd    dword ptr [esi+8]
25398: mov     [esp+20h+var_14], edx
25399: fstp    [esp+20h+var_20]
25400: mov     eax, [esp+20h+var_20]
25401: fld     [esp+20h+var_14]
25402: fadd    dword ptr [esi+0Ch]
25403: mov     [esi], eax
25404: fstp    [esp+20h+var_1C]
25405: mov     ecx, [esp+20h+var_1C]
25406: mov     [esi+4], ecx
25407: mov     [edi], eax
25408: mov     [edi+4], ecx
25409: mov     eax, edi
25410: add     esp, 20h
25411: retn
25412: 
25413: loc_412BD1:
25414: cmp     eax, 11h
25415: jnz     short loc_412C31
25416: mov     eax, [esi]
25417: mov     ecx, [esi+4]
25418: mov     [esp+20h+var_18], eax
25419: fld     [esp+20h+var_18]
25420: fadd    dword ptr [esi+18h]
25421: mov     [esp+20h+var_14], ecx
25422: fstp    [esp+20h+var_20]
25423: mov     eax, [esp+20h+var_20]
25424: fld     [esp+20h+var_14]
25425: fadd    dword ptr [esi+1Ch]
25426: mov     [esi], eax
25427: fstp    [esp+20h+var_1C]
25428: mov     ecx, [esp+20h+var_1C]
25429: mov     [esi+4], ecx
25430: fld     dword ptr [esi+18h]
25431: fadd    dword ptr [esi+8]
25432: fstp    [esp+20h+var_18]
25433: mov     edx, [esp+20h+var_18]
25434: fld     dword ptr [esi+0Ch]
25435: fadd    dword ptr [esi+1Ch]
25436: mov     [esi+18h], edx
25437: fstp    [esp+20h+var_14]
25438: mov     edx, [esp+20h+var_14]
25439: mov     [esi+1Ch], edx
25440: mov     [edi], eax
25441: mov     [edi+4], ecx
25442: mov     eax, edi
25443: add     esp, 20h
25444: retn
25445: 
25446: loc_412C31:
25447: cmp     eax, 8
25448: fild    [esp+20h+var_20]
25449: jnz     loc_412CFE
25450: fdivr   dword ptr [esi+28h]
25451: fld     st
25452: fadd    st, st(1)
25453: fld     st(1)
25454: fsub    ds:flt_470AFC
25455: fstp    [esp+20h+var_20]
25456: fld     ds:flt_470AFC
25457: fadd    st, st(1)
25458: fmul    [esp+20h+var_20]
25459: fmul    [esp+20h+var_20]
25460: fstp    [esp+20h+var_18]
25461: fsubr   ds:flt_470BD4
25462: fmul    st, st(1)
25463: fmul    st, st(1)
25464: fld     ds:flt_470AFC
25465: fsub    st, st(2)
25466: fld     st
25467: fmulp   st(1), st
25468: fmul    st, st(2)
25469: fld     [esp+20h+var_20]
25470: fmul    st, st(3)
25471: fmul    st, st(3)
25472: fld     st
25473: fmul    dword ptr [esi+18h]
25474: fstp    [esp+20h+var_10]
25475: fmul    dword ptr [esi+1Ch]
25476: fstp    [esp+20h+var_C]
25477: fld     st
25478: fmul    dword ptr [esi+10h]
25479: fstp    [esp+20h+var_20]
25480: fmul    dword ptr [esi+14h]
25481: fstp    [esp+20h+var_1C]
25482: fld     st
25483: fmul    dword ptr [esi+8]
25484: fstp    [esp+20h+var_8]
25485: fmul    dword ptr [esi+0Ch]
25486: fstp    st(1)
25487: fld     [esp+20h+var_18]
25488: fmul    dword ptr [esi]
25489: fld     [esp+20h+var_18]
25490: fmul    dword ptr [esi+4]
25491: fstp    [esp+20h+var_14]
25492: fadd    [esp+20h+var_8]
25493: fld     [esp+20h+var_14]
25494: fadd    st, st(2)
25495: fstp    [esp+20h+var_4]
25496: fadd    [esp+20h+var_20]
25497: fstp    st(1)
25498: fld     [esp+20h+var_4]
25499: fadd    [esp+20h+var_1C]
25500: fxch    st(1)
25501: fadd    [esp+20h+var_10]
25502: fstp    [esp+20h+var_18]
25503: mov     eax, [esp+20h+var_18]
25504: mov     [edi], eax
25505: fadd    [esp+20h+var_C]
25506: mov     eax, edi
25507: fstp    [esp+20h+var_14]
25508: mov     ecx, [esp+20h+var_14]
25509: mov     [edi+4], ecx
25510: add     esp, 20h
25511: retn
25512: 
25513: loc_412CFE:
25514: mov     edx, [esi+28h]
25515: push    ecx
25516: fstp    [esp+24h+var_24] ; float
25517: push    edx             ; float
25518: call    sub_44C350
25519: fld     dword ptr [esi+8]
25520: fsub    dword ptr [esi]
25521: fld     dword ptr [esi+0Ch]
25522: fsub    dword ptr [esi+4]
25523: fstp    [esp+20h+var_4]
25524: fmul    st, st(1)
25525: fld     [esp+20h+var_4]
25526: fmul    st, st(2)
25527: fstp    [esp+20h+var_4]
25528: fadd    dword ptr [esi]
25529: fstp    [esp+20h+var_10]
25530: mov     eax, [esp+20h+var_10]
25531: fstp    st
25532: fld     [esp+20h+var_4]
25533: fadd    dword ptr [esi+4]
25534: mov     [edi], eax
25535: mov     eax, edi
25536: fstp    [esp+20h+var_C]
25537: mov     ecx, [esp+20h+var_C]
25538: mov     [edi+4], ecx
25539: add     esp, 20h
25540: retn
25541: sub_412AC0 endp
```

## Referenced retail constants

### [ida/th10.exe.asm:163280–163280](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163280-L163280)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163280: flt_470AFC dd 1.0
```

### [ida/th10.exe.asm:163304–163304](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163304-L163304)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163304: flt_470B64 dd 1.01
```

### [ida/th10.exe.asm:163305–163305](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163305-L163305)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163305: flt_470B68 dd 0.99000001
```

### [ida/th10.exe.asm:163327–163327](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163327-L163327)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163327: flt_470BD4 dd 3.0
```

### [ida/th10.exe.asm:179651–179651](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L179651-L179651)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
179651: flt_476F78 dd 1.0
```

### [decompiled/ghidra_raw/00412AC0_FUN_00412ac0.c:1–116](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/decompiled/ghidra_raw/00412AC0_FUN_00412ac0.c#L1-L116)

Whole-file SHA-256: `bcaa407a09b9db5ccfeacb28c2df274925bdf6aa6126c361c98f765a3e8e838b`

```text
1: /*
2:  * Raw Ghidra pseudocode reference; not directly compilable.
3:  * Address: 0x00412AC0
4:  * Tracking name: FUN_00412ac0
5:  * Ghidra name: FUN_00412ac0
6:  * Tracked span: 752 bytes
7:  */
8: 
9: 
10: /* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
11: 
12: void FUN_00412ac0(void)
13: 
14: {
15:   float *pfVar1;
16:   float fVar2;
17:   float fVar3;
18:   float fVar4;
19:   float fVar5;
20:   float fVar6;
21:   float fVar7;
22:   float fVar8;
23:   float fVar9;
24:   float *unaff_ESI;
25:   float *unaff_EDI;
26:   float10 fVar10;
27:   ulonglong uVar11;
28:   float local_20;
29:   
30:   local_20 = unaff_ESI[0xd];
31:   if (0 < (int)local_20) {
32:     pfVar1 = (float *)unaff_ESI[0xb];
33:     unaff_ESI[8] = unaff_ESI[9];
34:     if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
35:       unaff_ESI[10] = *pfVar1 + unaff_ESI[10];
36:       uVar11 = FUN_00463b2c();
37:       unaff_ESI[9] = (float)uVar11;
38:     }
39:     else {
40:       fVar2 = unaff_ESI[10] + _DAT_00470afc;
41:       unaff_ESI[9] = (float)((int)unaff_ESI[9] + 1);
42:       unaff_ESI[10] = fVar2;
43:     }
44:     local_20 = unaff_ESI[0xd];
45:     if ((int)local_20 <= (int)unaff_ESI[9]) {
46:       if (((uint)unaff_ESI[0xc] & 1) == 0) {
47:         unaff_ESI[9] = 0.0;
48:         unaff_ESI[8] = -NAN;
49:         unaff_ESI[10] = 0.0;
50:         unaff_ESI[0xb] = (float)&DAT_00476f78;
51:         unaff_ESI[0xc] = (float)((uint)unaff_ESI[0xc] | 1);
52:       }
53:       unaff_ESI[9] = local_20;
54:       unaff_ESI[8] = (float)((int)local_20 + -1);
55:       unaff_ESI[10] = (float)(int)local_20;
56:       unaff_ESI[0xd] = 0.0;
57:       if (unaff_ESI[0xe] != 9.80909e-45) {
58:         *unaff_EDI = unaff_ESI[2];
59:         unaff_EDI[1] = unaff_ESI[3];
60:         return;
61:       }
62:       *unaff_EDI = *unaff_ESI;
63:       unaff_EDI[1] = unaff_ESI[1];
64:       return;
65:     }
66:   }
67:   fVar2 = unaff_ESI[0xe];
68:   if (fVar2 == 9.80909e-45) {
69:     fVar3 = *unaff_ESI;
70:     fVar4 = unaff_ESI[1];
71:     fVar2 = unaff_ESI[3];
72:     *unaff_ESI = fVar3 + unaff_ESI[2];
73:     unaff_ESI[1] = fVar4 + fVar2;
74:     *unaff_EDI = fVar3 + unaff_ESI[2];
75:     unaff_EDI[1] = fVar4 + fVar2;
76:     return;
77:   }
78:   if (fVar2 == 2.38221e-44) {
79:     fVar4 = *unaff_ESI;
80:     fVar5 = unaff_ESI[1];
81:     fVar2 = unaff_ESI[6];
82:     fVar3 = unaff_ESI[7];
83:     *unaff_ESI = fVar4 + fVar2;
84:     unaff_ESI[1] = fVar5 + fVar3;
85:     unaff_ESI[6] = unaff_ESI[6] + unaff_ESI[2];
86:     unaff_ESI[7] = unaff_ESI[3] + unaff_ESI[7];
87:     *unaff_EDI = fVar4 + fVar2;
88:     unaff_EDI[1] = fVar5 + fVar3;
89:     return;
90:   }
91:   if (fVar2 == 1.12104e-44) {
92:     fVar6 = unaff_ESI[10] / (float)(int)local_20;
93:     fVar2 = fVar6 - _DAT_00470afc;
94:     fVar9 = (_DAT_00470afc + fVar6 + fVar6) * fVar2 * fVar2;
95:     fVar7 = (_DAT_00470bd4 - (fVar6 + fVar6)) * fVar6 * fVar6;
96:     fVar8 = (_DAT_00470afc - fVar6) * (_DAT_00470afc - fVar6) * fVar6;
97:     fVar6 = fVar2 * fVar6 * fVar6;
98:     fVar2 = unaff_ESI[7];
99:     fVar3 = unaff_ESI[5];
100:     fVar4 = unaff_ESI[3];
101:     fVar5 = unaff_ESI[1];
102:     *unaff_EDI = fVar9 * *unaff_ESI + fVar7 * unaff_ESI[2] + fVar8 * unaff_ESI[4] +
103:                  fVar6 * unaff_ESI[6];
104:     unaff_EDI[1] = fVar9 * fVar5 + fVar7 * fVar4 + fVar8 * fVar3 + fVar6 * fVar2;
105:     return;
106:   }
107:   fVar10 = FUN_0044c350(unaff_ESI[10],(float)(int)local_20);
108:   fVar2 = unaff_ESI[3];
109:   fVar3 = unaff_ESI[1];
110:   fVar4 = unaff_ESI[1];
111:   *unaff_EDI = (float)(((float10)unaff_ESI[2] - (float10)*unaff_ESI) * fVar10 + (float10)*unaff_ESI)
112:   ;
113:   unaff_EDI[1] = (float)((float10)(fVar2 - fVar3) * fVar10) + fVar4;
114:   return;
115: }
116: 
```

## Production textual cross-references

All token occurrences in versioned `src/` and `standalone/` C++/headers are listed below, including definitions and comments. These are navigation aids; indirect calls and differently named adapters require further inspection. Tests are deliberately excluded from this production search.

- [matching2/src/game/bullet.cpp:246](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L246): `Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x1D4),`
- [matching2/src/game/bullet.cpp:252](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L252): `Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x24C),`
- [matching2/src/game/bullet.cpp:258](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L258): `Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x210),`
- [matching2/src/game/bullet.cpp:264](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L264): `Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x288),`
- [matching2/src/game/trajectory_evaluate.cpp:37](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/trajectory_evaluate.cpp#L37): `void Trajectory_Evaluate2D(Trajectory2D* state, float output[2],`

### [matching2/src/game/bullet.cpp:238–258](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L238-L258)

Whole-file SHA-256: `5c71109c0826ce8d6b334a610eb680b71a243bb83f4258518a95751db75c170a`

```text
238:     // Retail 0x0040DC80: per-axis record reads feed the angle/radius slots
239:     // (sub_412AC0), the two position paths follow the armed 0x13C/0x188
240:     // records (sub_404610) or integrate/rebuild from those slots, and the
241:     // three motion records advance through sub_44C2A0.
242:     TrajectoryEnv trajectory_env = {EntityDefaultSpeed(),
243:                                     Trajectory_EaseFraction};
244:     float pair[2];
245:     if (*reinterpret_cast<int32_t*>(state + 0x208) != 0) {
246:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x1D4),
247:                               pair, &trajectory_env);
248:         *reinterpret_cast<float*>(state + 0x70) = pair[1];
249:         *reinterpret_cast<float*>(state + 0x74) = Entity_WrapAngle(pair[0]);
250:     }
251:     if (*reinterpret_cast<int32_t*>(state + 0x280) != 0) {
252:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x24C),
253:                               pair, &trajectory_env);
254:         *reinterpret_cast<float*>(state + 0x78) = pair[0];
255:         *reinterpret_cast<float*>(state + 0x7C) = pair[1];
256:     }
257:     if (*reinterpret_cast<int32_t*>(state + 0x244) != 0) {
258:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x210),
```

### [matching2/src/game/bullet.cpp:244–264](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L244-L264)

Whole-file SHA-256: `5c71109c0826ce8d6b334a610eb680b71a243bb83f4258518a95751db75c170a`

```text
244:     float pair[2];
245:     if (*reinterpret_cast<int32_t*>(state + 0x208) != 0) {
246:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x1D4),
247:                               pair, &trajectory_env);
248:         *reinterpret_cast<float*>(state + 0x70) = pair[1];
249:         *reinterpret_cast<float*>(state + 0x74) = Entity_WrapAngle(pair[0]);
250:     }
251:     if (*reinterpret_cast<int32_t*>(state + 0x280) != 0) {
252:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x24C),
253:                               pair, &trajectory_env);
254:         *reinterpret_cast<float*>(state + 0x78) = pair[0];
255:         *reinterpret_cast<float*>(state + 0x7C) = pair[1];
256:     }
257:     if (*reinterpret_cast<int32_t*>(state + 0x244) != 0) {
258:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x210),
259:                               pair, &trajectory_env);
260:         *reinterpret_cast<float*>(state + 0x9C) = pair[1];
261:         *reinterpret_cast<float*>(state + 0xA0) = Entity_WrapAngle(pair[0]);
262:     }
263:     if (*reinterpret_cast<int32_t*>(state + 0x2BC) != 0) {
264:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x288),
```

### [matching2/src/game/bullet.cpp:250–270](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L250-L270)

Whole-file SHA-256: `5c71109c0826ce8d6b334a610eb680b71a243bb83f4258518a95751db75c170a`

```text
250:     }
251:     if (*reinterpret_cast<int32_t*>(state + 0x280) != 0) {
252:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x24C),
253:                               pair, &trajectory_env);
254:         *reinterpret_cast<float*>(state + 0x78) = pair[0];
255:         *reinterpret_cast<float*>(state + 0x7C) = pair[1];
256:     }
257:     if (*reinterpret_cast<int32_t*>(state + 0x244) != 0) {
258:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x210),
259:                               pair, &trajectory_env);
260:         *reinterpret_cast<float*>(state + 0x9C) = pair[1];
261:         *reinterpret_cast<float*>(state + 0xA0) = Entity_WrapAngle(pair[0]);
262:     }
263:     if (*reinterpret_cast<int32_t*>(state + 0x2BC) != 0) {
264:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x288),
265:                               pair, &trajectory_env);
266:         *reinterpret_cast<float*>(state + 0xA4) = pair[0];
267:         *reinterpret_cast<float*>(state + 0xA8) = pair[1];
268:     }
269: 
270:     if (*reinterpret_cast<int32_t*>(state + 0x180) != 0) {
```

### [matching2/src/game/bullet.cpp:256–276](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L256-L276)

Whole-file SHA-256: `5c71109c0826ce8d6b334a610eb680b71a243bb83f4258518a95751db75c170a`

```text
256:     }
257:     if (*reinterpret_cast<int32_t*>(state + 0x244) != 0) {
258:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x210),
259:                               pair, &trajectory_env);
260:         *reinterpret_cast<float*>(state + 0x9C) = pair[1];
261:         *reinterpret_cast<float*>(state + 0xA0) = Entity_WrapAngle(pair[0]);
262:     }
263:     if (*reinterpret_cast<int32_t*>(state + 0x2BC) != 0) {
264:         Trajectory_Evaluate2D(reinterpret_cast<Trajectory2D*>(state + 0x288),
265:                               pair, &trajectory_env);
266:         *reinterpret_cast<float*>(state + 0xA4) = pair[0];
267:         *reinterpret_cast<float*>(state + 0xA8) = pair[1];
268:     }
269: 
270:     if (*reinterpret_cast<int32_t*>(state + 0x180) != 0) {
271:         float path[3];
272:         Trajectory_Evaluate3D(reinterpret_cast<Trajectory3D*>(state + 0x13C),
273:                               path, &trajectory_env);
274:         float* position = reinterpret_cast<float*>(state + 0x64);
275:         position[0] = path[0] - *reinterpret_cast<float*>(state + 0x58);
276:         position[1] = path[1] - *reinterpret_cast<float*>(state + 0x5C);
```
