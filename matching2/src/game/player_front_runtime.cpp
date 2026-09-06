#include "th10/game/player_front_runtime.hpp"
#include <algorithm>
#include <cstdint>

// Retail data slot mirrored by the frame-delta scaling below: 0x004250B0 does
// `fmul flt_476F78` twice at 0x4253F4. Repo-wide convention names this
// DAT_00476f78 (default timer-speed sentinel, 1.0f; defined by
// standalone/host_main.cpp and the test mains, e.g. final_722_recovery_test).
extern float DAT_00476f78;

namespace th10::player_front {

// 0x004250B0 - UpdatePlayer: per-frame player movement (direction decode,
// slow toggle, sprite create/release, frame-delta-scaled position update with
// retail clamps, and the movement trail).
// GROUNDED (retail-exact): the 8-case direction table on dword_474E5C
// (0x10/0x20/0x40/0x80 and the four diagonals; the model previously swapped
// the up-right and down-left values 6/7 -- corrected to retail: 5=up-left,
// 6=down-left, 7=up-right, 8=down-right); speed slots +984/+992 (slow) vs
// +980/+988 (normal) -- the host model takes a single speed per mode and
// uses explicit cardinal/diagonal slots (+980/+984 and +988/+992);
// slow flag = (input>>2)&1 gated by the playable-state check (dword_477704
// && dword_477704[+0x60] && +1164>=4); slow_age (a1+17160) = 0 while slow,
// +1 up to 30 otherwise only when 3*dword_474C68+dword_474C6C==5, and 30
// when the playable gate fails; the x clamp
// [-18400,18400] and y clamp [3200,43200] (retail -18400/18400/3200/43200,
// exact); the frame-delta scaling (a1+1008/+1012 =
// (int)((double)component * flt_476F78), the two sub_463B2C calls; x87
// fild/fmul runs in double precision, mirrored by the double->int cast);
// the float writeback at +960/+964 ((float)int_pos * flt_470B00, i.e.
// 0.01f); the trail shift gated on !slow && moving with trail[0] written
// unconditionally (retail a1+17260/17264, 32 entries of 8 bytes). The host
// exposes sprite positioning through PlayerEdges while retaining the partial
// manager/orbit model.
// RETAIL SLOT-ORDER NOTE (verified this pass, asm 0x4253F4-0x425435): the
// retail body accumulates the LEFT/RIGHT component into a1+976 (the
// [3200,43200]-clamped slot) and the UP/DOWN component into a1+972 (the
// [-18400,18400]-clamped slot); i.e. retail's velocity-to-slot wiring is the
// mirror of the host model's vx->x / vy->y naming. The model keeps the
// previously grounded x/y convention (movement-core brief: do not rewrite)
// and applies the two adds and the clamps in the same relative order; a
// byte-fidelity audit comparing slot arithmetic must swap the two axes.
// PARTIAL MODEL (elided retail steps, not representable in the host API):
// retail creates the player sprite on demand (a1+12956 == 0 ->
// sub_449950 allocate + sub_449870(..., 352) init + handle via sub_4489D0,
// sprite id 9 at [obj+0x20] and flag 0x40000000 at [obj+0x35C]), releases it
// when not slow (sub_4491C0 validity check then sub_449210), runs a
// per-frame sub_4492F0 sprite-position call at (+960+224.0f, +964+16.0f),
// updates the 4 orbit records (a1+13024, stride 152; target offsets and
// slow interpolation gated on slow_age>=30, sub_449350 per record) and
// rotates the trail ring via the head index at a1+13568 (the model's linear
// shift mirrors the head>=4 state; retail collapses the tail entries to the
// head entry when head<4). The slow_age scene gate is represented by the
// explicit slow_age_selection_gate argument; orbit interpolation and manager
// ownership remain outside this host API.
// HOST-SIDE HOOKS: `direction_changed` stands in for the sub_43E710 frame
// flips and fires exactly when retail flips (loc_4252E0): the vertical
// (up/down) component's sign changed -- (new<0 && prev>=0) || (new>0 &&
// prev<=0) || (new==0 && prev!=0) against the stored previous a1+1100; the
// previous sign is read from Player::previous_vy. `sprite_create` fires where
// retail runs sub_449950+sub_449870+
// sub_4489D0 (slow && handle empty); `sprite_release` fires where retail
// runs sub_4491C0+sub_449210 (not slow, handle alive); `enabled` stands in
// for the retail playable-state gate.
// RANDOM EDGE (resolved this pass): retail 0x004250B0 contains NO random
// call -- its calls are sub_449950/sub_449870/sub_4489D0/sub_43E710/
// sub_4491C0/sub_449210/sub_463B2C (x2)/sub_4492F0/sub_449350 (x8) -- so the
// model stays random-free; the PlayerEdges::random member is retained but
// unused.
void UpdatePlayer(Player&p,std::uint32_t in,bool enabled,
                  const PlayerSpeedSlots& speeds,const PlayerEdges&e,
                  bool slow_age_selection_gate){
    const bool left = (in & 0x10) != 0;
    const bool right = (in & 0x20) != 0;
    const bool up = (in & 0x40) != 0;
    const bool down = (in & 0x80) != 0;

    // The opposing horizontal checks are deliberately ordered right before
    // left. Retail checks 0x20 after rejecting diagonals, so 0x30 selects 2.
    p.direction = (left && up) ? 5 : (right && up) ? 7
                 : (left && down) ? 6 : (right && down) ? 8
                 : right ? 2 : left ? 1 : up ? 3 : down ? 4 : 0;
    p.slow=enabled&&bool(in&4); // retail: (dword_474E5C>>2)&1 under the playable gate
    const bool diagonal = p.direction >= 5 && p.direction <= 8;
    const int v = p.slow
        ? (diagonal ? speeds.slow_diagonal : speeds.slow_cardinal)
        : (diagonal ? speeds.normal_diagonal : speeds.normal_cardinal);
    // Components follow the selected direction, rather than independently
    // re-reading the raw bits. This matters for opposing bits: retail's
    // selected direction 2 is a rightward cardinal move even though 0x10 is
    // also present in the input word.
    p.vx = 0;
    p.vy = 0;
    switch(p.direction){
        case 1: p.vx=-v; break;
        case 2: p.vx= v; break;
        case 3: p.vy=-v; break;
        case 4: p.vy= v; break;
        case 5: p.vx=-v; p.vy=-v; break;
        case 6: p.vx=-v; p.vy= v; break;
        case 7: p.vx= v; p.vy=-v; break;
        case 8: p.vx= v; p.vy= v; break;
        default: break;
    }

    // Retail updates this field before the sprite branch. The scene gate is
    // independent of the playable gate: when it is closed the old age is
    // retained, rather than being advanced once per host call.
    if(!enabled){
        p.slow_age=30;
    }else if(slow_age_selection_gate){
        p.slow_age=p.slow?0:std::min(30,p.slow_age+1);
    }
    // Retail sprite create-on-demand (loc_4251DA): slow && a1+12956==0 ->
    // sub_449950 alloc, [obj+0x20]=9 (sprite id), [obj+0x35C]|=0x40000000,
    // sub_449870(anm, obj, 352), sub_4489D0(&handle,...) -> a1+12956=handle.
    if(p.slow&&!p.sprite_handle){
        p.sprite_handle=1; // host stand-in for the sub_4489D0 handle value
        if(e.sprite_create)e.sprite_create(e.context);
    }
    // Retail release path (loc_4252D0, reached when not slow):
    // if(sub_4491C0(...,a1+12956)) sub_449210(...); a1+12956=0.
    // Host-side the handle is "alive" while nonzero, mirroring sub_4491C0's
    // existence test (handle 0 fails it, so no hook when already empty).
    if(!p.slow&&p.sprite_handle){
        p.sprite_handle=0;
        if(e.sprite_release)e.sprite_release(e.context);
    }
    // Retail sub_43E710 flip (loc_4252E0): fires exactly when the vertical
    // component's sign changes, comparing the new iVar7 with the previous
    // a1+1100.  The previous direction encodes that sign.
    const int prev_v=(p.previous_vy<0)?-1:(p.previous_vy>0)?1:0;
    const int new_v=(p.vy<0)?-1:(p.vy>0)?1:0;
    if(prev_v!=new_v&&e.direction_changed)e.direction_changed(e.context);
    p.previous_vx=p.vx;
    p.previous_vy=p.vy;
    // Retail frame-delta scaling (loc_4253F4): a1+1008=(int)((double)vy*flt),
    // a1+1012=(int)((double)vx*flt), then each position slot += its scaled
    // component (truncation toward zero via __ftol2, mirrored here by the
    // double->int cast).
    const int sx=(int)((double)p.vx*DAT_00476f78);
    const int sy=(int)((double)p.vy*DAT_00476f78);
    p.x=std::clamp(p.x+sx,-0x47e0,0x47e0);
    p.y=std::clamp(p.y+sy,0xc80,0xa8c0);
    // Retail float writeback (loc_42549E, every frame after the clamps):
    // a1+960=(float)(a1+972)*flt_470B00 and a1+964=(float)(a1+976)*flt_470B00
    // where flt_470B00 is the 0.01f render scale (repo name DAT_00470b00).
    p.x_f=(float)p.x*0.01f;
    p.y_f=(float)p.y*0.01f;
    if(!p.slow&&(p.vx||p.vy)){for(int i=31;i>0;--i)p.trail[i]=p.trail[i-1];}
    p.trail[0]={p.x,p.y};
    if(p.sprite_handle&&e.sprite_position)
        e.sprite_position(e.context,p.x_f+224.0f,p.y_f+16.0f);
}

void UpdatePlayer(Player&p,std::uint32_t in,bool enabled,int speed,int slow,
                  const PlayerEdges&e){
    // Preserve the old host API while making its limitation explicit: this
    // adapter cannot express separate cardinal and diagonal retail speeds.
    UpdatePlayer(p,in,enabled,
                 PlayerSpeedSlots{speed,slow,speed,slow},e,true);
}

// 0x00413BC0 - InitializeFront: rebuild the front/HUD state (task flags, the
// two front sprites, the 42 ANM slot draws, life icons, power digits, and
// the front animation registrations in retail order).
// GROUNDED: the update/draw task flags (retail: if the task pointer at +8/
// +0xc is nonzero, *(task+4) |= 2); the 42 ANM slot draws behind the
// (a2+876)&1 gate -- retail visit order, all stride 940: iteration k draws
// (a2+16+940k, id 10+k) then (a2+9416+940k, id 20+k) for k=0..9 (the first
// two banks are INTERLEAVED, verified from the retail body), then ids 30..38
// at +18816, 47..50 at +27276, 80..81 at +31036, 51..57 at +32916; the 9
// lives slots (stride 235 dwords at +19676, bit 1 set on the first
// dword_474C70 slots, cleared on the rest); the three power digits at base
// +8 -- word_474C48/20+8, (100*(word_474C48%20)/20)/10+8 and %10+8 (the +8
// base, the digit formula and the preload offsets +27276/+29156/+30096 are
// retail-exact; retail sources the word_474C48 power gauge, which the host
// model routes through `counter`); the sprite registrations in retail order
// -- 0 and 1 (the pair, when dword_474CA0&0x20 is clear and dword_491FB8!=8)
// or sprite 113 (0x71) when the flag is set, EITHER branch mutually
// exclusive, and 113 is created for dword_491FB8==8 as well (loc_413F87 ->
// loc_413F94); sprite 79 (0x4f) when dword_474C7C==1 && !dword_477810[23]
// && !dword_474C90; sprite difficulty+102 (0x66) when dword_491FC4; sprite
// difficulty+107 (0x6b) unconditionally.
// PARTIAL MODEL (elided retail steps, not representable in the host API):
// the create-on-demand sprite handles at +40536/+40540 (retail: when the
// slot is 0, sub_449950 allocate, [obj+0x20]=0xf, [obj+0x35C]|=
// 0x40000000, sub_449870(bank,obj,0/1), sub_4489D0 register -> handle), the
// single sub_43E710(a2+39496, g_pGameThread_anm, 0) draw after the pair/113
// registration, the per-registration task ids and the depth-3 task reorder
// (retail stores the 102+difficulty id at a2+40528 and the 107+difficulty id
// at a2+40532, walks the game-state-manager task lists, sets
// (ushort)[task+0x304]=3 and recurses into the child list at +0x14) and the
// a2+40592=0 tail; `linked_a`/`linked_b` mirror the last two registered
// sprites (a2+40528/a2+40532).
// HOST-SIDE GATES: the input fields special/mode/stage_one_clear/
// extra_overlay stand in for the retail globals listed above and are
// unverified stand-ins; retail clamps the lives count to 9 via the
// (9 - count) clear loop.
void InitializeFront(Front&f,const FrontInput&i,const FrontDrawEnv&env){
    f.update_task=f.draw_task=true;
    // Retail 0x00413BC0 slot draws (the (a2+876)&1 gate; retail visit
    // order, all stride 940).  The host mirrors them via the env hooks;
    // null hooks = not wired.
    if((env.flags&1)==0&&env.tick_slot){
        // Retail interleaves the first two banks: iteration k draws
        // (slot index k, id 10+k) then (slot index 10+k, id 20+k) for
        // k=0..9 (slot k = a2+16+940k, slot 10+k = a2+9416+940k).
        for(int k=0;k<10;++k){
            env.tick_slot(k,10+k);       // +16 bank
            env.tick_slot(10+k,20+k);    // +9416 bank
        }
        int slot=20;
        for(int n=30;n<39;++n)env.tick_slot(slot++,n);   // +18816
        for(int n=47;n<51;++n)env.tick_slot(slot++,n);   // +27276
        for(int n=80;n<82;++n)env.tick_slot(slot++,n);   // +31036
        for(int n=51;n<58;++n)env.tick_slot(slot++,n);   // +32916
    }
    for(int n=0;n<9;++n)f.lives[n]=n<i.lives; // retail: bit 1 on first dword_474C70 slots
    // Retail: the three sub_43E5A0 power-digit preloads at
    // +27276/+29156/+30096 (word_474C48 digits, base +8 - the model's
    // `digits` mirror below).
    if(env.preload){
        int q=((i.counter%20)*100)/20;
        env.preload(27276,i.counter/20+8,env.bank);
        env.preload(29156,q/10+8,env.bank);
        env.preload(30096,q%10+8,env.bank);
    }
    int q=((i.counter%20)*100)/20;
    f.digits={i.counter/20+8,q/10+8,q%10+8};  // retail: word_474C48 digits, base +8 exact
    f.animations.clear();
    if(i.special){ // retail: dword_474CA0&0x20 set -> sprite 113, also when dword_491FB8==8
        f.animations.push_back(0x71);
    }else if(i.mode!=8){ // retail: dword_491FB8==8 skips the 0/1 pair
        f.animations.push_back(0);f.animations.push_back(1);
    }
    if(i.stage_one_clear)f.animations.push_back(0x4f); // retail: sprite 79 (474C7C==1 && !477810[23] && !474C90)
    if(i.extra_overlay)f.animations.push_back(i.difficulty+0x66); // retail: sprite 102+difficulty (dword_491FC4)
    f.animations.push_back(i.difficulty+0x6b); // retail: sprite 107+difficulty, unconditional
    f.linked_a=f.animations.size()>1?f.animations[f.animations.size()-2]:0;
    f.linked_b=f.animations.back();
}
}
