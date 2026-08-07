#pragma once

// Core ECL interpreter tick, retail 0x0044E1A0 (7024 bytes).
// Retail signature: int __userpurge sub_44E1A0@<eax>(int a1@<eax>, float a2)
//   a1 = the interpreter record (0x1024 bytes, the record 0x004500D0 allocates)
//   a2 = the frame delta added to the VM clock when the tick yields.
//
// This header describes only what 0x0044E1A0 itself proves.  Fields it never
// touches are named from their *callees* and are flagged as unverified here.
//
// The layout below is the retail 32-bit layout.  The production build
// (matching2/build.sh, MSVC 7.1, /Gz) is 32-bit, so `EclCoreInstruction*` is
// four bytes and `EclCoreVm` is exactly 0x1024 bytes; the size check at the
// bottom enforces that whenever pointers are four bytes wide.
#include "th10/util/scalars.hpp"

// Retail ECL instruction header, 0x10 bytes.  Every offset below is a read
// performed by 0x0044E1A0 or by one of the operand helpers it calls:
//   +0x00 int32   read as `fild` and compared against the float clock
//   +0x04 int16   switch selector (movsx, then an unsigned bound test vs 0x57)
//   +0x06 uint16  size in bytes, header included; the walk advances by it
//   +0x08 uint16  parameter mask, bit n gates operand n (read by 0x0044FF00,
//                 0x0044FF80, 0x00450030, 0x00450070)
//   +0x0A uint8   rank mask, ANDed with vm+0x101C by the walk
//   +0x0B uint8   NOT read by 0x0044E1A0 or by any helper it calls.  Named
//                 from the file format; unverified from here.
//   +0x0C uint32  NOT read anywhere on this path.  Purpose unresolved.
//   +0x10 ...     argument words.  Verified three independent ways: case 0x0C
//                 takes its jump delta from +0x10 and its new clock from +0x14,
//                 case 0x10 takes a string length from +0x10, and 0x0044FDB0 /
//                 0x0044FE40 / 0x00450030 / 0x00450070 all index operand n at
//                 +0x10 + 4*n.
#pragma pack(push, 1)
struct EclCoreInstruction {
    int            time;          // +0x00
    short          opcode;        // +0x04
    unsigned short size;          // +0x06
    unsigned short param_mask;    // +0x08
    unsigned char  rank_mask;     // +0x0A
    unsigned char  param_count;   // +0x0B  unverified from this function
    unsigned int   zero;          // +0x0C  unresolved
    unsigned int   arguments[1];  // +0x10
};
#pragma pack(pop)

// The object at vm+0x1014.  0x0044E1A0 uses vtable slot 0 and nothing else;
// the operand helpers use slots 1..4 of the same object, which is why the
// existing ECLVariableResolver in th10/script/ecl.hpp describes the same
// pointer with a different (and, for the float slots, differently numbered)
// interface.  The two views are deliberately not merged here.
struct EclCoreVm;
struct EclCoreOwner;

// The 12-byte child-list link 0x004500D0 allocates and 0x00450160 returns.
struct EclCoreChildLink {
    struct EclCoreVm* vm;       // +0x00
    EclCoreChildLink* next;     // +0x04
    EclCoreChildLink* previous; // +0x08
};

// The sorted {name, value} records 0x00450470 searches (8-byte stride).
// The value is an absolute code address in both retail (a dword) and the
// host (a full pointer); the callee entry is 16 bytes past it.
struct EclCoreScriptEntry {
    const char* name;               // +0x00
    EclCoreInstruction* code;       // +0x04
};

// The label table object at owner+0x102C (retail 0x00450470's owner).
struct EclCoreScriptTable {
    unsigned int reserved_00;           // +0x00
    unsigned int reserved_04;           // +0x04
    int count;                          // +0x08, sorted entry count
    unsigned int reserved_0C[0x20];     // +0x0C .. +0x8B
    const EclCoreScriptEntry* entries;  // +0x8C (140)
};

