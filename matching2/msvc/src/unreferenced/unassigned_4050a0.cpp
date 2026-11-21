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
// Same 0x1C-byte layout as StageFog (th10/render/stage_fog.hpp).
#pragma code_seg(".text$01channels")
struct WordColor2 {
    float start;
    float end;
    float blue;
    float green;
    float red;
    float alpha;
    unsigned char packed_blue;
    unsigned char packed_green;
    unsigned char packed_red;
    unsigned char packed_alpha;

    __declspec(noinline) void UpdateChannels();
};

void WordColor2::UpdateChannels() {
    packed_blue = (unsigned char)blue;
    packed_green = (unsigned char)green;
    packed_red = (unsigned char)red;
    packed_alpha = (unsigned char)alpha;
}
#pragma code_seg()
