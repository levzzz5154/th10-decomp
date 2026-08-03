// 0x0041BE80 - Add one tenth of amount to the counter, saturating at 99,999.
#include "th10/game/score.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <cstring>

extern Entity* __fastcall Entity_Constructor(Entity* entity);
extern "C" float cosf(float);
extern "C" float sinf(float);
extern "C" float atan2f(float, float);
extern "C" void _free(void*);
extern void* PTR_LAB_0046dab0;
extern void* PTR_LAB_0046da60;
extern uint32_t DAT_00476f78;
extern uint32_t DAT_00491be4;

#ifdef _MSC_VER
extern "C" void sub_4091C0(void*);
extern "C" void sub_40B7B0(void*);
extern "C" void j__free(void*);
#endif

namespace {
PlayerScoreRuntimeBindings g_player_score_bindings = {};

int __fastcall PlayerScore_Update(void* owner) {
    if (g_player_score_bindings.update == 0)
        Runtime_MissingEdge(0x00408D60u, "player/score UI update");
    return g_player_score_bindings.update(owner);
}

int __fastcall PlayerScore_ReleasePrimary(void* owner) {
    if (g_player_score_bindings.release_primary == 0)
        Runtime_MissingEdge(0x00409230u, "player/score primary release");
    return g_player_score_bindings.release_primary(owner);
}

int __fastcall PlayerScore_ReleaseArrays(void* owner) {
    if (g_player_score_bindings.release_arrays == 0)
        Runtime_MissingEdge(0x00409270u, "player/score array release");
    return g_player_score_bindings.release_arrays(owner);
}
}  // namespace

// 0x0040B9D0 - Run the owned-object cleanup and release its allocation.
#ifdef _MSC_VER
__declspec(naked) void ScoreOwnedObject_Destroy(
        void* object, void (*cleanup)(void*)) {
    __asm {
        test esi, esi
        jz locret_40B9E1
        push esi
        call sub_40B7B0
        push esi
        call j__free
        pop ecx
locret_40B9E1:
        ret
    }
}
#else
void ScoreOwnedObject_Destroy(void* object, void (*cleanup)(void*)) {
    if (object != 0) {
        if (cleanup != 0)
            cleanup(object);
        _free(object);
    }
}
#endif

// 0x00408660 - Return the shortest signed difference on a periodic axis.
float WrappedAngleDifference(float angle, float reference,
                             float period, float half_period) {
    float difference = angle - reference;
    if (difference > half_period)
        return difference - period;
    if (-difference > half_period)
        return difference + period;
    return difference;
}

// 0x00426610 - Angle from an entity origin to a supplied point.
float Entity_AngleToPoint(const float* point, const float* origin) {
    float dx = point[0] - origin[0];
    float dy = point[1] - origin[1];
    if (dx == 0.0f && dy == 0.0f)
        return 3.14159265358979323846f;
    return atan2f(dy, dx);
}

// 0x00426660 - The inverse displacement form used by the companion leaf.
float Entity_AngleFromPoint(const float* point, const float* origin) {
    float dx = origin[0] - point[0];
    float dy = origin[1] - point[1];
    if (dx == 0.0f && dy == 0.0f)
        return 3.14159265358979323846f;
    return atan2f(dy, dx);
}

// 0x00408910 - Construct the entity arrays owned by the score runtime.
ScoreRuntimeState* ScoreRuntimeState_Initialize(ScoreRuntimeState* state) {
    Entity_Constructor(&state->primaryEntity);
    Entity_Constructor(&state->secondaryEntity);
    for (int index = 0; index != 8; ++index)
        Entity_Constructor(&state->stageEntities[index]);
    for (int index = 0; index != 5; ++index)
        Entity_Constructor(&state->effectEntities[index]);
    state->flags &= ~1u;
    return state;
}

