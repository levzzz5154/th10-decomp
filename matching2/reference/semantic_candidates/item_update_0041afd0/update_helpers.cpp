// Complete genuine helper bodies adapted to the coherent item-update types.
// Sources: score_bookkeeping.cpp, replay_progress.cpp, frame_timer.cpp,
// life_stock_add_004188a0.cpp, player_adjustpower_00405b60.cpp,
// power_display_set_digits_004054b0.cpp, floating_text_draw.cpp,
// entity_angle_from_point_00426660.cpp, sound_queue_pan_0043dd10.cpp.
#include <math.h>
#include "th10/game/item_update_0041afd0.hpp"
#include "th10/render/animation_byte_interpolator.hpp"

#pragma code_seg(".text$110adjust")
void ItemRunState::AdjustPower(int amount) {
    power_accumulator+=amount;
    if (power_accumulator>1024) power_accumulator=1024;
    else if (power_accumulator<-1024) power_accumulator=-1024;
}
#pragma code_seg(".text$111score")
void ItemRunState::AddScore(int amount) {
    score+=amount/10;
    if (score>=1000000000) score=999999999;
}
#pragma code_seg(".text$112gauge")
void ItemRunState::AddGauge(int amount) {
    gauge+=amount/10;
    if (gauge>99999) gauge=99999;
}
#pragma code_seg(".text$113hold")
void ItemRunState::AdvanceGaugeTimer(int frames) {
    if (gauge_timer.current<130) {
        FrameTimer& timer=gauge_timer;
        timer.Advance(float(frames));
        if (gauge_timer.current>130) {
            if (!(timer.flags&1)) {
                timer.current=0;
                timer.previous=-999999;
                timer.elapsed=0.0f;
                timer.speed=&g_score_default_speed;
                timer.flags|=1;
            }
            timer.current=130;
            timer.elapsed=130.0f;
            timer.previous=129;
        }
    }
}
#pragma code_seg(".text$114advance")
void FrameTimer::Advance(float delta) {
    previous=current;
    if (*speed>g_frame_timer_normal_lower && *speed<g_frame_timer_normal_upper)
        elapsed+=delta;
    else elapsed+=delta**speed;
    current=int(elapsed);
}
#pragma code_seg(".text$115power")
int ItemRunState::AddPower(int amount) {
    if (power>=100) return 0;
    power+=amount;
    if (power>100) {
        power=100;
        ItemAnimationHandle* banner=&data_0047770c->ExtendBanner();
        static_cast<ItemAnimationLists*>(data_00491c10)->MarkForRemoval(*banner);
        banner->value=0;
        void* created;
        void** output=ItemAnimation_CreatePrimaryBack(data_0047770c->AnimationResource(),&created,73,15);
        // The public helper returns its output pointer. Copy the handle's
        // representation, as the retained animation registrar does.
        memcpy(banner,output,sizeof(*banner));
    }
    return (power-static_cast<short>(amount))/20!=power/20;
}
#pragma code_seg(".text$116lives")
void ItemRunState::AddLives(int amount) {
    lives+=amount;
    if (lives>9) lives=9;
    else {
        data_00492590.Queue(44,0);
        ItemAnimationHandle* banner=&data_0047770c->ExtendBanner();
        static_cast<ItemAnimationLists*>(data_00491c10)->MarkForRemoval(*banner);
        banner->value=0;
        void* created;
        void** output=ItemAnimation_CreatePrimaryBack(data_0047770c->AnimationResource(),&created,75,15);
        memcpy(banner,output,sizeof(*banner));
    }
    data_0047770c->SetActiveCount(data_00474c40.lives);
}
#pragma code_seg(".text$117digits")
void ItemHud::SetPowerDigits(int whole,int fraction) {
    AnimationResource()->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(storage+0x6A8C),whole+8);
    AnimationResource()->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(storage+0x71E4),fraction/10+8);
    AnimationResource()->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(storage+0x7590),fraction%10+8);
}
#pragma code_seg(".text$118text")
void ItemFloatingTextPool::Spawn(int value,const Vector3* position,unsigned int color) {
    if (next_text>=0x2D0) next_text=0;
    ItemFloatingText* text=&texts[next_text];
    int length=0;
    text->active=1;
    if (value>=0) {
        while (value) {
            text->glyphs[length++]=value%10;
            value/=10;
        }
    } else {
        text->glyphs[0]=10;
        length=1;
    }
    if (length==0) { text->glyphs[0]=0; length=1; }
    text->length=length;
    text->color=color;
    FrameTimer_Restart(&text->timer);
    text->position=*position;
    ++next_text;
}
#pragma code_seg(".text$119angle")
float ItemCollector::AngleFromPoint(const Vector3* point) {
    float dx=position.x-point->x;
    float dy=position.y-point->y;
    if (dy==data_00470b04 && dx==data_00470b04) return data_00470b94;
    return static_cast<float>(atan2(static_cast<double>(dy),static_cast<double>(dx)));
}
#pragma code_seg(".text$120pan")
extern "C" short data_004749ce[];
void SoundQueue::QueuePan(int sound_id,float pan) {
    int priority=data_004749ce[sound_id*4];
    int request=int(pan*(1000.0f/192.0f));
    int slot;
    for (slot=0;slot<12;++slot) {
        if (sound_ids[slot]<0) break;
        if (sound_ids[slot]==sound_id) {
            int count=counts[slot];
            if (count<128) { requests[slot][count]=request; ++counts[slot]; }
            return;
        }
    }
    if (slot<12) {
        sound_ids[slot]=sound_id;
        priorities[sound_id]=priority;
        requests[slot][0]=request;
        ++counts[slot];
    }
}
#pragma code_seg()
