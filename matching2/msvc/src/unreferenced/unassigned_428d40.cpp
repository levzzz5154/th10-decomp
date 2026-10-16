// 0x00428D40..0x00428D58 (25 bytes): squared distance between two positions.
//
// Retail subtracts the y pair, subtracts the x pair, squares both and adds
// them, all in the x87 unit, leaving the sum in ST(0).  The first record
// arrives in EAX and the second in ECX.

struct Position3 {
    float x;                               // +0x00
    float y;                               // +0x04
};

__declspec(noinline) float __fastcall Position_00428d40_SquaredDistance(Position3* to,
                                                                        Position3* from);

#pragma code_seg(".text$01dist")
float __fastcall Position_00428d40_SquaredDistance(Position3* to,
                                                   Position3* from) {
    float dy = to->y - from->y;
    float dx = to->x - from->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
