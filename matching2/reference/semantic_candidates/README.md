# Unintegrated semantic source candidates

The [genuine linked-record/player-state graph](player_bullet_state_0041c800/)
contains 42 complete real functions and passes 9,812 bounded comparisons.
Four existing selected helpers / 264 bytes now use this real context; two
synthetic manager layouts are retired. Executing cleanup corrects the owner's
state-3 mode argument to 1. Both full builds pass; exact output equals retail.
No new recovery credit is claimed. See the [manager closure note](../recovery_notes/player_bullet_genuine_2026_10_06.md).

The [genuine movement/player-state graph](player_movement_state_004250b0/)
contains 40 complete real functions and passes 9,270 bounded cases. The complete
54-byte stop-frame and 90-byte position helpers now use this genuine production
context. Full normal and exact builds pass; exact output still equals retail.
Movement remains 1,640/1,656 and the owner 3,044/3,112, unselected. No new recovery
credit is claimed. See the [movement closure note](../recovery_notes/player_movement_genuine_2026_10_06.md).

The [genuine item-spawn/player-state graph](player_item_spawn_0041bb00/)
contains 36 complete real functions and passes 7,084 bounded cases. The complete
199-byte activation and 260-byte collision check now use this genuine graph as
their selected production context. Full normal and exact builds pass; the
exact executable still equals retail. Item Spawn remains 823/819 and the full
player owner 3,060/3,112, unselected. No new recovery credit is claimed. See the
[item-spawn closure note](../recovery_notes/player_item_spawn_genuine_2026_10_06.md).

The [genuine player-state collision graph](player_collision_state_00425730/)
contains 33 complete real functions and passes 5,510 bounded cases. Its full
owner measures 3,060/3,112 bytes. Collision, activation, bounds and animation
creation/loading execute as genuine C++ callees. The complete 199-byte activation
body is raw-exact through the real owner and collision loop; 23 complete bodies
are raw-exact in the isolated fixed graph. Production is unchanged and no new
recovery credit is claimed. See the
[collision graph note](../recovery_notes/player_collision_state_00425730_2026_10_06.md).

The [complete player-state owner](player_state_00425730/) extends the shared
graph to 28 genuine functions and passes 3,953 bounded cases. Its source covers
the full 3,112-byte owner and currently measures 3,024 bytes. The real caller
naturally makes sequence Update raw-exact for all 174 bytes at its retail
address. This isolated proof adds no production recovery credit. See the
[player-state graph note](../recovery_notes/player_state_genuine_00425730_2026_10_06.md).

The [scheduled effect creator](scheduled_effect_00427e90/) extends the shared
graph to 27 genuine functions and passes 3,006 bounded cases. Its full extent
is now 717/717, with 61 differing diagnostic bytes in nine instruction groups.
It remains assembly-owned. The existing 20 diagnostic bodies are unchanged;
23 functions in the larger graph are diagnostic-exact, including the complete
schedule walker through its genuine sequence-update caller. See the
[scheduled creation note](../recovery_notes/scheduled_effect_native_00427e90_2026_10_06.md).

The [shared effect/pickup graph](player_effect_pickup_00428280/) contains both
complete genuine callers and 20 complete bodies with one animation lookup and
removal implementation. Both callers now use one verified player/record/timer/
motion/descriptor layout. Creation, registration and lookup share the recovered
four-byte AnimationRef value interface. All 2508
bounded comparisons pass, including 328 sequences on shared records and lists.
Eighteen complete functions are diagnostic
exact; effect update remains 874/876 and sweep 1171/1170. The 202-byte hit-test
now passes the complete fixed-address gate and is selected as ordinary C++.
Effect update and sweep remain assembly-owned. The already selected initializer now
uses this genuine graph as its production compiler context. See the
[hit-test recovery note](../recovery_notes/player_hit_test_exact_2026_10_06.md).

The historical [player hit-test/pickup graph](player_hit_pickup_004059f0/) contains the
complete actual 128-pickup/32-region sweep and 15 genuine bodies. Its 1837
bounded comparisons pass with the corrected record/clock layout, binary32
edge stores, animation angle type and intrusive child links. The leaf naturally
gets ECX/EAX, but remains 203 / 202 bytes; the sweep is 1171 / 1170 and now
has retail's 64-byte frame. That checkpoint has zero recovery credit; the
selected 202-byte hit-test comes from the larger shared graph above. See the [frame and type note](../recovery_notes/player_pickup_frame_00428630_2026_10_06.md).

