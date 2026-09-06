/* Raw Ghidra reference; not compilable reconstruction. Address: 00427B50 */

undefined4 * __fastcall
FUN_00427b50(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4,
            undefined4 param_5,int param_6,undefined4 param_7)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(param_2 + 0x350c);
  iVar1 = 0;
  do {
    if ((*(byte *)(puVar2 + 0x1a) & 1) == 0) {
      puVar3 = puVar2;
      for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      puVar2[0x1a] = puVar2[0x1a] | 3;
      puVar3 = puVar2 + 6;
      for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      puVar2[6] = *param_3;
      puVar2[7] = param_3[1];
      puVar2[8] = param_3[2];
      *puVar2 = param_4;
      puVar2[1] = param_5;
      if ((puVar2[0x15] & 1) == 0) {
        puVar2[0x12] = 0;
        puVar2[0x11] = 0xfff0bdc1;
        puVar2[0x13] = 0;
        puVar2[0x14] = &DAT_00476f78;
        puVar2[0x15] = puVar2[0x15] | 1;
      }
      puVar2[0x12] = param_6;
      puVar2[0x11] = param_6 + -1;
      puVar2[0x13] = (float)param_6;
      puVar2[0x16] = param_7;
      puVar2[0x17] = 0;
      puVar2[0x18] = 999999;
      puVar2[0x19] = 4;
      return puVar2;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x1b;
  } while (iVar1 < 0x20);
  return puVar2;
}

