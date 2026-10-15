#include "th10/render/d3d_destroy_00438880.hpp"
#include "th10/platform/worker.hpp"
extern PlatformWorker g_destroy_worker_00438880;
#pragma code_seg(".text$01manager")
D3DResourceManager_Destroy_00438880::~D3DResourceManager_Destroy_00438880() {
    g_destroy_worker_00438880.Stop();
    primary.Release(reinterpret_cast<Scheduler*>(this));
    secondary.Release(reinterpret_cast<Scheduler*>(this));
}
#pragma code_seg()
