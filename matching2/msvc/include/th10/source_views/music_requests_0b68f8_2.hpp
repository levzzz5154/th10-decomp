#pragma once

#pragma code_seg()

// 0x00420B80: play the .wav rendition of `file_name` directly, without a
// preloaded slot, and remember that `heard_index` has been played. Retail
// keeps this copy without a remaining caller; the index arrives in ESI.
#pragma code_seg(".text$00c5playfile")
