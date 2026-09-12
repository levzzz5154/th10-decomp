#pragma once

// Sprite resource resolution into an unused descriptor slot (retail 0x00424480).
// --- 0x00424480 -------------------------------------------------------------
struct SpriteResource {
	float field_08, field_0c, field_30, field_34;
};
struct SpriteNode {
	int first_vm_handle;
	SpriteResource* resource;
};
