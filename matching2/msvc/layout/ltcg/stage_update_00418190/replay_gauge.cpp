#include "types.hpp"
#pragma code_seg(".text$00428e10_fn")
int Player_0042a450::SetBossGauge(const ReplayGaugeCounters_0042a6a0* source) {
    int* counters=&boss_gauge.value; counters[0]=source->value; counters[1]=source->maximum;
    *(float*)((char*)this+0x3c0)=float(boss_gauge.value)*0.01f;
    *(float*)((char*)this+0x3c4)=float(boss_gauge.maximum)*0.01f;
    for(int index=0;index<4;++index) options[index].flag=1;
    return reinterpret_cast<int>(this);
}
#pragma code_seg()
