// 0x0040C810: the second slot of the enemy control info vtable (0x0046D0F0,
// "EnemyCtrlInf"); constant leaf: the query always reports failure, whatever the
// caller passes.
int __stdcall EnemyControlInfo_Query(int a1) {
    return 0;
}
