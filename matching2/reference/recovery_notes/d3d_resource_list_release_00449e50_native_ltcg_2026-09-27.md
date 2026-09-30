# D3D resource list release, 0x00449E50

All 82 bytes are recovered as typed C++, without inline assembly or instruction
transformation. The normal probe reports zero differing bytes and no
relocations. This supersedes the stack/EAX ABI blocker in the former maintained
source and the older D3D resource reset cluster note.

Fresh Ghidra MCP analysis confirms the private receiver in EAX, scheduler owner
on the stack, and RET 4. The function walks the list at +0x18, preserving each
successor before removing the resource through the existing readable
`Scheduler_Remove`. Removal happens inside the shared critical section; the
scheduler lock depth increases and decreases around it.

The source uses the maintained scheduler and thread-synchronization types.
Explicit local function pointers preserve the retail cached lock imports in
EBX/EBP. Keeping the current node and saved successor separate allows the
compiler to reproduce the EAX/EDI traversal and shrink-wrapped saved registers.
The one-word owner aggregate has a volatile pointer field because the retail
body reloads that stack argument on every locked iteration. This also leaves
both saved registers available for the import pointers.

The native compiler context traverses an array of list pointers and is never
selected as recovered game code. No compiler barriers are required: removing
the experimental `_ReadWriteBarrier` preserves the exact contribution.

Final scratch evidence is under
`matching2/build/experiments/d3d_list_release_root/`; `attempt05.json` proves the
barrier-free body. Promotion re-probes the final commented source. The earlier
`d3d_list_release/` directory contains an incomplete initial experiment and is
not an integration source.

Whole-executable validation is recorded in the current recovery checkpoint.
