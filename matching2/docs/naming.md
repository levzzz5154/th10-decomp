# Naming ledger

This file records naming decisions made for reconstructed retail structures,
globals, and constants, together with the evidence behind each name. Names
fall into three confidence tiers:

- **confirmed** — the behavior in the pseudocode fully determines the meaning.
- **inferred** — strongly suggested by behavior plus game-domain knowledge
  (Touhou 10 gameplay: spell-card history "x/y" display, spell bonus that can
  fail, focus/slow movement, etc.). Safe to use, revisit if contradicted.
- **unidentified** — data flow is known but semantics are not; the name
  encodes the data flow honestly instead of guessing.

When renaming later, update the topical subsystem headers, the tests, and this
ledger together.

## Named constants (`include/th10/platform/joystick_poll.hpp`, `include/th10/platform/font_surface_blend.hpp`, `include/th10/game/spell_card_dispatch.hpp`)

| Name | Value | Tier | Evidence |
| --- | --- | --- | --- |
| `kPadShoot` | 0x001 | confirmed | Set from key-config record +0x00 ("shot") in 0x0044A190 |
| `kPadBomb` | 0x002 | confirmed | Key-config record +0x02 |
| `kPadFocus` | 0x004 | confirmed | Key-config record +0x04 ("slow"); community name is focus |
| `kPadPause` | 0x008 | confirmed | Key-config record +0x06 |
| `kPadUp/Down/Left/Right` | 0x010/0x020/0x040/0x080 | confirmed | Axis comparisons in 0x0044A190: y < center-q sets 0x10, y > center+q sets 0x20, x > center+q sets 0x80, x < center-q sets 0x40 |
| `kPadSkip` | 0x100 | inferred | Key-config record +0x10; fifth mapped button |
| `kFontFormatA8R8G8B8` | 0x15 | confirmed | D3DFMT_A8R8G8B8 = 21; 4-byte pixels, alpha at byte 3 (0x00437750) |
| `kFontFormatA1R5G5B5` | 0x19 | confirmed | D3DFMT_A1R5G5B5 = 25; 2-byte pixels, sign bit = alpha bit |
| `kFontFormatA4R4G4B4` | 0x1A | confirmed | D3DFMT_A4R4G4B4 = 26; nibble channels |
| `kSpellStateDeclare` | 0 | inferred | 0x0042A6A0 state 0 allocates + records the history entry |
| `kSpellStateActivate` | 1 | inferred | 0x0042A6A0 state 1 publishes the spell UI globals |
| `kEnemyModeRelaunchArmed` | 0x80 | inferred | Cleared at +0x43C when the relaunch counter hits its limit (0x00407A30) |
| `kDInputInputLost` | 0x8007001E | confirmed | DIERR_INPUTLOST; triggers the 400-try re-acquire loop |
| `kRelaunchHalfPi` | 1.5707964f | confirmed | Retail literal; fallback aim when enemy and player coincide |

## Spell-card record (0x1C4 bytes, allocated by 0x0042A6A0 state 0)

| Offset | Name | Tier | Evidence |
| --- | --- | --- | --- |
| +0x000 | `difficulty` | confirmed | Written from DAT_00474c7c at declare time |
| +0x002 | `spell_id` | confirmed | Copied from/to DAT_004918b0 (active spell id) |
| +0x00C | `bonus_initial` | inferred | Published to DAT_00474c44, the counting-down spell bonus |
| +0x010 | `bonus_active` | inferred | Short published to DAT_00474c48 next to the bonus value; the bonus can be forfeited ("Bonus failed") |
| +0x014 | `bonus_gauge` | inferred | Published *10 through the score-gauge store hook (0x00418B80) into DAT_00474c40 |
| +0x018 | `duration` | confirmed | Preloads the spell countdown clock at 0x00474c54 (timer = duration, previous = duration - 1) |
| +0x01C | `activation_param_a` | unidentified | Published to DAT_00474c70 at activation; semantics unknown |
| +0x020 | `activation_param_b` | unidentified | Published to DAT_00474c98 at activation; semantics unknown |
| +0x024 | `title_text[0x190]` | inferred | 400-byte gap before the history pair; believed spell title buffer, not yet confirmed by a writer function |
| +0x1B4 | `history_captures` | inferred | Published to DAT_00474c90; th10 shows "History captures/attempts" on declaration. Order of the pair is inferred and unverified |
| +0x1B8 | `history_attempts` | inferred | Published to DAT_00474c9c; see above |
| +0x1C0 | `flags` | confirmed | Bit 0 mirrors DAT_00491fc4 bit 0 at declare time |

## Spell UI globals (0x00474c40 block)

| Address | Name | Tier |
| --- | --- | --- |
| DAT_00474c40 | bonus score gauge (store hook target) | inferred |
| DAT_00474c44 | `bonus_value` | inferred |
| DAT_00474c48 | `bonus_active` | inferred |
| DAT_00474c54..64 | spell countdown clock (previous/frame/timer/control/flags) | confirmed |
| DAT_00474c70 | `activation_param_a` | unidentified |
| DAT_00474c90 | `history_captures` | inferred |
| DAT_00474c98 | `activation_param_b` | unidentified |
| DAT_00474c9c | `history_attempts` | inferred |
| DAT_004918b0 | `active_spell_id` | confirmed |
| DAT_004918b4 | `active_spell_aux` (always reset to 0) | unidentified |
| DAT_00491fc4 | capture flag (bit 0) | inferred |

## Bullet ring / ECL slot (batch 10, 0x0040C730)

