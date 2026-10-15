// 0x0040CF00..0x0040CF08: stores the countdown limit at +0x3C and returns it.
struct TimedOwner {
    unsigned char unknown_00[0x3C];
    int countdown_limit;             // +0x3C

    int SetCountdownLimit(int value);
};

int TimedOwner::SetCountdownLimit(int value) {
    countdown_limit = value;
    return value;
}
