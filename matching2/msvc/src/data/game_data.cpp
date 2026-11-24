// Initialized game globals and lookup tables in .data (0x00474170..0x0047700B).
// Compiled with MSVC 7.1 and placed via matching2/msvc/build_support/data_layout.json.
#include <stddef.h>

struct HintNameEntry {
    unsigned int name_va;
    int flags;
};

struct StageRouteData {
    int stage_id;
    unsigned int std_path_va;
    unsigned int anm_path_va;
    unsigned int ecl_path_va;
    unsigned int bgm_stage_va;
    unsigned int bgm_boss_va;
    unsigned int msg_mid_va;
    unsigned int msg_boss_va;
    unsigned int logo_anm_va;
    int bgm_stage_id;
    int bgm_boss_id;
    int reserved;
};

struct PixelFormatDesc {
    int d3d_format;
    unsigned int bits_per_pixel;
    unsigned int alpha_mask;
    unsigned int red_mask;
    unsigned int green_mask;
    unsigned int blue_mask;
};

struct SoundEffectSetting {
    int buffer_id;
    short volume_mb;
    short priority;
};

struct KeyBindingDefaults {
    short keys[9];
};

#pragma data_seg(".d01")
extern "C" int g_bullet_script_first[28] = {
    0, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 275, 283, 291, 299, 307, 347, 373, 315, 323, 331, 339, 240, 48, 374, 243, 0
};
#pragma data_seg()

#pragma data_seg(".d02")
extern "C" float g_bullet_hitbox_per_type[28] = {
    4.0f, 6.0f, 6.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 6.0f, 10.0f, 8.0f, 8.0f, 8.0f, 8.0f, 28.0f, 6.0f, 10.0f, 8.0f, 8.0f, 8.0f, 6.0f, 4.0f, 6.0f, 4.0f, 0.0f
};
#pragma data_seg()

#pragma data_seg(".d03")
extern "C" int g_bullet_render_layer_per_type[28] = {
    5, 3, 3, 4, 4, 4, 3, 4, 4, 4, 4, 3, 1, 2, 2, 2, 2, 0, 2, 2, 2, 1, 2, 3, 5, 2, 4, 0
};
#pragma data_seg()

#pragma data_seg(".d04")
extern "C" int g_bullet_death_selector[27] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 1, 0, 0, 4, 0
};
#pragma data_seg()

#pragma data_seg(".d05")
extern "C" int g_bullet_death_animation[9] = {
    17, 21, 25, 29, 33, 37, 41, 47, 0
};
#pragma data_seg()

#pragma data_seg(".d06")
extern "C" unsigned int g_burst_color_small[16] = {
    0xff808080u, 0xffff1010u, 0xffff1010u, 0xff801080u, 0xff801080u, 0xff1010ffu, 0xff1010ffu, 0xff108080u, 0xff108080u, 0xff10ff10u, 0xff10ff10u, 0xff10ff10u, 0xff808010u, 0xff808010u, 0xff808010u, 0xff808080u
};
#pragma data_seg()

#pragma data_seg(".d07")
extern "C" unsigned int g_burst_color_medium[8] = {
    0xff808080u, 0xffff1010u, 0xff801080u, 0xff1010ffu, 0xff108080u, 0xff10ff10u, 0xff808010u, 0xff808080u
};
#pragma data_seg()

#pragma data_seg(".d08")
extern "C" unsigned int g_burst_color_large[4] = {
    0xffff1010u, 0xff1010ffu, 0xff10ff10u, 0xff808010u
};
#pragma data_seg()

#pragma data_seg(".d09")
extern "C" signed char g_spell_card_difficulties[112] = {
    2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0
};
#pragma data_seg()

#pragma data_seg(".d10")
extern "C" int g_effect_kinds[4] = {
    352, 4239952, 0, 0
};
#pragma data_seg()

#pragma data_seg(".d11")
extern "C" unsigned int g_ending_files[13] = {
    0x0046d0acu, 0x0046d0a4u, 0x0046d09cu, 0x0046d094u, 0x0046d08cu, 0x0046d084u, 0x0046d07cu, 0x0046d074u, 0x0046d06cu, 0x0046d064u, 0x0046d05cu, 0x0046d054u, 0x0046d048u
};
#pragma data_seg()

