#include "th10/platform/sound_fade_manager_wave18.hpp"
struct OwnedObject_00418150;
struct OwnedObject_0042cdb0;
struct ScoreOwnedObject;
extern "C" OwnedObject_00418150* data_00477810;
extern "C" OwnedObject_0042cdb0* data_0047784c;
extern "C" ScoreOwnedObject* data_00477700;
extern "C" int data_00491c00;
extern "C" int data_00474c80;
extern "C" int data_00474c7c;
struct StageRouteWave18 { unsigned char bytes[0x30]; };
extern "C" StageRouteWave18 data_00474788[];
extern "C" StageRouteWave18* data_00477848;
struct GameUiArgumentWave18 { unsigned char reserved[0x5C]; unsigned int argument; };
extern "C" void (__stdcall *data_004660b0)(void*);
extern "C" void (__stdcall *data_004660b4)(void*);
extern "C" void* __cdecl ModeCreateStateWave18();
extern "C" void __stdcall ModeReleaseGlobalsWave18();
extern "C" void* __cdecl ModeCreateProgressWave18();
extern "C" void* __stdcall ModeCreateUiWave18(unsigned int);
extern "C" void* __stdcall ModeCreateSmallWave18();
__declspec(noinline) void DestroyOwned_00418150(OwnedObject_00418150*);
__declspec(noinline) void DestroyOwned_0042cdb0(OwnedObject_0042cdb0*);
__declspec(noinline) void ScoreOwnedObject_Destroy(ScoreOwnedObject*);
#pragma code_seg(".text$00c_mode")
int MainTaskStateWave18::UpdateMode() {
    if (current_mode == next_mode) return 1;
    data_004660b0(critical_sections[5]);
    int previous = current_mode;
    ++lock_depth[5];
    previous_mode = previous;
    overlay_color = 0xFF000000;
    switch (next_mode) {
    case 0:
        next_mode = 1;
        created_state = ModeCreateStateWave18();
        if (created_state) break;
        next_mode = 3;
    case 3:
        ModeReleaseGlobalsWave18();
        LeaveSlot(5);
        return 4;
    case 4:
        switch (previous) {
        case 1: case 2: break;
        case 7: DestroyOwned_00418150(data_00477810); break;
        case 14: ScoreOwnedObject_Destroy(data_00477700); break;
        default: goto done;
        }
        ModeCreateProgressWave18();
        break;
    case 7:
        if (previous == 4) DestroyOwned_0042cdb0(data_0047784c);
        ui_mode = 1;
        ModeCreateUiWave18(0);
        break;
    case 10:
        DestroyOwned_00418150(data_00477810);
        ui_mode = 1;
        next_mode = 7;
        data_00474c7c = data_00474c80;
        data_00477848 = data_00474788 + data_00474c80;
        ModeCreateUiWave18(0);
        break;
    case 11: {
        unsigned int argument = reinterpret_cast<GameUiArgumentWave18*>(data_00477810)->argument;
        ui_mode = 0;
        if (previous == 7) DestroyOwned_00418150(data_00477810);
        next_mode = 7;
        ModeCreateUiWave18(argument);
        break;
    }
    case 12:
        if (previous == 4) DestroyOwned_0042cdb0(data_0047784c);
        next_mode = 7;
        ui_mode = 1;
        ModeCreateUiWave18(1);
        break;
    case 13:
        DestroyOwned_00418150(data_00477810);
        ui_mode = 1;
        next_mode = 7;
        ModeCreateUiWave18(0);
        break;
    case 14:
        if (previous == 7) DestroyOwned_00418150(data_00477810);
        ModeCreateSmallWave18();
        break;
    case 15:
        if (previous != 2) {
            if (previous == 7) DestroyOwned_00418150(data_00477810);
            else if (previous == 14) ScoreOwnedObject_Destroy(data_00477700);
            else break;
        }
        next_mode = 4;
        data_00491c00 = 3;
        ModeCreateProgressWave18();
        break;
    }
done:
    current_mode = next_mode;
    data_004660b4(critical_sections[5]);
    --lock_depth[5];
    return 1;
}
#pragma code_seg()
#include "sound_fade_wave18_dependencies.cpp"
