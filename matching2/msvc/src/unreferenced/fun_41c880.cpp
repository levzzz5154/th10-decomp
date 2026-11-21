#include "../../build_support/include/asm_symbols.hpp"

// 0x0041C880..0x0041C8B5: walk linked records and sum virtual results.
struct CountArgument {
    int value;
};

struct ScoreLinkedRecord2 {
    virtual int Slot00();
    virtual int Slot04();
    virtual int Slot08();
    virtual int Slot0C();
    virtual int Slot10();
    virtual int Slot14();
    virtual int Slot18();
    virtual int Slot1C();
    virtual int Slot20(int first, CountArgument second);

    unsigned char reserved_004[4];
    ScoreLinkedRecord2 *next;
    int type;
};

struct ScoreRecords2 {
    unsigned char reserved_000[0x18];
    ScoreLinkedRecord2 *linked_head;
};

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) int __stdcall asm_FUN_0041c880_0041c880(
        ScoreRecords2 *records, int first,
        CountArgument second) {
    ScoreLinkedRecord2 *record = records->linked_head;
    int total = 0;
    while (record != 0) {
        ScoreLinkedRecord2 *next = record->next;
        if (record->type != 1)
            total += record->Slot20(first, second);
        record = next;
    }
    return total;
}
#pragma code_seg()