#pragma data_seg(".d12")
extern "C" int g_next_extend_score[8] = {
    2000000, 4000000, 8000000, 15000000, 1000000000, 3000000, 10000000, 1000000000
};
#pragma data_seg()

#pragma data_seg(".d13")
extern "C" HintNameEntry g_hint_align_names[3] = {
    { 0x0046d9c0u, 0 }, // center
    { 0x0046d9b8u, 1 }, // left
    { 0x0046d9b0u, 2 }, // right
};
#pragma data_seg()

#pragma data_seg(".d14")
extern "C" HintNameEntry g_hint_base_names[69] = {
    { 0x0046d9a8u, 0 }, // start
    { 0x0046d99cu, 1 }, // converse_1
    { 0x0046d990u, 2 }, // converse_2
    { 0x0046d984u, 3 }, // converse_3
    { 0x0046d978u, 4 }, // converse_4
    { 0x0046d96cu, 5 }, // converse_5
    { 0x0046d964u, 6 }, // mboss_1
    { 0x0046d95cu, 7 }, // mboss_2
    { 0x0046d954u, 8 }, // mboss_3
    { 0x0046d94cu, 9 }, // mboss_4
    { 0x0046d944u, 10 }, // mboss_5
    { 0x0046d93cu, 11 }, // mboss_6
    { 0x0046d934u, 12 }, // mboss_7
    { 0x0046d92cu, 13 }, // mboss_8
    { 0x0046d924u, 14 }, // mboss_9
    { 0x0046d914u, 15 }, // mboss_card_1
    { 0x0046d904u, 16 }, // mboss_card_2
    { 0x0046d8f4u, 17 }, // mboss_card_3
    { 0x0046d8e4u, 18 }, // mboss_card_4
    { 0x0046d8d4u, 19 }, // mboss_card_5
    { 0x0046d8c4u, 20 }, // mboss_card_6
    { 0x0046d8b4u, 21 }, // mboss_card_7
    { 0x0046d8a4u, 22 }, // mboss_card_8
    { 0x0046d894u, 23 }, // mboss_card_9
    { 0x0046d88cu, 24 }, // boss_1
    { 0x0046d884u, 25 }, // boss_2
    { 0x0046d87cu, 26 }, // boss_3
    { 0x0046d874u, 27 }, // boss_4
    { 0x0046d86cu, 28 }, // boss_5
    { 0x0046d864u, 29 }, // boss_6
    { 0x0046d85cu, 30 }, // boss_7
    { 0x0046d854u, 31 }, // boss_8
    { 0x0046d84cu, 32 }, // boss_9
    { 0x0046d844u, 33 }, // boss_10
    { 0x0046d83cu, 34 }, // boss_11
    { 0x0046d834u, 35 }, // boss_12
    { 0x0046d82cu, 36 }, // boss_13
    { 0x0046d824u, 37 }, // boss_14
    { 0x0046d81cu, 38 }, // boss_15
    { 0x0046d814u, 39 }, // boss_16
    { 0x0046d80cu, 40 }, // boss_17
    { 0x0046d804u, 41 }, // boss_18
    { 0x0046d7fcu, 42 }, // boss_19
    { 0x0046d7f0u, 43 }, // boss_card_1
    { 0x0046d7e4u, 44 }, // boss_card_2
    { 0x0046d7d8u, 45 }, // boss_card_3
    { 0x0046d7ccu, 46 }, // boss_card_4
    { 0x0046d7c0u, 47 }, // boss_card_5
    { 0x0046d7b4u, 48 }, // boss_card_6
    { 0x0046d7a8u, 49 }, // boss_card_7
    { 0x0046d79cu, 50 }, // boss_card_8
    { 0x0046d790u, 51 }, // boss_card_9
    { 0x0046d780u, 52 }, // boss_card_10
    { 0x0046d770u, 53 }, // boss_card_12
    { 0x0046d760u, 54 }, // boss_card_13
    { 0x0046d750u, 55 }, // boss_card_14
    { 0x0046d740u, 56 }, // boss_card_15
    { 0x0046d730u, 57 }, // boss_card_16
    { 0x0046d720u, 58 }, // boss_card_17
    { 0x0046d710u, 59 }, // boss_card_18
    { 0x0046d700u, 60 }, // boss_card_19
    { 0xff808080u, -65536 },
    { 0xffff0000u, -8388480 },
    { 0xff800080u, -16776961 },
    { 0xff0000ffu, -16744320 },
    { 0xff008080u, -16711936 },
    { 0xff00ff00u, -16711936 },
    { 0xff808000u, -8355840 },
    { 0xff808000u, -8355712 },
};
#pragma data_seg()

