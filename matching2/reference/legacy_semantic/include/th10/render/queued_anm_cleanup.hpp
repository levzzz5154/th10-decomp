#pragma once

// Queued animation cleanup of stored ANM handles (retail 0x00421070).
// --- 0x00421070 -------------------------------------------------------------
struct QueuedAnimationNode;
struct QueuedAnimationLink { QueuedAnimationNode* node; QueuedAnimationLink* next; };
struct QueuedAnimationNode {
	unsigned short stop_frame;
	int parent_marker;
	QueuedAnimationLink* children;
};
struct QueuedAnimations {
	int cleanup_requested;
	int handles[3];
	int shared_latch;
};
struct QueuedAnimationCleanupEnv {
	QueuedAnimationNode* (*resolve)(int handle);
};
void QueuedAnimations_Cleanup(QueuedAnimations* state,
                              QueuedAnimationCleanupEnv* env);
