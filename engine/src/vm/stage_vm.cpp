#include "th10/stage_loader.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace th10 {

// ========================================
// StageScriptVM
// ========================================

void StageScriptVM::load(const uint8_t* data, size_t size) {
    bytecode_ = data;
    bytecode_size_ = size;
    ip_ = 0;
    running_ = true;
    wait_counter_ = 0;
    enemies_cleared_ = false;
}

const StageScriptInstr* StageScriptVM::current_instr() const {
    if (!bytecode_ || ip_ >= bytecode_size_) return nullptr;
    return reinterpret_cast<const StageScriptInstr*>(bytecode_ + ip_);
}

void StageScriptVM::execute() {
    if (!bytecode_) return;
    running_ = true;

    while (running_ && ip_ < bytecode_size_) {
        if (wait_counter_ > 0) {
            wait_counter_--;
            break;
        }
        execute_opcode();
    }
}

void StageScriptVM::execute_opcode() {
    const StageScriptInstr* instr = current_instr();
    if (!instr) {
        running_ = false;
        return;
    }

    uint8_t opcode = instr->opcode;

    if (opcode > 0x17) {
        fprintf(stderr, "[StageVM] Unknown opcode: 0x%02X at IP=%zu\n", opcode, ip_);
        running_ = false;
        return;
    }

    switch (static_cast<StageScriptOpcode>(opcode)) {
        case StageScriptOpcode::END:           op_END();           break;
        case StageScriptOpcode::LOAD_ENEMY_1:  op_LOAD_ENEMY_1(); break;
        case StageScriptOpcode::LOAD_ENEMY_2:  op_LOAD_ENEMY_2(); break;
        case StageScriptOpcode::LOAD_ENEMY_3:  op_LOAD_ENEMY_3(); break;
        case StageScriptOpcode::FREE_ENEMY_1:  op_FREE_ENEMY_1(); break;
        case StageScriptOpcode::FREE_ENEMY_2:  op_FREE_ENEMY_2(); break;
        case StageScriptOpcode::FREE_ENEMY_3:  op_FREE_ENEMY_3(); break;
        case StageScriptOpcode::SPAWN_1:       op_SPAWN_1();      break;
        case StageScriptOpcode::SPAWN_2:       op_SPAWN_2();      break;
        case StageScriptOpcode::TOGGLE_FLAG:   op_TOGGLE_FLAG();  break;
        case StageScriptOpcode::CHECK_CLEAR:   op_CHECK_CLEAR();  break;
        case StageScriptOpcode::WAIT:          op_WAIT();         break;
        case StageScriptOpcode::BGM_TEMPO:     op_BGM_TEMPO();    break;
        case StageScriptOpcode::BGM_STAGE:     op_BGM_STAGE();    break;
        case StageScriptOpcode::LOAD_ECL_1:    op_LOAD_ECL_1();   break;
        case StageScriptOpcode::LOAD_ECL_2:    op_LOAD_ECL_2();   break;
        case StageScriptOpcode::LOAD_ECL_3:    op_LOAD_ECL_3();   break;
        case StageScriptOpcode::CLEANUP:        op_CLEANUP();      break;
        case StageScriptOpcode::LOAD_BGM:      op_LOAD_BGM();     break;
        case StageScriptOpcode::SET_ENEMY_DATA: op_SET_ENEMY_DATA(); break;
        case StageScriptOpcode::SCORE:          op_SCORE();        break;
        case StageScriptOpcode::BGM_FADEIN:    op_BGM_FADEIN();   break;
        case StageScriptOpcode::FREE_ECL_1:    op_FREE_ECL_1();   break;
        case StageScriptOpcode::FREE_ECL_2:    op_FREE_ECL_2();   break;
    }
}

