#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004066e0_004066e0() {
    __asm {
    L_004066e0:
        push esi
    L_004066e1:
        mov esi,dword ptr [eax+ecx*4+14h]
    L_004066e5:
        test esi,esi
    L_004066e7:
        je short L_0040675f
    L_004066e9:
        lea esp,[esp+force_disp32_zero]
    L_004066f0:
        fld dword ptr [esi+3B4h]
    L_004066f6:
        fadd dword ptr [data_00470b4c]
    L_004066fc:
        fstp dword ptr [esi+33Ch]
    L_00406702:
        fld dword ptr [esi+3B8h]
    L_00406708:
        fadd dword ptr [data_00470b48]
    L_0040670e:
        fstp dword ptr [esi+340h]
    L_00406714:
        mov edx,dword ptr [esi+3BCh]
    L_0040671a:
        mov dword ptr [esi+344h],edx
    L_00406720:
        test dword ptr [esi+364h],8000000h
    L_0040672a:
        je short L_00406747
    L_0040672c:
        mov eax,dword ptr [esi+3E4h]
    L_00406732:
        push 3FC90FDBh
    L_00406737:
        push eax
    L_00406738:
        call asm_Angle_NormalizeSum_0044bc10
    L_0040673d:
        fstp dword ptr [esi+34h]
    L_00406740:
        or dword ptr [esi+364h],4
    L_00406747:
        mov ecx,dword ptr [data_00491c10]
    L_0040674d:
        lea eax,[esi+8]
    L_00406750:
        call asm_FUN_004451c0_004451c0
    L_00406755:
        mov esi,dword ptr [esi+44Ch]
    L_0040675b:
        test esi,esi
    L_0040675d:
        jne short L_004066f0
    L_0040675f:
        mov eax,1
    L_00406764:
        pop esi
    L_00406765:
        ret
    }
}

// 0x00408100..0x00408203: FUN_00408100
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408100_00408100() {
    __asm {
    L_00408100:
        sub esp,18h
    L_00408103:
        push ebp
    L_00408104:
        push esi
    L_00408105:
        mov esi,eax
    L_00408107:
        push edi
    L_00408108:
        add esi,60h
    L_0040810b:
        mov ebp,7D0h
    L_00408110:
        mov ax,word ptr [esi+446h]
    L_00408117:
        test ax,ax
    L_0040811a:
        je asm_target_004081ec
    L_00408120:
        cmp ax,3
    L_00408124:
        je asm_target_004081ec
    L_0040812a:
        mov eax,dword ptr [esp+30h]
    L_0040812e:
        test eax,eax
    L_00408130:
        je short L_0040813d
    L_00408132:
        mov eax,dword ptr [esi+4]
    L_00408135:
        test eax,eax
    L_00408137:
        jne asm_target_004081ec
    L_0040813d:
        fld dword ptr [esi+3B4h]
    L_00408143:
        lea edi,[esi+3B4h]
    L_00408149:
        fsub dword ptr [ebx]
    L_0040814b:
        fstp dword ptr [esp+18h]
    L_0040814f:
        mov eax,dword ptr [esp+18h]
    L_00408153:
        fld dword ptr [esi+3B8h]
    L_00408159:
        mov dword ptr [esp+0Ch],eax
    L_0040815d:
        fsub dword ptr [ebx+4]
    L_00408160:
        fstp dword ptr [esp+1Ch]
    L_00408164:
        mov ecx,dword ptr [esp+1Ch]
    L_00408168:
        fld dword ptr [esi+3BCh]
    L_0040816e:
        mov dword ptr [esp+10h],ecx
    L_00408172:
        fsub dword ptr [ebx+8]
    L_00408175:
        fstp dword ptr [esp+20h]
    L_00408179:
        mov edx,dword ptr [esp+20h]
    L_0040817d:
        fld dword ptr [esi+3F0h]
    L_00408183:
        mov dword ptr [esp+14h],edx
    L_00408187:
        fmul dword ptr [data_00470b0c]
    L_0040818d:
        fadd dword ptr [esp+28h]
    L_00408191:
        fld dword ptr [esp+10h]
    L_00408195:
        fmul dword ptr [esp+10h]
    L_00408199:
        fld dword ptr [esp+0Ch]
    L_0040819d:
        fmul dword ptr [esp+0Ch]
    L_004081a1:
        faddp st(1),st
    L_004081a3:
        fld st(1)
    L_004081a5:
        fmul st,st(2)
    L_004081a7:
        fcompp
    L_004081a9:
        fnstsw ax
    L_004081ab:
        fstp st(0)
    L_004081ad:
        test ah,5
    L_004081b0:
        jnp short L_004081ec
    L_004081b2:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_004081b7:
        push 40000000h
    L_004081bc:
        push 40000000h
    L_004081c1:
        mov ecx,edi
    L_004081c3:
        call asm_OutsideAxisAlignedBounds_004086b0
    L_004081c8:
        test eax,eax
    L_004081ca:
        jne short L_004081ec
    L_004081cc:
        mov eax,dword ptr [esp+2Ch]
    L_004081d0:
        test eax,eax
    L_004081d2:
        je short L_004081ec
    L_004081d4:
        mov eax,dword ptr [data_00477818]
    L_004081d9:
        push 3F19999Ah
    L_004081de:
        push 0BFC90FDBh
    L_004081e3:
        push 0FFFFFFFFh
    L_004081e5:
        push 8
    L_004081e7:
        call asm_FUN_0041bb00_0041bb00
    L_004081ec:
        add esi,7F0h
    L_004081f2:
        dec ebp
    L_004081f3:
        jne asm_target_00408110
    L_004081f9:
        pop edi
    L_004081fa:
        pop esi
    L_004081fb:
        xor eax,eax
    L_004081fd:
        pop ebp
    L_004081fe:
        add esp,18h
    L_00408201:
        ret 0Ch
    }
}