#pragma data_seg(".d15")
extern "C" unsigned int g_ui_string_table[37] = {
    0x0046e2f8u, // ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-=.,!?@:;[]()_/{}|~^#$%&*   
    0x0046e2f0u, // ReimuA 
    0x0046e2e8u, // ReimuB 
    0x0046e2e0u, // ReimuC 
    0x0046e2d8u, // MarisaA
    0x0046e2d0u, // MarisaB
    0x0046e2c8u, // MarisaC
    0x0046e2c0u, // Easy   
    0x0046e2b8u, // Normal 
    0x0046e2b0u, // Hard   
    0x0046e2a8u, // Lunatic
    0x0046e2a0u, // Extra  
    0x0046e29cu, // E
    0x0046e298u, // N
    0x0046e294u, // H
    0x0046e290u, // L
    0x0046e28cu, // X
    0x0046e284u, // test   
    0x0046e27cu, // Stage 1
    0x0046e274u, // Stage 2
    0x0046e26cu, // Stage 3
    0x0046e264u, // Stage 4
    0x0046e25cu, // Stage 5
    0x0046e254u, // Stage 6
    0x0046e2a0u, // Extra  
    0x0046e24cu, // Clear  
    0x0046e244u, // ExClear
    0x0046e240u, // tst
    0x0046e23cu, // St1
    0x0046e238u, // St2
    0x0046e234u, // St3
    0x0046e230u, // St4
    0x0046e22cu, // St5
    0x0046e228u, // St6
    0x0046e224u, // Ex 
    0x0046e220u, // All
    0x0046e21cu, // ExA
};
#pragma data_seg()

#pragma data_seg(".d16")
extern "C" unsigned int g_shot_callback_tables[7] = {
    0x00000000u, 0x00428ad0u, 0x00000000u, 0x00000000u, 0x00428b10u, 0x00428c20u, 0x00000000u
};
#pragma data_seg()

#pragma data_seg(".d17")
extern "C" StageRouteData g_stage_routes[8] = {
    { 0, 0x0046ecdcu, 0x0046ecccu, 0x0046ecc0u, 0x0046ecb0u, 0x0046eca0u, 0x0046ec94u, 0x0046ec94u, 0x0046ec84u, 0, 0, 0 },
    { 1, 0x0046ec78u, 0x0046ec68u, 0x0046ec5cu, 0x0046ecb0u, 0x0046eca0u, 0x0046ec94u, 0x0046ec50u, 0x0046ec84u, 1, 2, 0 },
    { 2, 0x0046ec44u, 0x0046ec34u, 0x0046ec28u, 0x0046ec18u, 0x0046ec08u, 0x0046ebfcu, 0x0046ebf0u, 0x0046ebe0u, 3, 4, 0 },
    { 3, 0x0046ebd4u, 0x0046ebc4u, 0x0046ebb8u, 0x0046eba8u, 0x0046eb98u, 0x0046eb8cu, 0x0046eb80u, 0x0046eb70u, 5, 6, 0 },
    { 4, 0x0046eb64u, 0x0046eb54u, 0x0046eb48u, 0x0046eb38u, 0x0046eb28u, 0x0046eb1cu, 0x0046eb10u, 0x0046eb00u, 7, 8, 0 },
    { 5, 0x0046eaf4u, 0x0046eae4u, 0x0046ead8u, 0x0046eac8u, 0x0046eab8u, 0x0046eaacu, 0x0046eaa0u, 0x0046ea90u, 9, 10, 0 },
    { 6, 0x0046ea84u, 0x0046ea74u, 0x0046ea68u, 0x0046ea58u, 0x0046ea48u, 0x0046ea3cu, 0x0046ea30u, 0x0046ea20u, 11, 12, 0 },
    { 7, 0x0046ea14u, 0x0046ea04u, 0x0046e9f8u, 0x0046e9e8u, 0x0046e9d8u, 0x0046e9ccu, 0x0046e9c0u, 0x0046e9b0u, 13, 14, 0 },
};
#pragma data_seg()

