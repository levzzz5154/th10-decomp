// Host tests for the four ECL core edges reconstructed in
// src/script/ecl_core_interpreter.cpp:
//   0x0044DF70 EclCore_StartChild
//   0x004500D0 EclCore_SpawnChild
//   0x00450160 EclCore_FindChild
//   0x00450070 EclCore_ResolveFloatDestination
// The headline test runs a real call -> prologue -> ret -> stop cycle through
// EclVm_TickCore with the hooks bound, then checks the marshalled arguments.

#include "th10/script/ecl_core_interpreter.hpp"

#include "th10/math/timer.hpp"
#include "th10/script/ecl.hpp"
#include "th10/math/angle.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>

// Host test storage for the retail-data-backed globals the interpreter and
// ecl_vm.cpp reference (the retail build aliases them from .data).
float DAT_00470b04 = 0.0f;
float DAT_00470b60 = -1.0f;
void* g_pGameStateManager = 0;
int32_t DAT_00474c98 = 0;
int32_t DAT_00474c74 = 0;
uint32_t DAT_00476f78 = 0x3F800000u;  // 1.0f as bits
float DAT_00470d58 = 0.0f;
float DAT_00470b94 = 3.1415927f;
unsigned int DAT_00477830 = 0;
float DAT_00470b10 = -3.1415927f;  // -pi
float DAT_00470b14 = 6.2831855f;   // 2*pi
float DAT_00470b18 = 3.1415927f;   // pi
void AnimationManager_SetFlag(void*, int, unsigned int) {}
void AnimationManager_ClearFlag(void*, int, unsigned int) {}
extern "C" void AnimationManager_SetEclFlag(void) {}
extern "C" void AnimationManager_ClearEclFlag(void) {}
extern "C" uint32_t ECL_DispatchOpcode(uint32_t, void*, int) { return 0; }
void Timer_Set(FrameTimer* timer, int target) {
    (void)target;
    timer->current = 0;
    timer->elapsed = 0.0f;
    timer->flags |= 1u;
}

