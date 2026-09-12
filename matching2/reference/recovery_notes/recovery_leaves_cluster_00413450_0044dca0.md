# Recovery/configuration leaf cluster: 0x00413450..0x0044DCA0

Date: 2026-09-12
Scope: the 18 requested regions from `recovery_leaves.cpp` and their listed
live source files only. `matching2/msvc/regions.json` was not edited.

## Result

Eight regions are independently exact and have been left as semantic source with
task-local native-LTCG layouts, compiler contexts, and proposals:

| Region | Extent | Native-LTCG body SHA-256 | Result |
|---|---:|---|---|
| `0x0044D300` | 98 | `3e67e5e5b88a3f44d9b95d8b5a05421292ce7108d7e62413f65400fa0ce20c38` | exact, 0 differing bytes |
| `0x0044D370` | 103 | `06a311bd94498e7244dfaf5b833038471b39ff56fde1fb076bcc76e20644423e` | exact, 0 differing bytes |
| `0x0044D550` | 82 | `853cb006d29a81a47e74cdf8a3cdbd9dc68b5f82d25d7499887db1b7edf7a371` | exact, 0 differing bytes |
| `0x0044D5D0` | 41 | `c2b7e2c70ebaebef4bb0836e0554998d7483a5dd34b41665f163c686373eba00` | exact, 0 differing bytes |
| `0x0044D600` | 61 | `b663babc0b98b7088c3007870d4f513e9d76756f3666c83d2c02c5f35e8377f1` | exact, 0 differing bytes |
| `0x0044DCA0` | 78 | `c8e6d22510b15a9e6a3cc21aa09e7d76c8bfbb757ff66b3c3d5858eec1ca693c` | exact, 0 differing bytes |
| `0x0044D4E0` | 106 | `b3ef6515a777c88c96f0f99ec0685ca1029b89685076db9661dd1a5fa9f7c19e` | exact, 0 differing bytes |
| `0x0043D790` | 55 | `526116d6742ce9228e8722c4a21cbf53e30e207ac8e42c353cd9b388eb50cd52` | exact, 0 differing bytes |

The maintained semantic sources are:

- `src/game/platform_run_interface_0044d300.cpp`, interface in ESI and
  completion pointer in EBX;
- `src/game/platform_find_available_0044d370.cpp`, owner in EDI with a direct
  abstract COM state-query method;
- `src/game/platform_aggregate_interfaces_0044d550.cpp`, owner in EDI with
  typed COM stop/query slots;
- `src/game/platform_invoke_configured_0044d5d0.cpp`, owner in EAX with the
  final argument held in ESI and vtable in EDX;
- `src/game/platform_query_interfaces_0044d600.cpp`, receiver in EDI;
- `src/game/platform_select_stream_record_0044dca0.cpp`, state in ESI and
  record in ECX, with the retail `SetFilePointer` import and absolute data
  binding;
- `src/game/platform_set_operation_deadline_0044d4e0.cpp`, owner in EAX and
  the randomized x87 deadline expression with constants fixed at
  `0x00470AFC/0x00470B00`;
- `src/game/recovery_select_archive_entry_0043d790.cpp`, path in ECX and owner
  in EAX, calling exact DCA0 with record in ECX and selector state in ESI.

Their retained task-local artifacts are the corresponding address-specific
layout, compiler-context, and proposal files in `matching2/msvc/layout/ltcg/`.

## Exact/mismatch matrix

The following records cover all 18 requested regions. “Not retained” means the
candidate probe source/layout/output was removed and the production asm source
was left unchanged. “Not probed” identifies rows held for dependency triage
under the explicit no-new-address-probes wrap-up instruction.

