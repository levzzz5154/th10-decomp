#include "th10/render/d3d_destroy_00438880.hpp"
#include "th10/platform/worker.hpp"
extern PlatformWorker g_destroy_worker_00438880;
#pragma code_seg(".text$01manager")
FuncCtrlDestroyView::~FuncCtrlDestroyView() {
    g_destroy_worker_00438880.Stop();
    primary.Release(reinterpret_cast<FuncCtrl*>(this));
    secondary.Release(reinterpret_cast<FuncCtrl*>(this));
}
#pragma code_seg()
