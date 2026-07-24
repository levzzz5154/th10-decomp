#include "th10/render/composite_passes.hpp"
#include <cstdio>
static CompositeGlobalRenderState g;static int p,st,q;static void F(){}static void P(const unsigned*){p++;}static void S(){ }static void R(int,unsigned){}static void D(){st++;}static void Q(CompositeState*){q++;}static void T(CompositeState*s,float){s->counter--;}int main(){CompositeState s={};s.flags=1|2;s.counter=1;CompositeEnv e={&g,F,P,S,R,D,Q,T};if(CompositeEffect_Draw(&s,&e)!=1||p!=1||st!=2||q!=4||s.counter||!(s.flags&8)||s.visibility!=255)return 1;std::puts("recovery_batch36_test passed");}
