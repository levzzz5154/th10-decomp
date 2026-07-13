// =============================================================================
// ecl_vm.cpp - ECL (Enemy Control Language) VM dispatch
// Function: 0x0040E770 - 122 opcodes, 1826 lines decompiled
// =============================================================================
#include "th10/ecl.hpp"

// VM helper functions
extern "C" {
    uint32_t FUN_0044fdb0(uint32_t a, void* instr, int mode);  // read operand
    uint32_t FUN_0044ff00(void* vm, void* instr, int idx, int val);  // read indexed operand
    void*    FUN_00448e30(uint32_t table, int idx, int type);  // resource lookup
    int      FUN_00449450(uint32_t handle);                    // get resource data
    void     FUN_00449630(uint32_t handle);                    // release resource
    void     FUN_004495e0(void);                               // update anim
    float    FUN_00412aa0(int type, float val);                // float convert
    float    FUN_00412ac0(void);                               // rand float
    uint32_t FUN_0044bc70(float val);                          // float trunc
    void     FUN_0044c5d0(float* out, float a, float b);       // vec2 set
    void     FUN_0044c2a0(void);                               // vec normalize
    float*   FUN_00404610(void);                               // get player pos
}

extern uint32_t DAT_00473660;     // security cookie
extern uint32_t DAT_00477704;     // global config
extern uint8_t  PTR_caseD_14f_00411de0[];  // opcode jump table

// ============================================================================
// 0x0040E770 - ECL VM Dispatch
// __fastcall: ECX = param_1 (entity, passed as float for FPU access)
//
// Reads the current ECL instruction from entity+0x14D8, dispatches based on
// the 16-bit opcode (0x100-0x1B4). Uses a 181-entry jump table at 0x00411DE0.
//
// This is the heart of the bullet pattern/scripting engine. Each opcode
// manipulates entity state (position, animation, collision, bullets, sound).
//
// The function uses extraout_ECX extensively (ECX is repurposed as a scratch
// register between calls), making it impossible to decompile to clean C++.
// The __asm version from the naked generator handles byte matching.
//
// Below is the documented dispatch structure:
// ============================================================================
int __fastcall ECL_VM_Dispatch(void* entity) {
    // Get VM state from entity
    int vmState = *(int*)((int)entity + 0x14D8);
    int instrPtr = *(int*)(*(int*)(vmState + 4) + 4);
    short opcode = *(short*)(instrPtr + 4);

    // Range check: opcodes 0x100-0x1B4 (181 entries)
    if (opcode < 0x100 || opcode > 0x1B4) {
        return 0;
    }

    // Dispatch via jump table
    uint8_t jumpIndex = PTR_caseD_14f_00411de0[opcode - 0x100];

    // The actual implementation is a massive switch statement with 122 cases.
    // Each case reads operands from the instruction stream and modifies
    // entity state. Key opcode groups:
    //
    // 0x100-0x111: Entity setup (slot, anim, position, speed, target)
    // 0x118-0x12A: Visual properties (hitbox, color, scale, rotation, UV)
    // 0x140-0x156: Bullet firing (patterns, aim, spread, circle, burst)
    // 0x157-0x170: Variables and control flow (set, math, jump, call, wait)
    // 0x191-0x1B4: Audio (SFX, BGM, 3D sound, volume, effects)
    //
    // Due to the extensive use of extraout_ECX (ECX as scratch register),
    // this function cannot be expressed in portable C++. The __asm version
    // from the naked asm generator is used for byte-matching.

    (void)jumpIndex;
    return 0;
}

// ============================================================================
// Key opcode implementations (documented from Ghidra decompilation):
//
// case 0x101 (ECL_SET_SLOT):
//   Reads slot index from instruction, stores at entity+0xE8
//
// case 0x102 (ECL_LOAD_ANIM):
//   Reads animation ID, stores at entity+0xE8
//
// case 0x103 (ECL_SET_ANIM_VAR):
//   Reads slot + variable index, looks up in anim table,
//   stores result at entity+0xC0 + slot*4
//   If slot 0: also sets entity+0xF0 and entity+0xEC
//
// case 0x104 (ECL_SET_POS):
//   Reads 6 floats (x, y, z, with base offsets), stores to entity position
//   Sets local_90[0..3] = position data, copies 8 dwords from entity+0xFC
//
// case 0x105 (ECL_SET_POS_REL):
//   Similar to 0x104 but sets relative position
//
// case 0x106 (ECL_SET_ANIM_SLOT):
//   Reads slot + anim ID, looks up in resource table
//   Sets entity+0xC0 + slot*4 = anim handle
//   If slot 0: sets entity+0x13A4 and +0x13A8 from anim bounds
//   If flag 0x10 set: calls FUN_004495E0 (update anim)
//
// case 0x107 (ECL_LOAD_TEXTURE):
//   Reads texture index + slot, calls FUN_00448E30 with type 6
//
// case 0x109 (ECL_SET_FLAG):
//   Checks DAT_00477704+0x10, if set returns 0
//   Falls through to 0x100 (NOP/defaults)
//
// case 0x15C (ECL_CALL_SCRIPT):
//   Reads script ID + args, pushes current state, jumps to new script
//
// case 0x165 (ECL_RETURN):
//   Pops script stack, returns to caller script
//
// case 0x166 (ECL_JUMP):
//   Reads offset, sets instruction pointer
//
// case 0x167 (ECL_JUMP_IF):
//   Reads condition + offset, jumps if condition true
//
// case 0x168 (ECL_WAIT):
//   Reads frame count, sets wait timer, suspends execution
// ============================================================================
