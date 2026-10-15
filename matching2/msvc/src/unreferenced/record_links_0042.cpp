// Two leaves of one linked-record layout: 0x0042AAE0 initialises the record
// (clearing it and wiring the four tail links at +0x6274..+0x6280 to itself),
// 0x0042ABD0 unlinks its head/tail pair.  The initialiser receives its record in
// EDX (dead leading __fastcall slot) and the unlinker in EAX (member receiver).
struct RecordInit_0042aae0 {
    unsigned char data_000[0x5460];
    void* self_5460;                     // +0x5460
    unsigned char pad_5464[0xE10];
    void* link_6274;                     // +0x6274
    void* link_6278;                     // +0x6278
    void* link_627c;                     // +0x627C
    void* link_6280;                     // +0x6280
};
extern "C" __declspec(noinline) RecordInit_0042aae0* __fastcall
Init_0042aae0(void* unused, RecordInit_0042aae0* record);
#pragma code_seg(".text$01init")
RecordInit_0042aae0* __fastcall Init_0042aae0(void* unused, RecordInit_0042aae0* record) {
    (void)unused;
    memset(record, 0, sizeof(RecordInit_0042aae0));
    void** tail = &record->link_6274;
    tail[0] = (void*)((unsigned char*)record + 0x5464);
    record->self_5460 = record;
    tail[2] = 0;
    tail[3] = 0;
    tail[1] = record;
    return record;
}
#pragma code_seg()

struct RecordInit_0043bc20 {
    unsigned int flags_000;              // +0x000
    unsigned char pad_004[0x3C];
    unsigned int flags_040;              // +0x040
};
extern "C" __declspec(noinline) RecordInit_0043bc20* __fastcall
Init_0043bc20(void* unused, RecordInit_0043bc20* record);
#pragma code_seg(".text$05init2")
RecordInit_0043bc20* __fastcall Init_0043bc20(void* unused, RecordInit_0043bc20* record) {
    (void)unused;
    unsigned int* p = &record->flags_040;
    *p &= ~1u;
    memset(record, 0, sizeof(RecordInit_0043bc20));
    record->flags_000 |= 2u;
    return record;
}
#pragma code_seg()

struct ListNode_0042abd0 {
    unsigned char pad_000[4];
    ListNode_0042abd0* prev_004;         // +0x004
    ListNode_0042abd0* next_008;         // +0x008
};
struct ListHolder {
    unsigned char pad_000[0x627c];
    ListNode_0042abd0* head_627c;        // +0x627C
    ListNode_0042abd0* tail_6280;        // +0x6280
    __declspec(noinline) void Clear();
};
#pragma code_seg(".text$03unlink")
void ListHolder::Clear() {
    if (head_627c)
        head_627c->next_008 = tail_6280;
    if (tail_6280)
        tail_6280->prev_004 = head_627c;
    head_627c = 0;
    tail_6280 = 0;
}
#pragma code_seg()
