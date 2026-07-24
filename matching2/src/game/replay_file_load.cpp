#include "th10/game/replay_file_load.hpp"

#include <cstdio>
#include <cstring>

// 0x0042A200 - loads replay data from disk or the embedded resource path,
// validates its header, applies both retail cipher passes, decompresses it,
// and indexes up to six replay-player records by their encoded slot number.
int ReplayArchive_Load(ReplayFileState* state, const char* name,
                       ReplayFileEnv* env) {
	std::strncpy(state->name,name,sizeof(state->name)-1);
	state->name[sizeof(state->name)-1]=0;
	char path[256]; std::snprintf(path,sizeof(path),"replay/%s",name);
	unsigned char* payload=0; bool payload_owned=false;
	if(!env->load_source(path,env->embedded_mode,&state->header,&payload,
	                    &payload_owned)) return -1;
	if(state->header==0||state->header->magic!=0x72303174u||
	   state->header->version!=5){if(payload_owned&&payload)env->release_payload(payload);return -1;}
	state->decompressed=env->allocate(state->header->unpacked_size);
	if(state->decompressed==0){if(payload_owned&&payload)env->release_payload(payload);return -1;}
	env->decrypt(payload,state->header->packed_size,0xAA,0xE1);
	env->decrypt(payload,state->header->packed_size,0x3D,0x7A);
	env->decompress(payload,state->header->packed_size,state->decompressed,
	                state->header->unpacked_size);
	state->active_data=state->decompressed;
	for(int i=0;i<8;++i){state->entries[i]=0;state->script_data[i]=0;state->script_end[i]=0;}
	int count=*(int*)(state->decompressed+0x4C); if(count>=8)count=6;
	unsigned char* cursor=state->decompressed+0x64;
	for(int index=0;index<count;++index){
		ReplayFileEntry* entry=(ReplayFileEntry*)cursor;
		if(entry->slot>=0&&entry->slot<8){state->entries[entry->slot]=entry;
			state->script_data[entry->slot]=cursor+0x1C4;
			state->script_end[entry->slot]=state->script_data[entry->slot]+entry->script_count*6;}
		cursor+=0x1C4+entry->extra_size;
	}
	if(payload_owned&&payload)env->release_payload(payload);
	return 0;
}
