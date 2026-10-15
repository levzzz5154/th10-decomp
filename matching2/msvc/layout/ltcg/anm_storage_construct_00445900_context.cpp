#include "anm_storage_construct_entity.cpp"
#include "../../src/core/sprtlib/sprt_ctrl_construct.cpp"
inline void* __cdecl operator new(unsigned int, SprtCtrl& storage) { return &storage; }
#pragma code_seg(".text$02context")
extern "C" SprtCtrl* __stdcall ConstructAnmStorageContext(SprtCtrl* storage) { return new(*storage) SprtCtrl; }
#pragma code_seg()
