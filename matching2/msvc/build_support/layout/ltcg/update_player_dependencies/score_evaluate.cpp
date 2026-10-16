#include "th10/game/player_update_score.hpp"
#pragma code_seg(".text$090score")
int LaserManager3::CopyVectorAndEvaluate(const float* vector, float value,
                                                 int flag) {
    LaserListNode3* record = linked_head;
    vector_440 = *(const Vector38*)vector;
    int total = 0;
    while (record != 0) {
        LaserListNode3* next = record->next;
        if (record->type != 1) {
            total += record->Slot1C(vector, value, flag);
        }
        record = next;
    }
    return total;
}
#pragma code_seg()
