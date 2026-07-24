#include "th10/game/line_effect_sweep.hpp"
#include <cstdio>
static int s,i,sc;static void S(const float*,int x){s++;sc=x;}static void I(const float*,int,int,float,float){i++;}int main(){LineEffect l={0,{0,100,0},0,31,3};LineEffectSweepEnv e={S,I};if(LineEffect_SweepIntoItems(&l,1,&e)!=2||s!=2||i!=2||sc!=23||!l.finished)return 1;std::puts("recovery_batch37_test passed");}
