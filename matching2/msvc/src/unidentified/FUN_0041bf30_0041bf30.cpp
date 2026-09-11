// 0x0041BF30. Doubly linked list node: the successor sits at +4 and the
// predecessor at +8. Removing the node splices it out and patches both
// neighbours, then reports success with a zero result.
struct RecoveryNode_0041bf30 {
    int reserved;
    RecoveryNode_0041bf30* next;
    RecoveryNode_0041bf30* prev;
    int Unlink();
};

int RecoveryNode_0041bf30::Unlink() {
    next->prev = prev;
    if (prev)
        prev->next = next;
    return 0;
}
