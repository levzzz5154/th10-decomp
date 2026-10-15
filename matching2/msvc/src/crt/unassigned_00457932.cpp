extern "C" int __cdecl asm_XcptFilter_004577ce(unsigned int code, void* exception);

extern "C" int __cdecl asm_unassigned_00457932(unsigned int code, void* exception) {
    if (code == 0xE06D7363) return asm_XcptFilter_004577ce(code, exception);
    return 0;
}
