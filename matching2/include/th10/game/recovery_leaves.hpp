#pragma once

#include "th10/math/vector.hpp"

typedef unsigned char RecoveryByte;
typedef unsigned int RecoveryWord;

struct RecoveryListNode {
    RecoveryListNode* previous;
    RecoveryListNode* next;
};

// Lookup a UTF-16-style, null-terminated name in an array of entries whose
// value is stored immediately after the name pointer.
unsigned long Recovery_FindNamedValue(const unsigned short* name,
                                      const void* entries, int count);

struct RecoveryTimerState {
    RecoveryWord value;
    RecoveryWord current;
    RecoveryWord previous;
    const void* speed;
    RecoveryWord initialized;
};

struct RecoveryInterfaceArray {
    void** entries;
    RecoveryWord count;
};

struct RecoveryCleanupNode {
    RecoveryCleanupNode* previous;
    RecoveryCleanupNode* next;
    void (*cleanup)(RecoveryCleanupNode* node);
};

struct RecoveryAppendNode {
    RecoveryAppendNode* next;
    RecoveryAppendNode* previous;
};

struct RecoveryOwnedArrayState {
    void** entries;
    RecoveryWord count;
    void* auxiliary;
    RecoveryWord auxiliary_mode;
};

struct RecoveryStreamRecord {
    RecoveryWord offset;
    RecoveryWord length;
};

struct RecoveryStreamState {
    RecoveryWord kind;
    RecoveryWord memory_mode;
    RecoveryWord position;
    RecoveryWord cursor;
    RecoveryWord handle;
    RecoveryStreamRecord* record;
};

struct RecoveryOwnedLink {
    void* resource;
    RecoveryOwnedLink* next;
};

struct RecoveryTickState {
    RecoveryWord previous;
    RecoveryWord current;
    float elapsed;
    const float* speed;
};

struct RecoveryColorRecord {
    float channels[6];
    RecoveryByte random_channels[4];
};

struct RecoveryWordColorRecord {
    RecoveryWord channels[6];
    RecoveryByte random_channels[4];
};

void GameThread_RunQueueLeaf(void (*run)(void));
void* Bullet_DeletingDestructor(void* object, RecoveryByte flags,
                                void (*destroy)(void*), void (*free_memory)(void*));
void* Platform_DeletingDestructor(void* object, RecoveryByte flags,
                                  void (*destroy)(void*), void (*free_memory)(void*));
void Ecl_ForwardFloat(RecoveryByte opcode, float value,
                      void (*forward)(RecoveryByte, float));
void ScoreList_InsertAfter(RecoveryListNode* position, RecoveryListNode* node);
void Ecl_SetResourceSlot(void* state, int slot, int resource,
                         RecoveryWord first, RecoveryWord second);
void Animation_SetActiveCount(void* state, int count);
void RecoveryTimer_Reset(RecoveryTimerState* timer, const void* default_speed);
void Vector2_SetEllipticPolar(Vector2* destination, float angle,
                             float x_radius, float y_radius);
void Vector2_SetAnimationPolar(Vector2* destination, float angle, float length);
int PathState_Reset(void* state, RecoveryWord default_speed);
int Platform_InvokeConfigured(void* interface_owner,
                              int (*invoke)(void*, RecoveryWord, RecoveryWord));
RecoveryWord Platform_AggregateInterfaces(
    void** interfaces, RecoveryWord count,
    RecoveryWord (*first)(void*), RecoveryWord (*second)(void*, int));
void Score_SetMode(void* state, int mode);
void Score_SetNormalizedAngle(void* state, float angle);
RecoveryWord Platform_QueryInterfaces(
    const RecoveryInterfaceArray* array,
    RecoveryWord (*query)(void*, RecoveryWord));
void* Platform_FindAvailable(
    const RecoveryInterfaceArray* array, RecoveryWord initial_state,
    void (*read_state)(void*, RecoveryWord*),
    RecoveryWord (*random_index)(RecoveryWord));
void RecoveryLinkedCleanup(
    RecoveryCleanupNode** head, void (*free_memory)(void*));
extern void* g_recovery_global_state;
void* RecoveryState_Initialize(void* state);
void RecoveryState_Configure42300(void* state, const void* owner,
                                  RecoveryByte first, RecoveryByte second,
                                  RecoveryByte third, RecoveryWord speed);
void RecoveryState_Configure42220(void* state, const RecoveryByte first[3],
                                  const RecoveryByte second[3], RecoveryWord mode,
                                  RecoveryByte flags, RecoveryWord speed);
