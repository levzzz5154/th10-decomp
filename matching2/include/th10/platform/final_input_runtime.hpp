#pragma once
#include <array>
#include <cstdint>
namespace th10::input_final {struct State{std::uint16_t current{},previous{},pressed{},released{},repeat{};std::array<std::uint16_t,16>held{};};std::uint16_t Poll(State&,const std::array<std::uint8_t,256>&keys,const std::array<int,16>&mapping,std::uint16_t joystick,bool enabled);}
