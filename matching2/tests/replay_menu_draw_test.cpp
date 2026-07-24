#include "th10/game/replay_menu_draw.hpp"
#include <cstdio>
#include <cstring>
static int fails;
#define CHECK(x) do { if(!(x)){std::printf("FAIL %d %s\n",__LINE__,#x);++fails;} } while(0)
static ReplayMenuDrawState rs; static char out[64][192]; static ReplayMenuPoint pos[64]; static unsigned col[64]; static int n;
static const char* shots[]={"ReimuA","ReimuB","ReimuC"}; static const char* diffs[]={"Easy","Normal","Hard"}; static const char* stages[]={"St0","St1","St2"};
static ReplayMenuDate Date(int t){ if(t==1){ReplayMenuDate d={2026,7,24,12,34};return d;} ReplayMenuDate d={2025,12,31,23,59};return d;}
static void Draw(const ReplayMenuPoint* p,const char* s){pos[n]=*p;col[n]=rs.color;std::strncpy(out[n],s,191);out[n][191]=0;++n;}
static ReplayMenuDrawEnv Env(){ReplayMenuDrawEnv e={};e.render=&rs;e.charset="ABCDEFGHIJKLMxyz";e.character_shot_labels=shots;e.difficulty_labels=diffs;e.stage_labels=stages;e.all_stages_label="All";e.decode_date=Date;e.draw_text=Draw;return e;}
static void Reset(){std::memset(&rs,0,sizeof(rs));std::memset(out,0,sizeof(out));n=0;}
static void TestList(){Reset();ReplayMenu m={};m.state=2;m.selected_index=1;ReplayMenuInfo i={"REP",1,75.5f,0,1,2,1};ReplayMenuSlot s={&i};m.replay_slots[1]=&s;ReplayMenuDrawEnv e=Env();CHECK(ReplayManager_Draw(&m,&e)==1);CHECK(n==25);CHECK(std::strcmp(out[0],"No.01 -------- --/--/-- --:-- ------- ------- --- ---%")==0);CHECK(std::strcmp(out[1],"No.02 REP 26/07/24 12:34 ReimuB Hard St1 75.5%")==0);CHECK(pos[0].y==80.0f&&pos[24].y==440.0f);CHECK(col[0]==0xFF808080u&&col[1]==0xFFFFFF00u);CHECK(rs.color==0xFFFFFFFFu&&rs.busy==0);}
static void TestEntryTween(){Reset();ReplayMenu m={};m.state=3;m.entry_index=4;m.transition_frame=5;m.transition_progress=5.0f;ReplayMenuInfo i={"X",2,100.0f,0,0,1,2};ReplayMenuDrawEnv e=Env();e.selected_replay=&i;CHECK(ReplayManager_Draw(&m,&e)==1);CHECK(n==1);CHECK(pos[0].y==190.0f);CHECK(std::strstr(out[0],"No.05          25/12/31 23:59 ReimuA Normal All 100.0%")!=0);}
static void TestEditor(){Reset();ReplayMenu m={};m.state=3;m.entry_index=0;m.transition_frame=10;std::strcpy(m.entered_name,"ABC");m.name_cursor=8;m.charset_cursor=2;ReplayMenuInfo i={"X",2,1.0f,0,0,0,0};ReplayMenuDrawEnv e=Env();e.selected_replay=&i;CHECK(ReplayManager_Draw(&m,&e)==1);CHECK(n==3+(int)std::strlen(e.charset));CHECK(std::strcmp(out[1],"ABC")==0&&std::strcmp(out[2],"_")==0);CHECK(pos[2].x==175.0f);CHECK(col[5]==0xFFFFFF00u);int len=(int)std::strlen(e.charset);CHECK((unsigned char)out[3+len-3][0]==129);CHECK((unsigned char)out[3+len-2][0]==127);CHECK((unsigned char)out[3+len-1][0]==128);CHECK(pos[3].x==212.0f&&pos[16].x==212.0f&&pos[16].y==376.0f);}
static void TestDefault(){Reset();ReplayMenu m={};m.state=1;ReplayMenuDrawEnv e=Env();CHECK(ReplayManager_Draw(&m,&e)==1&&n==0);}
int main(){TestList();TestEntryTween();TestEditor();TestDefault();if(fails)return 1;std::printf("recovery_batch27_test passed\n");}
