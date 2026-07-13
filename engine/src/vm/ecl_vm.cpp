#include "th10/ecl_vm.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

namespace th10 {

// ========================================
// EclFile
// ========================================

EclFile::~EclFile() { close(); }

bool EclFile::open(const std::vector<uint8_t>& data) {
    close();
    data_ = data;
    return parse();
}

bool EclFile::open_file(const std::string& path) {
    close();
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return false;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size <= 0) { fclose(f); return false; }
    data_.resize(static_cast<size_t>(size));
    fread(data_.data(), 1, static_cast<size_t>(size), f);
    fclose(f);
    return parse();
}

void EclFile::close() {
    data_.clear();
    header_ = nullptr;
    anim_list_.clear();
    ecli_list_.clear();
    subs_.clear();
}

static const char* read_str(const uint8_t* base, size_t data_size, size_t& pos) {
    if (pos >= data_size) return "";
    const char* s = reinterpret_cast<const char*>(base + pos);
    size_t len = strnlen(s, data_size - pos);
    pos += len + 1;
    return s;
}

static size_t align4(size_t p) { return (p + 3) & ~3UL; }

bool EclFile::parse() {
    if (data_.size() < 36) return false;

    header_ = reinterpret_cast<const EclHeader*>(data_.data());
    if (memcmp(header_->magic, "SCPT", 4) != 0) return false;

    const uint8_t* base = data_.data();
    size_t data_size = data_.size();
    size_t pos = 36;

    if (pos + 8 > data_size) return false;

    // Parse ANIM list
    const EclListEntry* anim = reinterpret_cast<const EclListEntry*>(base + pos);
    if (memcmp(anim->magic, "ANIM", 4) == 0) {
        pos += 8;
        for (uint32_t i = 0; i < anim->count && pos < data_size; i++) {
            anim_list_.push_back(read_str(base, data_size, pos));
        }
        pos = align4(pos);
    }

    // Parse ECLI list
    if (pos + 8 > data_size) return false;
    const EclListEntry* ecli = reinterpret_cast<const EclListEntry*>(base + pos);
    if (memcmp(ecli->magic, "ECLI", 4) == 0) {
        pos += 8;
        for (uint32_t i = 0; i < ecli->count && pos < data_size; i++) {
            ecli_list_.push_back(read_str(base, data_size, pos));
        }
        pos = align4(pos);
    }

    // Read sub offset table
    uint32_t sub_count = *reinterpret_cast<const uint32_t*>(base + 8);
    std::vector<uint32_t> sub_offsets;
    for (uint32_t i = 0; i < sub_count && pos + 4 <= data_size; i++) {
        sub_offsets.push_back(*reinterpret_cast<const uint32_t*>(base + pos));
        pos += 4;
    }

    // Skip extra offset data until name table
    while (pos + 4 <= data_size) {
        uint32_t v = *reinterpret_cast<const uint32_t*>(base + pos);
        if (v < data_size && v > 100 && memcmp(base + v, "ECLH", 4) == 0) {
            pos += 4;
        } else {
            break;
        }
    }

    // Read sub names
    std::vector<std::string> sub_names;
    for (uint32_t i = 0; i < sub_count && pos < data_size; i++) {
        sub_names.push_back(read_str(base, data_size, pos));
    }
    pos = align4(pos);

    // Parse each sub
    for (uint32_t i = 0; i < sub_count && i < sub_offsets.size(); i++) {
        uint32_t off = sub_offsets[i];
        if (off + sizeof(EclSubHeader) > data_size) continue;

        const EclSubHeader* sub_hdr = reinterpret_cast<const EclSubHeader*>(base + off);
        if (memcmp(sub_hdr->magic, "ECLH", 4) != 0) continue;

        size_t sub_end;
        if (i + 1 < sub_offsets.size()) {
            sub_end = sub_offsets[i + 1];
        } else {
            sub_end = data_size;
        }
        if (sub_end > data_size) sub_end = data_size;
        if (sub_end < off) continue;

        std::vector<uint8_t> raw(base + off, base + sub_end);
        subs_.push_back(std::move(raw));
    }

    return true;
}

const std::vector<uint8_t>* EclFile::sub(int i) const {
    if (i >= 0 && i < static_cast<int>(subs_.size())) return &subs_[i];
    return nullptr;
}

// ========================================
// EclVM
// ========================================

void EclVM::load(EclFile* file) {
    file_    = file;
    sub_     = nullptr;
    frame_   = 0;
    running_ = false;
    ip_      = 0;
    pos_x_ = pos_y_ = pos_z_ = 0.0f;
    flags_ = 0;
    hitbox_w_ = hitbox_h_ = 0.0f;
    hurtbox_w_ = hurtbox_h_ = 0.0f;
    spell_bonus_timer_ = 0.0f;
    active_sub_idx_ = -1;
    sq_dist_threshold_ = 0.0f;
    sub_stack_.clear();
}

void EclVM::execute(int sub_index) {
    if (!file_) return;
    auto* s = file_->sub(sub_index);
    if (!s) return;
    sub_ = s;
    frame_ = -1;
    running_ = true;
    ip_ = sizeof(EclSubHeader);

    while (running_) {
        frame_++;
        tick();
    }
}

bool EclVM::tick() {
    if (!running_ || !sub_) return false;

    const uint8_t* base = sub_->data();
    size_t limit = sub_->size();

    while (ip_ < limit) {
        if (ip_ + 0x14 > limit) {
            running_ = false;
            return false;
        }

        const EclInstr10* instr = reinterpret_cast<const EclInstr10*>(base + ip_);

        // Skip instructions whose time hasn't elapsed yet
        if (instr->time > static_cast<int32_t>(frame_))
            return true;

        if (instr->time == static_cast<int32_t>(frame_)) {
            int result = execute_instruction(instr);
            if (result < 0) {
                // -1 returned means stop script (opcodes 0x153, 0x154)
                running_ = false;
                return false;
            }
        }

        ip_ += 0x14 + instr->param_count * 4;
        if (ip_ > limit) {
            running_ = false;
            return false;
        }
    }

    running_ = false;
    return false;
}

// ========================================
// Instruction dispatch (mirrors 0x0040E770)
// ========================================

