# Calibration packet: 0x0044C350

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

### [matching2/src/math/easing.cpp:1–51](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/math/easing.cpp#L1-L51)

Whole-file SHA-256: `4c4cb72ded38496c6f0bea69a0a32514786b6de188d70b930c199de72e420a03`

```text
1: #include "th10/math/easing.hpp"
2: 
3: // 0x0044C350 - Evaluate the retail animation easing table. Retail evaluates
4: // through x87 extended intermediates; double keeps the same shape on host
5: // builds while retaining the explicit mode/ratio semantics.
6: float Easing_Evaluate(int mode, float numerator, float denominator) {
7:     const double ratio = (double)numerator / (double)denominator;
8:     const double one = 1.0;
9:     const double two = 2.0;
10:     const double half = 0.5;
11:     double x;
12:     switch (mode) {
13:     case 1: return (float)(ratio * ratio);
14:     case 2: return (float)(ratio * ratio * ratio);
15:     case 3: return (float)(ratio * ratio * ratio * ratio);
16:     case 4: x = one - ratio; return (float)(one - x * x);
17:     case 5: x = one - ratio; return (float)(one - x * x * x);
18:     case 6: x = one - ratio; return (float)(one - x * x * x * x);
19:     case 9:
20:         x = ratio + ratio;
21:         return (float)(x < one ? x * x * half :
22:                        (two - (two - x) * (two - x)) * half);
23:     case 10:
24:         x = ratio + ratio;
25:         return (float)(x < one ? x * x * x * half :
26:                        (two - (two - x) * (two - x) * (two - x)) * half);
27:     case 11:
28:         x = ratio + ratio;
29:         return (float)(x < one ? x * x * x * x * half :
30:                        (two - (two - x) * (two - x) * (two - x) *
31:                         (two - x)) * half);
32:     case 12:
33:         x = ratio + ratio;
34:         return (float)(x < one ? half - (one - x) * (one - x) * half :
35:                        (x - one) * (x - one) * half + half);
36:     case 13:
37:         x = ratio + ratio;
38:         return (float)(x < one ? half - (one - x) * (one - x) *
39:                        (one - x) * half :
40:                        (x - one) * (x - one) * (x - one) * half + half);
41:     case 14:
42:         x = ratio + ratio;
43:         return (float)(x < one ? half - (one - x) * (one - x) *
44:                        (one - x) * (one - x) * half :
45:                        (x - one) * (x - one) * (x - one) * (x - one) *
46:                        half + half);
47:     case 15: return 0.0f;
48:     case 16: return 1.0f;
49:     default: return (float)ratio;
50:     }
51: }
```

### [matching2/include/th10/math/easing.hpp:1–5](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/math/easing.hpp#L1-L5)

Whole-file SHA-256: `48c3be602a5da9a8c6daaafc14d0796ff37919afdd9de4f78206de8d38d23379`

```text
1: #pragma once
2: 
3: // Piecewise easing selector used by animation interpolation. The mode is a
4: // hidden retail register argument; the conventional form makes it explicit.
5: float Easing_Evaluate(int mode, float numerator, float denominator);
```

### [ida/th10.exe.c:67760–67875](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.c#L67760-L67875)

Whole-file SHA-256: `61481fa38c3e5695794ef5f5dd439c7e2af4126514b508af0a83400bfb481163`

