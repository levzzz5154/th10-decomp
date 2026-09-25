// Semantic model of retail 0x00430250. The retail entry receives the key
// config object, slot index, and new key in private EAX/ECX/EDX registers;
// this readable interface makes those inputs explicit and injects the two
// observed side effects as callbacks.

struct KeyConfigState_00430250 {
    unsigned char unknown_prefix[0x59CC];
    short bindings[5];
};

typedef void (*RefreshKeyBindingLabels_00430250)(KeyConfigState_00430250* state);
typedef void (*QueueKeyConfigResource_00430250)(unsigned int manager_address,
                                                 unsigned int resource_id,
                                                 unsigned int argument);

// 0x00430250: replace one of the five key bindings. When the requested key is
// already assigned to another slot, that slot receives this slot's old key.
extern "C" void __cdecl asm_KeyConfig_ReassignSlotRetail_00430250(
    KeyConfigState_00430250* state,
    int slot_index,
    int new_key,
    RefreshKeyBindingLabels_00430250 refresh_labels,
    QueueKeyConfigResource_00430250 queue_resource) {
    const short old_key = state->bindings[slot_index];
    if (old_key == new_key) {
        return;
    }

    for (int other_index = 0; other_index < 5; ++other_index) {
        if (other_index != slot_index &&
            state->bindings[other_index] == new_key) {
            state->bindings[other_index] = old_key;
        }
    }

    state->bindings[slot_index] = static_cast<short>(new_key);

    // Retail calls 0x0042F8B0 with the config object in EAX; that helper
    // refreshes the displayed labels for the five bindings.
    refresh_labels(state);

    // Retail then calls 0x0043DC90 with ECX=0x00492590, EDI=10, and a stack
    // argument of zero. Keep those values explicit at the semantic boundary.
    queue_resource(0x00492590, 10, 0);
}
