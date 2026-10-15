// Compiler context only; never selected as recovered game code. Every body
// below is a copy of a callee recovered in another cluster, compiled here so
// the whole-program pass selects that callee's private registers; the copies
// carry their own section names because the originals' sort out of address
// order when combined.
#include "th10/script/ecl_children.hpp"
#include "script_vm_00450560.hpp"
#include "../../../src/game/spttest/spt_test_update.cpp"

extern "C" void __cdecl crt_free(void* memory);
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
        void* security, unsigned int stack_size, PlatformWorkerEntry start,
        void* arglist, unsigned int initflag, unsigned int* thread_id);

// 0x0040AC90
#pragma code_seg(".text$a1mode")
void __stdcall SptTest_SetGameMode(SptTestGameState* state, int mode) {
    if ((state->flags & 0x1000) == 0) {
        state->mode = mode;
    } else {
        state->mode = 2;
    }
}

// 0x0040ACE0
#pragma code_seg(".text$a2mask")
unsigned short SptTestInput::MaskActive(unsigned short mask) {
    return (mask & repeated) != 0 || (mask & held) != 0;
}

// 0x0042BAD0
#pragma code_seg(".text$a3names")
void SptTest_0042be20::ClearScriptNames() {
    if (script_names) {
        for (int i = 0; i < script_count; ++i) {
            if (script_names[i]) {
                free(const_cast<char*>(script_names[i]));
                script_names[i] = 0;
            }
        }
        if (script_names) {
            free(script_names);
            script_names = 0;
        }
        script_names = 0;
    }
}

// 0x0044BEA0
#pragma code_seg(".text$c1advance")
int MenuCursor::Advance(int delta) {
    int count = item_count;
    if (count > 0) {
    retry_selection:
        selection += delta;
        while (selection >= item_count) {
            if (wrap)
                selection -= count;
            else
                selection = count - 1;
        }
        while (selection < 0) {
            if (wrap)
                selection += count;
            else
                selection = 0;
        }
        for (int index = 0; index < disabled_count; ++index) {
            if (disabled_items[index] == selection)
                goto retry_selection;
        }
    }
    return selection;
}

// 0x0044C150
#pragma code_seg(".text$c2stop")
__declspec(noinline) void PlatformWorker::Stop() {
    if (thread) {
        stop_requested = 1;
        running = 0;
        while (WaitForSingleObject(thread, 200) == 258) {
            stop_requested = 1;
            running = 0;
            Sleep(1);
        }
        CloseHandle(thread);
        thread = 0;
        entry = 0;
    }
}

// 0x0044C1C0
#pragma code_seg(".text$c3start")
void PlatformWorker::Start(void* context, PlatformWorkerEntry start) {
    Stop();
    entry = start;
    running = 1;
    stop_requested = 0;
    thread = (void*)asm_beginthreadex_00453683(0, 0, start, context, 0, &thread_id);
}

// 0x0044FD10
#pragma code_seg(".text$c4tick")
extern "C" __declspec(noinline) int __stdcall SptTest_TickVm(SptTestResource* vm, float delta) {
    EclChildOwner* owner = reinterpret_cast<EclChildOwner*>(vm);
    EclChildNode* node = &owner->children;
    int first = 1;
    while (node) {
        EclChildNode* next = node->next;
        owner->active = node->state;
        if (first) {
            if (EclVm_RunInterpreter(owner->active, delta)) return -1;
            first = 0;
        } else if (EclVm_RunInterpreter(owner->active, delta)) {
            free(owner->active);
            node->Unlink();
            free(node);
        }
        node = next;
    }
    owner->active = &owner->root;
    return 0;
}

// 0x00450500
extern "C" const unsigned int g_enemy_vtable_released[];
inline ScriptVm::ScriptVm()
    : vtable(reinterpret_cast<unsigned int>(g_enemy_vtable_released)), field_1010(0), field_1014(0) {}
#pragma code_seg(".text$c5create")
SptTestResource* ScriptParser::CreateVm(const char* name) {
    ScriptVm* vm = new ScriptVm;
    vm->table = reinterpret_cast<ScriptTable_00450470*>(this);
    vm->current->instruction = vm->table->Resolve(name);
    vm->current->time = 0;
    return reinterpret_cast<SptTestResource*>(vm);
}
#pragma code_seg()

#pragma code_seg(".text$b3context")
void* __stdcall SptTestUpdateCompilerContext() {
    return reinterpret_cast<void*>(SptTest_UpdateTask_0042c580);
}
#pragma code_seg()
