#include <string.h>
#include "th10/game/entity.hpp"
static inline void ClearRegistration(unsigned* flags) { *flags &= ~1u; }
static inline Entity* ResetAnimation(Entity* entity) {
    ClearRegistration(&entity->flags_06C);
    ClearRegistration(&entity->flags_0B0);
    ClearRegistration(&entity->flags_0FC);
    ClearRegistration(&entity->flags_128);
    ClearRegistration(&entity->flags_174);
    ClearRegistration(&entity->flags_1B0);
    ClearRegistration(&entity->flags_1FC);
    ClearRegistration(&entity->flags_228);
    ClearRegistration(&entity->flags_378);
    memset(entity, 0, sizeof(Entity));
    entity->SpriteIndex() = -1;
    return entity;
}
struct RegistrationRecord_00405d00 {
    unsigned reserved_00[4];
    unsigned flags;
    unsigned reserved_14[8];
    __forceinline void Reset() { ClearRegistration(&flags); }
};
static inline void ResetNext(RegistrationRecord_00405d00*& record) {
    unsigned flags = record->flags;
    ++record;
    record[-1].flags = flags & ~1u;
}
struct EntityWrapper_00405d00 {
    unsigned header[2];
    Entity animation;
    unsigned char reserved_3b4[0x408-8-sizeof(Entity)];
    unsigned flags_408;
    unsigned char reserved_40c[0x10];
    unsigned flags_41c;
    unsigned char reserved_420[0x614-0x420];
    RegistrationRecord_00405d00 records[9];
    __declspec(noinline) __declspec(dllexport) EntityWrapper_00405d00* Reset();
};
typedef char RecordSize_00405d00[sizeof(RegistrationRecord_00405d00)==0x34?1:-1];
#pragma code_seg(".text$01reset")
EntityWrapper_00405d00* EntityWrapper_00405d00::Reset() {
    ResetAnimation(&animation);
    ClearRegistration(&flags_408);
    ClearRegistration(&flags_41c);
    RegistrationRecord_00405d00* r=records;
    ResetNext(r);
    ResetNext(r);
    ResetNext(r);
    ResetNext(r);
    r->Reset();
    (++r)->Reset();
    (++r)->Reset();
    (++r)->Reset();
    (++r)->Reset();
    return this;
}
#pragma code_seg()
