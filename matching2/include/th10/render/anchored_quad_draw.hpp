#pragma once
#include <array>
#include <cstdint>
namespace th10::render {struct AnchoredQuad{float width{},height{},scale_x{1},scale_y{1};std::array<float,3>position{},offset{},parent{};std::uint32_t flags{};};struct Vertex{float x{},y{},z{};};struct Quad{std::array<Vertex,4>v{};};Quad BuildAnchoredQuad(const AnchoredQuad&);}
