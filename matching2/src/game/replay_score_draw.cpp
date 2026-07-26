#include "th10/game/replay_score_draw.hpp"
#include <cstdarg>
#include <cstdio>
namespace {
void Draw(const ReplayScoreDrawEnv* e,const char* f,...){char b[192];va_list a;va_start(a,f);std::vsnprintf(b,sizeof(b),f,a);va_end(a);e->draw_text(e->render,b);}
}
// 0x004329F0 - Semantic reconstruction of the replay-score page draw.
// PE32 establishes the otherwise-missed context in EDI and returns with a
// plain `retn`; the conventional form makes that input explicit.
int ReplayScore_Draw(const ReplayScorePage* p,const ReplayScoreDrawEnv* e){
    if(p->state!=2)return 1;
    ReplayScoreDrawState& r=*e->render;r.busy=1;r.x=40.0f;r.y=160.0f;r.z=0.0f;
    if(!p->suppress_entries){
        const ReplayScoreEntry* q=e->data->entries+p->page*10;
        for(int i=0;i<10;++i){
            unsigned shade=0xffu-(unsigned)i*0x10u;r.color=0xff0000ffu|(shade<<8)|(shade<<16);
            const ReplayScoreEntry& x=q[i];
            if(x.timestamp){ReplayScoreDate d=e->decode_time(x.timestamp);Draw(e,"%2d  %s  %9ld%d  %.4d/%.2d/%.2d %.2d:%.2d  %s  %2.1f%%",i+1,x.name,(long)x.score,(int)x.stage,d.year,d.month,d.day,d.hour,d.minute,e->difficulty_labels[(unsigned char)x.difficulty],(double)x.clear_percent);}
            else Draw(e,"%2d  %s  %9ld%d  ----/--/-- --:--  Stage -  ---%%",i+1,x.name,(long)x.score,(int)x.stage);
            r.y+=15.0f;
        }
    }
    r.color=0xffffffffu;r.x=328.0f;r.y=378.0f;Draw(e,"    %5d",e->data->current_score[p->difficulty]);
    int t=e->data->elapsed_seconds[p->difficulty];r.y=396.0f;Draw(e,"%3d:%.2d:%.2d",t/3600,(t/60)%60,t%60);
    r.y=414.0f;Draw(e,"    %5d",e->data->stage_scores[p->difficulty][p->page]);
    r.color=0xffffffffu;r.busy=0;return 1;
}
