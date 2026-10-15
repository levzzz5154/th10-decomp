// Compiler context only; never selected as recovered game code. Every body
// below stands in for (or copies) a callee recovered or still assembly
// elsewhere, compiled here so the whole-program pass selects that callee's
// private registers.
#include "../../../../src/game/eclview/ecl_view_update.cpp"

extern "C" void __cdecl crt_free(void* memory);
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
        void* security, unsigned int stack_size, PlatformWorkerEntry start,
        void* arglist, unsigned int initflag, unsigned int* thread_id);
extern "C" __declspec(noinline) void __stdcall EclViewStandIn_Callee(void* object);
extern "C" __declspec(noinline) EclViewSpawn_0040a450* __stdcall EclViewStandIn_Init(void* memory, const char* entry);
extern "C" __declspec(noinline) void __stdcall EclViewStandIn_Callee2(void* manager, void* object);

// The seven owned-delete helpers.
#pragma code_seg(".text$a00")
void EclView_Release(EclViewLasers_0040a1a0* object) {
    if (object) {
        object->~EclViewLasers_0040a1a0();
        operator delete(object);
    }
}
#pragma code_seg(".text$a02")
void EclView_Release(EclViewBullets_0040a1a0* object) {
    if (object) {
        object->~EclViewBullets_0040a1a0();
        operator delete(object);
    }
}
#pragma code_seg(".text$c05")
void EclView_Release(EclViewEnemies_0040a940* object) {
    if (object) {
        object->~EclViewEnemies_0040a940();
        operator delete(object);
    }
}
#pragma code_seg(".text$c07")
void EclView_Release(EclViewItems_0040a1a0* object) {
    if (object) {
        object->~EclViewItems_0040a1a0();
        operator delete(object);
    }
}
#pragma code_seg(".text$c08")
void EclView_Release(EclViewEffects_0040a1a0* object) {
    if (object) {
        object->~EclViewEffects_0040a1a0();
        operator delete(object);
    }
}
#pragma code_seg(".text$c10")
void EclView_Release(EclViewPlayer_0040a1a0* object) {
    if (object) {
        object->~EclViewPlayer_0040a1a0();
        operator delete(object);
    }
}
#pragma code_seg(".text$c11")
void EclView_Release(EclViewPopups_0040a1a0* object) {
    if (object) {
        object->~EclViewPopups_0040a1a0();
        operator delete(object);
    }
}

// 0x00405ED0
#pragma code_seg(".text$a01")
void EclViewBullets_0040a1a0::Reset() {
    EclViewStandIn_Callee(update_task);
    memset(reserved_000, 0, 8);
    draw_task = 0;
}

// 0x00409E20
#pragma code_seg(".text$a03")
void EclViewTaskPair_0040a940::Suspend() {
    if (update_task) update_task->flags |= 2;
    if (draw_task) draw_task->flags |= 2;
}

// 0x00409EB0
#pragma code_seg(".text$a04")
void EclView_0040a940::ClearScriptNames() {
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

// 0x00409F90
#pragma code_seg(".text$a05")
void EclViewEnemies_0040a940::Clear() {
    SprtCtrlBatchView* manager = g_sprt_ctrl;
    void** handle = reinterpret_cast<void**>(reinterpret_cast<char*>(manager) + 0x3AD090);
    for (int i = 4; i; --i) EclViewStandIn_Callee2(manager, *handle++);
    for (int j = 0; j < enemy_count; ++j) EclViewStandIn_Callee(parser);
    enemy_count = 0;
}

// 0x0040A010
#pragma code_seg(".text$a06")
void EclViewPlayer_0040a1a0::SuspendAndStop() {
    update_task->flags |= 2;
    draw_task->flags |= 2;
    EclViewStandIn_Callee(this);
}

// 0x0040AC20
#pragma code_seg(".text$c00")
unsigned short EclViewInput_0040a450::Update() {
    unsigned short keys = held_keys;
    held = 0;
    unsigned short* counter = reinterpret_cast<unsigned short*>(this) + 0x1C;
    for (int index = 0; index < 16; ++index) {
        if (keys & 1) {
            if (++*counter >= 26) {
                repeat_flags |= 1;
                *counter -= 8;
            }
        } else {
            *counter = 0;
        }
        keys >>= 1;
        ++counter;
    }
    unsigned short now = held_keys;
    unsigned short before = previous_keys;
    unsigned short changed = now ^ before;
    new_press = changed & now;
    unsigned short released = changed & ~now;
    new_release = released;
    return released;
}

// 0x0040AC90
#pragma code_seg(".text$c01")
void __stdcall EclView_SetGameMode_0040ac90(EclViewGameState_0040a450* state, int mode) {
    if ((state->flags & 0x1000) == 0) {
        state->mode = mode;
    } else {
        state->mode = 2;
    }
}

// 0x0040ACE0
#pragma code_seg(".text$c02")
unsigned short EclViewInput_0040a450::MaskActive(unsigned short mask) {
    return (mask & repeated) != 0 || (mask & held) != 0;
}

// 0x0040CFB0
#pragma code_seg(".text$c03")
void EclViewSpawn_0040a450::Create(EclViewEnemies_0040a940* manager, const char* entry) {
    void* memory = operator new(0x2518);
    EclViewSpawn_0040a450* enemy = 0;
    if (memory) enemy = EclViewStandIn_Init(memory, entry);
    enemy[0x40].x = x;
    enemy[0x40].y = y;
    enemy[0x40].z = z;
    enemy[0x40].life = life;
    memcpy(enemy[0x41].reserved_18, &reserved_18[2], 32);
    EclViewStandIn_Callee2(manager, enemy);
}

// 0x0040D510
#pragma code_seg(".text$c04")
void EclViewEnemies_0040a940::SuspendTasks() {
    if (update_task) update_task->flags |= 2;
    if (draw_task) draw_task->flags |= 2;
}

// 0x00413BC0
#pragma code_seg(".text$c06")
void EclViewItems_0040a1a0::Reset() {
    if (update_task) update_task->flags |= 2;
    if (draw_task) draw_task->flags |= 2;
    SprtCtrlBatchView* manager = g_sprt_ctrl;
    for (int i = 0; i < 4; ++i) {
        EclViewStandIn_Callee2(manager, reserved_000 + i);
        EclViewStandIn_Callee2(manager, this);
    }
}

// 0x00424D90
#pragma code_seg(".text$c09")
void EclViewPlayer_0040a1a0::Reset() {
    EclViewStandIn_Callee(update_task);
    memset(reserved_000, 0, 8);
    draw_task = 0;
}

// 0x0044BEA0
#pragma code_seg(".text$c12")
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
#pragma code_seg(".text$c13")
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
#pragma code_seg(".text$c14")
void PlatformWorker::Start(void* context, PlatformWorkerEntry start) {
    Stop();
    entry = start;
    running = 1;
    stop_requested = 0;
    thread = (void*)asm_beginthreadex_00453683(0, 0, start, context, 0, &thread_id);
}
#pragma code_seg()

#pragma code_seg(".text$b3context")
void* __stdcall EclViewUpdateCompilerContext() {
    return reinterpret_cast<void*>(EclView_UpdateTask_0040abe0);
}
#pragma code_seg()
