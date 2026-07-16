// ECL (Enemy Control Language) VM dispatch, retail address 0x0040E770.
#include "th10/script/ecl.hpp"

extern "C" {
uint32_t FUN_0044fdb0(uint32_t dispatch_index, void* cursor, int operand);
void FUN_00449590(void);
void FUN_004495e0(void);
}

extern uint8_t PTR_caseD_14f_00411de0[];
extern float DAT_00470b04; // zero: first local-variable encoding
extern float DAT_00470b60; // -1: pop from the ECL argument stack

namespace {

const unsigned int kFlagsOffset = 0x1444;
const unsigned int kBoundaryOffset = 0x13ac;
const unsigned int kDifficultySlotsOffset = 0x13d0;
const unsigned int kArgumentStackTopOffset = 0x1008;
const unsigned int kLocalVariablesOffset = 0x100c;
const unsigned int kVariableResolverOffset = 0x1014;
const uint32_t kMovementBoundaryEnabled = 0x200;

float& EntityFloat(void* entity, unsigned int offset) {
    return *reinterpret_cast<float*>(static_cast<uint8_t*>(entity) + offset);
}

float BitsFloat(uint32_t value) {
    union FloatAndBits {
        float as_float;
        uint32_t as_bits;
    } converted;
    converted.as_bits = value;
    return converted.as_float;
}

uint32_t& EntityFlags(void* entity) {
    return *reinterpret_cast<uint32_t*>(
        static_cast<uint8_t*>(entity) + kFlagsOffset);
}

ECLMovementBoundary& EntityBoundary(void* entity) {
    return *reinterpret_cast<ECLMovementBoundary*>(
        static_cast<uint8_t*>(entity) + kBoundaryOffset);
}

uint32_t* EntityDifficultySlots(void* entity) {
    return reinterpret_cast<uint32_t*>(
        static_cast<uint8_t*>(entity) + kDifficultySlotsOffset);
}

int32_t& EntityInt(void* entity, unsigned int offset) {
    return *reinterpret_cast<int32_t*>(static_cast<uint8_t*>(entity) + offset);
}

} // namespace

uint32_t ECL_SetFlags(void* entity, uint32_t flags) {
    EntityFlags(entity) |= flags;
    return EntityFlags(entity);
}

uint32_t ECL_ClearFlags(void* entity, uint32_t flags) {
    EntityFlags(entity) &= ~flags;
    return EntityFlags(entity);
}

void ECL_SetMovementBoundary(void* entity,
                             const ECLMovementBoundary& boundary) {
    EntityFlags(entity) |= kMovementBoundaryEnabled;
    EntityBoundary(entity) = boundary;
}

void ECL_ClearMovementBoundary(void* entity) {
    EntityFlags(entity) &= ~kMovementBoundaryEnabled;
}

void ECL_ResetDifficultySlots(void* entity) {
    uint32_t* slots = EntityDifficultySlots(entity);
    for (int i = 0; i < 12; ++i)
        slots[i] = 0;
}

// 0x0044FF80 - Resolve an already-decoded float using an operand's mask bit.
float ECL_ResolveFloatValue(
    void* cursor_pointer, unsigned int operand, float encoded) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + 4);

    if ((instruction->param_mask & (1u << (operand & 31))) == 0)
        return encoded;

    if (encoded >= DAT_00470b04) {
        const int32_t byte_offset = static_cast<int32_t>(encoded);
        const int32_t locals_offset =
            *reinterpret_cast<int32_t*>(cursor + kLocalVariablesOffset);
        return *reinterpret_cast<float*>(cursor + locals_offset + 8 + byte_offset);
    }

    if (encoded != DAT_00470b60) {
        ECLVariableResolver* resolver =
            *reinterpret_cast<ECLVariableResolver**>(
                cursor + kVariableResolverOffset);
        return resolver->ResolveFloat(static_cast<int32_t>(encoded));
    }

    int32_t stack_top =
        *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) - 4;
    if (stack_top < 0)
        return encoded;

    *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) = stack_top;
    const uint32_t value = *reinterpret_cast<uint32_t*>(cursor + stack_top + 8);
    stack_top -= 4;
    *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) = stack_top;

    const char type = *reinterpret_cast<char*>(cursor + stack_top + 8);
    if (type == 'i')
        return static_cast<float>(static_cast<int32_t>(value));

    union FloatAndBits {
        uint32_t as_bits;
        float as_float;
    } converted;
    converted.as_bits = value;
    return converted.as_float;
}

// 0x0044FE40 - Resolve a float stored in the current instruction.
float ECL_ResolveFloatOperand(void* cursor_pointer, unsigned int operand) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + 4);
    return ECL_ResolveFloatValue(
        cursor_pointer, operand, BitsFloat(instruction->operands[operand]));
}

