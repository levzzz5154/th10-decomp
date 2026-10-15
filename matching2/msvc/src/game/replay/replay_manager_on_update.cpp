// 0x0042A3D0: the replay manager's update task (registered by 0x00428F60).
#include "../../../build_support/layout/ltcg/input_recorder.hpp"

#pragma code_seg(".text$05callback")
int __fastcall ReplayManager_OnUpdate(InputRecorder* recorder) {
    return recorder->Update();
}
#pragma code_seg()
