/* Raw Ghidra reference; not compilable reconstruction. Address: 00427D80 */

void __fastcall FUN_00427d80(int *param_1,int param_2)

{
  int iVar1;
  int *in_EAX;
  
  iVar1 = param_1[1];
  *in_EAX = *param_1 * param_2;
  in_EAX[1] = iVar1 * param_2;
  return;
}