These `.cpp` files preserve readable source models for regions with remaining
ABI, frame, or byte-matching differences. They are intentionally outside
`matching2/msvc/regions.json` and the maintained `translation_units` list; the
mapped files under `matching2/msvc/src` keep the original assembly entries
until their complete regions and any required caller/callee clusters pass
the exact-build gates.

Validation varies by candidate. Their Ghidra evidence, measured compiler
differences, tests and ABI limitations are recorded in the corresponding notes
under `matching2/reference/recovery_notes`. In particular, the compressor in
`score_save.cpp` compiles and passes retail differential tests, but its 963-byte
body does not yet match the retail 1029-byte interval.
The decoder in `lzss.cpp` passes 203 retail comparisons when compiled by native
Clang; its updated MSVC byte match remains unverified. See
`recovery_notes/lzss_decoder_00435dc0.md` for the tested contracts.
`dat_crypt.cpp` passes 1666 retail comparisons for encryption/decryption and
596 round trips; its explicit key parameter still requires the retail AL-based
calling convention to be recovered. See
`recovery_notes/dat_crypt_0044b0d0_0044b220.md`.
`dat_archive_read.cpp` passes 671 caller/control-flow comparisons with scripted
file and codec collaborators, preserving the retail cleanup paths. Its private
calling conventions remain unverified; see
`recovery_notes/dat_archive_read_00434dd0.md`.
`dat_archive_load_index.cpp` shares its archive types and passes 623 loader
comparisons, preserving header arithmetic and failure cleanup. See
`recovery_notes/dat_archive_load_index_00434f70.md`; MSVC matching is outstanding.
`dat.cpp` passes 174 packed-index parser comparisons using the actual retail
vector helper and entry constructors. The array cookie, name failures and
sentinel are reproduced. Its C++ allocation guard also passes 278 registered-state
and unwind-action comparisons; Windows exception dispatch and native MSVC
frame/byte matching remain unverified.
See `recovery_notes/dat_archive_parser_004350d0.md`.
Archive Close, Reset and entry deletion pass 1,072 retail comparisons using
the real vector-destructor helper. See
`recovery_notes/archive_cleanup_00434c20_00434d10.md` for flags, cookie counts
and state changes during cleanup.
The disk/resource openers and filename-copy helper pass 470 retail comparisons;
see `recovery_notes/dat_archive_open_00434c30_00434ca0.md`.
Together, ten lifecycle candidates pass 168 complete scenarios over 56 synthetic
DAT archives, 1,236 entry reads, 19 allocation-failure paths and 355 cleanup
calls. See
`recovery_notes/dat_archive_integration.md` for the executed helpers, ABI
adapter and remaining validation limits.
Resource loading/size queries, archive registration and entry-size lookup
pass 518 comparisons, including first-slash routing and stack-file unwind
actions. See `recovery_notes/resource_paths_004357d0_0043599d.md`.
Together with the DAT lifecycle, fourteen candidates pass 456 public resource
loads, 228 size queries and 73 registration attempts across single/multiple
archives and allocation failures. See `recovery_notes/resource_archive_integration.md`.
Private-ABI byte matching is still pending.
The FileHandle opener and path resolver now pass 554 comparisons, including
50 matching memory faults, overlap, import-result handling and callback changes.
See `recovery_notes/file_open_and_resolve.md`; stack-cookie frame matching
remains outstanding. The loose-file integration suite now runs those candidates
with resource dispatch and maintained ReadWhole: 420 loads, 210 size queries
and 108 direct ReadWhole calls agree with retail. See
`recovery_notes/resource_loose_file_integration.md`.
The pending WAVE loader in `sound_wave_load.cpp` passes 396 retail comparisons,
including handoff races, two-region copies and eight matching faults. It calls
the freshly compiled maintained chunk walker; see
`recovery_notes/sound_wave_load_0043d390.md` for ownership, format overreads and
remaining native MSVC/helper ABI differences.
`buffer_file_seek.cpp` passes 8,466 retail comparisons, preserving signed
remaining-count checks, address wrapping and the LONG_MIN magnitude. See
`recovery_notes/buffer_file_seek_004364f0.md`; native byte matching remains pending.
The complete sound initializer and primary-format helper pass 354 and 436
comparisons respectively. Together with the WAVE loader and chunk walker,
they pass 30 startup scenarios executing 709 WAVE preloads. Shared sound types
are in `sound_wave_types.hpp`. See `recovery_notes/sound_device_init_0043cd30.md`
and `recovery_notes/sound_primary_format_0044c7e0.md`; all new regions remain
outside the exact-build manifest.
The preload producer and single-slot helper pass 167 retail comparisons,
including two matching invalid writes. Their integration suite executes the
maintained cached-archive loader, recovered DAT lifecycle and WAVE consumer
together: 31 scenarios, 687 archive loads and 672 WAVE handoffs agree with
retail. See `recovery_notes/sound_preload_worker_0043d080.md` and
`recovery_notes/archive_load_cache_slot_0043d640.md` for shutdown ordering,
publication ownership, ignored read failures and private helper ABIs.
Sound cleanup and MIDI stop have typed candidates in `sound_cleanup.cpp` and
`sound_midi_stop.cpp`. Their individual/integrated tests pass 293 comparisons,
including 49 matching faults, with the maintained interface aggregator executed
in integrated cases. An archive-to-shutdown suite passes 28 scenarios with
874 published buffers, 321 WAVE consumptions and 553 pending-buffer frees.
See `recovery_notes/sound_shutdown_0043d120_0043dab0.md`; native private entry
conventions and byte matching remain pending.
Music slot caching and metadata-table publication pass 282 retail comparisons,
including 79 executions of the maintained basename lookup and six matching
faults. The shared manager layout now names music records, allocation/cursor/
remaining-byte tables, cached names and the container path. See
`recovery_notes/sound_music_cache_0043d7d0.md` for the global-name write,
metadata reloads, ignored I/O results and unchecked copying/indexing.
Stream start and command publication pass 222 individual and 73 integrated
comparisons, with three matching faults. Their helpers execute actual C++
selection, restoration, rewinding and volume setup; refill remains scripted.
`sound_stream_select.cpp` explicitly reloads the array after rand, correcting
a demonstrated Clang evaluation-order gap in the maintained selector source.
See `recovery_notes/sound_stream_start_0044d440.md`, including the corrected
interpretation of the saved ECX word as a restoration flag rather than an input.
Music cursor rewind/read in `music_cursor.cpp` pass 473 comparisons with 33
matching faults. `sound_stream_fill.cpp` passes 177 individual and 94 integrated
comparisons, including nine faults and two bounded no-progress traces. The
startup integration now executes actual selection/restoration/refill/cursor/
rewind/volume code through Play: 67 comparisons, 55 cursor reads, 57 Play calls,
three faults, and an independent PCM padding check. See
`recovery_notes/music_cursor_and_stream_refill.md` for callback reloads, forward
word copying, short file reads, silence padding and native ABI boundaries.
Restart and complete segment servicing now have typed candidates in
`sound_stream_restart.cpp` and `sound_stream_service.cpp`. They pass 435 unit
and 55 integrated comparisons, including eleven matching faults and three
bounded repeat traces. `sound_stream_worker.cpp` clarifies the already-semantic
notification worker and explicitly caches its imports: 53 unit and 24 integrated
comparisons pass, including four restart-to-worker sequences and 43 service calls.
See `recovery_notes/sound_stream_restart_service_worker.md` for write-cursor
gating, loop-start behavior, partial failure state, the maintained Clang import
caching gap, and the separately reported uninitialized-output diagnostic.
Array/single-buffer initialization, notification-buffer recreation and the
complete memory-backed stream factory now have typed candidates. They cover
1,216 retail bytes and pass 372 normal/fault-path comparisons plus 65 actual
table-selected unwind-action comparisons. Integrated tests execute refill,
cursors and restart, including notification table contents and PCM output.
See `recovery_notes/sound_stream_initialization_and_creation.md` for partial
ownership, ignored constructor errors, raw-allocation cleanup, and the observed
synchronous-versus-asynchronous Clang cleanup-state difference.
File-cursor opening, the complete file-stream factory and worker launch now
cover another 1,116 retail bytes. They pass 539 normal/fault comparisons plus
81 registered-state/unwind-action comparisons. Integrated launch executes
shutdown, the maintained aggregator, creation, opening, initialization and PCM
refill together. See `recovery_notes/sound_file_stream_open_create_launch.md`
for invalid-handle cleanup, cached format arithmetic, handle publication,
factory ownership, and the remaining native ABI and thread-scheduling limits.
The cached-music launcher in `sound_stream_launch_cached.cpp` adds a complete
298-byte routine and 373 comparisons. Its integrated branches execute the
memory factory/refill or the maintained basename and file-record selection
helpers. See `recovery_notes/sound_cached_stream_launch_0043d950.md` for format
caching across callbacks, current PCM-range reloads, unchanged selection errors,
and the caller's lack of prior-stream cleanup.
The complete music/effect dispatcher and both float-pan/stop producers now have
typed candidates in `sound_commands.cpp` and `sound_effect_queue.cpp`, covering
1,653 retail-region bytes. They pass 1,312 comparisons, including actual
create/play/shutdown and producer-to-consumer sequences. See
`recovery_notes/sound_commands_and_effect_queue.md` for staged command behavior,
queue compaction, sample aliases, zero-division faults, cubic volume arithmetic,
the tested x87 profile and remaining native byte-matching limits.

