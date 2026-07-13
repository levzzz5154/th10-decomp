/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004297D0
 * Tracking name: FUN_004297d0
 * Ghidra name: FUN_004297d0
 * Tracked span: 912 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004297d0(void)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined4 uVar3;
  int iVar4;
  undefined1 uVar5;
  int unaff_EDI;
  ulonglong uVar6;
  
  if (DAT_00477810 != 0) {
    if (*(int *)(unaff_EDI + 0x10) == 0) {
      DAT_00474e5c = CONCAT22((short)DAT_00474e5c,(short)DAT_00474e30) & 0xffff01f7;
      if ((DAT_00491d78 & 0x200) != 0) {
        if ((DAT_00474e30 & 1) == 0) {
          DAT_00474e5a = 0;
        }
        else {
          DAT_00474e5a = DAT_00474e5a + 1;
          if (7 < DAT_00474e5a) {
            DAT_00474e5c = CONCAT22(DAT_00474e5c._2_2_,(short)DAT_00474e30) & 0xffff01f7 | 4;
            DAT_00474e5a = 8;
          }
        }
      }
      FUN_0040ac20(0x474e30);
      if (*(int *)(unaff_EDI + 0x1c8) % 0x1e == 0) {
        if (*(float *)(DAT_00477708 + 0x34) + _DAT_00470b0c < _DAT_00470c34) {
          uVar6 = FUN_00463b2c();
          uVar5 = (undefined1)uVar6;
        }
        else {
          uVar5 = 0xff;
        }
        iVar4 = **(int **)(unaff_EDI + 0x9c);
        **(undefined1 **)(iVar4 + 0x6274) = uVar5;
        piVar1 = (int *)(iVar4 + 0x6274);
        *piVar1 = *piVar1 + 1;
      }
      bVar2 = FUN_0042a8a0((uint)DAT_00474e64,(short)DAT_00474e5c,DAT_00474e62,DAT_00474e64);
      if (CONCAT31(extraout_var,bVar2) != 0) {
        uVar3 = FUN_0042aa50(unaff_EDI);
        *(undefined4 *)(unaff_EDI + 0x9c) = uVar3;
        *(int *)(unaff_EDI + 0x1c8) = *(int *)(unaff_EDI + 0x1c8) + 1;
        return 1;
      }
    }
    else {
      if (-1 < *(int *)(unaff_EDI + 0x1d0)) {
        iVar4 = *(int *)(unaff_EDI + 0x1d0);
        if (*(int *)(unaff_EDI + (iVar4 * 9 + 0x2d) * 4) <
            *(int *)(*(int *)(unaff_EDI + 0xb0 + iVar4 * 0x24) + 4)) {
          DAT_00474e5c = CONCAT22((short)DAT_00474e5c,
                                  **(undefined2 **)(unaff_EDI + iVar4 * 0x24 + 0xa4));
          DAT_00474e62 = *(undefined2 *)
                          (*(int *)(unaff_EDI + 0xa4 + *(int *)(unaff_EDI + 0x1d0) * 0x24) + 2);
          DAT_00474e64 = *(undefined2 *)
                          (*(int *)(unaff_EDI + 0xa4 + *(int *)(unaff_EDI + 0x1d0) * 0x24) + 4);
          *(undefined1 *)(unaff_EDI + 0x1c4) =
               **(undefined1 **)(unaff_EDI + 0xac + *(int *)(unaff_EDI + 0x1d0) * 0x24);
          piVar1 = (int *)(unaff_EDI + *(int *)(unaff_EDI + 0x1d0) * 0x24 + 0xa4);
          *piVar1 = *piVar1 + 6;
          if (*(int *)(unaff_EDI + 0x1c8) % 0x1e == 0) {
            *(int *)(unaff_EDI + 0xac + *(int *)(unaff_EDI + 0x1d0) * 0x24) =
                 *(int *)(unaff_EDI + 0xac + *(int *)(unaff_EDI + 0x1d0) * 0x24) + 1;
          }
        }
        else {
          DAT_00474e5c = DAT_00474e5c << 0x10;
          DAT_00474e62 = 0;
          DAT_00474e64 = 0;
        }
        iVar4 = *(int *)(unaff_EDI + 0x1d0) + 5;
        *(int *)(unaff_EDI + iVar4 * 0x24) = *(int *)(unaff_EDI + iVar4 * 0x24) + 1;
        *(int *)(unaff_EDI + 0x1c8) = *(int *)(unaff_EDI + 0x1c8) + 1;
        return 1;
      }
      DAT_00474e5c = DAT_00474e5c & 0xffff0000;
      DAT_00474e62 = 0;
      DAT_00474e64 = 0;
    }
    *(int *)(unaff_EDI + 0x1c8) = *(int *)(unaff_EDI + 0x1c8) + 1;
  }
  return 1;
}

