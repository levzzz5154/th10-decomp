#include "th10/game/item_scatter.hpp"
#include <cstdio>
static int n,k[8],ri,rs;static float U(){return ri++?1:.5f;}static float S(){++rs;return 0;}static void P(const ItemDropVec3&,int x,int id,float a,float s){k[n++]=x;if(id!=-1||a> -1.5f||s!=2.2f)n=99;}int main(){ItemDropPlan p={};p.counts[0]=2;p.counts[10]=1;p.counts[11]=9;p.radius_x=p.radius_y=1;ItemDropEnv e={U,S,P};int r=ItemDrop_ScatterGroups(&p,&e);for(int x:p.counts)if(x)return 1;if(r!=3||n!=3||k[0]!=1||k[2]!=11||rs!=3)return 1;std::puts("recovery_batch31_test passed");}
