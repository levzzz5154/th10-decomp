// Baseline observation probe for commit 895c420. Success means the documented
// baseline behavior was reproduced, INCLUDING defects; this is not a correctness
// regression test. References are static assembly-derived models, never retail
// execution. See docs/audit/calibration_codex.md for limits and build command.
#include "th10/math/easing.hpp"
#include "th10/game/trajectory_evaluate.hpp"
#include "th10/game/score_popup.hpp"
#include "th10/app/version_marker.hpp"
#include "th10/app/fps_counter.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>

static void check(bool value, const char* label) {
    if (!value) { std::fprintf(stderr, "observation changed: %s\n", label); std::exit(1); }
}
static float reference_ease(int mode, float elapsed, float duration) {
    // Mathematical transcription of 0044C350, used only at exact dyadic inputs.
    long double t = (long double)elapsed / duration;
    if (mode >= 1 && mode <= 3) return (float)std::pow(t, mode + 1);
    if (mode >= 4 && mode <= 6) return (float)(1 - std::pow(1-t, mode-2));
    if (mode >= 9 && mode <= 11) {
        t *= 2;
        return (float)(t < 1 ? std::pow(t,mode-7)/2 : 1-std::pow(2-t,mode-7)/2);
    }
    if (mode >= 12 && mode <= 14) {
        t *= 2;
        return (float)(t < 1 ? (1-std::pow(1-t,mode-10))/2 : (1+std::pow(t-1,mode-10))/2);
    }
    return mode == 15 ? 0 : mode == 16 ? 1 : (float)t;
}
static unsigned char marker[3] = {1,2,3};
static char probe_name[128], load_name[128];
static bool probe_result = false, load_result = true;
static int loads = 0, logs = 0;
static bool probe(const char* name) { std::snprintf(probe_name,sizeof(probe_name),"%s",name); return probe_result; }
static unsigned char* load(const char* name, std::size_t* size) {
    ++loads; std::snprintf(load_name,sizeof(load_name),"%s",name);
    *size = load_result ? sizeof(marker) : 0;
    return load_result ? marker : nullptr;
}
static void log(const char*) { ++logs; }
static float live_fps = 20;
static Word color, seen_color;
static int updates = 0, prints = 0;
static void update() { ++updates; live_fps = 60; }
static void print(const char* format) { ++prints; seen_color=color; check(std::strcmp(format,"%2.1ffps")==0,"FPS format"); }

