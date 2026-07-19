#include "th10/script/entity_vm.hpp"

#include <cassert>
#include <cstring>

namespace {

struct ServiceLog {
    int timer;
    int resource;
    int event;
};

void ResetTimer(void* context, int value) {
    static_cast<ServiceLog*>(context)->timer = value;
}
void TransitionResource(void* context, int value) {
    static_cast<ServiceLog*>(context)->resource = value;
}
void EmitEvent(void* context, int event, int value) {
    static_cast<ServiceLog*>(context)->event = event * 1000 + value;
}

struct TestResolver : EntityScriptResolver {
    int integers[4];
    float floats[4];
    bool saw_indirect_operand;
    bool saw_indirect_destination;

    TestResolver() : saw_indirect_operand(false),
                     saw_indirect_destination(false) {
        std::memset(integers, 0, sizeof(integers));
        std::memset(floats, 0, sizeof(floats));
    }
    virtual int ResolveInteger(unsigned int encoded, bool indirect) {
        saw_indirect_operand = indirect;
        return indirect ? integers[encoded & 3] : (int)encoded;
    }
    virtual float ResolveFloat(unsigned int encoded, bool indirect) {
        saw_indirect_operand = indirect;
        if (indirect) return floats[encoded & 3];
        float value;
        std::memcpy(&value, &encoded, sizeof(value));
        return value;
    }
    virtual int* ResolveIntegerDestination(short encoded, bool indirect) {
        saw_indirect_destination = indirect;
        return &integers[(unsigned short)encoded & 3];
    }
    virtual float* ResolveFloatDestination(short encoded, bool indirect) {
        saw_indirect_destination = indirect;
        return &floats[(unsigned short)encoded & 3];
    }
};

unsigned int FloatBits(float value) {
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}

} // namespace

