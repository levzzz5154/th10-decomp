/* Raw Ghidra reference; not compilable reconstruction. Address: 0040AD20 */

uint __fastcall FUN_0040ad20(uint param_1,uint *param_2)

{
  uint uVar1;
  
  uVar1 = param_2[2];
  if (uVar1 == 0) {
    *param_2 = param_1;
    return param_1;
  }
  if ((int)uVar1 <= (int)param_1) {
    *param_2 = uVar1 - 1;
    return uVar1 - 1;
  }
  uVar1 = ((int)param_1 < 0) - 1 & param_1;
  *param_2 = uVar1;
  return uVar1;
}

