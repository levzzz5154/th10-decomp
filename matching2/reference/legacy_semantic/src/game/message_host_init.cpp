// =============================================================================
// message_host_init.cpp - Message (MSG) host construction
// Functions: 0x0040D280
// =============================================================================
#include "th10/game/message_host_init.hpp"

#include <cstring>

namespace {

// Both callback nodes are built by the same inline sequence. The allocation
// block reads the freshly allocated flags word before writing it, so the mask
// is applied to whatever operator new happened to leave there; the second
// update then forces bit 0 on and bit 1 off regardless.
SchedulerCallbackNode* BuildCallbackNode(const MessageHostInitHooks* hooks,
                                         void* callback, void* context) {
    SchedulerCallbackNode* node = (SchedulerCallbackNode*)hooks->allocate(
        hooks->context, MESSAGE_HOST_NODE_SIZE);
    if (node != 0) {
        const unsigned int previous = node->flags;
        node->callback = 0;
        node->reserved_0c = 0;
        node->reserved_10 = 0;
        node->reserved_00 = 0;
        node->flags = previous & ~1u;
        node->self = node;
        node->reserved_18 = 0;
        node->reserved_1c = 0;
    }

    // Retail reads through the node here without re-testing it for null, so a
    // failed allocation faults rather than propagating a null node.
    const unsigned int flags = (node->flags & ~3u) | 1u;
    node->callback = callback;
    node->reserved_0c = 0;
    node->reserved_10 = 0;
    node->context = context;
    node->flags = flags;
    return node;
}

} // namespace

// 0x0040D280 - Construct the message host: publish the animation archive,
// build the MSG parser, register the update and draw callbacks, and reset the
// host timer.
//
// Three details are preserved deliberately because they look like mistakes.
//
// First, the parser allocation zeroes its last two words before memset clears
// the whole 0x1098-byte block, so those two stores are dead.
//
// Second, both the parser and the callback nodes are null-checked at their
// allocation sites and then dereferenced unconditionally afterwards, so an
// allocation failure faults instead of returning cleanly. That is reproduced
// rather than hardened, since hardening it would change observable behavior.
//
// Third, the trailing timer block writes the -999999 sentinel and a zero
// counter only to overwrite both immediately, which is exactly the shared
// Timer_Reset leaf; this function reuses it instead of restating it.
int MessageHost_Init(MessageHost* host, int parser_argument,
                     const MessageHostInitHooks* hooks) {
    host->animation_archive =
        *(void* const*)((const unsigned char*)hooks->game_object +
                        MESSAGE_HOST_ARCHIVE_OFFSET);

    void* parser = hooks->allocate(hooks->context, MESSAGE_HOST_PARSER_SIZE);
    if (parser != 0) {
        unsigned int* words = (unsigned int*)parser;
        // Dead: overwritten by the memset on the next line.
        words[1060] = 0;
        words[1061] = 0;
        std::memset(parser, 0, MESSAGE_HOST_PARSER_SIZE);
        *(const void**)parser = hooks->parser_vtable;
    }
    host->parser = parser;
    hooks->parser_construct(parser, parser_argument);

    SchedulerCallbackNode* update =
        BuildCallbackNode(hooks, hooks->update_callback, host);
    hooks->register_primary(MESSAGE_HOST_UPDATE_PRIORITY, update,
                            hooks->callback_list);
    host->update_node = update;

    SchedulerCallbackNode* draw =
        BuildCallbackNode(hooks, hooks->draw_callback, host);
    hooks->register_secondary(MESSAGE_HOST_DRAW_PRIORITY, draw,
                              hooks->callback_list);
    host->draw_node = draw;

    Timer_Reset(&host->timer);
    return 0;
}
