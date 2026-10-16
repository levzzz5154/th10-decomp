// 0x0040B9D0. Tear down a score-owned object: detach its registered animation,
// then release its storage. Retail passes the object in ESI:
//
//   L10: test esi,esi          ; 85 f6
//               je   L11       ; 74 0d
//               push esi              ; 56
//               call 0x0040B7B0       ; e8 d6 fd ff ff  (__stdcall: pops its own argument)
//               push esi              ; 56
//               call free             ; e8 c1 6a 04 00  (__cdecl: caller pops)
//               pop  ecx              ; 59
//   L11: ret                   ; c3
//
// 0x0040B7B0 unlinks the object from the animation manager under its lock; the
// release call is the statically linked CRT free at 0x004524A1. The body is
// compiled in the native LTCG cluster of build_support/layout/ltcg/score_owned_destroy.json,
// whose synthetic array caller keeps the pointer in ESI across both calls.

struct ScoreOwnedObject;

extern "C" void asm_FUN_0040b7b0_0040b7b0(void* object);      // 0x0040B7B0, __stdcall
extern "C" void __cdecl crt_free_startup(void* memory);    // 0x004524A1, __cdecl

__declspec(noinline) void ScoreOwnedObject_Destroy(ScoreOwnedObject* object);

#pragma code_seg(".text$01destroy")
void ScoreOwnedObject_Destroy(ScoreOwnedObject* object) {
    if (object) {
        asm_FUN_0040b7b0_0040b7b0(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
