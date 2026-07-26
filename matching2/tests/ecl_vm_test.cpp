#include "th10/script/ecl.hpp"
#include "th10/math/timer.hpp"

#include <cassert>
#include <cstring>

// recovery_leaves.cpp publishes the large-state instance here. The PE32
// build aliases it from retail .data; the host test build supplies storage.
unsigned int DAT_00477830;

uint8_t PTR_caseD_14f_00411de0[0x200] = {};
float DAT_00470b04 = 0.0f;
float DAT_00470b60 = -1.0f;
void* g_pGameStateManager = 0;
int32_t DAT_00474c98 = 0;
int32_t DAT_00474c74 = 0;
uint32_t DAT_00476f78 = 0x3F800000u; // 1.0f as bits
float DAT_00470d58 = 0.0f;
float DAT_00470b94 = 3.1415927f;

extern "C" uint32_t ECL_DispatchOpcode(uint32_t, void*, int) { return 0; }
extern "C" void AnimationManager_SetEclFlag(void) {}
// ECL_SET_FLAGS / ECL_CLEAR_FLAGS reach the animation manager; the host test
// build has no render subsystem, so these record nothing.
void AnimationManager_SetFlag(void*, int, unsigned int) {}
void AnimationManager_ClearFlag(void*, int, unsigned int) {}
extern "C" void AnimationManager_ClearEclFlag(void) {}
static int g_string_index;
static char g_string_text[256];
static unsigned int g_string_length;
void Timer_Set(FrameTimer* timer, int target) {
    if ((timer->flags & 1u) == 0) {
        timer->previous = -1;
        timer->current = 0;
        timer->elapsed = 0.0f;
        timer->speed = reinterpret_cast<const float*>(&DAT_00476f78);
        timer->flags |= 1u;
    }
    timer->current = target;
    timer->previous = target - 1;
    timer->elapsed = static_cast<float>(target);
}

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
    // The dispatcher's largest entity field is the resource-slot table at
    // +0x2494 (16 bytes per slot), so the fixture must cover it: the old
    // 0x1600-byte buffer let opcode 0x14E smash the stack.
    uint8_t entity[0x2800] = {};
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
    // 0x0041004C sets the frame timer embedded at entity+0x1430 (retail
    // passes that address to 0x00405410). The test previously asserted a
    // g_difficulty_action global that no code ever wrote, so this case has
    // never compiled; assert the timer the opcode actually drives.
    fixture.instruction.instruction.opcode = ECL_APPLY_DIFFICULTY_ACTION;
    std::memset((uint8_t*)entity + 0x1430, 0, sizeof(FrameTimer));
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(((FrameTimer*)((uint8_t*)entity + 0x1430))->current == 27);
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

    // 0x14d / 0x14f: reset / assign timer target.
    fixture.instruction.instruction.opcode = 0x14d;
    fixture.instruction.instruction.param_mask = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(reinterpret_cast<FrameTimer*>(entity + 0x11c)->current == 0);
    fixture.instruction.instruction.opcode = 0x14f;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = 73;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(reinterpret_cast<FrameTimer*>(entity + 0x141c)->current == 73);

    // 0x153: 64-bit-safe paths.  The retail binary stores a 32-bit pointer
    // at manager+0x9eb8, so the live-boss dereference can only be exercised
    // on a 32-bit build (see the bullet_manager_test pattern).  The empty
    // paths still let us confirm the dispatcher routes through the gate.
    fixture.instruction.instruction.opcode = 0x153;
    fixture.instruction.instruction.param_mask = 0;
    g_pGameStateManager = manager;
    *(int32_t*)(manager + 0x9eb8) = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    *(int32_t*)(manager + 0x9eb8) = 0;

    fixture.instruction.instruction.opcode = 0x154;
    *(int32_t*)(manager + 0x10) = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    *(int32_t*)(manager + 0x10) = 1;
    assert(ECL_VM_Dispatch(entity) == (int)0xFFFFFFFFu);
    *(int32_t*)(manager + 0x10) = 0;

    // 0x155: label-table entry.  The VM state cursor holds a
    // 32-bit instruction pointer; the label slot at
    // (index + 0x24a) * 0x10 receives ip + 0x18.
    fixture.instruction.instruction.opcode = 0x155;
    fixture.instruction.instruction.param_mask = 1;
    fixture.Operands()[0] = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    uint32_t label_base = (uint32_t)(0x24a * 0x10);
    ECLInstruction* ip = *reinterpret_cast<ECLInstruction**>(
        fixture.bytes + 8);
    assert(*(uint32_t*)(fixture.bytes + label_base) ==
           (uint32_t)(uint64_t)ip + 0x18u);

    // 0x16a: set bit 3 of manager + 0x378c.
    fixture.instruction.instruction.opcode = 0x16a;
    fixture.instruction.instruction.param_mask = 0;
    *(uint32_t*)(manager + 0x378c) = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(manager + 0x378c) & 8u) != 0);
    *(uint32_t*)(manager + 0x378c) = 0xFF;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(manager + 0x378c) & 8u) != 0);

    // 0x16c: set bit 0x80000 from operand 0's bit 0x13.  When the operand
    // is zero the bit clears; a non-zero operand sets it.
    fixture.instruction.instruction.opcode = 0x16c;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = 1;
    *(uint32_t*)(entity + 0x1444) = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x80000u) == 0x80000u);
    fixture.Operands()[0] = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x80000u) == 0);
    fixture.Operands()[0] = 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x80000u) == 0x80000u);

    // 0x16e: set 0x100000 bit, write secondary operand to +0x1448, set +0x144c
    // from +0xf4, and clear 0x200000.
    fixture.instruction.instruction.opcode = 0x16e;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = 1;
    fixture.Operands()[1] = 42;
    *(uint32_t*)(entity + 0x1444) = 0;
    *(int32_t*)(entity + 0xf4) = 0xABCDEF12;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x100000u) == 0x100000u);
    assert((*(uint32_t*)(entity + 0x1444) & 0x200000u) == 0);
    assert(*(int32_t*)(entity + 0x1448) == 42);
    assert(*(uint32_t*)(entity + 0x144c) == 0xABCDEF12u);
    fixture.Operands()[0] = 0;
    *(uint32_t*)(entity + 0x1444) = 0x100000u | 0x200000u;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x100000u) == 0);
    assert((*(uint32_t*)(entity + 0x1444) & 0x200000u) == 0);

    // 0x16f: replace DAT_00476f78 with operand 0.
    fixture.instruction.instruction.opcode = 0x16f;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = FloatBits(0.5f);
    DAT_00476f78 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(DAT_00476f78 == FloatBits(0.5f));

    // 0x170: subtract difficulty-tier constant from the float the script
    // points to.  The retail cursor stores a 32-bit float pointer in its
    // first 4 bytes; on 64-bit hosts the truncated address is rarely a
    // valid pointer, so we exercise the no-op path (cursor[0] == 0) here
    // and rely on a 32-bit test for the live-subtraction path.
    fixture.instruction.instruction.opcode = 0x170;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = FloatBits(50.0f);
    fixture.Operands()[1] = 7;
    fixture.Operands()[2] = 25;
    fixture.Operands()[3] = 40;
    DAT_00474c74 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(fixture.Operands()[0] == FloatBits(50.0f));
    DAT_00474c74 = 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(fixture.Operands()[0] == FloatBits(50.0f));
    DAT_00474c74 = 2;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(fixture.Operands()[0] == FloatBits(50.0f));
    DAT_00474c74 = 3;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(fixture.Operands()[0] == FloatBits(50.0f));

    // 0x102: store operand 0 to entity+0xe8 (active enemy-type slot).
    fixture.instruction.instruction.opcode = 0x102;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = 7;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)(entity + 0xe8) == 7);

    // 0x118 / 0x11a: per-axis position copy and composite refresh.
    fixture.instruction.instruction.opcode = 0x118;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = FloatBits(11.0f);
    fixture.Operands()[1] = FloatBits(22.0f);
    *(uint32_t*)(entity + 0x58 + 0x28) = 1u;
    *(float*)(entity + 0x58) = 0.0f;
    *(float*)(entity + 0x5c) = 0.0f;
    *(float*)(entity + 0x84) = 100.0f;
    *(float*)(entity + 0x88) = 200.0f;
    *(float*)(entity + 0x8c) = 5.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x58) == 11.0f);
    assert(*(float*)(entity + 0x5c) == 22.0f);
    assert((*(uint32_t*)(entity + 0x58 + 0x28) & 1u) == 0);
    assert(*(float*)(entity + 0x2c) == 111.0f);
    assert(*(float*)(entity + 0x30) == 222.0f);

    fixture.instruction.instruction.opcode = 0x11a;
    fixture.Operands()[0] = FloatBits(33.0f);
    fixture.Operands()[1] = FloatBits(44.0f);
    *(uint32_t*)(entity + 0x84 + 0x28) = 1u;
    *(float*)(entity + 0x84) = 0.0f;
    *(float*)(entity + 0x88) = 0.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x84) == 33.0f);
    assert(*(float*)(entity + 0x88) == 44.0f);
    assert((*(uint32_t*)(entity + 0x84 + 0x28) & 1u) == 0);

    // 0x11c: mirror-and-set Z (no flag 0x800 -> straight store at +0x1c).
    fixture.instruction.instruction.opcode = 0x11c;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = FloatBits(1.5f);
    fixture.Operands()[1] = FloatBits(2.5f);
    *(uint32_t*)(entity + 0x1444) = 0;
    *(uint32_t*)(entity + 0x58 + 0x28) = 1u;
    *(float*)(entity + 0x58 + 0x1c) = 0.0f;
    *(float*)(entity + 0x58 + 0x18) = 0.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x58 + 0x1c) == 1.5f);
    assert(*(float*)(entity + 0x58 + 0x18) == 2.5f);
    assert((*(uint32_t*)(entity + 0x58 + 0x28) & 1u) == 0);

    // 0x11e: same shape targeting the secondary record at +0x84.
    fixture.instruction.instruction.opcode = 0x11e;
    fixture.Operands()[0] = FloatBits(0.5f);
    fixture.Operands()[1] = FloatBits(0.75f);
    *(uint32_t*)(entity + 0x84 + 0x28) = 1u;
    *(float*)(entity + 0x84 + 0x1c) = 0.0f;
    *(float*)(entity + 0x84 + 0x18) = 0.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x84 + 0x1c) == 0.5f);
    assert(*(float*)(entity + 0x84 + 0x18) == 0.75f);
    assert((*(uint32_t*)(entity + 0x84 + 0x28) & 1u) == 0);

    // 0x11c with flag 0x800 set: z is pre-mirrored around pi before the
    // final wrap-and-store.  For z = 0.5 the double-mirror yields -0.5.
    fixture.instruction.instruction.opcode = 0x11c;
    fixture.Operands()[0] = FloatBits(0.5f);
    fixture.Operands()[1] = FloatBits(0.0f);
    *(uint32_t*)(entity + 0x1444) = 0x800;
    *(uint32_t*)(entity + 0x58 + 0x28) = 1u;
    *(float*)(entity + 0x58 + 0x1c) = 0.0f;
    assert(ECL_VM_Dispatch(entity) == 0);
    const float mirrored_z = *(float*)(entity + 0x58 + 0x1c);
    assert(mirrored_z > -0.501f && mirrored_z < -0.499f);
    *(uint32_t*)(entity + 0x1444) = 0;

    // 0x193: per-slot laser record init (1.0/2.0).
    fixture.instruction.instruction.opcode = 0x193;
    fixture.instruction.instruction.param_mask = 0;
    fixture.Operands()[0] = 2;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + (2 * 3 + 0x4d1) * 4) == 1.0f);
    assert(*(float*)(entity + 0x1348 + 2 * 0xc) == 2.0f);

    // 0x194: per-slot laser speed init (1.0/2.0).
    fixture.instruction.instruction.opcode = 0x194;
    fixture.Operands()[0] = 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x210 + 0x2d4) == 1.0f);
    assert(*(float*)(entity + 0x210 + 0x2d8) == 2.0f);

    // 0x192: per-slot image counts (shorts) from operands 1/2.
    fixture.instruction.instruction.opcode = 0x192;
    fixture.Operands()[0] = 1;
    fixture.Operands()[1] = 7;
    fixture.Operands()[2] = 9;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x210 + 0x2c4) == 7);
    assert(*(short*)(entity + 0x210 + 0x2c6) == 9);

    // 0x196: per-slot angle/curve counts (shorts) from operands 1/2.
    fixture.instruction.instruction.opcode = 0x196;
    fixture.Operands()[0] = 1;
    fixture.Operands()[1] = 11;
    fixture.Operands()[2] = 13;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x210 + 0x4b8) == 11);
    assert(*(short*)(entity + 0x210 + 0x4ba) == 13);

    // 0x197: per-slot extension delay (short) from operand 1.
    fixture.instruction.instruction.opcode = 0x197;
    fixture.Operands()[0] = 1;
    fixture.Operands()[1] = 17;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x210 + 0x4bc) == 17);

    // 0x198: per-slot timing ints from operands 1/2.
    fixture.instruction.instruction.opcode = 0x198;
    fixture.Operands()[0] = 1;
    fixture.Operands()[1] = 21;
    fixture.Operands()[2] = 22;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(int32_t*)(entity + 0x210 + 0x4c4) == 21);
    assert(*(int32_t*)(entity + 0x210 + 0x4c8) == 22);

    // 0x199: per-slot laser timing sub-record (5 ints + 2 floats).
    fixture.instruction.instruction.opcode = 0x199;
    fixture.Operands()[0] = 1;
    fixture.Operands()[1] = 2;
    fixture.Operands()[2] = 100;
    fixture.Operands()[3] = 101;
    fixture.Operands()[4] = 102;
    fixture.Operands()[5] = 103;
    assert(ECL_VM_Dispatch(entity) == 0);
    int32_t record_index = 1 * 0x16 + 2;
    unsigned int record_base = record_index * 0x18u;
    assert(*(int32_t*)(entity + record_base + 0x2f8) == 100);
    assert(*(int32_t*)(entity + record_base + 0x2f4) == 101);
    assert(*(int32_t*)(entity + record_base + 0x2ec) == 102);
    assert(*(int32_t*)(entity + record_base + 0x2f0) == 103);
    assert(*(float*)(entity + record_base + 0x2e4) == 8.40779e-45f);
    assert(*(float*)(entity + (record_index * 3 + 0x5d) * 8) ==
           9.80909e-45f);

    // 0x19b: copy the 0x210-byte laser record from slot src to slot dst.
    fixture.instruction.instruction.opcode = 0x19b;
    fixture.Operands()[0] = 3;
    fixture.Operands()[1] = 1;
    for (int i = 0; i < 0x84; ++i)
        *(uint32_t*)(entity + 0x210 + 0x2c4 + i * 4) = 0x100 + i;
    for (int i = 0; i < 0x84; ++i)
        *(uint32_t*)(entity + 3 * 0x210 + 0x2c4 + i * 4) = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    for (int i = 0; i < 0x84; ++i)
        assert(*(uint32_t*)(entity + 3 * 0x210 + 0x2c4 + i * 4) ==
               (uint32_t)(0x100 + i));

    // 0x1a6: 2-tier difficulty-conditional per-slot float pair.
    fixture.instruction.instruction.opcode = 0x1a6;
    fixture.Operands()[0] = 0;
    DAT_00474c98 = 1024;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 7.0f);
    assert(*(float*)(entity + 0x2e0) == 8.0f);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 4.0f);
    assert(*(float*)(entity + 0x2e0) == 5.0f);
    DAT_00474c98 = -1024;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 1.0f);
    assert(*(float*)(entity + 0x2e0) == 2.0f);

    // 0x1a7: 3-tier difficulty-conditional per-slot float pair.
    fixture.instruction.instruction.opcode = 0x1a7;
    fixture.Operands()[0] = 0;
    DAT_00474c98 = 800;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 14.0f);
    assert(*(float*)(entity + 0x2e0) == 16.0f);
    DAT_00474c98 = 300;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 10.0f);
    assert(*(float*)(entity + 0x2e0) == 12.0f);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 7.0f);
    assert(*(float*)(entity + 0x2e0) == 8.0f);
    DAT_00474c98 = -300;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 4.0f);
    assert(*(float*)(entity + 0x2e0) == 5.0f);
    DAT_00474c98 = -500;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 1.0f);
    assert(*(float*)(entity + 0x2e0) == 2.0f);

    // 0x1a8: linear-interpolation per-slot float pair.
    fixture.instruction.instruction.opcode = 0x1a8;
    fixture.Operands()[0] = 0;
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 1.5f);
    assert(*(float*)(entity + 0x2e0) == 3.0f);
    DAT_00474c98 = 1024;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 2.0f);
    assert(*(float*)(entity + 0x2e0) == 4.0f);

    // 0x1a9: 2-tier difficulty-conditional per-slot short pair.
    fixture.instruction.instruction.opcode = 0x1a9;
    fixture.Operands()[0] = 0;
    fixture.Operands()[1] = 11;
    fixture.Operands()[2] = 12;
    fixture.Operands()[3] = 21;
    fixture.Operands()[4] = 22;
    fixture.Operands()[5] = 31;
    fixture.Operands()[6] = 32;
    DAT_00474c98 = 1024;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 31);
    assert(*(short*)(entity + 0x4ba) == 32);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 21);
    assert(*(short*)(entity + 0x4ba) == 22);
    DAT_00474c98 = -1024;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 11);
    assert(*(short*)(entity + 0x4ba) == 12);

    // 0x1aa: 3-tier difficulty-conditional per-slot short pair.
    fixture.instruction.instruction.opcode = 0x1aa;
    fixture.Operands()[0] = 0;
    fixture.Operands()[1] = 11;
    fixture.Operands()[2] = 12;
    fixture.Operands()[3] = 21;
    fixture.Operands()[4] = 22;
    fixture.Operands()[5] = 31;
    fixture.Operands()[6] = 32;
    fixture.Operands()[7] = 41;
    fixture.Operands()[8] = 42;
    fixture.Operands()[9] = 51;
    fixture.Operands()[10] = 52;
    DAT_00474c98 = 800;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 51);
    assert(*(short*)(entity + 0x4ba) == 52);
    DAT_00474c98 = 300;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 41);
    assert(*(short*)(entity + 0x4ba) == 42);
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 31);
    assert(*(short*)(entity + 0x4ba) == 32);
    DAT_00474c98 = -300;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 21);
    assert(*(short*)(entity + 0x4ba) == 22);
    DAT_00474c98 = -500;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 11);
    assert(*(short*)(entity + 0x4ba) == 12);

    // 0x1ab: linear-interpolation per-slot short pair.
    fixture.instruction.instruction.opcode = 0x1ab;
    fixture.Operands()[0] = 0;
    fixture.Operands()[1] = 100;
    fixture.Operands()[2] = 200;
    fixture.Operands()[3] = 300;
    fixture.Operands()[4] = 400;
    DAT_00474c98 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 200);
    assert(*(short*)(entity + 0x4ba) == 300);
    DAT_00474c98 = 0x400;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 300);
    assert(*(short*)(entity + 0x4ba) == 400);

    // 0x1b3: tier-conditional per-slot float pair (4 tiers).
    fixture.instruction.instruction.opcode = 0x1b3;
    fixture.Operands()[0] = 0;
    DAT_00474c74 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 1.0f);
    assert(*(float*)(entity + 0x2e0) == 7.0f);
    DAT_00474c74 = 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 2.0f);
    assert(*(float*)(entity + 0x2e0) == 8.0f);
    DAT_00474c74 = 2;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 4.0f);
    assert(*(float*)(entity + 0x2e0) == 10.0f);
    DAT_00474c74 = 4;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 0x2dc) == 5.0f);
    assert(*(float*)(entity + 0x2e0) == 12.0f);

    // 0x1b4: tier-conditional per-slot short pair (4 tiers).
    fixture.instruction.instruction.opcode = 0x1b4;
    fixture.Operands()[0] = 0;
    for (int i = 1; i <= 4; ++i) {
        fixture.Operands()[i] = i * 10;
        fixture.Operands()[i + 4] = i * 10 + 5;
    }
    DAT_00474c74 = 0;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 10);
    assert(*(short*)(entity + 0x4ba) == 15);
    DAT_00474c74 = 1;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 20);
    assert(*(short*)(entity + 0x4ba) == 25);
    DAT_00474c74 = 2;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 30);
    assert(*(short*)(entity + 0x4ba) == 35);
    DAT_00474c74 = 4;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(short*)(entity + 0x4b8) == 40);
    assert(*(short*)(entity + 0x4ba) == 45);

    // 0x107 / 0x108: sub-entity create (mode 6).  The stub records
    // (slot, sub_index, 6) for assertion.
    g_pGameStateManager = manager;
    uint8_t slot_record[0x20] = {};
    *(void**)(manager + 0x30 + 2 * 4) = slot_record;
    fixture.instruction.instruction.opcode = 0x107;
    fixture.Operands()[0] = 2;
    fixture.Operands()[1] = 5;
    assert(ECL_VM_Dispatch(entity) == 0);
    ECLSubEntityRequest* last = const_cast<ECLSubEntityRequest*>(
        ECL_LastSubEntityRequest());
    assert(last != 0);
    assert(last->mode == 6);
    assert(last->sub_index == 5);

    fixture.instruction.instruction.opcode = 0x108;
    fixture.Operands()[0] = 3;
    fixture.Operands()[1] = 7;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(ECL_LastSubEntityRequest()->mode == 6);
    assert(ECL_LastSubEntityRequest()->sub_index == 7);

    // 0x110: same sub-entity create shape (FUN_00448d00), also falls
    // through to the post-init block.  We assert mode 6 + the sub_index
    // from operand 1 just like 0x107.
    fixture.instruction.instruction.opcode = 0x110;
    fixture.Operands()[0] = 2;
    fixture.Operands()[1] = 11;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(ECL_LastSubEntityRequest()->mode == 6);
    assert(ECL_LastSubEntityRequest()->sub_index == 11);

    // 0x111: create with richer post-init; record+0x2c gets float operand
    // 2, record+0x35c gets bit 0x4 set, record+0x340/4/8 get spawned
    // position (zeros when flag 0x40000 clear, entity position otherwise).
    *(uint32_t*)(entity + 0x1444) = 0x40000;
    *(float*)(entity + 0x2c) = 12.5f;
    *(float*)(entity + 0x30) = 13.75f;
    *(float*)(entity + 0x34) = 14.25f;
    fixture.instruction.instruction.opcode = 0x111;
    fixture.Operands()[0] = 2;
    fixture.Operands()[1] = 9;
    fixture.Operands()[2] = FloatBits(3.5f);
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(ECL_LastSubEntityRequest()->mode == 6);
    assert(ECL_LastSubEntityRequest()->sub_index == 9);
    assert(*(float*)(entity + 2 * 0x210 + 0x340) == 12.5f);
    assert(*(float*)(entity + 2 * 0x210 + 0x344) == 13.75f);
    assert(*(float*)(entity + 2 * 0x210 + 0x348) == 14.25f);
    assert(*(float*)(entity + 2 * 0x210 + 0x2c) == 3.5f);
    assert((*(uint32_t*)(entity + 2 * 0x210 + 0x35c) & 4u) != 0);
    *(uint32_t*)(entity + 0x1444) = 0;
    g_pGameStateManager = 0;

    // 0x103/0x106/0x10d: sub-entity create mode 5 paths.
    fixture.instruction.instruction.opcode = 0x103;
    fixture.Operands()[0] = 4;
    fixture.Operands()[1] = 8;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(ECL_LastSubEntityRequest()->mode == 5);
    assert(ECL_LastSubEntityRequest()->sub_index == 8);

    fixture.instruction.instruction.opcode = 0x106;
    fixture.Operands()[0] = 5;
    fixture.Operands()[1] = 2;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(ECL_LastSubEntityRequest()->mode == 5);
    assert(ECL_LastSubEntityRequest()->sub_index == 2);

    fixture.instruction.instruction.opcode = 0x10d;
    fixture.Operands()[0] = 6;
    fixture.Operands()[1] = 3;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(ECL_LastSubEntityRequest()->mode == 5);
    assert(ECL_LastSubEntityRequest()->sub_index == 3);

    // 0x195: laser record 1.0/2.0 init at slot*0x210+0x2dc/0x2e0.
    fixture.instruction.instruction.opcode = 0x195;
    fixture.Operands()[0] = 3;
    assert(ECL_VM_Dispatch(entity) == 0);
    assert(*(float*)(entity + 3 * 0x210 + 0x2dc) == 1.0f);
    assert(*(float*)(entity + 3 * 0x210 + 0x2e0) == 2.0f);

    // Stubs (0x100, 0x101, 0x104, 0x105, 0x10e) — exercise the documented
    // stub path so any future regression in the dispatch table fails.
    static const unsigned short stub_opcodes[] = {
        0x100, 0x101, 0x104, 0x105, 0x10e, 0x109, 0x10a, 0x10b, 0x10c, 0x10f,
        0x119, 0x11b, 0x11d, 0x11f, 0x121, 0x123, 0x124, 0x125, 0x156, 0x15c,
        0x165, 0x166, 0x167, 0x191, 0x19a, 0x19c, 0x19d,
        0x1ac, 0x1ad, 0x1ae, 0x1af, 0x1b0, 0x1b1, 0x1b2
    };
    for (unsigned i = 0; i < sizeof(stub_opcodes)/sizeof(stub_opcodes[0]); ++i) {
        fixture.instruction.instruction.opcode = stub_opcodes[i];
        fixture.instruction.instruction.param_mask = 0;
        fixture.Operands()[0] = 0;
        fixture.Operands()[1] = 0;
        assert(ECL_VM_Dispatch(entity) == 0);
    }

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
