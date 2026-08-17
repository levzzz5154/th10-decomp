// =============================================================================
// manager_teardown.cpp - Stage/manager teardown chain
// =============================================================================
#include "th10/game/manager_teardown.hpp"


namespace {

void ClearNodePair(ManagerNodePair* nodes) {
    // Retail clears bit 1 on both scheduler nodes so the scheduler drops
    // them on the next pass without a full unregister.
    if (nodes->update_node_flags != 0)
        *nodes->update_node_flags &= ~2u;
    if (nodes->render_node_flags != 0)
        *nodes->render_node_flags &= ~2u;
}

void UnregisterNodePair(ManagerNodePair* nodes, const TeardownHooks* hooks) {
    hooks->unregister_node(hooks->context, nodes->update_node_flags);
    hooks->unregister_node(hooks->context, nodes->render_node_flags);
}

} // namespace

// 0x00409F90 - EnemyManager_ReleaseLists: detach the four aux VM slots from
// the manager render lists, invoke the release vtable entry on every live
// enemy node, and clear the live counters. The scheduler nodes only have
// their active bit cleared (full unregister happens in the destructor).
void EnemyManager_ReleaseLists(void* manager, ManagerNodePair* nodes,
                               const TeardownHooks* hooks,
                               void** vm_slots, int vm_slot_count,
                               void** list_head, int* live_count,
                               int* active_flag) {
    (void)manager;
    for (int slot = 0; slot < vm_slot_count; ++slot)
        hooks->release_vm_list_entry(hooks->context, vm_slots[slot]);
    while (*list_head != 0) {
        void** node = static_cast<void**>(*list_head);
        void* enemy = node[0];
        *list_head = node[1];
        hooks->release(hooks->context, enemy); // vtable slot +0x14 with (1)
    }
    *live_count = 0;
    *active_flag = 0;
    ClearNodePair(nodes);
}

// 0x0040D530 - EnemyManager_Destroy: full destructor. Runs the list release,
// unregisters both scheduler nodes, frees the per-difficulty heap blocks,
// releases the four enemy texture slots (unless a snapshot pass keeps
// textures alive), and clears the global owner pointer (DAT_00477704).
void EnemyManager_Destroy(void* manager, ManagerNodePair* nodes,
                          const TeardownHooks* hooks, void** heap_blocks,
                          int heap_block_count, int keep_textures,
                          void** owner_slot) {
    static void* no_list = 0;
    static int zero_count = 0, zero_flag = 0;
    no_list = 0; zero_count = 0; zero_flag = 0;
    EnemyManager_ReleaseLists(manager, nodes, hooks, &no_list, 0, &no_list,
                              &zero_count, &zero_flag);
    UnregisterNodePair(nodes, hooks);
    for (int block = 0; block < heap_block_count; ++block) {
        hooks->release(hooks->context, heap_blocks[block]);
        heap_blocks[block] = 0;
    }
    if (keep_textures == 0)
        for (int slot = 9; slot <= 0xC; ++slot)
            hooks->release_texture_slot(hooks->context, slot);
    *owner_slot = 0;
}

// 0x00424ED0 - StageBackground_Destroy: unregister the node pair, then
// either release the stage geometry (normal teardown) or park it in the
// keep-alive slot (DAT_00491BF0) when the snapshot pass owns it.
void StageBackground_Destroy(void* manager, ManagerNodePair* nodes,
                             const TeardownHooks* hooks, int keep_geometry,
                             void** geometry_slot, void** scratch_slot,
                             void** owner_slot) {
    (void)manager;
    UnregisterNodePair(nodes, hooks);
    *owner_slot = 0;
    if (keep_geometry == 0) {
        hooks->release_texture_slot(hooks->context, 8); // mgr+0x3AD08C slot
        hooks->release(hooks->context, *geometry_slot);
        *geometry_slot = 0;
    }
    hooks->release(hooks->context, *scratch_slot);
    *scratch_slot = 0;
}

