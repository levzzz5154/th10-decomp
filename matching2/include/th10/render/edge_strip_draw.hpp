#pragma once

// Textured edge-strip draw with state synchronization (retail 0x00444CE0).
// Retail function 0x00444CE0.
struct EdgeStripRecord{unsigned flags;unsigned char drawable;void*texture;int vertex_count,primitive_count;};
struct EdgeStripRenderer{int pending;void*texture;int mode;};
struct EdgeStripDrawEnv{void(*flush)();void(*bind_texture)(void*);void(*set_fvf)(unsigned);void(*apply_state)(const EdgeStripRecord*);void(*stage)(int,int,int);void(*draw)(int,int,int,int);};
int Renderer_DrawTexturedEdgeStrip(const EdgeStripRecord*,EdgeStripRenderer*,const EdgeStripDrawEnv*);
