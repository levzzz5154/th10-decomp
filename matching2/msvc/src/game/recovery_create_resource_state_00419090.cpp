// 0x00419090..0x004190D2 (67 bytes): Recovery_CreateResourceState
struct StageTipManager_00419090 {
    unsigned char bytes[0x1A8];
};

void* __cdecl operator new(unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" void* __fastcall Construct_00418d40(int unused, StageTipManager_00419090* manager);
extern "C" int __stdcall asm_StageTipRuntime_InitializeRetail_00418e30(
        StageTipManager_00419090* manager);
extern "C" void __stdcall asm_FUN_00418ee0_00418ee0(void* manager);

extern "C" __declspec(noinline) StageTipManager_00419090* __cdecl
asm_Recovery_CreateResourceState_00419090();
#pragma code_seg(".text$00d_fcreate")
extern "C" __declspec(noinline) StageTipManager_00419090* __cdecl
asm_Recovery_CreateResourceState_00419090() {
    StageTipManager_00419090* block = new StageTipManager_00419090;
    StageTipManager_00419090* manager;
    if (block)
        manager = (StageTipManager_00419090*)Construct_00418d40(0, block);
    else
        manager = 0;
    if (asm_StageTipRuntime_InitializeRetail_00418e30(manager)) {
        if (manager) {
            asm_FUN_00418ee0_00418ee0(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
