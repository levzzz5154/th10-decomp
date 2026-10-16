// Compiler-visibility context for the real allocator edges in the pause
// initializer. This includes the maintained semantic callee body used by
// AnimationPool::Allocate's heap fallback; it adds no synthetic caller.
#pragma code_seg(".text$01entity")
#include "../../contexts/legacy/game/entity_initialize.cpp"
#pragma code_seg()
