// Full original private lifetime leaves used by the real mode update.
#include "th10/app/main_task_mode.hpp"
extern "C" void __stdcall Game_DestroyMode(void*);
extern "C" void __stdcall Title_DestroyMode(void*);
extern "C" void __stdcall Ending_DestroyMode(void*);
extern "C" void __cdecl MainTask_FreeMode(void*);
#pragma code_seg(".text$00a_score_destroy")
void Ending_Delete(EndingObject* object) {
    if (object) { Ending_DestroyMode(object); MainTask_FreeMode(object); }
}
#pragma code_seg(".text$00b0_ui_destroy")
void Game_Delete(Game* object) {
    if (object) { Game_DestroyMode(object); MainTask_FreeMode(object); }
}
#pragma code_seg(".text$00d_leave")
void MainTaskState::LeaveSlot(int index) {
    imp_LeaveCriticalSection(critical_sections[index]);
    --lock_depth[index];
}
#pragma code_seg(".text$00f_script_destroy")
void Title_Delete(Title* object) {
    if (object) { Title_DestroyMode(object); MainTask_FreeMode(object); }
}
#pragma code_seg()
