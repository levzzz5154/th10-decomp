// =============================================================================
// animation_manager.cpp - Handle lookup and position propagation
// Functions: 0x004489D0/0x00448A50/0x00448AC0/0x00448B40 (Register),
//            0x00448860/0x00448900 (Update), 0x00448980 (render bucket),
//            0x00448DB0 (player creation), 0x0043E710/0x0043E7E0
//            (LoadScript), 0x004491C0 (Find),
//            0x004492F0 (SetPosition), 0x00449950 (Allocate)
// =============================================================================
#include "th10/render/animation_manager.hpp"
#include "th10/game/entity.hpp"
#include "th10/render/anm_entry_load.hpp"

extern "C" void* operator_new(unsigned int size);
extern "C" void _free(void* allocation);
extern void* g_pGameStateManager;
extern float _DAT_00470b48;
extern float _DAT_00470b4c;
extern float _DAT_00470b60;
extern unsigned int DAT_00476f78;
extern void* g_pD3DDevice;

#ifdef _MSC_VER
extern "C" unsigned long dword_491C10;
extern "C" void* sub_4491C0(void*);
extern "C" void sub_43E5A0(void*, void*);
extern "C" void sub_43EE30(void*);
extern "C" void sub_447810(void*);
extern "C" void j__free(void*);
extern "C" void* sub_449950(void*);
extern "C" void sub_449870(void*, void*);
extern "C" void sub_4489D0(void*, void*);
extern "C" void sub_448A50(void*, void*);
extern "C" void sub_448AC0(void*, void*);
extern "C" void sub_448B40(void*, void*);
extern "C" void sub_43E710(void*, void*);
extern "C" void sub_4451C0(void*, void*);
extern "C" void sub_4492A0(void*, void*);
extern "C" void _free(void*);
extern "C" float flt_470B4C;
extern "C" float flt_470B48;
extern "C" unsigned short word_4749CE;
extern "C" void sub_448BB0(void);
extern "C" void sub_43EE30(void*);
extern "C" unsigned long dword_46F288;
extern "C" unsigned long dword_46F2A0;
extern "C" unsigned long dword_491C30;
extern "C" void sub_4521A0(void*, void*, void*, void*, void*, void*, void*, void*);
extern "C" void sub_463B2C(void);
#endif

extern "C" int __stdcall D3DXCreateTexture(
    void* device, unsigned int width, unsigned int height,
    unsigned int mip_levels, unsigned int usage, unsigned int format,
    unsigned int pool, void* output);

Entity* __fastcall Entity_Constructor(Entity* entity);
void __fastcall Entity_Destructor(Entity* entity);
void __fastcall Entity_Init(void* unused, Entity* entity);
int AnimationObject_ExecuteScript(AnimationObject* animation);
void AnimationObject_Render(void* manager, AnimationObject* animation);

static AnimationListNode* AnimationManager_List(
    void* manager, unsigned int listIndex);
static void AnimationObject_SetPosition(
    AnimationObject* animation, const float* position);
static int* AnimationObject_RenderBucketSlot(AnimationObject* animation);

