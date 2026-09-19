// 0x4221E0, 0x4221F0, 0x424EB0, 0x424EC0: constant-zero leaves.
//
// Each address holds three bytes, `33 C0 C3`: return 0.  The pair at 0x4221E0 /
// 0x4221F0 and the pair at 0x424EB0 / 0x424EC0 are each sixteen bytes apart, so
// they are sibling virtual slots of one class whose default answer is "no"; no
// region in the image reaches them by a direct call either, so the only
// reference is a vtable entry.
//
// Nothing is read before the result is written, so a plain unit reproduces
// retail byte for byte.  /Gz makes the default convention __stdcall; with no
// parameters the body is still the bare `xor eax,eax; ret`.

extern "C" int Fun_4221e0() { return 0; }
extern "C" int Fun_4221f0() { return 0; }
extern "C" int Fun_424eb0() { return 0; }
extern "C" int Fun_424ec0() { return 0; }
