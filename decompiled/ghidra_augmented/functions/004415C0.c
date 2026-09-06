/* Raw Ghidra reference; not compilable reconstruction. Address: 004415C0 */

void __fastcall FUN_004415c0(void *param_1,int param_2,undefined2 *param_3)

{
  int in_EAX;
  void *extraout_ECX;
  
  for (; in_EAX != 0; in_EAX = in_EAX + -1) {
    FUN_00404f30(param_1,param_3);
    *(undefined2 *)(param_2 + 0x388) = *(undefined2 *)(param_2 + 900);
    param_2 = param_2 + 0x3ac;
    param_1 = extraout_ECX;
  }
  return;
}