struct EclCoreOwnerVtable {
    // slot 0 -> retail 0x0040E770, reconstructed as the extended-opcode
    // dispatcher in matching2/src/script/ecl_vm.cpp.  Returns -1 to stop the
    // walk for this frame.
    int (*DispatchExtendedOpcode)(EclCoreOwner* owner);
    void* slot1;                        // +0x04, operand helpers, unmodelled
    void* slot2;                        // +0x08, operand helpers, unmodelled
    void* slot3;                        // +0x0C, operand helpers, unmodelled
    // slot 4 -> the external-variable arm of 0x00450070: called with the
    // truncated negative slot index, returns the destination address.
    void* (*ResolveExternalFloat)(int index);
};
struct EclCoreOwner {
    const EclCoreOwnerVtable* vtable;   // +0x0000
    EclCoreVm* current_record;          // +0x0004 the active VM record;
                                        //         0x0044DF70 swaps it around
                                        //         label resolution and
                                        //         0x004500D0 copies its rank
                                        //         mask into new children
    unsigned int reserved_08[0x408];    // +0x0008 .. +0x102B
    const EclCoreScriptTable* script_table;  // +0x102C label table used by
                                        //         0x0044DF70's callee bind
    EclCoreChildLink child_list;        // +0x1030 list anchor; the head lives
                                        //         at anchor.next (+0x1034)
};

// The interpreter record.  Offsets are retail byte offsets from a1.
struct EclCoreVm {
    float               time;             // +0x0000 clock; frame_delta accumulates
                                          //         here, opcode 0x53 subtracts
                                          //         from it, opcode 0x0A restores
                                          //         it as a raw bit pattern
    EclCoreInstruction* ip;               // +0x0004 current instruction; 0 == done
    unsigned char       scratch[0x1000];  // +0x0008 scratch/local storage.  This
                                          //         address (a1+8) is what
                                          //         0x00450690 / 0x004506D0 /
                                          //         0x004505B0 receive in EAX.
    int                 scratch_top;      // +0x1008 byte offset into scratch[]
    int                 locals_offset;    // +0x100C local-variable frame base.
                                          //         0x0044E1A0 never names it
                                          //         directly, but opcodes 0x28 /
                                          //         0x29 push and pop it through
                                          //         0x00450690 / 0x004506D0 and
                                          //         every operand helper reads it.
    int                 async_id;         // +0x1010 the id 0x004500D0 writes and
                                          //         0x00450160 searches on.  It is
                                          //         an int, NOT a script handle:
                                          //         opcode 0x0F spawns with -1,
                                          //         opcode 0x10 with a resolved id.
                                          //         0x0044E1A0 never reads it.
    EclCoreOwner*       owner;            // +0x1014 default-arm dispatch target and
                                          //         the object handed to 0x004500D0
                                          //         / 0x00450160 / 0x00450190
    unsigned int        field_1018;       // +0x1018 written on *other* VMs by 0x14.
                                          //         Never read here; unresolved.
    unsigned char       rank_mask;        // +0x101C ANDed with instruction+0x0A
    unsigned char       pad_101d[3];      // +0x101D alignment
    unsigned int        flags_1020;       // +0x1020 bit 0 set by 0x12 and cleared
                                          //         by 0x13 on *other* VMs.  Never
                                          //         read here; meaning unresolved.
};                                        // sizeof == 0x1024

// Return values, matching retail EAX exactly.
enum EclCoreResult {
    kEclCoreRunning  = 0,
    kEclCoreFinished = -1
};

// Edges 0x0044E1A0 reaches.  All four were previously unbound (their old
// claimed models disagreed with retail; the rejection notes are preserved in
// git history); they are now implemented in ecl_core_interpreter.cpp as
// EclCore_StartChild / EclCore_SpawnChild / EclCore_FindChild /
// EclCore_ResolveFloatDestination.  A null member is not a no-op: the case
// body calls Runtime_MissingEdge() with the retail address rather than
// inventing a result.
struct EclCoreHooks {
    // 0x0044DF70, reached from opcode 0x0B (`call`).  Retail shape:
    //   int __userpurge sub_44DF70@<eax>(_DWORD* child@<eax>, _DWORD* parent,
    //                                    int first_argument)
    // and 0x0044E1A0 calls it as sub_44DF70(vm, vm, 0) - an ECL `call` reuses
    // the caller's own record.  Returns 0 on success, and on success it has
    // already planted vm+0x04 at the callee entry.
    int (*start_child)(EclCoreVm* child, EclCoreVm* parent, int first_argument);

