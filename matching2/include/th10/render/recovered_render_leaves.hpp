#pragma once

// Default platform leaves for the recovered render chain (src/ side).
//
// The retail draw paths bottom out at two globals: the D3D device
// (dword_491C30, whose vtable carries SetTextureStageState at +0x10C,
// SetFVF at +0x164 and DrawPrimitiveUP at +0x14C) and the animation
// manager (dword_491C10, whose vertex staging lives at +0x3ADAC8 staged
// count, +0x72DACC write cursor and +0x72DAD0 batch start - the same
// offsets the MSVC overlays of 0x00442F50 and 0x00442FE0 read).  The
// host injects its own render bindings over these defaults; the defaults
// exist so the game-owned edges can route into the recovered claims
// (0x00443080 quad builder, 0x00442FE0 vertex append, 0x00442F50 batch
// flush) without fabricating the device access.
//
// The ANM draw-mode handlers beyond mode 0/1/2/3 are not individually
// recovered; the default env routes them through the standard quad
// builder, which is the tree's semantic model of the shared path.

#include "th10/render/anm_batch_flush.hpp"
#include "th10/render/anm_vm_draw_dispatch.hpp"
#include "th10/render/quad_build_anchored.hpp"
#include "th10/render/quad_vertex_append.hpp"

#include <cmath>

namespace th10 {
namespace render_leaves {

// The three D3D device calls (dword_491C30 vtable +0x10C / +0x164 /
// +0x14C), spelled as literal vtable calls exactly like the MSVC overlay
// of 0x00442F50.
QuadBatchEnv DefaultQuadBatchEnv();

// The recovered 0x00442F50 flush applied to the animation manager's
// staging (dword_491C10).  Inert when the device global is null (the
// host injects its own render binding in that case).
void FlushQuadBatch();

// Append one four-vertex quad to the animation manager's staging
// (dword_491C10) through the recovered 0x00442FE0 writer, taking the
// colour from the record's primary/secondary colour registers (+0x2FC /
// +0x300, bit 15 of +0x35C selects) like the retail 0x00442670 pass.
// The sprite UV decode is not part of this leaf; UVs are zero.
void AppendQuadColored(const float corners[4][2], unsigned int color);

// Test-visible handle to the recovery-side staging (the host-form
// counterpart of the retail manager's scattered 32-bit fields at
// +0x3ADAC8 / +0x72DACC / +0x72DAD0).
QuadVertexStaging* Staging();

// Default AnmDrawEnv: every mode routes through the recovered quad
// builder (0x00443080) and the staging append above.  Mode 1/3 use the
// shared rotated-corner buffer (g_anm_corner_quad) filled by the
// recovered rotation helpers.
AnmDrawEnv DefaultAnmDrawEnv();

}  // namespace render_leaves
}  // namespace th10
