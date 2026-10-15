#pragma once
#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"
#include "th10/util/heap.hpp"




// Recovered semantic C++ definitions.

extern "C" void __cdecl crt_free(void*);
extern "C" void __cdecl crt_free_startup(void*);
#ifdef _MSC_VER
void* __cdecl operator new(uint32_t size);
#else
void* operator new(decltype(sizeof(0)) size);
#endif

