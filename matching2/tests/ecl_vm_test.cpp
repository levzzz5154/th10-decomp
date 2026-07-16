#include "th10/script/ecl.hpp"

#include <cassert>
#include <cstring>

uint8_t PTR_caseD_14f_00411de0[0x200] = {};
float DAT_00470b04 = 0.0f;
float DAT_00470b60 = -1.0f;
void* g_pGameStateManager = 0;
int32_t DAT_00474c98 = 0;
int32_t DAT_00474c74 = 0;

extern "C" uint32_t FUN_0044fdb0(uint32_t, void*, int) { return 0; }
extern "C" void FUN_00449590(void) {}
extern "C" void FUN_004495e0(void) {}
static int g_difficulty_action = -1;
extern "C" void FUN_00405410(int value) { g_difficulty_action = value; }

namespace {

struct Resolver : ECLVariableResolver {
    int32_t last_int;
    int32_t last_float;
    float external_value;
    int32_t external_int;

    Resolver() : last_int(0), last_float(0), external_value(0), external_int(0) {}
    virtual void Unknown0() {}
    virtual int32_t ResolveInt(int32_t variable) {
        last_int = variable;
        return 700 + variable;
    }
    virtual int32_t* ResolveIntPointer(int32_t) { return &external_int; }
    virtual void Unknown2() {}
    virtual float ResolveFloat(int32_t variable) {
        last_float = variable;
        return 20.5f + (float)variable;
    }
    virtual float* ResolveFloatPointer(int32_t) { return &external_value; }
};

struct InstructionStorage {
    ECLInstruction instruction;
    uint32_t extra_operands[3];
};

struct CursorFixture {
    uint8_t bytes[0x1040];
    InstructionStorage instruction;
    Resolver resolver;

    CursorFixture() {
        std::memset(bytes, 0, sizeof(bytes));
        std::memset(&instruction, 0, sizeof(instruction));
        *(ECLInstruction**)(bytes + 8) = &instruction.instruction;
        *(int32_t*)(bytes + 0x100C) = 0x20;
        *(ECLVariableResolver**)(bytes + 0x1014) = &resolver;
    }

    uint32_t* Operands() { return instruction.instruction.operands; }
};

uint32_t FloatBits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}

void Push(CursorFixture& fixture, char type, uint32_t value) {
    fixture.bytes[16] = (uint8_t)type;
    *(uint32_t*)(fixture.bytes + 20) = value;
    *(int32_t*)(fixture.bytes + 0x1008) = 8;
}

void TestDirectAndLocalOperands() {
    CursorFixture fixture;
    fixture.Operands()[0] = (uint32_t)-23;
    fixture.Operands()[1] = FloatBits(3.25f);
    assert(ECL_ResolveIntOperand(fixture.bytes, 0) == -23);
    assert(ECL_ResolveFloatOperand(fixture.bytes, 1) == 3.25f);

    fixture.instruction.instruction.param_mask = 3;
    fixture.Operands()[0] = 4;
    fixture.Operands()[1] = FloatBits(8.0f);
    *(int32_t*)(fixture.bytes + 0x20 + 8 + 4) = 91;
    *(float*)(fixture.bytes + 0x20 + 8 + 8) = -6.5f;
    assert(ECL_ResolveIntOperand(fixture.bytes, 0) == 91);
    assert(ECL_ResolveFloatOperand(fixture.bytes, 1) == -6.5f);
}

void TestEncryptedStringTransform() {
    static const char plaintext[] = "ECL text";
    char encrypted[sizeof(plaintext)] = {};
    char decoded[sizeof(plaintext)] = {};
    unsigned int key = 0x77;
    unsigned int step = 7;
    for (unsigned int index = 0; index != sizeof(plaintext) - 1; ++index) {
        encrypted[index] = (char)((unsigned char)plaintext[index] ^ key);
        key = (key + step) & 0xFF;
        step = (step + 0x10) & 0xFF;
    }
    ECL_DecodeEncryptedString(
        decoded, encrypted, (unsigned int)(sizeof(plaintext) - 1));
    assert(std::strcmp(decoded, plaintext) == 0);
    ECL_DecodeEncryptedString(decoded, encrypted, 0);
    assert(decoded[0] == plaintext[0]);
}

