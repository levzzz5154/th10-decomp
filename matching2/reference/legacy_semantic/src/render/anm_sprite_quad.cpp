#include "th10/render/anm_sprite_quad.hpp"

#include <cmath>

namespace {
const AnmSpriteRenderBackend* g_backend = nullptr;

void MatrixIdentity(float matrix[16]) {
    for (int index = 0; index < 16; ++index)
        matrix[index] = 0.0f;
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
}

void MatrixMultiply(float output[16], const float left[16],
                    const float right[16]) {
    float result[16];
    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column) {
            result[row * 4 + column] = 0.0f;
            for (int inner = 0; inner < 4; ++inner)
                result[row * 4 + column] +=
                    left[row * 4 + inner] * right[inner * 4 + column];
        }
    for (int index = 0; index < 16; ++index)
        output[index] = result[index];
}

void MatrixRotation(float output[16], int axis, float angle) {
    MatrixIdentity(output);
    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    if (axis == 0) {
        output[5] = cosine; output[6] = sine;
        output[9] = -sine; output[10] = cosine;
    } else if (axis == 1) {
        output[0] = cosine; output[2] = -sine;
        output[8] = sine; output[10] = cosine;
    } else {
        output[0] = cosine; output[1] = sine;
        output[4] = -sine; output[5] = cosine;
    }
}

void ProjectPoint(float output[3], const float input[3],
                  const AnmSpriteProjectionContext* context,
                  const float* world = nullptr) {
    const float* matrix_view = context->view;
    const float* matrix_projection = context->projection;
    const float* viewport = context->viewport;
    float source[4] = {input[0], input[1], input[2], 1.0f};
    float transformed[4];
    if (world != nullptr) {
        for (int row = 0; row < 4; ++row)
            transformed[row] = source[0] * world[row] +
                               source[1] * world[4 + row] +
                               source[2] * world[8 + row] +
                               source[3] * world[12 + row];
    } else {
        for (int row = 0; row < 4; ++row)
            transformed[row] = source[row];
    }
    float view[4];
    for (int row = 0; row < 4; ++row) {
        view[row] = transformed[0] * matrix_view[row] +
                    transformed[1] * matrix_view[4 + row] +
                    transformed[2] * matrix_view[8 + row] +
                    transformed[3] * matrix_view[12 + row];
    }
    float clip[4];
    for (int row = 0; row < 4; ++row) {
        clip[row] = view[0] * matrix_projection[row] +
                    view[1] * matrix_projection[4 + row] +
                    view[2] * matrix_projection[8 + row] +
                    view[3] * matrix_projection[12 + row];
    }
    if (clip[3] == 0.0f) {
        output[0] = output[1] = output[2] = 0.0f;
        return;
    }
    output[0] = (clip[0] / clip[3] + 1.0f) * viewport[2] * 0.5f + viewport[0];
    output[1] = (-clip[1] / clip[3] + 1.0f) * viewport[3] * 0.5f + viewport[1];
    output[2] = clip[2] / clip[3];
}
}

void AnmSpriteRenderer_BindBackend(const AnmSpriteRenderBackend* backend) {
    g_backend = backend;
}

const AnmSpriteRenderBackend* AnmSpriteRenderer_GetBackend() {
    return g_backend;
}

unsigned int AnmSprite_SelectedColor(const AnmSpriteQuadInput* input) {
    return (input->flags & 0x8000u) != 0 ? input->secondary_color
                                         : input->primary_color;
}

void AnmSprite_BuildQuad(const AnmSpriteQuadInput* input,
                         AnmSpriteQuadVertex output[4]) {
    float left;
    float right;
    switch ((input->flags >> 18) & 3u) {
    case 1:
        left = 0.0f;
        right = input->width;
        break;
    case 2:
        left = -input->width;
        right = 0.0f;
        break;
    default:
        left = input->width * -0.5f;
        right = input->width * 0.5f;
        break;
    }

    float top;
    float bottom;
    switch ((input->flags >> 20) & 3u) {
    case 1:
        top = 0.0f;
        bottom = input->height;
        break;
    case 2:
        top = -input->height;
        bottom = 0.0f;
        break;
    default:
        top = input->height * -0.5f;
        bottom = input->height * 0.5f;
        break;
    }

    const float cosine = std::cos(input->rotation);
    const float sine = std::sin(input->rotation);
    const float u0 = input->u0 + input->uv_scroll_x;
    const float v0 = input->v0 + input->uv_scroll_y;
    const float u1 = input->u1 + input->uv_scroll_x;
    const float v1 = input->v1 + input->uv_scroll_y;
    const unsigned int color = AnmSprite_SelectedColor(input);
    const float x[4] = {left, right, left, right};
    const float y[4] = {top, top, bottom, bottom};
    const float u[4] = {u0, u1, u0, u1};
    const float v[4] = {v0, v0, v1, v1};

    for (int index = 0; index < 4; ++index) {
        output[index].x = x[index] * cosine - y[index] * sine + input->center_x;
        output[index].y = x[index] * sine + y[index] * cosine + input->center_y;
        output[index].z = input->center_z;
        output[index].rhw = 1.0f;
        output[index].color = color;
        output[index].u = u[index];
        output[index].v = v[index];
    }
}

