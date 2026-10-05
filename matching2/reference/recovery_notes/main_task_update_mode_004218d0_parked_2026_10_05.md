# Main task mode switch 0x004218D0 - parked (2026-10-05)

Region is still assembly. The unselected model in
`layout/ltcg/sound_fade_wave18_mode.cpp` (cluster `sound_fade_real_tasks`) is
686 bytes against 666 and was left as it was so that the cluster layout stays
valid. A better body exists (below): 29 differing instructions over the 572
code bytes, same entry (four pushes, receiver EAX -> EDI, shared `return 1`).

## What the better body fixes

- `if (current_mode != next_mode) { ... } return 1;` instead of an early
  `return 1`: the early return shrink-wraps and moves the receiver to EDI.
- source order of the outer cases is 0, 3, 4, 15, 7, 12, 11, 10, 13, 14 (block
  order follows it);
- case 4 and case 15 are inner switches on `previous_mode`.

## What is still different

Retail places the unlock-and-return block (`current_mode = next_mode;` inlined
`LeaveSlot(5)`; `return 1`) directly after case 4's `ModeCreateProgressWave18()`
and every later case jumps *backwards* to it; inner case 14 of case 4 and the
tail of case 15 jump backwards to that create call. The model keeps the block
at the end of the function and keeps separate `call create` copies.

Under reverse post-order a join block cannot precede its predecessors, so at
layout time the later cases did not flow into that block: each had its own
copy of the exit, merged afterwards by the 20-byte common tail rule (survivor
= first copy, the one after case 4). Tried without success:

- one explicit second copy reached by `goto` from the later cases (right
  position, but the two-instruction head of the copy is hoisted into every
  case);
- a copy after every case through a macro (another survivor is kept);
- `return 1` inside the `if`, `if/else` returns, early return;
- letting LTCG inline a plain `LeaveSlot` (inlines the case 3 call too and
  changes the receiver register).

Open question: which construct makes c2 copy the exit sequence into each
`jmp` site (FgCodeMotion only does that for the real epilogue).

Case 10 also stores `ui_mode`/`next_mode` before reading `data_00474c80` in
retail; the model stores them after.

## Fast rig

`cl /O2` on the model alone reproduces the cluster's block order, so shapes can
be tested in two seconds per variant (compile, then compare the sequence of
call targets).

## Better body

    int MainTaskStateWave18::UpdateMode() {
        if (current_mode != next_mode) {
            data_004660b0(critical_sections[5]);
            ++lock_depth[5];
            previous_mode = current_mode;
            overlay_color = 0xFF000000;
            switch (next_mode) {
            case 0:
                next_mode = 1;
                created_state = ModeCreateStateWave18();
                if (created_state) break;
                next_mode = 3;
            case 3:
                ModeReleaseGlobalsWave18();
                LeaveSlot(5);
                return 4;
            case 4:
                switch (previous_mode) {
                case 7:
                    DestroyOwned_00418150(data_00477810);
                case 1:
                case 2:
                    ModeCreateProgressWave18();
                    break;
                case 14:
                    ScoreOwnedObject_Destroy(data_00477700);
                    ModeCreateProgressWave18();
                    break;
                }
                break;
            case 15:
                switch (previous_mode) {
                case 14:
                    ScoreOwnedObject_Destroy(data_00477700);
                    break;
                case 7:
                    DestroyOwned_00418150(data_00477810);
                case 2:
                    break;
                default:
                    goto done;
                }
                next_mode = 4;
                data_00491c00 = 3;
                ModeCreateProgressWave18();
                break;
            case 7:
                if (previous_mode == 4) DestroyOwned_0042cdb0(data_0047784c);
                ui_mode = 1;
                ModeCreateUiWave18(0);
                break;
            case 12:
                if (previous_mode == 4) DestroyOwned_0042cdb0(data_0047784c);
                next_mode = 7;
                ui_mode = 1;
                ModeCreateUiWave18(1);
                break;
            case 11: {
                unsigned int argument = reinterpret_cast<GameUiArgumentWave18*>(data_00477810)->argument;
                ui_mode = 0;
                if (previous_mode == 7) DestroyOwned_00418150(data_00477810);
                next_mode = 7;
                ModeCreateUiWave18(argument);
                break;
            }
            case 10:
                DestroyOwned_00418150(data_00477810);
                ui_mode = 1;
                next_mode = 7;
                data_00474c7c = data_00474c80;
                data_00477848 = data_00474788 + data_00474c80;
                ModeCreateUiWave18(0);
                break;
            case 13:
                DestroyOwned_00418150(data_00477810);
                ui_mode = 1;
                next_mode = 7;
                ModeCreateUiWave18(0);
                break;
            case 14:
                if (previous_mode == 7) DestroyOwned_00418150(data_00477810);
                ModeCreateSmallWave18();
                break;
            }
        done:
            current_mode = next_mode;
            data_004660b4(critical_sections[5]);
            --lock_depth[5];
        }
        return 1;
    }
