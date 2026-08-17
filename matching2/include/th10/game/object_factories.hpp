#pragma once

#include <cstdint>

// 0x0041C290 - Create the 0x45C-byte score manager: allocate, run the
// injected base constructor (retail 0x0041C030) on the sub-object at
// word 4, zero the whole block (making the base construction dead
// stores, as in retail), publish the instance through the retail global
// at 0x0047781C, and run the injected initializer (retail 0x0041C120).
// On initializer failure the injected destructor (retail 0x0041C1C0)
// and free run and the function returns null. Retail calls the
// initializer even when the allocation failed; the readable form keeps
// that ordering.
uint32_t* ScoreManager_CreateAndInit(void* (*allocate)(uint32_t size),
                                     void (*construct_base)(uint32_t* base),
                                     int32_t (*init)(uint32_t* state),
                                     void (*destroy)(uint32_t* state));

// 0x0041FD00 - Create one 0x3F0-byte enemy slot: allocate, run the
// injected constructor (retail 0x0041F850, returning the object), and
// run the injected global initializer (retail 0x0041FAC0). On
// initializer failure the injected destructor (retail 0x0041FB50) and
// free run and the function returns null. As in retail, the initializer
// runs even when the allocation failed.
uint32_t* EnemySlot_CreateAndInit(void* (*allocate)(uint32_t size),
                                  uint32_t* (*construct)(uint32_t* state),
                                  int32_t (*init)(),
                                  void (*destroy)(uint32_t* state));
