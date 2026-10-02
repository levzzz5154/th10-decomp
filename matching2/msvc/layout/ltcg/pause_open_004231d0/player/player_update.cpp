#include "th10/game/pause_result_open_004231d0/player/player_state.hpp"
#include "th10/game/pause_result_open_004231d0/player/indicator_polar/indicator_contract.hpp"
#include "th10/game/stage_schedule.hpp"

// Full owned 0x425730 behavior. There is no synthetic caller or extra input.
// The ignored compiler ECX environment in Ghidra's prototype is absent.
struct ReleaseRecord_00425730 {
    virtual int Slot00(); virtual int Slot04(); virtual int Slot08();
    virtual int Slot0C(); virtual int Slot10();
    virtual void Release(int value);
    unsigned reserved_04;
    ReleaseRecord_00425730* next;
    int type;
};
struct ReleaseList_00425730 {
    unsigned char reserved_00[0x18];
    ReleaseRecord_00425730* head;
    __declspec(noinline) int Cleanup(int value);
};

#pragma code_seg(".text$0041c850_fn")
int ReleaseList_00425730::Cleanup(int value) {
    ReleaseRecord_00425730* record=head;
    while (record) {
        ReleaseRecord_00425730* next=record->next;
        if (record->type!=1) record->Release(value);
        record=next;
    }
    return 1;
}
#pragma code_seg()

static __forceinline void ActivateRecords(int idle_only) {
    CollisionRecord_00408100* record=data_004776f0->records;
    for (int index=0;index<2000;++index,++record)
        if (record->state && record->state!=3 && (!idle_only || !record->countdown))
            record->Activate();
}
static __forceinline void ReleaseRecords(int value) {
    ReleaseRecord_00425730* record=
        reinterpret_cast<ReleaseList_00425730*>(data_0047781c)->head;
    while (record) {
        ReleaseRecord_00425730* next=record->next;
        if (record->type!=1) record->Release(value);
        record=next;
    }
}
static __forceinline void ResetTimer(FrameTimer& timer,int frame) {
    if (!(timer.flags & 1)) {
        timer.current=0;
        timer.previous=-999999;
        timer.elapsed=0.0f;
        timer.speed=&data_00476f78;
        timer.flags |= 1;
    }
    timer.current=frame;
    timer.elapsed=(float)frame;
    timer.previous=frame-1;
}
static __forceinline void SetTimer(FrameTimer& timer,int frame) {
    reinterpret_cast<PlayerSchedulerRecord*>(&timer)->SetSchedulerValue(frame);
}
static __forceinline void UpdatePowerDigits() {
    int power=data_00474c48;
    reinterpret_cast<PowerDisplayOwner_004054b0*>(data_0047770c)->SetPowerDigits(
        power/20,(power%20)*100/20);
}
static __forceinline void AdvanceInlineTimer(FrameTimer& timer) {
    timer.previous=timer.current;
    float speed=*timer.speed;
    if (speed>data_00470b68 && speed<data_00470b64) {
        ++timer.current;
        timer.elapsed += data_00470afc;
    } else {
        timer.current=(int)(timer.elapsed += speed);
    }
}
static __forceinline void SubtractInlineTimer(FrameTimer& timer) {
    timer.previous=timer.current;
    float speed=*timer.speed;
    if (speed>data_00470b68 && speed<data_00470b64)
        timer.elapsed -= data_00470afc;
    else
        timer.elapsed -= speed*data_00470afc;
    timer.current=(int)timer.elapsed;
}

