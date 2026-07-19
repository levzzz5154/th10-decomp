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
    unsigned int operand2;
    unsigned int operand3;
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

struct EntityScriptServices {
    void (*reset_timer)(void* context, int value);
    void (*resource_transition)(void* context, int value);
    void (*emit_animation_event)(void* context, int event, int value);
    void* context;
    float (*random_float)(void* context);
    int (*random_integer)(void* context, int bound);
    void (*set_vector)(void* context, int opcode, float x, float y, float z);
    void (*set_pair)(void* context, int opcode, float x, float y);
    void (*set_bytes)(void* context, int opcode, unsigned char a,
                      unsigned char b, unsigned char c);
    void (*write_byte)(void* context, int opcode, unsigned int target,
                       unsigned int offset, unsigned char value);
    void (*scale_pair)(void* context, int opcode, float factor);
    void (*set_mode)(void* context, unsigned char mode);
    void (*set_scalar)(void* context, int opcode, float value);
    void (*set_flags)(void* context, int opcode, unsigned int value);
    void (*reset_state)(void* context);
    void (*invoke_action)(void* context, unsigned int value);
};

struct EntityScriptCursor {
    const unsigned char* stream;
    unsigned int stream_size;
    unsigned int offset;
    bool halted;
    unsigned int call_stack[16];
    unsigned int call_depth;
    const EntityScriptServices* services;
};

EntityScriptStepResult EntityScript_ApplyIntegerArithmetic(
    int opcode, int* destination, int operand);
EntityScriptStepResult EntityScript_ApplyFloatArithmetic(
    int opcode, float* destination, float operand);
EntityScriptStepResult EntityScript_ApplyBinaryInteger(
    int opcode, int* destination, int left, int right);
EntityScriptStepResult EntityScript_ApplyBinaryFloat(
    int opcode, float* destination, float left, float right);
typedef float (*EntityScriptRandomFloat)(void* context);
EntityScriptStepResult EntityScript_AssignRandomFloat(
    float* destination, float minimum, float maximum,
    EntityScriptRandomFloat random, void* context);
bool EntityScript_CompareInteger(int opcode, int left, int right);
bool EntityScript_CompareFloat(int opcode, float left, float right);
EntityScriptStepResult EntityScript_ApplyUnaryFloat(
    int opcode, float* destination, float operand);
EntityScriptStepResult EntityScript_ExecuteOne(
    EntityScriptCursor* cursor, EntityScriptResolver* resolver);
EntityScriptStepResult EntityScript_Run(
    EntityScriptCursor* cursor, EntityScriptResolver* resolver,
    unsigned int max_steps, unsigned int* executed_steps);
EntityScriptStepResult EntityScript_JumpRelative(
    EntityScriptCursor* cursor, int relative_bytes);
EntityScriptStepResult EntityScript_InvokeService(
    const EntityScriptServices* services, int service, int value);
EntityScriptStepResult EntityScript_ExecuteServiceOpcode(
    const EntityScriptServices* services, int opcode, int value);
