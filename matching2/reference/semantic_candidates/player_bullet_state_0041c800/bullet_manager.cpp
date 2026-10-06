// Complete retail manager operations at 0x41C800 and 0x41C850.
#include "bullet_manager.hpp"
#pragma code_seg(".text$e00bulletevaluate")
int PlayerBulletManager::Evaluate(const Vec3* point, float radius, int mode) {
    PlayerBullet* record = first;
    evaluation_point = *point;
    int total = 0;
    while (record) {
        PlayerBullet* next = record->next;
        if (record->state != 1) total += record->Evaluate(point, radius, mode);
        record = next;
    }
    return total;
}
#pragma code_seg(".text$e10bulletreset")
int PlayerBulletManager::Reset(int mode) {
    PlayerBullet* record = first;
    while (record) {
        PlayerBullet* next = record->next;
        if (record->state != 1) record->Retire(mode);
        record = next;
    }
    return 1;
}
#pragma code_seg()