| Address | Live bytes | Focused result | First mismatch / dependency evidence |
|---|---:|---|---|
| `0x00442220` | 208 | not retained; candidate 192 bytes | first mismatch `+0x00`; semantic candidate had the wrong prologue/register schedule and was 16 bytes short |
| `0x0043BC40` | 135 | not probed; production asm retained | retail is a two-pass D3D device sequence through vtable `+0xAC`, `+0x44`, and `+0x40`, using global device `0x00491C30` and ESI; legacy callback form does not express this object ABI |
| `0x00442300` | 130 | not retained; candidate 128 bytes | first mismatch `+0x0D`; compiler consumed one byte in EDX and emitted `RET 8`, while retail has three stack bytes and `RET 0xC` |
| `0x00414570` | 121 | not probed; production asm retained | EAX/ECX/EBX coupled state, release/free calls, global `0x00491C10` offsets, and the `0x00474CA0` gate require the manager-teardown ABI cluster |
| `0x00441F50` | 116 | not retained; exact extent | 11 differing bytes, first `+0x02`; state/timer schedule matched, but LTCG selected ECX/EDX opposite to the retail compact-parameter register assignment |
| `0x0044D6A0` | 109 | not retained; semantic candidate 113 bytes | first mismatch `+0x00`; ordinary member lowering emitted `push esi; push edi; mov esi,ecx`, while retail enters with the receiver already in ESI and begins `push edi; push 4`; production asm restored |
| `0x0044D4E0` | 106 | exact | 0 differing bytes; final source hash `969e263e94c47867d920658b377d605e854393fcee4ce6a517070ef385c2efeb` |
| `0x0044D370` | 103 | exact | 0 differing bytes; final source hash `43a24a8606b7c54173435277dff7f5452d4f599358e57fa9f86243b92204ffef` |
| `0x0044D300` | 98 | exact | 0 differing bytes; final source hash `1859775b2db70fa5a28484417bdaa5c4750b7182e3c87f35f5d1c95c0f74c9bd` |
| `0x0041F930` | 91 | not probed; production asm retained | global pair slots at `0x00491C10+0x3AD084/+0x3AD088`, custom release helper, and callee-preserved ESI/EDI are coupled |
| `0x00413450` | 84 | not probed; production asm retained | EBX owner contains the resource at `+0x0C`; critical-section/depth bookkeeping, callback `0x00449F60`, global clear, and free must be recovered together |
| `0x00419040` | 79 | not probed; production asm retained | EAX receiver walks eight bucket/direct chains and directly frees resource payloads; legacy callback form does not reproduce the retail direct-free loop |
| `0x0044DCA0` | 78 | exact | 0 differing bytes; final source hash `b8d9872ac5d8432acca6300f55a1eb9879d3161c1106d3a69750d294f9e2f293` |
| `0x0043D790` | 55 | exact | 0 differing bytes with exact DCA0 linked as a fixed dependency; final source hash `73389c84e8f68b58500478e4c3d12a337f2bff3362dad3bef44a616cf5c5bdd5` |
| `0x0044D550` | 82 | exact | 0 differing bytes; typed COM slots corrected the prior `ECX`/`EDX` reload delta; final source hash `6ae879c9b176cda5cc14590071830082ba215088b948e5dd8dfd523b432bce90` |
| `0x0044D600` | 61 | exact | 0 differing bytes; final source hash `e6199af82f14f0bdc7ffde91fc79b4658179b79dccd2345c0ee9a294d7e02af7` |
| `0x0044D5D0` | 41 | exact | 0 differing bytes; typed slot-`0x30` invocation produced retail's ESI final argument and EDX vtable pointer; final source hash `d7f9175dd6024348cd8ad29d89b4c1b1446462f4f653ba1df03a3eef9280243f` |
| `0x00441EF0` | 30 | semantic conversion not probed; production asm retained | fixed x87 `FSINCOS` body; VC7.1 native C++ emits separate `FCOS/FSIN`, so no semantic candidate was retained |

## Probe details and next dependency

The productive COM subgroup used native LTCG pointer-array callers to obtain
the internal EDI/ESI receivers. `0x0044D600` matched the retail six-byte
zero-displacement layout instruction as well as the COM loop. `0x0044DCA0`
required the exact member layout at `+0x08/+0x2C/+0x7C/+0x8C/+0x90`, a volatile
position read to preserve the retail reload, and moving the position update
inside the nonzero-handle branch; that produced the retail `JE +0x23` and the
complete 78-byte body.

The productive platform follow-up recovered D300, D370, D550, and D5D0.
Direct abstract COM methods were decisive: they reproduced the
retail hidden receiver pushes, vtable registers, and reloads. D300 additionally
needed the caller-faithful `if (state & 2)` block shape to place the `return 1`
tail exactly.

