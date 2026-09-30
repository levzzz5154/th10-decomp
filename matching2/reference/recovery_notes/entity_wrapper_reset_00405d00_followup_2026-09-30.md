# Entity wrapper reset 0x00405D00: non-exact implementation receipt

Production ownership remains assembly, 215 bytes. No manifest promotion or main compiled-source change. The older entity_player_helpers note's semantic promotion claim is stale and explicitly had no verification.

Typed C++ partial layout reuses Entity at+8, flags408/41C and nine52-byte records with flags+16 at614. Evidence: retail clears embedded flags, wipes940 bytes, sets spriteIndexFFFF, clears outerflags, clears nine records and returns input ECX pointer inEAX. Normal EntityConstructor call emitted94 bytes; force-inlining plus ordinary loop169, explicitnine clears199. Volatilefirst/lastembeddedflag constraints brought standalone wrapper212 but broke existing88-byte EntityConstructor into96; that experiment is rejected, not a production fix.

Fresh native-LTCG topology trials emitted143/194/199 against215. Best retained candidate199 first mismatch+1; remaining differences include EBXreceiver ownership, initial/final embedded flag read/store scheduling and unrolled record pointer advancement. Candidate uses live-object Reset methods, not uninitialized-constructor reads, raw assembly or emitted-code patches.

Readable candidate preserved: reference/semantic_candidates/entity_wrapper_reset_00405d00.cpp. It is NOT an exact build input. Scratch /home/levzzz/.hermes/cache/scratch/entity-wrapper405d00/msvc; native manifest/driver layout/ltcg/entity_wrapper_reset_00405d00*; worker receipt includes metrics, retail/candidate disassembly and native PE/MAP paths.

Parent independently reran the scratch src/game/entity.cpp probe: all six existing regions EXACT, including constructor88; parent_owned_verify stores artifacts. Parent_target_verify for new source fails NOT EXACT / native cluster image base or entry address differs because shorter target shifts nativecontext. Do not apply worker entity.cpp.diff alone: it removes required assembly without replacing it by an exact contribution. Whole main executable previously verified487936 bytes; no new compiled changes applied and no recovery credited.
