#include "host_trace.hpp"
#include "th10/script/anm_vm_tick.hpp"

unsigned long long HostTraceEmitter::HashBytes(const unsigned char* bytes,
                                        unsigned int size) {
    unsigned long long hash = 1469598103934665603ull;
    for (unsigned int index = 0; index < size; ++index) {
        hash ^= bytes[index];
        hash *= 1099511628211ull;
    }
    return hash;
}

int HostTraceEmitter::VmId(const void* address) const {
    if (address == nullptr)
        return 0;
    for (int index = vm_id_count - 1; index >= 0; --index)
        if (vm_ids[index].address == address && vm_ids[index].live)
            return vm_ids[index].id;
    return 0;
}

int HostTraceEmitter::NewVmId(const void* address) {
    if (!active || address == nullptr)
        return 0;
    if (vm_id_count >= static_cast<int>(sizeof(vm_ids) / sizeof(vm_ids[0])))
        return 0;
    const int id = next_vm_id++;
    vm_ids[vm_id_count++] = {address, id, true};
    return id;
}

void HostTraceEmitter::RetireVmId(const void* address, int id) {
    for (int index = vm_id_count - 1; index >= 0; --index) {
        if (vm_ids[index].address == address && vm_ids[index].id == id) {
            vm_ids[index].live = false;
            return;
        }
    }
}

long long HostTraceEmitter::PcOffset(const AnmVmState* state, const unsigned char* pc) const {
    if (state == nullptr || state->script_base == nullptr || pc == nullptr)
        return -1;
    return static_cast<long long>(pc - state->script_base);
}

void HostTraceEmitter::BeginEvent(const char* type) {
    if (!active)
        return;
    std::fprintf(file,
                 "{\"seq\":%u,\"type\":\"%s\",\"frame\":%d",
                 sequence++, type, frame);
}

void HostTraceEmitter::EndEvent() {
    if (!active)
        return;
    std::fputs("}\n", file);
    std::fflush(file);
}

bool HostTraceEmitter::Open(const char* path) {
    if (path == nullptr || *path == '\0')
        return false;
    file = std::fopen(path, "wb");
    if (file == nullptr)
        return false;
    active = true;
    sequence = 0;
    frame = -1;
    frame_open = false;
    next_frame = 0;
    next_vm_id = 1;
    vm_id_count = 0;
    BeginEvent("header");
    std::fputs(",\"schema\":1,\"format\":\"th10-recon-jsonl-v1\"",
               file);
    EndEvent();
    return true;
}

void HostTraceEmitter::Close() {
    if (file == nullptr)
        return;
    if (frame_open)
        EndFrame();
    std::fflush(file);
    std::fclose(file);
    file = nullptr;
    active = false;
}

void HostTraceEmitter::Resource(const char* name, int resource_id,
                  const unsigned char* bytes, unsigned int size) {
    if (!active)
        return;
    BeginEvent("resource");
    std::fprintf(file,
                 ",\"id\":%d,\"name\":\"%s\",\"size\":%u,\"hash\":\"%016llx\"",
                 resource_id, name != nullptr ? name : "", size,
                 HashBytes(bytes, size));
    EndEvent();
}

void HostTraceEmitter::VmCreate(const void* address, const AnmVmState* state) {
    if (!active)
        return;
    const int id = NewVmId(address);
    BeginEvent("vm_create");
    std::fprintf(file, ",\"vm\":%d,\"pc\":%lld",
                 id, PcOffset(state, state != nullptr ? state->pc : nullptr));
    EndEvent();
}

void HostTraceEmitter::VmDestroy(const void* address, const char* reason) {
    if (!active)
        return;
    const int id = VmId(address);
    BeginEvent("vm_destroy");
    std::fprintf(file, ",\"vm\":%d,\"reason\":\"%s\"",
                 id, reason != nullptr ? reason : "");
    EndEvent();
    RetireVmId(address, id);
}

void HostTraceEmitter::Input(unsigned int held, unsigned int pressed, unsigned int menu) {
    if (!active)
        return;
    BeginEvent("input");
    std::fprintf(file, ",\"held\":%u,\"pressed\":%u,\"menu\":%u",
                 held, pressed, menu);
    EndEvent();
}

