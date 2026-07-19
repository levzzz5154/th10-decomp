// ECL (Enemy Control Language) VM dispatch, retail address 0x0040E770.
#include "th10/script/ecl.hpp"


extern "C" float cosf(float);
extern "C" float sinf(float);

extern "C" {
uint32_t ECL_DispatchOpcode(uint32_t dispatch_index, void* cursor, int operand);
void ECL_SetTimerTarget(int value);
void AnimationManager_SetEclFlag(void);
void AnimationManager_ClearEclFlag(void);
}

extern uint8_t PTR_caseD_14f_00411de0[];
extern float DAT_00470b04; // zero: first local-variable encoding
extern float DAT_00470b60; // -1: pop from the ECL argument stack
extern void* g_pGameStateManager;
extern int32_t DAT_00474c98;
extern int32_t DAT_00474c74;

namespace {

const unsigned int kFlagsOffset = 0x1444;
const unsigned int kBoundaryOffset = 0x13ac;
const unsigned int kDifficultySlotsOffset = 0x13d0;
const unsigned int kArgumentStackTopOffset = 0x1008;
const unsigned int kLocalVariablesOffset = 0x100c;
const unsigned int kVariableResolverOffset = 0x1014;
const unsigned int kInstructionPointerOffset =
    sizeof(void*) == 8 ? 8 : 4;
const unsigned int kStackValueBaseOffset =
    sizeof(void*) == 8 ? 16 : 8;
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
        *reinterpret_cast<ECLInstruction**>(cursor + kInstructionPointerOffset);

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
    const uint32_t value = *reinterpret_cast<uint32_t*>(
        cursor + stack_top + kStackValueBaseOffset);
    stack_top -= 4;
    *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) = stack_top;

    const char type = *reinterpret_cast<char*>(
        cursor + stack_top + kStackValueBaseOffset);
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
        *reinterpret_cast<ECLInstruction**>(cursor + kInstructionPointerOffset);
    return ECL_ResolveFloatValue(
        cursor_pointer, operand, BitsFloat(instruction->operands[operand]));
}

// 0x0044FF00 - Resolve an already-decoded integer using an operand's mask bit.
int32_t ECL_ResolveIntValue(
    void* cursor_pointer, unsigned int operand, int32_t value) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + kInstructionPointerOffset);

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
    const uint32_t raw = *reinterpret_cast<uint32_t*>(
        cursor + stack_top + kStackValueBaseOffset);
    stack_top -= 4;
    *reinterpret_cast<int32_t*>(cursor + kArgumentStackTopOffset) = stack_top;

    const char type = *reinterpret_cast<char*>(
        cursor + stack_top + kStackValueBaseOffset);
    if (type == 'f')
        return static_cast<int32_t>(BitsFloat(raw));
    return static_cast<int32_t>(raw);
}

// 0x0044FDB0 - Resolve an integer stored in the current instruction.
int32_t ECL_ResolveIntOperand(void* cursor_pointer, unsigned int operand) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + kInstructionPointerOffset);
    return ECL_ResolveIntValue(
        cursor_pointer, operand,
        static_cast<int32_t>(instruction->operands[operand]));
}

// 0x00412A00 - ECL_ResolveIntOperand wrapper that pulls the cursor from the
// VM state stored at entity+0x14D8. Retail hides the manager pointer in EAX
// and the operand index in ECX; the clean API takes both explicitly.
int32_t ECL_ResolveIntFromEntity(void* entity, unsigned int operand) {
    void* vm_state = *(void**)((uint8_t*)entity + 0x14D8);
    void* cursor = *(void**)((uint8_t*)vm_state + 4);
    return ECL_ResolveIntOperand(cursor, operand);
}

