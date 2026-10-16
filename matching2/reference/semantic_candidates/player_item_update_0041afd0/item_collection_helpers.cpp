// Complete genuine helper bodies adapted to the coherent item-update types.
// Sources: score_bookkeeping.cpp, replay_progress.cpp, frame_timer.cpp,
// life_stock_add.cpp, player_adjustpower.cpp,
// power_display_set_digits.cpp, floating_text_draw.cpp,
// entity_angle_from_point_00426660.cpp, sound_queue_pan_0043dd10.cpp.
#include <math.h>
#include "item_update.hpp"
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
#pragma code_seg(".text$115power")
int ItemRunState::AddPower(int amount) {
    if (power>=100) return 0;
    power+=amount;
    if (power>100) {
        power=100;
        AnimationRef* banner=&data_0047770c->ExtendBanner();
        static_cast<PickupAnimationLists*>(data_00491c10)->MarkForRemoval(*banner);
        banner->value=0;
        *banner=Pickup_CreatePrimaryBack(data_0047770c->AnimationResource(),73,15);
    }
    return (power-static_cast<short>(amount))/20!=power/20;
}
#pragma code_seg(".text$116lives")
void ItemRunState::AddLives(int amount) {
    lives+=amount;
    if (lives>9) lives=9;
    else {
        data_00492590.Queue(44,0);
        AnimationRef* banner=&data_0047770c->ExtendBanner();
        static_cast<PickupAnimationLists*>(data_00491c10)->MarkForRemoval(*banner);
        banner->value=0;
        *banner=Pickup_CreatePrimaryBack(data_0047770c->AnimationResource(),75,15);
    }
    data_0047770c->SetActiveCount(data_00474c40.lives);
}
#pragma code_seg(".text$117digits")
void FrontScript::SetPowerDigits(int whole,int fraction) {
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
#pragma code_seg()
