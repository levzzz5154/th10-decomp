// The original routine is a compiler-generated x87 angle helper.  Native
// LTCG supplies its two pointers in EAX and ECX, while this source keeps the
// operation expressed in terms of the point and the entity's world position.
extern "C" float data_00470b04;
extern "C" float data_00470b94;
extern "C" double atan2(double, double);

struct EntityAngleTarget_00426610 {
    unsigned char reserved_000[0x3c0];
    float x;
    float y;
};

typedef char EntityAngleTarget_00426610_layout[
    sizeof(EntityAngleTarget_00426610) == 0x3c8 ? 1 : -1];

#pragma code_seg(".text$01angle")
__declspec(noinline) double Entity_AngleToPoint(
        const EntityAngleTarget_00426610* entity, const float* point) {
    float horizontal = point[0] - entity->x;
    float vertical = point[1] - entity->y;
    if (vertical == data_00470b04 && horizontal == data_00470b04)
        return data_00470b94;
    return atan2(vertical, horizontal);
}
#pragma code_seg()
