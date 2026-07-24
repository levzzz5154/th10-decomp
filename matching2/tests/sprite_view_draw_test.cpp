#include "th10/game/sprite_test_overlay.hpp"
#include <cstdio>
#include <cstring>
static unsigned c;static int n,g;static char last[160];static const char*R(int){return"main";}static int E(){return 7;}static void D(const SpriteViewPoint*,const char*s){n++;std::strcpy(last,s);}static void G(SpriteView*){g++;}int main(){const char*f[]={"a"};SpriteView v={1,f,0,1,2,3,{0,0},2,{}};SpriteViewEnv e={&c,R,E,D,G};if(SpriteView_DrawDebugOverlay(&v,&e)!=1||n!=5||g!=1||c!=0xffffffff||std::strcmp(last,">"))return 1;std::puts("recovery_batch39_test passed");}
