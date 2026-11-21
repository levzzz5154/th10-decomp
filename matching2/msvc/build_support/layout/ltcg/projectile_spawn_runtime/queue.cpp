// Compiler context only: the anchor copy of 0x0043DC90, queueing one sound
// request. The whole-program pass derives the retail register state (sound id
// in EDI, receiver in ECX). The anchor bytes are never exported as recovered
// code.

#define TH10_SOUND_QUEUE_SECTION ".text$0043dc90_s"
#include "../../../../src/core/sound/sound_queue.cpp"
