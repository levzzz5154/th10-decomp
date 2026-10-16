// 0x004267F0..0x004269C7: Player::CheckLaserHit, the player against a laser.
//
// The player's position is taken relative to the rectangle's origin and
// rotated by -angle, so that the rectangle runs along +x. With the object's
// hitbox half size added on both sides:
//   * inside [0, length] along the rectangle and within half a width of the
//     centre line: the player is hit (unless a dialogue is running, the
//     player is already dying or respawning, or is invulnerable) -> 1;
//   * otherwise inside [0, length] and within 1.5 widths of the centre line
//     -> 2, a graze;
//   * otherwise -> 0.
//
// The player arrives in ECX and the origin in EAX.
//
// `lower` first holds the unrotated offset and is then reused for the lower
// corner; the rotation is written back into `rotated`. That sharing is what
// orders the two vectors in the frame (the compiler sorts stack slots by
// reference count).
#include "th10/game/trigger_region.hpp"

#pragma code_seg(".text$30classifier")
int Player::CheckLaserHit(const Point3_OrientedRect* origin, float angle, float width, float length) {
    Point3_OrientedRect rotated = reinterpret_cast<const Point3_OrientedRect&>(position) - *origin;
    Point3_OrientedRect lower = rotated;
    OrientedRectSine sine(-angle);
    rotated.x = lower.x * cos(-angle) - sine * lower.y;
    rotated.y = sine * lower.x + cos(-angle) * lower.y;

    const Point3_OrientedRect& half_size = reinterpret_cast<const Point3_OrientedRect&>(hitbox_half_size);
    lower = rotated - half_size;
    Point3_OrientedRect upper;
    upper = rotated + half_size;

    // Negated rejection tests, so that an unordered comparison does not
    // reject by itself.
    if (!(lower.x > length) && !(width * 0.5f < lower.y) && !(upper.x < 0.0f) && !(width * -0.5f > upper.y)) {
        if (g_front != 0 && g_front->active != 0)
            return 0;
        if (state == PLAYER_DYING || state == PLAYER_HIT || state == PLAYER_STATE_3)
            return 0;
        if (invulnerability_timer.current > 0)
            return 0;
        Player_Hit(this);
        return 1;
    }
    if (!(lower.x > length) && !(upper.x < 0.0f) && !(width * 1.5f < lower.y) && !(width * -1.5f > lower.y))
        return 2;
    return 0;
}
#pragma code_seg()