int main() {
    int controls = 0;
    for (int mode = -1; mode <= 18; ++mode) for (int quarter=0; quarter<=4; ++quarter) {
        const float t = quarter * .25f, expected = reference_ease(mode,t,1);
        check(Easing_Evaluate(mode,t,1)==expected,"math easing dyadic control"); ++controls;
        if (mode != 11 && mode != 12) {
            check(Trajectory_EaseFraction(t,1,mode)==expected,"trajectory easing unaffected mode"); ++controls;
        }
    }
    check(Trajectory_EaseFraction(2.5f,10,11)==.9375f && reference_ease(11,2.5f,10)==.03125f,"mode 11 lower mismatch");
    check(Trajectory_EaseFraction(7.5f,10,11)==.9375f && reference_ease(11,7.5f,10)==.96875f,"mode 11 upper mismatch");
    check(Trajectory_EaseFraction(2.5f,10,12)==.4375f && reference_ease(12,2.5f,10)==.375f,"mode 12 lower mismatch");
    check(Trajectory_EaseFraction(7.5f,10,12)==.5625f && reference_ease(12,7.5f,10)==.625f,"mode 12 upper mismatch");
    std::printf("easing: %d dyadic positive controls; four formula counterexamples reproduced\n",controls);

    const float one = 1, tiny_speed=std::ldexp(1.0f,-25);
    TrajectoryEnv env = {&one,Trajectory_EaseFraction};
    Trajectory2D state = {};
    state.speed=&tiny_speed; state.duration=10; state.mode=7;
    state.elapsed=std::nextafter(1.0f,0.0f);
    const long double extended_sum=(long double)state.elapsed + tiny_speed;
    float output[2];
    Trajectory_Evaluate2D(&state,output,&env);
    check(state.elapsed==1 && state.current==1 && (int)extended_sum==0,"2D preconversion rounding mismatch");
    state={}; state.speed=&one; state.duration=2; state.mode=7;
    state.p0[0]=3; state.velocity[0]=2;
    Trajectory_Evaluate2D(&state,output,&env);
    check(state.current==1 && state.previous==0 && output[0]==5,"2D integrate control");
    Trajectory_Evaluate2D(&state,output,&env);
    check(state.duration==0 && state.current==2 && state.previous==1 && output[0]==5 && (state.timer_flags&1),"2D completion control");
    state={}; state.speed=&one; state.duration=4; state.mode=8;
    state.velocity[0]=16;
    Trajectory_Evaluate2D(&state,output,&env);
    check(output[0]==2.5f,"2D Hermite control");
    state={}; state.speed=&one; state.mode=17; state.p0[0]=2; state.acceleration[0]=3; state.velocity[0]=4;
    Trajectory_Evaluate2D(&state,output,&env);
    check(output[0]==5 && state.acceleration[0]==7,"2D acceleration ordering control");
    state={}; state.speed=&one; state.duration=10; state.mode=12;
    state.elapsed=1.5f; state.current=1; state.velocity[0]=16;
    Trajectory_Evaluate2D(&state,output,&env);
    check(output[0]==7 && 16*reference_ease(12,2.5f,10)==6,"2D wrong easing binding propagation");
    std::puts("2D: rounding boundary reproduced against extended-sum model; four state controls passed");

    ScorePopupQueue queue = {};
    const float position[3]={1,2,3};
    auto* record=ScorePopup_Enqueue(&queue,12034,0xff123456,position,&one);
    const unsigned char digits[5]={4,3,0,2,1};
    check(record==&queue.records[0] && record->active==1 && record->digit_count==5 && std::memcmp(record->digits,digits,5)==0,"score positive digits");
    check(record->color==0xff123456 && record->position[1]==2 && record->timer.target==-1 && record->timer.current==0 && record->timer.previous==0 && record->timer.speed==&one && (record->timer.flags&1),"score publication and timer");
    check(ScorePopup_Enqueue(&queue,-987,0,position,&one)->digits[0]==10,"score negative glyph");
    check(ScorePopup_Enqueue(&queue,0,0,position,&one)->digits[0]==0,"score zero glyph");
    queue.next_index=720; record=ScorePopup_Enqueue(&queue,7,0,position,&tiny_speed);
    check(record==&queue.records[0] && queue.next_index==1 && record->timer.speed==&one,"score wrap and initialized speed");
    std::puts("score: positive/zero/negative digits, publication, wrap, and timer controls passed");

    unsigned char* data=marker; std::size_t size=99;
    VersionMarkerEnv version={0x100,'a',"missing","load failed",probe,load,log,&data,&size};
    check(VersionMarker_Load(&version)==-1 && loads==0 && logs==1 && data==marker && size==99,"version failed probe control");
    check(std::strcmp(probe_name,"th10.ver")==0,"version wrong literal baseline");
    probe_result=true;
    check(VersionMarker_Load(&version)==0 && data==marker && size==3 && std::strcmp(load_name,"th10_0100a.ver")==0,"version successful load control");
    load_result=false;
    check(VersionMarker_Load(&version)==-1 && data==nullptr && size==0 && logs==2,"version failed load control");
    std::puts("version: th10.ver probe (assembly: th10.dat); three result/publication controls passed");

    int accumulator=10, thread=0;
    check(FpsCounter_Render(update,1,&thread,live_fps,30,40,&color,print,&accumulator,2)==1,"FPS return");
    check(live_fps==60 && seen_color==0xff5050ff && color==0xffffffff && accumulator==13 && updates==1 && prints==1,"FPS stale snapshot mismatch and bookkeeping");
    FpsCounter_Render(update,14,&thread,60,30,40,&color,print,&accumulator,0);
    FpsCounter_Render(update,1,nullptr,60,30,40,&color,print,&accumulator,0);
    check(prints==1 && updates==3 && accumulator==15,"FPS suppressed draw controls");
    for (float fps : {30.0f,40.0f}) {
        FpsCounter_Render(update,1,&thread,fps,30,40,&color,print,&accumulator,0);
        check(seen_color==(fps==30 ? 0xffa0a0ffu : 0xffffffffu),"FPS threshold controls");
    }
    std::puts("FPS: stale 20fps/red after update to 60fps; suppression and threshold controls passed");
    std::puts("BASELINE OBSERVATIONS REPRODUCED (not retail equivalence)");
}
