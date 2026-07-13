/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421FA0
 * Tracking name: FUN_00421fa0
 * Ghidra name: FUN_00421fa0
 * Tracked span: 320 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00421fa0(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int unaff_EDI;
  
  iVar4 = 0;
  piVar2 = (int *)(DAT_00474c74 * 0xf0 + 0x10 + unaff_EDI);
  do {
    if (*piVar2 <= DAT_00474c44) {
      if (iVar4 < 10) {
        iVar3 = 9;
        if (iVar4 < 9) {
          do {
            puVar1 = (undefined4 *)(unaff_EDI + (iVar3 + DAT_00474c74 * 10) * 0x18);
            puVar1[4] = puVar1[-2];
            puVar1[5] = puVar1[-1];
            puVar1[6] = *puVar1;
            puVar1[7] = puVar1[1];
            puVar1[8] = puVar1[2];
            iVar3 = iVar3 + -1;
            puVar1[9] = puVar1[3];
          } while (iVar4 < iVar3);
        }
        *(int *)(unaff_EDI + 0x10 + (iVar4 + DAT_00474c74 * 10) * 0x18) = DAT_00474c44;
        *(undefined1 *)(unaff_EDI + 0x15 + (iVar4 + DAT_00474c74 * 10) * 0x18) = DAT_00474c90;
        *(undefined1 *)(unaff_EDI + 0x14 + (iVar4 + DAT_00474c74 * 10) * 0x18) =
             (undefined1)DAT_00474c7c;
        FID_conflict___time32((__time32_t *)(unaff_EDI + 0x20 + (iVar4 + DAT_00474c74 * 10) * 0x18))
        ;
        puVar1 = (undefined4 *)(unaff_EDI + 0x16 + (iVar4 + DAT_00474c74 * 10) * 0x18);
        *puVar1 = DAT_0046e354;
        puVar1[1] = DAT_0046e358;
        iVar3 = DAT_00477708;
        *(undefined1 *)(puVar1 + 2) = DAT_0046e35c;
        *(float *)(unaff_EDI + 0x24 + (iVar4 + DAT_00474c74 * 10) * 0x18) =
             (float)((float10)_DAT_00470b44 -
                    ((float10)*(double *)(iVar3 + 0x24) / (float10)*(double *)(iVar3 + 0x2c)) *
                    (float10)_DAT_00470b44);
        return iVar4;
      }
      return -1;
    }
    iVar4 = iVar4 + 1;
    piVar2 = piVar2 + 6;
  } while (iVar4 < 10);
  return -1;
}