// 0x00422220 - PauseMenu_Destroy: destroy the 0x19 child widgets, mark the
// pause-snapshot VM for reclamation in the manager ANM lists, and clear the
// owner pointer (DAT_00477830).
void PauseMenu_Destroy(void* manager, ManagerNodePair* nodes,
                       const TeardownHooks* hooks, void** child_slots,
                       int child_count, void** vm_slot, void** owner_slot) {
    (void)manager;
    UnregisterNodePair(nodes, hooks);
    for (int slot = 0; slot < child_count; ++slot) {
        hooks->release(hooks->context, child_slots[slot]);
        child_slots[slot] = 0;
    }
    if (*vm_slot != 0) {
        hooks->release_vm_list_entry(hooks->context, *vm_slot);
        *vm_slot = 0;
    }
    *owner_slot = 0;
}

// 0x00418EE0 - AsciiOverlay_Destroy: same child-slot sweep as the pause
// menu (retail shares the loop shape after LAB_00418FF1) for the text
// overlay manager (DAT_00477814).
void AsciiOverlay_Destroy(void* manager, ManagerNodePair* nodes,
                          const TeardownHooks* hooks, void** child_slots,
                          int child_count, void** vm_slot,
                          void** owner_slot) {
    PauseMenu_Destroy(manager, nodes, hooks, child_slots, child_count,
                      vm_slot, owner_slot);
}

// 0x0041ADF0 - BulletManager_Destroy: run the element destructor over the
// 0x896-entry bullet array (stride 0x3F0, retail dtor 0x0041AD60), then
// unregister and clear the owner (DAT_00477818).
void BulletManager_Destroy(void* manager, ManagerNodePair* nodes,
                           const TeardownHooks* hooks, void* element_base,
                           unsigned int element_stride,
                           unsigned int element_count, void** owner_slot) {
    (void)manager;
    hooks->destroy_elements(hooks->context, element_base, element_stride,
                            element_count);
    UnregisterNodePair(nodes, hooks);
    *owner_slot = 0;
}

// 0x00405F70 - ItemManager_Destroy: element sweep over the 0x7D1-entry item
// array (stride 0x7F0, retail dtor 0x00405DE0); owner DAT_004776F0.

void ItemManager_Destroy(void* manager, ManagerNodePair* nodes,
                         const TeardownHooks* hooks, void* element_base,
                         unsigned int element_stride,
                         unsigned int element_count, void** owner_slot) {
    BulletManager_Destroy(manager, nodes, hooks, element_base,
                          element_stride, element_count, owner_slot);
}

// 0x004294A0 - EffectManager_Destroy: eight-entry effect pool (stride 0x24,
// retail dtor LAB_0042AC60); owner DAT_00477838.
void EffectManager_Destroy(void* manager, ManagerNodePair* nodes,
                           const TeardownHooks* hooks, void* element_base,
                           unsigned int element_stride,
                           unsigned int element_count, void** owner_slot) {
    BulletManager_Destroy(manager, nodes, hooks, element_base,
                          element_stride, element_count, owner_slot);
}

// 0x004145F0 - PlayerManager_Destroy: unregister + owner clear
// (DAT_0047770C); the player VM slots are reclaimed by the ANM sweep.
void PlayerManager_Destroy(void* manager, ManagerNodePair* nodes,
                           const TeardownHooks* hooks, void** owner_slot) {
    (void)manager;
    UnregisterNodePair(nodes, hooks);
    *owner_slot = 0;
}

// 0x00414370 - BossManager_Destroy: identical unregister + owner clear for
// the boss coordinator.
void BossManager_Destroy(void* manager, ManagerNodePair* nodes,
                         const TeardownHooks* hooks, void** owner_slot) {
    PlayerManager_Destroy(manager, nodes, hooks, owner_slot);
}

