#include "../../src/unreferenced/unassigned_00450610.cpp"
#pragma code_seg(".text$03context")
void UnassignedStreamContext_00450610(UnassignedStream_00450610* streams, int count,
                                      void* dest, unsigned int size, char type) {
    for (int index = 0; index < count; ++index) streams[index].Assign(size, type, dest);
}
#pragma code_seg()
