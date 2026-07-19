#include "th10/script/entity_vm.hpp"

#include <cmath>

EntityScriptStepResult EntityScript_ApplyIntegerArithmetic(
    int opcode, int* destination, int operand) {
    if (destination == 0)
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    switch (opcode) {
    case ENTITY_SCRIPT_SET_INT:
        *destination = operand;
        break;
    case ENTITY_SCRIPT_ADD_INT:
        *destination += operand;
        break;
    case ENTITY_SCRIPT_SUB_INT:
        *destination -= operand;
        break;
    case ENTITY_SCRIPT_MUL_INT:
        *destination *= operand;
        break;
    case ENTITY_SCRIPT_DIV_INT:
        if (operand == 0)
            return ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO;
        *destination /= operand;
        break;
    case ENTITY_SCRIPT_MOD_INT:
        if (operand == 0)
            return ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO;
        *destination %= operand;
        break;
    default:
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
    return ENTITY_SCRIPT_STEP_APPLIED;
}

EntityScriptStepResult EntityScript_ApplyFloatArithmetic(
    int opcode, float* destination, float operand) {
    if (destination == 0)
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    switch (opcode) {
    case ENTITY_SCRIPT_SET_FLOAT:
        *destination = operand;
        break;
    case ENTITY_SCRIPT_ADD_FLOAT:
        *destination += operand;
        break;
    case ENTITY_SCRIPT_SUB_FLOAT:
        *destination -= operand;
        break;
    case ENTITY_SCRIPT_MUL_FLOAT:
        *destination *= operand;
        break;
    case ENTITY_SCRIPT_DIV_FLOAT:
        if (operand == 0.0f)
            return ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO;
        *destination /= operand;
        break;
    default:
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
    return ENTITY_SCRIPT_STEP_APPLIED;
}

EntityScriptStepResult EntityScript_ApplyBinaryInteger(
    int opcode, int* destination, int left, int right) {
    if (destination == 0) return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    switch (opcode) {
    case 0x12: *destination = left + right; break;
    case 0x14: *destination = left - right; break;
    case 0x16: *destination = left * right; break;
    case 0x18:
        if (right == 0) return ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO;
        *destination = left / right;
        break;
    case 0x1a:
        if (right == 0) return ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO;
        *destination = left % right;
        break;
    default: return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
    return ENTITY_SCRIPT_STEP_APPLIED;
}

EntityScriptStepResult EntityScript_ApplyBinaryFloat(
    int opcode, float* destination, float left, float right) {
    if (destination == 0) return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    switch (opcode) {
    case 0x13: *destination = left + right; break;
    case 0x15: *destination = left - right; break;
    case 0x17: *destination = left * right; break;
    case 0x19:
        if (right == 0.0f) return ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO;
        *destination = left / right;
        break;
    default: return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
    return ENTITY_SCRIPT_STEP_APPLIED;
}

EntityScriptStepResult EntityScript_AssignRandomFloat(
    float* destination, float minimum, float maximum,
    EntityScriptRandomFloat random, void* context) {
    if (destination == 0 || random == 0)
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    const float unit = random(context);
    *destination = minimum + (maximum - minimum) * unit;
    return ENTITY_SCRIPT_STEP_APPLIED;
}

bool EntityScript_CompareInteger(int opcode, int left, int right) {
    switch (opcode) {
    case 0x1c: return left != right;
    case 0x1e: return left == right;
    case 0x20: return left > right;
    case 0x22: return left < right;
    case 0x24: return left <= right;
    case 0x26: return left >= right;
    default: return false;
    }
}

bool EntityScript_CompareFloat(int opcode, float left, float right) {
    switch (opcode) {
    case 0x1d: return left != right;
    case 0x1f: return left == right;
    case 0x21: return left > right;
    case 0x23: return left < right;
    case 0x25: return left <= right;
    case 0x27: return left >= right;
    default: return false;
    }
}

EntityScriptStepResult EntityScript_ApplyUnaryFloat(
    int opcode, float* destination, float operand) {
    if (destination == 0) return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    switch (opcode) {
    case 0x2a: *destination = std::sin(operand); break;
    case 0x2b: *destination = std::cos(operand); break;
    case 0x2c: *destination = std::tan(operand); break;
    case 0x2e: *destination = std::atan(operand); break;
    default: return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
    return ENTITY_SCRIPT_STEP_APPLIED;
}

EntityScriptStepResult EntityScript_ExecuteOne(
    EntityScriptCursor* cursor, EntityScriptResolver* resolver) {
    if (cursor == 0 || resolver == 0 || cursor->stream == 0)
        return ENTITY_SCRIPT_STEP_MALFORMED;
    if (cursor->halted || cursor->offset == cursor->stream_size)
        return ENTITY_SCRIPT_STEP_FINISHED;
    if (cursor->offset > cursor->stream_size ||
        cursor->stream_size - cursor->offset < sizeof(EntityScriptInstruction))
        return ENTITY_SCRIPT_STEP_MALFORMED;

    const EntityScriptInstruction* instruction =
        reinterpret_cast<const EntityScriptInstruction*>(
            cursor->stream + cursor->offset);
    if (instruction->size < sizeof(EntityScriptInstruction) ||
        instruction->size > cursor->stream_size - cursor->offset)
        return ENTITY_SCRIPT_STEP_MALFORMED;
    if (instruction->opcode == ENTITY_SCRIPT_END ||
        instruction->opcode == ENTITY_SCRIPT_RETURN) {
        if (instruction->opcode == ENTITY_SCRIPT_RETURN &&
            cursor->call_depth != 0) {
            cursor->offset = cursor->call_stack[--cursor->call_depth];
            return ENTITY_SCRIPT_STEP_APPLIED;
        }
        cursor->halted = true;
        cursor->offset += instruction->size;
        return ENTITY_SCRIPT_STEP_FINISHED;
    }
    if (instruction->opcode == ENTITY_SCRIPT_JUMP ||
        instruction->opcode == ENTITY_SCRIPT_CALL ||
        instruction->opcode == ENTITY_SCRIPT_BRANCH_NONZERO) {
        const int relative = (int)instruction->operand;
        if (instruction->opcode == ENTITY_SCRIPT_BRANCH_NONZERO &&
            resolver->ResolveInteger((unsigned short)instruction->destination,
                (instruction->flags & ENTITY_SCRIPT_DESTINATION_INDIRECT) != 0) == 0)
            cursor->offset += instruction->size;
        else {
            if (instruction->opcode == ENTITY_SCRIPT_CALL) {
                if (cursor->call_depth == 16)
                    return ENTITY_SCRIPT_STEP_MALFORMED;
                cursor->call_stack[cursor->call_depth++] =
                    cursor->offset + instruction->size;
            }
            const long long target = (long long)cursor->offset + relative;
            if (target < 0 || (unsigned long long)target > cursor->stream_size)
                return ENTITY_SCRIPT_STEP_MALFORMED;
            cursor->offset = (unsigned int)target;
        }
        return ENTITY_SCRIPT_STEP_APPLIED;
    }
    if (instruction->opcode == 0x14d || instruction->opcode == 0x14f ||
        instruction->opcode == 0x150 || instruction->opcode == 0x151) {
        const EntityScriptStepResult result = EntityScript_ExecuteServiceOpcode(
            cursor->services, instruction->opcode, (int)instruction->operand);
        if (result == ENTITY_SCRIPT_STEP_APPLIED)
            cursor->offset += instruction->size;
        return result;
    }

    const bool operand_indirect =
        (instruction->flags & ENTITY_SCRIPT_OPERAND_INDIRECT) != 0;
    const bool destination_indirect =
        (instruction->flags & ENTITY_SCRIPT_DESTINATION_INDIRECT) != 0;
    EntityScriptStepResult result;
    if ((instruction->opcode & 1u) == 0) {
        int* destination = resolver->ResolveIntegerDestination(
            instruction->destination, destination_indirect);
        const int operand = resolver->ResolveInteger(
            instruction->operand, operand_indirect);
        result = EntityScript_ApplyIntegerArithmetic(
            instruction->opcode, destination, operand);
    } else {
        float* destination = resolver->ResolveFloatDestination(
            instruction->destination, destination_indirect);
        const float operand = resolver->ResolveFloat(
            instruction->operand, operand_indirect);
        result = EntityScript_ApplyFloatArithmetic(
            instruction->opcode, destination, operand);
    }
    if (result == ENTITY_SCRIPT_STEP_APPLIED)
        cursor->offset += instruction->size;
    return result;
}

EntityScriptStepResult EntityScript_JumpRelative(
    EntityScriptCursor* cursor, int relative_bytes) {
    if (cursor == 0 || cursor->stream == 0 || cursor->offset > cursor->stream_size)
        return ENTITY_SCRIPT_STEP_MALFORMED;
    const long long target = (long long)cursor->offset + relative_bytes;
    if (target < 0 || (unsigned long long)target > cursor->stream_size)
        return ENTITY_SCRIPT_STEP_MALFORMED;
    cursor->offset = (unsigned int)target;
    return ENTITY_SCRIPT_STEP_APPLIED;
}

EntityScriptStepResult EntityScript_InvokeService(
    const EntityScriptServices* services, int service, int value) {
    if (services == 0)
        return ENTITY_SCRIPT_STEP_MALFORMED;
    switch (service) {
    case 0:
        if (services->reset_timer == 0) return ENTITY_SCRIPT_STEP_UNSUPPORTED;
        services->reset_timer(services->context, value);
        return ENTITY_SCRIPT_STEP_APPLIED;
    case 1:
        if (services->resource_transition == 0)
            return ENTITY_SCRIPT_STEP_UNSUPPORTED;
        services->resource_transition(services->context, value);
        return ENTITY_SCRIPT_STEP_APPLIED;
    case 2:
        if (services->emit_animation_event == 0)
            return ENTITY_SCRIPT_STEP_UNSUPPORTED;
        services->emit_animation_event(services->context, service, value);
        return ENTITY_SCRIPT_STEP_APPLIED;
    default:
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
}

EntityScriptStepResult EntityScript_ExecuteServiceOpcode(
    const EntityScriptServices* services, int opcode, int value) {
    switch (opcode) {
    case 0x14d:
        return EntityScript_InvokeService(services, 0, 0);
    case 0x14f:
        return EntityScript_InvokeService(services, 0, value);
    case 0x150:
        return EntityScript_InvokeService(services, 1, value);
    case 0x151:
        return EntityScript_InvokeService(services, 2, value);
    default:
        return ENTITY_SCRIPT_STEP_UNSUPPORTED;
    }
}
