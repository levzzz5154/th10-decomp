#include "th10/game/manager_factories.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// Shared construct-then-initialize factory frame used by the manager
// creation helpers: allocate, run the in-place constructor, then run the
// global initializer; a failing initializer tears the object back down.
static void* CreateConstructedManager(unsigned int size,
                                      void* (*allocate)(unsigned int),
                                      void* (*construct)(void*),
                                      int (*initialize)(void),
                                      void (*destroy)(void*),
                                      void (*free_memory)(void*)) {
	void* manager = allocate(size);
	if (manager != 0) manager = construct(manager);
	if (initialize() != 0) {
		if (manager != 0) {
			destroy(manager);
			free_memory(manager);
		}
		return 0;
	}
	return manager;
}

// 0x0040D6B0 - Construct the enemy manager. Retail allocates the 0x68-byte
// block, zeroes all 0x1A dwords, sets header flag bit 1, publishes the
// instance through the manager global (retail DAT_00477704), then runs the
// script initializer; on failure the half-built manager is destroyed and
// freed and the constructor reports null.
void* EnemyManager_Create(void* script_name, void* (*allocate)(unsigned int size),
                          void** global_slot,
                          int (*initialize)(void* script_name),
                          void (*destroy)(void* manager),
                          void (*free_memory)(void* memory)) {
    Word* manager = (Word*)allocate(0x68);
    if (manager != 0) {
        for (int index = 0; index < 0x1A; ++index) manager[index] = 0;
        manager[0] = manager[0] | 2;
        *global_slot = manager;
    }
    if (initialize(script_name) != 0) {
        if (manager != 0) {
            if (destroy != 0) destroy(manager);
            free_memory(manager);
        }
        return 0;
    }
    return manager;
}

// 0x0043C8B0 - Construct the 0x44-byte overlay text manager. Retail zeroes
// all 0x11 dwords, sets header flag bit 1, and forwards the five creation
// arguments to the initializer (retail 0x0043C970) before returning the
// instance; allocation failure reports null.
void* AsciiManager_Create(void* (*allocate)(unsigned int size),
                          void (*initialize)(void* manager)) {
    Word* manager = (Word*)allocate(0x44);
    if (manager == 0) return 0;
    for (int index = 0; index < 0x11; ++index) manager[index] = 0;
    manager[0] = manager[0] | 2;
    if (initialize != 0) initialize(manager);
    return manager;
}

// 0x004296F0 - Construct the 0x2D4-byte stage manager under an SEH frame.
// Retail vector-constructs the eight 0x24-byte interpolator slots at +0xA0,
// zeroes the whole 0xB5-dword block, arms the state word (+0x10) with 2, and
// runs the stage-script initializer; on failure the manager is destroyed and
// freed and the constructor reports null.
void* StageManager_Create(const char* stage_path,
                          void* (*allocate)(unsigned int size),
                          void (*construct_slots)(void* slots, int stride,
                                                  int count),
                          int (*initialize)(void* manager,
                                            const char* stage_path),
                          void (*destroy)(void* manager),
                          void (*free_memory)(void* memory)) {
    Word* manager = (Word*)allocate(0x2D4);
    if (manager != 0) {
        if (construct_slots != 0) construct_slots(manager + 0x28, 0x24, 8);
        for (int index = 0; index < 0xB5; ++index) manager[index] = 0;
    }
    if (manager == 0) return 0;
    manager[4] = 2;
    if (initialize(manager, stage_path) == 0) return manager;
    if (destroy != 0) destroy(manager);
    free_memory(manager);
    return 0;
}

// 0x0042AE60 - Initialize the effect manager pools. Retail zeroes the whole
// 0x772D-dword block, loads the shared effect table into the first slot,
// initializes the trailing shared block (+0x1D86C), constructs the seven
// 0x437C-byte effect pools that start at +0x08, and finishes with the
// pool-registration helper (retail 0x0042B030).
void EffectManager_InitializePools(Word* manager_words,
                                   unsigned int word_count,
                                   const Byte* (*load_effect_table)(
                                       unsigned int* size_out),
                                   const Byte** table_slot,
                                   void (*initialize_shared)(void* shared_block),
                                   void* shared_block,
                                   void (*initialize_pool)(void* pool),
                                   Byte* first_pool,
                                   unsigned int pool_stride,
                                   unsigned int pool_count,
                                   void (*finalize)(void)) {
    for (unsigned int index = 0; index < word_count; ++index) {
        manager_words[index] = 0;
    }
    unsigned int table_size = 0;
    *table_slot = load_effect_table(&table_size);
    if (initialize_shared != 0) initialize_shared(shared_block);
    Byte* pool = first_pool;
    for (unsigned int index = 0; index < pool_count; ++index) {
        initialize_pool(pool);
        pool = pool + pool_stride;
    }
    if (finalize != 0) finalize();
}

