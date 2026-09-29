# Sound-effect stop request at `0x0043DDB0`

2026-09-26 update. The earlier generic key/flag interpretation is now resolved:
this routine queues a sound-effect stop. Pending sound IDs start at owner
`+0x620`; paired signed sample counts start at `+0x650`. Count `-1` instructs
the dispatcher to Stop the corresponding effect buffer without playing it.

The routine scans twelve IDs for a match or the first negative/free entry.
It writes the requested ID only into a free entry, then stores count `-1`.
A full queue with no match is unchanged. Retail EAX is the selected slot, or
twelve when full. Incoming values are owner in ESI and sound ID in EDI,
followed by plain RET; ECX/EAX are local scratch values initialized by the body.

The complete tested C++ candidate is now
`reference/semantic_candidates/sound_effect_queue.cpp`, with an explicit
two-argument stdcall/RET 8 interface. Its sibling pan producer and integrated
dispatcher tests pass 472 comparisons, including stop-after-play,
play-after-stop, full queues, negative counts and aliases. See
[the current recovery note](sound_commands_and_effect_queue.md) for exact
behavior, validation and limits.

`reference/semantic_candidates/unassigned_0043ddb0.cpp` retains the earlier
generic sketch for provenance. The maintained source
`msvc/src/unidentified/unassigned_0043ddb0.cpp` still contains the authoritative
assembly. Native private ABI/byte matching and whole-executable gates remain
pending; no region was promoted by this recovery.
