extern "C" unsigned int g_crt_heap_type;
extern "C" unsigned int __sbh_threshold;

// 0x00453C3D..0x00453C51: Return the mask for CRT state 3.
extern "C" unsigned int __cdecl crt_unassigned_453c3d() {
    return g_crt_heap_type == 3 ? __sbh_threshold : 0;
}
