// Focused semantic tests for the message host constructor at 0x0040D280.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#include "th10/game/message_host_init.hpp"

// math_utils.cpp declares this shared time scale as extern.
unsigned int DAT_00476f78 = 0x3F800000u;

namespace {

// Bump allocator over storage pre-filled with 0xFF so that the memset and the
// flag masking are both observable.
unsigned char g_arena[0x8000];
size_t g_used;
int g_allocations;
unsigned int g_alloc_sizes[8];

void* Allocate(void* context, unsigned int bytes) {
    (void)context;
    if (g_allocations < 8) g_alloc_sizes[g_allocations] = bytes;
    ++g_allocations;
    g_used = (g_used + 15) & ~(size_t)15;
    void* result = g_arena + g_used;
    // The retail sizes are recorded above and asserted by the tests, but the
    // block is padded here: this reconstruction's structs carry real pointers
    // and are therefore wider on a 64-bit host than the 32-bit retail layout,
    // so consecutive allocations would otherwise overlap.
    g_used += bytes + 64;
    assert(g_used <= sizeof(g_arena));
    return result;
}

int g_construct_calls;
void* g_construct_parser;
int g_construct_argument;

void Construct(void* parser, int argument) {
    ++g_construct_calls;
    g_construct_parser = parser;
    g_construct_argument = argument;
}

int g_primary_priority;
SchedulerCallbackNode* g_primary_node;
void* g_primary_list;
int g_primary_calls;

void RegisterPrimary(int priority, SchedulerCallbackNode* node, void* list) {
    ++g_primary_calls;
    g_primary_priority = priority;
    g_primary_node = node;
    g_primary_list = list;
}

int g_secondary_priority;
SchedulerCallbackNode* g_secondary_node;
void* g_secondary_list;
int g_secondary_calls;

void RegisterSecondary(int priority, SchedulerCallbackNode* node, void* list) {
    ++g_secondary_calls;
    g_secondary_priority = priority;
    g_secondary_node = node;
    g_secondary_list = list;
}


struct Fixture {
    std::vector<unsigned char> game_object;
    MessageHost host;
    MessageHostInitHooks hooks;
    void* archive;
    int list_marker;
    int update_fn;
    int draw_fn;
};

void Reset(Fixture& f) {
    std::memset(g_arena, 0xFF, sizeof(g_arena));
    g_used = 0;
    g_allocations = 0;
    g_construct_calls = 0;
    g_primary_calls = 0;
    g_secondary_calls = 0;

    f.game_object.assign(MESSAGE_HOST_ARCHIVE_OFFSET + 16, 0);
    f.archive = (void*)0xA5A5A5A0;
    *(void**)(f.game_object.data() + MESSAGE_HOST_ARCHIVE_OFFSET) = f.archive;

    std::memset(&f.host, 0xEE, sizeof(f.host));
    f.host.timer.flags = 0;

    f.hooks.context = 0;
    f.hooks.game_object = f.game_object.data();
    f.hooks.allocate = Allocate;
    f.hooks.parser_vtable = (const void*)&f.list_marker;
    f.hooks.parser_construct = Construct;
    f.hooks.register_primary = RegisterPrimary;
    f.hooks.register_secondary = RegisterSecondary;
    f.hooks.callback_list = &f.list_marker;
    f.hooks.update_callback = &f.update_fn;
    f.hooks.draw_callback = &f.draw_fn;
}

// The archive is republished from a fixed offset inside the global game
// object, the same field the region sweep reads.
void TestArchiveIsRepublished() {
    Fixture f;
    Reset(f);
    assert(MessageHost_Init(&f.host, 7, &f.hooks) == 0);
    assert(f.host.animation_archive == f.archive);
}

// Two allocations happen at the retail sizes, and the parser is fully zeroed
// apart from the installed vtable - which is what makes the two stores to the
// final words of the block dead.
void TestParserIsAllocatedAndFullyCleared() {
    Fixture f;
    Reset(f);
    MessageHost_Init(&f.host, 7, &f.hooks);

    assert(g_allocations == 3);
    // Retail requests one parser block and two callback nodes.
    assert(g_alloc_sizes[0] == MESSAGE_HOST_PARSER_SIZE);
    assert(g_alloc_sizes[1] == MESSAGE_HOST_NODE_SIZE);
    assert(g_alloc_sizes[2] == MESSAGE_HOST_NODE_SIZE);
    assert(g_alloc_sizes[0] == 0x1098u);
    assert(g_alloc_sizes[1] == 0x24u);

    unsigned char* parser = (unsigned char*)f.host.parser;
    assert(parser == g_arena);
    assert(*(const void**)parser == f.hooks.parser_vtable);
    for (size_t i = sizeof(void*); i < MESSAGE_HOST_PARSER_SIZE; ++i)
        assert(parser[i] == 0);

    // The two dead stores target the last two words of the block.
    const unsigned int* words = (const unsigned int*)parser;
    assert(words[1060] == 0);
    assert(words[1061] == 0);
}

// The parser constructor runs once against the freshly built parser.
void TestParserConstructorRuns() {
    Fixture f;
    Reset(f);
    MessageHost_Init(&f.host, 4321, &f.hooks);
    assert(g_construct_calls == 1);
    assert(g_construct_parser == f.host.parser);
    assert(g_construct_argument == 4321);
}

// Each node keeps a self pointer and the owning host, and its flag word has
// bit 0 forced on and bit 1 forced off while the remaining bits survive from
// the allocation.
void TestCallbackNodesAreBuilt() {
    Fixture f;
    Reset(f);
    MessageHost_Init(&f.host, 0, &f.hooks);

    SchedulerCallbackNode* update = f.host.update_node;
    SchedulerCallbackNode* draw = f.host.draw_node;
    assert(update != 0 && draw != 0 && update != draw);

    assert(update->callback == f.hooks.update_callback);
    assert(draw->callback == f.hooks.draw_callback);
    assert(update->context == &f.host);
    assert(draw->context == &f.host);
    assert(update->self == update);
    assert(draw->self == draw);
    assert(update->reserved_00 == 0);
    assert(update->reserved_0c == 0);
    assert(update->reserved_10 == 0);
    assert(update->reserved_18 == 0);
    assert(update->reserved_1c == 0);

    // Allocation storage was 0xFFFFFFFF: bit 0 set, bit 1 cleared, rest kept.
    assert(update->flags == 0xFFFFFFFDu);
    assert(draw->flags == 0xFFFFFFFDu);
}

// The update node goes to the primary list at priority 18 and the draw node to
// the secondary list at priority 20, both against the shared callback list.
void TestRegistrationPrioritiesAndLists() {
    Fixture f;
    Reset(f);
    MessageHost_Init(&f.host, 0, &f.hooks);

    assert(g_primary_calls == 1);
    assert(g_secondary_calls == 1);
    assert(g_primary_priority == MESSAGE_HOST_UPDATE_PRIORITY);
    assert(g_secondary_priority == MESSAGE_HOST_DRAW_PRIORITY);
    assert(g_primary_priority == 18);
    assert(g_secondary_priority == 20);
    assert(g_primary_node == f.host.update_node);
    assert(g_secondary_node == f.host.draw_node);
    assert(g_primary_list == f.hooks.callback_list);
    assert(g_secondary_list == f.hooks.callback_list);
}

// The trailing timer block is exactly the shared Timer_Reset leaf: the
// -999999 sentinel it writes is immediately replaced by -1.
void TestTimerIsResetNotLeftAtSentinel() {
    Fixture f;
    Reset(f);
    MessageHost_Init(&f.host, 0, &f.hooks);

    assert(f.host.timer.previous == -1);
    assert(f.host.timer.current == 0);
    assert(f.host.timer.elapsed == 0.0f);
    assert(f.host.timer.speed == (const float*)&DAT_00476f78);
    assert((f.host.timer.flags & 1u) != 0);
    assert(f.host.timer.previous != -999999);
}

// A host whose timer already carries the initialized bit keeps its existing
// speed pointer, because the sentinel branch is skipped.
void TestTimerSpeedIsNotRepublishedWhenAlreadyInitialized() {
    Fixture f;
    Reset(f);
    float other = 2.0f;
    f.host.timer.flags = 1u;
    f.host.timer.speed = &other;
    MessageHost_Init(&f.host, 0, &f.hooks);

    assert(f.host.timer.speed == &other);
    assert(f.host.timer.previous == -1);
    assert(f.host.timer.current == 0);
}

} // namespace

int main() {
    TestArchiveIsRepublished();
    TestParserIsAllocatedAndFullyCleared();
    TestParserConstructorRuns();
    TestCallbackNodesAreBuilt();
    TestRegistrationPrioritiesAndLists();
    TestTimerIsResetNotLeftAtSentinel();
    TestTimerSpeedIsNotRepublishedWhenAlreadyInitialized();
    std::printf("MESSAGE_HOST_INIT_PASS\n");
    return 0;
}
