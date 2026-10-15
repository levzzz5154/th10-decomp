// 0x0041ADF0: destroy the item manager: its two tasks leave the scheduler.
#include "th10/game/item_manager_destructor.hpp"
#pragma code_seg(".text$03manager_dtor")
ItemManager::~ItemManager() {
 SchedulerTask* task=primary;
 FuncCtrl* scheduler=(FuncCtrl*)g_func_ctrl;
 if(task) {
  EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
  ++g_thread_synchronization.scheduler_lock_depth;
  ManagerTeardownFuncCtrl_Remove(scheduler,task);
  LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
  --g_thread_synchronization.scheduler_lock_depth;
 }
 task=secondary;
 scheduler=(FuncCtrl*)g_func_ctrl;
 if(task) {
  EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
  ++g_thread_synchronization.scheduler_lock_depth;
  ManagerTeardownFuncCtrl_Remove(scheduler,task);
  LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
  --g_thread_synchronization.scheduler_lock_depth;
 }
 g_item_manager=0;
}
#pragma code_seg()
