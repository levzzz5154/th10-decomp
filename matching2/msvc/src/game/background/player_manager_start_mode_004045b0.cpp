// 0x004045B0: start the player manager's "active" mode, initialising its timer
// record to defaults while the record's initialised flag is still clear.
//
// Retail: 8B 88 2C 2A 00 00        mov ecx,[eax+0x2A2C]
//         F6 C1 01                 test cl,1
//         75 2B                    jne done
//         33 D2                    xor edx,edx
//         83 C9 01                 or ecx,1
//         89 90 20 2A 00 00        mov [eax+0x2A20],edx
//         C7 80 1C 2A 00 00 C1 BD F0 FF  mov [eax+0x2A1C],0xFFF0BDC1
//         89 90 24 2A 00 00        mov [eax+0x2A24],edx
//         C7 80 28 2A 00 00 78 6F 47 00  mov [eax+0x2A28],0x476F78
//         89 88 2C 2A 00 00        mov [eax+0x2A2C],ecx
//  done:  C7 80 20 2A 00 00 3C 00 00 00  mov [eax+0x2A20],60
//         C7 80 24 2A 00 00 00 00 70 42  mov [eax+0x2A24],60.0f
//         C7 80 1C 2A 00 00 3B 00 00 00  mov [eax+0x2A1C],59
//         83 88 18 2A 00 00 04     or  [eax+0x2A18],4
//         C3                       ret
// The manager pointer arrives in EAX, so the mode switch is compiled as a
// native LTCG cluster.
// Carved out of src/game/player.cpp (asm_PlayerManager_StartMode_004045b0).

struct PlayerManagerState {
    char unknown[0x2A18];
    int flags_2A18;   // 0x2A18 mode flags
    int field_2A1C;   // 0x2A1C timer value
    int field_2A20;   // 0x2A20 timer limit
    float field_2A24; // 0x2A24 timer limit as float
    int field_2A28;   // 0x2A28 timer marker
    int flags_2A2C;   // 0x2A2C timer initialised flag

    __declspec(noinline) void StartMode();
};

#pragma code_seg(".text$01startmode")
void PlayerManagerState::StartMode() {
    if (!(this->flags_2A2C & 1)) {
        this->field_2A20 = 0;
        this->field_2A1C = 0xFFF0BDC1;
        this->field_2A24 = 0.0f;
        this->field_2A28 = 0x476F78;
        this->flags_2A2C |= 1;
    }
    // The flag update is a single read-modify-write of the field: taking the
    // field's address first keeps it from being split into load/or/store.
    int* flags = &this->flags_2A18;
    this->field_2A20 = 60;
    this->field_2A24 = 60.0f;
    this->field_2A1C = 59;
    *flags |= 4;
}
#pragma code_seg()
