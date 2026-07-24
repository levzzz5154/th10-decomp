#pragma once

// Six score-row draw with selection blink (retail 0x00431410).
// Retail function 0x00431410.
struct ScoreMenuRow{const char*name;int available,score_units;};struct ScoreMenu{int state,selection,timer;ScoreMenuRow rows[6];};struct ScoreMenuEnv{unsigned*text_color;int*list_printing;void(*draw_text)(const char*);};int ScoreMenu_DrawRows(const ScoreMenu*,const ScoreMenuEnv*);
