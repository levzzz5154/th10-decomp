#include "th10/render/quad_batch.hpp"

// The entry takes an animation entity in ECX. Keep the provisional wrapper
// type separate from RenderEntity until its original class identity is known.
struct FanSubmitter_00445880 : RenderEntity {
    int Run();
};

// 0x00445880: send this entity, its +0x358 fan data, and fan count 0x21 to the
// animation manager. A regular non-static member has the retail __thiscall
// entry ABI (this in ECX); DrawFan's result is ignored and this wrapper returns 0.
int FanSubmitter_00445880::Run() {
    data_00491c10->DrawFan(this, strip_vertices, 0x21);
    return 0;
}
