// 0x00405040 (94 bytes): initialise a colour/word record from six float
// components and re-derive its four packed channel bytes.
//
// Retail, in order (D9/D8 are the x87 pair, E8 the __ftol2 conversion):
//
//   8B 44 24 04      mov  eax,[esp+4]        ; component 0
//   D9 44 24 0C      fld  dword ptr [esp+0Ch] ; first conversion operand
//   8B 4C 24 08      mov  ecx,[esp+8]
//   8B 54 24 0C      mov  edx,[esp+0Ch]
//   89 06            mov  [esi],eax
//   ...              the remaining five components, addresses ascending
//   E8 ..            call __ftol2             ; (unsigned char)component 2
//   D9 44 24 10      fld  dword ptr [esp+10h]
//   88 46 18         mov  [esi+18h],al
//   ...              components 3, 4, 5 -> [esi+19h], [esi+1Ah], [esi+1Bh]
//   8B C6            mov  eax,esi
//   C2 18 00         ret  18h
//
// The record arrives in ESI and all six components are on the stack, so the
// member is compiled as a native LTCG cluster; the arguments are floats (an
// integer first parameter makes the whole-program pass take it in EAX and the
// region then emits ret 14h).
// Same 0x1C-byte layout as StageFog (th10/render/stage_fog.hpp): fog range
// (start, end), float BGRA channels and their packed device-colour bytes.
#pragma code_seg(".text$01wordcolor")
struct WordColor {
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

    __declspec(noinline) WordColor* Initialize(float fog_start, float fog_end,
                                               float b, float g, float r, float a);
};

WordColor* WordColor::Initialize(float fog_start, float fog_end,
                                 float b, float g, float r, float a) {
    start = fog_start;
    end = fog_end;
    blue = b;
    green = g;
    red = r;
    alpha = a;
    packed_blue = (unsigned char)b;
    packed_green = (unsigned char)g;
    packed_red = (unsigned char)r;
    packed_alpha = (unsigned char)a;
    return this;
}
#pragma code_seg()