// 0x0040B110..0x0040B1A3: FUN_0040b110
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b110_0040b110() {
    __asm {
    L_0040b110:
        push ebx
    L_0040b111:
        push ebp
    L_0040b112:
        push esi
    L_0040b113:
        mov esi,dword ptr [data_00491c10]
    L_0040b119:
        shl eax,4
    L_0040b11c:
        add eax,474430h
    L_0040b121:
        push edi
    L_0040b122:
        mov edi,eax
    L_0040b124:
        movsx ebp,word ptr [edi]
    L_0040b127:
        call asm_FUN_00449950_00449950
    L_0040b12c:
        mov ecx,dword ptr [esp+18h]
    L_0040b130:
        mov ebx,eax
    L_0040b132:
        mov eax,dword ptr [ebx+35Ch]
    L_0040b138:
        push ebp
    L_0040b139:
        or eax,40000000h
    L_0040b13e:
        push ebx
    L_0040b13f:
        mov dword ptr [ebx+20h],0Fh
    L_0040b146:
        mov dword ptr [ebx+35Ch],eax
    L_0040b14c:
        call asm_FUN_00449870_00449870
    L_0040b151:
        mov esi,dword ptr [data_00491c10]
    L_0040b157:
        lea eax,[esp+18h]
    L_0040b15b:
        mov edx,esi
    L_0040b15d:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0040b162:
        mov ebx,dword ptr [esp+18h]
    L_0040b166:
        push ebx
    L_0040b167:
        mov edx,esi
    L_0040b169:
        call asm_AnimationManager_Find_004491c0
    L_0040b16e:
        mov esi,eax
    L_0040b170:
        test esi,esi
    L_0040b172:
        jne short L_0040b176
    L_0040b174:
        xor ebx,ebx
    L_0040b176:
        mov eax,dword ptr [edi+4]
    L_0040b179:
        test eax,eax
    L_0040b17b:
        je short L_0040b185
    L_0040b17d:
        mov edx,dword ptr [esp+1Ch]
    L_0040b181:
        mov ecx,esi
    L_0040b183:
        call eax
    L_0040b185:
        mov eax,dword ptr [edi+8]
    L_0040b188:
        mov dword ptr [esi+398h],eax
    L_0040b18e:
        mov ecx,dword ptr [edi+0Ch]
    L_0040b191:
        mov eax,dword ptr [esp+14h]
    L_0040b195:
        pop edi
    L_0040b196:
        mov dword ptr [esi+39Ch],ecx
    L_0040b19c:
        pop esi
    L_0040b19d:
        pop ebp
    L_0040b19e:
        mov dword ptr [eax],ebx
    L_0040b1a0:
        pop ebx
    L_0040b1a1:
        ret 0Ch
    }
}

