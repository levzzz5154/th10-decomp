#include "th10/game/player_update_score.hpp"
#pragma code_seg(".text$090score")
int LaserManager_0041c800::CopyVectorAndEvaluate(const float* vector, float value,
                                                 int flag) {
    LaserListNode_0041c800* record = linked_head;
    vector_440 = *(const Vector3_0041c800*)vector;
    int total = 0;
    while (record != 0) {
        LaserListNode_0041c800* next = record->next;
        if (record->type != 1) {
            total += record->Slot1C(vector, value, flag);
        }
        record = next;
    }
    return total;
}
#pragma code_seg()
