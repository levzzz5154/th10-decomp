// 0x00436570: start a program in an 80x25 console window and, when asked,
// wait for it and return its exit code.
struct StartupInfo {
    unsigned long size;
    char* reserved;
    char* desktop;
    char* title;
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
    unsigned long columns;
    unsigned long rows;
    unsigned long fill_attribute;
    unsigned long flags;
    unsigned short show_window;
    unsigned short reserved2_size;
    unsigned char* reserved2;
    void* standard_input;
    void* standard_output;
    void* standard_error;
};
struct ProcessInformation {
    void* process;
    void* thread;
    unsigned long process_id;
    unsigned long thread_id;
};
extern "C" __declspec(dllimport) int __stdcall CreateProcessA(const char* application, char* command_line, void* process_attributes, void* thread_attributes, int inherit_handles, unsigned long flags, void* environment, const char* directory, StartupInfo* startup, ProcessInformation* information);
extern "C" __declspec(dllimport) int __stdcall GetExitCodeProcess(void* process, unsigned long* exit_code);

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall LaunchProcess(char* command_line, const char* application, int wait) {
    StartupInfo startup;
    ProcessInformation information;
    startup.size = sizeof(startup);
    startup.reserved = 0;
    startup.desktop = 0;
    startup.title = 0;
    startup.x = 0x80000000;
    startup.y = 0x80000000;
    startup.width = 0x80000000;
    startup.height = 0x80000000;
    startup.columns = 80;
    startup.rows = 25;
    startup.fill_attribute = 0;
    startup.flags = 0;
    startup.show_window = 10;
    startup.reserved2_size = 0;
    startup.reserved2 = 0;
    startup.standard_input = 0;
    startup.standard_output = 0;
    startup.standard_error = 0;
    if (!CreateProcessA(application, command_line, 0, 0, 0, 0x20, 0, 0, &startup, &information)) return -1;
    if (wait) {
        unsigned long exit_code = 0x103;
        while (exit_code == 0x103) GetExitCodeProcess(information.process, &exit_code);
        return exit_code;
    }
    return 0;
}
#pragma code_seg()
