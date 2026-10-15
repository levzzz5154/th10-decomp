#include "workers.hpp"
#pragma code_seg(".text$01stop")
int SoundWorkerPair::Stop() {
    if (first_thread == 0) {
        return 0;
    }
    if (stop_requested == 0) {
        stop_requested = 1;
    }
    while (WaitForSingleObject(first_thread, 100) == kSoundWorkerWaitTimeout) {
        Sleep(1);
    }
    while (WaitForSingleObject(second_thread, 100) == kSoundWorkerWaitTimeout) {
        Sleep(1);
    }
    CloseHandle(first_thread);
    CloseHandle(second_thread);
    first_thread = 0;
    second_thread = 0;
    return 0;
}
#pragma code_seg()
