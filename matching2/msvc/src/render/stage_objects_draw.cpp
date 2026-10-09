// 0x00403090: cull one stage background object against the camera.
// 0x00403A30: draw every instance of the stage objects in one layer.
//
// The cull takes the object in ECX, the instance position in EDX and the
// camera in EAX, and the draw calls the camera apply, the batch flush and the
// entity dispatch on their whole-program registers, so both are compiled in
// the cluster layout/ltcg/anm_batch_flush_00442f50.json.
#include "th10/render/stage_objects.hpp"

#pragma code_seg(".text$000q1cull")
int StageObject::IsOutsideView(const StageVector* offset, const RenderCamera* camera,
                               float max_distance_squared) const {
    StageVector projected[8];
    StageVector corners[8];
    // The distance test borrows the first corner as its scratch vector.
    corners[0] = center + *offset;
    StageVector eye(camera->eye_offset.x + camera->position.x,
                    camera->eye_offset.y + camera->position.y,
                    camera->eye_offset.z + camera->position.z);
    corners[0] = corners[0] - eye;
    if (corners[0].x * corners[0].x + corners[0].y * corners[0].y + corners[0].z * corners[0].z >
        max_distance_squared) return 1;

    CameraMatrix world;
    StageVector half;
    half = size * 0.5f;
    corners[0].x = half.x + center.x; corners[0].y = half.y + center.y; corners[0].z = half.z + center.z;
    corners[1].x = half.x + center.x; corners[1].y = half.y + center.y; corners[1].z = center.z - half.z;
    corners[2].x = half.x + center.x; corners[2].y = center.y - half.y; corners[2].z = half.z + center.z;
    corners[3].x = half.x + center.x; corners[3].y = center.y - half.y; corners[3].z = center.z - half.z;
    corners[4].x = center.x - half.x; corners[4].y = half.y + center.y; corners[4].z = half.z + center.z;
    corners[5].x = center.x - half.x; corners[5].y = half.y + center.y; corners[5].z = center.z - half.z;
    corners[6].x = center.x - half.x; corners[6].y = center.y - half.y; corners[6].z = half.z + center.z;
    corners[7].x = center.x - half.x; corners[7].y = center.y - half.y; corners[7].z = center.z - half.z;

    WorldIdentity(&world);
    D3DXMatrixTranslation(&world, offset->x, offset->y, offset->z);
    D3DXVec3ProjectArray(projected, sizeof(StageVector), corners, sizeof(StageVector),
                         &camera->viewport_x, &camera->projection, &camera->view, &world, 8);

    // Bounds of the corners that project in front of the camera, starting
    // from an empty box inside the playfield.
    float min_x = 424.0f;
    float max_x = 24.0f;
    float min_y = 472.0f;
    float max_y = 8.0f;
    for (int i = 0; i < 8; ++i) {
        if (projected[i].z >= 0.0f && projected[i].z <= 1.0f) {
            if (projected[i].x < min_x) min_x = projected[i].x;
            else if (projected[i].x > max_x) max_x = projected[i].x;
            if (projected[i].y < min_y) min_y = projected[i].y;
            else if (projected[i].y > max_y) max_y = projected[i].y;
        }
    }
    if (max_x >= 32.0f && min_x <= 416.0f && max_y >= 16.0f && min_y <= 464.0f) return 0;
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$000q3draw")
int __stdcall StageObjects_DrawLayer(StageObjects* stage, int layer) {
    StageInstance* instance = stage->instances;
    data_00491c28.SelectStage(0);
    data_00491c10->cached_unknown_6c = 1;
    for (; instance->object >= 0; ++instance) {
        StageObject* object = stage->objects[instance->object];
        if (object->layer != layer) continue;
        // Copied by component; a whole-struct copy makes the compiler keep a
        // second pointer into the instance list.
        StageVector position;
        position.x = instance->position.x;
        position.y = instance->position.y;
        position.z = instance->position.z;
        if (object->IsOutsideView(&position, &data_00491c28.stages[0].camera,
                                  stage->max_distance_squared)) {
            ++stage->culled_objects;
            continue;
        }
        object->flags |= 2;
        for (StageQuad* quad = object->quads; quad->type >= 0;
             quad = reinterpret_cast<StageQuad*>(reinterpret_cast<char*>(quad) + quad->size)) {
            RenderEntity* entity = &stage->entities[quad->entity];
            if (quad->type != 0) continue;
            if ((entity->flags & 0x03C00000) >= 0x01000000) {
                entity->position.x = quad->position.x + instance->position.x;
                entity->position.y = quad->position.y + instance->position.y;
                entity->position.z = quad->position.z + instance->position.z;
                if (quad->width != 0.0f) {
                    entity->scale_x = quad->width / reinterpret_cast<StageSprite*>(entity->texture)->width;
                    entity->flags |= 8;
                }
                if (quad->height != 0.0f) {
                    entity->scale_y = quad->height / reinterpret_cast<StageSprite*>(entity->texture)->height;
                    entity->flags |= 8;
                }
            }
            if ((entity->flags & 0x03C00000) == 0x02000000) StageSetFog(1);
            else StageSetFog(0);
            asm_FUN_004451c0_004451c0(data_00491c10, entity);
            ++stage->drawn_quads;
        }
        ++stage->drawn_objects;
    }
    return 0;
}
#pragma code_seg()
