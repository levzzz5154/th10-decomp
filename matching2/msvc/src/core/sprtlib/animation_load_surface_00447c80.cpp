// 0x00447C80 (576 bytes): load image `index` of the manager from an archive
// file (or from the bytes a previous AnimationLoadMemory left behind) and
// build its two surfaces: a device-side one for blitting (render target, or
// an offscreen plain surface when that fails) and a system-memory copy. The
// file is decoded once into a 640x1024 scratch surface. Returns 0 or -1.
//
// Native LTCG passes the manager in ECX and the name in EDX; the index stays
// on the stack. Nothing in the retail image calls it.
//
// Every failure after the scratch surface exists leaves through one `fail`
// label; that is what places the failure cleanup ahead of the success path.
#include "th10/render/resource_surface_loading.hpp"
#include "th10/platform/archive_file.hpp"
#include "../../../build_support/layout/ltcg/resource_surface_loading_log.hpp"

// The device is always reached through this accessor: it makes the compiler
// load the device and its vtable before the arguments, as retail does.
static inline SurfaceDevice_00447c80* Device() { return g_d3d_device; }

#pragma code_seg(".text$02surface")
extern "C" __declspec(noinline) int __fastcall AnimationLoadSurface_00447c80(
        AnimationManagerIndexed_00447f70* manager, const char* name, int index) {
    char path[260];
    int size;
    char* data;
    Resource_00447f70* scratch;
    if (manager->primary[index])
        manager->Clear(index);
    if (!manager->memory[index]) {
        sprintf(path, str_string_format, name);
        data = Archive_LoadFile(path, &size, 0);
        if (!data) {
            g_log.AppendLine(str_cannot_load_format, name);
            return -1;
        }
    } else {
        data = static_cast<char*>(manager->memory[index]);
        size = manager->memorySize[index];
        manager->memory[index] = 0;
    }
    if (Device()->CreateOffscreenPlainSurface(640, 1024, data_00491d14, 3, &scratch, 0) != 0)
        return -1;
    if (LoadSurfaceFile_004521d0(scratch, 0, 0, data, size, 0, 1, 0, &manager->info[index]) != 0)
        goto fail;
    if (Device()->CreateRenderTarget(manager->info[index].width, manager->info[index].height,
                                     data_00491d14, 0, 0, 1, &manager->primary[index], 0) != 0) {
        if (Device()->CreateOffscreenPlainSurface(manager->info[index].width,
                                                  manager->info[index].height, data_00491d14, 3,
                                                  &manager->primary[index], 0) != 0)
            goto fail;
    }
    if (Device()->CreateOffscreenPlainSurface(manager->info[index].width,
                                              manager->info[index].height, data_00491d14, 3,
                                              &manager->secondary[index], 0) != 0)
        goto fail;
    if (LoadSurfaceCopy_004521d6(manager->primary[index], 0, 0, scratch, 0, 0, 1, 0) != 0)
        goto fail;
    if (LoadSurfaceCopy_004521d6(manager->secondary[index], 0, 0, scratch, 0, 0, 1, 0) != 0)
        goto fail;
    if (scratch) {
        scratch->Release();
        scratch = 0;
    }
    if (data)
        ReleaseHeapMemory_00452422(data);
    return 0;

fail:
    if (scratch) {
        scratch->Release();
        scratch = 0;
    }
    if (data)
        ReleaseHeapMemory_00452422(data);
    return -1;
}
#pragma code_seg()