static unsigned int AnimationManager_NextPoolIndex(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

// 0x00447050 - Allocate a one-level managed texture in one of the six retail
// pixel formats and retain the corresponding byte stride in its owner record.
#ifdef _MSC_VER
__declspec(naked) int AnimationTexture_Create(
        unsigned int width, unsigned int height,
        unsigned int format_index, AnimationTextureRecord* output) {
    __asm {
        mov eax, [esi*4+dword_46F288]
        push edi
        push 1
        push eax
        mov eax, dword_491C30
        push 0
        push 1
        push ecx
        push edx
        push eax
        call sub_4521A0
        mov ecx, [esi*4+dword_46F2A0]
        mov [edi+0Ch], ecx
        xor eax, eax
        ret
    }
}
#else
int AnimationTexture_Create(unsigned int width, unsigned int height,
                            unsigned int format_index,
                            AnimationTextureRecord* output) {
    static const unsigned int formats[6] = {0, 21, 25, 23, 20, 26};
    static const unsigned int bytes_per_pixel[6] = {4, 4, 2, 2, 3, 2};
    D3DXCreateTexture(g_pD3DDevice, width, height, 1, 0,
                      formats[format_index], 1, output);
    output->bytes_per_pixel = bytes_per_pixel[format_index];
    return 0;
}
#endif

// 0x00447810 - Retire a populated animation-resource batch. The retail leaf
// first synchronizes the owner, releases each interface/resource pair, then
// frees the entry table and four auxiliary allocations in deterministic
// address order.
void AnimationManager_ReleaseResourceBatch(
        AnimationResourceBatch* batch, void* context,
        void (*prepare)(void*, void*),
        void (*release)(void*), void (*free_memory)(void*)) {
    if (batch->active == 0)
        return;
    if (prepare != 0)
        prepare(context, batch);
    for (int index = 0; index < batch->entry_count; ++index) {
        AnimationResourceBatchEntry* entry = &batch->entries[index];
        if (entry->resource != 0 && release != 0)
            release(entry->resource);
        entry->resource = 0;
        if (entry->allocation != 0 && free_memory != 0)
            free_memory(entry->allocation);
        entry->allocation = 0;
    }
    if (free_memory != 0) {
        if (batch->entries != 0) free_memory(batch->entries);
        if (batch->auxiliary_a != 0) free_memory(batch->auxiliary_a);
        if (batch->auxiliary_b != 0) free_memory(batch->auxiliary_b);
        if (batch->auxiliary_c != 0) free_memory(batch->auxiliary_c);
    }
    batch->entries = 0;
    batch->auxiliary_a = 0;
    batch->auxiliary_b = 0;
    batch->auxiliary_c = 0;
    batch->active = 0;
}

// 0x004423C0 - Multiply two 7-bit-normalized color channels and saturate the
// result to the byte range used by the animation renderer.
#ifdef _MSC_VER
__declspec(naked) uint32_t AnimationColor_MultiplyChannel(
        uint32_t left, uint32_t right) {
    __asm {
        movzx eax, al
        movzx ecx, cl
        imul eax, ecx
        shr eax, 7
        cmp eax, 100h
        jb locret_4423D8
        mov eax, 0FFh
locret_4423D8:
        ret
    }
}
#else
uint32_t AnimationColor_MultiplyChannel(uint32_t left, uint32_t right) {
    uint32_t result = (left & 0xFF) * (right & 0xFF) >> 7;
    return result > 0xFF ? 0xFF : result;
}
#endif

// 0x00447940 - Copy one animation position record and derive its normalized
// coordinates and extents. The retail record is 0x44 bytes (17 floats).
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_CopyPositionRecord(
        void* manager, unsigned int index, const float* source) {
    __asm {
        imul eax, eax, 44h
        push esi
        push edi
        mov edi, [edx+118h]
        add edi, eax
        mov ecx, 11h
        mov esi, ebx
        rep movsd
        mov ecx, [edx+118h]
        add ecx, eax
        pop edi
        pop esi
        fld dword ptr [ecx+8]
        fdiv dword ptr [ecx+1Ch]
        fstp dword ptr [ecx+20h]
        mov ecx, [edx+118h]
        fld dword ptr [ecx+eax+10h]
        fdiv dword ptr [ecx+eax+1Ch]
        add ecx, eax
        fstp dword ptr [ecx+28h]
        mov ecx, [edx+118h]
        fld dword ptr [ecx+eax+0Ch]
        fdiv dword ptr [ecx+eax+18h]
        add ecx, eax
        fstp dword ptr [ecx+24h]
        mov ecx, [edx+118h]
        fld dword ptr [ecx+eax+14h]
        fdiv dword ptr [ecx+eax+18h]
        add ecx, eax
        fstp dword ptr [ecx+2Ch]
        mov ecx, [edx+118h]
        fld dword ptr [ecx+eax+10h]
        fsub dword ptr [ecx+eax+8]
        add ecx, eax
        fdiv dword ptr [ebx+38h]
        fstp dword ptr [ecx+34h]
        mov edx, [edx+118h]
        fld dword ptr [eax+edx+14h]
        fsub dword ptr [eax+edx+0Ch]
        add eax, edx
        fdiv dword ptr [ebx+3Ch]
        fstp dword ptr [eax+30h]
        ret
    }
}
#else
void AnimationManager_CopyPositionRecord(void* manager, unsigned int index,
                                         const float* source) {
    uint8_t* bytes = (uint8_t*)manager;
    float* destination = (float*)(bytes + 0x118 + index * 0x44);
    for (unsigned int field = 0; field != 17; ++field)
        destination[field] = source[field];
    // The trailing arithmetic is byte-identical to the tail of the archive
    // entry loader at 0x00447470, so both callers share one implementation.
    AnmSprite_DeriveRecord(destination);
}
#endif

// 0x0043EC70 - Read one of the animation interpreter's integer-valued
// variables. Float variables use the same truncating conversion as retail's
// x87 helper at 0x00463B2C.
#ifdef _MSC_VER
__declspec(naked) int AnimationObject_ReadIntegerVariable(
        AnimationObject* animation, int variableId) {
    __asm {
        lea edx, [eax-2710h]
        cmp edx, 9
        ja default_case
        jmp dword ptr [edx*4+43ECD8h]
case_zero:
        mov eax, [ecx+30Ch]
        ret
case_one:
        mov eax, [ecx+310h]
        ret
case_two:
        mov eax, [ecx+314h]
        ret
case_three:
        mov eax, [ecx+318h]
        ret
case_four:
        fld dword ptr [ecx+31Ch]
        jmp sub_463B2C
case_five:
        fld dword ptr [ecx+320h]
        jmp sub_463B2C
case_six:
        fld dword ptr [ecx+324h]
        jmp sub_463B2C
case_seven:
        fld dword ptr [ecx+328h]
        jmp sub_463B2C
case_eight:
        mov eax, [ecx+32Ch]
        ret
case_nine:
        mov eax, [ecx+330h]
default_case:
        ret
        _emit 0x82
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0x89
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0x90
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0x97
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0x9E
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0xA9
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0xB4
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0xBF
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0xCA
        _emit 0xEC
        _emit 0x43
        _emit 0x00
        _emit 0xD1
        _emit 0xEC
        _emit 0x43
        _emit 0x00
    }
}
#else
int AnimationObject_ReadIntegerVariable(
    AnimationObject* animation, int variableId) {
    Entity* entity = (Entity*)animation;
    if (10000 <= variableId && variableId <= 10003) {
        return entity->ScriptIntegerVariables()[variableId - 10000];
    }
    if (10004 <= variableId && variableId <= 10007) {
        return (int)entity->ScriptFloatVariables()[variableId - 10004];
    }
    if (10008 <= variableId && variableId <= 10009) {
        return entity->ScriptExtraIntegerVariables()[variableId - 10008];
    }
    return variableId;
}
#endif

// 0x0043EDA0 - Resolve a writable integer-variable operand. The retail helper
// receives the candidate value in EAX and uses the instruction parameter mask
// to decide whether it is an encoded variable or a literal fallback address.
#ifdef _MSC_VER
__declspec(naked) int* AnimationObject_ResolveIntegerVariable(
        AnimationObject* animation, int variableId, int* fallback,
        bool variableEncoded) {
    __asm {
        push esi
        mov esi, 1
        shl esi, cl
        movzx ecx, word ptr [esp+8]
        test esi, ecx
        pop esi
        je default_case
        mov ecx, [eax]
        add ecx, 0FFFFD8F0h
        cmp ecx, 9
        ja default_case
        jmp dword ptr [ecx*4+43EDFCh]
case_zero:
        lea eax, [edx+30Ch]
        ret 4
case_one:
        lea eax, [edx+310h]
        ret 4
case_two:
        lea eax, [edx+314h]
        ret 4
case_three:
        lea eax, [edx+318h]
        ret 4
case_four:
        lea eax, [edx+32Ch]
        ret 4
case_five:
        lea eax, [edx+330h]
default_case:
        ret 4
        _emit 0xC6
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xCF
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xD8
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xE1
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xF9
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xF9
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xF9
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xF9
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xEA
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0xF3
        _emit 0xED
        _emit 0x43
        _emit 0x00
    }
}
#else
int* AnimationObject_ResolveIntegerVariable(
    AnimationObject* animation, int variableId, int* fallback,
    bool variableEncoded) {
    if (!variableEncoded) {
        return fallback;
    }
    Entity* entity = (Entity*)animation;
    if (10000 <= variableId && variableId <= 10003) {
        return &entity->ScriptIntegerVariables()[variableId - 10000];
    }
    if (10008 <= variableId && variableId <= 10009) {
        return &entity->ScriptExtraIntegerVariables()[variableId - 10008];
    }
    return fallback;
}
#endif

// 0x0043ED00 - Resolve a writable floating-point variable. IDs 10013..10015
// expose the base-position vector directly to animation scripts.
#ifdef _MSC_VER
__declspec(naked) float* AnimationObject_ResolveFloatVariable(
        AnimationObject* animation, int variableId, float* fallback,
        bool variableEncoded) {
    __asm {
        mov eax, 1
        shl eax, cl
        movzx ecx, word ptr [esp+4]
        test eax, ecx
        je default_case
        fld dword ptr [edi]
        call sub_463B2C
        add eax, 0FFFFD8ECh
        cmp eax, 0Bh
        ja default_case
        jmp dword ptr [eax*4+43ED6Ch]
case_zero:
        lea eax, [esi+31Ch]
        ret 4
case_one:
        lea eax, [esi+320h]
        ret 4
case_two:
        lea eax, [esi+324h]
        ret 4
case_three:
        lea eax, [esi+328h]
        ret 4
case_four:
        lea eax, [esi+334h]
        ret 4
case_five:
        lea eax, [esi+338h]
        ret 4
case_six:
        lea eax, [esi+33Ch]
        ret 4
default_case:
        mov eax, edi
        ret 4
        _emit 0x28
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x31
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x3A
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x43
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x67
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x67
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x67
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x67
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x67
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x4C
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x55
        _emit 0xED
        _emit 0x43
        _emit 0x00
        _emit 0x5E
        _emit 0xED
        _emit 0x43
        _emit 0x00
    }
}
#else
float* AnimationObject_ResolveFloatVariable(
    AnimationObject* animation, int variableId, float* fallback,
    bool variableEncoded) {
    if (!variableEncoded) {
        return fallback;
    }
    Entity* entity = (Entity*)animation;
    if (10004 <= variableId && variableId <= 10007) {
        return &entity->ScriptFloatVariables()[variableId - 10004];
    }
    if (10013 <= variableId && variableId <= 10015) {
        return &entity->BasePosition().x + (variableId - 10013);
    }
    return fallback;
}
#endif

void AnimationManager_InitializeStorage(void* manager) {
    uint8_t* bytes = (uint8_t*)manager;

    // GameStateInit's generated array constructors run before this clear.
    // Their observable state is discarded, so express the resulting state
    // directly and avoid reading uninitialized allocations.
    unsigned int* word = (unsigned int*)bytes;
    for (unsigned int count = 0x1CC918; count != 0; --count) {
        *word++ = 0;
    }

    // The first two words are reset-sensitive render-target handles.
    *(int*)(bytes + 0x00) = -1;
    *(int*)(bytes + 0x04) = -1;

    // Defaults established immediately before the pool initialization loop.
    *(unsigned int*)(bytes + 0x3ADA60) = 1;
    bytes[0x3ADA68] = 0;
    bytes[0x3ADA69] = 0;
    bytes[0x3ADA6A] = 0;
    bytes[0x3ADA6B] = 0;
    bytes[0x3ADA6C] = 0xFF;
    *(unsigned int*)(bytes + 0x3ADA64) = 0;
    *(unsigned int*)(bytes + 0x3ADA74) = 0;

    Entity* entity = (Entity*)(bytes + 0x68);
    for (unsigned int index = 0; index != 0x1000; ++index) {
        Entity_Init(0, entity);
        entity = (Entity*)((uint8_t*)entity + 0x3AC);
    }
}

// 0x00446220 - Drain both lists and destroy the render sentinels, manager-owned
// buffer, and complete 4,096-object pool.
void AnimationManager_DestroyStorage(void* manager) {
    uint8_t* bytes = (uint8_t*)manager;

    // Save the next node before removal because pooled objects are reset by
    // AnimationManager_RemoveObject and fallback objects are freed by it.
    for (unsigned int listIndex = 0; listIndex != 2; ++listIndex) {
        AnimationListNode* node = AnimationManager_List(manager, listIndex);
        while (node != 0) {
            AnimationListNode* next = node->next;
            AnimationManager_RemoveObject(manager, node->animation);
            node = next;
        }
    }

    Entity* sentinel = (Entity*)(bytes + 0x72DAE4);
    for (unsigned int index = 0; index != 20; ++index) {
        Entity_Destructor(sentinel);
        sentinel = (Entity*)((uint8_t*)sentinel + 0x3AC);
    }

    void** ownedBuffer = (void**)(bytes + 0x3AD488);
    if (*ownedBuffer != 0) {
        _free(*ownedBuffer);
    }
    *ownedBuffer = 0;

    Entity* pooled = (Entity*)(bytes + 0x68);
    for (unsigned int index = 0; index != 0x1000; ++index) {
        Entity_Destructor(pooled);
        pooled = (Entity*)((uint8_t*)pooled + 0x3AC);
    }
}

AnimationObject* AnimationManager_AllocateObject(void* manager) {
    uint8_t* bytes = (uint8_t*)manager;
    unsigned int* cursor = (unsigned int*)(bytes + 0x3AD068);
    unsigned int index = *cursor;

    if (bytes[0x3AC068 + index] != 0) {
        index = AnimationManager_NextPoolIndex(index);
        *cursor = index;
        if (bytes[0x3AC068 + index] != 0) {
            Entity* allocated = (Entity*)operator_new(0x3AC);
            if (allocated == 0) {
                return 0;
            }
            Entity_Constructor(allocated);
            Entity_Init(0, allocated);
            *cursor = AnimationManager_NextPoolIndex(*cursor);
            return (AnimationObject*)allocated;
        }
    }

    AnimationObject* animation =
        (AnimationObject*)(bytes + 0x68 + index * 0x3AC);
    bytes[0x3AC068 + index] = 1;
    *cursor = AnimationManager_NextPoolIndex(*cursor);
    return animation;
}

static int AnimationManager_CreateObject(
    void* manager, void* resource, int animationIndex, int renderBucket,
    AnimationManagerList list, AnimationListInsertion insertion) {
    AnimationObject* animation = AnimationManager_AllocateObject(manager);
    if (animation == 0) {
        return 0;
    }
    *AnimationObject_RenderBucketSlot(animation) = renderBucket;
    ((Entity*)animation)->AnimationFlags() |= 0x40000000u;
    AnimationObject_InitializeScriptState(animation, resource, animationIndex);
    return AnimationManager_RegisterObjectAt(
        manager, animation, list, insertion);
}

// 0x00448D00 - Allocate and append an object to the primary animation list.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_CreatePrimaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    __asm {
        push ebx
        push esi
        mov esi, dword_491C10
        call sub_449950
        mov ecx, [esp+8+8]
        mov ebx, eax
        mov esi, [ebx+35Ch]
        mov eax, [esp+8+0Ch]
        push ecx
        mov ecx, [esp+0Ch+4]
        or esi, 40000000h
        push ebx
        mov [ebx+20h], eax
        mov [ebx+35Ch], esi
        call sub_449870
        mov edx, dword_491C10
        mov eax, edi
        call sub_4489D0
        pop esi
        pop ebx
        ret 0Ch
    }
}
#else
int AnimationManager_CreatePrimaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Primary, AnimationListInsertion_Back);
}
#endif