// --- Scheduler registration leaves ----------------------------------------------

// Shared body of the registration leaves: create a scheduler node for the
// callback, bind the owner, clear node-flag bit 1 (the auto-release bit),
// and push the node onto the requested queue.
SchedulerCallbackNode* Scheduler_RegisterOwnedCallback(
    void* owner, void* callback,
    SchedulerCallbackNode* (*create)(void* callback),
    void (*enqueue)(void* queue), void* queue) {
    SchedulerCallbackNode* node = create(callback);
    node->owner = owner;
    node->flags = node->flags & 0xFFFFFFFDu;
    if (enqueue != 0) enqueue(queue);
    return node;
}

// 0x0042B4D0 - Effect manager registration hook. Retail stamps the manager
// with the game thread's frame counter (+0x8994), registers the update and
// draw callbacks (both with the auto-release bit cleared) on the shared
// scheduler queue, resets the manager's timer block (+0x18, retail
// 0x00401DE0), stores the stamp copy at +0x320, and preloads the effect
// bank for it (retail 0x0043E5A0 with argument 0xC4).
int EffectManager_OnRegister(ManagerRegistration* manager, int frame_stamp,
                             void* update_callback, void* draw_callback,
                             SchedulerCallbackNode* (*create)(void* callback),
                             void (*enqueue_update)(void* queue),
                             void (*enqueue_draw)(void* queue), void* queue,
                             void (*reset_timer)(void* timer_block),
                             void* timer_block,
                             void (*preload)(int frame_stamp, int argument)) {
    manager->frame_stamp = frame_stamp;
    manager->update = Scheduler_RegisterOwnedCallback(
        manager, update_callback, create, enqueue_update, queue);
    manager->draw = Scheduler_RegisterOwnedCallback(
        manager, draw_callback, create, enqueue_draw, queue);
    int stamp = manager->frame_stamp;
    if (reset_timer != 0) reset_timer(timer_block);
    manager->stored_stamp = stamp;
    if (preload != 0) preload(stamp, 0xC4);
    return 0;
}

// 0x00408C90 - Player manager factory: 0x37B0-byte object, in-place
// constructor, then the resource initializer; failure destroys and frees.
void* PlayerManager_Create(void* (*allocate)(unsigned int size),
                           void* (*construct)(void* memory),
                           int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory)) {
	return CreateConstructedManager(0x37B0, allocate, construct, initialize,
	                                destroy, free_memory);
}

// 0x00414830 - Item manager factory: identical frame with a 0x9ED0-byte
// object and the item-side constructor/initializer pair.
void* ItemManager_Create(void* (*allocate)(unsigned int size),
                         void* (*construct)(void* memory),
                         int (*initialize)(void),
                         void (*destroy)(void* manager),
                         void (*free_memory)(void* memory)) {
	return CreateConstructedManager(0x9ED0, allocate, construct, initialize,
	                                destroy, free_memory);
}

// 0x00429610 - Stage manager factory taking the stage script path: allocate
// the 0x2D4-byte object, vector-construct its eight 0x24-byte interpolator
// slots at +0xA0, zero the whole object, then run the script initializer;
// failure destroys and frees the half-built manager.
void* StageManager_CreateFromScript(
    const char* script_path, void* (*allocate)(unsigned int size),
    void (*construct_slots)(void* slots, int stride, int count),
    int (*initialize)(const char* script_path), void (*destroy)(void* manager),
    void (*free_memory)(void* memory)) {
	Word* manager = (Word*)allocate(0x2D4);
	if (manager != 0) {
		construct_slots(manager + 0x28, 0x24, 8);
		for (int index = 0; index < 0xB5; ++index) manager[index] = 0;
	}
	if (initialize(script_path) != 0) {
		if (manager != 0) {
			destroy(manager);
			free_memory(manager);
		}
		return 0;
	}
	return manager;
}

// 0x0041AED0 - Effect manager factory: allocate the 0x21CEC0-byte pool,
// vector-construct the 0x896 effect slots (0x3F0 bytes each) at +0x14, zero
// the object, set the alive bit (|= 2), publish the global pointer, then
// run the initializer; failure destroys and frees the pool.
void* EffectManager_Create(void* (*allocate)(unsigned int size),
                           void (*construct_slots)(void* slots, int stride,
                                                   int count),
                           void** global_slot, int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory)) {
	Word* manager = (Word*)allocate(0x21CEC0);
	if (manager != 0) {
		construct_slots(manager + 5, 0x3F0, 0x896);
		for (int index = 0; index < 0x873B0; ++index) manager[index] = 0;
		manager[0] |= 2u;
		*global_slot = manager;
	}
	if (initialize() != 0) {
		if (manager != 0) {
			destroy(manager);
			free_memory(manager);
		}
		return 0;
	}
	return manager;
}
