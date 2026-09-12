#pragma once

struct ScoreCleanupNode {
    void* object;
    void* reserved;
    ScoreCleanupNode* next;
    int state;
};

struct ScoreCleanupList {
    ScoreCleanupNode* first;
};

typedef void (*ScoreCleanupHook)(ScoreCleanupNode* node);

// Visit every live node, caching next before dispatch so callbacks may unlink
// the current node. Nodes in state 1 are deliberately skipped.
int ScoreCleanup_Dispatch(ScoreCleanupList* list, ScoreCleanupHook cleanup);
