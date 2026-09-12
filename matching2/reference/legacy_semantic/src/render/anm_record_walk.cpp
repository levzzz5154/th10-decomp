#include "th10/render/anm_record_walk.hpp"

#include <cmath>

namespace {
}

// 0x00403A30 - walks records of the requested type, culls each projected box,
// marks accepted records, applies slot offsets/scales to id-zero VMs, toggles
// the special render state from VM mode bits, draws them, and updates counters.
int AnmRecordTable_DrawVisible(AnmRecordWalkState* state, int required_type,
                               AnmRecordWalkEnv* env) {
	bool special=false;
	for(int r=0;r<state->record_count;++r){
		AnmRecord* record=state->records[r];
		if(record->type!=required_type) continue;
		if(ProjectedBox_IsOutside(state->cull_source,&record->box,
		                          &record->translation,state->maximum_distance_squared,
		                          env->cull_env)!=0){++state->rejected_count;continue;}
		record->flags|=2u;
		for(int s=0;s<record->slot_count;++s){
			AnmRecordSlot& slot=record->slots[s];
			if(slot.id!=0||slot.vm==0) continue;
			AnmRecordVm* vm=slot.vm;
			unsigned mode=vm->flags&0x03C00000u;
			if(mode>=0x01000000u){
				vm->position.x=slot.offset.x+record->translation.x;
				vm->position.y=slot.offset.y+record->translation.y;
				vm->position.z=slot.offset.z+record->translation.z;
				if(slot.desired_width!=0&&vm->resource_height!=0){vm->scale_x=slot.desired_width/vm->resource_height;vm->flags|=8u;}
				if(slot.desired_height!=0&&vm->resource_width!=0){vm->scale_y=slot.desired_height/vm->resource_width;vm->flags|=8u;}
			}
			bool wanted=(vm->flags&0x03C00000u)==0x02000000u;
			if(wanted!=special){env->set_special_render_state(wanted);special=wanted;}
			env->draw_vm(vm);++state->drawn_vm_count;
		}
		++state->accepted_count;
	}
	return 0;
}
