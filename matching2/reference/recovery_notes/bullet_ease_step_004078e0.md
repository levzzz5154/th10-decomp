# 0x004078E0 bullet ease step

`BulletRuntimeDeceleration::EaseStep`, 335 bytes, promoted from the anchor
model in `bullet_runtime_caller`.

The earlier model needed `_ReadWriteBarrier` to pin the reset block. The
natural form matches once the statements follow retail's schedule:

    angle = angle_step;
    float reset_speed = next_speed;
    speed = reset_speed;
    unsigned int initial_flags = timer_flags;
    magnitude = reset_speed;

Assigning `magnitude` before the flags are read moves the `fstp` ahead of the
flag load; a chained `magnitude = speed = next_speed` places the heading store
one instruction early.
