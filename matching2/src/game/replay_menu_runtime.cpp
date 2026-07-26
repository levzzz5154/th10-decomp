#include "th10/game/replay_menu_runtime.hpp"
#include <cstdio>
namespace th10::replay_menu {
namespace {
std::string numbered(int n){char b[20];std::snprintf(b,sizeof b,"th10_%.2d.rpy",n);return b;}
void edge_transition(const ReplayMenuEdges&e,int p){if(e.transition)e.transition(e.context,p);} void edge_sound(const ReplayMenuEdges&e,int s){if(e.sound)e.sound(e.context,s);}
void edge_transition(const ReplayNameEdges&e,int p){if(e.transition)e.transition(e.context,p);} void edge_sound(const ReplayNameEdges&e,int s){if(e.sound)e.sound(e.context,s);}
int wrap(int v,int n){return n?((v%n)+n)%n:0;}
}
// Semantic reconstruction of retail 0x004315C0. External loading, animation,
// audio and replay launch remain explicit dependency edges; their internals
// are not attributed to this function.
int ReplayLoadMenu_Update(ReplayMenuState&s,std::uint32_t p,const ReplayMenuEdges&e){
 switch(s.phase){
  case 0:{s.previous_selection=s.selection;s.selection=wrap(s.selection,25);for(auto*&q:s.slots){if(q&&e.release)e.release(e.context,q);q=nullptr;}for(int i=0;i<25;++i)if(e.load)s.slots[i]=e.load(e.context,numbered(i+1));if(e.enumerate_user_files){auto files=e.enumerate_user_files(e.context);for(std::size_t i=0;i<files.size()&&i<25;++i)if(e.load)s.slots[25+i]=e.load(e.context,files[i]);}s.timer=0;s.phase=1;edge_transition(e,1);break;}
  case 1:if(s.timer>6){s.phase=2;s.timer=0;}break;
  case 2:{s.previous_selection=s.selection;if((p&0x10))s.selection=wrap(s.selection-1,50);if((p&0x20))s.selection=wrap(s.selection+1,50);if(s.selection!=s.previous_selection)edge_sound(e,0);if(p&0x0a){s.phase=5;edge_transition(e,5);edge_sound(e,0);break;}if((p&0x1001)&&s.slots[s.selection]){s.chosen_slot=s.selection;s.stage_count=0;for(int i=0;i<7;++i)if(s.slots[s.selection]->stage_present[i])s.available_stages[s.stage_count++]=i;s.chosen_stage=0;s.phase=4;s.timer=0;edge_transition(e,4);edge_sound(e,0);if(s.stage_count){s.chosen_stage=wrap(s.chosen_stage-1,s.stage_count);s.chosen_stage=wrap(s.chosen_stage+1,s.stage_count);}}break;}
  case 3:if(s.timer==2)edge_transition(e,0x20);if(s.timer>31&&s.slots[s.chosen_slot]&&s.stage_count){int st=s.available_stages[s.chosen_stage];if(e.start_replay)e.start_replay(e.context,*s.slots[s.chosen_slot],st,s.chosen_slot);}break;
  case 4:if(s.timer>=15){s.previous_selection=s.chosen_stage;if(p&0x10)s.chosen_stage=wrap(s.chosen_stage-1,s.stage_count);if(p&0x20)s.chosen_stage=wrap(s.chosen_stage+1,s.stage_count);if(s.chosen_stage!=s.previous_selection)edge_sound(e,0);if(p&0x1001){s.phase=3;s.timer=0;edge_transition(e,3);}else if(p&0x0a){s.phase=2;s.timer=0;edge_transition(e,2);edge_sound(e,0);}}break;
  case 5:if(s.timer>5){for(auto*&q:s.slots){if(q&&e.release)e.release(e.context,q);q=nullptr;}edge_transition(e,2);}break;
 }
 ++s.timer;return 1;
}

// Semantic reconstruction of retail 0x00433570. The IDA __userpurge body
// confirms ECX carries the title host while the menu state is the sole stack
// argument; the host-only teardown calls are represented by transition edges.
int ReplaySaveName_Update(ReplayNameState&s,std::uint32_t p,const ReplayNameEdges&e){
 static constexpr char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,-!?";
 constexpr int n=int(sizeof(alphabet)-1);
 switch(s.phase){
  case 0:for(int i=0;i<25;++i){if(s.slots[i]&&e.release)e.release(e.context,s.slots[i]);s.slots[i]=e.load?e.load(e.context,numbered(i+1)):nullptr;}s.selection=wrap(s.selection,25);s.name.fill(' ');s.name[8]='\0';s.cursor=0;s.timer=0;s.phase=1;edge_transition(e,1);break;
  case 1:if(s.timer>6){s.phase=2;s.timer=0;}break;
  case 2:s.previous_selection=s.selection;if(p&0x10)s.selection=wrap(s.selection-1,25);if(p&0x20)s.selection=wrap(s.selection+1,25);if(s.selection!=s.previous_selection)edge_sound(e,0);if(p&0x0a){s.phase=4;s.timer=0;edge_transition(e,4);edge_sound(e,0);}else if(p&0x1001){s.slot=s.selection;s.cursor=0;s.name.fill(' ');s.name[8]='\0';s.phase=3;s.timer=0;edge_transition(e,3);edge_sound(e,0);}break;
  case 3:{if(p&0x10)s.selection=wrap(s.selection-13,n+3);if(p&0x20)s.selection=wrap(s.selection+13,n+3);if(p&0x40)s.selection=wrap(s.selection-1,n+3);if(p&0x80)s.selection=wrap(s.selection+1,n+3);if(p&0x1001){if(s.selection<n){if(s.cursor<8)s.name[s.cursor++]=alphabet[s.selection];else s.name[7]=alphabet[s.selection];}else if(s.selection==n){if(s.cursor<8)s.name[s.cursor++]=' ';else s.name[7]=' ';}else if(s.selection==n+1){if(s.cursor>0)s.name[--s.cursor]=' ';else return 1;}else{std::string f=numbered(s.slot+1);bool ok=e.save&&e.save(e.context,f,s.name.data());if(ok){if(s.slots[s.slot]&&e.release)e.release(e.context,s.slots[s.slot]);s.slots[s.slot]=e.load?e.load(e.context,f):nullptr;s.phase=2;s.timer=0;edge_transition(e,2);} }edge_sound(e,0);}if(p&0x0a){if(s.cursor>0)s.name[--s.cursor]=' ';else{s.phase=2;s.timer=0;edge_transition(e,2);}edge_sound(e,0);}break;}
  case 4:if(s.timer>5){for(auto*&q:s.slots){if(q&&e.release)e.release(e.context,q);q=nullptr;}edge_transition(e,2);}break;
 }
 ++s.timer;return 1;
}
} // namespace th10::replay_menu
