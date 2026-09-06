/* Raw Ghidra reference; not compilable reconstruction. Address: 004451C0 */

undefined4 __fastcall FUN_004451c0(void *param_1)

{
  uint uVar1;
  int in_EAX;
  undefined4 uVar2;
  
  uVar1 = *(uint *)(in_EAX + 0x35c);
  if ((((uVar1 & 1) != 0) && ((uVar1 & 2) != 0)) && (*(char *)(in_EAX + 0x2ff) != '\0')) {
    switch(uVar1 >> 0x16 & 0xf) {
    case 0:
      uVar2 = FUN_00443080(param_1);
      return uVar2;
    case 1:
      uVar2 = FUN_004436c0(param_1,in_EAX);
      return uVar2;
    case 2:
      uVar2 = FUN_00443290(param_1);
      return uVar2;
    case 3:
      uVar2 = FUN_00443910(param_1,in_EAX);
      return uVar2;
    case 4:
      uVar2 = FUN_00443f80(param_1);
      return uVar2;
    case 5:
      uVar2 = FUN_00444580();
      return uVar2;
    case 6:
      uVar2 = FUN_00443fb0();
      return uVar2;
    case 7:
      uVar2 = FUN_004445c0(param_1,in_EAX);
      return uVar2;
    case 8:
      uVar2 = FUN_00444760((int)param_1);
      return uVar2;
    case 9:
      uVar2 = FUN_00444ce0((int)param_1);
      return uVar2;
    default:
      return 0;
    }
  }
  return 0xffffffff;
}

