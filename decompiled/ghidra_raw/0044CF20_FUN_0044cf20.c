/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044CF20
 * Tracking name: FUN_0044cf20
 * Ghidra name: FUN_0044cf20
 * Tracked span: 352 bytes
 */


/* WARNING: Removing unreachable block (ram,0x0044d019) */
/* WARNING: Removing unreachable block (ram,0x0044d051) */

undefined4 FUN_0044cf20(void)

{
  uint uVar1;
  undefined4 *puVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  int unaff_ESI;
  uint uVar6;
  int *piVar7;
  
  uVar5 = 0;
  uVar6 = 0;
  *(undefined4 *)(unaff_ESI + 0x30) = 0;
  if (*(int *)(unaff_ESI + 0x10) != 0) {
    do {
      piVar7 = *(int **)(*(int *)(unaff_ESI + 4) + uVar6 * 4);
      if (piVar7 != (int *)0x0) {
        (**(code **)(*piVar7 + 8))();
        *(undefined4 *)(*(int *)(unaff_ESI + 4) + uVar6 * 4) = 0;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(unaff_ESI + 0x10));
  }
  if (*(void **)(unaff_ESI + 4) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 4));
    *(undefined4 *)(unaff_ESI + 4) = 0;
  }
  pvVar3 = operator_new(*(int *)(unaff_ESI + 0x10) << 2);
  *(void **)(unaff_ESI + 4) = pvVar3;
  if (*(int *)(unaff_ESI + 0x10) != 0) {
    do {
      piVar7 = (int *)**(undefined4 **)(unaff_ESI + 0x58);
      iVar4 = (**(code **)(*piVar7 + 0xc))
                        (piVar7,unaff_ESI + 0x34,*(int *)(unaff_ESI + 4) + uVar5 * 4);
      if ((iVar4 < 0) ||
         (puVar2 = *(undefined4 **)(uVar5 * 4 + *(int *)(unaff_ESI + 4)),
         iVar4 = (**(code **)*puVar2)(puVar2,&DAT_0046743c,&stack0xffffffec), iVar4 < 0)) {
        return 0x80004005;
      }
      pvVar3 = operator_new(0x80);
      if (pvVar3 == (void *)0x0) {
        return 0x8007000e;
      }
      uVar6 = 0;
      do {
        uVar1 = uVar6 + 1;
        *(uint *)((int)pvVar3 + uVar6 * 8) = *(int *)(unaff_ESI + 0x6c) * uVar1 + -1;
        *(undefined4 *)((int)pvVar3 + uVar6 * 8 + 4) = *(undefined4 *)(unaff_ESI + 0x70);
        uVar6 = uVar1;
      } while (uVar1 < 0x10);
      iVar4 = (**(code **)(*piVar7 + 0xc))(piVar7,0x10,pvVar3);
      if (iVar4 < 0) {
        _free(pvVar3);
        return 0x80004005;
      }
      _free(pvVar3);
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(unaff_ESI + 0x10));
  }
  return 0;
}

