#pragma once

#include "th10/game/entity.hpp"

// TH10 ECL instruction header as consumed by the dispatcher at 0x0040E770.
// The header is 0x10 bytes and operands begin at +0x10. Verified by walking
// every ECLH sub of th10.dat's stage01.ecl: chaining instructions by the +0x06
// size field only closes with a 16-byte header, and the first argument of
// `op 0x28 size 0x14` sits at +0x10.
//
// This previously declared a 0x14-byte header with param_mask, rank_mask and
// param_count all 32 bits wide, which put operands[] at +0x14 - so every
// operand read in the dispatcher was four bytes past its argument.
#pragma pack(push, 1)
struct ECLInstruction {
    int32_t time;            // +0x00 scheduled script time
    int16_t opcode;          // +0x04 read sign-extended by the dispatcher
    uint16_t size;           // +0x06 header + arguments, in bytes
    uint16_t param_mask;     // +0x08 bit N: argument N is a variable reference
    uint8_t rank_mask;       // +0x0A ANDed with the VM's difficulty mask
    uint8_t param_count;     // +0x0B
    uint32_t reserved_0c;    // +0x0C always zero in shipped scripts
    uint32_t operands[1];    // +0x10
};
#pragma pack(pop)
#ifndef _MSC_VER
static_assert(sizeof(ECLInstruction) == 0x14,
              "0x10-byte header plus one operand word");
#endif

// The execution state owns a cursor object.  The retail dispatcher obtains the
// current instruction from cursor->instruction rather than treating +0x04 as
// an instruction pointer directly.
struct ECLInstructionCursor {
    uint32_t reserved_header;
    ECLInstruction* instruction;
};

struct ECLVMState {
    uint32_t reserved_state;
    ECLInstructionCursor* cursor;
};

// Verified opcode meanings from the 0x0040E770 switch.  Unlisted values are
// deliberately unnamed until their behavior has been established.
enum ECLLeafOpcode {
    ECL_SET_HITBOX_WIDTH       = 0x140,
    ECL_SET_HITBOX_HEIGHT      = 0x141,
    ECL_SET_FLAGS              = 0x142,
    ECL_CLEAR_FLAGS            = 0x143,
    ECL_SET_MOVEMENT_BOUNDARY  = 0x144,
    ECL_CLEAR_MOVEMENT_BOUNDARY= 0x145,
    ECL_RESET_DIFFICULTY_SLOTS = 0x146,
    ECL_SET_DIFFICULTY_SLOT    = 0x147,
    ECL_SET_RANGE_PARAMETERS   = 0x148,
    ECL_SET_CURRENT_DIFFICULTY = 0x14A,
    ECL_RESET_DIFFICULTY_STATE = 0x14B,
    ECL_SET_DIFFICULTY_SQUARED = 0x15A,
    ECL_SET_DIFFICULTY_PARAMETER = 0x15B,
    ECL_SELECT_DIFFICULTY_VALUE = 0x15D,
    ECL_SELECT_DIFFICULTY_CURVE = 0x15E,
    ECL_INTERPOLATE_DIFFICULTY  = 0x15F
    ,ECL_SET_GLOBAL_DIFFICULTY  = 0x168
    ,ECL_APPLY_DIFFICULTY_ACTION= 0x169
};

struct ECLMovementBoundary {
    float left;
    float top;
    float right;
    float bottom;
};

// Interface stored at cursor+0x1014.  ECL_ResolveFloatOperand calls vtable slot 3 for
// negative variable identifiers other than -1.
struct ECLVariableResolver {
    virtual void Unknown0() = 0;
    virtual int32_t ResolveInt(int32_t variable) = 0;
    virtual int32_t* ResolveIntPointer(int32_t variable) = 0;
    virtual void Unknown2() = 0;
    virtual float ResolveFloat(int32_t variable) = 0;
    virtual float* ResolveFloatPointer(int32_t variable) = 0;
};

// Readable leaf operations extracted from the retail dispatcher.  Keeping the
// values explicit makes these useful independently of its unusual register-
// based operand reader.
uint32_t ECL_SetFlags(void* entity, uint32_t flags);
uint32_t ECL_ClearFlags(void* entity, uint32_t flags);
void ECL_SetMovementBoundary(void* entity,
                             const ECLMovementBoundary& boundary);
void ECL_ClearMovementBoundary(void* entity);
void ECL_ResetDifficultySlots(void* entity);
float ECL_ResolveFloatOperand(void* cursor, unsigned int operand);
int32_t ECL_ResolveIntOperand(void* cursor, unsigned int operand);
int32_t ECL_ResolveIntFromEntity(void* entity, unsigned int operand);
float ECL_ResolveFloatValue(
    void* cursor, unsigned int operand, float value);
