#ifndef TH10_GAME_MAIN_00438AD0_HPP
#define TH10_GAME_MAIN_00438AD0_HPP

// The seven one-shot subsystem objects the main loop enters and leaves
// critical sections on (0x492274 + 0x18·i).
struct MainCritSection_00438ad0 {
    void* reserved[6];
};

// 0x00438AD0: the game's WinMain — the process entry the CRT startup calls.
// `instance` is stored to 0x4924F8; the return value is the process exit
// code the caller passes to ExitProcess.
__declspec(noinline) int __stdcall GameMain_00438ad0(
    void* instance, void* previous, char* command_line, int show);
#endif
