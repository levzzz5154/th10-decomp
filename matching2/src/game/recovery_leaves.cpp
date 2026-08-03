#include "th10/game/recovery_leaves.hpp"

#ifndef _MSC_VER
#include <cstring>
#else
extern "C" void* memset(void*, int, unsigned long);
extern "C" void* memmove(void*, const void*, unsigned long);
extern "C" unsigned int strlen(const char*);
extern "C" char* strrchr(const char*, int);
extern "C" void sub_401A50(void);
extern "C" void sub_419650(void);
extern "C" void sub_427960(void);
extern "C" void sub_4223F0(void);
extern "C" void sub_40DAE0(void);
extern "C" void j__free(void*);
extern "C" void sub_44D080(void);
extern "C" void sub_44FF80(void);
extern "C" void sub_44BF40(void*);
extern "C" float flt_476F78;
extern "C" unsigned long dword_497D8C;
extern "C" float flt_470B4C;
extern "C" float flt_470B48;
extern "C" float flt_497D80;
extern "C" float flt_497D84;
extern "C" unsigned long dword_497D88;
extern "C" int _rand(void);
extern "C" unsigned long dword_477830;
extern "C" char off_4705D8;
extern "C" void* __imp_CloseHandle;
extern "C" void sub_43CB00(void*);
extern "C" void sub_44D730(void*);
extern "C" unsigned long dword_477818;
extern "C" void sub_41BB00(void*, unsigned long, int, float, float);
extern "C" void sub_40C9D0(void*);
extern "C" char* _strchr(const char*, int);
extern "C" void sub_41A0A0(char*);
extern "C" char off_4703E4;
extern "C" unsigned long dword_477820;
extern "C" unsigned long dword_4977A4;
extern "C" void* __imp_SetFilePointer;
extern "C" int sub_43D2A0(void*);
extern "C" void sub_44DCA0(void*);
#endif

static float NormalizeRecoveryAngle(float angle) {
    int iterations = 0;
    while (angle > 3.1415927f) {
        angle -= 6.2831855f;
        if (iterations++ > 0x20) break;
    }
    while (angle < -3.1415927f) {
        angle += 6.2831855f;
        if (iterations++ > 0x20) break;
    }
    return angle;
}

// 0x004198C0 - Linear lookup of a UTF-16 name, returning the matching entry's
// value (the second word in each eight-byte table record).
unsigned long Recovery_FindNamedValue(const unsigned short* name,
                                      const void* entries, int count) {
    if (name == 0 || entries == 0 || count <= 0) return 0;
    const unsigned char* table = (const unsigned char*)entries;
    for (int index = 0; index < count; ++index) {
        const unsigned short* candidate = *(const unsigned short**)(table + index * 8);
        if (candidate == 0) continue;
        const unsigned short* left = name;
        const unsigned short* right = candidate;
        while (*left == *right && *left != 0) {
            ++left;
            ++right;
        }
        if (*left == *right)
            return *(const unsigned long*)(table + index * 8 + 4);
    }
    return 0;
}

// 0x00401520 - One-instruction game-thread queue dispatch wrapper.
#ifdef _MSC_VER
__declspec(naked) void GameThread_RunQueueLeaf(void (*run)(void)) {
    // Retail is a two-instruction thunk: it forwards ECX through EBX to
    // 0x00401A50 without touching the stack argument.
    __asm {
        push ebx
        mov ebx, ecx
        call sub_401A50
        pop ebx
        ret
    }
}
#else
void GameThread_RunQueueLeaf(void (*run)(void)) {
    if (run != 0) run();
}
#endif

// 0x0040CC50 - Bullet deleting destructor wrapper.
#ifdef _MSC_VER
__declspec(naked) void* Bullet_DeletingDestructor(void* object,
                                                  RecoveryByte flags,
                                                  void (*destroy)(void*),
                                                  void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        push esi
        call sub_40DAE0
        test byte ptr [esp+8], 1
        jz loc_40CC69
        push esi
        call j__free
        add esp, 4
loc_40CC69:
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
void* Bullet_DeletingDestructor(void* object, RecoveryByte flags,
                                void (*destroy)(void*),
                                void (*free_memory)(void*)) {
    if (destroy != 0) destroy(object);
    if ((flags & 1) != 0 && free_memory != 0) free_memory(object);
    return object;
}
#endif

// 0x0044CF00 - Platform collection deleting destructor wrapper.
#ifdef _MSC_VER
__declspec(naked) void* Platform_DeletingDestructor(void* object,
                                                    RecoveryByte flags,
                                                    void (*destroy)(void*),
                                                    void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        call sub_44D080
        test byte ptr [esp+8], 1
        jz loc_44CF18
        push esi
        call j__free
        add esp, 4
loc_44CF18:
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
void* Platform_DeletingDestructor(void* object, RecoveryByte flags,
                                  void (*destroy)(void*),
                                  void (*free_memory)(void*)) {
    if (destroy != 0) destroy(object);
    if ((flags & 1) != 0 && free_memory != 0) free_memory(object);
    return object;
}
#endif

// 0x00412AA0 - Forward an opcode and float operand to the ECL runtime leaf.
#ifdef _MSC_VER
__declspec(naked) void Ecl_ForwardFloat(RecoveryByte opcode, float value,
                                        void (*forward)(RecoveryByte, float)) {
    __asm {
        mov ecx, [esp+8]
        mov eax, [eax+14D8h]
        mov eax, [eax+4]
        push ecx
        mov ecx, [esp+4+4]
        call sub_44FF80
        ret 8
    }
}
#else
void Ecl_ForwardFloat(RecoveryByte opcode, float value,
                      void (*forward)(RecoveryByte, float)) {
    if (forward != 0) forward(opcode, value);
}
#endif

// 0x00413200 - Insert a node immediately after an intrusive-list position.
#ifdef _MSC_VER
__declspec(naked) void ScoreList_InsertAfter(RecoveryListNode* position,
                                             RecoveryListNode* node) {
    __asm {
        mov edx, [ecx+4]
        test edx, edx
        jz loc_413210
        mov [eax+4], edx
        mov edx, [ecx+4]
        mov [edx+8], eax
loc_413210:
        mov [ecx+4], eax
        mov [eax+8], ecx
        ret
    }
}
#else
void ScoreList_InsertAfter(RecoveryListNode* position, RecoveryListNode* node) {
    if (position->next != 0) {
        node->next = position->next;
        position->next->previous = node;
    }
    position->next = node;
    node->previous = position;
}
#endif

// 0x00412720 - Publish one 16-byte ECL resource slot. Negative resource
// identifiers only replace the identifier, preserving the other words.
#ifdef _MSC_VER
__declspec(naked) void Ecl_SetResourceSlot(void* state, int slot,
                                           int resource, RecoveryWord first,
                                           RecoveryWord second) {
    __asm {
        mov eax, edx
        shl eax, 4
        add eax, esi
        test ecx, ecx
        mov [eax+2494h], ecx
        jl locret_41274D
        mov ecx, [esp+4]
        add edx, 24Ah
        shl edx, 4
        mov [eax+2498h], ecx
        mov [eax+249Ch], edi
        mov [edx+esi], edi
locret_41274D:
        ret 4
    }
}
#else
void Ecl_SetResourceSlot(void* state, int slot, int resource,
                         RecoveryWord first, RecoveryWord second) {
    RecoveryByte* record = (RecoveryByte*)state + 0x2494 + slot * 0x10;
    *(int*)record = resource;
    if (resource >= 0) {
        *(RecoveryWord*)(record + 4) = first;
        *(RecoveryWord*)(record + 8) = second;
        *(RecoveryWord*)(record + 12) = second;
    }
}
#endif

// 0x00413790 - Enable the first count animation records and disable the
// remainder of the fixed nine-record table.
#ifdef _MSC_VER
__declspec(naked) void Animation_SetActiveCount(void* state, int count) {
    __asm {
        xor edx, edx
        test ecx, ecx
        push edi
        mov edi, eax
        jle loc_4137B5
        push esi
        lea eax, [edi+4CDCh]
        mov esi, ecx
        mov edx, ecx
loc_4137A4:
        or dword ptr [eax], 2
        add eax, 3ACh
        dec esi
        jnz loc_4137A4
        cmp ecx, 9
        pop esi
        jge loc_4137DB
loc_4137B5:
        mov eax, edx
        imul eax, 3ACh
        mov ecx, 9
        lea eax, [eax+edi+4CDCh]
        sub ecx, edx
        jmp loc_4137D0
        align 10h
loc_4137D0:
        and dword ptr [eax], 0FFFFFFFDh
        add eax, 3ACh
        dec ecx
        jnz loc_4137D0
loc_4137DB:
        pop edi
        ret
    }
}
#else
void Animation_SetActiveCount(void* state, int count) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    int index = 0;
    for (; index < count; ++index)
        *(RecoveryWord*)(bytes + 0x4CDC + index * 0x3AC) |= 2;
    if (index > 9) return;
    for (; index < 9; ++index)
        *(RecoveryWord*)(bytes + 0x4CDC + index * 0x3AC) &= ~2u;
}
#endif

// 0x00412DB0 - Lazily initialize, then reset, an embedded timer record.
#ifdef _MSC_VER
__declspec(naked) void RecoveryTimer_Reset(RecoveryTimerState* timer,
                                           const void* default_speed) {
    __asm {
        mov ecx, [eax+30h]
        xor edx, edx
        test cl, 1
        jnz loc_412DD4
        or ecx, 1
        mov [eax+24h], edx
        mov dword ptr [eax+20h], 0FFF0BDC1h
        mov [eax+28h], edx
        mov dword ptr [eax+2Ch], offset flt_476F78
        mov [eax+30h], ecx
loc_412DD4:
        mov [eax+24h], edx
        mov [eax+28h], edx
        mov dword ptr [eax+20h], 0FFFFFFFFh
        ret
    }
}
#else
void RecoveryTimer_Reset(RecoveryTimerState* timer, const void* default_speed) {
    if ((timer->initialized & 1) == 0) {
        timer->current = 0;
        timer->value = 0xFFF0BDC1u;
        timer->previous = 0;
        timer->speed = default_speed;
        timer->initialized |= 1;
    }
    timer->current = 0;
    timer->previous = 0;
    timer->value = 0xFFFFFFFFu;
}
#endif

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);