// 0x0040D750..0x0040D7F5: Enemy_TimerSweepRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_TimerSweepRetail_0040d750() {
    __asm {
    L_0040d750:
        push esi
    L_0040d751:
        mov esi,dword ptr [edi+58h]
    L_0040d754:
        test esi,esi
    L_0040d756:
        je short L_0040d7a2
    L_0040d758:
        push ebx
    L_0040d759:
        lea esp,[esp+force_disp32_zero]
    L_0040d760:
        mov eax,dword ptr [esi]
    L_0040d762:
        test dword ptr [eax+2480h],20000h
    L_0040d76c:
        mov ebx,dword ptr [esi+4]
    L_0040d76f:
        jne short L_0040d78e
    L_0040d771:
        add eax,103Ch
    L_0040d776:
        push eax
    L_0040d777:
        call asm_FUN_0040dc80_0040dc80
    L_0040d77c:
        test eax,eax
    L_0040d77e:
        jne short L_0040d78e
    L_0040d780:
        mov esi,dword ptr [esi]
    L_0040d782:
        and dword ptr [esi+2480h],0FFFFFBFFh
    L_0040d78c:
        jmp short L_0040d79b
    L_0040d78e:
        mov ecx,dword ptr [esi]
    L_0040d790:
        test ecx,ecx
    L_0040d792:
        je short L_0040d79b
    L_0040d794:
        mov eax,dword ptr [ecx]
    L_0040d796:
        push 1
    L_0040d798:
        call dword ptr [eax+14h]
    L_0040d79b:
        test ebx,ebx
    L_0040d79d:
        mov esi,ebx
    L_0040d79f:
        jne short L_0040d760
    L_0040d7a1:
        pop ebx
    L_0040d7a2:
        mov edx,dword ptr [edi+44h]
    L_0040d7a5:
        mov ecx,dword ptr [edi+4Ch]
    L_0040d7a8:
        mov dword ptr [edi+40h],edx
    L_0040d7ab:
        fld dword ptr [ecx]
    L_0040d7ad:
        fcomp dword ptr [data_00470b68]
    L_0040d7b3:
        pop esi
    L_0040d7b4:
        fnstsw ax
    L_0040d7b6:
        test ah,41h
    L_0040d7b9:
        jne short L_0040d7e0
    L_0040d7bb:
        fld dword ptr [ecx]
    L_0040d7bd:
        fcomp dword ptr [data_00470b64]
    L_0040d7c3:
        fnstsw ax
    L_0040d7c5:
        test ah,5
    L_0040d7c8:
        jp short L_0040d7e0
    L_0040d7ca:
        fld dword ptr [edi+48h]
    L_0040d7cd:
        inc edx
    L_0040d7ce:
        fadd dword ptr [data_00470afc]
    L_0040d7d4:
        mov dword ptr [edi+44h],edx
    L_0040d7d7:
        mov eax,1
    L_0040d7dc:
        fstp dword ptr [edi+48h]
    L_0040d7df:
        ret
    L_0040d7e0:
        fld dword ptr [ecx]
    L_0040d7e2:
        fadd dword ptr [edi+48h]
    L_0040d7e5:
        fst dword ptr [edi+48h]
    L_0040d7e8:
        call asm_FUN_00463b2c_00463b2c
    L_0040d7ed:
        mov dword ptr [edi+44h],eax
    L_0040d7f0:
        mov eax,1
    L_0040d7f5:
        ret
    }
}

// 0x0040DAE0. Teardown of one enemy record: unlink it from the manager's list,
// drop it from the selector's name tables and the active-enemy slot table,
// detach it from the current game state and release its owned allocation list.
// The link node at +0x116C is embedded in the record, so the same triple is
// both the record's link and the list's node type.
extern "C" unsigned char data_0046d0c0;   // 0x0046D0C0: live method table
extern "C" unsigned char data_0046d0d8;   // 0x0046D0D8: released method table
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Enemy_0040dae0;

struct EnemyLink_0040dae0 {
    int unknown_00;               // +0x00
    EnemyLink_0040dae0* next;     // +0x04
    EnemyLink_0040dae0* prev;     // +0x08

    void Unlink();
};

