#include <stdint.h>

struct IndexedRecord_00435fa0 {
    uint32_t limit;
    uint32_t first_counter;
    uint32_t second_counter;
};

extern "C" uint32_t data_0048f860; // selected record index
extern "C" IndexedRecord_00435fa0 data_00477858[];

// Retail 0x00435FA0..0x00435FC3 receives the selected index in EAX.
extern "C" void __cdecl InitializeIndexedRecord_00435fa0(uint32_t index) {
    data_0048f860 = index;
    IndexedRecord_00435fa0& record = data_00477858[index];
    record.limit = 0x2000;
    record.second_counter = 0;
    record.first_counter = 0;
}
