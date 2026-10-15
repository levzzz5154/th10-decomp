#define data_00491c10 stage_requests_data_00491c10
#define data_0047770c stage_requests_data_0047770c
#define data_00474c40 stage_requests_data_00474c40
#define data_004776e0 stage_requests_data_004776e0
#define data_00477704 stage_requests_data_00477704
#define g_player stage_requests_data_00477834
#define data_00477838 stage_requests_data_00477838
#define data_0047783c stage_requests_data_0047783c
#define data_00476f78 stage_requests_data_00476f78
#define data_00491fc4 stage_requests_data_00491fc4
#define data_00491fb8 stage_requests_data_00491fb8
#define data_00492590 stage_requests_data_00492590
#include "th10/render/resource_registrar_0043e460.hpp"

#pragma code_seg(".text$0043e460_fn")

char* AnimationManager_0043e460::RegisterResource(const char* name, int resource, int parameter) {
    int index = 0;
    for (; index < 31; ++index) {
        if (records[index].resource == 0) {
            records[index].resource = resource;
            records[index].parameter = parameter;
            char* out = records[index].name;
            const char* text = name;
            while ((*out++ = *text++) != 0) {}
            records[index].state = 0;
            return const_cast<char*>(text);
        }
    }
    return (char*)(long)index;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
