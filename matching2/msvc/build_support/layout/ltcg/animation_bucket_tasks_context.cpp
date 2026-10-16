// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/sprtlib/animation_bucket_tasks.cpp"
#include "../../../src/core/sprtlib/animation_manager_render_bucket.cpp"

#pragma code_seg(".text$05context")
int __stdcall AnimationBucketTasksContext(SprtCtrlBatchView** managers, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result += managers[index]->DrawBucket0();
        result += managers[index]->DrawBucket2();
        result += managers[index]->DrawBucket4();
        result += managers[index]->DrawBucket5();
        result += managers[index]->DrawBucket6();
        result += managers[index]->DrawBucket7();
        result += managers[index]->DrawBucket8();
        result += managers[index]->DrawBucket9();
        result += managers[index]->DrawBucket10();
        result += managers[index]->DrawBucket11();
        result += managers[index]->DrawBucket12();
        result += managers[index]->DrawBucket13();
    }
    return result;
}
#pragma code_seg()
