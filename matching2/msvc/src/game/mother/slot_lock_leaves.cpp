extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

struct SlotLockManager {
    unsigned char reserved_000[0x64c];

    __declspec(noinline) void Leave(int index);
};

#pragma code_seg(".text$01leave")
void SlotLockManager::Leave(int index) {
    imp_LeaveCriticalSection((unsigned char*)this + 0x64c + index * 0x18);
    ((unsigned char*)this + 0x6f4)[index]--;
}
#pragma code_seg()
