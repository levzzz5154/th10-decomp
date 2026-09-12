#include "th10/game/title_assets.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x0041F990 - title screen core asset load: opens sig.anm and text.anm,
// creates the title task, loads the score file, initializes the common
// sound buffers, starts the BGM stream (or selects midi playback), and
// enters the title menu. Any missing core asset sets the failure state.
int TitleScreen_LoadCoreAssets(TitleScreen* title, TitleEnv* env) {
	title->signature_anm = env->open_anm(1, env->archive_manager, "sig.anm");
	if (title->signature_anm != 0) {
		*title->update_flags |= 2;
		title->signature_ready = 1;
		void* task = env->create_title_task();
		if (task == 0) {
			env->report_error(env->error_sink, env->task_error_text);
		} else {
			title->interface_ready = 1;
			*env->interface_anm_slot =
			    env->open_anm(0, env->archive_manager, "text.anm");
			if (*env->interface_anm_slot != 0) {
				*env->score_data_slot = env->load_score_file(0, 0);
				if (*env->score_data_slot == 0) {
					env->report_error(env->error_sink, env->score_error_text);
				}
				env->init_sound_buffers();
				if (env->archive_has_file("thbgm.dat") != 0) {
					if ((env->config_flags & 0x10) == 0) {
						env->start_music_stream("thbgm.dat");
					} else {
						env->select_midi_playback();
					}
				}
				env->load_score_table();
				*title->draw_flags |= 2;
				env->enter_title_menu();
				return 0;
			}
		}
	}
	*env->failure_state = 3;
	*title->draw_flags |= 2;
	return 0;
}
