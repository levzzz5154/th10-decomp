#pragma once

// Segmented streaming buffer creation with end-of-segment notifications (retail 0x0044C8F0).
// Retail function 0x0044C8F0.
struct StreamBufferDesc{unsigned flags,segment_count,segment_size,file_size;unsigned format[4];void*event;};
struct StreamNotice{unsigned position;void*event;};struct StreamRecord{StreamBufferDesc desc;void*buffer;void*owner;void*event;unsigned cursor;};
struct StreamCreateEnv{void*device;void*owner;int(*open)(unsigned);void*(*create_buffer)(unsigned,unsigned,const unsigned*);void*(*query_notify)(void*);int(*set_notices)(void*,const StreamNotice*,unsigned);void(*release)(void*);StreamRecord*(*allocate_stream)();};
unsigned SoundStream_CreateSegmented(const StreamBufferDesc*,StreamRecord**,const StreamCreateEnv*);
