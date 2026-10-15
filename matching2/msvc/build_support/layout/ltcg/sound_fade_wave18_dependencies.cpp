// Full original private lifetime leaves used by the real mode update.
#include "th10/app/main_task_mode.hpp"
extern "C" void __stdcall ModeDestroyUiWave18(void*);
extern "C" void __stdcall ModeDestroyScriptWave18(void*);
extern "C" void __stdcall ModeDestroySmallWave18(void*);
extern "C" void __cdecl ModeFreeWave18(void*);
#pragma code_seg(".text$00a_score_destroy")
void ScoreOwnedObject_Destroy(ScoreOwnedObject* object) {
    if (object) { ModeDestroySmallWave18(object); ModeFreeWave18(object); }
}
#pragma code_seg(".text$00b0_ui_destroy")
void Game_Delete(Game* object) {
    if (object) { ModeDestroyUiWave18(object); ModeFreeWave18(object); }
}
#pragma code_seg(".text$00d_leave")
void MainTaskStateWave18::LeaveSlot(int index) {
    imp_LeaveCriticalSection(critical_sections[index]);
    --lock_depth[index];
}
#pragma code_seg(".text$00f_script_destroy")
void Title_Delete(Title* object) {
    if (object) { ModeDestroyScriptWave18(object); ModeFreeWave18(object); }
}
#pragma code_seg()
