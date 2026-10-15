// 0x0042E5A0: rebuild every option-screen label from the current volumes.
// Equivalent C++ model of asm_FUN_0042e5a0_0042e5a0; the exact build keeps the
// assembly region because the retail body receives the music room in EDI (a
// private register convention no declaration can name) and MSVC's LTCG
// tie-breaks the label walks and call argument setup in ways the readable
// structure below does not reproduce byte-for-byte (see the layout's recorded
// differences).
//
// The complete refresh is linked with its genuine options callers and the
// real resource-configuration and registration bodies. That lets LTCG derive
// retail's EDI room receiver, EAX object/queue receivers and plain RET.
//
// Per label the retail code walks slot 1's children for the script id, takes
// the found child's own id (or 0 when the walk fails) and looks that id up in
// the manager; the volume bytes are re-read from 0x00491D68/0x00491D69 at
// every site, which is why the helpers below take the volume as a reference
// instead of a cached copy.

#include "th10/game/options_label_refresh_0042e5a0.hpp"
#include "th10/render/resource_registrar_0043e460.hpp"

extern "C" int data_00497854;   // music volume copy for the sound thread
extern "C" int data_00497858;   // sound volume copy
extern "C" int data_0049785c;   // music DSP attenuation, DirectSound units
extern "C" const char data_0046ece8[];  // "bgm/th10_02.wav"

extern "C" int __ftol2(void);

// The retail curve constants, pooled at their retail addresses.
extern "C" const float data_00470afc;   // 1.0
extern "C" const float data_00470b00;   // 0.01
extern "C" const float data_00470b80;   // -5000.0

// The music DSP attenuation is -5000 - (int)((1 - x^4) * -5000) with
// x = 1 - music/100, read back from the stored volume copy the way the
// retail block does, and a fixed full attenuation while the music is off.
static int MusicAttenuation(const int& stored_music) {
    float fraction = stored_music * data_00470b00;
    float complement = data_00470afc - fraction;
    float squared = complement * complement;
    float fourth = data_00470afc - squared * squared;
    return -5000 - static_cast<int>(fourth * data_00470b80);
}

// The room's second animation slot holds the label parent.  A missing parent
// clears the slot; the walk answers with the found child's own id (0 when the
// walk fails) and the leaf looks that id up in the manager exactly like the
// retail block does.
static __forceinline LabelAnimation_0042d920* FindLabel(
        RecoveryLookupContext_0040bd80* manager, Title* room,
        int script) {
    RecoveryScriptId_0040bd80* slot =
        reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[1]);
    LabelParent_0042d920* parent = static_cast<LabelParent_0042d920*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(manager)->Find(manager, *slot));
    if (parent == 0)
        slot->value = 0;
    LabelLink_0042d920* match = 0;
    for (LabelLink_0042d920* link = &parent->children; link != 0; link = link->next) {
        if (link->object->script == script) {
            match = link;
            break;
        }
    }
    int id;
    if (match != 0)
        id = match->object->id;
    else
        id = 0;
    RecoveryScriptId_0040bd80 key = { id };
    return static_cast<LabelAnimation_0042d920*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(manager)->Find(manager, key));
}

// Point one digit label at the sprite for its digit of the readout.  The
// volume is re-read here, after the walk, the way the retail blocks do: the
// sprite is only computed for a label that was found.
static __forceinline void ConfigureHundreds(
        RecoveryLookupContext_0040bd80* manager, Title* room,
        int script, int font, const signed char& volume) {
    LabelAnimation_0042d920* label = FindLabel(manager, room, script);
    if (label == 0)
        return;
    AnimationObject_0043e5a0* object = reinterpret_cast<AnimationObject_0043e5a0*>(label);
    object->resource->ConfigureObject(object, volume / 100 + font);
}

static __forceinline void ConfigureTens(
        RecoveryLookupContext_0040bd80* manager, Title* room,
        int script, int font, const signed char& volume) {
    LabelAnimation_0042d920* label = FindLabel(manager, room, script);
    if (label == 0)
        return;
    AnimationObject_0043e5a0* object = reinterpret_cast<AnimationObject_0043e5a0*>(label);
    object->resource->ConfigureObject(object, volume / 10 % 10 + font);
}