int EclVM::execute_instruction(const EclInstr10* instr) {
    int16_t op = instr->opcode;

    if (static_cast<int32_t>(op) - 0x100 > 0xB4)
        return 0;

    switch (static_cast<EclOpcode>(op)) {
        // --- Movement: Bullet position (0x100-0x10F) ---
        case EclOpcode::SET_BULLET_POS:
        case EclOpcode::SET_BULLET_POS_MODE_9:
            ins_SET_BULLET_POS(instr); break;
        case EclOpcode::SET_BULLET_POS_STORE:
            ins_SET_BULLET_POS_STORE(instr); break;
        case EclOpcode::SET_BULLET_POS_IDX:
            ins_SET_BULLET_POS_IDX(instr); break;
        case EclOpcode::SET_BULLET_POS_SCREEN:
        case EclOpcode::SET_BULLET_POS_MODE_B:
            ins_SET_BULLET_POS_SCREEN(instr); break;
        case EclOpcode::SET_BULLET_POS_BOSS:
        case EclOpcode::SET_BULLET_POS_MODE_C:
            ins_SET_BULLET_POS_BOSS(instr); break;
        case EclOpcode::SET_BULLET_POS_ANIM:
            ins_SET_BULLET_POS_ANIM(instr); break;
        case EclOpcode::SET_BULLET_POS_ROTATE:
            ins_SET_BULLET_POS_ROTATE(instr); break;
        case EclOpcode::SET_BULLET_POS_MODE_8:
            ins_SET_BULLET_POS_MODE_8(instr); break;
        case EclOpcode::SET_BULLET_POS_MODE_D:
            ins_SET_BULLET_POS_IDX(instr); break;
        case EclOpcode::SET_BULLET_POS_ABS:
        case EclOpcode::SET_BULLET_POS_ABS_GATE:
            ins_SET_BULLET_POS_ABS(instr); break;
        case EclOpcode::SET_BULLET_POS_RANK:
        case EclOpcode::SET_BULLET_POS_MODE_A:
            ins_SET_BULLET_POS(instr); break;

        // --- Movement: Enemy position (0x110-0x111) ---
        case EclOpcode::SET_ENEMY_POS:
            ins_SET_ENEMY_POS(instr); break;
        case EclOpcode::SET_ENEMY_POS_ROTATE:
            ins_SET_ENEMY_POS_ROTATE(instr); break;

        // --- Movement: Speed/accel (0x118-0x11F) ---
        case EclOpcode::SET_SPEED_X:
        case EclOpcode::SET_SPEED_Y:
            ins_SET_SPEED_X(instr); break;
        case EclOpcode::SET_SPEED_X_INTERP:
        case EclOpcode::SET_SPEED_Y_INTERP:
            ins_SET_SPEED_X_INTERP(instr); break;
        case EclOpcode::SET_ACCEL_X:
        case EclOpcode::SET_ACCEL_Y:
            ins_SET_ACCEL_X(instr); break;
        case EclOpcode::SET_ACCEL_X_INTERP:
        case EclOpcode::SET_ACCEL_Y_INTERP:
            ins_SET_ACCEL_X_INTERP(instr); break;

        // --- Movement: Angular speed (0x120-0x123) ---
        case EclOpcode::SET_ANGULAR_SPEED_X:
        case EclOpcode::SET_ANGULAR_SPEED_Y:
            ins_SET_ANGULAR_SPEED_X(instr); break;
        case EclOpcode::SET_ANGULAR_SPEED_X_IP:
        case EclOpcode::SET_ANGULAR_SPEED_Y_IP:
            ins_SET_ANGULAR_SPEED_X_IP(instr); break;

        // --- Movement: Aim (0x124-0x127) ---
        case EclOpcode::AIM_TO_PLAYER_X:
        case EclOpcode::AIM_TO_PLAYER_Y:
            ins_AIM_TO_PLAYER_X(instr); break;
        case EclOpcode::SET_SPEED_TO_PLAYER:
            ins_SET_SPEED_TO_PLAYER(instr); break;

        // --- Movement: Add/accel (0x128-0x12B) ---
        case EclOpcode::ADD_POS_X:
        case EclOpcode::ADD_POS_Y:
            ins_ADD_POS(instr); break;
        case EclOpcode::SET_ACCEL_X_DIRECT:
        case EclOpcode::SET_ACCEL_Y_DIRECT:
            ins_SET_ACCEL_DIRECT(instr); break;

        // --- Enemy State (0x140-0x15B) ---
        case EclOpcode::SET_HITBOX_WIDTH:
            ins_SET_HITBOX_WIDTH(instr); break;
        case EclOpcode::SET_HITBOX_HEIGHT:
            ins_SET_HITBOX_HEIGHT(instr); break;
        case EclOpcode::SET_FLAGS:
            ins_SET_FLAGS(instr); break;
        case EclOpcode::CLEAR_FLAGS:
            ins_CLEAR_FLAGS(instr); break;
        case EclOpcode::SET_MOVE_BOUNDARY:
            ins_SET_MOVE_BOUNDARY(instr); break;
        case EclOpcode::CLEAR_MOVE_BOUNDARY:
            ins_CLEAR_MOVE_BOUNDARY(instr); break;
        case EclOpcode::RESET_BULLET_ARRAY:
            ins_RESET_BULLET_ARRAY(instr); break;
        case EclOpcode::SET_DIFFICULTY_PARAM:
            ins_SET_DIFFICULTY_PARAM(instr); break;
        case EclOpcode::SET_RANGE_PARAMS:
            ins_SET_RANGE_PARAMS(instr); break;
        case EclOpcode::BOSS_OPERATION:
            ins_BOSS_OPERATION(instr); break;
        case EclOpcode::SET_ENEMY_TYPE:
            ins_SET_ENEMY_TYPE(instr); break;
        case EclOpcode::SET_SPELL_BONUS_TIME:
            ins_SET_SPELL_BONUS_TIME(instr); break;
        case EclOpcode::SET_ACTIVE_SUB:
            ins_SET_ACTIVE_SUB(instr); break;
        case EclOpcode::CALL_FUNC_NO_PARAM:
            ins_CALL_FUNC_NO_PARAM(instr); break;
        case EclOpcode::STORE_INSTR_TABLE:
            ins_STORE_INSTR_TABLE(instr); break;
        case EclOpcode::CALL_FUNC_PARAM:
            ins_CALL_FUNC_PARAM(instr); break;
        case EclOpcode::SCRIPT_END_RESET:
            ins_SCRIPT_END_RESET(instr); break;
        case EclOpcode::PLAY_SOUND:
            ins_PLAY_SOUND(instr); break;
        case EclOpcode::HARD_RESET:
            ins_HARD_RESET(instr); break;
        case EclOpcode::END_IF_BOSS_ACTIVE:
            ins_END_IF_BOSS_ACTIVE(instr); break;
        case EclOpcode::END_IF_CONDITION:
            ins_END_IF_CONDITION(instr); break;
        case EclOpcode::STORE_INSTR_PTR:
            ins_STORE_INSTR_PTR(instr); break;
        case EclOpcode::SHOW_DIALOG:
        case EclOpcode::SHOW_DIALOG_RANK:
        case EclOpcode::SHOW_DIALOG_STAGE_0:
        case EclOpcode::SHOW_DIALOG_STAGE_1:
        case EclOpcode::SHOW_DIALOG_STAGE_2:
            ins_SHOW_DIALOG(instr); break;
        case EclOpcode::RUN_SUB_SCRIPT:
            ins_RUN_SUB_SCRIPT(instr); break;
        case EclOpcode::SET_VALUE:
            ins_SET_VALUE(instr); break;
        case EclOpcode::REFRESH_BULLETS:
            ins_REFRESH_BULLETS(instr); break;
        case EclOpcode::SET_SQ_DIST_THRESHOLD:
            ins_SET_SQ_DIST_THRESHOLD(instr); break;
        case EclOpcode::SET_SPELL_BONUS_PARAMS:
            ins_SET_SPELL_BONUS_PARAMS(instr); break;

        // --- Random/Rank/Difficulty (0x15D-0x164) ---
        case EclOpcode::GET_DIFF_RANDOM:
            ins_GET_DIFF_RANDOM(instr); break;
        case EclOpcode::GET_DIFF_SCALED:
            ins_GET_DIFF_SCALED(instr); break;
        case EclOpcode::GET_DIFF_INTERP:
            ins_GET_DIFF_INTERP(instr); break;
        case EclOpcode::GET_RANK_INT:
            ins_GET_RANK_INT(instr); break;
        case EclOpcode::GET_RANK_INT_MULTI:
            ins_GET_RANK_INT_MULTI(instr); break;
        case EclOpcode::GET_RANK_INTERP:
            ins_GET_RANK_INTERP(instr); break;
        case EclOpcode::GET_DIFF_PARAM_IDX:
            ins_GET_DIFF_PARAM_IDX(instr); break;
        case EclOpcode::GET_DIFF_FLOAT:
            ins_GET_DIFF_FLOAT(instr); break;

        // --- Script Control (0x168-0x170) ---
        case EclOpcode::STORE_GLOBAL_VALUE:
            ins_STORE_GLOBAL_VALUE(instr); break;
        case EclOpcode::CALL_FUNC_BY_INDEX:
            ins_CALL_FUNC_PARAM(instr); break;
        case EclOpcode::SET_GLOBAL_FLAG:
            ins_SET_GLOBAL_FLAG(instr); break;
        case EclOpcode::CONTROL_0x16B:
            ins_noop(instr); break;
        case EclOpcode::TOGGLE_FLAG_BIT:
            ins_TOGGLE_FLAG_BIT(instr); break;
        case EclOpcode::CONTROL_0x16D:
            ins_noop(instr); break;
        case EclOpcode::SET_SCRIPT_PARAMS:
            ins_SET_SCRIPT_PARAMS(instr); break;
        case EclOpcode::RESET_GLOBAL_FLOAT:
            ins_RESET_GLOBAL_FLOAT(instr); break;
        case EclOpcode::SUBTRACT_GLOBAL_INT:
            ins_SUBTRACT_GLOBAL_INT(instr); break;

        // --- Laser Operations (0x190-0x19B) ---
        case EclOpcode::CREATE_LASER:
            ins_CREATE_LASER(instr); break;
        case EclOpcode::SET_LASER_POS:
            ins_SET_LASER_POS(instr); break;
        case EclOpcode::SET_LASER_GRAPHIC_SIZE:
            ins_SET_LASER_GRAPHIC_SIZE(instr); break;
        case EclOpcode::SET_LASER_SPEED:
            ins_SET_LASER_SPEED(instr); break;
        case EclOpcode::SET_LASER_ANGLE:
            ins_SET_LASER_ANGLE(instr); break;
        case EclOpcode::SET_LASER_DIMENSIONS:
            ins_SET_LASER_DIMENSIONS(instr); break;
        case EclOpcode::SET_LASER_CONTROL:
            ins_SET_LASER_CONTROL(instr); break;
        case EclOpcode::SET_LASER_RENDER:
            ins_SET_LASER_RENDER(instr); break;
        case EclOpcode::SET_LASER_CONFIG:
            ins_SET_LASER_CONFIG(instr); break;
        case EclOpcode::CLEAR_BULLET_LIST:
            ins_CLEAR_BULLET_LIST(instr); break;
        case EclOpcode::COPY_LASER_DATA:
            ins_COPY_LASER_DATA(instr); break;

        // --- Bullet Properties (0x19C-0x1A3) ---
        case EclOpcode::CREATE_ENEMY_BULLET:
            ins_CREATE_ENEMY_BULLET(instr); break;
        case EclOpcode::CREATE_ENEMY_BULLET_EX:
            ins_CREATE_ENEMY_BULLET_EX(instr); break;
        case EclOpcode::SET_BULLET_SPEED:
            ins_SET_BULLET_SPEED(instr); break;
        case EclOpcode::SET_BULLET_ANGLE:
            ins_SET_BULLET_ANGLE(instr); break;
        case EclOpcode::SET_BULLET_ACCEL:
            ins_SET_BULLET_ACCEL(instr); break;
        case EclOpcode::SET_BULLET_HITBOX:
            ins_SET_BULLET_HITBOX(instr); break;
        case EclOpcode::SET_BULLET_SPACING:
            ins_SET_BULLET_SPACING(instr); break;
        case EclOpcode::SET_BULLET_PARAM:
            ins_SET_BULLET_PARAM(instr); break;

        // --- Bullet Firing Patterns (0x1A4-0x1B4) ---
        case EclOpcode::FIRE_BULLET_RING:
            ins_FIRE_BULLET_RING(instr); break;
        case EclOpcode::FIRE_BULLET_LINE:
            ins_FIRE_BULLET_LINE(instr); break;
        case EclOpcode::FIRE_WITH_BULLET_DATA:
            ins_CREATE_ENEMY_BULLET(instr); break;
        case EclOpcode::CREATE_BULLET_WITH_COPY:
            ins_CREATE_ENEMY_BULLET_EX(instr); break;

        default:
            break;
    }

    return 0;
}

