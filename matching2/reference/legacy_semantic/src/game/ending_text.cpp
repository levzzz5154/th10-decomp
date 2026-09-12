#include "th10/game/ending_text.hpp"
#include "th10/render/effect_ring_update.hpp"

#include <cmath>
#include <cstring>

namespace {

// Inlined timer initialization shared by the three embedded timers: install
// the frame-speed pointer with the 0xFFF0BDC1 (-999999) sentinel on first
// touch, then rewind to frame 0 with previous frame -1.
void InitEmbeddedTimer(EndingTimer* timer, const float* speed) {
	if ((timer->flags & 1u) == 0) {
		timer->current = 0;
		timer->previous = -999999;
		timer->elapsed = 0.0f;
		timer->speed = speed;
		timer->flags |= 1u;
	}
	timer->current = 0;
	timer->elapsed = 0.0f;
	timer->previous = -1;
}

} // namespace

// 0x0040BA90 - Construct the ending-text controller: zero the 0xEC-byte
// block, spin up five animation text VMs on scripts 0x42..0x46 (layer 15,
// anim flag 0x40000000), register them and keep their handles, remember the
// MSG script cursor, arm the three embedded frame timers at frame 0 with
// previous frame -1, set the active bit, and start with a white color.
// The SEH frame in the raw body is pure MSVC unwind bookkeeping for the
// inlined sub-object constructor at +0xD0; it has no semantic effect here.
EndingText* EndingText_Construct(EndingText* text,
                                        const unsigned char* script_cursor,
                                        const EndingTextEnv* env) {
	// The raw body clears all 0x3B dwords after the inlined sub-object
	// constructor runs; the surviving vtable value is the one re-written
	// here, so zero-then-install is the faithful net effect.
	std::memset(text, 0, sizeof(*text));
	text->on_deck_vtable = env->on_deck_vtable;

	for (int slot = 0; slot < 5; ++slot) {
		EndingAnimationVm* vm = env->allocate_vm(env->manager);
		vm->layer = 15;
		vm->anim_flags |= 0x40000000u;
		env->init_script(vm, 0x42 + slot);
		text->vm_handles[slot] = env->register_vm(vm, env->manager);

		// Three defensive handle re-resolves, matching the raw list walks
		// over the manager's two live lists. A failed walk zeroes the stored
		// handle; the raw body then stores its marker through the null
		// object, which can never execute because the VM was registered on
		// the line above, so the store is guarded here.
		EndingAnimationVm* found =
			env->find_vm(env->manager, text->vm_handles[slot]);
		if (found == 0) {
			text->vm_handles[slot] = 0;
		} else {
			found->marker_a = 0x10;
		}
		found = env->find_vm(env->manager, text->vm_handles[slot]);
		if (found == 0) {
			text->vm_handles[slot] = 0;
		} else {
			found->marker_b = 0x10;
		}
		found = env->find_vm(env->manager, text->vm_handles[slot]);
		if (found == 0) {
			text->vm_handles[slot] = 0;
		} else {
			found->state_flags |= 2u;
		}
	}

	text->script_cursor = script_cursor;
	InitEmbeddedTimer(&text->timer_a, env->frame_speed);
	InitEmbeddedTimer(&text->timer_b, env->frame_speed);
	InitEmbeddedTimer(&text->timer_c, env->frame_speed);
	text->flags |= 1u;
	text->color = 0x00FFFFFFu;
	return text;
}
