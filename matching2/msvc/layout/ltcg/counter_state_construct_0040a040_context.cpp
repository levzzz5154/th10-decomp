// Compiler context only; its bytes are not recovered game code.
#include "../../src/game/eclview/sprite_viewer_construct.cpp"

#pragma code_seg(".text$03context")
inline void* operator new(unsigned int, void* where) { return where; }
int __stdcall Ctx(void** p, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += (int)new (p[i]) SpriteViewerState;
    return r;
}
#pragma code_seg()