The deadline layout now extends text through the PE boundary before
`0x00470000`; this places the two compiler constants at the retail addresses
and makes all 106 bytes exact. D790 became exact only when linked together with
the exact DCA0 selector, which preserves its ECX/EAX input pair and the
downstream ECX/ESI pair.

The remaining constructor/streamer dependency is bounded but unresolved.
`0x0044D6A0` needs a real caller/definition cluster that fixes the constructor
receiver directly in ESI and calls D110 with streamer in EAX plus two stack
arguments. D110 in turn calls archive cursor Seek at `0x0044DD40` with state in
ESI and boolean in AL, and Read at `0x0044DE10` with state in EAX, destination
in EDX, two stack arguments, and `RET 8`. Those cursor leaves are still raw asm;
ordinary C++ declarations substitute incompatible conventions. This is the
next dependency before either D110 or D6A0 can be promoted semantically.

## Platform-tail focused matrix

| Address | Extent | Final disposition | Focused evidence |
|---|---:|---|---|
| `0x0044D4E0` | 106 | semantic exact retained | native-LTCG 106/106, 0 differences, SHA `b3ef6515a777c88c96f0f99ec0685ca1029b89685076db9661dd1a5fa9f7c19e` |
| `0x0044D6A0` | 109 | production asm restored | semantic 113/109, 95 differences in the first 109 bytes, first mismatch `+0x00`; wrong ECX-to-ESI member prologue |
| `0x0044D110` | 483 | production asm retained | baseline 483/483 exact, SHA `08bc2bcfc7c323ad5e5fb320384b90e64b8bbce47d0cd73df6317f5790ff5578`; semantic recovery blocked on the two cursor custom ABIs above |
| `0x0043D790` | 55 | semantic exact retained | native-LTCG 55/55, 0 differences, SHA `526116d6742ce9228e8722c4a21cbf53e30e207ac8e42c353cd9b388eb50cd52`; linked DCA0 also remained 78/78 exact |

## Wrap-up verification

On 2026-09-12 the retained proposals were rebuilt from their maintained source
and final task-local layouts/contexts after the last source state was settled:

| Region | Emitted extent | Byte comparison | Body SHA-256 |
|---|---:|---:|---|
| `0x0044D300` | 98/98 | exact, 0 differences | `3e67e5e5b88a3f44d9b95d8b5a05421292ce7108d7e62413f65400fa0ce20c38` |
| `0x0044D370` | 103/103 | exact, 0 differences | `06a311bd94498e7244dfaf5b833038471b39ff56fde1fb076bcc76e20644423e` |
| `0x0044D550` | 82/82 | exact, 0 differences | `853cb006d29a81a47e74cdf8a3cdbd9dc68b5f82d25d7499887db1b7edf7a371` |
| `0x0044D5D0` | 41/41 | exact, 0 differences | `c2b7e2c70ebaebef4bb0836e0554998d7483a5dd34b41665f163c686373eba00` |
| `0x0044D600` | 61/61 | exact, 0 differences | `b663babc0b98b7088c3007870d4f513e9d76756f3666c83d2c02c5f35e8377f1` |
| `0x0044DCA0` | 78/78 | exact, 0 differences | `c8e6d22510b15a9e6a3cc21aa09e7d76c8bfbb757ff66b3c3d5858eec1ca693c` |
| `0x0044D4E0` | 106/106 | exact, 0 differences | `b3ef6515a777c88c96f0f99ec0685ca1029b89685076db9661dd1a5fa9f7c19e` |
| `0x0043D790` | 55/55 | exact, 0 differences | `526116d6742ce9228e8722c4a21cbf53e30e207ac8e42c353cd9b388eb50cd52` |

The final platform wrap reran D300, D370, D550, and D5D0 from their maintained
semantic sources and final layouts; all four were independently exact. A
Targeted baseline probes confirmed D6A0 and D110 remain exact production asm.
The tail rerun independently validated D4E0 and D790 through their maintained
native-LTCG layouts; D790's linked DCA0 dependency was exact in the same image.
All failed tail candidates and temporary build roots were removed after their
measurements.
`matching2/msvc/regions.json` was not edited.
