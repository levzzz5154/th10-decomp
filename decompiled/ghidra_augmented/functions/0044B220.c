/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B220 */

byte * EncryptDatBuffer(byte *param_1,uint param_2,char param_3,int param_4,uint param_5)

{
  byte in_AL;
  byte *_Memory;
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  
  uVar3 = param_5;
  if ((int)param_2 < (int)param_5) {
    uVar3 = param_2;
  }
  _Memory = _malloc(uVar3);
  if (_Memory != (byte *)0x0) {
    iVar6 = param_2 - ((param_2 & 1) +
                      (((int)(param_4 + (param_4 >> 0x1f & 3U)) >> 2 <= (int)param_2 % param_4) - 1
                      & (int)param_2 % param_4));
    pbVar4 = param_1;
    pbVar7 = _Memory;
    for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)pbVar7 = *(undefined4 *)pbVar4;
      pbVar4 = pbVar4 + 4;
      pbVar7 = pbVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; pbVar5 = param_1, pbVar8 = _Memory, uVar3 != 0; uVar3 = uVar3 - 1) {
      *pbVar7 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      pbVar7 = pbVar7 + 1;
    }
    for (; (0 < iVar6 && (0 < (int)param_5)); param_5 = param_5 - param_4) {
      if (iVar6 < param_4) {
        param_4 = iVar6;
      }
      pbVar8 = pbVar8 + param_4;
      iVar1 = (param_4 + 1) / 2;
      pbVar4 = pbVar8 + -1;
      if (0 < iVar1) {
        do {
          *pbVar5 = *pbVar4 ^ in_AL;
          pbVar4 = pbVar4 + -2;
          in_AL = in_AL + param_3;
          pbVar5 = pbVar5 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      iVar1 = param_4 / 2;
      pbVar4 = pbVar8;
      if (0 < iVar1) {
        do {
          *pbVar5 = pbVar4[-2] ^ in_AL;
          in_AL = in_AL + param_3;
          pbVar5 = pbVar5 + 1;
          iVar1 = iVar1 + -1;
          pbVar4 = pbVar4 + -2;
        } while (iVar1 != 0);
      }
      iVar6 = iVar6 - param_4;
    }
    _free(_Memory);
  }
  return param_1;
}

