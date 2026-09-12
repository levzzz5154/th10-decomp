#include "th10/game/stage_timeline.hpp"

namespace {

const uint32_t kMaximumStepsPerFrame = 1024;

uint16_t Read16(const uint8_t* data) {
	return static_cast<uint16_t>(data[0]) |
	       static_cast<uint16_t>(static_cast<uint16_t>(data[1]) << 8);
}

uint32_t Read32(const uint8_t* data) {
	return static_cast<uint32_t>(data[0]) |
	       (static_cast<uint32_t>(data[1]) << 8) |
	       (static_cast<uint32_t>(data[2]) << 16) |
	       (static_cast<uint32_t>(data[3]) << 24);
}

bool Fits(size_t offset, size_t length, size_t end) {
	return offset <= end && length <= end - offset;
}

size_t MinimumAccessSize(uint16_t opcode) {
	static const uint8_t sizes[15] = {
	    8, 16, 20, 28, 20, 28, 20, 12, 20, 28, 52, 52, 9, 12, 16,
	};
	return opcode < 15 ? sizes[opcode] : 8;
}

void RecordMaximum(size_t value, size_t* maximum) {
	if (value > *maximum) *maximum = value;
}

StageTimelineDecodeResult Reject(StageTimelineView* view, bool budget) {
	++view->stats.rejected;
	if (budget) ++view->stats.budget_rejections;
	return kStageTimelineRejected;
}

} // namespace

bool StageTimeline_Initialize(const StageStdRawView* raw,
                              StageTimelineView* out) {
	if (raw == 0 || out == 0 || raw->data == 0 ||
	    raw->offset_08 > raw->size ||
	    !Fits(raw->offset_08, 8, raw->size)) {
		return false;
	}
	*out = {};
	out->raw = raw;
	out->cursor = raw->offset_08;
	out->container_end_bound = raw->size;
	return true;
}

StageTimelineDecodeResult StageTimeline_DecodeDue(
    StageTimelineView* view, StageTimelineEvent* out) {
	if (view == 0 || out == 0 || view->raw == 0 ||
	    view->raw->data == 0) {
		return kStageTimelineRejected;
	}
	if (view->stopped) return kStageTimelineStopped;
	if (view->budget_frame != view->frame) {
		view->budget_frame = view->frame;
		view->steps_this_frame = 0;
	}
	if (view->steps_this_frame >= kMaximumStepsPerFrame)
		return Reject(view, true);
	if (view->cursor < view->raw->offset_08 ||
	    !Fits(view->cursor, 8, view->container_end_bound)) {
		return Reject(view, false);
	}

	const uint8_t* instruction = view->raw->data + view->cursor;
	const uint32_t frame = Read32(instruction);
	if (frame > view->frame) return kStageTimelineNotDue;

	const uint16_t opcode = Read16(instruction + 4);
	const int16_t stride =
	    static_cast<int16_t>(Read16(instruction + 6));
	const size_t minimum_access = MinimumAccessSize(opcode);
	StageTimelineEvent event = {};
	event.frame = frame;
	event.opcode = opcode;
	event.stride = stride;
	event.offset = view->cursor;
	event.argument_offset = view->cursor + 8;

	++view->steps_this_frame;
	if (opcode == 0) {
		event.argument_size = 0;
		view->stopped = true;
		++view->stats.stopped_events;
		++view->stats.opcode_histogram[0];
		RecordMaximum(view->cursor + 7,
		              &view->stats.maximum_accessed_offset);
		*out = event;
		return kStageTimelineStopped;
	}
	if (stride <= 0 ||
	    static_cast<size_t>(stride) < minimum_access ||
	    !Fits(view->cursor, static_cast<size_t>(stride),
	          view->container_end_bound)) {
		return Reject(view, false);
	}
	if (!Fits(view->cursor, minimum_access, view->container_end_bound))
		return Reject(view, false);

	event.argument_size = static_cast<size_t>(stride) - 8;
	if (minimum_access >= 12) event.argument0 = Read32(instruction + 8);
	if (opcode == 1) event.argument1 = Read32(instruction + 12);

	const size_t previous_cursor = view->cursor;
	if (opcode == 1) {
		const size_t relative = event.argument0;
		if (relative > view->container_end_bound - view->raw->offset_08)
			return Reject(view, false);
		const size_t destination = view->raw->offset_08 + relative;
		if (!Fits(destination, 8, view->container_end_bound) ||
		    destination == previous_cursor) {
			return Reject(view, false);
		}
		event.destination_offset = static_cast<uint32_t>(destination);
		view->cursor = destination;
		++view->stats.cursor_jumps;
	} else {
		view->cursor += static_cast<size_t>(stride);
	}

	++view->stats.decoded;
	if (opcode < 15) ++view->stats.opcode_histogram[opcode];
	RecordMaximum(previous_cursor + minimum_access - 1,
	              &view->stats.maximum_accessed_offset);
	RecordMaximum(previous_cursor + static_cast<size_t>(stride) - 1,
	              &view->stats.maximum_record_extent);
	*out = event;
	return kStageTimelineDecoded;
}
