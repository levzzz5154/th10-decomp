/*
 * th10_decomp - Touhou 10: Mountain of Faith Decompilation
 *
 * Core game types and structures based on reverse engineering.
 * Image base: 0x00400000, Entry: 0x004537DC
 */

#pragma once
#include <cstdint>
#include <cstddef>

namespace th10 {

// ========================================
// SixElementFloat (common ZUN math type)
// ========================================
struct SixElementFloat {
    float val1;  // usually position or base value
    float val2;  // usually velocity or delta
    float val3;  // usually acceleration
    float val4;
    float val5;
    float val6;
};

// ========================================
// 2D / 3D Vector types
// ========================================
struct Vec2f {
    float x, y;
};

struct Vec3f {
    float x, y, z;
};

struct Vec2i {
    int32_t x, y;
};

// ========================================
// Entity type identifiers (int32_t field)
// ========================================
enum class EntityType : int32_t {
    Bullet  = 0,
    Enemy   = 1,
    Player  = 2,
    Effect  = 3,
};

// ========================================
// Entity lifecycle state (int16_t field)
// ========================================
enum class EntityState : int16_t {
    Active  = 0,
    Death   = 1,
    Removed = 3,
};

// ========================================
// Render flags (uint32_t bitfield)
// ========================================
enum RenderFlag : uint32_t {
    RENDER_VISIBLE = 0x0000001,
    RENDER_KILL    = 0x4000000,
};

// ========================================
// GameStateManager flags
// ========================================
enum class GameState : uint8_t {
    Running = 3,
};

enum class D3dMode : uint8_t {
    PreInit = 1,
    Ready   = 2,
};

// ========================================
// Game configuration structure
// ========================================
struct GameConfig {
    // Match with th10.cfg layout
    uint8_t  pad1[0x20];
    uint32_t version;
    uint8_t  pad2[0x04];
    uint8_t  keymap[0x80];  // key bindings
    // ...
};
static_assert(sizeof(GameConfig) >= 0xA8);

// ========================================
// ANM06 Sprite Header (64 bytes)
// ========================================
struct AnmSprite {
    uint8_t  pad0[28];
    uint32_t name_offset;     // offset 28
    int32_t  x;               // offset 32
    int32_t  y;               // offset 36
    uint8_t  pad1[8];
    uint32_t texture_offset;  // offset 48
    uint16_t has_data;        // offset 52
    uint8_t  pad2[2];
    uint32_t next_offset;     // offset 56
    uint8_t  pad3[4];         // padding to 64
};
static_assert(sizeof(AnmSprite) == 64, "ANM06 sprite header must be 64 bytes");

// ========================================
// MSG10 Message Instruction
// ========================================
#pragma pack(push, 1)
struct MsgInstr {
    uint16_t time;
    uint8_t  opcode;
    uint8_t  length;
    uint8_t  data[];  // variable-length, padded to 4 bytes
};

// MSG10 opcodes
enum MsgOpcode : uint8_t {
    MSG_TEXT        = 16,  // 'm' - XOR-encrypted text with auto linebreak
    MSG_TEXT_ALT    = 17,  // 'm' - alternate text format
    MSG_VOICE_ID    = 9,   // 'S' - voice/sound ID
    MSG_FACE_EXPR   = 12,  // 'S' - character face expression
    MSG_DIALOG_START= 1,   // 'S'
    MSG_DIALOG_END  = 3,
    MSG_CLEAR       = 7,
    MSG_WAIT        = 10,  // 'S' - wait timer value
    MSG_NEW_PAGE    = 20,
    MSG_END         = 0,
};

// MSG10 file header
struct MsgFileHeader {
    uint32_t entry_count;
    // Followed by: int32_t offset_table[entry_count * 2]
    // Then: MsgInstr instructions
};
#pragma pack(pop)

// ========================================
// ECL (Enemy Control Language) structures (TH06-TH09 format)
// ========================================
#pragma pack(push, 1)
struct EclHeader {
    char     magic[4];        // "SCPT"
    uint32_t version_info;    // 0x00340001
    uint32_t sub_count;       // 36 subs
    uint32_t include_offset;  // 0 (actual ANIM at 36, sizeof header)
    uint32_t unk;             // 68 = ECLI pos
    uint32_t zero;            // padding
    uint32_t zero2[3];        // zero to fill 36 bytes
};
static_assert(sizeof(EclHeader) == 36);

struct EclListEntry {
    char     magic[4];        // "ANIM" or "ECLI"
    uint32_t count;
    uint8_t  data[];          // null-terminated strings
};

struct EclSubHeader {
    char     magic[4];        // "ECLH"
    uint32_t size;
    uint32_t zero[2];
    uint8_t  data[];
};

struct EclInstr {
    uint16_t time;
    uint16_t id;
    uint16_t size;
    uint16_t param_count;     // auto_end/auto_line related
    uint8_t  data[];
};
#pragma pack(pop)

// ========================================
// ECL TH10 instruction format (reversed from th10.exe @ 0x0040E770)
// ========================================
#pragma pack(push, 1)
struct EclInstr10 {
    int32_t  time;          // 0x00 - frames until execution
    int16_t  opcode;        // 0x04 - instruction opcode (0x100-0x1b4)
    int16_t  size;          // 0x06 - instruction byte size (0x14 + params*4)
    int32_t  param_mask;    // 0x08 - bitmask: 1=float, 0=int per param
    int32_t  rank_mask;     // 0x0C - rank/difficulty gate mask
    int32_t  param_count;   // 0x10 - number of parameter int32s that follow
    // 0x14+: int32_t params[param_count] (floats stored as int32_t)
};
#pragma pack(pop)

// ========================================
// SHT (Shot Data) structure
// ========================================
struct ShotData {
    uint32_t count;    // number of sub-shot entries
    // Followed by float arrays (positions, velocities, sizes)
    // Each sub-shot defines: pos_x, pos_y, hitbox, damage, etc.
};

// ========================================
// STD (Stage Definition) structure
// ========================================
struct StageDef {
    uint32_t unk1;
    uint32_t unk2;
    uint32_t stage_anm_offset;   // offset to "stageXX.anm"
    uint32_t stage_data_offset;  // offset to other data
    // Followed by filename strings
};

// ========================================
// DAT Archive structures
// ========================================
#pragma pack(push, 1)
struct DatArchiveHeader {
    uint32_t count;
    uint32_t offset;
    uint32_t size;
};

struct DatEntryHeader {
    uint8_t  name[260];
    uint32_t extra;
    int32_t  size;      // uncompressed
    int32_t  zsize;     // compressed
    int32_t  offset;    // in archive
};

// Encryption params per file type
struct CryptParams {
    uint8_t  type;     // 'M'=msg, 'A'=anm, 'E'=ecl, 'W'=wav, etc.
    uint8_t  key;
    uint8_t  step;
    uint32_t block;
    uint32_t limit;
};

extern const CryptParams th10_crypt_params[];
extern const size_t     th10_crypt_params_count;
#pragma pack(pop)

// ========================================
// Game Constants
// ========================================
inline constexpr int GAME_WIDTH   = 640;
inline constexpr int GAME_HEIGHT  = 480;
inline constexpr int GAME_FPS     = 60;
inline constexpr float GAME_DT    = 1.0f / 60.0f;

inline constexpr int ENTITY_POOL1_SIZE = 4096;
inline constexpr int ENTITY_POOL2_SIZE = 20;

// Player shot types
enum class ShotType : uint8_t {
    ReimuA = 0,  // Persuasion Needle
    ReimuB = 1,  // Exorcism Rod
    ReimuC = 2,  // Youkai Buster
    MarisaA = 3, // Magic Missile
    MarisaB = 4, // Cold Inferno
    MarisaC = 5, // Asteroid Belt
};

// Difficulty
enum class Difficulty : uint8_t {
    Easy    = 0,
    Normal  = 1,
    Hard    = 2,
    Lunatic = 3,
    Extra   = 4,
};

// Stage
enum class Stage : uint8_t {
    Stage1 = 0,
    Stage2 = 1,
    Stage3 = 2,
    Stage4 = 3,
    Stage5 = 4,
    Stage6 = 5,
    Extra  = 6,
    AllClear = 7,
};

} // namespace th10
