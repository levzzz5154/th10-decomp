#include "th10/game/score_menu_rows.hpp"
#include <cstdio>
static unsigned c,cs[6];static int p,n;static void D(const char*){cs[n++]=c;}int main(){ScoreMenu m={3,2,2,{}};for(auto&r:m.rows)r={"ROW",1,1};ScoreMenuEnv e={&c,&p,D};if(ScoreMenu_DrawRows(&m,&e)!=1||n!=6||cs[2]!=0xff000000||c!=0xffffffff||p)return 1;std::puts("recovery_batch41_test passed");}
