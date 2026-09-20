
// A joystick slot owns an interface whose Release method is the vtable entry
// at +8.  The native-LTCG context keeps this receiver in ESI, matching the
// private retail calling convention at 0x0044C770.
struct JoystickInterface_0044c770 {
    struct Vtable {
        void* query_interface;
        void* add_reference;
        void (__stdcall *release)(JoystickInterface_0044c770*);
    };
    Vtable* vtable;
};

struct JoystickSlot_0044c770 {
    JoystickInterface_0044c770* interface_pointer;

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01release")
void JoystickSlot_0044c770::Release() {
    JoystickInterface_0044c770* interface_pointer = this->interface_pointer;
    if (interface_pointer != 0) {
        interface_pointer->vtable->release(interface_pointer);
        this->interface_pointer = 0;
    }
}
#pragma code_seg()
