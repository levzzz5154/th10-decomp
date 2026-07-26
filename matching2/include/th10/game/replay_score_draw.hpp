#pragma once

// Replay-score detail renderer (retail 0x004329F0, 704 bytes).
struct ReplayScoreDate { int year, month, day, hour, minute; };
struct ReplayScoreEntry {
    const char* name;
    int score;
    signed char difficulty;
    signed char stage;
    long timestamp;
    float clear_percent;
};
struct ReplayScorePage {
    int state;                 // retail +0x20; only state 2 draws
    int difficulty;            // +0x24
    int page;                  // +0xfc, selects ten entries
    int suppress_entries;      // +0x1d4
};
struct ReplayScoreData {
    const ReplayScoreEntry* entries; // pages are ten contiguous entries
    int current_score[4];
    int elapsed_seconds[4];
    const int* stage_scores[4];
};
struct ReplayScoreDrawState { float x, y, z; unsigned color; int busy; };
struct ReplayScoreDrawEnv {
    ReplayScoreDrawState* render;
    const ReplayScoreData* data;
    const char* const* difficulty_labels;
    ReplayScoreDate (*decode_time)(long timestamp);
    void (*draw_text)(const ReplayScoreDrawState* state, const char* text);
};
int ReplayScore_Draw(const ReplayScorePage* page, const ReplayScoreDrawEnv* env);
