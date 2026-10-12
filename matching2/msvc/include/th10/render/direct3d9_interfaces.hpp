#ifndef TH10_RENDER_DIRECT3D9_INTERFACES_HPP
#define TH10_RENDER_DIRECT3D9_INTERFACES_HPP

// As much of the Direct3D 9 interfaces as start-up and the main loop call.
// The unnamed slots only keep the named ones at their vtable offsets.
struct Direct3DDisplayMode {
    unsigned int width, height, refresh_rate, format;
};
struct Direct3DPresentParameters {
    unsigned int back_buffer_width;         // +0x00
    unsigned int back_buffer_height;        // +0x04
    unsigned int back_buffer_format;        // +0x08
    unsigned int back_buffer_count;         // +0x0C
    unsigned int multi_sample_type;         // +0x10
    unsigned int multi_sample_quality;      // +0x14
    unsigned int swap_effect;               // +0x18: 1 discard, 3 copy
    void* device_window;                    // +0x1C
    int windowed;                           // +0x20
    int enable_auto_depth_stencil;          // +0x24
    unsigned int auto_depth_stencil_format; // +0x28
    unsigned int flags;                     // +0x2C: 1 = lockable back buffer
    unsigned int refresh_rate;              // +0x30: full screen only
    unsigned int presentation_interval;     // +0x34: 1 one, 0x80000000 immediate
};
struct Direct3DViewport {
    unsigned int x, y, width, height;
    float min_z, max_z;
};
struct Direct3DCaps {
    unsigned char reserved_000[0x58];
    unsigned int max_texture_width;         // +0x58
    unsigned char reserved_05c[0x90 - 0x5C];
    unsigned int texture_op_caps;           // +0x90: 0x40 = D3DTEXOPCAPS_ADD
    unsigned char reserved_094[0x130 - 0x94];
};
struct Direct3DMatrix { float m[4][4]; };
struct Direct3DVector { float x, y, z; };

struct ComObject {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

struct Direct3DDevice : ComObject {
    virtual long __stdcall TestCooperativeLevel() = 0;                     // +0x0C
    virtual void __stdcall Slot04() = 0;
    virtual void __stdcall Slot05() = 0;
    virtual void __stdcall Slot06() = 0;
    virtual long __stdcall GetDeviceCaps(Direct3DCaps* caps) = 0;          // +0x1C
    virtual void __stdcall Slot08() = 0;
    virtual void __stdcall Slot09() = 0;
    virtual void __stdcall Slot10() = 0;
    virtual void __stdcall Slot11() = 0;
    virtual void __stdcall Slot12() = 0;
    virtual void __stdcall Slot13() = 0;
    virtual void __stdcall Slot14() = 0;
    virtual void __stdcall Slot15() = 0;
    virtual long __stdcall Reset(Direct3DPresentParameters* parameters) = 0;   // +0x40
    virtual void __stdcall Slot17() = 0;
    virtual void __stdcall Slot18() = 0;
    virtual void __stdcall Slot19() = 0;
    virtual void __stdcall Slot20() = 0;
    virtual void __stdcall Slot21() = 0;
    virtual void __stdcall Slot22() = 0;
    virtual void __stdcall Slot23() = 0;
    virtual void __stdcall Slot24() = 0;
    virtual void __stdcall Slot25() = 0;
    virtual void __stdcall Slot26() = 0;
    virtual void __stdcall Slot27() = 0;
    virtual void __stdcall Slot28() = 0;
    virtual void __stdcall Slot29() = 0;
    virtual void __stdcall Slot30() = 0;
    virtual void __stdcall Slot31() = 0;
    virtual void __stdcall Slot32() = 0;
    virtual void __stdcall Slot33() = 0;
    virtual void __stdcall Slot34() = 0;
    virtual void __stdcall Slot35() = 0;
    virtual void __stdcall Slot36() = 0;
    virtual void __stdcall Slot37() = 0;
    virtual void __stdcall Slot38() = 0;
    virtual void __stdcall Slot39() = 0;
    virtual void __stdcall Slot40() = 0;
    virtual void __stdcall Slot41() = 0;
    virtual void __stdcall Slot42() = 0;
    virtual void __stdcall Slot43() = 0;
    virtual long __stdcall SetTransform(unsigned int state, const Direct3DMatrix* matrix) = 0;  // +0xB0
    virtual void __stdcall Slot45() = 0;
    virtual void __stdcall Slot46() = 0;
    virtual void __stdcall Slot47() = 0;
    virtual long __stdcall GetViewport(Direct3DViewport* viewport) = 0;    // +0xC0
};

struct Direct3D : ComObject {
    virtual void __stdcall Slot03() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual void __stdcall Slot05() = 0;
    virtual void __stdcall Slot06() = 0;
    virtual void __stdcall Slot07() = 0;
    virtual long __stdcall GetAdapterDisplayMode(unsigned int adapter,
                                                 Direct3DDisplayMode* mode) = 0;   // +0x20
    virtual void __stdcall Slot09() = 0;
    virtual long __stdcall CheckDeviceFormat(unsigned int adapter, unsigned int device_type,
        unsigned int adapter_format, unsigned int usage, unsigned int resource_type,
        unsigned int check_format) = 0;                                    // +0x28
    virtual void __stdcall Slot11() = 0;
    virtual void __stdcall Slot12() = 0;
    virtual void __stdcall Slot13() = 0;
    virtual void __stdcall Slot14() = 0;
    virtual void __stdcall Slot15() = 0;
    virtual long __stdcall CreateDevice(unsigned int adapter, unsigned int device_type,
        void* focus_window, unsigned int behavior, Direct3DPresentParameters* parameters,
        Direct3DDevice** device) = 0;                                      // +0x40
};
#endif