// 0x00413270 - Elliptical polar conversion with independent X/Y radii.
#ifdef _MSC_VER
__declspec(naked) void Vector2_SetEllipticPolar(Vector2* destination,
                                                float angle, float x_radius,
                                                float y_radius) {
    __asm {
        push ecx
        mov [esp], ecx
        mov eax, [esp]
        fld [esp+8]
        fsincos
        fmul [esp+0Ch]
        fstp dword ptr [eax]
        fmul [esp+10h]
        fstp dword ptr [eax+4]
        pop ecx
        ret 0Ch
    }
}
#else
void Vector2_SetEllipticPolar(Vector2* destination, float angle,
                             float x_radius, float y_radius) {
    destination->x = (float)cos(angle) * x_radius;
    destination->y = (float)sin(angle) * y_radius;
}
#endif

// 0x00441EF0 - Animation-side circular polar conversion leaf.
#ifdef _MSC_VER
__declspec(naked) void Vector2_SetAnimationPolar(Vector2* destination,
                                                  float angle, float length) {
    __asm {
        push ecx
        mov [esp], ecx
        mov eax, [esp]
        fld [esp+8]
        fsincos
        fmul [esp+0Ch]
        fstp dword ptr [eax]
        fmul [esp+0Ch]
        fstp dword ptr [eax+4]
        pop ecx
        ret 8
    }
}
#else
void Vector2_SetAnimationPolar(Vector2* destination, float angle, float length) {
    destination->x = (float)cos(angle) * length;
    destination->y = (float)sin(angle) * length;
}
#endif

// 0x00417800 - Reset the path cursor/timer pair and clear its two trailing
// state words. The clean form exposes retail's global default-speed pointer.
#ifdef _MSC_VER
__declspec(naked) int PathState_Reset(void* state,
                                      RecoveryWord default_speed) {
    __asm {
        mov ecx, [eax+50h]
        xor edx, edx
        test cl, 1
        jnz loc_417824
        or ecx, 1
        mov [eax+44h], edx
        mov dword ptr [eax+40h], 0FFF0BDC1h
        mov [eax+48h], edx
        mov dword ptr [eax+4Ch], offset flt_476F78
        mov [eax+50h], ecx
loc_417824:
        mov [eax+44h], edx
        mov [eax+48h], edx
        mov dword ptr [eax+40h], 0FFFFFFFFh
        mov [eax+58h], edx
        mov [eax+5Ch], edx
        xor eax, eax
        ret
    }
}
#else
int PathState_Reset(void* state, RecoveryWord default_speed) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    RecoveryWord* flags = (RecoveryWord*)(bytes + 0x50);
    if ((*flags & 1) == 0) {
        *(RecoveryWord*)(bytes + 0x44) = 0;
        *(RecoveryWord*)(bytes + 0x40) = 0xFFF0BDC1u;
        *(RecoveryWord*)(bytes + 0x48) = 0;
        *(RecoveryWord*)(bytes + 0x4C) = default_speed;
        *flags |= 1;
    }
    *(RecoveryWord*)(bytes + 0x44) = 0;
    *(RecoveryWord*)(bytes + 0x48) = 0;
    *(RecoveryWord*)(bytes + 0x40) = 0xFFFFFFFFu;
    *(RecoveryWord*)(bytes + 0x58) = 0;
    *(RecoveryWord*)(bytes + 0x5C) = 0;
    return 0;
}
#endif

// 0x0044D5D0 - Invoke the configured interface operation, setting the
// in-progress marker first; missing owners return retail's initialization
// error code.
#ifdef _MSC_VER
__declspec(naked) int Platform_InvokeConfigured(
        void* interface_owner,
        int (*invoke)(void*, RecoveryWord, RecoveryWord)) {
    __asm {
        mov ecx, [eax+4]
        test ecx, ecx
        jnz loc_44D5DD
        mov eax, 800401F0h
        ret
loc_44D5DD:
        mov ecx, [ecx]
        push esi
        mov esi, [eax+24h]
        mov dword ptr [eax+30h], 1
        mov eax, [eax+20h]
        mov edx, [ecx]
        push esi
        push eax
        push 0
        push ecx
        call dword ptr [edx+30h]
        pop esi
        ret
    }
}
#else
int Platform_InvokeConfigured(void* interface_owner,
                              int (*invoke)(void*, RecoveryWord, RecoveryWord)) {
    RecoveryByte* bytes = (RecoveryByte*)interface_owner;
    void* interface_ptr = *(void**)(bytes + 4);
    if (interface_ptr == 0) return (int)0x800401F0u;
    *(RecoveryWord*)(bytes + 0x30) = 1;
    return invoke != 0 ? invoke(interface_ptr, *(RecoveryWord*)(bytes + 0x20),
                                *(RecoveryWord*)(bytes + 0x24)) : 0;
}
#endif

// 0x0044D550 - Run both shutdown operations over every interface and OR
// their status words, then clear the owner's active field.
#ifdef _MSC_VER
__declspec(naked) RecoveryWord Platform_AggregateInterfaces(
        void** interfaces, RecoveryWord count,
        RecoveryWord (*first)(void*), RecoveryWord (*second)(void*, int)) {
    __asm {
        mov eax, [edi+4]
        test eax, eax
        jnz loc_44D55D
        mov eax, 800401F0h
        ret
loc_44D55D:
        mov eax, [edi+10h]
        push ebx
        push esi
        xor ebx, ebx
        xor esi, esi
        test eax, eax
        mov [edi+30h], ebx
        jbe loc_44D596
        _emit 0x8D
        _emit 0x49
        _emit 0x00
loc_44D570:
        mov eax, [edi+4]
        mov eax, [eax+esi*4]
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+48h]
        mov edx, [edi+4]
        or ebx, eax
        mov eax, [edx+esi*4]
        mov ecx, [eax]
        push 0
        push eax
        call dword ptr [ecx+34h]
        or ebx, eax
        mov eax, [edi+10h]
        inc esi
        cmp esi, eax
        jb loc_44D570
loc_44D596:
        pop esi
        mov eax, ebx
        mov dword ptr [edi+1Ch], 0
        pop ebx
        ret
    }
}
#else
RecoveryWord Platform_AggregateInterfaces(
        void** interfaces, RecoveryWord count,
        RecoveryWord (*first)(void*), RecoveryWord (*second)(void*, int)) {
    if (interfaces == 0) return 0x800401F0u;
    RecoveryWord result = 0;
    for (RecoveryWord index = 0; index < count; ++index) {
        if (first != 0) result |= first(interfaces[index]);
        if (second != 0) result |= second(interfaces[index], 0);
    }
    return result;
}
#endif

// 0x00412ED0 - Change the score mode and invalidate the cached mode result.
#ifdef _MSC_VER
__declspec(naked) void Score_SetMode(void* state, int mode) {
    __asm {
        cmp [eax+44h], ecx
        mov [eax+44h], ecx
        jz locret_412EDF
        mov dword ptr [eax+4Ch], 0
locret_412EDF:
        ret
    }
}
#else
void Score_SetMode(void* state, int mode) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    int old_mode = *(int*)(bytes + 0x44);
    *(int*)(bytes + 0x44) = mode;
    if (old_mode != mode) *(RecoveryWord*)(bytes + 0x4C) = 0;
}
#endif

// 0x00413170 - Store an angle after folding it into the retail range.
void Score_SetNormalizedAngle(void* state, float angle) {
    *(float*)((RecoveryByte*)state + 0x1C) = NormalizeRecoveryAngle(angle);
}

// 0x0044D600 - OR the status returned by every configured interface.
#ifdef _MSC_VER
__declspec(naked) RecoveryWord Platform_QueryInterfaces(
        const RecoveryInterfaceArray* array,
        RecoveryWord (*query)(void*, RecoveryWord)) {
    __asm {
        mov eax, [edi+4]
        test eax, eax
        jnz loc_44D60D
        mov eax, 800401F0h
        ret
loc_44D60D:
        mov eax, [edi+10h]
        push ebx
        push esi
        xor ebx, ebx
        xor esi, esi
        test eax, eax
        jbe loc_44D638
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
loc_44D620:
        mov eax, [edi+4]
        mov eax, [eax+esi*4]
        mov ecx, [eax]
        push 0
        push eax
        call dword ptr [ecx+34h]
        or ebx, eax
        mov eax, [edi+10h]
        inc esi
        cmp esi, eax
        jb loc_44D620
loc_44D638:
        pop esi
        mov eax, ebx
        pop ebx
        ret
    }
}
#else
RecoveryWord Platform_QueryInterfaces(
        const RecoveryInterfaceArray* array,
        RecoveryWord (*query)(void*, RecoveryWord)) {
    if (array == 0 || array->entries == 0) return 0x800401F0u;
    RecoveryWord result = 0;
    for (RecoveryWord index = 0; index < array->count; ++index) {
        void* entry = array->entries[index];
        if (query != 0) result |= query(entry, 0);
    }
    return result;
}
#endif