// 0x00448E30 - Allocate and prepend an object to the primary animation list.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_CreatePrimaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    __asm {
        push ebx
        push esi
        mov esi, dword_491C10
        call sub_449950
        mov ecx, [esp+8+8]
        mov ebx, eax
        mov esi, [ebx+35Ch]
        mov eax, [esp+8+0Ch]
        push ecx
        mov ecx, [esp+0Ch+4]
        or esi, 40000000h
        push ebx
        mov [ebx+20h], eax
        mov [ebx+35Ch], esi
        call sub_449870
        mov edx, dword_491C10
        mov eax, edi
        call sub_448A50
        pop esi
        pop ebx
        ret 0Ch
    }
}
#else
int AnimationManager_CreatePrimaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Primary, AnimationListInsertion_Front);
}
#endif

// 0x00448F60 - Allocate and append an object to the secondary animation list.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_CreateSecondaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    __asm {
        push ebx
        push esi
        mov esi, dword_491C10
        call sub_449950
        mov ecx, [esp+8+8]
        mov ebx, eax
        mov esi, [ebx+35Ch]
        mov eax, [esp+8+0Ch]
        push ecx
        mov ecx, [esp+0Ch+4]
        or esi, 40000000h
        push ebx
        mov [ebx+20h], eax
        mov [ebx+35Ch], esi
        call sub_449870
        mov edx, dword_491C10
        mov eax, edi
        call sub_448AC0
        pop esi
        pop ebx
        ret 0Ch
    }
}
#else
int AnimationManager_CreateSecondaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Secondary, AnimationListInsertion_Back);
}
#endif

// 0x00449090 - Allocate and prepend an object to the secondary animation list.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_CreateSecondaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    __asm {
        push ebx
        push esi
        mov esi, dword_491C10
        call sub_449950
        mov ecx, [esp+8+8]
        mov ebx, eax
        mov esi, [ebx+35Ch]
        mov eax, [esp+8+0Ch]
        push ecx
        mov ecx, [esp+0Ch+4]
        or esi, 40000000h
        push ebx
        mov [ebx+20h], eax
        mov [ebx+35Ch], esi
        call sub_449870
        mov edx, dword_491C10
        mov eax, edi
        call sub_448B40
        pop esi
        pop ebx
        ret 0Ch
    }
}
#else
int AnimationManager_CreateSecondaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Secondary, AnimationListInsertion_Front);
}
#endif

// 0x00448D50 - Allocate a primary object whose initial position is supplied by
// the caller before its animation script is selected.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_CreatePositionedPrimary(
    void* manager, void* resource, int animationIndex,
    const float* position) {
    __asm {
        push ebx
        push ebp
        mov ebp, [esp+8+8]
        push esi
        mov esi, dword_491C10
        call sub_449950
        mov ebx, [esp+0Ch+0Ch]
        mov esi, eax
        or dword ptr [esi+35Ch], 40000000h
        mov dword ptr [esi+20h], 0
        mov ecx, [edi]
        lea eax, [esi+340h]
        mov [eax], ecx
        mov edx, [edi+4]
        mov [eax+4], edx
        mov ecx, [edi+8]
        mov [eax+8], ecx
        mov ecx, [esp+0Ch+4]
        mov eax, esi
        call sub_43E710
        mov edx, dword_491C10
        mov ebx, esi
        mov eax, ebp
        call sub_4489D0
        pop esi
        pop ebp
        pop ebx
        ret 0Ch
    }
}
#else
int AnimationManager_CreatePositionedPrimary(
    void* manager, void* resource, int animationIndex,
    const float* position) {
    AnimationObject* animation = AnimationManager_AllocateObject(manager);
    if (animation == 0) {
        return 0;
    }
    *AnimationObject_RenderBucketSlot(animation) = 0;
    ((Entity*)animation)->AnimationFlags() |= 0x40000000u;
    AnimationObject_SetPosition(animation, position);
    AnimationObject_LoadScript(animation, resource, animationIndex);
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
}
#endif

static AnimationListNode* AnimationManager_List(
    void* manager, unsigned int listIndex) {
    const unsigned int listOffset =
        0x72DAD4 + listIndex * 2 * sizeof(AnimationListNode*);
    return *(AnimationListNode**)((uint8_t*)manager + listOffset);
}

static AnimationListNode** AnimationManager_ListSlot(
    void* manager, unsigned int listIndex, bool tail) {
    const unsigned int slot = listIndex * 2 + (tail ? 1 : 0);
    return (AnimationListNode**)((uint8_t*)manager + 0x72DAD4 +
                                 slot * sizeof(AnimationListNode*));
}

// 0x004491C0 - Find a registered animation by its nonzero handle.
#ifdef _MSC_VER
__declspec(naked) AnimationObject* AnimationManager_Find(
    void* manager, int animationHandle) {
    __asm {
        mov ecx, [esp+4]
        test ecx, ecx
        jnz loc_4491CD
        xor eax, eax
        ret 4
loc_4491CD:
        mov eax, [edx+72DAD4h]
        test eax, eax
        push esi
        jz loc_4491E5
loc_4491D8:
        mov esi, [eax]
        cmp [esi], ecx
        jz loc_449203
        mov eax, [eax+4]
        test eax, eax
        jnz loc_4491D8
loc_4491E5:
        mov eax, [edx+72DADCh]
        test eax, eax
        jz loc_4491FD
        nop
loc_4491F0:
        mov edx, [eax]
        cmp [edx], ecx
        jz loc_449203
        mov eax, [eax+4]
        test eax, eax
        jnz loc_4491F0
loc_4491FD:
        xor eax, eax
        pop esi
        ret 4
loc_449203:
        mov eax, [eax]
        pop esi
        ret 4
    }
}
#else
AnimationObject* AnimationManager_Find(
    void* manager, int animationHandle) {
    if (animationHandle == 0) {
        return 0;
    }

    AnimationListNode* node = AnimationManager_List(manager, 0);
    while (node != 0) {
        if (*(int*)node->animation == animationHandle) {
            return node->animation;
        }
        node = node->next;
    }

    node = AnimationManager_List(manager, 1);
    while (node != 0) {
        if (*(int*)node->animation == animationHandle) {
            return node->animation;
        }
        node = node->next;
    }
    return 0;
}
#endif

int AnimationManager_RegisterObject(
    void* manager, AnimationObject* animation) {
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
}

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_RegisterPrimaryBack(
        void* manager, AnimationObject* animation, void* handle_out) {
    __asm {
        lea ecx, [ebx+4]
        push esi
        mov [ecx], ebx
        mov dword ptr [ecx+4], 0
        mov dword ptr [ecx+8], 0
        mov esi, [edx+72DAD4h]
        test esi, esi
        jnz loc_4489F6
        mov [edx+72DAD4h], ecx
        jmp loc_448A14
loc_4489F6:
        mov esi, [edx+72DAD8h]
        push edi
        mov edi, [esi+4]
        test edi, edi
        jz loc_448A0D
        mov [ecx+4], edi
        mov edi, [esi+4]
        mov [edi+8], ecx
loc_448A0D:
        mov [esi+4], ecx
        mov [ecx+8], esi
        pop edi
loc_448A14:
        mov [edx+72DAD8h], ecx
        mov esi, [edx+732454h]
        inc esi
        mov ecx, esi
        test ecx, ecx
        mov [edx+732454h], esi
        pop esi
        jnz loc_448A35
        inc ecx
        mov [edx+732454h], ecx
loc_448A35:
        mov ecx, [edx+732454h]
        mov [ebx], ecx
        mov edx, [edx+732454h]
        mov [eax], edx
        ret
    }
}
#else
int AnimationManager_RegisterPrimaryBack(
        void* manager, AnimationObject* animation, void* handle_out) {
    (void)handle_out;
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
}
#endif

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_RegisterPrimaryFront(
        void* manager, AnimationObject* animation, void* handle_out) {
    __asm {
        lea ecx, [ebx+4]
        push esi
        mov [ecx], ebx
        mov dword ptr [ecx+4], 0
        mov dword ptr [ecx+8], 0
        mov esi, [edx+72DAD4h]
        test esi, esi
        jnz loc_448A76
        mov [edx+72DAD8h], ecx
        jmp loc_448A8E
loc_448A76:
        push edi
        mov edi, [ecx+4]
        test edi, edi
        jz loc_448A87
        mov [esi+4], edi
        mov edi, [ecx+4]
        mov [edi+8], esi
loc_448A87:
        mov [ecx+4], esi
        mov [esi+8], ecx
        pop edi
loc_448A8E:
        mov [edx+72DAD4h], ecx
        mov esi, [edx+732454h]
        inc esi
        mov ecx, esi
        test ecx, ecx
        mov [edx+732454h], esi
        pop esi
        jnz loc_448AAF
        inc ecx
        mov [edx+732454h], ecx
loc_448AAF:
        mov ecx, [edx+732454h]
        mov [ebx], ecx
        mov edx, [edx+732454h]
        mov [eax], edx
        ret
    }
}
#else
int AnimationManager_RegisterPrimaryFront(
        void* manager, AnimationObject* animation, void* handle_out) {
    (void)handle_out;
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Primary,
        AnimationListInsertion_Front);
}
#endif

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_RegisterSecondaryBack(
        void* manager, AnimationObject* animation, void* handle_out) {
    __asm {
        lea ecx, [ebx+4]
        push esi
        mov [ecx], ebx
        mov dword ptr [ecx+4], 0
        mov dword ptr [ecx+8], 0
        mov esi, [edx+72DADCh]
        test esi, esi
        jnz loc_448AE6
        mov [edx+72DADCh], ecx
        jmp loc_448B04
loc_448AE6:
        mov esi, [edx+72DAE0h]
        push edi
        mov edi, [esi+4]
        test edi, edi
        jz loc_448AFD
        mov [ecx+4], edi
        mov edi, [esi+4]
        mov [edi+8], ecx
loc_448AFD:
        mov [esi+4], ecx
        mov [ecx+8], esi
        pop edi
loc_448B04:
        mov [edx+72DAE0h], ecx
        mov esi, [edx+732454h]
        inc esi
        mov ecx, esi
        test ecx, ecx
        mov [edx+732454h], esi
        pop esi
        jnz loc_448B25
        inc ecx
        mov [edx+732454h], ecx
loc_448B25:
        mov ecx, [edx+732454h]
        mov [ebx], ecx
        mov edx, [edx+732454h]
        mov [eax], edx
        ret
    }
}
#else
int AnimationManager_RegisterSecondaryBack(
        void* manager, AnimationObject* animation, void* handle_out) {
    (void)handle_out;
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Secondary,
        AnimationListInsertion_Back);
}
#endif

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_RegisterSecondaryFront(
        void* manager, AnimationObject* animation, void* handle_out) {
    __asm {
        lea ecx, [ebx+4]
        push esi
        mov [ecx], ebx
        mov dword ptr [ecx+4], 0
        mov dword ptr [ecx+8], 0
        mov esi, [edx+72DADCh]
        test esi, esi
        jnz loc_448B66
        mov [edx+72DAE0h], ecx
        jmp loc_448B7E
loc_448B66:
        push edi
        mov edi, [ecx+4]
        test edi, edi
        jz loc_448B77
        mov [esi+4], edi
        mov edi, [ecx+4]
        mov [edi+8], esi
loc_448B77:
        mov [ecx+4], esi
        mov [esi+8], ecx
        pop edi
loc_448B7E:
        mov [edx+72DADCh], ecx
        mov esi, [edx+732454h]
        inc esi
        mov ecx, esi
        test ecx, ecx
        mov [edx+732454h], esi
        pop esi
        jnz loc_448B9F
        inc ecx
        mov [edx+732454h], ecx
loc_448B9F:
        mov ecx, [edx+732454h]
        mov [ebx], ecx
        mov edx, [edx+732454h]
        mov [eax], edx
        ret
    }
}
#else
int AnimationManager_RegisterSecondaryFront(
        void* manager, AnimationObject* animation, void* handle_out) {
    (void)handle_out;
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Secondary,
        AnimationListInsertion_Front);
}
#endif

