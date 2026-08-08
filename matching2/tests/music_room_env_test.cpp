#include "th10/game/ui_final_runtime.hpp"
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace th10;

unsigned int DAT_00491fb8=0,DAT_00491ff4=0,DAT_00474c4c=0,
             DAT_00474c7c=0,DAT_00474c84=0,DAT_00474c8c=0;
unsigned int DAT_00474c68=0,DAT_00474c6c=0,DAT_00474c70=0,
             DAT_00474c74=0,DAT_00474ca0=0,DAT_00474e5c=0,DAT_00474e62=0;
unsigned char* DAT_004776f4=nullptr;
unsigned char* DAT_00477704=nullptr;
unsigned char* DAT_0047770c=nullptr;
unsigned char* DAT_0047783c=nullptr;
unsigned char* DAT_00477830=nullptr;
unsigned char* DAT_00477848=nullptr;
unsigned int DAT_00474c40=0;
unsigned short DAT_00474c48=0;
unsigned int DAT_00491c28=0;
float DAT_00476f78=1.0f;

namespace {
struct Probe {
  std::vector<int> registered;
  std::vector<int> depths;
  std::vector<int> stopped;
  std::vector<int> queries;
  std::vector<int> marked;
  std::vector<std::string> texts;
  std::vector<unsigned> text_colors;
  std::vector<int> position_modes; // 0 = immediate, 1 = sub_434A80 ramp
  std::vector<float> position_y;
  std::array<float,2048> current_y{};
  const ui_final::MusicRoom* history_arg{};
  int play_channel{-1};
  std::string play_title;
  std::array<bool,8> played{};
};
Probe* probe;

int RegisterAnm(void*,void*,int sprite){
  probe->registered.push_back(sprite);
  return sprite+1000;
}
int ResolveAnm(void*,int handle){return handle==0?0:handle;}
void DrawText(void*,int,unsigned color,const char* text){
  probe->text_colors.push_back(color);
  probe->texts.emplace_back(text==nullptr?"":text);
}
void SetDepth(void*,int handle,int depth){
  probe->depths.push_back(handle);
  probe->depths.push_back(depth);
}
void SetVisible(void*,int,bool){ }
void SetPosition(void*,int,float,float y,float){
  probe->position_modes.push_back(0);
  probe->position_y.push_back(y);
}
bool GetPositionY(void*,int handle,float* y){
  if(handle<0||handle>=(int)probe->current_y.size())return false;
  *y=probe->current_y[(std::size_t)handle];
  return true;
}
void SetPositionRamp(void*,int,float,float y,float){
  probe->position_modes.push_back(1);
  probe->position_y.push_back(y);
}
void StopAnm(void*,int handle){probe->stopped.push_back(handle);}
void PlaySound(int){ }
bool IsTrackPlayed(int track){
  probe->queries.push_back(track);
  return track>=0&&track<(int)probe->played.size()&&probe->played[track];
}
void MarkTrackPlayed(int track){probe->marked.push_back(track);probe->played[track]=true;}
const char* PreviewText(int frame){
  static const char* text[8]={"Preview 0","Preview 1","Preview 2","Preview 3",
                              "Preview 4","Preview 5","Preview 6","Preview 7"};
  return frame>=0&&frame<8?text[frame]:"";
}
void PlayMusic(int channel,const char* title){
  probe->play_channel=channel;
  probe->play_title=title==nullptr?"":title;
}
void HistoryPop(ui_final::MusicRoom& state){
  probe->history_arg=&state;
  state.selection=7;
  state.track_count=8;
}

ui_final::MusicRoomEnv MakeEnv(Probe& p){
  probe=&p;
  ui_final::MusicRoomEnv env{};
  env.register_anm=RegisterAnm;
  env.resolve_anm=ResolveAnm;
  env.draw_text=DrawText;
  env.set_depth=SetDepth;
  env.set_visible=SetVisible;
  env.set_position=SetPosition;
  env.get_position_y=GetPositionY;
  env.set_position_ramp=SetPositionRamp;
  env.preview_text=PreviewText;
  env.stop_anm=StopAnm;
  env.play_sound=PlaySound;
  env.is_track_played=IsTrackPlayed;
  env.mark_track_played=MarkTrackPlayed;
  env.play_music=PlayMusic;
  return env;
}
}

