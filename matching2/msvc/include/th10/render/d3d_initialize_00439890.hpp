#ifndef TH10_RENDER_D3D_INITIALIZE_00439890_HPP
#define TH10_RENDER_D3D_INITIALIZE_00439890_HPP

// The present-parameters block the mode enumeration fills and the
// CreateDevice retry loop consumes (0x38 bytes at [esp+0x38] in retail).
struct PresentParameters_00439890 {
    unsigned int back_buffer_width;      // +0x00
    unsigned int back_buffer_height;     // +0x04
    unsigned int back_buffer_format;     // +0x08
    unsigned int back_buffer_count;      // +0x0C
    unsigned int multisample;            // +0x10
    unsigned int multisample_quality;    // +0x14
    unsigned int swap_effect;            // +0x18
    void* device_window;                 // +0x1C
    int windowed;                        // +0x20
    int enable_auto_depth_stencil;       // +0x24
    unsigned int auto_depth_format;      // +0x28
    unsigned int flags;                  // +0x2C
    unsigned int refresh_rate;           // +0x30
    unsigned int presentation_interval;  // +0x34
};
typedef char PresentParametersSize_00439890[sizeof(PresentParameters_00439890) == 0x38 ? 1 : -1];

// 0x00439890: create the Direct3D device, the view/projection transforms
// and the render state. Nonzero when the device could not be created.
__declspec(noinline) int __stdcall D3DInitialize_00439890();
#endif