// ========================================
// Param access helpers
// ========================================

int32_t EclVM::read_param_int(const uint8_t* stream, int index) const {
    // Params start at instruction + 0x14, packed as int32_t values
    // param_mask bit determines if the value is float (bit set) or int (bit clear)
    // But for int reading we just grab the raw int32
    const int32_t* params = reinterpret_cast<const int32_t*>(stream + 0x14);
    return params[index];
}

float EclVM::read_param_float(const uint8_t* stream, int index) const {
    const int32_t* params = reinterpret_cast<const int32_t*>(stream + 0x14);
    int32_t raw = params[index];
    const EclInstr10* instr = reinterpret_cast<const EclInstr10*>(stream);
    // If param_mask bit is set, reinterpret as float; otherwise cast int to float
    if (instr->param_mask & (1 << index)) {
        float f;
        memcpy(&f, &raw, sizeof(float));
        return f;
    }
    return static_cast<float>(raw);
}

int32_t EclVM::read_param_raw(const uint8_t* stream, int index, int offset) const {
    // Reads raw int32_t from param at index, then applies offset logic
    (void)offset;
    return read_param_int(stream, index);
}

bool EclVM::is_rank_gated(const EclInstr10* instr) const {
    // rank_mask gates based on difficulty+rank bits
    // 0 means always execute
    return instr->rank_mask != 0;
}

