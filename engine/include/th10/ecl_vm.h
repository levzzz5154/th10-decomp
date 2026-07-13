#pragma once
#include "th10/types.h"
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <unordered_map>

namespace th10 {

// ========================================
// ECL Opcode enumeration (0x100 - 0x1B4)
// Reversed from th10.exe dispatch @ 0x0040E770
// ========================================
enum class EclOpcode : int16_t {
    // --- Movement: Set bullet position (0x100-0x10F) ---
    SET_BULLET_POS          = 0x100, // set bullet pos (world coords)
    SET_BULLET_POS_RANK     = 0x101, // set bullet pos (rank-gated)
    SET_BULLET_POS_STORE    = 0x102, // set bullet pos via bullet manager store
    SET_BULLET_POS_IDX      = 0x103, // set bullet pos with anim index lookup
    SET_BULLET_POS_SCREEN   = 0x104, // set bullet pos (screen-space projection)
    SET_BULLET_POS_BOSS     = 0x105, // set bullet pos (boss mode)
    SET_BULLET_POS_ANIM     = 0x106, // set bullet pos with anim + hitbox
    SET_BULLET_POS_ROTATE   = 0x107, // set bullet pos with rotation
    SET_BULLET_POS_MODE_8   = 0x108, // set bullet pos (alternate mode)
    SET_BULLET_POS_MODE_9   = 0x109, // set bullet pos (game-state gated)
    SET_BULLET_POS_MODE_A   = 0x10A, // set bullet pos (game-state gated + rank)
    SET_BULLET_POS_MODE_B   = 0x10B, // set bullet pos (inverted game-state gate)
    SET_BULLET_POS_MODE_C   = 0x10C, // set bullet pos (game-state gated + boss)
    SET_BULLET_POS_MODE_D   = 0x10D, // set bullet pos (upgrade anim)
    SET_BULLET_POS_ABS      = 0x10E, // set bullet pos (absolute world coords 3D)
    SET_BULLET_POS_ABS_GATE = 0x10F, // set bullet pos (absolute, game-state gated)

    // --- Movement: Set enemy position (0x110-0x117) ---
    SET_ENEMY_POS           = 0x110, // set enemy position (world coords)
    SET_ENEMY_POS_ROTATE    = 0x111, // set enemy position with rotation
    OP_0x112                = 0x112, // (unreferenced in dispatch)
    OP_0x113                = 0x113,
    OP_0x114                = 0x114,
    OP_0x115                = 0x115,
    OP_0x116                = 0x116,
    OP_0x117                = 0x117,

    // --- Movement: Speed/accel X (0x118-0x11F) ---
    SET_SPEED_X             = 0x118, // set horizontal speed (instant)
    SET_SPEED_X_INTERP      = 0x119, // set horizontal speed (interpolated)
    SET_SPEED_Y             = 0x11A, // set vertical speed (instant)
    SET_SPEED_Y_INTERP      = 0x11B, // set vertical speed (interpolated)
    SET_ACCEL_X             = 0x11C, // set horizontal acceleration (instant)
    SET_ACCEL_X_INTERP      = 0x11D, // set horizontal acceleration (interpolated)
    SET_ACCEL_Y             = 0x11E, // set vertical acceleration (instant)
    SET_ACCEL_Y_INTERP      = 0x11F, // set vertical acceleration (interpolated)

    // --- Movement: Angular speed (0x120-0x123) ---
    SET_ANGULAR_SPEED_X     = 0x120, // set angular speed X (instant)
    SET_ANGULAR_SPEED_X_IP  = 0x121, // set angular speed X (interpolated, dual-axis)
    SET_ANGULAR_SPEED_Y     = 0x122, // set angular speed Y (instant)
    SET_ANGULAR_SPEED_Y_IP  = 0x123, // set angular speed Y (interpolated, dual-axis)

    // --- Movement: Aim (0x124-0x127) ---
    AIM_TO_PLAYER_X         = 0x124, // aim horizontal towards player
    AIM_TO_PLAYER_Y         = 0x125, // aim vertical towards player
    OP_0x126                = 0x126, // unk movement
    SET_SPEED_TO_PLAYER     = 0x127, // copy velocity to player position

