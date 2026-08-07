#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::player_front {struct Player{int direction{},vx{},vy{},slow{},slow_age{30},x{},y{},shot_handle{},trail_count{};int sprite_handle{};float x_f{},y_f{};std::array<std::array<int,2>,32>trail{};};
struct PlayerEdges{void*context{};int(*random)(void*){};void(*direction_changed)(void*){};void(*sprite_create)(void*){};void(*sprite_release)(void*){};};
void UpdatePlayer(Player&,std::uint32_t input,bool control_enabled,int speed,int slow_speed,const PlayerEdges&);
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
