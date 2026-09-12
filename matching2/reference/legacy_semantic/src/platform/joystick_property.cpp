#include "th10/platform/joystick_property.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x0044C7E0 - sets a DirectInput device property from a packed axis range.
// The retail decompile is corrupted (the property block doubles as a fake
// vtable); this is a semantic reconstruction of the conventional-abi form.
int Input_SetJoystickProperty(Half range, short scale,
                              JoyPropertyEnv* env) {
	void* device = *env->device_slot;
	if (device == 0) {
		return (int)0x800401F0u; // retail: -0x7ffbfe10
	}
	int result = env->prepare_device(device);
	if (result < 0) {
		return result;
	}
	JoyPropertyBlock block;
	block.size = 0x24;
	block.header_size = 1;
	block.object = 0;
	block.how = 0;
	block.value = ((Word)range << 16) |
	              (Half)((range >> 3) * scale);
	result = env->set_property(device, &block);
	return result < 0 ? result : 0;
}
