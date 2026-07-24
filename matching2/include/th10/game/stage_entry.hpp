#pragma once

// Stage entry orchestrator and its task callbacks (retail 0x00417870, 0x004187C0, 0x004187D0).
//
// Retail functions:
//   0x00417870 (__stdcall, 1040 bytes) - stage entry. Called with the stage
//     context; waits for the render/loader sync pair (dword_491C10) to go
//     negative, seeds the score/lives/power block (dword_474C40..dword_474CAC)
//     from the score file (dword_47783C) on a fresh run (dword_491FC4),
//     registers the stage update task (callback 0x004187C0, priority 10 via
//     0x00449AE0) and draw task (callback 0x004187D0, priority 4 via
//     0x00449B70), copies the 52-byte stage descriptor (dword_491D48), and
//     runs the stage construction chain. A replay run (dword_474CA0 bit 1)
//     takes the short path 0x0042A6A0 / 0x00413A20 / 0x00402640; a normal run
//     calls the nine initializers 0x00429610, 0x00402640, 0x00414830,
//     0x00425020, 0x00406060, 0x0041AED0, 0x0041C290, 0x00422360, 0x00419090
//     and then 0x0042B660. Afterwards it resets the spell-practice path
//     (0x00417800) when dword_474CA0 & 9, else constructs the enemy manager
//     (0x0040D6B0), then 0x0040AF90 / 0x004056B0 / 0x00408C90, optionally
//     loads the two stage music tracks (0x00420C00, 0x00420A90 x2 unless
//     dword_474CA0 bit 5), zeroes the camera-shake doubles (dword_477708
//     +36/+44), arms the player spawn node (0x00405410), waits out the
//     loader word dword_494518, releases pending ANM handles (0x00421070
//     with &dword_491C28), and requests callback removal (0x00409E20).
//     Any failure jumps to the shared exit: set context flag bit 3, release
//     the overlay handles (0x00421300 with &dword_491C28), publish the
//     result words dword_492264=0 / dword_492260=1, mark both task nodes
//     with kill bit 1, and return -1. Note the entry bit (context flag
//     bit 2) is only cleared on success.
//     Hex-Rays' "possibly undefined" v1/v17 at the 0x00421300/0x00421070
//     call sites are phantom ecx values; the assembly pushes
//     `offset dword_491C28` as the single stack argument for both calls.
//   0x004187C0 (16 bytes) - update-task adapter: `push ecx; call sub_418190;
//     retn`. Forwards the task context to the stage tick 0x00418190 (still
//     unrecovered), so the tick stays an injected function pointer.
//   0x004187D0 (__thiscall) - draw-task callback: while the stage-entry bit
//     (context flag bit 2) is clear, zeroes camera-interpolator words 19,
//     20, 21, 22 of the dword_491C10 block; always returns 1.
//
// Every global block and helper is injected through StageEntryEnv so
// host-side tests can drive each branch deterministically. Env members that
// have no recovered semantic name yet are named by retail address.


// Scheduler task node slice (retail 0x24-byte node from 0x00449ED0).
// Retail dword indices: flags = node[1], context = node[8].
struct StageTaskNode {
	int head;              // node[0]
	unsigned int flags;    // node[1]: bit 1 cleared on arm, set to kill
	int reserved[6];       // node[2..7]
	void* context;         // node[8]
};

// Stage context slice (the 0x00417870 argument). Retail byte offsets given.
struct StageContext {
	int field_0;                   // +0 (untouched here)
	int stage_number;              // +4, copied from the stage record
	StageTaskNode* update_task;  // +8
	StageTaskNode* draw_task;    // +12
	float spawn[5];                // +16, armed via 0x00405410
	unsigned char descriptor[52];  // +36, copied from dword_491D48
	unsigned int flags;            // +88: bit 2 entering, bit 3 failed
	void* replay_handle;           // +92
};

// Stage record row (dword_477848). Retail byte offsets given.
struct StageRecord {
	int number;               // +0, published to context->stage_number
	const char* script_name;  // +4, 0x00402640 argument
	int reserved_8;           // +8
	void* enemy_script;       // +12, 0x0040D6B0 argument
	const char* music_name;   // +16, 0x00420A90 slot 0
	const char* music_loop;   // +20, 0x00420A90 slot 1
};