// 0x0044D370 - Pick the first interface whose state is not flagged, falling
// back to the retail random-index selection when all entries are busy.
#ifdef _MSC_VER
__declspec(naked) void* Platform_FindAvailable(
        const RecoveryInterfaceArray* array, RecoveryWord initial_state,
        void (*read_state)(void*, RecoveryWord*),
        RecoveryWord (*random_index)(RecoveryWord)) {
    __asm {
        push ecx
        mov eax, [edi+4]
        test eax, eax
        jnz loc_44D37C
        xor eax, eax
        pop ecx
        ret
loc_44D37C:
        mov eax, [edi+10h]
        push esi
        xor esi, esi
        test eax, eax
        jbe loc_44D3B6
loc_44D386:
        mov eax, [edi+4]
        cmp dword ptr [eax+esi*4], 0
        jz loc_44D3AE
        mov ecx, eax
        mov dword ptr [esp+8-4], 0
        mov eax, [ecx+esi*4]
        mov edx, [eax]
        lea ecx, [esp+8-4]
        push ecx
        push eax
        call dword ptr [edx+24h]
        test byte ptr [esp+8-4], 1
        jz loc_44D3B6
loc_44D3AE:
        mov eax, [edi+10h]
        inc esi
        cmp esi, eax
        jb loc_44D386
loc_44D3B6:
        cmp esi, [edi+10h]
        jz loc_44D3C4
        mov edx, [edi+4]
        mov eax, [edx+esi*4]
        pop esi
        pop ecx
        ret
loc_44D3C4:
        call _rand
        xor edx, edx
        div dword ptr [edi+10h]
        mov eax, [edi+4]
        pop esi
        mov eax, [eax+edx*4]
        pop ecx
        ret
    }
}
#else
void* Platform_FindAvailable(
        const RecoveryInterfaceArray* array, RecoveryWord initial_state,
        void (*read_state)(void*, RecoveryWord*),
        RecoveryWord (*random_index)(RecoveryWord)) {
    if (array == 0 || array->entries == 0) return 0;
    RecoveryWord index = 0;
    for (; index < array->count; ++index) {
        void* entry = array->entries[index];
        if (entry == 0) continue;
        RecoveryWord state = 0;
        if (read_state != 0) read_state(entry, &state);
        else state = initial_state;
        if ((state & 1) == 0) return entry;
    }
    if (array->count == 0) return 0;
    RecoveryWord random = random_index != 0
        ? random_index(array->count) : 0;
    return array->entries[random % array->count];
}
#endif

// 0x00417770 - Release every node in the intrusive cleanup chain, unlinking
// each node before handing its storage to the platform allocator.
#ifdef _MSC_VER
__declspec(naked) void RecoveryLinkedCleanup(RecoveryCleanupNode** head,
                                             void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, [eax+18h]
        test esi, esi
        jz loc_4177B0
        push edi
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
loc_417780:
        mov edx, [esi]
        mov edi, [esi+8]
        mov ecx, esi
        call dword ptr [edx+10h]
        mov eax, [esi+4]
        mov ecx, [esi+8]
        mov [eax+8], ecx
        mov eax, [esi+8]
        test eax, eax
        jz loc_4177A0
        mov edx, [esi+4]
        mov [eax+4], edx
loc_4177A0:
        push esi
        call j__free
        add esp, 4
        test edi, edi
        mov esi, edi
        jnz loc_417780
        pop edi
loc_4177B0:
        pop esi
        ret
    }
}
#else
void RecoveryLinkedCleanup(RecoveryCleanupNode** head,
                           void (*free_memory)(void*)) {
    if (head == 0) return;
    RecoveryCleanupNode* node = *head;
    while (node != 0) {
        RecoveryCleanupNode* next = node->next;
        if (node->cleanup != 0) node->cleanup(node);
        if (node->previous != 0) node->previous->next = next;
        else *head = next;
        if (next != 0) next->previous = node->previous;
        if (free_memory != 0) free_memory(node);
        node = next;
    }
}
#endif

// 0x004220E0 - Clear the 0x2c8-byte object and install its enabled flag in
// the first word, matching the constructor's final visible state.
#ifdef _MSC_VER
__declspec(naked) void* RecoveryState_Initialize(void* state) {
    __asm {
        mov ecx, [edx+20h]
        xor eax, eax
        and ecx, 0FFFFFFFEh
        mov [edx+20h], ecx
        mov [edx+0B0h], eax
        mov [edx+24h], eax
        mov [edx+0F8h], eax
        mov dword ptr [edx+0F4h], 1
        mov ecx, 3E7h
        mov [edx+2Ch], ecx
        mov [edx+104h], ecx
        push edi
        mov [edx+188h], eax
        mov [edx+0FCh], eax
        mov [edx+1D0h], eax
        mov dword ptr [edx+1CCh], 1
        mov ecx, 0B2h
        mov edi, edx
        rep stosd
        or dword ptr [edx], 2
        mov dword_477830, edx
        mov eax, edx
        pop edi
        ret
    }
}
#else
void* g_recovery_global_state;
extern RecoveryWord DAT_00477830;
void* RecoveryState_Initialize(void* state) {
    memset(state, 0, 0x2C8);
    *(RecoveryWord*)state |= 2;
    g_recovery_global_state = state;
    DAT_00477830 = (RecoveryWord)(unsigned long)state;
    return state;
}
#endif

static void ResetRawTimer(RecoveryByte* bytes, RecoveryWord target_offset,
                          RecoveryWord current_offset, RecoveryWord previous_offset,
                          RecoveryWord speed_offset, RecoveryWord flags_offset,
                          RecoveryWord speed) {
    RecoveryWord* flags = (RecoveryWord*)(bytes + flags_offset);
    if ((*flags & 1) == 0) {
        *(RecoveryWord*)(bytes + current_offset) = 0;
        *(RecoveryWord*)(bytes + target_offset) = 0xFFF0BDC1u;
        *(RecoveryWord*)(bytes + previous_offset) = 0;
        *(RecoveryWord*)(bytes + speed_offset) = speed;
        *flags |= 1;
    }
    *(RecoveryWord*)(bytes + current_offset) = 0;
    *(RecoveryWord*)(bytes + previous_offset) = 0;
    *(RecoveryWord*)(bytes + target_offset) = 0xFFFFFFFFu;
}

// 0x00442300 - Configure the state bytes and reset its embedded timer.
void RecoveryState_Configure42300(void* state, const void* owner,
                                  RecoveryByte first, RecoveryByte second,
                                  RecoveryByte third, RecoveryWord speed) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    *(RecoveryWord*)(bytes + 0x12C) =
        (RecoveryWord)(unsigned long)owner;
    *(RecoveryWord*)(bytes + 0x130) = first;
    *(RecoveryWord*)(bytes + 0x108) = second;
    *(RecoveryWord*)(bytes + 0x110) = 0;
    *(RecoveryWord*)(bytes + 0x114) = 0;
    *(RecoveryWord*)(bytes + 0x10C) = third;
    ResetRawTimer(bytes, 0x118, 0x11C, 0x120, 0x124, 0x128, speed);
}

// 0x00442220 - Copy the two RGB-like triples, clear transient fields, and
// reset the object's embedded timer.
void RecoveryState_Configure42220(void* state, const RecoveryByte first[3],
                                  const RecoveryByte second[3], RecoveryWord mode,
                                  RecoveryByte flags, RecoveryWord speed) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    *(RecoveryWord*)(bytes + 0x100) = mode;
    memset(bytes + 0xD4, 0, 0x18);
    *(RecoveryWord*)(bytes + 0x104) = flags;
    for (int index = 0; index < 3; ++index) {
        *(RecoveryWord*)(bytes + 0xBC + index * 4) = second[index];
        *(RecoveryWord*)(bytes + 0xC8 + index * 4) = first[index];
    }
    ResetRawTimer(bytes, 0xEC, 0xF0, 0xF4, 0xF8, 0xFC, speed);
}

// 0x00441F50 - Set the four compact state parameters and reset its timer.
#ifdef _MSC_VER
__declspec(naked) void RecoveryState_Configure41F50(
        void* state, RecoveryWord value, RecoveryWord mode,
        RecoveryByte first, RecoveryByte second, RecoveryWord speed) {
    __asm {
        movzx edx, dl
        mov [eax+230h], edx
        movzx edx, [esp+8]
        mov [eax+22Ch], ecx
        movzx ecx, [esp+4]
        mov [eax+20Ch], edx
        mov [eax+208h], ecx
        mov ecx, [eax+228h]
        xor edx, edx
        test cl, 1
        jnz loc_441FAB
        or ecx, 1
        mov [eax+21Ch], edx
        mov dword ptr [eax+218h], 0FFF0BDC1h
        mov [eax+220h], edx
        mov dword ptr [eax+224h], offset flt_476F78
        mov [eax+228h], ecx
loc_441FAB:
        mov [eax+21Ch], edx
        mov [eax+220h], edx
        mov dword ptr [eax+218h], 0FFFFFFFFh
        ret 8
    }
}
#else
void RecoveryState_Configure41F50(void* state, RecoveryWord value,
                                  RecoveryWord mode, RecoveryByte first,
                                  RecoveryByte second, RecoveryWord speed) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    *(RecoveryWord*)(bytes + 0x230) = mode & 0xFFu;
    *(RecoveryWord*)(bytes + 0x22C) = value;
    *(RecoveryWord*)(bytes + 0x20C) = second;
    *(RecoveryWord*)(bytes + 0x208) = first;
    ResetRawTimer(bytes, 0x218, 0x21C, 0x220, 0x224, 0x228, speed);
}
#endif