struct EnemyManager_0040dae0 {
    char unknown_000[0x10];       // +0x00
    int entries[0x12];            // +0x10, indexed by the record's slot index
    EnemyLink_0040dae0* head;     // +0x58
    EnemyLink_0040dae0* tail;     // +0x5C
    int count;                    // +0x60
};

// One bucket of the selector's name tables: the owner pointer designates the
// record whose first word is the searched name.
struct SelectorNode_0040dae0 {
    int* owner;                   // +0x00
    SelectorNode_0040dae0* next;  // +0x04
};

struct SelectorTarget_0040dae0;

struct MemberNode_0040dae0 {
    SelectorTarget_0040dae0* target;   // +0x00
    MemberNode_0040dae0* next;         // +0x04
};

struct SelectorTarget_0040dae0 {
    char unknown_000[0x14];            // +0x000
    MemberNode_0040dae0* members;      // +0x014
    int unknown_018;                   // +0x018
    char unknown_01C[0x35C - 0x1C];    // +0x01C
    int flags;                         // +0x35C
};

struct EnemySelector_0040dae0 {
    char unknown_00000[0x72DAD4];      // +0x000000
    SelectorNode_0040dae0* primary;    // +0x72DAD4
    int unknown_72DAD8;                // +0x72DAD8
    SelectorNode_0040dae0* secondary;  // +0x72DADC
};

struct EnemyFreeNode_0040dae0 {
    void* data;                        // +0x00
    EnemyFreeNode_0040dae0* next;      // +0x04
};

struct Enemy_0040dae0 {
    int vtable;                        // +0x0000
    char unknown_0004[0x1034 - 0x4];   // +0x0004
    EnemyFreeNode_0040dae0* free_list; // +0x1034
    char unknown_1038[0x10FC - 0x1038];
    int entries[10];                   // +0x10FC
    char unknown_1124[0x116C - 0x1124];
    EnemyLink_0040dae0 link;           // +0x116C
    char unknown_1178[0x2480 - 0x1178];
    int flags;                         // +0x2480
    char unknown_2484[0x248C - 0x2484];
    int index;                         // +0x248C
};

struct EnemyState_0040dae0 {
    char unknown_0000[0x3504];         // +0x0000
    Enemy_0040dae0* enemy;             // +0x3504
    unsigned char mirror;              // +0x3508
};

void EnemyLink_0040dae0::Unlink() {
    if (next != 0)
        next->prev = prev;
    if (prev != 0)
        prev->next = next;
    next = 0;
    prev = 0;
}

void __stdcall Enemy_Release_0040dae0(Enemy_0040dae0* self) {
    EnemyManager_0040dae0* manager = *(EnemyManager_0040dae0**)&data_00477704;
    self->vtable = (int)&data_0046d0c0;
    if (manager->head == &self->link)
        manager->head = self->link.next;
    if (manager->tail == &self->link)
        manager->tail = self->link.prev;
    self->link.Unlink();
    --manager->count;
    if (self->flags & 0x8000)
        manager->entries[self->index] = 0;

    EnemySelector_0040dae0* selector = *(EnemySelector_0040dae0**)&data_00491c10;
    int* entry = self->entries;
    for (int remaining = 10; remaining != 0; --remaining) {
        int name = *entry;
        if (name != 0) {
            SelectorNode_0040dae0* node = selector->primary;
            while (node != 0 && *node->owner != name)
                node = node->next;
            if (node == 0) {
                node = selector->secondary;
                while (node != 0 && *node->owner != name)
                    node = node->next;
            }
            if (node != 0) {
                SelectorTarget_0040dae0* target = (SelectorTarget_0040dae0*)node->owner;
                if (target != 0) {
                    target->flags |= 0x4000000;
                    if (target->unknown_018 == 0) {
                        for (MemberNode_0040dae0* member = target->members; member != 0;
                             member = member->next)
                            member->target->flags |= 0x4000000;
                    }
                }
            }
        }
        *entry = 0;
        ++entry;
    }

    EnemyState_0040dae0* state = *(EnemyState_0040dae0**)&data_00477834;
    if (state != 0) {
        if (state->enemy == self) {
            state->enemy = 0;
            state->mirror = 0;
        }
        int* slot = (int*)((char*)state + 0x4E8);
        for (int count = 0x80; count != 0; --count) {
            if (*slot == (int)self)
                *slot = 0;
            slot = (int*)((char*)slot + 0x5C);
        }
    }

    EnemyFreeNode_0040dae0* block = self->free_list;
    self->vtable = (int)&data_0046d0d8;
    while (block != 0) {
        EnemyFreeNode_0040dae0* next = block->next;
        entry_free_004524a1(block->data);
        entry_free_004524a1(block);
        block = next;
    }
}

