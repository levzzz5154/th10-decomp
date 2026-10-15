#pragma once


// 0x0044CF00 - scalar deleting destructor for the owned-array object: release
// the owned interfaces first, then free the object when the caller asks for it.
// The delete flag is the retail first stack argument, so the second __fastcall
// register argument (EDX) is unused.
