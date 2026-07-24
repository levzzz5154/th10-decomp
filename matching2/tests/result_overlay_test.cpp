#include "th10/game/result_overlay.hpp"
#include <cstdio>
#include <cstring>
static int fails;
#define CHECK(x) do{if(!(x)){std::printf("FAIL %d %s\n",__LINE__,#x);++fails;}}while(0)
static int retired[32],retired_n,created_scripts[16],created_n,assigned[8],registered_n,configured[8],shown[8],hidden[8];static ResultDigitVm vms[8];
static void Retire(int h){retired[retired_n++]=h;}static int Create(void*,int s,int l){CHECK(l==15);created_scripts[created_n++]=s;return 1000+s;}
static ResultDigitVm* Allocate(){return &vms[registered_n];}static void Assign(void*,ResultDigitVm*,int s){assigned[registered_n]=s;}static int Register(ResultDigitVm*){return 200+registered_n++;}
static void Configure(int h,int s){configured[h-200]=s;}static void Show(int* h){shown[*h-200]++;}static void Hide(int* h){hidden[*h-200]++;}
static ResultOverlayEnv Env(){ResultOverlayEnv e={Retire,Create,Allocate,Assign,Register,Configure,Show,Hide};return e;}
static void Reset(){std::memset(retired,0,sizeof(retired));std::memset(created_scripts,0,sizeof(created_scripts));std::memset(vms,0,sizeof(vms));std::memset(assigned,0,sizeof(assigned));std::memset(configured,0,sizeof(configured));std::memset(shown,0,sizeof(shown));std::memset(hidden,0,sizeof(hidden));retired_n=created_n=registered_n=0;}
static void TestDigits(){Reset();ResultOverlayState s={};s.main_handle=7;s.resource=&s;for(int i=0;i<8;++i)s.digit_handles[i]=10+i;ResultOverlayEnv e=Env();ResultOverlay_SetMode(&s,0,12034,&e);CHECK(retired_n==9&&retired[0]==7);CHECK(created_n==1&&created_scripts[0]==71&&s.main_handle==1071);for(int i=0;i<8;++i){CHECK(assigned[i]==39+i);CHECK(s.digit_handles[i]==200+i);CHECK(vms[i].layer==15&&(vms[i].flags&0x40000000u));}int expect[8]={8,8,8,9,10,8,11,12};for(int i=0;i<8;++i)CHECK(configured[i]==expect[i]);CHECK(hidden[0]&&hidden[1]&&hidden[2]);for(int i=3;i<8;++i)CHECK(shown[i]);}
static void TestZeroHidden(){Reset();ResultOverlayState s={};ResultOverlayEnv e=Env();ResultOverlay_SetMode(&s,0,0,&e);for(int i=0;i<8;++i){CHECK(hidden[i]==1);CHECK(shown[i]==0);CHECK(configured[i]==8);}}
static void TestModes(){Reset();ResultOverlayState s={};s.main_handle=1;s.secondary_handle=2;ResultOverlayEnv e=Env();ResultOverlay_SetMode(&s,1,0,&e);CHECK(s.main_handle==1072);ResultOverlay_SetMode(&s,2,0,&e);CHECK(s.secondary_handle==1073);ResultOverlay_SetMode(&s,3,0,&e);CHECK(s.secondary_handle==1074);ResultOverlay_SetMode(&s,4,0,&e);CHECK(s.secondary_handle==1075);ResultOverlay_SetMode(&s,6,0,&e);CHECK(s.main_handle==1076);int before=created_n;ResultOverlay_SetMode(&s,5,0,&e);ResultOverlay_SetMode(&s,99,0,&e);CHECK(created_n==before);}
int main(){TestDigits();TestZeroHidden();TestModes();if(fails)return 1;std::printf("recovery_batch29_test passed\n");}