int AnimationManager_RegisterObjectAt(
    void* manager, AnimationObject* animation,
    AnimationManagerList list, AnimationListInsertion insertion) {
    uint8_t* bytes = (uint8_t*)manager;
    AnimationListNode* node =
        (AnimationListNode*)((uint8_t*)animation + 4);
    node->animation = animation;
    node->next = 0;
    node->previous = 0;

    AnimationListNode** head =
        AnimationManager_ListSlot(manager, (unsigned int)list, false);
    AnimationListNode** tail =
        AnimationManager_ListSlot(manager, (unsigned int)list, true);
    if (*head == 0) {
        *head = node;
        *tail = node;
    } else if (insertion == AnimationListInsertion_Front) {
        node->next = *head;
        (*head)->previous = node;
        *head = node;
    } else {
        if ((*tail)->next != 0) {
            node->next = (*tail)->next;
            (*tail)->next->previous = node;
        }
        (*tail)->next = node;
        node->previous = *tail;
        *tail = node;
    }

    int* nextHandle = (int*)(bytes + 0x732454);
    ++*nextHandle;
    if (*nextHandle == 0) {
        ++*nextHandle;
    }
    *(int*)animation = *nextHandle;
    return *nextHandle;
}

static void AnimationList_Unlink(AnimationListNode* node) {
    if (node->next != 0) {
        node->next->previous = node->previous;
    }
    if (node->previous != 0) {
        node->previous->next = node->next;
    }
    node->next = 0;
    node->previous = 0;
}

static AnimationListNode* AnimationObject_ChildMembership(
    AnimationObject* animation) {
    return (AnimationListNode*)((uint8_t*)animation + 4 +
                                sizeof(AnimationListNode));
}

static AnimationObject** AnimationObject_RenderChainSlot(
    AnimationObject* animation) {
    return (AnimationObject**)((uint8_t*)animation + 4 +
                               2 * sizeof(AnimationListNode));
}

static int* AnimationObject_RenderBucketSlot(AnimationObject* animation) {
    return (int*)((uint8_t*)AnimationObject_RenderChainSlot(animation) +
                  sizeof(AnimationObject*));
}

static AnimationUpdateCallback AnimationObject_UpdateCallback(
    AnimationObject* animation) {
    return *(AnimationUpdateCallback*)((uint8_t*)animation + 0x398);
}

static AnimationDrawCallback AnimationObject_DrawCallback(
    AnimationObject* animation) {
    return *(AnimationDrawCallback*)((uint8_t*)animation + 0x398 +
                                     sizeof(AnimationUpdateCallback));
}

// 0x00448BB0 - Unlink and retire a pooled or fallback animation object.
void AnimationManager_RemoveObject(
    void* manager, AnimationObject* animation) {
    if (animation == 0) {
        return;
    }

    uint8_t* managerBytes = (uint8_t*)manager;
    uint8_t* animationBytes = (uint8_t*)animation;
    AnimationListNode* node =
        (AnimationListNode*)(animationBytes + 4);
    AnimationListNode** primaryHead =
        (AnimationListNode**)(managerBytes + 0x72DAD4);
    AnimationListNode** primaryTail =
        (AnimationListNode**)(managerBytes + 0x72DAD4 +
                              sizeof(AnimationListNode*));
    AnimationListNode** secondaryHead =
        (AnimationListNode**)(managerBytes + 0x72DAD4 +
                              2 * sizeof(AnimationListNode*));
    AnimationListNode** secondaryTail =
        (AnimationListNode**)(managerBytes + 0x72DAD4 +
                              3 * sizeof(AnimationListNode*));

    if (*primaryTail == node) *primaryTail = node->previous;
    if (*primaryHead == node) *primaryHead = node->next;
    if (*secondaryTail == node) *secondaryTail = node->previous;
    if (*secondaryHead == node) *secondaryHead = node->next;
    AnimationList_Unlink(node);

    // The object also embeds a node at +0x10 when it belongs to a parent's
    // child list. The retail remover detaches both memberships.
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    AnimationList_Unlink(childMembership);

    // The owned-resource pointer immediately precedes the 32-bit flags word.
    // Expressing it relative to the flags keeps host semantic tests valid
    // while producing retail +0x358 on the 32-bit target.
    void** resource = &((Entity*)animation)->OwnedResource();
    uint8_t* poolBegin = managerBytes + 0x68;
    uint8_t* poolEnd = managerBytes + 0x3AC068;
    if (poolBegin <= animationBytes && animationBytes < poolEnd) {
        unsigned int index =
            (unsigned int)(animationBytes - poolBegin) / 0x3AC;
        managerBytes[0x3AC068 + index] = 0;
        if (*resource != 0) {
            _free(*resource);
            *resource = 0;
        }
        Entity_Init(0, (Entity*)animation);
        return;
    }

    if (*resource != 0) {
        _free(*resource);
        *resource = 0;
    }
    _free(animation);
}

static void AnimationObject_SetPosition(
    AnimationObject* animation, const float* position) {
    Entity* entity = (Entity*)animation;
    entity->Position().x = position[0];
    entity->Position().y = position[1];
    entity->Position().z = position[2];
}

typedef void (*AnimationObjectOperation)(AnimationObject*, void* context);

static void AnimationObject_ApplyToRootAndChildren(
    AnimationObject* animation, AnimationObjectOperation operation,
    void* context) {
    operation(animation, context);
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    if (childMembership->previous != 0) {
        return;
    }
    AnimationListNode* child = childMembership->next;
    while (child != 0) {
        operation(child->animation, context);
        child = child->next;
    }
}

static void AnimationObject_WriteStopFrame(
    AnimationObject* animation, void* context) {
    ((Entity*)animation)->StopFrame() = *(short*)context;
}

// 0x00449210 - Set the root stop frame and propagate it to direct children.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_SetStopFrame(
        void* manager, int animationHandle, short frame) {
    __asm {
        mov eax, [esp+4]
        push eax
        call sub_4491C0
        test eax, eax
        jz locret_449243
        mov ecx, [eax+18h]
        test ecx, ecx
        mov [eax+304h], si
        jnz locret_449243
        mov eax, [eax+14h]
        test eax, eax
        jz locret_449243
loc_449233:
        mov ecx, [eax]
        mov [ecx+304h], si
        mov eax, [eax+4]
        test eax, eax
        jnz loc_449233
locret_449243:
        ret 4
    }
}
#else
void AnimationManager_SetStopFrame(
    void* manager, int animationHandle, short frame) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_WriteStopFrame, &frame);
    }
}
#endif

// 0x00449470 - Pointer-handle form used by gameplay owners.
void AnimationManager_SetStopFrameFromHandle(
    void* manager, const int* animationHandle, short frame) {
    AnimationManager_SetStopFrame(manager, *animationHandle, frame);
}

// 0x0040C480 - Gameplay shorthand for stopping an animation at frame 2.
// The retail entry receives its handle pointer in EAX and obtains the manager
// from the global game-state owner; the cleaned API makes the handle explicit.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_StopAtFrame2(
        const int* animationHandle) {
    __asm {
        mov eax, [eax]
        mov edx, dword_491C10
        push eax
        call sub_4491C0
        test eax, eax
        jz locret_40C4C0
        mov edx, [eax+18h]
        test edx, edx
        mov ecx, 2
        mov [eax+304h], cx
        jnz locret_40C4C0
        mov eax, [eax+14h]
        test eax, eax
        jz locret_40C4C0
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
loc_40C4B0:
        mov edx, [eax]
        mov [edx+304h], cx
        mov eax, [eax+4]
        test eax, eax
        jnz loc_40C4B0
locret_40C4C0:
        ret
    }
}
#else
void AnimationManager_StopAtFrame2(const int* animationHandle) {
    AnimationManager_SetStopFrame(
        g_pGameStateManager, *animationHandle, 2);
}
#endif

