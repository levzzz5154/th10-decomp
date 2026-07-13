/*
 * TH10 Replay (.rpy) Format
 * Based on Ghidra RE of FUN_00433570
 *
 * Replay file: "th10_%02d.rpy" (8-char initials + date/time header)
 * Stores input keystrokes per frame, score, stage, difficulty, shot type.
 */
#pragma once
#include "th10/types.h"
#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace th10 {

#pragma pack(push, 1)
struct ReplayHeader {
    char       magic[4];         // "T10R" - Touhou 10 Replay
    uint32_t   version;          // 0x10
    char       initials[9];      // 8 chars + null
    uint32_t   score;            // final score
    uint32_t   date;             // packed DOS date (year-1980 << 9 | month << 5 | day)
    uint32_t   time;             // packed DOS time (hour << 11 | min << 5 | sec/2)
    uint8_t    difficulty;       // 0-4
    uint8_t    shot_type;        // 0-5
    uint8_t    stage;            // 0-7 (0-indexed, 7=all clear)
    uint8_t    unk1;
    uint32_t   frame_count;      // total frames recorded
    uint32_t   rng_seed;         // initial RNG seed
    uint32_t   checksum;         // simple checksum of input data
    uint32_t   version_ex;       // extended version (0x10)
};
#pragma pack(pop)
static_assert(sizeof(ReplayHeader) == 49, "ReplayHeader must be 49 bytes");

struct ReplayFrame {
    uint16_t  input_bits;    // pressed keys bitmask
    uint8_t   padding[2];    // alignment to 4 bytes
};

class ReplayRecorder {
public:
    ReplayRecorder() = default;

    void begin_recording(const char* initials, Difficulty diff,
                         ShotType shot, int stage);
    void record_frame(uint16_t input_bits);
    void set_score(uint32_t score) { score_ = score; }
    void end_recording();
    bool save_to_file(const char* path);
    bool save_to_slot(int slot);

    bool           is_recording() const { return recording_; }
    uint32_t       frame_count()  const { return static_cast<uint32_t>(frames_.size()); }
    uint32_t       score()        const { return score_; }
    const uint8_t* frame_data()   const { return reinterpret_cast<const uint8_t*>(frames_.data()); }
    size_t         frame_data_size() const { return frames_.size() * sizeof(ReplayFrame); }

private:
    bool             recording_ = false;
    ReplayHeader     header_{};
    uint32_t         score_ = 0;
    std::vector<ReplayFrame> frames_;
};

class ReplayPlayer {
public:
    ReplayPlayer() = default;

    bool load_from_file(const char* path);
    bool load_from_slot(int slot);
    void close();

    bool           is_loaded()     const { return loaded_; }
    bool           is_playing()    const { return playing_; }
    void           start_playback();
    void           stop_playback();
    uint16_t       get_input(int frame) const;
    uint16_t       current_input() const { return current_input_; }
    void           advance_frame() { current_frame_++; current_input_ = get_input(current_frame_); }

    const ReplayHeader& header()  const { return header_; }
    uint32_t       total_frames() const { return header_.frame_count; }
    int            current_frame() const { return current_frame_; }

    Difficulty     difficulty() const { return static_cast<Difficulty>(header_.difficulty); }
    ShotType       shot_type()  const { return static_cast<ShotType>(header_.shot_type); }

private:
    bool             loaded_ = false;
    bool             playing_ = false;
    ReplayHeader     header_{};
    std::vector<ReplayFrame> frames_;
    int              current_frame_ = 0;
    uint16_t         current_input_ = 0;
};

// Key bitmask defines (DIRECTINPUT-compatible bit positions)
inline constexpr uint16_t INPUT_SHOT    = 0x0001;
inline constexpr uint16_t INPUT_BOMB    = 0x0002;
inline constexpr uint16_t INPUT_FOCUS   = 0x0004;
inline constexpr uint16_t INPUT_UP      = 0x0010;
inline constexpr uint16_t INPUT_DOWN    = 0x0020;
inline constexpr uint16_t INPUT_LEFT    = 0x0040;
inline constexpr uint16_t INPUT_RIGHT   = 0x0080;
inline constexpr uint16_t INPUT_SKIP    = 0x0100;
inline constexpr uint16_t INPUT_MENU    = 0x0200;
inline constexpr uint16_t INPUT_CONFIRM = 0x1000;
inline constexpr uint16_t INPUT_CANCEL  = 0x2000;

uint16_t build_input_mask(const uint8_t* kb);

} // namespace th10