bool EclVM::is_boss_active() const {
    return (flags_ & 0x10) != 0;
}

// ========================================
// Movement: Bullet position handlers
// ========================================

void EclVM::ins_SET_BULLET_POS(const EclInstr10* instr) {
    // 0x100/0x101/0x109/0x10A: Set bullet position (world coords, with rank/difficulty gate)
    // In real code: reads bullet pos via bullet manager, applies world-to-screen projection
    // if flag 0x40000 is set on enemy. Otherwise uses enemy world pos.
    // Params: x_offset, y_offset, bullet_slot, mode, flags
    //
    // Pseudocode structure:
    //   if (game_state == 0 && rank_gated) return;
    //   bullet_pos_x = enemy_x + read_param_float(0);
    //   bullet_pos_y = enemy_y + read_param_float(1);
    //   if (flags & 0x40000) { project to screen space }
    //   apply to bullet_manager at slot
}

void EclVM::ins_SET_BULLET_POS_STORE(const EclInstr10* instr) {
    // 0x102: Set bullet position via bullet manager store
    // Reads 1 param (bullet index), stores to enemy+0xE8
}

void EclVM::ins_SET_BULLET_POS_IDX(const EclInstr10* instr) {
    // 0x103/0x10D: Set bullet position with anim index lookup
    // Reads bullet index, then anim_index, looks up sprite width/height
    // Stores to enemy bullet slot array +0xC0
    // If first slot, also sets hitbox dimensions from anim sprite size
}

void EclVM::ins_SET_BULLET_POS_SCREEN(const EclInstr10* instr) {
    // 0x104/0x10B: Set bullet position (screen-space projection via D3DXVec3Project)
    // Always applies world-to-screen transformation
    // Uses D3D viewport, projection, and world matrices
}

void EclVM::ins_SET_BULLET_POS_BOSS(const EclInstr10* instr) {
    // 0x105/0x10C: Set bullet position (boss mode)
    // Gate on game_state == 0 for 0x10C
    // Similar to 0x100 but with boss-specific handling
}

void EclVM::ins_SET_BULLET_POS_ANIM(const EclInstr10* instr) {
    // 0x106: Set bullet position with animation data + hitbox
    // Reads bullet_slot, sprite_index
    // If first slot: updates hitbox from anim dimensions, ORs flag 0x1000
}

void EclVM::ins_SET_BULLET_POS_ROTATE(const EclInstr10* instr) {
    // 0x107: Set bullet position with rotation
    // Same as SET_BULLET_POS but +0xEE5B handler applies 3D rotation matrix
}

void EclVM::ins_SET_BULLET_POS_MODE_8(const EclInstr10* instr) {
    // 0x108: Set bullet position (alternate mode, no pos update)
    // Just stores bullet sprite index, no position writeback
}

void EclVM::ins_SET_BULLET_POS_ABS(const EclInstr10* instr) {
    // 0x10E/0x10F: Set bullet position (absolute world coords, 3 params)
    // Position computed from: ABS_WORLD_X + param0, ABS_WORLD_Y + param1, param2 (Z)
    // Also reads 6 params total: x, y, z, slot, mode, flags
    // If 0x10F: gated on game_state == 0
}

// ========================================
// Movement: Enemy position handlers
// ========================================

void EclVM::ins_SET_ENEMY_POS(const EclInstr10* instr) {
    // 0x110: Set enemy position (world coords)
    // Reads 2 params: bullet_slot, anim_sprite_index
    // If no screen-space flag (0x40000), copies player position to sprite+0x340
    // Otherwise uses enemy position directly
}

void EclVM::ins_SET_ENEMY_POS_ROTATE(const EclInstr10* instr) {
    // 0x111: Set enemy position with rotation
    // Same as 0x110 but also sets Z rotation angle and ORs flag 4 at +0x35C
    // Reads float from param 2 for rotation angle
}

// ========================================
// Movement: Speed/acceleration handlers
// ========================================

void EclVM::ins_SET_SPEED_X(const EclInstr10* instr) {
    // 0x118 (speed X) / 0x11A (speed Y): Set speed component (instant)
    // 0x118 targets enemy+0x58; 0x11A targets enemy+0x84
    // Reads 2 float params: new_speed_value, new_speed_value2
    // Sets the target speed, clears interpolated-animation flag (bit 0)
    // After update: pos = inertia_pos + velocity_sum_of_components
}

void EclVM::ins_SET_SPEED_X_INTERP(const EclInstr10* instr) {
    // 0x119 (speed X interp) / 0x11B (speed Y interp): Set speed with interpolation
    // 0x119 targets +0x58→+0x13C interp struct; 0x11B targets +0x84→+0x188 interp struct
    // Reads 2 params: acceleration, target_speed
    // Sets up a SixElementFloat with bezier-style interpolation
    // Copies current speed values, then sets acceleration+tangent for smooth transition
}

