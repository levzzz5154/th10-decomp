// 0x0043DDB0..0x0043DDE3: 12-slot key lookup/update.
// The retail body takes its owner in ESI and the key in EDI.  This ordinary
// C++ signature is a readable behavioral model; it uses the normal C calling
// convention and does not reproduce that private register ABI.
struct KeySlotSearchOwner_0043DDB0 {
    unsigned char unknown_0000_061F[0x620];
    int key_slots[12];
    int paired_flags[12];
};

extern "C" void __cdecl asm_unassigned_0043ddb0(
    KeySlotSearchOwner_0043DDB0* owner,
    int key) {
    for (int index = 0; index < 12; ++index) {
        const int slot_key = owner->key_slots[index];

        if (slot_key < 0) {
            owner->key_slots[index] = key;
            owner->paired_flags[index] = -1;
            return;
        }

        if (slot_key == key) {
            owner->paired_flags[index] = -1;
            return;
        }
    }
}
