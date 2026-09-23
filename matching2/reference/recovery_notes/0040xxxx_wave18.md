# 0x0040xxxx vein sweep (wave 18) - 88 of 179 unassigned regions landed EXACT

2026-09-19, agent `VeinBlock40`. Block: `0x00401490..0x0040E760`, every manifest
region whose `kind` is `asm`, whose `owner` is null, and whose size is 64 bytes or
less: 179 regions, 3,041 bytes. Work was done in `/tmp/VeinBlock40/msvc`
(`cp -a matching2/msvc`) and promoted with `promote_scratch.py --apply`.

**88 landed EXACT (826 bytes), 91 dropped (2,215 bytes).** Every landing below was re-probed
against the maintained tree after promotion and reports `EXACT`.

Landed by class:

| class | count | how |
| --- | ---: | --- |
| empty function (`ret`, 1 byte) | 16 | plain `extern "C" void f() {}` |
| return 0 (`xor eax,eax; ret`) | 5 | plain `extern "C" int f() { return 0; }` |
| EAX-receiver flag word ops (`and/or [eax+off],imm`) | 10 | cluster |
| EAX-receiver bit reads (`mov eax,[eax+off]; shr/and`) | 10 | cluster |
| EAX-receiver float field reads | 5 | cluster |
| EAX-receiver `add eax,imm` field-address accessors | 7 | cluster |
| EAX-receiver field zeroing/arming | 9 | cluster |
| EAX-receiver `movzx ...; and eax,ecx` masked loads | 3 | cluster |
| `__thiscall` predicates (ECX receiver, SETcc) | 6 | plain |
| `__thiscall` timer/rng forwarders | 3 | plain |
| vector copy / elementwise float ops / dist-squared | 10 | cluster |
| EAX-receiver timer decrement (`0x4052B0`) | 1 | cluster |
| object-returning flag clear | 1 | plain |
| modulo / accumulate (EAX receiver + stack or ECX arg) | 2 | cluster |

## The levers that mattered

1. **The EAX-receiver accessor cluster generalises well beyond plain loads and
   stores.** The `cluster_accessors.py` shape test only covers `mov eax,[eax+off]`
   and `mov [eax+off],reg`; once the driver is the same pointer-array walk, the pass
   also earns EAX for `and/or/test` on a field, for `(field >> k) & 1`, for a
   `float` load (`?LoadValue@@QBEMXZ`), for `(int)this + N`, and for a pointer-
   argument pair (receiver EAX, argument ECX: `LoadMasked`, `DistSq`, `Apply`).
   57 of the 88 landings use this one pointer-array-walk driver with a hand-written
   body (loads, stores, bit fields, masked loads, offsets, float reads, vector ops).
2. **`add eax,imm` (not `lea`) is what `return (int)this + N;` compiles to.** The
   seven `05/83 c0 xx` accessors only reproduce when the source adds the offset to
   the *integer* value of `this`; a cast to `char*` produces the 6-byte `lea` form
   and misses the 4/6-byte region.
3. **A struct-return C++ function is the natural model for the vector copies.**
   `Vec3* dst = (Vec3*)((int)this + 0x24); *dst = *src;` emits retail's
   `mov edx,[eax]/add ecx,24h/...` exactly, including the integer `add` for the
   field offset and the reuse of EAX as the last copy scratch.
4. **Float field loads need `__fltused` bound as `metadata` and a driver that never
   converts float to int** (the float->int conversion pulls in `__ftol2`, which the
   cluster link cannot resolve); comparing the accumulated total against `0.0f`
   and returning that as `int` avoids the helper.
5. **The context size must be read from the newest `cluster.map`, not the first.**
   Re-registering a layout leaves one map per attempt and the directory names are
   random, so an alphabetical pick reads a stale size and the next probe fails
   again with `function is not its entire declared compiler contribution`.
6. **Two spellings of a subtraction that differ only in the order of the operands
   hash differently in x87.** `0x405B40`/`0x408620` landed only with
   `float dy = y - other->y; float dx = x - other->x; return dx*dx + dy*dy;` - the
   y difference first, and *this* minus the argument. The mathematically identical
   `other->y - y` spelling is 9 bytes away at +1.

## Landings

| address | size | kind | symbol | sha256(retail)[:16] |
| --- | ---: | --- | --- | --- |
| `0x00401CA0` | 4 | cluster | `?LoadValue@ObjectAccessor_00401ca0@@QBEMXZ` | `30052cc13c30f9e6` |
| `0x00401D90` | 15 | cluster | `?Clear@ObjectAccessor_00401d90@@QAEXXZ` | `bea97a9038256db9` |
| `0x00401DA0` | 1 | plain | `_Empty_00401da0` | `ae3f4619b0413d70` |
| `0x00401DB0` | 1 | plain | `_Empty_00401db0` | `ae3f4619b0413d70` |
| `0x00401F40` | 15 | cluster | `?Arm@ObjectAccessor_00401f40@@QAEXXZ` | `2a256666f1d0c606` |
| `0x00401F90` | 11 | cluster | `?Set@ObjectAccessor_00401f90@@QAEXH@Z` | `b4463d448e399e80` |
| `0x00401FC0` | 1 | plain | `_Empty_00401fc0` | `ae3f4619b0413d70` |
| `0x004020F0` | 5 | cluster | `?ClearValue@ObjectAccessor_004020f0@@QAEXXZ` | `a19bc34830aae236` |
| `0x00402100` | 5 | cluster | `?ClearValue@ObjectAccessor_00402100@@QAEXXZ` | `e7313be86be5d373` |
| `0x00402110` | 5 | cluster | `?ClearValue@ObjectAccessor_00402110@@QAEXXZ` | `a19bc34830aae236` |
| `0x00402120` | 1 | plain | `_Empty_00402120` | `ae3f4619b0413d70` |
| `0x00402130` | 5 | cluster | `?ClearValue@ObjectAccessor_00402130@@QAEXXZ` | `333fcee6c27fb849` |
| `0x00402140` | 1 | plain | `_Empty_00402140` | `ae3f4619b0413d70` |
| `0x00402150` | 1 | plain | `_Empty_00402150` | `ae3f4619b0413d70` |
| `0x00402220` | 8 | cluster | `?ClearValue@ObjectAccessor_00402220@@QAEXXZ` | `3b2ad0bf56a92410` |
| `0x00404EC0` | 4 | cluster | `?LoadValue@ObjectAccessor_00404ec0@@QBEMXZ` | `090fded3ad477715` |
| `0x00404F20` | 8 | cluster | `?ClearValue@ObjectAccessor_00404f20@@QAEXXZ` | `7e9231a0ff7e3fa2` |
| `0x00405000` | 20 | cluster | `?CopyFrom@ObjectAccessor_00405000@@QAEXPBUVec3_00405000@@@Z` | `53d2157f756c9d5b` |
| `0x00405020` | 20 | cluster | `?CopyFrom@ObjectAccessor_00405020@@QAEXPBUVec3_00405020@@@Z` | `df7d1227bcfe88c3` |
| `0x00405110` | 20 | cluster | `?CopyFrom@ObjectAccessor_00405110@@QAEXPBUVec3_00405110@@@Z` | `feb8eabd5bb95c69` |
| `0x004051C0` | 14 | plain | `?IsNonZero@Predicate_004051c0@@QBEHXZ` | `737d2b579f71ed29` |
| `0x004052A0` | 11 | plain | `?Rewind@TimerResetter_004052a0@@QAEXXZ` | `c0e273d918494bf7` |
| `0x004052B0` | 20 | cluster | `?Decrement@TimerDecrementer_004052b0@@QAEXH@Z` | `431027a3afabdd97` |
| `0x004052D0` | 16 | plain | `?AdvanceCount@TimerAdvancer_004052d0@@QAEXH@Z` | `4d43ce53e6d2ac05` |
| `0x00405380` | 3 | cluster | `?LoadValue@ObjectAccessor_00405380@@QBEMXZ` | `e93d8c74f22c14e4` |
| `0x004053A0` | 7 | cluster | `?LoadValue@ObjectAccessor_004053a0@@QBEHXZ` | `999bd8aeef60ead5` |
| `0x004053E0` | 1 | plain | `_Empty_004053e0` | `ae3f4619b0413d70` |
| `0x004053F0` | 1 | plain | `_Empty_004053f0` | `ae3f4619b0413d70` |
| `0x00405490` | 4 | cluster | `?LoadValue@ObjectAccessor_00405490@@QBEMXZ` | `090fded3ad477715` |
| `0x004054A0` | 6 | cluster | `?Offset@ObjectAccessor_004054a0@@QBEHXZ` | `12c2fb32efbb33b4` |
| `0x00405560` | 10 | cluster | `?LoadValue@ObjectAccessor_00405560@@QBEHXZ` | `1b7fe96bf7793d3e` |
| `0x00405570` | 15 | plain | `?IsAtLeast60@Predicate_00405570@@QBEHXZ` | `083a0b6ff065cf96` |
| `0x00405B40` | 25 | cluster | `?DistSq@ObjectAccessor_00405b40@@QBEMPBUVec3_00405b40@@@Z` | `6a660cfeb4306c21` |
| `0x00405BA0` | 4 | cluster | `?LoadValue@ObjectAccessor_00405ba0@@QBEMXZ` | `59542bc06d5e5d8d` |
| `0x00405BC0` | 1 | plain | `_Empty_00405bc0` | `ae3f4619b0413d70` |
| `0x00405E10` | 7 | plain | `?Clear@ObjectClearer_00405e10@@QAEPAU1@XZ` | `0a61dd7ca8066513` |
| `0x00408620` | 25 | cluster | `?DistSq@ObjectAccessor_00408620@@QBEMPBUVec3_00408620@@@Z` | `6a660cfeb4306c21` |
| `0x00408640` | 20 | cluster | `?LengthSq@ObjectAccessor_00408640@@QBEMXZ` | `a9887a7d7bc2ef7f` |
| `0x00408730` | 25 | cluster | `?Apply@ObjectAccessor_00408730@@QAEXPBUVec3_00408730@@@Z` | `06822bceb7431150` |
| `0x00408770` | 12 | plain | `?Scale@RngScaler_00408770@@QBEMM@Z` | `94d421bda5bb6e0a` |
| `0x00408780` | 10 | cluster | `?LoadValue@ObjectAccessor_00408780@@QBEHXZ` | `1977b1a4d71cfb5c` |
| `0x00408790` | 14 | cluster | `?LoadValue@ObjectAccessor_00408790@@QBEHXZ` | `5244bf6970e7ffa2` |
| `0x004087C0` | 9 | cluster | `?LoadValue@ObjectAccessor_004087c0@@QBEHXZ` | `219cae37389bfc10` |
| `0x004087E0` | 25 | cluster | `?Apply@ObjectAccessor_004087e0@@QAEXPBUVec3_004087e0@@@Z` | `7a2814dd22ec52ce` |
| `0x00408800` | 1 | plain | `_Empty_00408800` | `ae3f4619b0413d70` |
| `0x00408810` | 1 | plain | `_Empty_00408810` | `ae3f4619b0413d70` |
| `0x00408820` | 6 | cluster | `?Offset@ObjectAccessor_00408820@@QBEHXZ` | `16884b4dd4f81964` |
| `0x00408840` | 8 | cluster | `?ClearValue@ObjectAccessor_00408840@@QAEXXZ` | `2d38e45272232bf5` |
| `0x00408850` | 8 | cluster | `?SetValue@ObjectAccessor_00408850@@QAEXXZ` | `48477415d111a03b` |
| `0x00408AA0` | 3 | plain | `_Zero_00408aa0` | `4bc724f3b1d0caf4` |
| `0x00408AB0` | 3 | plain | `_Zero_00408ab0` | `4bc724f3b1d0caf4` |
| `0x00408AC0` | 35 | cluster | `?Set@ObjectAccessor_00408ac0@@QAEXXZ` | `2078af663bfe2ba1` |
| `0x00409E00` | 12 | plain | `?IsOne@Predicate_00409e00@@QBEHXZ` | `468dc3fb76157bbc` |
| `0x00409E40` | 1 | plain | `_Empty_00409e40` | `ae3f4619b0413d70` |
| `0x00409EA0` | 1 | plain | `_Empty_00409ea0` | `ae3f4619b0413d70` |
| `0x0040ACC0` | 7 | cluster | `?LoadMasked@ObjectAccessor_0040acc0@@QBEHH@Z` | `54bc2be93679c475` |
| `0x0040ACD0` | 7 | cluster | `?LoadMasked@ObjectAccessor_0040acd0@@QBEHH@Z` | `ca4fc3c0f902836b` |
| `0x0040ADC0` | 1 | plain | `_Empty_0040adc0` | `ae3f4619b0413d70` |
| `0x0040AE00` | 28 | cluster | `?Clear@ObjectAccessor_0040ae00@@QAEXXZ` | `2c77fddc630d3976` |
| `0x0040B290` | 1 | plain | `_Empty_0040b290` | `ae3f4619b0413d70` |
| `0x0040B310` | 3 | plain | `_Zero_0040b310` | `4bc724f3b1d0caf4` |
| `0x0040B370` | 23 | cluster | `?CopyFrom@ObjectAccessor_0040b370@@QAEXPBUVec3_0040b370@@@Z` | `ac5787cc0475efe4` |
| `0x0040B390` | 1 | plain | `_Empty_0040b390` | `ae3f4619b0413d70` |
| `0x0040B460` | 9 | cluster | `?LoadValue@ObjectAccessor_0040b460@@QBEHXZ` | `654145fe349c71c7` |
| `0x0040B470` | 10 | cluster | `?LoadValue@ObjectAccessor_0040b470@@QBEHXZ` | `e412b60129e5a1a5` |
| `0x0040B500` | 7 | cluster | `?LoadValue@ObjectAccessor_0040b500@@QBEHXZ` | `6ae7e860f7a1dbfd` |
| `0x0040B510` | 9 | cluster | `?LoadValue@ObjectAccessor_0040b510@@QBEHXZ` | `16745b3fd6404563` |
| `0x0040B520` | 6 | cluster | `?Offset@ObjectAccessor_0040b520@@QBEHXZ` | `bdc787523c0711b7` |
| `0x0040C470` | 13 | cluster | `?Remainder@ObjectAccessor_0040c470@@QBEHH@Z` | `ea8833003f0c8a20` |
| `0x0040C530` | 6 | cluster | `?LoadMasked@ObjectAccessor_0040c530@@QBEHH@Z` | `6cf3abd285f4af35` |
| `0x0040C5D0` | 15 | cluster | `?Clear@ObjectAccessor_0040c5d0@@QAEXXZ` | `ab2b2a56c8311ea9` |
| `0x0040C710` | 21 | cluster | `?Init@ObjectAccessor_0040c710@@QAEXXZ` | `6771f082b11284c8` |
| `0x0040C800` | 15 | cluster | `?Clear@ObjectAccessor_0040c800@@QAEXXZ` | `09141160d3b42b75` |
| `0x0040C920` | 9 | cluster | `?Accumulate@ObjectAccessor_0040c920@@QAEHH@Z` | `04e88280b130756b` |
| `0x0040C930` | 10 | plain | `?IsPositive@Predicate_0040c930@@QBEHXZ` | `c69d6fdc2f320bd3` |
| `0x0040C940` | 11 | cluster | `?Clear@ObjectAccessor_0040c940@@QAEXXZ` | `30673e2c41208a39` |
| `0x0040CC10` | 4 | cluster | `?Offset@ObjectAccessor_0040cc10@@QAEHXZ` | `138137bccb08af4a` |
| `0x0040CC20` | 6 | cluster | `?Offset@ObjectAccessor_0040cc20@@QBEHXZ` | `90e14d5fd96ef825` |
| `0x0040CC30` | 6 | cluster | `?Offset@ObjectAccessor_0040cc30@@QBEHXZ` | `e56bd7f0bf44efb6` |
| `0x0040CD10` | 5 | cluster | `?ClearValue@ObjectAccessor_0040cd10@@QAEXXZ` | `e7313be86be5d373` |
| `0x0040CE30` | 14 | plain | `?IsNonZero@Predicate_0040ce30@@QBEHXZ` | `7230c2635f9d8990` |
| `0x0040CE70` | 6 | cluster | `?Offset@ObjectAccessor_0040ce70@@QBEHXZ` | `368f2eba7ac32e4a` |
| `0x0040CE80` | 11 | plain | `?IsNonZero@Predicate_0040ce80@@QBEHXZ` | `b131d79d081215e3` |
| `0x0040CE90` | 8 | cluster | `?SetValue@ObjectAccessor_0040ce90@@QAEXXZ` | `cf0ea9426115d1ed` |
| `0x0040CED0` | 13 | cluster | `?LoadValue@ObjectAccessor_0040ced0@@QBEHXZ` | `52a77fa17bd67e97` |
| `0x0040CEE0` | 20 | cluster | `?CopyFrom@ObjectAccessor_0040cee0@@QAEXPBUVec3_0040cee0@@@Z` | `53d2157f756c9d5b` |
| `0x0040D4F0` | 3 | plain | `_Zero_0040d4f0` | `4bc724f3b1d0caf4` |
| `0x0040D500` | 3 | plain | `_Zero_0040d500` | `4bc724f3b1d0caf4` |

