#pragma once

// Enemy list lifecycle: hitbox sync, capture marking, interpolators, spawning, blast sweep, and destruction (retail batches 7-10).
#include "th10/game/boss_overlays.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/util/scalars.hpp"

// Enemy list node fields touched by the hitbox sync leaf.
struct HitboxEnemy {
    BossVec3 position;       // retail +0x3B4
    BossVec3 hitbox;         // retail +0x33C (output)
    float sprite_angle;           // retail +0x034 (output)
    float facing_angle;           // retail +0x3E4
    unsigned int flags;           // retail +0x364
    HitboxEnemy* next;            // retail +0x44C
};

int EnemyList_SyncHitboxes(HitboxEnemy* head, float offset_x, float offset_y,
                           float (*normalize_angle)(float angle,
                                                    float quarter_turn),
                           void (*mark_dirty)(void* state), void* state);

// --- 0x0040E6A0 --------------------------------------------------------------
struct CaptureEnemy {
	Word flags;    // retail +0x2480
	int drop_slot;       // retail +0x2448
	int drop_index;      // retail +0x244C
};

struct CaptureNode {
	CaptureEnemy* enemy;
	CaptureNode* next;
};

void EnemyList_MarkDeadForCapture(CaptureNode* head,
                                  void* const* handler_table,
                                  void (*notify)(void* handler),
                                  PlayerDeathClock* clock, float span_low,
                                  float span_high, float frame_step,
                                  long long (*float_to_long)(float value));

// --- 0x0040D750 --------------------------------------------------------------
struct InterpEnemy {
	Word flags;    // retail +0x2480
	void* interpolator;  // retail +0x103C
};

struct InterpNode {
	InterpEnemy* enemy;
	InterpNode* next;
};

int EnemyList_TickInterpolators(InterpNode* head,
                                int (*step_interpolator)(void* interpolator),
                                void (*retire)(InterpEnemy* enemy,
                                               int mode),
                                PlayerDeathClock* clock, float span_low,
                                float span_high, float frame_step,
                                long long (*float_to_long)(float value));

struct SpawnEntry {
	short sprite_id;
	void (*on_spawn)(void);
	float anchor_x;
	float anchor_y;
};

struct SpawnEffectVm {
	int layer;
	Word flags;
};

struct SpawnedEnemy {
	float anchor_x; // +0x398
	float anchor_y; // +0x39c
};

struct SpawnEnv {
	SpawnEffectVm* (*acquire_effect)(void);
	void (*assign_sprite)(SpawnEffectVm* vm, int sprite_id);
	void* state_manager;
	void (*refresh_layout)(void* state_manager);
	SpawnedEnemy* (*resolve_enemy)(void* state_manager, int handle);
};

void EnemySpawner_CreateFromTable(const SpawnEntry* table, int index,
                                  int handle, int* result_slot,
                                  SpawnEnv* env);

struct BlastEnemy {
	short state;       // 0 = free, 3 = dying (both skipped)
	int boss_flag;     // nonzero marks bosses
	float position[2];
	float size;
};

struct BlastEnv {
	float half_scale;
	void (*kill_enemy)(BlastEnemy* enemy);
	int (*convert_to_item)(float* position, float step_x, float step_y);
	void* effect_pool;
	void (*spawn_effect)(void* pool, int id, Word color, float angle,
	                     float scale);
};

int EnemyPool_BlastRadius(BlastEnemy* enemies, int count,
                          const float* center, float radius,
                          int spawn_effects, int skip_bosses,
                          BlastEnv* env);

struct DtorNode {
	void* owner;
	DtorNode* next;
	DtorNode* prev;
};

struct DtorManager {
	DtorNode* head;
	DtorNode* tail;
	int count;
	void** slots; // boss slot table indexed by slot_index
};

struct RefNode;

struct EnemyRef {
	int id;
	RefNode* children;
	void* parent;
	Word flags; // |= 0x4000000 when the owner dies
};

struct RefNode {
	EnemyRef* value;
	RefNode* next;
};

struct ChainAlloc {
	void* data;
	ChainAlloc* next;
};

struct EffectSlotOwner {
	void* owner;
	int reserved[22]; // retail slot stride is 0x5c bytes
};

struct EffectRegistry {
	void** focus_slot;
	Byte* focus_flag;
	EffectSlotOwner* slots;
	int slot_count; // retail: 0x80
};

struct DtorEnemy {
	const void* vtable;
	DtorNode node;
	Word slot_flags; // bit 15: registered in a boss slot
	int slot_index;
	int handles[10];
	ChainAlloc* chain;
};

struct DtorEnv {
	DtorManager* manager;
	RefNode* search_list_a;
	RefNode* search_list_b;
	EffectRegistry* effects; // may be null
	void (*free_block)(void* block);
	const void* live_vtable;
	const void* dead_vtable;
};

void Enemy_Destroy(DtorEnemy* enemy, DtorEnv* env);