| Offset | Name | Tier | Evidence |
| --- | --- | --- | --- |
| +0x1018 | `sentinel` (-1) | confirmed | Constant -1 written on reset |
| +0x101C | `self` | confirmed | Self pointer written on reset |
| +0x1020 | `control_flags` | inferred | Bit 0 set by ECL opcode 0x12 and cleared by opcode 0x13 in the instruction dispatcher (0x0044E1A0); renamed from `field_1020` |
| +0x1028 | `flags` | confirmed | Bit 0 cleared on reset |
| +0x1034/+0x1038 | `count_a`/`count_b` | unidentified | Zeroed counters; roles not yet distinguished |

## Key-config button record (DAT_00474e88 + config*0x6A)

| Offset | Name | Notes |
| --- | --- | --- |
| +0x00 | `shoot` | Retail config calls it "shot" |
| +0x02 | `bomb` | |
| +0x04 | `focus` | Retail config calls it "slow" |
| +0x06 | `pause` | |
| +0x10 | `skip` | |

## Ending-text controller (batch 22, 0x0040BA90, 0xEC bytes)

Allocated by the ending MSG loader 0x0040B560 immediately after the selected
`eNN.msg` script is copied into the DAT_00497C38 buffer.

| Offset | Name | Tier | Evidence |
| --- | --- | --- | --- |
| +0x04/+0x18/+0x2C | `timer_a`/`timer_b`/`timer_c` | confirmed | Five-word frame timers: 0xFFF0BDC1 sentinel, &DAT_00476F78 speed, rewind to frame 0 with previous -1 |
| +0x40 | `vm_handles[5]` | confirmed | Handles returned by the VM register walk (0x004489D0), re-resolved through the two live lists at manager +0x72DAD4/+0x72DADC |
| +0x54 | `script_cursor` | confirmed | Caller passes msg_base + *(int*)(msg_base+4) (first MSG entry) |
| +0x74 | `flags` | inferred | Bit 0 set at the end of construction (active bit) |
| +0x7C | `color` | confirmed | Initialized to 0x00FFFFFF (white) |
| +0xD0 | `on_deck_vtable` | unidentified | Inlined sub-object constructor installs PTR_FUN_004703E4; role of the sub-object not yet identified |

The five VMs run ANM scripts 0x42..0x46 at layer 15 with anim flag
0x40000000 - one VM per ending text line. The SEH frame in the raw body is
MSVC unwind bookkeeping for the inlined sub-object constructor only.

## BGM streamer refill state (batch 22, 0x0044D850)

Called from the sound worker thread 0x0043E3A0 whenever the DirectSound
position-notify event fires; +0x74 is the in-refill guard the worker sets
around the call.

| Offset | Name | Tier | Evidence |
| --- | --- | --- | --- |
| +0x08 | `buffer_bytes` | confirmed | Modulo base for the write offset and wraparound accounting |
| +0x5C | `last_play_cursor` | confirmed | Updated from GetCurrentPosition (vtable +0x10) after each refill |
| +0x60 | `total_streamed` | confirmed | Accumulates play-cursor deltas with buffer wraparound |
| +0x64 | `write_offset` | confirmed | Lock offset; advanced by locked bytes modulo buffer size |
| +0x68 | `end_of_stream` | confirmed | Selects silence fill (0x80 for 8-bit) and arms the drain-then-Stop path |
| +0x6C | `segment_bytes` | confirmed | Lock size and the busy-window test against the play cursor |
| reader +0x2C | `total_pcm_bytes` | confirmed | Stop threshold once the silent tail has fully played |
| fmt +0x2E | `bits_per_sample` | confirmed | WAVEFORMATEX wBitsPerSample; picks the 0x80 silence byte |

DirectSound vtable slots used: GetCurrentPosition +0x10, Lock +0x2C,
Stop +0x48, Unlock +0x4C (consistent with docs/dynamic_call_site_audit.md).

## Ripple ring float block (batch 22, 0x00445620 / ctor 0x004452F0, 0x4B0 bytes)

The "overlapping particle records" are not a union: the malloc'd block at
owner +0x358 is 300 floats holding 33 seven-float vertices plus parallel
per-vertex arrays.

| Float index | Name | Tier | Evidence |
| --- | --- | --- | --- |
| 0..230 | `vertices[33]` | confirmed | x,y,z,w,diffuse,u,v stride 7; ctor writes w=1.0, u=v=0.5 |
| 232..262 | `radius[31 used]` | confirmed | Grown per frame by the parallel speed entry, fed to Vector2_SetPolar (0x004458B0) |
| 265..295 | `radial_speed[31 used]` | confirmed | Ctor seeds from RNG; update adds speed[i] to radius[i] |
| 297 | `uv_scroll_speed` | confirmed | Added to every u and v each frame with a +1.0 column re-wrap below 0.0 |
| 298 | `uv_scroll_speed_alt` | inferred | Seeded like index 297 by the ctor; consumed by the draw callback LAB_00445880, not by the update |

Vertex 0 is the fan center (owner position +0x334 plus +0x340, full owner
color from +0x2FC); vertices 1..31 are rim points at angles -pi + k*2*pi/32
with the alpha byte cleared; vertex 32 duplicates vertex 1 to close the fan.
Faithful quirk: rim z only ever accumulates the owner z sum and is never
reset by the update.

## Open questions

- `activation_param_a`/`activation_param_b` (+0x1C/+0x20, DAT_00474c70 /
  DAT_00474c98): identify the consumer of these globals to name them properly.
- `title_text`: confirm by finding the function that writes the spell name
  into the record.
- `history_captures` vs `history_attempts`: verify the order of the pair by
  finding the increment sites (attempt++ on declare, capture++ on clear).
- `active_spell_aux` (DAT_004918b4): only ever observed being reset to 0.
- Batch 10 ring `count_a`/`count_b` (+0x1034/+0x1038): distinguish their roles.
