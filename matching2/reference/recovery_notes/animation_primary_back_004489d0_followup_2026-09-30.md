# Primary-back registration native-LTCG candidate

Target 0x004489D0, 118-byte assembly region, src/render/animation_manager_register_primary_back_004489d0.cpp. Production ownership remains assembly. Built candidate in isolated copy of positioned_primary_00448d50_wave10 cluster, extracting its compiler-only 103-byte registrar anchor as an additional source. All three selected creator functions remained exact when the expanded registrar reached the requested extent.

The old ABI anchor omitted retail's explicit second tail->next read after setting node->next and reused the generated ID rather than reloading manager state for entity/out stores. Added the second tail->next read and separate counter reads. An 118-byte variant matches much of the body but uses EDI for the ID, pushes it before the empty-list branch, and hoists the counter read before publishing the tail.

With the explicit reread and revised ID code, the complete list insertion prefix through tail publication now matches retail. Remaining residual starts at the ID counter load 0x00448A1A: retail increments ESI, copies to ECX and tests ECX before storing ESI/pop ESI; candidate uses ECX directly and reuses INC flags, and the zero-ID correction becomes a MOV immediate rather than retail INC ECX. Volatile tail/counter access variants and a force-inline ID generator did not solve it. Latest contribution is shorter than 118 bytes and must not be promoted.

Candidate saved at reference/semantic_candidates/animation_primary_back_004489d0_ltcg.cpp. Scratch cluster /home/levzzz/.hermes/cache/scratch/th10-registrar-msvc; artifacts /home/levzzz/.hermes/cache/scratch/registrar-probe. No compiler tools, oracle hashes or production implementation changed. Production accounting remains 1835 C++ /95146 bytes and 469 assembly /227904 bytes; preceding full build verified all487936 executable bytes. This is a candidate/blocker receipt, not a landing.

Next lever: natural ID-generation/caller topology preserving the ESI/ECX snapshot, rather than assuming a current compiler ABI anchor itself byte-matches the owned retail region.