Most of the remaining files were integrated as maintained C++ and later
removed because the full byte-verified build rejected them: they compile, but
their code differs from retail (usually a private register ABI, register
allocation, or frame shape). Each is the unit's source as it stood when
removed; for a unit that also holds matching functions, the file keeps only the
rejected declarations. The mapped sources and their manifest records are back
on the exact assembly.

The four laser cutters have complete maintained candidate graphs in
`laser_rectangle_cut_0041eb00/`, `laser_circle_cut_0041efa0/`,
`laser_rectangle_trim_0041d880/` and `laser_circle_trim_0041dd80/`.
Their receipts distinguish native structural checks, complete raw equality
and bounded execution evidence. The rectangle trim is down to 13 differing
bytes; none of these four candidates has been promoted. See
`recovery_notes/laser_trim_native_0041d880_0041dd80_2026_10_06.md` for the
complete copied parameter records, rounding correction, actual virtual
interfaces and current reproduction commands.

- [`laser_cutter_family/`](laser_cutter_family/): coherent complete native graph of all four line-trim/beam-split cutters, with shared faithful virtual interfaces and genuine helpers. All 870 bounded observations are preserved; raw residues remain 13 / 876 / 27 / 433 differing overlap bytes, and the circle trim is one byte short. No promotion or recovered-byte credit. Includes reproducible linker-based execution-address separation and actual compiler include receipts; [follow-up](../recovery_notes/laser_cutter_family_followup_2026_10_06.md).
  The [splitter spilling follow-up](../recovery_notes/laser_rectangle_split_spilling_2026_10_06.md) records live operand widths, byte-only immediate replacements, five rejected counter-record controls and a full-family `/G5` no-op proof. The retained candidate and production ownership are unchanged.

- [`item_spawn_0041bb00/`](item_spawn_0041bb00/): complete 819-byte native candidate with two literal diagnostic differences. The [resource-lowering follow-up](../recovery_notes/item_spawn_resource_lowering_2026_10_06.md) compares pointer/value temporary allocation on the genuine graph, retains a complete real-caller control, and verifies build-6030 Rich-header evidence. No promotion or recovered-byte credit.

- [`item_update_0041afd0/`](item_update_0041afd0/): complete 2,198-slot update and 32-function genuine graph; 473 bounded retail/native comparisons pass, including 38 initializer and 16 heap-fallback cases. It supplies production's existing raw-exact conversion (165), power-add (166), and life-add (141) recoveries. An independent gate also proves the allocator's 161 bytes; its genuine player-initialization owner is retained. Update remains unselected at 2,232 / 2,320 bytes; spawn is 823 / 819. See the [motion follow-up](../recovery_notes/item_update_motion_0041afd0_2026_10_06.md) and historical [initializer note](../recovery_notes/item_update_initializer_0041afd0_2026_10_06.md) and archived [collaborator checkpoint](../recovery_notes/item_update_collaborators_0041afd0_2026_10_06.md); no new recovered-byte credit.
