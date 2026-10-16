#include "th10/source_views/fun_a1dd06_0.hpp"
#include "th10/source_views/fun_a1dd06_1.hpp"
int RenderStageState4::EnableFog() {
    if (fog_enabled != 1) {
        g_sprt_ctrl->Flush();
        RenderDevice* dev = device;
        fog_enabled = 1;
        return dev->State(28, 1);
    }
    return 0;
}


#include "../../../include/th10/source_views/fun_a1dd06_2.hpp"
#include "th10/source_views/fun_a1dd06_0.hpp"
#include "th10/source_views/fun_a1dd06_1.hpp"
#include "th10/source_views/fun_a1dd06_2.hpp"
int RenderStageState4::DisableFog() {
    if (fog_enabled) {
        g_sprt_ctrl->Flush();
        RenderDevice* dev = device;
        fog_enabled = 0;
        return dev->State(28, 0);
    }
    return 0;
}


#include "../../../include/th10/source_views/fun_a1dd06_3.hpp"
#include "th10/source_views/fun_a1dd06_0.hpp"
#include "th10/source_views/fun_a1dd06_1.hpp"
#include "th10/source_views/fun_a1dd06_2.hpp"
#include "th10/source_views/fun_a1dd06_3.hpp"
int RenderStageState4::EnableDepthWrite() {
    if (depth_write_enabled != 1) {
        g_sprt_ctrl->Flush();
        RenderDevice* dev = device;
        depth_write_enabled = 1;
        return dev->State(14, 1);
    }
    return 0;
}


#include "../../../include/th10/source_views/fun_a1dd06_4.hpp"
#include "th10/source_views/fun_a1dd06_0.hpp"
#include "th10/source_views/fun_a1dd06_1.hpp"
#include "th10/source_views/fun_a1dd06_2.hpp"
#include "th10/source_views/fun_a1dd06_3.hpp"
#include "th10/source_views/fun_a1dd06_4.hpp"
int RenderStageState4::DisableDepthWrite() {
    if (depth_write_enabled) {
        g_sprt_ctrl->Flush();
        RenderDevice* dev = device;
        depth_write_enabled = 0;
        return dev->State(14, 0);
    }
    return 0;
}


#include "../../../include/th10/source_views/fun_a1dd06_5.hpp"
#include "th10/source_views/fun_a1dd06_0.hpp"
#include "th10/source_views/fun_a1dd06_1.hpp"
#include "th10/source_views/fun_a1dd06_2.hpp"
#include "th10/source_views/fun_a1dd06_3.hpp"
#include "th10/source_views/fun_a1dd06_4.hpp"
#include "th10/source_views/fun_a1dd06_5.hpp"
int __stdcall RenderStageState_SetRenderState(RenderStageState4* stage,
                                              unsigned int state, unsigned int value) {
    g_sprt_ctrl->Flush();
    return stage->device->State(state, value);
}

