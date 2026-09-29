// 0x00404C60: copy one seven-word block.
struct Block_00404c60 {
    int words[7];
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall CopyBlock_00404c60(Block_00404c60* destination, const Block_00404c60* source) {
    *destination = *source;
}
#pragma code_seg()
