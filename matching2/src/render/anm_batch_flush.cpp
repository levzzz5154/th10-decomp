#include "th10/render/anm_batch_flush.hpp"

// 0x00442F50 - Draw the staged sprite quads and reopen the batch.
//
// Retail keeps the manager in ESI. The staged-quad count lives at
// manager+0x3ADAC8, the write cursor at manager+0x72DACC and the pointer to
// the first vertex of the open batch at manager+0x72DAD0; the draw-call
// counter is manager+0x58. With nothing staged the function loads the zero
// count into EAX and returns it untouched.
//
// The three device calls are literal, in this order:
//   SetTextureStageState(0, 6, 0)   D3DTSS_ALPHAARG2 <- D3DTA_DIFFUSE
//   SetTextureStageState(0, 3, 0)   D3DTSS_COLORARG2 <- D3DTA_DIFFUSE
//   SetFVF(0x144)                   D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1
//   DrawPrimitiveUP(4, 2 * quads, batch_start, 0x1C)
// D3DPT_TRIANGLELIST is 4 and the retail render vertex is 0x1C bytes wide.
// Forcing both ARG2 selectors to D3DTA_DIFFUSE is why 0x00442670 writes the
// modulation colour into the four vertices rather than relying on
// D3DRS_TEXTUREFACTOR.
int AnimationManager_FlushQuadBatch(QuadVertexStaging* staging,
                                    int* draw_calls,
                                    const QuadBatchEnv* env) {
    if (staging->quad_count == 0) {
        return 0;
    }
    env->set_texture_stage_state(0, 6, 0);
    env->set_texture_stage_state(0, 3, 0);
    env->set_fvf(0x144);
    env->draw_primitive_up(4, (unsigned int)(2 * staging->quad_count),
                           staging->batch_start, 0x1C);
    *draw_calls = *draw_calls + 1;
    staging->batch_start = staging->cursor;
    staging->quad_count = 0;
    return *draw_calls;
}