```text
67760: //----- (0044C350) --------------------------------------------------------
67761: double __userpurge sub_44C350@<st0>(int a1@<eax>, float a2, float a3)
67762: {
67763:   double result; // st7
67764:   double v4; // st7
67765:   double v5; // st7
67766:   double v6; // st7
67767:   double v7; // st7
67768:   double v8; // st5
67769:   double v9; // st7
67770:   double v10; // st7
67771:   double v11; // st5
67772:   double v12; // st7
67773:   double v13; // st5
67774:   double v14; // st7
67775:   double v15; // st7
67776: 
67777:   result = a2 / a3;
67778:   switch ( a1 )
67779:   {
67780:     case 1:
67781:       result = result * result;
67782:       break;
67783:     case 2:
67784:       result = result * (result * result);
67785:       break;
67786:     case 3:
67787:       result = result * (result * result * result);
67788:       break;
67789:     case 4:
67790:       result = 1.0 - (1.0 - result) * (1.0 - result);
67791:       break;
67792:     case 5:
67793:       result = 1.0 - (1.0 - result) * ((1.0 - result) * (1.0 - result));
67794:       break;
67795:     case 6:
67796:       result = 1.0 - (1.0 - result) * ((1.0 - result) * (1.0 - result) * (1.0 - result));
67797:       break;
67798:     case 9:
67799:       v4 = result + result;
67800:       if ( v4 >= 1.0 )
67801:         result = (2.0 - (2.0 - v4) * (2.0 - v4)) * 0.5;
67802:       else
67803:         result = v4 * v4 * 0.5;
67804:       break;
67805:     case 10:
67806:       v6 = result + result;
67807:       if ( v6 >= 1.0 )
67808:       {
67809:         v7 = 2.0 - v6;
67810:         v8 = v7 * v7;
67811:         goto LABEL_23;
67812:       }
67813:       result = v6 * (v6 * v6) * 0.5;
67814:       break;
67815:     case 11:
67816:       v14 = result + result;
67817:       if ( v14 >= 1.0 )
67818:       {
67819:         v7 = 2.0 - v14;
67820:         v8 = v7 * v7 * v7;
67821: LABEL_23:
67822:         result = (2.0 - v7 * v8) * 0.5;
67823:       }
67824:       else
67825:       {
67826:         result = v14 * (v14 * v14 * v14) * 0.5;
67827:       }
67828:       break;
67829:     case 12:
67830:       v5 = result + result;
67831:       if ( v5 >= 1.0 )
67832:         result = (v5 - 1.0) * (v5 - 1.0) * 0.5 + 0.5;
67833:       else
67834:         result = 0.5 - (1.0 - v5) * (1.0 - v5) * 0.5;
67835:       break;
67836:     case 13:
67837:       v9 = result + result;
67838:       if ( v9 < 1.0 )
67839:       {
67840:         v10 = 1.0 - v9;
67841:         v11 = v10 * v10;
67842:         goto LABEL_26;
67843:       }
67844:       v12 = v9 - 1.0;
67845:       v13 = v12 * v12;
67846:       goto LABEL_28;
67847:     case 14:
67848:       v15 = result + result;
67849:       if ( v15 >= 1.0 )
67850:       {
67851:         v12 = v15 - 1.0;
67852:         v13 = v12 * v12 * v12;
67853: LABEL_28:
67854:         result = v12 * v13 * 0.5 + 0.5;
67855:       }
67856:       else
67857:       {
67858:         v10 = 1.0 - v15;
67859:         v11 = v10 * v10 * v10;
67860: LABEL_26:
67861:         result = 0.5 - v10 * v11 * 0.5;
67862:       }
67863:       break;
67864:     case 15:
67865:       result = 0.0;
67866:       break;
67867:     case 16:
67868:       result = 1.0;
67869:       break;
67870:     default:
67871:       return result;
67872:   }
67873:   return result;
67874: }
67875: 
```

