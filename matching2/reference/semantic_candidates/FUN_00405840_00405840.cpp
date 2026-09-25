// Callback thunk installed for the player update task.  The native-LTCG
// cluster models the entry copy from ECX to EDI before it reaches the player
// body at 0x00405750.
struct PlayerUpdate_00405750;

extern "C" int __fastcall UpdatePlayer_00405750(
    PlayerUpdate_00405750* player);

#pragma code_seg(".text$03callback")
extern "C" __declspec(noinline) void __fastcall
PlayerUpdateCallback_00405840(PlayerUpdate_00405750* player) {
    (void)UpdatePlayer_00405750(player);
}
#pragma code_seg()
