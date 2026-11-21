// Compiler context only; none of these bytes enter the image.
#include "../../../src/game/laser/laser_manager_cut_rectangle.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall ListenerOwnerBroadcastContext_0041c760(
        LaserManagerCutView** owners, const Vector37* vectors, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i)
        total += owners[i]->CutRectangle(vectors + i, vectors + count, i);
    return total;
}
#pragma code_seg()
