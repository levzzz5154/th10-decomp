/* Raw Ghidra reference; not compilable reconstruction. Address: 00426520 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00426520(void)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  byte *pbVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int unaff_ESI;
  float10 fVar8;
  
  pbVar4 = FUN_0044b360((size_t *)0x0,0);
  *(byte **)(unaff_ESI + 0x45c) = pbVar4;
  if (pbVar4 == (byte *)0x0) {
    return 0xffffffff;
  }
  iVar7 = 0;
  fVar8 = (float10)fsin((float10)_DAT_00470c50);
  *(float *)(pbVar4 + 0x18) = (float)(fVar8 * (float10)*(float *)(pbVar4 + 0x10));
  *(float *)(*(int *)(unaff_ESI + 0x45c) + 0x1c) =
       (float)(fVar8 * (float10)*(float *)(*(int *)(unaff_ESI + 0x45c) + 0x14));
  *(float *)(*(int *)(unaff_ESI + 0x45c) + 0x18) =
       (float)(fVar8 * (float10)*(float *)(*(int *)(unaff_ESI + 0x45c) + 0x10));
  *(float *)(*(int *)(unaff_ESI + 0x45c) + 0x1c) =
       (float)(fVar8 * (float10)*(float *)(*(int *)(unaff_ESI + 0x45c) + 0x14));
  if (*(short *)(*(int *)(unaff_ESI + 0x45c) + 2) != 0) {
    iVar6 = 0x110;
    do {
      piVar2 = (int *)(iVar6 + *(int *)(unaff_ESI + 0x45c));
      *piVar2 = *piVar2 + *(int *)(unaff_ESI + 0x45c);
      pcVar5 = *(char **)(iVar6 + *(int *)(unaff_ESI + 0x45c));
      cVar3 = *pcVar5;
      while (-1 < cVar3) {
        *(undefined4 *)(pcVar5 + 0x24) =
             *(undefined4 *)(&DAT_0047476c + *(int *)(pcVar5 + 0x24) * 4);
        *(undefined4 *)(pcVar5 + 0x28) =
             *(undefined4 *)(&DAT_00474778 + *(int *)(pcVar5 + 0x28) * 4);
        *(undefined4 *)(pcVar5 + 0x2c) =
             *(undefined4 *)(&DAT_00491bf4 + *(int *)(pcVar5 + 0x2c) * 4);
        *(undefined4 *)(pcVar5 + 0x30) =
             *(undefined4 *)(&DAT_00491bf8 + *(int *)(pcVar5 + 0x30) * 4);
        pcVar1 = pcVar5 + 0x34;
        pcVar5 = pcVar5 + 0x34;
        cVar3 = *pcVar1;
      }
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 8;
    } while (iVar7 < (int)(uint)*(ushort *)(*(int *)(unaff_ESI + 0x45c) + 2));
  }
  return 0;
}

