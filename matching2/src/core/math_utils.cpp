// =============================================================================
// math_utils.cpp - Timer, vector math, and utility functions
// Functions: 0x00405410 (Timer_Set), 0x004050d0 (Timer_Reset),
//            0x00404ED0 (Timer_Tick), 0x00405B60 (ClampValue),
//            0x00404DA0 (Vec_Scale), 0x00404E10 (Vec_Add)
// =============================================================================
#include "th10/entity.hpp"

extern uint32_t DAT_00476f78;     // sentinel
extern float    _DAT_00470afc;    // 1.0f
extern float    _DAT_00470b68;    // bounds min
extern float    _DAT_00470b64;    // bounds max
extern "C" uint32_t FUN_00463b2c(void);  // rand

// ============================================================================
// Timer/Scheduler structure (20 bytes = 5 dwords)
// +0x00: current_value (int32)
// +0x04: target_value (int32)
// +0x08: float_value  (float)
// +0x0C: ptr          (void*)
// +0x10: flags        (uint32, bit 0 = initialized)
// ============================================================================

// ============================================================================
// 0x00405410 - Timer_Set: Initialize timer with target frame count
// EAX = timer ptr, param_1 (stack) = target frame count
// __cdecl with EAX input (non-standard)
// 67 cross-references — most used utility function in the game
//
// Disassembly:
//   MOV ECX,[EAX+0x10]    ; flags
//   TEST CL,1             ; initialized?
//   PUSH ESI
//   MOV ESI,[ESP+8]       ; param_1 (target)
//   JNZ skip_init
//   XOR EDX,EDX; OR ECX,1
//   [EAX+4]=0; [EAX]=0xFFF0BDC1; [EAX+8]=0; [EAX+0xC]=0x476F78; [EAX+0x10]=ECX
// skip_init:
//   FILD [ESP+8]          ; load target as float
//   [EAX+4]=ESI           ; target_value = param_1
//   DEC ESI; [EAX]=ESI    ; current = target - 1
//   FSTP [EAX+8]          ; float_value = (float)target
//   POP ESI; RET 4        ; stdcall cleanup (1 param)
// ============================================================================
__declspec(naked) void __stdcall Timer_Set(int target) {
    __asm {
        mov ecx, [eax + 0x10]
        test cl, 1
        push esi
        mov esi, [esp + 8]
        jnz skip_init
        xor edx, edx
        or ecx, 1
        mov [eax + 0x4], edx
        mov dword ptr [eax], 0xfff0bdc1
        mov [eax + 0x8], edx
        mov dword ptr [eax + 0xc], 0x476f78
        mov [eax + 0x10], ecx
    skip_init:
        fild dword ptr [esp + 8]
        mov [eax + 0x4], esi
        dec esi
        mov [eax], esi
        fstp dword ptr [eax + 0x8]
        pop esi
        ret 4
    }
}

// ============================================================================
// 0x004050D0 - Timer_Reset: Reset timer to inactive state
// EAX = timer ptr (offsets +0x30..+0x40 variant)
//
// Disassembly:
//   MOV ECX,[EAX+0x40]   ; flags
//   XOR EDX,EDX
//   TEST CL,1; JNZ skip
//   OR ECX,1; init +0x34=0, +0x30=0xFFF0BDC1, +0x38=0, +0x3C=0x476F78, +0x40=ECX
// skip:
//   +0x34=0, +0x38=0, +0x30=0xFFFFFFFF
//   RET
// ============================================================================
__declspec(naked) void Timer_Reset(void) {
    __asm {
        mov ecx, [eax + 0x40]
        xor edx, edx
        test cl, 1
        jnz skip_init
        or ecx, 1
        mov [eax + 0x34], edx
        mov dword ptr [eax + 0x30], 0xfff0bdc1
        mov [eax + 0x38], edx
        mov dword ptr [eax + 0x3c], 0x476f78
        mov [eax + 0x40], ecx
    skip_init:
        mov [eax + 0x34], edx
        mov [eax + 0x38], edx
        mov dword ptr [eax + 0x30], 0xffffffff
        ret
    }
}

// ============================================================================
// 0x00404ED0 - Timer_Tick: Advance timer by one frame
// ESI = timer ptr (unaff_ESI — set by caller)
// Checks if current time pointer is within bounds, increments counter
//
// Disassembly:
//   MOV EDX,[ESI+4]       ; current target
//   MOV ECX,[ESI+0xC]     ; time pointer
//   MOV [ESI],EDX         ; prev = current
//   FLD [ECX]; FCOMP [0x470B68]; FNSTSW AX; TEST AH,0x41; JNZ out_of_bounds
//   FLD [ECX]; FCOMP [0x470B64]; FNSTSW AX; TEST AH,0x5; JP out_of_bounds
//   FLD [ESI+8]; INC EDX; FADD [0x470AFC]; MOV [ESI+4],EDX; FSTP [ESI+8]; RET
// out_of_bounds:
//   FLD [ECX]; FADD [ESI+8]; FST [ESI+8]; CALL 0x463B2C; MOV [ESI+4],EAX; RET
// ============================================================================
__declspec(naked) void Timer_Tick(void) {
    __asm {
        mov edx, [esi + 0x4]
        mov ecx, [esi + 0xc]
        mov [esi], edx
        fld dword ptr [ecx]
        _emit 0xD8
        _emit 0x1D
        _emit 0x68
        _emit 0x0B
        _emit 0x47
        _emit 0x00
        fnstsw ax
        test ah, 0x41
        jnz out_of_bounds
        fld dword ptr [ecx]
        _emit 0xD8
        _emit 0x1D
        _emit 0x64
        _emit 0x0B
        _emit 0x47
        _emit 0x00
        fnstsw ax
        test ah, 0x5
        jp out_of_bounds
        fld dword ptr [esi + 0x8]
        inc edx
        _emit 0xD8
        _emit 0x05
        _emit 0xFC
        _emit 0x0A
        _emit 0x47
        _emit 0x00
        mov [esi + 0x4], edx
        fstp dword ptr [esi + 0x8]
        ret
    out_of_bounds:
        fld dword ptr [ecx]
        fadd dword ptr [esi + 0x8]
        fst dword ptr [esi + 0x8]
        call FUN_00463b2c
        mov [esi + 0x4], eax
        ret
    }
}

