// 0x0040D510: suspend the enemy manager (the sprite viewer calls it): set
// bit 1 of both of its scheduler tasks' flag words.
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_0040d510 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct EnemyManagerTasks {
    unsigned char pad_000[0x08];
    Flagged_0040d510* first;
    Flagged_0040d510* second;
};

void __declspec(noinline) EnemyManager_SuspendTasks(EnemyManagerTasks* object);
#pragma code_seg(".text$01accessor")
void EnemyManager_SuspendTasks(EnemyManagerTasks* object) {
    if (object->first) {
        object->first->flags |= 2u;
    }
    if (object->second) {
        object->second->flags |= 2u;
    }
}
#pragma code_seg()
