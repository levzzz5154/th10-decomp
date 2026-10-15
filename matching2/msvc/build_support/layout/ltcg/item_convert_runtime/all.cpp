// 0x0041E260: retire one line effect, create an animation segment every 12
// units along it and, when asked, drop a kind-8 item for each segment inside
// the inner screen rectangle. The animation list registration is the
// registrar at 0x004489D0 expanded in place.
#include "types/line_sweeps.hpp"
#pragma code_seg(".text$f0041e260F")
struct LineRef {
    unsigned int value;
    LineRef() {}
    LineRef(unsigned int value_) : value(value_) {}
    LineRef& operator++() { ++value; return *this; }
    bool operator==(LineRef other) const { return value == other.value; }
};
struct LineLists {
    unsigned char reserved_000[0x72dad4];
    LineAnimationNode* primary_head;
    LineAnimationNode* primary_tail;
    unsigned char reserved_72dadc[0x732454-0x72dadc];
    LineRef next_id;
    inline LineRef RegisterPrimaryBack(Entity* object) {
        LineAnimationNode* node = reinterpret_cast<LineAnimationNode*>(
            &object->manager_node_animation);
        node->object = object;
        node->next = 0;
        node->previous = 0;
        if (!primary_head)
            primary_head = node;
        else {
            LineAnimationNode* tail = primary_tail;
            LineAnimationNode* next = tail->next;
            if (next) {
                node->next = next;
                tail->next->previous = node;
            }
            tail->next = node;
            node->previous = tail;
        }
        primary_tail = node;
        ++next_id;
        if (next_id == 0) ++next_id;
        object->animation_handle = next_id.value;
        return next_id;
    }
};
__declspec(noinline) int LineEffectSweep::CreateAllSegments(int spawn_items) {
    float progress;
    int count=0;
    progress=6.0f;
    LineSweepStep step;
    step.velocity.SetPolar(angle,6.0f);
    LineSweepVector point;
    point=LineSweepVector(step.velocity.x+position.x,step.velocity.y+position.y,position.z);
    step.z=0.0f;
    step.velocity.x+=step.velocity.x;
    step.velocity.y+=step.velocity.y;
    if (12.0f<length) {
    do {
        ++count;
        int index=script_all*2+17;
        void* resource=g_laser_manager->line_animation;
        Entity* object=static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
        unsigned int flags=object->flags_35C;
        object->flags_35C=flags|0x40000000u;
        object->render_bucket=0;
        Vector3* out=&object->position;
        out->x=point.x+224.0f;
        out->z=point.z;
        out->y=point.y+16.0f;
        LoadScript_0043e710(static_cast<AnimationResourceFile*>(resource),
            reinterpret_cast<AnimationObjectFile*>(object),index);
        static_cast<LineLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
        if (spawn_items &&
            !(point.x+32.0f<=-192.0f) &&
            !(point.x-32.0f>=192.0f) &&
            !(point.y+32.0f<=flt_0) &&
            !(point.y-32.0f>=448.0f)) {
            g_item_manager->Spawn(&point,8,-1,-1.5707963705062866f,0.6f);
        }
        point.x+=step.velocity.x;
        point.y+=step.velocity.y;
        volatile float& point_z=point.z;
        point_z=point_z+step.z;
        progress+=12.0f;
    } while (progress+6.0f<length);
    }
    retired=1;
    return count;
}
#pragma code_seg()
