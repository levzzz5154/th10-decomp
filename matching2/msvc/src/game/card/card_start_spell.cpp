// 0x00409280: start a spell card on the in-game side panel - count the
// attempt, load the panel's sprites and create its animations.
#include "th10/game/card_update.hpp"
#include "th10/game/score_file.hpp"
#include "th10/game/card_animations.hpp"
#include "th10/platform/sound_queue.hpp"

struct AnimationResource_0043e710;
struct AnimationObject_0043e710;

// A text sprite; the formatter draws into its texture.
struct RecoveryIndicatorVm_00419120 {
    void __cdecl FormatRightAligned(void* manager, ...); // 0x00447AE0
};

struct GameMode_00409280 {
    unsigned char reserved[0x10];
    int replay;                                    // +0x10
};
struct FrontResources_00409280 {
    unsigned char reserved[0x9EC8];
    AnimationResource_0043e710* digits;            // +0x9EC8
};
struct GameThread_00409280 {
    unsigned char reserved_0000[0x8994];
    AnimationResource_00449870* front;             // +0x8994
    unsigned char reserved_8998[4];
    AnimationResource_00449870* text;              // +0x899C
};
struct EnemyManager_00409280 {
    unsigned char reserved[0x3E0B50];
    AnimationResource_00449870* effects;           // +0x3E0B50
};
struct MarkerTarget_00409280 {
    unsigned char reserved[0x1068];
    Vec3 position;                                 // +0x1068
};
struct StageOwner_00409280 {
    unsigned char reserved_00[0x10];
    MarkerTarget_00409280* target;                 // +0x10
    unsigned char reserved_14[0x24];
    AnimationResource_00449870* resource;          // +0x38
};
// Part of the global game state.
struct GameSelection_00409280 {
    int character;                                 // 0x00474C68
    int shot_type;                                 // 0x00474C6C
    unsigned char reserved_08[0x0C];
    int stage;                                     // 0x00474C7C
    unsigned char reserved_18[4];
    int stage_phase;                               // 0x00474C84
};

extern "C" {
extern GameMode_00409280* data_00477838;
extern FrontResources_00409280* data_0047770c;
extern GameThread_00409280* g_ascii_manager;
extern EnemyManager_00409280* data_004776f0;
extern ScoreManager* data_0047783c;
extern StageOwner_00409280* data_00477704;
extern GameSelection_00409280 g_selection;         // 0x00474C68
extern int data_00474c4c;
extern int data_00474c7c;                          // stage number
extern int data_00474c84;
void __stdcall LoadScript_0043e710(AnimationResource_0043e710* resource,
                                   AnimationObject_0043e710* object, int index);
}
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);

static inline void CountAttempt(ScoreSpellRecord* record) {
    if (record->attempts < 99999)
        ++record->attempts;
}

static inline void CopyRecordName(char* destination, const char* source) {
    char c;
    do {
        c = *source++;
        *destination++ = c;
    } while (c != 0);
}

static inline void CopyName(char* const destination, const char* const source) {
    const char* cursor = source;
    char* output = destination;
    while ((*output++ = *cursor++) != 0)
        ;
}

static inline void LoadDigit(HudSprite_00408d60* sprite, int script) {
    LoadScript_0043e710(data_0047770c->digits,
                        reinterpret_cast<AnimationObject_0043e710*>(sprite), script);
}

static inline void StartScript(HudSprite_00408d60* sprite, int script) {
    Entity_StartScript_00404f30(
        reinterpret_cast<AnimationResource_0043e710*>(data_00477704->resource),
        reinterpret_cast<Entity*>(sprite), script);
}

static inline AnimationLists* Animations() {
    return reinterpret_cast<AnimationLists*>(data_00491c10);
}

// Create an animation running `script` of `resource` on the panel's layer.
struct PanelAppearance { int render_bucket; unsigned int flags; };
static inline AnimationRef CreatePanelAnimation(AnimationResource_00449870* resource, int script, PanelAppearance appearance) {
    Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    object->render_bucket = appearance.render_bucket;
    object->flags_35C |= appearance.flags;
    resource->InitializeObject(object, script);
    return Animations()->RegisterPrimaryBack(object);
}
static inline AnimationRef CreateAnimation(AnimationResource_00449870* resource, int script) {
    PanelAppearance appearance = { 15, 0x40000000u };
    return CreatePanelAnimation(resource, script, appearance);
}

