#include <stdint.h>

struct CxxExceptionRecord_00462f4c {
    uint32_t code;
    uint32_t flags;
    void* nested_record;
    void* address;
    uint32_t parameter_count;
    uint32_t magic;
    void* object;
    void* throw_information;
};

// Retail 0x00462F4C..0x00462F7B receives the record slot in EAX.
extern "C" int __cdecl IsCxxExceptionRecordWithoutThrowInfo_00462f4c(
    const CxxExceptionRecord_00462f4c* const* record_slot) {
    const CxxExceptionRecord_00462f4c* record = *record_slot;
    return record->code == 0xE06D7363u &&
           record->parameter_count == 3 &&
           (record->magic == 0x19930520u ||
            record->magic == 0x19930521u) &&
           record->throw_information == 0;
}
