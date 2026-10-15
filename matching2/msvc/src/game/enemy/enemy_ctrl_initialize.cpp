// 0x0040D280..0x0040D3CD (334 bytes): MessageHost_Init
//
// Publishes the animation archive on the host, builds the 0x1098-byte message
// parser (vtable 0x0046D0B4), runs its second virtual slot with the script
// name, then builds and registers the two scheduler callback nodes that drive
// the parser and finally resets the host's frame timer.
//
// Retail receives the host in EBX - not a parameter register of any MSVC
// convention - and keeps the script name on the stack (RET 4).  That register
// is a whole-program agreement: the LTCG pass homes the host in EBX because the
// host is live across the parser construction, the parser's virtual call and
// both scheduler registrations, while the node under construction occupies ESI
// and the registration priority EDI.  This source is therefore compiled in the
// same native-LTCG link as the scheduler registration bodies it calls (see
// build_support/layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include <stddef.h>
#include "th10/core/func_ctrl.hpp"

void *__cdecl operator new(unsigned int size);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);
extern "C" unsigned char g_enemy_ctrl_vtable;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct SchedulerCallbackTask_0040d280;

// The 0x24-byte scheduler callback node.  The flag word is read before it is
// written, so the heap-owned clear is a load/mask/store rather than a single
// memory read-modify-write; the barrier keeps the mask next to its store
// instead of letting the scheduler hoist it onto the load.
struct SchedulerCallbackTask_0040d280 {
    int priority;                          // +0x00
    unsigned int flags;                    // +0x04, bit 0 = heap owned
    void *on_tick;                         // +0x08
    void *on_register;                     // +0x0C
    void *on_remove;                       // +0x10
    void *link_task;                       // +0x14
    void *link_next;                       // +0x18
    void *link_previous;                   // +0x1C
    void *context;                         // +0x20

    SchedulerCallbackTask_0040d280();
};

typedef char SchedulerCallbackTask_0040d280_size_must_be_24[
    sizeof(SchedulerCallbackTask_0040d280) == 0x24 ? 1 : -1];

inline SchedulerCallbackTask_0040d280::SchedulerCallbackTask_0040d280() {
    unsigned int previous = flags;
    on_tick = 0;
    on_register = 0;
    on_remove = 0;
    priority = 0;
    _ReadWriteBarrier();
    flags = previous & ~1u;
    link_task = this;
    link_next = 0;
    link_previous = 0;
}

// The parser's own 0x1098-byte body; only the vtable head and the two tail
// words the constructor clears before the memset are named.  The tail words go
// through a pointer local so the two dead stores stay together ahead of the
// inlined memset.
struct MessageParser_0040d280 {
    void *vtable;                          // +0x0000
    unsigned char reserved_004[0x1090 - 0x04];
    unsigned int tail_1090;                // +0x1090
    unsigned int tail_1094;                // +0x1094

    MessageParser_0040d280();
};

typedef char MessageParser_0040d280_size_must_be_1098[
    sizeof(MessageParser_0040d280) == 0x1098 ? 1 : -1];

inline MessageParser_0040d280::MessageParser_0040d280() {
    unsigned int *tail = (unsigned int *)((char *)this + 0x1090);
    tail[0] = 0;
    tail[1] = 0;
    memset(this, 0, sizeof(MessageParser_0040d280));
    vtable = &g_enemy_ctrl_vtable;
}

// View of the same object as a polymorphic one, so the parser's constructor
// call in vtable slot 2 compiles to `mov edx,[ecx]; push arg; call [edx+8]`
// with the object in ECX.
struct MessageParserVirtual_0040d280 {
    virtual void slot_00();
    virtual void slot_04();
    virtual int construct(int argument);   // +0x08
};

#include "th10/game/enemy_ctrl.hpp"

// The global game object whose archive field is published on the host.
struct GameArchiveOwner_0040d280 {
    unsigned char reserved_000[0x3E0B50];
    void *animation_archive;               // +0x3E0B50
};

extern "C" GameArchiveOwner_0040d280 *g_bullet_manager;
extern "C" unsigned char g_game_speed;
extern "C" FuncCtrl *g_func_ctrl;

// Both callback nodes are built by the same sequence: construct, re-clear the
// two routine words, publish the callback and the context, and force bit 0 on
// with bit 1 off.
static SchedulerCallbackTask_0040d280 *BuildCallbackNode_0040d280(
        void *callback, EnemyCtrl *host) {
    SchedulerCallbackTask_0040d280 *node = new SchedulerCallbackTask_0040d280;
    unsigned int flags = node->flags;
    node->on_tick = callback;
    node->on_register = 0;
    node->on_remove = 0;
    node->context = host;
    node->flags = (flags & ~2u) | 1u;
    return node;
}

#pragma code_seg(".text$00d_bmsghost")
extern "C" __declspec(noinline) int __stdcall
EnemyCtrl_Initialize(EnemyCtrl *host, int script_name) {
    host->animation_archive_030 = g_bullet_manager->animation_archive;

    MessageParser_0040d280 *parser = new MessageParser_0040d280;
    host->parser_054 = parser;
    ((MessageParserVirtual_0040d280 *)parser)->construct(script_name);

    SchedulerTask *update =
        (SchedulerTask *)BuildCallbackNode_0040d280((void *)0x40D810, host);
    FuncCtrl_RegisterPrimary(g_func_ctrl, update, 0x12);
    host->update_node_008 = update;

    SchedulerTask *draw =
        (SchedulerTask *)BuildCallbackNode_0040d280((void *)0x40D820, host);
    FuncCtrl_RegisterSecondary(g_func_ctrl, draw, 0x14);
    host->draw_node_00C = draw;

    unsigned int timer_flags = host->timer_flags_050;
    if ((timer_flags & 1u) == 0) {
        host->timer_current_044 = 0;
        host->timer_previous_040 = -999999;
        host->timer_elapsed_048 = 0.0f;
        host->timer_speed_04C = (const float *)&g_game_speed;
        host->timer_flags_050 = timer_flags | 1u;
    }
    host->timer_current_044 = 0;
    host->timer_elapsed_048 = 0.0f;
    host->timer_previous_040 = -1;
    return 0;
}
#pragma code_seg()
