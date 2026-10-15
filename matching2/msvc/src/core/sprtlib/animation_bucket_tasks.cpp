// 0x004485F0..0x0044873E: scheduler draw tasks, one per animation bucket.
//
// Each task is registered with the animation manager as its owner, so the
// scheduler calls it with the manager in ECX; it draws one bucket and returns
// the bucket renderer's result. The renderer at 0x00448980 takes the manager in
// EDI and the bucket index in EAX, a convention native LTCG assigns only when
// its body is in the same link, so these bodies are compiled in the cluster
// build_support/layout/ltcg/animation_bucket_tasks.json with that body as an ABI anchor.
// Buckets 1 (0x00448600) and 3 (0x00448620, which also selects a render stage)
// have their own sources.
#include "th10/render/quad_batch.hpp"

#pragma code_seg(".text$01b00")
int SprtCtrlBatchView::DrawBucket0() {
    return RenderBucket(0);
}
#pragma code_seg()

#pragma code_seg(".text$01b02")
int SprtCtrlBatchView::DrawBucket2() {
    return RenderBucket(2);
}
#pragma code_seg()

#pragma code_seg(".text$01b04")
int SprtCtrlBatchView::DrawBucket4() {
    return RenderBucket(4);
}
#pragma code_seg()

#pragma code_seg(".text$01b05")
int SprtCtrlBatchView::DrawBucket5() {
    return RenderBucket(5);
}
#pragma code_seg()

#pragma code_seg(".text$01b06")
int SprtCtrlBatchView::DrawBucket6() {
    return RenderBucket(6);
}
#pragma code_seg()

#pragma code_seg(".text$01b07")
int SprtCtrlBatchView::DrawBucket7() {
    return RenderBucket(7);
}
#pragma code_seg()

#pragma code_seg(".text$01b08")
int SprtCtrlBatchView::DrawBucket8() {
    return RenderBucket(8);
}
#pragma code_seg()

#pragma code_seg(".text$01b09")
int SprtCtrlBatchView::DrawBucket9() {
    return RenderBucket(9);
}
#pragma code_seg()

#pragma code_seg(".text$01b10")
int SprtCtrlBatchView::DrawBucket10() {
    return RenderBucket(10);
}
#pragma code_seg()

#pragma code_seg(".text$01b11")
int SprtCtrlBatchView::DrawBucket11() {
    return RenderBucket(11);
}
#pragma code_seg()

#pragma code_seg(".text$01b12")
int SprtCtrlBatchView::DrawBucket12() {
    return RenderBucket(12);
}
#pragma code_seg()

#pragma code_seg(".text$01b13")
int SprtCtrlBatchView::DrawBucket13() {
    return RenderBucket(13);
}
#pragma code_seg()
