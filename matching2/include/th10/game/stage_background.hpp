#pragma once

// Stage background texture rebind and scroll sync (retail 0x0040C3C0, 0x00427960).

int StageBackground_RebindTexture(const char* source_name, char* name_buffer,
                                  int slot_index, void** slot_table,
                                  unsigned int* busy_flags,
                                  void* state_manager,
                                  void* (*mount_texture)(int bank, void* state,
                                                         const char* name),
                                  void* previous_handle,
                                  void (*release_previous)(void* handle),
                                  int* thread_pending_word);

struct ScrollAnchor {
	int x;
	int y;
};

struct ScrollStage {
	int scroll_locked;
	int camera_x;
	int camera_y;
	ScrollAnchor* anchors;
	int (*random_pairs)[2]; // indexed by anchor slot * 8 + k
};

struct ScrollItem {
	int x;
	int y;
	int rel_x;
	int rel_y;
	int last_mode;
	int index;
};

struct ScrollEnv {
	ScrollStage* stage;
	int (*random_int)(void);
};

void StageBackground_SyncScroll(ScrollItem* item, ScrollEnv* env);
