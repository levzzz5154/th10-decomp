# Music_Play native-LTCG follow-up

Target: 0x00420B10, 73 bytes, currently assembly in src/platform/sound_dummy.cpp.

Tested in an isolated copy of the verified production project; production ownership remains unchanged. Added Music_Play to the existing resource-registrar cluster, retaining Music_Load, Music_Stop, Music_FadeOut and RegisterResource exact. Address-taking fourth root requires a measured 98-byte compiler context. Gaps are 8 bytes from 0x00420B08 and 167 bytes from 0x00420B59.

The plain readable candidate is the right 73-byte extent, but first differs at 0x00420B43. Retail loads the music-progress base into ECX, then the stack index into EDX. The compiler loads the stack index into ECX, then the base into EDX. The byte store's address is equivalent, but emitted instructions fail the exact-byte gate.

Follow-up variants: ordered volatile reads of both base and index produce base in EAX, index in ECX and shorten the extent; volatile index alone loads index into EAX before base into ECX; volatile base alone likewise changes the extent. Eight additional variants tested volatile store, volatile base+store, an intermediate heard-array pointer, commuted pointer addition, raw byte-pointer indexed/additive addressing, and unsigned index. None passed. Do not promote this candidate or count it as recovered.

Structured per-variant output: /home/levzzz/.hermes/cache/scratch/music_play_variant_results.json. Isolated project: /home/levzzz/.hermes/cache/scratch/th10-music-play-msvc. These scratch artifacts are temporary; this note preserves the measured conclusion. Next useful lever is genuine caller/inline topology or a compiler-specific scheduling setting, not further equivalent address spelling.
