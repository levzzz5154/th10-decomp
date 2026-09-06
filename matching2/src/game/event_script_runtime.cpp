#include "th10/game/event_script_runtime.hpp"
#include <algorithm>
#include <utility>
namespace th10::event_script {
// Semantic reconstruction of retail 0x0040BD80 - PARTIAL. The command
// dispatch skeleton, the flags (bits 0/1/2), the color word and the float
// time accumulator are faithful. The ANM/text/global timer subsystems are
// NOT modeled: cases 3/4 are retail text-ring draws (sub_417010,
// sub_449450, sub_447A50, sub_40C4D0 - a 5-slot ANM text ring at a1+64
// with ring position a1+120), cases 5/6 are countdown-timer waits
// (sub_405410, sub_44BF40, sub_43DC90 - they return 0 without advancing
// while the remaining-frame counter a1+48 is not divisible by 6), and
// case 8 is an ANM handle create/release (sub_4492A0, sub_448D00).
// Cases 10 and 13..17 likewise retain only host event edges for their
// sound/effect side effects; those retail globals are not represented here.
// Those cases dispatch to the host edge so a host can reimplement them.
// The pre-loop countdown (sub_405410 on the a1+24 timer) is also elided.
// The wait model below preserves the retail cursor/timer behavior and uses
// confirm as the host's explicit skip input; it cannot reproduce the retail
// global input/debug gates without those globals in the API.
int EndingScript_Update(EndingState&s,const std::vector<EndingCommand>&v,float speed,const EndingEdges&e){
if(s.flags&4)return 0;
const std::vector<EndingCommand>*stream=&v;
if(s.using_loaded_stream)stream=&s.loaded_stream;
while(s.cursor<(int)stream->size()&&(*stream)[s.cursor].time<=s.time){
const auto&c=(*stream)[s.cursor];
switch(c.opcode){
case 0:return -1;
case 3:
// Retail: text draw - sub_417010 resolves the string resource (arg0),
// sub_449450/sub_447A50 attach it to the 5-slot ANM text ring
// (slots at a1+64.., ring position a1+120, color a1+124). Host model:
// no ANM engine; dispatched to the host edge.
if(e.event)e.event(e.context,3,c);
break;
case 4:
// Retail: clear all 5 text-ring slots (sub_40C4D0 x5).
if(e.event)e.event(e.context,4,c);
break;
case 5:
// Retail: countdown-timer wait (sub_405410/sub_44BF40/sub_43DC90);
// returns 0 WITHOUT advancing while the frame counter a1+48 is not
// divisible by 6. The global six-frame gate is outside this API, but the
// timer and explicit host confirmation remain observable here.
if(s.wait_counter<=0){
if(!c.args.empty())s.wait_counter=c.args[0];
}
--s.wait_counter;
if(!c.args.empty()&&c.args[0]<0)s.wait_counter=999;
if(s.wait_counter>0&&!(e.confirm&&e.confirm(e.context)))return 0;
if(e.event)e.event(e.context,5,c);
s.wait_counter=0;
break;
case 6:
// Retail: countdown-timer wait (as case 5), then resets the text-ring
// position (a1+120=0) and dword_4918A4=0.
if(s.wait_counter<=0){
if(!c.args.empty())s.wait_counter=c.args[0];
}
--s.wait_counter;
if(s.wait_counter>0&&!(e.confirm&&e.confirm(e.context)))return 0;
if(e.event)e.event(e.context,6,c);
s.wait_counter=0;
break;
case 7:s.flags|=4u;if(e.event)e.event(e.context,7,c);++s.cursor;return 0;
case 8:
// Retail: ANM release of the slot arg0 handle (sub_4492A0) then create
// (sub_448D00) from the template slot arg1 with type arg2; the new
// handle is stored at a1+4*arg0+144. Host model: no ANM engine;
// dispatched to the host edge.
if(e.event)e.event(e.context,8,c);
break;
case 9:if(!c.args.empty())s.color=(std::uint32_t)c.args[0];break;
case 10:case 13:case 14:case 15:case 16:case 17:if(e.event)e.event(e.context,c.opcode,c);break;
case 11:
// Retail: sub_420C30(3.0) and clears the flag bit (a1+116 &= ~1).
if(e.event)e.event(e.context,11,c);
s.flags&=~1u;
break;
case 12:
// Retail: clears the text ring, loads the next script (sub_40B480),
// memsets the state (0xEC bytes), resets the three timers
// (sub_405410 x3) and starts the new stream with flags=2,
// color=0xFFFFFF. A loader is required to provide the named stream;
// without one, or when it reports failure, preserve the retail -1 result.
if(!e.load)return -1;
{
std::vector<EndingCommand>loaded;
if(!e.load(e.context,c.text,loaded))return -1;
s={};
s.loaded_stream=std::move(loaded);
s.using_loaded_stream=true;
s.flags=2;s.color=0xffffff;
stream=&s.loaded_stream;
}
continue;
default:break;
}
++s.cursor;
}
s.previous_time=s.time;
if(speed>.99f&&speed<1.01f){++s.time;s.fraction+=1.0f;}
else{s.fraction+=speed;s.time=static_cast<int>(s.fraction);}
return 0;}
// Semantic reconstruction of retail 0x00403C80 - PARTIAL. The command
// dispatch and the direct camera/color/global writes are faithful; the
// follow systems are not: the per-frame integration tail (sub_404610 x2
// for the up-follow a1+80 and target-follow a1+156 blocks, sub_4049A0
// for the effect-follow color state a1+232->a1+11080) and the shake
// branch (sub_404ED0) are elided, as are the timer-block initializations
// (previous=-999999, fraction=0, speed=&flt_476F78, flags|=1) that
// several cases perform. Case 0xE's effect-slot spawn/clear (sub_404F30,
// 940-byte stride pool at a1+384) is not modeled. Where the retail arg
// index and the host field disagree, the host mapping is commented.
int StageTimeline_Update(StageState&s,const std::vector<StageCommand>&v,float speed,const StageEdges&e){
while(s.cursor<(int)v.size()&&v[s.cursor].time<=s.time){
const auto&c=v[s.cursor];
auto a=[&](int i){return i<(int)c.args.size()?c.args[i]:0.f;};
switch(c.opcode){
case 0:
// Retail: hard stop - jumps past the time advance (LABEL_37) and runs
// only the matrix-follow tail. Host model: elided tail, so stop
// returns without the time advance.
s.cursor=(int)v.size();
return 0;
case 1:{
// Retail: scene jump. First use sets the init flag (a1+72 bit0) and
// zeroes time/previous/fraction (dead stores - overwritten below),
// then time=arg1, previous=arg1-1, fraction=arg1*1000, and the cursor
// jumps to cmd.arg0 + stream_base(a1+28) WITHOUT the normal stride
// advance. Host model: no stream base, so args[0] is the target
// cursor index.
s.flags|=2u;
s.time=(int)a(1);
s.previous_time=s.time-1;
s.fraction=s.time*1000;
s.cursor=(int)a(0);
continue;
}
case 2:for(int i=0;i<3;++i){float old=s.camera[i];s.camera[i]=a(i);s.camera_delta[i]=s.camera[i]-old;}break;
case 3:
// Retail: target-follow setup - enabled=arg0 (a1+224), mode=arg1
// (a1+228), follow origin=current camera (a1+156), velocity=args[2..4]
// (a1+168..176), timer-block init (a1+204..220).
s.target=s.camera;
for(int i=0;i<3;++i)s.target_delta[i]=a(i+2);
s.mode=(int)a(1);
break;
case 4:for(int i=0;i<3;++i)s.target[i]=a(i);break;
case 5:
// Retail: up-follow setup - enabled=arg0 (a1+148), a1+152=arg1,
// origin=current up (a1+80..88), velocity=args[2..4] (a1+92..100),
// timer-block init (a1+128..144). Host model: no up-velocity or
// follow-enable fields, and the tail integration (sub_404610) is
// elided, so nothing is carried.
break;
case 6:for(int i=0;i<3;++i)s.up[i]=a(i);break;
case 7:
// Retail: shake amplitude = arg0 (a1+10900). Host model: folded into
// the shake scalar.
s.shake=a(0);
break;
case 8:
// Retail: color=arg0 (a1+11104) plus byte channels (a1+11088..11100),
// and args[1..2] to a1+11080/11084 (fade state copied by case 9).
// Host model: color + channels carried; a1+11080/11084 elided.
s.color=(std::uint32_t)a(0);
for(int i=0;i<4;++i)s.color_channels[i]=float((s.color>>(i*8))&255);
break;
case 9:
// Retail: effect-follow setup - enabled=arg0 (a1+364), mode=arg1
// (a1+368), a color quad built from the bytes of arg2 (sub_405040)
// into the follow state (a1+232..288), timer-block init (a1+344..360).
// Host model: dispatched to the host edge; the init flag is folded
// into s.flags bit0.
if(e.event)e.event(e.context,9,c);
s.flags|=1;
break;
case 0xA:
// Retail: target-follow setup (camera-follow variant) - enabled=arg0
// (a1+224), origin=current camera (a1+156), three 3-vectors from
// args[2..10] (a1+168..200), mode=8 (a1+228), timer-block init
// (a1+204..220). Host model: only mode + origin carried; the tail
// integration (sub_404610) is elided.
s.mode=8;
s.target=s.camera;
break;
case 0xB:
// Retail: up-follow setup (as case 5, but does NOT touch the mode) -
// enabled=arg0 (a1+148), a1+152=arg1, origin=current up, velocity=
// args[2..4] (a1+92..100), timer-block init (a1+128..144). Host
// model: not carried (see case 5).
break;
case 0xC:
// Retail: shake-mode byte = arg0 (a1+32) plus a timer-block init
// (a1+36..52, previous=-1). Host model: folds the mode byte into the
// shake scalar; the tail shake branch (sin, sub_404ED0) is elided.
s.shake=a(0);
break;
case 0xD:s.global_value=(int)a(0);break;
case 0xE:
// Retail: effect-slot spawn/clear - 940-byte stride pool at a1+384,
// slot index=arg0; arg1<0 clears the slot's bit0, else sub_404F30
// spawns with the pool base (a1+376 context). Host model: no effect
// pool; not carried.
break;
default:break;
}
++s.cursor;
}
// Partial: the retail tail also runs the follow integrations
// (sub_404610 for the up-follow a1+80 and target-follow a1+156 blocks),
// the effect-follow color copy (sub_4049A0, a1+232 -> a1+11080) and the
// shake branch (sin(a1+44*0.012271847-pi)*-100 -> a1+10888, sub_404ED0,
// wrap at a1+40>=512). Host model: elided.
s.previous_time=s.time;
if(speed>.99f&&speed<1.01f){++s.time;++s.fraction;}
else{s.fraction+=(int)(speed*1000);s.time=s.fraction/1000;}
return 0;}
}
