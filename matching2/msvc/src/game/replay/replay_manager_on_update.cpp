// 0x0042A3D0: the replay manager's update task (registered by 0x00428F60).
#include "../../../layout/ltcg/input_recorder.hpp"

#pragma code_seg(".text$05callback")
int __fastcall ReplayManager_OnUpdate(InputRecorder_004297D0* recorder) {
    return recorder->Update();
}
#pragma code_seg()
