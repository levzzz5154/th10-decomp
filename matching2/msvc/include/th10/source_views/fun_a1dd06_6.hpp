#pragma once

#pragma code_seg()

// 0x0044C150: stop and join the worker thread.  The object stays live across
// the wait/sleep/close calls, the shape that earns it the ESI argument in
// retail.  The Win32 calls are opaque here - only the argument shape is
// modelled.
#pragma code_seg(".text$09bucketzf44c150")
