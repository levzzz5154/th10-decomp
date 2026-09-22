extern "C" unsigned int data_00499344;
extern "C" unsigned int data_00499330;

// 0x00453C3D..0x00453C51: Return the mask for CRT state 3.
extern "C" unsigned int __cdecl asm_unassigned_00453c3d() {
    return data_00499344 == 3 ? data_00499330 : 0;
}
