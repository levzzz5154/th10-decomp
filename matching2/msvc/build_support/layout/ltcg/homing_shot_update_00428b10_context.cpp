// Compiler context only; never selected as recovered game code.
// The update is reached through a table of callbacks, so the context calls it
// through the table slot and the pass keeps its declared register convention.
#include "../../../src/game/player/homing_shot_update_00428b10.cpp"

// Models of the two angle helpers, placed at their retail addresses so the
// pass can see that neither disturbs the x87 stack below its argument.
extern float DAT_00470b10;  // -pi
extern float DAT_00470b14;  // 2*pi
extern float DAT_00470b18;  // pi

#pragma code_seg(".text$03diff")
__declspec(noinline) double __stdcall AngleDifference(float first, float second) {
    float difference = first - second;
    if (difference > DAT_00470b18)
        return first - (DAT_00470b14 + second);
    if (second - first > DAT_00470b18)
        return first - (second - DAT_00470b14);
    return difference;
}
#pragma code_seg()

#pragma code_seg(".text$07normalize")
__declspec(noinline) float __stdcall Angle_Normalize(float angle) {
    int iterations = 0;
    while (angle > DAT_00470b18) {
        angle -= DAT_00470b14;
        if (iterations++ > 0x20)
            break;
    }
    while (angle < DAT_00470b10) {
        angle += DAT_00470b14;
        if (iterations++ > 0x20)
            break;
    }
    return angle;
}
#pragma code_seg()

typedef int (__fastcall* HomingShotCallback_00428b10)(void*, HomingShot*);
extern "C" HomingShotCallback_00428b10 g_homing_shot_update;  // the table slot that names the update

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall HomingShotUpdateCompilerContext(
        HomingShot** shots, int count) {
    int total = 0;
    while (count--)
        total += g_homing_shot_update(0, *shots++);
    return total;
}
#pragma code_seg()
