// 0x00417010: decode an obfuscated string embedded in script data.
//
// Each byte is XORed with a rolling key that starts at 0x77 and grows by a
// step that itself starts at 7 and grows by 0x10 per byte; decoding stops
// after the terminating NUL has been written.  The result lives in a single
// static buffer, so the returned text is only valid until the next call.
//
// Retail passes the encoded text in EAX; native LTCG picks that register
// from the callers, so the body is compiled in the cluster
// layout/ltcg/path_decode_xor_00417010.json.

// Static result buffer in .bss (0x00497D40).
extern char g_decoded_text_00497d40[];

#pragma code_seg(".text$01decode")
__declspec(noinline) char* Path_DecodeXor(const char* encoded) {
    unsigned char key = 0x77;
    unsigned char step = 7;
    char* out = g_decoded_text_00497d40;
    char c;
    do {
        c = *encoded ^ key;
        *out++ = c;
        encoded++;
        key += step;
        step += 0x10;
    } while (c);
    return g_decoded_text_00497d40;
}
#pragma code_seg()
