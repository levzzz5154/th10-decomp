#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
namespace th10::replay_menu {
struct ReplaySummary{std::array<int,7> stage_present{};std::string player_name;int character{},shot{},difficulty{};};
struct ReplayMenuState{int phase{},timer{},selection{},previous_selection{},chosen_slot{},chosen_stage{},stage_count{};std::array<ReplaySummary*,50> slots{};std::array<int,7> available_stages{};};
struct ReplayMenuEdges{std::vector<std::string>(*enumerate_user_files)(void*){};void* context{};ReplaySummary*(*load)(void*,const std::string&){};void(*release)(void*,ReplaySummary*){};void(*transition)(void*,int){};void(*sound)(void*,int){};void(*start_replay)(void*,const ReplaySummary&,int,int){};};
// Retail 0x004315C0: replay loading, browsing, stage selection, launch and cleanup.
int ReplayLoadMenu_Update(ReplayMenuState&,std::uint32_t pressed,const ReplayMenuEdges&);
struct ReplayNameState{int phase{},timer{},selection{},previous_selection{},slot{},cursor{};std::array<ReplaySummary*,25> slots{};std::array<char,9> name{};};
struct ReplayNameEdges{ReplaySummary*(*load)(void*,const std::string&){};void(*release)(void*,ReplaySummary*){};bool(*save)(void*,const std::string&,const char*){};void* context{};void(*transition)(void*,int){};void(*sound)(void*,int){};};
// Retail 0x00433570: replay-save slot selection and eight-character name entry.
int ReplaySaveName_Update(ReplayNameState&,std::uint32_t pressed,const ReplayNameEdges&);
}
