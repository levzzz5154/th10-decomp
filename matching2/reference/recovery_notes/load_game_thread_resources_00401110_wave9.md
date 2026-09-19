# `0x00401110` LoadGameThreadResources — convention cracked, four bytes from EXACT

2026-09-19, wave 9, agent `ThreadChain`. The region is **not landed** (a 4-byte
scheduling residual remains), but the allocator trap the third-wave note stopped
at is solved: the body now carries **retail's register pairing** — object in
EAX, saved to EBX with `push ebx` / `mov ebx,eax` / two `pop ebx`, interior
EBX/ESI/EDI — and the emitted extent is exactly retail's 330 bytes. The
`0x00401440` factory that goes with it is **EXACT 69/69, 0 differing**.

Probe (maintained flags, throwaway copy `/tmp/ThreadChain/msvc`, the layout
registered in that copy only):

```text
python3 matching2/tools/matching/probe.py \
    --source src/game/load_game_thread_resources_00401110.cpp \
    --project /tmp/ThreadChain/msvc --output /tmp/ThreadChain/outfinal --show 30
0x00401110     330 bytes  ?LoadGameThreadResources_00401110@GameThread@@QAEHXZ  DIFFERENT
  first difference at 0x0040121f
  expected: c6 8b cf 89 be 08 03 00 00 e8 73 d3 03 00 ...   0x0040121e: 8b c6  mov eax,esi
  actual:   cf 8b c6 89 be 08 03 00 00 e8 73 d3 03 00 ...   0x0040121e: 8b cf  mov ecx,edi
0x00401440      69 bytes  ?CreateGameThread_00401440@@YGPAUGameThread@@XZ  EXACT
NOT EXACT
```

