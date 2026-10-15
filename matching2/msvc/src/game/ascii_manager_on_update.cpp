// 0x004014F0: the ASCII manager's update task. It empties both string queues
// (the frame's code fills them again before the draw tasks run), counts the
// update and reports success.
#include "th10/game/ascii_manager.hpp"

int AsciiManager::OnUpdate() {
    record_count = 0;
    late_record_count = 0;
    ++update_count;
    return 1;
}
