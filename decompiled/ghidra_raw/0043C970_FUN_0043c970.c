/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043C970
 * Tracking name: FUN_0043c970
 * Ghidra name: FUN_0043c970
 * Tracked span: 400 bytes
 */


void FUN_0043c970(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  int unaff_ESI;
  
  switch(param_1) {
  case 0:
    goto LAB_0043c98b;
  case 1:
    goto LAB_0043ca69;
  case 2:
    goto LAB_0043c9bd;
  case 3:
    *(undefined4 *)(unaff_ESI + 0x18) = 0xff;
LAB_0043c9bd:
    iVar1 = FUN_0044a000(unaff_ESI);
    *(int *)(unaff_ESI + 8) = iVar1;
    iVar1 = FUN_0044a030(unaff_ESI);
    *(int *)(unaff_ESI + 0xc) = iVar1;
    break;
  case 4:
    iVar1 = FUN_0044a000(unaff_ESI);
    *(int *)(unaff_ESI + 8) = iVar1;
    iVar1 = FUN_0044a030(unaff_ESI);
    *(int *)(unaff_ESI + 0xc) = iVar1;
    break;
  case 5:
LAB_0043c98b:
    iVar1 = FUN_0044a000(unaff_ESI);
    *(int *)(unaff_ESI + 8) = iVar1;
    iVar1 = FUN_0044a030(unaff_ESI);
    *(int *)(unaff_ESI + 0xc) = iVar1;
    break;
  case 6:
    iVar1 = FUN_0044a000(unaff_ESI);
    *(int *)(unaff_ESI + 8) = iVar1;
    iVar1 = FUN_0044a030(unaff_ESI);
    *(int *)(unaff_ESI + 0xc) = iVar1;
    break;
  case 7:
    iVar1 = FUN_0044a000(unaff_ESI);
    *(int *)(unaff_ESI + 8) = iVar1;
    iVar1 = FUN_0044a030(unaff_ESI);
    *(int *)(unaff_ESI + 0xc) = iVar1;
    break;
  case 8:
LAB_0043ca69:
    iVar1 = FUN_0044a000(unaff_ESI);
    *(int *)(unaff_ESI + 8) = iVar1;
  }
  *(code **)(*(int *)(unaff_ESI + 8) + 0x10) = FUN_0043c870;
  if ((*(uint *)(unaff_ESI + 0x40) & 1) == 0) {
    *(undefined4 *)(unaff_ESI + 0x34) = 0;
    *(undefined4 *)(unaff_ESI + 0x30) = 0xfff0bdc1;
    *(undefined4 *)(unaff_ESI + 0x38) = 0;
    *(undefined4 **)(unaff_ESI + 0x3c) = &DAT_00476f78;
    *(uint *)(unaff_ESI + 0x40) = *(uint *)(unaff_ESI + 0x40) | 1;
  }
  *(undefined4 *)(unaff_ESI + 0x34) = 0;
  *(undefined4 *)(unaff_ESI + 0x38) = 0;
  *(undefined4 *)(unaff_ESI + 0x30) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x1c) = param_2;
  *(undefined4 *)(unaff_ESI + 0x10) = param_1;
  *(undefined4 *)(unaff_ESI + 0x20) = param_3;
  *(undefined4 *)(unaff_ESI + 0x24) = param_4;
  *(undefined4 *)(unaff_ESI + 0x28) = param_5;
  return;
}

