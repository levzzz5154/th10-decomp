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
#pragma code_seg(".text$01wordcolor")
struct WordColor_00405040 {
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

    __declspec(noinline) WordColor_00405040* Initialize(float a0, float a1, float a2,
                                                       float a3, float a4, float a5);
};

WordColor_00405040* WordColor_00405040::Initialize(float a0, float a1, float a2,
                                                   float a3, float a4, float a5) {
    f_00 = a0;
    f_04 = a1;
    f_08 = a2;
    f_0c = a3;
    f_10 = a4;
    f_14 = a5;
    b_18 = (unsigned char)a2;
    b_19 = (unsigned char)a3;
    b_1a = (unsigned char)a4;
    b_1b = (unsigned char)a5;
    return this;
}
#pragma code_seg()
