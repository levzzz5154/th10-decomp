#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
namespace th10::ui_final {struct Notice{int slot{};std::string text;int value{};int count{};std::array<int,8>animations{};};void QueueNotice(Notice&,int,const std::string&,int,int difficulty,int stage);
struct FrontTick{int timer{},mode{},lives{},bombs{},score{},faith{},graze{};bool boss_active{},player_visible{},transition{};std::vector<int>events;};int UpdateFront(FrontTick&);
struct StageSequence{int cursor{},time{},phase{},selection{},cooldown{};std::array<int,5>handles{};std::vector<int>events;};int UpdateStageSequence(StageSequence&,const std::vector<int>&opcodes,std::uint32_t input,int difficulty,int stage);
struct ReplaySaveFlow{int phase{6},timer{},selection{},cursor{};std::array<std::string,25>slots{};std::array<char,9>name{};bool saved{};std::vector<int>events;};int UpdateReplaySave(ReplaySaveFlow&,std::uint32_t input);
struct OptionsView{int music{},sound{},window{},shots{},selection{};std::array<int,32>sprites{};};void DrawOptions(OptionsView&);
struct MainView{int selection{},value{},difficulty{};std::array<int,32>sprites{};};void DrawMain(MainView&);
struct MusicRoom{int phase{},timer{},selection{},track_count{},scroll{};std::vector<std::string>comments;std::vector<int>events;};int UpdateMusicRoom(MusicRoom&,std::uint32_t input,const std::string&resource);
}
