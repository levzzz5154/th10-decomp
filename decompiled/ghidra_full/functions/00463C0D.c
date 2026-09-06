/* Raw Ghidra reference; not compilable reconstruction. Address: 00463C0D */

void __cdecl FUN_00463c0d(int param_1,uint param_2)

{
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUControlWord;
  float10 in_ST0;
  float10 extraout_ST0;
  undefined4 unaff_retaddr;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
      FUN_00464f2c();
    }
LAB_00463c9c:
    if (DAT_00477384 == 0) {
      __startOneArgErrorHandling(&DAT_00477060,0xd,in_FPUControlWord,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_00464f15();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fpatan(SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)),in_ST0);
    }
    else if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_00463c9c;
    if (DAT_00477384 == 0) {
      __math_exit(&DAT_00477060,0xd,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  return;
}

