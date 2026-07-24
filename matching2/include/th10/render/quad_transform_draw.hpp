#pragma once

// Quad world-transform rebuild and two-triangle draw (retail 0x00444760).
// Retail function 0x00444760.
struct QuadMatrix{float m[16];};struct QuadTexture{void*handle;float u,v;};
struct TransformedQuad{unsigned flags;unsigned char drawable;float angle[3],scale[2],size[2],texoff[2];QuadMatrix base,world,texture_matrix;float local[3],shared[3],anchor[3];QuadTexture*texture;};
struct QuadRenderer{int pending;void*texture_handle;QuadTexture*texture_record;int vertex_mode;void*vertex_buffer;};
struct QuadDrawEnv{void(*flush)();void(*rotation)(QuadMatrix*,int,float);void(*multiply)(QuadMatrix*,const QuadMatrix*,const QuadMatrix*);void(*apply_state)(const TransformedQuad*);void(*transform)(int,const QuadMatrix*);void(*bind)(void*);void(*stream)(void*,int);void(*fvf)(unsigned);void(*stage)(int,int,int);void(*draw)(int,int,int);};
int Renderer_DrawTransformedQuad(TransformedQuad*,QuadRenderer*,const QuadDrawEnv*);
