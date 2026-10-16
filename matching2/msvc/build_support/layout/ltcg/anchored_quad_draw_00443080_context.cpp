// Genuine complete retail caller/callee graph; only the 515-byte anchored
// worker is selected. The unchanged real dispatcher is the public cdecl link
// entry here, with its complete 236-byte contribution and two stack arguments;
// its separately selected retail owner remains 216 bytes with a private entry.
// SubmitSpriteQuad retains its existing FRNDINT pixel-snap assembly. All helper
// contributions are unselected and receive no extra recovery credit here.
#include "../../../src/core/sprtfunc/quad_build_anchored.cpp"
#include "../../../src/core/sprtfunc/animation_color_multiply_channel.cpp"
#include "../../../src/core/sprtfunc/render_state_sync.cpp"
#include "../../../src/core/sprtfunc/sprite_quad_submit.cpp"
#include "../../../src/core/sprtfunc/anm_batch_flush.cpp"
#include "../../../src/core/sprtfunc/quad_vertex_append.cpp"
#include "../../../src/core/sprtfunc/anm_vm_draw_dispatch.cpp"
