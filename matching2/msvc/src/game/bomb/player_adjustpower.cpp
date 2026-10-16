// 0x00405B60 (42 bytes): add a signed delta to the clamped power accumulator
// of the global player state at 0x00474C40.
//
// retail:
//   mov edx,[eax+58h] / add edx,ecx / mov ecx,edx / cmp ecx,400h
//   mov [eax+58h],edx
//   jle lower_bound -> mov [eax+58h],400h / ret
//   cmp ecx,0FFFFFC00h / jge ret
//   mov [eax+58h],0FFFFFC00h / ret
// The state pointer arrives in EAX and the delta in ECX, the internal
// convention the link-time code generator chose; declaring the member void and
// compiling the synthetic caller in the same /LTCG cluster reproduces it.

struct PlayerPowerState {
    char unknown[0x58];
    int power;                      // +0x58, clamped to [-1024, 1024]

    __declspec(noinline) void AdjustPower(int delta);
};

#pragma code_seg(".text$01adjustpower")
void PlayerPowerState::AdjustPower(int delta) {
    this->power += delta;
    if (this->power > 1024)
        this->power = 1024;
    else if (this->power < -1024)
        this->power = -1024;
}
#pragma code_seg()
