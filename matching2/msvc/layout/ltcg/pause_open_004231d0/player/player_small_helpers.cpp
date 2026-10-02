#include "th10/game/pause_result_open_004231d0/player/player_state.hpp"
extern "C" double __cdecl atan2(double,double);
extern "C" float data_00470b94;

// Complete helper bodies, with only actual object/value inputs.
#pragma code_seg(".text$00405410_fn")
void PlayerSchedulerRecord::SetSchedulerValue(int value) {
    if (!(flags_10&1)) {
        field_04=0;
        field_00=-999999;
        field_08=0.0f;
        field_0C=&data_00476f78;
        flags_10 |= 1;
    }
    field_04=value;
    field_00=value-1;
    field_08=(float)value;
}
#pragma code_seg(".text$0040ac90_fn")
void PlayerSetInputMode_0040ac90(InputState_00425730* state,int mode) {
    state->mode=(state->flags&0x1000)?2:mode;
}
#pragma code_seg(".text$00426610_fn")
double Entity_AngleToPoint(const EntityAngleTarget_00426610* entity,const float* point) {
    float horizontal=point[0]-entity->x;
    float vertical=point[1]-entity->y;
    if (vertical==data_00470b04 && horizontal==data_00470b04)
        return data_00470b94;
    return atan2((double)vertical,(double)horizontal);
}
#pragma code_seg(".text$004054b0_fn")
void PowerDisplayOwner_004054b0::SetPowerDigits(int whole,int fraction) {
    // This is the existing complete 79-byte digit owner behavior.
    sprites->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(whole_digit),whole+8);
    sprites->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(tens_digit),fraction/10+8);
    sprites->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(ones_digit),fraction%10+8);
}
#pragma code_seg(".text$0041c800_fn")
int ScoreRecords_0041c800::CopyVectorAndEvaluate(const float* vector,float value,int flag) {
    ScoreLinkedRecord_0041c800* record=linked_head;
    vector_440=*reinterpret_cast<const Vector3_0041c800*>(vector);
    int total=0;
    while (record) {
        ScoreLinkedRecord_0041c800* next=record->next;
        if (record->type!=1) total += record->Slot1C(vector,value,flag);
        record=next;
    }
    return total;
}
#pragma code_seg()
