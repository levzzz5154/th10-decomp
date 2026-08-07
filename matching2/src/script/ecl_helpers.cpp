// ECL retail helper reconstructions used by the 0x0040E770 dispatcher.
//
// The simple resolvers and PRNG wrap the existing readable API; the
// state-only helpers (sub-entity creation, manager link, animation flag
// toggles) are best-effort stubs that record enough state for the
// dispatcher to exercise the leaf opcode shape without depending on the
// full sub-entity / animation manager state machine.
#include "th10/script/ecl.hpp"
#include <cstring>

extern "C" uint32_t ECL_DispatchOpcode(uint32_t, void*, int);
extern void* g_pGameStateManager;
extern uint8_t PTR_caseD_14f_00411de0[];
extern uint32_t DAT_00476f78;

namespace {

// PRNG state layout (mirrors FUN_0044bb90's 8-byte state at param_1):
//   bytes 0..1 : 16-bit xorshift register
//   bytes 2..3 : padding (treated as 0 in retail)
//   bytes 4..7 : 32-bit iteration count
struct ECLPrngState {
    uint16_t reg;
    uint16_t pad;
    uint32_t counter;
};

constexpr float kEclRangeHigh = 3.1415927f;
constexpr float kEclRangeLow = -3.1415927f;
constexpr float kEclRangeStep = 6.2831855f;

}  // namespace

// FUN_0044fe40 / FUN_0044ff80: float operand resolver that uses the
// caller's pre-decoded bit position and value.  Equivalent to
// ECL_ResolveFloatValue but with the bit position explicit in the
// argument list (matching the retail register layout).
float ECL_ResolveFloatAtCursor(void* cursor_pointer, unsigned int bit_index,
                               float encoded) {
    if (cursor_pointer == 0) return encoded;
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + 8);
    if (instruction == 0) return encoded;
    if ((instruction->param_mask & (1u << (bit_index & 31))) == 0)
        return encoded;
    if (encoded >= 0.0f) {
        const int32_t locals_offset =
            *reinterpret_cast<int32_t*>(cursor + 0x100c);
        return *reinterpret_cast<float*>(
            cursor + locals_offset + 8 + (int)encoded);
    }
    if (encoded != -1.0f) {
        ECLVariableResolver* resolver =
            *reinterpret_cast<ECLVariableResolver**>(cursor + 0x1014);
        if (resolver != 0)
            return resolver->ResolveFloat((int32_t)encoded);
        return encoded;
    }
    int32_t stack_top =
        *reinterpret_cast<int32_t*>(cursor + 0x1008) - 4;
    if (stack_top < 0) return encoded;
    *reinterpret_cast<int32_t*>(cursor + 0x1008) = stack_top;
    const uint32_t value = *reinterpret_cast<uint32_t*>(
        cursor + stack_top + 8);
    stack_top -= 4;
    *reinterpret_cast<int32_t*>(cursor + 0x1008) = stack_top;
    const char type = *reinterpret_cast<char*>(
        cursor + stack_top + 8);
    if (type == 'f') {
        float decoded;
        std::memcpy(&decoded, &value, sizeof(decoded));
        return decoded;
    }
    return (float)(int32_t)value;
}