### Probe lines

```text
0x00401ca0       4 bytes  ?LoadValue@ObjectAccessor_00401ca0@@QBEMXZ  EXACT   src/unidentified/unassigned_00401ca0.cpp
0x00401d90      15 bytes  ?Clear@ObjectAccessor_00401d90@@QAEXXZ  EXACT   src/unidentified/unassigned_00401d90.cpp
0x00401da0       1 bytes  _Empty_00401da0  EXACT   src/unidentified/unassigned_00401da0.cpp
0x00401db0       1 bytes  _Empty_00401db0  EXACT   src/unidentified/unassigned_00401db0.cpp
0x00401f40      15 bytes  ?Arm@ObjectAccessor_00401f40@@QAEXXZ  EXACT   src/unidentified/unassigned_00401f40.cpp
0x00401f90      11 bytes  ?Set@ObjectAccessor_00401f90@@QAEXH@Z  EXACT   src/unidentified/unassigned_00401f90.cpp
0x00401fc0       1 bytes  _Empty_00401fc0  EXACT   src/unidentified/unassigned_00401fc0.cpp
0x004020f0       5 bytes  ?ClearValue@ObjectAccessor_004020f0@@QAEXXZ  EXACT   src/unidentified/unassigned_004020f0.cpp
0x00402100       5 bytes  ?ClearValue@ObjectAccessor_00402100@@QAEXXZ  EXACT   src/unidentified/unassigned_00402100.cpp
0x00402110       5 bytes  ?ClearValue@ObjectAccessor_00402110@@QAEXXZ  EXACT   src/unidentified/unassigned_00402110.cpp
0x00402120       1 bytes  _Empty_00402120  EXACT   src/unidentified/unassigned_00402120.cpp
0x00402130       5 bytes  ?ClearValue@ObjectAccessor_00402130@@QAEXXZ  EXACT   src/unidentified/unassigned_00402130.cpp
0x00402140       1 bytes  _Empty_00402140  EXACT   src/unidentified/unassigned_00402140.cpp
0x00402150       1 bytes  _Empty_00402150  EXACT   src/unidentified/unassigned_00402150.cpp
0x00402220       8 bytes  ?ClearValue@ObjectAccessor_00402220@@QAEXXZ  EXACT   src/unidentified/unassigned_00402220.cpp
0x00404ec0       4 bytes  ?LoadValue@ObjectAccessor_00404ec0@@QBEMXZ  EXACT   src/unidentified/unassigned_00404ec0.cpp
0x00404f20       8 bytes  ?ClearValue@ObjectAccessor_00404f20@@QAEXXZ  EXACT   src/unidentified/unassigned_00404f20.cpp
0x00405000      20 bytes  ?CopyFrom@ObjectAccessor_00405000@@QAEXPBUVec3_00405000@@@Z  EXACT   src/unidentified/unassigned_00405000.cpp
0x00405020      20 bytes  ?CopyFrom@ObjectAccessor_00405020@@QAEXPBUVec3_00405020@@@Z  EXACT   src/unidentified/unassigned_00405020.cpp
0x00405110      20 bytes  ?CopyFrom@ObjectAccessor_00405110@@QAEXPBUVec3_00405110@@@Z  EXACT   src/unidentified/unassigned_00405110.cpp
0x004051c0      14 bytes  ?IsNonZero@Predicate_004051c0@@QBEHXZ  EXACT   src/unidentified/unassigned_004051c0.cpp
0x004052a0      11 bytes  ?Rewind@TimerResetter_004052a0@@QAEXXZ  EXACT   src/unidentified/unassigned_004052a0.cpp
0x004052b0      20 bytes  ?Decrement@TimerDecrementer_004052b0@@QAEXH@Z  EXACT   src/unidentified/unassigned_004052b0.cpp
0x004052d0      16 bytes  ?AdvanceCount@TimerAdvancer_004052d0@@QAEXH@Z  EXACT   src/unidentified/unassigned_004052d0.cpp
0x00405380       3 bytes  ?LoadValue@ObjectAccessor_00405380@@QBEMXZ  EXACT   src/unidentified/unassigned_00405380.cpp
0x004053a0       7 bytes  ?LoadValue@ObjectAccessor_004053a0@@QBEHXZ  EXACT   src/unidentified/unassigned_004053a0.cpp
0x004053e0       1 bytes  _Empty_004053e0  EXACT   src/unidentified/unassigned_004053e0.cpp
0x004053f0       1 bytes  _Empty_004053f0  EXACT   src/unidentified/unassigned_004053f0.cpp
0x00405490       4 bytes  ?LoadValue@ObjectAccessor_00405490@@QBEMXZ  EXACT   src/unidentified/unassigned_00405490.cpp
0x004054a0       6 bytes  ?Offset@ObjectAccessor_004054a0@@QBEHXZ  EXACT   src/unidentified/unassigned_004054a0.cpp
0x00405560      10 bytes  ?LoadValue@ObjectAccessor_00405560@@QBEHXZ  EXACT   src/unidentified/unassigned_00405560.cpp
0x00405570      15 bytes  ?IsAtLeast60@Predicate_00405570@@QBEHXZ  EXACT   src/unidentified/unassigned_00405570.cpp
0x00405b40      25 bytes  ?DistSq@ObjectAccessor_00405b40@@QBEMPBUVec3_00405b40@@@Z  EXACT   src/unidentified/unassigned_00405b40.cpp
0x00405ba0       4 bytes  ?LoadValue@ObjectAccessor_00405ba0@@QBEMXZ  EXACT   src/unidentified/unassigned_00405ba0.cpp
0x00405bc0       1 bytes  _Empty_00405bc0  EXACT   src/unidentified/unassigned_00405bc0.cpp
0x00405e10       7 bytes  ?Clear@ObjectClearer_00405e10@@QAEPAU1@XZ  EXACT   src/unidentified/unassigned_00405e10.cpp
0x00408620      25 bytes  ?DistSq@ObjectAccessor_00408620@@QBEMPBUVec3_00408620@@@Z  EXACT   src/unidentified/unassigned_00408620.cpp
0x00408640      20 bytes  ?LengthSq@ObjectAccessor_00408640@@QBEMXZ  EXACT   src/unidentified/unassigned_00408640.cpp
0x00408730      25 bytes  ?Apply@ObjectAccessor_00408730@@QAEXPBUVec3_00408730@@@Z  EXACT   src/unidentified/unassigned_00408730.cpp
0x00408770      12 bytes  ?Scale@RngScaler_00408770@@QBEMM@Z  EXACT   src/unidentified/unassigned_00408770.cpp
0x00408780      10 bytes  ?LoadValue@ObjectAccessor_00408780@@QBEHXZ  EXACT   src/unidentified/unassigned_00408780.cpp
0x00408790      14 bytes  ?LoadValue@ObjectAccessor_00408790@@QBEHXZ  EXACT   src/unidentified/unassigned_00408790.cpp
0x004087c0       9 bytes  ?LoadValue@ObjectAccessor_004087c0@@QBEHXZ  EXACT   src/unidentified/unassigned_004087c0.cpp
0x004087e0      25 bytes  ?Apply@ObjectAccessor_004087e0@@QAEXPBUVec3_004087e0@@@Z  EXACT   src/unidentified/unassigned_004087e0.cpp
0x00408800       1 bytes  _Empty_00408800  EXACT   src/unidentified/unassigned_00408800.cpp
0x00408810       1 bytes  _Empty_00408810  EXACT   src/unidentified/unassigned_00408810.cpp
0x00408820       6 bytes  ?Offset@ObjectAccessor_00408820@@QBEHXZ  EXACT   src/unidentified/unassigned_00408820.cpp
0x00408840       8 bytes  ?ClearValue@ObjectAccessor_00408840@@QAEXXZ  EXACT   src/unidentified/unassigned_00408840.cpp
0x00408850       8 bytes  ?SetValue@ObjectAccessor_00408850@@QAEXXZ  EXACT   src/unidentified/unassigned_00408850.cpp
0x00408aa0       3 bytes  _Zero_00408aa0  EXACT   src/unidentified/unassigned_00408aa0.cpp
0x00408ab0       3 bytes  _Zero_00408ab0  EXACT   src/unidentified/unassigned_00408ab0.cpp
0x00408ac0      35 bytes  ?Set@ObjectAccessor_00408ac0@@QAEXXZ  EXACT   src/unidentified/unassigned_00408ac0.cpp
0x00409e00      12 bytes  ?IsOne@Predicate_00409e00@@QBEHXZ  EXACT   src/unidentified/unassigned_00409e00.cpp
0x00409e40       1 bytes  _Empty_00409e40  EXACT   src/unidentified/unassigned_00409e40.cpp
0x00409ea0       1 bytes  _Empty_00409ea0  EXACT   src/unidentified/unassigned_00409ea0.cpp
0x0040acc0       7 bytes  ?LoadMasked@ObjectAccessor_0040acc0@@QBEHH@Z  EXACT   src/unidentified/unassigned_0040acc0.cpp
0x0040acd0       7 bytes  ?LoadMasked@ObjectAccessor_0040acd0@@QBEHH@Z  EXACT   src/unidentified/unassigned_0040acd0.cpp
0x0040adc0       1 bytes  _Empty_0040adc0  EXACT   src/unidentified/unassigned_0040adc0.cpp
0x0040ae00      28 bytes  ?Clear@ObjectAccessor_0040ae00@@QAEXXZ  EXACT   src/unidentified/unassigned_0040ae00.cpp
0x0040b290       1 bytes  _Empty_0040b290  EXACT   src/unidentified/unassigned_0040b290.cpp
0x0040b310       3 bytes  _Zero_0040b310  EXACT   src/unidentified/unassigned_0040b310.cpp
0x0040b370      23 bytes  ?CopyFrom@ObjectAccessor_0040b370@@QAEXPBUVec3_0040b370@@@Z  EXACT   src/unidentified/unassigned_0040b370.cpp
0x0040b390       1 bytes  _Empty_0040b390  EXACT   src/unidentified/unassigned_0040b390.cpp
0x0040b460       9 bytes  ?LoadValue@ObjectAccessor_0040b460@@QBEHXZ  EXACT   src/unidentified/unassigned_0040b460.cpp
0x0040b470      10 bytes  ?LoadValue@ObjectAccessor_0040b470@@QBEHXZ  EXACT   src/unidentified/unassigned_0040b470.cpp
0x0040b500       7 bytes  ?LoadValue@ObjectAccessor_0040b500@@QBEHXZ  EXACT   src/unidentified/unassigned_0040b500.cpp
0x0040b510       9 bytes  ?LoadValue@ObjectAccessor_0040b510@@QBEHXZ  EXACT   src/unidentified/unassigned_0040b510.cpp
0x0040b520       6 bytes  ?Offset@ObjectAccessor_0040b520@@QBEHXZ  EXACT   src/unidentified/unassigned_0040b520.cpp
0x0040c470      13 bytes  ?Remainder@ObjectAccessor_0040c470@@QBEHH@Z  EXACT   src/unidentified/unassigned_0040c470.cpp
0x0040c530       6 bytes  ?LoadMasked@ObjectAccessor_0040c530@@QBEHH@Z  EXACT   src/unidentified/unassigned_0040c530.cpp
0x0040c5d0      15 bytes  ?Clear@ObjectAccessor_0040c5d0@@QAEXXZ  EXACT   src/unidentified/unassigned_0040c5d0.cpp
0x0040c710      21 bytes  ?Init@ObjectAccessor_0040c710@@QAEXXZ  EXACT   src/unidentified/unassigned_0040c710.cpp
0x0040c800      15 bytes  ?Clear@ObjectAccessor_0040c800@@QAEXXZ  EXACT   src/unidentified/unassigned_0040c800.cpp
0x0040c920       9 bytes  ?Accumulate@ObjectAccessor_0040c920@@QAEHH@Z  EXACT   src/unidentified/unassigned_0040c920.cpp
0x0040c930      10 bytes  ?IsPositive@Predicate_0040c930@@QBEHXZ  EXACT   src/unidentified/unassigned_0040c930.cpp
0x0040c940      11 bytes  ?Clear@ObjectAccessor_0040c940@@QAEXXZ  EXACT   src/unidentified/unassigned_0040c940.cpp
0x0040cc10       4 bytes  ?Offset@ObjectAccessor_0040cc10@@QAEHXZ  EXACT   src/unidentified/unassigned_0040cc10.cpp
0x0040cc20       6 bytes  ?Offset@ObjectAccessor_0040cc20@@QBEHXZ  EXACT   src/unidentified/unassigned_0040cc20.cpp
0x0040cc30       6 bytes  ?Offset@ObjectAccessor_0040cc30@@QBEHXZ  EXACT   src/unidentified/unassigned_0040cc30.cpp
0x0040cd10       5 bytes  ?ClearValue@ObjectAccessor_0040cd10@@QAEXXZ  EXACT   src/unidentified/unassigned_0040cd10.cpp
0x0040ce30      14 bytes  ?IsNonZero@Predicate_0040ce30@@QBEHXZ  EXACT   src/unidentified/unassigned_0040ce30.cpp
0x0040ce70       6 bytes  ?Offset@ObjectAccessor_0040ce70@@QBEHXZ  EXACT   src/unidentified/unassigned_0040ce70.cpp
0x0040ce80      11 bytes  ?IsNonZero@Predicate_0040ce80@@QBEHXZ  EXACT   src/unidentified/unassigned_0040ce80.cpp
0x0040ce90       8 bytes  ?SetValue@ObjectAccessor_0040ce90@@QAEXXZ  EXACT   src/unidentified/unassigned_0040ce90.cpp
0x0040ced0      13 bytes  ?LoadValue@ObjectAccessor_0040ced0@@QBEHXZ  EXACT   src/unidentified/unassigned_0040ced0.cpp
0x0040cee0      20 bytes  ?CopyFrom@ObjectAccessor_0040cee0@@QAEXPBUVec3_0040cee0@@@Z  EXACT   src/unidentified/unassigned_0040cee0.cpp
0x0040d4f0       3 bytes  _Zero_0040d4f0  EXACT   src/unidentified/unassigned_0040d4f0.cpp
0x0040d500       3 bytes  _Zero_0040d500  EXACT   src/unidentified/unassigned_0040d500.cpp
```