namespace {

#pragma pack(push, 1)
// The packed retail instruction layout the interpreter walks (the size field
// advances the ip by its own value, so the host struct must be byte-exact).
struct TestInstruction {
    int time;              // +0x00
    short opcode;          // +0x04
    unsigned short size;   // +0x06
    unsigned short param_mask;  // +0x08
    unsigned char rank_mask;    // +0x0A
    unsigned char param_count;  // +0x0B
    unsigned int zero;          // +0x0C
    unsigned int args[8];       // +0x10
};
#pragma pack(pop)

void WriteHeader(unsigned char* p, int opcode, int size, int rank,
                 int count) {
    std::memset(p, 0, 0x10);
    p[4] = (unsigned char)(opcode & 0xFF);
    p[5] = (unsigned char)(opcode >> 8);
    p[6] = (unsigned char)(size & 0xFF);
    p[7] = (unsigned char)(size >> 8);
    p[0xA] = (unsigned char)rank;
    p[0xB] = (unsigned char)count;
}

// A complete callable script image (byte-explicit, as the loader would feed
// the interpreter): the sub record (16-byte header), the prologue (0x28,
// one operand: frame size 8 - the two marshalled args' extent, so the locals
// marker lands above them; size 0x14 covers header + operand) and the ret
// (0x0A) at prologue + 0x14.
struct TestSubImage {
    unsigned char header[0x10];
    unsigned char prologue[0x10];
    unsigned char prologue_arg[4];
    unsigned char ret[0x10];
    void Build() {
        WriteHeader(header, 0, 0x10, 1, 0);
        WriteHeader(prologue, 0x28, 0x14, 1, 1);
        *(unsigned int*)prologue_arg = 8;             // frame size
        WriteHeader(ret, 0x0A, 0x10, 1, 0);
    }
};

// The caller's stream: a call (0x0B) to "Sub" with two marshalled arguments
// (int 42, float 3.5), then a stop (0x01) immediately after the call's size
// extent, so the ret's advance lands on it.
struct TestCallImage {
    unsigned char bytes[0x28 + 0x10];
    void Build() {
        WriteHeader(bytes, 0x0B, 0x28, 1, 3);
        *(unsigned int*)(bytes + 0x10) = 4;           // sub name length
        std::memcpy(bytes + 0x14, "Sub", 4);          // the name, padded
        bytes[0x18] = 'i';                            // arg1 record
        bytes[0x19] = 'i';
        *(int*)(bytes + 0x1C) = 42;
        bytes[0x20] = 'f';                            // arg2 record
        bytes[0x21] = 'f';
        *(float*)(bytes + 0x24) = 3.5f;
        WriteHeader(bytes + 0x28, 0x01, 0x10, 1, 0);  // stop
    }
};

int ExternalCalls = 0;

void* ResolveExternalFloat(int index) {
    ++ExternalCalls;
    return reinterpret_cast<void*>(0x4000 + index);
}

int DispatchExtended(EclCoreOwner*) {
    return 0;
}

EclCoreOwnerVtable g_vtable = {
    DispatchExtended, 0, 0, 0, ResolveExternalFloat,
};
EclCoreOwner g_owner = {};

// The four reconstructions, bound exactly as the stage host binds them.
EclCoreHooks Hooks() {
    EclCoreHooks hooks = {};
    hooks.start_child = EclCore_StartChild;
    hooks.spawn_child = EclCore_SpawnChild;
    hooks.find_child = EclCore_FindChild;
    hooks.resolve_float_destination = EclCore_ResolveFloatDestination;
    return hooks;
}

TestSubImage* BuildSub(TestSubImage* sub) {
    sub->Build();
    return sub;
}

TestCallImage* BuildCall(TestCallImage* call) {
    call->Build();
    return call;
}

// -- 0x00450070 -------------------------------------------------------------

void TestResolveFloatDestination() {
    EclCoreVm vm = {};
    TestInstruction instruction = {};
    vm.ip = reinterpret_cast<EclCoreInstruction*>(&instruction);
    vm.locals_offset = 4;
    g_owner.vtable = &g_vtable;
    vm.owner = &g_owner;
    instruction.param_mask = 1u << 0;             // operand 0 present
    instruction.args[0] = 0x41200000;             // 10.0f

    float* local = EclCore_ResolveFloatDestination(&vm, 0);
    assert(local == reinterpret_cast<float*>(vm.scratch + 4 + 10));

    instruction.args[0] = 0xC0400000;             // -3.0f
    float* external = EclCore_ResolveFloatDestination(&vm, 0);
    assert(external == reinterpret_cast<float*>(0x4000 - 3));
    assert(ExternalCalls == 1);

    instruction.args[0] = 0xBF800000;             // -1.0f, the sentinel index
    assert(EclCore_ResolveFloatDestination(&vm, 0) ==
           reinterpret_cast<float*>(0x4000 - 1));
    assert(ExternalCalls == 2);

    instruction.param_mask = 0;                   // mask bit clear -> null
    assert(EclCore_ResolveFloatDestination(&vm, 0) == 0);

    instruction.param_mask = 1u << 1;             // wrong bit -> null
    assert(EclCore_ResolveFloatDestination(&vm, 0) == 0);
}

// -- 0x00450160 / 0x004500D0 ------------------------------------------------

void TestSpawnAndFind() {
    TestSubImage sub;
    BuildSub(&sub);
    TestCallImage call;
    BuildCall(&call);
    EclCoreScriptEntry entries[1] = {
        {"Sub", reinterpret_cast<EclCoreInstruction*>(&sub.header)},
    };
    EclCoreScriptTable table = {};
    table.count = 1;
    table.entries = entries;

    EclCoreVm active = {};
    active.rank_mask = 0x55;
    active.ip = reinterpret_cast<EclCoreInstruction*>(&call.bytes);
    EclCoreOwner owner = {};
    owner.vtable = &g_vtable;
    owner.current_record = &active;
    owner.script_table = &table;
    active.owner = &owner;

    assert(EclCore_FindChild(&owner, 7) == 0);    // empty list

    assert(EclCore_SpawnChild(&owner, 7, 0) == 0);
    EclCoreChildLink* link7 = EclCore_FindChild(&owner, 7);
    assert(link7 != 0);
    assert(link7->vm->async_id == 7);
    assert(link7->vm->owner == &owner);
    assert(link7->vm->rank_mask == 0x55);         // copied from active record
    assert(link7->vm->ip ==
           reinterpret_cast<EclCoreInstruction*>(&sub.prologue));

    assert(EclCore_SpawnChild(&owner, 9, 0) == 0);
    EclCoreChildLink* link9 = EclCore_FindChild(&owner, 9);
    assert(link9 != 0);
    assert(link9->vm->async_id == 9);
    assert(owner.child_list.next == link9);       // head insertion
    assert(link9->next == link7);
    assert(link7->previous == link9);
    assert(link9->previous == &owner.child_list);
    assert(EclCore_FindChild(&owner, 7) == link7);
    assert(EclCore_FindChild(&owner, 99) == 0);
}

// -- 0x0044DF70: unknown callee --------------------------------------------

void TestStartChildUnknownName() {
    TestSubImage sub;
    BuildSub(&sub);
    TestCallImage call;
    BuildCall(&call);
    EclCoreScriptTable table = {};                // no entries
    EclCoreVm vm = {};
    vm.ip = reinterpret_cast<EclCoreInstruction*>(&call.bytes);
    g_owner.vtable = &g_vtable;
    g_owner.current_record = &vm;
    g_owner.script_table = &table;
    vm.owner = &g_owner;
    vm.rank_mask = 0xFF;

    assert(EclCore_StartChild(&vm, &vm, 0) == -1);
    assert(vm.ip == 0);                           // parent stopped
}

// -- the full cycle through EclVm_TickCore ----------------------------------

void TestCallRetCycle() {
    TestSubImage sub;
    BuildSub(&sub);
    TestCallImage call;
    BuildCall(&call);
    EclCoreScriptEntry entries[1] = {
        {"Sub", reinterpret_cast<EclCoreInstruction*>(&sub.header)},
    };
    EclCoreScriptTable table = {};
    table.count = 1;
    table.entries = entries;

    EclCoreVm vm = {};
    vm.ip = reinterpret_cast<EclCoreInstruction*>(&call.bytes);
    vm.rank_mask = 0xFF;
    EclCoreOwner owner = {};
    owner.vtable = &g_vtable;
    owner.current_record = &vm;
    owner.script_table = &table;
    vm.owner = &owner;

    const EclCoreHooks hooks = Hooks();
    // One tick runs the whole cycle: call (binds "Sub") -> prologue ->
    // ret (pops the frame) -> stop (halts).
    const int result = EclVm_TickCore(&vm, 1.0f, &hooks);
    assert(result == kEclCoreFinished);
    assert(vm.ip == 0);
    assert(owner.current_record == &vm);          // restored after the bind

    // The marshalled arguments sat at the callee's frame base (scratch[16..]
    // on the host: two zero dwords + a pointer-width ip, with the args at the
    // post-push top).  The ret's teardown restored the caller's top (16), then
    // its two pops left scratch_top at 4 (time was at scratch[4]).
    assert(vm.scratch_top == 4);
    assert(vm.locals_offset == 0);
    int arg1 = 0;
    std::memcpy(&arg1, vm.scratch + 8 + sizeof(void*), sizeof(arg1));
    assert(arg1 == 42);
    float arg2 = 0.0f;
    std::memcpy(&arg2, vm.scratch + 8 + sizeof(void*) + 4, sizeof(arg2));
    assert(arg2 == 3.5f);
}

// -- nested call frame ------------------------------------------------------

void TestNestedCallFrame() {
    TestSubImage sub;
    BuildSub(&sub);
    TestCallImage call;
    BuildCall(&call);
    EclCoreScriptEntry entries[1] = {
        {"Sub", reinterpret_cast<EclCoreInstruction*>(&sub.header)},
    };
    EclCoreScriptTable table = {};
    table.count = 1;
    table.entries = entries;

    // A child that already ran one call: frame [0][0][ip] + two arg dwords.
    EclCoreVm vm = {};
    vm.rank_mask = 0xFF;
    EclCoreVm parent = {};
    g_owner.vtable = &g_vtable;
    g_owner.current_record = &parent;
    g_owner.script_table = &table;
    parent.owner = &g_owner;

    const int base = 8 + (int)sizeof(void*) + 8;
    vm.scratch_top = base;
    parent.time = 0.5f;
    parent.ip = reinterpret_cast<EclCoreInstruction*>(&call.bytes);

    assert(EclCore_StartChild(&vm, &parent, 0) == 0);
    // Nested frame: time bits at base, ip pointer after it, args at the new
    // top (base + 4 + pointer width).
    assert(vm.scratch_top == base + 4 + (int)sizeof(void*));
    int time_bits = 0;
    std::memcpy(&time_bits, vm.scratch + base, sizeof(time_bits));
    float time_float = 0.0f;
    std::memcpy(&time_float, &time_bits, sizeof(time_float));
    assert(time_float == 0.5f);
    assert(*reinterpret_cast<EclCoreInstruction**>(vm.scratch + base + 4) ==
           parent.ip);
    int arg1 = 0;
    std::memcpy(&arg1, vm.scratch + base + 4 + sizeof(void*), sizeof(arg1));
    assert(arg1 == 42);
    float arg2 = 0.0f;
    std::memcpy(&arg2, vm.scratch + base + 4 + sizeof(void*) + 4,
                sizeof(arg2));
    assert(arg2 == 3.5f);
    assert(g_owner.current_record == &parent);     // restored
    assert(parent.ip != 0);
}

}  // namespace

int main() {
    TestResolveFloatDestination();
    TestSpawnAndFind();
    TestStartChildUnknownName();
    TestCallRetCycle();
    TestNestedCallFrame();
    std::cout << "ECL_CORE_EDGES_TESTS_PASS\n";
    return 0;
}
