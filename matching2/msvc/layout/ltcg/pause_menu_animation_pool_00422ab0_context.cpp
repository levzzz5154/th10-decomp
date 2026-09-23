// Compiler-visibility context for the real allocator edges in the pause
// initializer. This includes the maintained semantic callee body used by
// AnimationPool::Allocate's heap fallback; it adds no synthetic caller.
#pragma code_seg(".text$01entity")
#include "../../src/game/entity_initialize_00401de0.cpp"
#pragma code_seg()
