#pragma once

// Line-laser per-frame update and cancel sweep (retail 0x0041D3D0, 0x0041F400).
// 0x0041D3D0 and its resolved virtual dispatch table.
//
// Evidence chain that resolved the previous roadblock:
// - 0x0041D3D0 is slot +0x08 of the 19-slot vtable off_46DA60 (.rdata),
//   directly between the off_46DA10 and off_46DAB0 sibling vtables and the
//   `.\src\game\laser.cpp:227 LaserLineInf` / `laser.cpp:236
//   LaserInfiniteInf` allocation-site strings.
// - The constructor 0x0041C5B0 installs off_46DA60 (already recovered as
//   ScoreExtendedObject_Initialize in src/game/score.cpp; the laser.cpp
//   allocation strings show the family is the laser pool).
// - The factory 0x0041C510 proves the dynamic type: selector 0 news 0xD58
//   bytes and calls 0x0041C5B0 (off_46DA60, this class); selector 1 news
//   0xD74 bytes and calls 0x0041C680 (off_46DA10, the infinite-laser
//   variant). 0x0041CFD0 (bounce) spawns reflected copies through the same
//   factory with selector 0.
// - Every "unresolved" virtual slot therefore has a concrete binding:
//     vtbl+0x00 -> 0x0041CA80 (embedded command-stream processor)
//     vtbl+0x18 -> 0x0041D880 (player interaction callback)
//     vtbl+0x24 -> nullsub          (flag 0x00000001)
//     vtbl+0x28 -> 0x0041D2C0      (flag 0x00000010, accel step,
//                                    recovered as Effect_AccelStep)
//     vtbl+0x2C -> nullsub          (flag 0x00000020)
//     vtbl+0x30 -> 0x0041D170      (flag 0x00000040, timed turn step)
//     vtbl+0x34 -> nullsub          (flag 0x00000100)
//     vtbl+0x38 -> nullsub          (flag 0x00000080)
//     vtbl+0x3C -> 0x0041CFD0      (flags 0x0800_0C00, boundary bounce,
//                                    recovered as Projectile_BounceAtBounds)
//     vtbl+0x40 -> nullsub          (flag 0x00100000)
//     vtbl+0x44 -> nullsub          (flag 0x00200000)
//     vtbl+0x48 -> nullsub          (flag 0x04000000)

// ---------------------------------------------------------------------------
// 0x0041D3D0 - line-laser update (object size 0xD58, vtable off_46DA60)
// ---------------------------------------------------------------------------

struct LaserVec3 {
	float x, y, z;
};

// Same 0x14-byte frame-timer shape as earlier batches; the advance hook is
// retail 0x0044BF40 (FrameTimer_Advance).
struct LaserTimer {
	int previous;       // +0x00
	int current;        // +0x04
	float elapsed;      // +0x08
	const float* speed; // +0x0C (&DAT_00476F78 in the exe)
	unsigned int flags; // +0x10 (bit0 = initialized)
};

// Logical view of the fields 0x0041D3D0 touches on the 0xD58-byte object.
// Offsets are noted from the retail object base.
struct LineLaser {
	int retired;              // +0x0C (set once a cancel sweep consumes the beam)
	LaserTimer age;         // +0x10 (current = age in frames; graze gate)
	LaserVec3 position;     // +0x24 (tail/origin point)
	LaserVec3 velocity;     // +0x30
	float angle;              // +0x3C
	float length;             // +0x40 (current beam length)
	float width;              // +0x44
	float grow_speed;         // +0x48 (units per frame)
	float traveled;           // +0x4C (distance consumed by the tail)
	LaserTimer flash_timer; // +0x15C (flag 0x8000 countdown)
	unsigned int flags;       // +0x404 (dispatch bits, tested live)
	LaserTimer hold_timer;  // +0x410 (off-screen cull grace countdown)
	float length_limit;       // +0x434 (growth target)
	float total_length;       // +0x43C (total emitted length; 0 = endless)
	short colour;             // +0x466 (sparkle script selector, 17 + 2*colour)
};

// Sprite/format record referenced by the body VM at vm+0x394; the update
// reads the two floats at +0x30/+0x34.
struct LineLaserSprite {
	float width;  // sprite +0x30
	float height; // sprite +0x34
};

// The slice of the embedded animation VMs (laser+0x600 body, laser+0x9AC
// head) that this update touches.
struct LineLaserVm {
	float growth_x;                   // vm+0x3C = width / sprite height
	float growth_y;                   // vm+0x40 = length / sprite width
	unsigned int flags;               // vm+0x35C (|= 0x8, growth dirty)
	const LineLaserSprite* sprite; // vm+0x394
};

typedef void (*LineLaserSlot)(LineLaser* laser);

