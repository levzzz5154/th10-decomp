#include "th10/menu.h"
#include <cstdio>
#include <algorithm>
#include <SDL2/SDL.h>

namespace th10 {

MenuStateMachine::MenuStateMachine() {
    build_pages();
}

void MenuStateMachine::build_pages() {
    // TITLE
    pages_[0] = MenuPage(
        "Touhou 10: Mountain of Faith",
        {}, 0, 0, 0,
        MenuAnim::FADE_IN, MenuAnim::NONE, 60, 0xFF000000);

    // MAIN_MENU
    pages_[1] = MenuPage(
        "Main Menu",
        {
            {"Start Game",     static_cast<int32_t>(MenuState::DIFF_SELECT),  true},
            {"Practice Start", static_cast<int32_t>(MenuState::PRACTICE_MENU),  true},
            {"Replay",         static_cast<int32_t>(MenuState::REPLAY_LIST),   true},
            {"Music Room",     static_cast<int32_t>(MenuState::MUSIC_ROOM),    true},
            {"Options",        static_cast<int32_t>(MenuState::OPTIONS),       true},
            {"Quit",           static_cast<int32_t>(MenuState::QUIT_CONFIRM),  true},
        },
        0, 0, 6,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // START_GAME - transient
    pages_[2] = MenuPage(
        "Starting...", {}, 0, 0, 0,
        MenuAnim::FADE_OUT, MenuAnim::NONE, 30, 0xFF000000);

    // STAGE_SELECT
    pages_[3] = MenuPage(
        "Select Stage",
        {
            {"Stage 1", 0, true},
            {"Stage 2", 0, true},
            {"Stage 3", 0, true},
            {"Stage 4", 0, true},
            {"Stage 5", 0, true},
            {"Stage 6", 0, true},
            {"Extra",   0, true},
            {"Back",    static_cast<int32_t>(MenuState::MAIN_MENU), true},
        },
        0, 0, 8,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // DIFF_SELECT
    pages_[4] = MenuPage(
        "Select Difficulty",
        {
            {"Easy",     static_cast<int32_t>(MenuState::SHOT_SELECT), true},
            {"Normal",   static_cast<int32_t>(MenuState::SHOT_SELECT), true},
            {"Hard",     static_cast<int32_t>(MenuState::SHOT_SELECT), true},
            {"Lunatic",  static_cast<int32_t>(MenuState::SHOT_SELECT), true},
            {"Extra",    static_cast<int32_t>(MenuState::SHOT_SELECT), true},
            {"Back",     static_cast<int32_t>(MenuState::MAIN_MENU),  true},
        },
        1, 0, 6,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // SHOT_SELECT
    pages_[5] = MenuPage(
        "Select Character",
        {
            {"Reimu A",  static_cast<int32_t>(MenuState::START_GAME), true},
            {"Reimu B",  static_cast<int32_t>(MenuState::START_GAME), true},
            {"Reimu C",  static_cast<int32_t>(MenuState::START_GAME), true},
            {"Marisa A", static_cast<int32_t>(MenuState::START_GAME), true},
            {"Marisa B", static_cast<int32_t>(MenuState::START_GAME), true},
            {"Marisa C", static_cast<int32_t>(MenuState::START_GAME), true},
            {"Back",     static_cast<int32_t>(MenuState::DIFF_SELECT), true},
        },
        0, 0, 7,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // OPTIONS
    pages_[6] = MenuPage(
        "Options",
        {
            {"Back", static_cast<int32_t>(MenuState::MAIN_MENU), true},
        },
        0, 0, 1,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // REPLAY_LIST
    {
        std::vector<MenuItem> replay_items;
        for (int i = 0; i < MAX_REPLAY_SLOTS; i++) {
            char buf[32];
            snprintf(buf, sizeof(buf), "Replay %02d", i + 1);
            replay_items.push_back({buf, static_cast<int32_t>(MenuState::REPLAY_PLAY), true});
        }
        replay_items.push_back({"Back", static_cast<int32_t>(MenuState::MAIN_MENU), true});
        pages_[7] = MenuPage(
            "Select Replay",
            std::move(replay_items),
            0, 0, 8,
            MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);
    }

    // REPLAY_PLAY - transient
    pages_[8] = MenuPage(
        "Playing Replay...", {}, 0, 0, 0,
        MenuAnim::NONE, MenuAnim::NONE, 0, 0xFF000000);

    // PRACTICE_MENU
    pages_[9] = MenuPage(
        "Practice Mode",
        {
            {"Stage 1",  static_cast<int32_t>(MenuState::STAGE_SELECT), true},
            {"Back",     static_cast<int32_t>(MenuState::MAIN_MENU),    true},
        },
        0, 0, 2,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // PRACTICE_START - transient
    pages_[10] = MenuPage(
        "Practice Starting...", {}, 0, 0, 0,
        MenuAnim::FADE_OUT, MenuAnim::NONE, 30, 0xFF000000);

    // MUSIC_ROOM
    pages_[11] = MenuPage(
        "Music Room",
        {
            {"Back", static_cast<int32_t>(MenuState::MAIN_MENU), true},
        },
        0, 0, 1,
        MenuAnim::SLIDE, MenuAnim::SLIDE, 20, 0xFF101020);

    // RESULT
    pages_[12] = MenuPage(
        "Result",
        {
            {"Continue", static_cast<int32_t>(MenuState::MAIN_MENU), true},
        },
        0, 0, 1,
        MenuAnim::FADE_IN, MenuAnim::NONE, 60, 0xFF000000);

    // QUIT_CONFIRM
    pages_[13] = MenuPage(
        "Really Quit?",
        {
            {"Yes", static_cast<int32_t>(MenuState::EXIT),             true},
            {"No",  static_cast<int32_t>(MenuState::MAIN_MENU),        true},
        },
        1, 0, 2,
        MenuAnim::NONE, MenuAnim::NONE, 0, 0xFF101020);

    // EXIT
    pages_[14] = MenuPage(
        "", {}, 0, 0, 0,
        MenuAnim::FADE_OUT, MenuAnim::NONE, 30, 0xFF000000);

    // INGAME_TITLE
    pages_[15] = MenuPage(
        "", {}, 0, 0, 0,
        MenuAnim::NONE, MenuAnim::NONE, 0, 0xFF000000);

    // PAUSED
    pages_[16] = MenuPage(
        "Paused",
        {
            {"Resume", static_cast<int32_t>(MenuState::INGAME_TITLE), true},
            {"Retry",  static_cast<int32_t>(MenuState::START_GAME),   true},
            {"Quit",   static_cast<int32_t>(MenuState::MAIN_MENU),    true},
        },
        0, 0, 3,
        MenuAnim::FADE_IN, MenuAnim::NONE, 15, 0x80404040);
}

void MenuStateMachine::init() {
    state_ = MenuState::TITLE;
    next_state_ = MenuState::TITLE;
    frame_counter_ = 0;
    input_locked_ = false;
    input_lock_timer_ = 0;

    // Reset cursors
    for (auto& p : pages_) {
        p.cursor = 0;
        p.anim_timer = p.anim_in != MenuAnim::NONE ? 60 : 0;
    }
    // Set difficulty cursor to Normal (index 1)
    pages_[4].cursor = 1;
}

void MenuStateMachine::reset() {
    init();
}

int MenuStateMachine::find_next_enabled(int from, int dir) const {
    const auto& items = active_page().items;
    if (items.empty()) return 0;

    int count = static_cast<int>(items.size());
    int idx = from;
    for (int attempt = 0; attempt < count; attempt++) {
        idx = (idx + dir + count) % count;
        if (items[idx].enabled) return idx;
    }
    return from;
}

void MenuStateMachine::transition_to(MenuState next) {
    next_state_ = next;
    input_locked_ = true;
    input_lock_timer_ = 15;
}

void MenuStateMachine::handle_title_input(bool z, bool esc) {
    if (frame_counter_ > 90 || z) {
        transition_to(MenuState::MAIN_MENU);
    }
    if (esc) {
        transition_to(MenuState::EXIT);
    }
}

void MenuStateMachine::handle_main_menu_input(bool z, bool esc) {
    auto& page = active_page();

    if (is_active() && page.items[page.cursor].target_state >= 0 && z) {
        MenuState target = static_cast<MenuState>(page.items[page.cursor].target_state);
        transition_to(target);
    }
    if (esc) transition_to(MenuState::QUIT_CONFIRM);
}

void MenuStateMachine::handle_stage_select_input(bool z, bool esc) {
    auto& page = active_page();
    if (esc) { transition_to(MenuState::PRACTICE_MENU); return; }
    if (z) {
        if (page.cursor < 7) {
            selected_stage_ = page.cursor;
            transition_to(MenuState::PRACTICE_START);
        } else {
            transition_to(static_cast<MenuState>(page.items[page.cursor].target_state));
        }
    }
}

void MenuStateMachine::handle_diff_select_input(bool z, bool esc) {
    auto& page = active_page();
    if (esc) { transition_to(MenuState::MAIN_MENU); return; }
    if (z) {
        if (page.cursor < 5) {
            selected_difficulty_ = static_cast<Difficulty>(page.cursor);
            transition_to(MenuState::SHOT_SELECT);
        } else {
            transition_to(static_cast<MenuState>(page.items[page.cursor].target_state));
        }
    }
}

void MenuStateMachine::handle_shot_select_input(bool z, bool esc) {
    auto& page = active_page();
    if (esc) { transition_to(MenuState::DIFF_SELECT); return; }
    if (z) {
        if (page.cursor < 6) {
            selected_shot_ = static_cast<ShotType>(page.cursor);
            transition_to(MenuState::START_GAME);
        } else {
            transition_to(static_cast<MenuState>(page.items[page.cursor].target_state));
        }
    }
}

void MenuStateMachine::handle_options_input(bool z, bool esc) {
    if (esc || z) transition_to(MenuState::MAIN_MENU);
}

void MenuStateMachine::handle_replay_list_input(bool z, bool esc) {
    auto& page = active_page();
    if (esc) { transition_to(MenuState::MAIN_MENU); return; }
    if (z) {
        if (page.cursor < MAX_REPLAY_SLOTS) {
            selected_replay_ = page.cursor;
            transition_to(MenuState::REPLAY_PLAY);
        } else {
            transition_to(MenuState::MAIN_MENU);
        }
    }
}

void MenuStateMachine::handle_practice_input(bool z, bool esc) {
    auto& page = active_page();
    if (esc) { transition_to(MenuState::MAIN_MENU); return; }
    if (z) {
        if (page.cursor == 0) {
            transition_to(MenuState::STAGE_SELECT);
        } else {
            transition_to(static_cast<MenuState>(page.items[page.cursor].target_state));
        }
    }
}

void MenuStateMachine::handle_exit_input(bool z, bool esc) {
    auto& page = active_page();
    if (z) {
        if (page.cursor == 0) {
            next_state_ = MenuState::EXIT;
        } else {
            transition_to(MenuState::MAIN_MENU);
        }
    }
    if (esc) transition_to(MenuState::MAIN_MENU);
}

bool MenuStateMachine::update(const uint8_t* kb, bool z_pressed, bool esc_pressed) {
    frame_counter_++;

    if (input_locked_) {
        input_lock_timer_--;
        if (input_lock_timer_ <= 0) {
            input_locked_ = false;
        }
        // Still process animation timers
        if (active_page().anim_in != MenuAnim::NONE && active_page().anim_timer > 0) {
            active_page().anim_timer--;
        }
        return false;
    }

    // If next_state differs, execute transition immediately
    if (static_cast<int>(next_state_) != static_cast<int>(state_)) {
        state_ = next_state_;
        auto& pg = active_page();
        pg.cursor = 0;
        pg.anim_timer = pg.anim_in != MenuAnim::NONE ? 60 : 0;
    }

    if (state_ == MenuState::TITLE) {
        if (z_pressed) {
            handle_title_input(true, esc_pressed);
        } else {
            handle_title_input(false, esc_pressed);
        }
        if (active_page().anim_timer > 0) active_page().anim_timer--;
        return true;
    }

    // Only process menu navigation for states with items
    auto& page = active_page();
    if (page.items.empty()) {
        if (state_ == MenuState::START_GAME || state_ == MenuState::REPLAY_PLAY ||
            state_ == MenuState::PRACTICE_START || state_ == MenuState::EXIT) {
            return true;
        }
        return false;
    }

    // Keyboard navigation with cooldown
    static int nav_cooldown = 0;
    if (nav_cooldown > 0) {
        nav_cooldown--;
    }

    if (nav_cooldown == 0) {
        if (kb[SDL_SCANCODE_UP] || kb[SDL_SCANCODE_W]) {
            page.cursor = find_next_enabled(page.cursor, -1);
            nav_cooldown = 12;
        }
        if (kb[SDL_SCANCODE_DOWN] || kb[SDL_SCANCODE_S]) {
            page.cursor = find_next_enabled(page.cursor, 1);
            nav_cooldown = 12;
        }
    }

    // Dispatch input based on state
    switch (state_) {
        case MenuState::MAIN_MENU:    handle_main_menu_input(z_pressed, esc_pressed); break;
        case MenuState::STAGE_SELECT: handle_stage_select_input(z_pressed, esc_pressed); break;
        case MenuState::DIFF_SELECT:  handle_diff_select_input(z_pressed, esc_pressed); break;
        case MenuState::SHOT_SELECT:  handle_shot_select_input(z_pressed, esc_pressed); break;
        case MenuState::OPTIONS:      handle_options_input(z_pressed, esc_pressed); break;
        case MenuState::REPLAY_LIST:  handle_replay_list_input(z_pressed, esc_pressed); break;
        case MenuState::PRACTICE_MENU: handle_practice_input(z_pressed, esc_pressed); break;
        case MenuState::QUIT_CONFIRM: handle_exit_input(z_pressed, esc_pressed); break;
        case MenuState::PAUSED:
            if (esc_pressed) transition_to(MenuState::INGAME_TITLE);
            handle_main_menu_input(z_pressed, false);
            break;
        default: break;
    }

    return true;
}

} // namespace th10
