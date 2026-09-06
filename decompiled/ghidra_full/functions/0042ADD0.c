/* Raw Ghidra reference; not compilable reconstruction. Address: 0042ADD0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042add0(undefined4 param_1,undefined4 *param_2)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  short *psVar4;
  undefined4 *puVar5;
  
  puVar5 = param_2;
  for (iVar3 = 0x112; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)((int)param_2 + 2) = 0;
  *(undefined2 *)param_2 = 0x5453;
  param_2[2] = 0x448;
  param_2[3] = DAT_0046e354;
  param_2[4] = DAT_0046e358;
  *(undefined1 *)(param_2 + 5) = DAT_0046e35c;
  iVar3 = 0x200;
  psVar4 = (short *)((int)param_2 + 0x46);
  do {
    uVar1 = ((ushort)_DAT_004918b0 ^ 0x9630) + 0x9aad;
    sVar2 = (uVar1 >> 0xe) + uVar1 * 4;
    DAT_004918b4 = DAT_004918b4 + 1;
    iVar3 = iVar3 + -1;
    _DAT_004918b0 = CONCAT22(DAT_004918b0_2,sVar2);
    *psVar4 = sVar2;
    psVar4 = psVar4 + 1;
  } while (iVar3 != 0);
  return;
}