void HostTraceEmitter::VmTick(const void* address, const AnmVmState* state, int script_id,
                int resource_id, const unsigned char* before_pc, int ended) {
    if (!active)
        return;
    const int id = VmId(address);
    BeginEvent("vm_tick");
    std::fprintf(
        file,
        ",\"vm\":%d,\"script\":%d,\"resource\":%d,\"pc_before\":%lld,\"pc_after\":%lld,\"time\":%d,\"sprite\":%d,\"flags\":%u,\"ended\":%d",
        id, script_id, resource_id, PcOffset(state, before_pc),
        PcOffset(state, state != nullptr ? state->pc : nullptr),
        state != nullptr ? state->time : 0,
        state != nullptr ? state->sprite : -1,
        state != nullptr ? state->flags : 0u, ended);
    EndEvent();
}

void HostTraceEmitter::Object(int handle, const void* vm_address) {
    if (!active)
        return;
    BeginEvent("object");
    std::fprintf(file, ",\"handle\":%d,\"vm\":%d",
                 handle, VmId(vm_address));
    EndEvent();
}

void HostTraceEmitter::ObjectDestroy(int handle, const char* reason) {
    if (!active)
        return;
    BeginEvent("object_destroy");
    std::fprintf(file, ",\"handle\":%d,\"reason\":\"%s\"",
                 handle, reason != nullptr ? reason : "");
    EndEvent();
}

void HostTraceEmitter::Draw(const void* address, const AnmVmState* state, int script_id,
              int resource_id, int via_manager) {
    if (!active || state == nullptr)
        return;
    BeginEvent("draw");
    std::fprintf(
        file,
        ",\"vm\":%d,\"script\":%d,\"resource\":%d,\"sprite\":%d,\"layer\":%d,\"x\":%.9g,\"y\":%.9g,\"rotation\":%.9g,\"manager\":%d",
        VmId(address), script_id, resource_id, state->sprite, state->layer,
        state->position[0], state->position[1], state->rotation[2],
        via_manager);
    EndEvent();
}

void HostTraceEmitter::BeginFrame(int index) {
    if (!active)
        return;
    if (frame_open)
        EndFrame();
    (void)index;
    frame = ++next_frame;
    frame_open = true;
    BeginEvent("frame_begin");
    EndEvent();
}

void HostTraceEmitter::EndFrame() {
    if (!active || !frame_open)
        return;
    BeginEvent("frame_end");
    EndEvent();
    frame_open = false;
}

void HostTraceEmitter::StageBegin(const char* script) {
    if (!active)
        return;
    BeginEvent("stage_begin");
    std::fprintf(file, ",\"script\":\"%s\"",
                 script != nullptr ? script : "");
    EndEvent();
}

void HostTraceEmitter::StagePhase(int stage_frame, const char* phase) {
    if (!active)
        return;
    BeginEvent("stage_phase");
    std::fprintf(file, ",\"stage_frame\":%d,\"phase\":\"%s\"",
                 stage_frame, phase != nullptr ? phase : "");
    EndEvent();
}

void HostTraceEmitter::EclCreate(int vm_id, int parent_id, int async_id, int rank_mask,
                   long long pc_offset) {
    if (!active)
        return;
    BeginEvent("ecl_vm_create");
    std::fprintf(file,
                 ",\"vm\":%d,\"parent\":%d,\"async_id\":%d,\"rank_mask\":%d,\"pc\":%lld",
                 vm_id, parent_id, async_id, rank_mask, pc_offset);
    EndEvent();
}

void HostTraceEmitter::EclDestroy(int vm_id, int stage_frame, const char* reason) {
    if (!active)
        return;
    BeginEvent("ecl_vm_destroy");
    std::fprintf(file, ",\"vm\":%d,\"stage_frame\":%d,\"reason\":\"%s\"",
                 vm_id, stage_frame, reason != nullptr ? reason : "");
    EndEvent();
}

