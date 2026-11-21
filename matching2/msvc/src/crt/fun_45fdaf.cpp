extern "C" void __cdecl crt_amsg_exit(int value);

// Exit after CRT message 2.
extern "C" void __cdecl crt_helper_45fdaf() {
    crt_amsg_exit(2);
}
