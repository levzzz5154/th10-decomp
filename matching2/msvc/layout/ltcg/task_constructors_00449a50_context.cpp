#include "../../src/core/zunlib/task_constructors_00449a50.cpp"
inline void* __cdecl operator new(unsigned int, void* memory) { return memory; }
#pragma code_seg(".text$03context")
extern "C" void __stdcall TaskConstructorContext(EmptyTask* empty, RoutineTask* routine, TaskRoutine callback, int count) {
 for(int i=0;i<count;++i) { new(&empty[i]) EmptyTask; new(&routine[i]) RoutineTask(callback); }
}
#pragma code_seg()
