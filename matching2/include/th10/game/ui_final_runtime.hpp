#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
namespace th10::ui_final {
// Host-side models of the retail UI-final runtime (0x00409280, 0x00414900,
// 0x00415E90, 0x004236F0, 0x0042E5A0, 0x0042F8B0, 0x00433EF0). Each model keeps the
// retail-grounded subset (loop counts, timer gates, sprite ids, digit bases) and
// explicitly marks the rest 'partial'; no fabricated behavior is presented as
// recovered. 0x0042E5A0 (DrawOptions) is structurally complete: the 12 digit
// draws, the magnitude-based record-flag toggles and the volume/SetVol side
// effects, with the retail globals (byte_491D68/69, dword_491C10, dword_492590,
// the panel parent handle) standing in as OptionsView fields and the recovered
// preload leaf (EffectRuntime_Preload) injectable through OptionsView::preload.
// The `events` vectors are HOST stand-ins for retail side effects that
// have no env here (ANM slot ticks / sub_43DC90 sound ids / sub_449870 registrations).
struct Notice{
  // Full reconstruction of retail 0x00409280 (score-notice queue). Retail
  // layout (a1 offsets): +14132..+14148 the frame ramp (target-1 / counter /
  // float / &flt_476F78 / flags), +14152 the text copy, +14216 the slot id,
  // +14220 the flags word (bits 0-4 = the ramp/notice state, written as
  // (flags & ~0x1B) | 3), +1896/+1900/+1904/+1908 the four ANM handles
  // (sprites 1/72/2 and the 417 rank icon), +14224/+14228 the score pair
  // (10*score*(3*difficulty+10), capped 99999999), +14232 the rank value,
  // +14236..+14244 the boss position copy.
  int frame_target_minus1{-999999},frame_counter{},flags{};float frame_float{};
  const float* frame_delta{};
  int slot{},value{},rank{};
  std::string text;                       // +14152 mirror (strcpy in retail)
  std::array<int,4>handles{};             // +1896/+1900/+1904/+1908
  int score{},score_capped{};             // +14224/+14228
  std::array<float,3>boss_pos{};          // +14236..+14244
  std::array<int,8>animations{};          // legacy host field (sprites 1/72/2 mirror)
};struct NoticeEnv{
  void* manager{};                        // dword_491C10
  void* game_state{};                     // Block (the +16 == 1 gate)
  void* bank_a{};                         // dword_4776E0[8805]/[8807] (sprite banks)
  void* bank_b{};                         // dword_4776F0[1016532] (icon bank)
  void* slot_bank{};                      // dword_47770C[10162] (the 13 slot draws)
  void* player_slot{};                    // dword_477704
  // slot indices: 0-7 = +1912 loop, 8-12 = +9432 loop (stride 940)
  void (*tick_slot)(int,int);             // sub_43E710(bank, slot, id)
  void* (*allocate_object)(void*);        // sub_449950
  void (*init_object)(void*,void*,int);   // sub_449870 (bank, obj, id)
  void* (*find_object)(int);              // AnimationManager_Find
  void (*text_set)(void*,int,const char*);// sub_447AE0(obj, 0xFFFFFF, text)
  void (*queue_sound)(int);               // sub_43DC90(&unk_492590, id, 0)
  void (*register_icon)(int,int,int,void*); // sub_404F30(x, y, slot, bank)
  void (*attach_position)(void*,float*);  // sub_449350(manager, obj, pos, handle)
  void* (*register_text)(void*);          // sub_4489D0(&Format, manager, obj)
};void QueueNotice(Notice&,const NoticeEnv&,int slot,const std::string&,int value);
// Full reconstruction of retail 0x00414900 (stage-front HUD tick). The model
// mirrors the retail manager's relevant state; side effects route through
// FrontEnv (the recovered callees: AnmVm_Tick slot ticks, EffectRuntime_Preload
// sprite draws, AnimationManager_AllocateObject/RegisterObject, the
// sub_43DC90 sound queue, the sub_449870 object init, and the sibling
// sequence tick 0x00415E90). Retail global mapping (a1+...):
//   +40628 flags, +40652 transition timer, +33688[7] position words (stride 470),
//   +31808/+32748 lives-digit words, +40268 rank word, +40263 rank alpha,
//   +40328/+40332 boss position pair, +40580/+40584/+40588 boss gauge,
//   +40484 boss-name id, +40488[10] boss ids + +40592 count, +40632 sequence,
//   +40648 ANM bank, +40640/+40644 lives/graze, +40544..+40556 fade ramp.
struct FrontTick{
  int timer{},mode{};bool extra_mode{},transition{};uint32_t flags{};
  int score{},lives{},graze_disp{};
  std::array<uint16_t,7>position_words{};uint16_t lives_words[2]{};
  uint16_t rank_word{};uint8_t rank_alpha{};
  float boss_pos[2]{};int boss_hp{};float boss_ratio{},boss_disp{};
  std::array<int,10>boss_ids{};int boss_id_count{},boss_name_id{};
  void* sequence{};void* bank{};
  int fade_int{},fade_old{};float fade_acc{},fade_rate{};
};struct FrontEnv{
  void* manager{};void* game_state{};void* player{};void* player_slot{};
  // Slot indices follow the retail visit order: 0-8 = +18816 loop,
  // 9-12 = +27276 loop, 13-14 = +31036 loop, 15 = +32916, 16-20 = the five
  // score-digit slots (+33856 + 940i), 21 = +38556, 22 = +39496.
  int (*tick_slot)(int);                // sub_43EE30 (AnmVm_Tick wrapper)
  int (*preload_sprite)(int, int, void*);  // sub_43E5A0 (EffectRuntime_Preload)
  void* (*allocate_object)(void*);          // sub_449950 (AnimationManager_AllocateObject)
  void (*init_object)(void*,void*,int);     // sub_449870 (AnimationObject_InitializeScriptState)
  void (*queue_sound)(int);                 // sub_43DC90(&unk_492590, id, 0)
  void* (*find_object)(int);                // AnimationManager_Find
  void (*stop_object_tree)(void*,int);      // +772 word write + child walk
  void (*set_flag_tree)(void*,unsigned int); // +860 flag write + child walk
  int (*tick_sequence)(void*);              // sub_415E90 (sibling sequence tick)
};int UpdateFront(FrontTick&,const FrontEnv&);
// 0x00415AE0 - Retail forwarder into the front-HUD update (0x00414900).
int UpdateFrontAlias(FrontTick&,const FrontEnv&);
struct StageSequence{
  // Full reconstruction of retail 0x00415E90 (sequence script opcode walker).
  // Retail layout (a1 offsets): +0 counter, +24/+28/+32 the frame ramp
  // (target-1 / counter / float), +36 -> flt_476F78 (frame-delta pointer),
  // +40 flags, +44/+48 the timer pair, +64..+84 the six ANM handle slots,
  // +92 the script-stream pointer, +96/+108 the two text slots,
  // +120 cooldown, +124 flags byte, +128 text-phase counter, +132 slot
  // selector, +136+4*sel the text param. The opcode stream: count word at
  // +0, opcode byte at +2, length byte at +3, operands from +4; each record
  // advances by 4 + length. Case 0 returns -1 (done); the 0xA pause returns
  // 0 (the caller keeps the sequence); otherwise 0 with the stream at the
  // next record.
  int counter{};              // +0
  int frame_target_minus1{};  // +24 (also the -999999 init state)
  int frame_counter{};        // +28
  float frame_float{};        // +32
  const float* frame_delta{}; // +36 (retail: &flt_476F78)
  int flags{};                // +40 (bit 0 = initialized)
  float timer_value{};        // +44
  int timer_count{};          // +48
  std::array<int,6>handles{}; // +64..+84 (sprite/text slots)
  const unsigned char* script{}; // +92
  std::array<int,2>text_slots{}; // +96/+108
  int cooldown{};             // +120
  uint32_t flag_byte{};       // +124
  int text_phase{};           // +128
  int slot_selector{};        // +132
  int text_param{};           // +136
  std::vector<int>events;     // legacy host field (unused by the reconstruction)
};struct SequenceEnv{
  void* manager{};            // dword_491C10
  void* game_state{};         // dword_4776F4-style arena (unused here)
  // callee hooks (host twins of the retail callees):
  int (*alloc_sprite)(void* bank,int sprite);          // sub_448D00(bank,sprite,15)
  void (*release_handle)(int handle,int opcode);       // sub_409E50(&slot, opcode)
  void (*release_text)(int handle,int opcode);         // sub_40C4D0(&slot, opcode)
  void (*release_other)(int handle,int opcode);        // sub_40C480(&slot, opcode)
  void* (*text_register)(int x,int font,int* handle);  // sub_4497D0(x,font,tmp,&slot)
  void (*text_place)(void* obj,int x);                 // sub_449670/sub_4496A0(obj,x)
  void* (*text_find)(int handle);                      // sub_4491C0(x,manager,handle)
  void (*text_set)(void* obj,int param,const char* s); // sub_447A50(obj,manager,param,s)
  const char* (*string_convert)(const unsigned char*); // sub_417010
  void (*timer_start)(float* t,int v);                 // sub_405410
  void (*timer_step)(float* t,float d);                // sub_44BF40
  void (*frame_advance)(void* ramp);                   // sub_404ED0
  void (*score_add)(int* target,int value);            // sub_409D90
  void (*sound_id)(int id);                            // sub_43DC90(&unk_492590,id,0)
  void (*sound_boss_bgm)(int mode,int arg);            // sub_420B10(mode,arg)
  void (*sound_speed)(float rate);                     // sub_420C30
  void (*anim_register)(int x,int handle,int* slot);   // sub_4492F0(manager,x,slot,handle)
  void (*anim_propagate)(int* handle,int opcode,int n);// sub_449470(&slot,opcode,7)
  void (*stage_clear)(void* a,void* b);                // sub_423370
  int (*clear_done)();                                 // the clear-state check (Block+16==1)
  void (*setup_clear)(int kind);                       // sub_40AC90(&dword_491C28, kind)
  void (*clear_sound)();                               // sub_43C8B0(49,5,120,0,0,0)
  void (*clear_notify)();                              // the 47770C+10157 flag writes
  void (*clear_anim)();                                // sub_4492A0 clear animation
  void (*clear_text)();                                // sub_4175E0(&dword_474C40)
  int* (*notice_counter)();                            // the +1232 table counter (99999 cap)
};int UpdateStageSequence(StageSequence&,const SequenceEnv&);
struct ReplaySaveFlow{int phase{6},timer{},selection{},cursor{};std::array<std::string,25>slots{};std::array<char,9>name{};bool saved{};std::vector<int>events;};int UpdateReplaySave(ReplaySaveFlow&,std::uint32_t input);
struct OptionsView{int music{},sound{},selection{};int parent_handle{};void* manager{};void* sound_context{};int (*preload)(void*,int,void*){};int volume_music{},volume_sound{},volume_pan{};std::array<int,32>sprites{};std::array<int,8>flags{};};void DrawOptions(OptionsView&);
// Full host-side model of retail 0x0042F8B0 (main-menu score/rank draw).
// Retail layout (a1 offsets): +716 the parent record handle (zeroed on every
// resolve failure), +22988..+22996 the five __int16 metrics (score/rank
// digits; the caller writes dwords at +22988/+22992, so +22990/+22994 are the
// high words of those dwords). The body performs 20 sub_43E5A0 digit draws
// (4 per metric: tens /10+51 and ones %10+51 on a base record pair, then both
// again on the base+10 pair), resolving each record retail-style
// (sub_4491C0 find-by-handle + child-list tag walk at +0x38A) and preloading
// via record[+0x308]; the last draw is a tail call whose result is returned.
// `value` is the +22988 metric (host int; retail reads it as __int16 --
// mirrored with a (short) cast in DrawMain); `metric[0..3]` are +22990..+22996.
// dword_491C10 -> manager, *(a1+716) -> parent_handle, sub_43E5A0
// (EffectRuntime_Preload) -> preload.
struct MainView{
  int selection{};        // host field (menu selection)
  int value{};            // +22988 metric (test-visible alias)
  int difficulty{};       // host field
  short metric[4];        // +22990..+22996 (the other four __int16 metrics)
  int parent_handle{};    // +716 (parent record handle; zeroed on resolve failure)
  void* manager{};        // dword_491C10 (animation manager)
  int (*preload)(void*,int,void*){};  // sub_43E5A0 (EffectRuntime_Preload)
  std::array<int,32>sprites{};
};int DrawMain(MainView&);
// Callback surface for the retail side effects of 0x00433EF0. The callback
// arguments deliberately use the retail values (ANM sprite id, text colour,
// depth, position, and sound id), while the manager/bank pointers let a host
// bind them to the real animation manager without exposing its object layout.
struct MusicRoom;
struct MusicRoomEnv{
  void* manager{};                         // dword_491C10
  const float* frame_delta{};              // flt_476F78
  void* animation_bank{};                  // music-room object +0x14
  void* frame_bank{};                      // dword_491FEC (text.anm)
  void* fallback_bank{};                   // dword_4776E0 + 0x8994
  int (*register_anm)(void*,void*,int){};  // alloc/init/register, type 15
  int (*resolve_anm)(void*,int){};         // sub_4491C0; non-zero means live
  void (*draw_text)(void*,int,unsigned,const char*){}; // sub_447A50
  void (*set_depth)(void*,int,int){};      // +0x304, including children
  void (*set_visible)(void*,int,bool){};   // +0x35C bit 1, including children
  // Position sink for an already-resolved object. This is deliberately a
  // narrow host callback: sub_434A80 also chooses between an immediate write
  // and an existing-object ramp, so this callback is not that ramp unless the
  // host implements the resolved-object/ramp state behind it.
  void (*set_position)(void*,int,float,float,float){};
  // Optional resolved-object position read and the sub_434A80 ramp sink.
  // The retail selection-change path uses an immediate write when the
  // existing Y differs by at least 40, and otherwise installs a four-frame
  // position ramp. Hosts that do not expose object position can retain the
  // immediate set_position fallback without claiming to model that choice.
  bool (*get_position_y)(void*,int,float*){};
  void (*set_position_ramp)(void*,int,float,float,float){};
  // sub_409E50 marks an object tree at depth 1; it does not release the ANM.
  void (*stop_anm)(void*,int){};
  void (*play_sound)(int){};               // sub_43DC90(&DAT_00492590,id,0)
  void (*dummy_state)(int){};              // sub_43E460("dummy", mode, 0)
  bool dummy_mode4{};                      // (byte)dword_491D78 & 0x10
  void (*play_music)(int,const char*){};   // sub_420A90(0,title)
  void (*restore_bgm)(const char*){};      // sub_420A90(0,"bgm/th10_02.wav")
  void (*set_bgm_state)(int,int){};        // sub_420B10(0,0)
  const char* (*preview_text)(int){};      // off_476FD8[frame], encoded text
  // sub_44BE70 receives the music-room history object (the retail call passes
  // this+0x24), not the animation manager.
  void (*history_pop)(MusicRoom&){};
  // dword_47783C + 0x1D892 is the retail played table. Row/preview queries
  // receive the row index; the retail playback write receives the literal
  // table index emitted by 0x00433EF0 (zero in the recovered instruction).
  bool (*is_track_played)(int){};
  void (*mark_track_played)(int){};
  bool resource_available{true};          // host result of sub_44B360
};
// Host model of retail 0x00433EF0. State fields mirror the retail offsets:
// +28 substate, +32 phase, +36 selection, +40 previous selection,
// +44 parsed track count, +692 timer, +1636 eight frame handles, +1556 row
// handles, +1672 parsed record count, +1676 frame cursor, +1680 displayed
// selection, +1684 preview-armed flag, +1688 titles, +3736 comments,
// +5848 eight row strings per track, +22744 scroll, and +23212 the owned
// musiccmt.txt buffer. `rows` retains the sprite ids for the older host API;
// `row_handles` is the corresponding retail +1556 handle array.
struct MusicRoom{
  int phase{},timer{},selection{},previous_selection{},track_count{},scroll{};
  int ramp_target_minus1{-999999};     // +688 (retail reset mirror)
  int ramp_counter{};                   // +692 (retail timer mirror)
  float ramp_value{};                   // +696 (retail reset mirror)
  const float* ramp_delta{};            // +700 (retail reset mirror)
  std::uint32_t ramp_flags{};           // +704 flag word mirror
  int substate{};                       // +28 (sub_42C5C0 writes 2 here)
  bool loaded{},played{},armed{};        // played mirrors selected global byte; armed = +1684
  int displayed{};                       // +1680
  int draw_cursor{};                     // +1676
  int parent_handle{};                   // +0x440 (ANM sprite 95)
  int fallback_handle{};                 // +0x5D0 (sprite 8)
  int auxiliary_handle{};                // +0x460 (ANM sprite 103)
  void* file_buffer{};                   // +23212
  void* animation_bank{};                // +0x14, used by sub_42C670 and row ANMs
  std::array<int,104>anm_handles{};      // +0x2C4 + 4*sprite for 0..103
  std::array<int,8>frame_handles{};      // +1636, sprites 39..46
  std::vector<std::uint8_t>played_tracks; // dword_47783C+0x1D892+selection
  std::vector<std::string>titles;        // +1688, stride 64
  std::vector<std::string>comments;      // +3736, stride 66
  std::vector<std::string>row_texts;     // +5848, track*8, stride 66
  std::vector<int>events;                // legacy no-env side-effect trace
  std::vector<int>rows;                  // legacy sprite ids (173+v19)
  std::vector<int>row_handles;           // +1556, one handle per parsed row
  // sub_44BE70 decrements this cursor (clamping at zero) and reads the
  // corresponding +12/+76 history pair; it does not erase the backing table.
  // -1 is the host sentinel for a table whose current cursor is its last row.
  int history_cursor{-1};
  std::vector<std::pair<int,int>>history; // +12/+76 history entries for sub_44BE70
};
int UpdateMusicRoom(MusicRoom&,const MusicRoomEnv&,std::uint32_t input,
                    const std::string&resource);
// Compatibility entry point for existing host callers. With no callbacks it
// retains the historical registration trace in `events`.
int UpdateMusicRoom(MusicRoom&,std::uint32_t input,const std::string&resource);
}
