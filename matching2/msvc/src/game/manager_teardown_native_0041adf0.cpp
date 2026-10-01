#include "th10/game/manager_teardown_native_0041adf0.hpp"
#pragma code_seg(".text$03manager_dtor")
NativeEffectManager_0041ADF0::~NativeEffectManager_0041ADF0() {
 SchedulerTask* task=primary;
 Scheduler* scheduler=(Scheduler*)data_00491be4;
 if(task) {
  EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
  ++g_thread_synchronization.scheduler_lock_depth;
  ManagerTeardownScheduler_Remove_00449F60(scheduler,task);
  LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
  --g_thread_synchronization.scheduler_lock_depth;
 }
 task=secondary;
 scheduler=(Scheduler*)data_00491be4;
 if(task) {
  EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
  ++g_thread_synchronization.scheduler_lock_depth;
  ManagerTeardownScheduler_Remove_00449F60(scheduler,task);
  LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
  --g_thread_synchronization.scheduler_lock_depth;
 }
 data_00477818=0;
}
#pragma code_seg()
