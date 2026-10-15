typedef void (__stdcall *RtlUnwindFn)(void*, void*, void*, void*);
extern "C" RtlUnwindFn imp_RtlUnwind;
extern "C" void __stdcall asm_RtlUnwind_0046263a(
    void* target_frame, void* target_ip, void* exception_record, void* return_value) {
    imp_RtlUnwind(target_frame, target_ip, exception_record, return_value);
}
