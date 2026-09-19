#include <string.h>
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405D00..0x00405DD6: FUN_00405d00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405d00_00405d00() {
    __asm {
    L_00405d00:
        push ebx
    L_00405d01:
        mov ebx,ecx
    L_00405d03:
        mov eax,dword ptr [ebx+74h]
    L_00405d06:
        lea edx,[ebx+8]
    L_00405d09:
        push esi
    L_00405d0a:
        mov esi,0FFFFFFFEh
    L_00405d0f:
        and eax,esi
    L_00405d11:
        mov dword ptr [edx+6Ch],eax
    L_00405d14:
        push edi
    L_00405d15:
        and dword ptr [edx+0B0h],esi
    L_00405d1b:
        and dword ptr [edx+0FCh],esi
    L_00405d21:
        and dword ptr [edx+128h],esi
    L_00405d27:
        and dword ptr [edx+174h],esi
    L_00405d2d:
        and dword ptr [edx+1B0h],esi
    L_00405d33:
        and dword ptr [edx+1FCh],esi
    L_00405d39:
        and dword ptr [edx+228h],esi
    L_00405d3f:
        mov ecx,dword ptr [edx+378h]
    L_00405d45:
        xor eax,eax
    L_00405d47:
        and ecx,esi
    L_00405d49:
        mov dword ptr [edx+378h],ecx
    L_00405d4f:
        mov edi,edx
    L_00405d51:
        mov ecx,0EBh
    L_00405d56:
        rep stosd
    L_00405d58:
        mov word ptr [edx+384h],0FFFFh
    L_00405d61:
        and dword ptr [ebx+408h],esi
    L_00405d67:
        and dword ptr [ebx+41Ch],esi
    L_00405d6d:
        mov edx,dword ptr [ebx+624h]
    L_00405d73:
        lea eax,[ebx+614h]
    L_00405d79:
        add eax,34h
    L_00405d7c:
        and edx,esi
    L_00405d7e:
        mov dword ptr [eax-24h],edx
    L_00405d81:
        mov edi,dword ptr [eax+10h]
    L_00405d84:
        add eax,34h
    L_00405d87:
        and edi,esi
    L_00405d89:
        mov dword ptr [eax-24h],edi
    L_00405d8c:
        mov ecx,dword ptr [eax+10h]
    L_00405d8f:
        add eax,34h
    L_00405d92:
        and ecx,esi
    L_00405d94:
        mov dword ptr [eax-24h],ecx
    L_00405d97:
        mov edx,dword ptr [eax+10h]
    L_00405d9a:
        add eax,34h
    L_00405d9d:
        and edx,esi
    L_00405d9f:
        mov dword ptr [eax-24h],edx
    L_00405da2:
        and dword ptr [eax+10h],esi
    L_00405da5:
        mov ecx,dword ptr [eax+44h]
    L_00405da8:
        add eax,34h
    L_00405dab:
        and ecx,esi
    L_00405dad:
        mov dword ptr [eax+10h],ecx
    L_00405db0:
        mov edx,dword ptr [eax+44h]
    L_00405db3:
        add eax,34h
    L_00405db6:
        and edx,esi
    L_00405db8:
        mov dword ptr [eax+10h],edx
    L_00405dbb:
        mov edi,dword ptr [eax+44h]
    L_00405dbe:
        add eax,34h
    L_00405dc1:
        and edi,esi
    L_00405dc3:
        mov dword ptr [eax+10h],edi
    L_00405dc6:
        mov ecx,dword ptr [eax+44h]
    L_00405dc9:
        add eax,34h
    L_00405dcc:
        and ecx,esi
    L_00405dce:
        mov dword ptr [eax+10h],ecx
    L_00405dd1:
        mov eax,ebx
    L_00405dd3:
        pop edi
    L_00405dd4:
        pop esi
    L_00405dd5:
        pop ebx
    L_00405dd6:
        ret
    }
}


// Recovered semantic C++ definitions.
#include "th10/game/entity.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void* __cdecl operator_new(uint32_t);




// 0x00406160 / 0x004061D0 - Playfield culling tests. The retail ABI keeps the
// tested screen position in ECX and pushes the queried extents, so both are
// members of that position. Each returns 1 while a box of `width` x `height`
// centred on the position stays clear of the playfield rectangle; the
// inclusive variant tests the playfield proper (y from 0) instead of the band
// that starts 64 pixels above it.
//
// The rectangle and the half-size scale are the shared .rdata constants the
// renderer uses, so they are read through their retail addresses.
// Playfield rectangle and frame constants shared with the renderer.
extern float g_playfield_min_x;   // 0x00470B40, -192.0
extern float g_playfield_max_x;   // 0x00470B3C,  192.0
extern float g_playfield_min_y;   // 0x00470B04,    0.0
extern float g_playfield_max_y;   // 0x00470B38,  448.0

struct PlayfieldPoint {
    float x;
    float y;
    int32_t OutsidePlayfield(float width, float height) const;
    int32_t OutsidePlayfieldInclusive(float width, float height) const;
};

int32_t PlayfieldPoint::OutsidePlayfield(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= -64.0f || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

int32_t PlayfieldPoint::OutsidePlayfieldInclusive(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= g_playfield_min_y || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

// Clears the "registered with the animation list" bit of one slot flag word.
// The retail constructor reaches every flag through a pointer, which keeps the
// store in the read-modify-write form the image uses.
static void Entity_ClearRegistrationBit(uint32_t* flags) {
    *flags &= ~1u;
}

// 0x00402050 - Entity_Constructor: retire every animation slot's registration
// bit, wipe the entity and mark its sprite index unused. Returns the entity.
Entity* __fastcall Entity_Constructor(Entity* entity) {
    Entity_ClearRegistrationBit(&entity->flags_06C);
    Entity_ClearRegistrationBit(&entity->flags_0B0);
    Entity_ClearRegistrationBit(&entity->flags_0FC);
    Entity_ClearRegistrationBit(&entity->flags_128);
    Entity_ClearRegistrationBit(&entity->flags_174);
    Entity_ClearRegistrationBit(&entity->flags_1B0);
    Entity_ClearRegistrationBit(&entity->flags_1FC);
    Entity_ClearRegistrationBit(&entity->flags_228);
    Entity_ClearRegistrationBit(&entity->flags_378);
    memset(entity, 0, sizeof(Entity));
    entity->SpriteIndex() = -1;
    return entity;
}

void __fastcall Entity_Destructor(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->resource = 0;
}

void __fastcall EntitySecondaryResource_Release(Entity* entity) {
    void* resource = entity->secondary_resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->secondary_resource = 0;
}

void __fastcall EntityAnimation_Release(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->resource = 0;
}
