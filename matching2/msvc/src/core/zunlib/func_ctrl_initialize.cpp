// Initializes the primary and secondary D3D resource lists.
// Native LTCG retains the private manager-in-EAX entry convention.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct FuncCtrlInitializeList {
    unsigned int reserved, flags;
    void* pendingFirst;
    void* pendingLast;
    void* pendingCursor;
    FuncCtrlInitializeList* owner;
    void* first;
    void* last;
    unsigned int unused;
};
struct FuncCtrlInitializeView {
    FuncCtrlInitializeList primary, secondary;
    __declspec(noinline) void Initialize();
};
#pragma code_seg(".text$01init")
void FuncCtrlInitializeView::Initialize() {
    unsigned int flags = primary.flags;
    primary.pendingFirst = 0;
    primary.pendingLast = 0;
    primary.pendingCursor = 0;
    primary.reserved = 0;
    // Finish clearing pending state before publishing the reset flags.
    _ReadWriteBarrier();
    primary.flags = flags & ~1u;
    FuncCtrlInitializeList* list = &secondary;
    primary.owner = &primary;
    primary.first = 0;
    primary.last = 0;
    // Keep each embedded list initialization as a separate compiler phase.
    _ReadWriteBarrier();
    list->flags &= ~1u;
    list->pendingFirst = 0;
    list->pendingLast = 0;
    list->pendingCursor = 0;
    list->reserved = 0;
    list->owner = list;
    list->first = 0;
    list->last = 0;
}
#pragma code_seg()