// 0x0040C4D0 - Companion shorthand that stops at frame 3.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_StopAtFrame3(
        const int* animationHandle) {
    __asm {
        mov eax, [eax]
        mov edx, dword_491C10
        push eax
        call sub_4491C0
        test eax, eax
        jz locret_40C510
        mov edx, [eax+18h]
        test edx, edx
        mov ecx, 3
        mov [eax+304h], cx
        jnz locret_40C510
        mov eax, [eax+14h]
        test eax, eax
        jz locret_40C510
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
loc_40C500:
        mov edx, [eax]
        mov [edx+304h], cx
        mov eax, [eax+4]
        test eax, eax
        jnz loc_40C500
locret_40C510:
        ret
    }
}
#else
void AnimationManager_StopAtFrame3(const int* animationHandle) {
    AnimationManager_SetStopFrame(
        g_pGameStateManager, *animationHandle, 3);
}
#endif

// 0x00449250 - Set a stop frame and immediately advance root and child scripts.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_SetStopFrameAndRun(
        void* manager, int animationHandle, short frame) {
    __asm {
        mov eax, [esp+4]
        push esi
        push eax
        call sub_4491C0
        mov esi, eax
        test esi, esi
        jz loc_449298
        push esi
        mov [esi+304h], di
        call sub_43EE30
        mov eax, [esi+18h]
        test eax, eax
        jnz loc_449298
        mov esi, [esi+14h]
        test esi, esi
        jz loc_449298
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
loc_449280:
        mov ecx, [esi]
        mov [ecx+304h], di
        mov edx, [esi]
        push edx
        call sub_43EE30
        mov esi, [esi+4]
        test esi, esi
        jnz loc_449280
loc_449298:
        pop esi
        ret 4
    }
}
#else
int AnimationManager_SetStopFrameAndRun(
    void* manager, int animationHandle, short frame) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return 0;
    }

    AnimationManager_SetStopFrame(manager, animationHandle, frame);
    int result = AnimationObject_ExecuteScript(animation);
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    if (childMembership->previous == 0) {
        AnimationListNode* child = childMembership->next;
        while (child != 0) {
            result = AnimationObject_ExecuteScript(child->animation);
            child = child->next;
        }
    }
    return result;
}
#endif

struct AnimationFlagChange {
    unsigned int flag;
    bool set;
};

static void AnimationObject_ChangeFlag(
    AnimationObject* animation, void* context) {
    AnimationFlagChange* change = (AnimationFlagChange*)context;
    unsigned int* flags = &((Entity*)animation)->AnimationFlags();
    if (change->set) {
        *flags |= change->flag;
    } else {
        *flags &= ~change->flag;
    }
}

// 0x004492A0 - Set an animation flag on a root and its direct children.
// 0x00449590 - The fixed-flag entry point uses this operation with bit 1.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_SetFlag(
        void* manager, int animationHandle, unsigned int flag) {
    __asm {
        mov eax, [esp+4]
        push eax
        call sub_4491C0
        test eax, eax
        jz locret_4492DF
        mov ecx, [eax+35Ch]
        mov edx, 4000000h
        or ecx, edx
        mov [eax+35Ch], ecx
        mov ecx, [eax+18h]
        test ecx, ecx
        jnz locret_4492DF
        mov eax, [eax+14h]
        test eax, eax
        jz locret_4492DF
        nop
loc_4492D0:
        mov ecx, [eax]
        or [ecx+35Ch], edx
        mov eax, [eax+4]
        test eax, eax
        jnz loc_4492D0
locret_4492DF:
        ret 4
    }
}
#else
void AnimationManager_SetFlag(
    void* manager, int animationHandle, unsigned int flag) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationFlagChange change = {flag, true};
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_ChangeFlag, &change);
    }
}
#endif

// 0x004495E0 - Clear an animation flag on a root and its direct children.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_ClearFlag(
        void* manager, int animationHandle, unsigned int flag) {
    __asm {
        mov ecx, [eax]
        mov edx, dword_491C10
        push ecx
        call sub_4491C0
        test eax, eax
        jz locret_449622
        mov ecx, [eax+35Ch]
        mov edx, 0FFFFFFFDh
        and ecx, edx
        mov [eax+35Ch], ecx
        mov ecx, [eax+18h]
        test ecx, ecx
        jnz locret_449622
        mov eax, [eax+14h]
        test eax, eax
        jz locret_449622
loc_449613:
        mov ecx, [eax]
        and [ecx+35Ch], edx
        mov eax, [eax+4]
        test eax, eax
        jnz loc_449613
locret_449622:
        ret
    }
}
#else
void AnimationManager_ClearFlag(
    void* manager, int animationHandle, unsigned int flag) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationFlagChange change = {flag, false};
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_ChangeFlag, &change);
    }
}
#endif

// 0x00449590 - Fixed-flag entry point that sets animation bit 1.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_SetFlagBit1(
        void* manager, int animationHandle) {
    __asm {
        mov ecx, [eax]
        mov edx, dword_491C10
        push ecx
        call sub_4491C0
        test eax, eax
        jz locret_4495D2
        mov ecx, [eax+35Ch]
        mov edx, 2
        or ecx, edx
        mov [eax+35Ch], ecx
        mov ecx, [eax+18h]
        test ecx, ecx
        jnz locret_4495D2
        mov eax, [eax+14h]
        test eax, eax
        jz locret_4495D2
loc_4495C3:
        mov ecx, [eax]
        or [ecx+35Ch], edx
        mov eax, [eax+4]
        test eax, eax
        jnz loc_4495C3
locret_4495D2:
        ret
    }
}
#else
void AnimationManager_SetFlagBit1(void* manager, int animationHandle) {
    AnimationManager_SetFlag(manager, animationHandle, 2);
}
#endif

// 0x004493E0 - Mark objects using a retired script resource for removal.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_MarkResourceForRemoval(
    void* manager, void* resource) {
    __asm {
        push esi
        mov esi, eax
        mov eax, [esi+72DAD4h]
        test eax, eax
        push edi
        mov edi, 4000000h
        jz loc_44940C
loc_4493F3:
        mov ecx, [eax+4]
        mov eax, [eax]
        cmp [eax+308h], edx
        jnz loc_449406
        or [eax+35Ch], edi
loc_449406:
        test ecx, ecx
        mov eax, ecx
        jnz loc_4493F3
loc_44940C:
        mov eax, [esi+72DADCh]
        test eax, eax
        jz loc_449439
        jmp loc_449420
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90
loc_449420:
        mov ecx, [eax+4]
        mov eax, [eax]
        cmp [eax+308h], edx
        jnz loc_449433
        or [eax+35Ch], edi
loc_449433:
        test ecx, ecx
        mov eax, ecx
        jnz loc_449420
loc_449439:
        pop edi
        pop esi
        ret
    }
}
#else
void AnimationManager_MarkResourceForRemoval(
    void* manager, void* resource) {
    for (unsigned int listIndex = 0; listIndex != 2; ++listIndex) {
        AnimationListNode* node =
            AnimationManager_List(manager, listIndex);
        while (node != 0) {
            AnimationObject* animation = node->animation;
            node = node->next;
            Entity* entity = (Entity*)animation;
            if (entity->ScriptResource() == resource) {
                entity->AnimationFlags() |= 0x04000000u;
            }
        }
    }
}
#endif

static void AnimationObject_LoadScriptInternal(
    AnimationObject* animation, void* resource, int animationIndex,
    bool resetEntity) {
    uint8_t* animationBytes = (uint8_t*)animation;
    uint8_t* resourceBytes = (uint8_t*)resource;
    Entity* entity = (Entity*)animation;
    void** scripts = *(void***)(resourceBytes + 0x11C);
    void* script = scripts[animationIndex];

    if (script == 0 || *(int*)(resourceBytes + 0x124) != 0) {
        unsigned int* destination = (unsigned int*)animation;
        for (int count = 0xEB; count != 0; --count) {
            *destination++ = 0;
        }
        return;
    }

    if (resetEntity) {
        Entity_Init(0, (Entity*)animation);
    }
    entity->ScriptIndex() = (short)animationIndex;
    entity->ScriptResourceId() = *(unsigned short*)resourceBytes;
    entity->ScriptResource() = resource;
    entity->AnimationFlags() &= 0xFFFFF9FFu;
    entity->ScriptBase() = script;
    entity->ScriptCursor() = script;

    unsigned int* timerFlags =
        (unsigned int*)(animationBytes + 0x6C);
    if ((*timerFlags & 1) == 0) {
        *(int*)(animationBytes + 0x60) = 0;
        *(unsigned int*)(animationBytes + 0x5C) = 0xFFF0BDC1u;
        *(int*)(animationBytes + 0x64) = 0;
        *(unsigned int**)(animationBytes + 0x68) = &DAT_00476f78;
        *timerFlags |= 1;
    }
    *(int*)(animationBytes + 0x60) = 0;
    *(int*)(animationBytes + 0x64) = 0;
    *(int*)(animationBytes + 0x5C) = -1;
    entity->AnimationFlags() &= ~1u;

    AnimationObject_ExecuteScript(animation);
    ++*(int*)((uint8_t*)g_pGameStateManager + 0x4C);
}

void AnimationObject_LoadScript(
    AnimationObject* animation, void* resource, int animationIndex) {
    AnimationObject_LoadScriptInternal(
        animation, resource, animationIndex, true);
}

void AnimationObject_LoadScriptPreservingState(
    AnimationObject* animation, void* resource, int animationIndex) {
    AnimationObject_LoadScriptInternal(
        animation, resource, animationIndex, false);
}

