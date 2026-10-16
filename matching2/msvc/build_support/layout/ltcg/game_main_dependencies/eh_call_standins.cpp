// Compiler context only; never selected as recovered game code.
//
// Stand-ins for the three /EHsc callees GameMain2 calls. Their real bodies
// are recovered byte-exact in their own clusters, but GameMain2 needs the
// private whole-program conventions those bodies negotiate (receiver pushed,
// callee RET4; retail call sites at 0x00438C56/0x00438DAA/0x00438DF7), and
// this cluster cannot compile the real bodies: their complete unwind groups
// are exported by the clusters that own them.
//
// Shape (per the flex-params entry scan): the stand-ins never read their
// receiver before a call, so the entry scan never sees a receiver load and
// the receiver stays on the stack. The destructors tail-call on, passing the
// receiver through its own slot; the constructor only needs it for its
// implicit EAX result.
struct GameMainCalleeStandInState {
    unsigned char reserved_00[0x68];
    unsigned int counters[4];
};

// C++ linkage: a call the compiler must assume can throw.
void __stdcall GameMainCalleeStandIn_MayThrow(void* owner);

// A first call closes the entry block before the receiver is passed on, so
// the receiver never earns a register parameter.
static __forceinline void GameMainCalleeStandIn_Touch(GameMainCalleeStandInState* state) {
    GameMainCalleeStandIn_MayThrow(0);
    GameMainCalleeStandIn_MayThrow(state);
}

struct SprtCtrl {
    unsigned char storage[0x732460];
    __declspec(noinline) SprtCtrl();
};
struct AnimationManagerStorage {
    unsigned char storage[0x732460];
    __declspec(noinline) ~AnimationManagerStorage();
};
struct FuncCtrlDestroyView {
    unsigned char storage[0x48];
    __declspec(noinline) ~FuncCtrlDestroyView();
};

// The storage constructor: receiver on the stack, result in EAX, RET4.
#pragma code_seg(".text$01construct")
SprtCtrl::SprtCtrl() {
    GameMainCalleeStandIn_MayThrow(0);
}
#pragma code_seg()

// The storage destructor: receiver on the stack, RET4.
#pragma code_seg(".text$01dtor")
AnimationManagerStorage::~AnimationManagerStorage() {
    GameMainCalleeStandIn_Touch(reinterpret_cast<GameMainCalleeStandInState*>(this));
}
#pragma code_seg()

// The manager destructor: receiver on the stack, RET4.
#pragma code_seg(".text$00g05")
FuncCtrlDestroyView::~FuncCtrlDestroyView() {
    GameMainCalleeStandIn_Touch(reinterpret_cast<GameMainCalleeStandInState*>(this));
}
#pragma code_seg()
