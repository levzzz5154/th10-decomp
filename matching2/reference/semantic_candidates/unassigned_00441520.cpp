#include "asm_symbols.hpp"

#include <cstdint>

// 0x00441520..0x00441580: apply a 16-bit state to each entity whose animation
// handle resolves to a resource with a non-null payload.
//
// Retail's private entry ABI is not represented by this ordinary C++ signature:
// EAX supplies entity_count, ECX supplies entity_base, and the low word of the
// stack argument supplies state_value.  The function returns with RET 4.  This
// signature is a readable model for analysis, not an ABI-compatible replacement.
extern "C" void __cdecl asm_unassigned_00441520(
    unsigned char* entity_base,
    std::uint32_t entity_count,
    std::uint16_t state_value) {
    const std::uint32_t kEntityStride = 0x3AC;
    const std::uint32_t kAnimationHandleOffset = 0x394;
    const std::uint32_t kStateOffset = 0x304;
    const std::uint32_t kResourceSlotsOffset = 0x3AD06C;
    const std::uint32_t kResourcePayloadOffset = 0x120;

    // Retail branches out before loading the global manager when EAX is zero.
    if (entity_count == 0)
        return;

    // Retail loads the animation-manager pointer stored at data_00491c10.
    unsigned char* manager = *reinterpret_cast<unsigned char**>(&data_00491c10);
    void** resource_slots = reinterpret_cast<void**>(
        manager + kResourceSlotsOffset);

    // Retail decrements the 32-bit count until it reaches zero.  Keeping the
    // remaining count unsigned also models the register loop for any nonzero
    // EAX value, including values with the high bit set.
    std::uint32_t remaining = entity_count;
    unsigned char* entity = entity_base;
    while (remaining != 0) {
        void* animation_handle = *reinterpret_cast<void**>(
            entity + kAnimationHandleOffset);

        if (animation_handle != 0) {
            const std::int32_t resource_id =
                *reinterpret_cast<const std::int32_t*>(animation_handle);

            // The retail code rejects negative IDs, then indexes the global
            // resource-slot table directly.  It does not check an upper bound.
            if (resource_id >= 0) {
                void* resource = resource_slots[resource_id];
                if (resource != 0) {
                    unsigned char* resource_bytes =
                        static_cast<unsigned char*>(resource);
                    void* payload = *reinterpret_cast<void**>(
                        resource_bytes + kResourcePayloadOffset);
                    if (payload != 0) {
                        *reinterpret_cast<std::uint16_t*>(
                            entity + kStateOffset) = state_value;
                    }
                }
            }
        }

        entity += kEntityStride;
        --remaining;
    }
}
