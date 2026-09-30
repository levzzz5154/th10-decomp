# Screen-positioned primary animation creation, 0x00448DB0

Replaced 118-byte assembly owner src/render/player_animation_create_00448db0.cpp with readable native-LTCG C++. Reuses the positioned_primary_00448d50_wave10 cluster and its existing allocator, script loader and list insertion ABI anchors. These anchors are not credited as new recoveries.

Retail behavior: allocate animation object, clear render bucket at +0x20, set flag 0x40000000 at +0x35C, write position at +0x340 with playfield-to-screen offsets (224,16) and unchanged z, load the resource's script, append to primary-back list, return the output handle record. Position enters EDI, other three inputs are stack arguments, RET 12.

The retained prior candidate emitted 118 bytes but reordered the flag update ahead of the render-bucket clear, first difference 0x00448DD2. Replaced the bitfield representation with an unsigned flags dword, explicitly read existing flags, then clear bucket and write updated flags using volatile-qualified accesses. This constrains the evidenced access order without claiming thread synchronization. No inline assembly or emitted-byte rewriting remains in the selected source.

Extended cluster ownership with the 118-byte function, an explicit one-byte compiler-layout gap at 0x00448DAF, and the remaining 2858-byte gap from 0x00448E26 to allocator anchor 0x00449950. The new compiler-only context is measured at 136 bytes. Float constants bind 224.0 and 16.0 to their retail pool addresses. Preserved owner and full original record in previous_record.

Spec/quality review: existing allocator/script/registration calls and retail flags/position offsets retained, no fabricated behavior; address-qualified partial object type prevents collisions; compiler anchors remain unselected. Scratch test first reproduced the mismatch, then exact matched after the access-order fix.

Maintained probe EXACT: 0x00448D00 (73 bytes), 0x00448D50 (95 bytes), new 0x00448DB0 (118 bytes).
Root make build: 1931/1931 sources, zero failures; Whole EXE exact 487936 bytes.
Progress: 1831 C++ /94674 bytes -> 1832 C++ /94792 bytes; assembly 473 /228376 bytes ->472 /228258 bytes. One new recovery, 118 bytes. No commit; prior WIP preserved.

Follow-up leads: the other screen-positioned variants at 0x00448EE0, 0x00449010 and 0x00449140 had the same retained-candidate store-order residual. Apply and independently measure this lever in their respective clusters rather than assuming they match.