int main(){
  // The four-argument retail overload consumes, but does not advance, +0x2B4.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=3;
    state.timer=7;
    state.ramp_counter=91;
    ui_final::UpdateMusicRoom(state,env,0,"");
    assert(state.timer==7&&state.ramp_counter==91);
    state.phase=1;
    state.timer=4;
    ui_final::UpdateMusicRoom(state,env,0,"");
    assert(state.phase==1&&state.timer==4);
    state.timer=5;
    ui_final::UpdateMusicRoom(state,env,0,"");
    assert(state.phase==2&&state.timer==0);
  }

  // Retail music playback is channel 0 and uses the title. The row query is
  // indexed by the selected track, while the retail playback write targets
  // the played-table base byte exactly as disassembled.
  {
    Probe p;
    p.played[1]=true;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=2;
    state.selection=1;
    state.titles={"ignored","Track title"};
    state.played_tracks={0,0};
    ui_final::UpdateMusicRoom(state,env,0x1001,"");
    assert(p.play_channel==0&&p.play_title=="Track title");
    assert(!p.queries.empty()&&p.queries.back()==1);
    assert(p.marked.size()==1&&p.marked[0]==0&&p.played[0]);
  }

  // Preview frames use the encoded off_476FD8 text and 0x8080FF, while the
  // played path above uses the parsed title and normal text color.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=1;
    state.selection=0;
    state.displayed=0;
    state.armed=true;
    state.played_tracks={0};
    state.frame_handles[0]=201;
    ui_final::UpdateMusicRoom(state,env,0,"");
    assert(p.texts.size()==1&&p.texts[0]=="Preview 0"&&
           p.text_colors[0]==0x008080FFu);
  }

  // sub_44BE70 receives and owns the music-room history operation. A callback
  // mutation is not overwritten by a second local pop.
  {
    Probe p;
    auto env=MakeEnv(p);
    env.history_pop=HistoryPop;
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=3;
    state.selection=1;
    ui_final::UpdateMusicRoom(state,env,0xA,"");
    assert(p.history_arg==&state&&state.selection==7&&state.track_count==8);
  }

  // Cleanup stops rows at depth 1 and keeps their handles. The phase-3
  // fallback follows the same stop-only contract and also remains populated.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=2;
    state.row_handles={101,102};
    state.frame_handles={201,202,203,204,205,206,207,208};
    ui_final::UpdateMusicRoom(state,env,0xA,"");
    assert(state.phase==3&&state.row_handles.size()==2&&
           state.row_handles[0]==101&&state.row_handles[1]==102);
    assert(p.stopped.size()==2&&p.stopped[0]==101&&p.stopped[1]==102);
    assert(p.depths.size()==18&&p.depths[16]==208&&p.depths[17]==1);
    state.timer=10;
    state.parent_handle=301;
    state.auxiliary_handle=302;
    state.fallback_handle=303;
    ui_final::UpdateMusicRoom(state,env,0,"");
    assert(state.phase==0&&state.parent_handle==0&&state.auxiliary_handle==0&&
           state.fallback_handle==303);
    assert(p.stopped.size()==3&&p.stopped.back()==303);
  }

  // The menu cursor wraps as sub_44BEA0 does instead of clamping at an edge.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=3;
    state.selection=0;
    ui_final::UpdateMusicRoom(state,env,0x10,"");
    assert(state.selection==2);
    ui_final::UpdateMusicRoom(state,env,0x20,"");
    assert(state.selection==0);
  }

  // Selection changes use sub_434A80 only when the existing row Y is within
  // 40 units of the target; a distant row takes the immediate-write branch.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=2;
    state.selection=0;
    state.row_handles={101,102};
    p.current_y[101]=94.0f; // target 96: ramp
    p.current_y[102]=0.0f;  // target 116: immediate
    ui_final::UpdateMusicRoom(state,env,0x20,"");
    assert(state.selection==1&&p.position_modes.size()==2&&
           p.position_modes[0]==1&&p.position_modes[1]==0);
  }

  // The host history model mirrors sub_44BE70's cursor mutation without
  // erasing the retail backing entries.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.phase=2;
    state.track_count=9;
    state.selection=8;
    state.history={{2,3},{6,7}};
    ui_final::UpdateMusicRoom(state,env,0xA,"");
    assert(state.phase==3&&state.selection==6&&state.track_count==7&&
           state.history.size()==2&&state.history_cursor==1);
    state.timer=10;
    ui_final::UpdateMusicRoom(state,env,0,"");
    assert(state.phase==0&&state.selection==2&&state.track_count==3&&
           state.history.size()==2&&state.history_cursor==0);
  }

  // Retail parser rows are title, comment, then eight fixed-size row strings.
  {
    Probe p;
    auto env=MakeEnv(p);
    ui_final::MusicRoom state;
    state.timer=1;
    const std::string resource=
      "# comment\r\n@Song A\r\nComment A\r\nA0\r\nA1\r\nA2\r\nA3\r\nA4\r\nA5\r\nA6\r\nA7\r\n"
      "@Song B\nComment B\nB0\nB1\nB2\nB3\nB4\nB5\nB6\nB7\n";
    ui_final::UpdateMusicRoom(state,env,0,resource);
    assert(state.timer==1&&state.track_count==2);
    assert(state.titles[0]=="Song A"&&state.comments[0]=="Comment A");
    assert(state.row_texts.size()==16&&state.row_texts[0]=="A0"&&
           state.row_texts[7]=="A7"&&state.row_texts[8]=="B0"&&
           state.row_texts[15]=="B7");
    assert(state.events.empty()&&!p.registered.empty());
  }

  // The shared room timer follows the frame-speed gate: paused frames do not
  // advance, while fractional speeds retain their accumulated fraction.
  {
    ui_final::MusicRoom state;
    float speed=0.0f;
    ui_final::AdvanceMusicRoomTimer(state,&speed);
    assert(state.timer==0);
    speed=1.0f;
    ui_final::AdvanceMusicRoomTimer(state,&speed);
    assert(state.timer==1);
    speed=0.5f;
    ui_final::AdvanceMusicRoomTimer(state,&speed);
    assert(state.timer==1);
    ui_final::AdvanceMusicRoomTimer(state,&speed);
    assert(state.timer==2);
  }

  // The old overload retains its fixture parser/clock without being selected
  // by the retail env API.
  {
    ui_final::MusicRoom state;
    assert(ui_final::UpdateMusicRoom(state,0,"@a\n@b\n@c\n")==0&&
           state.track_count==3&&state.events.size()==8);
    state.timer=9;
    ui_final::UpdateMusicRoom(state,0,"");
    assert(state.phase==1);
  }

  std::cout<<"MUSIC_ROOM_ENV_TESTS_PASS\n";
}