void EclVM::ins_SET_ACCEL_X(const EclInstr10* instr) {
    // 0x11C (accel X) / 0x11E (accel Y): Set instantaneous acceleration
    // 0x11C targets enemy+0x58; 0x11E targets enemy+0x84
    // Reads 2 floats: accel_value, decel_value
    // If flag 0x800 set, applies an angle normalization
    // Calls FUN_00413170 (set_acceleration_direct) with accel value
    // Also sets deceleration value
    // Clears animation bit
}

void EclVM::ins_SET_ACCEL_X_INTERP(const EclInstr10* instr) {
    // 0x11D (accel X interp) / 0x11F (accel Y interp): Set acceleration with interpolation
    // 0x11D targets +0x58→+0x1D4 interp; 0x11F targets +0x84→+0x210 interp
    // Reads 2 params: accel_value, interpolate_mode
    // Sets up interpolated acceleration structure
    // If flag 0x800 set, normalizes angle
    // Copies current acceleration as base, sets new target with smooth lerp
}

// ========================================
// Movement: Angular speed handlers
// ========================================

void EclVM::ins_SET_ANGULAR_SPEED_X(const EclInstr10* instr) {
    // 0x120 (angular speed X) / 0x122 (angular speed Y): Set angular speed (instant)
    // 0x120 targets +0x58; 0x122 targets +0x84
    // Reads 4 floats: base_angle, angular_velocity, angular_accel, max_angle
    // If animation not running, copies current velocity as base
    // Sets up angular speed params directly (instant change)
    // ORs bit 1 (starts animation-driven movement)
}

void EclVM::ins_SET_ANGULAR_SPEED_X_IP(const EclInstr10* instr) {
    // 0x121 (angular speed X interp) / 0x123 (angular speed Y interp): Set angular speed (interpolated)
    // 0x121 targets +0x58→+0x1D4+0x24C dual-interp; 0x123 targets +0x84→+0x210+0x288
    // Reads 4 floats + 2 int params: base_angle, angular_vel, angular_accel, max_angle, duration, mode
    // Sets up TWO interpolated structures (for dual-axis interpolation)
    // Falls back to current values if params are zero/epsilon
    // Initializes interpolation with current→target values
    // ORs bit 1
}

// ========================================
// Movement: Aim handlers
// ========================================

void EclVM::ins_AIM_TO_PLAYER_X(const EclInstr10* instr) {
    // 0x124 (aim X to player) / 0x125 (aim Y to player): Aim towards player position
    // Computes angle based on player position relative to enemy
    // Uses atan2 to calculate the angle
    // Reads 2 params: speed, duration
    // Sets up an interpolated target angle aiming at the player
    // 0x124 uses move boundary rect (+0x13AC) for position clamping
    // 0x125 also uses boundary rect
}

void EclVM::ins_SET_SPEED_TO_PLAYER(const EclInstr10* instr) {
    // 0x127: Copy velocity to point at player position
    // Copies player world position (+0x1068) to enemy inertia velocity (+0x84/+0x88/+0x8C)
    // Makes enemy drift toward the player
}

// ========================================
// Movement: Add position / acceleration handlers
// ========================================

void EclVM::ins_ADD_POS(const EclInstr10* instr) {
    // 0x128 (add to X) / 0x129 (add to Y): Add offset to position
    // 0x128 targets +0x58 (X component); 0x129 targets +0x84 (Y component)
    // Reads 3 floats: dx, dy, dz — adds them to the positional accumulator
    // pos.x += dx; pos.y += dy; pos.z += dz;
}

void EclVM::ins_SET_ACCEL_DIRECT(const EclInstr10* instr) {
    // 0x12A (set accel X direct) / 0x12B (set accel Y direct, shares handler with 0x12A in boss mode)
    // 0x12A targets +0x58; 0x12B targets +0x84
    // Reads 2 floats: accel_x_value, accel_y_value
    // Sets acceleration directly (bypasses interpolation)
    // If boss mode (flag 0x800 set), applies normalization
}

// ========================================
// Enemy State handlers
// ========================================

void EclVM::ins_SET_HITBOX_WIDTH(const EclInstr10* instr) {
    // 0x140: Set enemy hitbox width
    // Reads 2 floats: half_width, half_height (collision rect half-extents)
    // Stores at enemy+0xB0 and enemy+0xB4
    float w = read_param_float(reinterpret_cast<const uint8_t*>(instr), 0);
    float h = read_param_float(reinterpret_cast<const uint8_t*>(instr), 1);
    hitbox_w_ = w;
    hitbox_h_ = h;
}

void EclVM::ins_SET_HITBOX_HEIGHT(const EclInstr10* instr) {
    // 0x141: Set enemy hurtbox width/height (damage box)
    // Reads 2 floats: half_hurtbox_w, half_hurtbox_h
    // Stores at enemy+0xB8 and enemy+0xBC
    float w = read_param_float(reinterpret_cast<const uint8_t*>(instr), 0);
    float h = read_param_float(reinterpret_cast<const uint8_t*>(instr), 1);
    hurtbox_w_ = w;
    hurtbox_h_ = h;
}

void EclVM::ins_SET_FLAGS(const EclInstr10* instr) {
    // 0x142: OR flags into enemy bitfield at +0x1444
    // Reads 1 int param: flag bits to set
    // flags_ |= param
    // If bit 0x10 set after operation, calls disable animations (10 times)
    uint32_t bits = static_cast<uint32_t>(read_param_int(reinterpret_cast<const uint8_t*>(instr), 0));
    flags_ |= bits;
}

void EclVM::ins_CLEAR_FLAGS(const EclInstr10* instr) {
    // 0x143: AND NOT flags from enemy bitfield at +0x1444
    // Reads 1 int param: flag bits to clear
    // flags_ &= ~param
    // If bit 0x10 cleared after operation, calls enable animations (10 times)
    uint32_t bits = static_cast<uint32_t>(read_param_int(reinterpret_cast<const uint8_t*>(instr), 0));
    flags_ &= ~bits;
}

void EclVM::ins_SET_MOVE_BOUNDARY(const EclInstr10* instr) {
    // 0x144: Set movement boundary rect (4 floats)
    // ORs flag 0x200 into enemy flags
    // Reads 4 floats: left, top, right, bottom
    // Stores at enemy+0x13AC (center_x), +0x13B0 (center_y),
    //                     +0x13B4 (half_width), +0x13B8 (half_height)
}

