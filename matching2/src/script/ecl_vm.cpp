// ECL (Enemy Control Language) VM dispatch, retail address 0x0040E770.
#include "th10/script/ecl.hpp"
#include "th10/script/final_script_runtime.hpp"
#include "th10/script/script_label_search.hpp"
#include "th10/render/animation_manager.hpp"
#include "th10/math/timer.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <cstdio>

#include <cmath>
#include <cstring>

extern "C" float cosf(float);
extern "C" float sinf(float);

extern float DAT_00470b04; // zero: first local-variable encoding
extern float DAT_00470b60; // -1: pop from the ECL argument stack
extern void* g_pGameStateManager;
extern int32_t DAT_00474c98;
extern int32_t DAT_00474c74;
extern uint32_t DAT_00476f78; // script-time scale, shared with player/bullet
extern float DAT_00470d58;   // tiny positive comparison constant (0.0f)
extern float DAT_00470b94;   // angle mirror base used by 0x11c/0x11e


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

void SetEntityTimer(void* entity, unsigned int offset, int target) {
    FrameTimer* timer = reinterpret_cast<FrameTimer*>(
        static_cast<uint8_t*>(entity) + offset);
    Timer_Set(timer, target);
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

// Script-label lookup for the ECL VM host edge.  Retail 0x00450470's search
// is implemented canonically in src/script/final_script_runtime.cpp; this
// wrapper adapts the raw VM byte offsets and delegates to the shared search
// helper (th10/script/script_label_search.hpp).
void* ECL_FindScriptLabel(void* vm_pointer, const char* name) {
    const th10::script_final::EclScriptEntry* entry =
        th10::script_label_search::FindScriptLabelEntry<
            th10::script_final::EclScriptTable,
            th10::script_final::EclScriptEntry>(
            static_cast<const th10::script_final::EclScriptTable*>(vm_pointer),
            name);
    return entry == nullptr
               ? 0
               : reinterpret_cast<char*>(
                     static_cast<uintptr_t>(entry->value)) + 0x10;
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
        const uint32_t flags = static_cast<uint32_t>(
            ECL_ResolveIntOperand(state->cursor, 0));
        if ((ECL_SetFlags(entity, flags) & 0x10) != 0) {
            for (int i = 0; i < 10; ++i) {
                AnimationManager_ClearFlag(
                    g_pGameStateManager, EntityInt(entity, 0xC0 + i * 4), 2);
            }
        }
        return 0;
    }
    case ECL_CLEAR_FLAGS: {
        const uint32_t flags = static_cast<uint32_t>(
            ECL_ResolveIntOperand(state->cursor, 0));
        if ((ECL_ClearFlags(entity, flags) & 0x10) == 0) {
            for (int i = 0; i < 10; ++i) {
                AnimationManager_SetFlag(
                    g_pGameStateManager, EntityInt(entity, 0xC0 + i * 4), 2);
            }
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
        // 0x0041004C: retail passes entity+0x1430 in EAX to 0x00405410.
        SetEntityTimer(entity, 0x1430,
                       ECL_ResolveIntOperand(state->cursor, 0));
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
    case 0x14d:
        // 0x00410C58: reset the movement timer at entity+0x11C.
        SetEntityTimer(entity, 0x11c, 0);
        return 0;
    case 0x14f: {
        // 0x0041001F: the other embedded timer lives at entity+0x141C.
        const int32_t value = ECL_ResolveIntOperand(state->cursor, 0);
        SetEntityTimer(entity, 0x141c, value);
        return 0;
    }
    case 0x153:
        // Conditional script exit (return 0xffffffff).  The retail gate is
        // (DAT_0047770c + 0x9eb8)->0x78 == 0; when the manager has no live
        // boss entry the script should terminate immediately.  The retail
        // binary stores the boss pointer as a 32-bit value, so on 64-bit
        // hosts we treat the manager field as a small handle and only
        // dereference it when the value looks like a valid 32-bit address.
        if (g_pGameStateManager != 0) {
            const uint32_t boss_address = *reinterpret_cast<uint32_t*>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x9eb8);
            if (boss_address != 0) {
                const int32_t live_value = *reinterpret_cast<const int32_t*>(
                    reinterpret_cast<const void*>(
                        static_cast<unsigned long long>(boss_address + 0x78)));
                if (live_value == 0)
                    return 0xffffffff;
            }
        }
        return 0;
    case 0x154:
        // Conditional script exit (return 0xffffffff) when the global config
        // has a non-null +0x10 pointer, mirroring the retail 0x0040E770 case.
        if (g_pGameStateManager != 0 &&
            *reinterpret_cast<int32_t*>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x10) != 0)
            return 0xffffffff;
        return 0;
    case 0x155: {
        // Label-table entry.  Operand 0 selects the script-local label index;
        // retail stores the address of the next instruction header (iVar27 +
        // 0x18) at the VM-owned label table.  The retail binary stores the
        // raw 32-bit pointer (this is a 32-bit retail binary), so we keep the
        // instruction pointer in a uint32_t for storage.
        const int32_t label = ECL_ResolveIntOperand(state->cursor, 0);
        if (state->cursor == 0) return 0;
        ECLInstruction* instruction =
            *reinterpret_cast<ECLInstruction**>(
                reinterpret_cast<uint8_t*>(state->cursor) +
                kInstructionPointerOffset);
        const uint64_t instruction_address =
            reinterpret_cast<uint64_t>(instruction);
        *reinterpret_cast<uint32_t*>(
            reinterpret_cast<uint8_t*>(state->cursor) +
            (label + 0x24a) * 0x10) =
            static_cast<uint32_t>(instruction_address) + 0x18;
        return 0;
    }
    case 0x16a:
        // Set the global "play sound" pending bit on the player state block.
        if (g_pGameStateManager != 0)
            *reinterpret_cast<uint32_t*>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x378c) |= 8u;
        return 0;
    case 0x16c: {
        // XOR the 0x80000 flag with the LSB of the resolved integer operand.
        // The retail expression `(value << 0x13 ^ flags) & 0x80000` selects
        // bit 0x80000 only when the operand is non-zero.
        const int32_t value = ECL_ResolveIntOperand(state->cursor, 0);
        EntityFlags(entity) ^= (uint32_t)(
            ((int)value << 0x13) ^ EntityFlags(entity)) & 0x80000u;
        return 0;
    }
    case 0x16e: {
        // Same bit-twiddling as 0x16c but for 0x100000.  After the XOR the
        // script also writes the next two operands into entity+0x1448 and
        // entity+0x144c, and clears bit 0x200000.
        const int32_t bit_value = ECL_ResolveIntOperand(state->cursor, 0);
        EntityFlags(entity) ^= (uint32_t)(
            (bit_value << 0x14) ^ EntityFlags(entity)) & 0x100000u;
        const int32_t secondary = ECL_ResolveIntOperand(state->cursor, 1);
        EntityInt(entity, 0x1448) = secondary;
        EntityFlags(entity) &= ~0x200000u;
        EntityInt(entity, 0x144c) = EntityInt(entity, 0xf4);
        return 0;
    }
    case 0x16f: {
        // Replace DAT_00476f78 (the script-time scale) with operand 0.
        const float value = ECL_ResolveFloatOperand(state->cursor, 0);
        std::memcpy(&DAT_00476f78, &value, sizeof(DAT_00476f78));
        return 0;
    }
    case 0x170: {
        // Subtract a difficulty-tier constant from the float that the
        // script's operand 0 points to.  Retail treats the cursor's first
        // 4 bytes as a 32-bit float pointer; on 64-bit hosts we also
        // support a 64-bit pointer stored at offset 0 (the script loader
        // writes whichever pointer size matches the host).
        int operand_index = 0;
        if (DAT_00474c74 == 1) operand_index = 1;
        else if (DAT_00474c74 == 2) operand_index = 2;
        else if (DAT_00474c74 >= 3) operand_index = 3;
        const int32_t value = ECL_ResolveIntOperand(state->cursor, operand_index);
        if (state->cursor != 0) {
            const uint32_t target_address = *reinterpret_cast<uint32_t*>(
                reinterpret_cast<uint8_t*>(state->cursor));
            if (target_address != 0) {
                float* target = reinterpret_cast<float*>(
                    static_cast<unsigned long long>(target_address));
                *target = *target - (float)value;
            }
        }
        return 0;
    }
    case 0x102: {
        // Select the active enemy-type slot from operand 0.  The retail
        // stores the resolved integer at entity+0xe8 so subsequent opcodes
        // (0x103, 0x106, 0x10d) can refer to the same slot.
        const int32_t value = ECL_ResolveIntOperand(state->cursor, 0);
        EntityInt(entity, 0xe8) = value;
        return 0;
    }
    case 0x118:
    case 0x11a: {
        // Copy the per-axis position from operand 0/1 to the entity's
        // primary (0x118 -> +0x58) or secondary (0x11a -> +0x84) movement
        // record, clear its active flag, and refresh the composite entity
        // position by adding the two records together.
        const unsigned int offset = opcode == 0x118 ? 0x58u : 0x84u;
        uint8_t* record = static_cast<uint8_t*>(entity) + offset;
        const float first = ECL_ResolveFloatOperand(state->cursor, 0);
        const float second = ECL_ResolveFloatOperand(state->cursor, 1);
        if (first > 0.0f)
            *reinterpret_cast<float*>(record) = first;
        if (second > 0.0f)
            *reinterpret_cast<float*>(record + 4) = second;
        *reinterpret_cast<uint32_t*>(record + 0x28) &= ~1u;
        EntityFloat(entity, 0x2c) =
            EntityFloat(entity, 0x84) + EntityFloat(entity, 0x58);
        EntityFloat(entity, 0x30) =
            EntityFloat(entity, 0x88) + EntityFloat(entity, 0x5c);
        EntityFloat(entity, 0x34) =
            EntityFloat(entity, 0x8c) + EntityFloat(entity, 0x60);
        return 0;
    }
    case 0x11c:
    case 0x11e: {
        // Mirror-and-set the Z position.  Operand 0 = z, operand 1 = y.
        // Z is run through ECL_SetPositionZWithWrap (FUN_00413170),
        // optionally pre-mirrored around DAT_00470b94 when the entity
        // flag 0x800 is set.  Y is stored at record+0x18, then bit 0 of
        // the record's flag word (record+0x28) is cleared.
        const unsigned int offset = opcode == 0x11c ? 0x58u : 0x84u;
        uint8_t* record = static_cast<uint8_t*>(entity) + offset;
        float z = ECL_ResolveFloatOperand(state->cursor, 0);
        const float y = ECL_ResolveFloatOperand(state->cursor, 1);
        if (DAT_00470d58 < z) {
            if ((EntityFlags(entity) & 0x800u) != 0) {
                float temp = z - DAT_00470b94;
                ECL_WrapValue(&temp);
                temp = DAT_00470b94 - temp;
                ECL_WrapValue(&temp);
                z = temp;
            }
            ECL_SetPositionZWithWrap(record, z);
        }
        if (DAT_00470d58 < y)
            *reinterpret_cast<float*>(record + 0x18) = y;
        *reinterpret_cast<uint32_t*>(record + 0x28) &= ~1u;
        return 0;
    }
    case 0x190: {
        // Retail 0x0040E770 clears the complete 0x210-byte per-slot
        // projectile descriptor, then installs its fixed defaults. The timer
        // helper used by other movement records is a different operation.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        constexpr int kSlotBase = 0x2C4;
        constexpr int kSlotStride = 0x210;
        constexpr int kSlotLimit = (0x2514 - kSlotBase) / kSlotStride;
        if (index >= 0 && index < kSlotLimit) {
            uint8_t* record = static_cast<uint8_t*>(entity) +
                              kSlotBase + index * kSlotStride;
            std::memset(record, 0, kSlotStride);
            *reinterpret_cast<short*>(record + 0x1F4) = 1;
            *reinterpret_cast<short*>(record + 0x1F6) = 1;
            *reinterpret_cast<float*>(record + 0x10) = 0.0f;
            *reinterpret_cast<float*>(record + 0x18) = 2.0f;
            *reinterpret_cast<int32_t*>(record + 0x1FC) = 0x203;
            *reinterpret_cast<int32_t*>(record + 0x200) = 7;
            *reinterpret_cast<int32_t*>(record + 0x204) = 0x18;
            EntityFloat(entity, (index * 3 + 0x4D1) * 4) = 0.0f;
            EntityFloat(entity, 0x1348 + index * 0xC) = 0.0f;
        }
        return 0;
    }
    case 0x193: {
        // Initialise the per-slot laser/anchor record with 1.0/2.0 base
        // values.  Retail writes 1.0f at (index * 3 + 0x4d1) * 4 and 2.0f
        // at 0x1348 + index * 0xc.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        EntityFloat(entity, (index * 3 + 0x4d1) * 4) = 1.0f;
        EntityFloat(entity, 0x1348 + index * 0xc) = 2.0f;
        return 0;
    }
    case 0x194: {
        // Initialise the per-slot laser speed record with 1.0/2.0 base
        // values, written at offset 0x210 * index + 0x2d4 / 0x2d8.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        EntityFloat(entity, base + 0x2d4) = 1.0f;
        EntityFloat(entity, base + 0x2d8) = 2.0f;
        return 0;
    }
    case 0x192: {
        // Initialise the per-slot laser image count (short) from operands
        // 1 and 2.  Operand 0 selects the slot.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t count_x = ECL_ResolveIntOperand(state->cursor, 1);
        const int32_t count_y = ECL_ResolveIntOperand(state->cursor, 2);
        const unsigned int base = index * 0x210u;
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x2c4) = (short)count_x;
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x2c6) = (short)count_y;
        return 0;
    }
    case 0x196: {
        // Initialise the per-slot laser angle/curvature counts from
        // operands 1 and 2.  Operand 0 selects the slot.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t angle = ECL_ResolveIntOperand(state->cursor, 1);
        const int32_t curve = ECL_ResolveIntOperand(state->cursor, 2);
        const unsigned int base = index * 0x210u;
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4b8) = (short)angle;
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4ba) = (short)curve;
        return 0;
    }
    case 0x197: {
        // Set the per-slot laser extension delay (single short) from
        // operand 1.  Operand 0 selects the slot.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t value = ECL_ResolveIntOperand(state->cursor, 1);
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + index * 0x210u + 0x4bc) =
            (short)value;
        return 0;
    }
    case 0x198: {
        // Set the per-slot laser timing parameters (two ints) from
        // operands 1 and 2.  Operand 0 selects the slot.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t a = ECL_ResolveIntOperand(state->cursor, 1);
        const int32_t b = ECL_ResolveIntOperand(state->cursor, 2);
        const unsigned int base = index * 0x210u;
        *reinterpret_cast<int32_t*>(
            static_cast<uint8_t*>(entity) + base + 0x4c4) = a;
        *reinterpret_cast<int32_t*>(
            static_cast<uint8_t*>(entity) + base + 0x4c8) = b;
        return 0;
    }
    case 0x199: {
        // Set the per-slot laser timing sub-record (five ints + two floats)
        // from operands 0..5.  The slot is selected by operands 0 and 1.
        const int32_t slot = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t sub = ECL_ResolveIntOperand(state->cursor, 1);
        const int32_t v2 = ECL_ResolveIntOperand(state->cursor, 2);
        const int32_t v3 = ECL_ResolveIntOperand(state->cursor, 3);
        const int32_t v4 = ECL_ResolveIntOperand(state->cursor, 4);
        const int32_t v5 = ECL_ResolveIntOperand(state->cursor, 5);
        const int32_t record_index = slot * 0x16 + sub;
        const unsigned int record_base = record_index * 0x18u;
        *reinterpret_cast<int32_t*>(
            static_cast<uint8_t*>(entity) + record_base + 0x2f8) = v2;
        *reinterpret_cast<int32_t*>(
            static_cast<uint8_t*>(entity) + record_base + 0x2f4) = v3;
        *reinterpret_cast<int32_t*>(
            static_cast<uint8_t*>(entity) + record_base + 0x2ec) = v4;
        *reinterpret_cast<int32_t*>(
            static_cast<uint8_t*>(entity) + record_base + 0x2f0) = v5;
        EntityFloat(entity, record_base + 0x2e4) = 8.40779e-45f;
        EntityFloat(entity, (record_index * 3 + 0x5d) * 8) = 9.80909e-45f;
        return 0;
    }
    case 0x19b: {
        // Copy the 0x210-byte laser record from slot src (operand 1) to
        // slot dst (operand 0).  Each record is 0x84 ints.
        const int32_t dst = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t src = ECL_ResolveIntOperand(state->cursor, 1);
        const uint32_t* src_record = reinterpret_cast<const uint32_t*>(
            static_cast<uint8_t*>(entity) + src * 0x210u + 0x2c4);
        uint32_t* dst_record = reinterpret_cast<uint32_t*>(
            static_cast<uint8_t*>(entity) + dst * 0x210u + 0x2c4);
        for (int i = 0; i < 0x84; ++i)
            dst_record[i] = src_record[i];
        return 0;
    }
    case 0x1a6: {
        // Difficulty-conditional per-slot float pair (2 tiers).  Tier 0
        // writes (7, 8) and tier 1 writes (1, 2).  The retail uses -0x200
        // as the second boundary and falls through to the (4, 5) write at
        // LAB_00410738, then to the (1, 2) baseline at LAB_00410408.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        if (DAT_00474c98 > 0x1FF) {
            EntityFloat(entity, base + 0x2dc) = 7.0f;
            EntityFloat(entity, base + 0x2e0) = 8.0f;
        } else if (DAT_00474c98 >= -0x200) {
            EntityFloat(entity, base + 0x2dc) = 4.0f;
            EntityFloat(entity, base + 0x2e0) = 5.0f;
        } else {
            EntityFloat(entity, base + 0x2dc) = 1.0f;
            EntityFloat(entity, base + 0x2e0) = 2.0f;
        }
        return 0;
    }
    case 0x1a7: {
        // Difficulty-conditional per-slot float pair (3 tiers).  Tiers are
        // bound by DAT_00474c98 > 599, 199, -199, -400.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        if (DAT_00474c98 > 599) {
            EntityFloat(entity, base + 0x2dc) = 14.0f;
            EntityFloat(entity, base + 0x2e0) = 16.0f;
        } else if (DAT_00474c98 > 199) {
            EntityFloat(entity, base + 0x2dc) = 10.0f;
            EntityFloat(entity, base + 0x2e0) = 12.0f;
        } else if (DAT_00474c98 > -200) {
            EntityFloat(entity, base + 0x2dc) = 7.0f;
            EntityFloat(entity, base + 0x2e0) = 8.0f;
        } else if (DAT_00474c98 >= -600) {
            EntityFloat(entity, base + 0x2dc) = 4.0f;
            EntityFloat(entity, base + 0x2e0) = 5.0f;
        } else {
            EntityFloat(entity, base + 0x2dc) = 1.0f;
            EntityFloat(entity, base + 0x2e0) = 2.0f;
        }
        return 0;
    }
    case 0x1a8: {
        // Linear-interpolation float pair (per-slot 0x2dc, 0x2e0).  Retail
        // applies the same DAT_00474c98 -> [0, 1] range used by 0x15f.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        const float scale = (float)(DAT_00474c98 + 0x400) * (1.0f / 2048.0f);
        EntityFloat(entity, base + 0x2dc) = (2.0f - 1.0f) * scale + 1.0f;
        EntityFloat(entity, base + 0x2e0) = (4.0f - 2.0f) * scale + 2.0f;
        return 0;
    }
    case 0x1a9: {
        // Difficulty-conditional per-slot short pair (2 tiers, operand 5/6).
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        if (DAT_00474c98 > 0x1FF) {
            const int32_t a = ECL_ResolveIntOperand(state->cursor, 5);
            const int32_t b = ECL_ResolveIntOperand(state->cursor, 6);
            *reinterpret_cast<short*>(
                static_cast<uint8_t*>(entity) + base + 0x4b8) = (short)a;
            *reinterpret_cast<short*>(
                static_cast<uint8_t*>(entity) + base + 0x4ba) = (short)b;
        } else if (DAT_00474c98 >= -0x200) {
            const int32_t a = ECL_ResolveIntOperand(state->cursor, 3);
            const int32_t b = ECL_ResolveIntOperand(state->cursor, 4);
            *reinterpret_cast<short*>(
                static_cast<uint8_t*>(entity) + base + 0x4b8) = (short)a;
            *reinterpret_cast<short*>(
                static_cast<uint8_t*>(entity) + base + 0x4ba) = (short)b;
        } else {
            const int32_t a = ECL_ResolveIntOperand(state->cursor, 1);
            const int32_t b = ECL_ResolveIntOperand(state->cursor, 2);
            *reinterpret_cast<short*>(
                static_cast<uint8_t*>(entity) + base + 0x4b8) = (short)a;
            *reinterpret_cast<short*>(
                static_cast<uint8_t*>(entity) + base + 0x4ba) = (short)b;
        }
        return 0;
    }
    case 0x1aa: {
        // Difficulty-conditional per-slot short pair (3 tiers, operand 1..10).
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        const int operand_pair =
            DAT_00474c98 > 599 ? 9 :
            DAT_00474c98 > 199 ? 7 :
            DAT_00474c98 > -200 ? 5 :
            DAT_00474c98 >= -600 ? 3 : 1;
        const int32_t a = ECL_ResolveIntOperand(state->cursor, operand_pair);
        const int32_t b = ECL_ResolveIntOperand(state->cursor, operand_pair + 1);
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4b8) = (short)a;
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4ba) = (short)b;
        return 0;
    }
    case 0x1ab: {
        // Linear-interpolation short pair (per-slot 0x4b8, 0x4ba).  Uses
        // operand 1/2 for the lower-bound and 3/4 for the upper-bound pair.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        const int32_t lo_x = ECL_ResolveIntOperand(state->cursor, 1);
        const int32_t lo_y = ECL_ResolveIntOperand(state->cursor, 2);
        const int32_t hi_x = ECL_ResolveIntOperand(state->cursor, 3);
        const int32_t hi_y = ECL_ResolveIntOperand(state->cursor, 4);
        const int32_t delta_x = (hi_x - lo_x) * (DAT_00474c98 + 0x400);
        const int32_t delta_y = (hi_y - lo_y) * (DAT_00474c98 + 0x400);
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4b8) =
            (short)(((delta_x + (delta_x >> 31 & 0x7FF)) >> 11) + lo_x);
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4ba) =
            (short)(((delta_y + (delta_y >> 31 & 0x7FF)) >> 11) + lo_y);
        return 0;
    }
    case 0x1b3: {
        // Tier-conditional per-slot float pair (4 tiers via DAT_00474c74).
        // Tiers 0/1/2/3 (or 4) write (1, 7), (2, 8), (4, 10), (5, 12).
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        float first;
        float second;
        switch (DAT_00474c74) {
        case 0:  first = 1.0f;  second = 7.0f;  break;
        case 1:  first = 2.0f;  second = 8.0f;  break;
        case 2:  first = 4.0f;  second = 10.0f; break;
        default: first = 5.0f;  second = 12.0f; break;
        }
        EntityFloat(entity, base + 0x2dc) = first;
        EntityFloat(entity, base + 0x2e0) = second;
        return 0;
    }
    case 0x1b4: {
        // Tier-conditional per-slot short pair (4 tiers via DAT_00474c74).
        // Each tier pulls a different pair of operands: (1, 5), (2, 6),
        // (3, 7), (4, 8) for tiers 0..3 (tier 4 reuses tier 3).
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        const unsigned int base = index * 0x210u;
        int pair_index;
        switch (DAT_00474c74) {
        case 0:  pair_index = 1; break;
        case 1:  pair_index = 2; break;
        case 2:  pair_index = 3; break;
        default: pair_index = 4; break;
        }
        const int32_t a = ECL_ResolveIntOperand(state->cursor, pair_index);
        const int32_t b =
            ECL_ResolveIntOperand(state->cursor, pair_index + 4);
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4b8) = (short)a;
        *reinterpret_cast<short*>(
            static_cast<uint8_t*>(entity) + base + 0x4ba) = (short)b;
        return 0;
    }
    case 0x107:
    case 0x108:
    case 0x110: {
        // Sub-entity create (mode 6).  Operand 0 is the slot index in the
        // manager's slot table (DAT_00477704 + 0x30), operand 1 is the
        // sub-slot index.  0x107 (FUN_00448e30) and 0x110 (FUN_00448d00)
        // both fall through to the post-init block (LAB_0040ee5b);
        // 0x108 returns directly without the post-init walk.
        const int32_t slot = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t sub_index = ECL_ResolveIntOperand(state->cursor, 1);
        if (g_pGameStateManager != 0) {
            void* slot_record = *reinterpret_cast<void**>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x30 + slot * 4);
            const uint64_t slot_record_bits =
                reinterpret_cast<uint64_t>(slot_record);
            ECL_SubEntityCreate(
                static_cast<int32_t>(slot_record_bits), sub_index, 6);
        }
        if (opcode == 0x107 || opcode == 0x110) {
            // LAB_0040ee5b: mark the sub-entity via ECL_SubEntityMark and
            // (when the entity flag 0x40000 is clear) copy its spawn
            // position from FUN_00418810.  The readable version of
            // FUN_00418810 is a separate reconstruction pass; for now we
            // mirror the entity's composite position at +0x2c/0x30/0x34.
            int32_t marked = ECL_SubEntityMark(slot);
            (void)marked;
            if ((EntityFlags(entity) & 0x40000u) == 0) {
                uint8_t* record = static_cast<uint8_t*>(entity) + slot * 0x210;
                *reinterpret_cast<float*>(record + 0x340) =
                    EntityFloat(entity, 0x2c);
                *reinterpret_cast<float*>(record + 0x344) =
                    EntityFloat(entity, 0x30);
                *reinterpret_cast<float*>(record + 0x348) =
                    EntityFloat(entity, 0x34);
            }
        }
        return 0;
    }
    case 0x111: {
        // Sub-entity create (FUN_00448e30 mode 6) that performs a richer
        // post-init than 0x107: the spawn position is taken from
        // FUN_00418810 when the 0x40000 flag is clear, otherwise from the
        // entity position.  Then a second operand (2.0f encoding = float
        // operand index 2) is written at record+0x2c, and bit 4 of the
        // record's flag word at +0x35c is set.
        const int32_t slot = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t sub_index = ECL_ResolveIntOperand(state->cursor, 1);
        if (g_pGameStateManager != 0) {
            void* slot_record = *reinterpret_cast<void**>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x30 + slot * 4);
            const uint64_t slot_record_bits =
                reinterpret_cast<uint64_t>(slot_record);
            ECL_SubEntityCreate(
                static_cast<int32_t>(slot_record_bits), sub_index, 6);
        }
        int32_t marked = ECL_SubEntityMark(slot);
        (void)marked;
        uint8_t* record = static_cast<uint8_t*>(entity) + slot * 0x210;
        if ((EntityFlags(entity) & 0x40000u) != 0) {
            *reinterpret_cast<float*>(record + 0x340) =
                EntityFloat(entity, 0x2c);
            *reinterpret_cast<float*>(record + 0x344) =
                EntityFloat(entity, 0x30);
            *reinterpret_cast<float*>(record + 0x348) =
                EntityFloat(entity, 0x34);
        } else {
            // FUN_00418810 returns a fresh 3-float vec from the
            // manager's spawned-entity pool; we treat it as zeros
            // until FUN_00418810 is reconstructed separately.
            *reinterpret_cast<float*>(record + 0x340) = 0.0f;
            *reinterpret_cast<float*>(record + 0x344) = 0.0f;
            *reinterpret_cast<float*>(record + 0x348) = 0.0f;
        }
        const float second = ECL_ResolveFloatOperand(state->cursor, 2);
        *reinterpret_cast<float*>(record + 0x2c) = second;
        *reinterpret_cast<uint32_t*>(record + 0x35c) |= 4u;
        return 0;
    }
    case 0x16b:
        // FUN_0040cea0: set the player-state 0x378c bit 0x10 and dispatch
        // the sound-queue helper.  The dispatch_index (uVar8) is the
        // sound-resource id.
        ECL_ApplyEclFlag();
        return 0;
    case 0x16d:
        // FUN_0041c7d0: walk the entity's secondary script list and mark
        // every entry whose 0x50 byte is zero.  The readable version
        // is a no-op until the entity script list is reconstructed.
        return 0;
    case 0x149:
        // FUN_0040c9a0: play an in-game sound by id.  The readable
        // version is a no-op until the sound queue is reconstructed.
        ECL_ApplyEclFlagAlt();
        return 0;
    case 0x19e:
    case 0x1a0:
    case 0x1a1:
    case 0x1a2:
    case 0x1a3: {
        // FUN_0040cf90 + 0xcf60 (0x19f): per-bullet init from operand 0.
        // The retail writes (0.0, 1.0, 2.0, etc.) into specific
        // offsets of the bullet record; the readable version looks up
        // the record by id and either initializes it (0x19e, 0x1a0,
        // 0x1a1, 0x1a2, 0x1a3) or marks it (0x19f).
        const int32_t bullet_id = ECL_ResolveIntOperand(state->cursor, 0);
        void* record = ECL_FindByID(bullet_id);
        if (record != 0) {
            if (opcode == 0x19e) {
                *reinterpret_cast<float*>(
                    static_cast<uint8_t*>(record) + 0x24) = 1.0f;
                *reinterpret_cast<float*>(
                    static_cast<uint8_t*>(record) + 0x28) = 2.0f;
                *reinterpret_cast<int32_t*>(
                    static_cast<uint8_t*>(record) + 0x2c) = 0;
            } else {
                *reinterpret_cast<float*>(
                    static_cast<uint8_t*>(record) +
                    (opcode == 0x1a0 ? 0x48 :
                     opcode == 0x1a1 ? 0x44 :
                     opcode == 0x1a2 ? 0x3c : 0x440)) = 1.0f;
            }
        }
        return 0;
    }
    case 0x19f: {
        // FUN_0040cf90 + FUN_0040cf60: look up a bullet by id and mark
        // it for release.  The readable version records the id so a
        // test can assert the right lookup happened.
        const int32_t bullet_id = ECL_ResolveIntOperand(state->cursor, 0);
        ECL_ReleaseByID(bullet_id);
        return 0;
    }
    case 0x150: {
        // FUN_0043dd10: read operand 0 and dispatch the script-time
        // animation tick.  The readable version is a no-op until the
        // animation manager is reconstructed.
        ECL_ResolveIntOperand(state->cursor, 0);
        return 0;
    }
    case 0x151: {
        // FUN_0043c8b0: 5-argument script call (mode 1, op, x, y, 0).
        // The readable version is a no-op until the animation manager
        // is reconstructed.
        ECL_ResolveIntOperand(state->cursor, 0);
        ECL_ResolveIntOperand(state->cursor, 1);
        ECL_ResolveIntOperand(state->cursor, 2);
        return 0;
    }
    case 0x152: {
        // FUN_00415db0 + FUN_00408210(0) + FUN_0041c850 + FUN_0040e6a0:
        // full state reset (clear scripts, hide sprites, reset ranges).
        ECL_ResolveIntOperand(state->cursor, 0);
        ECL_RangeReset();
        return 0;
    }
    case 0x157: {
        // FUN_00409c00: dispatch the ECL sound helper with the
        // dispatch_index.  The readable version is a no-op until the
        // sound queue is reconstructed.
        return 0;
    }
    case 0x159: {
        // FUN_0040e6a0: clear the manager's range state.  The
        // readable version is a no-op until the range state machine
        // is reconstructed.
        ECL_RangeReset();
        return 0;
    }
    case 0x1a4: {
        // FUN_00408100(operand 0, 1, 0) + FUN_0041c800: enable the
        // boss range.  The readable version is a no-op until the
        // range state machine is reconstructed.
        ECL_ResolveFloatOperand(state->cursor, 0);
        return 0;
    }
    case 0x1a5: {
        // FUN_00408100(operand 0, 0, 0) + FUN_0041c800: disable the
        // boss range.  The readable version is a no-op until the
        // range state machine is reconstructed.
        ECL_ResolveFloatOperand(state->cursor, 0);
        return 0;
    }
    case 0x109:
    case 0x10a:
    case 0x10c: {
        // Manager-counter guards.  Retail returns early when the
        // DAT_00477704 + 0x10 counter is non-zero (otherwise it falls
        // through to 0x100/0x101/0x105 respectively, the complex enemy-
        // init + D3DXVec3Project path that remains on the retail image).
        if (g_pGameStateManager != 0 &&
            *reinterpret_cast<int32_t*>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x10) != 0) {
            return 0;
        }
        return 0;
    }
    case 0x10b:
    case 0x10f: {
        // Inverted guard: retail proceeds only when the manager counter
        // is non-zero, otherwise falls through to 0x104 (0x10b) or
        // 0x10e (0x10f).  Both fall-through bodies are the D3DXVec3Project
        // enemy-init path, kept on the retail image; both branches of
        // the readable stub return 0.
        if (g_pGameStateManager != 0 &&
            *reinterpret_cast<int32_t*>(
                static_cast<uint8_t*>(g_pGameStateManager) + 0x10) == 0) {
            return 0;
        }
        return 0;
    }
    case 0x100:
    case 0x101:
    case 0x104:
    case 0x105:
    case 0x10e: {
        // Enemy-init family: the host stage supplies the retail manager/list
        // binding, while this canonical dispatcher retains opcode selection
        // and operand ownership for every VM. A missing binding is explicit
        // and leaves the instruction consumed without fabricating an entity.
        (void)ECL_ExecuteEnemySpawn(entity, opcode, state->cursor);
        return 0;
    }
    case 0x103:
    case 0x106:
    case 0x10d: {
        // Sub-entity create via FUN_00448e30 mode 5 (slot from operand 0,
        // sub_index from operand 1) and FUN_00449630 link.  0x106 reads
        // player position at +0x46/0x4c after the link; 0x10d folds in an
        // extra 0xc4 word.  The readable version stubs to recording
        // (slot, sub_index, 5) and marking the slot, mirroring 0x107.
        const int32_t slot = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t sub_index = ECL_ResolveIntOperand(state->cursor, 1);
        ECL_SubEntityCreate(slot, sub_index, 5);
        ECL_SubEntityMark(slot);
        return 0;
    }
    case 0x119:
    case 0x11b: {
        // Retail loc_40F273 (jumptable cases 281,283).  Per-axis sub-record
        // init: the record lives at entity+0x13C (0x119) / +0x188 (0x11b)
        // and is seeded from the position triple at entity+0x58 / +0x84.
        // Resolves float operands 2/3 and int operands 0/1, writes the
        // record triple (dword_491C14/18/1C are zero-filled BSS), copies
        // the source triple, then hands the record to FUN_004050d0
        // (ECL_InitBulletRecord).  [source+0x28] bit 0 is cleared.
        const unsigned int source_offset = opcode == 0x119 ? 0x58u : 0x84u;
        const unsigned int record_offset = opcode == 0x119 ? 0x13Cu : 0x188u;
        uint8_t* source = static_cast<uint8_t*>(entity) + source_offset;
        uint8_t* record = static_cast<uint8_t*>(entity) + record_offset;

        const float f2 = ECL_ResolveFloatOperand(state->cursor, 2);
        const float f3 = ECL_ResolveFloatOperand(state->cursor, 3);
        EntityInt(record, 0x44) = ECL_ResolveIntOperand(state->cursor, 0);
        // dword_491C14/18/1C: zero-filled BSS in retail; the record's two
        // 3-float blocks at +0x18 and +0x24 are seeded from them.
        std::memset(record + 0x18, 0, 3 * sizeof(float));
        std::memset(record + 0x24, 0, 3 * sizeof(float));
        EntityInt(record, 0x48) = ECL_ResolveIntOperand(state->cursor, 1);
        // record+0x00..0x08 = source triple (entity+0x58/0x84 + 0..8).
        std::memcpy(record + 0x00, source, 3 * sizeof(float));
        // X/Y: operand when >= 0, otherwise the source triple component.
        // Retail's `fcomp dbl_470D58 (=0.0); test ah,41h; jnz` branch keeps
        // the operand for positive values and falls back to [edi]/[edi+4].
        const float x = (DAT_00470d58 < f2) ? f2 : EntityFloat(source, 0x00);
        const float y = (DAT_00470d58 < f3) ? f3 : EntityFloat(source, 0x04);
        EntityFloat(record, 0x0C) = x;
        EntityFloat(record, 0x10) = y;
        EntityFloat(record, 0x14) = 0.0f;
        ECL_InitBulletRecord(record);
        EntityInt(source, 0x28) &= ~1u;
        return 0;
    }
    case 0x11d:
    case 0x11f: {
        // Retail loc_40F460 (jumptable cases 285,287).  Comprehensive
        // per-axis record init at entity+0x1D4 (0x11d) / +0x210 (0x11f),
        // reading float operands 2/3 and int operands 0/1.
        //
        // i1 == 7: X = f2 if f2 > 0 else 0; Y = f3 if f3 > 0 else 0.
        // i1 != 7: X = f2 (optionally mirrored around DAT_00470b94 when
        // entity flag 0x800 is set) if f2 > 0, else [source+0x1C];
        //          Y = f3 if f3 > 0 else [source+0x18].
        // Then the angle-unwrap step brings [source+0x1C] and X within a
        // half-turn of each other before the record is written:
        // record+0x00..0x0C = (a, b, X, Y), record fields +0x10/14/18/1C
        // seeded from dword_491C20/24 (zero BSS), record+0x34 = i0,
        // record+0x38 = i1, and FUN_00412db0 (ECL_InitMovementRecord)
        // arms the record.  [source+0x28] bit 0 is cleared.
        const unsigned int source_offset = opcode == 0x11d ? 0x58u : 0x84u;
        const unsigned int record_offset = opcode == 0x11d ? 0x1D4u : 0x210u;
        uint8_t* source = static_cast<uint8_t*>(entity) + source_offset;
        uint8_t* record = static_cast<uint8_t*>(entity) + record_offset;

        const float f2 = ECL_ResolveFloatOperand(state->cursor, 2);
        const float f3 = ECL_ResolveFloatOperand(state->cursor, 3);
        const int32_t i1 = ECL_ResolveIntOperand(state->cursor, 1);
        EntityInt(record, 0x38) = i1;

        float x;
        float y;
        if (i1 == 7) {
            x = (DAT_00470d58 < f2) ? f2 : 0.0f;
            y = (DAT_00470d58 < f3) ? f3 : 0.0f;
        } else {
            if (DAT_00470d58 < f2) {
                float value = f2;
                if ((EntityFlags(entity) & 0x800u) != 0) {
                    // Retail loc_40F507's mirror: f2 -= pi/2, wrap,
                    // f2 = pi/2 - f2, wrap.  sub_44BC70 is the angle
                    // wrap into [-pi, pi] that ECL_WrapValue performs.
                    value -= DAT_00470b94;
                    ECL_WrapValue(&value);
                    value = DAT_00470b94 - value;
                    ECL_WrapValue(&value);
                }
                x = value;
            } else {
                x = EntityFloat(source, 0x1C);
            }
            y = (DAT_00470d58 < f3) ? f3 : EntityFloat(source, 0x18);
        }

        // Angle-unwrap: only when |[source+0x1C] - x| >= pi do we add a
        // full turn to one of them.  Retail (loc_570/5AD) adds 2pi to the
        // smaller so the pair lands within a half-turn.
        float a = EntityFloat(source, 0x1C);
        const float b = EntityFloat(source, 0x18);
        if (std::fabs(a - x) >= 3.14159274f) {
            if (a < x)
                a += 6.28318548f;
            else
                x += 6.28318548f;
        }

        const int32_t i0 = ECL_ResolveIntOperand(state->cursor, 0);
        EntityInt(record, 0x34) = i0;
        // dword_491C20/24 are zero-filled BSS in retail.
        std::memset(record + 0x10, 0, 4 * sizeof(float));
        EntityFloat(record, 0x00) = a;
        EntityFloat(record, 0x04) = b;
        EntityFloat(record, 0x08) = x;
        EntityFloat(record, 0x0C) = y;
        ECL_InitMovementRecord(record);
        EntityInt(source, 0x28) &= ~1u;
        return 0;
    }
    case 0x121:
    case 0x123: {
        // Retail loc_40F6F1 (jumptable cases 289,291).  Two-record init: a
        // per-axis record (rec1 at entity+0x1D4 for 0x121 / +0x210 for
        // 0x123) plus a per-track record (rec2 at entity+0x24C / +0x288),
        // all read from the source triple block (entity+0x58 / +0x84).
        // Resolves float operands 2/3/4/5 and int operands 0/1.  X/Y come
        // from the operands with [source+0x1C]/[source+0x18] fallback; the
        // second pair reuses f5 (or [source+0x24]) and f4 (or
        // [source+0x20]).  Both records are armed with
        // FUN_00412db0 (ECL_InitMovementRecord).  Finally the source triple
        // is copied over source+0x0C and [source+0x28] bit 0 is set.
        const unsigned int source_offset = opcode == 0x121 ? 0x58u : 0x84u;
        const unsigned int rec1_offset = opcode == 0x121 ? 0x1D4u : 0x210u;
        const unsigned int rec2_offset = opcode == 0x121 ? 0x24Cu : 0x288u;
        uint8_t* source = static_cast<uint8_t*>(entity) + source_offset;
        uint8_t* rec1 = static_cast<uint8_t*>(entity) + rec1_offset;
        uint8_t* rec2 = static_cast<uint8_t*>(entity) + rec2_offset;

        const float f2 = ECL_ResolveFloatOperand(state->cursor, 2);
        const float f3 = ECL_ResolveFloatOperand(state->cursor, 3);
        const float f4 = ECL_ResolveFloatOperand(state->cursor, 4);
        const float f5 = ECL_ResolveFloatOperand(state->cursor, 5);
        const float x = (DAT_00470d58 < f2) ? f2 : EntityFloat(source, 0x1C);
        const float y = (DAT_00470d58 < f3) ? f3 : EntityFloat(source, 0x18);
        const float w = (DAT_00470d58 < f4) ? f4 : EntityFloat(source, 0x20);
        const float z = (DAT_00470d58 < f5) ? f5 : EntityFloat(source, 0x24);
        const float a = EntityFloat(source, 0x18);
        const float b = EntityFloat(source, 0x1C);
        const float c = EntityFloat(source, 0x24);
        const float d = EntityFloat(source, 0x20);

        const int32_t i0 = ECL_ResolveIntOperand(state->cursor, 0);
        const int32_t i1 = ECL_ResolveIntOperand(state->cursor, 1);

        // rec1: (b, a, X, Y) with zeroed 0x10..0x1C block.
        EntityFloat(rec1, 0x00) = b;
        EntityFloat(rec1, 0x04) = a;
        EntityFloat(rec1, 0x08) = x;
        EntityFloat(rec1, 0x0C) = y;
        std::memset(rec1 + 0x10, 0, 4 * sizeof(float));
        EntityInt(rec1, 0x34) = i0;
        EntityInt(rec1, 0x38) = i1;
        ECL_InitMovementRecord(rec1);
        // rec2: (d, c, w, z) with a zeroed 0x10..0x14 block.
        EntityFloat(rec2, 0x00) = d;
        EntityFloat(rec2, 0x04) = c;
        EntityFloat(rec2, 0x08) = w;
        EntityFloat(rec2, 0x0C) = z;
        std::memset(rec2 + 0x10, 0, 4 * sizeof(float));
        EntityInt(rec2, 0x34) = i0;
        EntityInt(rec2, 0x38) = i1;
        ECL_InitMovementRecord(rec2);
        // Source triple -> source + 0x0C, then arm bit 0 of source+0x28.
        std::memcpy(source + 0x0C, source, 3 * sizeof(float));
        EntityInt(source, 0x28) |= 1u;
        return 0;
    }
    case 0x124:
    case 0x125: {
        // Retail loc_40FA84 places movement records using player position,
        // movement bounds, and PRNG draws. No placement is implemented here.
        char edge[96];
        std::snprintf(edge, sizeof(edge), "ECL opcode 0x%03X: random movement placement", opcode);
        Runtime_MissingEdge(0x0040E770, edge);
    }
    case 0x156:
    case 0x15c:
    case 0x165:
    case 0x166:
    case 0x167: {
        // Retail loc_410E7B decodes text and queues it through FUN_00409280.
        // The sound-command manager binding is not reconstructed.
        char edge[96];
        std::snprintf(edge, sizeof(edge), "ECL opcode 0x%03X: encrypted sound commands", opcode);
        Runtime_MissingEdge(0x0040E770, edge);
    }
    case 0x191: {
        // Retail 0x004073E0 materializes the configured record relative to the
        // entity position, then launches it through the bullet manager.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        constexpr int kSlotLimit = (0x2514 - 0x2C4) / 0x210;
        if (index < 0 || index >= kSlotLimit)
            return 0;
        const unsigned int base = static_cast<unsigned int>(index) * 0x210u;
        const unsigned int vector =
            static_cast<unsigned int>(index * 3 + 0x4D1) * 4u;
        const float x = EntityFloat(entity, vector) +
                        EntityFloat(entity, 0x2C);
        const float y = EntityFloat(entity, vector + 4) +
                        EntityFloat(entity, 0x30);
        const float z = EntityFloat(entity, vector + 8) +
                        EntityFloat(entity, 0x34);
        uint8_t* record = static_cast<uint8_t*>(entity) + base;
        EntityFloat(record, 0x2C8) = x;
        EntityFloat(record, 0x2CC) = y;
        EntityFloat(record, 0x2D0) = z;

        // The retail distance gate is evaluated against the player block. The
        // host publishes the same launch boundary through the entity field; a
        // zero boundary is the shipped default and launches immediately.
        if (EntityFloat(entity, 0x1454) <= 0.0f)
            ECL_ExecuteProjectileSpawn(
                static_cast<uint8_t*>(entity) + base + 0x2C4, 0, 0, x, y, z);
        return 0;
    }
    case 0x195: {
        // Initial 1.0/2.0 float values into laser record offset
        // (LAB_00410408 path shared with 0x1a6).  Real write.
        const int32_t index = ECL_ResolveIntOperand(state->cursor, 0);
        uint8_t* record = static_cast<uint8_t*>(entity) + index * 0x210;
        *reinterpret_cast<float*>(record + 0x2dc) = 1.0f;
        *reinterpret_cast<float*>(record + 0x2e0) = 2.0f;
        return 0;
    }
    case 0x19a: {
        // Retail invokes FUN_00408210(1) and FUN_0041C850 here.
        char edge[96];
        std::snprintf(edge, sizeof(edge), "ECL opcode 0x%03X: manager cleanup", opcode);
        Runtime_MissingEdge(0x0040E770, edge);
    }
    case 0x19c:
    case 0x19d:
    case 0x1ac:
    case 0x1ad:
    case 0x1ae:
    case 0x1af:
    case 0x1b0:
    case 0x1b1:
    case 0x1b2: {
        // Retail prepares a 0x77-float buffer and dispatches FUN_0041C510;
        // the per-opcode seed/copy and state-mixer integration are missing.
        char edge[96];
        std::snprintf(edge, sizeof(edge), "ECL opcode 0x%03X: enemy state mixer", opcode);
        Runtime_MissingEdge(0x0040E770, edge);
    }
    default:
        // Unclassified opcodes currently advance without work. The retail
        // default/valid-opcode boundary still needs auditing; no retail code
        // is called here. This dispatcher remains partial in the ledger.
        return 0;
    }
}
