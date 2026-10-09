// Arithmetic of the stage fog record, as its interpolator uses it. Every
// result is rebuilt through the constructor, which re-derives the packed
// colour from the float channels.
#include "th10/render/stage_fog.hpp"

#pragma code_seg(".text$00404d40_fn")
StageFog StageFog::operator-(const StageFog& v) const {
    return StageFog(start - v.start, end - v.end, blue - v.blue, green - v.green,
                    red - v.red, alpha - v.alpha);
}
#pragma code_seg(".text$00404da0_fn")
StageFog StageFog::operator*(float f) const {
    return StageFog(start * f, end * f, blue * f, green * f, red * f, alpha * f);
}
#pragma code_seg(".text$00404e10_fn")
StageFog StageFog::operator+(const StageFog& v) const {
    return StageFog(start + v.start, end + v.end, blue + v.blue, green + v.green,
                    red + v.red, alpha + v.alpha);
}
#pragma code_seg()
