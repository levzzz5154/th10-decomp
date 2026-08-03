#include "th10/render/resource_manager.hpp"

extern "C" void __stdcall EnterCriticalSection(void* critical_section);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);

#ifdef _MSC_VER
extern "C" void* dword_4660B0;
extern "C" void* dword_4660B4;
extern "C" unsigned char byte_49231C;
extern "C" void sub_449F60(void*, void*);
extern "C" void sub_44C150(void);
extern "C" void sub_449E50(void*, void*);
#endif

extern uint32_t DAT_00492274;
extern uint8_t DAT_0049231c;

void __fastcall D3DResource_Release(void* resource, void* device_owner);
void D3DResourceWorker_Stop(void);

// 0x00449A90 - Clear the three deferred resource-operation slots. Retail
// also uses this helper from constructor-unwind cleanup.
#ifdef _MSC_VER
__declspec(naked) void D3DResourceList_ClearPending(D3DResourceList* list) {
    __asm {
        xor ecx, ecx
        mov [eax+8], ecx
        mov [eax+0Ch], ecx
        mov [eax+10h], ecx
        ret
    }
}
#else
void D3DResourceList_ClearPending(D3DResourceList* list) {
    list->pending_008 = 0;
    list->pending_00C = 0;
    list->pending_010 = 0;
}
#endif

void D3DResourceList_Initialize(D3DResourceList* list) {
    list->reserved_header = 0;
    list->flags &= 0xFFFFFFFE;
    D3DResourceList_ClearPending(list);
    list->owner = list;
    list->first = 0;
    list->last = 0;
}

// 0x00449E50 - Release each D3D object tracked by one resource list.
#ifdef _MSC_VER
__declspec(naked) void D3DResourceList_ReleaseResources(
        D3DResourceList* list, void* device_owner) {
    __asm {
        mov eax, [eax+18h]
        test eax, eax
        je done
        push ebx
        mov ebx, dword_4660B0
        push ebp
        mov ebp, dword_4660B4
        push esi
        push edi
release_loop:
        mov esi, [eax]
        test esi, esi
        mov edi, [eax+4]
        je next
        push 492274h
        call ebx
        inc byte ptr byte_49231C
        mov edx, [esp+14h]
        mov ecx, esi
        call sub_449F60
        push 492274h
        call ebp
        dec byte ptr byte_49231C
next:
        test edi, edi
        mov eax, edi
        jne release_loop
        pop edi
        pop esi
        pop ebp
        pop ebx
done:
        ret 4
    }
}
#else
void D3DResourceList_ReleaseResources(
        D3DResourceList* list, void* device_owner) {
    D3DResourceNode* node = list->first;
    while (node != 0) {
        void* resource = node->resource;
        node = node->next;
        if (resource != 0) {
            EnterCriticalSection(&DAT_00492274);
            ++DAT_0049231c;
            D3DResource_Release(resource, device_owner);
            LeaveCriticalSection(&DAT_00492274);
            --DAT_0049231c;
        }
    }
}
#endif

// 0x00449AA0 - Initialize both embedded resource lists.
#ifdef _MSC_VER
__declspec(naked) void D3DResourceManager_Initialize(
        D3DResourceManager* manager) {
    __asm {
        mov ecx, [eax+4]
        xor edx, edx
        mov [eax+8], edx
        mov [eax+0Ch], edx
        mov [eax+10h], edx
        mov [eax], edx
        and ecx, 0FFFFFFFEh
        mov [eax+4], ecx
        lea ecx, [eax+24h]
        mov [eax+14h], eax
        mov [eax+18h], edx
        mov [eax+1Ch], edx
        and dword ptr [ecx+4], 0FFFFFFFEh
        mov [ecx+8], edx
        mov [ecx+0Ch], edx
        mov [ecx+10h], edx
        mov [ecx], edx
        mov [ecx+14h], ecx
        mov [ecx+18h], edx
        mov [ecx+1Ch], edx
        ret
    }
}
#else
void D3DResourceManager_Initialize(D3DResourceManager* manager) {
    D3DResourceList_Initialize(&manager->primary);
    D3DResourceList_Initialize(&manager->secondary);
}
#endif

// 0x00438880 - Stop the worker and release both classes of D3D resources.
#ifdef _MSC_VER
__declspec(naked) void D3DResourceManager_Destroy(
        D3DResourceManager* manager) {
    __asm {
        mov eax, fs:[0]
        push 0FFFFFFFFh
        push 465363h
        push eax
        mov fs:[0], esp
        push esi
        push edi
        mov edi, [esp+18h]
        mov esi, 492254h
        mov dword ptr [esp+10h], 1
        call sub_44C150
        push edi
        mov eax, edi
        call sub_449E50
        lea esi, [edi+24h]
        push edi
        mov eax, esi
        call sub_449E50
        mov ecx, [esp+8]
        xor eax, eax
        mov [esi+8], eax
        mov [esi+0Ch], eax
        mov [esi+10h], eax
        mov [edi+8], eax
        mov [edi+0Ch], eax
        mov [edi+10h], eax
        pop edi
        mov fs:[0], ecx
        pop esi
        add esp, 0Ch
        ret 4
    }
}
#else
void D3DResourceManager_Destroy(D3DResourceManager* manager) {
    D3DResourceWorker_Stop();
    D3DResourceList_ReleaseResources(&manager->primary, manager);
    D3DResourceList_ReleaseResources(&manager->secondary, manager);
    D3DResourceList_ClearPending(&manager->primary);
    D3DResourceList_ClearPending(&manager->secondary);
}
#endif
