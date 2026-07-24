#include "th10/game/replay_file_load.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {
ReplayFileHeader header;unsigned char payload[32];unsigned char unpacked[0x500];bool load_ok=true,released;int decrypts,decompresses;
bool Load(const char* path,bool embedded,ReplayFileHeader** h,unsigned char** p,bool* owned){assert(std::strcmp(path,"replay/demo.rpy")==0);assert(!embedded);if(!load_ok)return false;*h=&header;*p=payload;*owned=true;return true;}
unsigned char* Allocate(unsigned size){assert(size==sizeof(unpacked));return unpacked;}
void Decrypt(unsigned char*,unsigned,unsigned char seed,unsigned int step){if(decrypts==0){assert(seed==0xAA&&step==0xE1);}else{assert(seed==0x3D&&step==0x7A);}++decrypts;}
void Decompress(const unsigned char*,unsigned,unsigned char* out,unsigned){std::memset(out,0,sizeof(unpacked));*(int*)(out+0x4C)=2;ReplayFileEntry* a=(ReplayFileEntry*)(out+0x64);a->slot=2;a->script_count=3;a->extra_size=4;ReplayFileEntry* b=(ReplayFileEntry*)((unsigned char*)a+0x1C4+4);b->slot=5;b->script_count=1;b->extra_size=0;++decompresses;}
void Release(unsigned char* p){assert(p==payload);released=true;}
void TestLoad(){std::memset(&header,0,sizeof(header));header.magic=0x72303174;header.version=5;header.packed_size=sizeof(payload);header.unpacked_size=sizeof(unpacked);ReplayFileState state={};ReplayFileEnv env={false,Load,Allocate,Decrypt,Decompress,Release};released=false;decrypts=decompresses=0;assert(ReplayArchive_Load(&state,"demo.rpy",&env)==0);assert(std::strcmp(state.name,"demo.rpy")==0);assert(decrypts==2&&decompresses==1&&released);assert(state.entries[2]&&state.entries[5]);assert(state.script_data[2]==(unsigned char*)state.entries[2]+0x1C4);assert(state.script_end[2]==state.script_data[2]+18);assert(state.script_end[5]==state.script_data[5]+6);}
void TestFailure(){ReplayFileState state={};ReplayFileEnv env={false,Load,Allocate,Decrypt,Decompress,Release};load_ok=false;assert(ReplayArchive_Load(&state,"demo.rpy",&env)==-1);load_ok=true;header.magic=0;released=false;assert(ReplayArchive_Load(&state,"demo.rpy",&env)==-1);assert(released);}
}
int main(){TestLoad();TestFailure();std::puts("BATCH21_TESTS_PASS");}
