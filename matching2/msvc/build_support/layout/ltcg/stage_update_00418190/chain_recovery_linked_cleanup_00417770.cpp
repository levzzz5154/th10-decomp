#define g_sprt_ctrl stage_chain_g_sprt_ctrl
#define g_front stage_chain_g_front
#define g_globals stage_chain_data_00474c40
#define g_ascii_manager stage_chain_data_004776e0
#define g_enemy_ctrl stage_chain_g_enemy_ctrl
#define g_player stage_chain_data_00477834
#define g_replay stage_chain_data_00477838
#define g_score stage_chain_data_0047783c
#define g_game_speed stage_chain_data_00476f78
#define g_stage_flags stage_chain_data_00491fc4
#define g_main_state stage_chain_data_00491fb8
#define g_sound_manager stage_chain_data_00492590
// Variant A: member with the container walk, head cached in a local.
extern "C" void __cdecl crt_free_startup(void* memory);

struct LinkedNode {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Release();
    virtual void Slot5(void* arg);

    LinkedNode* prev;
    LinkedNode* next;
    int state;
};

struct ScoreChain {
    unsigned char reserved_000[0x18];
    LinkedNode* head;

    __declspec(noinline) void ReleaseChain();
};

#pragma code_seg(".text$00417770_fn")
void ScoreChain::ReleaseChain() {
    LinkedNode* node = head;
    while (node != 0) {
        LinkedNode* next = node->next;
        node->Release();
        node->prev->next = node->next;
        if (node->next != 0)
            node->next->prev = node->prev;
        crt_free_startup(node);
        node = next;
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
