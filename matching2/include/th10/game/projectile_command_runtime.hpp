#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::projectile_commands {struct Command{std::uint32_t opcode{};std::array<float,10>a{};};struct State{int cursor{};std::uint32_t flags{};float angle{},speed{},accel{},target_speed{},scale{},duration{},spawn_x{},spawn_y{},spawn_z{};int sound{-1},spawn_count{},effect_count{};};struct Edges{void*context{};void(*event)(void*,std::uint32_t,const Command&){};};void Apply(State&,const std::vector<Command>&,const Edges&);}
