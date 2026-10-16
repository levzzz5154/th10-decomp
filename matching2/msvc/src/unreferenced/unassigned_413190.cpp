// 0x00413190: clear the eleven-word block
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

#include <string.h>

__declspec(noinline) void ClearBlock(void* block);
#pragma code_seg(".text$01accessor")
void ClearBlock(void* block) {
    memset(block, 0, 44);
}
#pragma code_seg()
