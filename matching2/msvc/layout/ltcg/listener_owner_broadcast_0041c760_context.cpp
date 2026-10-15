// Compiler context only; none of these bytes enter the image.
#include "../../src/game/laser/listener_owner_broadcast_0041c760.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall ListenerOwnerBroadcastContext_0041c760(
        ListenerOwner_0041c760** owners, const Vector3_0041c760* vectors, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i)
        total += owners[i]->Broadcast(vectors + i, vectors + count, i);
    return total;
}
#pragma code_seg()
