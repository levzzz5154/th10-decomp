// 0x0041E260: retire one line effect, create an animation segment every 12
// units along it and, when asked, drop a kind-8 item for each segment inside
// the inner screen rectangle. The animation list registration is the
// registrar at 0x004489D0 expanded in place.
#include "../../../build_support/layout/ltcg/item_line_runtime_0041e260/types/line_sweeps.hpp"
#pragma code_seg(".text$45allsegments")
struct LineRef_0041e260 {
    unsigned int value;
    LineRef_0041e260() {}
    LineRef_0041e260(unsigned int value_) : value(value_) {}
    LineRef_0041e260& operator++() { ++value; return *this; }
    bool operator==(LineRef_0041e260 other) const { return value == other.value; }
};
struct LineLists_0041e260 {
    unsigned char reserved_000[0x72dad4];
    LineAnimationNode_0041e260* primary_head;
    LineAnimationNode_0041e260* primary_tail;
    unsigned char reserved_72dadc[0x732454-0x72dadc];
    LineRef_0041e260 next_id;
    inline LineRef_0041e260 RegisterPrimaryBack(Entity* object) {
        LineAnimationNode_0041e260* node = reinterpret_cast<LineAnimationNode_0041e260*>(
            &object->manager_node_animation);
        node->object = object;
        node->next = 0;
        node->previous = 0;
        if (!primary_head)
            primary_head = node;
        else {
            LineAnimationNode_0041e260* tail = primary_tail;
            LineAnimationNode_0041e260* next = tail->next;
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
__declspec(noinline) int LineEffectSweep_0041e260::CreateAllSegments(int spawn_items) {
    float progress;
    int count=0;
    progress=6.0f;
    LineSweepStep_0041e260 step;
    step.velocity.SetPolar(angle,6.0f);
    LineSweepVector_0041e260 point;
    point=LineSweepVector_0041e260(step.velocity.x+position.x,step.velocity.y+position.y,position.z);
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
        LoadScript_0043e710(static_cast<AnimationResource_0043e710*>(resource),
            reinterpret_cast<AnimationObject_0043e710*>(object),index);
        static_cast<LineLists_0041e260*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
        if (spawn_items &&
            !(point.x+32.0f<=-192.0f) &&
            !(point.x-32.0f>=192.0f) &&
            !(point.y+32.0f<=data_00470b04) &&
            !(point.y-32.0f>=448.0f)) {
            data_00477818->Spawn(&point,8,-1,-1.5707963705062866f,0.6f);
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
