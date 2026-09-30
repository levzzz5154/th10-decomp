#include "th10/render/gdi_font_state.hpp"

// Native LTCG keeps the destination on the stack for the exception cleanup.
// If AssignRange throws, C++ destroys the already constructed face member.
#pragma code_seg(".text$01font")
GdiFontState::GdiFontState() {
    handle = 0;
    weight = 600;
    height = 16;
    width = 0;
    face.AssignRange(g_default_font_face_cp932, 13);
}
#pragma code_seg()
