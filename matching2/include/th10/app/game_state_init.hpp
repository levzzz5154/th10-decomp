// =============================================================================
// game_state_init.hpp - Game-state arena construction (retail 0x00445900)
// =============================================================================
#ifndef TH10_APP_GAME_STATE_INIT_HPP
#define TH10_APP_GAME_STATE_INIT_HPP

// Layout constants recovered from the retail constructor.
enum GameStateArenaLayout {
    GAME_STATE_ENTITY_STRIDE_BYTES = 0x3AC,
    GAME_STATE_ENTITY_COUNT = 0x1000,
    GAME_STATE_ENTITY_TABLE_OFFSET = 0x68,        // param + 0x1A dwords
    GAME_STATE_SECOND_TABLE_OFFSET = 0x72DAE4,    // param + 0x1CB6B9 dwords
    GAME_STATE_SECOND_TABLE_COUNT = 0x14,
    GAME_STATE_CLEAR_BASE_OFFSET = 0x3AD130,      // param + 0xEB44C dwords
    GAME_STATE_CLEAR_DWORDS = 0xEB,
    GAME_STATE_TAIL_CLEAR_OFFSET = 0x732460 - 0x14A0, // trailing dword block
};

// Scheduler callbacks registered by the constructor, in retail order.
struct GameStateCallbackPlan {
    int primary_count;    // registered through 0x00449AE0 (2 in retail)
    int secondary_count;  // registered through 0x00449B70 (18 in retail)
};

struct GameStateMatrixGlobals {
    // Absolute retail range 0x0049786C..0x0049792C.
    float values[49];
};

struct GameStateInitHooks {
    void* context;
    // _eh_vector_constructor_iterator_ replacement: construct `count`
    // elements of `stride` bytes starting at `base` (ctor 0x00402050).
    void (*construct_entities)(void* context, void* base, int stride,
                               int count);
    // Per-entity registration pass (retail 0x00401DE0 per index).
    void (*bind_entity)(void* context, int index, void* entity);
    // Scheduler node creation + insertion (retail new(0x24) + 0x00449AE0 /
    // 0x00449B70). `callback_index` follows retail registration order.
    int (*register_primary)(void* context, int callback_index);
    int (*register_secondary)(void* context, int callback_index);
    // IDirect3DDevice9::SetSoftwareVertexProcessing(dev, 0) (vtable +0x170).
    void (*device_disable_software_vp)(void* context);
};

void* GameStateInit_Construct(void* arena, unsigned int arena_bytes,
                              const GameStateInitHooks* hooks,
                              const GameStateCallbackPlan* plan,
                              GameStateMatrixGlobals* matrices = 0);

#endif // TH10_APP_GAME_STATE_INIT_HPP
