// Compiler context only: the real interface run 0x0044D300, so the pass sees the
// callee's body and gives its caller the private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#include "th10/game/sound_start_context.hpp"
#define code_seg(name) code_seg(".text$a03g")
#include "../sound_start_platform_run_interface.cpp"