    // 0x004500D0, reached from opcodes 0x0F (`async`) and 0x10 (`asyncId`).
    // Retail shape:
    //   int __userpurge sub_4500D0@<eax>(int owner@<edi>, int async_id,
    //                                    int first_argument)
    // It allocates a 0x1024 record, stores async_id at child+0x1010, links the
    // child onto owner+0x1030/+0x1034, copies the active VM's rank mask into
    // child+0x101C and tail-calls 0x0044DF70(child, active_vm, first_argument).
    int (*spawn_child)(EclCoreOwner* owner, int async_id, int first_argument);

    // 0x00450160, reached from opcodes 0x11, 0x12, 0x13, 0x14.  Retail:
    //   _DWORD* __usercall sub_450160@<eax>(int owner@<eax>, int id@<ecx>)
    //   result = (_DWORD *)(owner + 0x1030);              // the ANCHOR ADDRESS
    //   while (*(_DWORD *)(*result + 0x1010) != id) {
    //       result = (_DWORD *)result[1];
    //       if (!result) return 0;
    //   }
    //   return result;
    EclCoreChildLink* (*find_child)(EclCoreOwner* owner, int async_id);

    // 0x00450070, reached from opcodes 0x2D, 0x51, 0x52, 0x56, 0x57.  Retail:
    //   mask is the uint16 at instruction+0x08; the encoded slot is the FLOAT
    //   at instruction+0x10+4*n, truncated to an integer byte offset; >= 0 is
    //   vm+8+locals_offset+offset and < 0 (INCLUDING -1) goes to vtable slot 4
    //   of vm+0x1014.  A clear mask bit returns null and retail stores through
    //   it unchecked.
    float* (*resolve_float_destination)(EclCoreVm* vm, unsigned int operand);

    // Optional.  When null, the default arm performs the real virtual call
    // through vtable slot 0 of vm+0x1014 (retail 0x0040E770).  This member
    // exists so the walk can be exercised without a retail-shaped vtable; it
    // adds no behaviour of its own.
    int (*dispatch_extended)(EclCoreOwner* owner);
};

// Retail 0x0044E1A0.  Returns 0 while the VM is still live and -1 when it has
// finished (vm->ip cleared, or a `call`/`ret` failure edge).
int EclVm_TickCore(EclCoreVm* vm, float frame_delta, const EclCoreHooks* hooks);

// Fails to compile if the record stops being 0x1024 bytes in a 32-bit build.
typedef int EclCoreVmSizeCheck[
    (sizeof(void*) != 4 || sizeof(EclCoreVm) == 0x1024) ? 1 : -1];

// Retail 0x0044DF70: start the child at the sub name embedded in the parent's
// call instruction.  Marshals the call's argument records into the child's
// scratch area (below the return frame it pushes), then binds the callee by
// resolving the name in owner->script_table (retail 0x00450470) and planting
// the entry in the child's ip slot.  Returns 0 on success, -1 when the name
// is unknown (parent->ip cleared -> the parent stops on its next tick).
int EclCore_StartChild(EclCoreVm* child, EclCoreVm* parent, int first_argument);

// Retail 0x004500D0: allocate a fresh 0x1024 record, link it onto the head of
// owner->child_list, copy the active record's rank mask, and tail-call
// EclCore_StartChild(child, owner->current_record, first_argument).  Returns
// the start result (0 success, -1 failure).
int EclCore_SpawnChild(EclCoreOwner* owner, int async_id, int first_argument);

// Retail 0x00450160: walk owner->child_list from the anchor and return the
// first link whose VM's async_id matches, or 0.
EclCoreChildLink* EclCore_FindChild(EclCoreOwner* owner, int async_id);

// Retail 0x00450070: resolve the destination of a writable float operand.
// A clear param_mask bit returns 0; a non-negative encoded slot resolves to
// vm scratch + locals_offset + slot; a negative slot (including -1) goes
// through vtable slot 4 of vm+0x1014.
float* EclCore_ResolveFloatDestination(EclCoreVm* vm, unsigned int operand);
