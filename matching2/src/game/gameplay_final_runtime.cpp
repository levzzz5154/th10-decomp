#include "th10/game/gameplay_final_runtime.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
namespace th10::gameplay_final {

namespace {

float NormalizeIndicatorAngle(float angle) {
    while (angle > 3.14159265358979323846f)
        angle -= 6.28318530717958647692f;
    while (angle < -3.14159265358979323846f)
        angle += 6.28318530717958647692f;
    return angle;
}

int FloatBits(float value) {
    int bits=0;
    std::memcpy(&bits,&value,sizeof(bits));
    return bits;
}

float BitsFloat(int bits) {
    float value=0.0f;
    std::memcpy(&value,&bits,sizeof(value));
    return value;
}

void MirrorEmbeddedTimers(PlayerRuntime& state) {
    state.state_timer.target=state.timer_prev;
    state.state_timer.current=state.timer;
    state.state_timer.previous=FloatBits(state.timer_frac);
    state.state_timer.speed=&state.state_timer_speed;
    state.state_timer.flags=static_cast<unsigned int>(state.timer_flags);
    // +0x430C is copied before the countdown decrement and is retained as
    // the timer mirror; the tail has already populated `target` when active.
    state.invulnerability_timer.current=state.invulnerable;
    state.invulnerability_timer.previous=FloatBits(state.invuln_frac);
    state.invulnerability_timer.speed=&state.invulnerability_timer_speed;
    // Retail leaves the initialized bit armed after the countdown reaches
    // zero; later FUN_00405410 calls reuse the same timer without reseeding
    // the sentinel.
    state.hold_timer_state.target=state.hold_timer_prev;
    state.hold_timer_state.current=state.hold_timer;
    state.hold_timer_state.previous=FloatBits(state.hold_timer_frac);
    state.hold_timer_state.speed=&state.hold_timer_speed;
    state.hold_timer_state.flags=static_cast<unsigned int>(state.hold_flags);
}

void ImportEmbeddedTimerAliases(PlayerRuntime& state) {
    // Existing callers use the compact scalar fields. A typed caller may seed
    // one of the mirrors directly; import it only when the legacy flags still
    // show first use, preserving both APIs without inventing a second clock.
    if (state.timer_flags==0 && (state.state_timer.flags&1u)!=0) {
        state.timer_flags=static_cast<int>(state.state_timer.flags);
        state.timer_prev=state.state_timer.target;
        state.timer=state.state_timer.current;
        state.timer_frac=BitsFloat(state.state_timer.previous);
    }
    if (state.invulnerable==0 && (state.invulnerability_timer.flags&1u)!=0 &&
        state.invulnerability_timer.current!=0) {
        state.invulnerable=state.invulnerability_timer.current;
        state.invuln_frac=BitsFloat(state.invulnerability_timer.previous);
    }
    if (state.hold_flags==0 && (state.hold_timer_state.flags&1u)!=0) {
        state.hold_flags=static_cast<int>(state.hold_timer_state.flags);
        state.hold_timer_prev=state.hold_timer_state.target;
        state.hold_timer=state.hold_timer_state.current;
        state.hold_timer_frac=BitsFloat(state.hold_timer_state.previous);
    }
}

// The retail tail uses the same five-word timer shape as the other embedded
// timers, but its first word is previous/current bookkeeping rather than a
// stop target. Keep the sentinel and initialized-bit transition observable.
void AdvanceAuxiliaryTimer(PlayerRuntime& state, float speed) {
    state.auxiliary_frame_delta=speed;
    state.auxiliary_timer.speed=&state.auxiliary_frame_delta;
    if ((state.auxiliary_timer.flags & 1u) == 0) {
        state.auxiliary_timer.current = 0;
        state.auxiliary_timer.target = (int)0xFFF0BDC1;
        state.auxiliary_timer.previous = 0;
        state.auxiliary_timer.flags |= 1u;
        state.auxiliary_timer_fraction = 0.0f;
    }
    state.auxiliary_timer.target = state.auxiliary_timer.current;
    if (0.99f < speed && speed < 1.01f) {
        ++state.auxiliary_timer.current;
        state.auxiliary_timer_fraction += 1.0f;
    } else {
        state.auxiliary_timer_fraction += speed;
        state.auxiliary_timer.current =
            static_cast<int>(state.auxiliary_timer_fraction);
    }
    state.auxiliary_timer.previous=FloatBits(state.auxiliary_timer_fraction);
}

float QuantizeIndicatorCoordinate(float value) {
    // 0x44C2A0 multiplies by flt_470B44 (100), floors, then multiplies by
    // flt_470B00 (0.01f). These constants are the retail fixed-point snap.
    return std::floor(value * 100.0f) * 0.01f;
}

void UpdateIndicatorPool(PlayerRuntime& state, float speed) {
    state.indicator_frame_delta=speed;
    for (PlayerIndicatorSlot& slot : state.indicators.slots) {
        if ((slot.flags & 1u) == 0)
            continue;
        slot.timer_speed=&state.indicator_frame_delta;

        // Raw 0x425D83-0x425E2B: 0x44C5D0 builds the motion vector in
        // linear mode; polar mode advances radius/angle before 0x44C2A0.
        if ((slot.motion_flags & 1u) == 0) {
            // 0x44C5D0 writes the generated vector into +0x24/+0x28 before
            // 0x44C2A0 adds those words to the persistent +0x18/+0x1c
            // motion. +0x2c is not overwritten by 0x44C5D0.
            slot.velocity_x=std::cos(slot.angle)*slot.angle_step;
            slot.velocity_y=std::sin(slot.angle)*slot.angle_step;
        } else {
            slot.radius += slot.radius_step;
            slot.angle=NormalizeIndicatorAngle(slot.angle + slot.angle_step);
        }

        // 0x44C2A0: linear records add the generated vector; polar records
        // rebuild from angle/radius and add the persistent offset vector, then
        // floor only horizontal values.
        if ((slot.motion_flags & 1u) == 0) {
            slot.motion_x += slot.velocity_x;
            slot.motion_y += slot.velocity_y;
            slot.motion_z += slot.velocity_z;
        } else {
            slot.motion_x=std::cos(slot.angle)*slot.radius + slot.velocity_x;
            slot.motion_y=std::sin(slot.angle)*slot.radius + slot.velocity_y;
            slot.motion_z=slot.velocity_z;
        }
        slot.motion_x=QuantizeIndicatorCoordinate(slot.motion_x);
        slot.motion_y=QuantizeIndicatorCoordinate(slot.motion_y);

        // The pool's position pair is separate from the 0x44C2A0 motion
        // record: raw lines 267-269 add +0x04/+0x0C to +0x00/+0x08.
        slot.position_x += slot.position_delta_x;
        slot.position_y += slot.position_delta_y;

        // Raw lines 270-283 are the embedded countdown timer at +0x44.
        slot.timer_previous=slot.timer_current;
        const float timer_speed=*slot.timer_speed;
        if (0.99f < timer_speed && timer_speed < 1.01f)
            slot.timer_fraction -= 1.0f;
        else
            slot.timer_fraction -= timer_speed;
        slot.timer_current=static_cast<int>(slot.timer_fraction);
        if (slot.timer_current < 1)
            slot.flags &= ~1u;
    }
}

} // namespace

// Partial host-side model of retail 0x0041AFD0 (sub_41AFD0, item sweep).
// PARTIAL MODEL: retail sweeps 2198 item records (stride 1008) with states
// 0-5/7/8/0xA/0xB and per-type collection effects (score/power/text via
// sub_42B9C0/sub_4054B0/sub_43DD10), ANM updates (sub_43EE30) and a case-5
// countdown spawn (sub_404F30) that this host model cannot express.
// GROUNDED: per-item state machine; gravity vy += 0.03*frame capped at 2.0
// with vx cleared once vy>=0 (retail case 1/2); despawn at x > 472.0
// (retail checks x, not y); atan2 magnet steering (retail sub_426660 +
// sub_41BEB0) with collection on player contact; active count = uncollected
// items (retail increments at LABEL_83).
// HOST-SIDE CONVENTIONS: `active` stands in for retail state 0; `speed`
// stands in for the frame delta flt_476F78; the magnet magnitude is fixed
// (retail keeps it in record slot +56, ramping +0.2/frame up to 12.0 from
// the player's magnet speed); the collect rect is a fixed 8-unit box (retail
// reads the player's magnet rect from record slots 4297-4314).
// REMOVED (fabricated): the 0.1f linear magnet, the 0.95f velocity damping,
// the z-ramp (retail has no such sub-state), the y>480 despawn, and the
// difficulty/type-5 gravity tweak all had no retail counterpart.
// The env carries the player position (dword_477834 +960/+964), the frame
// delta (flt_476F78) and the collect/magnet rects (retail slots 4297-4314).
int UpdateItems(ItemPool&p,ItemEnv&env){
    const float px=env.player_x,py=env.player_y,speed=env.frame_delta;
    p.active=0;
    for(auto&i:p.items){
        if(i.state==0)continue;  // retail: state 0 = inactive
        ++i.timer;
        switch(i.state){
        case 1: // falling (retail case 1); magnet once conditions are met
            i.vy=std::min(2.0f,i.vy+.03f*speed);   // retail: vy += 0.03*dt, cap 2.0
            if(i.vy>=0.0f)i.vx=0.0f;               // retail: vx cleared when vy>=0
            i.x+=i.vx*speed;i.y+=i.vy*speed;
            if(i.x>472.0f){i.state=0;break;}  // retail: x>472 -> state 0  // retail: x>472 -> state 0
            // retail gates the magnet on the player's state (2/4 or y>=128);
            // the host model has no player-state channel, so it steers directly.
            i.state=3;
            break;
        case 2: // rising (retail case 2), flips to magnet when vy>=0
            i.vy=std::min(2.0f,i.vy+.03f*speed);
            i.x+=i.vx*speed;i.y+=i.vy*speed;
            if(i.x>472.0f){i.state=0;break;}  // retail: x>472 -> state 0
            if(i.vy>=0.0f)i.state=3;
            break;
        case 3: // magnet (retail LABEL_25/36 and case 4)
        case 4:
        {
            float dx=px-i.x,dy=py-i.y;
            if(dx==0.0f&&dy==0.0f)break;
            float a=std::atan2(dy,dx);
            // retail: sub_41BEB0(vel, a, slot+56); slot+56 ramps +0.2 per
            // frame up to 12.0, seeded from the player's magnet speed
            // (dword_477834 + 1124) when the magnet starts.  The host Item
            // carries the slot (magnet_speed, +56); the seed comes from the
            // env when the slot is still zero.
            if(i.magnet_speed==0.0f&&env.magnet_speed>0.0f)
                i.magnet_speed=env.magnet_speed;
            if(i.magnet_speed<12.0f)i.magnet_speed+=0.2f; // retail: +0.2 cap 12.0
            i.vx=std::cos(a)*i.magnet_speed;
            i.vy=std::sin(a)*i.magnet_speed;
            i.x+=i.vx*speed;i.y+=i.vy*speed;
            break;
        }
        default:
            // retail also has state 5 (countdown -> spawn sub_404F30) and
            // collection types 7/8/9/0xA/0xB with score/power effects;
            // unmodeled.
            break;
        }
        // collection on player contact (retail: item inside the player's
        // magnet rect -> per-type collect switch -> state 0)
        if(i.state!=0&&std::fabs(px-i.x)<8.0f&&std::fabs(py-i.y)<8.0f){
            i.state=0;++p.collected; // retail: contact collect -> state 0
        }
        // retail LABEL_83: the active count covers the items still active
        // after the state update (despawned/collected items do not count)
        if(i.state!=0)++p.active;
    }
    return p.active; // retail returns 1; host returns the active count
}

// Partial host-side model of retail 0x00425730 (sub_425730, player update).
// STATUS: PARTIAL. The case state machine and all record-local side effects
// below are ordered from the full listing; external manager operations remain
// explicit hooks and are not claimed as semantic C++.
// RETAIL-ORDERED (asm-verified this pass against the full 0x00425730
// listing): the case state machine (0..4) and every representable side
// effect in retail order:
//   case 0: entry motion y = 48000 - timer*8000/60 (signed /60 via the
//     0x88888889 magic) with py = y * flt_470B00 (0.01f); the entry-trail
//     history ring (33 pairs at +0x436C, ring slot = 8*spawn_count pairs:
//     copy the ring pair into pairs 32..8*count+1, shift pairs 8*count..1
//     by one, then history[0] = (fx, y)); t<30 entry effects (radius =
//     t*flt_470D44(17.066667f)+flt_470BC8(64.0f) -> sub_408100(radius,0,1),
//     sub_408100(radius*flt_470D40(0.25f),0,0), sub_41C800) and the t>=30
//     2000-enemy sweep (sub_408030; state!=0/3 && +4==0) + node-list walk
//     (vtbl+0x14(0), node[3]!=1); state-1 transition at t>=60 with the
//     timer-struct reset (a3[285]=-999999 then -1, a3[286]=0, a3[287]=0,
//     a3[288]=&flt_476F78, a3[289]|=1) and fallthrough into the case-1
//     body.
//   case 1: shot-drain branch (player record alive && game state type 0 &&
//     power/20 != 0 && dword_474E5C&2): invuln timer = 0x10E (270),
//     sub_405860, word_474C48 -= 20, sub_426F70, power HUD
//     (sub_4054B0(level, level, frac)), bonus timer sub_412E70(&DAT_00474C40,
//     3000); then the t<30 sweep + list walk; then sub_4250B0 movement.
//   case 2 / case 4 (shared path, retail LABEL_46): t==3 -> power -= 64
//     (clamp 0), power HUD, fan angle sub_426610 (atan2(-224.0f, -px) from
//     the (0, py-224, 0) probe), 7x sub_41BB00 (type 4 on i=1/3/5 else 1,
//     angle = i*flt_470D3C(0.11219974f) + fan - flt_470D38(0.39269909f),
//     color 0xFFFFFF, speed 3.0), sub_426F70; t>=30 -> DAT_00474C70 < 0 ?
//     sub_40AC90(4) (Block+0x10==1) or sub_4231D0 : respawn (state 0,
//     DAT_00476F78 = 1.0f, sub_427B50(px, 32.0f, 16.0f, 30, 150), prev-pos
//     snap, fx=0, y=48000, px=0, py=480.0f, invuln timer 0x118 (280), timer
//     reset 0).
//   case 3: t==15 (retail also tests t!=4, dead code kept for shape) ->
//     sweep (no +4 gate in retail) + sub_41C850.
//   case 4: t>=8 -> sub_4269D0 then the shared path; t<8 -> revive drain
//     (game state type 0 && power/20 != 0 && dword_474E5C&2): timer = 0x3C
//     (60), invuln = 200, sub_405860, power -= 20, sub_426F70, power HUD,
//     state = 1.
//   tail (all cases): blink (a3[220] bit15 + flash a3[197]=0xFF0000FF when
//     invulnerable >= 1 and timer != timer_prev && timer%3 == 0), the
//     sub_43EE30 ANM tick, the four rect sets (a3[257..262] = pos +/- size_a,
//     a3[4297..4302] = pos +/- size_b*flt_470B0C(0.5f), a3[4303..4308] =
//     pos +/- size_c, a3[4309..4314] = pos +/- size_b), the scale-pointer
//     timer advance (prev = current; speed inside (flt_470B68(0.99f),
//     flt_470B64(1.01f)) ? current++, frac += flt_470AFC(1.0f) : frac +=
//     speed, current = __ftol2(frac) via sub_463B2C), the frame counter
//     (DAT_00474C98 += 1 every 60 ticks while hold enabled, clamp
//     [-1024,1024]), hold routing (player present && hold enabled ->
//     sub_4281D0 and LABEL_115 is skipped; otherwise the hold-timer hard
//     reset: a3[280..284] = -2/-1/-1.0f + a3[3393] = 0 + byte_13576 = 0),
//     and the sub_428280 tail call; returns 1.
// HOST CONVENTIONS (pinned by tests/final_722_recovery_test.cpp): the state
// timer and invulnerability advances run in the retail tail, after switch
// callbacks observe pre-advance values; a newly-written invulnerability is
// decremented by that same tail. `power` stands in
// for the signed-16-bit word_474C48 gauge; `input` is routed only where
// retail reads dword_474E5C; the a3[288]/a3[293] speed pointers map to
// env.frame_delta; the invuln timer's +0x430C mirror, +0x4318 speed pointer
// and +0x431C flags have no host fields.
// The player record now carries the 32 indicator slots, the four familiar
// level words, and the third embedded timer. The ANM manager work reached
// through those records remains callback-owned.
int UpdatePlayerState(PlayerRuntime&s,std::uint32_t input,PlayerStateEnv* env){
    ImportEmbeddedTimerAliases(s);
    PlayerStateEnv e = env ? *env : PlayerStateEnv{};
    // Retail leaves the state timer and invulnerability untouched while the
    // switch and its callbacks run. Both advances happen in the tail below.
    // Respawn writes the global frame delta to 1.0 before this tail, so this
    // remains mutable rather than caching the pre-switch value.
    float spd = e.frame_delta;

    // Retail FUN_00405410 on the a3[285..289] timer struct (a1+0x474):
    // first-use sentinel init, then current = value, previous = value - 1,
    // frac = (float)value.  `small_invuln` is the host face of the a3[285]
    // dword's float alias per the hpp contract (60 on drain, 0 on respawn).
    auto set_timer = [&](int value) {
        if ((s.timer_flags & 1) == 0) {
            s.timer = 0;
            s.timer_prev = -999999;   // 0xFFF0BDC1 first-use sentinel
            s.timer_frac = 0.0f;
            s.timer_flags |= 1;       // a3[288] speed pointer -> env.frame_delta
        }
        s.timer = value;
        s.timer_prev = value - 1;
        s.timer_frac = (float)value;
        s.small_invuln = value;
    };
    // Retail FUN_00405410 on the invuln struct (a1+0x430C): current
    // (a3[4292]) = value, frac (a3[4293]) = (float)value; the +0x430C
    // mirror (= value-1), +0x4318 speed pointer and +0x431C flags have no
    // host fields.
    auto set_invuln = [&](int value) {
        if ((s.invulnerability_timer.flags & 1u) == 0) {
            s.invulnerability_timer.target=-999999;
            s.invulnerability_timer.current=0;
            s.invuln_frac=0.0f;
            s.invulnerability_timer.flags|=1u;
        }
        s.invulnerable=value;
        s.invulnerability_timer.target=value-1;
        s.invulnerability_timer.current=value;
        s.invuln_frac=(float)value;
    };
    // Retail case 1 body; also reached by the case-0 transition fallthrough.
    auto play = [&]() {
        // Shot-drain branch (retail 0x425964), power > 0 + shot key:
        if (e.player_present && e.focus_object && s.power / 20 != 0 && (input & 2)) {
            set_invuln(270);                       // FUN_00405410(0x10E)
            if (e.focus_drain) e.focus_drain();    // sub_405860 (InitializePlayer)
            s.power -= 20;                         // word_474C48 -= 0x14
            if (e.attached_effects) e.attached_effects(s);   // sub_426F70
            if (e.power_hud) e.power_hud(s.power / 20, (s.power % 20) * 100 / 20);  // sub_4054B0
            if (e.bonus_timer) e.bonus_timer(3000);          // sub_412E70(&DAT_00474C40, 3000)
        }
        if (s.timer < 30) {                        // retail: t < 0x1E
            if (e.sweep_enemy) e.sweep_enemy(0, 0);   // sub_408030 x2000 (state!=0/3, +4==0)
            if (e.clear_bullets) e.clear_bullets(0);  // list walk, vtbl+0x14(0), node[3]!=1
        }
        if (e.move) e.move(s, input);              // sub_4250B0 (movement)
    };
    // Retail shared case 2/4 path (switchD_0042574a_caseD_2 / LABEL_46).
    auto death = [&]() {
        if (s.timer == 3) {
            s.power = std::max(0, s.power - 64);   // word_474C48 -= 0x40, clamp 0
            if (e.power_hud) e.power_hud(s.power / 20, (s.power % 20) * 100 / 20);
            // fan base angle: sub_426610 on (0, py-224, 0) -> atan2(-224, -px)
            const float fan_point[3] = {0.0f, s.py - 224.0f, 0.0f};
            const float fa = e.fan_angle_ex ? e.fan_angle_ex(fan_point, s) :
                             (e.fan_angle ? e.fan_angle(s) :
                              std::atan2(-224.0f, -s.px));
            const float fan_position[3] = {s.px, s.py, s.pz};
            for (int i = 0; i < 7; ++i) {
                const int type = (i == 1 || i == 3 || i == 5) ? 4 : 1;
                const float angle = (float)i * 0.11219974f + fa - 0.39269909f;
                if (e.death_fan_ex)
                    e.death_fan_ex(fan_position, type, 0x00FFFFFFu, angle, 3.0f);
                else if (e.death_fan)
                    e.death_fan(type, angle);   // sub_41BB00(px, type, 0xFFFFFF, angle, 3.0)
            }
            if (e.attached_effects) e.attached_effects(s);   // sub_426F70
        }
        if (s.timer >= 30) {                       // retail: 0x1D < t
            if (!e.can_respawn) {                  // DAT_00474C70 < 0
                if (e.game_over_flag == 1) {
                    if (e.game_over_ex) e.game_over_ex(4);
                    else if (e.game_over) e.game_over();
                }  // sub_40AC90(4)
                else { if (e.stage_start) e.stage_start(); }                    // sub_4231D0
            } else {
                s.state = 0;
                spd = 1.0f;                         // retail: DAT_00476F78 = 1.0f
                e.frame_delta = spd;
                if (env) env->frame_delta = spd;
                const float respawn_position[3] = {s.px, s.py, s.pz};
                if (e.respawn_effect_ex)
                    e.respawn_effect_ex(respawn_position, 32.0f, 16.0f, 30, 150);
                else if (e.respawn_effect)
                    e.respawn_effect(s);             // sub_427B50(px, 32.0f, 16.0f, 30, 150)
                s.px_prev = s.px;                  // retail: +0x440..8 = +0x3C0..8
                s.py_prev = s.py;
                s.pz_prev = s.pz;
                s.fx = 0;                          // +0x3CC
                s.y = 48000;                       // +0x3D0
                s.px = 0.0f;                       // +0x3C0
                s.py = 480.0f;                     // +0x3C4 (0x43F00000)
                set_invuln(280);                   // FUN_00405410(0x118)
                set_timer(0);                      // FUN_00405410(0)
            }
        }
    };
    switch (s.state) {
    case 0: {   // entry motion (retail 0x425751)
        s.y = 48000 - s.timer * 8000 / 60;   // a3[244] = 48000 - 8000*a3[286]/0x3C
        s.py = (float)s.y * 0.01f;           // a3[241] = y * flt_470B00 (0.01f)
        // Retail writes the four familiar-slot level words on every entry
        // frame, independent of the formation rebuild's current count.
        s.familiar_levels = {1,1,1,1};
        // Entry-trail history ring (33 pairs at +0x436C, ring slot =
        // 8*spawn_count pairs): copy the ring pair into the tail pairs,
        // shift the ring by one pair, prepend (fx, y).
        const int c8 = 8 * s.spawn_count;    // a3[3392], the ring slot in pairs
        if (c8 < 32) {
            const int hx = s.history[2 * c8];
            const int hy = s.history[2 * c8 + 1];
            for (int k = 32; k > c8; --k) { s.history[2 * k] = hx; s.history[2 * k + 1] = hy; }
        }
        for (int i = (c8 < 32 ? c8 : 32); i >= 1; --i) {
            s.history[2 * i] = s.history[2 * (i - 1)];
            s.history[2 * i + 1] = s.history[2 * (i - 1) + 1];
        }
        s.history[0] = s.fx;                 // retail: +0x436C = +0x3CC
        s.history[1] = s.y;                  // retail: +0x4370 = +0x3D0
        if (s.timer < 30) {                  // retail: t < 0x1E
            const float radius = (float)s.timer * 17.066667f + 64.0f;  // flt_470D44/470BC8
            if (e.entry_effect_ex) {
                e.entry_effect_ex(radius, 0, 1);           // sub_408100(radius, 0, 1)
                e.entry_effect_ex(radius * 0.25f, 0, 0);   // sub_408100(radius*flt_470D40, 0, 0)
            } else if (e.entry_effect) {
                e.entry_effect(radius, 1);
                e.entry_effect(radius * 0.25f, 0);
            }
            if (e.entry_bullets_ex)
                e.entry_bullets_ex(radius, 0);              // sub_41C800(manager, radius)
            else if (e.entry_bullets)
                e.entry_bullets(radius);
        } else {
            if (e.sweep_enemy) e.sweep_enemy(0, 0);
            if (e.clear_bullets) e.clear_bullets(0);
        }
        if (s.timer >= 60) {                 // retail: 0x3B < t -> state 1
            s.state = 1;
            set_timer(0);                    // retail: a3[285]=-1, a3[286]=0, a3[287]=0
            play();                          // retail: goto case 1 body
        }
        break;
    }
    case 1:
        play();
        break;
    case 2:
        death();                             // retail: goto shared path
        break;
    case 3:   // clear state (retail 0x425D25): t == 15 (t != 4 kept for
        // shape; retail has no +4==0 gate on this sweep)
        if (s.timer != 4 && s.timer == 15) {
            if (e.sweep_enemy) e.sweep_enemy(0, 0);
            if (e.clear_bullets) e.clear_bullets(1);   // sub_41C850
        }
        break;
    case 4:   // death state (retail 0x425A96)
        if (s.timer >= 8) {                  // retail: 7 < t
            if (e.hitbox_update) e.hitbox_update(s);   // sub_4269D0 (point decay, state 2, invuln 180)
            death();                         // retail: goto shared path
        } else {
            // revive drain (retail 0x425BD9): game state type 0 &&
            // power/20 != 0 && dword_474E5C bit 0x2
            if (e.focus_object && s.power / 20 != 0 && (input & 2)) {
                set_timer(60);               // FUN_00405410(0x3C) on a3[285..289]
                set_invuln(200);             // FUN_00405410(200) on a3[4291..4295]
                if (e.focus_drain) e.focus_drain();    // sub_405860
                s.power -= 20;
                if (e.attached_effects) e.attached_effects(s);   // sub_426F70
                if (e.power_hud) e.power_hud(s.power / 20, (s.power % 20) * 100 / 20);
                s.state = 1;
            }
        }
        break;
    default:
        break;
    }
    // ---- retail tail (0x425D72..) ----
    // The indicator pool is updated first. The newly-written invulnerability
    // value from a switch callback is then decremented before blink observes
    // it, exactly as raw 0x425EE6-0x425EF1.
    UpdateIndicatorPool(s, spd);
    if (s.invulnerable >= 1) {
        if ((s.invulnerability_timer.flags & 1u)==0) {
            s.invulnerability_timer.target=s.invulnerable-1;
            s.invulnerability_timer.current=s.invulnerable;
            s.invuln_frac=(float)s.invulnerable;
            s.invulnerability_timer.flags|=1u;
        }
        s.invulnerability_timer.target=s.invulnerable;
        s.invulnerability_timer_speed=spd;
        s.invulnerability_timer.speed=&s.invulnerability_timer_speed;
        if (0.99f < spd && spd < 1.01f)
            s.invuln_frac -= 1.0f;
        else
            s.invuln_frac -= spd;
        s.invulnerable=static_cast<int>(s.invuln_frac);
        s.invulnerability_timer.current=s.invulnerable;
        s.invulnerability_timer.previous=FloatBits(s.invuln_frac);
    }

    if (s.invulnerable < 1) {
        s.blink = false;                     // a3[220] bit15 clear
    } else if (s.timer != s.timer_prev && s.timer % 3 == 0) {
        s.flash_color = 0xFF0000FF;          // a3[197]
        s.blink = true;                      // a3[220] bit15 set
    } else {
        s.blink = false;
    }
    if (e.anm_tick) e.anm_tick(s);           // sub_43EE30(a1+0x14, a1+0x14)
    // Rect sets from the live position and the three half-extent triples.
    {
        const float pos[3] = {s.px, s.py, s.pz};
        for (int a = 0; a < 3; ++a) {
            s.rect_off[a] = pos[a] - s.size_a[a];          // a3[257..262] = pos +/- size_a
            s.rect_off[a + 3] = pos[a] + s.size_a[a];
            s.rect_outer[a] = pos[a] - 0.5f * s.size_b[a]; // a3[4297..4302] = pos +/- size_b*0.5
            s.rect_outer[a + 3] = pos[a] + 0.5f * s.size_b[a];
            s.rect_focus[a] = pos[a] - s.size_c[a];       // a3[4303..4308] = pos +/- size_c
            s.rect_focus[a + 3] = pos[a] + s.size_c[a];
            s.rect_magnet[a] = pos[a] - s.size_b[a];      // a3[4309..4314] = pos +/- size_b
            s.rect_magnet[a + 3] = pos[a] + s.size_b[a];
        }
    }
    // Retail state timer advance (raw 0x4261A0) runs after callbacks,
    // blink, animation, and rectangle writes. Callbacks therefore observe the
    // pre-advance timer and a newly-set timer advances only here.
    s.state_timer_speed=spd;
    s.state_timer.speed=&s.state_timer_speed;
    s.timer_prev=s.timer;
    if (0.99f < spd && spd < 1.01f) {
        s.timer_frac += 1.0f;
        s.timer=s.timer_prev + 1;
    } else {
        s.timer_frac += spd;
        s.timer=static_cast<int>(s.timer_frac); // retail __ftol2 truncates
    }
    s.hold_timer_speed=spd;
    s.hold_timer_state.speed=&s.hold_timer_speed;
    AdvanceAuxiliaryTimer(s, spd);

    // sub_424D90's external reset remains outside this function's contract.
    bool hold_path = false;                  // retail: sub_4281D0 skips LABEL_115
    if (e.player_present) {
        if (e.hold_enabled && s.timer % 60 == 0) {
            e.frame_counter = std::clamp(e.frame_counter + 1, -1024, 1024);  // DAT_00474C98
            if (env) env->frame_counter = e.frame_counter;
        }
        if (e.hold_enabled) {
            if (e.hold_update) e.hold_update(s);   // sub_4281D0
            hold_path = true;
        }
    }
    if (!hold_path) {
        // retail LABEL_115: hard reset of the hold-timer struct (a3[280..284])
        if ((s.hold_flags & 1) == 0) {
            s.hold_timer = 0;
            s.hold_timer_prev = -999999;     // 0xFFF0BDC1 first-use sentinel
            s.hold_timer_frac = 0.0f;
            s.hold_flags |= 1;
        }
        s.hold_timer = -1;                   // 0xFFFFFFFF
        s.hold_timer_frac = -1.0f;           // 0xBF800000
        s.hold_timer_prev = -2;              // 0xFFFFFFFE
        s.field_3393 = 0;                    // a3[3393] (+0x3504)
        s.byte_13576 = 0;                    // +0x3508
    }
    if (e.tail_update) e.tail_update(s);     // sub_428280
    MirrorEmbeddedTimers(s);
    return 1;                                // retail returns 1
}

// 0x00426500 - Retail forwarder: `return sub_425730(a1, a2, a1)` - a tail
// jump into the player state runtime (0x00425730) with the player record
// as the env source.  The host alias routes to the same reconstruction
// with the default env (the retail env fields come from the player record
// the host model keeps in the PlayerRuntime/environment).
int UpdatePlayerStateAlias(PlayerRuntime& s, std::uint32_t input) {
    return UpdatePlayerState(s, input);
}

// Partial host-side model of retail 0x00426F70 (sub_426F70, attached-effect
// sprite management / familiar-formation refresh).
// STATUS: PARTIAL. Record-local formation writes and external calls are
// represented through typed fields/hooks; live ANM-list traversal and manager
// object mutation remain outside this host contract.
// RETAIL-ORDERED (asm-verified this pass, full 0x00426F70 listing), sweep 1:
// the four effect-handle slots (a1+0x330C, stride 0x98).  With the power
// gauge (word_474C48) < 100 every live handle found in the two ANM lists
// (g_pGameStateManager+0x72DAD4 / +0x72DADC) gets record word +0x304 = 1
// (frame; the linked chain at record[+0x14] when record[+0x18] == 0 too).
// With the gauge >= 100 every live handle gets record[+0x35C] |= 0x4000000
// (linked chain too), then the slot is cleared and refetched through
// sub_448E30(player ANM VM a1+0x10, 0x14 + (shot + 3*difficulty) % 3, 0xF)
// -- sprite 20/21/22 -- and the new handle goes back into the slot.  The
// `shot`/`difficulty` fields map to dword_474C6C/dword_474C68.  NOTE: retail
// refetches ALL four slots on the >= 100 path (empty ones included); the
// host only reports the refetch ids of slots that held a live handle
// (`events` is a host channel; tests/final_722_recovery_test.cpp pins that
// contract, and with a null refetch_sprite hook the refetched handles stay
// cleared either way).
// The second sweep is represented in FamiliarSlot and the formation inputs:
// level c/20 (cap 4), mode/position/random words, old-handle flagging,
// excess-slot release, level words, script selection, and callback selection
// are all retained. External ANM allocation/randomness stays behind hooks;
// formation_partial records a call that lacks those external channels.
// `events` remains only the host channel for live effect-slot refetch ids
// 20/21/22; retail itself publishes no event vector.
void UpdateAttachedEffects(AttachedEffects&s,int c){
    s.counter=c; // host-side counter; retail gates on word_474C48 (>= 100)
    s.events.clear();
    auto live_handle = [&](int handle) {
        if (handle == 0)
            return false;
        // A concrete adapter searches both retail intrusive lists.  The old
        // callback remains a compatibility channel for callers that do not
        // bind a manager in this standalone process.
        if (s.animation_manager && s.animation_manager->HasManager())
            return s.animation_manager->IsLive(handle);
        if (!s.handle_live) {
            s.manager_partial=true;
            return false;
        }
        return s.handle_live(handle);
    };
    auto mark_high = [&](int handle) {
        if (s.animation_manager && s.animation_manager->HasManager()) {
            if (!s.animation_manager->SetHighPathFlag(handle))
                s.manager_partial=true;
            return;
        }
        if (s.flag_linked)
            s.flag_linked(handle);
        else
            s.manager_partial=true;
    };
    auto mark_low = [&](int handle) {
        if (s.animation_manager && s.animation_manager->HasManager()) {
            if (!s.animation_manager->SetLowPathFrame(handle, 1))
                s.manager_partial=true;
            return;
        }
        if (s.frame_linked)
            s.frame_linked(handle);
        else
            s.manager_partial=true;
    };
    auto refetch_sprite_for = [&]() {
        // Raw switch 0x42704E: cases 0/3 -> 0x14, 1/4 -> 0x15,
        // 5 -> 0x16; case 2 and out-of-range leave the slot empty.
        switch (s.shot + 3*s.difficulty) {
        case 0: case 3: return 20;
        case 1: case 4: return 21;
        case 5: return 22;
        default: return -1;
        }
    };
    if(c>=100){
        const int sprite=refetch_sprite_for();
        for(int i=0;i<4;++i){
            const bool live=live_handle(s.handles[i]);
            if(live){
                // Retail high path writes ANM record +0x35C and its linked
                // chain, independent of the low-path +0x304 frame word.
                s.animation_flags[i]|=0x4000000u;
                mark_high(s.handles[i]);
            }
            // 0x42702F clears every slot, including empty/stale records,
            // before the exact six-way refetch switch.
            s.handles[i]=0;
            if (sprite >= 0) {
                const bool adapter_bound =
                    s.animation_manager != 0 &&
                    s.animation_manager->HasManager() &&
                    s.animation_manager->HasResourceBinding();
                if (adapter_bound) {
                    s.handles[i] = s.animation_manager->Refetch(sprite, 0x0F);
                    if (s.handles[i] == 0)
                        s.manager_partial=true;
                } else if (s.refetch_animation)
                    s.handles[i] = s.refetch_animation(i, sprite, 0x0F);
                else if (s.refetch_sprite)
                    s.handles[i] = s.refetch_sprite(sprite);
                else {
                    s.manager_partial=true;
                    s.formation_partial=true;
                }
                if (s.animation_manager != 0 && !adapter_bound)
                    s.manager_partial=true;
            }
            if(live && sprite>=0)s.events.push_back(sprite);
        }
    }else{
        // Retail low path only writes the distinct 16-bit +0x304 frame state
        // of live ANM records; it does not clear or overwrite +0x35C flags.
        for(int i=0;i<4;++i){
            if(live_handle(s.handles[i])){
                s.frame_states[i]=1;
                mark_low(s.handles[i]);
            }
        }
    }

    // Retail LAB_00427169 onward rebuilds the familiar formation whenever
    // gauge/20 (capped at four) changes. This is separate from the four
    // effect-handle slots above: each familiar has its own ANM handle at
    // +0x3308 and mode/index/position words in a 0x98-byte record.
    const int level = std::max(0, std::min(4, c / 20));
    if(s.familiar_count == level)
        return;

    auto mark_and_clear = [&](FamiliarSlot& slot) {
        // The release sweep writes mode=0 first, then marks a live familiar
        // with the low +0x304 frame state. It does not use the high +0x35C
        // retirement flag used when rebuilding an active slot.
        const int old_handle=slot.handle;
        slot.mode=0;
        if(live_handle(old_handle))
            mark_low(old_handle);
        // Retail leaves the old ANM handle word untouched; manager ownership
        // decides when that object is reclaimed.
    };
    for(int i=level;i<4;++i)
        mark_and_clear(s.familiar_slots[i]);

    int random_index=0;
    auto random_word = [&]() {
        if(s.formation.random_word)
            return static_cast<int>(s.formation.random_word());
        s.formation_partial=true;
        if(random_index<4)
            return s.formation.random_values[random_index++];
        return 0;
    };
    int base_random_x=0;
    int base_random_y=0;
    bool base_random_ready=false;
    auto base_random = [&]() {
        if(!base_random_ready){
            base_random_x=random_word();
            base_random_y=random_word();
            base_random_ready=true;
        }
    };
    auto read_pair = [&](std::array<int,4>& random, int offset,
                         const std::array<int,2>& table_pair) {
        if (s.formation.table_offsets_valid) {
            random[offset]=table_pair[0];
            random[offset+1]=table_pair[1];
        } else {
            random[offset]=random_word();
            random[offset+1]=random_word();
        }
    };

    for(int i=0;i<level;++i){
        FamiliarSlot& slot=s.familiar_slots[i];
        const int old_mode=slot.mode;
        const int old_position_x=slot.position_x;
        const int old_position_y=slot.position_y;
        // +0x32DC/+0x32E0 are initialized from the player's current fixed
        // point position before mode-specific branches adjust them.
        slot.previous_x=s.formation.source_x;
        slot.previous_y=s.formation.source_y;
        const int old_handle=slot.handle;
        if (live_handle(old_handle))
            mark_high(old_handle);
        slot.handle=0;
        slot.index=i;
        // Retail writes mode=2 only after the ANM has been allocated and the
        // optional focus initialization/callback assignment has completed.
        slot.callback_kind=0;
        slot.script=0;
        slot.animation_flags=0;

        const bool focus=s.formation.focus;
        const int difficulty=s.difficulty;
        const int shot=s.shot;
        bool has_position=true;
        if(difficulty==0){
            read_pair(slot.random, 0, s.formation.table_pair_a[i]);
            read_pair(slot.random, 2, s.formation.table_pair_b[i]);
            const int random_base=focus ? 2 : 0;
            slot.position_x=s.formation.source_x + slot.random[random_base];
            slot.position_y=s.formation.source_y + slot.random[random_base+1];
            // Raw 0x4272D7 mirrors the computed d=0 position into +0x32DC.
            slot.previous_x=slot.position_x;
            slot.previous_y=slot.position_y;
        }else if(difficulty==1 && shot==0){
            if(!focus)
                read_pair(slot.random, 0, s.formation.table_pair_a[i]);
            read_pair(slot.random, 2, s.formation.table_pair_b[i]);
            slot.position_x=s.formation.player_positions[i][0];
            slot.position_y=s.formation.player_positions[i][1];
            if(focus && old_mode==0){
                if(i==0){
                    if (s.formation.table_offsets_valid) {
                        slot.random[0]=s.formation.table_pair_a[0][0];
                        slot.random[1]=s.formation.table_pair_a[0][1];
                    } else {
                        base_random();
                        slot.random[0]=base_random_x;
                        slot.random[1]=base_random_y;
                    }
                }else{
                    slot.random[0]=s.formation.defaults[i][0];
                    slot.random[1]=s.formation.defaults[i][1];
                }
            }
            // The initial position is the entry-trail pair selected by the
            // familiar index (retail writes this mirror after ANM creation).
        }else if(difficulty==1 && shot==1){
            read_pair(slot.random, 0, s.formation.table_pair_a[i]);
            read_pair(slot.random, 2, s.formation.table_pair_b[i]);
            const int random_base=focus ? 2 : 0;
            slot.position_x=s.formation.source_x + slot.random[random_base];
            slot.position_y=s.formation.source_y + slot.random[random_base+1];
        }else if(difficulty==1 && shot==2){
            read_pair(slot.random, 0, s.formation.table_pair_a[i]);
            if(!focus || old_mode==0){
                slot.position_x=s.formation.source_x + slot.random[0];
                slot.position_y=s.formation.source_y + slot.random[1];
                // Raw 0x4272D7 mirrors the computed position into the
                // second random pair (+0x32EC/+0x32F0).
                slot.random[2]=slot.position_x;
                slot.random[3]=slot.position_y;
            }else{
                // Retail preserves the focused slot's existing target when
                // the orbit is already active.
                slot.position_x=old_position_x;
                slot.position_y=old_position_y;
            }
        }else{
            // Retail still materializes mode/index/positions for unsupported
            // difficulty/shot combinations, but does not create an ANM.
            has_position=false;
            s.formation_partial=true;
        }

        if(has_position && difficulty<=1 && shot>=0 && shot<=2){
            slot.script=0x11+shot;
            slot.animation_flags=0x40000000u;
            // Raw d=1/shot0 stores FUN_00427950 at +0x3330 before creating
            // the ANM. d=1/shot2 creates first, runs focused init, then
            // stores FUN_00427AD0. Keep those observable orderings separate.
            if(difficulty==1 && shot==0){
                slot.callback_kind=1;
                if(s.formation.set_callback){
                    s.formation.callback_order.push_back(1);
                    s.formation.set_callback(i,slot.callback_kind);
                }
            }
            const bool adapter_bound =
                s.animation_manager != 0 &&
                s.animation_manager->HasManager() &&
                s.animation_manager->HasResourceBinding();
            if (adapter_bound) {
                const float position[3] = {
                    static_cast<float>(slot.position_x),
                    static_cast<float>(slot.position_y), 0.0f
                };
                s.formation.callback_order.push_back(2);
                slot.handle=s.animation_manager->Create(
                    slot.script, 0x0F, position);
                if (slot.handle == 0)
                    s.manager_partial=true;
            } else if (s.formation.create_animation_ex) {
                s.formation.callback_order.push_back(2);
                slot.handle=s.formation.create_animation_ex(
                    i, slot.script, 0x0F, 0x40000000u);
            } else if(s.formation.create_animation){
                s.formation.callback_order.push_back(2);
                slot.handle=s.formation.create_animation(i,slot.script);
            } else {
                s.formation_partial=true;
            }
            if (s.animation_manager != 0 && !adapter_bound)
                s.manager_partial=true;
            if(difficulty==1 && shot==0){
                // Raw 0x427381 writes the history mirror after creation.
                slot.previous_x=s.formation.history[16*i];
                slot.previous_y=s.formation.history[16*i+1];
            }
            if(difficulty==1 && shot==2){
                if(focus && s.formation.focus_init){
                    s.formation.callback_order.push_back(3);
                    s.formation.focus_init(i);
                }
                slot.callback_kind=2;
                if(s.formation.set_callback){
                    s.formation.callback_order.push_back(1);
                    s.formation.set_callback(i,slot.callback_kind);
                }
            }
        }
        // Common tail at 0x42782F: every rebuilt record becomes active only
        // after its branch-specific manager calls have completed.
        slot.mode=2;
    }
    s.familiar_count=level;
    s.familiar_levels={1,1,1,1};
}

}
