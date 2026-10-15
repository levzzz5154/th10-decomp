// The laser manager's spawn and the two laser constructors.
#include "th10/game/laser_spawn_0041c510.hpp"

void* __cdecl operator new(unsigned int size);

// 0x0041C510: create a laser of a kind and set it up from these parameters.
//
// Ids count up and skip zero. Each kind links its new laser and runs its
// virtual set-up; an unknown kind only consumes an id. The parameters arrive
// in EDI, the manager in ESI and the kind on the stack. A failed allocation
// is not checked.
#pragma code_seg(".text$a03spawn")
int LaserSpawnParameters::SpawnIn(LaserManager_0041c510* manager, int kind) const {
    if (manager->count >= 256)
        return 0;
    if (++manager->next_id == 0)
        manager->next_id = 1;
    LaserBase* laser;
    switch (kind) {
    case 0: {
        LineLaser_0041c5b0* line =
            static_cast<LineLaser_0041c5b0*>(operator new(sizeof(LineLaser_0041c5b0)));
        laser = line ? LineLaser_Construct_0041c5b0(line) : 0;
        manager->Append(laser);
        laser->Methods()->Initialize(this);
        break;
    }
    case 1: {
        BeamLaser* beam =
            static_cast<BeamLaser*>(operator new(sizeof(BeamLaser)));
        laser = beam ? BeamLaser_Construct_0041c680(beam) : 0;
        manager->Append(laser);
        laser->Methods()->Initialize(this);
        break;
    }
    }
    return manager->next_id;
}

// 0x0041C5B0: construct a line laser in raw storage: the common part, the
// vtable, cleared parameters and the two sprites. The retail laser arrives in EBX; this unselected native graph may
// choose its own register for that internal call.
#pragma code_seg(".text$a05line")
LineLaser_0041c5b0* __fastcall LineLaser_Construct_0041c5b0(LineLaser_0041c5b0* self) {
    LaserBase_Construct_0041c030(self);
    self->vtable = &g_line_laser_vtable;
    self->params.Construct();
    self->beam.Construct();
    self->flare.Construct();
    return self;
}

// 0x0041C680: construct a beam laser the same way. The retail laser arrives in EBX; this unselected native graph may
// choose its own register for that internal call.
#pragma code_seg(".text$a07beam")
BeamLaser* __fastcall BeamLaser_Construct_0041c680(BeamLaser* self) {
    LaserBase_Construct_0041c030(self);
    self->vtable = &g_beam_laser_vtable;
    self->params.Construct();
    self->beam.Construct();
    self->flare.Construct();
    return self;
}
#pragma code_seg()