// FUN_0044ff00 (int variant) and FUN_00412a10 (int destination).  This
// helper exists for symmetry with ECL_ResolveFloatAtCursor and is used
// by the int-family opcodes that decode their own operand bit.
int32_t ECL_ResolveIntAtCursor(void* cursor_pointer, unsigned int bit_index,
                                int32_t encoded) {
    if (cursor_pointer == 0) return encoded;
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + 8);
    if (instruction == 0) return encoded;
    if ((instruction->param_mask & (1u << (bit_index & 31))) == 0)
        return encoded;
    if (encoded >= 0) {
        const int32_t locals_offset =
            *reinterpret_cast<int32_t*>(cursor + 0x100c);
        return *reinterpret_cast<int32_t*>(
            cursor + locals_offset + 8 + encoded);
    }
    if (encoded != -1) {
        ECLVariableResolver* resolver =
            *reinterpret_cast<ECLVariableResolver**>(cursor + 0x1014);
        if (resolver != 0)
            return resolver->ResolveInt(encoded);
        return encoded;
    }
    int32_t stack_top =
        *reinterpret_cast<int32_t*>(cursor + 0x1008) - 4;
    if (stack_top < 0) return encoded;
    *reinterpret_cast<int32_t*>(cursor + 0x1008) = stack_top;
    const int32_t value = *reinterpret_cast<int32_t*>(
        cursor + stack_top + 8);
    stack_top -= 4;
    *reinterpret_cast<int32_t*>(cursor + 0x1008) = stack_top;
    const char type = *reinterpret_cast<char*>(
        cursor + stack_top + 8);
    if (type == 'f') {
        float decoded;
        std::memcpy(&decoded, &value, sizeof(decoded));
        return (int32_t)decoded;
    }
    return value;
}

// FUN_0044bb90: xorshift-style PRNG.  The retail stores a 16-bit state
// and a 32-bit iteration counter at param_1, and returns a float in
// (-pi, pi].
float ECL_PrngFloat(void* state) {
    if (state == 0) return 0.0f;
    ECLPrngState* s = static_cast<ECLPrngState*>(state);
    const uint32_t mixed = ((uint32_t)s->reg ^ 0x9630u) - 0x6553u;
    const int32_t shifted =
        (int32_t)((mixed >> 14) & 3u) + (int32_t)(mixed * 4u);
    uint16_t u1 = (uint16_t)shifted;
    uint16_t u2 = (uint16_t)((u1 ^ 0x9630u) + 0x9aadu);
    s->reg = u2 * 4u + (u2 >> 14);
    s->counter += 2;
    int32_t combined = (shifted << 16) | (int32_t)s->reg;
    double value = (double)combined;
    if (combined < 0)
        value += 4.294967296e9;  // 2^32
    return (float)(value * (1.0 / 4294967296.0) * kEclRangeStep - 3.1415927f);
}

// FUN_0044bc70: in-place wrap of an angle into (-pi, pi].  The retail
// subtracts 2*pi up to 32 times until the value drops below pi, then
// adds 2*pi up to 32 times until the value rises above -pi.
void ECL_WrapValue(float* value) {
    if (value == 0) return;
    int iterations = 0;
    while (*value > kEclRangeHigh) {
        *value -= kEclRangeStep;
        if (++iterations > 0x20) break;
    }
    iterations = 0;
    while (*value < kEclRangeLow) {
        *value += kEclRangeStep;
        if (++iterations > 0x20) break;
    }
}

void ECL_PrngSeed(void* state, unsigned short seed) {
    if (state == 0) return;
    ECLPrngState* s = static_cast<ECLPrngState*>(state);
    s->reg = seed;
    s->pad = 0;
    s->counter = 0;
}

// FUN_00412db0 / FUN_004050d0: lazy-init a movement/laser record and
// reset its 0x10-byte block to "armed" state.  The retail uses this
// pattern for both the per-axis movement record (offsets 0x20/0x30)
// and the per-bullet spawn record (offsets 0x30/0x40).
void ECL_InitMovementRecord(void* record) {
    if (record == 0) return;
    uint8_t* bytes = static_cast<uint8_t*>(record);
    uint32_t* flags = reinterpret_cast<uint32_t*>(bytes + 0x30);
    if ((*flags & 1u) == 0) {
        *reinterpret_cast<int32_t*>(bytes + 0x24) = 0;
        *reinterpret_cast<int32_t*>(bytes + 0x20) = 0xfff0bdc1;
        *reinterpret_cast<int32_t*>(bytes + 0x28) = 0;
        *reinterpret_cast<uint32_t**>(bytes + 0x2c) =
            reinterpret_cast<uint32_t*>(&DAT_00476f78);
        *flags |= 1u;
    }
    *reinterpret_cast<int32_t*>(bytes + 0x24) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x28) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x20) = 0xffffffff;
}

