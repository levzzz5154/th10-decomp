#include "th10/game/pause_result_open_004231d0/player/item_collision/item_collision.hpp"

struct ConfigureVector_00404f30 : Vector3 {
    ConfigureVector_00404f30(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }
};
#pragma code_seg(".text$00404f30_fn")
void ItemConfiguredEntity_00404f30::Configure(
    int index, ConfigureResource_00404f30 resource) {
    Entity* entity = this;
    Entity_Init(entity);
    entity->position = ConfigureVector_00404f30(0.0f, 0.0f, 0.0f);
    entity->base_position = ConfigureVector_00404f30(0.0f, 0.0f, 0.0f);
    entity->render_offset = ConfigureVector_00404f30(0.0f, 0.0f, 0.0f);
    reinterpret_cast<unsigned char*>(entity)[0x3A1] = 0x10;
    reinterpret_cast<unsigned char*>(entity)[0x3A0] = 0x10;
    entity->ScriptIndex() = static_cast<short>(index);
    MovementLoadScript_0043e710(resource.value, entity, index);
}
#pragma code_seg()
