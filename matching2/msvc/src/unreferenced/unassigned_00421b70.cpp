// 0x00421B70..0x00421B86 (23 bytes): publish the selected phase record.
//
// Retail reads the two dwords at +0x3C and +0x40 of the object in ECX, copies
// the later one into the earlier, and publishes a pointer to the 0x30-byte
// record the copied index selects out of the table at 0x00474788 through the
// shared pointer 0x00477848.  ECX is the object, so the body is an ordinary
// __thiscall member and compiles as a plain translation unit.
//
// `&table[index]` is the shape that emits retail's `lea eax,[eax+eax*2]` /
// `shl eax,4` (index * 0x30, each record being three dwords) rather than an
// `imul`.

struct PhaseCursor {
    unsigned char unknown_00[0x3C];
    unsigned int published;                 // +0x3C
    unsigned int selected;                  // +0x40

    __declspec(noinline) void Publish();
};

struct PhaseRecord {
    unsigned int values[0xC];               // 0x30 bytes
};

extern "C" PhaseRecord g_stage_routes[];
extern "C" PhaseRecord* g_stage_route_current;

#pragma code_seg(".text$01publish")
void PhaseCursor::Publish() {
    unsigned int index = selected;
    published = index;
    g_stage_route_current = &g_stage_routes[index];
}
#pragma code_seg()
