#include "th10/game/score_cleanup.hpp"

// 0x0041C850 - Walk the manager's cleanup chain. Retail follows the pointer at
// node+0x08 before invoking vtable slot +0x14, making removal of the current
// node safe, and suppresses dispatch for nodes whose state word equals one.
int ScoreCleanup_Dispatch(ScoreCleanupList* list, ScoreCleanupHook cleanup) {
    ScoreCleanupNode* node = list->first;
    while (node != 0) {
        ScoreCleanupNode* next = node->next;
        if (node->state != 1) {
            cleanup(node);
        }
        node = next;
    }
    return 1;
}
