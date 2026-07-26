#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

#include "th10/game/laser_segment_cut.hpp"

namespace {
std::vector<LaserCutState> clones;
std::vector<int> scripts;
std::vector<float> spark_x;
int items;
void Spark(void*, const float p[3], int script) { spark_x.push_back(p[0]); scripts.push_back(script); }
void Item(void*, const float[3], int kind, int id, float angle, float speed) { assert(kind==8&&id==-1); assert(std::fabs(angle+1.5707964f)<1e-6f&&speed==0.6f); ++items; }
int Outside(void*, const float*, float, float) { return 0; }
void Clone(void*, const LaserCutState* s) { clones.push_back(*s); }
LaserCutOps Ops(){return {0,Spark,Item,Outside,Clone};}
LaserCutState Laser(){LaserCutState l={{0,100,5},0,78,9,200,3,4,2,false,0,78};return l;}
void Clear(){clones.clear();scripts.clear();spark_x.clear();items=0;}
}
int main(){LaserCutOps ops=Ops();
 {Clear(); auto l=Laser(); float c[3]={30,100,0}; int n=LaserCut_Circle(&l,c,7,1,&ops); assert(n==1&&l.length==24); assert(clones.size()==1); assert(clones[0].origin[0]==36&&clones[0].length==36&&clones[0].width==36&&clones[0].distance_budget==164); assert(scripts[0]==21&&spark_x[0]==254&&items==1);}
 {Clear(); auto l=Laser(); float c[3]={12,100,0}; int n=LaserCut_Circle(&l,c,7,0,&ops); assert(n==2&&l.length==0); assert(clones.size()==1&&clones[0].origin[0]==24&&clones[0].length==48);}
 {Clear(); auto l=Laser(); LaserCutRegion r={{30,100,0},{24,10,0}}; int n=LaserCut_Rectangle(&l,&r,0,&ops); assert(n==3&&l.length==12); assert(clones.size()==1&&clones[0].origin[0]==48&&clones[0].length==24); assert(spark_x[0]==18&&scripts[0]==21);}
 {Clear(); auto l=Laser(); float c[3]={300,300,0}; assert(LaserCut_Circle(&l,c,1,0,&ops)==0); assert(l.length==78&&clones.empty());}
 {Clear(); auto l=Laser(); l.length=l.length_limit=90; float c[3]={12,100,0}; int n=LaserTrim_Circle(&l,c,7,0,&ops); assert(n==2&&!l.retired); assert(l.origin[0]==24&&l.length==66&&l.length_limit==66&&l.traveled==24);}
 {Clear(); auto l=Laser(); l.length=l.length_limit=90; float c[3]={42,100,0}; int n=LaserTrim_Circle(&l,c,7,0,&ops); assert(n==1&&!l.retired); assert(l.length==36&&l.length_limit==36); assert(clones.size()==1&&clones[0].origin[0]==48&&clones[0].length==36); assert(scripts[0]==25);}
 {Clear(); auto l=Laser(); l.length=l.length_limit=90; LaserCutRegion r={{42,100,0},{13,10,0}}; int n=LaserTrim_Rectangle(&l,&r,1,&ops); assert(n==1&&l.length==36); assert(clones.size()==1&&clones[0].origin[0]==48); assert(spark_x[0]==42&&items==1);}
 {Clear(); auto l=Laser(); l.length=l.length_limit=30; float c[3]={18,100,0}; int n=LaserTrim_Circle(&l,c,100,0,&ops); assert(n==2&&l.retired);}
 std::puts("LASER_SEGMENT_CUT_TESTS_PASS");}
