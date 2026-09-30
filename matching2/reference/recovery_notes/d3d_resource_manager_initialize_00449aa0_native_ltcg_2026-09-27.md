# D3D resource manager initializer, 0x00449AA0

Date: 2026-09-27. Extent: 59 bytes.

The complete typed C++ `D3DResourceManager_00449AA0::Initialize` contribution is byte-exact in a native MSVC 7.1 `/GL` + `/LTCG` cluster. Its private entry receives the manager in EAX and ends with plain RET. The synthetic array-walking compiler context is never selected as recovered game code.

Fresh Ghidra MCP decompilation agrees with the field operations: two embedded 0x24-byte resource lists, at offsets 0 and 0x24. Each initializer clears reserved and pending fields, clears bit 0 of flags, points the list owner to itself, and clears the first/last pointers. Field +0x20 remains untouched.

The plain typed source first emitted 69 bytes because MSVC moved both flag masks ahead of the zero stores, shared the mask, and spilled ESI. Loading primary flags into a local and placing `_ReadWriteBarrier` after the primary reserved store keeps the first mask after that zero group. A typed pointer to the secondary list, declared after the primary flag assignment, plus another `_ReadWriteBarrier` after the primary last store preserves the two list phases. Both intrinsics emit no instruction bytes. This produces the exact first flag load in ECX, zero in EDX, and secondary-list address in ECX, including the retail in-place second flag mask.

Verified artifact: `matching2/build/experiments/d3d_list_initialize/final.json`; native report under its `final/clusters/d3d_list_initialize_00449aa0/` directory. The fixed-address function has its full declared 59-byte contribution, zero differing bytes, zero masked bytes, zero instruction rewrites, and zero address operand rewrites. The source contains no inline assembly, naked function, or encoded instructions.

This supersedes the scheduling blocker for this initializer in the 2026-09-12 `d3d_resource_reset_cluster_00438880_00449e50.md` attempt. Related release/reset functions remain independent work.
