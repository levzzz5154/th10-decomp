#pragma once

// Spell card state dispatch (retail 0x0042A6A0).
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

// Spell-card manager states handled by SpellCard_Dispatch.
enum SpellCardState {
	kSpellStateDeclare = 0,  // boss declared the card: record history
	kSpellStateActivate = 1, // card goes live: publish the UI globals
};

struct SpellRecord { // retail allocation size 0x1C4
	short difficulty;   // +0x000
	short spell_id;     // +0x002
	int reserved0[2];   // +0x004
	int bonus_initial;      // +0x00C: starting spell bonus value
	short bonus_active;     // +0x010: nonzero while the bonus can still be won
	short pad;              // +0x012
	int bonus_gauge;        // +0x014: published *10 through the score-gauge hook
	int duration;           // +0x018: spell time limit in frames
	int activation_param_a; // +0x01C -> DAT_00474c70 (semantics unidentified)
	int activation_param_b; // +0x020 -> DAT_00474c98 (semantics unidentified)
	char title_text[0x190]; // +0x024: believed spell title buffer (unconfirmed)
	int history_captures;   // +0x1B4 -> DAT_00474c90 ("History x/y" numerator)
	int history_attempts;   // +0x1B8 -> DAT_00474c9c ("History x/y" denominator)
	int reserved2;          // +0x1BC
	Word flags;      // +0x1C0; bit 0 mirrors the global capture flag
};

struct SpellSlot { // retail manager+0xA0 + difficulty*0x24
	int current_a;              // +0x00
	int previous_a;             // +0x04
	int current_b;              // +0x08
	int previous_b;             // +0x0C
	SpellRecord* record; // +0x10
	int counter;                // +0x14 (cleared on activation)
	int reserved[3];            // +0x18
};

struct SpellManager {
	int state;                    // retail +0x10; 0 records, 1 activates
	SpellRecord** history; // retail +0x1C table, indexed by difficulty
	SpellSlot* slots;      // retail +0xA0 table, indexed by difficulty
};

struct SpellUiGlobals {
	short* active_spell_id;  // retail DAT_004918b0
	int* active_spell_aux;   // retail DAT_004918b4 (always reset to 0)
	int* bonus_value;        // retail DAT_00474c44
	short* bonus_active;     // retail DAT_00474c48
	void* gauge;             // retail &DAT_00474c40
	void (*store_gauge)(void* gauge, int value); // retail 0x00418B80
	// Retail spell clock at 0x00474c54..0x00474c64; its frame word doubles
	// as the published spell duration (DAT_00474c58).
	RegisteredClock* spell_clock;
	float* frame_scale;      // retail &DAT_00476f78
	int* activation_param_a; // retail DAT_00474c70
	int* activation_param_b; // retail DAT_00474c98
	int* history_captures;   // retail DAT_00474c90
	int* history_attempts;   // retail DAT_00474c9c
	const Word* capture_flag; // retail DAT_00491fc4 (bit 0)
};

struct SpellDispatchEnv {
	const int* difficulty; // retail DAT_00474c7c
	// Returns a zeroed 0x1C4-byte record (retail operator new + wipe loop).
	SpellRecord* (*allocate_record)();
	SpellUiGlobals ui;
};

void SpellCard_Dispatch(SpellManager* manager, SpellDispatchEnv* env);
