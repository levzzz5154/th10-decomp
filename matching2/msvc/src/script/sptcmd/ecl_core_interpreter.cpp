// Execute core ECL instructions until the VM waits, terminates, or reaches a future frame.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"
#pragma intrinsic(sin, cos, atan2)

// Compiled out in retail; opcode 30 still formats its arguments for it.
static void DebugLog(const char* format, ...) {}

// A binary stack operation pops its right operand first. Keep each pop's
// address-taken destination in the case's scope: sharing storage across cases
// or moving these locals into a helper changes the recovered stack frame.
#define ECL_POP_PAIR(type, pop, left, right) \
    type right;                             \
    pop(&right);                            \
    type left;                              \
    pop(&left)

// Both format specifiers consume one descriptor. Resolve according to its
// source tag, then pass the type required by the format specifier.
#define ECL_LOG_ARGUMENT(output_type) \
    do { \
        const char tag = instr->s[instr->i[0] + argument_index * 8 + 4]; \
        if (tag == 'f' || tag == 'g') { \
            DebugLog(buffer, static_cast<output_type>(FloatOperands().ResolveFloatValue(argument_index + 1, \
                instr->f[instr->i[0] / 4 + 2 + argument_index * 2]))); \
        } else { \
            DebugLog(buffer, static_cast<output_type>(IntValue(argument_index + 1, \
                instr->i[instr->i[0] / 4 + 2 + argument_index * 2]))); \
        } \
    } while (0)

// Core ECL VM opcodes (0..87); owner-specific opcodes (>= 0x100) delegate to owner->Execute().
enum EclCoreOpcode {
    ECL_NOP = 0,
    ECL_DELETE = 1,
    ECL_RETURN = 10,
    ECL_CALL = 11,
    ECL_JMP = 12,
    ECL_JMP_Z = 13,
    ECL_JMP_NZ = 14,
    ECL_SPAWN_CHILD = 15,
    ECL_SPAWN_CHILD_ID = 16,
    ECL_KILL_CHILD = 17,
    ECL_PAUSE_CHILD = 18,
    ECL_RESUME_CHILD = 19,
    ECL_SET_CHILD_STATE = 20,
    ECL_RESET_VAR_BINDINGS = 21,
    ECL_DEBUG_LOG = 30,
    ECL_STACK_ALLOC = 40,
    ECL_STACK_FREE = 41,
    ECL_PUSH_INT = 42,
    ECL_POP_INT = 43,
    ECL_PUSH_FLOAT = 44,
    ECL_POP_FLOAT = 45,
    ECL_ADD_I = 50,
    ECL_ADD_F = 51,
    ECL_SUB_I = 52,
    ECL_SUB_F = 53,
    ECL_MUL_I = 54,
    ECL_MUL_F = 55,
    ECL_DIV_I = 56,
    ECL_DIV_F = 57,
    ECL_MOD_I = 58,
    ECL_CMP_EQ_I = 59,
    ECL_CMP_EQ_F = 60,
    ECL_CMP_NE_I = 61,
    ECL_CMP_NE_F = 62,
    ECL_CMP_LT_I = 63,
    ECL_CMP_LT_F = 64,
    ECL_CMP_LE_I = 65,
    ECL_CMP_LE_F = 66,
    ECL_CMP_GT_I = 67,
    ECL_CMP_GT_F = 68,
    ECL_CMP_GE_I = 69,
    ECL_CMP_GE_F = 70,
    ECL_NOT_I = 71,
    ECL_NOT_F = 72,
    ECL_OR_I = 73,
    ECL_AND_I = 74,
    ECL_BIT_XOR = 75,
    ECL_BIT_OR = 76,
    ECL_BIT_AND = 77,
    ECL_DEC_INT = 78,
    ECL_SIN = 79,
    ECL_COS = 80,
    ECL_POLAR_TO_XY = 81,
    ECL_NORMALIZE_ANGLE = 82,
    ECL_WAIT = 83,
    ECL_NEG_I = 84,
    ECL_NEG_F = 85,
    ECL_LENGTH_SQ = 86,
    ECL_ATAN2_DELTA = 87
};

enum EclVmFlag {
    ECL_VM_PAUSED = 1
};

