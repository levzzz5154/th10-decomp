// Equivalent recovery of the core ECL interpreter at 0x0044E1A0. The default
// build compiles this into the executable once tools/matching/equivalence.py
// has checked that it differs from the exact bytes only as recorded in
// build_support/layout/equivalent/ecl_core_interpreter.json. The inline assembly in
// build_support/layout/units/ecl_core_interpreter_exact.cpp supplies those exact bytes and
// `make EXACT=1`.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"
#pragma intrinsic(sin, cos, atan2)


// Compiled out in retail; opcode 30 still formats its arguments for it.
static void DebugLog(const char* format, ...) {}

int EclVm::Run(float delta) {
    if (instr == 0) return -1;
    EclInstr** pc = &instr;
    while ((float)instr->time <= time) {
        EclInstr* ins = *pc;
        if (ins->rank & rank) {
            switch (ins->id) {
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
                { EclStack* s = &stack; s->PopRaw(pc); }
                PopRaw(&time);
                if (*pc == 0) return -1;
                break;
            case 15:
                owner->SpawnChild(-1, 0);
                break;
            case 21:
                owner->ResetVariableBindings();
                break;
            case 16:
                owner->SpawnChild(IntValue(1, ins->i[(unsigned int)(ins->i[0] + 4) / 4]), 1);
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
            case 11:
                if (Start(this, 0)) return -1;
                continue;
            case 14: {
                int a;
                PopInt(&a);
                if (a) goto jump;
                break;
            }
            case 13: {
                int a;
                PopInt(&a);
                if (a) break;
            }
            case 12:
            jump:
                {
                    EclInstr* target = *pc;
                    time = (float)target->i[1];
                    *pc = (EclInstr*)((char*)target + target->i[0]);
                }
                continue;
            case 83:
                time -= (float)IntOperand(0);
                break;
            case 40:
                stack.Push(IntOperand(0));
                break;
            case 41:
                stack.Pop();
                break;
            case 42: {
                int v = IntOperand(0);
                stack.Write('i', 4, &v);
                break;
            }
            case 43: {
                int* d = IntDest(0);
                PopInt(d);
                break;
            }
            case 44: {
                float v = FloatOperand(0);
                stack.Write('f', 4, &v);
                break;
            }
            case 45: {
                float* d = FloatDest(0);
                PopFloat(d);
                break;
            }
            case 50: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                left_storage = left_operand + right_operand;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 52: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                left_storage = left_operand - right_operand;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 54: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                left_storage = left_operand * right_operand;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 56: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                left_storage = left_operand / right_operand;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 58: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                left_storage = left_operand % right_operand;
                stack.Write('i', 4, &left_storage);
                break;
            }
            case 51: {
                float right_storage; PopFloat(&right_storage);
                float left_storage; PopFloat(&left_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                left_storage = left_operand + right_operand;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 53: {
                float right_storage; PopFloat(&right_storage);
                float left_storage; PopFloat(&left_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                left_storage = left_operand - right_operand;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 55: {
                float right_storage; PopFloat(&right_storage);
                float left_storage; PopFloat(&left_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                left_storage = left_operand * right_operand;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 57: {
                float right_storage; PopFloat(&right_storage);
                float left_storage; PopFloat(&left_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                left_storage = left_operand / right_operand;
                stack.Write('f', 4, &left_storage);
                break;
            }
            case 59: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int r = left_operand == right_operand;
                stack.Write('i', 4, &r);
                break;
            }
            case 61: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int r = left_operand != right_operand;
                stack.Write('i', 4, &r);
                break;
            }
            case 63: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int r = left_operand < right_operand;
                stack.Write('i', 4, &r);
                break;
            }
            case 65: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int r = left_operand <= right_operand;
                stack.Write('i', 4, &r);
                break;
            }
            case 67: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int r = left_operand > right_operand;
                stack.Write('i', 4, &r);
                break;
            }
            case 69: {
                int right_storage; PopInt(&right_storage);
                int left_storage; PopInt(&left_storage);
                const int left_operand = left_storage;
                const int right_operand = right_storage;
                int r = left_operand >= right_operand;
                stack.Write('i', 4, &r);
                break;
            }
            case 71: {
                int a; PopInt(&a);
                int r = a == 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 60: {
                float right_storage; PopFloat(&right_storage);
                float left_storage; PopFloat(&left_storage);
                const float left_operand = left_storage;
                const float right_operand = right_storage;
                int r = (left_operand == right_operand) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 62: {
                float a; PopFloat(&a);
                float b; PopFloat(&b);
                const float left_operand = b;
                const float right_operand = a;
                                int r = (left_operand != right_operand) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 64: {
                float a; PopFloat(&a);
                float b; PopFloat(&b);
                const float left_operand = b;
                const float right_operand = a;
                                int r = (left_operand < right_operand) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 66: {
                float a; PopFloat(&a);
                float b; PopFloat(&b);
                const float left_operand = b;
                const float right_operand = a;
                                int r = (left_operand <= right_operand) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 68: {
                float a; PopFloat(&a);
                float b; PopFloat(&b);
                const float left_operand = b;
                const float right_operand = a;
                                int r = (left_operand > right_operand) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 70: {
                float a; PopFloat(&a);
                float b; PopFloat(&b);
                const float left_operand = b;
                const float right_operand = a;
                                int r = (left_operand >= right_operand) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 72: {
                float a; PopFloat(&a);
                int r = (a == 0.0f) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 73: {
                int a; PopInt(&a);
                int b; PopInt(&b);
                int r = (b || a) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 74: {
                int a; PopInt(&a);
                int b; PopInt(&b);
                int r = (b && a) ? 1 : 0;
                stack.Write('i', 4, &r);
                break;
            }
            case 75: {
                int a; PopInt(&a);
                int b; PopInt(&b);
                int r = b ^ a;
                stack.Write('i', 4, &r);
                break;
            }
            case 76: {
                int a; PopInt(&a);
                int b; PopInt(&b);
                int r = b | a;
                stack.Write('i', 4, &r);
                break;
            }
            case 77: {
                int a; PopInt(&a);
                int b; PopInt(&b);
                int r = b & a;
                stack.Write('i', 4, &r);
                break;
            }
            case 84: {
                int a; PopInt(&a);
                a = -a;
                stack.Write('i', 4, &a);
                break;
            }
            case 85: {
                int a; PopFloat((float*)&a);
                a = -a;
                stack.Write('f', 4, &a);
                break;
            }
            case 78: {
                int v = IntOperand(0);
                int* d = IntDest(0);
                *d = v - 1;
                stack.Write('i', 4, &v);
                break;
            }
            case 79: {
                float a; PopFloat(&a);
                float r = (float)sin(a);
                stack.Write('f', 4, &r);
                break;
            }
            case 80: {
                float a; PopFloat(&a);
                float r = (float)cos(a);
                stack.Write('f', 4, &r);
                break;
            }
            case 81: {
                EclPolar v;
                v.SetPolar(Angle_Normalize(FloatOperand(2)), FloatOperand(3));
                *FloatDest(0) = v.x;
                *FloatDest(1) = v.y;
                break;
            }
            case 86: {
                float a = FloatOperand(1);
                float b = FloatOperand(2);
                *FloatDest(0) = b * b + a * a;
                break;
            }
            case 82: {
                float* d = FloatDest(0);
                *d = Angle_Normalize(FloatOperand(0));
                break;
            }
            case 87: {
                float x = FloatOperand(2) - FloatOperand(0);
                float y = FloatOperand(3) - FloatOperand(1);
                y = (float)atan2(y, x);
                *FloatDest(0) = y;
                break;
            }
            case 30: {
                ins = (EclInstr*)(ins->s + 4);
                char* buffer = (char*)malloc(0x400);
                buffer[0] = 0;
                int count = 0;
                while ((char*)ins != 0) {
                    char* percent = strchr((char*)ins, '%');
                    if (percent == 0) break;
                    strcpy(buffer, (char*)ins);
                    buffer[percent - (char*)ins] = 0;
                    switch (percent[1]) {
                    case '%':
                        DebugLog(buffer);
                        break;
                    case 'd':
                    case 'f': {
                        char type = instr->s[instr->i[0] + count * 8 + 4];
                        if (type == 'f' || type == 'g') {
                            DebugLog(buffer, EclVm::FloatValue(count + 1, this, ((float*)instr)[instr->i[0] / 4 + 6 + count * 2]));
                            count++;
                        } else {
                            DebugLog(buffer, IntValue(count + 1, ((int*)instr)[instr->i[0] / 4 + 6 + count * 2]));
                            count++;
                        }
                        break;
                    }
                    }
                    ins = (EclInstr*)(percent + 2);
                }
                free(buffer);
                break;
            }
            default:
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