// 0x00427950 - Invoke the downstream update leaf and return its zero status.
#ifdef _MSC_VER
__declspec(naked) RecoveryWord Recovery_InvokeZero(void (*invoke)(void)) {
    __asm {
        push esi
        mov esi, ecx
        call sub_427960
        xor eax, eax
        pop esi
        ret
    }
}
#else
RecoveryWord Recovery_InvokeZero(void (*invoke)(void)) {
    if (invoke != 0) invoke();
    return 0;
}
#endif

// 0x004198A0 - Forward the update call without changing its void result.
#ifdef _MSC_VER
__declspec(naked) void Recovery_InvokeVoid(void (*invoke)(void)) {
    __asm {
        push ebx
        mov ebx, ecx
        call sub_419650
        pop ebx
        ret
    }
}
#else
void Recovery_InvokeVoid(void (*invoke)(void)) {
    if (invoke != 0) invoke();
}
#endif

// 0x00422A90 - Preserve the two-word result of the downstream state update.
#ifdef _MSC_VER
__declspec(naked) unsigned long long Recovery_InvokePair(
        void* argument, unsigned long long (*invoke)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        call sub_4223F0
        pop esi
        ret
    }
}
#else
unsigned long long Recovery_InvokePair(
        void* argument, unsigned long long (*invoke)(void*)) {
    return invoke != 0 ? invoke(argument) : 0;
}
#endif

// 0x0041AB10 - Append a node to the tail of the doubly-linked chain.
#ifdef _MSC_VER
__declspec(naked) void Recovery_AppendNode(RecoveryAppendNode* list,
                                           RecoveryAppendNode* node) {
    __asm {
        lea ecx, [eax+4]
        push esi
        cmp dword ptr [ecx], 0
        jz loc_41AB2C
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
loc_41AB20:
        mov eax, [ecx]
        mov esi, [eax+4]
        test esi, esi
        lea ecx, [eax+4]
        jnz loc_41AB20
loc_41AB2C:
        mov ecx, [eax+4]
        test ecx, ecx
        pop esi
        jz loc_41AB3D
        mov [edx+4], ecx
        mov ecx, [eax+4]
        mov [ecx+8], edx
loc_41AB3D:
        mov [eax+4], edx
        mov [edx+8], eax
        ret
    }
}
#else
void Recovery_AppendNode(RecoveryAppendNode* list,
                         RecoveryAppendNode* node) {
    if (list == 0 || node == 0) return;
    RecoveryAppendNode* tail = list;
    while (tail->next != 0) tail = tail->next;
    node->next = 0;
    node->previous = tail;
    tail->next = node;
}
#endif

// 0x0044D080 - Release every interface entry and the optional auxiliary
// stream, leaving the owner in its post-destruction empty state.
#ifdef _MSC_VER
__declspec(naked) void Platform_ReleaseOwnedArray(
        RecoveryOwnedArrayState* state, void (*release)(void*),
        void (*close_auxiliary)(void*), void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        mov eax, [esi+10h]
        push edi
        xor edi, edi
        test eax, eax
        mov dword ptr [esi], offset off_4705D8
        jbe loc_44D0BA
loc_44D093:
        mov eax, [esi+4]
        mov ecx, [eax+edi*4]
        test ecx, ecx
        lea eax, [eax+edi*4]
        jz loc_44D0B2
        mov eax, ecx
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+8]
        mov edx, [esi+4]
        mov dword ptr [edx+edi*4], 0
loc_44D0B2:
        mov eax, [esi+10h]
        inc edi
        cmp edi, eax
        jb loc_44D093
loc_44D0BA:
        mov eax, [esi+4]
        test eax, eax
        jz loc_44D0D1
        push eax
        call j__free
        add esp, 4
        mov dword ptr [esi+4], 0
loc_44D0D1:
        mov edi, [esi+0Ch]
        test edi, edi
        jz loc_44D105
        cmp dword ptr [edi+78h], 1
        jnz loc_44D0F5
        mov eax, [edi+8Ch]
        push eax
        call dword ptr [__imp_CloseHandle]
        mov dword ptr [edi+8Ch], 0FFFFFFFFh
loc_44D0F5:
        push edi
        call j__free
        add esp, 4
        mov dword ptr [esi+0Ch], 0
loc_44D105:
        pop edi
        pop esi
        ret
    }
}
#else
void Platform_ReleaseOwnedArray(
        RecoveryOwnedArrayState* state, void (*release)(void*),
        void (*close_auxiliary)(void*), void (*free_memory)(void*)) {
    if (state == 0) return;
    for (RecoveryWord index = 0; index < state->count; ++index) {
        void* entry = state->entries != 0 ? state->entries[index] : 0;
        if (entry != 0 && release != 0) release(entry);
        if (state->entries != 0) state->entries[index] = 0;
    }
    if (state->entries != 0 && free_memory != 0) free_memory(state->entries);
    state->entries = 0;
    if (state->auxiliary != 0) {
        if (state->auxiliary_mode == 1 && close_auxiliary != 0)
            close_auxiliary(state->auxiliary);
        if (free_memory != 0) free_memory(state->auxiliary);
        state->auxiliary = 0;
    }
}
#endif

// 0x0044D300 - Start an interface operation, optionally polling until the
// operation reports completion. The busy HRESULT is retried after 10 ms.
int Platform_RunInterface(void* interface_object, RecoveryWord* completed,
                          int (*begin)(void*), int (*poll)(void*),
                          void (*sleep_ms)(unsigned)) {
    if (interface_object == 0) return (int)0x800401F0u;
    if (completed != 0) *completed = 0;
    int result = begin != 0 ? begin(interface_object) : 0;
    if (result < 0) return result;
    if (poll == 0) return 1;
    for (;;) {
        result = poll(interface_object);
        if (result == (int)0x88780096u) {
            if (sleep_ms != 0) sleep_ms(10);
            continue;
        }
        if (result != 0) return result;
        if (completed != 0) *completed = 1;
        return 0;
    }
}

// 0x004297B0 - Release a resource object and free its storage when present.
void* Platform_DeletingDestructorWithRelease(
        void* object, RecoveryByte flags, void (*release)(void*),
        void (*free_memory)(void*)) {
    if (object != 0 && release != 0) release(object);
    if (object != 0 && (flags & 1) != 0 && free_memory != 0)
        free_memory(object);
    return object;
}

// 0x0044DCA0 - Select a stream record and update the logical cursor. A real
// file handle is represented by the nonzero handle token in the clean ABI.
#ifdef _MSC_VER
__declspec(naked) int Platform_SelectStreamRecord(
        RecoveryStreamState* state, RecoveryStreamRecord* record,
        RecoveryWord archive_base, void (*seek)(RecoveryWord)) {
    __asm {
        mov eax, [esi+7Ch]
        test eax, eax
        jnz loc_44DCB2
        mov eax, [esi+8Ch]
        cmp eax, 0FFFFFFFFh
        jnz loc_44DCB8
loc_44DCB2:
        mov eax, 80004005h
        ret
loc_44DCB8:
        test eax, eax
        mov [esi+90h], ecx
        jz loc_44DCE5
        mov ecx, [ecx+10h]
        mov edx, dword_4977A4
        push 0
        push 0
        add ecx, edx
        push ecx
        push eax
        call dword ptr [__imp_SetFilePointer]
        mov edx, [esi+90h]
        mov eax, [edx+1Ch]
        mov [esi+8], eax
loc_44DCE5:
        mov ecx, [esi+8]
        mov [esi+2Ch], ecx
        xor eax, eax
        ret
    }
}
#else
int Platform_SelectStreamRecord(
        RecoveryStreamState* state, RecoveryStreamRecord* record,
        RecoveryWord archive_base, void (*seek)(RecoveryWord)) {
    if (state == 0 || (state->memory_mode == 0 && state->handle == 0xFFFFFFFFu))
        return (int)0x80004005u;
    state->record = record;
    if (state->memory_mode == 0 && state->handle != 0 &&
        seek != 0 && record != 0) seek(record->offset + archive_base);
    if (record != 0) state->position = record->length;
    state->cursor = state->position;
    return 0;
}
#endif