### Source text

#### `0x00401CA0` (4 bytes, cluster) - `src/unidentified/unassigned_00401ca0.cpp`

layout `layout/ltcg/acc_00401ca0.json`

```cpp
// 0x00401CA0: load the +0x3C float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401ca0 {
    unsigned char pad_000[0x3C];
    float field_3c;                          // +0x3C
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00401ca0::LoadValue() const {
    return field_3c;
}
#pragma code_seg()
```

#### `0x00401D90` (15 bytes, cluster) - `src/unidentified/unassigned_00401d90.cpp`

layout `layout/ltcg/acc_00401d90.json`

```cpp
// 0x00401D90: zero the +0x896C/+0x8970 pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401d90 {
    unsigned char pad_000[0x896C];
    int field_896c;
    int field_8970;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00401d90::Clear() {
    field_896c = 0;
    field_8970 = 0;
}
#pragma code_seg()
```

#### `0x00401DA0` (1 bytes, plain) - `src/unidentified/unassigned_00401da0.cpp`

```cpp
// 0x00401DA0: an empty function; retail's body is a bare return.
extern "C" void Empty_00401da0() {
}
```

#### `0x00401DB0` (1 bytes, plain) - `src/unidentified/unassigned_00401db0.cpp`

```cpp
// 0x00401DB0: an empty function; retail's body is a bare return.
extern "C" void Empty_00401db0() {
}
```

#### `0x00401F40` (15 bytes, cluster) - `src/unidentified/unassigned_00401f40.cpp`

layout `layout/ltcg/acc_00401f40.json`

```cpp
// 0x00401F40: arm the +0x0/+0x4/+0x8 timer fields (previous sentinel, cleared others)
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401f40 {
    int field_0;
    int field_4;
    int field_8;
    __declspec(noinline) void Arm();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00401f40::Arm() {
    field_4 = 0;
    field_0 = 0xFFF0BDC1;
    field_8 = 0;
}
#pragma code_seg()
```

#### `0x00401F90` (11 bytes, cluster) - `src/unidentified/unassigned_00401f90.cpp`

layout `layout/ltcg/acc_00401f90.json`

```cpp
// 0x00401F90: store the argument in +0x0 and clear +0x4/+0x8
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00401f90 {
    int field_0;
    int field_4;
    int field_8;
    __declspec(noinline) void Set(int value);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00401f90::Set(int value) {
    field_0 = value;
    field_4 = 0;
    field_8 = 0;
}
#pragma code_seg()
```