// 0x00450070 - Resolve a writable float local/external variable destination.
float* ECL_ResolveFloatDestination(void* cursor_pointer, unsigned int operand) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + kInstructionPointerOffset);
    if ((instruction->param_mask & (1u << (operand & 31))) == 0)
        return 0;
    const int32_t encoded = (int32_t)BitsFloat(instruction->operands[operand]);
    if (encoded >= 0) {
        const int32_t locals_offset =
            *reinterpret_cast<int32_t*>(cursor + kLocalVariablesOffset);
        return reinterpret_cast<float*>(cursor + locals_offset + 8 + encoded);
    }
    if (encoded != -1) {
        ECLVariableResolver* resolver =
            *reinterpret_cast<ECLVariableResolver**>(
                cursor + kVariableResolverOffset);
        return resolver->ResolveFloatPointer(encoded);
    }
    return 0;
}

// 0x00412A10 - Resolve a writable integer local/external variable destination.
int32_t* ECL_ResolveIntDestination(void* cursor_pointer, unsigned int operand) {
    uint8_t* cursor = static_cast<uint8_t*>(cursor_pointer);
    ECLInstruction* instruction =
        *reinterpret_cast<ECLInstruction**>(cursor + kInstructionPointerOffset);
    if ((instruction->param_mask & (1u << (operand & 31))) == 0)
        return 0;
    const int32_t encoded = (int32_t)instruction->operands[operand];
    if (encoded >= 0) {
        const int32_t locals_offset =
            *reinterpret_cast<int32_t*>(cursor + kLocalVariablesOffset);
        return reinterpret_cast<int32_t*>(cursor + locals_offset + 8 + encoded);
    }
    if (encoded != -1) {
        ECLVariableResolver* resolver =
            *reinterpret_cast<ECLVariableResolver**>(
                cursor + kVariableResolverOffset);
        return resolver->ResolveIntPointer(encoded);
    }
    return 0;
}

// 0x00450030 - Resolve a variable encoded in the ECL local-variable table.
// Positive entries point into the VM's inline local area; negative entries
// are delegated to the external variable resolver.
void* ECL_ResolveVariableValue(void* vm_pointer, int32_t variable) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    const uint16_t mask = *reinterpret_cast<uint16_t*>(
        *reinterpret_cast<uint8_t**>(vm + 4) + 8);
    if ((mask & (1u << (static_cast<uint32_t>(variable) & 31))) == 0)
        return 0;
    const int32_t entry = *reinterpret_cast<int32_t*>(
        *reinterpret_cast<uint8_t**>(vm + 4) + 0x10 + variable * 4);
    if (entry >= 0)
        return vm + 8 + *reinterpret_cast<int32_t*>(vm + 0x100c) + entry;
    ECLVariableResolver* resolver = *reinterpret_cast<ECLVariableResolver**>(
        vm + 0x1014);
    return resolver == 0 ? 0 : resolver->ResolveIntPointer(entry);
}

// 0x00450160 - Find a linked external variable record by its retail id.
void* ECL_FindVariable(void* vm_pointer, int32_t variable) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    struct Node { void* object; Node* next; };
    Node* node = *reinterpret_cast<Node**>(vm + 0x1030);
    while (node != 0) {
        uint8_t* object = static_cast<uint8_t*>(node->object);
        if (object != 0 && *reinterpret_cast<int32_t*>(object + 0x1010) == variable)
            return node;
        node = node->next;
    }
    return 0;
}

// 0x00450190 - Clear the bound object pointer in every linked variable node.
void ECL_ResetVariableBindings(void* vm_pointer) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    struct Node { void* object; Node* next; };
    for (Node* node = *reinterpret_cast<Node**>(vm + 0x1034);
         node != 0; node = node->next) {
        if (node->object != 0)
            *reinterpret_cast<void**>(static_cast<uint8_t*>(node->object) + 4) = 0;
    }
}

// 0x00450690 - Reserve scratch space and save the previous top marker.
int32_t ECL_PushScratchValue(void* vm_pointer, int32_t value) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    const int32_t old_top = *reinterpret_cast<int32_t*>(vm + 0x1000);
    const int32_t new_top = old_top + value;
    if (new_top > 0xfff)
        return -1;
    *reinterpret_cast<int32_t*>(vm + 0x1000) = new_top;
    if (new_top + 4 < 0x1000) {
        *reinterpret_cast<int32_t*>(vm + new_top) =
            *reinterpret_cast<int32_t*>(vm + 0x1004);
        *reinterpret_cast<int32_t*>(vm + 0x1000) = new_top + 4;
    }
    *reinterpret_cast<int32_t*>(vm + 0x1004) = old_top;
    return 0;
}

