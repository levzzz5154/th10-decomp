// 0x00403080: normalize the stage ECL loader's result to 0 or -1.
// Native LTCG supplies the private adapter entry: loader in ECX, filename
// in EAX, result in EAX, plain RET. The loader itself keeps public thiscall.
#include "th10/game/background.hpp"
#pragma code_seg(".text$01forward")
int BackGround::LoadNormalized(const char* name) {
    return Load(name) != 0 ? -1 : 0;
}
#pragma code_seg()
