// 0x00449EB0 (30 bytes): stop the loader worker, then release everything both
// resource lists still hold. The manager's destructor at 0x00438880 carries an
// inlined copy of this routine; this out-of-line copy has no retail caller.
//
// Native LTCG passes the manager in EDI.
#include "th10/core/func_ctrl_release.hpp"

#pragma code_seg(".text$08manager")
void FuncCtrlReleaseView::ReleaseTasks() {
    g_destroy_worker.Stop();
    ReleaseTaskList(reinterpret_cast<FuncCtrl*>(this), &primary);
    ReleaseTaskList(reinterpret_cast<FuncCtrl*>(this), &secondary);
}
#pragma code_seg()