    // --- Movement: Add/accel (0x128-0x12B) ---
    ADD_POS_X               = 0x128, // add to position X
    ADD_POS_Y               = 0x129, // add to position Y
    SET_ACCEL_X_DIRECT      = 0x12A, // set acceleration X (direct)
    SET_ACCEL_Y_DIRECT      = 0x12B, // set acceleration Y (direct, shares handler with 0x12A in some modes)

    OP_0x12C = 0x12C, OP_0x12D = 0x12D, OP_0x12E = 0x12E, OP_0x12F = 0x12F,
    OP_0x130 = 0x130, OP_0x131 = 0x131, OP_0x132 = 0x132, OP_0x133 = 0x133,
    OP_0x134 = 0x134, OP_0x135 = 0x135, OP_0x136 = 0x136, OP_0x137 = 0x137,
    OP_0x138 = 0x138, OP_0x139 = 0x139, OP_0x13A = 0x13A, OP_0x13B = 0x13B,
    OP_0x13C = 0x13C, OP_0x13D = 0x13D, OP_0x13E = 0x13E, OP_0x13F = 0x13F,

    // --- Enemy State (0x140-0x15B) ---
    SET_HITBOX_WIDTH        = 0x140, // set enemy hitbox width
    SET_HITBOX_HEIGHT       = 0x141, // set enemy hitbox height
    SET_FLAGS               = 0x142, // OR flags into bitfield at enemy+0x1444
    CLEAR_FLAGS             = 0x143, // AND NOT flags from bitfield at enemy+0x1444
    SET_MOVE_BOUNDARY       = 0x144, // set movement boundary rect (4 floats)
    CLEAR_MOVE_BOUNDARY     = 0x145, // clear movement boundary rect
    RESET_BULLET_ARRAY      = 0x146, // reset bullet/option arrays (zero out)
    SET_DIFFICULTY_PARAM    = 0x147, // set difficulty-dependent param (12 slots)
    SET_RANGE_PARAMS        = 0x148, // set range min/max parameters
    BOSS_OPERATION          = 0x149, // multi-phase boss operations
    SET_ENEMY_TYPE          = 0x14A, // set enemy type/variant
    SET_SPELL_BONUS_TIME    = 0x14B, // set spell card bonus timer
    SET_ACTIVE_SUB          = 0x14C, // set active ECL subroutine index
    CALL_FUNC_NO_PARAM      = 0x14D, // call function by index (no param)
    STORE_INSTR_TABLE       = 0x14E, // store instruction table entry
    CALL_FUNC_PARAM         = 0x14F, // call function by index (with param)
    SCRIPT_END_RESET        = 0x150, // reset / end-of-script handler
    PLAY_SOUND              = 0x151, // play sound/music (4 params)
    HARD_RESET              = 0x152, // full reset: clear bullets, sounds, subs
    END_IF_BOSS_ACTIVE      = 0x153, // end script if boss active (returns -1)
    END_IF_CONDITION        = 0x154, // end script if condition false (returns -1)
    STORE_INSTR_PTR         = 0x155, // store instruction pointer offset
    SHOW_DIALOG             = 0x156, // show dialog text (XOR-decrypted inline)
    RUN_SUB_SCRIPT          = 0x157, // run ECL sub-script
    SET_VALUE               = 0x158, // set value from param via alloc
    REFRESH_BULLETS         = 0x159, // refresh bullet manager (cleanup dead)
    SET_SQ_DIST_THRESHOLD   = 0x15A, // set square distance threshold
    SET_SPELL_BONUS_PARAMS  = 0x15B, // set spell card bonus parameters

    // --- Dialog (0x15C, 0x165-0x167) ---
    SHOW_DIALOG_RANK        = 0x15C, // show dialog text (rank-gated)

