// Native-LTCG primary-back intrusive animation-list registration.
__forceinline int NextAnimationId_004489d0(unsigned char* manager) {
    int id = ++*(int*)(manager + 0x732454);
    if (id == 0) { id = ++*(int*)(manager + 0x732454); }
    return *(int*)(manager + 0x732454);
}
#pragma code_seg(".text$03regprimary")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    void** node = (void**)(e + 0x04);
    node[0] = e; node[1] = 0; node[2] = 0;
    void* head = *(void**)(m + 0x72DAD4);
    if (head == 0) { *(void**)(m + 0x72DAD4) = node; }
    else {
        unsigned char* tail = *(unsigned char**)(m + 0x72DAD8);
        unsigned char* next = *(unsigned char**)(tail + 0x04);
        if (next != 0) {
            node[1] = next;
            unsigned char* linked_next = *(unsigned char**)(tail + 0x04);
            *(unsigned char**)(linked_next + 0x08) = (unsigned char*)node;
        }
        *(unsigned char**)(tail + 0x04) = (unsigned char*)node;
        node[2] = tail;
    }
    *(void**)(m + 0x72DAD8) = node;
    *(int*)(e + 0x00) = NextAnimationId_004489d0(m);
    *(int*)out = *(int*)(m + 0x732454);
    return out;
}
#pragma code_seg()
