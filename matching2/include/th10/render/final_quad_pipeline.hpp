#pragma once
#include <array>
#include <cstdint>
namespace th10::render_final {struct Vertex{float x{},y{},z{};std::uint32_t color{};};struct QuadInput{std::array<Vertex,4>v{};float offset_x{},offset_y{},uv_left{},uv_top{},uv_right{},uv_bottom{};std::uint32_t color{0xffffffff};int viewport_x{},viewport_y{},viewport_w{},viewport_h{};bool snap{},override_color{};};struct QuadResult{std::array<Vertex,4>v{};bool visible{},texture_changed{},state_changed{};};QuadResult DrawQuad(const QuadInput&);}
