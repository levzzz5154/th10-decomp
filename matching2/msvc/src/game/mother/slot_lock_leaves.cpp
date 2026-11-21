// 0x00421C50: SlotLockManager::Leave
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

struct SlotLockManager {
    unsigned char reserved_000[0x64c];
    unsigned char critical_sections[6][0x18];
    unsigned char reserved_6DC[0x18];
    unsigned char lock_depth[6];

    __declspec(noinline) void Leave(int index);
};

#pragma code_seg(".text$01leave")
void SlotLockManager::Leave(int index) {
    imp_LeaveCriticalSection(critical_sections[index]);
    --lock_depth[index];
}
#pragma code_seg()
