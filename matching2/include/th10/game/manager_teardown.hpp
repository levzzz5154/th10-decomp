// =============================================================================
// manager_teardown.hpp - Stage/manager teardown surfaces
// Retail functions: 0x00417C80, 0x0041FB50, 0x00408AF0, 0x004145F0,
//   0x00414370, 0x0042CB60, 0x0040B7B0, 0x004294A0, 0x00418EE0, 0x0040D530,
//   0x00424ED0, 0x00422220, 0x00405F70, 0x0041ADF0, 0x00409F90
// =============================================================================
#ifndef TH10_GAME_MANAGER_TEARDOWN_HPP
#define TH10_GAME_MANAGER_TEARDOWN_HPP

// Scheduler-node pair embedded in every manager (this+8 / this+0xC).
struct ManagerNodePair {
    unsigned int* update_node_flags;
    unsigned int* render_node_flags;
};

struct TeardownHooks {
    void* context;
    void (*release)(void* context, void* memory);
    void (*unregister_node)(void* context, unsigned int* node_flags);
    void (*release_texture_slot)(void* context, int slot); // 0x00447810
    void (*release_vm_list_entry)(void* context, void* vm); // +0x35C |= flag
    void (*destroy_elements)(void* context, void* base, unsigned int stride,
                             unsigned int count); // vector dtor iterator
};

// Individual manager destructors (each clears its global owner slot).
void EnemyManager_ReleaseLists(void* manager, ManagerNodePair* nodes,
                               const TeardownHooks* hooks,
                               void** vm_slots, int vm_slot_count,
                               void** list_head, int* live_count,
                               int* active_flag);
void EnemyManager_Destroy(void* manager, ManagerNodePair* nodes,
                          const TeardownHooks* hooks, void** heap_blocks,
                          int heap_block_count, int keep_textures,
                          void** owner_slot);
void StageBackground_Destroy(void* manager, ManagerNodePair* nodes,
                             const TeardownHooks* hooks, int keep_geometry,
                             void** geometry_slot, void** scratch_slot,
                             void** owner_slot);
void PauseMenu_Destroy(void* manager, ManagerNodePair* nodes,
                       const TeardownHooks* hooks, void** child_slots,
                       int child_count, void** vm_slot, void** owner_slot);
void AsciiOverlay_Destroy(void* manager, ManagerNodePair* nodes,
                          const TeardownHooks* hooks, void** child_slots,
                          int child_count, void** vm_slot,
                          void** owner_slot);
void BulletManager_Destroy(void* manager, ManagerNodePair* nodes,
                           const TeardownHooks* hooks, void* element_base,
                           unsigned int element_stride,
                           unsigned int element_count, void** owner_slot);
void ItemManager_Destroy(void* manager, ManagerNodePair* nodes,
                         const TeardownHooks* hooks, void* element_base,
                         unsigned int element_stride,
                         unsigned int element_count, void** owner_slot);
void EffectManager_Destroy(void* manager, ManagerNodePair* nodes,
                           const TeardownHooks* hooks, void* element_base,
                           unsigned int element_stride,
                           unsigned int element_count, void** owner_slot);
void PlayerManager_Destroy(void* manager, ManagerNodePair* nodes,
                           const TeardownHooks* hooks, void** owner_slot);
void BossManager_Destroy(void* manager, ManagerNodePair* nodes,
                         const TeardownHooks* hooks, void** owner_slot);
void SpellcardManager_Destroy(void* manager, ManagerNodePair* nodes,
                              const TeardownHooks* hooks, void** owner_slot);
void StageScript_Destroy(void* manager, ManagerNodePair* nodes,
                         const TeardownHooks* hooks, void** owner_slot);
void GuiManager_Destroy(void* manager, ManagerNodePair* nodes,
                        const TeardownHooks* hooks, void** child_slots,
                        int child_count, void** owner_slot);

// Full stage-transition teardown (retail 0x00417C80).
struct StageTransitionHooks {
    void* context;
    void (*save_score_file)(void* context);       // 0x0042B1E0
    void (*capture_background)(void* context);    // 0x0040C540
    void (*swap_stage_scripts)(void* context);    // 0x00418A90
    // Destroy one manager by role id; role order matches retail.
    void (*destroy_manager)(void* context, int role);
    void (*keep_alive_pass)(void* context);       // 0x00414570
    void (*queue_dummy_sound)(void* context, int mode); // 0x0043E460
    void (*clear_bullet_arena)(void* context);    // 0x873A8-dword clear
    void (*unregister_root_nodes)(void* context);
};

int StageTransition_Teardown(int game_state, int stage_index,
                             int next_stage_index, unsigned int* mode_bits,
                             const StageTransitionHooks* hooks);

#endif // TH10_GAME_MANAGER_TEARDOWN_HPP