    // --- Random/Rank/Difficulty (0x15D-0x164) ---
    GET_DIFF_RANDOM         = 0x15D, // get difficulty-scaled random float
    GET_DIFF_SCALED         = 0x15E, // get difficulty-scaled value (5 tiers)
    GET_DIFF_INTERP         = 0x15F, // get linear-interpolated difficulty value
    GET_RANK_INT            = 0x160, // get rank-dependent int (2 tiers)
    GET_RANK_INT_MULTI      = 0x161, // get rank-dependent int (5 tiers)
    GET_RANK_INTERP         = 0x162, // get interpolated rank int
    GET_DIFF_PARAM_IDX      = 0x163, // get difficulty-dependent param by index
    GET_DIFF_FLOAT          = 0x164, // get difficulty-dependent float (5 tiers)

    SHOW_DIALOG_STAGE_0     = 0x165, // show dialog (stage relative, offset +0)
    SHOW_DIALOG_STAGE_1     = 0x166, // show dialog (stage relative, offset -1)
    SHOW_DIALOG_STAGE_2     = 0x167, // show dialog (stage relative, offset -2)

    // --- Script Control (0x168-0x170) ---
    STORE_GLOBAL_VALUE      = 0x168, // store value to global variable slot
    CALL_FUNC_BY_INDEX      = 0x169, // call function by index (with param, alias)
    SET_GLOBAL_FLAG         = 0x16A, // set global flag bit in manager
    CONTROL_0x16B           = 0x16B, // control/cleanup operation
    TOGGLE_FLAG_BIT         = 0x16C, // XOR a flag bit at enemy+0x1444
    CONTROL_0x16D           = 0x16D, // control operation (cleanup)
    SET_SCRIPT_PARAMS       = 0x16E, // set per-script parameter values
    RESET_GLOBAL_FLOAT      = 0x16F, // reset a global float to 0
    SUBTRACT_GLOBAL_INT     = 0x170, // subtract global int from script time

    OP_0x171 = 0x171, OP_0x172 = 0x172, OP_0x173 = 0x173, OP_0x174 = 0x174,
    OP_0x175 = 0x175, OP_0x176 = 0x176, OP_0x177 = 0x177, OP_0x178 = 0x178,
    OP_0x179 = 0x179, OP_0x17A = 0x17A, OP_0x17B = 0x17B, OP_0x17C = 0x17C,
    OP_0x17D = 0x17D, OP_0x17E = 0x17E, OP_0x17F = 0x17F,
    OP_0x180 = 0x180, OP_0x181 = 0x181, OP_0x182 = 0x182, OP_0x183 = 0x183,
    OP_0x184 = 0x184, OP_0x185 = 0x185, OP_0x186 = 0x186, OP_0x187 = 0x187,
    OP_0x188 = 0x188, OP_0x189 = 0x189, OP_0x18A = 0x18A, OP_0x18B = 0x18B,
    OP_0x18C = 0x18C, OP_0x18D = 0x18D, OP_0x18E = 0x18E, OP_0x18F = 0x18F,

    // --- Laser Operations (0x190-0x19B) ---
    CREATE_LASER            = 0x190, // create laser entry (0x210-byte struct)
    SET_LASER_POS           = 0x191, // set laser position (relative+offset)
    SET_LASER_GRAPHIC_SIZE  = 0x192, // set laser graphic width/height
    SET_LASER_SPEED         = 0x193, // set laser speed (target velocity)
    SET_LASER_ANGLE         = 0x194, // set laser angle/rotation
    SET_LASER_PARAM         = 0x195, // set laser rendering parameter
    SET_LASER_DIMENSIONS    = 0x196, // set laser length/width dimensions
    SET_LASER_CONTROL       = 0x197, // set laser control value
    SET_LASER_RENDER        = 0x198, // set laser render flags
    SET_LASER_CONFIG        = 0x199, // set laser config struct (6 params)
    CLEAR_BULLET_LIST       = 0x19A, // clear bullet list (index 1)
    COPY_LASER_DATA         = 0x19B, // copy laser data from one slot to another

