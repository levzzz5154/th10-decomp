#ifndef TH10_STAGE_ECL_LOAD_00403850_HPP
#define TH10_STAGE_ECL_LOAD_00403850_HPP
struct StageEclFile_00403850 {
    short sub_count, instance_count;
    unsigned int timeline_offset, auxiliary_offset;
    char reserved_0c[4];
    char animation_name[0x80];
    unsigned int sub_offsets[1];
};
struct StageEclLoader_00403850 {
    char reserved_0000[0x10];
    StageEclFile_00403850* file;
    unsigned int* subroutines;
    char* timeline;
    char* auxiliary;
    char reserved_0020[0x178 - 0x20];
    void* animation;
    void* instances;
    char reserved_0180[0x2A30 - 0x180];
    unsigned int flags;
    char reserved_2a34[0x2A44 - 0x2A34];
    char* original;
    int file_size;
    __declspec(noinline) int Load(const char* name);
};
#endif