int AnmSprite_BuildProjectedWorldQuad(
    unsigned char* object, const AnmSpriteQuadInput* input,
    const AnmSpriteProjectionContext* projection,
    AnmSpriteQuadVertex output[4], float output_world[16]) {
    if (object == nullptr || input == nullptr || projection == nullptr ||
        output == nullptr || output_world == nullptr ||
        projection->view == nullptr || projection->projection == nullptr ||
        projection->viewport == nullptr)
        return -1;
    unsigned int& flags = *reinterpret_cast<unsigned int*>(object + 0x35C);
    float* source_matrix = reinterpret_cast<float*>(object + 0x23C);
    float* world_matrix = reinterpret_cast<float*>(object + 0x27C);
    if ((flags & 0x4000u) == 0 && (flags & 0xCu) != 0) {
        for (int index = 0; index < 16; ++index)
            world_matrix[index] = source_matrix[index];
        world_matrix[0] *= *reinterpret_cast<float*>(object + 0x3C);
        world_matrix[5] *= *reinterpret_cast<float*>(object + 0x40);
        flags &= ~8u;
        for (int axis = 0; axis < 3; ++axis) {
            const float angle = *reinterpret_cast<float*>(object + 0x24 + axis * 4);
            if (angle == 0.0f)
                continue;
            float rotation[16];
            float combined[16];
            MatrixRotation(rotation, axis, angle);
            MatrixMultiply(combined, world_matrix, rotation);
            for (int index = 0; index < 16; ++index)
                world_matrix[index] = combined[index];
        }
        flags &= ~4u;
    }
    for (int index = 0; index < 16; ++index)
        output_world[index] = world_matrix[index];
    output_world[12] += input->center_x;
    output_world[13] += input->center_y;
    output_world[14] += input->center_z;

    float left;
    float right;
    float top;
    float bottom;
    switch ((flags >> 18) & 3u) {
    case 1: left = 0.0f; right = 256.0f; break;
    case 2: left = -256.0f; right = 0.0f; break;
    default: left = -128.0f; right = 128.0f; break;
    }
    switch ((flags >> 20) & 3u) {
    case 1: top = 0.0f; bottom = 256.0f; break;
    case 2: top = -256.0f; bottom = 0.0f; break;
    default: top = -128.0f; bottom = 128.0f; break;
    }
    const float positions[4][3] = {
        {left, top, 0.0f}, {right, top, 0.0f},
        {left, bottom, 0.0f}, {right, bottom, 0.0f}};
    const float u[4] = {input->u0 + input->uv_scroll_x,
                        input->u1 + input->uv_scroll_x,
                        input->u0 + input->uv_scroll_x,
                        input->u1 + input->uv_scroll_x};
    const float v[4] = {input->v0 + input->uv_scroll_y,
                        input->v0 + input->uv_scroll_y,
                        input->v1 + input->uv_scroll_y,
                        input->v1 + input->uv_scroll_y};
    const unsigned int color = AnmSprite_SelectedColor(input);
    for (int index = 0; index < 4; ++index) {
        float projected[3];
        ProjectPoint(projected, positions[index], projection, output_world);
        output[index].x = projected[0];
        output[index].y = projected[1];
        output[index].z = projected[2];
        output[index].rhw = 1.0f;
        output[index].color = color;
        output[index].u = u[index];
        output[index].v = v[index];
    }
    return 0;
}

