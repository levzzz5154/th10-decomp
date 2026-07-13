// =============================================================================
// ecl.hpp - ECL (Enemy Control Language) VM types and opcodes
// =============================================================================
#pragma once
#include "th10/entity.hpp"
// ============================================================================
// ECL Opcodes (0x100-0x1B4)
// Extracted from FUN_0040E770 switch dispatch
// ============================================================================
enum ECLOpcode {
    ECL_NOP             = 0x100,  // no operation / fallback
    ECL_SET_SLOT        = 0x101,  // set entity slot
    ECL_LOAD_ANIM       = 0x102,  // load animation by ID
    ECL_SET_ANIM_VAR    = 0x103,  // set animation variable
    ECL_SET_POS         = 0x104,  // set position (x, y, z)
    ECL_SET_POS_REL     = 0x105,  // set relative position
    ECL_SET_ANIM_SLOT   = 0x106,  // set animation slot with lookup
    ECL_LOAD_TEXTURE    = 0x107,  // load texture
    ECL_LOAD_TEXTURE2   = 0x108,  // load texture (variant)
    ECL_SET_FLAG        = 0x109,  // set flag if config allows
    ECL_SET_SPEED       = 0x10A,  // set movement speed
    ECL_SET_ACCEL       = 0x10B,  // set acceleration
    ECL_SET_ANGLE       = 0x10C,  // set movement angle
    ECL_SET_ANGLE_RATE  = 0x10D,  // set angular velocity
    ECL_SET_POS_SPEED   = 0x10E,  // set position-based speed
    ECL_SET_POS_ACCEL   = 0x10F,  // set position-based accel
    ECL_SET_TARGET      = 0x110,  // set target position
    ECL_SET_TARGET_SPEED= 0x111,  // set target seek speed

    ECL_SET_HITBOX      = 0x118,  // set collision hitbox
    ECL_SET_EXTRA       = 0x119,  // set extra property
    ECL_SET_LIFETIME    = 0x11A,  // set lifetime/duration
    ECL_SET_DAMAGE      = 0x11B,  // set damage value
    ECL_SET_HEALTH      = 0x11C,  // set health/HP
    ECL_SET_SCORE       = 0x11E,  // set score value
    ECL_SET_ITEM        = 0x11D,  // set item drop
    ECL_SET_INVULN      = 0x11F,  // set invincibility frames
    ECL_SET_BLEND       = 0x120,  // set blend mode
    ECL_SET_COLOR       = 0x122,  // set color (RGBA)
    ECL_SET_COLOR_RGB   = 0x121,  // set color (RGB only)
    ECL_SET_ALPHA       = 0x123,  // set alpha
    ECL_SET_SCALE       = 0x124,  // set scale
    ECL_SET_SCALE_XY    = 0x125,  // set scale X/Y
    ECL_SET_ROTATION    = 0x126,  // set rotation
    ECL_SET_SORT        = 0x127,  // set sort order
    ECL_SET_Z           = 0x128,  // set Z-order
    ECL_SET_UV          = 0x129,  // set UV coordinates
    ECL_SET_UV_SCROLL   = 0x12A,  // set UV scroll rate

    ECL_FIRE_BULLET     = 0x140,  // fire bullet pattern
    ECL_FIRE_BULLET_AIM = 0x141,  // fire bullet aimed at player
    ECL_FIRE_BULLET_SPD = 0x142,  // fire bullet with speed
    ECL_FIRE_LASER      = 0x143,  // fire laser
    ECL_FIRE_LASER_AIM  = 0x144,  // fire laser aimed at player
    ECL_FIRE_SPREAD     = 0x145,  // fire spread pattern
    ECL_FIRE_CIRCLE     = 0x146,  // fire circular pattern
    ECL_FIRE_RANDOM     = 0x147,  // fire random pattern
    ECL_FIRE_BURST      = 0x148,  // fire burst pattern
    ECL_SET_BULLET_TYPE = 0x149,  // set bullet sprite type
    ECL_SET_BULLET_COLOR= 0x14A,  // set bullet color
    ECL_SET_BULLET_SIZE = 0x14B,  // set bullet size
    ECL_SET_BULLET_SPEED= 0x14C,  // set bullet speed
    ECL_SET_BULLET_COUNT= 0x14D,  // set bullet count
    ECL_SET_BULLET_ANGLE= 0x14E,  // set bullet angle
    ECL_SET_BULLET_SPREAD=0x14F,  // set bullet spread
    ECL_SET_BULLET_DELAY= 0x150,  // set bullet delay
    ECL_SET_BULLET_LIFE = 0x151,  // set bullet lifetime
    ECL_SET_BULLET_GRAV = 0x152,  // set bullet gravity
    ECL_SET_BULLET_FLAGS= 0x153,  // set bullet flags
    ECL_SET_BULLET_HIT  = 0x154,  // set bullet hitbox
    ECL_SET_BULLET_DMG  = 0x155,  // set bullet damage
    ECL_SET_BULLET_BLEND= 0x156,  // set bullet blend mode