    // --- Bullet Properties (0x19C-0x1A3) ---
    CREATE_ENEMY_BULLET     = 0x19C, // create enemy bullet (basic)
    CREATE_ENEMY_BULLET_EX  = 0x19D, // create enemy bullet (extended params)
    SET_BULLET_SPEED        = 0x19E, // set bullet speed (velocity)
    SET_BULLET_ANGLE        = 0x19F, // set bullet angle/direction
    SET_BULLET_ACCEL        = 0x1A0, // set bullet acceleration
    SET_BULLET_HITBOX       = 0x1A1, // set bullet hitbox radius
    SET_BULLET_SPACING      = 0x1A2, // set bullet spacing for patterns
    SET_BULLET_PARAM        = 0x1A3, // set bullet extra parameter (offset 0x440)

    // --- Bullet Firing Patterns (0x1A4-0x1B4) ---
    FIRE_BULLET_RING        = 0x1A4, // fire bullet ring (dense/circular)
    FIRE_BULLET_LINE        = 0x1A5, // fire bullet line
    OP_0x1A6                = 0x1A6, // fire pattern variant
    OP_0x1A7                = 0x1A7,
    OP_0x1A8                = 0x1A8,
    OP_0x1A9                = 0x1A9,
    OP_0x1AA                = 0x1AA,
    OP_0x1AB                = 0x1AB,
    OP_0x1AC                = 0x1AC,
    OP_0x1AD                = 0x1AD,
    OP_0x1AE                = 0x1AE,
    FIRE_WITH_BULLET_DATA   = 0x1AF, // fire bullets with copied bullet data
    CREATE_BULLET_WITH_COPY = 0x1B0, // create bullet with data copy
    OP_0x1B1                = 0x1B1,
    OP_0x1B2                = 0x1B2,
    OP_0x1B3                = 0x1B3,
    OP_0x1B4                = 0x1B4,
};

// ========================================
// ECL File parser: loads and parses .ecl bytecode
// ========================================
class EclFile {
public:
    EclFile() = default;
    ~EclFile();

    bool open(const std::vector<uint8_t>& data);
    bool open_file(const std::string& path);
    void close();

    const EclHeader*                  header()    const { return header_; }
    const std::vector<std::vector<uint8_t>>& subs() const { return subs_; }
    const std::vector<std::string>&   anim_list() const { return anim_list_; }
    const std::vector<std::string>&   ecli_list() const { return ecli_list_; }
    int                               sub_count() const { return static_cast<int>(subs_.size()); }
    const std::vector<uint8_t>*       sub(int i)  const;

private:
    bool parse();
    const char* read_string(uint32_t offset, const uint8_t* base, size_t data_size) const;

    std::vector<uint8_t>  data_;
    const EclHeader*      header_ = nullptr;
    std::vector<std::string> anim_list_;
    std::vector<std::string> ecli_list_;
    std::vector<std::vector<uint8_t>> subs_;
};

// ========================================
// ECL Virtual Machine: TH10 ECL bytecode execution
// Reversed from th10.exe dispatch @ 0x0040E770
// ========================================
class EclVM {
public:
    EclVM() = default;
    ~EclVM() = default;

    void load(EclFile* file);

    // Execute a subroutine starting from frame 0
    void execute(int sub_index);

    // Execute the current subroutine for one frame tick
    // Returns false when sub has terminated
    bool tick();

    int   frame()    const { return frame_; }
    bool  running()  const { return running_; }
    float pos_x()    const { return pos_x_; }
    float pos_y()    const { return pos_y_; }
    int   difficulty() const { return difficulty_; }
    int   rank()       const { return rank_value_; }

    // Read params from instruction stream
    int32_t read_param_int(const uint8_t* stream, int index) const;
    float   read_param_float(const uint8_t* stream, int index) const;
    int32_t read_param_raw(const uint8_t* stream, int index, int offset) const;

