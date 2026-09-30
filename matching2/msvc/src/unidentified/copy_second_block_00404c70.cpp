// 0x00404C70: copy a seven-word block into the second half of a block pair.
struct Block_00404c60 {
    int words[7];
};
struct BlockPair_00404c70 {
    Block_00404c60 first;
    Block_00404c60 second;       // +0x1C
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall CopySecond_00404c70(BlockPair_00404c70* destination, const Block_00404c60* source) {
    destination->second = *source;
}
#pragma code_seg()