### [ida/th10.exe.asm:112590–112802](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L112590-L112802)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
112590: sub_44C350 proc near
112591: 
112592: arg_0= dword ptr  4
112593: arg_4= dword ptr  8
112594: 
112595: fld     [esp+arg_0]
112596: dec     eax             ; switch 16 cases
112597: cmp     eax, 0Fh
112598: fdiv    [esp+arg_4]
112599: ja      def_44C362      ; jumptable 0044C362 default case, cases 7,8
112600: jmp     ds:jpt_44C362[eax*4] ; switch jump
112601: 
112602: loc_44C369:             ; jumptable 0044C362 case 1
112603: fld     st
112604: fmulp   st(1), st
112605: retn    8
112606: 
112607: loc_44C370:             ; jumptable 0044C362 case 4
112608: fsubr   ds:flt_470AFC
112609: fld     st
112610: fmulp   st(1), st
112611: fsubr   ds:flt_470AFC
112612: retn    8
112613: 
112614: loc_44C383:             ; jumptable 0044C362 case 2
112615: fld     st
112616: fmul    st, st(1)
112617: fmulp   st(1), st
112618: retn    8
112619: 
112620: loc_44C38C:             ; jumptable 0044C362 case 5
112621: fsubr   ds:flt_470AFC
112622: fld     st
112623: fld     st
112624: fmul    st, st(1)
112625: fmulp   st(2), st
112626: fxch    st(1)
112627: fsubr   ds:flt_470AFC
112628: fstp    st(1)
112629: retn    8
112630: 
112631: loc_44C3A7:             ; jumptable 0044C362 case 3
112632: fld     st
112633: fmul    st, st(1)
112634: fmul    st, st(1)
112635: fmulp   st(1), st
112636: retn    8
112637: 
112638: loc_44C3B2:             ; jumptable 0044C362 case 6
112639: fsubr   ds:flt_470AFC
112640: fld     st
112641: fld     st
112642: fmul    st, st(1)
112643: fmul    st, st(2)
112644: fmulp   st(2), st
112645: fxch    st(1)
112646: fsubr   ds:flt_470AFC
112647: fstp    st(1)
112648: retn    8
112649: 
112650: loc_44C3CF:             ; jumptable 0044C362 case 9
112651: fadd    st, st
112652: fcom    ds:flt_470AFC
112653: fnstsw  ax
112654: test    ah, 5
112655: jp      short loc_44C3EB
112656: fld     st
112657: fmulp   st(1), st
112658: fmul    ds:flt_470B0C
112659: retn    8
112660: 
112661: loc_44C3EB:
112662: fsubr   ds:flt_470B08
112663: fld     st
112664: fmulp   st(1), st
112665: fsubr   ds:flt_470B08
112666: fmul    ds:flt_470B0C
112667: retn    8
112668: 
112669: loc_44C404:             ; jumptable 0044C362 case 12
112670: fadd    st, st
112671: fcom    ds:flt_470AFC
112672: fnstsw  ax
112673: test    ah, 5
112674: jp      short loc_44C42C
112675: fsubr   ds:flt_470AFC
112676: fld     st
112677: fmulp   st(1), st
112678: fmul    ds:flt_470B0C
112679: fsubr   ds:flt_470B0C
112680: retn    8
112681: 
112682: loc_44C42C:
112683: fsub    ds:flt_470AFC
112684: fld     st
112685: fmulp   st(1), st
112686: fmul    ds:flt_470B0C
112687: fadd    ds:flt_470B0C
112688: retn    8
112689: 
112690: loc_44C445:             ; jumptable 0044C362 case 10
112691: fadd    st, st
112692: fcom    ds:flt_470AFC
112693: fnstsw  ax
112694: test    ah, 5
112695: jp      short loc_44C463
112696: fld     st
112697: fmul    st, st(1)
112698: fmulp   st(1), st
112699: fmul    ds:flt_470B0C
112700: retn    8
112701: 
112702: loc_44C463:
112703: fsubr   ds:flt_470B08
112704: fld     st
112705: fld     st
112706: fmul    st, st(1)
112707: jmp     short loc_44C4CD
112708: 
112709: loc_44C471:             ; jumptable 0044C362 case 13
112710: fadd    st, st
112711: fcom    ds:flt_470AFC
112712: fnstsw  ax
112713: test    ah, 5
112714: jp      short loc_44C48E
112715: fsubr   ds:flt_470AFC
112716: fld     st
112717: fld     st
112718: fmul    st, st(1)
112719: jmp     short loc_44C4FF
112720: 
112721: loc_44C48E:
112722: fsub    ds:flt_470AFC
112723: fld     st
112724: fld     st
112725: fmul    st, st(1)
112726: jmp     loc_44C522
112727: 
112728: loc_44C49F:             ; jumptable 0044C362 case 11
112729: fadd    st, st
112730: fcom    ds:flt_470AFC
112731: fnstsw  ax
112732: test    ah, 5
112733: jp      short loc_44C4BF
112734: fld     st
112735: fmul    st, st(1)
112736: fmul    st, st(1)
112737: fmulp   st(1), st
112738: fmul    ds:flt_470B0C
112739: retn    8
112740: 
112741: loc_44C4BF:
112742: fsubr   ds:flt_470B08
112743: fld     st
112744: fld     st
112745: fmul    st, st(1)
112746: fmul    st, st(2)
112747: 
112748: loc_44C4CD:
112749: fmulp   st(2), st
112750: fxch    st(1)
112751: fsubr   ds:flt_470B08
112752: fmul    ds:flt_470B0C
112753: fstp    st(1)
112754: retn    8
112755: 
112756: loc_44C4E2:             ; jumptable 0044C362 case 14
112757: fadd    st, st
112758: fcom    ds:flt_470AFC
112759: fnstsw  ax
112760: test    ah, 5
112761: jp      short loc_44C514
112762: fsubr   ds:flt_470AFC
112763: fld     st
112764: fld     st
112765: fmul    st, st(1)
112766: fmul    st, st(2)
112767: 
112768: loc_44C4FF:
112769: fmulp   st(2), st
112770: fxch    st(1)
112771: fmul    ds:flt_470B0C
112772: fsubr   ds:flt_470B0C
112773: fstp    st(1)
112774: retn    8
112775: 
112776: loc_44C514:
112777: fsub    ds:flt_470AFC
112778: fld     st
112779: fld     st
112780: fmul    st, st(1)
112781: fmul    st, st(2)
112782: 
112783: loc_44C522:
112784: fmulp   st(2), st
112785: fxch    st(1)
112786: fmul    ds:flt_470B0C
112787: fadd    ds:flt_470B0C
112788: fstp    st(1)
112789: retn    8
112790: 
112791: loc_44C537:             ; jumptable 0044C362 case 15
112792: fstp    st
112793: fld     ds:flt_470B04
112794: retn    8
112795: 
112796: loc_44C542:             ; jumptable 0044C362 case 16
112797: fstp    st
112798: fld     ds:flt_470AFC
112799: 
112800: def_44C362:             ; jumptable 0044C362 default case, cases 7,8
112801: retn    8
112802: sub_44C350 endp
```

## Referenced retail constants

### [ida/th10.exe.asm:163280–163280](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163280-L163280)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163280: flt_470AFC dd 1.0
```

