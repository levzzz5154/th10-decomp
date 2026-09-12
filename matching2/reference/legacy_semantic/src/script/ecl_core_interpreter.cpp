// Core ECL interpreter tick, retail address 0x0044E1A0 (7024 bytes).
//
// Recovered from ida/th10.exe.c lines 69250-70772 (body from 69576) and from
// ida/th10.exe.asm loc_44E1A0..loc_44FBB2, with decompiled/ghidra_raw/
// 0044E1A0_FUN_0044e1a0.c as a third opinion.  Where the pseudocode and the
// listing disagree the listing wins; every such case is called out inline.
//
// The function walks a linear instruction stream, gates each instruction on a
// rank mask and a clock, and runs a jump table over opcodes 0x00..0x57.  Its
// default arm forwards everything else - including the whole 0x100+ family -
// to vtable slot 0 of the object at vm+0x1014, which is retail 0x0040E770,
// already reconstructed in matching2/src/script/ecl_vm.cpp.
//
// Retail edges reached from inside the switch:
//   0x0044DF70 `call`                     -> EclCore_StartChild (below)
//   0x004500D0 async spawn                -> EclCore_SpawnChild (below)
//   0x00450160 child lookup by id         -> EclCore_FindChild (below)
//   0x00450070 float destination resolve  -> EclCore_ResolveFloatDestination
//                                            (below)
//   0x0044FF00 ECL_ResolveIntValue        -> bound (ecl_vm.cpp)
//   0x0044FF80 ECL_ResolveFloatValue      -> bound (ecl_vm.cpp)
//   0x00450030 ECL_ResolveVariableValue   -> bound (ecl_vm.cpp)
//   0x00450190 ECL_ResetVariableBindings  -> bound (ecl_vm.cpp)
//   0x00450690 ECL_PushScratchValue       -> bound (ecl_vm.cpp)
//   0x004506D0 ECL_PopScratchValue        -> bound (ecl_vm.cpp)
//   0x004505B0 ECL_WriteScratch           -> bound (ecl_vm.cpp)
//   0x004501B0 ECL_SetPolarVector         -> bound (ecl_vm.cpp)
//   0x0044BC70 Angle_Normalize            -> bound (math/angle.cpp)
//   0x00463B2C __ftol2                    -> the CRT truncating float->int cast
//   fsin / fcos / fpatan                  -> x87 instructions, not calls
//
// 0x0044FDB0 and 0x0044FE40 are deliberately NOT called: see the note above
// EclCore_ResolveIntOperand.
#include "th10/script/ecl_core_interpreter.hpp"

#include "th10/script/ecl.hpp"
#include "th10/script/script_label_search.hpp"
#include "th10/math/angle.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <stdlib.h>   // malloc / free, called directly by opcode 0x1E
#include <string.h>   // strchr, called directly by opcode 0x1E

extern "C" float sinf(float);
extern "C" float cosf(float);
extern "C" double atan2(double y, double x);

// Retail reads uninitialised stack slots on the scratch-underflow paths of
// opcodes 0x0D, 0x0E, 0x32-0x3F, 0x40-0x4E, 0x54 and 0x55 - the guarded pop
// simply does not run and the arithmetic proceeds on whatever the slot held.
// That is reproduced here rather than papered over with a default value, so
// the diagnostic below is CORRECT about this code and about retail.  It is
// silenced only so a -Werror host build does not reject a faithful
// transcription; do not "fix" the warning by initialising the locals.
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

