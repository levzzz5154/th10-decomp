/* Raw Ghidra reference; not compilable reconstruction. Address: 00446500 */

void __fastcall FUN_00446500(byte *param_1,int *param_2)

{
  int *in_EAX;
  
  if (param_1[3] != 0) {
    *in_EAX = *in_EAX + (uint)param_1[2];
    in_EAX[1] = in_EAX[1] + (uint)param_1[1];
    in_EAX[2] = in_EAX[2] + (uint)*param_1;
    *param_2 = *param_2 + 1;
  }
  return;
}