// 0x0042CB60 - SpellcardManager_Destroy: identical unregister + owner clear
// for the spellcard bookkeeping manager (DAT_00477840 family).
void SpellcardManager_Destroy(void* manager, ManagerNodePair* nodes,
                              const TeardownHooks* hooks,
                              void** owner_slot) {
    PlayerManager_Destroy(manager, nodes, hooks, owner_slot);
}

// 0x0040B7B0 - StageScript_Destroy: identical unregister + owner clear for
// the stage-script driver (DAT_004776FC).
void StageScript_Destroy(void* manager, ManagerNodePair* nodes,
                         const TeardownHooks* hooks, void** owner_slot) {
    PlayerManager_Destroy(manager, nodes, hooks, owner_slot);
}

// 0x0041FB50 - GuiManager_Destroy: destroy the HUD child widgets then
// unregister + owner clear (DAT_0047781C family).
void GuiManager_Destroy(void* manager, ManagerNodePair* nodes,
                        const TeardownHooks* hooks, void** child_slots,
                        int child_count, void** owner_slot) {
    (void)manager;
    for (int slot = 0; slot < child_count; ++slot) {
        hooks->release(hooks->context, child_slots[slot]);
        child_slots[slot] = 0;
    }
    UnregisterNodePair(nodes, hooks);
    *owner_slot = 0;
}

// 0x00417C80 - StageTransition_Teardown: the state-driven teardown that runs
// between stages, on game over, and on return to title. Computes the mode
// bits from the game state, saves the score file, tears down every stage
// manager in retail order (respecting keep-alive modes), queues the dummy
// sound, and clears the bullet arena.
int StageTransition_Teardown(int game_state, int stage_index,
                             int next_stage_index, unsigned int* mode_bits,
                             const StageTransitionHooks* hooks) {
    hooks->save_score_file(hooks->context);
    *mode_bits &= ~3u;

    switch (game_state) {
    case 10: // stage clear: keep results visible
        if (stage_index == next_stage_index)
            *mode_bits |= 1u;
        break;
    case 0xB: // continue screen: capture the background, keep managers
        hooks->capture_background(hooks->context);
        *mode_bits |= 2u;
        break;
    case 4:
    case 0xF: // pause/retry snapshot
        hooks->capture_background(hooks->context);
        break;
    case 0xD: // next-stage handoff
        hooks->capture_background(hooks->context);
        if (stage_index != next_stage_index) {
            hooks->swap_stage_scripts(hooks->context);
            *mode_bits |= 8u;
        }
        break;
    default:
        break;
    }
    *mode_bits |= 1u;

    if ((*mode_bits & 2u) == 0) {
        // Full teardown, retail role order: effects, replay pair, pause
        // menu, player, stage background, items, bullets, HUD, overlay.
        static const int kRoleOrder[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int role : kRoleOrder)
            hooks->destroy_manager(hooks->context, role);
        hooks->clear_bullet_arena(hooks->context);
    } else {
        hooks->keep_alive_pass(hooks->context); // 0x00414570
    }

    // Enemy manager: full destroy unless a keep-alive bit holds it.
    hooks->destroy_manager(hooks->context, (*mode_bits & 9u) == 0 ? 10 : 11);
    // Stage script, boss, enemy-script managers always go down. Role 14 is
    // 0x00408AF0 (DAT_004776F4): destroy the scheduler objects at +0x768/
    // +0x76C/+0x770, release the +8/+0xC/+0x37AC heap nodes under the
    // critical section, vector-destruct the 5/8/2 element arrays (stride
    // 0x3AC), and clear the owner.
    hooks->destroy_manager(hooks->context, 12);
    hooks->destroy_manager(hooks->context, 13);
    hooks->destroy_manager(hooks->context, 14);
    hooks->unregister_root_nodes(hooks->context);

    if ((*mode_bits & 0x22u) == 0)
        hooks->queue_dummy_sound(hooks->context, 0);
    return 0;
}
