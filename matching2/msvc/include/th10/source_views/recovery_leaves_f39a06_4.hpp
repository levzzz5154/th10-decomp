#pragma once


// 0x004203F0..0x0042046F: Recovery_ReleaseGlobalStates
// Tear down every global state object the engine allocated for the running
// session: manager state, script state, resource state, the small state and the
// pending block. Each object is destroyed through its own release routine and
// then handed back to the CRT heap. The globals keep their stale values, just
// as the retail code leaves them.
typedef void (__stdcall* GlobalStateDestroyFn)(void*);

