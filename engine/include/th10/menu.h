/*
 * TH10 Menu State Machine
 * Based on Ghidra RE of FUN_00433570 (replay screen) and FUN_004236f0 (save screen)
 *
 * State switch pattern: state = *(int*)(this+0x20); nextState = *(int*)(this+0x4)
 * Input polling: bitmask on 16-bit input word
 */
#pragma once
#include "th10/types.h"
#include <cstdint>
#include <string>
#include <array>
#include <vector>

namespace th10 {

enum class MenuState : int32_t {
    TITLE          = 0,
    MAIN_MENU      = 1,
    START_GAME     = 2,
    STAGE_SELECT   = 3,
    DIFF_SELECT    = 4,
    SHOT_SELECT    = 5,
    OPTIONS        = 6,
    REPLAY_LIST    = 7,
    REPLAY_PLAY    = 8,
    PRACTICE_MENU  = 9,
    PRACTICE_START = 10,
    MUSIC_ROOM     = 11,
    RESULT         = 12,
    QUIT_CONFIRM   = 13,
    EXIT           = 14,
    INGAME_TITLE   = 15,
    PAUSED         = 16,
};

enum class MenuAnim : int32_t {
    NONE    = 0,
    FADE_IN = 1,
    SLIDE   = 2,
    FADE_OUT= 3,
};

struct MenuItem {
    std::string label;
    int32_t     target_state;
    bool        enabled;
};

struct MenuPage {
    std::string              title;
    std::vector<MenuItem>    items;
    int32_t                  cursor = 0;
    int32_t                  scroll_offset = 0;
    int32_t                  max_visible = 0;
    MenuAnim                 anim_in = MenuAnim::NONE;
    MenuAnim                 anim_out = MenuAnim::NONE;
    int32_t                  anim_timer = 0;
    uint32_t                 bg_color = 0xFF000000;

    MenuPage() = default;

    MenuPage(std::string t, std::vector<MenuItem> itms, int32_t cur, int32_t s_off,
             int32_t max_v, MenuAnim a_in, MenuAnim a_out, int32_t a_timer, uint32_t bg)
        : title(std::move(t)), items(std::move(itms)), cursor(cur),
          scroll_offset(s_off), max_visible(max_v),
          anim_in(a_in), anim_out(a_out), anim_timer(a_timer), bg_color(bg) {}
};

class MenuStateMachine {
public:
    MenuStateMachine();

    void init();
    void reset();
    bool update(const uint8_t* kb, bool z_pressed, bool esc_pressed);

    MenuState current_state() const { return state_; }
    MenuState next_state()    const { return next_state_; }
    void     set_state(MenuState s) { state_ = s; }

    bool              is_active()       const { return state_ != MenuState::EXIT; }
    bool              wants_to_play()   const { return next_state_ == MenuState::START_GAME; }
    int               selected_stage()  const { return selected_stage_; }
    Difficulty        selected_difficulty() const { return selected_difficulty_; }
    ShotType          selected_shot()   const { return selected_shot_; }
    int               selected_replay() const { return selected_replay_; }

    const MenuPage&   current_page()    const { return pages_[static_cast<int>(state_)]; }

    static constexpr int MAX_REPLAY_SLOTS = 20;

private:
    void transition_to(MenuState next);
    void build_pages();
    int  find_next_enabled(int from, int dir) const;

    MenuPage& active_page() { return pages_[static_cast<int>(state_)]; }
    const MenuPage& active_page() const { return pages_[static_cast<int>(state_)]; }

    void handle_title_input(bool z, bool esc);
    void handle_main_menu_input(bool z, bool esc);
    void handle_stage_select_input(bool z, bool esc);
    void handle_diff_select_input(bool z, bool esc);
    void handle_shot_select_input(bool z, bool esc);
    void handle_options_input(bool z, bool esc);
    void handle_replay_list_input(bool z, bool esc);
    void handle_practice_input(bool z, bool esc);
    void handle_exit_input(bool z, bool esc);

    MenuState            state_  = MenuState::TITLE;
    MenuState            next_state_ = MenuState::TITLE;
    std::array<MenuPage, 18> pages_;

    int32_t              frame_counter_ = 0;
    bool                 input_locked_  = false;
    int32_t              input_lock_timer_ = 0;

    Difficulty           selected_difficulty_ = Difficulty::Normal;
    ShotType             selected_shot_  = ShotType::ReimuA;
    int                  selected_stage_ = 0;
    int                  selected_replay_= 0;
};

} // namespace th10
