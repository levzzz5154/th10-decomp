// Compiler context only: the real cached music launcher 0x0043D950, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a01play")
#include "../../../../src/core/sound/sound_music_play_cached.cpp"
