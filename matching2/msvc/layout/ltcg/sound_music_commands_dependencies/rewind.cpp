// Compiler context only: the real archive rewind 0x0044DD40, so the pass sees the
// callee's body and gives its caller the private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#include "th10/game/sound_start_context.hpp"
#define code_seg(name) code_seg(".text$a08rewind")
#include "../sound_start_sound_fill_rewind.cpp"
