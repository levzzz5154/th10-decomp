/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B0D0
 * Tracking name: FUN_0044b0d0
 * Ghidra name: FUN_0044b0d0
 * Tracked span: 336 bytes
 */


byte * FUN_0044b0d0(byte *param_1,uint param_2,char param_3,int param_4,uint param_5)

{
  byte *pbVar1;
  byte in_AL;
  byte *_Memory;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  
  uVar4 = param_5;
  if ((int)param_2 < (int)param_5) {
    uVar4 = param_2;
  }
  _Memory = _malloc(uVar4);
  if (_Memory != (byte *)0x0) {
    iVar7 = param_2 - ((param_2 & 1) +
                      (((int)(param_4 + (param_4 >> 0x1f & 3U)) >> 2 <= (int)param_2 % param_4) - 1
                      & (int)param_2 % param_4));
    pbVar5 = param_1;
    pbVar8 = _Memory;
    for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pbVar8 = *(undefined4 *)pbVar5;
      pbVar5 = pbVar5 + 4;
      pbVar8 = pbVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; pbVar6 = _Memory, pbVar1 = param_1, uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar8 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      pbVar8 = pbVar8 + 1;
    }
    for (; (0 < iVar7 && (0 < (int)param_5)); param_5 = param_5 - param_4) {
      if (iVar7 < param_4) {
        param_4 = iVar7;
      }
      pbVar1 = pbVar1 + param_4;
      iVar2 = (param_4 + 1) / 2;
      pbVar5 = pbVar1 + -1;
      if (0 < iVar2) {
        do {
          *pbVar5 = *pbVar6 ^ in_AL;
          pbVar5 = pbVar5 + -2;
          in_AL = in_AL + param_3;
          pbVar6 = pbVar6 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      iVar2 = param_4 / 2;
      pbVar5 = pbVar1;
      if (0 < iVar2) {
        do {
          pbVar5[-2] = *pbVar6 ^ in_AL;
          in_AL = in_AL + param_3;
          pbVar6 = pbVar6 + 1;
          iVar2 = iVar2 + -1;
          pbVar5 = pbVar5 + -2;
        } while (iVar2 != 0);
      }
      iVar7 = iVar7 - param_4;
    }
    _free(_Memory);
  }
  return param_1;
}

