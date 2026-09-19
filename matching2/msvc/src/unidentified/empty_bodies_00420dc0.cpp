// 0x420DC0, 0x421410, 0x421D40, 0x4245F0, 0x427E00, 0x42AC10, 0x42B420,
// 0x42BAB0, 0x42C5A0: empty out-of-line bodies.
//
// Each of these addresses holds a single byte, 0xC3: a function that does
// nothing and returns.  There is no caller in the image that reaches them
// (their addresses appear in no other region's operand), so they are the
// out-of-line halves of virtual slots a class declares and a later derived
// class overrides, kept by the linker because the vtable names them.
//
// The plain cdecl spelling is the only one that emits a bare `ret`: a
// __stdcall body with arguments would pop them (`ret N`).  Nothing below names
// a parameter, so all nine compile to the single byte retail has.

extern "C" void Fun_420dc0() {}
extern "C" void Fun_421410() {}
extern "C" void Fun_421d40() {}
extern "C" void Fun_4245f0() {}
extern "C" void Fun_427e00() {}
extern "C" void Fun_42ac10() {}
extern "C" void Fun_42b420() {}
extern "C" void Fun_42bab0() {}
extern "C" void Fun_42c5a0() {}