void EclVM::ins_CLEAR_MOVE_BOUNDARY(const EclInstr10* instr) {
    // 0x145: Clear movement boundary
    // AND NOT flag 0x200
    flags_ &= ~0x200U;
}

void EclVM::ins_RESET_BULLET_ARRAY(const EclInstr10* instr) {
    // 0x146: Reset bullet/option array (zero 12 DWORDs at enemy+0x13D0)
    // Clears the bullet slot assignments
}

void EclVM::ins_SET_DIFFICULTY_PARAM(const EclInstr10* instr) {
    // 0x147: Set difficulty-dependent parameter (12 slots)
    // Reads 2 params: slot_index, value
    // If boss mode (flags & 0x8000): slot 1 → 10, slot 4 → 11
    // Stores at enemy+0x13CC + slot * 4
}

void EclVM::ins_SET_RANGE_PARAMS(const EclInstr10* instr) {
    // 0x148: Set range parameters
    // Reads 2 floats: min_range, max_range
    // Stores at enemy+0x1400 and +0x1404
}

void EclVM::ins_BOSS_OPERATION(const EclInstr10* instr) {
    // 0x149: Multi-phase boss operations
    // Calls FUN_0040c9a0(boss_manager)
    // Handles boss phase transitions, health gates, spell card activation
}

void EclVM::ins_SET_ENEMY_TYPE(const EclInstr10* instr) {
    // 0x14A: Set enemy type/variant
    // Reads 1 int param: type_id
    // If boss mode (flags & 0x8000): type 1 → 10, type 4 → 11
    // Stores at enemy+0x13CC
}

void EclVM::ins_SET_SPELL_BONUS_TIME(const EclInstr10* instr) {
    // 0x14B: Set spell card bonus timer
    // Reads 1 int param: timer_value
    // Stores at enemy+0x13C0 and +0x13C4
    // Resets spell card tracking array (8 DWORDs at spell_manager+0x9E94)
    // Sets enemy+0x13C8 = enemy+0x13C0
}

void EclVM::ins_SET_ACTIVE_SUB(const EclInstr10* instr) {
    // 0x14C: Set active ECL subroutine
    // Reads 1 int param: sub_index
    // If sub_index < 0: clear current sub, clear flag 0x8000
    //   If boss mode also clear sub from sub_table
    // Else: OR flag 0x8000, set sub_table[sub_index] = enemy_ptr, store sub_index at +0x1450
}

void EclVM::ins_CALL_FUNC_NO_PARAM(const EclInstr10* instr) {
    // 0x14D: Call function by index (no parameter)
    // Calls FUN_00405410(0) — generic function call with no args
}

void EclVM::ins_STORE_INSTR_TABLE(const EclInstr10* instr) {
    // 0x14E: Store instruction table entry
    // Reads 3 params: key, value_type, table_index
    // Calls FUN_00412720(value_type, key, table_index) — stores in a lookup table
}

void EclVM::ins_CALL_FUNC_PARAM(const EclInstr10* instr) {
    // 0x14F/0x169: Call function by index (with parameter)
    // Reads 1 int param: function_index
    // Calls FUN_00405410(function_index)
}

void EclVM::ins_SCRIPT_END_RESET(const EclInstr10* instr) {
    // 0x150: Reset / call end of script
    // Reads 1 int param: mode
    // Calls FUN_0043dd10() — resets script execution state
}

void EclVM::ins_PLAY_SOUND(const EclInstr10* instr) {
    // 0x151: Play sound/music
    // Reads 4 params: sound_id, volume, channel, flags
    // Calls FUN_0043c8b0(1, sound_id, volume, channel, flags) to play audio
}

void EclVM::ins_HARD_RESET(const EclInstr10* instr) {
    // 0x152: Full enemy reset
    // Reads 1 int param: mode
    // Calls: CLEAR_BULLETS, STOP_SOUNDS(0), CLEAR_LASERS, REFRESH_BULLETS
    // Complete cleanup: bullets, sound effects, subroutines, lasers
}

void EclVM::ins_END_IF_BOSS_ACTIVE(const EclInstr10* instr) {
    // 0x153: End script if boss is active
    // Checks if boss_manager+0x9EB8 is non-null AND boss+0x78 == 0
    // If true: return -1 (terminate script execution)
    // This prevents normal enemies from running while a boss fight is active
}

void EclVM::ins_END_IF_CONDITION(const EclInstr10* instr) {
    // 0x154: End script if condition false
    // Checks if bullet_manager+0x10 (game state?) != 0
    // If true: return -1
}

void EclVM::ins_STORE_INSTR_PTR(const EclInstr10* instr) {
    // 0x155: Store instruction pointer at fixed offset
    // Reads 1 int param: slot_index
    // Stores (current_instr_ptr + 0x18) at instruction_table + slot_index * 0x10
    // This creates a jump/call table entry for later use
}

void EclVM::ins_SHOW_DIALOG(const EclInstr10* instr) {
    // 0x156/0x15C/0x165/0x166/0x167: Show dialog text
    // Dialog text is XOR-encrypted inline using key sequence (0x77, 0x7E, 0x8E, ...)
    // First param: text_length (int32), text follows as bytes at instr+0x20
    // XOR decrypt: for i in 0..len: text[i] ^= (0x77 + i*7 + i*(i-1)/2*16)
    // Additional params: dialog_id, display_mode
    // 0x165: dialog_id += stage_id
    // 0x166: dialog_id += stage_id - 1
    // 0x167: dialog_id += stage_id - 2
    // Calls FUN_00409280(dialog_manager, dialog_id, decrypted_text, display_mode)
}

void EclVM::ins_RUN_SUB_SCRIPT(const EclInstr10* instr) {
    // 0x157: Run ECL sub-script
    // Calls FUN_00409c00(param) — starts a child ECL sub-script execution
}

void EclVM::ins_SET_VALUE(const EclInstr10* instr) {
    // 0x158: Set value from param
    // Reads param 0 via alloc, then calls FUN_00412ed0(value) — stores in global slot
}

void EclVM::ins_REFRESH_BULLETS(const EclInstr10* instr) {
    // 0x159: Refresh bullet manager (cleanup dead bullets)
    // Calls FUN_0040e6a0(bullet_manager) — cleans up destroyed bullets
}

