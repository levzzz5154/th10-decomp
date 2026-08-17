#pragma once

#include <cstdint>

// 0x004180E0 - Create the 0x60-byte game UI manager and publish it
// through the retail global at 0x00477810. Retail clears bit 0 of word
// 8 and runs the config-defaults constructor (0x00418C40) on the record
// at word 9, but the following full-object wipe makes both dead; only
// the wipe is observable. The device's EvictManagedResources call
// (vtable +0x14) always runs, the caller's return address lands in word
// 0x17, bit 2 of word 0x16 sets, and the worker thread spawner (retail
// 0x00420EA0) starts the UI worker (retail LAB_00417C70) with a null
// argument. Retail would write through a null allocation after the
// evict call; the readable form returns null instead. The allocator,
// evict edge, and spawner are injected.
uint32_t* GameUi_CreateAndPublish(void* (*allocate)(uint32_t size),
                                  void (*evict_managed_resources)(),
                                  void (*spawn_worker)(void* start_address,
                                                       void* argument),
                                  void* worker_proc,
                                  uint32_t return_address);
