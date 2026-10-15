#define g_sprt_ctrl stage_chain_g_sprt_ctrl
#define g_front stage_chain_g_front
#define data_00474c40 stage_chain_data_00474c40
#define g_ascii_manager stage_chain_data_004776e0
#define g_enemy_ctrl stage_chain_g_enemy_ctrl
#define g_player stage_chain_data_00477834
#define data_00477838 stage_chain_data_00477838
#define data_0047783c stage_chain_data_0047783c
#define data_00476f78 stage_chain_data_00476f78
#define data_00491fc4 stage_chain_data_00491fc4
#define data_00491fb8 stage_chain_data_00491fb8
#define data_00492590 stage_chain_data_00492590
// Variant A: member with the container walk, head cached in a local.
extern "C" void __cdecl entry_free_004524a1(void* memory);

struct LinkedNode_00417770 {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Release();
    virtual void Slot5(void* arg);

    LinkedNode_00417770* prev;
    LinkedNode_00417770* next;
    int state;
};

struct ScoreChain_00417770 {
    unsigned char reserved_000[0x18];
    LinkedNode_00417770* head;

    __declspec(noinline) void ReleaseChain();
};

#pragma code_seg(".text$00417770_fn")
void ScoreChain_00417770::ReleaseChain() {
    LinkedNode_00417770* node = head;
    while (node != 0) {
        LinkedNode_00417770* next = node->next;
        node->Release();
        node->prev->next = node->next;
        if (node->next != 0)
            node->next->prev = node->prev;
        entry_free_004524a1(node);
        node = next;
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
