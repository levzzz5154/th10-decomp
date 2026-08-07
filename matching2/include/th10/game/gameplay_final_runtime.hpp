#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "th10/math/timer.hpp"
namespace th10::gameplay_final {
// Env channel for the retail item sweep 0x0041AFD0 (sub_41AFD0). Each field
// names its retail global or player-record slot; player slots are float
// indices into dword_477834 (slot*4 = byte offset, e.g. slot 4297 = +0x4324).
struct ItemEnv {
    float player_x{}, player_y{};          // retail dword_477834 + 960/+964 (item-visible player pos)
    int player_state{};                    // retail dword_477834 + 1112 (player state field)
    float magnet_speed{};                  // retail dword_477834 + 1124 (player magnet speed source)
    bool focus{};                          // retail (dword_474E5C & 4) != 0 (focus key selects magnet rect)
    bool force_magnet{};                   // retail *((_DWORD*)dword_4776EC + 10) != 0 (skips gravity fall)
    float frame_delta{};                   // retail flt_476F78 (frame delta)
    float collect_l{}, collect_t{}, collect_r{}, collect_b{};  // retail slots 4297-4301 (contact collect rect)
    float magnet_l{}, magnet_t{}, magnet_r{}, magnet_b{};      // retail slots 4309-4313 (unfocused magnet rect)
    float focus_l{}, focus_t{}, focus_r{}, focus_b{};          // retail slots 4303-4307 (focused magnet rect)
    int power{};                           // retail word_474C48 (power gauge)
    int item_value{};                      // retail dword_474C4C (point-item base)
    int point_value{};                     // retail dword_474C74 (0/1->5000, 2->8000, 3/4->10000)
    bool roll_big{};                       // host stand-in for sub_418930's per-item roll (types 1/0xA/4/0xB)
    long long score{};                     // sub_409D90 + sub_41BE80 score accumulation (persists across calls)
    int score_texts{}, sounds{}, effects{}, power_draws{};     // sub_42B9C0 / sub_43DD10 / sub_426F70 / sub_4054B0
    int timers{}, delays{}, spell_hits{}, spawns{};            // sub_405B60 / sub_412FF0 / sub_4188A0 / sub_404F30
    int anm_updates{};                     // sub_43EE30 calls (LABEL_83)
    int limit_hits{};                      // v41 (power >= 100 on collect); reset per call; fires sub_41BA50
};
struct Item {
    int state{};             // retail record +44 (item state machine)
    int type{};              // retail record +48 (collect effect type)
    int timer{};             // host-side only (retail has no per-item frame counter)
    float x{}, y{}, z{};     // retail record +0/+4/+8
    float vx{}, vy{}, vz{};  // retail record +12/+16/+20
    int anim_prev{}, anim_frame{};         // retail record +24/+28
    float anim_accum{};      // retail record +32
    float anim_rate{1.0f};   // host stand-in for the external rate pointer at retail record +36
    float magnet_speed{};    // retail record +56 (magnet speed, ramps +0.2/frame while < 12.0)
    int countdown{};         // retail record +60 (state-5 spawner countdown)
    bool active{};           // host: retail state != 0 (retail "state = 0" writes map to active = false)
};
struct ItemPool {
    std::vector<Item> items;  // retail: 2198 fixed records, stride 1008, first at a1+964
    int active{};             // retail a1+2215604: per-call count of LABEL_83 (still-active) items
    int collected{};          // host-side count of contact collections (retail LABEL_69 path)
};
int UpdateItems(ItemPool&, ItemEnv&);

// One of the four familiar records rebuilt by 0x00426F70. The integer
// positions are the fixed-point values at +0x32D4/+0x32D8 and their previous
// values at +0x32DC/+0x32E0. `random` is the four-word offset block at
// +0x32E4..+0x32F0; keeping it makes the focus/non-focus branches observable.
struct FamiliarSlot {
    int mode{};                       // +0x32A0, 0 = released, 2 = active
    int position_x{}, position_y{};   // +0x32D4/+0x32D8
    int previous_x{}, previous_y{};   // +0x32DC/+0x32E0
    std::array<int,4> random{};       // +0x32E4..+0x32F0
    int handle{};                     // +0x3308
    int index{};                       // +0x3328
    int callback_kind{};              // 0, 1 (0x427950), or 2 (0x427AD0)
    int script{};                      // 0x11, 0x12, or 0x13
    std::uint32_t animation_flags{};  // ANM object +0x35C |= 0x40000000
};

// Host representation of one logical retail indicator record at player
// +0x350C. Retail stride is 0x6C, but this host shape is deliberately not a
// native overlay: +0x50 is a retail pointer and C++ pointer size/alignment can
// change the host stride. Scalar names retain the exact offsets used by the
// 0x00425730 tail and by 0x00427B50's allocator.
struct PlayerIndicatorSlot {
    float position_x{};                  // +0x00, tail adds motion_x
    float position_delta_x{};            // +0x04, tail input to position_x
    float position_y{};                  // +0x08, tail adds motion_y
    float position_delta_y{};            // +0x0C, tail input to position_y
    float field_10{};                    // +0x10, not changed by this tail
    float field_14{};                    // +0x14, not changed by this tail
    float motion_x{};                    // +0x18, 0x44C2A0 output
    float motion_y{};                    // +0x1C, 0x44C2A0 output
    float motion_z{};                    // +0x20, 0x44C2A0 output
    float velocity_x{};                  // +0x24, 0x44C2A0 input
    float velocity_y{};                  // +0x28, 0x44C2A0 input
    float velocity_z{};                  // +0x2C, 0x44C2A0 input
    float angle_step{};                  // +0x30, linear radius / polar angle step
    float angle{};                       // +0x34, polar angle
    float radius{};                      // +0x38, polar radius / linear z input
    float radius_step{};                 // +0x3C, polar radius increment / linear z step
    std::uint32_t motion_flags{};        // +0x40, bit 0 selects 0x44C2A0 polar mode
    int timer_previous{};                // +0x44, tail copies timer_current here
    int timer_current{};                 // +0x48, tail writes __ftol2 result
    float timer_fraction{};              // +0x4C, countdown float image
    const float* timer_speed{};          // +0x50, retail pointer to frame delta
    std::uint32_t timer_flags{};         // +0x54, allocator-zeroed word
    std::uint32_t allocator_value{};     // +0x58, 0x00427B50 argument 7
    std::uint32_t allocator_counter{};   // +0x5C, allocator initializes 0
    int allocator_limit{};               // +0x60, allocator initializes 999999
    int allocator_phase{};               // +0x64, allocator initializes 4
    std::uint32_t flags{};               // +0x68, bit 0 is retail in-use
};

// Host state for the retail pool at player +0x350C. The array stores logical
// records; it intentionally does not promise a native 0x6C C++ stride.
struct PlayerIndicatorPool {
    std::array<PlayerIndicatorSlot,32> slots{};
};

// Host inputs and observable hooks for the formation half of 0x00426F70.
// The retail source positions and entry history are fixed-point words owned by
// the player record; these arrays provide those exact values to the readable
// model without pretending to own the animation manager.
struct FamiliarFormationInputs {
    bool focus{};                              // player +0x4474
    int source_x{};                            // player +0x3CC
    int source_y{};                            // player +0x3D0
    std::array<std::array<int,2>,4> player_positions{}; // +0x43AC/+0x43B0
    std::array<std::array<int,2>,4> defaults{};          // +0x324C/+0x3250
    std::array<int,66> history{};              // +0x436C entry trail
    // Scaled fixed-point pairs read from the player difficulty table at
    // +0x45C (the retail dword_476F7C level/index selection). Pair A is the
    // +0x20 source and pair B is the +0x98 source. They are per familiar slot
    // after applying the retail level offset, so no native table pointer is
    // required in the host model.
    bool table_offsets_valid{};
    std::array<std::array<int,2>,4> table_pair_a{};
    std::array<std::array<int,2>,4> table_pair_b{};
    std::array<int,4> random_values{};         // deterministic fallback only
    std::uint32_t (*random_word)(){};          // fallback channel when table data is absent
    int (*create_animation)(int slot, int script){}; // 0x449950/0x449870/0x4489D0
    // Exact creation contract: layer 0x0F and the freshly allocated VM's
    // 0x40000000 flag are manager-owned side effects.
    int (*create_animation_ex)(int slot, int script, int layer,
                               std::uint32_t animation_flags){};
    void (*set_callback)(int slot, int callback_kind){}; // pointer write at +0x3330
    void (*focus_init)(int slot){};            // 0x449470, d=1/shot2 focused path
    std::vector<int> callback_order{};         // host trace: callback/create/focus order
};

// Host model of the retail player record (dword_477834). Member comments name
// the retail dword index (a3[N] = +N*4 bytes) as used by 0x00425730.
struct PlayerRuntime {
    int state{};              // a3[278]  (+1112) state machine: 0 entry, 1 play, 2->4, 3 clear, 4 death
    int timer{};              // a3[286]  (+1144) per-state frame counter, advanced at the tail
    int timer_prev{};         // a3[285]  (+1140) last frame's timer. RETAIL ALIASES this dword
                              //   with float slot +285 (sub_405410's 60-frame small invuln);
                              //   the host keeps the two faces separate (small_invuln below).
    float timer_frac{};       // float a3[287] (+1148) fractional timer accumulator
    int timer_flags{};        // a3[289]  (+1156) bit0: scale pointer initialized (retail a3[288] = &flt_476F78)
    EmbeddedTimerState state_timer{}; // typed mirror of a3[285..289]
    float state_timer_speed{1.0f};
    int small_invuln{};       // float slot +285 (retail aliases timer_prev; 60 on focus drain, 0 on respawn)
    int invulnerable{};       // a3[4292] (+17168) main invuln countdown (270/200/280; float slot +4291 mirrors it)
    float invuln_frac{};      // float a3[4293] (+17172) invuln fractional accumulator
    EmbeddedTimerState invulnerability_timer{}; // typed mirror of a3[4291..4295]
    float invulnerability_timer_speed{1.0f};
    bool blink{};             // a3[220] bit15 (+880): invuln blink flag
    int flash_color{};        // a3[197]  (+788): 0xFF0000FF while blinking
    int hold_timer{};         // a3[281]  (+1124) hold timer (retail LABEL_115 / sub_4281D0)
    int hold_timer_prev{};    // a3[280]  (+1120)
    float hold_timer_frac{};  // float a3[282] (+1128)
    int hold_flags{};         // a3[284]  (+1136) bit0: scale pointer initialized (retail a3[283] = &flt_476F78)
    EmbeddedTimerState hold_timer_state{}; // typed mirror of a3[280..284]
    float hold_timer_speed{1.0f};
    int spawn_count{};        // a3[3392] (+13568) entry-history ring counter; the case-0 copy gate
                              //   is 8*count >= 32 (retail: if (8*a3[3392] >= 32) goto LABEL_6)
    int field_3393{};         // a3[3393] (+13572) cleared in retail LABEL_115
    std::uint8_t byte_13576{};// +13576 cleared in retail LABEL_115
    int fx{};                 // a3[243]  (+972) fixed-point x (entry/respawn)
    int y{};                  // a3[244]  (+976) fixed-point y; entry motion y = 48000 - 8000*timer/60
    float px{}, py{}, pz{};   // float a3[240..242] (+960/+964/+968) live position (written by sub_4250B0 in retail)
    float px_prev{}, py_prev{}, pz_prev{};  // float a3[272..274] (+1088..) position snap at respawn
    std::array<float,3> size_a{};  // float a3[263..265] (+1052..) half-extent A (rect_off)
    std::array<float,3> size_b{};  // float a3[266..268] (+1064..) extent B (rect_outer / rect_magnet)
    std::array<float,3> size_c{};  // float a3[269..271] (+1076..) extent C (rect_focus)
    std::array<float,6> rect_off{};    // float a3[257..262]  pos +/- A
    std::array<float,6> rect_outer{};  // float a3[4297..4302] pos +/- B/2
    std::array<float,6> rect_focus{};  // float a3[4303..4308] pos +/- C
    std::array<float,6> rect_magnet{}; // float a3[4309..4314] pos +/- B
    std::array<int,66> history{};      // a3[4315..4380] entry-trail position history (33 pairs)
    std::array<int,8> ring{};          // a3[17260..17267] history ring (retail stride 64B at +17260;
                                       //   only the pair at +0/+4 is consumed; written elsewhere in retail)
    std::array<int,4> familiar_levels{}; // +0x332C/+0x33C4/+0x345C/+0x34F4
    PlayerIndicatorPool indicators{};    // +0x350C, 32 logical retail records (retail stride 0x6C)
    float indicator_frame_delta{1.0f};    // host storage for indicator +0x50 speed pointer
    EmbeddedTimerState auxiliary_timer{}; // +0x488..+0x498, third tail timer
    float auxiliary_timer_fraction{};    // float image at +0x490
    float auxiliary_frame_delta{1.0f};   // host-owned speed for auxiliary_timer
    // host-only channels (no retail counterpart at these offsets):
    int lives{}, bombs{}, score{};  // unused by retail 0x00425730 (kept for host callers)
    int power{};                    // word_474C48 (absolute gauge; 20 units = 1.00 power)
    std::array<int,4> effect_handles{};
    std::vector<int> events;
};
// Env channel for the retail player-state runtime 0x00425730 (sub_425730). Each
// field names its retail global; the function-pointer hooks name the retail
// callee and may stay 0 (then the call is skipped; the harness wires counters).
struct PlayerStateEnv {
    float frame_delta{1.0f};   // flt_476F78 (frame delta; retail scale pointers a3[288]/a3[293] point at it)
    bool player_present{true}; // retail *((_DWORD*)dword_47770C + 10158) == 0 (player record alive)
    bool focus_object{true};   // retail dword_4776EC != 0 && *((_DWORD*)dword_4776EC + 10) == 0
    bool hold_enabled{true};   // retail dword_477704 != 0 && *((_DWORD*)dword_477704 + 24) != 0
    bool can_respawn{true};    // retail dword_474C70 >= 0 (case-4 t>=30 route)
    int game_over_flag{};      // retail *((_DWORD*)Block + 4) == 1 (continue screen route)
    int frame_counter{};       // retail dword_474C98 (+1 every 60 frames, clamped to [-1024, 1024])
    void (*move)(PlayerRuntime&, std::uint32_t input);      // sub_4250B0 (host twin: player_front_runtime.cpp::UpdatePlayer)
    void (*attached_effects)(PlayerRuntime&);               // sub_426F70
    void (*hitbox_update)(PlayerRuntime&);                  // sub_4269D0 (case 4, timer >= 8)
    void (*sweep_enemy)(int entry_y, int index);            // sub_408030 (2000 candidates, cases 0/1/3)
    void (*clear_bullets)(int mode);                        // case 0/1 list walk (0) / sub_41C850 (1)
    void (*entry_effect)(float radius, int mode);           // sub_408100 (case 0, t < 30; modes 1/0)
    void (*entry_effect_ex)(float radius, int origin, int mode); // exact (radius, 0, mode)
    void (*entry_bullets)(float radius);                    // sub_41C800 (case 0, t < 30)
    void (*entry_bullets_ex)(float radius, int origin);      // exact (radius, 0)
    void (*respawn_effect)(PlayerRuntime&);                 // sub_427B50 (case-4 respawn)
    void (*respawn_effect_ex)(const float position[3], float width,
                              float height, int frames, int mode);
    float (*fan_angle)(PlayerRuntime&);                     // sub_426610 (death-fan base angle)
    float (*fan_angle_ex)(const float point[3], const PlayerRuntime&);
    void (*death_fan)(int type, float angle);               // sub_41BB00 x7 (LABEL_46, t == 3)
    void (*death_fan_ex)(const float position[3], int type,
                         std::uint32_t color, float angle, float speed);
    void (*power_hud)(int level, int frac);                 // sub_4054B0
    void (*bonus_timer)(int value);                         // sub_412E70 (3000)
    void (*focus_drain)();                                  // sub_405860
    void (*anm_tick)(PlayerRuntime&);                       // sub_43EE30 (player sprite ANM, a3+5)
    void (*hold_update)(PlayerRuntime&);                    // sub_4281D0
    void (*tail_update)(PlayerRuntime&);                    // sub_428280
    void (*game_over)();                                    // sub_40AC90 (continue screen)
    void (*game_over_ex)(int mode);                         // exact sub_40AC90(4)
    void (*stage_start)();                                  // sub_4231D0 (stage restart)
};
int UpdatePlayerState(PlayerRuntime&, std::uint32_t input, PlayerStateEnv* env = nullptr);
// 0x00426500 - Retail forwarder into the player state runtime (0x00425730).
int UpdatePlayerStateAlias(PlayerRuntime&, std::uint32_t input);
struct AttachedEffects {
    int counter{}, difficulty{}, shot{};
    std::array<int,4> handles{};
    std::array<std::uint16_t,4> frame_states{}; // low path record +0x304 (16-bit retail write)
    std::array<std::uint32_t,4> animation_flags{}; // high path ANM +0x35C flags
    std::vector<int> events;
    // The second retail sweep is the four familiar records at +0x32A0.
    std::array<FamiliarSlot,4> familiar_slots{};
    int familiar_count{};                 // player +0x3500, current level
    std::array<int,4> familiar_levels{};  // +0x332C/+0x33C4/+0x345C/+0x34F4
    FamiliarFormationInputs formation{};
    bool formation_partial{};              // set when external ANM/random hooks are absent
    bool manager_partial{};                 // set when ANM-list membership/chain hooks are absent
    // Retail 0x00426F70 env hooks: flag_linked fires per swept record whose
    // linked chain gets the +860 flag; refetch_sprite replaces an effect slot
    // through sub_448E30. `create_animation`/`set_callback` and the formation
    // arrays expose the previously omitted familiar side effects.
    void (*flag_linked)(int handle){};   // high-path +0x35C flag/link walk
    void (*frame_linked)(int handle){};  // low-path +0x304 frame/link walk
    bool (*handle_live)(int handle){}; // host stand-in for the two retail ANM lists
    int (*refetch_sprite)(int sprite_id){};
    int (*refetch_animation)(int slot, int sprite_id, int layer){};
};
void UpdateAttachedEffects(AttachedEffects&, int global_counter);
}
