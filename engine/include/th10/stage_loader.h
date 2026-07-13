/*
 * TH10 Stage Loading System
 * Based on Ghidra RE of th10.exe
 *
 * StageEntry table at 0x00474788 (8 entries x 0x30 bytes)
 * Stage script VM executor at FUN_00415e90
 * Stage flow controller at FUN_0042cdf0
 */
#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

namespace th10 {

// ========================================
// GameMode enum (matches binary)
// ========================================
enum class GameMode : int32_t {
    MODE_TITLE        = 0,
    MODE_MENU         = 4,
    MODE_LOADING      = 7,
    MODE_STAGE_START  = 10,
    MODE_STAGE_PLAY   = 11,
    MODE_STAGE_CLEAR  = 12,
    MODE_BOSS         = 13,
    MODE_EXIT         = 14,
    MODE_CONTINUE     = 15,
    MODE_DEMO         = 16,
};

// ========================================
// StageEntry (0x30 bytes, at 0x00474788)
// Uses uint32_t offsets instead of pointers to match 32-bit binary layout
// ========================================
#pragma pack(push, 1)
struct StageEntry {
    int32_t  stageId;        // +0x00
    int32_t  stdPathOff;     // +0x04  offset to "stageXX.std"
    int32_t  anmPathOff;     // +0x08  offset to "stgenmXX.anm"
    int32_t  eclPathOff;     // +0x0C  offset to "stageXX.ecl"
    int32_t  bgmPath0Off;    // +0x10  offset to boss BGM path
    int32_t  bgmPath1Off;    // +0x14  offset to stage BGM path
    int32_t  msgPath0Off;    // +0x18  offset to dialogue path
    int32_t  msgPath1Off;    // +0x1C  offset to extra dialogue path
    int32_t  logoAnimOff;    // +0x20  offset to "stXXlogo.anm"
    int32_t  flags0;         // +0x24
    int32_t  flags1;         // +0x28  used for BGM switching
    int32_t  flags2;         // +0x2C
};
#pragma pack(pop)
static_assert(sizeof(StageEntry) == 0x30, "StageEntry must be 0x30 bytes");

// ========================================
// StdHeader: STD file format header
// ========================================
// STD file layout:
//   0x00: magic (int32) = 0x00100003
//   0x04: data[0x30] (48 bytes of stage config)
//   0x34: validation_bytes[6] (each must be < 2 or < 3)
#pragma pack(push, 1)
struct StdHeader {
    int32_t magic;                  // 0x00: 0x00100003
    uint8_t stage_config[0x30];     // 0x04: 48 bytes stage config
    uint8_t validation[6];          // 0x34: validation bytes
};
#pragma pack(pop)
static_assert(sizeof(StdHeader) == 0x3A, "StdHeader must be 0x3A (58) bytes");

// ========================================
// Stage script instruction (packed bytecode)
// ========================================
// Instruction format:
//   IP+0: opcode_slot (uint8)
//   IP+1: opcode       (uint8)
//   IP+2: size         (uint8)  data bytes that follow
//   IP+3: param1       (uint8)  general-purpose param
//   IP+4+: data[size]  (variable)
#pragma pack(push, 1)
struct StageScriptInstr {
    uint8_t  slot;      // +0x00
    uint8_t  opcode;    // +0x01
    uint8_t  size;      // +0x02
    uint8_t  param1;    // +0x03
    uint8_t  data[];    // +0x04
};
#pragma pack(pop)

// ========================================
// StageScriptOpcode enum (0x00-0x17, 24 opcodes)
// ========================================
enum class StageScriptOpcode : uint8_t {
    END           = 0x00,  // End stage / advance to next phase
    LOAD_ENEMY_1  = 0x01,  // Load enemy data from table 1
    LOAD_ENEMY_2  = 0x02,  // Load enemy data from table 2
    LOAD_ENEMY_3  = 0x03,  // Load enemy data from table 3
    FREE_ENEMY_1  = 0x04,  // Free enemy data slot 1
    FREE_ENEMY_2  = 0x05,  // Free enemy data slot 2
    FREE_ENEMY_3  = 0x06,  // Free enemy data slot 3
    SPAWN_1       = 0x07,  // Spawn enemies (variant 1) / start ECL script
    SPAWN_2       = 0x08,  // Spawn enemies (variant 2) / start ECL script
    TOGGLE_FLAG   = 0x09,  // XOR bit 1 on byte param
    CHECK_CLEAR   = 0x0A,  // Check if all enemies cleared -> advance
    WAIT          = 0x0B,  // Set delay counter
    BGM_TEMPO     = 0x0C,  // Set BGM tempo
    BGM_STAGE     = 0x0D,  // Set per-stage BGM parameters (8 subtypes)
    LOAD_ECL_1    = 0x0E,  // Load ECL script (variant 1)
    LOAD_ECL_2    = 0x0F,  // Load ECL script (variant 2)
    LOAD_ECL_3    = 0x10,  // Load ECL script (variant 3)
    CLEANUP       = 0x11,  // Clean up enemy data
    LOAD_BGM      = 0x12,  // Load stage BGM
    SET_ENEMY_DATA = 0x13, // Set enemy data per stage (7 subtypes)
    SCORE         = 0x14,  // Score display + stage advance (calls FUN_004175e0)
    BGM_FADEIN    = 0x15,  // Start BGM fade-in
    FREE_ECL_1    = 0x16,  // Free ECL script (variant 1)
    FREE_ECL_2    = 0x17,  // Free ECL script (variant 2)
};

// ========================================
// StageScriptVM: bytecode interpreter
// Run at FUN_00415e90 in original binary
// ========================================
class StageScriptVM {
public:
    StageScriptVM() = default;
    ~StageScriptVM() = default;

