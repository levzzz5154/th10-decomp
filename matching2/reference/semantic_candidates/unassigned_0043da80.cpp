// 0x0043DA80: start the stream stored in a sound owner and publish the
// 32-bit command value only when the stream start succeeds.
//
// This semantic spelling gives the observed operations ordinary C++ types.
// It is not a native ABI replacement: retail takes the owner in ESI, cleans
// one 4-byte stack slot with RET 4, and calls 0x0044D440 with its stream in EAX,
// two stack arguments, and the caller's ECX interface context. MSVC has no
// ordinary C++ convention for those private register inputs, so the call below
// is a readable semantic contract, not a byte-equivalent bridge.

struct SoundStreamOwner_0043da80 {
    unsigned char unknown_0000[0x5208];
    void* stream_5208;
    unsigned int unknown_520c;
    unsigned int command_value_5210;
};

// Semantic call shape for the retail helper at 0x0044D440. The actual helper
// consumes `stream` in EAX, uses the inherited ECX interface context, and
// returns with RET 8; see the ABI note above.
extern "C" int __cdecl asm_SoundStream_Start_0044d440();
typedef int (__fastcall *SoundStreamStartMethod_0044d440)(
    void* stream, void* unused_edx,
    unsigned int start_argument, unsigned int mode_argument);

extern "C" int __cdecl asm_unassigned_0043da80(
    SoundStreamOwner_0043da80* owner, unsigned int command_value) {
    if (owner->stream_5208 == 0)
        return -1;

    const SoundStreamStartMethod_0044d440 start_stream =
        reinterpret_cast<SoundStreamStartMethod_0044d440>(
            &asm_SoundStream_Start_0044d440);
    const int start_result = start_stream(owner->stream_5208, 0, 0, 1);
    if (start_result < 0)
        return -1;

    owner->command_value_5210 = command_value;
    return 0;
}
