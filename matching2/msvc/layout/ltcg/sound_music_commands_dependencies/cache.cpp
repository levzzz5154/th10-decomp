// Compiler context only: the real track cache 0x0043D7D0, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a00cache")
#include "../../../src/core/sound/sound_music_cache.cpp"