// 0x0040E6A0..0x0040E755: Enemy_DeathSweepRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_DeathSweepRetail_0040e6a0() {
    __asm {
    L_0040e6a0:
        push ebp
    L_0040e6a1:
        mov ebp,dword ptr [esp+8]
    L_0040e6a5:
        mov eax,dword ptr [ebp+58h]
    L_0040e6a8:
        test eax,eax
    L_0040e6aa:
        je short L_0040e707
    L_0040e6ac:
        push ebx
    L_0040e6ad:
        push esi
    L_0040e6ae:
        push edi
    L_0040e6af:
        nop
    L_0040e6b0:
        mov esi,dword ptr [eax]
    L_0040e6b2:
        mov ebx,dword ptr [eax+4]
    L_0040e6b5:
        mov eax,dword ptr [esi+2480h]
    L_0040e6bb:
        test al,50h
    L_0040e6bd:
        jne short L_0040e6c4
    L_0040e6bf:
        test ah,0C0h
    L_0040e6c2:
        je short L_0040e6c8
    L_0040e6c4:
        test al,al
    L_0040e6c6:
        jns short L_0040e6fe
    L_0040e6c8:
        mov eax,dword ptr [esi+2448h]
    L_0040e6ce:
        test eax,eax
    L_0040e6d0:
        jl short L_0040e6f4
    L_0040e6d2:
        mov ecx,dword ptr [esi+244Ch]
    L_0040e6d8:
        mov edx,dword ptr [data_00477704]
    L_0040e6de:
        push eax
    L_0040e6df:
        lea eax,[esp+18h]
    L_0040e6e3:
        push eax
    L_0040e6e4:
        mov eax,dword ptr [edx+ecx*4+30h]
    L_0040e6e8:
        lea edi,[esi+1068h]
    L_0040e6ee:
        push eax
    L_0040e6ef:
        call asm_PlayerAnimation_Create_00448db0
    L_0040e6f4:
        or dword ptr [esi+2480h],20000h
    L_0040e6fe:
        test ebx,ebx
    L_0040e700:
        mov eax,ebx
    L_0040e702:
        jne short L_0040e6b0
    L_0040e704:
        pop edi
    L_0040e705:
        pop esi
    L_0040e706:
        pop ebx
    L_0040e707:
        mov edx,dword ptr [ebp+44h]
    L_0040e70a:
        mov ecx,dword ptr [ebp+4Ch]
    L_0040e70d:
        mov dword ptr [ebp+40h],edx
    L_0040e710:
        fld dword ptr [ecx]
    L_0040e712:
        fcomp dword ptr [data_00470b68]
    L_0040e718:
        fnstsw ax
    L_0040e71a:
        test ah,41h
    L_0040e71d:
        jne short L_0040e742
    L_0040e71f:
        fld dword ptr [ecx]
    L_0040e721:
        fcomp dword ptr [data_00470b64]
    L_0040e727:
        fnstsw ax
    L_0040e729:
        test ah,5
    L_0040e72c:
        jp short L_0040e742
    L_0040e72e:
        fld dword ptr [ebp+48h]
    L_0040e731:
        inc edx
    L_0040e732:
        fadd dword ptr [data_00470afc]
    L_0040e738:
        mov dword ptr [ebp+44h],edx
    L_0040e73b:
        fstp dword ptr [ebp+48h]
    L_0040e73e:
        pop ebp
    L_0040e73f:
        ret 4
    L_0040e742:
        fld dword ptr [ecx]
    L_0040e744:
        fadd dword ptr [ebp+48h]
    L_0040e747:
        fst dword ptr [ebp+48h]
    L_0040e74a:
        call asm_FUN_00463b2c_00463b2c
    L_0040e74f:
        mov dword ptr [ebp+44h],eax
    L_0040e752:
        pop ebp
    L_0040e753:
        ret 4
    }
}
