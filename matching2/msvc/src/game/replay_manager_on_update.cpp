#include "../../layout/ltcg/input_recorder.hpp"

#pragma code_seg(".text$05callback")
int __fastcall ReplayManager_OnUpdate(InputRecorder_004297D0* recorder) {
    return recorder->Update();
}
#pragma code_seg()