// ============================================================================
// 0x00405B60 - ClampValue: Add delta to value, clamp to [-0x400, 0x400]
// EAX = struct ptr, ECX = delta (int32)
// __fastcall with EAX input
//
// Disassembly:
//   MOV EDX,[EAX+0x58]; ADD EDX,ECX; MOV ECX,EDX
//   CMP ECX,0x400; MOV [EAX+0x58],EDX; JLE check_min
//   MOV [EAX+0x58],0x400; RET
// check_min:
//   CMP ECX,0xFFFFFC00; JGE done
//   MOV [EAX+0x58],0xFFFFFC00
// done: RET
// ============================================================================
__declspec(naked) void __fastcall ClampValue(int delta) {
    __asm {
        mov edx, [eax + 0x58]
        add edx, ecx
        mov ecx, edx
        cmp ecx, 0x400
        mov [eax + 0x58], edx
        jle check_min
        mov dword ptr [eax + 0x58], 0x400
        ret
    check_min:
        cmp ecx, 0xfffffc00
        jge done
        mov dword ptr [eax + 0x58], 0xfffffc00
    done:
        ret
    }
}

// ============================================================================
// 0x00404DA0 - Vec_Scale: Multiply 6-float vector by scalar, fill 4 random bytes
// EAX = src vector (6 floats), ESI = dst, param_1 (stack) = scalar
// Also calls rand 4 times for bytes at dst+0x18..0x1B
// Returns ESI
//
// Disassembly (FPU heavy):
//   FLD [ESP+4]; FMUL [EAX+0x14]  ; scalar * src[5]
//   FLD [ESP+4]; FMUL [EAX+0x10]  ; scalar * src[4]
//   FLD [ESP+4]; FMUL [EAX+0xC]   ; scalar * src[3]
//   FLD [ESP+4]; FMUL [EAX+8]     ; scalar * src[2]
//   FLD [ESP+4]; FMUL [EAX+4]     ; scalar * src[1]
//   FLD [ESP+4]; FMUL [EAX]       ; scalar * src[0]
//   FSTP [ESI]; FSTP [ESI+4]; FST [ESI+8]
//   FLD ST1; FSTP [ESI+0xC]
//   FLD ST2; FSTP [ESI+0x10]
//   FLD ST3; FSTP [ESI+0x14]
//   CALL rand; MOV [ESI+0x18],AL
//   CALL rand; MOV [ESI+0x19],AL
//   CALL rand; MOV [ESI+0x1A],AL
//   CALL rand; MOV [ESI+0x1B],AL
//   MOV EAX,ESI; RET 4
// ============================================================================
__declspec(naked) void* __stdcall Vec_Scale(float scalar) {
    __asm {
        fld dword ptr [esp + 4]
        fmul dword ptr [eax + 0x14]
        fld dword ptr [esp + 4]
        fmul dword ptr [eax + 0x10]
        fld dword ptr [esp + 4]
        fmul dword ptr [eax + 0xc]
        fld dword ptr [esp + 4]
        fmul dword ptr [eax + 8]
        fld dword ptr [esp + 4]
        fmul dword ptr [eax + 4]
        fld dword ptr [esp + 4]
        fmul dword ptr [eax]
        fstp dword ptr [esi]
        fstp dword ptr [esi + 4]
        fst dword ptr [esi + 8]
        fld st(1)
        fstp dword ptr [esi + 0xc]
        fld st(2)
        fstp dword ptr [esi + 0x10]
        fld st(3)
        fstp dword ptr [esi + 0x14]
        call FUN_00463b2c
        mov byte ptr [esi + 0x18], al
        call FUN_00463b2c
        mov byte ptr [esi + 0x19], al
        call FUN_00463b2c
        mov byte ptr [esi + 0x1a], al
        call FUN_00463b2c
        mov byte ptr [esi + 0x1b], al
        mov eax, esi
        ret 4
    }
}

// ============================================================================
// 0x00404E10 - Vec_Add: Add two 6-float vectors, fill 4 random bytes
// EAX = src vector, param_1 (fastcall ECX?) = second vector, ESI = dst
// Also calls rand 4 times for bytes at dst+0x18..0x1B
//
// Disassembly would be similar to Vec_Scale but with FADD instead of FMUL
// ============================================================================
// (Similar FPU pattern — documented asm, same rand byte fill)
