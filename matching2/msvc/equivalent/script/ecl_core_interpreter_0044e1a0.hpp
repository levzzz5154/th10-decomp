#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern "C" float data_00470b04;
extern "C" float data_00470b60;

struct EclInstr {
    int time;
    short id;
    unsigned short size;
    unsigned short mask;
    unsigned char rank;
    unsigned char argc;
    int reserved;
    union {
        int i[1];
        float f[1];
        char s[1];
    };
};

struct EclVm;
struct EclOwner;

struct EclNode {
    EclVm* vm;
    EclNode* next;
    EclNode* previous;
};

struct EclStack {
    unsigned char data[0x1000];
    int sp;
    int base;

    __declspec(noinline) int Push(int size);
    __declspec(noinline) int Pop();
    __declspec(noinline) int Write(char type, unsigned int size, const void* source);

    // The raw pop reports success so the typed pops can consume the tag
    // word only when a value was actually taken.
    __forceinline bool PopRaw(void* out) {
        if (sp - 4 >= 0) { sp -= 4; *(int*)out = *(int*)&data[sp]; return true; }
        return false;
    }
    __forceinline void PopInt(int* out) {
        if (PopRaw(out)) {
            sp -= 4;
            char tag = data[sp];
            if (tag == 'f') *out = (int)*(float*)out;
        }
    }
    __forceinline void PopFloat(float* out) {
        if (PopRaw(out)) {
            sp -= 4;
            char tag = data[sp];
            if (tag == 'f') {} else if (tag == 'i') *out = (float)*(int*)out;
        }
    }
};

struct EclPolar {
    float x, y, z;
    EclPolar* SetPolar(float angle, float radius);
};

float __stdcall Angle_Normalize(float angle);

struct EclVm {
    float time;
    EclInstr* instr;
    EclStack stack;
    int id;
    EclOwner* owner;
    int f1018;
    unsigned char rank;
    unsigned char pad[3];
    int flags;

    __forceinline void PopRaw(void* out) { stack.PopRaw(out); }
    __forceinline void PopInt(int* out) { stack.PopInt(out); }
    __forceinline void PopFloat(float* out) { stack.PopFloat(out); }
    __declspec(noinline) int Run(float delta);
    __declspec(noinline) int Start(EclVm* volatile source, int index);
    __declspec(noinline) int IntOperand(int selector);
    __declspec(noinline) int IntValue(int selector, int value);
    __declspec(noinline) float FloatOperand(int selector);
    __declspec(noinline) static float FloatValue(int selector, EclVm* vm, float value);
    __declspec(noinline) int* IntDest(int index);
    __declspec(noinline) float* FloatDest(int index);
};

struct EclOwner {
    virtual int Execute();
    virtual int ResolveInt(int);
    virtual int* ResolveIntDest(int);
    virtual float ResolveFloat(int);
    virtual float* ResolveFloatDest(int);
    EclVm* active;
    EclVm root;
    void* script;
    EclNode children;

    __declspec(noinline) EclNode* FindVariable(int id);
    __declspec(noinline) void ResetVariableBindings();
    __declspec(noinline) int SpawnChild(int id, int index);
    __declspec(noinline) int Tick(float delta);
};
