// Candidate only: native LTCG with genuine member destruction unwind semantics.
#include "th10/game/resource_list_destroy_abi.hpp"
#include "th10/platform/worker.hpp"
extern PlatformWorker g_destroy_worker_00438880;
#pragma code_seg(".text$00listclear")
struct D3DResourceList_Destroy_00438880 : ResourceList_DestroyABI_00449e50 {
    unsigned int tail[2];
    ~D3DResourceList_Destroy_00438880() {
        unsigned int* pending = reinterpret_cast<unsigned int*>(reserved + 8);
        pending[0] = 0;
        pending[1] = 0;
        pending[2] = 0;
    }
};
#pragma code_seg(".text$00destroy")
struct D3DResourceManager_Destroy_00438880 {
    D3DResourceList_Destroy_00438880 primary, secondary;
    __declspec(noinline) ~D3DResourceManager_Destroy_00438880() {
        g_destroy_worker_00438880.Stop();
        primary.Release(reinterpret_cast<Scheduler*>(this));
        secondary.Release(reinterpret_cast<Scheduler*>(this));
    }
};
#pragma code_seg(".text$40wrapper")
__declspec(noinline) void __stdcall D3DResourceManager_Destroy_00438880(
    D3DResourceManager_Destroy_00438880* manager) {
    manager->~D3DResourceManager_Destroy_00438880();
}
#pragma code_seg()
