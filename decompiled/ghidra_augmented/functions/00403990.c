/* Raw Ghidra reference; not compilable reconstruction. Address: 00403990 */

undefined4 FUN_00403990(void)

{
  int iVar1;
  short *psVar2;
  short *extraout_ECX;
  int unaff_EBX;
  int iVar3;
  short *psVar4;
  int local_8;
  int local_4;
  
  psVar2 = *(short **)(unaff_EBX + 0x10);
  local_4 = 0;
  if (0 < *psVar2) {
    do {
      iVar1 = *(int *)(*(int *)(unaff_EBX + 0x14) + local_4 * 4);
      if ((*(byte *)(iVar1 + 3) & 1) != 0) {
        psVar4 = (short *)(iVar1 + 0x1c);
        local_8 = 0;
        if (-1 < *(short *)(iVar1 + 0x1c)) {
          do {
            iVar3 = psVar4[3] * 0x3ac + *(uint *)(unaff_EBX + 0x17c);
            FUN_0043ee30(psVar2,*(uint *)(unaff_EBX + 0x17c),iVar3);
            if (*(int *)(iVar3 + 0x390) != 0) {
              local_8 = local_8 + 1;
            }
            psVar4 = (short *)((int)psVar4 + (int)psVar4[1]);
            psVar2 = extraout_ECX;
          } while (-1 < *psVar4);
          if (local_8 != 0) goto LAB_00403a0e;
        }
        *(byte *)(iVar1 + 3) = *(byte *)(iVar1 + 3) & 0xfe;
      }
LAB_00403a0e:
      psVar2 = *(short **)(unaff_EBX + 0x10);
      local_4 = local_4 + 1;
    } while (local_4 < *psVar2);
  }
  return 0;
}

