#pragma once


// 0x0044D710 - scalar deleting destructor for the sound-buffer object: restore
// the derived table through its base destructor, then free the object on
// request. The delete flag is the retail first stack argument, so the second
// __fastcall register argument (EDX) is unused.
