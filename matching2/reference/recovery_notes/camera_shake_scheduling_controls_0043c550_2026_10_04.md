# Camera shake 0x0043C550: three distinct scheduling controls

The previous genuine-graph 439-byte model has one FIDIV scheduling residual.
This pass tests controls outside the already exhausted source/helper/axis matrix:

- A volatile view of the existing integer divisor emits 447 bytes. It forces an
  extra load/store and still places FIDIV before the second RNG advancement.
- Disabling global optimization for the callback emits 701 bytes.
- Enabling size optimization emits 388 bytes, with an EBP frame and cached RNG
  constants; the original scheduling window and native layout are not preserved.

All three use the saved complete genuine caller graph and the current native
MSVC probe tool. Their complete MAP contributions are measured. Subsequent
helper addresses drift because these complete callback sizes differ; no gaps
were adjusted to disguise that, and nothing was promoted or truncated.

Sources, native images, maps and measurement receipts are archived in
`matching2/build/experiments/camera_shake_scheduling_controls_2026_10_04`.
Scratch project: `/tmp/th10-camera-order/msvc`. No maintained code, layout,
compiler flag contract, or region ownership changed. The ordinary genuine
439-byte model remains the best known candidate. Avoid repeating the volatile
local-divisor and these per-function optimization controls.

The sound-factory body review confirms the existing 692-byte model still has
its documented segment-count/zero-constant register allocation differences;
no new exact factory implementation is claimed.