// 0x0043E8B0 - Switch an existing object to another script without running
// the entity constructor. Invalid or currently-loading resources are ignored.
void AnimationObject_ChangeScript(
    AnimationObject* animation, void* resource, int animationIndex) {
    uint8_t* bytes = (uint8_t*)animation;
    uint8_t* resourceBytes = (uint8_t*)resource;
    void** scripts = *(void***)(resourceBytes + 0x11C);
    void* script = scripts[animationIndex];
    if (script == 0 || *(int*)(resourceBytes + 0x124) != 0) {
        return;
    }

    Entity* entity = (Entity*)animation;
    entity->ScriptIndex() = (short)animationIndex;
    entity->ScriptResource() = resource;
    if ((entity->AnimationFlags() & 0x200u) != 0) {
        *(float*)(bytes + 0x3C) *= _DAT_00470b60;
        entity->AnimationFlags() =
            (entity->AnimationFlags() | 8u) ^ 0x200u;
    }
    *(unsigned short*)(bytes + 0x35C) = 7;
    *(int*)(bytes + 0x2FC) = -1;
    *(int*)(bytes + 0x60) = 0;
    *(int*)(bytes + 0x64) = 0;
    *(unsigned int*)(bytes + 0x5C) = 0xFFF0BDC1u;
    const unsigned int resetOffsets[] = {
        0xB4, 0x100, 0x12C, 0x178, 0x1B4, 0x200, 0x22C
    };
    for (unsigned int index = 0;
         index != sizeof(resetOffsets) / sizeof(resetOffsets[0]); ++index) {
        *(int*)(bytes + resetOffsets[index]) = 0;
    }
    entity->ScriptResourceId() = *(unsigned short*)resourceBytes;
    entity->ScriptResource() = resource;
    entity->AnimationFlags() &= 0xFFFFF9FFu;
    entity->ScriptBase() = script;
    entity->ScriptCursor() = script;

    unsigned int* timerFlags = (unsigned int*)(bytes + 0x6C);
    if ((*timerFlags & 1u) == 0) {
        *(int*)(bytes + 0x60) = 0;
        *(unsigned int*)(bytes + 0x5C) = 0xFFF0BDC1u;
        *(int*)(bytes + 0x64) = 0;
        *(unsigned int**)(bytes + 0x68) = &DAT_00476f78;
        *timerFlags |= 1u;
    }
    *(int*)(bytes + 0x60) = 0;
    *(int*)(bytes + 0x64) = 0;
    *(int*)(bytes + 0x5C) = -1;
    entity->AnimationFlags() &= ~1u;
    AnimationObject_ExecuteScript(animation);
    ++*(int*)((uint8_t*)g_pGameStateManager + 0x4C);
}

// 0x004496D0 - Handle-based script switch using the object's current resource.
void AnimationManager_ChangeScript(
    void* manager, const int* animationHandle, int animationIndex) {
    AnimationObject* animation =
        AnimationManager_Find(manager, *animationHandle);
    if (animation != 0) {
        AnimationObject_ChangeScript(
            animation, ((Entity*)animation)->ScriptResource(),
            animationIndex);
    }
}

// 0x00449870 - Initialize position/script state before selecting a script.
void AnimationObject_InitializeScriptState(
    AnimationObject* animation, void* resource, int animationIndex) {
    uint8_t* bytes = (uint8_t*)animation;
    Entity* entity = (Entity*)animation;
    entity->Position().x = 0.0f;
    entity->Position().y = 0.0f;
    entity->Position().z = 0.0f;
    entity->BasePosition().x = 0.0f;
    entity->BasePosition().y = 0.0f;
    entity->BasePosition().z = 0.0f;
    entity->RenderOffset().x = 0.0f;
    entity->RenderOffset().y = 0.0f;
    entity->AnimationFlags() |= 0x40000000u;
    entity->ScriptIndex() = (short)animationIndex;
    entity->RenderOffset().z = 0.0f;
    bytes[0x3A0] = 0x10;
    bytes[0x3A1] = 0x10;
    AnimationObject_LoadScriptPreservingState(
        animation, resource, animationIndex);
}

// 0x0043E5A0 - Apply one resource position record to an animation object.
// The clean entry makes the hidden object/resource/index registers explicit.
int AnimationObject_ConfigureFromResource(
    void* animation, void* resource, int animationIndex) {
    unsigned char* object = (unsigned char*)animation;
    unsigned char* resourceBytes = (unsigned char*)resource;
    if (*(uint32_t*)(resourceBytes + 0x108) == 0 ||
        *(uint32_t*)(resourceBytes + 0x124) != 0)
        return -1;

    *(int16_t*)(object + 0x384) = (int16_t)animationIndex;
    *(void**)(object + 0x308) = resource;
    unsigned char* record = *(unsigned char**)(resourceBytes + 0x118) +
        animationIndex * 0x44;
    *(void**)(object + 0x394) = record;
    *(uint32_t*)(object + 0x4C) = *(uint32_t*)(record + 0x34);
    *(uint32_t*)(object + 0x50) = *(uint32_t*)(record + 0x30);

    for (unsigned int offset = 0x23C; offset <= 0x2F4; offset += 4)
        *(uint32_t*)(object + offset) = 0;
    *(uint32_t*)(object + 0x23C) = 0x3F800000;
    *(uint32_t*)(object + 0x250) = 0x3F800000;
    *(uint32_t*)(object + 0x264) = 0x3F800000;
    *(uint32_t*)(object + 0x278) = 0x3F800000;
    *(uint32_t*)(object + 0x2D0) = 0x3F800000;
    *(uint32_t*)(object + 0x2E4) = 0x3F800000;
    *(uint32_t*)(object + 0x2F8) = 0x3F800000;

    float width = *(float*)(object + 0x4C);
    float height = *(float*)(object + 0x50);
    const float textureScale = 1.0f;
    *(float*)(object + 0x23C) = width * textureScale;
    *(float*)(object + 0x250) = height * textureScale;
    *(float*)(object + 0x2BC) =
        (*(float*)(record + 0x38) / *(float*)(record + 0x1C)) * width;
    *(float*)(object + 0x2D0) =
        (*(float*)(record + 0x3C) / *(float*)(record + 0x18)) * height;
    for (unsigned int offset = 0; offset != 0x40; offset += 4)
        *(uint32_t*)(object + 0x27C + offset) =
            *(uint32_t*)(object + 0x23C + offset);
    return 0;
}

#ifdef _MSC_VER
__declspec(naked) void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position) {
    __asm {
        mov eax, [esp+4]
        push eax
        call sub_4491C0
        test eax, eax
        jz locret_449347
        push edi
        mov edx, esi
        mov edi, [edx]
        lea ecx, [eax+340h]
        mov [ecx], edi
        mov edi, [edx+4]
        mov [ecx+4], edi
        mov edx, [edx+8]
        mov [ecx+8], edx
        mov ecx, [eax+18h]
        test ecx, ecx
        jnz loc_449346
        mov eax, [eax+14h]
        test eax, eax
        jz loc_449346
loc_449325:
        mov ecx, [eax]
        add ecx, 340h
        mov edx, esi
        mov edi, [edx]
        mov [ecx], edi
        mov edi, [edx+4]
        mov [ecx+4], edi
        mov edx, [edx+8]
        mov [ecx+8], edx
        mov eax, [eax+4]
        test eax, eax
        jnz loc_449325
loc_449346:
        pop edi
locret_449347:
        ret 4
    }
}
#else
void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return;
    }

    AnimationObject_SetPosition(animation, position);
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    if (childMembership->previous != 0) {
        return;
    }

    AnimationListNode* child = childMembership->next;
    while (child != 0) {
        AnimationObject_SetPosition(child->animation, position);
        child = child->next;
    }
}
#endif

// 0x00449350 - Apply the gameplay-to-render translation and propagate it.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_SetTranslatedPosition(
    void* manager, int animationHandle, const float* position) {
    __asm {
        mov eax, [esp+4]
        push eax
        call sub_4491C0
        test eax, eax
        jz locret_4493BC
        fld dword ptr [esi]
        fadd [flt_470B4C]
        fstp dword ptr [eax+340h]
        fld dword ptr [esi+4]
        fadd [flt_470B48]
        fstp dword ptr [eax+344h]
        mov ecx, [esi+8]
        mov [eax+348h], ecx
        mov ecx, [eax+18h]
        test ecx, ecx
        jnz locret_4493BC
        mov ecx, [eax+14h]
        test ecx, ecx
        jz locret_4493BC
loc_449392:
        fld dword ptr [esi]
        mov eax, [ecx]
        fadd [flt_470B4C]
        add eax, 340h
        fstp dword ptr [eax]
        fld dword ptr [esi+4]
        fadd [flt_470B48]
        fstp dword ptr [eax+4]
        mov edx, [esi+8]
        mov [eax+8], edx
        mov ecx, [ecx+4]
        test ecx, ecx
        jnz loc_449392
locret_4493BC:
        ret 4
    }
}
#else
void AnimationManager_SetTranslatedPosition(
    void* manager, int animationHandle, const float* position) {
    float translated[3] = {
        position[0] + _DAT_00470b4c,
        position[1] + _DAT_00470b48,
        position[2]
    };
    AnimationManager_SetPosition(manager, animationHandle, translated);
}
#endif

// 0x00449450 - Clear a stale animation handle after a failed lookup.
#ifdef _MSC_VER
__declspec(naked) bool AnimationManager_ValidateHandle(
        void* manager, int* animationHandle) {
    __asm {
        mov eax, [esi]
        mov edx, dword_491C10
        push eax
        call sub_4491C0
        test eax, eax
        jnz locret_449464
        mov [esi], eax
locret_449464:
        ret
    }
}
#else
bool AnimationManager_ValidateHandle(
    void* manager, int* animationHandle) {
    if (AnimationManager_Find(manager, *animationHandle) != 0) {
        return true;
    }
    *animationHandle = 0;
    return false;
}
#endif

