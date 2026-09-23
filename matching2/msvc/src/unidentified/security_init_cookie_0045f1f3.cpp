#include "asm_symbols.hpp"

namespace {

struct SecurityFileTime_0045F1F3 {
    unsigned int low;
    unsigned int high;
};

struct SecurityPerformanceCounter_0045F1F3 {
    unsigned int low;
    unsigned int high;
};

typedef void (__stdcall *GetSystemTimeAsFileTime_0045F1F3)(
    SecurityFileTime_0045F1F3* file_time);
typedef unsigned int (__stdcall *GetProcessId_0045F1F3)(void);
typedef unsigned int (__stdcall *GetThreadId_0045F1F3)(void);
typedef unsigned int (__stdcall *GetTickCount_0045F1F3)(void);
typedef int (__stdcall *QueryPerformanceCounter_0045F1F3)(
    SecurityPerformanceCounter_0045F1F3* counter);

template <typename FunctionPointer>
FunctionPointer import_at(unsigned char* slot) {
    return *reinterpret_cast<FunctionPointer*>(slot);
}

}  // namespace

// Visual Studio 2003 CRT __security_init_cookie.
// The import calls and xor inputs follow the order in the retail routine.
extern "C" __declspec(noinline) void __cdecl
asm_security_init_cookie_0045f1f3(void) {
    const unsigned int current_cookie = data_00473660;
    if (current_cookie != 0 && current_cookie != 0xBB40E64E) {
        return;
    }

    SecurityFileTime_0045F1F3 file_time = {0, 0};
    SecurityPerformanceCounter_0045F1F3 performance_counter = {0, 0};
    const GetSystemTimeAsFileTime_0045F1F3 get_system_time =
        import_at<GetSystemTimeAsFileTime_0045F1F3>(&data_004661b0);
    get_system_time(&file_time);

    unsigned int cookie = file_time.high ^ file_time.low;
    const GetProcessId_0045F1F3 get_process_id =
        import_at<GetProcessId_0045F1F3>(&data_004661b4);
    cookie ^= get_process_id();
    const GetThreadId_0045F1F3 get_thread_id =
        import_at<GetThreadId_0045F1F3>(&data_0046619c);
    cookie ^= get_thread_id();
    const GetTickCount_0045F1F3 get_tick_count =
        import_at<GetTickCount_0045F1F3>(&data_004660f0);
    cookie ^= get_tick_count();
    const QueryPerformanceCounter_0045F1F3 query_performance_counter =
        import_at<QueryPerformanceCounter_0045F1F3>(&data_004660fc);
    query_performance_counter(&performance_counter);
    cookie ^= performance_counter.high ^ performance_counter.low;

    data_00473660 = cookie;
    if (cookie == 0) {
        data_00473660 = 0xBB40E64E;
    }
}
