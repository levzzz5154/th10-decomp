#pragma once

struct MessageManagerState {
    void* update_task;
    void* draw_task;
    void* resource;
    void* parser;
    int message_index;
    unsigned int first_seen_flags;
};

struct MessageManagerInitEnv {
    void* context;
    int character;
    int stage;
    int power;
    int difficulty;
    unsigned char* seen_messages; // at least 13 entries
    unsigned char* seen_special;
    const char* const* resource_names;
    void* (*create_task)(void* context, int callback_kind, int priority,
                         void* owner);
    void** indicator_handle;
    void* (*create_indicator)(void* context, float x, float y,
                              int script_id);
    void* (*load_resource)(void* context, const char* path);
    void* (*create_parser)(void* context, void* resource);
    void (*report_missing)(void* context);
};

// 0x0040B560 - register the message tasks, choose the stage/character script,
// update first-seen flags, load its resource, and construct the parser.
int MessageManager_Initialize(MessageManagerState* state,
                              const MessageManagerInitEnv* env);