// 0x00449630 - Mark an object tree for removal and invalidate its owner handle.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_MarkForRemovalAndClearHandle(
    void* manager, int* animationHandle) {
    __asm {
        mov eax, [esi]
        mov edx, dword_491C10
        push eax
        call sub_4492A0
        mov dword ptr [esi], 0
        ret
    }
}
#else
void AnimationManager_MarkForRemovalAndClearHandle(
    void* manager, int* animationHandle) {
    AnimationManager_SetFlag(
        manager, *animationHandle, 0x04000000u);
    *animationHandle = 0;
}
#endif


// 0x00449670 - Select a sprite from the object's current script resource.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_SelectSpriteFromCurrentResource(
        void* manager, const int* animationHandle, int spriteIndex,
        AnimationSpriteSelector selector) {
    __asm {
        mov ecx, [eax]
        mov edx, dword_491C10
        push ecx
        call sub_4491C0
        test eax, eax
        jz locret_449691
        mov edx, [esp+4]
        mov ecx, [eax+308h]
        call sub_43E5A0
locret_449691:
        ret 4
    }
}
#else
int AnimationManager_SelectSpriteFromCurrentResource(
    void* manager, const int* animationHandle, int spriteIndex,
    AnimationSpriteSelector selector) {
    AnimationObject* animation =
        AnimationManager_Find(manager, *animationHandle);
    if (animation == 0) {
        return -1;
    }
    return selector(
        animation, ((Entity*)animation)->ScriptResource(), spriteIndex);
}
#endif

// 0x004496A0 - Select a sprite from an explicitly supplied resource.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_SelectSpriteFromResource(
        void* manager, const int* animationHandle, void* resource,
        int spriteIndex, AnimationSpriteSelector selector) {
    __asm {
        mov ecx, [eax]
        mov edx, dword_491C10
        push ecx
        call sub_4491C0
        test eax, eax
        jz locret_4496BF
        mov edx, [esp+8]
        mov ecx, [esp+4]
        call sub_43E5A0
locret_4496BF:
        ret 8
    }
}
#else
int AnimationManager_SelectSpriteFromResource(
    void* manager, const int* animationHandle, void* resource,
    int spriteIndex, AnimationSpriteSelector selector) {
    AnimationObject* animation =
        AnimationManager_Find(manager, *animationHandle);
    if (animation == 0) {
        return -1;
    }
    return selector(animation, resource, spriteIndex);
}
#endif

static AnimationObject** AnimationManager_RenderBucketHead(
    void* manager, unsigned int bucketIndex) {
    AnimationObject* sentinel =
        (AnimationObject*)((uint8_t*)manager + 0x72DAE4 +
                           bucketIndex * 0x3AC);
    return AnimationObject_RenderChainSlot(sentinel);
}

static bool AnimationManager_UpdateObject(
    void* manager, AnimationObject* animation) {
    if ((((Entity*)animation)->AnimationFlags() & 0x04000000u) != 0) {
        AnimationManager_RemoveObject(manager, animation);
        return false;
    }

    AnimationUpdateCallback callback =
        AnimationObject_UpdateCallback(animation);
    if (callback != 0) {
        callback(animation);
    }
    if (AnimationObject_ExecuteScript(animation) != 0) {
        AnimationManager_RemoveObject(manager, animation);
        return false;
    }
    return true;
}

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_UpdatePrimary(void* manager) {
    __asm {
        sub esp, 50h
        push ebp
        push edi
        mov edi, eax
        xor ebp, ebp
        xor eax, eax
        lea ecx, [edi+72DAE4h]
init_loop:
        mov [esp+eax*4+8], ecx
        mov [ecx+1Ch], ebp
        inc eax
        add ecx, 3ACh
        cmp eax, 13h
        jl init_loop
        mov eax, [edi+72DAD4h]
        cmp eax, ebp
        je done
        push ebx
        push esi
update_loop:
        mov esi, [eax]
        mov ebx, [eax+4]
        test dword ptr [esi+35Ch], 4000000h
        je not_flagged
        call sub_448BB0
        jmp next
not_flagged:
        mov eax, [esi+398h]
        cmp eax, ebp
        je no_callback
        mov ecx, esi
        call eax
no_callback:
        push esi
        call sub_43EE30
        test eax, eax
        je keep
        call sub_448BB0
        jmp next
keep:
        mov eax, [esi+20h]
        mov ecx, [esp+eax*4+10h]
        mov [ecx+1Ch], esi
        mov edx, [esi+20h]
        mov [esp+edx*4+10h], esi
        mov [esi+1Ch], ebp
next:
        mov edx, [edi+64h]
        inc edx
        cmp ebx, ebp
        mov [edi+64h], edx
        mov eax, ebx
        jne update_loop
        pop esi
        pop ebx
done:
        pop edi
        mov eax, 1
        pop ebp
        add esp, 50h
        ret
    }
}
#else
int AnimationManager_UpdatePrimary(void* manager) {
    AnimationObject* tails[19];
    for (unsigned int index = 0; index != 19; ++index) {
        AnimationObject* sentinel =
            (AnimationObject*)((uint8_t*)manager + 0x72DAE4 +
                               index * 0x3AC);
        tails[index] = sentinel;
        *AnimationObject_RenderChainSlot(sentinel) = 0;
    }

    AnimationListNode* node = AnimationManager_List(manager, 0);
    while (node != 0) {
        AnimationObject* animation = node->animation;
        node = node->next;
        if (AnimationManager_UpdateObject(manager, animation)) {
            int bucket = *AnimationObject_RenderBucketSlot(animation);
            *AnimationObject_RenderChainSlot(tails[bucket]) = animation;
            tails[bucket] = animation;
            *AnimationObject_RenderChainSlot(animation) = 0;
        }
        ++*(unsigned int*)((uint8_t*)manager + 0x64);
    }
    return 1;
}
#endif

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_UpdateSecondary(void* manager) {
    __asm {
        push ebp
        push edi
        mov edi, eax
        mov eax, [edi+72DADCh]
        xor ecx, ecx
        cmp eax, ecx
        mov [edi+7320C4h], ecx
        lea ebp, [edi+7320A8h]
        mov [edi+64h], ecx
        je done
        push ebx
        push esi
update_loop:
        mov esi, [eax]
        mov ebx, [eax+4]
        test dword ptr [esi+35Ch], 4000000h
        je not_flagged
        call sub_448BB0
        jmp next
not_flagged:
        mov eax, [esi+398h]
        test eax, eax
        je no_callback
        mov ecx, esi
        call eax
no_callback:
        push esi
        call sub_43EE30
        test eax, eax
        je keep
        call sub_448BB0
        jmp next
keep:
        mov [ebp+1Ch], esi
        mov ebp, esi
        mov dword ptr [esi+1Ch], 0
next:
        mov edx, [edi+64h]
        inc edx
        test ebx, ebx
        mov [edi+64h], edx
        mov eax, ebx
        jne update_loop
        pop esi
        pop ebx
done:
        pop edi
        mov eax, 1
        pop ebp
        ret
    }
}
#else
int AnimationManager_UpdateSecondary(void* manager) {
    AnimationObject* sentinel =
        (AnimationObject*)((uint8_t*)manager + 0x72DAE4 + 19 * 0x3AC);
    AnimationObject* tail = sentinel;
    *AnimationObject_RenderChainSlot(sentinel) = 0;
    *(unsigned int*)((uint8_t*)manager + 0x64) = 0;

    AnimationListNode* node = AnimationManager_List(manager, 1);
    while (node != 0) {
        AnimationObject* animation = node->animation;
        node = node->next;
        if (AnimationManager_UpdateObject(manager, animation)) {
            *AnimationObject_RenderChainSlot(tail) = animation;
            tail = animation;
            *AnimationObject_RenderChainSlot(animation) = 0;
        }
        ++*(unsigned int*)((uint8_t*)manager + 0x64);
    }
    return 1;
}
#endif

#ifdef _MSC_VER
__declspec(naked) int AnimationManager_RenderBucket(
    void* manager, int bucketIndex) {
    __asm {
        imul eax, 3ACh
        push esi
        mov esi, [eax+edi+72DB00h]
        test esi, esi
        jz loc_4489BC
loc_448992:
        test dword ptr [esi+35Ch], 4000000h
        jnz loc_4489B5
        mov eax, [esi+39Ch]
        test eax, eax
        jz loc_4489AC
        mov ecx, esi
        call eax
loc_4489AC:
        mov eax, esi
        mov ecx, edi
        call sub_4451C0
loc_4489B5:
        mov esi, [esi+1Ch]
        test esi, esi
        jnz loc_448992
loc_4489BC:
        mov eax, 1
        pop esi
        ret
    }
}
#else
int AnimationManager_RenderBucket(void* manager, int bucketIndex) {
    AnimationObject* animation =
        *AnimationManager_RenderBucketHead(manager, (unsigned int)bucketIndex);
    while (animation != 0) {
        if ((((Entity*)animation)->AnimationFlags() & 0x04000000u) == 0) {
            AnimationDrawCallback callback =
                AnimationObject_DrawCallback(animation);
            if (callback != 0) {
                callback(animation);
            }
            AnimationObject_Render(manager, animation);
        }
        animation = *AnimationObject_RenderChainSlot(animation);
    }
    return 1;
}
#endif

