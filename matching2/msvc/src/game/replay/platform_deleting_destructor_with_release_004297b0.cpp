// 0x004297B0..0x004297C1: destroy a platform resource after releasing the
// resources it owns. Retail passes the resource pointer in ESI:
//
//   test esi,esi / je done
//   push esi / call Platform_ReleaseResources (0x004294A0, __stdcall)
//   push esi / call operator delete (0x004524A1, __cdecl)
//   pop ecx / done: ret
//
// The native-LTCG cluster gives this ordinary C++ function the same internal
// register convention. Its synthetic caller keeps the pointer live across
// both calls, which is what makes MSVC choose ESI.

struct PlatformResource;

extern "C" __stdcall void Platform_ReleaseResources(PlatformResource* resource);
void __cdecl operator delete(void* memory);

__declspec(noinline) void PlatformResource_Destroy(PlatformResource* resource);

#pragma code_seg(".text$01destroy")
void PlatformResource_Destroy(PlatformResource* resource) {
    if (resource) {
        Platform_ReleaseResources(resource);
        operator delete(resource);
    }
}
#pragma code_seg()