// 0x0044D710 - Run the final virtual cleanup and honor the deleting flag.
#ifdef _MSC_VER
__declspec(naked) void* Platform_DeletingDestructorVtable(
        void* object, RecoveryByte flags, void (*destroy)(void*),
        void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        call sub_44D730
        test byte ptr [esp+8], 1
        jz loc_44D728
        push esi
        call j__free
        add esp, 4
loc_44D728:
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
void* Platform_DeletingDestructorVtable(
        void* object, RecoveryByte flags, void (*destroy)(void*),
        void (*free_memory)(void*)) {
    if (destroy != 0) destroy(object);
    if ((flags & 1) != 0 && free_memory != 0) free_memory(object);
    return object;
}
#endif

// 0x0044D4E0 - Install either the fixed fallback deadline or the randomized
// interval used by the retail presentation path.
int Platform_SetOperationDeadline(
        bool randomized, RecoveryWord (*random_value)(void*), void* random_state,
        void (*set_deadline)(int)) {
    RecoveryWord value = randomized && random_value != 0
        ? random_value(random_state) : 0;
    int deadline = randomized ? (int)value - 5000 : -10000;
    if (set_deadline != 0) set_deadline(deadline);
    return deadline;
}

static void ClearOwnedChain(RecoveryOwnedLink* link,
                            void (*free_memory)(void*)) {
    while (link != 0) {
        RecoveryOwnedLink* next = link->next;
        if (free_memory != 0) free_memory(link->resource);
        link = next;
    }
}

// 0x00419040 - Clear the eight paired resource buckets maintained by the
// animation loader.
#ifdef _MSC_VER
__declspec(naked) void Recovery_ClearEightBuckets(
        RecoveryOwnedLink buckets[8], RecoveryOwnedLink direct[8],
        void (*free_memory)(void*)) {
    __asm {
        push ebx
        push esi
        push edi
        mov edi, eax
        add edi, 7Ch
        mov ebx, 8
        _emit 0x8D
        _emit 0x49
        _emit 0x00
loc_419050:
        mov eax, [edi-60h]
        test eax, eax
        jz loc_41906B
loc_419057:
        mov esi, [eax+4]
        mov eax, [eax]
        push eax
        call j__free
        add esp, 4
        test esi, esi
        mov eax, esi
        jnz loc_419057
loc_41906B:
        mov eax, [edi]
        test eax, eax
        jz loc_419085
loc_419071:
        mov ecx, [eax]
        mov esi, [eax+4]
        push ecx
        call j__free
        add esp, 4
        test esi, esi
        mov eax, esi
        jnz loc_419071
loc_419085:
        add edi, 0Ch
        dec ebx
        jnz loc_419050
        pop edi
        pop esi
        pop ebx
        ret
    }
}
#else
void Recovery_ClearEightBuckets(
        RecoveryOwnedLink buckets[8], RecoveryOwnedLink direct[8],
        void (*free_memory)(void*)) {
    if (buckets == 0 || direct == 0) return;
    for (int index = 0; index < 8; ++index) {
        ClearOwnedChain(buckets[index].next, free_memory);
        ClearOwnedChain(direct[index].next, free_memory);
        buckets[index].next = 0;
        direct[index].next = 0;
    }
}
#endif

// 0x00413450 - Release the optional owned resource and then its owner.
void Platform_ReleaseOwnedHandle(
        void* resource, void (*release)(void*), void (*free_memory)(void*)) {
    if (resource != 0 && release != 0) release(resource);
    if (resource != 0 && free_memory != 0) free_memory(resource);
}

// 0x0040BD20 - Advance the frame counter, using the fast path near unit
// speed and the rounded elapsed-time path for all other speed values.
int Recovery_TickState(RecoveryTickState* state, int (*update)(void*),
                       float stable_speed, RecoveryWord (*random_round)(void*),
                       void* random_state) {
    if (state == 0) return 1;
    if (update != 0 && update(state) != 0) return 1;
    state->previous = state->current;
    const float speed = state->speed != 0 ? *state->speed : 0.0f;
    if (speed > stable_speed - 0.01f && speed < stable_speed + 0.01f) {
        ++state->current;
        state->elapsed += 1.0f;
        return 0;
    }
    state->elapsed += speed;
    state->current = random_round != 0 ? random_round(random_state) : 0;
    return 0;
}

// 0x00427AE0 - Switch between the direct and buffered playback coordinates.
void Recovery_SwitchPlaybackState(void* state, bool secondary_active,
                                  void (*transition)(void*)) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    if (!secondary_active) {
        if (*(RecoveryWord*)(bytes + 0x84) != 0 && transition != 0)
            transition(state);
        *(RecoveryWord*)(bytes + 0x4C) = *(RecoveryWord*)(bytes + 0x3C);
        *(RecoveryWord*)(bytes + 0x50) = *(RecoveryWord*)(bytes + 0x40);
        *(RecoveryWord*)(bytes + 0x84) = 0;
        return;
    }
    if (*(RecoveryWord*)(bytes + 0x84) == 0 && transition != 0)
        transition(state);
    *(RecoveryWord*)(bytes + 0x34) = *(RecoveryWord*)(bytes + 0x4C);
    *(RecoveryWord*)(bytes + 0x38) = *(RecoveryWord*)(bytes + 0x50);
    *(RecoveryWord*)(bytes + 0x84) = 1;
}

// 0x00404DA0 - Scale six color channels and fill the four byte tint fields
// from the same rounded random source used by the retail animation path.
void Recovery_ScaleColor(const float source[6], RecoveryColorRecord* destination,
                         float scale, RecoveryWord (*random_byte)(void*),
                         void* random_state) {
    if (source == 0 || destination == 0) return;
    for (int index = 0; index < 6; ++index)
        destination->channels[index] = source[index] * scale;
    for (int index = 0; index < 4; ++index)
        destination->random_channels[index] = (RecoveryByte)(
            random_byte != 0 ? random_byte(random_state) : 0);
}

static int InstallPair(void** first_slot, void** second_slot,
                       void* first_resource, void* second_resource,
                       RecoveryWord first_flags, RecoveryWord second_flags,
                       void (*configure)(void*, RecoveryWord)) {
    if (first_slot == 0 || second_slot == 0) return -1;
    *first_slot = first_resource;
    *second_slot = second_resource;
    if (configure != 0) {
        if (first_resource != 0) configure(first_resource, first_flags);
        if (second_resource != 0) configure(second_resource, second_flags);
    }
    return 0;
}

// 0x004055C0 - Install the pair of enabled animation registrations.
int Recovery_InstallPairSetFlags(
        void** first_slot, void** second_slot, void* first_resource,
        void* second_resource, void (*configure)(void*, RecoveryWord)) {
    return InstallPair(first_slot, second_slot, first_resource, second_resource,
                       2, 2, configure);
}

// 0x0041AD90 - Install the pair of registrations with their disabled flags.
int Recovery_InstallPairClearFlags(
        void** first_slot, void** second_slot, void* first_resource,
        void* second_resource, void (*configure)(void*, RecoveryWord)) {
    return InstallPair(first_slot, second_slot, first_resource, second_resource,
                       0, 0, configure);
}

// 0x0041F930 - Release both cached resource slots and clear their ownership.
int Recovery_ReleasePair(void** first_slot, void** second_slot,
                         void (*release)(void*), void (*free_memory)(void*)) {
    if (first_slot == 0 || second_slot == 0) return -1;
    void* slots[2] = {*first_slot, *second_slot};
    for (int index = 0; index < 2; ++index) {
        if (slots[index] != 0 && release != 0) release(slots[index]);
        if (slots[index] != 0 && free_memory != 0) free_memory(slots[index]);
    }
    *first_slot = 0;
    *second_slot = 0;
    return 0;
}

// 0x00421F00 - Reset the fixed-size state object after initializing its
// embedded subobject, then install the two retail mode bits.
void* Recovery_InitializeLargeState(void* state,
                                    void (*initialize_subobject)(void*)) {
    if (state == 0) return 0;
    if (initialize_subobject != 0)
        initialize_subobject((RecoveryByte*)state + 0x48);
    memset(state, 0, 0x1E1 * sizeof(RecoveryWord));
    *(RecoveryWord*)((RecoveryByte*)state + 0x3CC) |= 0x140;
    return state;
}

// 0x00423510 - Set the initial mode, reset the timer, run the two update
// notifications, and publish the state's trailing speed word.
void Recovery_InitializeTimedState(void* state, void (*tick)(void),
                                    RecoveryWord* default_speed) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    *(RecoveryWord*)(bytes + 4) = 0xD;
    ResetRawTimer(bytes, 0x10, 0x14, 0x18, 0x1C, 0x20, 0);
    if (tick != 0) {
        tick();
        tick();
    }
    if (default_speed != 0)
        *default_speed = *(RecoveryWord*)(bytes + 0x2C0);
}

// 0x0041F8D0 - Load the front and bullet startup resources, reporting the
// matching retail fallback string when either load fails.
int Recovery_LoadStartupResources(
        void* context, void* (*load)(void*, int, const char*),
        void (*report_missing)(const char*)) {
    if (load == 0) return -1;
    if (load(context, 6, "front.anm") == 0) {
        if (report_missing != 0) report_missing("front.anm");
        return -1;
    }
    if (load(context, 7, "bullet.anm") != 0) return 0;
    if (report_missing != 0) report_missing("bullet.anm");
    return -1;
}

// 0x0042C670 - Create and register one animation slot, preserving the
// source resource token in the owner's indexed table.
int Recovery_InstallAnimationSlot(
        void* owner, int index, RecoveryWord resource,
        void* (*create)(void), void (*configure)(void*, int),
        void (*register_object)(void*),
        void (*store)(void*, int, RecoveryWord)) {
    if (create == 0 || store == 0 || index < 0) return -1;
    void* animation = create();
    if (animation == 0) return -1;
    if (configure != 0) configure(animation, index);
    if (register_object != 0) register_object(animation);
    store(owner, index, resource);
    return 0;
}

// 0x0042C6D0 - Mark the selected animation and its children as pending
// removal, then release the owner's slot token.
void Recovery_ClearAnimationSlot(
        RecoveryWord* slot, void* lookup_key,
        void* (*lookup)(void*, void*), void (*mark)(void*),
        void** children, RecoveryWord child_count) {
    if (slot == 0) return;
    void* root = lookup != 0 ? lookup(lookup_key, (void*)(unsigned long)*slot) : 0;
    if (root != 0 && mark != 0) {
        mark(root);
        if (children != 0) {
            for (RecoveryWord index = 0; index < child_count; ++index)
                if (children[index] != 0) mark(children[index]);
        }
    }
    *slot = 0;
}

