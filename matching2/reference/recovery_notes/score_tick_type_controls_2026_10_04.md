# Score tick type/control-flow controls, 2026-10-04

Fresh isolated project: `matching2/build/experiments/score_tick_2026_10_04/project`. The current production project was copied before overlaying the preserved full tick model, callback, node header and cluster. Production ownership was not modified.

The preserved baseline still emits 272 bytes for the required 274-byte score-record tick at `0x0041C330`. A retirement-count value type with reference-returning increment emits 276 bytes: it adds AL/CL moves and retains the wrong combined destruction setup. A state value type still emits 272 bytes. A state switch emits 206 bytes because it merges the two separate retirement tails; its compactness is incompatible with retail's complete body and cannot be promoted.

An explicit callback-table model using `__thiscall` function pointers is rejected by the pinned compiler with C4234: this keyword is reserved for future use in that declaration. No fabricated extra register arguments or assembly adapter was added to bypass the compiler contract.

`measurements.json` records complete native MAP contribution sizes. Each variant's source/header, probe log, compiler output, native map and executable are retained under the experiment directory. The disposable project is restored to the coherent virtual-method baseline. The next useful attempt must preserve retail's separate early virtual dispatch preparation and two distinct unlink tails; these counter/state wrappers do not accomplish it.
