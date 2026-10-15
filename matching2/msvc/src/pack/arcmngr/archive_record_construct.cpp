// 0x00434C10..0x00434C1F: the constructor of one 16-byte archive record
// (StaticInit_ArchiveArray builds twenty of them).
// Recovered: clears the four leading words of the object and returns the object
// pointer (retail returns it in EAX, so the body is __thiscall).
int* __fastcall ArchiveRecord_Construct(int* self) {
    self[0] = 0;
    self[1] = 0;
    self[2] = 0;
    self[3] = 0;
    return self;
}