// 0x00447280 - Resolve a cached resource or load it asynchronously and wait
// for its loading flag to clear, matching the one-millisecond polling loop.
void* Recovery_LoadCachedResource(
        void** slots, RecoveryWord count, int index, void* context,
        const char* name, void* (*load)(void*, int, const char*),
        RecoveryWord* loading, bool cancelled, void (*sleep_ms)(unsigned)) {
    if (slots == 0 || index < 0 || (RecoveryWord)index >= count) return 0;
    void* resource = slots[index];
    if (resource != 0) return resource;
    if (load == 0) return 0;
    resource = load(context, index, name);
    slots[index] = resource;
    if (resource == 0 || loading == 0) return resource;
    *loading = 1;
    while (!cancelled && *loading != 0) {
        if (sleep_ms != 0) sleep_ms(1);
        else break;
    }
    return resource;
}

// 0x0043D790 - Find an archive record and hand it to the stream selector.
#ifdef _MSC_VER
__declspec(naked) int Recovery_SelectArchiveEntry(
        bool available, void* request, void* archive,
        int (*find_index)(void*, void*),
        int (*select_record)(void*, RecoveryWord)) {
    __asm {
        push esi
        mov esi, eax
        mov eax, [esi+5208h]
        test eax, eax
        jnz loc_43D7A2
        or eax, 0FFFFFFFFh
        pop esi
        ret
loc_43D7A2:
        push esi
        call sub_43D2A0
        mov ecx, eax
        mov eax, [esi+1F84h]
        imul ecx, 34h
        add ecx, eax
        mov eax, [esi+5208h]
        mov esi, [eax+0Ch]
        call sub_44DCA0
        xor eax, eax
        pop esi
        ret
    }
}
#else
int Recovery_SelectArchiveEntry(
        bool available, void* request, void* archive,
        int (*find_index)(void*, void*),
        int (*select_record)(void*, RecoveryWord)) {
    if (!available || find_index == 0 || select_record == 0) return -1;
    int index = find_index(request, archive);
    if (index < 0) return index;
    return select_record(archive, (RecoveryWord)index * 0x34u);
}
#endif

// 0x0041A050 - Copy a resource path, split at its colon, and reset the
// resulting path state when the separator is present.
#ifdef _MSC_VER
__declspec(naked) int Recovery_SplitResourcePath(
        char* destination, const char* source,
        RecoveryWord capacity, void (*reset)(void)) {
    __asm {
        mov edx, edi
        sub edx, eax
loc_41A054:
        mov cl, [eax]
        mov [edx+eax], cl
        inc eax
        test cl, cl
        jnz loc_41A054
        push 3Ah
        push edi
        call _strchr
        add esp, 8
        test eax, eax
        jnz loc_41A074
        mov eax, edi
        jmp sub_41A0A0
loc_41A074:
        push esi
        lea ecx, [eax+1]
        mov esi, ebx
        sub esi, ecx
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
loc_41A080:
        mov dl, [ecx]
        mov [esi+ecx], dl
        inc ecx
        test dl, dl
        jnz loc_41A080
        mov [eax], dl
        mov eax, edi
        call sub_41A0A0
        mov eax, ebx
        pop esi
        jmp sub_41A0A0
    }
}
#else
int Recovery_SplitResourcePath(char* destination, const char* source,
                               RecoveryWord capacity, void (*reset)(void)) {
    if (destination == 0 || source == 0 || capacity == 0) return -1;
    RecoveryWord index = 0;
    for (; index + 1 < capacity && source[index] != '\0'; ++index)
        destination[index] = source[index];
    destination[index] = '\0';
    char* separator = 0;
    for (RecoveryWord cursor = 0; cursor < index; ++cursor)
        if (destination[cursor] == ':') separator = destination + cursor;
    if (separator == 0) {
        if (reset != 0) reset();
        return 0;
    }
    *separator = '\0';
    if (reset != 0) {
        reset();
        reset();
    }
    return 1;
}
#endif

// 0x00428160 - Dispatch the entries whose period/remainder pair matches the
// current tick. The table is a compact two-byte period/remainder sequence.
int Recovery_DispatchSchedule(
        int tick, const char* schedule, RecoveryWord schedule_count,
        void (*dispatch)(const char*, int)) {
    if (schedule == 0) return 0;
    int dispatched = 0;
    for (RecoveryWord index = 0; index < schedule_count; ++index) {
        const char* entry = schedule + index * 0x34;
        const int period = (signed char)entry[0];
        if (period < 0) break;
        if (period != 0 && tick % period == (signed char)entry[1]) {
            if (dispatch != 0) dispatch(entry, tick);
            ++dispatched;
        }
    }
    return dispatched;
}

// 0x0043C870 - Release a resource and always return the retail null status.
#ifdef _MSC_VER
__declspec(naked) void* Platform_DeletingDestructorNoReturn(
        void* object, void (*release)(void*), void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        test esi, esi
        jz loc_43C886
        push esi
        call sub_43CB00
        push esi
        call j__free
        add esp, 4
loc_43C886:
        xor eax, eax
        pop esi
        ret
    }
}
#else
void* Platform_DeletingDestructorNoReturn(
        void* object, void (*release)(void*), void (*free_memory)(void*)) {
    if (object != 0 && release != 0) release(object);
    if (object != 0 && free_memory != 0) free_memory(object);
    return 0;
}
#endif

// 0x0040C9A0 - Flush the pending emitter count through the spawn callback,
// reset the emitter, and clear the count.
#ifdef _MSC_VER
__declspec(naked) void Recovery_ResetEmitter(
        int* count, void* emitter,
        void (*spawn)(void*, int, RecoveryWord, float, float),
        void (*reset)(void*)) {
    __asm {
        push esi
        mov esi, eax
        mov eax, [edi]
        test eax, eax
        jle loc_40C9C2
        push 400CCCCDh
        push 0BFC90FDBh
        push 0FFFFFFFFh
        push eax
        mov eax, dword_477818
        mov ecx, esi
        call sub_41BB00
loc_40C9C2:
        push edi
        call sub_40C9D0
        mov dword ptr [edi], 0
        pop esi
        ret
    }
}
#else
void Recovery_ResetEmitter(
        int* count, void* emitter,
        void (*spawn)(void*, int, RecoveryWord, float, float),
        void (*reset)(void*)) {
    if (count == 0) return;
    if (*count > 0 && spawn != 0)
        spawn(emitter, *count, 0xFFFFFFFFu, -1.5707964f, 2.2f);
    if (reset != 0) reset(emitter);
    *count = 0;
}
#endif

// 0x00404530 - Initialize the player timer and install its 30-frame mode.
void Recovery_InitializePlayerTimer(void* state, RecoveryWord speed,
                                    void (*configure)(RecoveryWord, RecoveryWord)) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    if (configure != 0) configure(2, 0x1E);
    ResetRawTimer(bytes, 0x2A1C, 0x2A20, 0x2A24, 0x2A28, 0x2A2C, speed);
    *(RecoveryWord*)(bytes + 0x2A20) = 0x1E;
    *(RecoveryWord*)(bytes + 0x2A24) = 0x41F00000u;
    *(RecoveryWord*)(bytes + 0x2A1C) = 0x1D;
    *(RecoveryWord*)(bytes + 0x2A18) |= 2;
}

// 0x0041A0A0 - Trim the four whitespace classes from both ends of a string.
#ifdef _MSC_VER
__declspec(naked) void Recovery_TrimWhitespace(char* text) {
    __asm {
        push esi
        push edi
loc_41A0A2:
        mov cl, [eax]
        cmp cl, 20h
        jz loc_41A0B8
        cmp cl, 9
        jz loc_41A0B8
        cmp cl, 0Ah
        jz loc_41A0B8
        cmp cl, 0Dh
        jnz loc_41A0D6
loc_41A0B8:
        mov ecx, eax
        lea esi, [ecx+1]
        _emit 0x8D
        _emit 0x49
        _emit 0x00
loc_41A0C0:
        mov dl, [ecx]
        inc ecx
        test dl, dl
        jnz loc_41A0C0
        sub ecx, esi
        test ecx, ecx
        jle loc_41A0A2
        lea esi, [eax+1]
        mov edi, eax
        rep movsb
        jmp loc_41A0A2
loc_41A0D6:
        mov ecx, eax
        lea esi, [ecx+1]
        jmp loc_41A0E0
        _emit 0x8D
        _emit 0x49
        _emit 0x00
loc_41A0E0:
        mov dl, [ecx]
        inc ecx
        test dl, dl
        jnz loc_41A0E0
        sub ecx, esi
        lea edx, [ecx-1]
        test edx, edx
        pop edi
        pop esi
        jl locret_41A111
loc_41A0F2:
        mov cl, [edx+eax]
        cmp cl, 20h
        jz loc_41A109
        cmp cl, 9
        jz loc_41A109
        cmp cl, 0Ah
        jz loc_41A109
        cmp cl, 0Dh
        jnz locret_41A111
loc_41A109:
        dec edx
        mov byte ptr [edx+eax+1], 0
        jns loc_41A0F2
locret_41A111:
        ret
    }
}
#else
void Recovery_TrimWhitespace(char* text) {
    if (text == 0) return;
    char* begin = text;
    while (*begin == ' ' || *begin == '\t' || *begin == '\n' || *begin == '\r')
        ++begin;
    if (begin != text) memmove(text, begin, strlen(begin) + 1);
    unsigned long length = strlen(text);
    while (length != 0) {
        char value = text[length - 1];
        if (value != ' ' && value != '\t' && value != '\n' && value != '\r')
            break;
        text[--length] = '\0';
    }
}
#endif