void TestExternalVariables() {
    CursorFixture fixture;
    fixture.instruction.instruction.param_mask = 3;
    fixture.Operands()[0] = (uint32_t)-7;
    fixture.Operands()[1] = FloatBits(-3.0f);
    assert(ECL_ResolveIntOperand(fixture.bytes, 0) == 693);
    assert(fixture.resolver.last_int == -7);
    assert(ECL_ResolveFloatOperand(fixture.bytes, 1) == 17.5f);
    assert(fixture.resolver.last_float == -3);
}

void TestDecodedValueResolvers() {
    CursorFixture fixture;
    fixture.Operands()[0] = 999;
    assert(ECL_ResolveIntValue(fixture.bytes, 0, 41) == 41);
    assert(ECL_ResolveFloatValue(fixture.bytes, 0, 2.5f) == 2.5f);

    fixture.instruction.instruction.param_mask = 1;
    *(int32_t*)(fixture.bytes + 0x20 + 8 + 4) = 123;
    *(float*)(fixture.bytes + 0x20 + 8 + 8) = 9.75f;
    assert(ECL_ResolveIntValue(fixture.bytes, 0, 4) == 123);
    assert(ECL_ResolveFloatValue(fixture.bytes, 0, 8.0f) == 9.75f);
    assert(ECL_ResolveIntValue(fixture.bytes, 0, -9) == 691);
    assert(ECL_ResolveFloatValue(fixture.bytes, 0, -2.0f) == 18.5f);
}

void TestTypedStackPops() {
    CursorFixture fixture;
    fixture.instruction.instruction.param_mask = 1;
    fixture.Operands()[0] = (uint32_t)-1;

    Push(fixture, 'f', FloatBits(12.75f));
    assert(ECL_ResolveIntOperand(fixture.bytes, 0) == 12);
    assert(*(int32_t*)(fixture.bytes + 0x1008) == 0);

    fixture.Operands()[0] = FloatBits(-1.0f);
    Push(fixture, 'i', 37);
    assert(ECL_ResolveFloatOperand(fixture.bytes, 0) == 37.0f);
    assert(*(int32_t*)(fixture.bytes + 0x1008) == 0);

    fixture.Operands()[0] = (uint32_t)-1;
    *(int32_t*)(fixture.bytes + 0x1008) = 0;
    assert(ECL_ResolveIntOperand(fixture.bytes, 0) == -1);
    fixture.Operands()[0] = FloatBits(-1.0f);
    assert(ECL_ResolveFloatOperand(fixture.bytes, 0) == -1.0f);
}