#### `0x00401FC0` (1 bytes, plain) - `src/unidentified/unassigned_00401fc0.cpp`

```cpp
// 0x00401FC0: an empty function; retail's body is a bare return.
extern "C" void Empty_00401fc0() {
}
```

#### `0x004020F0` (5 bytes, cluster) - `src/unidentified/unassigned_004020f0.cpp`

layout `layout/ltcg/acc_004020f0.json`

```cpp
// 0x004020F0: clear bit 0 of +0x40.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_004020f0 {
    unsigned char pad_000[0x40];
    unsigned int field_040;                 // +0x40
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004020f0::ClearValue() {
    field_040 &= ~1u;
}
#pragma code_seg()
```

#### `0x00402100` (5 bytes, cluster) - `src/unidentified/unassigned_00402100.cpp`

layout `layout/ltcg/acc_00402100.json`

```cpp
// 0x00402100: clear bit 0 of +0x30.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402100 {
    unsigned char pad_000[0x30];
    unsigned int field_030;                 // +0x30
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402100::ClearValue() {
    field_030 &= ~1u;
}
#pragma code_seg()
```

#### `0x00402110` (5 bytes, cluster) - `src/unidentified/unassigned_00402110.cpp`

layout `layout/ltcg/acc_00402110.json`

```cpp
// 0x00402110: clear bit 0 of +0x40.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402110 {
    unsigned char pad_000[0x40];
    unsigned int field_040;                 // +0x40
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402110::ClearValue() {
    field_040 &= ~1u;
}
#pragma code_seg()
```

#### `0x00402120` (1 bytes, plain) - `src/unidentified/unassigned_00402120.cpp`

```cpp
// 0x00402120: an empty function; retail's body is a bare return.
extern "C" void Empty_00402120() {
}
```

#### `0x00402130` (5 bytes, cluster) - `src/unidentified/unassigned_00402130.cpp`

layout `layout/ltcg/acc_00402130.json`

```cpp
// 0x00402130: clear bit 0 of +0x20.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402130 {
    unsigned char pad_000[0x20];
    unsigned int field_020;                 // +0x20
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402130::ClearValue() {
    field_020 &= ~1u;
}
#pragma code_seg()
```

#### `0x00402140` (1 bytes, plain) - `src/unidentified/unassigned_00402140.cpp`

```cpp
// 0x00402140: an empty function; retail's body is a bare return.
extern "C" void Empty_00402140() {
}
```

#### `0x00402150` (1 bytes, plain) - `src/unidentified/unassigned_00402150.cpp`

```cpp
// 0x00402150: an empty function; retail's body is a bare return.
extern "C" void Empty_00402150() {
}
```

#### `0x00402220` (8 bytes, cluster) - `src/unidentified/unassigned_00402220.cpp`

layout `layout/ltcg/acc_00402220.json`

```cpp
// 0x00402220: clear bit 0 of +0x80.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00402220 {
    unsigned char pad_000[0x80];
    unsigned int field_080;                 // +0x80
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00402220::ClearValue() {
    field_080 &= ~1u;
}
#pragma code_seg()
```

#### `0x00404EC0` (4 bytes, cluster) - `src/unidentified/unassigned_00404ec0.cpp`

layout `layout/ltcg/acc_00404ec0.json`

```cpp
// 0x00404EC0: load the +0x8 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00404ec0 {
    unsigned char pad_000[0x8];
    float field_8;                          // +0x8
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00404ec0::LoadValue() const {
    return field_8;
}
#pragma code_seg()
```

#### `0x00404F20` (8 bytes, cluster) - `src/unidentified/unassigned_00404f20.cpp`

layout `layout/ltcg/acc_00404f20.json`

```cpp
// 0x00404F20: clear bit 0 of +0x35C.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00404f20 {
    unsigned char pad_000[0x35C];
    unsigned int field_35c;                 // +0x35C
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00404f20::ClearValue() {
    field_35c &= ~1u;
}
#pragma code_seg()
```

#### `0x00405000` (20 bytes, cluster) - `src/unidentified/unassigned_00405000.cpp`

layout `layout/ltcg/acc_00405000.json`

```cpp
// 0x00405000: copy the argument vector into the +0x24 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00405000 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405000 {
    unsigned char pad_000[0x24];
    Vec3_00405000 field;                          // +0x24
    __declspec(noinline) void CopyFrom(const Vec3_00405000* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00405000::CopyFrom(const Vec3_00405000* src) {
    Vec3_00405000* dst = (Vec3_00405000*)((int)this + 0x24);
    *dst = *src;
}
#pragma code_seg()
```

#### `0x00405020` (20 bytes, cluster) - `src/unidentified/unassigned_00405020.cpp`

layout `layout/ltcg/acc_00405020.json`

```cpp
// 0x00405020: copy the argument vector into the +0x18 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00405020 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405020 {
    unsigned char pad_000[0x18];
    Vec3_00405020 field;                          // +0x18
    __declspec(noinline) void CopyFrom(const Vec3_00405020* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00405020::CopyFrom(const Vec3_00405020* src) {
    Vec3_00405020* dst = (Vec3_00405020*)((int)this + 0x18);
    *dst = *src;
}
#pragma code_seg()
```

#### `0x00405110` (20 bytes, cluster) - `src/unidentified/unassigned_00405110.cpp`

layout `layout/ltcg/acc_00405110.json`

```cpp
// 0x00405110: copy the argument vector into the +0xC field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00405110 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405110 {
    unsigned char pad_000[0xC];
    Vec3_00405110 field;                          // +0xC
    __declspec(noinline) void CopyFrom(const Vec3_00405110* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00405110::CopyFrom(const Vec3_00405110* src) {
    Vec3_00405110* dst = (Vec3_00405110*)((int)this + 0xC);
    *dst = *src;
}
#pragma code_seg()
```

#### `0x004051C0` (14 bytes, plain) - `src/unidentified/unassigned_004051c0.cpp`

```cpp
// 0x004051C0: read whether the +0x390 field is set.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_004051c0 {
    unsigned char pad_000[0x390];
    int field_390;                          // +0x390
    __declspec(noinline) int IsNonZero() const;
};

int Predicate_004051c0::IsNonZero() const {
    return field_390 != 0;
}
```

#### `0x004052A0` (11 bytes, plain) - `src/unidentified/unassigned_004052a0.cpp`

```cpp
// 0x004052A0: rewind the frame timer one step.
//
// The timer pointer arrives in ECX, a plain __thiscall receiver.
#include "th10/math/timer.hpp"

struct TimerResetter_004052a0 {
    __declspec(noinline) void Rewind();
};

void TimerResetter_004052a0::Rewind() {
    ((FrameTimer*)this)->Advance(-1.0f);
}
```

#### `0x004052B0` (20 bytes, cluster) - `src/unidentified/unassigned_004052b0.cpp`

layout `layout/ltcg/acc_004052b0.json`

```cpp
#include "th10/math/timer.hpp"

// 0x004052B0: advance the timer by minus an integer count.
//
// The timer pointer arrives in ECX (a plain __thiscall receiver) and the count
// in EAX, which only the whole-program pass of a native LTCG link selects, so
// the body is compiled as a single-function cluster.
struct TimerDecrementer_004052b0 {
    __declspec(noinline) void Decrement(int count);
};

#pragma code_seg(".text$01accessor")
void TimerDecrementer_004052b0::Decrement(int count) {
    ((FrameTimer*)this)->Advance((float)(-count));
}
#pragma code_seg()
```

#### `0x004052D0` (16 bytes, plain) - `src/unidentified/unassigned_004052d0.cpp`

```cpp
// 0x004052D0: advance the frame timer by an integer count.
//
// The timer pointer arrives in ECX, a plain __thiscall receiver.
#include "th10/math/timer.hpp"

struct TimerAdvancer_004052d0 {
    __declspec(noinline) void AdvanceCount(int count);
};

void TimerAdvancer_004052d0::AdvanceCount(int count) {
    ((FrameTimer*)this)->Advance((float)count);
}
```

#### `0x00405380` (3 bytes, cluster) - `src/unidentified/unassigned_00405380.cpp`

layout `layout/ltcg/acc_00405380.json`

```cpp
// 0x00405380: load the +0x0 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00405380 {
    float field_0;                          // +0x0
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405380::LoadValue() const {
    return field_0;
}
#pragma code_seg()
```

#### `0x004053A0` (7 bytes, cluster) - `src/unidentified/unassigned_004053a0.cpp`

layout `layout/ltcg/acc_004053a0.json`

```cpp
// 0x004053A0: read bit 0 of the +0x60 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_004053a0 {
    unsigned char pad_000[0x60];
    unsigned int field_60;                    // +0x60
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004053a0::LoadValue() const {
    return field_60 & 1;
}
#pragma code_seg()
```

#### `0x004053E0` (1 bytes, plain) - `src/unidentified/unassigned_004053e0.cpp`

```cpp
// 0x004053E0: an empty function; retail's body is a bare return.
extern "C" void Empty_004053e0() {
}
```

#### `0x004053F0` (1 bytes, plain) - `src/unidentified/unassigned_004053f0.cpp`

```cpp
// 0x004053F0: an empty function; retail's body is a bare return.
extern "C" void Empty_004053f0() {
}
```

#### `0x00405490` (4 bytes, cluster) - `src/unidentified/unassigned_00405490.cpp`

layout `layout/ltcg/acc_00405490.json`

```cpp
// 0x00405490: load the +0x8 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00405490 {
    unsigned char pad_000[0x8];
    float field_8;                          // +0x8
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405490::LoadValue() const {
    return field_8;
}
#pragma code_seg()
```

#### `0x004054A0` (6 bytes, cluster) - `src/unidentified/unassigned_004054a0.cpp`

layout `layout/ltcg/acc_004054a0.json`

```cpp
// 0x004054A0: address of the sub-object at +0x3C0.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_004054a0 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004054a0::Offset() const {
    return (int)this + 0x3C0;
}
#pragma code_seg()
```

#### `0x00405560` (10 bytes, cluster) - `src/unidentified/unassigned_00405560.cpp`

layout `layout/ltcg/acc_00405560.json`

```cpp
// 0x00405560: read bit 0 of the +0x378C flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_00405560 {
    unsigned char pad_000[0x378C];
    unsigned int field_378c;                    // +0x378C
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00405560::LoadValue() const {
    return field_378c & 1;
}
#pragma code_seg()
```

#### `0x00405570` (15 bytes, plain) - `src/unidentified/unassigned_00405570.cpp`

```cpp
// 0x00405570: read whether the +0x3738 field is at least 60.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_00405570 {
    unsigned char pad_000[0x3738];
    int field_3738;                          // +0x3738
    __declspec(noinline) int IsAtLeast60() const;
};

int Predicate_00405570::IsAtLeast60() const {
    return field_3738 >= 0x3C;
}
```

#### `0x00405B40` (25 bytes, cluster) - `src/unidentified/unassigned_00405b40.cpp`

layout `layout/ltcg/acc_00405b40.json`

```cpp
// 0x00405B40: squared distance between the receiver and the argument vector.
//
// The receiver arrives in EAX and the argument in ECX - a register pair no
// C++ declaration names - so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00405b40 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405b40 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) float DistSq(const Vec3_00405b40* other) const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405b40::DistSq(const Vec3_00405b40* other) const {
    float dy = y - other->y;
    float dx = x - other->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
```

