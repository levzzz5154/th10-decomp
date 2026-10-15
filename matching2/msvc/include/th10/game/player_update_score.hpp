#pragma once
// 0x0041C800..0x0041C84B (76 bytes):
//   ?CopyVectorAndEvaluate@LaserManager_0041c800@@QAEHPBMMH@Z
//
// Copies the caller's three-component vector into the record area at this+0x440
// and then walks the linked record list rooted at this+0x18, adding up what each
// record's evaluator returns.  The evaluator is the virtual function in vtable
// slot 7 (byte offset 0x1C) and is handed the same vector plus the two values
// the caller supplied; records whose type word at +0x0C is 1 are skipped (they
// are already retired) and their evaluator is never called.  The accumulated
// value is the result.
//
// Retail reaches this member with the receiver in EAX, the vector in EBX and
// both remaining parameters on the stack (RET 8) - a whole-program register
// agreement, not a C++ convention.  Two details of the model are load-bearing:
//
//  * The vector parameter must be a _pointer_ (EBX) while the first value
//    parameter is a `float`: that is what makes the whole-program pass hold the
//    float in the callee-saved EBP across the evaluator call (retail caches the
//    float and reloads the int); with an `int` in that position the pass caches
//    the *second* parameter instead and the prologue moves.
//  * The record type must be the polymorphic class itself, so the evaluator call
//    compiles to `mov eax,[ecx]; push ...; call [eax+1Ch]` with the record in
//    ECX, exactly as retail.
//
// This unit is therefore compiled inside the native-LTCG cluster declared by
// layout/ltcg/score_records_copy_vector_and_evaluate.json, whose
// synthetic caller supplies that register state.
#include <stddef.h>

struct LaserListNode_0041c800 {
    // Vtable slot 7 (byte offset 0x1C) is the evaluator; slots 0..6 belong to
    // the other record operations and are never named here.
    virtual int Slot00();
    virtual int Slot04();
    virtual int Slot08();
    virtual int Slot0C();
    virtual int Slot10();
    virtual int Slot14();
    virtual int Slot18();
    virtual int Slot1C(const float* vector, float value, int flag);

    unsigned char reserved_004[4];              // +0x04
    LaserListNode_0041c800* next;           // +0x08
    int type;                                   // +0x0C, 1 marks a retired record
};

struct Vector3_0041c800 { float x; float y; float z; };

struct LaserManager_0041c800 {
    unsigned char reserved_000[0x18];
    LaserListNode_0041c800* linked_head;    // +0x18
    unsigned char reserved_01C[0x440 - 0x1C];
    Vector3_0041c800 vector_440;                // +0x440

    __declspec(noinline) int CopyVectorAndEvaluate(const float* vector, float value,
                                                   int flag);
};

typedef char LaserManager_0041c800_head_must_be_18[
    (offsetof(LaserManager_0041c800, linked_head) == 0x18) ? 1 : -1];
typedef char LaserManager_0041c800_vector_must_be_440[
    (offsetof(LaserManager_0041c800, vector_440) == 0x440) ? 1 : -1];
typedef char LaserListNode_0041c800_next_must_be_8[
    (offsetof(LaserListNode_0041c800, next) == 0x08) ? 1 : -1];
typedef char LaserListNode_0041c800_type_must_be_c[
    (offsetof(LaserListNode_0041c800, type) == 0x0C) ? 1 : -1];
