#include "th10/game/trajectory_evaluate.hpp"
#include <cstdio>
static float one=1;static float E(float a,float b){return a/b;}int main(){Trajectory2D s={};s.p0[0]=1;s.velocity[0]=3;s.speed=&one;s.duration=10;s.mode=7;float o[2];TrajectoryEnv e={&one,E};Trajectory_Evaluate2D(&s,o,&e);if(o[0]!=4||s.current!=1)return 1;s.mode=0;s.current=9;s.elapsed=9;s.velocity[0]=8;Trajectory_Evaluate2D(&s,o,&e);if(s.duration||o[0]!=8)return 1;std::puts("recovery_batch38_test passed");}
