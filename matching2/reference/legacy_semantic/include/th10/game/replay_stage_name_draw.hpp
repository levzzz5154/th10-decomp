#pragma once
#include "th10/game/replay_score_draw.hpp"
struct ReplayStageNamePage{int state,selection;bool fade_rows;int page;char name[16];int name_cursor,charset_cursor;};
struct ReplayStageNameEnv{ReplayScoreDrawState*render;const ReplayScoreEntry*entries;int replay_group;int difficulty_group;const char*charset;const char*const*difficulty_labels;ReplayScoreDate(*decode_time)(long);void(*draw_text)(const ReplayScoreDrawState*,const char*);};
int ReplayStageName_Draw(const ReplayStageNamePage*,const ReplayStageNameEnv*);