int main() {
    int integer = 3;
    assert(EntityScript_ApplyIntegerArithmetic(6, &integer, 10) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 10);
    assert(EntityScript_ApplyIntegerArithmetic(8, &integer, 4) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 14);
    assert(EntityScript_ApplyIntegerArithmetic(10, &integer, 2) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 12);
    assert(EntityScript_ApplyIntegerArithmetic(12, &integer, 3) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 36);
    assert(EntityScript_ApplyIntegerArithmetic(14, &integer, 4) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 9);
    assert(EntityScript_ApplyIntegerArithmetic(16, &integer, 4) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 1);
    assert(EntityScript_ApplyIntegerArithmetic(14, &integer, 0) ==
           ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO && integer == 1);

    float floating = 2.0f;
    assert(EntityScript_ApplyFloatArithmetic(7, &floating, 5.0f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 5.0f);
    assert(EntityScript_ApplyFloatArithmetic(9, &floating, 1.5f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 6.5f);
    assert(EntityScript_ApplyFloatArithmetic(11, &floating, 0.5f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 6.0f);
    assert(EntityScript_ApplyFloatArithmetic(13, &floating, 2.0f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 12.0f);
    assert(EntityScript_ApplyFloatArithmetic(15, &floating, 3.0f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 4.0f);
    assert(EntityScript_ApplyFloatArithmetic(15, &floating, 0.0f) ==
           ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO && floating == 4.0f);
    assert(EntityScript_ApplyFloatArithmetic(99, &floating, 1.0f) ==
           ENTITY_SCRIPT_STEP_UNSUPPORTED);
    assert(EntityScript_ApplyBinaryInteger(0x12, &integer, 7, 5) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 12);
    assert(EntityScript_ApplyBinaryInteger(0x14, &integer, 7, 5) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 2);
    assert(EntityScript_ApplyBinaryInteger(0x16, &integer, 7, 5) ==
           ENTITY_SCRIPT_STEP_APPLIED && integer == 35);
    assert(EntityScript_ApplyBinaryFloat(0x13, &floating, 7.0f, 5.0f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 12.0f);
    assert(EntityScript_ApplyBinaryFloat(0x15, &floating, 7.0f, 5.0f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 2.0f);
    assert(EntityScript_ApplyBinaryFloat(0x17, &floating, 7.0f, 5.0f) ==
           ENTITY_SCRIPT_STEP_APPLIED && floating == 35.0f);

    EntityScriptInstruction stream[2] = {};
    stream[0].opcode = ENTITY_SCRIPT_SET_INT;
    stream[0].size = sizeof(EntityScriptInstruction);
    stream[0].destination = 1;
    stream[0].flags = ENTITY_SCRIPT_OPERAND_INDIRECT |
                      ENTITY_SCRIPT_DESTINATION_INDIRECT;
    stream[0].operand = 2;
    stream[1].opcode = ENTITY_SCRIPT_ADD_FLOAT;
    stream[1].size = sizeof(EntityScriptInstruction);
    stream[1].destination = 3;
    stream[1].operand = FloatBits(1.25f);
    TestResolver resolver;
    resolver.integers[2] = 44;
    resolver.floats[3] = 2.0f;
    EntityScriptCursor cursor = {
        reinterpret_cast<const unsigned char*>(stream), sizeof(stream), 0,
        false, {}, 0, 0
    };
    assert(EntityScript_ExecuteOne(&cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(resolver.integers[1] == 44);
    assert(resolver.saw_indirect_operand && resolver.saw_indirect_destination);
    assert(cursor.offset == sizeof(EntityScriptInstruction));
    assert(EntityScript_ExecuteOne(&cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(resolver.floats[3] == 3.25f);
    assert(cursor.offset == sizeof(stream));
    assert(EntityScript_ExecuteOne(&cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_FINISHED);

    stream[0].size = 1;
    cursor.offset = 0;
    assert(EntityScript_ExecuteOne(&cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_MALFORMED);
    stream[0].size = sizeof(EntityScriptInstruction);
    stream[0].opcode = ENTITY_SCRIPT_END;
    cursor.offset = 0;
    cursor.halted = false;
    assert(EntityScript_ExecuteOne(&cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_FINISHED);
    assert(cursor.halted && cursor.offset == sizeof(EntityScriptInstruction));
    assert(EntityScript_JumpRelative(&cursor, -1) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(cursor.offset == sizeof(EntityScriptInstruction) - 1);
    assert(EntityScript_JumpRelative(&cursor, -100) ==
           ENTITY_SCRIPT_STEP_MALFORMED);

    ServiceLog log = {-1, -1, -1};
    EntityScriptServices services = {
        ResetTimer, TransitionResource, EmitEvent, &log
    };
    assert(EntityScript_InvokeService(&services, 0, 12) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.timer == 12);
    assert(EntityScript_InvokeService(&services, 1, 34) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.resource == 34);
    assert(EntityScript_InvokeService(&services, 2, 56) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.event == 2056);
    assert(EntityScript_InvokeService(&services, 3, 1) ==
           ENTITY_SCRIPT_STEP_UNSUPPORTED);
    assert(EntityScript_ExecuteServiceOpcode(&services, 0x14d, 99) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.timer == 0);
    assert(EntityScript_ExecuteServiceOpcode(&services, 0x14f, 77) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.timer == 77);
    assert(EntityScript_ExecuteServiceOpcode(&services, 0x150, 88) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.resource == 88);
    assert(EntityScript_ExecuteServiceOpcode(&services, 0x151, 99) ==
           ENTITY_SCRIPT_STEP_APPLIED && log.event == 2099);
    EntityScriptInstruction service_instruction = {};
    service_instruction.opcode = 0x14f;
    service_instruction.size = sizeof(EntityScriptInstruction);
    service_instruction.operand = 123;
    EntityScriptCursor service_cursor = {
        reinterpret_cast<const unsigned char*>(&service_instruction),
        sizeof(service_instruction), 0, false, {}, 0, &services
    };
    assert(EntityScript_ExecuteOne(&service_cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(log.timer == 123 && service_cursor.offset ==
           sizeof(EntityScriptInstruction));

    EntityScriptInstruction flow[3] = {};
    flow[0].opcode = ENTITY_SCRIPT_CALL;
    flow[0].size = sizeof(EntityScriptInstruction);
    flow[0].operand = sizeof(EntityScriptInstruction) * 2;
    flow[1].opcode = ENTITY_SCRIPT_END;
    flow[1].size = sizeof(EntityScriptInstruction);
    flow[2].opcode = ENTITY_SCRIPT_RETURN;
    flow[2].size = sizeof(EntityScriptInstruction);
    EntityScriptCursor call_cursor = {
        reinterpret_cast<const unsigned char*>(flow), sizeof(flow), 0,
        false, {}, 0, 0
    };
    assert(EntityScript_ExecuteOne(&call_cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(call_cursor.offset == sizeof(EntityScriptInstruction) * 2);
    assert(call_cursor.call_depth == 1);
    assert(EntityScript_ExecuteOne(&call_cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(call_cursor.offset == sizeof(EntityScriptInstruction));
    assert(call_cursor.call_depth == 0);
    assert(EntityScript_ExecuteOne(&call_cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_FINISHED);
    assert(call_cursor.halted);
    EntityScriptInstruction branch[3] = {};
    branch[0].opcode = ENTITY_SCRIPT_BRANCH_NONZERO;
    branch[0].size = sizeof(EntityScriptInstruction);
    branch[0].destination = 1;
    branch[0].flags = ENTITY_SCRIPT_DESTINATION_INDIRECT;
    branch[0].operand = sizeof(EntityScriptInstruction) * 2;
    branch[1].opcode = ENTITY_SCRIPT_END;
    branch[1].size = sizeof(EntityScriptInstruction);
    branch[2].opcode = ENTITY_SCRIPT_END;
    branch[2].size = sizeof(EntityScriptInstruction);
    EntityScriptCursor branch_cursor = {
        reinterpret_cast<const unsigned char*>(branch), sizeof(branch), 0,
        false, {}, 0, &services
    };
    resolver.integers[1] = 0;
    assert(EntityScript_ExecuteOne(&branch_cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(branch_cursor.offset == sizeof(EntityScriptInstruction));
    branch_cursor.offset = 0;
    resolver.integers[1] = 1;
    assert(EntityScript_ExecuteOne(&branch_cursor, &resolver) ==
           ENTITY_SCRIPT_STEP_APPLIED);
    assert(branch_cursor.offset == sizeof(EntityScriptInstruction) * 2);
    return 0;
}
