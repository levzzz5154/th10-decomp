// 0x0040D510: suspend the enemy manager (the ECL viewer calls it): set
// bit 1 of both of its scheduler tasks' flag words.
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct EnemyCtrl {
    unsigned char pad_000[0x08];
    Flagged* first;
    Flagged* second;
};

void __declspec(noinline) EnemyCtrl_SuspendTasks(EnemyCtrl* object);
#pragma code_seg(".text$01accessor")
void EnemyCtrl_SuspendTasks(EnemyCtrl* object) {
    if (object->first) {
        object->first->flags |= 2u;
    }
    if (object->second) {
        object->second->flags |= 2u;
    }
}
#pragma code_seg()