// 0x0041F850 - Clear the fixed state table and install its enabled bit.
#ifdef _MSC_VER
__declspec(naked) void* Recovery_InitializeStateTable(void* state) {
    __asm {
        mov dword ptr [esi+10h], offset off_4703E4
        lea edx, [esi+30h]
        xor eax, eax
        mov [esi+14h], eax
        mov [esi+18h], eax
        mov [esi+1Ch], eax
        mov [esi+20h], eax
        mov ecx, [edx+6Ch]
        mov eax, 0FFFFFFFEh
        and ecx, eax
        mov [edx+6Ch], ecx
        push edi
        and [edx+0B0h], eax
        and [edx+0FCh], eax
        and [edx+128h], eax
        and [edx+174h], eax
        and [edx+1B0h], eax
        and [edx+1FCh], eax
        and [edx+228h], eax
        and [edx+378h], eax
        xor eax, eax
        mov ecx, 0EBh
        mov edi, edx
        rep stosd
        mov word ptr [edx+384h], 0FFFFh
        mov ecx, 0FCh
        mov edi, esi
        rep stosd
        or dword ptr [esi], 2
        mov dword_477820, esi
        mov eax, esi
        pop edi
        ret
    }
}
#else
void* Recovery_InitializeStateTable(void* state) {
    if (state == 0) return 0;
    memset(state, 0, 0x3F0);
    *(RecoveryWord*)state |= 2;
    return state;
}
#endif

// 0x00420A90 - Replace a resource extension with .wav and submit it.
int Recovery_ReplaceExtensionWav(void* context, char* path,
                                 void (*load)(void*, const char*)) {
    if (path == 0) return 0;
    char* extension = strrchr(path, '.');
    if (extension == 0 || extension[1] == '\0') return 0;
    extension[1] = 'w';
    extension[2] = 'a';
    extension[3] = 'v';
    extension[4] = '\0';
    if (load != 0) load(context, path);
    return 1;
}

// 0x00405040 - Copy six word color fields and fill four random tint bytes.
void Recovery_InitializeWordColor(
        const RecoveryWord values[6], RecoveryWordColorRecord* destination,
        RecoveryWord (*random_byte)(void*), void* random_state) {
    if (values == 0 || destination == 0) return;
    for (int index = 0; index < 6; ++index)
        destination->channels[index] = values[index];
    for (int index = 0; index < 4; ++index)
        destination->random_channels[index] = (RecoveryByte)(
            random_byte != 0 ? random_byte(random_state) : 0);
}

// 0x0043CB00 - Release the two raw resource slots at offsets +8 and +c.
void Recovery_ReleaseRawPair(void* state, void (*release)(void*),
                             void (*free_memory)(void*)) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    void** first = (void**)(bytes + 8);
    void** second = (void**)(bytes + 0xC);
    Recovery_ReleasePair(first, second, release, free_memory);
}

// 0x00405620 - Release the pair and clear the owner's external marker.
void Recovery_ReleaseRawPairAndReset(void* state, void (*release)(void*),
                                     void (*free_memory)(void*),
                                     RecoveryWord* global_flag) {
    Recovery_ReleaseRawPair(state, release, free_memory);
    if (global_flag != 0) *global_flag = 0;
}

// 0x0040B940 - Allocate, initialize, and publish the small ten-word state.
void* g_recovery_small_state;
void* Recovery_CreateSmallState(
        void* (*allocate)(RecoveryWord), int (*initialize)(void*),
        void (*destroy)(void*), void (*free_memory)(void*)) {
    if (allocate == 0) return 0;
    void* state = allocate(0x28);
    if (state == 0) return 0;
    memset(state, 0, 0x28);
    *(RecoveryWord*)state |= 2;
    g_recovery_small_state = state;
    if (initialize != 0 && initialize(state) != 0) {
        if (destroy != 0) destroy(state);
        if (free_memory != 0) free_memory(state);
        if (g_recovery_small_state == state) g_recovery_small_state = 0;
        return 0;
    }
    return state;
}

// 0x0044CE80 - Copy an interface array into an owner and query each entry.
void Recovery_InitializeInterfaceArray(
        RecoveryOwnedArrayState* state, void** source, RecoveryWord count,
        void* argument, RecoveryWord (*query)(void*, RecoveryWord)) {
    if (state == 0) return;
    state->entries = source;
    state->count = count;
    state->auxiliary = argument;
    state->auxiliary_mode = 0;
    if (query != 0 && source != 0)
        for (RecoveryWord index = 0; index < count; ++index)
            if (source[index] != 0) query(source[index], 0);
}

// 0x0044D6A0 - Initialize the one-entry interface owner and query it once.
void Recovery_InitializeSingleInterface(
        RecoveryInterfaceArray* state, void* entry, void* first_argument,
        void* second_argument, RecoveryWord (*query)(void*, RecoveryWord)) {
    if (state == 0) return;
    state->entries = (void**)first_argument;
    state->count = 1;
    if (state->entries != 0) state->entries[0] = entry;
    if (query != 0 && entry != 0) query(entry, 0);
    (void)second_argument;
}

// 0x00418810 - Offset a three-dimensional point by the retail stage origin.
#ifdef _MSC_VER
__declspec(naked) void Recovery_OffsetPoint(const float input[3],
                                            float output[3]) {
    __asm {
        mov dl, byte ptr dword_497D8C
        mov ecx, 1
        _emit 0x84
        _emit 0xD1
        jnz loc_418825
        or dword_497D8C, ecx
loc_418825:
        fld dword ptr [eax]
        fadd dword ptr [flt_470B4C]
        fstp dword ptr [flt_497D80]
        fld dword ptr [eax+4]
        fadd dword ptr [flt_470B48]
        fstp dword ptr [flt_497D84]
        mov eax, [eax+8]
        mov dword_497D88, eax
        mov eax, offset flt_497D80
        ret
    }
}
#else
void Recovery_OffsetPoint(const float input[3], float output[3]) {
    if (input == 0 || output == 0) return;
    output[0] = input[0] + 20.0f;
    output[1] = input[1] + 10.0f;
    output[2] = input[2];
}
#endif

// 0x00418A00 - Apply the presentation decay to the timer counter.
#ifdef _MSC_VER
__declspec(naked) void Recovery_DecayCounter(void* state,
                                             void (*reset)(float)) {
    __asm {
        mov ecx, [eax+18h]
        test ecx, ecx
        push esi
        jle loc_418A17
        push 0BF800000h
        lea esi, [eax+14h]
        call sub_44BF40
        pop esi
        ret
loc_418A17:
        mov ecx, [eax+0Ch]
        mov esi, 1388h
        cmp ecx, esi
        jle loc_418A3F
        mov edx, [eax+10h]
        sub ecx, edx
        cmp edx, 12h
        mov [eax+0Ch], ecx
        jge loc_418A37
        mov dword ptr [eax+10h], 12h
loc_418A37:
        cmp [eax+0Ch], esi
        jge loc_418A3F
        mov [eax+0Ch], esi
loc_418A3F:
        pop esi
        ret
    }
}
#else
void Recovery_DecayCounter(void* state, void (*reset)(float)) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    if (*(int*)(bytes + 0x18) > 0) {
        if (reset != 0) reset(-1.0f);
        return;
    }
    if (*(int*)(bytes + 0xC) > 5000) {
        *(int*)(bytes + 0xC) -= *(int*)(bytes + 0x10);
        if (*(int*)(bytes + 0x10) < 0x12) *(int*)(bytes + 0x10) = 0x12;
        if (*(int*)(bytes + 0xC) < 5000) *(int*)(bytes + 0xC) = 5000;
    }
}
#endif

// 0x0042A8A0 - Append three 16-bit packet fields and report when the packet
// buffer has crossed the retail 0xe0f-entry threshold.
bool Recovery_AppendPacket(RecoveryPacketBuffer* buffer, RecoveryWord first,
                           RecoveryWord second, RecoveryWord third) {
    if (buffer == 0 || buffer->cursor == 0 || buffer->begin == 0 ||
        buffer->cursor + 6 > buffer->begin + buffer->limit) return true;
    unsigned short* values = (unsigned short*)buffer->cursor;
    values[0] = (unsigned short)first;
    values[1] = (unsigned short)second;
    values[2] = (unsigned short)third;
    buffer->cursor += 6;
    return (RecoveryWord)((buffer->cursor - buffer->begin) / 6) > 0xE0Fu;
}

// 0x0042ADD0 - Clear the state header and fill the 0x200-entry random table.
void Recovery_InitializeRandomTable(void* state,
                                    RecoveryWord (*random_value)(void*),
                                    void* random_state) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    memset(bytes, 0, 0x448);
    *(RecoveryWord*)(bytes + 0) = 0x5453;
    *(RecoveryWord*)(bytes + 8) = 0x448;
    short* table = (short*)(bytes + 0x46);
    for (int index = 0; index < 0x200; ++index) {
        RecoveryWord random = random_value != 0 ? random_value(random_state) : 0;
        table[index] = (short)random;
    }
}

