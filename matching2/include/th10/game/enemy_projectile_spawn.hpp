#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::enemy_projectile {
struct SpawnDescriptor {float x{},y{},z{},spacing{},speed0{},speed1{};std::uint16_t type{},variant{},rows{},columns{},layout{};std::uint8_t parity_flags{};std::uint32_t flags{},payload_tag{},payload_value{};std::array<std::uint32_t,108> payload{};};
struct SpawnSlot {bool active{};std::uint16_t state{},type{},variant{};float x{},y{},z{},angle{},speed{};std::uint32_t flags{},animation{},color{},payload_tag{},payload_value{};std::array<std::uint32_t,108> payload{};};
struct SpawnPool {std::vector<SpawnSlot> slots;std::size_t cursor{};};
struct SpawnEdges {float(*random_symmetric)(void*,float){};void* random_context{};void(*initialize_motion)(SpawnSlot&){};void(*publish)(SpawnSlot&){};};
// Retail 0x004067D0. False only if the bounded 2000-slot scan finds no free record.
bool EnemyProjectile_SpawnOne(SpawnPool&,const SpawnDescriptor&,unsigned column,int row,float base_angle,const SpawnEdges&);
}
