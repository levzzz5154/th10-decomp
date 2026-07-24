#pragma once

#include "th10/game/stage_std.hpp"

#include <cstddef>
#include <cstdint>

enum StageTimelineDecodeResult {
	kStageTimelineDecoded,
	kStageTimelineNotDue,
	kStageTimelineStopped,
	kStageTimelineRejected,
};

struct StageTimelineEvent {
	uint32_t frame;
	uint16_t opcode;
	int16_t stride;
	size_t offset;
	size_t argument_offset;
	size_t argument_size;
	uint32_t destination_offset;
	uint32_t argument0;
	uint32_t argument1;
};

struct StageTimelineStats {
	uint32_t decoded;
	uint32_t stopped_events;
	uint32_t opcode_histogram[15];
	uint32_t cursor_jumps;
	size_t maximum_accessed_offset;
	size_t maximum_record_extent;
	uint32_t rejected;
	uint32_t budget_rejections;
};

struct StageTimelineView {
	const StageStdRawView* raw;
	size_t cursor;
	size_t container_end_bound;
	uint32_t frame;
	bool stopped;
	uint32_t budget_frame;
	uint32_t steps_this_frame;
	StageTimelineStats stats;
};

bool StageTimeline_Initialize(const StageStdRawView* raw,
                              StageTimelineView* out);
StageTimelineDecodeResult StageTimeline_DecodeDue(
    StageTimelineView* view, StageTimelineEvent* out);
