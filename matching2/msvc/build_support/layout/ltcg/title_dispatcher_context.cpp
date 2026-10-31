// The title dispatcher 0x0042CDF0 as its original translation unit, with the
// compiler context it was recovered against: its one caller (0x0042D2E0,
// Title::OnUpdate) and the game state as one object whose address escapes in
// the whole program.
#include "../../../src/game/title/title_dispatcher.cpp"

#pragma code_seg(".text$0042d2e0_fn")
struct TitleModel {
    __declspec(noinline) int Update();
};
int TitleModel::Update() {
    return TitleDispatcher(reinterpret_cast<Title*>(this));
}
#pragma code_seg(".text$00401440_park")
extern "C" void __stdcall TitleDispatcherEscape(void** objects) {
    objects[0] = &g_globals_score;
}
#pragma code_seg()
