// 0x0042E5A0: rebuild every option-screen label from the current volumes.
// Equivalent C++ model of asm_FUN_0042e5a0_0042e5a0; the exact build keeps the
// assembly region because MSVC's LTCG tie-breaks the shared label walk into a
// folded read-modify-write and a hoisted argument setup that the readable
// structure below does not reproduce byte-for-byte (see the layout's
// recorded differences).
//
// The ConfigureFromResource body is included so the model link sees the callee
// in the same translation unit, the way the retail compiler did; its calling
// convention is the custom (ECX resource, EAX object, DX index) form the
// retail image uses.

#include "../../src/game/animation_object_configure_from_resource_0043e5a0.cpp"

#include "th10/game/options_label_refresh_0042e5a0.hpp"

extern "C" int data_00497854;   // music volume copy for the sound thread
extern "C" int data_00497858;   // sound volume copy
extern "C" int data_0049785c;   // music DSP attenuation, DirectSound units
extern "C" const char data_0046ece8[];  // "bgm/th10_02.wav"

extern "C" int __ftol2(void);

// The retail curve constants, pooled at their retail addresses.
extern "C" const float data_00470afc;   // 1.0
extern "C" const float data_00470b00;   // 0.01
extern "C" const float data_00470b80;   // -5000.0

extern "C" int __ftol2(void);

// The music DSP attenuation is -5000 - (int)((1 - x^4) * -5000) with
// x = 1 - music/100, and a fixed full attenuation while the music is off.
static int MusicAttenuation(int music) {
    float fraction = music * data_00470b00;
    float complement = data_00470afc - fraction;
    float squared = complement * complement;
    float fourth = data_00470afc - squared * squared;
    return data_00470b80 - static_cast<int>(fourth * data_00470b80);
}

// The room's second animation slot holds the label parent.  A missing parent
// clears the slot; the walk answers whether a child with the script exists,
// and the leaf then operates on the manager's id-0 record (the label object
// itself) exactly like the retail block does.
static __forceinline LabelAnimation_0042d920* FindLabel(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room,
        int script) {
    RecoveryScriptId_0040bd80* slot =
        reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[1]);
    LabelParent_0042d920* parent = static_cast<LabelParent_0042d920*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(manager)->Find(manager, *slot));
    if (parent == 0)
        slot->value = 0;
    for (LabelLink_0042d920* link = &parent->children; link != 0; link = link->next)
        if (link->object->script == script)
            return link->object;
    RecoveryScriptId_0040bd80 none = { 0 };
    return static_cast<LabelAnimation_0042d920*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(manager)->Find(manager, none));
}

// Point one digit label at the sprite for `digit` in the given font.
// Digit positions of one readout, computed the way the retail blocks do:
// each label block derives its sprite immediately before configuring.
static __forceinline int SpriteHundreds(int volume) { return volume / 100; }
static __forceinline int SpriteTens(int volume) { return (volume / 10) % 10; }
static __forceinline int SpriteOnes(int volume) { return volume % 10; }

static __forceinline void ConfigureDigit(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room,
        int script, int sprite) {
    LabelAnimation_0042d920* label = FindLabel(manager, room, script);
    if (label == 0)
        return;
    reinterpret_cast<AnimationObject_0043e5a0*>(label)->resource->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0*>(label), sprite);
}

// Show or hide one digit label through animation flag bit 1.
static __forceinline void ShowDigit(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room,
        int script, bool visible) {
    LabelAnimation_0042d920* label = FindLabel(manager, room, script);
    if (visible)
        label->flags_35c |= 2;
    else
        label->flags_35c &= ~2u;
}

// The three digit positions of one readout in both fonts.  The digits are
// drawn unconditionally with the current volume's sprites.
static __forceinline void DrawMusicDigits(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room,
        int volume) {
    ConfigureDigit(manager, room, 0x25, SpriteHundreds(volume) + 0x33);
    ConfigureDigit(manager, room, 0x26, SpriteTens(volume) + 0x33);
    ConfigureDigit(manager, room, 0x27, SpriteOnes(volume) + 0x33);
    ConfigureDigit(manager, room, 0x29, SpriteHundreds(volume) + 0x3D);
    ConfigureDigit(manager, room, 0x2A, SpriteTens(volume) + 0x3D);
    ConfigureDigit(manager, room, 0x2B, SpriteOnes(volume) + 0x3D);
}

static __forceinline void DrawSoundDigits(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room,
        int volume) {
    ConfigureDigit(manager, room, 0x2D, SpriteHundreds(volume) + 0x33);
    ConfigureDigit(manager, room, 0x2E, SpriteTens(volume) + 0x33);
    ConfigureDigit(manager, room, 0x2F, SpriteOnes(volume) + 0x33);
    ConfigureDigit(manager, room, 0x31, SpriteHundreds(volume) + 0x3D);
    ConfigureDigit(manager, room, 0x32, SpriteTens(volume) + 0x3D);
    ConfigureDigit(manager, room, 0x33, SpriteOnes(volume) + 0x3D);
}

#pragma code_seg(".text$0042e5a0_fn")
__declspec(noinline) void __stdcall OptionsLabelRefresh_0042e5a0(
    RecoveryMusicRoom_00433ef0* room) {
    RecoveryLookupContext_0040bd80* manager =
        reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10);
    int music = data_00491d4c.music_volume;
    data_00497854 = music;

    reinterpret_cast<RecoveryMusicResourceQueue_0043e460*>(
        &data_00492590)->RegisterResource(data_0046ece8, 8, 0);

    int sound = data_00491d4c.sound_volume;
    data_00497858 = sound;
    if (sound == 0)
        data_0049785c = -10000;
    else
        data_0049785c = MusicAttenuation(music);

    DrawMusicDigits(manager, room, music);
    DrawSoundDigits(manager, room, sound);

    // A readout below ten renders the ones digit alone; at one hundred the
    // full three digits appear; in between the tens digit joins the ones.
    if (music < 10) {
        ShowDigit(manager, room, 0x25, false);
        ShowDigit(manager, room, 0x26, false);
        ShowDigit(manager, room, 0x27, false);
        ShowDigit(manager, room, 0x2A, false);
    } else if (music >= 100) {
        ShowDigit(manager, room, 0x25, true);
        ShowDigit(manager, room, 0x26, true);
        ShowDigit(manager, room, 0x27, true);
        ShowDigit(manager, room, 0x2A, true);
    } else {
        ShowDigit(manager, room, 0x25, false);
        ShowDigit(manager, room, 0x26, true);
        ShowDigit(manager, room, 0x27, false);
        ShowDigit(manager, room, 0x2A, true);
    }
    if (sound < 10) {
        ShowDigit(manager, room, 0x2D, false);
        ShowDigit(manager, room, 0x2E, false);
        ShowDigit(manager, room, 0x31, false);
        ShowDigit(manager, room, 0x32, false);
    } else if (sound >= 100) {
        ShowDigit(manager, room, 0x2D, true);
        ShowDigit(manager, room, 0x2E, true);
        ShowDigit(manager, room, 0x31, true);
        ShowDigit(manager, room, 0x32, true);
    } else {
        ShowDigit(manager, room, 0x2D, false);
        ShowDigit(manager, room, 0x2E, true);
        ShowDigit(manager, room, 0x31, false);
        ShowDigit(manager, room, 0x32, true);
    }
}
#pragma code_seg()
