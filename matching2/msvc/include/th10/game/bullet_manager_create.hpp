#pragma once
#include "th10/game/bullet_manager_teardown.hpp"

void* __cdecl operator new(unsigned int size);

__declspec(noinline) BulletManager2* __stdcall BulletManager_Create2();