void HostTraceEmitter::EclOpcode(int vm_id, int stage_frame, int order, int opcode,
                   long long pc_offset, int instruction_time, int rank_mask) {
    if (!active)
        return;
    BeginEvent("ecl_opcode");
    std::fprintf(file,
                 ",\"vm\":%d,\"stage_frame\":%d,\"order\":%d,\"opcode\":%d,\"pc\":%lld,\"time\":%d,\"rank_mask\":%d",
                 vm_id, stage_frame, order, opcode, pc_offset,
                 instruction_time, rank_mask);
    EndEvent();
}

void HostTraceEmitter::EclTick(int vm_id, int stage_frame, int order, int async_id,
                 int rank_mask, long long pc_before, long long pc_after,
                 unsigned int time_before, int scratch_before, int scratch_top,
                 int result, int live) {
    if (!active)
        return;
    BeginEvent("ecl_vm_tick");
    std::fprintf(
        file,
        ",\"vm\":%d,\"stage_frame\":%d,\"order\":%d,\"async_id\":%d,\"rank_mask\":%d,\"pc_before\":%lld,\"pc_after\":%lld,\"time_before\":%u,\"scratch_before\":%d,\"scratch_top\":%d,\"result\":%d,\"live\":%d",
        vm_id, stage_frame, order, async_id, rank_mask, pc_before,
        pc_after, time_before, scratch_before, scratch_top, result, live);
    EndEvent();
}

void HostTraceEmitter::Entity(int entity_id, int kind, int live, int stage_frame) {
    if (!active)
        return;
    BeginEvent("entity");
    std::fprintf(file, ",\"id\":%d,\"kind\":%d,\"stage_frame\":%d,\"live\":%d",
                 entity_id, kind, stage_frame, live);
    EndEvent();
}

void HostTraceEmitter::StageSpawn(int entity_id, int opcode, int manager_count,
                    int spawn_serial, float x, float y, float z) {
    if (!active)
        return;
    BeginEvent("stage_spawn");
    std::fprintf(file, ",\"entity\":%d,\"opcode\":%d,\"manager_count\":%d,\"spawn_serial\":%d,\"x\":%.6f,\"y\":%.6f,\"z\":%.6f",
                 entity_id, opcode, manager_count, spawn_serial, x, y, z);
    EndEvent();
}

void HostTraceEmitter::StageDraw(int stage_frame, int placement_id, int vm_slot,
                   int sprite, float x, float y, float scale) {
    if (!active)
        return;
    BeginEvent("stage_draw");
    std::fprintf(file, ",\"stage_frame\":%d,\"placement\":%d,\"vm_slot\":%d,\"sprite\":%d,\"x\":%.6f,\"y\":%.6f,\"scale\":%.6f",
                 stage_frame, placement_id, vm_slot, sprite, x, y, scale);
    EndEvent();
}

void HostTraceEmitter::BulletLifecycle(int bullet_id, int stage_frame, int is_active, int row) {
    if (!this->active)
        return;
    BeginEvent("bullet");
    std::fprintf(file, ",\"id\":%d,\"stage_frame\":%d,\"active\":%d,\"row\":%d",
                 bullet_id, stage_frame, is_active, row);
    EndEvent();
}

void HostTraceEmitter::Bullet(int active_count, int updated_count, int stage_frame) {
    if (!active)
        return;
    BeginEvent("bullet_summary");
    std::fprintf(file, ",\"stage_frame\":%d,\"active\":%d,\"updated\":%d",
                 stage_frame, active_count, updated_count);
    EndEvent();
}

void HostTraceEmitter::StageEnd(int stage_frame, int result) {
    if (!active)
        return;
    BeginEvent("stage_end");
    std::fprintf(file, ",\"stage_frame\":%d,\"result\":%d",
                 stage_frame, result);
    EndEvent();
}

void HostTraceEmitter::Present(bool checksum_valid, unsigned long long checksum,
                 unsigned int width, unsigned int height) {
    if (!active)
        return;
    BeginEvent("present");
    if (checksum_valid)
        std::fprintf(file, ",\"width\":%u,\"height\":%u,\"checksum\":\"%016llx\"",
                     width, height, checksum);
    else
        std::fputs(",\"width\":0,\"height\":0,\"checksum\":null",
                   file);
    EndEvent();
}
