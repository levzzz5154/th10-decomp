// 0x0041C760 (102 bytes): record a pair of vectors on the owner, then offer
// them to every listener on its list that is not in state 1, and return the
// sum of the listeners' results. Nothing in the retail image calls it.
//
// Native LTCG passes the owner in EAX and the second vector in EBX.
struct Vector37 {
    float x, y, z;
};

struct Listener2 {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual int Notify(const Vector37* first, const Vector37* second, int argument);

    int reserved_004;
    Listener2* next;                           // +0x08
    int state;                                         // +0x0C
};

struct ListenerOwner {
    unsigned char reserved_000[0x18];
    Listener2* listeners;                      // +0x018
    unsigned char reserved_01c[0x440 - 0x1C];
    Vector37 first;                            // +0x440
    Vector37 second;                           // +0x44C

    __declspec(noinline) int Broadcast(const Vector37* first_value,
                                       const Vector37* second_value, int argument);
};

#pragma code_seg(".text$01broadcast")
int ListenerOwner::Broadcast(const Vector37* first_value,
                                      const Vector37* second_value, int argument) {
    int total = 0;
    Listener2* listener = listeners;
    first = *first_value;
    second = *second_value;
    while (listener) {
        Listener2* next = listener->next;
        if (listener->state != 1)
            total += listener->Notify(first_value, second_value, argument);
        listener = next;
    }
    return total;
}
#pragma code_seg()
