#include "asm_symbols.hpp"

#pragma comment(linker, "/alternatename:_asm_FUN_004266b0_004266b0=_ItemFieldContact_004266B0")

namespace {

float ReadFieldFloat(const void* fieldState, unsigned offset) {
    const unsigned char* bytes = static_cast<const unsigned char*>(fieldState);
    return *reinterpret_cast<const float*>(bytes + offset);
}

int ReadFieldInt(const void* fieldState, unsigned offset) {
    const unsigned char* bytes = static_cast<const unsigned char*>(fieldState);
    return *reinterpret_cast<const int*>(bytes + offset);
}

} // namespace

// Retail entry 0x004266B0. The original private inputs were size in EAX,
// position in ECX, and field state in EDX. The caller-inclusive C ABI is
// (__cdecl): position, size, field state, with the return value in EAX.
extern "C" int __cdecl ItemFieldContact_004266B0(
    const float* position, const float* size, void* fieldState) {
    const float halfScale = *reinterpret_cast<const float*>(&data_00470b0c);
    const float margin = *reinterpret_cast<const float*>(&data_00470be8);
    const float halfWidth = size[0] * halfScale;
    const float halfHeight = size[1] * halfScale;

    const float minX = ReadFieldFloat(fieldState, 0x404);
    const float minY = ReadFieldFloat(fieldState, 0x408);
    const float maxX = ReadFieldFloat(fieldState, 0x410);
    const float maxY = ReadFieldFloat(fieldState, 0x414);

    const bool outsideInnerField =
        position[0] + halfWidth < minX ||
        position[1] + halfHeight < minY ||
        maxX < position[0] - halfWidth ||
        maxY < position[1] - halfHeight;

    if (outsideInnerField) {
        if (minX <= position[0] + margin &&
            minY <= position[1] + margin &&
            position[0] - margin <= maxX &&
            position[1] - margin <= maxY) {
            return 2;
        }
        return 0;
    }

    const unsigned char* dialogueManager =
        *reinterpret_cast<const unsigned char* const*>(&data_0047770c);
    if (dialogueManager != 0 &&
        *reinterpret_cast<const int*>(dialogueManager + 0x9eb8) != 0) {
        return 0;
    }

    const int fieldMode = ReadFieldInt(fieldState, 0x458);
    if (fieldMode == 2 || fieldMode == 3 || fieldMode == 4) return 0;

    if (ReadFieldInt(fieldState, 0x4310) < 1) {
        // The activation entry keeps its existing one-stack-argument RET 4
        // contract. Cast the generated raw declaration to that observed ABI.
        typedef void (__stdcall *ActivateField)(void*);
        ActivateField activate = reinterpret_cast<ActivateField>(
            &asm_FUN_00426cf0_00426cf0);
        activate(fieldState);
    }
    return 1;
}
