// 0x00404C60: copy one seven-word block.
struct Block {
    int words[7];
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall CopyBlock(Block* destination, const Block* source) {
    *destination = *source;
}
#pragma code_seg()
