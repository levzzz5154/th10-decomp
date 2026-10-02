# 0x0040B110: effect kind spawn from a file (parked)

Twin of 0x0040B070 (recovered in `src/game/effect_kind_spawn_0040b070.cpp`),
taking the animation file directly instead of through an owner. Both return
the handle through a hidden pointer (the handle type has a constructor) and
take the kind in EAX; nothing in the program calls either.

In the `effect_kind_spawn_0040b070` cluster the same body

    AnimationHandle __stdcall Spawn(int kind, AnimationResource* file, void* argument)

matches every instruction except the position of `shl eax,4`: retail emits
`push esi; mov esi,[0x491c10]; shl eax,4; add eax,0x474430`, the probe emits
`shl eax,4; push esi; mov esi,[0x491c10]; add eax,0x474430` (the order retail
uses in 0x0040B070).

Tried without effect: kind as first or last parameter, entry pointer declared
before or after the handle, a reference, `table + kind`, a manager local read
first, the create step expanded by hand, assignment inside the argument.
Indexing the table at every use puts the manager load first but folds the
table address into each access instead of keeping the pointer in EDI. A shared
inline body for both entries breaks 0x0040B070.

The register model in `layout/ltcg/effect_kind_spawn_0040b070_anchors.cpp` is
close to the retail 0x004489D0 body (it differs in the id increment), which
may help the parked 0x004489D0 family.
