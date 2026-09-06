/* Raw Ghidra reference; not compilable reconstruction. Address: 00405410 */

void FUN_00405410(int param_1)

{
  int *in_EAX;
  
  if ((in_EAX[4] & 1U) == 0) {
    in_EAX[1] = 0;
    *in_EAX = -999999;
    in_EAX[2] = 0;
    in_EAX[3] = (int)&DAT_00476f78;
    in_EAX[4] = in_EAX[4] | 1;
  }
  in_EAX[1] = param_1;
  *in_EAX = param_1 + -1;
  in_EAX[2] = (int)(float)param_1;
  return;
}