// 0x004497D0 - Resolve a direct child by script index.
#ifdef _MSC_VER
__declspec(naked) int AnimationManager_FindChildByScriptIndex(
        void* manager, int animationHandle, short scriptIndex) {
    __asm {
        mov eax, [esi]
        mov edx, dword_491C10
        push eax
        call sub_4491C0
        test eax, eax
        jne after_find
        mov [esi], eax
after_find:
        add eax, 10h
        je not_found
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
search_loop:
        mov ecx, [eax]
        movsx edx, word ptr [ecx+38Ah]
        cmp edx, ebx
        je found
        mov eax, [eax+4]
        test eax, eax
        jne search_loop
not_found:
        mov dword ptr [edi], 0
        mov eax, edi
        ret
found:
        mov eax, [eax]
        mov ecx, [eax]
        mov [edi], ecx
        mov eax, edi
        ret
    }
}
#else
int AnimationManager_FindChildByScriptIndex(
    void* manager, int animationHandle, short scriptIndex) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return 0;
    }

    AnimationListNode* child =
        AnimationObject_ChildMembership(animation)->next;
    while (child != 0) {
        AnimationObject* childAnimation = child->animation;
        if (((Entity*)childAnimation)->ScriptIndex() == scriptIndex) {
            return *(int*)childAnimation;
        }
        child = child->next;
    }
    return 0;
}
#endif

#ifdef _MSC_VER
__declspec(naked) int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position) {
    __asm {
        push ebx
        push ebp
        mov ebp, [esp+8+8]
        push esi
        mov esi, dword_491C10
        call sub_449950
        mov esi, eax
        mov eax, [esi+35Ch]
        mov ebx, [esp+0Ch+0Ch]
        mov ecx, [esp+0Ch+4]
        mov dword ptr [esi+20h], 0
        or eax, 40000000h
        mov [esi+35Ch], eax
        fld dword ptr [edi]
        fadd [flt_470B4C]
        fstp dword ptr [esi+340h]
        fld dword ptr [edi+4]
        fadd [flt_470B48]
        fstp dword ptr [esi+344h]
        mov eax, [edi+8]
        mov [esi+348h], eax
        mov eax, esi
        call sub_43E710
        mov edx, dword_491C10
        mov ebx, esi
        mov eax, ebp
        call sub_4489D0
        pop esi
        pop ebp
        pop ebx
        ret 0Ch
    }
}
#else
int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position) {
    AnimationObject* animation =
        AnimationManager_AllocateObject(g_pGameStateManager);
    if (animation == 0) {
        return 0;
    }

    uint8_t* bytes = (uint8_t*)animation;
    *(unsigned int*)(bytes + 0x20) = 0;
    ((Entity*)animation)->AnimationFlags() |= 0x40000000u;
    float translated[3] = {
        position[0] + _DAT_00470b4c,
        position[1] + _DAT_00470b48,
        position[2]
    };
    AnimationObject_SetPosition(animation, translated);
    AnimationObject_LoadScript(animation, resource, animationIndex);

    int handle =
        AnimationManager_RegisterObject(g_pGameStateManager, animation);
    *(int*)scratch = handle;
    return handle;
}
#endif

// 0x00447F70 - Release the three indexed resource slots owned by a manager.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_ClearIndexedResources(
    void* manager, unsigned int index,
    void (*release)(void*), void (*free_memory)(void*)) {
    __asm {
        mov eax, [edi+esi*4+3AD4E0h]
        push ebx
        xor ebx, ebx
        cmp eax, ebx
        jz loc_447F8B
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+8]
        mov [edi+esi*4+3AD4E0h], ebx
loc_447F8B:
        mov eax, [edi+esi*4+3AD560h]
        cmp eax, ebx
        jz loc_447FA3
        mov edx, [eax]
        push eax
        call dword ptr [edx+8]
        mov [edi+esi*4+3AD560h], ebx
loc_447FA3:
        mov eax, [edi+esi*4+3AD5E0h]
        cmp eax, ebx
        jz loc_447FBE
        push eax
        call _free
        add esp, 4
        mov [edi+esi*4+3AD5E0h], ebx
loc_447FBE:
        mov [edi+esi*4+3AD5E0h], ebx
        pop ebx
        ret
    }
}
#else
void AnimationManager_ClearIndexedResources(void* manager, unsigned int index,
        void (*release)(void*), void (*free_memory)(void*)) {
    uint8_t* bytes = (uint8_t*)manager;
    void** first = (void**)(bytes + 0x3AD4E0 + index * 4);
    void** second = (void**)(bytes + 0x3AD560 + index * 4);
    void** memory = (void**)(bytes + 0x3AD5E0 + index * 4);
    if (*first != 0) { if (release) release(*first); *first = 0; }
    if (*second != 0) { if (release) release(*second); *second = 0; }
    if (*memory != 0) { if (free_memory) free_memory(*memory); *memory = 0; }
}
#endif

// 0x004477D0 - Release and free one of the manager's 33 resource slots.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_ClearResourceSlot(
        void* manager, int index, void (*release)(void*),
        void (*free_memory)(void*)) {
    __asm {
        test esi, esi
        jl locret_447806
        cmp esi, 21h
        jnb locret_447806
        push edi
        mov edi, [ebx+esi*4+3AD06Ch]
        test edi, edi
        jz loc_447805
        call sub_447810
        mov eax, [ebx+esi*4+3AD06Ch]
        push eax
        call j__free
        add esp, 4
        mov dword ptr [ebx+esi*4+3AD06Ch], 0
loc_447805:
        pop edi
locret_447806:
        ret
    }
}
#else
void AnimationManager_ClearResourceSlot(void* manager, int index,
                                        void (*release)(void*),
                                        void (*free_memory)(void*)) {
    if (index < 0 || index >= 0x21)
        return;
    void** slot = (void**)((uint8_t*)manager + 0x3AD06C + index * 4);
    if (*slot == 0)
        return;
    void* resource = *slot;
    if (release != 0)
        release(resource);
    if (free_memory != 0)
        free_memory(resource);
    *slot = 0;
}
#endif

// 0x0043E460 - Install a resource record in the first free manager slot.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_RegisterResource(
        void* manager, unsigned int index,
        const char* name, int value, int flags) {
    __asm {
        push esi
        mov esi, eax
        xor eax, eax
        lea ecx, [esi+1F88h]
        jmp search_loop
        _emit 0x8D
        _emit 0x49
        _emit 0x00
search_loop:
        cmp dword ptr [ecx], 0
        je found
        inc eax
        add ecx, 10Ch
        cmp eax, 1Fh
        jl search_loop
        pop esi
        ret 8
found:
        imul eax, eax, 10Ch
        lea ecx, [eax+esi]
        mov eax, [esp+8]
        mov [ecx+1F88h], eax
        mov eax, [esp+0Ch]
        lea esi, [ecx+1F94h]
        mov [ecx+1F8Ch], eax
        mov eax, edx
        sub esi, edx
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
copy_name:
        mov dl, [eax]
        mov [esi+eax], dl
        inc eax
        test dl, dl
        jne copy_name
        mov dword ptr [ecx+1F90h], 0
        pop esi
        ret 8
    }
}
#else
void AnimationManager_RegisterResource(void* manager, unsigned int index,
        const char* name, int value, int flags) {
    uint8_t* bytes = (uint8_t*)manager;
    for (unsigned int slot = 0; slot != 0x1f; ++slot) {
        uint8_t* record = bytes + 0x1f88 + slot * 0x10c;
        if (*(int*)record == 0) {
            *(int*)record = value;
            *(int*)(record + 4) = flags;
            char* destination = (char*)(record + 0xc);
            while ((*destination++ = *name++) != 0) {}
            *(int*)(record + 8) = 0;
            return;
        }
    }
    (void)index;
}
#endif

// 0x0043DC90 - Queue a resource pointer in the matching indexed bucket.
#ifdef _MSC_VER
__declspec(naked) void AnimationManager_QueueResource(
        void* manager, int resource_id, void* resource) {
    __asm {
        push ebx
        movsx ebx, word ptr [edi*8+word_4749CE]
        push ebp
        mov ebp, [esp+0Ch]
        push esi
        xor eax, eax
        lea edx, [ecx+620h]
search_loop:
        mov esi, [edx]
        test esi, esi
        jl new_bucket
        cmp esi, edi
        je existing_bucket
        inc eax
        add edx, 4
        cmp eax, 0Ch
        jl search_loop
        pop esi
        pop ebp
        pop ebx
        ret 4
existing_bucket:
        mov edx, [ecx+eax*4+650h]
        cmp edx, 80h
        jge done
        mov esi, eax
        shl esi, 7
        add esi, edx
        mov [ecx+esi*4+680h], ebp
        jmp inc_count
new_bucket:
        cmp eax, 0Ch
        jge done
        mov edx, eax
        mov [ecx+eax*4+620h], edi
        shl edx, 9
        mov [ecx+edi*4+408h], ebx
        mov [edx+ecx+680h], ebp
inc_count:
        inc dword ptr [ecx+eax*4+650h]
done:
        pop esi
        pop ebp
        pop ebx
        ret 4
    }
}
#else
void AnimationManager_QueueResource(void* manager, int resource_id,
                                    void* resource) {
    uint8_t* bytes = (uint8_t*)manager;
    for (int bucket = 0; bucket != 12; ++bucket) {
        int* id = (int*)(bytes + 0x620 + bucket * 4);
        int* count = (int*)(bytes + 0x650 + bucket * 4);
        if (*id < 0) {
            *id = resource_id;
            *count = 0;
            *(void**)(bytes + 0x680 + bucket * 0x200) = resource;
            return;
        }
        if (*id == resource_id) {
            if (*count < 0x80)
                *(void**)(bytes + 0x680 + bucket * 0x200 + *count * 4) = resource;
            ++*count;
            return;
        }
    }
}
#endif

// 0x004054B0 - Configure the resource manager with the requested value and
// its decimal tens/ones digits, in retail call order.
void AnimationManager_ConfigureDigitTriplet(
    void* resource_manager, int value, int number,
    int (*configure)(void*, int)) {
    if (configure == 0)
        return;
    configure(resource_manager, value);
    configure(resource_manager, number / 10 + 8);
    configure(resource_manager, number % 10 + 8);
}
