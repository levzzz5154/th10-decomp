// 0x0040C730 - reset one script record so it can run a new script.
//
// A record owns its script instance in place at +0x0008 and keeps the instance
// the interpreter walks in the +0x0004 cursor; the record's own link node at
// +0x1030 heads the chain of instances it drives, so the reset points the
// cursor and that node at the embedded instance and empties the chain behind it.
//
// The record is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// build_support/layout/ltcg/ecl_record_reset.json supplies that convention while
// keeping the recovered operation readable.

struct EclInstance;
struct EclRecord;

// One entry of the record's instance chain: the instance it names, then the
// chain links.  The record's own node is embedded at +0x1030.
struct EclInstanceNode {
    EclInstance* instance;        // +0x00
    EclInstanceNode* next;        // +0x04
    EclInstanceNode* prev;        // +0x08
};

// The 0x1024-byte interpreter state.  A record embeds one at +0x0008 and the
// interpreter reaches it through whichever cursor the record holds.
struct EclInstance {
    float timer;                           // +0x0000  compared with the instruction's time
    void* instruction;                     // +0x0004  instruction being run
    unsigned char unknown_008[0x1008 - 0x008];
    int scratch_cursor;                    // +0x1008  offset into the scratch area at +0x0008
    int unknown_100C;                      // +0x100C
    int name;                              // +0x1010  lookup key; -1 while unnamed
    EclRecord* owner;             // +0x1014  record this instance belongs to
    int unknown_1018;                      // +0x1018
    unsigned char mask;                    // +0x101C  copied into spawned children
    unsigned char unknown_101D[3];         // +0x101D
    unsigned int flags;                    // +0x1020  bit 0 is cleared by the reset
};

struct EclRecord {
    void* vtable;                          // +0x0000
    EclInstance* running;         // +0x0004  instance the interpreter is on
    EclInstance instance;         // +0x0008
    void* script;                          // +0x102C
    EclInstanceNode self;         // +0x1030

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01reset")
void EclRecord::Reset() {
    instance.timer = 0.0f;
    instance.instruction = 0;
    instance.flags &= ~1u;
    instance.owner = this;
    instance.name = -1;
    instance.unknown_1018 = 0;
    running = &instance;
    self.instance = &instance;
    self.next = 0;
    self.prev = 0;
}
#pragma code_seg()
