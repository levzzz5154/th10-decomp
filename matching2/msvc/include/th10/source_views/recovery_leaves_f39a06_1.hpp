#pragma once


// The installer takes the state as its only stack argument and cleans it, so
// the recovered call keeps the retail push/callee-clean shape.
typedef int (__stdcall* SmallStateInstallFn)(void* state);
typedef void (__stdcall* SmallStateReleaseFn)(void* state);

