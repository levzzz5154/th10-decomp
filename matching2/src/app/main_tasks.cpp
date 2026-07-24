// =============================================================================
// main_tasks.cpp - Main-task registration/shutdown, config load, screenshots
// =============================================================================
#include "th10/app/main_tasks.hpp"

// Semantic reconstruction 0x00420470 - prime and register the main tasks.
// the four root callbacks (input poll on the primary list, three helpers on
// the secondary list). Returns the primary-list insertion status.
int MainTasks_Register(MainTaskState* state, const MainTaskHooks* hooks) {
    state->stage_counter = -2;      // _DAT_00491FB4 = 0xFFFFFFFE
    state->mode = 0;                // DAT_00491FB8
    state->transition_pending = 0;  // _DAT_00491FC0

    void* input_node = hooks->create_node(hooks->context, 0); // 0x0041FF80
    int status = hooks->register_primary(hooks->context, input_node);
    if (status != 0)
        return status;
    for (int callback_index = 1; callback_index <= 3; ++callback_index) {
        void* node = hooks->create_node(hooks->context, callback_index);
        hooks->register_secondary(hooks->context, node);
    }
    return 0;
}

// Semantic reconstruction 0x00420270 - tear down root task state in retail
// order. Sets the sound-worker stop flag between the two frame markers.
int MainTasks_Shutdown(int* sound_worker_stop,
                       const MainTaskShutdownHooks* hooks) {
    hooks->log_frame_marker(hooks->context);
    *sound_worker_stop = 2; // DAT_004977B4
    hooks->log_frame_marker(hooks->context);
    hooks->release_tracked_block(hooks->context);
    hooks->release_input_bindings(hooks->context);
    hooks->release_text_objects(hooks->context);
    hooks->release_manager_texture(hooks->context);
    hooks->queue_dummy_sound(hooks->context);
    hooks->release_font_cache(hooks->context);
    hooks->release_device_surfaces(hooks->context);
    hooks->kill_config_timer(hooks->context);
    hooks->release_dinput(hooks->context);
    return 0;
}

namespace {

bool ConfigImageIsValid(const GameConfig* config) {
    return config->magic == 0x100003u &&
           config->difficulty < 2 && config->bgm_mode < 3 &&
           config->sfx_mode < 2 && config->windowed < 2 &&
           config->skip_limit < 3 && config->slow_mode < 3;
}

} // namespace

// Semantic reconstruction 0x00420870 - load and validate th10.cfg,
// fall back to defaults on any mismatch, then write the image back. Returns
// -1 when the write-back fails (retail aborts the boot in that case).
int Config_LoadAndValidate(GameConfig* config, const char* file_name,
                           unsigned int* runtime_flags,
                           const ConfigLoadHooks* hooks) {
    hooks->apply_defaults(hooks->context, config);

    unsigned int size = 0;
    void* image = hooks->load_file(hooks->context, file_name, &size);
    if (image != 0) {
        // Copy the 0xD dwords of the on-disk image over the defaults.
        const unsigned char* bytes = static_cast<const unsigned char*>(image);
        unsigned char* out = reinterpret_cast<unsigned char*>(config);
        for (unsigned int index = 0; index < 0x34u && index < size; ++index)
            out[index] = bytes[index];
        hooks->release(hooks->context, image);

        if (size != 0x34u || !ConfigImageIsValid(config)) {
            hooks->log_invalid(hooks->context);
            hooks->apply_defaults(hooks->context, config);
        }
    }

    // Runtime flag echo: retail logs each debug bit (0x04/0x01/0x02/0x08/
    // 0x10/0x20/0x40) it finds in the loaded flag byte.
    if (runtime_flags != 0)
        hooks->log_flag_bits(hooks->context, *runtime_flags);

    if (hooks->write_file(hooks->context, file_name, config) != 0) {
        hooks->log_write_failure(hooks->context);
        return -1;
    }
    return 0;
}

// 0x00420670 - Screenshot_CaptureBmp: copy the 640x480 back buffer into a
// bottom-up 24-bit BMP image and hand it to the writer thread. Returns 1 on
// success, 0 when the surface format is not the XRGB path retail supports.
int Screenshot_CaptureBmp(const char* file_name, int surface_format,
                          const ScreenshotHooks* hooks) {
    (void)file_name;
    hooks->wait_idle(hooks->context);
    if (surface_format != 0x16) { // retail only handles D3DFMT_X8R8G8B8 slot
        hooks->log_error(hooks->context,
                         surface_format == 0x17 ? "unsupported-alpha"
                                                : "error ? .\\src\\game\\mother.cpp");
        return 0;
    }

    const int width = 0x280, height = 0x1E0;
    unsigned char* header = static_cast<unsigned char*>(
        hooks->alloc(hooks->context, 0x36));
    unsigned char* pixels = static_cast<unsigned char*>(
        hooks->alloc(hooks->context, 0xE1000)); // 640*480*3
    if (header == 0 || pixels == 0) {
        if (header != 0) hooks->release(hooks->context, header);
        if (pixels != 0) hooks->release(hooks->context, pixels);
        return 0;
    }

    // BITMAPFILEHEADER + BITMAPINFOHEADER, 24bpp, single plane.
    for (int index = 0; index < 0x36; ++index) header[index] = 0;
    header[0] = 'B'; header[1] = 'M';
    unsigned int file_size = 0x36u + 0xE1000u;
    header[2] = static_cast<unsigned char>(file_size);
    header[3] = static_cast<unsigned char>(file_size >> 8);
    header[4] = static_cast<unsigned char>(file_size >> 16);
    header[10] = 0x36;                       // pixel data offset
    header[14] = 0x28;                       // BITMAPINFOHEADER size
    header[18] = 0x80; header[19] = 0x02;    // width 0x280
    header[22] = 0xE0; header[23] = 0x01;    // height 0x1E0
    header[26] = 1;                          // planes
    header[28] = 0x18;                       // 24 bpp

    unsigned char* source = 0;
    int pitch = 0;
    if (hooks->lock_surface(hooks->context, &source, &pitch) != 0) {
        hooks->release(hooks->context, header);
        hooks->release(hooks->context, pixels);
        return 0;
    }
    // Bottom-up copy, dropping the X byte of each 32-bit texel.
    for (int row = 0; row < height; ++row) {
        const unsigned char* in = source + (height - 1 - row) * pitch;
        unsigned char* out = pixels + row * width * 3;
        for (int column = 0; column < width; ++column) {
            out[column * 3 + 0] = in[column * 4 + 0];
            out[column * 3 + 1] = in[column * 4 + 1];
            out[column * 3 + 2] = in[column * 4 + 2];
        }
    }
    hooks->unlock_surface(hooks->context);
    hooks->queue_writer_thread(hooks->context, header, pixels);
    return 1;
}
