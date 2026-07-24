#include "th10/game/item_spawn.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>
static int fails;
#define CHECK(x) do{if(!(x)){std::printf("FAIL %d %s\n",__LINE__,#x);++fails;}}while(0)
static int retire_n,retire_id,load_n,load_script;static float frame=1.0f;
static void Velocity(float v[2],float a,float s){v[0]=a;v[1]=s;}static void Retire(Item*,int id){++retire_n;retire_id=id;}static void Load(Item*,int s){++load_n;load_script=s;}
static ItemSpawnEnv Env(short bombs=0){ItemSpawnEnv e={bombs,&frame,Velocity,Retire,Load};return e;}
static ItemManager* NewManager(){static ItemManager m;std::memset(&m,0,sizeof(m));retire_n=retire_id=load_n=load_script=0;return &m;}
static void TestNormal(){ItemManager*m=NewManager();float p[3]={250,2,3};ItemSpawnEnv e=Env();CHECK(ItemManager_Spawn(m,p,2,77,-1.5f,2.2f,&e)==0);Item&i=m->normal[0];CHECK(i.state==1&&i.position[0]==192&&i.position[1]==2&&i.position[2]==3);CHECK(i.velocity[0]==-1.5f&&std::fabs(i.velocity[1]-2.2f)<1e-6f);CHECK(i.timer.target==-1&&i.timer.current==0&&i.timer.previous==0&&(i.timer.flags&1)&&i.timer.speed==&frame);CHECK(i.kind==2&&i.display_kind==2&&i.identifier==77);CHECK(load_n==1&&load_script==376);}
static void TestClampAndKinds(){ItemManager*m=NewManager();float p[3]={-300,0,0};ItemSpawnEnv e=Env();m->normal[0].kind=3;ItemManager_Spawn(m,p,10,9,0,1,&e);CHECK(m->normal[0].position[0]==-192);CHECK(m->normal[0].kind==10&&m->normal[0].display_kind==1&&load_script==375);CHECK(retire_n==1&&retire_id==393);m=NewManager();e=Env();ItemManager_Spawn(m,p,11,0,0,0,&e);CHECK(m->normal[0].display_kind==4&&load_script==378);m=NewManager();e=Env(100);ItemManager_Spawn(m,p,1,0,0,0,&e);CHECK(m->normal[0].kind==9&&load_script==383);m=NewManager();e=Env(100);ItemManager_Spawn(m,p,11,0,0,0,&e);CHECK(m->normal[0].kind==5&&load_script==379);}
static void TestPoolFull(){ItemManager*m=NewManager();for(int i=0;i<150;++i)m->normal[i].state=1;float p[3]={0,0,0};ItemSpawnEnv e=Env();ItemManager_Spawn(m,p,2,0,0,0,&e);CHECK(load_n==0);}
static void TestSpecialBands(){ItemManager*m=NewManager();float p[3]={300,4,5};ItemSpawnEnv e=Env();m->special_cursor=7;m->special_count=254;ItemManager_Spawn(m,p,8,-1,1,0.6f,&e);Item&i=m->special[7];CHECK(i.state==5&&i.kind==8&&i.display_kind==8&&i.variant==3);CHECK(i.position[0]==300&&m->special_cursor==8&&m->special_count==255);m=NewManager();m->special_cursor=7;m->special_count=255;ItemManager_Spawn(m,p,8,0,0,0,&e);CHECK(m->special[7].variant==11);m=NewManager();m->special_cursor=17;m->special_count=511;ItemManager_Spawn(m,p,8,0,0,0,&e);CHECK(m->special[17].variant==9);m=NewManager();m->special_cursor=33;m->special_count=1023;ItemManager_Spawn(m,p,8,0,0,0,&e);CHECK(m->special[33].variant==17);}
static void TestOccupiedSpecial(){ItemManager*m=NewManager();m->special_cursor=2047;m->special[2047].state=4;float p[3]={0,0,0};ItemSpawnEnv e=Env();ItemManager_Spawn(m,p,8,0,0,0,&e);CHECK(m->special[2047].state==4&&m->special_cursor==0&&m->special_count==1);}
int main(){TestNormal();TestClampAndKinds();TestPoolFull();TestSpecialBands();TestOccupiedSpecial();if(fails)return 1;std::printf("recovery_batch30_test passed\n");}