// 0x004506D0 - Restore the previous scratch marker.
int32_t ECL_PopScratchValue(void* vm_pointer) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    const int32_t prior = *reinterpret_cast<int32_t*>(vm + 0x1000) - 4;
    const int32_t saved = *reinterpret_cast<int32_t*>(vm + 0x1004);
    if (prior >= 0) {
        *reinterpret_cast<int32_t*>(vm + 0x1000) = prior;
        *reinterpret_cast<int32_t*>(vm + 0x1004) =
            *reinterpret_cast<int32_t*>(vm + prior);
    }
    *reinterpret_cast<int32_t*>(vm + 0x1000) = saved;
    return 0;
}

// 0x004501B0 - Convert polar coordinates to a two-component vector.
void ECL_SetPolarVector(float* destination, float angle, float magnitude) {
    destination[0] = cosf(angle) * magnitude;
    destination[1] = sinf(angle) * magnitude;
}

// 0x004505B0 - Append a typed value to the VM scratch area.
int32_t ECL_WriteScratch(void* vm_pointer, char type, unsigned int size,
                         const void* data) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    int32_t& top = *reinterpret_cast<int32_t*>(vm + 0x1000);
    if (top + static_cast<int32_t>(size) > 0xfff)
        return -1;
    if (type != 0) {
        *reinterpret_cast<char*>(vm + top) = type;
        top += 4;
    }
    const unsigned char* source = static_cast<const unsigned char*>(data);
    for (unsigned int index = 0; index != size; ++index)
        vm[top + index] = source[index];
    top += static_cast<int32_t>(size);
    return 0;
}

// 0x00450470 - Binary-search the sorted UTF-16 script-label table.
void* ECL_FindScriptLabel(void* vm_pointer, const unsigned short* name) {
    uint8_t* vm = static_cast<uint8_t*>(vm_pointer);
    const int32_t count = *reinterpret_cast<int32_t*>(vm + 8);
    struct Entry { const unsigned short* name; void* value; };
    Entry* entries = *reinterpret_cast<Entry**>(vm + 0x8c);
    int32_t first = 0;
    int32_t last = count - 1;
    while (first <= last) {
        const int32_t middle = first + (last - first) / 2;
        const unsigned short* left = name;
        const unsigned short* right = entries[middle].name;
        int comparison = 0;
        while (*left == *right && *left != 0) {
            ++left;
            ++right;
        }
        if (*left < *right) comparison = -1;
        else if (*left > *right) comparison = 1;
        if (comparison == 0)
            return static_cast<uint8_t*>(entries[middle].value) + 0x10;
        if (comparison < 0) last = middle - 1;
        else first = middle + 1;
    }
    return 0;
}

// Shared by the encrypted text branches at 0x0040E770 cases 0x165–0x167.
// The retail key starts at 0x77 and advances by an increasing 0x10-step after
// each byte (the step itself starts at 7).
void ECL_DecodeEncryptedString(
    char* destination, const char* encrypted, unsigned int length) {
    unsigned int key = 0x77;
    unsigned int step = 7;
    for (unsigned int index = 0; index != length; ++index) {
        destination[index] = (char)((unsigned char)encrypted[index] ^ key);
        key = (key + step) & 0xFF;
        step = (step + 0x10) & 0xFF;
    }
}

// 0x0040E770 cases 0x156/0x15c/0x165-0x167.  Retail applies the difficulty
// offset only to the three difficulty-sensitive variants; 0x156 and 0x15c
// use the encoded resource index unchanged.
void ECL_ExecuteEncryptedStringOpcode(
    int opcode, int base_index, int difficulty, const char* encrypted,
    unsigned int length,
    void (*emit)(int resource_index, const char* text, unsigned int length)) {
    if (emit == 0 || encrypted == 0) return;
    int resource_index = base_index;
    if (opcode == 0x165)
        resource_index += difficulty;
    else if (opcode == 0x166)
        resource_index += difficulty - 1;
    else if (opcode == 0x167)
        resource_index += difficulty - 2;
    // ECL strings are short instruction payloads.  Keep the temporary buffer
    // bounded while preserving the exact byte-wise retail transform.
    char decoded[256];
    const unsigned int decoded_length = length < sizeof(decoded) ? length :
        (unsigned int)sizeof(decoded);
    ECL_DecodeEncryptedString(decoded, encrypted, decoded_length);
    emit(resource_index, decoded, decoded_length);
}

