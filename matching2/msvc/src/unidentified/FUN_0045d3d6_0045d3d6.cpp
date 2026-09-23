// 0x0045D3D6..0x0045D3E1: FUN_0045d3d6
// The retail entry takes one destination pointer from the stack and clears
// exactly three consecutive dwords.  Its caller performs stack cleanup.
extern "C" void __cdecl asm_FUN_0045d3d6_0045d3d6(
    unsigned int* destination) {
    destination[0] = 0;
    destination[1] = 0;
    destination[2] = 0;
}