#### `0x00405BA0` (4 bytes, cluster) - `src/unidentified/unassigned_00405ba0.cpp`

layout `layout/ltcg/acc_00405ba0.json`

```cpp
// 0x00405BA0: load the +0x40 float.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_00405ba0 {
    unsigned char pad_000[0x40];
    float field_40;                          // +0x40
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00405ba0::LoadValue() const {
    return field_40;
}
#pragma code_seg()
```

#### `0x00405BC0` (1 bytes, plain) - `src/unidentified/unassigned_00405bc0.cpp`

```cpp
// 0x00405BC0: an empty function; retail's body is a bare return.
extern "C" void Empty_00405bc0() {
}
```

#### `0x00405E10` (7 bytes, plain) - `src/unidentified/unassigned_00405e10.cpp`

```cpp
// 0x00405E10: clear bit 0 of the +0x10 flags word and return the object.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is an
// ordinary translation unit; the returned object is what the caller keeps.
struct ObjectClearer_00405e10 {
    unsigned char pad_000[0x10];
    unsigned int flags;                       // +0x10
    __declspec(noinline) ObjectClearer_00405e10* Clear();
};

ObjectClearer_00405e10* ObjectClearer_00405e10::Clear() {
    flags &= ~1u;
    return this;
}
```

#### `0x00408620` (25 bytes, cluster) - `src/unidentified/unassigned_00408620.cpp`

layout `layout/ltcg/acc_00408620.json`

```cpp
// 0x00408620: squared distance between the receiver and the argument vector.
//
// The receiver arrives in EAX and the argument in ECX - a register pair no
// C++ declaration names - so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00408620 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00408620 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) float DistSq(const Vec3_00408620* other) const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00408620::DistSq(const Vec3_00408620* other) const {
    float dy = y - other->y;
    float dx = x - other->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
```

#### `0x00408640` (20 bytes, cluster) - `src/unidentified/unassigned_00408640.cpp`

layout `layout/ltcg/acc_00408640.json`

```cpp
// 0x00408640: squared length of the two-component vector.
//
// The vector pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster.
struct Vec3_00408640 {
    float x;                                  // +0x0
    float y;                                  // +0x4
    float z;                                  // +0x8
};

struct ObjectAccessor_00408640 {
    float x;                                  // +0x0
    float y;                                  // +0x4
    float z;                                  // +0x8
    __declspec(noinline) float LengthSq() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00408640::LengthSq() const {
    return y * y + x * x;
}
#pragma code_seg()
```

#### `0x00408730` (25 bytes, cluster) - `src/unidentified/unassigned_00408730.cpp`

layout `layout/ltcg/acc_00408730.json`

```cpp
// 0x00408730: subtract the argument vector componentwise.
//
// The destination vector arrives in EAX and the source vector in ECX - a
// register pair no C++ declaration names - so the body is compiled as a
// single-function native-LTCG cluster.
struct Vec3_00408730 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00408730 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) void Apply(const Vec3_00408730* other);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408730::Apply(const Vec3_00408730* other) {
    x = x - other->x;
    y = y - other->y;
    z = z - other->z;
}
#pragma code_seg()
```

#### `0x00408770` (12 bytes, plain) - `src/unidentified/unassigned_00408770.cpp`

```cpp
// 0x00408770: scale the next random float by a factor.
#include "th10/math/rng.hpp"

struct RngScaler_00408770 {
    __declspec(noinline) float Scale(float factor) const;
};

float RngScaler_00408770::Scale(float factor) const {
    return Rng_NextFloat((RngState*)this) * factor;
}
```

#### `0x00408780` (10 bytes, cluster) - `src/unidentified/unassigned_00408780.cpp`

layout `layout/ltcg/acc_00408780.json`

```cpp
// 0x00408780: read bit 2 of the +0x58 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00408780 {
    unsigned char pad_000[0x58];
    unsigned int field_058;                 // +0x58
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00408780::LoadValue() const {
    return (field_058 >> 2) & 1;
}
#pragma code_seg()
```

#### `0x00408790` (14 bytes, cluster) - `src/unidentified/unassigned_00408790.cpp`

layout `layout/ltcg/acc_00408790.json`

```cpp
// 0x00408790: read bit 2 of +0x58 via or-fold.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00408790 {
    unsigned char pad_000[0x58];
    unsigned int field_058;                 // +0x58
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00408790::LoadValue() const {
    return ((field_058 >> 2) | field_058) & 1;
}
#pragma code_seg()
```

#### `0x004087C0` (9 bytes, cluster) - `src/unidentified/unassigned_004087c0.cpp`

layout `layout/ltcg/acc_004087c0.json`

```cpp
// 0x004087C0: read bit 1 of the +0x58 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_004087c0 {
    unsigned char pad_000[0x58];
    unsigned int field_058;                 // +0x58
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004087c0::LoadValue() const {
    return (field_058 >> 1) & 1;
}
#pragma code_seg()
```

#### `0x004087E0` (25 bytes, cluster) - `src/unidentified/unassigned_004087e0.cpp`

layout `layout/ltcg/acc_004087e0.json`

```cpp
// 0x004087E0: add the argument vector componentwise.
//
// The destination vector arrives in EAX and the source vector in ECX - a
// register pair no C++ declaration names - so the body is compiled as a
// single-function native-LTCG cluster.
struct Vec3_004087e0 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_004087e0 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) void Apply(const Vec3_004087e0* other);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004087e0::Apply(const Vec3_004087e0* other) {
    x = x + other->x;
    y = y + other->y;
    z = z + other->z;
}
#pragma code_seg()
```

#### `0x00408800` (1 bytes, plain) - `src/unidentified/unassigned_00408800.cpp`

```cpp
// 0x00408800: an empty function; retail's body is a bare return.
extern "C" void Empty_00408800() {
}
```

#### `0x00408810` (1 bytes, plain) - `src/unidentified/unassigned_00408810.cpp`

```cpp
// 0x00408810: an empty function; retail's body is a bare return.
extern "C" void Empty_00408810() {
}
```

#### `0x00408820` (6 bytes, cluster) - `src/unidentified/unassigned_00408820.cpp`

layout `layout/ltcg/acc_00408820.json`

```cpp
// 0x00408820: address of the sub-object at +0x1068.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00408820 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00408820::Offset() const {
    return (int)this + 0x1068;
}
#pragma code_seg()
```

#### `0x00408840` (8 bytes, cluster) - `src/unidentified/unassigned_00408840.cpp`

layout `layout/ltcg/acc_00408840.json`

```cpp
// 0x00408840: clear bit 0 of +0x2A18.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00408840 {
    unsigned char pad_000[0x2A18];
    unsigned int field_2a18;                 // +0x2A18
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408840::ClearValue() {
    field_2a18 &= ~1u;
}
#pragma code_seg()
```

#### `0x00408850` (8 bytes, cluster) - `src/unidentified/unassigned_00408850.cpp`

layout `layout/ltcg/accessor_00408850.json`

```cpp
// 0x00408850: raise bit 0 of the object's +0x2A18 flag word.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster whose synthetic
// caller walks an array of objects.
struct ObjectAccessor_00408850 {
    unsigned char pad_000[0x2A18];
    unsigned int field_2a18;                 // +0x2A18
    __declspec(noinline) void SetValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408850::SetValue() {
    field_2a18 |= 1u;
}
#pragma code_seg()
```

#### `0x00408AA0` (3 bytes, plain) - `src/unidentified/unassigned_00408aa0.cpp`

```cpp
// 0x00408AA0: return 0.
extern "C" int Zero_00408aa0() {
    return 0;
}
```

#### `0x00408AB0` (3 bytes, plain) - `src/unidentified/unassigned_00408ab0.cpp`

```cpp
// 0x00408AB0: return 0.
extern "C" int Zero_00408ab0() {
    return 0;
}
```

#### `0x00408AC0` (35 bytes, cluster) - `src/unidentified/unassigned_00408ac0.cpp`

layout `layout/ltcg/acc_00408ac0.json`

```cpp
// 0x00408AC0: raise bit 1 of the flags word of the +0x8 and +0xC sub-objects and
// of the object named by the +0x37AC pointer.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster.
struct SetTarget_00408ac0 {
    unsigned char pad_000[4];
    unsigned int flags;                       // +0x4
};

struct ObjectAccessor_00408ac0 {
    unsigned char pad_000[8];
    SetTarget_00408ac0* first;                // +0x8
    SetTarget_00408ac0* second;               // +0xC
    unsigned char pad_010[0x37AC - 0x10];
    SetTarget_00408ac0* third;                // +0x37AC
    __declspec(noinline) void Set();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408ac0::Set() {
    if (first) first->flags |= 2u;
    if (second) second->flags |= 2u;
    third->flags |= 2u;
}
#pragma code_seg()
```

#### `0x00409E00` (12 bytes, plain) - `src/unidentified/unassigned_00409e00.cpp`

```cpp
// 0x00409E00: read whether the +0x10 field is 1.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_00409e00 {
    unsigned char pad_000[0x10];
    int field_10;                          // +0x10
    __declspec(noinline) int IsOne() const;
};

int Predicate_00409e00::IsOne() const {
    return field_10 == 1;
}
```

#### `0x00409E40` (1 bytes, plain) - `src/unidentified/unassigned_00409e40.cpp`

```cpp
// 0x00409E40: an empty function; retail's body is a bare return.
extern "C" void Empty_00409e40() {
}
```

#### `0x00409EA0` (1 bytes, plain) - `src/unidentified/unassigned_00409ea0.cpp`

```cpp
// 0x00409EA0: an empty function; retail's body is a bare return.
extern "C" void Empty_00409ea0() {
}
```

#### `0x0040ACC0` (7 bytes, cluster) - `src/unidentified/unassigned_0040acc0.cpp`

layout `layout/ltcg/acc_0040acc0.json`

```cpp
// 0x0040ACC0: mask the +0x8 word.
//
// The object pointer arrives in EAX and the mask in ECX, a register pair no
// C++ declaration names, so the body is compiled as a single-function
// native-LTCG cluster whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040acc0 {
    unsigned char pad_000[0x8];
    unsigned short field_008;               // +0x8
    __declspec(noinline) int LoadMasked(int mask) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040acc0::LoadMasked(int mask) const {
    return (int)field_008 & mask;
}
#pragma code_seg()
```

#### `0x0040ACD0` (7 bytes, cluster) - `src/unidentified/unassigned_0040acd0.cpp`

layout `layout/ltcg/acc_0040acd0.json`

```cpp
// 0x0040ACD0: mask the +0x6 word.
//
// The object pointer arrives in EAX and the mask in ECX, a register pair no
// C++ declaration names, so the body is compiled as a single-function
// native-LTCG cluster whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040acd0 {
    unsigned char pad_000[0x6];
    unsigned short field_006;               // +0x6
    __declspec(noinline) int LoadMasked(int mask) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040acd0::LoadMasked(int mask) const {
    return (int)field_006 & mask;
}
#pragma code_seg()
```

#### `0x0040ADC0` (1 bytes, plain) - `src/unidentified/unassigned_0040adc0.cpp`

```cpp
// 0x0040ADC0: an empty function; retail's body is a bare return.
extern "C" void Empty_0040adc0() {
}
```

