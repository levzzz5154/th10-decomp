#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace th10::midi {struct Channel{std::array<bool,128>notes{};std::uint8_t program{},bank{},volume{},pan{},reverb{},chorus{};};struct Track{std::vector<std::uint8_t>data;std::size_t cursor{};std::uint8_t running_status{};std::uint64_t tick{};bool ended{};};struct State{std::array<Channel,16>channels{};std::int8_t transpose{};std::uint32_t tempo{};std::uint64_t elapsed{};std::vector<std::vector<std::uint8_t>>sysex;};bool ProcessEvent(State&,Track&);}