#pragma data_seg(".d18")
extern "C" unsigned int g_file_open_modes[3] = {
    0x0046f2c0u, 0x0046f2bcu, 0x0046f2b8u
};
#pragma data_seg()

#pragma data_seg(".d19")
extern "C" PixelFormatDesc g_font_formats[6] = {
    { 22, 32u, 0x00000000u, 0x00ff0000u, 0x0000ff00u, 0x000000ffu },
    { 21, 32u, 0xff000000u, 0x00ff0000u, 0x0000ff00u, 0x000000ffu },
    { 24, 16u, 0x00000000u, 0x00007c00u, 0x000003e0u, 0x0000001fu },
    { 23, 16u, 0x00000000u, 0x0000f800u, 0x000007e0u, 0x0000001fu },
    { 25, 16u, 0x00008000u, 0x00007c00u, 0x000003e0u, 0x0000001fu },
    { 26, 16u, 0x0000f000u, 0x00000f00u, 0x000000f0u, 0x0000000fu },
};
#pragma data_seg()

#pragma data_seg(".d20")
extern "C" int g_font_formats_end = -1;
#pragma data_seg()

#pragma data_seg(".d21")
extern "C" int g_sound_default_enabled = 1;
#pragma data_seg()

#pragma data_seg(".d22")
extern "C" SoundEffectSetting g_sound_effect_settings[79] = {
    { 0, -1900, 0 },
    { 0, -2100, 0 },
    { 1, -1200, 5 },
    { 1, -1500, 5 },
    { 2, -1100, 100 },
    { 3, -700, 100 },
    { 4, -700, 100 },
    { 5, -1900, 50 },
    { 6, -2200, 50 },
    { 7, -2400, 50 },
    { 8, -500, 100 },
    { 9, -400, 100 },
    { 10, -800, 10 },
    { 11, -1500, 10 },
    { 12, -1000, 100 },
    { 5, -1100, 50 },
    { 13, -1300, 50 },
    { 14, -1400, 50 },
    { 15, -900, 100 },
    { 16, -880, 0 },
    { 17, -1500, 0 },
    { 5, -300, 20 },
    { 6, -1800, 20 },
    { 7, -1800, 20 },
    { 18, -1100, 50 },
    { 19, -1300, 50 },
    { 20, -1500, 50 },
    { 21, -500, 100 },
    { 22, -1100, 20 },
    { 23, -800, 90 },
    { 22, -1200, 20 },
    { 18, -500, 50 },
    { 24, -800, 100 },
    { 25, -800, 100 },
    { 26, -800, 100 },
    { 27, -500, 0 },
    { 28, -300, 100 },
    { 29, 0, 100 },
    { 30, 0, 100 },
    { 30, -600, 100 },
    { 8, -300, 100 },
    { 31, -300, 100 },
    { 32, -300, 100 },
    { 33, -300, 100 },
    { 34, -100, 100 },
    { 35, 0, 100 },
    { 36, -800, 50 },
    { 4653236, 164, 71 },
    { 4653204, 132, 71 },
    { 4653172, 100, 71 },
    { 4653140, 68, 71 },
    { 4653112, 40, 71 },
    { 4653080, 8, 71 },
    { 4653048, -24, 70 },
    { 4653016, -56, 70 },
    { 4652984, -88, 70 },
    { 4652952, -120, 70 },
    { 4652920, -152, 70 },
    { 4652888, -184, 70 },
    { 4652856, -216, 70 },
    { 4652824, -248, 70 },
    { 4652792, -280, 70 },
    { 4652760, -308, 70 },
    { 4652736, -336, 70 },
    { 4652704, -368, 70 },
    { 4652672, 0, 0 },
    { 11155227, 64, 0 },
    { 10240, -5807, 187 },
    { 64, 12288, 0 },
    { 13390273, 128, 0 },
    { 12800, 6403, 221 },
    { 1024, 30720, 0 },
    { 15650219, 512, 0 },
    { 10240, 13330, 255 },
    { 128, 12800, 0 },
    { 1152821, 128, 0 },
    { 10240, 14233, 119 },
    { 1024, 8192, 0 },
    { -1, 0, 0 },
};
#pragma data_seg()

