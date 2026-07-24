#pragma once

// Rectangle triangle-fan draw with flush (retail 0x004450E0).
#include "th10/util/scalars.hpp"

// --- 0x004450E0 --------------------------------------------------------------
int Renderer_DrawRectFan(int pending_vertices, void (*flush)(void),
                         Byte* blend_state,
                         void (*set_blend_render_state)(void),
                         void (*commit_world)(void), int shader_handle,
                         int* bound_handle,
                         void (*bind_shader)(int stage, int handle),
                         void (*set_texture_stage)(int stage, int value),
                         void (*set_sampler_state)(int stage, int state,
                                                   int value),
                         void (*draw_fan)(int primitive_type,
                                          const void* vertices, int stride),
                         const void* vertices);