// ========================================
// Opcode 0x00: END — End stage / terminate script
// ========================================
void StageScriptVM::op_END() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: END (slot=%d)\n", ip_, instr->slot);
    running_ = false;
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x01: LOAD_ENEMY_1 — Load enemy data from primary table
// ========================================
void StageScriptVM::op_LOAD_ENEMY_1() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_ENEMY_1 slot=%d size=%d param1=%d\n",
           ip_, instr->slot, instr->size, instr->param1);
    // Reads enemy data from global enemy table at index=param1
    // Allocates enemy slots in entity pool for each entry
    // Sets enemy type, position, and initial script sub
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x02: LOAD_ENEMY_2 — Load enemy data from secondary table
// ========================================
void StageScriptVM::op_LOAD_ENEMY_2() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_ENEMY_2 slot=%d size=%d param1=%d\n",
           ip_, instr->slot, instr->size, instr->param1);
    // Same as LOAD_ENEMY_1 but uses alternate enemy table
    // Table offset differs by stage ID
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x03: LOAD_ENEMY_3 — Load enemy data from tertiary table
// ========================================
void StageScriptVM::op_LOAD_ENEMY_3() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_ENEMY_3 slot=%d size=%d param1=%d\n",
           ip_, instr->slot, instr->size, instr->param1);
    // Uses third enemy data table variant
    // May include midboss/boss-specific initialization
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x04: FREE_ENEMY_1 — Free enemy data slots (variant 1)
// ========================================
void StageScriptVM::op_FREE_ENEMY_1() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: FREE_ENEMY_1 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Unlinks enemy entities from the entity pool
    // Marks entity slots as available for reuse
    // Uses slot range specified by param1
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x05: FREE_ENEMY_2 — Free enemy data slots (variant 2)
// ========================================
void StageScriptVM::op_FREE_ENEMY_2() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: FREE_ENEMY_2 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Frees from secondary pool or with different cleanup behavior
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x06: FREE_ENEMY_3 — Free enemy data slots (variant 3)
// ========================================
void StageScriptVM::op_FREE_ENEMY_3() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: FREE_ENEMY_3 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Third variant with boss cleanup specifics
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x07: SPAWN_1 — Spawn enemies / start ECL script (variant 1)
// ========================================
void StageScriptVM::op_SPAWN_1() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: SPAWN_1 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Activates enemy from loaded data
    // Starts ECL script execution on the spawned entity
    // Sets initial transform and render state
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x08: SPAWN_2 — Spawn enemies / start ECL script (variant 2)
// ========================================
void StageScriptVM::op_SPAWN_2() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: SPAWN_2 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Same as SPAWN_1 but may use a different spawn pattern
    // Handles mid-boss spawn transitions
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x09: TOGGLE_FLAG — XOR bit 1 on byte param
// ========================================
void StageScriptVM::op_TOGGLE_FLAG() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: TOGGLE_FLAG slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Toggles bit 1 on the byte value at param1
    // Used for stage state flag toggling (e.g. boss transition flags)
    // Implementation: target_byte ^= 2;  (bit 1 toggle)
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x0A: CHECK_CLEAR — Check if all enemies cleared -> advance
// ========================================
void StageScriptVM::op_CHECK_CLEAR() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: CHECK_CLEAR slot=%d\n", ip_, instr->slot);
    // Scans entity pool for remaining active enemies
    // If no enemies remain (excluding player/effects), sets enemies_cleared_ = true
    // When cleared, triggers transition to next phase
    enemies_cleared_ = true;
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x0B: WAIT — Set delay counter
// ========================================
void StageScriptVM::op_WAIT() {
    const StageScriptInstr* instr = current_instr();
    int32_t delay = static_cast<int32_t>(instr->param1);
    if (instr->size >= 2) {
        delay |= (static_cast<int32_t>(instr->data[0]) << 8);
    }
    printf("[StageVM] 0x%04zX: WAIT delay=%d frames\n", ip_, delay);
    wait_counter_ = delay;
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x0C: BGM_TEMPO — Set BGM tempo
// ========================================
void StageScriptVM::op_BGM_TEMPO() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: BGM_TEMPO slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Adjusts BGM playback tempo via audio subsystem
    // param1 encodes the tempo multiplier or target BPM delta
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x0D: BGM_STAGE — Set per-stage BGM parameters (8 subtypes)
// ========================================
void StageScriptVM::op_BGM_STAGE() {
    const StageScriptInstr* instr = current_instr();
    uint8_t subtype = instr->param1 & 0x07;
    printf("[StageVM] 0x%04zX: BGM_STAGE slot=%d subtype=%d\n",
           ip_, instr->slot, subtype);
    // 8 subtypes control different BGM aspects:
    //   0: Load stage BGM file
    //   1: Set BGM volume envelope
    //   2: Cross-fade between BGMs
    //   3: Pause/resume BGM
    //   4: Set BGM for boss transition
    //   5: End-of-stage BGM fade
    //   6: Loop point configuration
    //   7: BGM flag settings
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x0E: LOAD_ECL_1 — Load ECL script (variant 1)
// ========================================
void StageScriptVM::op_LOAD_ECL_1() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_ECL_1 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Loads an ECL file from th10.dat by name index
    // param1 selects which ECL name from the stage entry's eclPath
    // Calls EclFile::open_file() with the resolved path
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x0F: LOAD_ECL_2 — Load ECL script (variant 2)
// ========================================
void StageScriptVM::op_LOAD_ECL_2() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_ECL_2 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Same as LOAD_ECL_1 but loads additional sub-scripts
    // Handles multi-phase ECL loading for boss encounters
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x10: LOAD_ECL_3 — Load ECL script (variant 3)
// ========================================
void StageScriptVM::op_LOAD_ECL_3() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_ECL_3 slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Loads ECL with additional difficulty/rank-specific data
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x11: CLEANUP — Clean up enemy data
// ========================================
void StageScriptVM::op_CLEANUP() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: CLEANUP slot=%d\n", ip_, instr->slot);
    // Cleans up all temporary enemy allocations
    // Resets bullet pools, laser arrays, and effect entities
    // Called between phases to clear stage state
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x12: LOAD_BGM — Load stage BGM
// ========================================
void StageScriptVM::op_LOAD_BGM() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: LOAD_BGM slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Loads the BGM file specified by param1 index
    // Sets up BGM playback with looping and volume envelope
    // Uses BGM path from current StageEntry
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x13: SET_ENEMY_DATA — Set enemy data per stage (7 subtypes)
// ========================================
void StageScriptVM::op_SET_ENEMY_DATA() {
    const StageScriptInstr* instr = current_instr();
    uint8_t subtype = instr->param1 & 0x07;
    printf("[StageVM] 0x%04zX: SET_ENEMY_DATA slot=%d subtype=%d\n",
           ip_, instr->slot, subtype);
    // 7 subtypes configure enemy behavior per stage:
    //   0: HP scaling by difficulty
    //   1: Drop item tables
    //   2: Spell card time limits
    //   3: Enemy movement speed
    //   4: Bullet density multiplier
    //   5: Midboss health gate
    //   6: Boss spell card order
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x14: SCORE — Score display + stage advance
// Calls FUN_004175e0 in the original binary
// ========================================
void StageScriptVM::op_SCORE() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: SCORE slot=%d\n", ip_, instr->slot);
    // Displays stage clear score screen
    // Calculates bonuses: point items, spell card captures, graze
    // Calls score calculation engine (FUN_004175e0)
    // Advances stage index and transitions to next phase
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x15: BGM_FADEIN — Start BGM fade-in
// ========================================
void StageScriptVM::op_BGM_FADEIN() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: BGM_FADEIN slot=%d param1=%d\n",
           ip_, instr->slot, instr->param1);
    // Initiates BGM fade-in from current volume to target
    // param1 encodes fade duration in frames
    // Starts from silence (volume 0) and ramps up to full volume
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x16: FREE_ECL_1 — Free ECL script (variant 1)
// ========================================
void StageScriptVM::op_FREE_ECL_1() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: FREE_ECL_1 slot=%d\n", ip_, instr->slot);
    // Unloads ECL script data from memory
    // Called when transitioning between stage phases
    // Frees the EclFile references and decompressed bytecode
    ip_ += 4 + instr->size;
}

// ========================================
// Opcode 0x17: FREE_ECL_2 — Free ECL script (variant 2)
// ========================================
void StageScriptVM::op_FREE_ECL_2() {
    const StageScriptInstr* instr = current_instr();
    printf("[StageVM] 0x%04zX: FREE_ECL_2 slot=%d\n", ip_, instr->slot);
    // Same as FREE_ECL_1 but for secondary/additional ECLs
    // Handles cleanup of boss-specific scripts
    ip_ += 4 + instr->size;
}

// ========================================
// StageFlowController
// ========================================

void StageFlowController::init(StageScriptVM* vm) {
    vm_ = vm;
    phase_ = 0;
    frame_counter_ = 0;
    game_mode_ = GameMode::MODE_LOADING;
}

void StageFlowController::update() {
    frame_counter_++;

    switch (phase_) {
        case 0:  update_phase0();        break;
        case 1:  update_phase1();        break;
        case 2:  update_phase2();        break;
        default: update_phase_default(); break;
    }
}

void StageFlowController::update_phase0() {
    // Phase 0: Initialization
    //   Load stage BGM from StageEntry
    //   Parse STD file
    //   Initialize stage script VM
    //   Setup camera, player, and UI
    if (frame_counter_ > 60) {
        game_mode_ = GameMode::MODE_STAGE_START;
        phase_ = 1;
    }
}

void StageFlowController::update_phase1() {
    // Phase 1: In-game — main gameplay update
    //   Run stage script VM (execute one tick)
    //   Update all active entities
    //   Check bullet collisions
    //   Render frame
    game_mode_ = GameMode::MODE_STAGE_PLAY;

    if (vm_ && vm_->running()) {
        vm_->execute();
    }

    // Check for stage clear condition
    if (vm_ && !vm_->running()) {
        phase_ = 2;
        frame_counter_ = 0;
    }
}

void StageFlowController::update_phase2() {
    // Phase 2: Stage clear — results and transition
    //   Display score screen
    //   Fade BGM
    //   Transition to next stage or ending
    game_mode_ = GameMode::MODE_STAGE_CLEAR;

    if (frame_counter_ > 120) {
        game_mode_ = GameMode::MODE_EXIT;
        phase_ = 3;
    }
}

void StageFlowController::update_phase_default() {
    // Phases 3-16: Various transitions
    //   Phase 3: Exit / clean up
    //   Phase 4-6: Loading screens
    //   Phase 7-9: Dialog sequences
    //   Phase 10-12: Boss intro cutscenes
    //   Phase 13-16: Ending / credits
    phase_++;
    if (phase_ > 16) {
        phase_ = 0; // Loop or terminate
    }
}

} // namespace th10