    // Load bytecode program
    void load(const uint8_t* data, size_t size);

    // Run the full bytecode program
    void execute();

    // Execute a single opcode at current IP
    void execute_opcode();

    // VM state accessors
    bool   running()       const { return running_; }
    size_t ip()            const { return ip_; }
    int32_t wait_counter() const { return wait_counter_; }

private:
    // All 24 opcode handlers
    void op_END();
    void op_LOAD_ENEMY_1();
    void op_LOAD_ENEMY_2();
    void op_LOAD_ENEMY_3();
    void op_FREE_ENEMY_1();
    void op_FREE_ENEMY_2();
    void op_FREE_ENEMY_3();
    void op_SPAWN_1();
    void op_SPAWN_2();
    void op_TOGGLE_FLAG();
    void op_CHECK_CLEAR();
    void op_WAIT();
    void op_BGM_TEMPO();
    void op_BGM_STAGE();
    void op_LOAD_ECL_1();
    void op_LOAD_ECL_2();
    void op_LOAD_ECL_3();
    void op_CLEANUP();
    void op_LOAD_BGM();
    void op_SET_ENEMY_DATA();
    void op_SCORE();
    void op_BGM_FADEIN();
    void op_FREE_ECL_1();
    void op_FREE_ECL_2();

    // Instruction access
    const StageScriptInstr* current_instr() const;

    const uint8_t* bytecode_  = nullptr;
    size_t         bytecode_size_ = 0;
    size_t         ip_            = 0;
    bool           running_       = false;
    int32_t        wait_counter_  = 0;
    int32_t        stage_id_      = 0;
    int32_t        game_mode_     = 0;
    bool           enemies_cleared_ = false;
};

// ========================================
// StageFlowController: manages stage phase state machine
// Original function: FUN_0042cdf0
// ========================================
class StageFlowController {
public:
    StageFlowController() = default;
    ~StageFlowController() = default;

    void init(StageScriptVM* vm);
    void update();

    // Phase state machine
    // Phase 0: Init (load BGM, setup)
    // Phase 1: In-game (main gameplay update)
    // Phase 2: Stage clear (results)
    // Phases 3-16: Various transitions
    void update_phase0();
    void update_phase1();
    void update_phase2();
    void update_phase_default();

    int32_t phase()       const { return phase_; }
    GameMode game_mode()  const { return game_mode_; }
    void set_game_mode(GameMode mode) { game_mode_ = mode; }

private:
    StageScriptVM* vm_        = nullptr;
    int32_t        phase_     = 0;
    GameMode       game_mode_ = GameMode::MODE_TITLE;
    int32_t        frame_counter_ = 0;
};

// ========================================
// Public API
// ========================================

// Initialize the global stage entry table with hardcoded paths.
// Table is at 0x00474788 in the original binary.
void InitStageTable(StageEntry* table);

// StageEntry string accessors (reinterpret int32_t offset as const char*)
const char* StageEntry_GetStdPath(const StageEntry* entry);
const char* StageEntry_GetAnmPath(const StageEntry* entry);
const char* StageEntry_GetEclPath(const StageEntry* entry);
const char* StageEntry_GetBgmPath0(const StageEntry* entry);
const char* StageEntry_GetBgmPath1(const StageEntry* entry);
const char* StageEntry_GetMsgPath0(const StageEntry* entry);
const char* StageEntry_GetMsgPath1(const StageEntry* entry);
const char* StageEntry_GetLogoAnimPath(const StageEntry* entry);

// Load and parse a STD file from raw data.
// Returns true if the magic matches and validation passes.
bool LoadStdFile(StdHeader* hdr, const uint8_t* data, size_t size);

// Maximum number of stage entries
inline constexpr int STAGE_ENTRY_COUNT = 8;

} // namespace th10
