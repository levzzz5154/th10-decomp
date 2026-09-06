/* Raw Ghidra reference; not compilable reconstruction. Address: 0044C000 */

byte * __fastcall FUN_0044c000(undefined4 param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *unaff_ESI;
  
  pbVar3 = unaff_ESI;
  for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    pbVar3[0] = 0;
    pbVar3[1] = 0;
    pbVar3[2] = 0;
    pbVar3[3] = 0;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar2 = param_3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pbVar3 = 0;
    pbVar3 = pbVar3 + 1;
  }
  bVar1 = *param_2;
  if (bVar1 != 10) {
    do {
      if ((bVar1 == 0xd) || (param_3 == 0)) goto LAB_0044c052;
      *unaff_ESI = bVar1;
      bVar1 = *param_2;
      pbVar3 = unaff_ESI + 1;
      if (((0x80 < bVar1) && (bVar1 < 0xa0)) || ((pbVar4 = param_2, 0xdf < bVar1 && (bVar1 < 0xfd)))
         ) {
        pbVar4 = param_2 + 1;
        param_3 = param_3 - 1;
        *pbVar3 = param_2[1];
        pbVar3 = unaff_ESI + 2;
      }
      bVar1 = pbVar4[1];
      param_2 = pbVar4 + 1;
      param_3 = param_3 - 1;
      unaff_ESI = pbVar3;
    } while (bVar1 != 10);
    param_2 = pbVar4 + 2;
  }
LAB_0044c052:
  for (; (*param_2 == 10 || (*param_2 == 0xd)); param_2 = param_2 + 1) {
  }
  return param_2;
}

