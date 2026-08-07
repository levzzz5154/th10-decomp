#pragma once

#include "th10/game/stage_tips.hpp"
#include "th10/platform/pack_file_loader.hpp"

// Retail 0x00419960: parse the stage-tips text file and populate the stage-tip
// manager's per-stage chains.  The file is a sequence of `key: value` lines:
// a required `Version: 0.0` header (any other version clears the manager and
// aborts), `Stage: N` / `StageEnd` block delimiters (N in 1..7), and `Tips:`
// blocks whose `Pos` / `Text` / `Count` / `Time` / `Base` / `Align` /
// `Remain` / `Scale` / `Color` / `Alpha` / `End` property lines describe one
// tip record each.
//
// `suppress_duplicate` mirrors retail argument 3: when zero, every parsed tip
// is also copied into the manager's second per-stage chain (lists[stage + 8]).
//
// Returns 0 on success and on version mismatch (after clearing the manager),
// or -1 when the file cannot be opened.
int ParseStageTips(StageTipManager* manager, const char* filename,
                   int suppress_duplicate, const PackFileTable* table,
                   const PackFileHooks* hooks);
