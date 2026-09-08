#pragma once

#include <cstdio>

struct AnmVmState;

// Optional deterministic diagnostics for reconstruction-vs-retail probes. The
// emitter is deliberately host-local: it records stable IDs and script-relative
// offsets, never process addresses or wall-clock values.
struct HostTraceEmitter {
    struct VmIdentity {
        const void* address;
        int id;
        bool live;
    };

    std::FILE* file = nullptr;
    bool active = false;
    unsigned int sequence = 0;
    int frame = -1;
    bool frame_open = false;
    int next_frame = 0;
    int next_vm_id = 1;
    VmIdentity vm_ids[1024] = {};
    int vm_id_count = 0;

    static unsigned long long HashBytes(const unsigned char* bytes,
                                        unsigned int size);

    int VmId(const void* address) const;

    int NewVmId(const void* address);

    void RetireVmId(const void* address, int id);

    long long PcOffset(const AnmVmState* state, const unsigned char* pc) const;

    void BeginEvent(const char* type);

    void EndEvent();

    bool Open(const char* path);

    void Close();

    void Resource(const char* name, int resource_id,
                  const unsigned char* bytes, unsigned int size);

    void VmCreate(const void* address, const AnmVmState* state);

    void VmDestroy(const void* address, const char* reason);

    void Input(unsigned int held, unsigned int pressed, unsigned int menu);

    void VmTick(const void* address, const AnmVmState* state, int script_id,
                int resource_id, const unsigned char* before_pc, int ended);

    void Object(int handle, const void* vm_address);

    void ObjectDestroy(int handle, const char* reason);

    void Draw(const void* address, const AnmVmState* state, int script_id,
              int resource_id, int via_manager);

    void BeginFrame(int index);

    void EndFrame();

    void StageBegin(const char* script);

    void StagePhase(int stage_frame, const char* phase);

    void EclCreate(int vm_id, int parent_id, int async_id, int rank_mask,
                   long long pc_offset);

    void EclDestroy(int vm_id, int stage_frame, const char* reason);

    void EclOpcode(int vm_id, int stage_frame, int order, int opcode,
                   long long pc_offset, int instruction_time, int rank_mask);

    void EclTick(int vm_id, int stage_frame, int order, int async_id,
                 int rank_mask, long long pc_before, long long pc_after,
                 unsigned int time_before, int scratch_before, int scratch_top,
                 int result, int live);

    void Entity(int entity_id, int kind, int live, int stage_frame);

    void StageSpawn(int entity_id, int opcode, int manager_count,
                    int spawn_serial, float x, float y, float z);

    void StageDraw(int stage_frame, int placement_id, int vm_slot,
                   int sprite, float x, float y, float scale);

    void BulletLifecycle(int bullet_id, int stage_frame, int is_active, int row);

    void Bullet(int active_count, int updated_count, int stage_frame);

    void StageEnd(int stage_frame, int result);

    void Present(bool checksum_valid, unsigned long long checksum,
                 unsigned int width, unsigned int height);
};