    // Execute single instruction (called by tick loop)
    int execute_instruction(const EclInstr10* instr);

private:
    // Opcode handlers
    void ins_SET_BULLET_POS(const EclInstr10* instr);
    void ins_SET_BULLET_POS_STORE(const EclInstr10* instr);
    void ins_SET_BULLET_POS_IDX(const EclInstr10* instr);
    void ins_SET_BULLET_POS_SCREEN(const EclInstr10* instr);
    void ins_SET_BULLET_POS_BOSS(const EclInstr10* instr);
    void ins_SET_BULLET_POS_ANIM(const EclInstr10* instr);
    void ins_SET_BULLET_POS_ROTATE(const EclInstr10* instr);
    void ins_SET_BULLET_POS_MODE_8(const EclInstr10* instr);
    void ins_SET_BULLET_POS_ABS(const EclInstr10* instr);
    void ins_SET_ENEMY_POS(const EclInstr10* instr);
    void ins_SET_ENEMY_POS_ROTATE(const EclInstr10* instr);
    void ins_SET_SPEED_X(const EclInstr10* instr);
    void ins_SET_SPEED_X_INTERP(const EclInstr10* instr);
    void ins_SET_ACCEL_X(const EclInstr10* instr);
    void ins_SET_ACCEL_X_INTERP(const EclInstr10* instr);
    void ins_SET_ANGULAR_SPEED_X(const EclInstr10* instr);
    void ins_SET_ANGULAR_SPEED_X_IP(const EclInstr10* instr);
    void ins_AIM_TO_PLAYER_X(const EclInstr10* instr);
    void ins_SET_SPEED_TO_PLAYER(const EclInstr10* instr);
    void ins_ADD_POS(const EclInstr10* instr);
    void ins_SET_ACCEL_DIRECT(const EclInstr10* instr);
    void ins_SET_HITBOX_WIDTH(const EclInstr10* instr);
    void ins_SET_HITBOX_HEIGHT(const EclInstr10* instr);
    void ins_SET_FLAGS(const EclInstr10* instr);
    void ins_CLEAR_FLAGS(const EclInstr10* instr);
    void ins_SET_MOVE_BOUNDARY(const EclInstr10* instr);
    void ins_CLEAR_MOVE_BOUNDARY(const EclInstr10* instr);
    void ins_RESET_BULLET_ARRAY(const EclInstr10* instr);
    void ins_SET_DIFFICULTY_PARAM(const EclInstr10* instr);
    void ins_SET_RANGE_PARAMS(const EclInstr10* instr);
    void ins_BOSS_OPERATION(const EclInstr10* instr);
    void ins_SET_ENEMY_TYPE(const EclInstr10* instr);
    void ins_SET_SPELL_BONUS_TIME(const EclInstr10* instr);
    void ins_SET_ACTIVE_SUB(const EclInstr10* instr);
    void ins_CALL_FUNC_NO_PARAM(const EclInstr10* instr);
    void ins_STORE_INSTR_TABLE(const EclInstr10* instr);
    void ins_CALL_FUNC_PARAM(const EclInstr10* instr);
    void ins_SCRIPT_END_RESET(const EclInstr10* instr);
    void ins_PLAY_SOUND(const EclInstr10* instr);
    void ins_HARD_RESET(const EclInstr10* instr);
    void ins_END_IF_BOSS_ACTIVE(const EclInstr10* instr);
    void ins_END_IF_CONDITION(const EclInstr10* instr);
    void ins_STORE_INSTR_PTR(const EclInstr10* instr);
    void ins_SHOW_DIALOG(const EclInstr10* instr);
    void ins_RUN_SUB_SCRIPT(const EclInstr10* instr);
    void ins_SET_VALUE(const EclInstr10* instr);
    void ins_REFRESH_BULLETS(const EclInstr10* instr);
    void ins_SET_SQ_DIST_THRESHOLD(const EclInstr10* instr);
    void ins_SET_SPELL_BONUS_PARAMS(const EclInstr10* instr);
    void ins_GET_DIFF_RANDOM(const EclInstr10* instr);
    void ins_GET_DIFF_SCALED(const EclInstr10* instr);
    void ins_GET_DIFF_INTERP(const EclInstr10* instr);
    void ins_GET_RANK_INT(const EclInstr10* instr);
    void ins_GET_RANK_INT_MULTI(const EclInstr10* instr);
    void ins_GET_RANK_INTERP(const EclInstr10* instr);
    void ins_GET_DIFF_PARAM_IDX(const EclInstr10* instr);
    void ins_GET_DIFF_FLOAT(const EclInstr10* instr);
    void ins_SHOW_DIALOG_STAGE(const EclInstr10* instr);
    void ins_STORE_GLOBAL_VALUE(const EclInstr10* instr);
    void ins_SET_GLOBAL_FLAG(const EclInstr10* instr);
    void ins_TOGGLE_FLAG_BIT(const EclInstr10* instr);
    void ins_SET_SCRIPT_PARAMS(const EclInstr10* instr);
    void ins_RESET_GLOBAL_FLOAT(const EclInstr10* instr);
    void ins_SUBTRACT_GLOBAL_INT(const EclInstr10* instr);
    void ins_CREATE_LASER(const EclInstr10* instr);
    void ins_SET_LASER_POS(const EclInstr10* instr);
    void ins_SET_LASER_GRAPHIC_SIZE(const EclInstr10* instr);
    void ins_SET_LASER_SPEED(const EclInstr10* instr);
    void ins_SET_LASER_ANGLE(const EclInstr10* instr);
    void ins_SET_LASER_DIMENSIONS(const EclInstr10* instr);
    void ins_SET_LASER_CONTROL(const EclInstr10* instr);
    void ins_SET_LASER_RENDER(const EclInstr10* instr);
    void ins_SET_LASER_CONFIG(const EclInstr10* instr);
    void ins_CLEAR_BULLET_LIST(const EclInstr10* instr);
    void ins_COPY_LASER_DATA(const EclInstr10* instr);
    void ins_CREATE_ENEMY_BULLET(const EclInstr10* instr);
    void ins_CREATE_ENEMY_BULLET_EX(const EclInstr10* instr);
    void ins_SET_BULLET_SPEED(const EclInstr10* instr);
    void ins_SET_BULLET_ANGLE(const EclInstr10* instr);
    void ins_SET_BULLET_ACCEL(const EclInstr10* instr);
    void ins_SET_BULLET_HITBOX(const EclInstr10* instr);
    void ins_SET_BULLET_SPACING(const EclInstr10* instr);
    void ins_SET_BULLET_PARAM(const EclInstr10* instr);
    void ins_FIRE_BULLET_RING(const EclInstr10* instr);
    void ins_FIRE_BULLET_LINE(const EclInstr10* instr);
    void ins_FIRE_WITH_BULLET_DATA(const EclInstr10* instr);
    void ins_CREATE_BULLET_WITH_COPY(const EclInstr10* instr);
    void ins_noop(const EclInstr10* instr);