#### `0x0040AE00` (28 bytes, cluster) - `src/unidentified/unassigned_0040ae00.cpp`

layout `layout/ltcg/acc_0040ae00.json`

```cpp
// 0x0040AE00: clear bit 1 of the flags word of both +0x8 and +0xC sub-objects.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster.
struct ClearTarget_0040ae00 {
    unsigned char pad_000[4];
    unsigned int flags;                       // +0x4
};

struct ObjectAccessor_0040ae00 {
    unsigned char pad_000[8];
    ClearTarget_0040ae00* first;              // +0x8
    ClearTarget_0040ae00* second;             // +0xC
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040ae00::Clear() {
    if (first) first->flags &= ~2u;
    if (second) second->flags &= ~2u;
}
#pragma code_seg()
```

#### `0x0040B290` (1 bytes, plain) - `src/unidentified/unassigned_0040b290.cpp`

```cpp
// 0x0040B290: an empty function; retail's body is a bare return.
extern "C" void Empty_0040b290() {
}
```

#### `0x0040B310` (3 bytes, plain) - `src/unidentified/unassigned_0040b310.cpp`

```cpp
// 0x0040B310: return 0.
extern "C" int Zero_0040b310() {
    return 0;
}
```

#### `0x0040B370` (23 bytes, cluster) - `src/unidentified/unassigned_0040b370.cpp`

layout `layout/ltcg/acc_0040b370.json`

```cpp
// 0x0040B370: copy the argument vector into the +0x340 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_0040b370 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_0040b370 {
    unsigned char pad_000[0x340];
    Vec3_0040b370 field;                          // +0x340
    __declspec(noinline) void CopyFrom(const Vec3_0040b370* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040b370::CopyFrom(const Vec3_0040b370* src) {
    Vec3_0040b370* dst = (Vec3_0040b370*)((int)this + 0x340);
    *dst = *src;
}
#pragma code_seg()
```

#### `0x0040B390` (1 bytes, plain) - `src/unidentified/unassigned_0040b390.cpp`

```cpp
// 0x0040B390: an empty function; retail's body is a bare return.
extern "C" void Empty_0040b390() {
}
```

#### `0x0040B460` (9 bytes, cluster) - `src/unidentified/unassigned_0040b460.cpp`

layout `layout/ltcg/acc_0040b460.json`

```cpp
// 0x0040B460: read bit 1 of the +0x74 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b460 {
    unsigned char pad_000[0x74];
    unsigned int field_074;                 // +0x74
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b460::LoadValue() const {
    return (field_074 >> 1) & 1;
}
#pragma code_seg()
```

#### `0x0040B470` (10 bytes, cluster) - `src/unidentified/unassigned_0040b470.cpp`

layout `layout/ltcg/acc_0040b470.json`

```cpp
// 0x0040B470: read bit 2 of the +0x74 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b470 {
    unsigned char pad_000[0x74];
    unsigned int field_074;                 // +0x74
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b470::LoadValue() const {
    return (field_074 >> 2) & 1;
}
#pragma code_seg()
```

#### `0x0040B500` (7 bytes, cluster) - `src/unidentified/unassigned_0040b500.cpp`

layout `layout/ltcg/acc_0040b500.json`

```cpp
// 0x0040B500: read bit 0 of the +0x20 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b500 {
    unsigned char pad_000[0x20];
    unsigned int field_020;                 // +0x20
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b500::LoadValue() const {
    return field_020 & 1;
}
#pragma code_seg()
```

#### `0x0040B510` (9 bytes, cluster) - `src/unidentified/unassigned_0040b510.cpp`

layout `layout/ltcg/acc_0040b510.json`

```cpp
// 0x0040B510: read bit 1 of the +0x20 flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b510 {
    unsigned char pad_000[0x20];
    unsigned int field_020;                 // +0x20
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b510::LoadValue() const {
    return (field_020 >> 1) & 1;
}
#pragma code_seg()
```

#### `0x0040B520` (6 bytes, cluster) - `src/unidentified/unassigned_0040b520.cpp`

layout `layout/ltcg/acc_0040b520.json`

```cpp
// 0x0040B520: address of the sub-object at +0x1D86C.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b520 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b520::Offset() const {
    return (int)this + 0x1D86C;
}
#pragma code_seg()
```

#### `0x0040C470` (13 bytes, cluster) - `src/unidentified/unassigned_0040c470.cpp`

layout `layout/ltcg/acc_0040c470.json`

```cpp
// 0x0040C470: return the field at +0x4 modulo the argument.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_0040c470 {
    unsigned char pad_000[0x4];
    int field_4;                             // +0x4
    __declspec(noinline) int Remainder(int divisor) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c470::Remainder(int divisor) const {
    return field_4 % divisor;
}
#pragma code_seg()
```

#### `0x0040C530` (6 bytes, cluster) - `src/unidentified/unassigned_0040c530.cpp`

layout `layout/ltcg/acc_0040c530.json`

```cpp
// 0x0040C530: mask the word at +0x0.
//
// The object pointer arrives in EAX and the mask in ECX, a register pair no
// C++ declaration names, so the body is compiled as a single-function
// native-LTCG cluster whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040c530 {
    unsigned short field_000;               // +0x0
    __declspec(noinline) int LoadMasked(int mask) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c530::LoadMasked(int mask) const {
    return (int)field_000 & mask;
}
#pragma code_seg()
```

#### `0x0040C5D0` (15 bytes, cluster) - `src/unidentified/unassigned_0040c5d0.cpp`

layout `layout/ltcg/acc_0040c5d0.json`

```cpp
// 0x0040C5D0: zero the +0x1000/+0x1004 pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c5d0 {
    unsigned char pad_000[0x1000];
    int field_1000;
    int field_1004;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c5d0::Clear() {
    field_1000 = 0;
    field_1004 = 0;
}
#pragma code_seg()
```

#### `0x0040C710` (21 bytes, cluster) - `src/unidentified/unassigned_0040c710.cpp`

layout `layout/ltcg/acc_0040c710.json`

```cpp
// 0x0040C710: stamp the +0x0 vtable word and clear the +0x1010/+0x1014 pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c710 {
    int field_0;
    unsigned char pad_004[0x100C];
    int field_1010;
    int field_1014;
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c710::Init() {
    field_0 = 0x46D0D8;
    field_1010 = 0;
    field_1014 = 0;
}
#pragma code_seg()
```

#### `0x0040C800` (15 bytes, cluster) - `src/unidentified/unassigned_0040c800.cpp`

layout `layout/ltcg/acc_0040c800.json`

```cpp
// 0x0040C800: zero the +0x1008/+0x100C pair
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c800 {
    unsigned char pad_000[0x1008];
    int field_1008;
    int field_100c;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c800::Clear() {
    field_1008 = 0;
    field_100c = 0;
}
#pragma code_seg()
```

#### `0x0040C920` (9 bytes, cluster) - `src/unidentified/unassigned_0040c920.cpp`

layout `layout/ltcg/acc_0040c920.json`

```cpp
// 0x0040C920: subtract the argument from the +0x0 field and return the new value.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_0040c920 {
    int field_0;                             // +0x0
    __declspec(noinline) int Accumulate(int value);
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c920::Accumulate(int value) {
    field_0 = field_0 - value;
    return field_0;
}
#pragma code_seg()
```

#### `0x0040C930` (10 bytes, plain) - `src/unidentified/unassigned_0040c930.cpp`

```cpp
// 0x0040C930: read whether the +0x0 field is positive.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_0040c930 {
    int field_0;                          // +0x0
    __declspec(noinline) int IsPositive() const;
};

int Predicate_0040c930::IsPositive() const {
    return field_0 > 0;
}
```

#### `0x0040C940` (11 bytes, cluster) - `src/unidentified/unassigned_0040c940.cpp`

layout `layout/ltcg/acc_0040c940.json`

```cpp
// 0x0040C940: zero the three +0x0/+0x4/+0x8 fields
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster whose
// synthetic caller walks an array of objects.
struct ObjectAccessor_0040c940 {
    int field_0;
    int field_4;
    int field_8;
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040c940::Clear() {
    field_0 = 0;
    field_4 = 0;
    field_8 = 0;
}
#pragma code_seg()
```

#### `0x0040CC10` (4 bytes, cluster) - `src/unidentified/unassigned_0040cc10.cpp`

layout `layout/ltcg/acc_0040cc10.json`

```cpp
// 0x0040CC10: return the address of the sub-object at +0x2C.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// this body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_0040cc10 {
    __declspec(noinline) int Offset();
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cc10::Offset() {
    return (int)this + 0x2C;
}
#pragma code_seg()
```

#### `0x0040CC20` (6 bytes, cluster) - `src/unidentified/unassigned_0040cc20.cpp`

layout `layout/ltcg/acc_0040cc20.json`

```cpp
// 0x0040CC20: address of the sub-object at +0x13C0.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040cc20 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cc20::Offset() const {
    return (int)this + 0x13C0;
}
#pragma code_seg()
```

#### `0x0040CC30` (6 bytes, cluster) - `src/unidentified/unassigned_0040cc30.cpp`

layout `layout/ltcg/acc_0040cc30.json`

```cpp
// 0x0040CC30: address of the sub-object at +0x23FC.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040cc30 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cc30::Offset() const {
    return (int)this + 0x23FC;
}
#pragma code_seg()
```

#### `0x0040CD10` (5 bytes, cluster) - `src/unidentified/unassigned_0040cd10.cpp`

layout `layout/ltcg/acc_0040cd10.json`

```cpp
// 0x0040CD10: clear bit 0 of +0x30.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040cd10 {
    unsigned char pad_000[0x30];
    unsigned int field_030;                 // +0x30
    __declspec(noinline) void ClearValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040cd10::ClearValue() {
    field_030 &= ~1u;
}
#pragma code_seg()
```

#### `0x0040CE30` (14 bytes, plain) - `src/unidentified/unassigned_0040ce30.cpp`

```cpp
// 0x0040CE30: read whether the +0x9EB8 field is set.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_0040ce30 {
    unsigned char pad_000[0x9EB8];
    int field_9eb8;                          // +0x9EB8
    __declspec(noinline) int IsNonZero() const;
};

int Predicate_0040ce30::IsNonZero() const {
    return field_9eb8 != 0;
}
```

#### `0x0040CE70` (6 bytes, cluster) - `src/unidentified/unassigned_0040ce70.cpp`

layout `layout/ltcg/acc_0040ce70.json`

```cpp
// 0x0040CE70: address of the sub-object at +0x9A48.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040ce70 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040ce70::Offset() const {
    return (int)this + 0x9A48;
}
#pragma code_seg()
```

#### `0x0040CE80` (11 bytes, plain) - `src/unidentified/unassigned_0040ce80.cpp`

```cpp
// 0x0040CE80: read whether the +0x28 field is set.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_0040ce80 {
    unsigned char pad_000[0x28];
    int field_28;                          // +0x28
    __declspec(noinline) int IsNonZero() const;
};

int Predicate_0040ce80::IsNonZero() const {
    return field_28 != 0;
}
```

#### `0x0040CE90` (8 bytes, cluster) - `src/unidentified/unassigned_0040ce90.cpp`

layout `layout/ltcg/acc_0040ce90.json`