// 0x00422360 - Allocate and initialize the timer state, cleaning it up if
// the downstream initialization reports failure.
void* Recovery_CreateTimerState(
        void* (*allocate)(RecoveryWord), int (*initialize)(void*),
        void (*destroy)(void*), void (*free_memory)(void*)) {
    if (allocate == 0) return 0;
    void* state = allocate(0x2C8);
    if (state == 0) return 0;
    RecoveryState_Initialize(state);
    if (initialize != 0 && initialize(state) != 0) {
        if (destroy != 0) destroy(state);
        if (free_memory != 0) free_memory(state);
        return 0;
    }
    return state;
}

// 0x004243F0 - Mark an animation root and its children with state six.
void Recovery_MarkAnimationTree(RecoveryWord* root_status,
                                RecoveryWord* child_status,
                                RecoveryWord child_count) {
    if (root_status != 0) *root_status = 6;
    if (child_status != 0)
        for (RecoveryWord index = 0; index < child_count; ++index)
            child_status[index] = 6;
}

// 0x004056B0 - Allocate a fixed state, zero it, and run its initializer.
void* Recovery_CreateFixedState(
        RecoveryWord size, void* (*allocate)(RecoveryWord),
        int (*initialize)(void*), void (*destroy)(void*),
        void (*free_memory)(void*)) {
    if (allocate == 0) return 0;
    void* state = allocate(size);
    if (state == 0) return 0;
    memset(state, 0, size);
    *(RecoveryWord*)state |= 2;
    if (initialize != 0 && initialize(state) != 0) {
        if (destroy != 0) destroy(state);
        if (free_memory != 0) free_memory(state);
        return 0;
    }
    return state;
}

// 0x0040B9F0 - Update the emitter's frame count and select the occasional
// six-frame cadence when the state flags permit it.
RecoveryWord Recovery_UpdateEmitterDecision(
        void* state, int (*tick)(void*), RecoveryWord flags,
        bool twelve_frame_mode) {
    if (tick != 0 && tick(state) != 0) return 1;
    RecoveryByte* bytes = (RecoveryByte*)state;
    int count = ++*(int*)(bytes + 0x24);
    if ((flags & 4) != 0 || (flags & 2) == 0 || !twelve_frame_mode)
        return 1;
    return count % 12 == 0 ? 6 : 1;
}

// 0x004188A0 - Increment the animation count, clamping at nine and asking
// the resource manager to reload the active record below that cap.
void Recovery_IncrementAnimationCount(void* state, int delta,
                                      void (*reload)(void*)) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    int count = *(int*)(bytes + 0x30) + delta;
    *(int*)(bytes + 0x30) = count;
    if (count > 9) {
        *(int*)(bytes + 0x30) = 9;
        return;
    }
    if (reload != 0) reload(state);
}

// 0x00446EB0 - Create a texture through the platform callback and finalize
// its format metadata on success.
int Recovery_CreateTextureFromMemory(
        void* state, int format, int mip_levels,
        int (*create)(void*, int, int), void (*finalize)(void*)) {
    if (create == 0 || create(state, format, mip_levels) != 0) return -1;
    if (finalize != 0) finalize(state);
    return 0;
}

// 0x00447A50 - Forward a formatted log line and set the owner's active bit.
void Recovery_MarkLogState(void* state, void (*write)(void*, const char*),
                           const char* text) {
    if (write != 0) write(state, text != 0 ? text : "");
    if (state != 0) *(RecoveryWord*)((RecoveryByte*)state + 0x35C) |= 1;
}

// 0x00419090 - Allocate and initialize the 0x1a8-byte resource state.
void* Recovery_CreateResourceState(
        RecoveryWord size, void* (*allocate)(RecoveryWord),
        int (*initialize)(void*), void (*destroy)(void*),
        void (*free_memory)(void*)) {
    if (allocate == 0) return 0;
    void* state = allocate(size);
    if (state == 0) return 0;
    if (initialize != 0 && initialize(state) != 0) {
        if (destroy != 0) destroy(state);
        if (free_memory != 0) free_memory(state);
        return 0;
    }
    return state;
}

// 0x0041FAC0 - Install the worker callback and publish its handle/id pair.
int Recovery_StartWorker(void* state, void (*start)(void*),
                         RecoveryWord* handle, RecoveryWord* thread_id) {
    if (state == 0 || start == 0 || handle == 0 || thread_id == 0) return -1;
    *handle = 1;
    *thread_id = 0;
    start(state);
    return 0;
}

// 0x00414570 - Release the three optional composite resources at their raw
// offsets and clear the slots.
void Recovery_ReleaseCompositeState(void* state, void (*release)(void*),
                                    void (*free_memory)(void*)) {
    RecoveryByte* bytes = (RecoveryByte*)state;
    void* slots[3] = {*(void**)(bytes + 0x9EB8),
                      *(void**)(bytes + 0x9EBC), *(void**)(bytes + 0x9E80)};
    for (int index = 0; index < 3; ++index) {
        if (slots[index] != 0 && release != 0) release(slots[index]);
        if (slots[index] != 0 && free_memory != 0) free_memory(slots[index]);
    }
    *(void**)(bytes + 0x9EB8) = 0;
    *(void**)(bytes + 0x9EBC) = 0;
    *(RecoveryWord*)(bytes + 0x9E80) = 0;
}

// 0x004203F0 - Release each global state in the supplied shutdown order.
void Recovery_ReleaseGlobalStates(void** states, RecoveryWord count,
                                  void (*release)(void*),
                                  void (*free_memory)(void*)) {
    if (states == 0) return;
    for (RecoveryWord index = 0; index < count; ++index) {
        if (states[index] != 0 && release != 0) release(states[index]);
        if (states[index] != 0 && free_memory != 0) free_memory(states[index]);
        states[index] = 0;
    }
}

// 0x004479D0 - Normalize the requested text count, draw four random color
// words, and dispatch the appropriate text renderer variant.
int Recovery_DispatchRandomText(int count, void* context,
                                RecoveryWord (*random_value)(void*),
                                void (*dispatch)(void*, const RecoveryWord[4], int)) {
    if (count < 1) count = 0x11;
    else if (count < 9) return 0;
    RecoveryWord colors[4] = {};
    for (int index = 0; index < 4; ++index)
        colors[index] = random_value != 0 ? random_value(context) : 0;
    if (dispatch != 0) dispatch(context, colors, count);
    return 1;
}

// 0x00425020 - Allocate and initialize the large 0x4478-byte resource state.
void* Recovery_CreateLargeResourceState(
        void* (*allocate)(RecoveryWord), int (*initialize)(void*),
        void (*destroy)(void*), void (*free_memory)(void*)) {
    return Recovery_CreateResourceState(0x4478, allocate, initialize, destroy,
                                        free_memory);
}

// 0x0042B660 - Allocate and initialize the huge 0xb884-byte resource state.
void* Recovery_CreateHugeResourceState(
        void* (*allocate)(RecoveryWord), int (*initialize)(void*),
        void (*destroy)(void*), void (*free_memory)(void*)) {
    return Recovery_CreateResourceState(0xB884, allocate, initialize, destroy,
                                        free_memory);
}

// 0x0043BC40 - Reset the device streams, restoring state after each draw
// attempt when the draw callback reports failure.
void Recovery_ResetDeviceStreams(void* device, void (*set_stream)(void*),
                                 int (*draw)(void*), void (*restore)(void*)) {
    for (int index = 0; index < 2; ++index) {
        if (set_stream != 0) set_stream(device);
        if (draw != 0 && draw(device) < 0 && restore != 0) restore(device);
    }
}

// 0x004281D0 - Advance the stage sequence.  The retail function clears the
// published owner when the sequence is inactive, repairs a negative stage
// only when the feature flag permits it, dispatches a changed schedule, and
// selects the normal or terminal update path at stage fifteen.
int Recovery_UpdateStageSequence(
        void* state, bool feature_enabled,
        void (*dispatch_schedule)(void*), void (*set_stage)(int),
        void (*reset_timer)(float), void (*continue_update)(void*)) {
    if (state == 0) return 0;
    RecoveryByte* bytes = (RecoveryByte*)state;
    int& active = *(int*)(bytes + 0x458);
    int& previous_stage = *(int*)(bytes + 0x460);
    int& stage = *(int*)(bytes + 0x464);
    if (active != 1) {
        *(RecoveryWord*)(bytes + 0x3504) = 0;
        bytes[0x3508] = 0;
        return 0;
    }
    if (stage < 0) {
        if (!feature_enabled) return 0;
        if (set_stage != 0) set_stage(0);
    }
    if (stage != previous_stage && dispatch_schedule != 0)
        dispatch_schedule(state);
    if (stage > 14) {
        if (feature_enabled) {
            if (reset_timer != 0) reset_timer(-15.0f);
        } else if (set_stage != 0) {
            set_stage(-1);
        }
        return 0;
    }
    if (continue_update != 0) continue_update(state);
    return 0;
}

// 0x0044C2A0 - Advance a three-axis motion record.  Linear records add their
// velocity directly; polar records derive the horizontal displacement from
// angle/radius before applying the same base velocity.  Retail then snaps the
// horizontal coordinates through its floating-point quantizer.
void Recovery_AdvancePolarMotion(float state[11],
                                 float (*quantize)(float)) {
    if (state == 0) return;
    if ((((RecoveryWord*)state)[10] & 1u) == 0) {
        state[0] += state[3];
        state[1] += state[4];
        state[2] += state[5];
    } else {
        const float angle = state[7];
        const float radius = state[8];
        state[0] = state[3] + radius * (float)cos((double)angle);
        state[1] = state[4] + radius * (float)sin((double)angle);
        state[2] = state[5];
    }
    if (quantize != 0) {
        state[0] = quantize(state[0]);
        state[1] = quantize(state[1]);
    }
}
