// 0x0040CC70: EnemyData_Construct
#include "th10/source_views/bullet_99a1d5_0.hpp"
ClearAnimsOwner* __fastcall EnemyData_Construct(int unused, ClearAnimsOwner* owner) {
    ClearActiveFlag(&owner->flag_12C);
    ClearActiveFlag(&owner->flag_17C);
    ClearActiveFlag(&owner->flag_1C8);
    ClearActiveFlag(&owner->flag_204);
    ClearActiveFlag(&owner->flag_240);
    ClearActiveFlag(&owner->flag_27C);
    ClearActiveFlag(&owner->flag_2B8);
    AnimSlot* slot = owner->slots;
    for (int i = 0; i < 8; ++i) {
        memset(slot, 0, 0x210);
        slot->field_204 = -1;
        ++slot;
    }
    ClearActiveFlag(&owner->flag_142C);
    ClearActiveFlag(&owner->flag_1440);
    return owner;
}
