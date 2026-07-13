/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00431410
 * Tracking name: FUN_00431410
 * Ghidra name: FUN_00431410
 * Tracked span: 432 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00431410(void)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  int unaff_EDI;
  
  pvVar3 = g_pGameThread;
  if ((1 < *(int *)(unaff_EDI + 0x20)) && (*(int *)(unaff_EDI + 0x20) < 4)) {
    iVar4 = 1;
    *(undefined4 *)((int)g_pGameThread + 0x8988) = 1;
    if ((9 < *(int *)(unaff_EDI + 0x2b4)) || (*(int *)(unaff_EDI + 0x20) == 3)) {
      do {
        iVar1 = DAT_0047783c;
        if (*(int *)(unaff_EDI + 0x24) == iVar4 + -1) {
          if (*(char *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c + 0x4e1 +
                       (iVar4 + DAT_00474c74 * 6) * 8) == '\0') {
            *(undefined4 *)((int)pvVar3 + 0x8974) = 0xffdfdfdf;
          }
          else {
            if (*(int *)(unaff_EDI + 0x20) == 3) {
              uVar2 = *(uint *)(unaff_EDI + 0x2b4) & 0x80000003;
              if ((int)uVar2 < 0) {
                uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
              }
              if (1 < (int)uVar2) {
                *(undefined4 *)((int)pvVar3 + 0x8974) = 0xff000000;
                goto LAB_00431513;
              }
            }
            *(undefined4 *)((int)pvVar3 + 0x8974) = 0xffffff00;
          }
        }
        else {
          *(undefined4 *)((int)pvVar3 + 0x8974) = 0xff808080;
        }
LAB_00431513:
        if (*(char *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + iVar1 + 0x4e1 +
                     (iVar4 + DAT_00474c74 * 6) * 8) == '\0') {
          FUN_00401630((int)pvVar3,"%s  ---------");
        }
        else {
          FUN_00401630((int)pvVar3,"%s  %.8d0");
        }
        iVar4 = iVar4 + 1;
        pvVar3 = g_pGameThread;
      } while (iVar4 < 7);
    }
    *(undefined4 *)((int)pvVar3 + 0x8974) = 0xffffffff;
    *(undefined4 *)((int)pvVar3 + 0x8988) = 0;
  }
  return 1;
}

