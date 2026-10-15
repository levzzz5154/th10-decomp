// 0x00421F50 - reads one word out of the live game state pointed to by the
// global at 0x004776E0. Only the touched offset is described.
struct GameState {
    unsigned char unknown_00[0x8998];
    int field_8998;                  // +0x8998
};

extern "C" unsigned char data_004776e0;

int __cdecl FUN_00421f50_00421f50() {
    return ((GameState*)*(void**)&data_004776e0)->field_8998;
}
