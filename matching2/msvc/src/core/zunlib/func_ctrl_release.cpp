// 0x00449EB0 (30 bytes): stop the loader worker, then release everything both
// resource lists still hold. The manager's destructor at 0x00438880 carries an
// inlined copy of this routine; this out-of-line copy has no retail caller.
//
// Native LTCG passes the manager in EDI.
#include "th10/render/d3d_resource_manager_00449eb0.hpp"

#pragma code_seg(".text$08manager")
void FuncCtrlReleaseView::ReleaseResources() {
    g_destroy_worker.Stop();
    ReleaseResourceList(reinterpret_cast<FuncCtrl*>(this), &primary);
    ReleaseResourceList(reinterpret_cast<FuncCtrl*>(this), &secondary);
}
#pragma code_seg()
