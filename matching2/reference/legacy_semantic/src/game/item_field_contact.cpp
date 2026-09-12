#include "th10/game/item_field_contact.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x004266B0 - item vs. collection-field contact test: returns 2 while the
// item is outside the inner field but within the keep-alive margin, 1 when
// it is inside the field (triggering a full auto-collect if no dialogue is
// active, the field mode allows it, and the timer has elapsed), else 0.
int Item_TestFieldContact(const float* position, const float* size,
                          ItemField* field, ItemFieldEnv* env) {
	float half_w = size[0] * env->half_scale;
	float half_h = size[1] * env->half_scale;
	int outside = position[0] + half_w < field->min_x ||
	              position[1] + half_h < field->min_y ||
	              field->max_x < position[0] - half_w ||
	              field->max_y < position[1] - half_h;
	if (outside != 0) {
		if (field->min_x <= position[0] + env->margin &&
		    field->min_y <= position[1] + env->margin &&
		    position[0] - env->margin <= field->max_x &&
		    position[1] - env->margin <= field->max_y) {
			return 2;
		}
	} else if ((env->dialogue_active == 0 || *env->dialogue_active == 0) &&
	           field->mode != 2 && field->mode != 4 && field->mode != 3) {
		if (field->autocollect_timer < 1) env->collect_all(field);
		return 1;
	}
	return 0;
}
