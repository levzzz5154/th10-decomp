// 0x0040ACE0. Test whether either of the two 16-bit key-mask words of a
// key-repeat state object intersects the requested mask. Retail passes the
// object in ECX and the mask in EAX, and returns 0/1 in EAX:
//
//   L8: xor  edx,edx            ; 33 d2
//               mov  dx,[ecx+6]         ; 66 8b 51 06
//               and  edx,eax            ; 23 d0
//               test dx,dx              ; 66 85 d2
//               jne  L9         ; 75 0e
//               movzx ecx,[ecx+4]       ; 0f b7 49 04
//               and  ecx,eax            ; 23 c8
//               test cx,cx              ; 66 85 c9
//               jne  L9         ; 75 03
//               xor  eax,eax            ; 33 c0
//               ret                     ; c3
//   L9: mov  eax,1
//               ret
//
// Only the low 16 bits of the mask matter, which is why the compiler may use a
// 32-bit AND and then test the 16-bit halves. Both retail call sites load the
// object address (0x00474E30, the same global that ?Update@KeyRepeatState@@
// runs on) into ECX and a literal mask (0x80) into EAX, so the body is
// compiled in the native LTCG cluster of build_support/layout/ltcg/input_mask_active.json.

struct KeyRepeatState {
    unsigned char  unknown_00[4];
    unsigned short pressed;     // +0x04, see src/game/eclview/score.cpp
    unsigned short unknown_06;  // +0x06
    __declspec(noinline) int InputMaskActive(unsigned short mask);
};

extern "C" KeyRepeatState g_input_keys_raw;   // 0x00474E30

#pragma code_seg(".text$01mask")
int KeyRepeatState::InputMaskActive(unsigned short mask) {
    return (mask & unknown_06) != 0 || (mask & pressed) != 0;
}
#pragma code_seg()
