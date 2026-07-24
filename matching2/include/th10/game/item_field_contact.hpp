#pragma once

// Item field contact test (retail 0x004266B0).

struct ItemField {
	float min_x; // +0x404
	float min_y; // +0x408
	float max_x; // +0x410
	float max_y; // +0x414
	int mode;    // +0x458, modes 2/3/4 suppress auto-collection
	int autocollect_timer; // +0x4310
};

struct ItemFieldEnv {
	float half_scale;          // half-extent factor (0.5)
	float margin;              // outer keep-alive margin
	const int* dialogue_active; // may be null when no dialogue owner exists
	void (*collect_all)(ItemField* field);
};

int Item_TestFieldContact(const float* position, const float* size,
                          ItemField* field, ItemFieldEnv* env);
