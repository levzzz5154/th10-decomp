#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::player_front {struct Player{int direction{},vx{},vy{},slow{},slow_age{30},x{},y{},shot_handle{},trail_count{};std::array<std::array<int,2>,32>trail{};};struct PlayerEdges{void*context{};int(*random)(void*){};void(*direction_changed)(void*){};};void UpdatePlayer(Player&,std::uint32_t input,bool control_enabled,int speed,int slow_speed,const PlayerEdges&);
struct Front{bool update_task{},draw_task{};std::array<bool,9>lives{};std::array<int,3>digits{};std::vector<int>animations;int linked_a{},linked_b{};};struct FrontInput{int lives{},counter{},mode{},stage{},difficulty{};bool special{},extra_overlay{},stage_one_clear{};};void InitializeFront(Front&,const FrontInput&);}
