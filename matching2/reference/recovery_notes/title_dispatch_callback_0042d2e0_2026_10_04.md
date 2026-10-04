# Exact title-dispatch callback: 0x0042D2E0

The complete seven-byte ECX-to-EAX adapter is now a natural C++ member:
`TitleRuntime::Update()` returns the result of the complete readable title
state dispatcher. Native MSVC 13.10.6030 LTCG emits `mov eax, ecx` followed by
the tail jump to 0x42CDF0. The former naked owner was removed; its complete
record is retained in the new semantic region's previous_record.

The cluster selects only these seven bytes. Its full unselected models include
the dispatcher, ending handler, music-room caller and animation/timer/sound
leaves. This recovers the adapter without claiming that the other models match.
The dispatcher is a 1092-byte contribution versus retail's 1128-byte owned
region; the ending handler has retail's 288-byte extent but different bytes.
All unselected contributions retain their complete generated bodies and switch
tables. No helper is shortened to a retail extent.

The music caller did not resolve the ending handler's incoming register:
it still receives EAX and saves/moves EBX. Slot installation still uses an
implicit EBX room instead of the retail stack room. The adapter supplies the
actual outer ECX entry and naturally causes the dispatcher to receive EAX;
this replaces the earlier speculative public-stack dispatcher root.

The seven bytes are `8b c1 e9 09 fb ff ff`. SHA256:
`b6f8146034bff80a9d7731d3d0b39fc79b778baa7661c603229a5bd8638c2079`.
Independent PE extraction from the retail executable confirmed equality.
The native verifier reports zero changed instruction bytes, zero masked bytes,
and no reference bytes used for the build. Float literals of unselected bodies
remain native; the unused __fltused linker marker binds to the retail zero
word at 0x470B04. The music path string is a checked compiled-graph data alias.

Production files:
- src/game/title_dispatch_callback_0042d2e0.cpp
- include/th10/game/title_dispatch_callback_0042d2e0.hpp
- layout/ltcg/title_dispatch_callback_0042d2e0.json and its context/dependencies

Verification: the production full ordinary build passes with exactly the
three previously recorded equivalent regions (31,400 bytes); the exact build
passes and independent cmp confirms the whole 487,936-byte executable.
Ordinary exact C++ is now 2192 regions / 162140 bytes. Remaining assembly is
126 regions / 127448 bytes. Exact mode still uses assembly for the three
large equivalent interpreters; the complete goal remains unfinished.

The independent evidence JSON is adjacent. Full native probe artifacts are
archived under build/experiments/title_dispatch_callback_recovered_2026_10_04.
Reproduce the selected function with:

```
python3 matching2/tools/matching/probe.py --source src/game/title_dispatch_callback_0042d2e0.cpp --output /tmp/title-dispatch-recheck
```

Next recover or improve the complete dispatcher/ending-handler graph rather
than revisiting the adapter, which is exact. The MusicRoom graph alone leaves
the slot helper's ABI different; fuller existing script callers/callees may
constrain its preservation and argument placement.
