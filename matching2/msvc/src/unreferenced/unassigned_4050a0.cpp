// 0x004050A0 (45 bytes): re-derive the packed channel bytes from the record's
// four float components; the same record 0x00405040 initialises.
//
// Retail, in order:
//
//   D9 46 08      fld  dword ptr [esi+8]
//   E8 ..         call __ftol2
//   D9 46 0C      fld  dword ptr [esi+0Ch]
//   88 46 18      mov  [esi+18h],al
//   E8 ..         call __ftol2
//   D9 46 10      fld  dword ptr [esi+10h]
//   88 46 19      mov  [esi+19h],al
//   E8 ..         call __ftol2
//   D9 46 14      fld  dword ptr [esi+14h]
//   88 46 1A      mov  [esi+1Ah],al
//   E8 ..         call __ftol2
//   88 46 1B      mov  [esi+1Bh],al
//   C3            ret
//
// Each load is scheduled after the preceding conversion and before its store,
// which is what the statement order below produces.  The record arrives in ESI
// and the function takes no arguments, so this too is a native LTCG cluster.
// The region has no reference anywhere in the image: no E8/E9 rel32, no pushed
// address and no data pointer names 0x004050A0.
#pragma code_seg(".text$01channels")
struct WordColor2 {
    float f_00;
    float f_04;
    float f_08;
    float f_0c;
    float f_10;
    float f_14;
    unsigned char b_18;
    unsigned char b_19;
    unsigned char b_1a;
    unsigned char b_1b;

    __declspec(noinline) void UpdateChannels();
};

void WordColor2::UpdateChannels() {
    b_18 = (unsigned char)f_08;
    b_19 = (unsigned char)f_0c;
    b_1a = (unsigned char)f_10;
    b_1b = (unsigned char)f_14;
}
#pragma code_seg()
