#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
namespace th10::replay_large {struct StageBlob{bool present{};std::vector<std::uint8_t>header,commands,tail;};struct Replay{std::array<char,9>name{};std::array<StageBlob,8>stages{};int rank{},character{},score{};float slow_rate{};std::int64_t timestamp{};};struct Serialized{std::vector<std::uint8_t>header,compressed,user_text,user_notice;};Serialized Serialize(Replay&,const std::string&name);
struct InputMenu{int phase{},timer{},axis{},selection{},page{},page_count{},repeat{};std::array<std::uint8_t,256>previous{},current{},pressed{};};struct InputEdges{void*context{};bool(*poll)(void*,std::array<std::uint8_t,256>&){};void(*event)(void*,int){};};int UpdateInputMenu(InputMenu&,std::uint32_t keys,const InputEdges&);}
