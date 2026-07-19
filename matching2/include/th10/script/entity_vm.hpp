#pragma once

// Portable core for the large entity/animation script interpreter.  The
// retail instruction stream uses paired integer/float opcodes for assignment
// and arithmetic; isolating them keeps the eventual interpreter loop free of
// implicit-register dependencies.
enum EntityScriptArithmeticOpcode {
    ENTITY_SCRIPT_END = 1,
    ENTITY_SCRIPT_RETURN = 2,
    ENTITY_SCRIPT_JUMP = 3,
    ENTITY_SCRIPT_CALL = 4,
    ENTITY_SCRIPT_BRANCH_NONZERO = 5,
    ENTITY_SCRIPT_SET_INT = 6,
    ENTITY_SCRIPT_SET_FLOAT = 7,
    ENTITY_SCRIPT_ADD_INT = 8,
    ENTITY_SCRIPT_ADD_FLOAT = 9,
    ENTITY_SCRIPT_SUB_INT = 10,
    ENTITY_SCRIPT_SUB_FLOAT = 11,
    ENTITY_SCRIPT_MUL_INT = 12,
    ENTITY_SCRIPT_MUL_FLOAT = 13,
    ENTITY_SCRIPT_DIV_INT = 14,
    ENTITY_SCRIPT_DIV_FLOAT = 15,
    ENTITY_SCRIPT_MOD_INT = 16
};

enum EntityScriptStepResult {
    ENTITY_SCRIPT_STEP_APPLIED,
    ENTITY_SCRIPT_STEP_UNSUPPORTED,
    ENTITY_SCRIPT_STEP_DIVIDE_BY_ZERO,
    ENTITY_SCRIPT_STEP_MALFORMED,
    ENTITY_SCRIPT_STEP_FINISHED
};

#pragma pack(push, 1)
struct EntityScriptInstruction {
    unsigned short opcode;
    unsigned short size;
    short destination;
    unsigned short flags;
    unsigned int operand;
};
#pragma pack(pop)

enum EntityScriptInstructionFlags {
    ENTITY_SCRIPT_OPERAND_INDIRECT = 1,
    ENTITY_SCRIPT_DESTINATION_INDIRECT = 2
};

struct EntityScriptResolver {
    virtual ~EntityScriptResolver() {}
    virtual int ResolveInteger(unsigned int encoded, bool indirect) = 0;
    virtual float ResolveFloat(unsigned int encoded, bool indirect) = 0;
    virtual int* ResolveIntegerDestination(short encoded, bool indirect) = 0;
    virtual float* ResolveFloatDestination(short encoded, bool indirect) = 0;
};

struct EntityScriptCursor {
    const unsigned char* stream;
    unsigned int stream_size;
    unsigned int offset;
    bool halted;
    unsigned int call_stack[16];
    unsigned int call_depth;
};

EntityScriptStepResult EntityScript_ApplyIntegerArithmetic(
    int opcode, int* destination, int operand);
EntityScriptStepResult EntityScript_ApplyFloatArithmetic(
    int opcode, float* destination, float operand);
EntityScriptStepResult EntityScript_ExecuteOne(
    EntityScriptCursor* cursor, EntityScriptResolver* resolver);
EntityScriptStepResult EntityScript_JumpRelative(
    EntityScriptCursor* cursor, int relative_bytes);