void ECL_InitBulletRecord(void* record) {
    if (record == 0) return;
    uint8_t* bytes = static_cast<uint8_t*>(record);
    uint32_t* flags = reinterpret_cast<uint32_t*>(bytes + 0x40);
    if ((*flags & 1u) == 0) {
        *reinterpret_cast<int32_t*>(bytes + 0x34) = 0;
        *reinterpret_cast<int32_t*>(bytes + 0x30) = 0xfff0bdc1;
        *reinterpret_cast<int32_t*>(bytes + 0x38) = 0;
        *reinterpret_cast<uint32_t**>(bytes + 0x3c) =
            reinterpret_cast<uint32_t*>(&DAT_00476f78);
        *flags |= 1u;
    }
    *reinterpret_cast<int32_t*>(bytes + 0x34) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x38) = 0;
    *reinterpret_cast<int32_t*>(bytes + 0x30) = 0xffffffff;
}

// FUN_00413170: store the wrapped Z position at record+0x1c.
void ECL_SetPositionZWithWrap(void* record, float value) {
    if (record == 0) return;
    ECL_WrapValue(&value);
    *reinterpret_cast<float*>(
        static_cast<uint8_t*>(record) + 0x1c) = value;
}

namespace {

// Storage for the most recent sub-entity create request.  The tests
// inspect this to verify the dispatcher invoked the right helper.
ECLSubEntityRequest g_last_sub_entity;

}  // namespace

// FUN_00448e30 (mode 5) and FUN_00448d00 (mode 6) and FUN_00448e30
// alternate (mode 7).  Retail allocates a new sub-entity record and
// links it to the manager; the readable stub records the request.
ECLSubEntityRequest* ECL_SubEntityCreate(int32_t slot, int32_t sub_index,
                                         int32_t mode) {
    g_last_sub_entity.slot = slot;
    g_last_sub_entity.sub_index = sub_index;
    g_last_sub_entity.mode = mode;
    g_last_sub_entity.record = 0;
    return &g_last_sub_entity;
}

const ECLSubEntityRequest* ECL_LastSubEntityRequest(void) {
    return &g_last_sub_entity;
}

namespace {

int32_t g_last_mark_slot = -1;

}  // namespace

// FUN_00449450: lookup the sub-entity record by slot id.  Retail returns
// the record pointer; the stub returns the slot id so a test can assert
// that the dispatcher called the right helper.
int32_t ECL_SubEntityMark(int32_t slot) {
    g_last_mark_slot = slot;
    return slot;
}

void ECL_AnimationFlagSet(void) {
    // FUN_004495e0: increment the ECL-flag counter.  The readable
    // dispatcher handles the high-level flagging inline; this stub
    // exists so opcode-level smoke tests can link.
}

void ECL_AnimationFlagClear(void) {
    // FUN_00449590: decrement the ECL-flag counter.
}

void ECL_AddToActiveList(void* manager, void* sub_entity) {
    // FUN_0040cfb0: append the sub-entity to the manager's active
    // list.  The readable version is a no-op until the manager state
    // machine is reconstructed.
    (void)manager;
    (void)sub_entity;
}

void* ECL_FindByID(int32_t id) {
    // FUN_0040cf90: lookup a manager-owned record by its 32-bit id.
    (void)id;
    return 0;
}

void ECL_ReleaseByID(int32_t id) {
    // FUN_0040cf60: release a manager-owned record by its 32-bit id.
    (void)id;
}

void ECL_ApplyEclFlag(void) {
    // FUN_0040cea0: set the manager's 0x10 bit and dispatch the
    // sound-queue helper.  The readable version drives this from the
    // 0x16a opcode.
}

void ECL_ApplyEclFlagAlt(void) {
    // FUN_0040c9a0: same idea, called by 0x149.
}

void ECL_RangeReset(void) {
    // FUN_0040e6a0: clear the manager's range state, called by 0x152
    // and 0x159.
}
