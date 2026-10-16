// The laser manager's spawn and the two laser constructors.
#include "th10/game/laser_spawn.hpp"

void* __cdecl operator new(unsigned int size);

// 0x0041C510: create a laser of a kind and set it up from these parameters.
//
// Ids count up and skip zero. Each kind links its new laser and runs its
// virtual set-up; an unknown kind only consumes an id. The parameters arrive
// in EDI, the manager in ESI and the kind on the stack. A failed allocation
// is not checked.
#pragma code_seg(".text$0041c510_fn")
int LaserSpawnParameters::SpawnIn(LaserManager2* manager, int kind) const {
    if (manager->count >= 256)
        return 0;
    if (++manager->next_id == 0)
        manager->next_id = 1;
    LaserBase* laser;
    switch (kind) {
    case 0: {
        LineLaser2* line =
            static_cast<LineLaser2*>(operator new(sizeof(LineLaser2)));
        laser = line ? LineLaser_Construct2(line) : 0;
        manager->Append(laser);
        laser->Methods()->Initialize(this);
        break;
    }
    case 1: {
        BeamLaser* beam =
            static_cast<BeamLaser*>(operator new(sizeof(BeamLaser)));
        laser = beam ? BeamLaser_Construct2(beam) : 0;
        manager->Append(laser);
        laser->Methods()->Initialize(this);
        break;
    }
    }
    return manager->next_id;
}

// 0x0041C5B0: construct a line laser in raw storage: the common part, the
// vtable, cleared parameters and the two sprites. The laser arrives in EBX.
#pragma code_seg(".text$0041c5b0_fn")
LineLaser2* __fastcall LineLaser_Construct2(LineLaser2* self) {
    LaserBase_Construct2(0, self);
    self->vtable = &g_line_laser_vtable;
    self->params.Construct();
    self->beam.Construct();
    self->flare.Construct();
    return self;
}

// 0x0041C680: construct a beam laser the same way. The laser arrives in EBX.
#pragma code_seg(".text$0041c680_fn")
BeamLaser* __fastcall BeamLaser_Construct2(BeamLaser* self) {
    LaserBase_Construct2(0, self);
    self->vtable = &g_beam_laser_vtable;
    self->params.Construct();
    self->beam.Construct();
    self->flare.Construct();
    return self;
}
#pragma code_seg()
