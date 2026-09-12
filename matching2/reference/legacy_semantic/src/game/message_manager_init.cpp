#include "th10/game/message_manager_init.hpp"

// Semantic reconstruction 0x0040B560 - initialize the stage message manager.
int MessageManager_Initialize(MessageManagerState* state,
                              const MessageManagerInitEnv* env) {
    state->update_task = env->create_task(env->context, 0, 28, state);
    state->draw_task = env->create_task(env->context, 1, 6, state);
    if (*env->indicator_handle == nullptr)
        *env->indicator_handle =
            env->create_indicator(env->context, 464.0f, 352.0f, 6);

    int index = env->stage + 3 * env->character;
    if (env->power == 0 && env->difficulty >= 1)
        index += 6;
    state->message_index = index;
    if (env->seen_messages[index] == 0)
        state->first_seen_flags |= 1u;
    if (*env->seen_special == 0)
        state->first_seen_flags |= 2u;
    env->seen_messages[index] = 1;
    if (index >= 6)
        *env->seen_special = 1;

    state->resource =
        env->load_resource(env->context, env->resource_names[index]);
    if (state->resource == nullptr) {
        env->report_missing(env->context);
        return -1;
    }
    state->parser = env->create_parser(env->context, state->resource);
    return 0;
}
