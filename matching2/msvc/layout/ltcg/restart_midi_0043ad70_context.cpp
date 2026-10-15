// Compiler context only; no context bytes count as recovered game code.
#include "../../src/unreferenced/unassigned_0043ad70.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall RestartMidiContext(MidiSequencer_0043ad70** managers, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result += managers[index]->Restart();
    }
    return result;
}
#pragma code_seg()
