#include "th10/render/queued_anm_cleanup.hpp"

namespace {

void StopTree(QueuedAnimationNode* node) {
	if (node == 0) return;
	node->stop_frame = 1;
	if (node->parent_marker == 0) {
		for (QueuedAnimationLink* link = node->children; link != 0;
		     link = link->next) {
			if (link->node != 0) link->node->stop_frame = 1;
		}
	}
}

}  // namespace

// 0x00421070 - when the queued cleanup flag is set, resolves three stored ANM
// handles, marks each root and its direct children to stop, clears the handles
// and request flag, and always clears the shared one-shot latch.
void QueuedAnimations_Cleanup(QueuedAnimations* state,
                              QueuedAnimationCleanupEnv* env) {
	if (state->cleanup_requested == 1) {
		for (int index = 0; index < 3; ++index) {
			StopTree(env->resolve(state->handles[index]));
			state->handles[index] = 0;
		}
		state->cleanup_requested = 0;
	}
	if (state->shared_latch != 0) state->shared_latch = 0;
}
