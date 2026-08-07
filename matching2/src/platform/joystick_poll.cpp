#include "th10/platform/joystick_poll.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {

// The two joystick entry points share the retail acquisition sequence. In
// particular, a successful reacquire does not fall through to GetDeviceState
// in either retail function; the current frame remains all-zero.
bool ReadDirectInputState(
        void* device, int (*poll)(void*), int (*acquire)(void*),
        int (*get_state)(void*, DirectInputState*), DirectInputState* out) {
	if (poll(device) >= 0)
		return get_state(device, out) >= 0;

	int attempts = 0;
	int result = acquire(device);
	if (result != kDInputInputLost)
		return false;
	for (;;) {
		result = acquire(device);
		attempts += 1;
		if (attempts > 399)
			return false;
		if (result != kDInputInputLost)
			return false;
	}
}

} // namespace

// 0x0044A190 - merges one joystick's state into the packed input word. The
// winmm path polls joyGetPosEx, maps the five configured buttons through
// their bit masks, and derives the four direction bits from the calibrated
// axis center with a quarter-range dead zone. The DirectInput path polls the
// device (re-acquiring up to 400 times on DIERR_INPUTLOST), reads the
// device state, maps the same five buttons from rgbButtons bit 7, and
// compares lX/lY against the global thresholds.
Half Joystick_Poll(Half state, int config_index, int pad,
                          JoyPollEnv* env) {
	const PadButtons* config = &env->configs[config_index];

	if (!env->use_direct_input) {
		WinmmState info = {0, 0, 0};
		if (env->get_position(pad != 0 ? 1 : 0, &info) != 0) {
			return state;
		}
		if (config->shoot >= 0 &&
		    ((1u << (config->shoot & 0x1F)) & info.buttons) != 0) {
			state |= kPadShoot;
		}
		if (config->bomb >= 0 &&
		    ((1u << (config->bomb & 0x1F)) & info.buttons) != 0) {
			state |= kPadBomb;
		}
		if (config->pause >= 0 &&
		    ((1u << (config->pause & 0x1F)) & info.buttons) != 0) {
			state |= kPadPause;
		}
		if (config->focus >= 0 &&
		    ((1u << (config->focus & 0x1F)) & info.buttons) != 0) {
			state |= kPadFocus;
		}
		if (config->skip >= 0 &&
		    ((1u << (config->skip & 0x1F)) & info.buttons) != 0) {
			state |= kPadSkip;
		}
		const JoyCalibration* cal = &env->calibrations[pad];
		Word quarter_x = (Word)(cal->x_max - cal->x_min) >> 2;
		Word quarter_y = (Word)(cal->y_max - cal->y_min) >> 2;
		Word center_x = (Word)(cal->x_min + cal->x_max) >> 1;
		Word center_y = (Word)(cal->y_min + cal->y_max) >> 1;
		if (info.y < center_y - quarter_y) {
			state |= kPadUp;
		}
		if (center_y + quarter_y < info.y) {
			state |= kPadDown;
		}
		if (center_x + quarter_x < info.x) {
			state |= kPadRight;
		}
		if (info.x < center_x - quarter_x) {
			state |= kPadLeft;
		}
		return state;
	}

	void* device = env->devices[pad];
	DirectInputState di = {};
	if (!ReadDirectInputState(device, env->poll, env->acquire,
	                          env->get_state, &di)) {
		return state;
	}
	if (config->shoot >= 0) { // kPadShoot
		state |= (Half)(di.buttons[config->shoot] >> 7);
	}
	if (config->bomb >= 0) { // kPadBomb
		state |= (Half)((di.buttons[config->bomb] >> 6) & 2);
	}
	if (config->pause >= 0) { // kPadPause
		state |= (Half)((di.buttons[config->pause] >> 4) & 8);
	}
	if (config->focus >= 0) { // kPadFocus
		state |= (Half)((di.buttons[config->focus] >> 5) & 4);
	}
	if (config->skip >= 0) { // kPadSkip
		state |= (Half)((di.buttons[config->skip] & 0x80) << 1);
	}
	if (di.x < -(int)env->threshold_x) {
		state |= kPadLeft;
	}
	if (di.y < -(int)env->threshold_y) {
		state |= kPadUp;
	}
	if (env->threshold_x < di.x) {
		state |= kPadRight;
	}
	if (env->threshold_y < di.y) {
		state |= kPadDown;
	}
	return state;
}

// 0x0044A4E0 - clears the 32-byte button buffer, then reads either the WinMM
// button word or the DirectInput rgbButtons array. This is the portable
// semantic counterpart used by standalone key configuration; platform
// adapters supply the same callbacks as Joystick_Poll's testable backend.
bool Joystick_PollButtonBytes(unsigned char* destination, int pad,
                              const JoystickButtonPollEnv* env) {
	if (destination == nullptr)
		return false;
	std::memset(destination, 0, 32);
	if (env == nullptr)
		return false;

	if (!env->use_direct_input) {
		if (env->get_position == nullptr)
			return false;
		WinmmState info = {0, 0, 0};
		// 0x0044A4E0's WinMM branch always asks for joystick 0. The pad
		// parameter is only used by the DirectInput device table.
		if (env->get_position(0, &info) != 0)
			return false;
		for (unsigned int index = 0; index != 32; ++index) {
			if ((info.buttons & (1u << index)) != 0)
				destination[index] = 0x80;
		}
		return true;
	}

	if (env->devices == nullptr || env->poll == nullptr ||
	    env->acquire == nullptr || env->get_state == nullptr)
		return false;
	DirectInputState state = {};
	void* device = env->devices[pad];
	if (!ReadDirectInputState(device, env->poll, env->acquire,
	                          env->get_state, &state))
		return false;
	// Retail copies rgbButtons byte-for-byte, rather than normalizing to 0x80.
	std::memcpy(destination, state.buttons, 32);
	return true;
}
