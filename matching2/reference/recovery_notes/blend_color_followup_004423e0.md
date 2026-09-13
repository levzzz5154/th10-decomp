# Blend/color helper follow-up at 0x004423E0

The render cluster expansion makes this helper's private EAX manager / EBX entity
ABI expressible. It was tested alongside the exact state synchronizer, flusher,
appender, and primitive callers; those 13 bodies remain exact. The 440-byte blend
candidate has the complete retail extent, frame, branch layout, private calls,
color selection, and state-cache tail. It remains assembly because 33 instruction
bytes differ in the color-modulation interval 0x00442473..0x004424EF.

The candidate uses the accepted SyncRenderState source pattern, adding switch
case 2, selection between entity colors at 0x2FC/0x300, four saturated color
products, and cached texture-factor state 60. The manager fade bytes are at
0x732458 and its enable word is at 0x73245C. The source for the missed interval is:

```cpp
inline unsigned int ScaleColor(unsigned char channel, unsigned char tint) {
    unsigned int result = (channel * (unsigned int)tint) >> 7;
    if (result >= 256) result = 255;
    return result;
}
// color is the selected unsigned 32-bit entity color.
if (fade_enabled) {
    unsigned char* channels = (unsigned char*)&color;
    channels[2] = (unsigned char)ScaleColor((unsigned char)(color >> 16), fade[2]);
    channels[1] = (unsigned char)ScaleColor((unsigned char)(color >> 8), fade[1]);
    channels[0] = (unsigned char)ScaleColor((unsigned char)color, fade[0]);
    channels[3] = (unsigned char)ScaleColor((unsigned char)(color >> 24), fade[3]);
}
```

Retail loads the red fade byte into EAX, extracts red into EDX, and multiplies
EAX by EDX. The candidate loads fade into ECX, extracts red into EAX, and multiplies
EAX by ECX. Green and alpha have similar register differences, and their fade
loads move before the preceding local byte store. Blue already matches. The
clamps, shifts, and all code outside the modulation interval match.

Five bounded probes separated source-shape and ABI issues. Swapping multiplication
operands, reversing inline-helper parameter order, and widening its arguments to
unsigned int all retain the same 440-byte/33-byte mismatch. Volatile fade reads
change scheduling but grow the body to 446 bytes. These are optimization
scheduling/register-allocation misses, not caller/callee visibility, retention,
constant placement, jump tables, or SEH. They do not prove the shape unreachable.

Diagnostic outputs are under `matching2/build/recovery-lab/blend1` through `blend5`.
`blend5` passes the complete cluster extent gates and reports only this body
DIFFERENT; the first differing instruction is the MOVZX at 0x00442473. The lab's
233-byte context grows to 247 bytes when it also calls this helper. Neither
context is counted as recovered code. No masks, substitutions, or aliases were
used. Retry with a distinct source model for the four-channel multiplication,
or with its real transformed-quad caller at 0x00444760, rather than repeating
commutative-expression variants.
