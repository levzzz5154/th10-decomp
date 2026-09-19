// 0x0043E500..0x0043E51E (31 bytes): stamp a duration in frames onto a value
// record.
//
// Retail, in order (D9/D8 are the x87 pair, E8 the __ftol2 conversion):
//
//   D9 44 24 04      fld   dword ptr [esp+4]      ; the seconds argument
//   C7 46 1C 01..    mov   dword ptr [esi+1Ch],1
//   D8 0D <470b1c>   fmul  dword ptr [60.0f]
//   E8 <463b2c>      call  __ftol2               ; (int)(seconds * 60.0f)
//   89 46 14         mov   [esi+14h],eax
//   89 46 18         mov   [esi+18h],eax         ; the same result twice
//   C2 04 00         ret   4
//
// The record arrives in ESI and the one float argument on the stack, so the
// member is compiled as a native LTCG cluster.  ESI is what the pass picks
// because the record is live across the __ftol2 call, which needs a
// callee-saved register; the caller-supplied array walk in the cluster driver
// is what makes it a callee-saved register instead of ECX/EAX.  The result of
// the call is then used twice - the conversion value is stored straight out of
// EAX into both +0x14 and +0x18.
//
// Two spellings were measured against retail's bytes in the same link:
//
// * the scale as an `extern float` variable.  The compiler then loads the
//   *constant* into st(0) and multiplies by the argument - `flds [470b1c]` /
//   `fmuls [esp+4]` - and 15 of the 31 bytes differ.  Both operands are memory
//   operands, so this is not a length effect: the operand form of the scale,
//   not the expression's left-to-right order, decides which side the x87 pair
//   loads.  Writing the scale as the float *literal* 60.0f and aliasing the
//   compiler's pooled `__real@42700000` to retail's 0x470B1C (the layout's
//   `constant_aliases`) reproduces retail's load-then-multiply order exactly.
// * the two stores: a named temporary, `field_018 = field_014 = <expr>`, a
//   plain `field_018 = field_014` reload and two separate conversions of the
//   same expression all emit retail's `mov [esi+14h],eax; mov [esi+18h],eax`.
//   The conversion result stays in EAX for both stores whatever the spelling,
//   so no consumed-temporary lever is needed here, and a `void` or `int`
//   return is equally inert because retail's EAX at both exits is already the
//   conversion result.  What is load-bearing is the *statement order* the
//   0x1C flag is written in: with the flag store written after the two stores
//   it is no longer hoisted into the multiply's latency window and the body
//   differs from the second byte on.
struct TimeValue_0043e500 {
    unsigned char pad_000[0x14];
    int field_014;                      // +0x14  duration in frames
    int field_018;                      // +0x18  ... and its copy
    int field_01c;                      // +0x1C  the record's "set" flag

    __declspec(noinline) void SetSeconds(float seconds);
};

typedef char TimeValue_0043e500_pad_000_must_be_14[
    (sizeof(((TimeValue_0043e500*)0)->pad_000) == 0x14) ? 1 : -1];

#pragma code_seg(".text$01accessor")
void TimeValue_0043e500::SetSeconds(float seconds) {
    field_01c = 1;
    int frames = (int)(seconds * 60.0f);
    field_014 = frames;
    field_018 = frames;
}
#pragma code_seg()
