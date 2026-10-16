// 0x0042A810: stamp the replay-header magic "USER" (0x52455355).
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster
// (build_support/layout/ltcg/replay_header_stamp.json).
// Same immediate is written inline at 0x00429F6A/0x0042A136 when a
// replay header is built.

struct ReplayHeader3 {
    int magic; // +0x00, "USER"
    __declspec(noinline) void StampUser();
};
typedef char ReplayHeader_0042a810_size_must_fit[sizeof(ReplayHeader3) == 4 ? 1 : -1];

#pragma code_seg(".text$01stamp")
void ReplayHeader3::StampUser() {
    magic = 0x52455355;
}
#pragma code_seg()
