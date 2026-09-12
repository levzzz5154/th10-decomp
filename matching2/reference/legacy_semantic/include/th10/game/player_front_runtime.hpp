#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::player_front {
struct Player {
    int direction{}, vx{}, vy{}, slow{}, slow_age{30}, x{}, y{}, shot_handle{},
        trail_count{};
    int sprite_handle{};
    // The retail routine keeps the previous components at +0x44c/+0x450.
    // Keep these after the preexisting sprite handle so positional host
    // initializers retain their earlier field order.
    int previous_vx{}, previous_vy{};
    float x_f{}, y_f{};
    std::array<std::array<int, 2>, 32> trail{};
};

// Retail has four speed slots: +0x3d4/+0x3d8 for normal/slow cardinal
// movement and +0x3dc/+0x3e0 for normal/slow diagonal movement.
struct PlayerSpeedSlots {
    int normal_cardinal{};
    int slow_cardinal{};
    int normal_diagonal{};
    int slow_diagonal{};
};

struct PlayerEdges {
    void* context{};
    int (*random)(void*){};
    void (*direction_changed)(void*){};
    void (*sprite_create)(void*){};
    void (*sprite_release)(void*){};
    // Retail calls sub_4492F0 after each valid sprite-handle check. The
    // callback receives the rendered position (+224,+16), which is the
    // useful part of that otherwise host-specific animation call.
    void (*sprite_position)(void*, float, float){};
};

// The selection gate is the retail condition 3*dword_474C68+dword_474C6C==5.
// When it is false, retail leaves slow_age unchanged while the playable gate
// remains active; when control_enabled is false it resets slow_age to 30.
void UpdatePlayer(Player&, std::uint32_t input, bool control_enabled,
                  const PlayerSpeedSlots&, const PlayerEdges&,
                  bool slow_age_selection_gate = true);

// Compatibility entry point for existing host callers. It intentionally
// supplies the same magnitude to all four retail slots; callers needing the
// retail data contract should use PlayerSpeedSlots above.
void UpdatePlayer(Player&, std::uint32_t input, bool control_enabled,
                  int speed, int slow_speed, const PlayerEdges&);
struct Front{bool update_task{},draw_task{};std::array<bool,9>lives{};std::array<int,3>digits{};std::vector<int>animations;int linked_a{},linked_b{};};struct FrontInput{int lives{},counter{},mode{},stage{},difficulty{};bool special{},extra_overlay{},stage_one_clear{};};
// Slot-draw bridge for the retail 0x00413BC0 ANM slot draws (the
// (a2+876)&1-gated sub_43E710 loops: sprites 10..19 at +16, 20..29 at
// +9416, 30..38 at +18816, 47..50 at +27276, 80..81 at +31036, 51..57 at
// +32916 - 42 draws, stride 940) and the three sub_43E5A0 power-digit
// preloads (+27276/+29156/+30096).  Slot indices follow the retail visit
// order (0-9 = +16, 10-19 = +9416, 20-28 = +18816, 29-32 = +27276,
// 33-34 = +31036, 35-41 = +32916).  Null hooks = the draws are not wired
// (the model's mirrors stay authoritative for the tests).
struct FrontDrawEnv{
  int flags{};      // retail a2+876 (bit 0 clear = the slot draws run)
  void* bank{};     // retail a2+40648 (the ANM bank for the draws)
  void (*tick_slot)(int slot_index,int sprite_id){};  // sub_43E710
  void (*preload)(int byte_offset,int sprite,void* bank){};  // sub_43E5A0
};
void InitializeFront(Front&,const FrontInput&,const FrontDrawEnv& env={});}
