// 0x00438880..0x00465358: FuncCtrlDestroyView::~FuncCtrlDestroyView, FuncCtrlUnwindPrimary_00465350, FuncCtrlUnwindSecondary_00465358
#include "th10/core/func_ctrl_destroy.hpp"
#include "th10/platform/worker.hpp"
extern PlatformWorker g_destroy_worker;
#pragma code_seg(".text$01manager")
FuncCtrlDestroyView::~FuncCtrlDestroyView() {
    g_destroy_worker.Stop();
    primary.Release(reinterpret_cast<FuncCtrl*>(this));
    secondary.Release(reinterpret_cast<FuncCtrl*>(this));
}
#pragma code_seg()
