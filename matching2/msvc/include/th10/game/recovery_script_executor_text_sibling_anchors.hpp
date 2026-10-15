#ifndef TH10_RECOVERY_SCRIPT_EXECUTOR_TEXT_SIBLING_ANCHORS_HPP
#define TH10_RECOVERY_SCRIPT_EXECUTOR_TEXT_SIBLING_ANCHORS_HPP

#include <stddef.h>
#include "th10/game/recovery_script_executor_caller_00419120.hpp"

// Both sibling formatters additionally read the shared animation resource's
// width at +34. The complete resource allocation size remains unspecified.
struct RecoveryTextResourceWidthView {
    unsigned char reserved_000[0x34];
    float width;
};
typedef char RecoveryTextResourceWidthOffsetCheck[
    offsetof(RecoveryTextResourceWidthView, width) == 0x34 ? 1 : -1];

// The genuine variadic member prototypes FormatRightAligned and FormatCentered
// belong to HintVm in the caller's shared header.
#endif
