// 0x0042BE20: (re)load the selected script file. Releases the previous
// resource and data, reads the named file from the archive, parses it with a
// fresh parser and resets the cursor. Native LTCG keeps the viewer in ESI.
// 0x0042BE10: the argument-less callback that loads for the global viewer.
#include "th10/game/script_viewer_load_0042be20.hpp"

#pragma code_seg(".text$01load")
int ScriptViewer_0042be20::LoadScript() {
    char path[260];
    sprintf(path, "%s", script_names[file_cursor.selection]);
    int selected = 0;
    if (resource) {
        resource->Retire(1);
        resource = 0;
    }
    resource = 0;
    if (script_data) {
        free(script_data);
        script_data = 0;
    }
    script_data = Archive_LoadFile(path, 0, 0);
    parser = new ScriptParser_0042be20;
    parser->Load(script_data);
    entry_cursor.item_count = parser->entry_count;
    ScriptViewer_ClampSelection(entry_cursor, selected);
    entry_cursor.selection = selected;
    state = 1;
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$00task")
int __stdcall ScriptViewer_LoadTask_0042be10() {
    data_00477844->LoadScript();
    return 0;
}
#pragma code_seg()
