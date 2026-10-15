#include "resource_surface_loading_log.cpp"
#include "../../src/unreferenced/unassigned_00439700.cpp"

#pragma code_seg(".text$11context")
int __stdcall TextLogLineCompilerContext(TextLog_0044b8e0** logs, int count, int value, const char* name) {
    for (int index = 0; index < count; ++index)
        logs[index]->AppendLine("%d %s", value, name);
    return 0;
}
#pragma code_seg()
