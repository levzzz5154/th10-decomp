#include "anm_storage_construct_entity.cpp"
#include "../../src/app/anm_storage_construct_00445900.cpp"
inline void* __cdecl operator new(unsigned int, AnmStorageConstruct_00445900& storage) { return &storage; }
#pragma code_seg(".text$02context")
extern "C" AnmStorageConstruct_00445900* __stdcall ConstructAnmStorageContext(AnmStorageConstruct_00445900* storage) { return new(*storage) AnmStorageConstruct_00445900; }
#pragma code_seg()
