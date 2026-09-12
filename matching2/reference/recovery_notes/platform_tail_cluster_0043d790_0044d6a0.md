# Platform-tail recovery wrap

Date: 2026-09-12. `matching2/msvc/regions.json` was not edited.

## Final status

| Address | Size | Disposition | Final probe |
|---|---:|---|---|
| `0x0044D4E0` | 106 | exact semantic source/layout/proposal retained | 106/106, 0 differences, SHA-256 `b3ef6515a777c88c96f0f99ec0685ca1029b89685076db9661dd1a5fa9f7c19e` |
| `0x0043D790` | 55 | exact semantic source/layout/proposal retained | 55/55, 0 differences, SHA-256 `526116d6742ce9228e8722c4a21cbf53e30e207ac8e42c353cd9b388eb50cd52`; fixed DCA0 dependency was also 78/78 exact |
| `0x0044D6A0` | 109 | exact production asm restored | baseline 109/109, 0 differences; failed semantic candidate was 113 bytes with 95 differences in the first 109 and first mismatch at `+0x00` |
| `0x0044D110` | 483 | exact production asm retained | baseline 483/483, 0 differences, SHA-256 `08bc2bcfc7c323ad5e5fb320384b90e64b8bbce47d0cd73df6317f5790ff5578` |

## Failure and next dependency

D6A0's semantic candidate lowered an ordinary ECX member receiver and emitted
`push esi; push edi; mov esi,ecx`; retail enters with the receiver already in
ESI and begins `push edi; push 4`. A productive retry requires a real
constructor/D110 caller cluster that fixes D6A0's ESI receiver and D110's EAX
receiver plus two stack arguments.

D110 additionally depends on archive cursor custom ABIs: Seek `0x0044DD40`
uses ESI state and AL boolean, while Read `0x0044DE10` uses EAX state, EDX
destination, two stack arguments, and `RET 8`. Both cursor leaves remain raw
asm, so ordinary declarations cannot preserve the retail calls.

All candidate-only tail files and temporary probe/build outputs were removed.
