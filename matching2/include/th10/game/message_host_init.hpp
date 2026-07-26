// =============================================================================
// message_host_init.hpp - Message (MSG) host construction
// Retail function: 0x0040D280
// =============================================================================
#ifndef TH10_GAME_MESSAGE_HOST_INIT_HPP
#define TH10_GAME_MESSAGE_HOST_INIT_HPP

#include "th10/math/timer.hpp"

enum {
    MESSAGE_HOST_PARSER_SIZE = 0x1098,  // operator new size for the parser
    MESSAGE_HOST_NODE_SIZE = 0x24,      // operator new size for a callback node
    MESSAGE_HOST_UPDATE_PRIORITY = 18,  // primary list slot (0x00449AE0)
    MESSAGE_HOST_DRAW_PRIORITY = 20,    // secondary list slot (0x00449B70)
    // Byte offset of the animation archive inside the global game object.
    // The rectangular region sweep at 0x00408210 reads the same field.
    MESSAGE_HOST_ARCHIVE_OFFSET = 4066128
};

// The 0x24-byte scheduler callback node built inline by 0x0040D280. The list
// insertion itself lives in scheduler.cpp (0x00449AE0 / 0x00449B70).
struct SchedulerCallbackNode {
    unsigned int reserved_00; // +0x00
    unsigned int flags;       // +0x04
    void* callback;           // +0x08
    unsigned int reserved_0c; // +0x0C
    unsigned int reserved_10; // +0x10
    SchedulerCallbackNode* self; // +0x14, points back at the node
    unsigned int reserved_18; // +0x18
    unsigned int reserved_1c; // +0x1C
    void* context;            // +0x20, the owning host
};

// The 0x68-byte host allocated by the caller at 0x0040D3E0.
struct MessageHost {
    unsigned int flags;                  // +0x00
    unsigned int reserved_04;            // +0x04
    SchedulerCallbackNode* update_node;  // +0x08
    SchedulerCallbackNode* draw_node;    // +0x0C
    unsigned char reserved_10[0x20];     // +0x10
    void* animation_archive;             // +0x30
    unsigned char reserved_34[0x0C];     // +0x34
    FrameTimer timer;                    // +0x40
    void* parser;                        // +0x54
    unsigned char reserved_58[0x10];     // +0x58
};

struct MessageHostInitHooks {
    void* context;
    // The global game object (retail 0x004776F0) that carries the archive.
    const void* game_object;
    // operator new for the two allocation sites.
    void* (*allocate)(void* context, unsigned int bytes);
    // Vtable installed at the head of the parser (retail 0x0046D0B4) and the
    // constructor reached through its third slot.
    const void* parser_vtable;
    void (*parser_construct)(void* parser, int argument);
    // Retail 0x00449AE0 and 0x00449B70; the third argument is the shared
    // callback list at 0x00491BE4.
    void (*register_primary)(int priority, SchedulerCallbackNode* node,
                             void* list);
    void (*register_secondary)(int priority, SchedulerCallbackNode* node,
                               void* list);
    void* callback_list;
    // Retail 0x0040D810 and 0x0040D820, still unrecovered leaves.
    void* update_callback;
    void* draw_callback;
};

// Returns 0, matching retail.
int MessageHost_Init(MessageHost* host, int parser_argument,
                     const MessageHostInitHooks* hooks);

#endif // TH10_GAME_MESSAGE_HOST_INIT_HPP
