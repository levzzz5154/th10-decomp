#include "th10/render/anm_vm_draw_dispatch.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// Anchored extent helper for the rotated-quad path of 0x004451C0: mode 0
// centers the extent, mode 1 anchors at the near edge, mode 2 at the far
// edge.
void ComputeAnchoredExtents(Word mode, float extent, float low,
                            float high, float* near_edge, float* far_edge) {
	if (mode == 0) {
		*near_edge = low * extent;
		*far_edge = high * extent;
	} else if (mode == 1) {
		*near_edge = 0.0f;
		*far_edge = extent;
	} else {
		*near_edge = -extent;
		*far_edge = 0.0f;
	}
}

// Rotated-quad corner fill shared by draw modes 1 and 3 of 0x004451C0.
void ComputeRotatedQuad(const AnmDrawVm* vm, AnmDrawEnv* env) {
	float cos_r = cosf(vm->rotation);
	float sin_r = sinf(vm->rotation);
	float width = vm->size_x * vm->scale_x;
	float height = vm->size_y * vm->scale_y;
	float x_near, x_far, y_near, y_far;
	ComputeAnchoredExtents((vm->flags >> 0x12) & 3, width, env->anchor_low,
	                       env->anchor_high, &x_near, &x_far);
	ComputeAnchoredExtents((vm->flags >> 0x14) & 3, height, env->anchor_low,
	                       env->anchor_high, &y_near, &y_far);
	const float xs[4] = {x_near, x_far, x_near, x_far};
	const float ys[4] = {y_near, y_near, y_far, y_far};
	for (int i = 0; i < 4; ++i) {
		env->quad->corners[i][0] = xs[i] * cos_r - ys[i] * sin_r + vm->origin_x;
		env->quad->corners[i][1] = xs[i] * sin_r + ys[i] * cos_r + vm->origin_y;
		env->quad->corners[i][2] = vm->origin_z;
	}
}

// 0x004451C0 - ANM VM draw dispatch: bails out unless the VM is alive,
// enabled, and visible, then routes to the draw handler selected by the
// mode bits; modes 1 and 3 rasterize a rotated quad through the shared
// corner buffer, falling back to the unrotated path at zero rotation.
int AnmVm_DrawDispatch(AnmDrawVm* vm, void* context, AnmDrawEnv* env) {
	if ((vm->flags & 1) == 0 || (vm->flags & 2) == 0 || vm->visible == 0) {
		return -1;
	}
	switch ((vm->flags >> 0x16) & 0xF) {
	case 0:
		return env->draw_standard(context);
	case 1:
	case 3:
		if (vm->rotation == 0.0f) return env->draw_unrotated(context);
		ComputeRotatedQuad(vm, env);
		return env->draw_corner_quad(context, 0);
	case 2:
		return env->draw_unrotated(context);
	case 4:
		return env->draw_mode4(context);
	case 5:
		return env->draw_mode5(context);
	case 6:
		return env->draw_mode6(context);
	case 7:
		return env->draw_mode7(context, vm);
	case 8:
		return env->draw_mode8(context);
	case 9:
		return env->draw_mode9(context);
	default:
		return 0;
	}
}
