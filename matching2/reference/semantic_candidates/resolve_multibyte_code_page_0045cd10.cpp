// Resolve the special code-page values used by the multibyte CRT.
// Retail 0x0045CD10..0x0045CD55 receives the requested page in EAX.
extern "C" unsigned int (__stdcall *data_00466048)(); // GetOEMCP import
extern "C" unsigned int (__stdcall *data_0046604c)(); // GetACP import
extern "C" unsigned int data_00477664; // current multibyte code page
extern "C" unsigned int data_00477690; // special-page request flag

extern "C" unsigned int __cdecl ResolveMultibyteCodePage_0045cd10(
    int requested_page) {
    data_00477690 = 0;
    if (requested_page == -2) {
        data_00477690 = 1;
        return data_00466048();
    }
    if (requested_page == -3) {
        data_00477690 = 1;
        return data_0046604c();
    }
    if (requested_page == -4) {
        data_00477690 = 1;
        return data_00477664;
    }
    return static_cast<unsigned int>(requested_page);
}
