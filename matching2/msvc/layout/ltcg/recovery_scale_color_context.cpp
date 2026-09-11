// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_scale_color_00404da0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryScaleColorCompilerContext(RecoveryScaleColorSource** sources, RecoveryScaleColorResult* result,
                                                float* scales, int count) {
    while (count--) {
        result = RecoveryScaleColor_Scale(*sources++, result, *scales++);
    }
    return 0;
}
#pragma code_seg()