void RecoveryState_Configure41F50(void* state, RecoveryWord value,
                                  RecoveryWord mode, RecoveryByte first,
                                  RecoveryByte second, RecoveryWord speed);
RecoveryWord Recovery_InvokeZero(void (*invoke)(void));
void Recovery_InvokeVoid(void (*invoke)(void));
unsigned long long Recovery_InvokePair(
    void* argument, unsigned long long (*invoke)(void*));
void Recovery_AppendNode(RecoveryAppendNode* list, RecoveryAppendNode* node);
void Platform_ReleaseOwnedArray(
    RecoveryOwnedArrayState* state, void (*release)(void*),
    void (*close_auxiliary)(void*), void (*free_memory)(void*));
int Platform_RunInterface(void* interface_object, RecoveryWord* completed,
                          int (*begin)(void*), int (*poll)(void*),
                          void (*sleep_ms)(unsigned));
void* Platform_DeletingDestructorWithRelease(
    void* object, RecoveryByte flags, void (*release)(void*),
    void (*free_memory)(void*));
int Platform_SelectStreamRecord(
    RecoveryStreamState* state, RecoveryStreamRecord* record,
    RecoveryWord archive_base, void (*seek)(RecoveryWord));
void* Platform_DeletingDestructorVtable(
    void* object, RecoveryByte flags, void (*destroy)(void*),
    void (*free_memory)(void*));
int Platform_SetOperationDeadline(
    bool randomized, RecoveryWord (*random_value)(void*), void* random_state,
    void (*set_deadline)(int));
void Recovery_ClearEightBuckets(
    RecoveryOwnedLink buckets[8], RecoveryOwnedLink direct[8],
    void (*free_memory)(void*));
void Platform_ReleaseOwnedHandle(
    void* resource, void (*release)(void*), void (*free_memory)(void*));
int Recovery_TickState(RecoveryTickState* state, int (*update)(void*),
                       float stable_speed, RecoveryWord (*random_round)(void*),
                       void* random_state);
void Recovery_SwitchPlaybackState(void* state, bool secondary_active,
                                  void (*transition)(void*));
void Recovery_ScaleColor(const float source[6], RecoveryColorRecord* destination,
                         float scale, RecoveryWord (*random_byte)(void*),
                         void* random_state);
int Recovery_InstallPairSetFlags(
    void** first_slot, void** second_slot, void* first_resource,
    void* second_resource, void (*configure)(void*, RecoveryWord));
int Recovery_InstallPairClearFlags(
    void** first_slot, void** second_slot, void* first_resource,
    void* second_resource, void (*configure)(void*, RecoveryWord));
int Recovery_ReleasePair(void** first_slot, void** second_slot,
                         void (*release)(void*), void (*free_memory)(void*));
void* Recovery_InitializeLargeState(void* state,
                                     void (*initialize_subobject)(void*));
void Recovery_InitializeTimedState(void* state, void (*tick)(void),
                                   RecoveryWord* default_speed);
int Recovery_LoadStartupResources(
    void* context, void* (*load)(void*, int, const char*),
    void (*report_missing)(const char*));
int Recovery_InstallAnimationSlot(
    void* owner, int index, RecoveryWord resource,
    void* (*create)(void), void (*configure)(void*, int),
    void (*register_object)(void*),
    void (*store)(void*, int, RecoveryWord));
void Recovery_ClearAnimationSlot(
    RecoveryWord* slot, void* lookup_key,
    void* (*lookup)(void*, void*), void (*mark)(void*),
    void** children, RecoveryWord child_count);
void* Recovery_LoadCachedResource(
    void** slots, RecoveryWord count, int index, void* context,
    const char* name, void* (*load)(void*, int, const char*),
    RecoveryWord* loading, bool cancelled, void (*sleep_ms)(unsigned));
int Recovery_SelectArchiveEntry(
    bool available, void* request, void* archive,
    int (*find_index)(void*, void*),
    int (*select_record)(void*, RecoveryWord));
int Recovery_SplitResourcePath(char* destination, const char* source,
                               RecoveryWord capacity,
                               void (*reset)(void));
int Recovery_DispatchSchedule(
    int tick, const char* schedule, RecoveryWord schedule_count,
    void (*dispatch)(const char*, int));
void* Platform_DeletingDestructorNoReturn(
    void* object, void (*release)(void*), void (*free_memory)(void*));
void Recovery_ResetEmitter(
    int* count, void* emitter, void (*spawn)(void*, int, RecoveryWord,
                                             float, float),
    void (*reset)(void*));