| | value |
| --- | --- |
| declared size | 330 |
| emitted size | **330** (equal: the extent is retail's) |
| differing bytes | **4 of 330** |
| differing instructions | 4 of 87 — two pairs of 2-byte register moves, transposed |
| first difference | `0x0040121f` |
| factory `0x00401440` | **69 emitted, 0 differing** |

## 1. The one line that flips the whole-program pass

The three-source link of the previous note emitted EAX-in + ESI-interior (332
bytes, `this` in ESI); the fuller links flipped the entry to EBX (325 bytes,
transparent EBX, no prologue, 308 differing). Retail is EAX-in **and**
EBX-interior. What forces both at once is the **statement order of the second
block's two preamble statements**. Retail's own scheduling shows it:

```asm
0040122d  lea 0x3c0(%ebx),%esi     ; block = &this->blocks[1]  first
00401233  mov 0x8994(%ebx),%ebx    ; resource = this->resource_8994  second
```

Writing exactly that order in the source —

```cpp
    block = &this->blocks[1];
    resource = this->resource_8994;
```

— makes the pass emit `push ebx` / `mov ebx,eax` (the object now *has* to be
saved and sunk, because the body writes EBX for the second resource), and the
entry register falls back to EAX. Measured, same anchors, only that one swap:

| source order of block 1's preamble | loader | differing | factory |
| --- | ---: | ---: | --- |
| `resource = …; block = …;` (previous note's model) | 325 | 308 | 22 differing |
| `block = …; resource = …;` (**this note**) | **330** | **4** | **EXACT** |

Everything else in the previous note's model is unchanged and every one of the
87 instructions is retail's, instruction for instruction, with retail's
EBX/ESI/EDI interior, the three scheduler registration call sites, the
`TextLog::Append` site, both `Entity_Init` sites (no `xor %ecx,%ecx`) and both
`ConfigureFromResource` sites all byte-identical.

A second, independent ordering fact: the two *secondary* registrations must be
written **context before flags** (`secondary->context = this;` then
`secondary->reserved_flags &= ~1u;`). Written flags-first (as in the previous
note) the pass transposes the two stores at `0x4011CF`/`0x4011FB` (8 of the 12
residual bytes). Retail's primary registration keeps flags-first; swapping the
primary as well is byte-neutral, so only the two secondary groups matter.

## 2. The remaining four bytes

```text
0x40121e  emitted 8b cf 8b c6   mov ecx,edi / mov esi,eax
0x40121e  retail  c6 8b cf      mov eax,esi / mov edi,ecx      (block 0)
0x401245  emitted 8b cb 8b c6   mov ecx,ebx / mov esi,eax
0x401245  retail  c6 8b cb      mov eax,esi / mov ebx,ecx      (block 1)
```

Both sites materialise the same three argument registers for the animation call
(this `0x43E5A0` takes object in EAX, resource in ECX, index in EDX): ours emits
them right-to-left (index, resource, this), retail emits index, **this**,
resource. Every other byte, including the store `mov %edi,0x308(%esi)` that sits
between the moves and the call, agrees.

That order is a list-scheduling decision, and it is stable under everything I
could reach: 40-odd shapes listed in §5 all leave exactly these four bytes.
Two independent checks say the order is not a property of the callee: the
landed `0x0043E5A0` cluster's own context loop emits the same right-to-left
order for the same ABI, and the anchor-body experiments below only changed it by
changing the *ABI*, never the ABI's move order.

## 3. Integration shape: anchors, not a four-cluster merge

The previous note's §7 plan (dissolve `scheduler_tasks.json`,
`d3d_text_log_append_0044b810.json`, `game_thread.json`,
`anm_object_configure_0043e5a0.json` and rename two `code_seg` tags) is **no
longer the shape the tree needs**: commit `c27b9812` already merged
`scheduler_tasks.cpp`, `text_log.cpp` and `joystick_probe.cpp` into the
five-source cluster `layout/ltcg/bullet_manager_load_scripts_0040ae70.json`
(they can no longer be claimed by a second cluster), and `0x401DE0` has since
landed as the carved unit `src/game/entity_initialize_00401de0.cpp`.

This note's cluster therefore claims **only its own two sources** and carries
the callees it needs to see as compiled **ABI anchors** in its driver — the
mechanism `0x0041C480` introduced. Nothing landed is touched, no section is
renamed, no landed cluster is dissolved:

| layout entry | kind | address | size | body in the driver |
| --- | --- | ---: | ---: | --- |
| `LoadGameThreadResources_00401110` | selected | `0x401110` | 330 | — |
| `CreateGameThread_00401440` | selected | `0x401440` | 69 | — |
| `??0GameThread@@QAE@XZ` | anchor | `0x401000` | 251 | the landed constructor body |
| `@Entity_Init_Model@8` | anchor | `0x401DE0` | 63 | raw-offset stand-in (see below) |
| `ConfigureFromResource@…0043e5a0` | anchor | `0x43E5A0` | 356 | the landed configuration body |
| `_Scheduler_RegisterPrimary@12` | anchor | `0x449AE0` | 131 | the landed registration body |
| `_Scheduler_RegisterSecondary@12` | anchor | `0x449B70` | 131 | the landed registration body |
| `?Append@TextLog_0044b810@@QAAPADPADZZ` | anchor | `0x44B810` | 201 | the landed append body |

Measured: the scheduler, text-log and constructor anchors emit **byte-identical
to retail** inside this link (0 differing); the animation anchor differs in 6
bytes, all of them the pooled `0.00390625` operand address (`fmuls 0x44C000`
against retail's `ds:0x470B7C`) — harmless, because an anchor is never exported,
but it is why the merged layout cannot carry the previous note's
`constant_aliases` entry: `validate_native_output` requires an alias to be
referenced by a *selected* body, and here the literal only appears in an anchor.

**The entity anchor is deliberately a stand-in.** A visible body whose first
slot is dead is what removes the two `xor %ecx,%ecx` from the loader's call
sites; binding the symbol opaquely (absolute_symbols only) brings them back, and
so does a body shape that moves the ABI (`this` read first) — verified. The
faithful 273-byte body cannot be compiled in the driver TU (`entity.hpp`'s
`SchedulerTask` collides with `scheduler.hpp`'s), so the anchor uses a
raw-offset body with the landed body's statement structure; a 271-byte faithful
raw-offset variant was measured to leave the loader's bytes unchanged.

## 4. Cluster layout (as measured) and driver

`layout/ltcg/loader_chain.json` (schema 1; the file as built is in
`/tmp/ThreadChain/msvc/layout/ltcg/`): `source`
`src/game/load_game_thread_resources_00401110.cpp`, `additional_sources`
`["src/game/create_game_thread_00401440.cpp"]`, `headers`
`["include/th10/game/game_thread.hpp", "include/th10/game/scheduler.hpp",
"include/th10/platform/thread_sync.hpp"]`, `driver`
`layout/ltcg/loader_chain_context.cpp`, the two selected functions and the six
anchors of §3, context `?CreateGameThreadCompilerContext@@YGHPAUGameThread@@HPAUScheduler@@PAPAUSchedulerTask@@H@Z`
in `.text$05context` at `0x401F00` (99 bytes emitted), and these eight gaps
(section names sort after the item they follow, per the merge rule):

```text
.text$01zgap  0x4010FB   21     .text$05zgap  0x401F63  247357
.text$02zgap  0x40125A  486     .text$06zgap  0x43E704   46044
.text$04dgap  0x401485 2395     .text$20zgap  0x449B63      13
.text$04zkgap 0x401E1F  225     .text$40zgap  0x449BF3    7197
```

`layout/ltcg/loader_chain_context.cpp` is the previous note's driver with the
six anchor bodies in front of it:

```cpp
// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../src/game/load_game_thread_resources_00401110.cpp"
#include "th10/platform/thread_sync.hpp"
#include <string.h>
#include <stdarg.h>

#define GameThread_ClearSlotFlag(address) \
    do { unsigned* flag_ = (address); *flag_ &= ~1u; } while (0)

// ... the six anchors of §3, each in its own .text$ section and noinline ...

// ---------------------------------------------------------------- context ---
GameThread* CreateGameThread_00401440();

#pragma code_seg(".text$05context")
__forceinline void* __cdecl operator new(unsigned int, void* memory) { return memory; }

int __stdcall CreateGameThreadCompilerContext(GameThread* threads, int count,
                                              Scheduler* scheduler, SchedulerTask** tasks,
                                              int priority) {
    for (int index = 0; index < count; ++index)
        new (&threads[index]) GameThread;
    for (int index = 0; index < count; ++index) {
        SchedulerTask* task = tasks[index];
        Scheduler_RegisterPrimary(scheduler, task, priority);
        Scheduler_RegisterSecondary(scheduler, task, priority);
    }
    return CreateGameThread_00401440() != 0;
}
#pragma code_seg()
```

The driver TU must `#include` the loader source (the include check requires every
declared source to appear) and the anchors must follow it; the priority moves in
§1 stay in the source. `include/th10/game/game_thread.hpp` (new; `GameThread` +
`GameThreadBlock` with `offsetof`//`sizeof` assertions) is shared by the loader
and the factory, and `src/game/game_thread.cpp` should be migrated to it — that
migration was **not** done here (no landing), and it is the only landed file the
final integration has to touch besides the manifest.

## 5. Shapes tried against the last four bytes (all 330 bytes, all 4 differing)

Anchor side: the animation anchor replaced by a `this`-first body, a
resource-first body, a 23-byte body (that one also breaks the ABI: 322 bytes,
142 differing); a 271-byte faithful raw-offset entity anchor; the entity,
animation and text-log entry order in the layout reversed; the anchor `name`
fields renamed; the animation's *class* name is fixed by the mangled symbol.

Caller side: member, free `__cdecl`/`__stdcall`/`__fastcall` and static-member
declarations of the region; one and two dead parameters (including the
`member_dead` shape that is the sibling's entity trick); a `self`-local copy of
`this`; an empty `__asm {}` barrier at the top; the animation group as an
inlined pair-setter, as a per-block helper, as an index-first helper, per block
and for both blocks; the group's store first, last, through the animation
object, through a raw `*(CachedResource**)((char*)block+0x308)` cast, through a
temp; the resource argument re-read from `block->animation`; the parameters
declared in swapped order (that one changes the ABI: 12 differing); context
before/after flags for all three registrations; block-0 preamble swapped
separately and together with block 1; the whole pair as an unrolled two-iteration
loop (311 bytes, not unrolled); three register-pressure contexts, two direct
loader-call loops, a factory loop, a 174-byte pair of synthetic second callers
that keep callee-saved values live across the call, three register-pressure
ballast anchors, and the loader-call context called at four different points.

## 6. Reproduce

```bash
cp -a matching2/msvc /tmp/<id>/msvc
# /tmp/ThreadChain/{harness.py,press*.py} drives the variant builds directly
# through matching2.tools.matching.ltcg_cluster.{load_cluster,build_cluster}
# (no registration, adaptive size/gap convergence from the link map).
python3 press10.py aliasonly        # the shaped model of §1: 330 / 4 differing
```

## 7. Integration statement

Nothing from this run is in the maintained tree: no manifest record, no layout,
no header, no source, no section was edited, and no symbol of another agent's
region is bound. The artifacts live in `/tmp/ThreadChain/msvc/` (`src/game/…`,
`layout/ltcg/loader_chain.{json,cpp}`, the shared header) and would need an
`apply_package.py` payload plus the `game_thread.cpp` header migration if a
future agent closes the last four bytes. **A non-exact layout must not be
registered**, so `0x00401110` and `0x00401440` stay `asm` for now — even though
the factory's model in this same link is byte-exact, it is only reachable
through the link that also renders the loader, and the factory's own record
cannot be split from it.

## Appendix A: the shaped model (`src/game/load_game_thread_resources_00401110.cpp`)

```cpp
// 0x00401110: bind the game thread's resources, scheduler tasks and blocks.
//
// The thread object arrives in EAX in retail and is kept in EBX inside the
// body, so the region is modelled as a member function and compiled through a
// native LTCG cluster (see layout/ltcg/loader_chain.json) whose driver carries
// compiled ABI anchors for the callees whose parameter registers no declaration
// names.

#include "th10/game/game_thread.hpp"
#include "th10/game/scheduler.hpp"

typedef void (__cdecl *ScheduleCallback)(void);

// The shared resource table pointer, the global scheduler and the resource
// names all live in absolute slots the image fixes.
extern "C" void* data_00491c10;
extern "C" Scheduler* data_00491be4;
extern "C" char data_0046cb80[];
extern "C" char data_0046cb5c[];
extern "C" char data_0046cb50[];
extern "C" char data_0046cb68[];
// The constant log object and the three task callbacks.
extern "C" char data_00474f70[];
extern "C" void __cdecl callback_004014f0();
extern "C" void __cdecl callback_00401510();
extern "C" void __cdecl callback_00401520();

CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name);
extern "C" int* __stdcall SchedulerCallback_Create_00449ed0(ScheduleCallback callback);

// The animation object and its archive record, declared exactly as the landed
// 0x0043E5A0 configuration body declares them; the loader only calls the member
// and the cluster's driver anchors the body at its retail address.
struct Resource_0043e5a0 {
    unsigned char reserved[0x200];
};

struct Matrix4x4_0043e5a0 {
    float values[4][4];

    __forceinline void SetIdentity();
};

struct AnimationObject_0043e5a0 {
    unsigned char reserved_0000[0x04C];
    float width;                                       // +0x04C
    float height;                                      // +0x050
    unsigned char reserved_054[0x23C - 0x054];
    Matrix4x4_0043e5a0 block_a;                        // +0x23C
    Matrix4x4_0043e5a0 block_copy;                     // +0x27C
    Matrix4x4_0043e5a0 block_b;                        // +0x2BC
    unsigned char reserved_2fc[0x308 - 0x2FC];
    Resource_0043e5a0* resource;                       // +0x308
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;                       // +0x384
    unsigned char reserved_386[0x394 - 0x386];
    unsigned char* record;                             // +0x394

    __declspec(noinline) int ConfigureFromResource(Resource_0043e5a0* resource,
                                                   int index);
};

__forceinline void Matrix4x4_0043e5a0::SetIdentity() {
    values[3][2] = 0.0f;
    values[3][1] = 0.0f;
    values[3][0] = 0.0f;
    values[2][3] = 0.0f;
    values[2][1] = 0.0f;
    values[2][0] = 0.0f;
    values[1][3] = 0.0f;
    values[1][2] = 0.0f;
    values[1][0] = 0.0f;
    values[0][3] = 0.0f;
    values[0][2] = 0.0f;
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}

struct Entity;
extern "C" void __fastcall Entity_Init_Model(void* unused, Entity* entity);

// The constant log's 8 KiB text buffer, its write cursor and its dirty byte.
struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    __declspec(noinline) char* Append(char* format, ...);
};

// The three loads that must all succeed; a failure logs the constant message
// and reports -1, which the factory turns into a destroyed thread.
#pragma code_seg(".text$02load")
int GameThread::LoadGameThreadResources_00401110() {
    resource_8994 = Recovery_LoadCachedResource(2, data_00491c10, data_0046cb80);
    if (resource_8994 == 0) {
        ((TextLog_0044b810*)data_00474f70)->Append(data_0046cb68);
        return -1;
    }
    resource_899C = Recovery_LoadCachedResource(0, data_00491c10, data_0046cb5c);
    if (resource_899C == 0) {
        ((TextLog_0044b810*)data_00474f70)->Append(data_0046cb68);
        return -1;
    }
    resource_8998 = Recovery_LoadCachedResource(3, data_00491c10, data_0046cb50);
    if (resource_8998 == 0) {
        ((TextLog_0044b810*)data_00474f70)->Append(data_0046cb68);
        return -1;
    }

    // The primary task ticks at the base priority, the two secondary ones at
    // 0x30 and 0x26.
    SchedulerTask* primary =
        (SchedulerTask*)SchedulerCallback_Create_00449ed0(callback_004014f0);
    primary->reserved_flags &= ~1u;
    primary->context = this;
    Scheduler_RegisterPrimary(data_00491be4, primary, 4);
    this->primary_task = primary;

    SchedulerTask* secondary =
        (SchedulerTask*)SchedulerCallback_Create_00449ed0(callback_00401510);
    secondary->context = this;
    secondary->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 0x30);
    this->secondary_task = secondary;

    SchedulerTask* tertiary =
        (SchedulerTask*)SchedulerCallback_Create_00449ed0(callback_00401520);
    tertiary->context = this;
    tertiary->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, tertiary, 0x26);
    this->third_task = tertiary;

    // Each block binds the first resource as its animation owner, at frame 0
    // for the first player and frame 0x62 for the second.
    CachedResource* resource = this->resource_8994;
    GameThreadBlock* block = &this->blocks[0];
    Entity_Init_Model(0, (Entity*)block);
    block->animation = resource;
    ((AnimationObject_0043e5a0*)block)->ConfigureFromResource((Resource_0043e5a0*)resource, 0);

    block = &this->blocks[1];
    resource = this->resource_8994;
    Entity_Init_Model(0, (Entity*)block);
    block->animation = resource;
    ((AnimationObject_0043e5a0*)block)->ConfigureFromResource((Resource_0043e5a0*)resource, 0x62);
    return 0;
}
#pragma code_seg()

```

## Appendix B: the factory (`src/game/create_game_thread_00401440.cpp`, EXACT in this link)

```cpp
// 0x00401440: allocate and construct the game thread, then bind its resources.
//
// The factory hands the loader the thread in EAX and keeps its own copy in ESI,
// so it is compiled inside the loader's native LTCG cluster
// (layout/ltcg/loader_chain.json).

#include "th10/game/game_thread.hpp"

void* __cdecl operator new(unsigned int size);

extern "C" void __stdcall DestroyGameThread_00401260(GameThread* thread);
extern "C" void __cdecl Free_004524a1(void* memory);

#pragma code_seg(".text$04create")
__declspec(noinline) GameThread* CreateGameThread_00401440() {
    GameThread* thread = new GameThread;
    if (thread->LoadGameThreadResources_00401110() != 0) {
        if (thread) {
            DestroyGameThread_00401260(thread);
            Free_004524a1(thread);
        }
        return 0;
    }
    return thread;
}
#pragma code_seg()

```
