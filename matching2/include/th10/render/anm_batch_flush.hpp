#pragma once

// Sprite-batch flush for the animation manager (retail 0x00442F50).
#include "th10/render/quad_vertex_append.hpp"

// The three device leaves retail's flush drives, all through the
// IDirect3DDevice9 vtable of dword_491C30:
//   +0x10C SetTextureStageState, +0x164 SetFVF, +0x14C DrawPrimitiveUP.
struct QuadBatchEnv {
    void (*set_texture_stage_state)(unsigned int stage, unsigned int type,
                                    unsigned int value);
    void (*set_fvf)(unsigned int fvf);
    void (*draw_primitive_up)(unsigned int primitive_type,
                              unsigned int primitive_count,
                              const QuadRenderVertex* vertices,
                              unsigned int stride);
};

// Draw every quad staged since the last flush and reopen the batch. Returns
// the incremented draw-call counter, or 0 when nothing was staged - retail
// returns the counter it loaded, which is the zero quad count in that case.
int AnimationManager_FlushQuadBatch(QuadVertexStaging* staging,
                                    int* draw_calls,
                                    const QuadBatchEnv* env);
