#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::player_front {

// Retail 0x004250B0's slice of the player object. The retail byte offset is
// named beside every field; positions are hundredths of a screen pixel, which
// is how retail stores and clamps them.
struct Player {
    int direction{};    // +1108, the 0..8 direction code
    int vx{}, vy{};     // +1008 / +1012, this frame's scaled step
    int prev_vx{};      // +1100, last frame's horizontal step
    int prev_vy{};      // +1104, last frame's vertical step
    int slow{};         // +17524, focus flag
    int slow_age{30};   // +17160, frames since focus was released
    int x{};            // +972, hundredths, 0 is the playfield centre
    int y{40000};       // +976, hundredths; retail spawns the player at 400.0
    int shot_handle{};  // +12956
    int trail_count{};
    std::array<std::array<int, 2>, 32> trail{};  // +17260, hundredths pairs
};

// The four speeds retail reads out of the player object, all hundredths of a
// pixel per frame. 0x00426520 fills the .sht image they are copied from:
// the two diagonal entries are the straight ones scaled by sin(pi/4).
struct PlayerSpeeds {
    int straight{};        // +980, from .sht float 4
    int focus_straight{};  // +984, from .sht float 5
    int diagonal{};        // +988, .sht float 6 = float 4 * sin(pi/4)
    int focus_diagonal{};  // +992, .sht float 7 = float 5 * sin(pi/4)
    float frame_scale{1.0f};  // flt_476F78, the global frame-rate scale
};

struct PlayerEdges {
    void* context{};
    // 0x0043E710 on the player's own ANM VM. Retail sends 1 when the player
    // starts moving left, 3 when it starts moving right, and 2 / 4 when it
    // stops doing either.
    void (*direction_changed)(void* context, int interrupt){};
};

// 0x004250B0 - one frame of player motion. `input` is retail's key word
// (dword_474E5C: 0x10 up, 0x20 down, 0x40 left, 0x80 right, 0x04 focus),
// `shot_index` is retail's 3 * character + weapon selector, and
// `control_enabled` is the "player accepts input" precondition.
void UpdatePlayer(Player&, std::uint32_t input, bool control_enabled,
                  int shot_index, const PlayerSpeeds&, const PlayerEdges&);

struct Front{bool update_task{},draw_task{};std::array<bool,9>lives{};std::array<int,3>digits{};std::vector<int>animations;int linked_a{},linked_b{};};struct FrontInput{int lives{},counter{},mode{},stage{},difficulty{};bool special{},extra_overlay{},stage_one_clear{};};void InitializeFront(Front&,const FrontInput&);}
