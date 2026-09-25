#include "asm_symbols.hpp"

// Retail CRT helper at 0x00454479.  It releases an empty 32 KiB small-block
// heap region and removes its descriptor when the containing group is empty.
struct SbhRegionGroup_00454479 {
    unsigned int class_bitmap_low;
    unsigned int class_bitmap_high;
    unsigned int available_regions;
    unsigned char* region_base;
    unsigned char* region_metadata;
};

typedef int (__stdcall *VirtualFree_00454479)(
    void* address, unsigned int size, unsigned int free_type);
typedef int (__stdcall *HeapFree_00454479)(
    void* heap, unsigned int flags, void* memory);

extern "C" void __cdecl asm_unassigned_00454479(void) {
    SbhRegionGroup_00454479* group =
        *reinterpret_cast<SbhRegionGroup_00454479**>(&data_00499324);
    if (group == 0) {
        return;
    }

    const unsigned int region_index =
        *reinterpret_cast<unsigned int*>(&data_0049933c);
    const unsigned int region_bit = 0x80000000u >> (region_index & 31u);

    VirtualFree_00454479 virtual_free =
        *reinterpret_cast<VirtualFree_00454479*>(&data_00466188);
    virtual_free(group->region_base + (region_index << 15), 0x8000, 0x4000);

    group->available_regions |= region_bit;
    *reinterpret_cast<unsigned int*>(
        group->region_metadata + 0xc4 + region_index * sizeof(unsigned int)) = 0;

    unsigned char* active_region_count = group->region_metadata + 0x43;
    --*active_region_count;
    if (*active_region_count == 0) {
        group->class_bitmap_high &= ~1u;
    }

    unsigned int& descriptor_count =
        *reinterpret_cast<unsigned int*>(&data_00499328);
    if (group->available_regions == 0xffffffffu && descriptor_count > 1) {
        HeapFree_00454479 heap_free =
            *reinterpret_cast<HeapFree_00454479*>(&data_004661e8);
        void* heap = *reinterpret_cast<void**>(&data_00499340);
        heap_free(heap, 0, group->region_metadata);

        SbhRegionGroup_00454479* descriptor_table =
            *reinterpret_cast<SbhRegionGroup_00454479**>(&data_0049932c);
        const unsigned int group_index =
            static_cast<unsigned int>(group - descriptor_table);
        const unsigned int descriptors_after =
            descriptor_count - group_index - 1;
        asm_memmove_00453280(group, group + 1,
                    descriptors_after * sizeof(SbhRegionGroup_00454479));
        --descriptor_count;
    }

    *reinterpret_cast<SbhRegionGroup_00454479**>(&data_00499324) = 0;
}
