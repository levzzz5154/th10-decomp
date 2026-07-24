#pragma once

#include <cstdint>

// 0x0042CD50 - Allocate the 0x5ACC-byte progress manager, construct and
// publish it (0x0042C920), stop any current worker through the shared
// stop path (0x0044C150), and start the progress worker thread whose
// control block lives in the manager's tail words (retail word offsets:
// handle 0x16AD, thread id 0x16AE, stop request 0x16AF, running 0x16B0,
// entry point 0x16B2). The allocator, stop path, _beginthreadex edge,
// and the thread procedure (retail LAB_0042C9F0) are injected. Returns
// the manager, or null when the allocation fails (retail would continue
// into the thread start with a null manager; the readable form returns
// early). Host pointers stored into the 32-bit tail words keep the
// retail truncation semantics.
uint32_t* ProgressManager_CreateAndStartWorker(
    void* (*allocate)(uint32_t size),
    void (*stop_current)(uint32_t* manager),
    uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                              void* start, void* argument, unsigned flags,
                              uint32_t* thread_id),
    void* thread_proc);
