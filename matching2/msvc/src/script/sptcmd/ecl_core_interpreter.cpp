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

int EclVm::Run(float delta) {
    if (instr == 0) return -1;
    EclInstr** pc = &instr;
    while ((float)instr->time <= time) {
        EclInstr* instruction = *pc;
        if (instruction->rank & rank) {
            switch (instruction->id) {
            // VM termination and return. A saved PC is the call instruction; the
            // normal advance below steps past it after restoring the caller's time.
            case 0:
                break;
            case 1:
                *pc = 0;
                return -1;
            case 10:
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
            case 15:
                owner->SpawnChild(-1, 0);
                break;
            case 21:
                owner->ResetVariableBindings();
                break;
            case 16:
                owner->SpawnChild(
                    IntValue(1, instruction->i[(unsigned int)(instruction->i[0] + 4) / 4]), 1);
                break;
            case 17: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) node->vm->instr = 0;
                break;
            }
            case 18: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) node->vm->flags |= 1;
                break;
            }
            case 19: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) node->vm->flags &= ~1;
                break;
            }
            case 20: {
                EclNode* node = owner->FindVariable(IntOperand(0));
                if (node) {
                    EclVm* child = node->vm;
                    child->f1018 = IntOperand(1);
                }
                break;
            }

            // Calls and relative branches replace the PC. Continue dispatch at the
            // new instruction without applying the normal instruction-size advance.
            case 11:
                if (Start(this, 0)) return -1;
                continue;
            case 14: {
                int condition;
                PopInt(&condition);
                if (condition) goto relative_jump;
                break;
            }
            case 13: {
                int condition;
                PopInt(&condition);
                if (condition) break;
            }
            // A zero condition falls through to the unconditional jump.
            case 12:
            relative_jump:
                {
                    EclInstr* branch = *pc;
                    time = (float)branch->i[1];
                    *pc = (EclInstr*)((char*)branch + branch->i[0]);
                }
                continue;
            case 83:
                time -= (float)IntOperand(0);
                break;

            // Stack frames, then typed transfers between operands and the stack.
            case 40:
                stack.Push(IntOperand(0));
                break;
            case 41:
                stack.Pop();
                break;
            case 42: {
                int value = IntOperand(0);
                stack.Write('i', 4, &value);
                break;
            }
            case 43: {
                int* destination = IntDest(0);
                PopInt(destination);
                break;
            }
            case 44: {
                float value = FloatOperand(0);
                stack.Write('f', 4, &value);
                break;
            }
            case 45: {
                float* destination = FloatDest(0);
                PopFloat(destination);
                break;
            }

            // Integer arithmetic reuses the left operand storage for the result:
            // the integer and float operations both push from that same word.
            case 50: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage + right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 52: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage - right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 54: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage * right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 56: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage / right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 58: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                left_storage = left_storage % right_storage;
                stack.Write('i', 4, &left_storage);
                break;
            }

            // Floating-point arithmetic uses the same pop order and a float result tag.
            case 51: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage + right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 53: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage - right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 55: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage * right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 57: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                left_storage = left_storage / right_storage;
                stack.Write('f', 4, &left_storage);
                break;
            }

            // Integer comparisons and logical NOT produce an integer result.
            case 59: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand == right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case 61: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand != right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case 63: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand < right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case 65: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand <= right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case 67: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand > right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case 69: {
                ECL_POP_PAIR(int, PopInt, left_storage, right_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int result = left_operand >= right_operand;
                stack.Write('i', 4, &result);
                break;
            }
            case 71: {
                int value;
                PopInt(&value);
                int result = value == 0;
                stack.Write('i', 4, &result);
                break;
            }

            // Floating-point comparisons also push an integer, not a float.
            case 60: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand == right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 62: {
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
            case 64: {
                ECL_POP_PAIR(float, stack.PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand < right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 66: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand <= right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 68: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand > right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 70: {
                ECL_POP_PAIR(float, PopFloat, left_storage, right_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int result = (left_operand >= right_operand) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 72: {
                float value;
                PopFloat(&value);
                int result = (value == 0.0f) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }

            // Logical and bitwise operations on integer stack words.
            case 73: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = (left || right) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 74: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = (left && right) ? 1 : 0;
                stack.Write('i', 4, &result);
                break;
            }
            case 75: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = left ^ right;
                stack.Write('i', 4, &result);
                break;
            }
            case 76: {
                ECL_POP_PAIR(int, stack.PopInt, left, right);
                int result = left | right;
                stack.Write('i', sizeof(int), &result);
                break;
            }
            case 77: {
                ECL_POP_PAIR(int, PopInt, left, right);
                int result = left & right;
                stack.Write('i', 4, &result);
                break;
            }

            // Negation and post-decrement.
            case 84: {
                int value;
                PopInt(&value);
                value = -value;
                stack.Write('i', 4, &value);
                break;
            }
            case 85: {
                // Negate the integer word, then write it back with the float tag.
                int word;
                PopFloat((float*)&word);
                word = -word;
                stack.Write('f', 4, &word);
                break;
            }
            case 78: {
                int original_value = IntOperand(0);
                int* destination = IntDest(0);
                *destination = original_value - 1;
                stack.Write('i', 4, &original_value);
                break;
            }

            // Trigonometry and vector operations.
            case 79: {
                float angle;
                PopFloat(&angle);
                float result = (float)sin(angle);
                stack.Write('f', 4, &result);
                break;
            }
            case 80: {
                float angle;
                PopFloat(&angle);
                float result = (float)cos(angle);
                stack.Write('f', 4, &result);
                break;
            }
            case 81: {
                EclPolar vector;
                vector.SetPolar(Angle_Normalize(FloatOperand(2)), FloatOperand(3));
                *FloatDest(0) = vector.x;
                *FloatDest(1) = vector.y;
                break;
            }
            case 86: {
                float x = FloatOperand(1);
                float y = FloatOperand(2);
                *FloatDest(0) = y * y + x * x;
                break;
            }
            case 82: {
                float* destination = FloatDest(0);
                *destination = Angle_Normalize(FloatOperand(0));
                break;
            }
            case 87: {
                float x = FloatOperand(2) - FloatOperand(0);
                float y = FloatOperand(3) - FloatOperand(1);
                y = (float)atan2(y, x);
                *FloatDest(0) = y;
                break;
            }

            // Packed debug format and typed arguments. The cursor scans the format
            // string while instr still points to the header and argument descriptors.
            case 30: {
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
