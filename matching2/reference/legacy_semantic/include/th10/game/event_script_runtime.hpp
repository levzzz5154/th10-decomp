#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
namespace th10::event_script {
struct EndingCommand{int time{};std::uint8_t opcode{};std::vector<int> args;std::string text;};
struct EndingState {
    int time{}, previous_time{}, cursor{}, wait_counter{};
    // Retail keeps this as the float accumulator at +0x20 and derives the
    // integer command time from it.  Keeping only a scaled integer loses the
    // sub-frame remainder after a fractional-speed update.
    float fraction{};
    std::uint32_t flags{};
    std::uint32_t color{0xffffff};
    std::array<int,5> handles{};
    // A successfully loaded opcode-12 stream remains owned by the state so
    // subsequent calls do not fall back to the caller's old vector.
    std::vector<EndingCommand> loaded_stream{};
    bool using_loaded_stream{};
};
struct EndingEdges {
    void*context{};
    void(*event)(void*,int,const EndingCommand&){};
    bool(*confirm)(void*){};
    // Return false for the retail load-failure path.  The callback fills the
    // host-owned command stream corresponding to opcode 12's name.
    bool(*load)(void*,const std::string&,std::vector<EndingCommand>&){};
};
// Retail 0x0040BD80: execute due ending-script commands and advance scaled time.
int EndingScript_Update(EndingState&,const std::vector<EndingCommand>&,float speed,const EndingEdges&);
struct StageCommand{int time{};std::uint16_t opcode{};std::vector<float> args;};
struct StageState{int time{},previous_time{},fraction{},cursor{};std::uint32_t flags{};std::array<float,3> camera{},camera_delta{},target{},target_delta{},up{};std::uint32_t color{};std::array<float,4> color_channels{};int mode{},global_value{};float shake{};};
struct StageEdges{void*context{};void(*event)(void*,int,const StageCommand&){};};
// Retail 0x00403C80: execute stage timeline opcodes 0..14 and advance time.
int StageTimeline_Update(StageState&,const std::vector<StageCommand>&,float speed,const StageEdges&);
}
