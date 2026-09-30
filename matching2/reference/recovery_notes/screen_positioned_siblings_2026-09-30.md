# Screen-positioned sibling factory recoveries

Recovered all three remaining screen-positioned list variants, each 118 bytes:
- 0x00448EE0: primary-front, source src/unidentified/FUN_00448ee0_00448ee0.cpp, cluster positioned_primary_front_00448e80_wave12.
- 0x00449010: secondary-back, source src/unidentified/FUN_00449010_00449010.cpp, cluster positioned_secondary_back_00448fb0.
- 0x00449140: secondary-front, source src/unidentified/FUN_00449140_00449140.cpp, cluster positioned_secondary_front_004490e0.

All now use readable typed C++ following the verified 0x00448DB0 factory. Retain retail allocation/script calls, their specific primary/secondary front/back registration, flag 0x40000000, render-bucket clear and (224,16) playfield-to-screen translation with unchanged z. No invented null handling or behavior.

For each sibling, scratch probes first reproduced the plain-access flag-before-bucket scheduling mismatch, at 0x00448F02, 0x00449032 and 0x00449162 respectively. Explicit volatile-qualified existing-flags read, bucket clear, and flags update matched the observed order and passed the full cluster. These accesses are code-generation constraints, not synchronization claims. Distinct address-qualified partial object/position types avoid conflicting global declarations.

Extended each existing native-LTCG cluster with the complete 118-byte contribution, 1-byte gap following the 95-byte positioned sibling, resized gap to allocator anchor 0x00449950, measured 136-byte synthetic context, and retail constant bindings for 224.0/16.0. Compiler-only anchors remain unselected and uncredited. All previous manifest records and owners retained; translation-unit membership unchanged.

Spec review: each registration call matches its exact retail family; body offsets/flags/position math/call order/return convention agree with original assembly. Quality review: no naked functions, byte emission, fabricated state or tool/oracle edits; pre-existing recoveries in each cluster remain exact.

Maintained probes each EXACT for 73-byte bucket creator, 95-byte positioned creator and new 118-byte screen-positioned creator. Whole make build: 1928/1928 sources, zero failures, executable EXACT across 487936 bytes.
Starting C++ 1832 regions /94792 bytes, assembly 472 /228258 bytes. Final C++ 1835 /95146, assembly 469 /227904. Net 3 recoveries /354 bytes. No commit.
