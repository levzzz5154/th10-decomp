// 0x0042C850..0x0042C894: report whether any of the six play-record bytes is set.
//
// The progress object arrives in EAX and the result is returned in EAX — a
// convention only a native LTCG link chooses — so this region is compiled as a
// cluster (see layout/ltcg/progress_record_0042c850.json).
struct GameProgress_0042c850 {
    unsigned char pad_000[0x1D888];
    unsigned char record_present[6];     // +0x1D888
    __declspec(noinline) int HasAnyPlayRecord();
};

#pragma code_seg(".text$01accessor")
int GameProgress_0042c850::HasAnyPlayRecord() {
    return record_present[0] != 0
        || record_present[1] != 0
        || record_present[2] != 0
        || record_present[3] != 0
        || record_present[4] != 0
        || record_present[5] != 0;
}
#pragma code_seg()
