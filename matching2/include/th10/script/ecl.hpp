#pragma once

#include "th10/game/entity.hpp"

// TH10 ECL instruction header as consumed by the dispatcher at 0x0040E770.
// Operands follow the 0x14-byte header.  Their interpretation is controlled by
// param_mask and by the VM's variable-resolution helpers.
#pragma pack(push, 1)
struct ECLInstruction {
    int32_t time;
    int16_t opcode;
    int16_t size;
    uint32_t param_mask;
    uint32_t rank_mask;
    int32_t param_count;
    uint32_t operands[1];
};
#pragma pack(pop)

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

int __fastcall ECL_VM_Dispatch(void* entity);
