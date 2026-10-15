#pragma once


// 0x00435580 - Read the whole file into a fresh heap block when the file is
// no larger than the caller's capacity. Read starts at the current position;
// a nonzero read is success and attempts to restore that position. A zero
// read frees the block, but an initial failed Seek returns without freeing it.
// Retail comparisons: reference/recovery_notes/resource_loose_file_integration.md.
