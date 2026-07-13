/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00430250
 * Tracking name: FUN_00430250
 * Ghidra name: FUN_00430250
 * Tracked span: 208 bytes
 */


void __fastcall FUN_00430250(int param_1,int param_2)

{
  short sVar1;
  int in_EAX;
  
  sVar1 = *(short *)(in_EAX + 0x59cc + param_1 * 2);
  if (sVar1 != param_2) {
    if ((param_1 != 0) && (*(short *)(in_EAX + 0x59cc) == param_2)) {
      *(short *)(in_EAX + 0x59cc) = sVar1;
    }
    if ((param_1 != 1) && (*(short *)(in_EAX + 0x59ce) == param_2)) {
      *(undefined2 *)(in_EAX + 0x59ce) = *(undefined2 *)(in_EAX + 0x59cc + param_1 * 2);
    }
    if ((param_1 != 2) && (*(short *)(in_EAX + 0x59d0) == param_2)) {
      *(undefined2 *)(in_EAX + 0x59d0) = *(undefined2 *)(in_EAX + 0x59cc + param_1 * 2);
    }
    if ((param_1 != 3) && (*(short *)(in_EAX + 0x59d2) == param_2)) {
      *(undefined2 *)(in_EAX + 0x59d2) = *(undefined2 *)(in_EAX + 0x59cc + param_1 * 2);
    }
    if ((param_1 != 4) && (*(short *)(in_EAX + 0x59d4) == param_2)) {
      *(undefined2 *)(in_EAX + 0x59d4) = *(undefined2 *)(in_EAX + 0x59cc + param_1 * 2);
    }
    *(short *)(in_EAX + 0x59cc + param_1 * 2) = (short)param_2;
    FUN_0042f8b0(param_1);
    FUN_0043dc90(&DAT_00492590,0);
  }
  return;
}

