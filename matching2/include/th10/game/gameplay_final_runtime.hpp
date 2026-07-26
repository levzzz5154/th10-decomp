#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::gameplay_final {struct Item{int state{},type{},timer{};float x{},y{},z{},vx{},vy{},vz{};bool active{};};struct ItemPool{std::vector<Item>items;int active{},collected{};};int UpdateItems(ItemPool&,float player_x,float player_y,float speed,int difficulty);
struct PlayerRuntime{int state{},timer{},invulnerable{},lives{},bombs{},power{},score{};float x{},y{};std::array<int,4>effect_handles{};std::vector<int>events;};int UpdatePlayerState(PlayerRuntime&,std::uint32_t input);
struct AttachedEffects{int counter{},difficulty{},shot{};std::array<int,4>handles{};std::array<int,4>states{};std::vector<int>events;};void UpdateAttachedEffects(AttachedEffects&,int global_counter);
}
