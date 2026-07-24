#include "th10/game/stage_timeline.hpp"

#include <cassert>
#include <cstdio>
#include <vector>

namespace {

void Write16(std::vector<uint8_t>& bytes, size_t offset, uint16_t value) {
	bytes[offset] = static_cast<uint8_t>(value);
	bytes[offset + 1] = static_cast<uint8_t>(value >> 8);
}

void Write32(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
	for (int index = 0; index < 4; ++index)
		bytes[offset + index] =
		    static_cast<uint8_t>(value >> (index * 8));
}

StageStdRawView Raw(std::vector<uint8_t>& bytes, size_t start = 16) {
	StageStdRawView raw = {};
	raw.data = bytes.data();
	raw.size = bytes.size();
	raw.offset_08 = static_cast<uint32_t>(start);
	return raw;
}

void Instruction(std::vector<uint8_t>& bytes, size_t offset, uint32_t frame,
                 uint16_t opcode, int16_t stride) {
	Write32(bytes, offset, frame);
	Write16(bytes, offset + 4, opcode);
	Write16(bytes, offset + 6, static_cast<uint16_t>(stride));
}

void TestDecodedAndNotDue() {
	std::vector<uint8_t> bytes(80, 0);
	Instruction(bytes, 16, 4, 2, 20);
	StageStdRawView raw = Raw(bytes);
	StageTimelineView view = {};
	StageTimelineEvent event = {};
	assert(StageTimeline_Initialize(&raw, &view));
	view.frame = 3;
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineNotDue);
	assert(view.cursor == 16 && view.stats.decoded == 0);
	view.frame = 4;
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineDecoded);
	assert(event.opcode == 2 && event.offset == 16);
	assert(view.cursor == 36 && view.stats.decoded == 1);
	assert(view.stats.maximum_accessed_offset == 35);
	assert(view.stats.maximum_record_extent == 35);
}

void TestStopIgnoresStrideAndPersists() {
	for (int16_t stride : {int16_t(20), int16_t(0), int16_t(-1)}) {
		std::vector<uint8_t> bytes(48, 0);
		Instruction(bytes, 16, 0, 0, stride);
		StageStdRawView raw = Raw(bytes);
		StageTimelineView view = {};
		StageTimelineEvent event = {};
		assert(StageTimeline_Initialize(&raw, &view));
		assert(StageTimeline_DecodeDue(&view, &event) ==
		       kStageTimelineStopped);
		assert(view.stopped && view.cursor == 16);
		assert(view.stats.stopped_events == 1);
		assert(StageTimeline_DecodeDue(&view, &event) ==
		       kStageTimelineStopped);
		assert(view.stats.stopped_events == 1);
	}
}

void TestInvalidStridesAndTruncation() {
	for (int16_t stride : {int16_t(0), int16_t(-8)}) {
		std::vector<uint8_t> bytes(64, 0);
		Instruction(bytes, 16, 0, 2, stride);
		StageStdRawView raw = Raw(bytes);
		StageTimelineView view = {};
		StageTimelineEvent event = {};
		assert(StageTimeline_Initialize(&raw, &view));
		assert(StageTimeline_DecodeDue(&view, &event) ==
		       kStageTimelineRejected);
	}
	std::vector<uint8_t> bytes(64, 0);
	Instruction(bytes, 16, 0, 10, 52);
	StageStdRawView raw = Raw(bytes);
	StageTimelineView view = {};
	StageTimelineEvent event = {};
	assert(StageTimeline_Initialize(&raw, &view));
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineRejected);
}

void TestJumpValidation() {
	std::vector<uint8_t> bytes(64, 0);
	Instruction(bytes, 16, 0, 1, 16);
	Write32(bytes, 24, 44); // destination 60: fewer than 8 bytes remain
	StageStdRawView raw = Raw(bytes);
	StageTimelineView view = {};
	StageTimelineEvent event = {};
	assert(StageTimeline_Initialize(&raw, &view));
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineRejected);

	Write32(bytes, 24, 0x100);
	assert(StageTimeline_Initialize(&raw, &view));
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineRejected);

	Write32(bytes, 24, 0); // direct self-loop
	assert(StageTimeline_Initialize(&raw, &view));
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineRejected);
}

void TestCycleBudget() {
	std::vector<uint8_t> bytes(64, 0);
	Instruction(bytes, 16, 0, 1, 16);
	Write32(bytes, 24, 16); // -> 32
	Instruction(bytes, 32, 0, 1, 16);
	Write32(bytes, 40, 0); // -> 16
	StageStdRawView raw = Raw(bytes);
	StageTimelineView view = {};
	StageTimelineEvent event = {};
	assert(StageTimeline_Initialize(&raw, &view));
	for (int index = 0; index < 1024; ++index)
		assert(StageTimeline_DecodeDue(&view, &event) ==
		       kStageTimelineDecoded);
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineRejected);
	assert(view.stats.budget_rejections == 1);
}

void TestUnknownOpcodeAndStatistics() {
	std::vector<uint8_t> bytes(48, 0);
	Instruction(bytes, 16, 0, 99, 12);
	StageStdRawView raw = Raw(bytes);
	StageTimelineView view = {};
	StageTimelineEvent event = {};
	assert(StageTimeline_Initialize(&raw, &view));
	assert(StageTimeline_DecodeDue(&view, &event) ==
	       kStageTimelineDecoded);
	assert(event.opcode == 99 && event.argument_size == 4);
	assert(view.stats.decoded == 1);
	assert(view.stats.maximum_accessed_offset == 23);
	assert(view.stats.maximum_record_extent == 27);
	for (uint32_t count : view.stats.opcode_histogram) assert(count == 0);
}

} // namespace

int main() {
	TestDecodedAndNotDue();
	TestStopIgnoresStrideAndPersists();
	TestInvalidStridesAndTruncation();
	TestJumpValidation();
	TestCycleBudget();
	TestUnknownOpcodeAndStatistics();
	std::puts("stage timeline tests passed");
}
