#include "th10/script/ecl.hpp"

#include <cassert>
#include <cstring>

uint8_t PTR_caseD_14f_00411de0[0x200] = {};
float DAT_00470b04 = 0.0f;
float DAT_00470b60 = -1.0f;
void* g_pGameStateManager = 0;
int32_t DAT_00474c98 = 0;
int32_t DAT_00474c74 = 0;

extern "C" uint32_t ECL_DispatchOpcode(uint32_t, void*, int) { return 0; }
extern "C" void AnimationManager_SetEclFlag(void) {}
extern "C" void AnimationManager_ClearEclFlag(void) {}
static int g_difficulty_action = -1;
static int g_string_index;
static char g_string_text[256];
static unsigned int g_string_length;
extern "C" void ECL_SetTimerTarget(int value) { g_difficulty_action = value; }

static void CaptureEncryptedString(int index, const char* text,
                                   unsigned int length) {
    g_string_index = index;
    g_string_length = length;
    std::memcpy(g_string_text, text, length);
    g_string_text[length] = '\0';
}

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
    ECL_DecodeEncryptedString(
        encrypted, encrypted, (unsigned int)(sizeof(plaintext) - 1));
    assert(std::strcmp(encrypted, plaintext) == 0);
    ECL_DecodeEncryptedString(decoded, encrypted, 0);
    assert(decoded[0] == plaintext[0]);

    char encoded_again[sizeof(plaintext)] = {};
    key = 0x77;
    step = 7;
    for (unsigned int index = 0; index != sizeof(plaintext) - 1; ++index) {
        encoded_again[index] = (char)((unsigned char)plaintext[index] ^ key);
        key = (key + step) & 0xFF;
        step = (step + 0x10) & 0xFF;
    }
    g_string_index = -1;
    ECL_ExecuteEncryptedStringOpcode(0x165, 20, 3, encoded_again,
                                      (unsigned int)(sizeof(plaintext) - 1),
                                      CaptureEncryptedString);
    assert(g_string_index == 23);
    assert(g_string_length == sizeof(plaintext) - 1);
    assert(std::strcmp(g_string_text, plaintext) == 0);
}

void TestScratchStackHelpers() {
    uint8_t vm[0x1100] = {};
    *(int32_t*)(vm + 0x1000) = 0;
    *(int32_t*)(vm + 0x1004) = 0;
    assert(ECL_PushScratchValue(vm, 8) == 0);
    assert(*(int32_t*)(vm + 0x1000) == 12);
    assert(*(int32_t*)(vm + 0x1004) == 0);
    assert(ECL_PopScratchValue(vm) == 0);
    assert(*(int32_t*)(vm + 0x1000) == 0);
}

void TestScratchWriterAndPolarVector() {
    uint8_t vm[0x1100] = {};
    int32_t value = 0x12345678;
    assert(ECL_WriteScratch(vm, 'i', sizeof(value), &value) == 0);
    assert(*(char*)vm == 'i');
    assert(*(int32_t*)(vm + 4) == value);
    float vector[2] = {};
    ECL_SetPolarVector(vector, 0.0f, 3.0f);
    assert(vector[0] == 3.0f && vector[1] == 0.0f);
}

