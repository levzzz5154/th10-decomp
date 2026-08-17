#include "th10/render/anm_sprite_quad.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>

int main() {
    AnmSpriteQuadInput input = {};
    input.center_x = 100.0f;
    input.center_y = 50.0f;
    input.center_z = 0.25f;
    input.width = 20.0f;
    input.height = 10.0f;
    input.flags = (1u << 18) | (2u << 20) | 0x8000u;
    input.primary_color = 0x11223344u;
    input.secondary_color = 0xAABBCCDDu;
    input.u0 = 0.1f;
    input.v0 = 0.2f;
    input.u1 = 0.5f;
    input.v1 = 0.7f;
    input.uv_scroll_x = 0.03f;
    input.uv_scroll_y = -0.02f;

    AnmSpriteQuadVertex quad[4];
    AnmSprite_BuildQuad(&input, quad);
    assert(AnmSprite_SelectedColor(&input) == 0xAABBCCDDu);
    assert(std::fabs(quad[0].x - 100.0f) < 1e-5f);
    assert(std::fabs(quad[0].y - 40.0f) < 1e-5f);
    assert(std::fabs(quad[3].x - 120.0f) < 1e-5f);
    assert(std::fabs(quad[3].y - 50.0f) < 1e-5f);
    assert(std::fabs(quad[0].u - 0.13f) < 1e-5f);
    assert(std::fabs(quad[3].v - 0.68f) < 1e-5f);
    assert(quad[0].z == 0.25f && quad[0].rhw == 1.0f);
    assert(input.rotation == 0.0f);

    input.rotation = 0.25f;
    AnmSprite_BuildQuad(&input, quad);
    assert(std::fabs(quad[0].x - 102.474f) < 1e-3f);
    assert(std::fabs(quad[0].y - 40.310f) < 1e-3f);

    AnmSpriteQuadVertex triangles[6];
    AnmSprite_ExpandTriangleList(quad, triangles);
    assert(&triangles[0] != &quad[0]);
    assert(triangles[0].x == quad[0].x && triangles[1].x == quad[1].x);
    assert(triangles[2].x == quad[2].x && triangles[3].x == quad[1].x);
    assert(triangles[4].x == quad[2].x && triangles[5].x == quad[3].x);

    float identity[16] = {};
    identity[0] = identity[5] = identity[10] = identity[15] = 1.0f;
    float viewport[4] = {0.0f, 0.0f, 100.0f, 100.0f};
    AnmSpriteProjectionContext projection = {
        identity, identity, viewport, {1.0f, 0.0f, 0.0f}};
    AnmSpriteQuadInput billboard = {};
    billboard.center_z = 0.5f;
    billboard.width = 2.0f;
    billboard.height = 2.0f;
    billboard.primary_color = 0xFFFFFFFFu;
    billboard.u1 = billboard.v1 = 1.0f;
    assert(AnmSprite_BuildProjectedBillboard(
               &billboard, &projection, quad) == 0);
    assert(std::fabs(quad[0].x - 24.999f) < 0.01f);
    assert(std::fabs(quad[0].y - 24.999f) < 0.01f);
    assert(std::fabs(quad[3].x - 75.001f) < 0.01f);
    assert(std::fabs(quad[3].y - 75.001f) < 0.01f);
    assert(quad[0].z == 0.5f && quad[3].z == 0.5f);
    billboard.center_z = 2.0f;
    assert(AnmSprite_BuildProjectedBillboard(
               &billboard, &projection, quad) != 0);

    alignas(float) unsigned char object[0x3AC] = {};
    float* source_matrix = reinterpret_cast<float*>(object + 0x23C);
    float* world_matrix = reinterpret_cast<float*>(object + 0x27C);
    source_matrix[0] = source_matrix[5] = source_matrix[10] =
        source_matrix[15] = 1.0f;
    world_matrix[0] = world_matrix[5] = world_matrix[10] =
        world_matrix[15] = 1.0f;
    *reinterpret_cast<float*>(object + 0x3C) = 0.005f;
    *reinterpret_cast<float*>(object + 0x40) = 0.005f;
    *reinterpret_cast<unsigned int*>(object + 0x35C) = 0xCu;
    AnmSpriteQuadInput projected = {};
    projected.center_z = 0.5f;
    projected.flags = 0xCu;
    projected.primary_color = 0xFFFFFFFFu;
    projected.u1 = projected.v1 = 1.0f;
    float published_world[16];
    assert(AnmSprite_BuildProjectedWorldQuad(
               object, &projected, &projection, quad,
               published_world) == 0);
    assert(world_matrix[0] == 0.005f && world_matrix[5] == 0.005f);
    assert((*reinterpret_cast<unsigned int*>(object + 0x35C) & 0xCu) == 0);
    assert(published_world[14] == 0.5f);
    assert(std::fabs(quad[0].x - 18.0f) < 0.01f);
    assert(std::fabs(quad[0].y - 82.0f) < 0.01f);
    assert(std::fabs(quad[3].x - 82.0f) < 0.01f);
    assert(std::fabs(quad[3].y - 18.0f) < 0.01f);
    assert(quad[0].z == 0.5f);

    unsigned char probes[4 * 0x14] = {};
    *reinterpret_cast<float*>(probes + 0x00) = 2.0f;
    *reinterpret_cast<float*>(probes + 0x14) = 10.0f;
    *reinterpret_cast<float*>(probes + 0x28) = 15.0f;
    *reinterpret_cast<float*>(probes + 0x3C) = 25.0f;
    float fade_world[16] = {};
    fade_world[0] = fade_world[5] = fade_world[10] = fade_world[15] = 1.0f;
    const float fade_camera[3] = {0.0f, 0.0f, 0.0f};
    assert(AnmSprite_ApplyProjectedDistanceColors(
               quad, probes, fade_world, 0xCC804020u, fade_camera,
               5.0f, 15.0f, 0xFF000000u) == 0);
    assert(quad[0].color == 0xCC804020u);
    assert(quad[1].color == 0xCC402010u);
    assert(quad[2].color == 0xCC000000u);
    assert(quad[3].color == 0xCC000000u);
    std::puts("ANM_SPRITE_QUAD_PASS");
    return 0;
}
