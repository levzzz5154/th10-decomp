#include "th10/game/replay_stage_name_draw.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstring>
namespace{void D(const ReplayStageNameEnv*e,const char*f,...){char b[192];va_list a;va_start(a,f);std::vsnprintf(b,sizeof b,f,a);va_end(a);e->draw_text(e->render,b);}}
// 0x00433230 - Semantic reconstruction of stage replay/name-entry drawing.
int ReplayStageName_Draw(const ReplayStageNamePage*p,const ReplayStageNameEnv*e){if(p->state!=2)return 1;auto&r=*e->render;r.busy=1;r.x=40;r.y=160;r.z=0;const ReplayScoreEntry*q=e->entries+(e->replay_group*10);for(int i=0;i<10;++i){if(p->fade_rows){unsigned a=0xffu-i*0x10u;r.color=0xff0000ffu|(a<<8)|(a<<16);}else r.color=i==p->selection?0xffffff00u:0xff404040u;const auto&x=q[i];if(x.timestamp){auto d=e->decode_time(x.timestamp);D(e,"%2d  %s  %9ld%d  %.4d/%.2d/%.2d %.2d:%.2d  %s  %2.1f%%",i+1,x.name,(long)x.score,(int)x.stage,d.year,d.month,d.day,d.hour,d.minute,e->difficulty_labels[(unsigned char)x.difficulty],(double)x.clear_percent);}else D(e,"%2d  %s  %9ld%d  ----/--/-- --:--  Stage -  ---%%",i+1,x.name,(long)x.score,(int)x.stage);r.y+=18;}
 if(!p->fade_rows){r.color=0xffffffffu;r.x=84;r.y=p->selection*18.0f+160;D(e,"%s",p->name);r.color=0xffffff00u;r.x=84+p->name_cursor*9.0f-(p->name_cursor==8?9.0f:0.0f);D(e,"_");int n=(int)std::strlen(e->charset);r.x=212;r.y=360;for(int i=0;i<n;++i){r.color=i==p->charset_cursor?0xffffff00u:0xff808080u;int c=i<n-3?(unsigned char)e->charset[i]:i==n-3?129:i==n-2?127:128;D(e,"%c",c);if(i%13==12){r.x=212;r.y+=16;}else r.x+=18;}r.color=0xffffffffu;}return 1;}