// The handle's animation; a stale handle is cleared.
static inline Entity* GetAnimation(int& handle) {
    Entity* object = Animations()->FindInline(handle);
    if (object == 0)
        handle = 0;
    return object;
}

static __forceinline Entity* FindChild(int& handle, int script) {
    Entity* object = GetAnimation(handle);
    for (AnimationListNode* link = reinterpret_cast<AnimationListNode*>(
             &object->child_node_animation); link != 0; link = link->next)
        if (link->object->ScriptIndex() == script)
            return link->object;
    return 0;
}

#pragma code_seg(".text$00409280_fn")
void Card_00408d60::StartSpell(int index, const char* name, int duration) {
    timer.Set(0);
    record_index = index;
    const char* panel_name_cursor = name;
    char* panel_name_destination = spell_name;
    while ((*panel_name_destination++ = *panel_name_cursor++) != 0)
        ;
    flags = (flags & ~0x18u) | 3;

    if (data_00477838->replay != 1) {
        CopyRecordName(data_0047783c->records[g_selection.shot_type + g_selection.character * 3].spells[index].name, name);
        CountAttempt(&data_0047783c->records[g_selection.shot_type + g_selection.character * 3].spells[index]);
        CopyName(data_0047783c->records[6].spells[index].name, name);
        CountAttempt(&data_0047783c->records[6].spells[index]);
    }

    int i;
    for (i = 0; i < 8; ++i)
        LoadDigit(&bonus_digits[i], i + 58);
    for (i = 0; i < 5; ++i)
        LoadDigit(&counter_digits[i], i + 66);

    panel_handles[0].value = CreateAnimation(g_ascii_manager->front, 1).value;
    panel_handles[1].value = CreateAnimation(g_ascii_manager->text, 72).value;
    panel_handles[2].value = CreateAnimation(g_ascii_manager->front, 2).value;
    reinterpret_cast<RecoveryIndicatorVm_00419120*>(
        GetAnimation(reinterpret_cast<int&>(panel_handles[1].value)))
        ->FormatRightAligned(data_00491c10, 0x00FFFFFFu, name);
    data_00492590.Queue(14, 0);

    marker_handle.value = CreateAnimation(data_004776f0->effects, 417).value;
    marker_position = data_00477704->target->position;
    SetAnimationTranslatedPosition_00449350(
        reinterpret_cast<const PositionVector_004492f0*>(&marker_position), data_00491c10,
        marker_handle);
    FindChild(marker_handle.value, 415)->ScriptIntegerVariables()[2] = duration;
    FindChild(marker_handle.value, 416)->ScriptIntegerVariables()[2] = duration;

    bonus_duration = duration;
    bonus = (g_selection.stage * 3 + 10) * data_00474c4c * 10;
    bonus_start = bonus;
    if (bonus >= 100000000)
        bonus_start = 99999999;

    CreateAnimation(data_004776f0->effects, 427);
    switch (g_selection.stage) {
    case 1:
        StartScript(&frame_sprite, 12);
        StartScript(&label_sprite, 11);
        if (index >= 2)
            CreateAnimation(data_00477704->resource, 14);
        else
            CreateAnimation(data_00477704->resource, 15);
        break;
    case 2:
        StartScript(&frame_sprite, 14);
        StartScript(&label_sprite, 15);
        CreateAnimation(data_00477704->resource, 17);
        break;
    case 3:
        StartScript(&frame_sprite, 18);
        StartScript(&label_sprite, 19);
        CreateAnimation(data_00477704->resource, 21);
        break;
    case 4:
        StartScript(&frame_sprite, 19);
        StartScript(&label_sprite, 20);
        CreateAnimation(data_00477704->resource, 22);
        break;
    case 5:
        StartScript(&frame_sprite, 12);
        StartScript(&label_sprite, 13);
        CreateAnimation(data_00477704->resource, 15);
        break;
    case 6:
        StartScript(&frame_sprite, 33);
        StartScript(&label_sprite, 34);
        CreateAnimation(data_00477704->resource, 36);
        break;
    case 7:
        if (g_selection.stage_phase < 24) {
            StartScript(&frame_sprite, 38);
            CreateAnimation(data_00477704->resource, 40);
        } else {
            StartScript(&frame_sprite, 27);
            StartScript(&label_sprite, 28);
            CreateAnimation(data_00477704->resource, 30);
        }
        break;
    }
}
#pragma code_seg()