static __forceinline void ConfigureOnes(
        RecoveryLookupContext_0040bd80* manager, Title* room,
        int script, int font, const signed char& volume) {
    LabelAnimation_0042d920* label = FindLabel(manager, room, script);
    if (label == 0)
        return;
    AnimationObject_0043e5a0* object = reinterpret_cast<AnimationObject_0043e5a0*>(label);
    object->resource->ConfigureObject(object, volume % 10 + font);
}

// Show or hide one digit label through animation flag bit 1.  Like the retail
// ladder the found label is flagged without a further check; the update is a
// load, a mask and a separate store, the shape the retail blocks share tails
// around.
static __forceinline void ShowDigit(
        RecoveryLookupContext_0040bd80* manager, Title* room,
        int script, bool visible) {
    LabelAnimation_0042d920* label = FindLabel(manager, room, script);
    unsigned int* flags = &label->flags_35c;
    if (visible)
        *flags |= 2u;
    else
        *flags &= ~2u;
}

#pragma code_seg(".text$0042e5a0_fn")
__declspec(noinline) void __stdcall RefreshOptions_0042e5a0(
    Title* room) {
    RecoveryLookupContext_0040bd80* manager =
        reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10);
    data_00497854 = data_00491d4c.music_volume;

    // The request queue records "bgm/th10_02.wav" for resource 8; the retail
    // form passes the queue in a register (EAX) and the name in EDX.
    reinterpret_cast<AnimationManager_0043e460*>(&data_00492590)->RegisterResource(data_0046ece8, 8, 0);

    int sound = data_00491d4c.sound_volume;
    data_00497858 = sound;
    if (sound != 0)
        data_0049785c = MusicAttenuation(data_00497854);
    else
        data_0049785c = -10000;

    // The twelve digit labels are drawn unconditionally with the current
    // volume's sprites: hundreds, tens, ones of the large font, then the small.
    const signed char& music = data_00491d4c.music_volume;
    const signed char& sound_volume = data_00491d4c.sound_volume;
    ConfigureHundreds(manager, room, 0x25, 0x33, music);
    ConfigureTens(manager, room, 0x26, 0x33, music);
    ConfigureOnes(manager, room, 0x27, 0x33, music);
    ConfigureHundreds(manager, room, 0x29, 0x3D, music);
    ConfigureTens(manager, room, 0x2A, 0x3D, music);
    ConfigureOnes(manager, room, 0x2B, 0x3D, music);
    ConfigureHundreds(manager, room, 0x2D, 0x33, sound_volume);
    ConfigureTens(manager, room, 0x2E, 0x33, sound_volume);
    ConfigureOnes(manager, room, 0x2F, 0x33, sound_volume);
    ConfigureHundreds(manager, room, 0x31, 0x3D, sound_volume);
    ConfigureTens(manager, room, 0x32, 0x3D, sound_volume);
    ConfigureOnes(manager, room, 0x33, 0x3D, sound_volume);

    // A readout below ten hides the hundreds and tens labels of both fonts;
    // at one hundred all four appear; in between the tens digits appear and
    // the hundreds stay hidden.  The volume is re-read for every ladder test.
    if (music < 10) {
        ShowDigit(manager, room, 0x25, false);
        ShowDigit(manager, room, 0x26, false);
        ShowDigit(manager, room, 0x29, false);
        ShowDigit(manager, room, 0x2A, false);
    } else if (music < 100) {
        ShowDigit(manager, room, 0x25, false);
        ShowDigit(manager, room, 0x26, true);
        ShowDigit(manager, room, 0x29, false);
        ShowDigit(manager, room, 0x2A, true);
    } else {
        ShowDigit(manager, room, 0x25, true);
        ShowDigit(manager, room, 0x26, true);
        ShowDigit(manager, room, 0x29, true);
        ShowDigit(manager, room, 0x2A, true);
    }
    if (sound_volume < 10) {
        ShowDigit(manager, room, 0x2D, false);
        ShowDigit(manager, room, 0x2E, false);
        ShowDigit(manager, room, 0x31, false);
        ShowDigit(manager, room, 0x32, false);
    } else if (sound_volume < 100) {
        ShowDigit(manager, room, 0x2D, false);
        ShowDigit(manager, room, 0x2E, true);
        ShowDigit(manager, room, 0x31, false);
        ShowDigit(manager, room, 0x32, true);
    } else {
        ShowDigit(manager, room, 0x2D, true);
        ShowDigit(manager, room, 0x2E, true);
        ShowDigit(manager, room, 0x31, true);
        ShowDigit(manager, room, 0x32, true);
    }
}
#pragma code_seg()