### [ida/th10.exe.asm:163282–163282](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163282-L163282)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163282: flt_470B04 dd 0.0
```

### [ida/th10.exe.asm:163283–163283](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163283-L163283)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163283: flt_470B08 dd 2.0
```

### [ida/th10.exe.asm:163284–163284](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L163284-L163284)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
163284: flt_470B0C dd 0.5
```

### [decompiled/ghidra_raw/0044C350_FUN_0044c350.c:1–100](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/decompiled/ghidra_raw/0044C350_FUN_0044c350.c#L1-L100)

Whole-file SHA-256: `01c2574bad427fb5e65fc57b67e9e639343355e147e143a18c6b8b3d22095c22`

```text
1: /*
2:  * Raw Ghidra pseudocode reference; not directly compilable.
3:  * Address: 0x0044C350
4:  * Tracking name: FUN_0044c350
5:  * Ghidra name: FUN_0044c350
6:  * Tracked span: 640 bytes
7:  */
8: 
9: 
10: /* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
11: 
12: float10 FUN_0044c350(float param_1,float param_2)
13: 
14: {
15:   undefined4 in_EAX;
16:   float10 fVar1;
17:   float10 fVar2;
18:   
19:   fVar1 = (float10)param_1 / (float10)param_2;
20:   switch(in_EAX) {
21:   case 1:
22:     return fVar1 * fVar1;
23:   case 2:
24:     return fVar1 * fVar1 * fVar1;
25:   case 3:
26:     return fVar1 * fVar1 * fVar1 * fVar1;
27:   case 4:
28:     return (float10)_DAT_00470afc -
29:            ((float10)_DAT_00470afc - fVar1) * ((float10)_DAT_00470afc - fVar1);
30:   case 5:
31:     fVar1 = (float10)_DAT_00470afc - fVar1;
32:     return (float10)_DAT_00470afc - fVar1 * fVar1 * fVar1;
33:   case 6:
34:     fVar1 = (float10)_DAT_00470afc - fVar1;
35:     return (float10)_DAT_00470afc - fVar1 * fVar1 * fVar1 * fVar1;
36:   default:
37:     return fVar1;
38:   case 9:
39:     fVar1 = fVar1 + fVar1;
40:     if ((float10)_DAT_00470afc <= fVar1) {
41:       return ((float10)_DAT_00470b08 -
42:              ((float10)_DAT_00470b08 - fVar1) * ((float10)_DAT_00470b08 - fVar1)) *
43:              (float10)_DAT_00470b0c;
44:     }
45:     return fVar1 * fVar1 * (float10)_DAT_00470b0c;
46:   case 10:
47:     fVar1 = fVar1 + fVar1;
48:     if (fVar1 < (float10)_DAT_00470afc) {
49:       return fVar1 * fVar1 * fVar1 * (float10)_DAT_00470b0c;
50:     }
51:     fVar1 = (float10)_DAT_00470b08 - fVar1;
52:     fVar2 = fVar1 * fVar1;
53:     break;
54:   case 0xb:
55:     fVar1 = fVar1 + fVar1;
56:     if (fVar1 < (float10)_DAT_00470afc) {
57:       return fVar1 * fVar1 * fVar1 * fVar1 * (float10)_DAT_00470b0c;
58:     }
59:     fVar1 = (float10)_DAT_00470b08 - fVar1;
60:     fVar2 = fVar1 * fVar1 * fVar1;
61:     break;
62:   case 0xc:
63:     fVar1 = fVar1 + fVar1;
64:     if ((float10)_DAT_00470afc <= fVar1) {
65:       return (fVar1 - (float10)_DAT_00470afc) * (fVar1 - (float10)_DAT_00470afc) *
66:              (float10)_DAT_00470b0c + (float10)_DAT_00470b0c;
67:     }
68:     return (float10)_DAT_00470b0c -
69:            ((float10)_DAT_00470afc - fVar1) * ((float10)_DAT_00470afc - fVar1) *
70:            (float10)_DAT_00470b0c;
71:   case 0xd:
72:     fVar1 = fVar1 + fVar1;
73:     if ((float10)_DAT_00470afc <= fVar1) {
74:       fVar1 = fVar1 - (float10)_DAT_00470afc;
75:       fVar2 = fVar1 * fVar1;
76: LAB_0044c522:
77:       return fVar2 * fVar1 * (float10)_DAT_00470b0c + (float10)_DAT_00470b0c;
78:     }
79:     fVar1 = (float10)_DAT_00470afc - fVar1;
80:     fVar2 = fVar1 * fVar1;
81:     goto LAB_0044c4ff;
82:   case 0xe:
83:     fVar1 = fVar1 + fVar1;
84:     if ((float10)_DAT_00470afc <= fVar1) {
85:       fVar1 = fVar1 - (float10)_DAT_00470afc;
86:       fVar2 = fVar1 * fVar1 * fVar1;
87:       goto LAB_0044c522;
88:     }
89:     fVar1 = (float10)_DAT_00470afc - fVar1;
90:     fVar2 = fVar1 * fVar1 * fVar1;
91: LAB_0044c4ff:
92:     return (float10)_DAT_00470b0c - fVar2 * fVar1 * (float10)_DAT_00470b0c;
93:   case 0xf:
94:     return (float10)_DAT_00470b04;
95:   case 0x10:
96:     return (float10)_DAT_00470afc;
97:   }
98:   return ((float10)_DAT_00470b08 - fVar2 * fVar1) * (float10)_DAT_00470b0c;
99: }
100: 
```

## Production textual cross-references

All token occurrences in versioned `src/` and `standalone/` C++/headers are listed below, including definitions and comments. These are navigation aids; indirect calls and differently named adapters require further inspection. Tests are deliberately excluded from this production search.

- [matching2/src/game/bullet.cpp:243](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L243): `Trajectory_EaseFraction};`
- [matching2/src/game/trajectory_evaluate.cpp:98](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/trajectory_evaluate.cpp#L98): `float Trajectory_EaseFraction(float elapsed, float duration, int mode) {`
- [matching2/src/math/easing.cpp:6](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/math/easing.cpp#L6): `float Easing_Evaluate(int mode, float numerator, float denominator) {`
- [matching2/src/math/param_block_interp.cpp:135](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/math/param_block_interp.cpp#L135): `const float eased = Easing_Evaluate(mode, state->elapsed,`

### [matching2/src/game/bullet.cpp:235–255](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/game/bullet.cpp#L235-L255)

Whole-file SHA-256: `5c71109c0826ce8d6b334a610eb680b71a243bb83f4258518a95751db75c170a`

```text
235: 
236:     std::memcpy(state, state + 0x2c, 0x2c);
237: 
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
```

### [matching2/src/math/param_block_interp.cpp:127–147](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/math/param_block_interp.cpp#L127-L147)

Whole-file SHA-256: `ea2c32ad2874471f7355b05cfc57bd1166b1d993edcf7ddf0b170709491bf40b`

```text
127:         QuantizedVector partial_with_start;
128:         Vec_Add(&partial_with_start, &scaled_start, &partial);
129:         Vec_Add(&scratch, &scaled_end, &partial_with_start);
130:         source = &scratch;
131:     } else {
132:         // Eased blend: A + (B - A) * ease(mode, elapsed / duration). Retail
133:         // subtracts the EAX operand from the ECX operand, so the delta really
134:         // is target minus value.
135:         const float eased = Easing_Evaluate(mode, state->elapsed,
136:                                             (float)state->duration);
137:         QuantizedVector delta;
138:         Vec_Subtract(&delta, &state->blocks[1], &state->blocks[0]);
139:         QuantizedVector weighted;
140:         Vec_Scale(&weighted, &delta, eased);
141:         Vec_Add(&scratch, &state->blocks[0], &weighted);
142:         source = &scratch;
143:     }
144: 
145:     *result = *source;
146:     return result;
147: }
```
