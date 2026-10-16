// 0x00404C70: copy a seven-word block into the second half of a block pair.
struct Block {
    int words[7];
};
struct BlockPair {
    Block first;
    Block second;       // +0x1C
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall CopySecond(BlockPair* destination, const Block* source) {
    destination->second = *source;
}
#pragma code_seg()
