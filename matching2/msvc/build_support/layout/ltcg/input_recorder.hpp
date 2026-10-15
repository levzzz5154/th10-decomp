#pragma once
#include "input_recorder_dependencies.hpp"

struct InputReplayPacketHeader {
    int reserved_00;
    int input_count;
};

struct InputReplayStage {
    void* input_allocation;
    RecorderInputRecord* input_cursor;
    void* sample_allocation;
    unsigned char* sample_cursor;
    InputReplayPacketHeader* header;
    int consumed;
    unsigned char reserved_18[0xC];
};

struct InputRecorder_004297D0 {
    unsigned char reserved_000[0x10];
    int playback_mode;
    void* header;
    void* configuration;
    void* stage_records[8];
    RecorderPoolLink stage_heads[8];
    RecorderPoolLink* current_pool;
    InputReplayStage playback[8];
    int reserved_1c0;
    unsigned char sample;
    unsigned char reserved_1c5[3];
    int frame_count;
    void* secondary_task;
    int active_stage;

    __declspec(noinline) int Update();
};

struct InputAnalogSource {
    unsigned char reserved_00[0x34];
    float value;
};

typedef char InputReplayStageSize[sizeof(InputReplayStage)==0x24?1:-1];
typedef char InputRecorderHeadsOffset[offsetof(InputRecorder_004297D0,stage_heads)==0x3C?1:-1];
typedef char InputRecorderPoolOffset[offsetof(InputRecorder_004297D0,current_pool)==0x9C?1:-1];
typedef char InputRecorderPlaybackOffset[offsetof(InputRecorder_004297D0,playback)==0xA0?1:-1];
typedef char InputRecorderSampleOffset[offsetof(InputRecorder_004297D0,sample)==0x1C4?1:-1];
typedef char InputRecorderFrameOffset[offsetof(InputRecorder_004297D0,frame_count)==0x1C8?1:-1];
typedef char InputRecorderStageOffset[offsetof(InputRecorder_004297D0,active_stage)==0x1D0?1:-1];

extern "C" {
extern void* g_game;
extern InputAnalogSource* g_fps;
extern unsigned int data_00491d78;
}

int __fastcall ReplayManager_OnUpdate(InputRecorder_004297D0*);
