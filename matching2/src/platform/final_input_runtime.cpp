#include "th10/platform/final_input_runtime.hpp"
namespace th10::input_final {
// 0x0044A5F0 - input_final::Poll. The state core below (edge detection
// pressed/released, held/repeat counters, 16-bit return value) matches
// the retail tail exactly. INJECTION BOUNDARY: the retail DirectInput
// device reads (dword_491C38 vtable +36/+28), the GetKeyboardState
// fallback, the dword_491FF4&0x200 mode select, the dword_4924FC gate,
// sub_44A190 and the per-player block dword_474E30+53*a1 are elided
// here - the injected k[256]/m[16]/joy/enabled arguments are the host
// adapter's input source.
std::uint16_t Poll(State&s,const std::array<std::uint8_t,256>&k,const std::array<int,16>&m,std::uint16_t joy,bool enabled){std::uint16_t bits=0;if(enabled)for(int i=0;i<16;++i)if(m[i]>=0&&m[i]<256&&(k[m[i]]&0x80))bits|=std::uint16_t(1u<<i);bits|=joy;s.previous=s.current;s.current=bits;s.pressed=(s.previous^bits)&bits;s.released=(s.previous^bits)&~bits;s.repeat=0;for(int i=0;i<16;++i){if(bits&(1u<<i)){if(++s.held[i]>25){s.repeat|=1u<<i;s.held[i]-=8;}}else s.held[i]=0;}return bits;}
}