// Global words touched by 0x00417870, named by retail address.
struct StageGlobals {
	float frame_scale;        // flt_476F78, reset to 1.0
	int counter_474c88;       // dword_474C88, zeroed
	int counter_474c8c;       // dword_474C8C, zeroed
	int fresh_run;            // dword_491FC4, nonzero seeds the score block
	unsigned int ui_flags;    // dword_491FF4, bit 0x80 aborts the sync wait
	int sync[2];              // *dword_491C10 first two ints; both < 0 = ready
	int score_seed;           // dword_474C40
	int score_current;        // dword_474C44
	short bomb_fragments;     // word_474C48: 0x50, or 0 when mode == 1
	int extend_index;         // dword_474C50, set to 9
	int character;            // dword_474C68
	int stage;                // dword_474C6C
	int lives;                // dword_474C70
	int difficulty;           // dword_474C74, forced to 4 when mode == 7
	int mode;                 // dword_474C7C (7 = stage practice, 1 = no bombs)
	int pending_474c84;       // dword_474C84, consumed at the success tail
	int power_474c90;         // dword_474C90, zeroed unless game_flags bit 3
	int power_seed;           // dword_474C94, byte from the score file
	int counter_474c98;       // dword_474C98: -512 when game_flags bit 3 else 0
	int counter_474c9c;       // dword_474C9C, zeroed
	unsigned int game_flags;  // dword_474CA0
	int continues;            // dword_474CAC
	int counter_4918a4;       // dword_4918A4, zeroed on success
	int result_492264;        // dword_492264, published 0
	int result_492260;        // dword_492260, published 1
	int loader_busy;          // dword_494518, waited out with Sleep(16)
	double camera_a;          // *(double*)(dword_477708 + 36), zeroed
	double camera_b;          // *(double*)(dword_477708 + 44), zeroed
};

// Injected globals and helper edges for 0x00417870.
struct StageEntryEnv {
	StageGlobals* globals;
	// dword_47783C: score file image. Per character/stage record stride is
	// 17276 bytes at index (3*character + stage); the score dword sits at
	// record + 240*difficulty + 24, the power byte at record +
	// 240*difficulty + 29, and the play count dword at record + 1224.
	unsigned char* score_file;
	const StageRecord* stage_record;   // dword_477848
	const unsigned char* stage_descriptor;    // dword_491D48, 52 bytes
	void* scheduler;                          // dword_491BE4
	void* anm_slots;                          // &dword_491C28
	void* game;                               // dword_47770C (0x00413A20 arg)
	void* spell_practice_state;               // dword_477704 (0x00417800 arg)
	void* key_buffer;                         // byte_477710 (0x00429610 arg)
	void (*sleep)(unsigned int milliseconds); // Sleep
	// 0x00418B80: seed the extend/gauge threshold from the starting score.
	void (*seed_extend_threshold)(int* score_seed, int amount);
	// 0x00449ED0: allocate a task node; 0 = update (0x004187C0),
	// 1 = draw (0x004187D0).
	StageTaskNode* (*create_task)(int callback_index);
	void (*register_update)(int priority, StageTaskNode* node,
	                        void* scheduler); // 0x00449AE0, priority 10
	void (*register_draw)(int priority, StageTaskNode* node,
	                      void* scheduler);   // 0x00449B70, priority 4
	void (*replay_reset)();                   // 0x0042A6A0 (replay block)
	void (*replay_seed)(void* game);          // 0x00413A20, result ignored
	int (*load_stage_script)(const char* name, int flag); // 0x00402640
	int (*init_side_panel)(void* replay_handle, void* key_buffer); // 0x00429610
	int (*init_414830)();                     // 0x00414830
	int (*init_425020)();                     // 0x00425020
	int (*init_406060)();                     // 0x00406060
	int (*init_41aed0)();                     // 0x0041AED0
	int (*create_score_manager)();            // 0x0041C290
	int (*init_422360)();                     // 0x00422360
	int (*init_419090)();                     // 0x00419090
	int (*create_stage_state)();              // 0x0042B660
	void (*spell_practice_reset)(void* state);// 0x00417800
	int (*create_enemy_manager)(void* enemy_script); // 0x0040D6B0
	int (*create_bullet_manager)();           // 0x0040AF90
	int (*init_4056b0)();                     // 0x004056B0
	int (*init_408c90)();                     // 0x00408C90
	void (*music_reset)();                    // 0x00420C00
	void (*music_load)(int slot, const char* name); // 0x00420A90
	void (*reset_player_spawn)(float* spawn, int value); // 0x00405410
	void (*release_overlay_anm)(void* slots); // 0x00421300 (failure exit)
	void (*release_pending_anm)(void* slots); // 0x00421070 (success tail)
	void (*request_callback_removal)(void* context); // 0x00409E20
};

// 0x00417870 - Enter a stage: sync wait, score seeding, task registration,
// construction chain, music, spawn, loader wait, and handle bookkeeping.
// Returns 0 on success and -1 on any failure or sync abort.
int StageContext_Enter(StageContext* context,
                       const StageEntryEnv* env);

// 0x004187C0 - Update-task adapter: forwards the task context to the stage
// tick (retail 0x00418190, injected here) and returns its result.
int StageTask_UpdateThunk(void* context, int (*stage_update)(void* context));

// 0x004187D0 - Draw-task callback: while the stage-entry bit (context flag
// bit 2) is clear, zero camera-interpolator words 19..22 of the
// dword_491C10 block. Always returns 1.
int StageTask_ClearCameraOnIdle(const StageContext* context,
                                int* camera_words);