int __fastcall ECL_VM_Dispatch(void* entity) {
    if (entity == 0)
        return 0;
    ECLVMState* state = *reinterpret_cast<ECLVMState**>(
        static_cast<uint8_t*>(entity) + 0x14d8);
    if (state == 0 || state->cursor == 0 || state->cursor->instruction == 0)
        return 0;
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
        const uint32_t flags = ECL_DispatchOpcode(dispatch_index, state->cursor, 0);
        if ((ECL_SetFlags(entity, flags) & 0x10) != 0) {
            for (int i = 0; i < 10; ++i)
                AnimationManager_ClearEclFlag();
        }
        return 0;
    }
    case ECL_CLEAR_FLAGS: {
        const uint32_t flags = ECL_DispatchOpcode(dispatch_index, state->cursor, 0);
        if ((ECL_ClearFlags(entity, flags) & 0x10) == 0) {
            for (int i = 0; i < 10; ++i)
                AnimationManager_SetEclFlag();
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
    case ECL_SET_CURRENT_DIFFICULTY: {
        int32_t difficulty = ECL_ResolveIntOperand(state->cursor, 0);
        if ((EntityFlags(entity) & 0x8000u) != 0) {
            if (difficulty == 1)
                difficulty = 10;
            else if (difficulty == 4)
                difficulty = 11;
        }
        EntityInt(entity, 0x13CC) = difficulty;
        return 0;
    }
    case ECL_RESET_DIFFICULTY_STATE: {
        const int32_t difficulty = ECL_ResolveIntOperand(state->cursor, 0);
        EntityInt(entity, 0x13C0) = difficulty;
        EntityInt(entity, 0x13C4) = difficulty;
        EntityInt(entity, 0x13C8) = difficulty;
        if (g_pGameStateManager != 0) {
            uint8_t* manager = (uint8_t*)g_pGameStateManager;
            for (unsigned int offset = 0x9E94;
                 offset <= 0x9EB0; offset += 4)
                *(int32_t*)(manager + offset) = 0;
        }
        return 0;
    }
    case ECL_SET_DIFFICULTY_SQUARED: {
        const float value = ECL_ResolveFloatOperand(state->cursor, 0);
        EntityFloat(entity, 0x1454) = value * value;
        return 0;
    }
    case ECL_SET_DIFFICULTY_PARAMETER: {
        // Retail evaluates the integer parameter, float parameter, then slot
        // index in that order before touching the shared difficulty table.
        const int32_t value = ECL_ResolveIntOperand(state->cursor, 2);
        const float scale = ECL_ResolveFloatOperand(state->cursor, 1);
        const int32_t slot = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t difficulty = EntityInt(entity, 0x13C4);
        if (g_pGameStateManager != 0) {
            uint8_t* manager = (uint8_t*)g_pGameStateManager;
            *(int32_t*)(manager + 0x9E98 + slot * 8) = value;
            *(float*)(manager + 0x9E94 + slot * 8) =
                scale / (float)difficulty;
        }
        return 0;
    }
    case ECL_SELECT_DIFFICULTY_VALUE:
    case ECL_SELECT_DIFFICULTY_CURVE: {
        int operand = 0;
        if (opcode == ECL_SELECT_DIFFICULTY_VALUE) {
            operand = DAT_00474c98 >= 0x200 ? 2 : 0;
        } else if (DAT_00474c98 > 599) {
            operand = 4;
        } else if (DAT_00474c98 > 199) {
            operand = 3;
        } else if (DAT_00474c98 < -400) {
            operand = 0;
        } else if (DAT_00474c98 < -200) {
            operand = 1;
        } else {
            operand = 2;
        }
        float* destination = ECL_ResolveFloatDestination(state->cursor, 0);
        if (destination != 0)
            *destination = ECL_ResolveFloatOperand(state->cursor, operand);
        return 0;
    }
    case ECL_INTERPOLATE_DIFFICULTY: {
        float* destination = ECL_ResolveFloatDestination(state->cursor, 0);
        const float lower = ECL_ResolveFloatOperand(state->cursor, 1);
        const float upper = ECL_ResolveFloatOperand(state->cursor, 2);
        if (destination != 0)
            *destination = (upper - lower) *
                ((float)DAT_00474c98 + 1024.0f) * (1.0f / 2048.0f) + lower;
        return 0;
    }
    case 0x160:
    case 0x161: {
        int operand = opcode == 0x160 ?
            (DAT_00474c98 > 0x1FF ? 2 : 0) :
            (DAT_00474c98 > 599 ? 4 :
             (DAT_00474c98 > 199 ? 3 :
              (DAT_00474c98 <= -400 ? 0 :
               (DAT_00474c98 <= -200 ? 1 : 2))));
        int32_t* destination = ECL_ResolveIntDestination(state->cursor, 0);
        if (destination != 0)
            *destination = ECL_ResolveIntOperand(state->cursor, operand);
        return 0;
    }
    case 0x162: {
        int32_t* destination = ECL_ResolveIntDestination(state->cursor, 0);
        const int32_t lower = ECL_ResolveIntOperand(state->cursor, 1);
        const int32_t upper = ECL_ResolveIntOperand(state->cursor, 2);
        const int32_t delta = (upper - lower) * (DAT_00474c98 + 0x400);
        if (destination != 0)
            *destination = ((delta + (delta < 0 ? 0x7FF : 0)) >> 11) + lower;
        return 0;
    }
    case 0x163: {
        int operand = -1;
        if (DAT_00474c74 == 0) operand = 1;
        else if (DAT_00474c74 == 1) operand = 2;
        else if (DAT_00474c74 == 2) operand = 3;
        else if (DAT_00474c74 == 3 || DAT_00474c74 == 4) operand = 4;
        int32_t* destination = ECL_ResolveIntDestination(state->cursor, 0);
        if (destination != 0 && operand >= 0)
            *destination = ECL_ResolveIntOperand(state->cursor, operand);
        return 0;
    }
    case 0x164: {
        int operand = -1;
        if (DAT_00474c74 == 0) operand = 1;
        else if (DAT_00474c74 == 1) operand = 2;
        else if (DAT_00474c74 == 2) operand = 3;
        else if (DAT_00474c74 == 3) operand = 4;
        else if (DAT_00474c74 == 4) operand = 5;
        float* destination = ECL_ResolveFloatDestination(state->cursor, 0);
        if (destination != 0 && operand >= 0)
            *destination = ECL_ResolveFloatOperand(state->cursor, operand);
        return 0;
    }
    case ECL_SET_GLOBAL_DIFFICULTY:
        if (g_pGameStateManager != 0)
            *(int32_t*)((uint8_t*)g_pGameStateManager + 0x9E90) =
                ECL_ResolveIntOperand(state->cursor, 0);
        return 0;
    case ECL_APPLY_DIFFICULTY_ACTION:
        ECL_SetTimerTarget(ECL_ResolveIntOperand(state->cursor, 0));
        return 0;
    case 0x158:
        Score_SetMode(entity, ECL_ResolveIntOperand(state->cursor, 0));
        return 0;
    case 0x14e: {
        // Resource-slot assignment (retail helper 0x00412720).  The opcode
        // supplies the slot, resource id, and packed metadata in that order.
        const int slot = ECL_ResolveIntOperand(state->cursor, 0);
        const int resource = ECL_ResolveIntOperand(state->cursor, 1);
        const uint32_t metadata = static_cast<uint32_t>(
            ECL_ResolveIntOperand(state->cursor, 2));
        Ecl_SetResourceSlot(entity, slot, resource, metadata, metadata);
        return 0;
    }
    case 0x14c: {
        // Bind this entity's VM to a manager slot, or clear the binding when
        // the script supplies a negative slot.  This mirrors the retail
        // 0x0040E770 case without invoking the manager's external callbacks.
        const int slot = ECL_ResolveIntOperand(state->cursor, 0);
        if (slot < 0) {
            EntityFlags(entity) &= ~0x8000u;
            return 0;
        }
        EntityFlags(entity) |= 0x8000u;
        EntityInt(entity, 0x1450) = slot;
        if (g_pGameStateManager != 0) {
            void* vm = *reinterpret_cast<void**>(
                static_cast<uint8_t*>(entity) + 0x14d8);
            *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(
                g_pGameStateManager) + 0x10 + slot * 4) =
                static_cast<uint32_t>(reinterpret_cast<unsigned long long>(vm));
        }
        return 0;
    }
    case 0x128:
    case 0x129: {
        const unsigned int offset = opcode == 0x128 ? 0x58u : 0x84u;
        EntityFloat(entity, offset) += ECL_ResolveFloatOperand(state->cursor, 0);
        EntityFloat(entity, offset + 4) +=
            ECL_ResolveFloatOperand(state->cursor, 1);
        EntityFloat(entity, offset + 8) +=
            ECL_ResolveFloatOperand(state->cursor, 2);
        return 0;
    }
    case 0x126:
    case 0x127:
        if (g_pGameStateManager != 0) {
            void* manager_state = *reinterpret_cast<void**>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x10);
            if (manager_state != 0) {
                const uint8_t* source = static_cast<const uint8_t*>(manager_state);
                const unsigned int offset = opcode == 0x126 ? 0x58u : 0x84u;
                EntityFloat(entity, offset) = *reinterpret_cast<const float*>(source + 0x1068);
                EntityFloat(entity, offset + 4) = *reinterpret_cast<const float*>(source + 0x106c);
                EntityFloat(entity, offset + 8) = *reinterpret_cast<const float*>(source + 0x1070);
            }
        }
        return 0;
    case 0x12a:
    case 0x12b: {
        const unsigned int offset = opcode == 0x12a ? 0x58u : 0x84u;
        EntityFloat(entity, offset + 0x0c) =
            ECL_ResolveFloatOperand(state->cursor, 0);
        EntityFloat(entity, offset + 0x10) =
            ECL_ResolveFloatOperand(state->cursor, 1);
        return 0;
    }
    case 0x120:
    case 0x122: {
        const unsigned int offset = opcode == 0x120 ? 0x58u : 0x84u;
        uint8_t* record = static_cast<uint8_t*>(entity) + offset;
        const uint32_t flags = *reinterpret_cast<uint32_t*>(record + 0x28);
        if ((flags & 1u) == 0) {
            *reinterpret_cast<float*>(record + 0x0c) =
                *reinterpret_cast<float*>(record + 0x00);
            *reinterpret_cast<float*>(record + 0x10) =
                *reinterpret_cast<float*>(record + 0x04);
            *reinterpret_cast<float*>(record + 0x14) =
                *reinterpret_cast<float*>(record + 0x08);
        }
        const float angle = ECL_ResolveFloatOperand(state->cursor, 0);
        const float speed = ECL_ResolveFloatOperand(state->cursor, 1);
        const float duration = ECL_ResolveFloatOperand(state->cursor, 2);
        const float delay = ECL_ResolveFloatOperand(state->cursor, 3);
        if (angle > 0.0f)
            Score_SetNormalizedAngle(record, angle);
        if (speed > 0.0f)
            *reinterpret_cast<float*>(record + 0x18) = speed;
        if (duration > 0.0f)
            *reinterpret_cast<float*>(record + 0x20) = duration;
        if (delay > 0.0f)
            *reinterpret_cast<float*>(record + 0x24) = delay;
        *reinterpret_cast<uint32_t*>(record + 0x28) |= 1u;
        return 0;
    }
    default:
        // The remaining opcode families still execute from the retail image.
        // Their behavior is being moved here in independently verified groups.
        return 0;
    }
}
