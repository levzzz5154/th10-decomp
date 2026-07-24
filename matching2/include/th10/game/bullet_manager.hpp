#pragma once

// Bullet manager lifecycle: registration, pool reset, creation, sprite activation, shot-type selection, relink, ring reset, and draw (retail batches 7-10).
#include "th10/game/manager_factories.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

int BulletManager_OnRegister(ManagerRegistration* manager,
                             void** animation_slot,
                             void* (*mount_animation)(int bank, void* state,
                                                      const char* name),
                             void* state_manager,
                             void (*report_error)(const char* message,
                                                  const char* argument),
                             const char* error_message,
                             const char* error_argument, void** cursor_out,
                             void* pool_base, unsigned short* state_word,
                             void* update_callback, void* draw_callback,
                             SchedulerCallbackNode* (*create)(void* callback),
                             void (*enqueue_update)(void* queue),
                             void (*enqueue_draw)(void* queue), void* queue);

void BulletManager_ResetPool(void (*rebind_animation)(void* handle,
                                                      void* animation),
                             void* handle, void* animation,
                             Word* pool_words,
                             unsigned int pool_word_count, void** cursor_out,
                             void* pool_base, unsigned short* state_word);

// --- 0x00404450 --------------------------------------------------------------
struct BulletSchedulerNode {
	Word flags;
};

struct BulletSpriteRecord {
	short id;      // negative id terminates a bank
	short stride;  // byte stride to the next record
	short reserved;
	short assigned;
};

struct BulletSpriteBank {
	Byte tag[3];
	Byte active;              // retail bank byte +3
	Byte reserved[0x18];
	BulletSpriteRecord records[1];  // records begin at +0x1C
};

struct BulletHost {
	short* bank_count;             // retail *(+0x10)
	BulletSpriteBank** banks;      // retail +0x14
	BulletSchedulerNode* update;   // retail +0x08
	BulletSchedulerNode* draw;     // retail +0x0C
	BulletSchedulerNode* overlay;  // retail +0x2A40
	void* sprite_pool;             // retail +0x178
	void* cursor;                  // retail +0x4C
	void* pool_base;               // retail +0x1C
};

void BulletManager_ActivateSprites(BulletHost* host,
                                   void (*register_sprite)(void* pool));

// --- 0x00406060 --------------------------------------------------------------
void* BulletManager_Create(void* (*allocate)(unsigned int size),
                           void (*construct_slots)(void* slots, int stride,
                                                   int count),
                           void** global_slot, int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory));

// --- 0x00404F30 --------------------------------------------------------------
struct BulletSlot {
	Word motion[9];  // retail +0x334..+0x354
	Byte scale_a;    // retail +0x3A0
	Byte scale_b;    // retail +0x3A1
	short id;              // retail +0x38A
};

void BulletSlot_Construct(BulletSlot* slot, short id, void* base,
                          void (*base_init)(void* base, void* slot),
                          void* timer, void (*init_timer)(void* timer));

// --- 0x00405300 --------------------------------------------------------------
void BulletManager_SelectShotType(void** active_slot, char* shot_table,
                                  int stride, int index,
                                  void (*refresh)(void), void* device,
                                  void (*upload_palette)(void* device,
                                                         void* palette),
                                  int palette_offset, int* current_index);

struct LinkBullet {
	short state;                   // +0x4a6, 0 = free slot
	FrameClock clock;        // +0x458
	float age;                     // +0x4ac, cleared on relink
	float layer;                   // +0x4c0, list index stored as float
	struct LinkBullet* next; // +0x44c
};

struct BulletLinkManager {
	int active_count;           // +0x5c
	LinkBullet* heads[6]; // +0x14
	LinkBullet* tails[6]; // +0x2c
};

struct BulletLinkEnv {
	// Player status flag word; bullet updates are skipped while the player
	// is in the (2 | 0x400) capture state.
	const Word* player_flags;
	int (*update_bullet)(LinkBullet* bullet); // nonzero = drop from lists
	ClockEnv clock_env;
};

int BulletManager_RelinkActive(BulletLinkManager* manager,
                               LinkBullet* bullets, int count,
                               BulletLinkEnv* env);

struct BulletDrawHost {
	Word flags;              // +0x2a18
	int freeze_timer;              // +0x2a20
	float recoil[5];               // +0x2b34, zeroed every frame
	float aim_source[3];           // +0x2a58
	float aim_normalized[3];       // +0x2a70
	Word ambient_color;      // +0x1ee8
	int overlay_pending;           // +0x1eec
	void* layer_batches[8];        // +0x180, stride 0x3ac
	void* overlay_batches[3];      // +0x1f08 / +0x22b4 / +0x2660
	Word camera_block[0x46]; // +0x2a4c
	int draw_counter;              // +0x2a34
};

struct BulletDrawEnv {
	void (*normalize)(float* out3, const float* in3);
	void (*prepare_common_state)(void);
	void (*refresh_layout)(BulletDrawHost* host);
	void (*draw_batch)(void* batch);
	float* global_scale;           // overlay batches draw at scale 1.0
	Word* camera_snapshot;   // global copy of the camera block
};

int BulletManager_OnDraw(BulletDrawHost* host, BulletDrawEnv* env);

struct BulletRingNode {
	BulletRingNode* next;
	BulletRingNode* prev;
};

struct BulletRing {
	BulletRingNode* head;
	BulletRingNode node;
	int sentinel;       // -1
	void* self;
	int control_flags; // retail +0x1020; bit 0 set/cleared by ECL opcodes
	                   // 0x12/0x13 in the instruction dispatcher (0x0044E1A0)
	Word flags;  // bit 0 cleared
	BulletRingNode* cursor;
	int count_a;
	int count_b;
};

void BulletRing_Reset(BulletRing* ring);