int EclVm::Run(float delta) {
    if (instr == 0) return -1;
    EclInstr** pc = &instr;
    while ((float)instr->time <= time) {
        EclInstr* instruction = *pc;
        if (instruction->rank & rank) {
            switch (instruction->id) {
            // VM termination and return. A saved PC is the call instruction; the
            // normal advance below steps past it after restoring the caller's time.
            case ECL_NOP:
                break;
            case ECL_DELETE:
                *pc = 0;
                return -1;
            case ECL_RETURN:
                stack.Pop();
                if (stack.sp == 0) {
                    *pc = 0;
                    return -1;
                }
                {
                    EclStack* frame = &stack;
                    frame->PopRaw(pc);
                }
                PopRaw(&time);
                if (*pc == 0) return -1;
                break;

            // Spawn or update a child VM selected by its ID.
            case ECL_SPAWN_CHILD:
                owner->SpawnChild(-1, 0);
                break;
            case ECL_RESET_VAR_BINDINGS:
                owner->ResetVariableBindings();
                break;
            case ECL_SPAWN_CHILD_ID:
                owner->SpawnChild(
                    IntValue(1, instruction->i[(unsigned int)(instruction->i[0] + 4) / 4]), 1);
                break;
            case ECL_KILL_CHILD: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) node->vm->instr = 0;
                break;
            }
            case ECL_PAUSE_CHILD: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) node->vm->flags |= ECL_VM_PAUSED;
                break;
            }
            case ECL_RESUME_CHILD: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) node->vm->flags &= ~ECL_VM_PAUSED;
                break;
            }
            case ECL_SET_CHILD_STATE: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) {
                    EclVm* child = node->vm;
                    child->f1018 = IntOperand(1);
                }
                break;
            }

            // Calls and relative branches replace the PC. Continue dispatch at the
            // new instruction without applying the normal instruction-size advance.
            case ECL_CALL:
                if (Start(this, 0)) return -1;
                continue;
            case ECL_JMP_NZ: {
                int condition;
                PopInt(&condition);
                if (condition) goto relative_jump;
                break;
            }
            case ECL_JMP_Z: {
                int condition;
                PopInt(&condition);
                if (condition) break;
            }
            // A zero condition falls through to the unconditional jump.
            case ECL_JMP:
            relative_jump:
                {
                    EclInstr* branch = *pc;
                    time = (float)branch->i[1];
                    *pc = (EclInstr*)((char*)branch + branch->i[0]);
                }
                continue;
            case ECL_WAIT:
                time -= (float)IntOperand(0);
                break;

            // Stack frames, then typed transfers between operands and the stack.
            case ECL_STACK_ALLOC:
                stack.Push(IntOperand(0));
                break;
            case ECL_STACK_FREE:
                stack.Pop();
                break;
            case ECL_PUSH_INT: {
                int value = IntOperand(0);
                stack.Write('i', 4, &value);
                break;
            }
            case ECL_POP_INT: {
                int* destination = IntDest(0);
                PopInt(destination);
                break;
            }
            case ECL_PUSH_FLOAT: {
                float value = FloatOperand(0);
                stack.Write('f', 4, &value);
                break;
            }
            case ECL_POP_FLOAT: {
                float* destination = FloatDest(0);
                PopFloat(destination);
                break;
            }

            // Integer arithmetic reuses the left operand storage for the result:
            // the integer and float operations both push from that same word.
            case ECL_ADD_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage + right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case ECL_SUB_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage - right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case ECL_MUL_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage * right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case ECL_DIV_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage / right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case ECL_MOD_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage % right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }

            // Floating-point arithmetic uses the same pop order and a float result tag.
            case ECL_ADD_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage + right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case ECL_SUB_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage - right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case ECL_MUL_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage * right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case ECL_DIV_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage / right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }

            // Integer comparisons and logical NOT produce an integer result.
            case ECL_CMP_EQ_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand == right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_NE_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand != right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_LT_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand < right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_LE_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand <= right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_GT_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand > right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_GE_I: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand >= right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_NOT_I: {
                int value;
                PopInt(&value);
                int result = value == 0;
                stack.Write('i', 4, &result);
                break;
            }

            // Floating-point comparisons also push an integer, not a float.
            case ECL_CMP_EQ_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand == right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_NE_F: {
                EclStack* operands = &stack;
                float right_storage;
                PopFloat(&right_storage);
                float left_storage;
                operands->PopFloat(&left_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand != right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_LT_F: {
                ECL_POP_PAIR(float, stack.PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand < right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_LE_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand <= right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_GT_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand > right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_CMP_GE_F: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand >= right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_NOT_F: {
                float value;
                PopFloat(&value);
                int result = (value == 0.0f) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }

            // Logical and bitwise operations on integer stack words.
            case ECL_OR_I: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = (left || right) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_AND_I: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = (left && right) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_BIT_XOR: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = left ^ right;
                stack.Write('i', 4, &result);
                break;
            }
            case ECL_BIT_OR: {
                ECL_POP_PAIR(int, stack.PopInt, left, right);
                int result = left | right;
                stack.Write('i', sizeof(int), &result);
                break;
            }
            case ECL_BIT_AND: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = left & right;
                stack.Write('i', 4, &result);
                break;
            }

            // Negation and post-decrement.
            case ECL_NEG_I: {
                int value;
                PopInt(&value);
                value = -value;
                stack.Write('i', 4, &value);
                break;
            }
            case ECL_NEG_F: {
                // Negate the integer word, then write it back with the float tag.
                int word;
                PopFloat((float*)&word);
                word = -word;
                stack.Write('f', 4, &word);
                break;
            }
            case ECL_DEC_INT: {
                int original_value = IntOperand(0);
                int* destination = IntDest(0);
                *destination = original_value - 1;
                stack.Write('i', 4, &original_value);
                break;
            }

            // Trigonometry and vector operations.
            case ECL_SIN: {
                float angle;
                PopFloat(&angle);
                float result = (float)sin(angle);
                stack.Write('f', 4, &result);
                break;
            }
            case ECL_COS: {
                float angle;
                PopFloat(&angle);
                float result = (float)cos(angle);
                stack.Write('f', 4, &result);
                break;
            }
            case ECL_POLAR_TO_XY: {
                EclPolar vector;
                vector.SetPolar(Angle_Normalize(FloatOperand(2)), FloatOperand(3));
                *FloatDest(0) = vector.x;
                *FloatDest(1) = vector.y;
                break;
            }
            case ECL_LENGTH_SQ: {
                float x = FloatOperand(1);
                float y = FloatOperand(2);
                *FloatDest(0) = y * y + x * x;
                break;
            }
            case ECL_NORMALIZE_ANGLE: {
                float* destination = FloatDest(0);
                *destination = Angle_Normalize(FloatOperand(0));
                break;
            }
            case ECL_ATAN2_DELTA: {
                float x = FloatOperand(2) - FloatOperand(0);
                float y = FloatOperand(3) - FloatOperand(1);
                y = (float)atan2(y, x);
                *FloatDest(0) = y;
                break;
            }

            // Packed debug format and typed arguments. The cursor scans the format
            // string while instr still points to the header and argument descriptors.
            case ECL_DEBUG_LOG: {
                instruction = (EclInstr*)(instruction->s + 4);
                char* buffer = (char*)malloc(0x400);
                buffer[0] = 0;
                int argument_index = 0;
                while ((char*)instruction != 0) {
                    char* percent = strchr((char*)instruction, '%');
                    if (percent == 0) break;
                    strcpy(buffer, (char*)instruction);
                    buffer[percent - (char*)instruction] = 0;
                    switch (percent[1]) {
                    case '%':
                        DebugLog(buffer);
                        break;
                    case 'd': {
                        ECL_LOG_ARGUMENT(int);
                        ++argument_index;
                        break;
                    }
                    case 'f': {
                        ECL_LOG_ARGUMENT(double);
                        ++argument_index;
                        break;
                    }
                    }
                    instruction = (EclInstr*)(percent + 2);
                }
                free(buffer);
                break;
            }
            default:
                // The owner handles game-specific opcodes. A wait leaves the PC
                // and VM time unchanged here so the same instruction can run again.
                if (owner->Execute() == -1) return 0;
                break;
            }
        }
        pc = &instr;
        *pc = (EclInstr*)((char*)instr + instr->size);
    }
    time += delta;
    return 0;
}

#undef ECL_POP_PAIR

#undef ECL_LOG_ARGUMENT