void EclVM::ins_SET_SQ_DIST_THRESHOLD(const EclInstr10* instr) {
    // 0x15A: Set square distance threshold
    // Reads 1 float param, squares it, stores at enemy+0x1454
    float dist = read_param_float(reinterpret_cast<const uint8_t*>(instr), 0);
    sq_dist_threshold_ = dist * dist;
}

void EclVM::ins_SET_SPELL_BONUS_PARAMS(const EclInstr10* instr) {
    // 0x15B: Set spell card bonus parameters
    // Reads 3 params: bonus_amount, timer_value, slot_index
    // Computes: bonus_per_frame = timer / base_time
    // Stores at spell_manager+0x9E94 + slot*8
}

// ========================================
// Random/Rank/Difficulty handlers
// ========================================

void EclVM::ins_GET_DIFF_RANDOM(const EclInstr10* instr) {
    // 0x15D: Get difficulty-scaled random float
    // If rank > 0x1FF: returns 2.0f
    // If rank < -0x1FF: returns 0.0f
    // Otherwise falls through to difficulty-dependent float lookup
}

void EclVM::ins_GET_DIFF_SCALED(const EclInstr10* instr) {
    // 0x15E: Get difficulty-scaled value (5 tiers)
    // Based on rank_value_:
    //   rank > 599:   returns 3.0f
    //   rank > 199:   returns 2.0f
    //   rank >= -199: returns 1.0f
    //   rank >= -399: returns 0.5f (1.0f in alternate path)
    //   rank < -399:  returns 0.0f
}

void EclVM::ins_GET_DIFF_INTERP(const EclInstr10* instr) {
    // 0x15F: Get linear-interpolated difficulty value
    // Returns: min_val + (max_val - min_val) * (rank + 512) / 1024
    // Interpolates between min (param0) and max (param1) based on rank
}

void EclVM::ins_GET_RANK_INT(const EclInstr10* instr) {
    // 0x160: Get rank-dependent int (2 tiers)
    // rank > 0x1FF: returns alloc_int(2)
    // rank <= 0x1FF: returns alloc_int(0)
}

void EclVM::ins_GET_RANK_INT_MULTI(const EclInstr10* instr) {
    // 0x161: Get rank-dependent int (5 tiers)
    // rank > 599:  returns alloc_int(4)
    // rank > 199:  returns alloc_int(3)
    // rank > -199: returns alloc_int(2)
    // rank > -399: returns alloc_int(1)
    // else:        returns alloc_int(0)
}

void EclVM::ins_GET_RANK_INTERP(const EclInstr10* instr) {
    // 0x162: Get interpolated rank int
    // Reads min_int from param via alloc_int(1), max_int from alloc_int(2)
    // Returns: min_int + ((max_int - min_int) * (rank + 1024)) >> 11
}

void EclVM::ins_GET_DIFF_PARAM_IDX(const EclInstr10* instr) {
    // 0x163: Get difficulty-dependent parameter by index
    // Uses stage_id_ (0-4 -> extra stages) to select multiplier:
    //   stage 0: 1, stage 1: 2, stage 2: 3, stage 3/4: 4
    // Reads params at those indices from the instruction
    // Returns the value stored at the selected difficulty slot
}

void EclVM::ins_GET_DIFF_FLOAT(const EclInstr10* instr) {
    // 0x164: Get difficulty-dependent float (5 tiers)
    // Uses stage_id_ to select:
    //   stage 0: 0.5f,   stage 1: 1.0f
    //   stage 2: 1.5f,   stage 3: 2.0f
    //   stage 4: 2.5f
}

// ========================================
// Script Control handlers
// ========================================

void EclVM::ins_STORE_GLOBAL_VALUE(const EclInstr10* instr) {
    // 0x168: Store value to global variable
    // Reads param 0 via alloc, stores at global_manager+0x9E90
}

void EclVM::ins_SET_GLOBAL_FLAG(const EclInstr10* instr) {
    // 0x16A: Set global flag
    // ORs bit 8 into global_manager+0x378C
}

void EclVM::ins_TOGGLE_FLAG_BIT(const EclInstr10* instr) {
    // 0x16C: XOR a flag bit at enemy+0x1444
    // Reads 1 int param: bit_position
    // flags_ ^= (param << 19) & 0x80000
}

void EclVM::ins_SET_SCRIPT_PARAMS(const EclInstr10* instr) {
    // 0x16E: Set per-script parameter values
    // Reads 2 int params from alloc: flag_value, script_param
    // Sets flag 0x100000 based on flag_value, clears flag 0x200000
    // Stores script_param at enemy+0x1448
    // Copies enemy+0xF4 to enemy+0x144C
}

void EclVM::ins_RESET_GLOBAL_FLOAT(const EclInstr10* instr) {
    // 0x16F: Reset a global float to 0
    // Sets global_float_0 (DAT_00476f78) = 0.0f
}

void EclVM::ins_SUBTRACT_GLOBAL_INT(const EclInstr10* instr) {
    // 0x170: Subtract global int from script time
    // Based on stage_id_ (0-3), reads a different global int
    // Subtracts that value from the instruction stream's time field pointer
    // Advances the script time counter
}

// ========================================
// Laser Operation handlers
// ========================================

void EclVM::ins_CREATE_LASER(const EclInstr10* instr) {
    // 0x190 (0x400 in enum): Create laser entry
    // Reads 1 int param: laser_slot
    // Allocates a 0x210-byte laser struct at enemy + laser_slot * 0x210 + 0x2C4
    // Zeroes 0x84 DWORDs of laser struct
    // Initializes defaults:
    //   +0x4B8: size_w = 1, +0x4BA: size_h = 1
    //   +0x2D4: angle = 0, +0x2DC: render_flag = 0x40000000
    //   +0x4C4: segment_count = 7, +0x4C8: segment_len = 0x18
    //   +0x4C0: control_flags = 0x203
    // Zeroes laser pos tracking: offset at +0x4D1 (+3 entries * 4 bytes) and +0x1348 (+12 bytes)
}

void EclVM::ins_SET_LASER_POS(const EclInstr10* instr) {
    // 0x191: Set laser position
    // Reads 1 int param: laser_slot
    // Computes position: laser_pos = enemy_pos + laser_offset[slot]
    // Assigns to laser struct at +0x2C8, +0x2CC, +0x2D0 (x,y,z)
    // If sq_dist_threshold_ != 0, checks distance from camera;
    // if outside threshold, calls laser_cull_func to hide laser
}

