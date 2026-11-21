// The draw routine at 0x00415800 (Front_Draw in game_state_overlay_draw.cpp): it takes its one
// argument on the stack and pops it (`ret 4`), so the call is issued through a
// __stdcall pointer while the bound symbol keeps its __cdecl spelling.
extern "C" int __cdecl Front_DrawEntry(int arg);
typedef int (__stdcall* FrontDrawFn)(int object);

// 0x00415AF0: the HUD's draw task.
// Recovered: forwarding stub - hands the object to the 0x00415800 Front_Draw routine.
int __fastcall Front_OnDraw(void* self) {
    return ((FrontDrawFn)Front_DrawEntry)((int)self);
}
