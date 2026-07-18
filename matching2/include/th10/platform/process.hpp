#pragma once

#include "th10/platform/windows_types.hpp"

int Platform_LaunchProcess(void* unused, char* command_line,
                           const char* application_name, int wait_for_exit);
void Platform_StopWorker(void* state, unsigned int (*wait)(void*, unsigned int),
                         void (*sleep)(unsigned int), void (*close)(void*));
void Platform_DestroyWorker(void* state, void* vtable, unsigned char flags,
                            unsigned int (*wait)(void*, unsigned int),
                            void (*sleep)(unsigned int),
                            void (*close)(void*), void (*free_memory)(void*));
int Platform_InvokeInterface(void* state, int (*invoke)(void*));