#pragma data_seg(".d23")
extern "C" int g_globals_default_474c54 = -1;
#pragma data_seg()

#pragma data_seg(".d24")
extern "C" int g_globals_difficulty_default = 1;
#pragma data_seg()

#pragma data_seg(".d25")
extern "C" int g_font_texture_id_default = -1;
#pragma data_seg()

#pragma data_seg(".d26")
extern "C" unsigned int g_input_worker_vtable = 0x004703e4u;
#pragma data_seg()

#pragma data_seg(".d27")
extern "C" float g_enemy_project_viewport_identity[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};
#pragma data_seg()

#pragma data_seg(".d28")
extern "C" KeyBindingDefaults g_key_bindings_default_0 = { { 0, 1, 2, 3, -1, -1, -1, -1, 4 } };
#pragma data_seg()

#pragma data_seg(".d29")
extern "C" KeyBindingDefaults g_key_bindings_default_1 = { { 0, 1, 2, 3, -1, -1, -1, -1, 4 } };
#pragma data_seg()

#pragma data_seg(".d30")
extern "C" KeyBindingDefaults g_key_bindings_default_2 = { { 0, 1, 2, 3, -1, -1, -1, -1, 4 } };
#pragma data_seg()

#pragma data_seg(".d31")
extern "C" unsigned int g_log_write_cursor = 0x00474f70u;
#pragma data_seg()

#pragma data_seg(".d32")
extern "C" float g_game_speed_default = 1.0f;
#pragma data_seg()

#pragma data_seg(".d33")
extern "C" int g_stage_threshold_table[7] = {
    1, 3, 6, 10, 11, 13, 16
};
#pragma data_seg()

#pragma data_seg(".d34")
extern "C" float g_camera_defaults[8] = {
    5.0f, 7.0f, 100.0f, 118.0f, 40.0f, 48.0f, 2.0f, 3.5f
};
#pragma data_seg()

#pragma data_seg(".d35")
extern "C" unsigned int g_shot_music_demo_strings[19] = {
    0x0046e3e0u, // pl00a.sht
    0x0046e3d4u, // pl00b.sht
    0x0046e3c8u, // pl00c.sht
    0x0046e3bcu, // pl01a.sht
    0x0046e3b0u, // pl01b.sht
    0x0046e3a4u, // pl01c.sht
    0x0046ee34u, // 　
    0x0046edf8u, // 　　＊＊選択した曲はまだゲーム中で再生されていません＊＊
    0x0046cfd4u, //  
    0x0046edc0u, // 　　　　曲のコメントがネタバレになる恐れがあります。
    0x0046ed94u, // 　　　　　　　　　それでも再生しますか？
    0x0046ee34u, // 　
    0x0046ed5cu, // 　　　再生したい方はもう一度決定ボタンを押してください
    0x0046ed24u, // 　　　再生したくない方は、カーソルを移動してください
    0x0046f058u, // demo/demo1.rpy
    0x0046f048u, // demo/demo2.rpy
    0x0046f038u, // demo/demo3.rpy
    0x0046f028u, // demo/demo0.rpy
    0x00000000u, // 
};
#pragma data_seg()

