// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/msg_decode_xor.cpp"

void __stdcall PathDecodeSink_00417040(const char* text);

#pragma code_seg(".text$02context")
int __stdcall PathDecodeContext_00417010(const char** records, int count) {
    for (int i = 0; i < count; ++i)
        PathDecodeSink_00417040(Msg_DecodeXor(records[i] + 4));
    return count;
}
#pragma code_seg()
