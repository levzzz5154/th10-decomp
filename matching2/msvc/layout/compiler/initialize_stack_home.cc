// GCC 16.2 experimental RTL pass. This file contains no target-program names,
// addresses, byte strings, inline assembly, or assembly-output callbacks.
//
// Choose the value about to initialize a new one-word local as the value
// pushed to reserve that local. The original volatile initialization remains.
// Restrict the transformation to a scratch-register reservation emitted by
// GCC's own prologue peephole: changing a saved-register push is forbidden.
#include "gcc-plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "rtl.h"
#include "tree-pass.h"
#include "function.h"
#include "context.h"
#include "memmodel.h"
#include "insn-config.h"
#include "emit-rtl.h"
#include "recog.h"
#include "df.h"

int plugin_is_GPL_compatible;

namespace {
const pass_data home_pass_data = {
    RTL_PASS, "initialize_stack_home", OPTGROUP_NONE, TV_NONE,
    0, 0, 0, 0, 0
};

bool stack_register(rtx value) {
    return REG_P(value) && REGNO(value) == STACK_POINTER_REGNUM;
}

bool ordinary_word_register(rtx value) {
    return REG_P(value) && GET_MODE(value) == SImode &&
           GENERAL_REGNO_P(REGNO(value)) && !stack_register(value);
}

bool one_word_frame_adjustment(rtx note) {
    if (!note) return false;
    rtx expression = XEXP(note, 0);
    if (!expression || GET_CODE(expression) != SET || !stack_register(SET_DEST(expression)))
        return false;
    rtx value = SET_SRC(expression);
    return GET_CODE(value) == PLUS && stack_register(XEXP(value, 0)) &&
           CONST_INT_P(XEXP(value, 1)) && INTVAL(XEXP(value, 1)) == -4;
}

bool local_word_store(rtx_insn *instruction, rtx *source) {
    if (!NONJUMP_INSN_P(instruction)) return false;
    rtx set = single_set(instruction);
    if (!set) return false;
    rtx memory = SET_DEST(set);
    rtx value = SET_SRC(set);
    if (!MEM_P(memory) || GET_MODE(memory) != SImode ||
        !stack_register(XEXP(memory, 0)) || !MEM_VOLATILE_P(memory) ||
        !ordinary_word_register(value))
        return false;
    tree declaration = MEM_EXPR(memory);
    if (!declaration || TREE_CODE(declaration) != VAR_DECL ||
        DECL_CONTEXT(declaration) != current_function_decl ||
        TREE_STATIC(declaration) || DECL_EXTERNAL(declaration))
        return false;
    *source = value;
    return true;
}

class initialize_stack_home final : public rtl_opt_pass {
public:
    explicit initialize_stack_home(gcc::context *context)
        : rtl_opt_pass(home_pass_data, context) {}

    unsigned int execute(function *) override {
        // This prototype is deliberately restricted to the 32-bit x86 ABI.
        if (GET_MODE(stack_pointer_rtx) != SImode) return 0;
        unsigned changed = 0;
        for (rtx_insn *instruction = get_insns(); instruction;
             instruction = NEXT_INSN(instruction)) {
            if (!NONJUMP_INSN_P(instruction) ||
                !RTX_FRAME_RELATED_P(instruction)) continue;
            rtx pattern = PATTERN(instruction);
            if (GET_CODE(pattern) != PARALLEL || XVECLEN(pattern, 0) != 2)
                continue;
            rtx set = XVECEXP(pattern, 0, 0);
            rtx barrier = XVECEXP(pattern, 0, 1);
            if (GET_CODE(set) != SET || GET_CODE(barrier) != CLOBBER ||
                !MEM_P(XEXP(barrier, 0)) ||
                GET_MODE(XEXP(barrier, 0)) != BLKmode ||
                GET_CODE(XEXP(XEXP(barrier, 0), 0)) != SCRATCH)
                continue;
            rtx memory = SET_DEST(set);
            rtx scratch = SET_SRC(set);
            if (!MEM_P(memory) || GET_MODE(memory) != SImode ||
                GET_CODE(XEXP(memory, 0)) != PRE_DEC ||
                !stack_register(XEXP(XEXP(memory, 0), 0)) ||
                !ordinary_word_register(scratch))
                continue;

            // Only the immediately preceding compiler scratch clobber proves
            // that the push reserves space rather than saves a live register.
            rtx_insn *previous = prev_nonnote_nondebug_insn(instruction);
            if (!previous || !NONJUMP_INSN_P(previous) ||
                BLOCK_FOR_INSN(previous) != BLOCK_FOR_INSN(instruction) ||
                GET_CODE(PATTERN(previous)) != CLOBBER ||
                !rtx_equal_p(XEXP(PATTERN(previous), 0), scratch))
                continue;
            rtx adjustment = find_reg_note(instruction, REG_CFA_ADJUST_CFA, 0);
            if (!one_word_frame_adjustment(adjustment)) continue;
            bool other_frame_note = false;
            for (rtx note = REG_NOTES(instruction); note; note = XEXP(note, 1))
                if (REG_NOTE_KIND(note) != REG_CFA_ADJUST_CFA &&
                    REG_NOTE_KIND(note) != REG_DEAD)
                    other_frame_note = true;
            if (other_frame_note) continue;

            rtx_insn *following = next_nonnote_nondebug_insn(instruction);
            rtx value = nullptr;
            if (!following || BLOCK_FOR_INSN(following) != BLOCK_FOR_INSN(instruction) ||
                !local_word_store(following, &value) || rtx_equal_p(value, scratch))
                continue;

            // Validate through GCC's target recognizer; retain the original
            // stack-memory barrier, stack effect, frame notes and local store.
            if (!validate_change(instruction, &SET_SRC(set), value, false))
                continue;
            rtx dead = find_reg_note(instruction, REG_DEAD, scratch);
            if (dead) remove_note(instruction, dead);
            df_insn_rescan(instruction);
            ++changed;
        }
        if (dump_file)
            fprintf(dump_file, "Initialized %u one-word local reservations.\n", changed);
        return 0;
    }
};
}

int plugin_init(plugin_name_args *arguments, plugin_gcc_version *version) {
    if (!plugin_default_version_check(version, &gcc_version)) return 1;
    register_pass_info information;
    information.pass = new initialize_stack_home(g);
    information.reference_pass_name = "peephole2";
    information.ref_pass_instance_number = 1;
    information.pos_op = PASS_POS_INSERT_AFTER;
    register_callback(arguments->base_name, PLUGIN_PASS_MANAGER_SETUP, nullptr, &information);
    return 0;
}