```cpp
// 0x0040CE90: raise bit 3 of +0x378C.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040ce90 {
    unsigned char pad_000[0x378C];
    unsigned int field_378c;                 // +0x378C
    __declspec(noinline) void SetValue();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040ce90::SetValue() {
    field_378c |= 8u;
}
#pragma code_seg()
```

#### `0x0040CED0` (13 bytes, cluster) - `src/unidentified/unassigned_0040ced0.cpp`

layout `layout/ltcg/acc_0040ced0.json`

```cpp
// 0x0040CED0: read bit 3 of the +0x378C flags.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040ced0 {
    unsigned char pad_000[0x378C];
    unsigned int field_378c;                 // +0x378C
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040ced0::LoadValue() const {
    return (field_378c >> 3) & 1;
}
#pragma code_seg()
```

#### `0x0040CEE0` (20 bytes, cluster) - `src/unidentified/unassigned_0040cee0.cpp`

layout `layout/ltcg/acc_0040cee0.json`

```cpp
// 0x0040CEE0: copy the argument vector into the +0x24 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_0040cee0 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_0040cee0 {
    unsigned char pad_000[0x24];
    Vec3_0040cee0 field;                          // +0x24
    __declspec(noinline) void CopyFrom(const Vec3_0040cee0* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040cee0::CopyFrom(const Vec3_0040cee0* src) {
    Vec3_0040cee0* dst = (Vec3_0040cee0*)((int)this + 0x24);
    *dst = *src;
}
#pragma code_seg()
```

#### `0x0040D4F0` (3 bytes, plain) - `src/unidentified/unassigned_0040d4f0.cpp`

```cpp
// 0x0040D4F0: return 0.
extern "C" int Zero_0040d4f0() {
    return 0;
}
```

#### `0x0040D500` (3 bytes, plain) - `src/unidentified/unassigned_0040d500.cpp`

```cpp
// 0x0040D500: return 0.
extern "C" int Zero_0040d500() {
    return 0;
}
```

## Dropped candidates (91)

Every dropped region is still `kind: asm` with a null owner in the manifest, i.e.
exactly where it was before this wave. The 60 regions that were only inspected
(never probed with a model) are listed by family with the retail shape that has to be
reproduced; the 9 that were actually probed with a model carry a byte-level delta.

### 1. Pure `int 3` alignment runs - 13 regions, should not be functions at all

`0x40150A`, `0x401517`, `0x40152A`, `0x403041`, `0x403057`, `0x403067`, `0x4054FF`,
`0x40584A`, `0x405856`, `0x406798`, `0x40B056`, `0x40B066`, `0x40DAD1`.

Each region is a solid run of `0xCC` sitting between two functions (for example
`0x40150A..0x40150F` lies between the semantic `0x004014F0` and `0x00401510`), so it
is the same alignment padding the `text_padding_*` entries in `src/data/text_0040.cpp`
already cover - those were also selected by "repeated_CC/00 or inspected INT3 run"
and simply were not caught because the manifest lists these ranges as `asm`.

**Nothing can emit them as a function**: a C++ function always ends in a return, and
retail ends on an INT3. Measured once, deliberately, on `0x40150A`: six
`__debugbreak()` calls emit **7** bytes, `cc cc cc cc cc cc c3` - six INT3 plus the
closing `C3` - against the region's 6. The honest fix is a manifest reclassification
to `kind: padding` with the bytes appended to `src/data/text_0040.cpp`, which
`promote_scratch.py` and `register_cluster.py` deliberately do not do, so it was left
for a wave that owns the padding unit.

### 2. ESI deleting-destructor family - 16 regions, not attempted

`0x401490`, `0x4026E0`, `0x405710`, `0x406120`, `0x408D20`, `0x40A410`, `0x40AFF0`,
`0x40B9B0` (27/28 bytes), `0x40B920`, `0x40D710` (28 bytes), and `0x4014B0`, `0x402700`,
`0x408D40`, `0x40A430`, `0x40B010` (18 bytes).

Two shapes, both entered with the object in **ESI**:

```text
push esi / call <dtor> / test byte [esp+4],1 / je L / push esi / call free /
    add esp,4 / L: mov eax,esi / ret 4                       (27-28 bytes)
test esi,esi / je L / push esi / call <dtor> / push esi / call free /
    pop ecx / L: ret                                          (18 bytes)
```

The 18-byte form is a clean `if (p) { p->~T(); free(p); }` with `p` in ESI. The
destructor it calls (`0x00401260` and friends) reads *its* `this` from the stack
(`mov 0x1c(%esp),%ebp` after six pushes), i.e. the pushed ESI is the argument, which
confirms the object is carried in ESI. The 27-byte form is the same function with a
delete flag, but it **tests `[esp+4]` after its own `push esi`**, i.e. it tests the low
byte of the return address, and it never pops ESI, so its `ret 4` would return to ESI.
That shape is only self-consistent for a function that is never called, which is what
the whole family is: **not one of these 179 regions is referenced** - a scan of the
image found no `e8` call and no vtable/data pointer to any of them except `0x40E760`.

Both forms need the ESI convention, which only a compiled body in the same LTCG link
can earn (the `0x004134B0` ESI-receiver landing is the precedent), i.e. the same
cluster treatment as the landed EAX accessors with a driver whose walk keeps the
object in ESI. That is the next idea for this family; it was not attempted here
because the whole-program pass picks EAX, not ESI, for the accessor driver shape and
each attempt costs a full cluster build.

### 3. `rep stosd` initialisers with the object in EDX - 10 regions, not attempted

`0x409F10` (17), `0x409F50` (16), `0x4055A0` (29), `0x405C80` (28), `0x40C830` (34),
`0x40CBD0` (25), `0x40CBF0` (17), `0x40CF30` (16), `0x40D260` (29), `0x40D3D0` (34).

All ten are the same generated shape - `push edi / xor eax,eax / mov ecx,<count> /
mov edi,edx / rep stosd / ...` - a zeroed or vtable-stamped record whose pointer
arrives in **EDX** and which is returned in EAX (`mov eax,edx`). `0x40D260` and
`0x4055A0` additionally clear a flag before the fill and publish the pointer to
`data_00477704` / `data_004776ec`. Two of them (`0x40CBF0`, `0x409F10`) start the fill
at an interior offset (`add edi,4` / `add edi,14h`). They need an EDX-receiver cluster;
not attempted.

### 4. x87 three-component vector ops - 7 regions, not attempted

`0x404E70` and `0x4051F0` (scale a vector by a stack scalar into EAX from ECX),
`0x405240` (componentwise subtract, `edx - ecx` into EAX), `0x405260` (componentwise
add), `0x405220` (two-vector dot product of `[eax..eax+8]`), `0x408730`/`0x4087E0` are
the landed ones, `0x40C6D0` (`mov eax,[eax+4]; fld [eax]; fsub [esp+4]; fstp [eax];
ret 4`) and `0x40CE10` (`fld [esp+4]; mov [ecx+eax*8+9E98h],edx; fstp
[ecx+eax*8+9E94h]; ret 4`).

The two-vector ones subtract in retail's order (`edx - ecx`) and compute z first;
the landed `0x405B40`/`0x408620` show the x87 addend/order sensitivity, so each needs
its own spelling search. The scale forms also need the receiver in EAX *and* the
argument in ECX *and* a stack scalar, i.e. a three-register convention.

### 5. x87 scalar math thunks - 3 regions, not attempted

`0x404EB0` (`fld [esp+4]; fsin; ret 4`), `0x408720` (`fld [esp+4]; fabs; ret 4`),
`0x408710` (`fld [esp+4]; fld [esp+8]; fpatan; ret 8`). These are `sinf`/`fabsf`/
`atan2f` with the argument loaded directly off the stack and the result left in ST0;
the project compiles without `/Oi`, so the CRT helpers would be calls, and the retail
bodies are the intrinsics. Not attempted.

### 6. EAX receiver + stack argument store pairs - 3 regions, ATTEMPTED

`0x405170` (`mov ecx,[esp+4]; mov [eax+40h],ecx; or [eax+35Ch],8; ret 4`),
`0x405190` (same, `+0x3C`), `0x4087A0` (same, `+0x2C` / bit 2).

Modelled as `void Set(int value) { field = value; flags |= N; }` in the EAX-receiver
cluster. **Delta: 6 bytes / emitted 11 vs retail 17.** The pass leaves the argument in
ECX and drops the stack: emitted `mov [eax+40h],ecx / or dword ptr [eax+35Ch],8 / ret`
where retail has `mov ecx,[esp+4] / mov [eax+40h],ecx / or [eax+35Ch],8 / ret 4`. The
same shape landed at `0x40C470` (`int divisor` on the stack), so the difference is
that the caller in that case had no free register; making the synthetic driver keep a
value live across the call should push the argument back onto the stack.

### 7. `__thiscall` predicates with a stack argument - 2 regions, ATTEMPTED

`0x404E90` (`mov edx,[ecx+4]; mov ecx,[esp+4]; xor eax,eax; cmp edx,ecx; setge al;
ret 4`) and `0x405280` (the `setle` twin), modelled as
`int AtLeast(int v) const { return field_4 >= v; }` on the plain `__thiscall` path.

**Delta: 3 bytes, first difference at `+1`.** Retail loads the field into EDX and the
argument into ECX (`8b 51 04 / 8b 4c 24 04 / 3b d1`); the compiler loads the field into
ECX and the argument into EDX (`8b 49 04 / 8b 54 24 04 / 3b ca`). Five spellings were
tried (`>=`, `v <= field`, a local copy, `field - v >= 0`, and a `volatile` field); all
three of the 17-byte ones differ by exactly those 3 bytes, the other two change the
length. The register assignment is a pure allocator tie-break on the incoming `this`
register; the pair is probably earned from a caller shape this dead region never had.

### 8. Zero-then-publish pair - 2 regions, ATTEMPTED

`0x40AE50` (30 bytes: zero six words of `this`, `or [eax],2`, store `this` to
`data_004776FC`) and `0x40B530` (42 bytes, ten words, `data_00477700`).

Retail keeps a **second** pointer (`mov edx,eax`) for the zeroing stores and writes
the flag through EAX, and does not fold the `or` into a `mov` because it cannot prove
`[edx]` and `[eax]` alias. Modelled four ways - a pointer local, an unrolled loop, a
`volatile` field and an `unsigned int*` - and **four spellings all fold**: the emitted
body is 29, not 30, with no `mov edx,eax`, the six stores through EAX, and
`mov dword ptr [eax],2` in place of `or dword ptr [eax],2`; 21 differing bytes. The
shared-pointer lever (wave-17 `0x00405BE0`) is the documented fix for exactly this, but
it needs the two pointers to be distinct values in the source; a cast of `this` is
coalesced back.

**2026-09-23 resolution for `0x40B530`:** a fixed-size `memset(this, 0,
sizeof(*this))` in a native-LTCG member context emits the retail `mov edx,eax`
and ten zero stores, then retains the separate `or [eax],2` instruction. The
42-byte C++ body passed the focused probe and the whole 487,936-byte executable
check. `0x40AE50` had already been promoted through the same `memset` source
shape before this follow-up.

### 9. `0x40C440` - 24 bytes, ATTEMPTED

`push esi / mov esi,eax / add esi,89A4h / mov eax,esi / call 0x409E50 / mov
dword ptr [esi],0 / pop esi / ret` - the caller of the already-landed
`AnimationHandle::StopAtFrame1` (`0x409E50`, `src/render/anm_propagate.cpp`).