void TestRecoveredLeafDispatcher() {
    uint8_t entity[0x1600] = {};
    uint8_t state_bytes[0x20] = {};
    ECLVMState* state = (ECLVMState*)state_bytes;
    CursorFixture fixture;
    state->cursor = (ECLInstructionCursor*)fixture.bytes;
    *(ECLVMState**)(entity + 0x14D8) = state;

    fixture.instruction.instruction.opcode = ECL_SET_HITBOX_WIDTH;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = FloatBits(4.5f);
    fixture.Operands()[1] = FloatBits(7.25f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0xB0) == 4.5f);
    assert(*(float*)(entity + 0xB4) == 7.25f);

    fixture.instruction.instruction.opcode = ECL_SET_MOVEMENT_BOUNDARY;
    fixture.Operands()[0] = FloatBits(-1.0f);
    fixture.Operands()[1] = FloatBits(2.0f);
    fixture.Operands()[2] = FloatBits(3.0f);
    fixture.Operands()[3] = FloatBits(4.0f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x200u) != 0);
    assert(*(float*)(entity + 0x13AC) == -1.0f);
    assert(*(float*)(entity + 0x13B8) == 4.0f);

    fixture.instruction.instruction.opcode = ECL_CLEAR_MOVEMENT_BOUNDARY;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x200u) == 0);

    fixture.instruction.instruction.opcode = ECL_RESET_DIFFICULTY_SLOTS;
    for (int index = 0; index != 12; ++index)
        *(int32_t*)(entity + 0x13D0 + index * 4) = index + 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    for (int index = 0; index != 12; ++index)
        assert(*(int32_t*)(entity + 0x13D0 + index * 4) == 0);

    fixture.instruction.instruction.opcode = ECL_SET_CURRENT_DIFFICULTY;
    fixture.Operands()[0] = 4;
    *(uint32_t*)(entity + 0x1444) = 0x8000u;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)(entity + 0x13CC) == 11);

    uint8_t manager[0x9F00] = {};
    g_pGameStateManager = manager;
    for (unsigned int offset = 0x9E94; offset <= 0x9EB0; offset += 4)
        *(int32_t*)(manager + offset) = 99;
    fixture.instruction.instruction.opcode = ECL_RESET_DIFFICULTY_STATE;
    fixture.Operands()[0] = 6;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)(entity + 0x13C0) == 6);
    assert(*(int32_t*)(entity + 0x13C4) == 6);
    assert(*(int32_t*)(entity + 0x13C8) == 6);
    for (unsigned int offset = 0x9E94; offset <= 0x9EB0; offset += 4)
        assert(*(int32_t*)(manager + offset) == 0);

    fixture.instruction.instruction.opcode = ECL_SET_DIFFICULTY_SQUARED;
    fixture.Operands()[0] = FloatBits(-3.5f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x1454) == 12.25f);

    fixture.instruction.instruction.opcode = ECL_SET_DIFFICULTY_PARAMETER;
    fixture.Operands()[0] = 2;
    fixture.Operands()[1] = FloatBits(4.5f);
    fixture.Operands()[2] = 77;
    *(int32_t*)(entity + 0x13C4) = 3;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)(manager + 0x9E98 + 2 * 8) == 77);
    assert(*(float*)(manager + 0x9E94 + 2 * 8) == 1.5f);

    fixture.instruction.instruction.param_mask = 1;
    fixture.Operands()[0] = FloatBits(256.0f);
    fixture.Operands()[1] = FloatBits(10.0f);
    fixture.Operands()[2] = FloatBits(20.0f);
    float* destination = (float*)(fixture.bytes + 0x20 + 8 + 0x100);
    *destination = 10.0f;
    fixture.instruction.instruction.opcode = 0x15D;
    DAT_00474c98 = -512;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 10.0f);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 10.0f);
    DAT_00474c98 = 512;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 20.0f);

    fixture.instruction.instruction.opcode = 0x15E;
    fixture.Operands()[3] = FloatBits(40.0f);
    fixture.Operands()[4] = FloatBits(50.0f);
    DAT_00474c98 = -500;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 20.0f);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 20.0f);
    DAT_00474c98 = 300;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 40.0f);
    DAT_00474c98 = 700;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 50.0f);

    fixture.instruction.instruction.opcode = 0x15F;
    fixture.Operands()[1] = FloatBits(10.0f);
    fixture.Operands()[2] = FloatBits(30.0f);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 20.0f);

    int32_t* int_destination =
        (int32_t*)(fixture.bytes + 0x20 + 8 + 0x104);
    fixture.Operands()[0] = 0x104;
    fixture.Operands()[1] = 10;
    fixture.Operands()[2] = 30;
    fixture.Operands()[3] = 40;
    fixture.Operands()[4] = 50;
    fixture.Operands()[5] = 60;
    fixture.instruction.instruction.opcode = 0x160;
    DAT_00474c98 = 512;
    assert(ECL_VM_Dispatch(entity) == 0 && *int_destination == 30);
    fixture.instruction.instruction.opcode = 0x161;
    DAT_00474c98 = 700;
    assert(ECL_VM_Dispatch(entity) == 0 && *int_destination == 50);
    fixture.instruction.instruction.opcode = 0x162;
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0 && *int_destination == 20);
    fixture.instruction.instruction.opcode = 0x163;
    DAT_00474c74 = 2;
    assert(ECL_VM_Dispatch(entity) == 0 && *int_destination == 40);
    fixture.instruction.instruction.opcode = 0x164;
    DAT_00474c74 = 4;
    fixture.Operands()[0] = FloatBits(256.0f);
    fixture.Operands()[5] = FloatBits(60.0f);
    assert(ECL_VM_Dispatch(entity) == 0 && *destination == 60.0f);
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = 27;
    fixture.instruction.instruction.opcode = ECL_SET_GLOBAL_DIFFICULTY;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)(manager + 0x9E90) == 27);
    fixture.instruction.instruction.opcode = ECL_APPLY_DIFFICULTY_ACTION;
    g_difficulty_action = -1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(g_difficulty_action == 27);
    g_pGameStateManager = 0;
}

} // namespace

int main() {
    TestDirectAndLocalOperands();
    TestEncryptedStringTransform();
    TestExternalVariables();
    TestDecodedValueResolvers();
    TestTypedStackPops();
    TestRecoveredLeafDispatcher();
    return 0;
}
