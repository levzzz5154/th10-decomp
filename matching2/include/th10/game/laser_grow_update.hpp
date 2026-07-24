#pragma once

// Laser wait/grow/hold/shrink state machine and collision (retail 0x0041E700).
// Retail function 0x0041E700.
struct GrowLaser{int state,timer_current;float timer_elapsed,position[3],angle,length,width,secondary_render_gate,velocity[3],angular_velocity,target_length,length_growth,target_width;int wait_frames,grow_frames,hold_frames,shrink_frames;unsigned flags;float sprite_width,sprite_height,render_scale[2];unsigned render_flags;};struct GrowLaserEnv{float game_speed;const float*player_position;float(*add_normalized_angle)(float,float);int(*collision_test)(const float[3],float,float,float);void(*on_player_hit)(GrowLaser*);void(*on_graze_effect)(GrowLaser*);void(*update_primary_vm)(GrowLaser*);void(*update_secondary_vm)(GrowLaser*);};int Laser_UpdateState(GrowLaser*,const GrowLaserEnv*);
