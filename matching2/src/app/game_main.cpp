// =============================================================================
// game_main.cpp - Readable reconstruction of the retail boot orchestrator
// =============================================================================
#include "th10/app/game_main.hpp"

namespace {

// Retail allocates a 0xA004-byte allocation tracker (0x2801 dwords; the final
// dword flags whether the 0x2800 tracked slots must be freed on shutdown).
constexpr unsigned int kTrackerPoolBytes = 0xA004;
constexpr int kCriticalSectionCount = 7;
constexpr int kFrameDivisorDefault = 0xFC;
constexpr int kResetGraceFrames = 3;

void ZeroTrackerPool(void* pool) {
    unsigned int* slots = static_cast<unsigned int*>(pool);
    for (unsigned int index = 0; index < kTrackerPoolBytes / 4u; ++index)
        slots[index] = 0;
}

} // namespace

// 0x00438AD0 - GameMain: boot, run, and tear down one game session.
// The retail function loops so that "exit mode 2" (restart after device or
// display-mode change) re-runs the whole boot without writing th10.cfg back.
int GameMain_Run(GameMainState* state, const GameMainHooks* hooks) {
    void* ctx = hooks->context;

    // One-time process setup: allocation tracker and critical sections.
    state->tracker_pool = hooks->alloc(kTrackerPoolBytes);
    if (state->tracker_pool != 0)
        ZeroTrackerPool(state->tracker_pool);
    state->critical_sections = kCriticalSectionCount;
    hooks->critical_sections_init(ctx, kCriticalSectionCount);
    hooks->log_open(ctx, "log opened");

    int exit_mode = GAME_MAIN_EXIT_NORMAL;
    for (;;) { // retail restart loop (LAB back-edge for exit mode 2)
        exit_mode = GAME_MAIN_EXIT_NORMAL;

        // ---- Boot sequence; any failure routes to the cleanup label. ----
        if (hooks->load_config(ctx) == -1) {
            exit_mode = GAME_MAIN_EXIT_BOOT_FAILURE;
        } else if (hooks->create_window(ctx) != 0 ||
                   hooks->create_input(ctx) != 0) {
            exit_mode = GAME_MAIN_EXIT_BOOT_FAILURE;
        } else {
            // Optional startup confirmation dialog (config bit 0x100);
            // IDNO (retail compares against 6 == IDYES) declines fullscreen.
            if ((state->config_flags & 0x100u) != 0)
                state->dialog_declined =
                    hooks->confirm_startup_dialog(ctx) != 6;
            hooks->checksum_executable(ctx);

            state->scheduler = hooks->create_scheduler(ctx);
            state->direct3d = hooks->create_direct3d(ctx);
            if (state->direct3d == 0 ||
                hooks->create_device(ctx) != 0) {
                exit_mode = GAME_MAIN_EXIT_BOOT_FAILURE;
            } else {
                state->sound_worker_stop = 0;
                state->sound_worker_thread = hooks->spawn_sound_worker(ctx);
                if (hooks->init_device_objects(ctx) == 0) {
                    hooks->probe_joystick(ctx);
                    hooks->init_text_layer(ctx);
                    state->game_state_manager =
                        hooks->create_game_state(ctx, 0);
                    if (state->dialog_declined == 0)
                        hooks->disable_ime_and_cursor(ctx);

                    // Seed the frame clock (retail stores the first sample
                    // into 0x00492540/38/28/30 before entering the pump).
                    state->clock_floor = hooks->read_clock(ctx);
                    state->clock_samples[0] = state->clock_floor;
                    state->clock_samples[1] = state->clock_floor;
                    state->clock_samples[2] = state->clock_floor;
                    hooks->set_foreground_window(ctx);

                    int task_status = hooks->register_main_tasks(ctx);
                    if (task_status == 0) {
                        state->frame_divisor = kFrameDivisorDefault;

                        // ---- Message pump / frame loop. ----
                        while (state->quit_requested == 0) {
                            if (hooks->pump_messages(ctx) != 0)
                                break;
                            int probe = hooks->probe_device(ctx);
                            if (probe == GAME_MAIN_DEVICE_READY) {
                                int frame = hooks->frame_advance(ctx);
                                state->device_flags &= ~0x10u;
                                if (frame != 0) {
                                    exit_mode = (frame == 2)
                                        ? GAME_MAIN_EXIT_RESTART
                                        : GAME_MAIN_EXIT_BOOT_FAILURE;
                                    break;
                                }
                            } else if (probe == GAME_MAIN_DEVICE_NEEDS_RESET) {
                                hooks->device_release_resources(ctx);
                                hooks->device_reset(ctx);
                                hooks->device_apply_default_state(ctx);
                                state->reset_grace_frames = kResetGraceFrames;
                                state->device_flags |= 0x10u;
                            }
                            // GAME_MAIN_DEVICE_LOST: keep pumping only.
                        }
                    } else if (task_status != -1) {
                        exit_mode = GAME_MAIN_EXIT_RESTART;
                    }
                    hooks->shutdown_main_tasks(ctx);
                }
                hooks->destroy_scheduler(ctx, state->scheduler);
                state->scheduler = 0;
                // Drain queued sound commands until the queue reports empty.
                while (hooks->drain_sound_commands(ctx) != 0) {
                }
            }
        }

        // ---- Cleanup label (retail joins every failure path here). ----
        state->sound_worker_stop = 2;
        hooks->stop_sound_worker(ctx);
        hooks->destroy_sound(ctx);
        if (state->game_state_manager != 0) {
            hooks->destroy_game_state(ctx, state->game_state_manager);
            state->game_state_manager = 0;
        }
        hooks->release_device_chain(ctx);
        state->device = 0;
        state->direct3d = 0;
        hooks->destroy_window(ctx);

        if (exit_mode != GAME_MAIN_EXIT_RESTART)
            hooks->save_config(ctx);
        if (state->midi_active != 0) {
            hooks->shutdown_midi(ctx);
            state->midi_active = 0;
        }

        if (exit_mode != GAME_MAIN_EXIT_RESTART)
            break;
        // Restart: reopen the log and pump 0x3C grace iterations so the
        // display mode change settles before the next boot.
        hooks->log_open(ctx, "restart");
        hooks->restart_grace_pump(ctx);
    }

    // ---- Process teardown. ----
    hooks->log_flush_and_close(ctx);
    hooks->critical_sections_destroy(ctx, state->critical_sections);
    hooks->restore_system_parameters(ctx);
    if (state->tracker_pool != 0) {
        hooks->release(state->tracker_pool);
        state->tracker_pool = 0;
    }
    return 0;
}
