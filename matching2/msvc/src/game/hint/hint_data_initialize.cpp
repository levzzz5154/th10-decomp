#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"
#include "th10/game/hint_data.hpp"

extern "C" void* __cdecl memset(void* destination, int value,
                                  unsigned int size);

// 0x00418D00..0x00418D32: initialize one parsed hint record.
HintData* __fastcall HintData_Initialize(void*, HintData* tip) {
    memset(tip, 0, sizeof(*tip));
    tip->node.Initialize(tip);
    tip->state = -1;
    tip->selection = -1;
    tip->duration = 300;
    tip->scale = 1.0f;
    return tip;
}