int32_t ECL_ResolveIntValue(
    void* cursor, unsigned int operand, int32_t value);
float* ECL_ResolveFloatDestination(void* cursor, unsigned int operand);
int32_t* ECL_ResolveIntDestination(void* cursor, unsigned int operand);
// 0x00412ED0: update score mode and invalidate its cached result.
void Score_SetMode(void* state, int mode);
void Score_SetNormalizedAngle(void* state, float angle);
void Ecl_SetResourceSlot(void* state, int slot, int resource,
                         unsigned int first, unsigned int second);
// ECL variable-table and scratch-stack helpers (0x00450030, 0x00450160,
// 0x00450190, 0x00450690, 0x004506D0), expressed with a normal C++ ABI.
void* ECL_ResolveVariableValue(void* vm, int32_t variable);
void ECL_ResetVariableBindings(void* vm);
int32_t ECL_PushScratchValue(void* vm, int32_t value);
int32_t ECL_PopScratchValue(void* vm);
void ECL_SetPolarVector(float* destination, float angle, float magnitude);
int32_t ECL_WriteScratch(void* vm, char type, unsigned int size,
                         const void* data);
void* ECL_FindScriptLabel(void* vm, const unsigned short* name);
void ECL_DecodeEncryptedString(
    char* destination, const char* encrypted, unsigned int length);

// Execute the common encrypted-string opcode family (0x156/0x15c/0x165-0x167).
// The callback owns the decoded buffer only for the duration of the call.
void ECL_ExecuteEncryptedStringOpcode(
    int opcode, int base_index, int difficulty, const char* encrypted,
    unsigned int length,
    void (*emit)(int resource_index, const char* text, unsigned int length));

// Readable reconstructions of the ECL retail helper functions.  The simple
// resolvers wrap the existing variable-resolution API; the more complex
// state writers are best-effort stubs that record enough state for the
// dispatcher to exercise the leaf opcode shape without depending on the
// sub-entity / animation manager state machine.  Callers that need the
// full retail behavior should provide a more complete implementation.
float ECL_ResolveFloatAtCursor(void* cursor, unsigned int bit_index,
                               float encoded);
int32_t ECL_ResolveIntAtCursor(void* cursor, unsigned int bit_index,
                                int32_t encoded);
float ECL_PrngFloat(void* state);
void ECL_WrapValue(float* value);
void ECL_PrngSeed(void* state, unsigned short seed);
// Init a movement/laser record (the 0x10-byte block the retail sets up
// before populating speeds / positions).  `record` points at the record
// base; `offset_24`, `offset_28`, etc. are the record's field offsets.
void ECL_InitMovementRecord(void* record);
// Init a "bullet" record variant: same shape but the active-flag lives
// at +0x40 instead of +0x30.
void ECL_InitBulletRecord(void* record);
// Set a movement record's primary Z value (offset 0x1c) with retail wrap.
void ECL_SetPositionZWithWrap(void* record, float value);
// Sub-entity creation (FUN_00448e30 / FUN_00448d00).  These stubs record
// the call so a test can assert that the dispatcher invoked the right
// helper with the right arguments; the actual entity state machine is
// the next reconstruction pass.
struct ECLSubEntityRequest {
    int32_t slot;
    int32_t sub_index;
    int32_t mode;  // 5 (FUN_00448e30) or 6 (FUN_00448d00) or 7 (FUN_00448e30 alt)
    void* record;
};
ECLSubEntityRequest* ECL_SubEntityCreate(int32_t slot, int32_t sub_index,
                                         int32_t mode);
const ECLSubEntityRequest* ECL_LastSubEntityRequest(void);
// Sub-entity markers (FUN_00449450 / FUN_004495e0 / FUN_00449590).
int32_t ECL_SubEntityMark(int32_t slot);
void ECL_AnimationFlagSet(void);
void ECL_AnimationFlagClear(void);
// Manager operations (FUN_0040cfb0, FUN_0040cf90, FUN_0040cf60, etc.).
void ECL_AddToActiveList(void* manager, void* sub_entity);
void* ECL_FindByID(int32_t id);
void ECL_ReleaseByID(int32_t id);
void ECL_ApplyEclFlag(void);
void ECL_ApplyEclFlagAlt(void);
void ECL_RangeReset(void);
// Score mode / curve setters (FUN_00412ed0 family).  Already covered by
// Score_SetMode above.

int __fastcall ECL_VM_Dispatch(void* entity);
