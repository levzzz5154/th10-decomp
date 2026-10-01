#include "th10/platform/native_font_start.hpp"
#include "../../layout/ltcg/native_font_start/release_surface.cpp"
#include "../../layout/ltcg/native_font_start/create_surface.cpp"
#pragma code_seg(".text$a08font")
extern "C" void __cdecl InitializeFontCache_00437a00() {
    if (!FontSurface_Create_00436af0(&data_00474cb0,0x400,0x40,0x1a))
        FontSurface_Create_00436af0(&data_00474cb0,0x400,0x40,0x15);
    unsigned char* bytes=(unsigned char*)&data_00474cb0;
    for (unsigned int index=0;index<256;++index) {
        unsigned short next=data_004918b0.Next();
        bytes[index]=(unsigned char)(next>>9);
    }
    data_00491868[14]=CreateFontA(32,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[13]=CreateFontA(34,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[12]=CreateFontA(36,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[11]=CreateFontA(38,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[10]=CreateFontA(40,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[9]=CreateFontA(42,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[8]=CreateFontA(44,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[7]=CreateFontA(46,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[6]=CreateFontA(48,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[5]=CreateFontA(50,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[4]=CreateFontA(52,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[3]=CreateFontA(54,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[2]=CreateFontA(56,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[1]=CreateFontA(58,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
    data_00491868[0]=CreateFontA(60,0,0,0,400,0,0,0,0x80,0,0,4,0x11,data_0046f36c);
}
#pragma code_seg()

#include "../../layout/ltcg/native_font_start/clip.cpp"
#include "../../layout/ltcg/native_font_start/stop_worker.cpp"
#include "../unidentified/FUN_004201b0_004201b0.cpp"

#include "th10/platform/native_game_input.hpp"
#include "../../layout/ltcg/native_game_input/logger.cpp"
#include "../../layout/ltcg/native_game_input/release_input.cpp"
#include "dinput_device_setup.cpp"
#include "../unidentified/FUN_0043ba90_0043ba90.cpp"
