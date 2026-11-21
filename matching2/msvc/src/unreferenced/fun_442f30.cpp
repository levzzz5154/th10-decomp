// 0x00442F30: empty the vertex batch and point both cursors at its start.
struct TexturedVertex2 { float x, y, z, rhw; unsigned int color; float u, v; };
struct QuadBatch {
    unsigned char reserved_000[0x3ADAC8];
    int quad_count;                                    // +0x3ADAC8
    TexturedVertex2 vertices[0x20000];         // +0x3ADACC
    TexturedVertex2* cursor;                   // +0x72DACC
    TexturedVertex2* batch_start;              // +0x72DAD0
    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01accessor")
void QuadBatch::Reset() {
    quad_count = 0;
    cursor = vertices;
    batch_start = vertices;
}
#pragma code_seg()
