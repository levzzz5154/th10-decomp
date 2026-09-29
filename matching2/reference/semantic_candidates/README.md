# Unintegrated semantic source candidates

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