// 0x0044FF00 - Resolve an already-decoded integer using an operand's mask bit.
int32_t ECL_ResolveIntValue(
    void* cursor_pointer, unsigned int operand, int32_t value) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + 4);

    if ((instruction->param_mask & (1u << (operand & 31))) == 0)
        return value;

    if (value >= 0) {
        const int32_t locals_offset =
            *reinterpret_cast<int32_t*>(cursor + kLocalVariablesOffset);
        return *reinterpret_cast<int32_t*>(cursor + locals_offset + 8 + value);
    }

    if (value != -1) {
        ECLVariableResolver* resolver =
            *reinterpret_cast<ECLVariableResolver**>(
                cursor + kVariableResolverOffset);
        return resolver->ResolveInt(value);
    }

    int32_t stack_top =
        *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) - 4;
    if (stack_top < 0)
        return value;

    *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) = stack_top;
    const uint32_t raw = *reinterpret_cast<uint32_t*>(cursor + stack_top + 8);
    stack_top -= 4;
    *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) = stack_top;

    const char type = *reinterpret_cast<char*>(cursor + stack_top + 8);
    if (type == 'f')
        return static_cast<int32_t>(BitsFloat(raw));
    return static_cast<int32_t>(raw);
}

// 0x0044FDB0 - Resolve an integer stored in the current instruction.
int32_t ECL_ResolveIntOperand(void* cursor_pointer, unsigned int operand) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + 4);
    return ECL_ResolveIntValue(
        cursor_pointer, operand,
        static_cast<int32_t>(instruction->operands[operand]));
}

int __fastcall ECL_VM_Dispatch(void* entity) {
    ECLVMState* state = *reinterpret_cast<ECLVMState**>(
        static_cast<uint8_t*>(entity) + 0x14d8);
    ECLInstruction* instruction = state->cursor->instruction;
    const int opcode = instruction->opcode;

    if (static_cast<unsigned int>(opcode - 0x100) > 0xb4)
        return 0;

    // Ghidra names the symbol 0x100 bytes before the actual byte-index table;
    // indexing it by the full opcode reaches the retail table at 0x00411EE0.
    const uint32_t dispatch_index = PTR_caseD_14f_00411de0[opcode];

    switch (opcode) {
    case ECL_SET_HITBOX_WIDTH:
        EntityFloat(entity, 0xb0) = ECL_ResolveFloatOperand(state->cursor, 0);
        EntityFloat(entity, 0xb4) = ECL_ResolveFloatOperand(state->cursor, 1);
        return 0;
    case ECL_SET_HITBOX_HEIGHT:
        EntityFloat(entity, 0xb8) = ECL_ResolveFloatOperand(state->cursor, 0);
        EntityFloat(entity, 0xbc) = ECL_ResolveFloatOperand(state->cursor, 1);
        return 0;
    case ECL_SET_FLAGS: {
        const uint32_t flags = FUN_0044fdb0(dispatch_index, state->cursor, 0);
        if ((ECL_SetFlags(entity, flags) & 0x10) != 0) {
            for (int i = 0; i < 10; ++i)
                FUN_004495e0();
        }
        return 0;
    }
    case ECL_CLEAR_FLAGS: {
        const uint32_t flags = FUN_0044fdb0(dispatch_index, state->cursor, 0);
        if ((ECL_ClearFlags(entity, flags) & 0x10) == 0) {
            for (int i = 0; i < 10; ++i)
                FUN_00449590();
        }
        return 0;
    }
    case ECL_CLEAR_MOVEMENT_BOUNDARY:
        ECL_ClearMovementBoundary(entity);
        return 0;
    case ECL_SET_MOVEMENT_BOUNDARY: {
        ECLMovementBoundary boundary;
        boundary.left = ECL_ResolveFloatOperand(state->cursor, 0);
        boundary.top = ECL_ResolveFloatOperand(state->cursor, 1);
        boundary.right = ECL_ResolveFloatOperand(state->cursor, 2);
        boundary.bottom = ECL_ResolveFloatOperand(state->cursor, 3);
        ECL_SetMovementBoundary(entity, boundary);
        return 0;
    }
    case ECL_RESET_DIFFICULTY_SLOTS:
        ECL_ResetDifficultySlots(entity);
        return 0;
    case ECL_SET_DIFFICULTY_SLOT: {
        int32_t slot = ECL_ResolveIntOperand(state->cursor, 0);
        // The high-bit mode substitutes the two extra difficulty slots used
        // by the retail script tables.
        if ((EntityFlags(entity) & 0x8000) != 0) {
            if (slot == 1)
                slot = 10;
            else if (slot == 4)
                slot = 11;
        }
        const int32_t value = ECL_ResolveIntOperand(state->cursor, 1);
        EntityInt(entity, 0x13cc + slot * 4) = value;
        return 0;
    }
    case ECL_SET_RANGE_PARAMETERS: {
        // Retail resolves operand 1 first.  This is observable when both
        // operands pop values from the ECL argument stack.
        const float maximum = ECL_ResolveFloatOperand(state->cursor, 1);
        const float minimum = ECL_ResolveFloatOperand(state->cursor, 0);
        EntityFloat(entity, 0x1400) = minimum;
        EntityFloat(entity, 0x1404) = maximum;
        return 0;
    }
    default:
        // The remaining opcode families still execute from the retail image.
        // Their behavior is being moved here in independently verified groups.
        return 0;
    }
}
