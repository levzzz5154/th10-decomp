#pragma once

// Score globals creation, score task init, and score task list tick (retail 0x0042AF20, 0x00413A20, 0x0041C330).
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

struct ScoreCreateEnv {
	void* (*allocate)(unsigned int size);
	void* (*initialize)(void* block);
	void** global_slot;
};

void ScoreData_CreateGlobal(ScoreCreateEnv* env);

struct ScoreHost {
	RegisteredClock clock;
	int saved_score;
	void* task;
	Byte* data;
	int hud_a;
	int hud_b;
};

struct ScoreInitEnv {
	void* (*create_task)(int size, void* manager, const char* name);
	void* manager;
	const char* task_name;
	Byte** preloaded_data;
	const char* score_path;
	char* path_buffer;
	Byte* (*load_file)(unsigned int* size_out, int mode);
	void (*fatal_error)(void* sink, const char* message);
	void* error_sink;
	const char* error_text;
	int current_score;
	float* frame_scale;
};

int ScoreTask_Init(ScoreHost* host, ScoreInitEnv* env);

struct ScoreTaskNode {
	// Retail dispatches through the node vtable: update at +0x08 (returns 0
	// to keep the task alive) and destroy at +0x10.
	int (*update)(ScoreTaskNode* node);
	void (*destroy)(ScoreTaskNode* node);
	ScoreTaskNode* prev;    // retail +0x04 (first node points at the sentinel)
	ScoreTaskNode* next;    // retail +0x08
	int kill_flag;            // retail +0x0C; 1 forces retirement
	FrameClock clock;  // retail +0x10..+0x1C
	Byte retire_count; // retail byte at +0x50; nonzero starts retirement
};

struct ScoreTaskList {
	// Retail keeps the head pointer at owner+0x18, which is the `next` field
	// of a sentinel located at owner+0x10; unlinking always writes through
	// node->prev without a null check.
	ScoreTaskNode head_sentinel;
	ScoreTaskNode* cursor; // retail +0x434; repaired when its node is freed
	int live_count;          // retail +0x438
	void (*free_node)(ScoreTaskNode* node); // retail _free
};

int ScoreTaskList_Tick(ScoreTaskList* list, const ClockEnv* clock_env);