// 0x004089C0 - Build and register the score runtime's three callbacks.
int ScoreRuntimeCallbacks_Initialize(
        ScoreRuntimeCallbacks* callbacks, void* scheduler_device,
        SchedulerFunction primary_function,
        SchedulerFunction secondary_function,
        SchedulerFunction tertiary_function) {
    callbacks->primary = Scheduler_CreateAndRegister(
        primary_function, 0, scheduler_device);
    callbacks->secondary = Scheduler_CreateAndRegister(
        secondary_function, 0, scheduler_device);
    callbacks->tertiary = Scheduler_CreateAndRegister(
        tertiary_function, 0, scheduler_device);
    return callbacks->primary != 0 && callbacks->secondary != 0 &&
           callbacks->tertiary != 0;
}

void PlayerScoreRuntime_SetBindings(
        const PlayerScoreRuntimeBindings* bindings) {
    if (bindings != 0)
        g_player_score_bindings = *bindings;
    else {
        PlayerScoreRuntimeBindings empty;
        std::memset(&empty, 0, sizeof(empty));
        g_player_score_bindings = empty;
    }
}

// 0x004089C0 - Register the three player/score callbacks and initialize the
// trailing frame timer at +0x3734.
int PlayerScoreRuntime_Initialize(void* state) {
    if (state == 0 || DAT_00491be4 == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)state;
    SchedulerCallback* primary =
        SchedulerCallback_Create(PlayerScore_Update);
    if (primary == 0)
        return -1;
    primary->flags &= ~2u;
    primary->owner = state;
    Scheduler_RegisterPrimary(primary, 0, (void*)(unsigned long)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = primary;

    SchedulerCallback* secondary =
        SchedulerCallback_Create(PlayerScore_ReleasePrimary);
    if (secondary == 0) {
        Scheduler_Remove(primary, (void*)(unsigned long)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    secondary->flags &= ~2u;
    secondary->owner = state;
    Scheduler_RegisterSecondary(secondary, 0, (void*)(unsigned long)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = secondary;

    SchedulerCallback* tertiary =
        SchedulerCallback_Create(PlayerScore_ReleaseArrays);
    if (tertiary == 0) {
        Scheduler_Remove(primary, (void*)(unsigned long)DAT_00491be4);
        Scheduler_Remove(secondary, (void*)(unsigned long)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        *(SchedulerCallback**)(bytes + 12) = 0;
        return -1;
    }
    tertiary->flags &= ~2u;
    tertiary->owner = state;
    Scheduler_RegisterSecondary(tertiary, 0, (void*)(unsigned long)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 0x37AC) = tertiary;

    unsigned int* flags = (unsigned int*)(bytes + 0x3744);
    if ((*flags & 1u) == 0) {
        *(int*)(bytes + 0x3738) = 0;
        *(int*)(bytes + 0x3734) = (int)0xFFF0BDC1u;
        *(int*)(bytes + 0x373C) = 0;
        *(unsigned int*)(bytes + 0x3740) =
            (unsigned int)(unsigned long)&DAT_00476f78;
        *flags |= 1u;
    }
    *(int*)(bytes + 0x3738) = 0;
    *(int*)(bytes + 0x373C) = 0;
    *(int*)(bytes + 0x3734) = -1;
    return 0;
}

// 0x004086B0 - Report whether two axis-aligned extents are disjoint.
bool OutsideAxisAlignedBounds(float center_x, float center_y,
                              float offset_x, float offset_y,
                              float half_width, float half_height) {
    return (center_x + offset_x > half_width ||
            center_x - offset_x > half_width ||
            center_y + offset_y > half_height ||
            center_y - offset_y > half_height);
}

// 0x0040ACE0 - Test a query against both held and newly-pressed input masks.
#ifdef _MSC_VER
__declspec(naked) bool InputMaskActive(uint16_t held_mask,
                                       uint16_t pressed_mask,
                                       uint16_t query_mask) {
    __asm {
        xor edx, edx
        mov dx, [ecx+6]
        and edx, eax
        test dx, dx
        jnz loc_40ACFB
        movzx ecx, word ptr [ecx+4]
        and ecx, eax
        test cx, cx
        jnz loc_40ACFB
        xor eax, eax
        ret
loc_40ACFB:
        mov eax, 1
        ret
    }
}
#else
bool InputMaskActive(uint16_t held_mask, uint16_t pressed_mask,
                     uint16_t query_mask) {
    return (held_mask & query_mask) != 0 ||
           (pressed_mask & query_mask) != 0;
}
#endif

// 0x0044A4E0 - Encode the low 32 joystick button bits into the engine's
// byte-per-button input buffer. Pressed buttons use the retail 0x80 marker.
void Input_EncodeJoystickButtons(uint32_t buttons,
                                 unsigned char* destination) {
    for (unsigned int index = 0; index != 32; ++index) {
        destination[index] = (buttons & (1u << index)) != 0 ? 0x80 : 0;
    }
}

// 0x0044B010 - Clear the 256-byte keyboard buffer and acquire a fresh state
// through either the platform keyboard provider or the active input device.
int Input_UpdateKeyboardState(unsigned char* destination, bool inputEnabled,
                              bool directInputMode,
                              int (*pollKeyboard)(unsigned char*)) {
    for (unsigned int index = 0; index != 256; ++index)
        destination[index] = 0;
    if (!inputEnabled)
        return 0;
    if (directInputMode) {
        if (pollKeyboard != 0)
            pollKeyboard(destination);
        return 1;
    }
    return pollKeyboard != 0 ? pollKeyboard(destination) : 0;
}

// 0x0044B080 - Strip the transient high bit from every keyboard-state byte
// and publish the normalized 256-byte state.
void Input_NormalizeKeyboardState(
    unsigned char* state, int (*getState)(unsigned char*),
    int (*setState)(const unsigned char*)) {
    if (getState != 0)
        getState(state);
    for (unsigned int index = 0; index != 256; ++index)
        state[index] &= 0x7F;
    if (setState != 0)
        setState(state);
}

// 0x0044BE70 - Pop one input-history entry and restore its paired state
// values. The history index clamps at zero rather than wrapping.
#ifdef _MSC_VER
__declspec(naked) void Score_InputHistoryStep(void* state) {
    __asm {
        dec dword ptr [eax+8Ch]
        mov edx, 0
        jns loc_44BE83
        mov [eax+8Ch], edx
loc_44BE83:
        mov ecx, [eax+8Ch]
        push esi
        mov esi, [eax+ecx*4+0Ch]
        mov [eax], esi
        mov ecx, [eax+ecx*4+4Ch]
        mov [eax+8], ecx
        mov [eax+0D4h], edx
        pop esi
        ret
    }
}
#else
void Score_InputHistoryStep(void* state) {
    unsigned char* bytes = (unsigned char*)state;
    uint32_t index = *(uint32_t*)(bytes + 0x8C);
    if (index != 0)
        --index;
    *(uint32_t*)(bytes + 0x8C) = index;
    *(uint32_t*)bytes = *(uint32_t*)(bytes + 12 + index * 4);
    *(uint32_t*)(bytes + 8) =
        *(uint32_t*)(bytes + 0x4C + index * 4);
    *(uint32_t*)(bytes + 0xD4) = 0;
}
#endif

// 0x0044BE20 - Save the current input pair into the bounded history ring.
#ifdef _MSC_VER
__declspec(naked) void Score_InputHistorySave(void* state) {
    __asm {
        mov ecx, [eax+8Ch]
        mov edx, [eax]
        mov [eax+ecx*4+0Ch], edx
        mov ecx, [eax+8Ch]
        mov edx, [eax+8]
        mov [eax+ecx*4+4Ch], edx
        mov edx, [eax+8Ch]
        inc edx
        mov ecx, edx
        cmp ecx, 10h
        mov [eax+8Ch], edx
        mov dword ptr [eax+0D4h], 0
        jl locret_44BE61
        mov dword ptr [eax+8Ch], 0Fh
locret_44BE61:
        ret
    }
}
#else
void Score_InputHistorySave(void* state) {
    unsigned char* bytes = (unsigned char*)state;
    uint32_t index = *(uint32_t*)(bytes + 0x8C);
    *(uint32_t*)(bytes + 12 + index * 4) = *(uint32_t*)bytes;
    *(uint32_t*)(bytes + 0x4C + index * 4) = *(uint32_t*)(bytes + 8);
    ++index;
    if (index > 0xF)
        index = 0xF;
    *(uint32_t*)(bytes + 0x8C) = index;
    *(uint32_t*)(bytes + 0xD4) = 0;
}
#endif

// 0x004088C0 - Count occurrences of a byte in each fixed-width pattern.
unsigned int CountPatternMatches(const unsigned char* table,
                                 unsigned int groups, unsigned int stride,
                                 unsigned int width, unsigned char query) {
    unsigned int matches = 0;
    for (unsigned int group = 0; group != groups; ++group) {
        const unsigned char* pattern = table + group * stride;
        for (unsigned int index = 0; index != width; ++index)
            if (pattern[index] == query)
                ++matches;
    }
    return matches;
}

// 0x0040AC20 - Advance per-button repeat counters and derive edge masks.
void UpdateInputState(void* input_state) {
    unsigned char* bytes = (unsigned char*)input_state;
    unsigned short held = *(unsigned short*)(bytes + 0x2c);
    *(unsigned short*)(bytes + 4) = 0;
    unsigned short* repeat = (unsigned short*)(bytes + 0x38);
    for (int index = 0; index != 16; ++index) {
        if ((held & 1) == 0) {
            repeat[index] = 0;
        } else if (++repeat[index] > 0x19) {
            *(unsigned short*)(bytes + 0x30) |= 1;
            repeat[index] -= 8;
        }
        held >>= 1;
    }
    held = *(unsigned short*)(bytes + 0x2c);
    unsigned short changed = *(unsigned short*)(bytes + 0x2e) ^ held;
    *(unsigned short*)(bytes + 0x32) = changed & held;
    *(unsigned short*)(bytes + 0x34) = (unsigned short)(~held & changed);
}

// 0x0040AD20 - Update a bounded counter while preserving unsigned wrap rules.
unsigned int UpdateBoundedCounter(unsigned int requested,
                                  unsigned int* current_limit) {
    unsigned int limit = current_limit[2];
    if (limit == 0) {
        *current_limit = requested;
        return requested;
    }
    if ((int)limit <= (int)requested) {
        *current_limit = limit - 1;
        return limit - 1;
    }
    unsigned int value = ((int)requested < 0) ? 0xFFFFFFFFu : requested;
    *current_limit = value;
    return value;
}

// 0x0040AC90 - Store the requested input mode, honoring the forced-mode bit.
#ifdef _MSC_VER
__declspec(naked) void SetInputMode(void* input_state,
                                    unsigned int requested_mode) {
    __asm {
        mov ecx, [eax+3CCh]
        test ch, 10h
        jnz loc_40ACA8
        mov ecx, [esp+4]
        mov [eax+390h], ecx
        ret 4
loc_40ACA8:
        mov dword ptr [eax+390h], 2
        ret 4
    }
}
#else
void SetInputMode(void* input_state, unsigned int requested_mode) {
    unsigned char* bytes = (unsigned char*)input_state;
    if ((*(unsigned int*)(bytes + 0x3cc) & 0x1000) == 0)
        *(unsigned int*)(bytes + 0x390) = requested_mode;
    else
        *(unsigned int*)(bytes + 0x390) = 2;
}
#endif

// 0x00408750 - Convert polar input to a two-component score vector.
void Score_SetPolarVector(float* destination, float angle, float magnitude) {
    destination[0] = cosf(angle) * magnitude;
    destination[1] = sinf(angle) * magnitude;
}

// 0x0041BEB0 - Construct the same two-component vector used by score
// rendering from an angle and radius.
void Score_VectorFromPolar(float* destination, float angle, float magnitude) {
    destination[0] = cosf(angle) * magnitude;
    destination[1] = sinf(angle) * magnitude;
}

// 0x0041C030 - Initialize the score object's scheduler links and clear its
// 0x424-byte state block. The retail constructor intentionally restores the
// sentinel link fields after the bulk clear.
void* ScoreObject_Initialize(void*, void* object) {
    unsigned char* bytes = (unsigned char*)object;
    *(void**)bytes = PTR_LAB_0046dab0;
    *(uint32_t*)(bytes + 0x20) &= ~1u;
    for (unsigned int offset = 0x68; offset != 0x68 + 0x12 * 0x34;
         offset += 0x34)
        *(uint32_t*)(bytes + offset) &= ~1u;
    *(uint32_t*)(bytes + 0x420) &= ~1u;
    for (unsigned int offset = 0; offset != 0x424; offset += 4)
        *(uint32_t*)(bytes + offset) = 0;
    uint32_t flags = *(uint32_t*)(bytes + 0x20);
    if ((flags & 1u) == 0) {
        *(uint32_t*)(bytes + 0x14) = 0;
        *(uint32_t*)(bytes + 0x10) = 0xFFF0BDC1;
        *(uint32_t*)(bytes + 0x18) = 0;
        *(uint32_t*)(bytes + 0x1C) =
            (uint32_t)(unsigned long)&DAT_00476f78;
        *(uint32_t*)(bytes + 0x20) = flags | 1u;
    }
    *(uint32_t*)(bytes + 0x14) = 0;
    *(uint32_t*)(bytes + 0x18) = 0;
    *(uint32_t*)(bytes + 0x10) = 0xFFFFFFFF;
    return object;
}

// 0x0041C5B0 - Extend the score object constructor with the two embedded
// entity blocks and their construction sentinels.
void* ScoreExtendedObject_Initialize(void* unused, void* object) {
    ScoreObject_Initialize(unused, object);
    unsigned char* bytes = (unsigned char*)object;
    *(void**)bytes = PTR_LAB_0046da60;
    for (unsigned int offset = 0x424; offset != 0x424 + 0x77 * 4;
         offset += 4)
        *(uint32_t*)(bytes + offset) = 0;
    const unsigned int flags[] = {
        0x66C, 0x6B0, 0x6FC, 0x728, 0x774, 0x7B0, 0x7FC, 0x828,
        0x978, 0xA18, 0xA5C, 0xAA8, 0xAD4, 0xB20, 0xB5C, 0xBA8,
        0xBD4, 0xD24
    };
    for (unsigned int index = 0; index != sizeof(flags) / sizeof(flags[0]);
         ++index)
        *(uint32_t*)(bytes + flags[index]) &= ~1u;
    for (unsigned int offset = 0x600; offset != 0x600 + 0xEB * 4;
         offset += 4)
        *(uint32_t*)(bytes + offset) = 0;
    *(uint16_t*)(bytes + 0x984) = 0xFFFF;
    for (unsigned int offset = 0x9AC; offset != 0x9AC + 0xEB * 4;
         offset += 4)
        *(uint32_t*)(bytes + offset) = 0;
    *(uint16_t*)(bytes + 0xD30) = 0xFFFF;
    return object;
}

// 0x0041C1C0 - Retire the two scheduler-owned callbacks and drain the
// score object's owned-record chain. The callback hook is explicit here so
// host tests can model the scheduler critical-section boundary.
void ScoreExtendedObject_Destroy(void* object,
                                 void (*retireCallback)(void*)) {
    unsigned char* bytes = (unsigned char*)object;
    if (*(void**)(bytes + 8) != 0 && retireCallback != 0)
        retireCallback(*(void**)(bytes + 8));
    if (*(void**)(bytes + 12) != 0 && retireCallback != 0)
        retireCallback(*(void**)(bytes + 12));
    ScoreOwnedRecord* record = *(ScoreOwnedRecord**)(bytes + 0x18);
    while (record != 0) {
        ScoreOwnedRecord* next = record->next;
        if (record->cleanup != 0)
            record->cleanup(record->object);
        _free(record);
        record = next;
    }
    *(void**)(bytes + 0x18) = 0;
}

// 0x00408030 - Advance the score-state activation transition after its
// geometry query. The query and stage-spawn hooks are explicit so this leaf
// can be tested without the global renderer/game-state managers.
int ScoreState_ActivateFromResult(void* state, int geometryResult,
                                  int stageIndex, void (*spawn)(void*)) {
    unsigned char* bytes = (unsigned char*)state;
    uint16_t phase = *(uint16_t*)(bytes + 0x446);
    if (phase != 1 && phase != 2)
        return 0;
    *(uint16_t*)(bytes + 0x30C) = 1;
    *(uint16_t*)(bytes + 0x446) = 3;
    if (geometryResult != 0) {
        *(uint32_t*)bytes |= 8u;
        return 1;
    }
    if (stageIndex >= 0 && spawn != 0)
        spawn(state);
    if ((*(uint32_t*)(bytes + 0x408) & 1u) == 0) {
        *(uint32_t*)(bytes + 0x3FC) = 0;
        *(uint32_t*)(bytes + 0x3F8) = 0xFFF0BDC1;
        *(uint32_t*)(bytes + 0x400) = 0;
        *(uint32_t*)(bytes + 0x404) =
            (uint32_t)(unsigned long)&DAT_00476f78;
        *(uint32_t*)(bytes + 0x408) |= 1u;
    }
    *(uint32_t*)(bytes + 0x3FC) = 0;
    *(uint32_t*)(bytes + 0x400) = 0;
    *(uint32_t*)(bytes + 0x3F8) = 0xFFFFFFFF;
    return 1;
}

// 0x0041C7D0 - Mark non-terminal linked records for deferred removal.
void ScoreRecords_MarkEligible(ScoreLinkedRecord* first) {
    for (ScoreLinkedRecord* record = first; record != 0;
         record = record->next) {
        if (record->type != 1 && record->marked == 0)
            record->marked = 1;
    }
}

// 0x0041C800 - Copy a vector and accumulate linked-record callback results.
int ScoreRecords_CopyVectorAndEvaluate(
        ScoreLinkedRecord* first, float* destination, const float* vector) {
    destination[0] = vector[0];
    destination[1] = vector[1];
    destination[2] = vector[2];
    int result = 0;
    for (ScoreLinkedRecord* record = first; record != 0;
         record = record->next) {
        if (record->type != 1 && record->Evaluate != 0)
            result += record->Evaluate(record);
    }
    return result;
}

#ifdef _MSC_VER
__declspec(naked) void ScoreCounter::AddScaled(int32_t amount) {
    __asm {
        mov eax, 66666667h
        imul dword ptr [esp+4]
        sar edx, 2
        mov eax, edx
        shr eax, 1Fh
        add eax, edx
        mov edx, [ecx+0Ch]
        add edx, eax
        mov eax, edx
        cmp eax, 1869Fh
        mov [ecx+0Ch], edx
        jle locret_41BEAB
        mov dword ptr [ecx+0Ch], 1869Fh
locret_41BEAB:
        ret 4
    }
}
#else
void ScoreCounter::AddScaled(int32_t amount) {
    value += amount / 10;
    if (value > 99999) {
        value = 99999;
    }
}
#endif

// 0x00409D90 - Add one tenth of an award to the current run score.
void GameScore::AddScaled(int32_t amount) {
    value += amount / 10;
    if (value >= 1000000000) {
        value = 999999999;
    }
}

// 0x00412E70 - Add a tenth of the award to the global gauge at +0x0C and
// clamp the result to a minimum of 5000 so the gauge never empties below
// the retail baseline. The retail entry receives the gauge pointer through
// EAX, but the only field it touches is the integer at +0x0C.
#ifdef _MSC_VER
__declspec(naked) void ScoreGauge_AddWithMinimum(void* gauge, int award) {
    __asm {
        mov eax, 99999999h
        imul dword ptr [esp+4]
        sar edx, 2
        mov eax, edx
        shr eax, 1Fh
        add eax, edx
        mov edx, [ecx+0Ch]
        add edx, eax
        mov eax, edx
        cmp eax, 1388h
        mov [ecx+0Ch], edx
        jge locret_412E9B
        mov dword ptr [ecx+0Ch], 1388h
locret_412E9B:
        ret 4
    }
}
#else
void ScoreGauge_AddWithMinimum(void* gauge, int award) {
    int* field = (int*)((uint8_t*)gauge + 0x0C);
    *field += award / 10;
    if (*field < 5000) {
        *field = 5000;
    }
}
#endif

// 0x0041F7A0 / 0x00428D70 - Test a position with a radius against the play
// area, returning 0 when the point is at least partially in the viewport and
// 1 when every edge is off-screen. The two retail entries are byte-identical
// and use the supplied radii directly without the existing bounds' half-size
// multiplier. Callers chain two checks to early-exit when both source and
// target positions are off-screen.
extern float DAT_00470b04;
extern float DAT_00470b38;
extern float DAT_00470b3c;
extern float DAT_00470b40;

int Position_IsPartiallyInViewport(const void* center, float radius_x,
                                    float radius_y) {
    const float* position = static_cast<const float*>(center);
    const float right = position[0] + radius_x;
    const float left = position[0] - radius_x;
    const float top = position[1] + radius_y;
    const float bottom = position[1] - radius_y;
    if (right < DAT_00470b40) return 1;
    if (left > DAT_00470b3c) return 1;
    if (top < DAT_00470b04) return 1;
    if (bottom > DAT_00470b38) return 1;
    return 0;
}

// 0x00409E20 - Request removal of both registered runtime callbacks.
#ifdef _MSC_VER
__declspec(naked) void ScoreRuntimeCallbacks::Retire() {
    __asm {
        mov ecx, [eax+8]
        test ecx, ecx
        mov edx, 2
        jz loc_409E2F
        or [ecx+4], edx
loc_409E2F:
        mov ecx, [eax+0Ch]
        test ecx, ecx
        jz locret_409E3B
        mov eax, ecx
        or [eax+4], edx
locret_409E3B:
        ret
    }
}
#else
void ScoreRuntimeCallbacks::Retire() {
    if (primary != 0) {
        primary->flags |= 2;
    }
    if (secondary != 0) {
        secondary->flags |= 2;
    }
    if (tertiary != 0) {
        tertiary->flags |= 2;
    }
}
#endif

// 0x00409230 - Release the runtime's first two entities during teardown.
int ScoreRuntimeState::ReleaseFlaggedEntities(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    if ((flags & 1) != 0) {
        releaseEntity(entityManager, &primaryEntity);
        releaseEntity(entityManager, &secondaryEntity);
    }
    return 1;
}

// 0x004091C0 - Release the two trailing entity arrays while this runtime's
// release flag is set. The retail function receives this object through EBX
// and each Entity argument through EAX, which the raw decompiler omits.
int ScoreRuntimeState::ReleaseFlaggedEntityArrays(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    if ((flags & 1) != 0) {
        for (int index = 0; index != 8; ++index) {
            releaseEntity(entityManager, &stageEntities[index]);
        }
        for (int index = 0; index != 5; ++index) {
            releaseEntity(entityManager, &effectEntities[index]);
        }
    }
    return 1;
}

// 0x00409270 - Secondary scheduler callback wrapper. Retail preserves the
// callback owner in EBX before entering the shared array-release routine.
#ifdef _MSC_VER
__declspec(naked) int ScoreRuntimeState::RunArrayReleaseCallback(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    __asm {
        push ebx
        mov ebx, ecx
        call sub_4091C0
        pop ebx
        ret
    }
}
#else
int ScoreRuntimeState::RunArrayReleaseCallback(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    return ReleaseFlaggedEntityArrays(releaseEntity, entityManager);
}
#endif
