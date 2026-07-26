#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
namespace th10::script_final {struct Instruction{std::uint16_t opcode{};std::array<float,8>f{};std::array<int,8>i{};std::string text;};struct EntityVm{int time{},cursor{},wait{},result{};std::array<float,16>fv{};std::array<int,16>iv{};std::uint32_t flags{};std::vector<int>events;};int TickEntityVm(EntityVm&,const std::vector<Instruction>&);
struct ParseState{std::vector<std::string>tokens;std::vector<Instruction>instructions;std::vector<std::string>errors;};bool ParseScript(ParseState&,const std::string&);
struct EclState{std::uint16_t opcode{};std::array<float,16>f{};std::array<int,16>i{};std::array<std::uint8_t,256>buffer{};std::uint32_t flags{};std::vector<int>events;};int ExecuteEcl(EclState&);}
