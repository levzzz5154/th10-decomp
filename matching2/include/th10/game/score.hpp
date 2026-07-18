#pragma once

#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"

// Partial layout for the score/counter object used by 0x0041BE80.
struct ScoreCounter {
    uint32_t reserved_header[3];
    int32_t value;  // +0x0C, capped at 99,999

    void AddScaled(int32_t amount);
};

void ScoreOwnedObject_Destroy(void* object, void (*cleanup)(void*));

float WrappedAngleDifference(float angle, float reference,
                             float period, float half_period);
float Entity_AngleToPoint(const float* point, const float* origin);
float Entity_AngleFromPoint(const float* point, const float* origin);
bool OutsideAxisAlignedBounds(float center_x, float center_y,
                              float offset_x, float offset_y,
                              float half_width, float half_height);
bool InputMaskActive(uint16_t held_mask, uint16_t pressed_mask,
                     uint16_t query_mask);
void Input_EncodeJoystickButtons(uint32_t buttons,
                                 unsigned char* destination);
int Input_UpdateKeyboardState(unsigned char* destination, bool inputEnabled,
                              bool directInputMode,
                              int (*pollKeyboard)(unsigned char*));
void Input_NormalizeKeyboardState(
    unsigned char* state, int (*getState)(unsigned char*),
    int (*setState)(const unsigned char*));
void Score_InputHistoryStep(void* state);
void Score_InputHistorySave(void* state);
unsigned int CountPatternMatches(const unsigned char* table,
                                  unsigned int groups, unsigned int stride,
                                  unsigned int width, unsigned char query);
void UpdateInputState(void* input_state);
unsigned int UpdateBoundedCounter(unsigned int requested,
                                  unsigned int* current_limit);
void SetInputMode(void* input_state, unsigned int requested_mode);
void Score_SetPolarVector(float* destination, float angle, float magnitude);
void Score_VectorFromPolar(float* destination, float angle, float magnitude);
void* ScoreObject_Initialize(void* unused, void* object);
void* ScoreExtendedObject_Initialize(void* unused, void* object);
struct ScoreOwnedRecord {
    void* object;
    ScoreOwnedRecord* previous;
    ScoreOwnedRecord* next;
    void (*cleanup)(void* object);
};
void ScoreExtendedObject_Destroy(void* object,
                                 void (*retireCallback)(void*));
int ScoreState_ActivateFromResult(void* state, int geometryResult,
                                  int stageIndex, void (*spawn)(void*));

struct ScoreLinkedRecord {
    unsigned char reserved_000[8];
    ScoreLinkedRecord* next;       // +0x08
    int type;                      // +0x0C
    unsigned char reserved_010[0x40];
    unsigned char marked;          // +0x50
    unsigned char reserved_051[3];
    int (*Evaluate)(ScoreLinkedRecord* record); // +0x54 typed callback view
};

void ScoreRecords_MarkEligible(ScoreLinkedRecord* first);
int ScoreRecords_CopyVectorAndEvaluate(
    ScoreLinkedRecord* first, float* destination, const float* vector);
void ScoreGauge_AddWithMinimum(void* gauge, int award);
int Position_IsPartiallyInViewport(const void* center, float radius_x,
                                    float radius_y);

// Partial layout of the global run-score state at 0x00474C40. The field at
// +0x04 is the player's score; callers pass awards in tenths of a point.
struct GameScore {
    uint32_t reserved_header;
    int32_t value;  // +0x04, capped at 999,999,999

    void AddScaled(int32_t amount);
};

// Partial owner layout used by the score/game-flow callbacks adjacent to the
// score accumulator code. A callback with its retirement bit (0x02) set is
// removed by the scheduler on its next pass.
struct ScoreRuntimeCallbacks {
    uint32_t reserved_header[2];
    SchedulerCallback* primary;    // +0x08
    SchedulerCallback* secondary;  // +0x0C
    SchedulerCallback* tertiary;   // runtime's third callback handle

    void Retire();
};

int ScoreRuntimeCallbacks_Initialize(
    ScoreRuntimeCallbacks* callbacks, void* scheduler_device,
    SchedulerFunction primary_function, SchedulerFunction secondary_function,
    SchedulerFunction tertiary_function);

typedef void (*ScoreEntityRelease)(void* manager, Entity* entity);
// Partial layout of the score/gameplay runtime owning all entity arrays visited
// by the teardown callbacks at 0x004091C0 and 0x00409230.
struct ScoreRuntimeState {
    uint32_t reserved_header[4];
    Entity primaryEntity;    // +0x0010
    Entity secondaryEntity;  // +0x03BC
    uint8_t reserved_0768[0x10];
    Entity stageEntities[8]; // +0x0778
    Entity effectEntities[5];// +0x24D8
    uint8_t reserved_3744[0x48];
    uint32_t flags;          // +0x378C; bit 0 requests entity release

    int ReleaseFlaggedEntities(
        ScoreEntityRelease releaseEntity, void* entityManager);
    int ReleaseFlaggedEntityArrays(
        ScoreEntityRelease releaseEntity, void* entityManager);
    int RunArrayReleaseCallback(
        ScoreEntityRelease releaseEntity, void* entityManager);
};

ScoreRuntimeState* ScoreRuntimeState_Initialize(ScoreRuntimeState* state);