void TestScriptLabelLookup() {
    struct Entry { const unsigned short* name; void* value; };
    static const unsigned short alpha[] = {'a','l','p','h','a',0};
    static const unsigned short beta[] = {'b','e','t','a',0};
    uint8_t vm[0x100] = {};
    uint8_t record_a[0x20] = {};
    Entry entries[2] = {{alpha, record_a}, {beta, record_a}};
    *(int32_t*)(vm + 8) = 2;
    *(Entry**)(vm + 0x8c) = entries;
    static const unsigned short query[] = {'b','e','t','a',0};
    assert(ECL_FindScriptLabel(vm, query) == record_a + 0x10);
    static const unsigned short missing[] = {'z',0};
    assert(ECL_FindScriptLabel(vm, missing) == 0);
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
    assert(ECL_VM_Dispatch(0) == 0);
    uint8_t entity[0x1600] = {};
    assert(ECL_VM_Dispatch(entity) == 0);
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
    fixture.instruction.instruction.opcode = 0x158;
    fixture.Operands()[0] = 9;
    *(int32_t*)((uint8_t*)entity + 0x44) = 3;
    *(uint32_t*)((uint8_t*)entity + 0x4c) = 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)((uint8_t*)entity + 0x44) == 9);
    assert(*(uint32_t*)((uint8_t*)entity + 0x4c) == 0);
    fixture.instruction.instruction.opcode = 0x14e;
    fixture.Operands()[0] = 2;
    fixture.Operands()[1] = 17;
    fixture.Operands()[2] = 0x12345678u;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)((uint8_t*)entity + 0x2494 + 2 * 0x10) == 17);
    assert(*(uint32_t*)((uint8_t*)entity + 0x2498 + 2 * 0x10) == 0x12345678u);
    fixture.instruction.instruction.opcode = 0x14c;
    fixture.Operands()[0] = 3;
    void* vm_marker = state;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)((uint8_t*)entity + 0x1444) & 0x8000u) != 0);
    assert(*(int32_t*)((uint8_t*)entity + 0x1450) == 3);
    assert(*(uint32_t*)((uint8_t*)manager + 0x10 + 3 * 4) ==
           static_cast<uint32_t>(reinterpret_cast<unsigned long long>(vm_marker)));
    fixture.Operands()[0] = (uint32_t)-1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)((uint8_t*)entity + 0x1444) & 0x8000u) == 0);
    fixture.instruction.instruction.opcode = 0x128;
    fixture.Operands()[0] = FloatBits(1.5f);
    fixture.Operands()[1] = FloatBits(-2.0f);
    fixture.Operands()[2] = FloatBits(3.25f);
    *(float*)(entity + 0x58) = 10.0f;
    *(float*)(entity + 0x5c) = 20.0f;
    *(float*)(entity + 0x60) = 30.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x58) == 11.5f);
    assert(*(float*)(entity + 0x5c) == 18.0f);
    assert(*(float*)(entity + 0x60) == 33.25f);
    fixture.instruction.instruction.opcode = 0x129;
    fixture.Operands()[0] = FloatBits(-1.0f);
    fixture.Operands()[1] = FloatBits(2.0f);
    fixture.Operands()[2] = FloatBits(-3.0f);
    *(float*)(entity + 0x84) = 4.0f;
    *(float*)(entity + 0x88) = 5.0f;
    *(float*)(entity + 0x8c) = 6.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x84) == 3.0f);
    assert(*(float*)(entity + 0x88) == 7.0f);
    assert(*(float*)(entity + 0x8c) == 3.0f);
    fixture.instruction.instruction.opcode = 0x127;
    uint8_t manager_state[0x1080] = {};
    *(void**)(manager + 0x10) = manager_state;
    *(float*)(manager_state + 0x1068) = 7.0f;
    *(float*)(manager_state + 0x106c) = -8.0f;
    *(float*)(manager_state + 0x1070) = 9.5f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x84) == 7.0f);
    assert(*(float*)(entity + 0x88) == -8.0f);
    assert(*(float*)(entity + 0x8c) == 9.5f);
    fixture.instruction.instruction.opcode = 0x126;
    *(float*)(manager_state + 0x1068) = -10.0f;
    *(float*)(manager_state + 0x106c) = 11.0f;
    *(float*)(manager_state + 0x1070) = -12.5f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x58) == -10.0f);
    assert(*(float*)(entity + 0x5c) == 11.0f);
    assert(*(float*)(entity + 0x60) == -12.5f);
    fixture.instruction.instruction.opcode = 0x12a;
    fixture.Operands()[0] = FloatBits(2.25f);
    fixture.Operands()[1] = FloatBits(-4.5f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x64) == 2.25f);
    assert(*(float*)(entity + 0x68) == -4.5f);
    fixture.instruction.instruction.opcode = 0x12b;
    fixture.Operands()[0] = FloatBits(-6.0f);
    fixture.Operands()[1] = FloatBits(8.0f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x90) == -6.0f);
    assert(*(float*)(entity + 0x94) == 8.0f);
    fixture.instruction.instruction.opcode = 0x120;
    fixture.Operands()[0] = FloatBits(1.0f);
    fixture.Operands()[1] = FloatBits(2.0f);
    fixture.Operands()[2] = FloatBits(3.0f);
    fixture.Operands()[3] = FloatBits(4.0f);
    *(uint32_t*)(entity + 0x80) = 0;
    *(float*)(entity + 0x58) = 20.0f;
    *(float*)(entity + 0x5c) = 21.0f;
    *(float*)(entity + 0x60) = 22.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x64) == 20.0f);
    assert(*(float*)(entity + 0x68) == 21.0f);
    assert(*(float*)(entity + 0x6c) == 22.0f);
    assert(*(float*)(entity + 0x70) == 2.0f);
    assert(*(float*)(entity + 0x78) == 3.0f);
    assert(*(float*)(entity + 0x7c) == 4.0f);
    fixture.instruction.instruction.opcode = 0x122;
    fixture.Operands()[0] = FloatBits(0.0f);
    fixture.Operands()[1] = FloatBits(0.0f);
    fixture.Operands()[2] = FloatBits(5.0f);
    fixture.Operands()[3] = FloatBits(0.0f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0xa4) == 5.0f);
    g_pGameStateManager = 0;
}

} // namespace

int main() {
    TestDirectAndLocalOperands();
    TestEncryptedStringTransform();
    TestScratchStackHelpers();
    TestScratchWriterAndPolarVector();
    TestScriptLabelLookup();
    TestExternalVariables();
    TestDecodedValueResolvers();
    TestTypedStackPops();
    TestRecoveredLeafDispatcher();
    return 0;
}