    // Helpers
    bool is_rank_gated(const EclInstr10* instr) const;
    bool is_boss_active() const;

    // VM state (mirrors enemy struct fields)
    EclFile*               file_            = nullptr;
    const std::vector<uint8_t>* sub_         = nullptr;
    int                    frame_           = 0;
    bool                   running_         = false;
    size_t                 ip_              = 0;      // byte offset into current sub
    float                  pos_x_           = 0.0f;   // enemy+0x2C
    float                  pos_y_           = 0.0f;   // enemy+0x30
    float                  pos_z_           = 0.0f;   // enemy+0x34
    int                    difficulty_      = 0;
    int                    rank_value_      = 0;       // dynamic rank (DAT_00474c98)
    int                    stage_id_        = 0;       // current stage (DAT_00474c74)

    // Enemy state mirrors (fields written by ECL ops)
    float                  hitbox_w_        = 0.0f;   // enemy+0xB0
    float                  hitbox_h_        = 0.0f;   // enemy+0xB4
    float                  hurtbox_w_       = 0.0f;   // enemy+0xB8
    float                  hurtbox_h_       = 0.0f;   // enemy+0xBC
    uint32_t               flags_           = 0;       // enemy+0x1444
    float                  spell_bonus_timer_ = 0.0f;  // enemy+0x13C0
    int                    active_sub_idx_  = -1;      // enemy+0x1450
    float                  sq_dist_threshold_ = 0.0f;  // enemy+0x1454

    // ECL sub-script stack
    std::vector<int>       sub_stack_;

    // Bullet manager reference
    void*                  bullet_manager_  = nullptr; // DAT_00477704 equivalent

    // Instruction table pointer (enemy+0x14D8 in real code)
    void*                  instruction_table_ = nullptr; // DAT_004776f4 equivalent
};

} // namespace th10
