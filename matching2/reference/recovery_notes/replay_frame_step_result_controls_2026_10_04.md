# Replay frame-step result-type controls, 2026-10-04

The 68-byte callback at `0x0042A3E0` remains assembly. A fresh isolated copy of the current production project was probed with the ordinary fastcall entry `?ReplayFrameStep@@YIHPAUFrameStepReplay@@@Z`; its physical callback ABI is the observed one-pointer ECX input and EAX result.

The plain return baseline emits 68 bytes and reproduces the documented failure-branch target residual. A copied result value type with reference-returning assignment and an implicitly converted return retains the same failure targets and 68-byte extent. Constructed result assignments at the branch join do likewise. Constructing the result before the scene-flag test instead emits 63 bytes and is rejected by the full contribution gate.

The actual compiled symbol was verified and the scratch manifest corrected before recording these normal probe outcomes. Initial name-resolution failures are not byte-gate measurements. Sources and authoritative final probe logs are preserved under `matching2/build/experiments/replay_frame_step_2026_10_04/`; the disposable project is restored to the plain baseline. No compiler barrier, volatile object, assembly or output patch was added. The result-type technique does not keep the late join needed by the retail dual-return layout, so repeating it is not a justified next step.

No maintained source, header, layout or region ownership changed. The last verified complete EXACT executable still equals the retail oracle.