void Recovery_InitializePlayerTimer(void* state, RecoveryWord speed,
                                    void (*configure)(RecoveryWord, RecoveryWord));
void Recovery_TrimWhitespace(char* text);
void* Recovery_InitializeStateTable(void* state);
int Recovery_ReplaceExtensionWav(void* context, char* path,
                                 void (*load)(void*, const char*));
void Recovery_InitializeWordColor(const RecoveryWord values[6],
                                  RecoveryWordColorRecord* destination,
                                  RecoveryWord (*random_byte)(void*),
                                  void* random_state);
void Recovery_ReleaseRawPair(void* state, void (*release)(void*),
                             void (*free_memory)(void*));
void Recovery_ReleaseRawPairAndReset(void* state, void (*release)(void*),
                                     void (*free_memory)(void*),
                                     RecoveryWord* global_flag);
extern void* g_recovery_small_state;
void* Recovery_CreateSmallState(
    void* (*allocate)(RecoveryWord), int (*initialize)(void*),
    void (*destroy)(void*), void (*free_memory)(void*));
void Recovery_InitializeInterfaceArray(
    RecoveryOwnedArrayState* state, void** source, RecoveryWord count,
    void* argument, RecoveryWord (*query)(void*, RecoveryWord));
void Recovery_InitializeSingleInterface(
    RecoveryInterfaceArray* state, void* entry, void* first_argument,
    void* second_argument, RecoveryWord (*query)(void*, RecoveryWord));
void Recovery_OffsetPoint(const float input[3], float output[3]);
void Recovery_DecayCounter(void* state, void (*reset)(float));
struct RecoveryPacketBuffer {
    unsigned char* begin;
    unsigned char* cursor;
    RecoveryWord limit;
};
bool Recovery_AppendPacket(RecoveryPacketBuffer* buffer, RecoveryWord first,
                           RecoveryWord second, RecoveryWord third);
void Recovery_InitializeRandomTable(void* state, RecoveryWord (*random_value)(void*),
                                    void* random_state);
void* Recovery_CreateTimerState(
    void* (*allocate)(RecoveryWord), int (*initialize)(void*),
    void (*destroy)(void*), void (*free_memory)(void*));
void Recovery_MarkAnimationTree(RecoveryWord* root_status,
                                RecoveryWord* child_status,
                                RecoveryWord child_count);
void* Recovery_CreateFixedState(
    RecoveryWord size, void* (*allocate)(RecoveryWord),
    int (*initialize)(void*), void (*destroy)(void*),
    void (*free_memory)(void*));
RecoveryWord Recovery_UpdateEmitterDecision(
    void* state, int (*tick)(void*), RecoveryWord flags,
    bool twelve_frame_mode);
void Recovery_IncrementAnimationCount(
    void* state, int delta, void (*reload)(void*));
int Recovery_CreateTextureFromMemory(
    void* state, int format, int mip_levels,
    int (*create)(void*, int, int), void (*finalize)(void*));
void Recovery_FlushRenderStaging(void* state, void (*flush)(void*),
                                 void (*advance)(void*));
void Recovery_MarkLogState(void* state, void (*write)(void*, const char*),
                           const char* text);
void* Recovery_CreateResourceState(
    RecoveryWord size, void* (*allocate)(RecoveryWord),
    int (*initialize)(void*), void (*destroy)(void*),
    void (*free_memory)(void*));
int Recovery_StartWorker(void* state, void (*start)(void*),
                         RecoveryWord* handle, RecoveryWord* thread_id);
void Recovery_ReleaseCompositeState(void* state, void (*release)(void*),
                                    void (*free_memory)(void*));
void Recovery_ReleaseGlobalStates(void** states, RecoveryWord count,
                                  void (*release)(void*),
                                  void (*free_memory)(void*));
int Recovery_DispatchRandomText(int count, void* context,
                                RecoveryWord (*random_value)(void*),
                                void (*dispatch)(void*, const RecoveryWord[4], int));
void* Recovery_CreateLargeResourceState(
    void* (*allocate)(RecoveryWord), int (*initialize)(void*),
    void (*destroy)(void*), void (*free_memory)(void*));
void* Recovery_CreateHugeResourceState(
    void* (*allocate)(RecoveryWord), int (*initialize)(void*),
    void (*destroy)(void*), void (*free_memory)(void*));
void Recovery_ResetDeviceStreams(void* device, void (*set_stream)(void*),
                                 int (*draw)(void*), void (*restore)(void*));
