// 0x00418810..0x0041884F (64 bytes): convert a point into the shared
// screen-space point.
//
// The body adds the playfield origin (224, 16) to the first two components of
// the pointed-to point, copies the third, and returns the shared record.  Its
// two call sites (0x0040EE75 and 0x0040EF6B, both inside the ECL interpreter)
// are `lea eax,[ebx+2Ch]; call 0x00418810`, after which the caller copies the
// three dwords it returned into its entity at +0x340.
//
// Retail's ABI is the source point in EAX and nothing else.  The body's last
// read of that register is `mov eax,[eax+8]`, EAX then carries the returned
// address, and the guard's scratch is ECX and DL - all of which only hold if the
// receiver is EAX.  No C++ declaration names that register (a member receives
// `this` in ECX, a parameter travels on the stack), so the body is compiled as a
// member of the point type through the native-LTCG cluster path
// (build_support/layout/ltcg/recovery_offset_point.json): the array-walking context
// in the layout's driver keeps ECX and EDX live at the call, and the
// whole-program pass then hands the receiver EAX on its own.
//
// The guard is MSVC's per-function lazy-initialization bit - `$S1`, bit 0 of a
// dword in .bss - for a function-local static whose initializer the compiler
// elided, which is why the guarded static contributes nothing but the flag:
// this function is the flag's only reader in the whole image.  A function-local
// static cannot be rebound to retail's address (its symbol has internal
// linkage), so the shared record and its flag are declared with external
// linkage here and the guard is spelled as the bit test it performs.
//
// x87 sum rule: each sum is one struct field plus a pooled literal
// (224.0f at 0x00470B4C and 16.0f at 0x00470B48).  Retail emits
// `fld [field]; fadd [pooled]`, and the rule's ordering half holds - the addend
// order follows the operands' memory form, not the source order: writing
// `224.0f + x` instead of `x + 224.0f` compiles to exactly the same pair.
struct Vector36 {
    float x;
    float y;
    float z;

    __declspec(noinline) Vector36* OffsetPoint() const;
};

extern Vector36 g_offset_point;
extern unsigned int g_offset_point_state;

#pragma code_seg(".text$01offsetpoint")
Vector36* Vector36::OffsetPoint() const {
    if (!(g_offset_point_state & 1)) {
        g_offset_point_state |= 1;
    }
    g_offset_point.x = x + 224.0f;
    g_offset_point.y = y + 16.0f;
    g_offset_point.z = z;
    return &g_offset_point;
}
#pragma code_seg()
