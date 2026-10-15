// 0x004501D0..0x004501D0: empty leaf.
// The image holds a lone RET here; no caller and no pointer to it exists, so an
// empty function recovers it exactly.

extern "C" void unassigned_004501d0(void) {
}
