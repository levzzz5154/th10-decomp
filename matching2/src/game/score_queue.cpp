#include "th10/game/score_queue.hpp"

// 0x0041C510 - Push one popup onto the score queue. Retail keeps the
// manager in ESI (queue fields at +0x434/+0x438/+0x43C) and picks the
// constructor by the kind argument; the appended node stores the id at
// word 0x15, points its prev word at the old tail, and is chained
// through the old tail's next word before the virtual attach hook runs.
uint32_t ScoreQueue_Push(ScorePopupQueue* queue, int32_t kind,
                         void* (*allocate)(uint32_t size),
                         ScorePopupNode* (*construct_plain)(void* memory),
                         ScorePopupNode* (*construct_view)(void* memory),
                         void (*on_attached)(ScorePopupNode* node)) {
    if (queue->count > 0xFF) {
        return 0;
    }
    queue->next_id += 1;
    if (queue->next_id == 0) {
        queue->next_id = 1;
    }

    ScorePopupNode* node = 0;
    if (kind == 0) {
        void* memory = allocate != 0 ? allocate(0xD58) : 0;
        node = memory != 0 && construct_plain != 0 ? construct_plain(memory)
                                                   : (ScorePopupNode*)0;
    } else if (kind == 1) {
        void* memory = allocate != 0 ? allocate(0xD74) : 0;
        node = memory != 0 && construct_view != 0 ? construct_view(memory)
                                                  : (ScorePopupNode*)0;
    } else {
        return (uint32_t)queue->next_id;
    }

    if (node != 0) {
        node->id = (uint32_t)queue->next_id;
        node->prev = queue->tail;
        queue->tail->next = node;
        queue->count += 1;
        queue->tail = node;
        if (on_attached != 0) {
            on_attached(node);
        }
    }
    return (uint32_t)queue->next_id;
}