int AnmSprite_ApplyProjectedDistanceColors(
    AnmSpriteQuadVertex quad[4], const unsigned char* probes,
    const float world[16], unsigned int base_color, const float camera[3],
    float near_distance, float far_distance, unsigned int far_color) {
    if (quad == nullptr || probes == nullptr || world == nullptr ||
        camera == nullptr || near_distance == far_distance)
        return -1;
    const float denominator = near_distance - far_distance;
    const unsigned char base[4] = {
        static_cast<unsigned char>(base_color),
        static_cast<unsigned char>(base_color >> 8),
        static_cast<unsigned char>(base_color >> 16),
        static_cast<unsigned char>(base_color >> 24)};
    const unsigned char far[4] = {
        static_cast<unsigned char>(far_color),
        static_cast<unsigned char>(far_color >> 8),
        static_cast<unsigned char>(far_color >> 16),
        static_cast<unsigned char>(far_color >> 24)};
    for (int index = 0; index < 4; ++index) {
        const float* probe = reinterpret_cast<const float*>(probes + index * 0x14);
        float transformed[3];
        for (int axis = 0; axis < 3; ++axis)
            transformed[axis] = probe[0] * world[axis] +
                                probe[1] * world[4 + axis] +
                                probe[2] * world[8 + axis] + world[12 + axis];
        const float dx = transformed[0] - camera[0];
        const float dy = transformed[1] - camera[1];
        const float dz = transformed[2] - camera[2];
        const float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
        unsigned char color[4] = {base[0], base[1], base[2], base[3]};
        if (distance > near_distance) {
            const float amount = (near_distance - distance) / denominator;
            if (amount >= 1.0f) {
                color[0] = far[0]; color[1] = far[1]; color[2] = far[2];
            } else {
                for (int channel = 0; channel < 3; ++channel)
                    color[channel] = static_cast<unsigned char>(
                        static_cast<int>(base[channel]) -
                        static_cast<int>((static_cast<int>(base[channel]) -
                                          static_cast<int>(far[channel])) * amount));
            }
        }
        quad[index].color = static_cast<unsigned int>(color[0]) |
            (static_cast<unsigned int>(color[1]) << 8) |
            (static_cast<unsigned int>(color[2]) << 16) |
            (static_cast<unsigned int>(color[3]) << 24);
        quad[index].rhw = 1.0f;
    }
    return 0;
}

void AnmSprite_ExpandTriangleList(const AnmSpriteQuadVertex quad[4],
                                  AnmSpriteQuadVertex output[6]) {
    static const int order[6] = {0, 1, 2, 1, 2, 3};
    for (int index = 0; index < 6; ++index)
        output[index] = quad[order[index]];
}

int AnmSprite_BuildProjectedBillboard(
    const AnmSpriteQuadInput* input,
    const AnmSpriteProjectionContext* projection,
    AnmSpriteQuadVertex output[4]) {
    if (input == nullptr || projection == nullptr || output == nullptr ||
        projection->view == nullptr || projection->projection == nullptr ||
        projection->viewport == nullptr)
        return -1;
    const float center_world[3] = {
        input->center_x, input->center_y, input->center_z};
    float center[3];
    ProjectPoint(center, center_world, projection);
    if (center[2] < 0.0f || center[2] > 1.0f)
        return -1;
    float reference[3];
    ProjectPoint(reference, projection->reference_point, projection);
    const float dx = reference[0] - center[0];
    const float dy = reference[1] - center[1];
    const float dz = reference[2] - center[2];
    const float perspective = std::sqrt(dx * dx + dy * dy + dz * dz) * 0.5f;
    const float width = input->width * perspective;
    const float height = input->height * perspective;
    float left;
    float right;
    float top;
    float bottom;
    const unsigned int flags = input->flags;
    switch ((flags >> 18) & 3u) {
    case 1: left = 0.0f; right = width; break;
    case 2: left = -width; right = 0.0f; break;
    default: left = -width * 0.5f; right = width * 0.5f; break;
    }
    switch ((flags >> 20) & 3u) {
    case 1: top = 0.0f; bottom = height; break;
    case 2: top = -height; bottom = 0.0f; break;
    default: top = -height * 0.5f; bottom = height * 0.5f; break;
    }
    const float cosine = std::cos(input->rotation);
    const float sine = std::sin(input->rotation);
    const float x[4] = {left, right, left, right};
    const float y[4] = {top, top, bottom, bottom};
    const float u[4] = {input->u0 + input->uv_scroll_x,
                        input->u1 + input->uv_scroll_x,
                        input->u0 + input->uv_scroll_x,
                        input->u1 + input->uv_scroll_x};
    const float v[4] = {input->v0 + input->uv_scroll_y,
                        input->v0 + input->uv_scroll_y,
                        input->v1 + input->uv_scroll_y,
                        input->v1 + input->uv_scroll_y};
    const unsigned int color = AnmSprite_SelectedColor(input);
    for (int index = 0; index < 4; ++index) {
        output[index].x = x[index] * cosine - y[index] * sine + center[0];
        output[index].y = x[index] * sine + y[index] * cosine + center[1];
        output[index].z = center[2];
        output[index].rhw = 1.0f;
        output[index].color = color;
        output[index].u = u[index];
        output[index].v = v[index];
    }
    return 0;
}
