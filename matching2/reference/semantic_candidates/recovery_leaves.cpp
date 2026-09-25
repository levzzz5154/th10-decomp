// Readable models removed from matching2/msvc/src/game/recovery_leaves.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include <string.h>
#include <math.h>
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// The raw-pair release uses one stack argument and callee cleanup, matching the
// retail stdcall entry. Keep the callback type explicit at this call site.
typedef void (__stdcall* RawPairReleaseFn)(void* pair);

// Ghidra confirms __thiscall with angle, horizontal scale and vertical scale
// on the stack, in that order. The stores target this+0 then this+4.
struct EllipticPolarVector2_00413270 {
    float x;
    float y;

    __declspec(noinline) void SetEllipticPolar(
        float angle, float horizontalScale, float verticalScale);
};

// 0x00413270..0x0041328D: Vector2_SetEllipticPolar
void EllipticPolarVector2_00413270::SetEllipticPolar(
    float angle, float horizontalScale, float verticalScale) {
    x = cosf(angle) * horizontalScale;
    y = sinf(angle) * verticalScale;
}

// 0x004198C0..0x00419921: Recovery_FindNamedValue
// The table layout is only the observed pair of a key pointer and 32-bit value.
struct RecoveryNamedValueRecord_004198C0 {
    const char* key;
    unsigned int value;
};

// ECX is retained as an ignored first fastcall parameter so key stays in EDX;
// callers leave parser-local values there, and the retail body never reads it.
extern "C" unsigned int __fastcall asm_Recovery_FindNamedValue_004198c0(
    unsigned int ignoredEcX,
    const char* key,
    const RecoveryNamedValueRecord_004198C0* records,
    int recordCount) {
    (void)ignoredEcX;

    for (int index = 0; index < recordCount; ++index) {
        const unsigned char* query =
            reinterpret_cast<const unsigned char*>(key);
        const unsigned char* candidate =
            reinterpret_cast<const unsigned char*>(records[index].key);

        while (*query != 0 && *query == *candidate) {
            ++query;
            ++candidate;
        }
        if (*query == *candidate) {
            return records[index].value;
        }
    }
    return 0;
}

// The manager pointer is stored at data_00491c10. The fastcall resource
// loader uses ECX=id, EDX=manager, and a stack name; the variadic log member
// uses ECX=this and a stack message, matching the recovered call sites.
struct CachedResource;

CachedResource* __fastcall Recovery_LoadCachedResource(
        int index, void* owner, const char* name);

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

// 0x0041F8D0..0x0041F921: ?Recovery_LoadStartupResources@@
extern "C" __declspec(noinline) int __cdecl
asm_Recovery_LoadStartupResources_0041f8d0() {
    CachedResource* front = Recovery_LoadCachedResource(
            6, *reinterpret_cast<void**>(&data_00491c10),
            reinterpret_cast<const char*>(0x0046D254));
    if (front == 0) {
        ((TextLog_0044b810*)0x00474F70)->Append(
                reinterpret_cast<char*>(0x0046CB68));
        return -1;
    }

    CachedResource* bullet = Recovery_LoadCachedResource(
            7, *reinterpret_cast<void**>(&data_00491c10),
            reinterpret_cast<const char*>(0x0046CD88));
    if (bullet == 0) {
        ((TextLog_0044b810*)0x00474F70)->Append(
                reinterpret_cast<char*>(0x0046CD54));
        return -1;
    }

    return 0;
}

// 0x0043CB00..0x0043CB7E: ?Recovery_ReleaseRawPair@@
// The pair is passed on the stack; scheduler removal uses ECX=entry, EDX=scheduler.
extern "C" void __stdcall asm_Recovery_ReleaseRawPair_0043cb00(void* pair) {
    typedef void (__stdcall *CriticalSectionCallback)(void* section);
    typedef void (__fastcall *SchedulerRemoveCallback)(void* entry,
                                                        void* scheduler);

    CriticalSectionCallback enterCriticalSection =
        *reinterpret_cast<CriticalSectionCallback*>(&data_004660b0);
    CriticalSectionCallback leaveCriticalSection =
        *reinterpret_cast<CriticalSectionCallback*>(&data_004660b4);
    SchedulerRemoveCallback removeScheduledEntry =
        reinterpret_cast<SchedulerRemoveCallback>(asm_Scheduler_Remove_00449f60);
    void* criticalSection = reinterpret_cast<void*>(0x00492274);
    void** pairFields = reinterpret_cast<void**>(pair);
    void* firstEntry = pairFields[2];
    void* scheduler = *reinterpret_cast<void**>(&data_00491be4);
    if (firstEntry != 0) {
        enterCriticalSection(criticalSection);
        ++data_0049231c;
        removeScheduledEntry(firstEntry, scheduler);
        leaveCriticalSection(criticalSection);
        --data_0049231c;
    }

    void* secondEntry = pairFields[3];
    scheduler = *reinterpret_cast<void**>(&data_00491be4);
    if (secondEntry != 0) {
        enterCriticalSection(criticalSection);
        ++data_0049231c;
        removeScheduledEntry(secondEntry, scheduler);
        leaveCriticalSection(criticalSection);
        --data_0049231c;
    }
}

// 0x00441EF0..0x00441F0D: Vector2_SetAnimationPolar
// Retail uses __thiscall: ECX is the receiver, angle and length are stack
// floats, and the callee removes both arguments with RET 8. Its single
// FSINCOS instruction is not reproduced by this ordinary C++ math spelling.
struct AnimationPolarVector2_00441EF0 {
    float x;
    float y;

    __declspec(noinline) void SetAnimationPolar(float angle, float length);
};

void AnimationPolarVector2_00441EF0::SetAnimationPolar(float angle,
                                                        float length) {
    x = cosf(angle) * length;
    y = sinf(angle) * length;
}
