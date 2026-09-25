// 0x004598BC..0x004598DD: handler installed by __local_unwind2.
struct LocalUnwindExceptionRecord_004598bc {
    unsigned int code;
    unsigned int flags;
};

// The context record is part of the SEH handler ABI but is unused here.
extern "C" int __cdecl LocalUnwindExceptionHandler_004598bc(
    const LocalUnwindExceptionRecord_004598bc* exception,
    void* establisher_frame,
    void* context_record,
    void** dispatcher_context) {
    const unsigned int unwind_flags = 0x02u | 0x04u;
    if ((exception->flags & unwind_flags) != 0) {
        *dispatcher_context = establisher_frame;
        return 3; // ExceptionCollidedUnwind
    }
    return 1; // ExceptionContinueSearch
}
