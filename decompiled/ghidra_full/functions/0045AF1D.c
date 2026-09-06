/* Raw Ghidra reference; not compilable reconstruction. Address: 0045AF1D */

int __cdecl
FUN_0045af1d(int param_1,byte *param_2,uint param_3,byte *param_4,undefined2 *param_5,uint param_6)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar2 = param_2;
  uVar3 = param_6;
  if (param_6 == 0) {
    uVar3 = *(uint *)(param_1 + 0x4c);
  }
  if (param_3 != 0) {
    param_6 = param_3;
    pbVar5 = param_4;
    if (param_3 != 0) {
      do {
        bVar1 = *pbVar5;
        if (bVar1 == 0) break;
        if (bVar1 == 0x25) {
          pbVar6 = pbVar5 + 1;
          bVar1 = *pbVar6;
          if (bVar1 == 0x23) {
            pbVar6 = pbVar5 + 2;
          }
          iVar4 = __expandtime(&param_2,param_1,param_5,uVar3,(uint)(bVar1 == 0x23));
          if (iVar4 == 0) goto LAB_0045afd3;
        }
        else {
          if (((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (uint)bVar1 * 2) & 0x80) != 0) &&
             (1 < param_6)) {
            pbVar5 = pbVar5 + 1;
            if (*pbVar5 == 0) goto LAB_0045afd3;
            *param_2 = bVar1;
            param_2 = param_2 + 1;
            param_6 = param_6 - 1;
          }
          *param_2 = *pbVar5;
          param_2 = param_2 + 1;
          param_6 = param_6 - 1;
          pbVar6 = pbVar5;
        }
        pbVar5 = pbVar6 + 1;
      } while (param_6 != 0);
      if (param_6 != 0) {
        *param_2 = 0;
        return param_3 - param_6;
      }
    }
LAB_0045afd3:
    *pbVar2 = 0;
  }
  return 0;
}