struct LineLaserEnv {
	// Resolved off_46DA60 virtual slots in retail dispatch order.
	LineLaserSlot run_commands;     // vtbl+0x00 -> 0x0041CA80
	LineLaserSlot on_flag_0001;     // vtbl+0x24 -> nullsub_29
	LineLaserSlot on_flag_0010;     // vtbl+0x28 -> 0x0041D2C0
	LineLaserSlot on_flag_0020;     // vtbl+0x2C -> nullsub_31
	LineLaserSlot on_flag_0040;     // vtbl+0x30 -> 0x0041D170
	LineLaserSlot on_flag_0100;     // vtbl+0x34 -> nullsub_33
	LineLaserSlot on_flag_0080;     // vtbl+0x38 -> nullsub_34
	LineLaserSlot on_flag_bounce;   // vtbl+0x3C -> 0x0041CFD0
	                                   // (mask 0x0800_0C00)
	LineLaserSlot on_flag_100000;   // vtbl+0x40 -> nullsub_36
	LineLaserSlot on_flag_200000;   // vtbl+0x44 -> nullsub_37
	LineLaserSlot on_flag_4000000;  // vtbl+0x48 -> nullsub_38
	// vtbl+0x18 -> 0x0041D880: player interaction callback invoked on a
	// direct hit with (player_state, {32, 32, 0}, 0).
	void (*hit_player)(LineLaser* laser, void* player_state,
	                   const float* box, int flag);

	// Non-virtual helpers.
	void (*advance_timer)(LaserTimer* timer, float delta); // 0x0044BF40
	// 0x0041F800: writes destination[0]/[1]; z handling is the caller's.
	void (*set_polar)(float* destination, float angle, float length);
	// 0x0041F7A0: 1 when the point +/- the radii is entirely off-screen.
	int (*outside_viewport)(const float* point, float radius_x,
	                        float radius_y);
	// 0x004267F0: rotate the probe into laser space and classify against
	// the player; 1 = direct hit, 2 = graze band.
	int (*classify_player)(const float* probe, void* player, float angle,
	                       float half_width, float reach);
	// 0x00448DB0 on the player state with the sample handle at
	// DAT_004776F0+0x3E0B50; receives the collision half-width slot.
	void (*register_graze)(void* player_state, float* half_width);
	void (*play_graze_sound)(int id, float x); // 0x0043DD10 (id 28)
	void (*tick_vm)(LineLaserVm* vm);       // 0x0043EE30

	void* player;       // DAT_00477834
	void* player_state; // DAT_00477834 + 0x3C0
	LineLaserVm* body_vm; // laser+0x600
	LineLaserVm* head_vm; // laser+0x9AC
	float frame_speed;  // *DAT_00476F78
};

// Returns 1 when the laser should be retired (fully consumed or entirely
// off-screen), 0 otherwise.
int LaserLine_Update(LineLaser* laser, LineLaserEnv* env);

// ---------------------------------------------------------------------------
// 0x0041F400 - laser cancel sweep (vtable off_46DA60 slot +0x14)
// ---------------------------------------------------------------------------
// Walks the beam from 6 units past the tail in 12-unit steps. Each on-screen
// step allocates a sparkle VM from the world animation manager (0x00449950),
// marks it with flag 0x40000000, zeroes its +0x20 word, places it at the
// screen-space point (x+224, y+16, z), loads sparkle script 17 + 2*colour
// from the laser-manager ANM file at DAT_0047781C+0x458 (0x0043E710), and
// registers it (0x004489D0). When item spawning is requested and the point
// passes the wider 32-unit bound, it also drops item kind 8 (id -1, angle
// -pi/2, speed 0.6) through 0x0041BB00 on the item manager DAT_00477818.
// Finally marks the laser retired (+0x0C = 1). Returns the step count.

// The slice of the sparkle animation VM this sweep touches.
struct LaserSweepVm {
	unsigned int flags; // vm+0x35C (|= 0x40000000)
	int pending_word;   // vm+0x20 (cleared)
	float position[3];  // vm+0x340/0x344/0x348 (screen space)
};

struct LaserSweepEnv {
	void (*set_polar)(float* destination, float angle, float length); // 0x0041F800
	LaserSweepVm* (*allocate_vm)(void* anm_manager);                 // 0x00449950
	void (*load_script)(LaserSweepVm* vm, void* anm_file,
	                    int script_id);                                // 0x0043E710
	void (*register_vm)(LaserSweepVm* vm, void* anm_manager);        // 0x004489D0
	// 0x0041BB00: point is the (x, y) world position of the step.
	void (*spawn_item)(void* item_manager, const float* point, int kind,
	                   int id, float angle, float speed);
	void* anm_manager;  // DAT_00491C10
	void* anm_file;     // *(DAT_0047781C + 0x458)
	void* item_manager; // DAT_00477818
};

// Returns the number of 12-unit steps walked (0 for beams of 12 units or
// shorter; retail leaves the register garbage on that early exit).
int LaserLine_SweepIntoItems(LineLaser* laser, int spawn_items,
                             LaserSweepEnv* env);