void EclVM::ins_SET_LASER_GRAPHIC_SIZE(const EclInstr10* instr) {
    // 0x192: Set laser graphic width/height
    // Reads 3 params: laser_slot, width, height
    // Stores int16 width/height at laser_struct +0x2C4 / +0x2C6
}

void EclVM::ins_SET_LASER_SPEED(const EclInstr10* instr) {
    // 0x193: Set laser speed (target velocity)
    // Reads 1 int param: laser_slot
    // Reads 2 floats: target_speed_x, target_speed_y (at offset +0x4D1 and +0x1348 in enemy)
    // Sets laser movement target velocity
}

void EclVM::ins_SET_LASER_ANGLE(const EclInstr10* instr) {
    // 0x194: Set laser angle/rotation
    // Reads 1 int param: laser_slot
    // Reads 2 floats: angle_radians, rotation_speed
    // Stores at laser_struct +0x2D4 / +0x2D8
}

void EclVM::ins_SET_LASER_DIMENSIONS(const EclInstr10* instr) {
    // 0x196: Set laser length/width dimensions
    // Reads 3 params: laser_slot, length, width
    // Stores at laser_struct +0x4B8 / +0x4BA
}

void EclVM::ins_SET_LASER_CONTROL(const EclInstr10* instr) {
    // 0x197: Set laser control value
    // Reads 2 params: laser_slot, control_value
    // Stores int16 at laser_struct +0x4BC
}

void EclVM::ins_SET_LASER_RENDER(const EclInstr10* instr) {
    // 0x198: Set laser render flags
    // Reads 3 params: laser_slot, render_type, color_mode
    // Stores at laser_struct +0x4C4 / +0x4C8
}

void EclVM::ins_SET_LASER_CONFIG(const EclInstr10* instr) {
    // 0x199: Set laser config (6 params)
    // Reads params: laser_slot, segment_index, value1, value2, value3, value4
    // Computes offset: (laser_slot * 0x16 + segment_index) * 0x18 + enemy_base
    // Stores at config struct: +0x2F8, +0x2F4, +0x2EC, +0x2F0, +0x2E4
    // Sets laser enable timer at calculated position
}

void EclVM::ins_CLEAR_BULLET_LIST(const EclInstr10* instr) {
    // 0x19A: Clear bullet list (index 1)
    // Calls stop_sounds(1) + clear_lasers()
    // Cleans up all active bullets and lasers
}

void EclVM::ins_COPY_LASER_DATA(const EclInstr10* instr) {
    // 0x19B: Copy laser data from source slot to dest slot
    // Reads 2 params: source_slot, dest_slot
    // Copies 0x84 DWORDs (0x210 bytes) from source laser struct to dest
}

// ========================================
// Bullet Property handlers
// ========================================

void EclVM::ins_CREATE_ENEMY_BULLET(const EclInstr10* instr) {
    // 0x19C / 0x1AF: Create enemy bullet
    // 0x19C: basic creation from local data
    // 0x1AF: copies 0x6C DWORDs from enemy+0x2E4 (previous bullet data) first
    // Reads params: bullet_sprite_id (int16), color (int16)
    // Computes bullet pos = enemy_pos + bullet_offset (enemy+0x1344)
    // Sets up bullet struct with: pos, sprite, color, speed, accel, hitbox, flags
    // Calls FUN_0041c510(0) to spawn
}

void EclVM::ins_CREATE_ENEMY_BULLET_EX(const EclInstr10* instr) {
    // 0x19D / 0x1B0: Create enemy bullet (extended)
    // 0x19D: basic extended creation (7 params + extra flags)
    // 0x1B0: copies 0x6C DWORDs from previous bullet data first
    // Sets default speed = 8.0f (0x41000000)
    // Reads params: bullet_sprite_id (int16), extra_flag1 (int16),
    //   accel (float), speed (float), angle_offset (float),
    //   param6, param7, param8, param9, param11
    // More params than 0x19C: includes angle, spawn interval, sound mode
    // Calls FUN_0041c510(1) to spawn, stores result
}

void EclVM::ins_SET_BULLET_SPEED(const EclInstr10* instr) {
    // 0x19E: Set bullet speed
    // Gets bullet from bullet_manager by alloc, reads 2 floats: vel_x, vel_y
    // Stores at bullet +0x24, +0x28
    // Sets bullet +0x2C = 0 (current position offset)
}

void EclVM::ins_SET_BULLET_ANGLE(const EclInstr10* instr) {
    // 0x19F: Set bullet angle/direction
    // Gets bullet, reads 2 floats: angle_x, angle_y
    // Stores at bullet +0x24, +0x28, sets +0x2C = 0
}

void EclVM::ins_SET_BULLET_ACCEL(const EclInstr10* instr) {
    // 0x1A0: Set bullet acceleration
    // Gets bullet, reads 1 float, stores at bullet +0x48
}

void EclVM::ins_SET_BULLET_HITBOX(const EclInstr10* instr) {
    // 0x1A1: Set bullet hitbox radius
    // Gets bullet, reads 1 float, stores at bullet +0x44
}

void EclVM::ins_SET_BULLET_SPACING(const EclInstr10* instr) {
    // 0x1A2: Set bullet spacing for patterns
    // Gets bullet, reads 1 float, stores at bullet +0x3C
}

void EclVM::ins_SET_BULLET_PARAM(const EclInstr10* instr) {
    // 0x1A3: Set bullet extra parameter
    // Gets bullet, reads 1 float, stores at bullet +0x440
}

// ========================================
// Bullet Firing Pattern handlers
// ========================================

void EclVM::ins_FIRE_BULLET_RING(const EclInstr10* instr) {
    // 0x1A4: Fire bullet ring (dense circular pattern)
    // Reads 1 float: ring_radius
    // Calls FUN_00408100(radius, 1, 0) — fire ring mode with is_ring=true
    // Then calls spawn_all_bullets()
}

void EclVM::ins_FIRE_BULLET_LINE(const EclInstr10* instr) {
    // 0x1A5: Fire bullet line
    // Reads 1 float: spread_width
    // Calls FUN_00408100(spread, 0, 0) — fire line mode with is_ring=false
    // Then calls spawn_all_bullets()
}

// ========================================
// No-op fallback
// ========================================

void EclVM::ins_noop(const EclInstr10* instr) {
    (void)instr;
    // Unknown/unimplemented opcodes fall through here
}

} // namespace th10
