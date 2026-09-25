extern "C" unsigned long __readfsdword(unsigned long offset);
#pragma intrinsic(__readfsdword)

// Existing assembly callers use the former naked entry name.
#pragma comment(linker, "/alternatename:_asm_abnormal_termination_00459946=_AbnormalTermination_00459946")

struct AbnormalTerminationRegistration_00459946 {
    AbnormalTerminationRegistration_00459946* next; // +0x00
    void* handler;                                  // +0x04
    int state;                                      // +0x08
    const unsigned char* scope_data;                // +0x0C
};

struct AbnormalTerminationScopeData_00459946 {
    unsigned long reserved_000[3];
    int state;                                      // +0x0C
};

typedef char AbnormalTerminationRegistration_size_must_be_16_bytes[
    sizeof(AbnormalTerminationRegistration_00459946) == 0x10 ? 1 : -1];

// Ghidra shows this test in the sole caller's C++ EH path. The active x86
// registration record qualifies only when its handler and scope state match.
extern "C" int __cdecl AbnormalTermination_00459946(void) {
    int abnormal = 0;
    const AbnormalTerminationRegistration_00459946* const registration =
        reinterpret_cast<const AbnormalTerminationRegistration_00459946*>(
            __readfsdword(0));

    if (registration->handler == reinterpret_cast<void*>(0x004598BC)) {
        const AbnormalTerminationScopeData_00459946* const scope_data =
            reinterpret_cast<const AbnormalTerminationScopeData_00459946*>(
                registration->scope_data);
        if (registration->state == scope_data->state)
            abnormal = 1;
    }
    return abnormal;
}