#pragma code_seg(".text$00425730_fn")
extern "C" __declspec(noinline) int __stdcall PlayerStateUpdate_00425730(
    PlayerState_00425730* player) {
    switch (player->phase) {
    case 0: {
        int entry_y=48000-player->state_timer.current*8000/60;
        player->fixed_y=entry_y;
        player->position.y=(float)entry_y*data_00470b00;
        player->familiar_0_state=1;
        player->familiar_1_state=1;
        player->familiar_2_state=1;
        player->familiar_3_state=1;
        int index=32;
        while (index>player->familiar_level*8) {
            player->history[index]=player->history[player->familiar_level*8];
            --index;
        }
        while (index>0) {
            player->history[index]=player->history[index-1];
            --index;
        }
        player->history[0].x=player->fixed_x;
        player->history[0].y=player->fixed_y;
        if (player->state_timer.current<30) {
            float radius=(float)player->state_timer.current*data_00470d44+data_00470bc8;
            data_004776f0->Check(
                reinterpret_cast<const PositionVector_004492f0*>(&player->entry_position),
                radius,0,1);
            data_004776f0->Check(
                reinterpret_cast<const PositionVector_004492f0*>(&player->entry_position),
                radius*data_00470d40,0,0);
            data_0047781c->CopyVectorAndEvaluate(&player->entry_position.x,radius,0);
        } else {
            ActivateRecords(1);
            ReleaseRecords(0);
        }
        if (player->state_timer.current<60) break;
        player->phase=1;
        ResetTimer(player->state_timer,0);
        // Retail intentionally falls through after the entry timer resets.
    }
    case 1: {
        FrontScript_00425730* front=reinterpret_cast<FrontScript_00425730*>(data_0047770c);
        PlayerInitialization_00425730* initializing=data_004776ec;
        if (front && !front->script && initializing && !initializing->initialized &&
            (short)(data_00474c48/20)!=0 && (data_00474e5c&2)) {
            SetTimer(player->invulnerability_timer,270);
            PlayerInitialize_00405860(initializing);
            data_00474c48 -= 20;
            PlayerFamiliarRefresh_00426f70(player);
            UpdatePowerDigits();
            data_00474c40.ReduceGauge(3000);
        }
        if (player->state_timer.current<30) {
            ActivateRecords(1);
            ReleaseRecords(0);
        }
        PlayerMovement_004250b0(reinterpret_cast<MovementState*>(player));
        break;
    }
    case 4:
        if (player->state_timer.current>7) {
            PlayerSpellTimeout_004269d0(player);
            goto death_state;
        }
        if (data_004776ec && !data_004776ec->initialized &&
            (short)(data_00474c48/20)!=0 && (data_00474e5c&2)) {
            SetTimer(player->state_timer,60);
            SetTimer(player->invulnerability_timer,200);
            PlayerInitialize_00405860(data_004776ec);
            data_00474c48 -= 20;
            PlayerFamiliarRefresh_00426f70(player);
            UpdatePowerDigits();
            player->phase=1;
        }
        break;
    case 2:
death_state:
        if (player->state_timer.current==3) {
            data_00474c48 -= 64;
            if (data_00474c48<0) data_00474c48=0;
            UpdatePowerDigits();
            PolarVec3 target={0.0f,player->position.y-data_00470b4c,0.0f};
            float angle=(float)Entity_AngleToPoint(
                reinterpret_cast<const EntityAngleTarget_00426610*>(player),&target.x);
            for (int index=0;index<7;++index) {
                int kind=(index==1 || index==3 || index==5)?4:1;
                data_00477818->Spawn(&player->position.x,kind,0xFFFFFF,
                    (float)index*data_00470d3c+angle-data_00470d38,3.0f);
            }
            PlayerFamiliarRefresh_00426f70(player);
        }
        if (player->state_timer.current>29) {
            if (data_00474c70<0) {
                if (data_00477838->mode==1)
                    PlayerSetInputMode_0040ac90(&data_00491c28,4);
                else
                    data_00477830->OpenPause();
            } else {
                player->phase=0;
                data_00476f78=1.0f;
                reinterpret_cast<IndicatorPlayerView*>(player)->AllocateIndicator(
                    &player->position,32.0f,16.0f,30,150);
                player->entry_position=player->position;
                player->fixed_x=0;
                player->fixed_y=48000;
                player->position.x=0.0f;
                player->position.y=480.0f;
                SetTimer(player->invulnerability_timer,280);
                SetTimer(player->state_timer,0);
            }
        }
        break;
    case 3:
        if (player->state_timer.current!=4 && player->state_timer.current==15) {
            ActivateRecords(0);
            reinterpret_cast<ReleaseList_00425730*>(data_0047781c)->Cleanup(1);
        }
        break;
    }

    for (int index=0;index<32;++index) {
        PlayerParticle_00425730& particle=player->particles[index];
        if (!(particle.flags&1)) continue;
        particle.motion.Update();
        particle.motion.Advance();
        particle.horizontal_extent += particle.horizontal_growth;
        particle.vertical_extent += particle.vertical_growth;
        SubtractInlineTimer(particle.timer);
        if (particle.timer.current<=0) particle.flags &= ~1u;
    }
    unsigned flags=player->animation.flags_35C & ~0x8000u;
    if (player->invulnerability_timer.current>0) {
        SubtractInlineTimer(player->invulnerability_timer);
        if (player->state_timer.current!=player->state_timer.previous &&
            player->state_timer.current%3==0) {
            player->animation.secondary_color=0xFF0000FFu;
            flags |= 0x8000u;
        }
    }
    player->animation.flags_35C=flags;
    PlayerAnimationVmTick_0043ee30(&player->animation);
    player->collision_min.x=player->position.x-player->collision_extent.x;
    player->collision_min.y=player->position.y-player->collision_extent.y;
    player->collision_min.z=player->position.z-player->collision_extent.z;
    player->collision_max.x=player->collision_extent.x+player->position.x;
    player->collision_max.y=player->collision_extent.y+player->position.y;
    player->collision_max.z=player->collision_extent.z+player->position.z;
    float half_z=player->secondary_size.z*data_00470b0c;
    player->secondary_half_min.x=player->position.x-player->secondary_size.x*data_00470b0c;
    player->secondary_half_min.y=player->position.y-player->secondary_size.y*data_00470b0c;
    player->secondary_half_min.z=player->position.z-half_z;
    half_z=player->secondary_size.z*data_00470b0c;
    player->secondary_half_max.x=player->secondary_size.x*data_00470b0c+player->position.x;
    player->secondary_half_max.y=player->secondary_size.y*data_00470b0c+player->position.y;
    player->secondary_half_max.z=half_z+player->position.z;
    player->secondary_min.x=player->position.x-player->secondary_extent.x;
    player->secondary_min.y=player->position.y-player->secondary_extent.y;
    player->secondary_min.z=player->position.z-player->secondary_extent.z;
    player->secondary_max.x=player->secondary_extent.x+player->position.x;
    player->secondary_max.y=player->secondary_extent.y+player->position.y;
    player->secondary_max.z=player->secondary_extent.z+player->position.z;
    player->size_min.x=player->position.x-player->secondary_size.x;
    player->size_min.y=player->position.y-player->secondary_size.y;
    player->size_min.z=player->position.z-player->secondary_size.z;
    player->size_max.x=player->secondary_size.x+player->position.x;
    player->size_max.y=player->secondary_size.y+player->position.y;
    player->size_max.z=player->secondary_size.z+player->position.z;
    AdvanceInlineTimer(player->state_timer);
    AdvanceInlineTimer(player->auxiliary_timer);
    FrontScript_00425730* front=reinterpret_cast<FrontScript_00425730*>(data_0047770c);
    ActiveStage_00425730* stage=data_00477704;
    if (!front->script && stage && stage->active && player->state_timer.current%60==0) {
        ++data_00474c98;
        if (data_00474c98>1024) data_00474c98=1024;
        else if (data_00474c98<-1024) data_00474c98=-1024;
    }
    if (!front->script && stage && stage->active)
        reinterpret_cast<StageSequence*>(player)->Update();
    else {
        ResetTimer(player->stage_timer,-1);
        player->pending_stage=0;
        player->pending_stage_name=0;
    }
    PlayerEffectPoolUpdate_00428280(player);
    return 1;
}
#pragma code_seg()
