#pragma once

#pragma code_seg()

// 0x00420B10: start `track` and remember that `heard_index` has been played
// (for the music room). The progress pointer is loaded before the index
// only when the link sees a direct caller, which the cluster context supplies.
#pragma code_seg(".text$00c1play")
