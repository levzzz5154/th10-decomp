#pragma once

// Lazy creation of result screen effects (retail 0x0041FDD0).
#include "th10/util/scalars.hpp"

struct ResultEffectVm {
	int layer;
	Word flags;
};

struct ResultLazyHost {
	void* owner_slot;
	int stage_a; // creates the effect vm when it reaches 1
	int stage_b; // resolves the cached sprite when it reaches 1
	int frame;
};

struct ResultLazyEnv {
	ResultEffectVm* (*acquire_effect)(void);
	void (*assign_script)(ResultEffectVm* vm, int script);
	void (*register_front)(void* manager);
	void* manager;
	Word* cached_sprite_slot;
	Word* (*clone_sprite)(void* source);
	void* sprite_source;
};

int ResultScreen_LazyCreateEffects(ResultLazyHost* host, ResultLazyEnv* env);