    ECL_CALL_SCRIPT     = 0x15C,  // call ECL sub-script
    ECL_RETURN          = 0x165,  // return from script
    ECL_JUMP            = 0x166,  // unconditional jump
    ECL_JUMP_IF         = 0x167,  // conditional jump
    ECL_SET_VAR         = 0x157,  // set variable
    ECL_SET_VAR_FLOAT   = 0x158,  // set float variable
    ECL_SET_VAR_INT     = 0x159,  // set int variable
    ECL_SET_VAR_RANDOM  = 0x15A,  // set variable to random
    ECL_SET_VAR_TIME    = 0x15B,  // set variable to frame time
    ECL_SET_VAR_DIFF    = 0x15D,  // set variable by difficulty
    ECL_ADD_VAR         = 0x15E,  // add to variable
    ECL_SUB_VAR         = 0x15F,  // subtract from variable
    ECL_MUL_VAR         = 0x160,  // multiply variable
    ECL_DIV_VAR         = 0x161,  // divide variable
    ECL_MOD_VAR         = 0x162,  // modulo variable
    ECL_CMP_VAR         = 0x163,  // compare variable
    ECL_SET_VAR2        = 0x164,  // set variable (variant)

    ECL_WAIT            = 0x168,  // wait N frames
    ECL_WAIT_UNTIL      = 0x169,  // wait until condition
    ECL_SET_INT         = 0x16A,  // set int register
    ECL_SET_FLOAT       = 0x16B,  // set float register
    ECL_SET_INT_VAR     = 0x16C,  // set int from variable
    ECL_SET_FLOAT_VAR   = 0x16D,  // set float from variable
    ECL_SET_INT_GLOBAL  = 0x16E,  // set global int
    ECL_SET_FLOAT_GLOBAL= 0x16F,  // set global float
    ECL_SET_INT_RESULT  = 0x170,  // set result int

    // Sound/music opcodes (0x191-0x1B4)
    ECL_PLAY_SFX        = 0x191,  // play sound effect
    ECL_STOP_SFX        = 0x192,  // stop sound effect
    ECL_PLAY_BGM        = 0x193,  // play background music
    ECL_STOP_BGM        = 0x194,  // stop background music
    ECL_PAUSE_BGM       = 0x195,  // pause background music
    ECL_RESUME_BGM      = 0x196,  // resume background music
    ECL_SET_BGM_VOL     = 0x197,  // set BGM volume
    ECL_SET_SFX_VOL     = 0x198,  // set SFX volume
    ECL_SET_BGM_POS     = 0x199,  // set BGM position
    ECL_FADE_BGM        = 0x19A,  // fade BGM
    ECL_PLAY_CHR        = 0x19B,  // play character voice
    ECL_STOP_CHR        = 0x19C,  // stop character voice
    ECL_STOP_ALL_SFX    = 0x1AF,  // stop all sound effects
    ECL_SET_PITCH       = 0x19D,  // set pitch
    ECL_STOP_ALL_BGM    = 0x1B0,  // stop all BGM
    ECL_SET_REVERB      = 0x19E,  // set reverb
    ECL_SET_CHORUS      = 0x19F,  // set chorus
    ECL_SET_3D_POS      = 0x1A0,  // set 3D position
    ECL_SET_3D_DIST     = 0x1A1,  // set 3D distance
    ECL_LOAD_BANK       = 0x1A2,  // load sound bank
    ECL_UNLOAD_BANK     = 0x1A3,  // unload sound bank
    ECL_SET_MASTER_VOL  = 0x1A4,  // set master volume
    ECL_PLAY_SEQ        = 0x1A5,  // play sequence
    ECL_STOP_SEQ        = 0x1A6,  // stop sequence
    ECL_SET_SEQ_VOL     = 0x1A7,  // set sequence volume
    ECL_SET_SEQ_TEMPO   = 0x1A8,  // set sequence tempo
    ECL_PLAY_3D_SFX     = 0x1A9,  // play 3D sound effect
    ECL_SET_PAN         = 0x1AA,  // set pan
    ECL_SET_OUTPUT      = 0x1AB,  // set output mode
    ECL_SET_EFFECT      = 0x1AC,  // set effect
    ECL_SET_EQ          = 0x1B1,  // set equalizer
    ECL_MUTE            = 0x1AD,  // mute/unmute
    ECL_UNMUTE          = 0x1B2,  // unmute
    ECL_SET_VOICE_VOL   = 0x1AE,  // set voice volume
    ECL_RESET_AUDIO     = 0x1B3,  // reset audio state
    ECL_SET_MIX         = 0x1B4,  // set mix level
};

// ============================================================================
// ECL Instruction Header (5 bytes)
// Read by the VM dispatch at 0x0040E770
// ============================================================================
struct ECLInstruction {
    uint32_t offset;     // instruction offset in script data
    unsigned short opcode;     // ECL opcode (0x100-0x1B4)
    uint8_t  data[];     // variable-length operand data
};

// ============================================================================
// ECL VM Context
// The entity at +0x14D8 has a pointer to the ECL execution state
// ============================================================================
struct ECLVMState {
    void*    current_script;    // +0x00 script pointer
    void*    instruction_ptr;   // +0x04 current instruction pointer
    int32_t  instruction_offset;// +0x08
};
