// 0x004051B0: store a byte flag in the shared game runtime state.
// Retail receives the state in EAX and the byte value in CL and ends in a plain RET.

struct GameRuntimeState {
    char unknown_0000[0x3ADA6C];
    char enabled_3ADA6C;                // +0x3ADA6C

    __declspec(noinline) void SetEnabled(char value);
};

#pragma code_seg(".text$01f4051b0")
void GameRuntimeState::SetEnabled(char value) {
    this->enabled_3ADA6C = value;
}
#pragma code_seg()
