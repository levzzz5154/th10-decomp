#include "th10/replay.h"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <SDL2/SDL.h>

namespace th10 {

// ============================================================
//  Input mask builder
// ============================================================

uint16_t build_input_mask(const uint8_t* kb) {
    uint16_t mask = 0;
    if (kb[SDL_SCANCODE_Z] || kb[SDL_SCANCODE_SPACE]) mask |= INPUT_SHOT;
    if (kb[SDL_SCANCODE_X])                           mask |= INPUT_BOMB;
    if (kb[SDL_SCANCODE_LSHIFT] || kb[SDL_SCANCODE_RSHIFT]) mask |= INPUT_FOCUS;
    if (kb[SDL_SCANCODE_UP]    || kb[SDL_SCANCODE_W]) mask |= INPUT_UP;
    if (kb[SDL_SCANCODE_DOWN]  || kb[SDL_SCANCODE_S]) mask |= INPUT_DOWN;
    if (kb[SDL_SCANCODE_LEFT]  || kb[SDL_SCANCODE_A]) mask |= INPUT_LEFT;
    if (kb[SDL_SCANCODE_RIGHT] || kb[SDL_SCANCODE_D]) mask |= INPUT_RIGHT;
    if (kb[SDL_SCANCODE_LCTRL] || kb[SDL_SCANCODE_RCTRL]) mask |= INPUT_SKIP;
    if (kb[SDL_SCANCODE_ESCAPE])                       mask |= INPUT_MENU;
    if (kb[SDL_SCANCODE_RETURN] || kb[SDL_SCANCODE_Z]) mask |= INPUT_CONFIRM;
    if (kb[SDL_SCANCODE_ESCAPE] || kb[SDL_SCANCODE_X]) mask |= INPUT_CANCEL;
    return mask;
}

// ============================================================
//  ReplayRecorder
// ============================================================

void ReplayRecorder::begin_recording(const char* initials, Difficulty diff,
                                     ShotType shot, int stage) {
    frames_.clear();
    frames_.reserve(60 * 60 * 5); // ~5 minutes at 60fps

    memset(&header_, 0, sizeof(header_));
    memcpy(header_.magic, "T10R", 4);
    header_.version = 0x10;
    strncpy(header_.initials, initials, 8);
    header_.initials[8] = '\0';

    time_t now = time(nullptr);
    struct tm* tm_info = localtime(&now);
    header_.date = static_cast<uint32_t>(
        ((tm_info->tm_year + 1900 - 1980) << 9) |
        ((tm_info->tm_mon + 1) << 5) |
        tm_info->tm_mday);
    header_.time = static_cast<uint32_t>(
        (tm_info->tm_hour << 11) |
        (tm_info->tm_min << 5) |
        (tm_info->tm_sec / 2));

    header_.difficulty = static_cast<uint8_t>(diff);
    header_.shot_type  = static_cast<uint8_t>(shot);
    header_.stage      = static_cast<uint8_t>(stage);
    header_.rng_seed   = static_cast<uint32_t>(now & 0xFFFFFFFF);

    score_ = 0;
    recording_ = true;
}

void ReplayRecorder::record_frame(uint16_t input_bits) {
    if (!recording_) return;
    ReplayFrame f;
    f.input_bits = input_bits;
    f.padding[0] = 0;
    f.padding[1] = 0;
    frames_.push_back(f);
}

void ReplayRecorder::end_recording() {
    if (!recording_) return;
    header_.frame_count = static_cast<uint32_t>(frames_.size());
    header_.score = score_;

    // Compute simple checksum
    uint32_t csum = 0;
    for (auto& f : frames_) {
        csum += f.input_bits;
    }
    header_.checksum = csum;

    recording_ = false;
}

bool ReplayRecorder::save_to_file(const char* path) {
    if (frames_.empty()) return false;

    FILE* f = fopen(path, "wb");
    if (!f) return false;

    fwrite(&header_, sizeof(header_), 1, f);
    fwrite(frames_.data(), sizeof(ReplayFrame), frames_.size(), f);
    fclose(f);
    return true;
}

bool ReplayRecorder::save_to_slot(int slot) {
    if (slot < 0 || slot >= 99) return false;
    char path[512];
    snprintf(path, sizeof(path), "th10_%02d.rpy", slot);
    return save_to_file(path);
}

// ============================================================
//  ReplayPlayer
// ============================================================

bool ReplayPlayer::load_from_file(const char* path) {
    close();

    FILE* f = fopen(path, "rb");
    if (!f) return false;

    if (fread(&header_, sizeof(header_), 1, f) != 1) {
        fclose(f);
        return false;
    }

    // Validate magic
    if (memcmp(header_.magic, "T10R", 4) != 0) {
        fclose(f);
        return false;
    }

    size_t frame_bytes = header_.frame_count * sizeof(ReplayFrame);
    frames_.resize(header_.frame_count);

    if (fread(frames_.data(), sizeof(ReplayFrame), header_.frame_count, f)
        != header_.frame_count) {
        fclose(f);
        return false;
    }

    fclose(f);
    loaded_ = true;
    return true;
}

bool ReplayPlayer::load_from_slot(int slot) {
    if (slot < 0 || slot >= 99) return false;
    char path[512];
    snprintf(path, sizeof(path), "th10_%02d.rpy", slot);
    return load_from_file(path);
}

void ReplayPlayer::close() {
    loaded_ = false;
    playing_ = false;
    frames_.clear();
    current_frame_ = 0;
    current_input_ = 0;
    memset(&header_, 0, sizeof(header_));
}

void ReplayPlayer::start_playback() {
    if (!loaded_) return;
    playing_ = true;
    current_frame_ = 0;
    current_input_ = frames_.empty() ? 0 : frames_[0].input_bits;
}

void ReplayPlayer::stop_playback() {
    playing_ = false;
}

uint16_t ReplayPlayer::get_input(int frame) const {
    if (frame < 0 || frame >= static_cast<int>(frames_.size())) return 0;
    return frames_[frame].input_bits;
}

} // namespace th10
