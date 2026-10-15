// 0x00449A90: retire the three pending-resource words of a D3D resource list.
//
// Retail addresses the list through EAX and returns without touching the stack,
// a convention MSVC only chooses during a native /GL link, so the body is
// compiled as a cluster (build_support/layout/ltcg/d3d_resource_list_clear_pending_00449a90.json).

struct D3DResourceList_ClearPending_00449a90 {
    unsigned char pad_000[8];
    int field_008;                  // +0x08
    int field_00C;                  // +0x0c
    int field_010;                  // +0x10
    __declspec(noinline) void ClearPending();
};

#pragma code_seg(".text$01clear")
void D3DResourceList_ClearPending_00449a90::ClearPending() {
    field_008 = 0;
    field_00C = 0;
    field_010 = 0;
}
#pragma code_seg()
