#include "../../../src/unreferenced/FUN_0043ac90_0043ac90.cpp"
#include "temporary_track_canonical_anchors.cpp"
#pragma code_seg(".text$80context")
int __stdcall TemporaryTrackContext(MidiSequencer** sequences, const char** names, int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) sum += LoadTemporaryTrack_0043ac90(sequences[i], names[i]);
    return sum;
}
#pragma code_seg()
