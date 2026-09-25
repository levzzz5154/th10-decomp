#include <cstring>

struct Entity;

struct BulletEntitySlot_00405cc0 {
    unsigned char state[0x7F0];
};

struct BulletPool_00405cc0 {
    unsigned char header[0x60];
    BulletEntitySlot_00405cc0 entities[0x7D1];
    void* animation_resource;
};

typedef char BulletPool_00405cc0_size_check[
    sizeof(BulletPool_00405cc0) == 0x3E0B54 ? 1 : -1];

extern "C" unsigned char* __fastcall Entity_ResetRuntimeState_00405D00(
    unsigned char* entity);
void __fastcall EntitySecondaryResource_Release(Entity* entity);
extern "C" void __cdecl asm_eh_vector_constructor_iterator_0045252d();
extern "C" BulletPool_00405cc0* data_004776f0;

namespace {

typedef void (__fastcall *EntityCallback)(void* entity);
typedef void (__stdcall *ConstructEntityArray)(
    void* first, unsigned int element_size, int count,
    EntityCallback constructor, EntityCallback destructor);

} // namespace

// Retail 0x00405CC0..0x00405CF2 receives the pool in ESI. The vector
// constructor runs before the full pool clear, so keep that order.
extern "C" BulletPool_00405cc0* __cdecl BulletPool_ConstructAndClear_00405cc0(
    BulletPool_00405cc0* pool) {
    const ConstructEntityArray construct_entities =
        reinterpret_cast<ConstructEntityArray>(
            &asm_eh_vector_constructor_iterator_0045252d);
    construct_entities(
        pool->entities, sizeof(BulletEntitySlot_00405cc0), 0x7D1,
        reinterpret_cast<EntityCallback>(&Entity_ResetRuntimeState_00405D00),
        reinterpret_cast<EntityCallback>(&EntitySecondaryResource_Release));

    std::memset(pool, 0, sizeof(*pool));
    data_004776f0 = pool;
    return pool;
}
