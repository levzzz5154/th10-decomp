#pragma once

// One 28-byte retail render vertex (position, color, and texture
// coordinates packed as seven 32-bit words). The staging writer below
// copies vertices wholesale, so the exact word meaning is not needed
// here.
struct QuadRenderVertex {
    unsigned int words[7];
};

// Vertex staging state embedded in the animation manager. In retail the
// write cursor lives at manager+0x72DACC and the staged-quad counter at
// manager+0x3ADAC8; the readable form groups the two fields the append
// path touches.
struct QuadVertexStaging {
    QuadRenderVertex* cursor;  // retail manager+0x72DACC
    int quad_count;            // retail manager+0x3ADAC8
};

// Expand one four-vertex quad into the staging buffer as two triangles
// (vertices 0,1,2 then 1,2,3), advance the cursor by six vertices
// (0xA8 bytes), and count one staged quad. Always returns 0, matching
// the retail function.
unsigned int AnimationManager_AppendQuadVertices(
    QuadVertexStaging* staging, const QuadRenderVertex vertices[4]);
