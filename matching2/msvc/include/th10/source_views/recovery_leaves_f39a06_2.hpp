#pragma once


// 0x0040CC50 - the enemy's scalar deleting destructor (vtable 0x0046D0C0
// slot 0x14): run the enemy destructor (0x0040DAE0), then free it on request.
// The delete flag is the retail first stack argument, so the second __fastcall
// register argument (EDX) is unused. The destructor is called through its
// fixed retail prototype.
typedef void (__stdcall* EnemyDestroyFn)(void* enemy);

