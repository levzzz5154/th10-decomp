#include "../../../src/core/zwave/sound_stream_fill_model.cpp"
#include "sound_fill_read.cpp"
#include "sound_fill_rewind.cpp"
#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) int __stdcall FillContext(SoundStream** streams,WaveBuffer** buffers,unsigned int* repeats,bool* modes,int count) {
 int result=0;
 while (count--) { SoundStream* stream=*streams++; result |= ArchiveRewind(stream->reader,*modes++); result |= SoundStreamFill(stream,*buffers++,*repeats++); }
 return result;
}
#pragma code_seg()
