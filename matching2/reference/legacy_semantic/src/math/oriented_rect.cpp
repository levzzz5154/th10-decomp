#include "th10/math/oriented_rect.hpp"

#include <cmath>

// 0x0041E4D0 - transforms the circle center into rectangle-local space and
// performs the retail expanded-axis overlap test. Width and height are stored
// as full extents, so the comparison uses half extents.
int OrientedRect_IntersectsCircle(const OrientedRect* rect,
                                  const OrientedRectVec2* circle_center,
                                  float radius) {
	const float dx = circle_center->x - rect->center.x;
	const float dy = circle_center->y - rect->center.y;
	const float sine = std::sin(-rect->angle);
	const float cosine = std::cos(-rect->angle);
	const float local_x = dx * cosine - sine * dy;
	const float local_y = sine * dx + cosine * dy;
	if (local_x - radius <= rect->width * 0.5f &&
	    local_y - radius <= rect->height * 0.5f &&
	    0.0f <= local_x + radius &&
	    rect->height * -0.5f <= local_y + radius) {
		return 2;
	}
	return 0;
}