Modelled as `handle.StopAtFrame1(); handle.value = 0;` with the handle at `+0x89A4`
and the receiver in EAX; **delta: 1 byte, first difference at `+9`.** Retail has
`mov eax,esi` (`8b c6`), the emitted has `mov ecx,esi` (`8b ce`) - the callee is
declaration-only here, so the call uses the declared `__thiscall` (ECX) while retail
uses the private EAX convention the maintained cluster for `0x409E50` earns. Landing
it needs that callee compiled into this link as an anchor, which collides with the
existing registration of `0x409E50`; left for a merge into
`layout/ltcg/stop_at_frame_pair_0040c480.json` whose driver already establishes the
EAX convention.

### 10. Everything else - 34 regions, inspected only

Listed with the retail shape and the register pair the cluster would have to earn.

| address | size | retail shape (abridged) | why it needs more than a plain unit |
| --- | ---: | --- | --- |
| `0x004014D0` | 32 | `xor ecx,ecx ; mov dword ptr [eax+896Ch],ecx ; mov dword ptr [eax+8970h],ecx ; inc dword ptr [eax+8990h] ; mov ` | zero `+896C`/`+8970`, `inc [eax+8990h]`, return 1, then 6 INT3 |
| `0x00401CE0` | 44 | `mov ecx,dword ptr [esp+4] ; mov edx,dword ptr [esp+8] ; mov dword ptr [eax+4Ch],ecx ; mov ecx,dword ptr [eax+3` | two-argument setter with `ret 8` immediately followed by a second getter body - the region is two functions |
| `0x00401D60` | 33 | `mov ecx,dword ptr [esp+4] ; mov edx,dword ptr [esp+8] ; mov dword ptr [eax+3Ch],ecx ; mov ecx,dword ptr [eax+3` | two-argument setter (`ret 8`) with a trailing stray `ret` |
| `0x00401DC0` | 29 | `mov edx,esi ; call asm_InitializeEntity_00401de0 ; mov edx,dword ptr [esp+4] ; mov eax,esi ; mov ecx,edi ; mov` | `esi` receiver, `edi` argument, two calls |
| `0x00402020` | 30 | `mov eax,dword ptr [esi+358h] ; test eax,eax ; je short L_00402033 ; push eax ; call asm_free_00452422 ; add es` | `if ([esi+358h]) free(...)` then clear the slot |
| `0x00402040` | 8 | `push eax ; call asm_free_00452422 ; pop ecx ; ret` | `push eax; call free; pop ecx; ret` |
| `0x004020B0` | 56 | `mov edx,dword ptr [eax+6Ch] ; mov ecx,0FFFFFFFEh ; and edx,ecx ; mov dword ptr [eax+6Ch],edx ; and dword ptr [` | load/store `+6Ch` then seven `and [eax+off],ecx` shares ECX=-2 |
| `0x00403077` | 25 | `int 3 ; int 3 ; int 3 ; int 3 ; int 3 ; int 3 ; int 3 ; int 3 ; int 3 ; push eax ; call asm_FUN_00403850_00403` | 6 INT3, `push eax; call; neg eax; sbb eax,eax; ret`, 5 INT3 |
| `0x004043D0` | 59 | `mov dword ptr [edx+1EECh],1 ; push esi ; push edi ; mov edi,dword ptr [ecx] ; lea esi,[edx+1EF0h] ; mov dword ` | three-register (`ecx`,`edx`,`eax`) component copy |
| `0x00404420` | 47 | `mov eax,dword ptr [esi+2A38h] ; push edi ; mov edi,dword ptr [data_00491c10] ; push eax ; mov edx,edi ; mov dw` | `esi` receiver, two animation-manager calls with `edx` context |
| `0x00404C60` | 35 | `push esi ; push edi ; mov ecx,7 ; mov esi,eax ; mov edi,edx ; rep movsd ; pop edi ; pop esi ; ret ; push esi ;` | two 7-dword `rep movsd` copies from `eax`/`edx` |
| `0x00404CA0` | 56 | `mov ecx,dword ptr [eax+80h] ; xor edx,edx ; test cl,1 ; jne short L_00404cca ; or ecx,1 ; mov dword ptr [eax+7` | EAX receiver timer arm with a `test cl,1` first-store sink |
| `0x00404CF0` | 20 | `fild dword ptr [eax+44h] ; push ecx ; mov ecx,dword ptr [eax+38h] ; mov eax,dword ptr [eax+48h] ; fstp dword p` | `fild [eax+44h]`, `ecx`/`eax` loads, two-argument call |
| `0x00404D10` | 26 | `fild dword ptr [eax+84h] ; push ecx ; mov ecx,dword ptr [eax+78h] ; mov eax,dword ptr [eax+88h] ; fstp dword p` | the `+0x78`/`+0x84`/`+0x88` twin of `0x404CF0` |
| `0x004051D0` | 7 | `push eax ; call asm_FUN_0043ee30_0043ee30 ; ret` | `push eax; call 0x43EE30; ret` - argument in EAX |
| `0x004051E0` | 10 | `push eax ; call asm_malloc_00452706 ; add esp,4 ; ret` | `push eax; call malloc; add esp,4; ret` - argument in EAX |
| `0x00405450` | 57 | `mov ecx,dword ptr [eax+10h] ; test cl,1 ; push esi ; mov esi,dword ptr [esp+8] ; jne short L_00405478 ; xor ed` | EAX receiver timer arm with `fild [esp+8]` and `esi` scratch |
| `0x00405CC0` | 51 | `push edi ; push 405DE0h ; push 405D00h ; push 7D1h ; push 7F0h ; lea eax,[esi+60h] ; push eax ; call asm_eh_ve` | `esi` receiver, SEH vector-constructor call, 0xF82D5-dword fill |
| `0x00405F00` | 50 | `mov edx,dword ptr [data_00491c10] ; push 46CD88h ; mov ecx,7 ; call asm_Recovery_LoadCachedResource_00447280 ;` | resource load with two opaque calls and two returns |
| `0x00405F40` | 47 | `push esi ; mov esi,dword ptr [data_00491c10] ; add esi,3AD088h ; push edi ; mov edi,dword ptr [esi] ; test edi` | `esi` receiver over `data_00491c10 + 0x3AD088` |
| `0x004066C0` | 25 | `push esi ; xor esi,esi ; mov ecx,esi ; mov eax,edi ; call asm_FUN_004066e0_004066e0 ; inc esi ; cmp esi,6 ; jl` | `edi` receiver, six calls of `0x4066E0` with `eax`/`ecx` pair |
| `0x00408460` | 62 | `push esi ; mov esi,eax ; push edi ; add esi,60h ; mov edi,7D0h ; TH10_NOP_LEA_ESP_DISP8() ; mov ax,word ptr [e` | `eax` receiver, 0x7D0-iteration slot walk calling `0x408030` |
| `0x004088A0` | 11 | `imul eax,437Ch ; lea eax,[eax+ecx+8] ; ret` | `imul eax,437Ch; lea eax,[eax+ecx+8]; ret` - EAX *and* ECX inputs |
| `0x00409190` | 46 | `test byte ptr [esi+378Ch],1 ; je short L_004091b8 ; mov ecx,dword ptr [data_00491c10] ; lea eax,[esi+10h] ; ca` | `esi` receiver, two animation dispatch calls |
| `0x00409E10` | 12 | `mov eax,dword ptr [ecx+28h] ; mov edx,dword ptr [ecx+2Ch] ; lea eax,[eax+eax*2] ; add eax,edx ; ret` | `eax = [ecx+28h]*3 + [ecx+2Ch]` - plain `__thiscall` but the fold order differs |
| `0x0040ADA0` | 25 | `lea edx,[eax+eax*2] ; shl edx,4 ; add edx,474788h ; mov dword ptr [data_00477848],edx ; mov dword ptr [ecx+3Ch` | `eax`/`ecx` pair, global store plus two field stores |
| `0x0040C590` | 17 | `mov edx,dword ptr [ecx] ; mov ecx,dword ptr [esp+4] ; xor eax,eax ; cmp edx,ecx ; sete al ; ret 4 ; ret` | `sete` predicate with `ret 4` and a trailing stray `ret` (17 bytes for 16 of code) |
| `0x0040C5F0` | 10 | `mov edx,dword ptr [ecx+4] ; push eax ; call asm_ECL_ResolveIntOperand_0044fdb0 ; ret` | `mov edx,[ecx+4]; push eax; call @ECL_ResolveIntOperand@4` - `edx` and a stack argument |
| `0x0040C670` | 11 | `mov edx,dword ptr [edx+4] ; push eax ; push ecx ; call asm_ECL_ResolveIntValue_0044ff00 ; ret` | `mov edx,[edx+4]; push eax; push ecx; call` - two registers plus a stack argument |
| `0x0040C780` | 47 | `push esi ; mov esi,dword ptr [ecx+1034h] ; test esi,esi ; mov dword ptr [ecx],46D0D8h ; je short L_0040c7ad ; ` | `ecx` receiver, `esi`/`edi` scratch, two frees in a list walk |
| `0x0040C860` | 36 | `mov eax,dword ptr [esi+8Ch] ; test eax,eax ; mov dword ptr [esi],46D0F0h ; je short L_0040c883 ; push eax ; ca` | `if ([esi+8Ch]) free(...)` then clear the slot, plus a vtable stamp |
| `0x0040CE50` | 17 | `cmp eax,63h ; jle short L_0040ce5a ; mov eax,63h ; mov dword ptr [ecx+9EC0h],eax ; ret` | `cmp eax,63h; jle; mov eax,63h; mov [ecx+9EC0h],eax` - clamp with the argument in EAX |
| `0x0040DC70` | 12 | `add eax,103Ch ; push eax ; call asm_FUN_0040dc80_0040dc80 ; ret` | `add eax,103Ch; push eax; call 0x40DC80; ret` - argument in EAX |
| `0x0040E760` | 11 | `add ecx,103Ch ; jmp asm_FUN_0040e770_0040e770` | `add ecx,103Ch; jmp 0x40E770` - the one vtable-referenced region (`0x46CCC0`, slot 0) |

## What is left in the block

91 of the 179 regions (`2215` of the 3,041 bytes) are still `asm` with a null owner:
the 13 pure-`INT3` alignments that want a `padding` reclassification, the
ESI/EDX-receiver families that need a driver earning those registers (16 + 10),
the x87 vector/scale and scalar-math thunks (10), and 34 inspected-only regions
whose retail shape is tabulated above.

Landing total for this wave: **88 regions / 826 bytes**, 57 new single-source cluster
layouts. The maintained `ltcg_clusters` list read 335 entries when this note was
written (274 when this wave started; the rest of the increase is siblings landing into
their own blocks). Both manifest gates pass on the result:
`build_msvc.validate_project` 4425 regions / 2376 units, `ltcg_cluster.load_clusters`
377 clusters, none rejected.
Every landing was re-probed `EXACT` against the maintained tree after promotion. No manifest field was hand-
edited; all 88 went through `promote_scratch.py --scratch /tmp/VeinBlock40/msvc
--address <addr> --apply` (57 of them registering a new single-source cluster and
30 flipping a plain record). `make` was not run - the owner gates the build once per
wave.