namespace {

// What an opcode body tells the walk to do next.  These four continuations are
// the only ones that exist: every `goto` out of the retail switch lands on
// LABEL_294, LABEL_296, one of the two `return -1` tails, or the default arm's
// own `return 0`.
enum EclCoreAction {
    kEclCoreAdvance   = 0,  // LABEL_294/295: re-read vm+0x04, step by its +0x06
    kEclCoreRetest    = 1,  // LABEL_296: the body already placed vm+0x04
    kEclCoreStop      = 2,  // return -1
    kEclCoreYield     = 3,  // return 0 WITHOUT adding frame_delta (default arm)
    kEclCoreUnhandled = 4   // not a real case label -> take the default arm
};

union EclCoreWord {
    unsigned int as_bits;
    int          as_int;
    float        as_float;
};

float EclCore_BitsFloat(unsigned int bits) {
    EclCoreWord converted;
    converted.as_bits = bits;
    return converted.as_float;
}

unsigned int EclCore_FloatBits(float value) {
    EclCoreWord converted;
    converted.as_float = value;
    return converted.as_bits;
}

// 0x0044FDB0 and 0x0044FE40 are `operands[n] -> 0x0044FF00 / 0x0044FF80` and
// nothing else.  They are spelled out here instead of being called because the
// symbols that claim those two addresses (ECL_ResolveIntOperand /
// ECL_ResolveFloatOperand in matching2/src/script/ecl_vm.cpp) fetch the operand
// through ECLInstruction::operands, and th10/script/ecl.hpp places that array
// at instruction+0x14.  Retail indexes operand n at instruction+0x10+4*n - see
// sub_44FDB0 line 70836, `*(_DWORD *)(v2 + 4 * a2 + 16)`.  The value-taking
// halves (0x0044FF00 / 0x0044FF80) are faithful and are called directly.
int EclCore_ResolveIntOperand(EclCoreVm* vm, unsigned int operand) {
    const EclCoreInstruction* instruction = vm->ip;          // vm+0x04
    return ECL_ResolveIntValue(vm, operand,
                               (int)instruction->arguments[operand]);
}

float EclCore_ResolveFloatOperand(EclCoreVm* vm, unsigned int operand) {
    const EclCoreInstruction* instruction = vm->ip;          // vm+0x04
    return ECL_ResolveFloatValue(
        vm, operand, EclCore_BitsFloat(instruction->arguments[operand]));
}

// ---------------------------------------------------------------------------
// The two scratch pops retail inlines at roughly 190 sites.
//
// A scratch entry is eight bytes: a type tag byte at scratch[top-8] and the
// value word at scratch[top-4].  Both pops decrement vm+0x1008 twice by four.
//
// Two retail hazards are reproduced deliberately:
//  1. Only the FIRST decrement is range-checked.  With scratch_top == 4 the
//     second decrement stores -4 into vm+0x1008 and reads the tag byte from
//     vm+0x04, the low byte of the instruction pointer.  Retail really does
//     this; it is reachable only on a malformed stack.
//  2. When the first check fails nothing at all happens - not the store to
//     vm+0x1008, not the write to the destination.  The caller then uses an
//     uninitialised local.  *value is therefore left UNTOUCHED on that path.
// ---------------------------------------------------------------------------

// Integer flavour: only the 'f' tag converts, through __ftol2 (0x00463B2C),
// which truncates toward zero.
void EclCore_PopInt(EclCoreVm* vm, int* value) {
    int top = vm->scratch_top - 4;                            // vm+0x1008
    if (top < 0)
        return;
    vm->scratch_top = top;
    const unsigned int raw = *(const unsigned int*)(vm->scratch + top);
    top -= 4;
    vm->scratch_top = top;
    if (*(const char*)(vm->scratch + top) == 'f')
        *value = (int)EclCore_BitsFloat(raw);
    else
        *value = (int)raw;
}

// Float flavour: retail tests 'f' first (keep the bits) and then 'i' (fild),
// so any other tag - including garbage - is taken as a float bit pattern.
void EclCore_PopFloat(EclCoreVm* vm, float* value) {
    int top = vm->scratch_top - 4;                            // vm+0x1008
    if (top < 0)
        return;
    vm->scratch_top = top;
    const unsigned int raw = *(const unsigned int*)(vm->scratch + top);
    top -= 4;
    vm->scratch_top = top;
    if (*(const char*)(vm->scratch + top) == 'i')
        *value = (float)(int)raw;
    else
        *value = EclCore_BitsFloat(raw);
}

// The second operand of the float arithmetic opcodes 0x33/0x35/0x37/0x39 is
// popped WITHOUT the rounding store: retail leaves the `fild` result on the
// x87 stack and folds the arithmetic in before the single `fstp`, which is why
// IDA renders those four as `(double)SLODWORD(v) op rhs`.  This split lets the
// callers reproduce that asymmetry.  On underflow *raw is left untouched and
// `is_int` is false, exactly like the short-circuited `&&` in the pseudocode.
void EclCore_PopFloatRaw(EclCoreVm* vm, float* raw, bool* is_int) {
    *is_int = false;
    int top = vm->scratch_top - 4;                            // vm+0x1008
    if (top < 0)
        return;
    vm->scratch_top = top;
    *raw = EclCore_BitsFloat(*(const unsigned int*)(vm->scratch + top));
    top -= 4;
    vm->scratch_top = top;
    *is_int = *(const char*)(vm->scratch + top) == 'i';
}

// 0x004505B0 with dl = 0x69 'i' / 0x66 'f' and size 4.  The scratch base it
// receives in EAX is vm+8, which is why it indexes its own top at +0x1000.
void EclCore_PushInt(EclCoreVm* vm, int value) {
    ECL_WriteScratch(vm->scratch, 'i', 4, &value);
}

void EclCore_PushFloat(EclCoreVm* vm, float value) {
    ECL_WriteScratch(vm->scratch, 'f', 4, &value);
}

// LABEL_299 (loc_44FBB0), shared by opcode 0x01 and by opcode 0x0A when the
// scratch stack is empty.
int EclCore_HaltCurrent(EclCoreVm* vm) {
    vm->ip = 0;                                               // vm+0x04
    return kEclCoreStop;
}

// LABEL_35 (loc_44E40F), the shared body of opcodes 0x0C, 0x0D and 0x0E.
// arguments[0] at instruction+0x10 is a raw BYTE delta - it is not
// param_mask-resolved - and arguments[1] at instruction+0x14 is the new clock,
// converted with `fild`/`fstp`.  Retail writes the clock first, then moves the
// pointer, then falls into LABEL_296 without running the normal advance.
int EclCore_Jump(EclCoreVm* vm) {
    EclCoreInstruction* current = vm->ip;                     // vm+0x04
    vm->time = (float)(int)current->arguments[1];             // instruction+0x14
    const unsigned int delta = current->arguments[0];         // instruction+0x10
    vm->ip = (EclCoreInstruction*)((unsigned char*)current + delta);
    return kEclCoreRetest;
}

// ---------------------------------------------------------------------------
// The jump table, in retail case order.  59 labels; the 29 values inside
// 0x00..0x57 that are NOT labels (0x02-0x09, 0x16-0x1D, 0x1F-0x27, 0x2E-0x31 -
// IDA annotates them at def_44E205 as "default case, cases 2-9,22-29,31-39,
// 46-49") fall through to kEclCoreUnhandled so the walk hands them to the
// extended dispatcher, exactly as retail does.
// ---------------------------------------------------------------------------
int EclCore_ExecuteOpcode(EclCoreVm* vm, EclCoreInstruction* instruction,
                          int opcode, const EclCoreHooks* hooks) {
    switch (opcode) {

    // ---- 0x00  nop ------------------------------------------------------
    // Jump-table slot 0 points straight at LABEL_294; the case has no body.
    case 0x00:
        return kEclCoreAdvance;

    // ---- 0x01  stop -----------------------------------------------------
    case 0x01:
        return EclCore_HaltCurrent(vm);

    // ---- 0x0A  ret ------------------------------------------------------
    // loc_44E20C.  Tears the local-variable frame down, then pops the saved
    // instruction pointer and the saved clock.
    case 0x0A: {
        // 0x004506D0 receives vm+8, so its +0x1000/+0x1004 are vm+0x1008 and
        // vm+0x100C: it restores locals_offset and rewinds scratch_top to the
        // caller's frame base.
        ECL_PopScratchValue(vm->scratch);

        // Tested AFTER the teardown, not before.  An empty stack here means
        // the outermost sub returned.
        if (vm->scratch_top == 0)                             // vm+0x1008
            return EclCore_HaltCurrent(vm);

        // Two pops after the teardown, independently guarded.  The ip slot is
        // pointer-width on the host (0x0044DF70 pushes it as a full pointer);
        // a 32-bit build reads exactly the retail dword.
        int top = vm->scratch_top - (int)sizeof(void*);
        if (top >= 0) {
            vm->scratch_top = top;
            vm->ip = *(EclCoreInstruction**)(vm->scratch + top);   // vm+0x04
        }
        top = vm->scratch_top - 4;
        if (top >= 0) {
            vm->scratch_top = top;
            // `mov eax,[edi+eax] / mov [esi],eax`: a RAW DWORD copy into the
            // float clock.  No conversion - the caller pushed the bit pattern,
            // so it comes back as bits.
            vm->time = EclCore_BitsFloat(
                *(const unsigned int*)(vm->scratch + top));        // vm+0x00
        }

        // loc_44FBB2: return -1 without re-clearing vm+0x04, which is already
        // zero on this path.
        if (vm->ip == 0)
            return kEclCoreStop;

        // The restored pointer still addresses the `call` instruction, so the
        // normal advance steps past it.
        return kEclCoreAdvance;
    }

    // ---- 0x0B  call -----------------------------------------------------
    // loc_44E35C: `push ebp / push esi / mov eax,esi / call sub_44DF70`, i.e.
    // sub_44DF70(vm, vm, 0).  child == parent: an ECL `call` runs in the SAME
    // 0x1024 record and pushes its return state onto that record's own scratch
    // stack, which is what opcode 0x0A pops back off.
    case 0x0B:
        if (hooks->start_child == 0)
            Runtime_MissingEdge(0x0044DF70u, "ecl/core 0x0B call: 0x0044DF70");
        if (hooks->start_child(vm, vm, 0) != 0)
            return kEclCoreStop;               // loc_44FBB2, vm+0x04 untouched
        // Zero -> `jmp loc_44FB85` (LABEL_296): SKIP the advance, because
        // 0x0044DF70 has already planted vm+0x04 at the callee entry.
        return kEclCoreRetest;

    // ---- 0x0C  jump -----------------------------------------------------
    case 0x0C:
        return EclCore_Jump(vm);

    // ---- 0x0D  jump if zero ---------------------------------------------
    // loc_44E3C1.  The listing ends in `cmp [esp+var_1C], ebp / jnz LABEL_294`
    // - an INTEGER test.  IDA renders the same slot as `v321 != 0.0`; that is
    // a typing artifact of the shared float stack slot, not a float compare.
    case 0x0D: {
        int condition;                    // intentionally uninitialised
        EclCore_PopInt(vm, &condition);
        if (condition != 0)
            return kEclCoreAdvance;
        return EclCore_Jump(vm);
    }

    // ---- 0x0E  jump if non-zero -----------------------------------------
    // loc_44E372, the same pop with the test inverted.
    case 0x0E: {
        int condition;                    // intentionally uninitialised
        EclCore_PopInt(vm, &condition);
        if (condition == 0)
            return kEclCoreAdvance;
        return EclCore_Jump(vm);
    }

    // ---- 0x0F  async ----------------------------------------------------
    // loc_44E25F: sub_4500D0(vm->owner, -1, 0).  The -1 becomes the child's
    // async id at child+0x1010; the 0 is the first-argument index handed on to
    // 0x0044DF70.  No operand is read here - the callee walks them.  Retail
    // discards the returned child pointer.
    case 0x0F:
        if (hooks->spawn_child == 0)
            Runtime_MissingEdge(0x004500D0u, "ecl/core 0x0F async: 0x004500D0");
        hooks->spawn_child(vm->owner, -1, 0);                 // vm+0x1014
        return kEclCoreAdvance;

    // ---- 0x10  async with id --------------------------------------------
    // loc_44E282.  Argument 0 is a sub name stored as [len:4][bytes:len] and
    // argument 1's raw word sits immediately after it: retail computes
    // `instruction + 0x10 + 4*((len + 4) >> 2)` with an UNSIGNED shift.
    // Verified on th10.dat: stage01 sub 40 @0x65e8 is
    //   time=0x3c op=0x10 size=0x24 mask=0 rank=0xff count=2 zero=0
    //   len=12 "Girl01_at\0\0\0" id=0
    // and 0x24 == 0x10 + 4 + 12 + 4.
    case 0x10: {
        const unsigned int length =
            *(const unsigned int*)((const unsigned char*)instruction + 0x10);
        const int raw_id = *(const int*)((const unsigned char*)instruction +
                                         0x10 + 4 * ((length + 4) >> 2));
        // 0x0044FF00 on operand index 1.
        const int async_id = ECL_ResolveIntValue(vm, 1, raw_id);
        if (hooks->spawn_child == 0)
            Runtime_MissingEdge(0x004500D0u, "ecl/core 0x10 asyncId: 0x004500D0");
        // first_argument = 1: arguments 0 and 1 are consumed here, so the
        // child-start helper marshals from index 2 up.
        hooks->spawn_child(vm->owner, async_id, 1);
        return kEclCoreAdvance;
    }

    // ---- 0x11  kill child by id -----------------------------------------
    // loc_44E2AC.  Clearing child+0x04 is what LABEL_299 does to a running VM:
    // the child's next tick returns -1 and the child walker unlinks it.
    case 0x11: {
        const int async_id = EclCore_ResolveIntOperand(vm, 0);
        if (hooks->find_child == 0)
            Runtime_MissingEdge(0x00450160u, "ecl/core 0x11: 0x00450160");
        EclCoreChildLink* link = hooks->find_child(vm->owner, async_id);
        if (link != 0)
            link->vm->ip = 0;                                 // child+0x04
        return kEclCoreAdvance;
    }

    // ---- 0x12  set bit 0 of child+0x1020 --------------------------------
    // loc_44E2D3.  UNRESOLVED: 0x0044E1A0 never reads +0x1020, so the meaning
    // of bit 0 cannot be established from this function.  Only the pairing
    // with 0x13 is verified.
    case 0x12: {
        const int async_id = EclCore_ResolveIntOperand(vm, 0);
        if (hooks->find_child == 0)
            Runtime_MissingEdge(0x00450160u, "ecl/core 0x12: 0x00450160");
        EclCoreChildLink* link = hooks->find_child(vm->owner, async_id);
        if (link != 0)
            link->vm->flags_1020 |= 1u;                       // child+0x1020
        return kEclCoreAdvance;
    }

    // ---- 0x13  clear bit 0 of child+0x1020 ------------------------------
    case 0x13: {
        const int async_id = EclCore_ResolveIntOperand(vm, 0);
        if (hooks->find_child == 0)
            Runtime_MissingEdge(0x00450160u, "ecl/core 0x13: 0x00450160");
        EclCoreChildLink* link = hooks->find_child(vm->owner, async_id);
        if (link != 0)
            link->vm->flags_1020 &= ~1u;                      // child+0x1020
        return kEclCoreAdvance;
    }

    // ---- 0x14  write operand 1 into child+0x1018 ------------------------
    // loc_44E329.  UNRESOLVED: +0x1018 is never read by 0x0044E1A0 and
    // 0x004500D0 does not initialise it; its consumer is elsewhere.
    case 0x14: {
        const int async_id = EclCore_ResolveIntOperand(vm, 0);
        if (hooks->find_child == 0)
            Runtime_MissingEdge(0x00450160u, "ecl/core 0x14: 0x00450160");
        EclCoreChildLink* link = hooks->find_child(vm->owner, async_id);
        if (link != 0) {
            // Retail latches link->vm into EDI *before* resolving operand 1
            // (`mov edi,[eax]` then `call sub_44FDB0`), so a resolver that
            // rearranged the child list would leave this pointer stale.  The
            // order is reproduced deliberately.
            EclCoreVm* child = link->vm;
            child->field_1018 =
                (unsigned int)EclCore_ResolveIntOperand(vm, 1);
        }
        return kEclCoreAdvance;
    }

    // ---- 0x15  detach every child ---------------------------------------
    // loc_44E272 -> 0x00450190, which walks the list head at owner+0x1034 and
    // stores 0 into every node->vm+0x04.  No operands: every 0x15 in
    // stage01.ecl is 0x10 bytes with param_count 0.  Retail discards the
    // return value.
    case 0x15:
        ECL_ResetVariableBindings(vm->owner);
        return kEclCoreAdvance;

    // ---- 0x1E  debug format ---------------------------------------------
    // loc_44FA71..loc_44FB5D.  Confirmed in the listing rather than inferred:
    // the retail build has NO output call here.  The integer path's EAX is
    // dropped, the float path is followed by a bare `fstp st`, and the
    // 0x400-byte buffer is freed unread.  The surviving effects are the
    // malloc/free pair and the side effects inside the operand resolvers -
    // notably the scratch pops a -1 operand encoding performs.  This is a
    // debug print whose printf was compiled out, not a no-op.
    case 0x1E: {
        // Argument 0's length is at +0x10 and its bytes at +0x14; the typed
        // argument records follow the bytes.
        const char* cursor = (const char*)((const unsigned char*)instruction + 0x14);

        // No null check on malloc in retail, and no bound check on the copy
        // below either: a format segment longer than 0x3FF bytes overruns.
        char* buffer = (char*)malloc(0x400);
        buffer[0] = 0;

        // `cmp edi, ebp` with EBP held at zero - a null test on
        // instruction+0x14, which can never be null.  Kept literal.
        if (cursor != 0) {
            unsigned int argument_index = 1;   // EBX: operand index
            int type_offset = 0;               // var_100: byte offset into the
                                               //          8-byte records
            int value_index = 6;               // EBP: dword index of the value
                                               //      word, base 0x18/4
            for (;;) {
                const char* percent = strchr(cursor, '%');
                if (percent == 0)
                    break;

                // Inlined strcpy(buffer, cursor) then truncation at the '%'.
                // Each pass overwrites the buffer from scratch, so it only
                // ever holds one segment - and nothing reads it.
                {
                    const char* source = cursor;
                    char character;
                    do {
                        character = *source;
                        buffer[source - cursor] = character;
                        ++source;
                    } while (character != 0);
                }
                buffer[percent - cursor] = 0;

                // `movsx eax,byte [eax+1] / sub eax,25h / jz ... / sub eax,3Fh
                //  / jz ... / sub eax,2 / jnz ...`: accept 'd' (0x25+0x3F) and
                // 'f' (+2), skip "%%" and every other conversion without
                // consuming an argument.
                const char conversion = percent[1];
                if (conversion != '%') {
                    if (conversion == 'd' || conversion == 'f') {
                        // Retail re-reads vm+0x04 for every formatted argument
                        // instead of reusing the dispatched instruction.
                        const unsigned char* base =
                            (const unsigned char*)vm->ip;
                        const int length = *(const int*)(base + 0x10);
                        // Record k: source type byte at +0x14+len+8k, value
                        // word at +0x18+len+8k.  `length / 4` is retail's
                        // signed divide (cdq / and edx,3 / add / sar 2).
                        const char source_type =
                            *(const char*)(base + 0x14 + length + type_offset);
                        const int word = 4 * (length / 4 + value_index);
                        if (source_type == 'f' || source_type == 'g') {
                            // 0x0044FF80; result discarded (`fstp st`).
                            ECL_ResolveFloatValue(vm, argument_index,
                                                  *(const float*)(base + word));
                        } else {
                            // 0x0044FF00; result discarded.
                            ECL_ResolveIntValue(vm, argument_index,
                                                *(const int*)(base + word));
                        }
                        type_offset += 8;
                        value_index += 2;
                        ++argument_index;
                    }
                }

                // `add edi,2 / jnz`: the loop-back test is on the advanced
                // cursor and is always taken; strchr returning 0 is the only
                // exit.
                cursor = percent + 2;
            }
        }

        free(buffer);
        return kEclCoreAdvance;
    }

    // ---- 0x28  enter local-variable frame -------------------------------
    // loc_44E437.  Operand 0 is the frame size in bytes; 0x00450690 reserves
    // it at vm+0x1008, chains the old vm+0x100C into scratch and sets
    // vm+0x100C to the new frame base.  Retail discards the -1 overflow
    // return.  Every stage01 sub opens with `0x28 4`.
    case 0x28: {
        const int frame_size = EclCore_ResolveIntOperand(vm, 0);
        ECL_PushScratchValue(vm->scratch, frame_size);
        return kEclCoreAdvance;
    }

    // ---- 0x29  leave local-variable frame -------------------------------
    // loc_44E450.  No operands.  Retail discards the return value.
    case 0x29:
        ECL_PopScratchValue(vm->scratch);
        return kEclCoreAdvance;

    // ---- 0x2A  push int -------------------------------------------------
    case 0x2A: {
        const int value = EclCore_ResolveIntOperand(vm, 0);
        EclCore_PushInt(vm, value);
        return kEclCoreAdvance;
    }

    // ---- 0x2B  pop into an int variable ---------------------------------
    // loc_44E47F.  `xor ecx,ecx / call sub_450030` - operand index 0 in ECX,
    // the VM in ESI.  The value copy is `mov ecx,[esi+eax+8] / mov [edi],ecx`,
    // a plain integer move, so no float round-trip happens on the payload.
    // Retail does NOT null-check the destination: 0x00450030 returns 0 when
    // operand 0's mask bit is clear and retail stores through it anyway.
    // Reproduced; every 0x2B in stage01 sets the bit.
    case 0x2B: {
        int* destination = (int*)ECL_ResolveVariableValue(vm, 0);  // 0x00450030
        int top = vm->scratch_top - 4;                         // vm+0x1008
        if (top >= 0) {
            vm->scratch_top = top;
            *destination = (int)*(const unsigned int*)(vm->scratch + top);
            top -= 4;
            vm->scratch_top = top;                             // unguarded
            if (*(const char*)(vm->scratch + top) == 'f') {
                // `fld dword [edi] / call __ftol2 / mov [edi],eax`
                *destination =
                    (int)EclCore_BitsFloat((unsigned int)*destination);
            }
        }
        return kEclCoreAdvance;
    }

    // ---- 0x2C  push float -----------------------------------------------
    // 0x0044FE40 returns in st0 and retail stores it to a dword float
    // temporary, so the single-precision rounding happens here.
    case 0x2C: {
        const float value = EclCore_ResolveFloatOperand(vm, 0);
        EclCore_PushFloat(vm, value);
        return kEclCoreAdvance;
    }

    // ---- 0x2D  pop into a float variable --------------------------------
    // loc_44E4F2, the mirror of 0x2B: the payload copy is again a plain
    // integer move, and only the 'i' tag converts (`cmp 'f' jz skip /
    // cmp 'i' jnz skip / fild [eax] / fstp [eax]`).  Same missing null check.
    case 0x2D: {
        if (hooks->resolve_float_destination == 0)
            Runtime_MissingEdge(0x00450070u, "ecl/core 0x2D: 0x00450070");
        float* destination = hooks->resolve_float_destination(vm, 0);
        int top = vm->scratch_top - 4;                          // vm+0x1008
        if (top >= 0) {
            vm->scratch_top = top;
            *destination =
                EclCore_BitsFloat(*(const unsigned int*)(vm->scratch + top));
            top -= 4;
            vm->scratch_top = top;                              // unguarded
            if (*(const char*)(vm->scratch + top) == 'i')
                *destination = (float)(int)EclCore_FloatBits(*destination);
        }
        return kEclCoreAdvance;
    }

    // ---- 0x32  int add --------------------------------------------------
    // The first pop is the right-hand operand (top of stack), the second is
    // the left-hand one.  That order holds for every binary opcode below.
    case 0x32: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs + rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x33  float add ------------------------------------------------
    // The 'i' arm keeps the `fild` result at x87 precision and rounds once, at
    // the `fstp`; `double` is the closest portable stand-in.
    case 0x33: {
        float rhs;
        EclCore_PopFloat(vm, &rhs);
        float lhs_raw;
        bool  lhs_is_int;
        EclCore_PopFloatRaw(vm, &lhs_raw, &lhs_is_int);
        float result;
        if (lhs_is_int)
            result = (float)((double)(int)EclCore_FloatBits(lhs_raw) + (double)rhs);
        else
            result = lhs_raw + rhs;
        EclCore_PushFloat(vm, result);
        return kEclCoreAdvance;
    }

    // ---- 0x34  int subtract ---------------------------------------------
    case 0x34: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs - rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x35  float subtract -------------------------------------------
    case 0x35: {
        float rhs;
        EclCore_PopFloat(vm, &rhs);
        float lhs_raw;
        bool  lhs_is_int;
        EclCore_PopFloatRaw(vm, &lhs_raw, &lhs_is_int);
        float result;
        if (lhs_is_int)
            result = (float)((double)(int)EclCore_FloatBits(lhs_raw) - (double)rhs);
        else
            result = lhs_raw - rhs;
        EclCore_PushFloat(vm, result);
        return kEclCoreAdvance;
    }

    // ---- 0x36  int multiply ---------------------------------------------
    // Retail duplicates the tail (one arm per operand register) but both
    // compute the same product; multiplication is commutative so the operand
    // order is unobservable here, unlike 0x38 and 0x3A.
    case 0x36: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs * rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x37  float multiply -------------------------------------------
    case 0x37: {
        float rhs;
        EclCore_PopFloat(vm, &rhs);
        float lhs_raw;
        bool  lhs_is_int;
        EclCore_PopFloatRaw(vm, &lhs_raw, &lhs_is_int);
        float result;
        if (lhs_is_int)
            result = (float)((double)(int)EclCore_FloatBits(lhs_raw) * (double)rhs);
        else
            result = lhs_raw * rhs;
        EclCore_PushFloat(vm, result);
        return kEclCoreAdvance;
    }

    // ---- 0x38  int divide -----------------------------------------------
    // Retail emits cdq/idiv: a zero divisor raises #DE.  No guard exists in
    // the binary and none is added here.
    case 0x38: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs / rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x39  float divide ---------------------------------------------
    case 0x39: {
        float rhs;
        EclCore_PopFloat(vm, &rhs);
        float lhs_raw;
        bool  lhs_is_int;
        EclCore_PopFloatRaw(vm, &lhs_raw, &lhs_is_int);
        float result;
        if (lhs_is_int)
            result = (float)((double)(int)EclCore_FloatBits(lhs_raw) / (double)rhs);
        else
            result = lhs_raw / rhs;
        EclCore_PushFloat(vm, result);
        return kEclCoreAdvance;
    }

    // ---- 0x3A  int modulo -----------------------------------------------
    // idiv remainder: the sign follows the dividend, matching C++ %.  A zero
    // divisor raises #DE, unguarded, as above.
    case 0x3A: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs % rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x3B  int equal ------------------------------------------------
    // Every comparison in the family pushes its boolean with the INT tag,
    // including the float-typed ones.
    case 0x3B: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs == rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x3C  float equal ----------------------------------------------
    // Tail shared with 0x3E/0x40/0x42/0x44/0x46/0x48 (LABEL_166 / LABEL_211).
    // The listing's `fnstsw / test ah,44h / jnp` makes plain C++ `==` exact,
    // NaN included: every unordered compare in this family pushes 0.
    case 0x3C: {
        float rhs;
        float lhs;
        EclCore_PopFloat(vm, &rhs);
        EclCore_PopFloat(vm, &lhs);
        EclCore_PushInt(vm, lhs == rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x3D  int not-equal --------------------------------------------
    case 0x3D: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs != rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x3E  float not-equal ------------------------------------------
    // Retail preloads 1 and jumps to LABEL_211 (store 0) when the values
    // compare equal, so an unordered pair yields 1 here.
    case 0x3E: {
        float rhs;
        float lhs;
        EclCore_PopFloat(vm, &rhs);
        EclCore_PopFloat(vm, &lhs);
        EclCore_PushInt(vm, lhs == rhs ? 0 : 1);
        return kEclCoreAdvance;
    }

    // ---- 0x3F  int less-than --------------------------------------------
    case 0x3F: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs < rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x40  float less-than ------------------------------------------
    // loc_44F191: `fld lhs / fcomp rhs / fnstsw ax / test ah,5 / jnp push-1`.
    // C0 alone (lhs < rhs) has odd parity and pushes 1; unordered sets C0 and
    // C2 together, so it pushes 0.  IDA's `if (lhs >= rhs) push 0 else push 1`
    // is wrong for NaN; the listing is authoritative and plain `<` matches it.
    case 0x40: {
        float rhs;
        float lhs;
        EclCore_PopFloat(vm, &rhs);
        EclCore_PopFloat(vm, &lhs);
        EclCore_PushInt(vm, lhs < rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x41  int less-or-equal ----------------------------------------
    case 0x41: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs <= rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x42  float less-or-equal --------------------------------------
    case 0x42: {
        float rhs;
        float lhs;
        EclCore_PopFloat(vm, &rhs);
        EclCore_PopFloat(vm, &lhs);
        EclCore_PushInt(vm, lhs <= rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x43  int greater-than -----------------------------------------
    case 0x43: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs > rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x44  float greater-than ---------------------------------------
    case 0x44: {
        float rhs;
        float lhs;
        EclCore_PopFloat(vm, &rhs);
        EclCore_PopFloat(vm, &lhs);
        EclCore_PushInt(vm, lhs > rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x45  int greater-or-equal -------------------------------------
    case 0x45: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs >= rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x46  float greater-or-equal -----------------------------------
    case 0x46: {
        float rhs;
        float lhs;
        EclCore_PopFloat(vm, &rhs);
        EclCore_PopFloat(vm, &lhs);
        EclCore_PushInt(vm, lhs >= rhs ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x47  int logical not ------------------------------------------
    // An integer `cmp ... ,0`, not a float compare.
    case 0x47: {
        int value;
        EclCore_PopInt(vm, &value);
        EclCore_PushInt(vm, value == 0 ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x48  float logical not ----------------------------------------
    // `fld 0.0 (flt_470B04) / fucompp / test ah,44h / jnp`: NaN pushes 0.
    case 0x48: {
        float value;
        EclCore_PopFloat(vm, &value);
        EclCore_PushInt(vm, value == 0.0f ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x49  logical or -----------------------------------------------
    // loc_44F4C4 is `cmp [var], ebp / jnz` twice - INTEGER tests on the popped
    // words.  IDA renders them as `!= 0.0` because the slots are typed float;
    // the listing settles it.
    case 0x49: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, (lhs != 0 || rhs != 0) ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x4A  logical and ----------------------------------------------
    case 0x4A: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, (lhs != 0 && rhs != 0) ? 1 : 0);
        return kEclCoreAdvance;
    }

    // ---- 0x4B  bitwise xor ----------------------------------------------
    case 0x4B: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs ^ rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x4C  bitwise or -----------------------------------------------
    case 0x4C: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs | rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x4D  bitwise and ----------------------------------------------
    case 0x4D: {
        int rhs;
        int lhs;
        EclCore_PopInt(vm, &rhs);
        EclCore_PopInt(vm, &lhs);
        EclCore_PushInt(vm, lhs & rhs);
        return kEclCoreAdvance;
    }

    // ---- 0x4E  post-decrement -------------------------------------------
    // loc_44F86A.  Resolve operand 0 as a value, resolve the SAME operand as a
    // writable slot through 0x00450030, store value-1, and push the ORIGINAL
    // value (`mov [var],edi` happens before `dec edi`).  Retail dereferences
    // the destination with no null check; 0x00450030 returns 0 when operand
    // 0's mask bit is clear.  All 14 stage01 sites set the bit.
    case 0x4E: {
        const int value = EclCore_ResolveIntOperand(vm, 0);
        int* destination = (int*)ECL_ResolveVariableValue(vm, 0);
        *destination = value - 1;
        EclCore_PushInt(vm, value);
        return kEclCoreAdvance;
    }

    // ---- 0x4F  sin ------------------------------------------------------
    // `fld / fsin / fstp dword` - an x87 instruction, not a CRT call.  sinf()
    // is the tree's existing stand-in (ECL_SetPolarVector does the same); it
    // is NOT bit-exact, because retail evaluates at 80 bits and rounds once.
    // Retail also never inspects C2, so for |x| >= 2^63 fsin leaves the
    // operand unchanged where sinf would not.
    case 0x4F: {
        float angle;
        EclCore_PopFloat(vm, &angle);
        EclCore_PushFloat(vm, sinf(angle));
        return kEclCoreAdvance;
    }

    // ---- 0x50  cos ------------------------------------------------------
    // Shares 0x4F's push tail at loc_44F934.  Same fcos caveat.
    case 0x50: {
        float angle;
        EclCore_PopFloat(vm, &angle);
        EclCore_PushFloat(vm, cosf(angle));
        return kEclCoreAdvance;
    }

    // ---- 0x51  polar to vector ------------------------------------------
    // loc_44F94B.  Four operands: +0x10 destination x, +0x14 destination y,
    // +0x18 angle, +0x1C magnitude.  Retail's order is magnitude, angle,
    // wrap, polar, then the two destinations.  Every 0x51 in th10.dat is 32
    // bytes with param_mask 0xF, so the unchecked stores below never fire on
    // shipped data.
    case 0x51: {
        const float magnitude = EclCore_ResolveFloatOperand(vm, 3);
        const float angle = Angle_Normalize(EclCore_ResolveFloatOperand(vm, 2));
        float vector[2];
        ECL_SetPolarVector(vector, angle, magnitude);          // 0x004501B0
        if (hooks->resolve_float_destination == 0)
            Runtime_MissingEdge(0x00450070u, "ecl/core 0x51: 0x00450070");
        *hooks->resolve_float_destination(vm, 0) = vector[0];
        *hooks->resolve_float_destination(vm, 1) = vector[1];
        return kEclCoreAdvance;
    }

    // ---- 0x52  wrap an angle in place -----------------------------------
    // loc_44F9EE.  One operand used as BOTH destination and source, and the
    // destination pointer is resolved FIRST.
    case 0x52: {
        if (hooks->resolve_float_destination == 0)
            Runtime_MissingEdge(0x00450070u, "ecl/core 0x52: 0x00450070");
        float* destination = hooks->resolve_float_destination(vm, 0);
        *destination = Angle_Normalize(EclCore_ResolveFloatOperand(vm, 0));
        return kEclCoreAdvance;
    }

    // ---- 0x53  wait ------------------------------------------------------
    // loc_44E41E: `fild var / fsubr dword [esi] / fstp dword [esi]`.  The
    // clock at vm+0x00 moves BACKWARDS by the operand; the walk then advances
    // vm+0x04 and the time gate parks the VM until the clock catches up.
    case 0x53: {
        const int frames = EclCore_ResolveIntOperand(vm, 0);
        vm->time = (float)(vm->time - (double)frames);         // vm+0x00
        return kEclCoreAdvance;
    }

    // ---- 0x54  integer negate --------------------------------------------
    // loc_44F7A3.  This pop is NOT the shared float-flavoured one: it tests
    // only for 'f' and has no 'i' arm, so any other tag negates the raw dword.
    // The result is pushed with the INT tag.
    case 0x54: {
        int value;                          // intentionally uninitialised
        int top = vm->scratch_top - 4;                          // vm+0x1008
        if (top >= 0) {
            vm->scratch_top = top;
            const unsigned int raw = *(const unsigned int*)(vm->scratch + top);
            value = (int)raw;
            top -= 4;
            vm->scratch_top = top;                              // unguarded
            if (*(const char*)(vm->scratch + top) == 'f')
                value = (int)EclCore_BitsFloat(raw);            // __ftol2
        }
        EclCore_PushInt(vm, -value);
        return kEclCoreAdvance;
    }

    // ---- 0x55  "float negate" --------------------------------------------
    // loc_44F812.  RETAIL QUIRK, reproduced deliberately - do NOT rewrite this
    // as -value.  The negation at loc_44F851 is `neg edx`: a two's-complement
    // negate of the 32-bit pattern, and the result is pushed tagged 'f'.  For
    // a float that is not a sign flip (1.0f = 0x3F800000 negates to
    // 0xC0800000 = -4.0f).  There is no fchs and no sign-bit xor anywhere in
    // the case.  The 'i' arm converts int->float first and then hits the same
    // integer negate, so the result is wrong for both tags.  All three sources
    // agree: IDA `LODWORD(v265) = -LODWORD(v227)`, Ghidra
    // `local_fc = (float)-(int)local_fc`, and the listing above.
    case 0x55: {
        float slot;                         // intentionally uninitialised
        EclCore_PopFloat(vm, &slot);
        EclCore_PushFloat(
            vm, EclCore_BitsFloat((unsigned int)(-(int)EclCore_FloatBits(slot))));
        return kEclCoreAdvance;
    }

    // ---- 0x56  sum of squares --------------------------------------------
    // loc_44F9AC.  Three operands: +0x10 destination, +0x14 and +0x18 sources.
    // There is NO square root - the listing is fld/fmul/fld/fmul/faddp and
    // nothing else - so this writes a squared length.  Retail squares the
    // second source first and adds the first source's square into it; written
    // in that order to keep the x87 rounding sequence.
    case 0x56: {
        const float a = EclCore_ResolveFloatOperand(vm, 1);
        const float b = EclCore_ResolveFloatOperand(vm, 2);
        if (hooks->resolve_float_destination == 0)
            Runtime_MissingEdge(0x00450070u, "ecl/core 0x56: 0x00450070");
        *hooks->resolve_float_destination(vm, 0) = b * b + a * a;
        return kEclCoreAdvance;
    }

    // ---- 0x57  atan2 of two points ---------------------------------------
    // loc_44FA12.  Reads operands 0..3 as sources and then resolves operand 0
    // AGAIN as the destination, so the instruction overwrites its own first
    // argument: op0 = atan2(op3 - op1, op2 - op0).  All four reads complete
    // before the destination is resolved, so there is no aliasing hazard - but
    // the self-overwrite is real.  UNVERIFIABLE AGAINST DATA: opcode 0x57 does
    // not occur in any of th10.dat's eight ECL files, so a plausible off-by-one
    // in ZUN's source (dst, x1, y1, x2, y2 at indices 0..4) cannot be ruled
    // out.  Recovered as the binary reads, not "corrected".
    case 0x57: {
        const float x2 = EclCore_ResolveFloatOperand(vm, 2);
        const float dx = x2 - EclCore_ResolveFloatOperand(vm, 0);
        const float y2 = EclCore_ResolveFloatOperand(vm, 3);
        const float dy = y2 - EclCore_ResolveFloatOperand(vm, 1);
        // `fld dx / fpatan` == atan2(dy, dx).
        const float angle = (float)atan2((double)dy, (double)dx);
        if (hooks->resolve_float_destination == 0)
            Runtime_MissingEdge(0x00450070u, "ecl/core 0x57: 0x00450070");
        *hooks->resolve_float_destination(vm, 0) = angle;
        return kEclCoreAdvance;
    }

    // 0x02-0x09, 0x16-0x1D, 0x1F-0x27 and 0x2E-0x31 are NOT case labels.
    // They take the extended-dispatch arm exactly like opcodes >= 0x100.
    default:
        break;
    }
    return kEclCoreUnhandled;
}

}  // namespace

// ---------------------------------------------------------------------------
// The walk.  Retail lays this out as prologue / gate / switch / advance /
// time test / epilogue with five exits; the switch bodies above are a
// presentation split, not a retail boundary.
// ---------------------------------------------------------------------------
int EclVm_TickCore(EclCoreVm* vm, float frame_delta, const EclCoreHooks* hooks) {
    // --- prologue -----------------------------------------------------------
    // A null instruction pointer is retail's "this VM is done".
    if (vm->ip == 0)                                           // vm+0x04
        return kEclCoreFinished;

    // Retail widens the int32 instruction time to an x87 double and compares
    // it against the float clock at vm+0x00.  If the next instruction is not
    // due yet the entire walk is skipped.
    if ((double)vm->ip->time > (double)vm->time) {
        vm->time = frame_delta + vm->time;                     // LABEL_297
        return kEclCoreRunning;
    }

    for (;;) {
        EclCoreInstruction* instruction = vm->ip;   // vm+0x04, re-read per pass

        int action = kEclCoreAdvance;

        // Rank gate: instruction+0x0A AND vm+0x101C.  A zero result is not an
        // error: retail falls straight into the advance path and skips the
        // instruction without executing anything.
        if ((instruction->rank_mask & vm->rank_mask) != 0) {
            // The selector is read sign-extended (movsx) and then compared
            // unsigned against 0x57, so every opcode >= 0x58 - the 0x100+
            // family included - takes the default arm.
            const int opcode = instruction->opcode & 0xFFFF;
            if (hooks->trace_opcode != 0)
                hooks->trace_opcode(vm, instruction);

            action = kEclCoreUnhandled;
            if ((unsigned int)opcode <= 0x57u)
                action = EclCore_ExecuteOpcode(vm, instruction, opcode, hooks);

            if (action == kEclCoreUnhandled) {
                // default arm: slot 0 of the vtable at vm+0x1014, retail
                // 0x0040E770.
                const int dispatched = hooks->dispatch_extended != 0
                    ? hooks->dispatch_extended(vm->owner)
                    : vm->owner->vtable->DispatchExtendedOpcode(vm->owner);
                // Only -1 is special-cased; every other value advances.  What
                // else 0x0040E770 can return is not determined by this
                // function.
                if (dispatched == -1)
                    return kEclCoreRunning;   // note: the clock is NOT advanced
                action = kEclCoreAdvance;
            }
        }

        if (action == kEclCoreStop)
            return kEclCoreFinished;
        if (action == kEclCoreYield)
            return kEclCoreRunning;

        // --- advance ---------------------------------------------------------
        if (action == kEclCoreAdvance) {
            // LABEL_294 reloads vm+0x04 here rather than reusing the pointer
            // captured at the top of the pass, because a body may have
            // replaced it (opcode 0x0A does).  LABEL_295 then adds the
            // *current* instruction's own +0x06 size, in bytes.  Retail has no
            // guard against a zero size, and none is added here.
            EclCoreInstruction* current = vm->ip;
            const unsigned int size = current->size;
            vm->ip = (EclCoreInstruction*)((unsigned char*)current + size);
        }
        // kEclCoreRetest lands here directly - LABEL_296.

        // --- time gate -------------------------------------------------------
        if ((double)vm->ip->time > (double)vm->time) {
            vm->time = frame_delta + vm->time;                 // LABEL_297
            return kEclCoreRunning;
        }
    }
}

// ---------------------------------------------------------------------------
// The four edges the switch reaches through EclCoreHooks.  All recovered from
// ida/th10.exe.c with the .asm as the instruction-level cross-check; the
// rejected alternative models (ecl_vm_children.cpp / ecl_vm.cpp) are left in
// place for their tests but are no longer candidates for binding.
// ---------------------------------------------------------------------------

namespace {

// Retail 0x00450470's binary search is implemented canonically in
// src/script/final_script_runtime.cpp; this edge adapts the typed ECL core
// table and delegates to the shared search helper.
EclCoreInstruction* EclCore_ResolveScriptLabel(
    const EclCoreScriptTable* table, const char* name) {
    const EclCoreScriptEntry* entry =
        th10::script_label_search::FindScriptLabelEntry<EclCoreScriptTable,
                                                         EclCoreScriptEntry>(
            table, name);
    return entry == nullptr
               ? 0
               : (EclCoreInstruction*)((char*)entry->code + 16);
}

}  // namespace

// 0x0044DF70 - EclCore_StartChild.
//
// Retail layout of the marshalled return frame in the child's scratch:
//   first call   scratch[0..3] = 0 (the zero/return word), scratch[4..7] = 0,
//                scratch[8..11] = parent->ip, args at scratch[12..]
//   nested call  scratch[T..T+3] = parent->time bits, scratch[T+4..T+7] =
//                parent->ip, args at scratch[T+8..]  (T = scratch_top)
// The callee's locals prologue (0x00450690) sets locals_offset to the old
// scratch_top, so the args must sit exactly at the post-push top.
//
// On the host the ip slot holds a full pointer (the ret, opcode 0x0A, reads
// it back as one), so the frame grows by sizeof(void*)-4 per ip slot: the
// zero/ip pushes are pointer-width and the args move to scratch[8+ptr] /
// scratch[T+4+ptr].  A 32-bit build degenerates to the retail layout
// exactly.  The dead re-store of the popped return word at scratch[T-4..T-1]
// (retail reads and writes the same dword; on the host it is a no-op over
// the caller's last marshalled arg) is reproduced.
int EclCore_StartChild(EclCoreVm* child, EclCoreVm* parent,
                       int first_argument) {
    const int original_top = child->scratch_top;               // v5
    const EclCoreInstruction* instruction = parent->ip;        // *v3
    // v6: byte offset from instruction+0x10 to the first record to marshal.
    // *(instruction+0x10) is the sub name's length dword; each consumed
    // argument (first_argument of them) sits in one 4-byte word, plus one
    // word for the name's own length.
    int offset = *(const int*)((const unsigned char*)instruction + 0x10) +
                 4 * first_argument + 4;
    int saved_popped = 0;                                      // v24
    int destination_offset;                                    // v7
    if (original_top == 0) {
        *(int*)(child->scratch + 0) = 0;                       // a1[2] = 0
        child->scratch_top += 4;
        destination_offset = 8 + (int)sizeof(void*);
    } else {
        destination_offset = original_top + 4 + (int)sizeof(void*);
    }

    // Argument marshalling: 8-byte records, type byte at +0, store-kind byte
    // at +1, raw value at +4.  'f'/'g' resolve as float, everything else as
    // int; a store-kind of 'f' stores a float, anything else an int.
    int arg_index = first_argument + 1;                        // v8
    if (arg_index < instruction->param_count) {
        int cursor = offset + 4;                               // v9
        float* destination = (float*)(child->scratch + destination_offset);
        for (;;) {
            const unsigned char* record =
                (const unsigned char*)instruction + 0x10 + offset;
            const unsigned char resolve_kind = record[0];
            const unsigned char store_kind = record[1];
            const int word_index = cursor >> 2;
            if (resolve_kind == 102 || resolve_kind == 103) {  // 'f' / 'g'
                const float raw = *(const float*)(
                    (const unsigned char*)instruction + 0x10 +
                    4 * word_index);
                const float resolved =
                    ECL_ResolveFloatValue(parent, (unsigned)arg_index, raw);
                if (store_kind == 102)
                    *destination = resolved;
                else
                    *(int*)destination = (int)resolved;
            } else {
                const int raw = *(const int*)(
                    (const unsigned char*)instruction + 0x10 +
                    4 * word_index);
                const int resolved =
                    ECL_ResolveIntValue(parent, (unsigned)arg_index, raw);
                if (store_kind == 102)
                    *destination = (float)resolved;
                else
                    *(int*)destination = resolved;
            }
            ++destination;
            ++arg_index;
            offset += 8;
            cursor += 8;
            if (arg_index >= instruction->param_count)
                break;
        }
    }

    // Return-frame push.  First call: two zero dwords, then parent->ip as a
    // full host pointer.  Nested: pop the previous return word (re-stored
    // dead), then push parent->time bits and parent->ip.
    if (original_top == 0) {
        child->scratch_top = 4;                                // a1[1026] = 4
        *(int*)(child->scratch + 4) = 0;                       // a1[3] = 0
        child->scratch_top += 4;
        const int v17 = child->scratch_top;
        if (v17 + (int)sizeof(void*) < 4096) {
            *(EclCoreInstruction**)(child->scratch + v17) =
                parent->ip;                                    // LABEL_24
            child->scratch_top += (int)sizeof(void*);
        }
    } else {
        const int v15 = child->scratch_top - 4;
        if (v15 >= 0) {
            child->scratch_top = v15;
            saved_popped = *(int*)(child->scratch + v15);
        }
        child->scratch_top = original_top;
        *(int*)(child->scratch + original_top - 4) = saved_popped;
        const int v16 = child->scratch_top;
        if (v16 + 4 < 4096) {
            int time_bits;
            memcpy(&time_bits, parent, sizeof(time_bits));   // *a2, raw bits
            *(int*)(child->scratch + v16) = time_bits;
            child->scratch_top += 4;
        }
        const int v17 = child->scratch_top;
        if (v17 + (int)sizeof(void*) < 4096) {
            *(EclCoreInstruction**)(child->scratch + v17) =
                parent->ip;
            child->scratch_top += (int)sizeof(void*);
        }
    }

    // Callee bind: the call instruction's sub name sits at ip+0x14.  Retail
    // publishes the resolved entry through owner->current_record (the same
    // {name, resolved} record 0x00450700 writes) with the child temporarily
    // installed as the record, then restores the previous record.  The
    // resolved value lands in child->ip, so the child's next tick enters the
    // callee.
    EclCoreOwner* owner = parent->owner;
    EclCoreVm* saved_record = owner->current_record;           // v20
    owner->current_record = child;
    const EclCoreInstruction* resolved = EclCore_ResolveScriptLabel(
        owner->script_table, (const char*)instruction + 0x14);
    child->ip = (EclCoreInstruction*)resolved;
    child->time = 0.0f;
    if (resolved != 0) {
        owner->current_record = saved_record;
        return 0;
    }
    parent->ip = 0;                                            // *v3 = 0
    return -1;
}

// 0x004500D0 - EclCore_SpawnChild.
int EclCore_SpawnChild(EclCoreOwner* owner, int async_id,
                       int first_argument) {
    EclCoreVm* child = new EclCoreVm;
    if (child != 0) {
        child->scratch_top = 0;                                // v3[1026]
        child->locals_offset = 0;                              // v3[1027]
    }
    EclCoreChildLink* link = new EclCoreChildLink;
    if (child == 0 || link == 0) {
        // Retail writes through the null allocations here; the host guards
        // instead and reports the failure.
        delete link;
        delete child;
        return -1;
    }
    child->async_id = async_id;                                // v4[1028]
    child->owner = owner;                                      // v4[1029]
    child->time = 0.0f;                                        // *v4
    child->ip = 0;                                             // v4[1]
    child->rank_mask = owner->current_record->rank_mask;
    // (Retail copies the byte at +0x101C of the active record; the typed
    // member keeps the wider host layout self-consistent.)
    link->vm = child;                                          // *v5
    link->next = 0;
    link->previous = 0;
    EclCoreChildLink* head = owner->child_list.next;           // *(a1+0x1034)
    if (head != 0) {
        link->next = head;
        head->previous = link;
    }
    owner->child_list.next = link;                             // *(a1+0x1034)
    link->previous = &owner->child_list;                       // a1+0x1030
    return EclCore_StartChild(child, owner->current_record,
                              first_argument);
}

// 0x00450160 - EclCore_FindChild.
EclCoreChildLink* EclCore_FindChild(EclCoreOwner* owner, int async_id) {
    // Retail starts the walk at the anchor address (owner+0x1030) and tests
    // the anchor's own vm slot first; the spawner never writes that slot, so
    // the guarded test below treats it as empty.  The observable search - the
    // first linked child whose async_id matches - is identical.
    EclCoreChildLink* link = &owner->child_list;
    while (link != 0) {
        if (link->vm != 0 && link->vm->async_id == async_id)
            return link;
        link = link->next;
    }
    return 0;
}

// 0x00450070 - EclCore_ResolveFloatDestination.
float* EclCore_ResolveFloatDestination(EclCoreVm* vm,
                                       unsigned int operand) {
    if ((vm->ip->param_mask & (1u << (operand & 31))) == 0)
        return 0;
    const float raw =
        *(const float*)((const unsigned char*)vm->ip + 0x10 + 4 * operand);
    if (raw >= 0.0f) {
        // Local slot: vm scratch base + locals_offset + truncated offset.
        // (Retail hardcodes +8 from the record base; the typed member keeps
        // the host layout, with its wider ip pointer, self-consistent.)
        return (float*)(vm->scratch + vm->locals_offset + (int)raw);
    }
    // External slot: vtable slot 4 of the object at vm+0x1014 returns the
    // destination for the truncated negative index.
    const EclCoreOwnerVtable* vtable = *(const EclCoreOwnerVtable**)vm->owner;
    return (float*)vtable->ResolveExternalFloat((int)raw);
}
