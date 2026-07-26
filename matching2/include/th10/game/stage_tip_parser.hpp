#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace th10::stage_tips {
struct ParsedTip{int stage{};float x{},y{};std::string text;int count{},time{},base{},align{},remain{};float scale{1};std::uint8_t r{},g{},b{},a{};float rendered_width{};int list_index{};};
struct ParseResult{bool opened{};bool version_ok{true};std::vector<ParsedTip> tips;};
// Retail 0x00419960: parse Version/Stage/Tips blocks and optionally duplicate each tip.
ParseResult ParseStageTips(const std::string& text,bool suppress_duplicate);
}
