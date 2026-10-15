#define data_00491c10 stage_sched_data_00491c10
#define data_0047770c stage_sched_data_0047770c
#define data_00474c40 stage_sched_data_00474c40
#define g_ascii_manager stage_sched_data_004776e0
#define data_00477704 stage_sched_data_00477704
#define g_player stage_sched_data_00477834
#define data_00477838 stage_sched_data_00477838
#define data_0047783c stage_sched_data_0047783c
#define data_00476f78 stage_sched_data_00476f78
#define data_00491fc4 stage_sched_data_00491fc4
#define data_00491fb8 stage_sched_data_00491fb8
#define data_00492590 stage_sched_data_00492590
// 0x00405410: store a scheduler value into the record whose address arrives in
// EAX, initialising the record to its defaults while its "initialised" flag is
// still clear.
//
// Retail: 8B 48 10           mov ecx,[eax+0x10]
//         F6 C1 01           test cl,1
//         56                 push esi
//         8B 74 24 08        mov esi,[esp+8]      ; value
//         75 1B              jne done
//         33 D2              xor edx,edx
//         83 C9 01           or ecx,1
//         89 50 04           mov [eax+4],edx
//         C7 00 C1 BD F0 FF  mov [eax],0xFFF0BDC1
//         89 50 08           mov [eax+8],edx
//         C7 40 0C 78 6F 47 00  mov [eax+0xC],0x476F78
//         89 48 10           mov [eax+0x10],ecx
//  done:  DB 44 24 08        fild dword [esp+8]
//         89 70 04           mov [eax+4],esi
//         4E                 dec esi
//         89 30              mov [eax],esi
//         D9 58 08           fstp dword [eax+8]
//         5E                 pop esi
//         C2 04 00           ret 4
// The record pointer arrives in EAX while the value stays on the stack, so the
// setter is compiled as a native LTCG cluster.
// Carved out of src/game/player.cpp (asm_Player_SetSchedulerValue_00405410).

struct PlayerSchedulerRecord {
    int field_00;    // 0x00 value, stored one below the raw value
    int field_04;    // 0x04 value
    float field_08;  // 0x08 value converted to float
    int field_0C;    // 0x0C default marker
    int flags_10;    // 0x10 initialised flag

    __declspec(noinline) void SetSchedulerValue(int value);
};

#pragma code_seg(".text$00405410_fn")
void PlayerSchedulerRecord::SetSchedulerValue(int value) {
    if (!(this->flags_10 & 1)) {
        this->field_04 = 0;
        this->field_00 = 0xFFF0BDC1;
        this->field_08 = 0.0f;
        this->field_0C = 0x476F78;
        this->flags_10 |= 1;
    }
    this->field_04 = value;
    this->field_00 = value - 1;
    this->field_08 = (float)value;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
