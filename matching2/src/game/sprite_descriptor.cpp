#include "th10/game/sprite_descriptor.hpp"
#include "th10/game/result_menu_open.hpp"
#include "th10/render/projection_quads.hpp"

#include <cmath>
#include <cstring>

namespace {
}

// 0x00424480 - resolves the sprite resource, converts its four float metadata
// fields in retail order, and fills an unused descriptor slot.
int WindowDescriptor_Configure(MenuWindowDescriptor* descriptor, int handle,
                               int x, int y, int width, unsigned int flags,
                               MenuWindowEnv* env) {
	SpriteNode* node = env->resolve(handle);
	int value_30 = env->float_to_long(node->resource->field_30);
	int value_34 = env->float_to_long(node->resource->field_34);
	int value_0c = env->float_to_long(node->resource->field_0c);
	int value_08 = env->float_to_long(node->resource->field_08);
	if (descriptor->sprite_handle >= 0) return -1;
	descriptor->sprite_handle = node->first_vm_handle;
	descriptor->x = x; descriptor->y = y; descriptor->width = width;
	descriptor->flags = flags;
	descriptor->resource_08 = value_08;
	descriptor->resource_0c = value_0c;
	descriptor->resource_34 = value_34;
	descriptor->resource_30 = value_30;
	descriptor->trailing = 0;
	return 0;
}

namespace {
}
