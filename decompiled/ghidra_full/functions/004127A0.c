/* Raw Ghidra reference; not compilable reconstruction. Address: 004127A0 */

undefined4 __fastcall FUN_004127a0(int param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  
  uVar3 = 0;
  piVar4 = (int *)(param_1 + 0x2494);
  do {
    if (-1 < *piVar4) {
      iVar2 = uVar3 * 0x10 + param_1;
      *(int *)(param_1 + 0x2404) =
           *(int *)(param_1 + 0x23fc) - *(int *)(uVar3 * 0x10 + 0x2494 + param_1);
      if (*(int *)(param_1 + 0x23fc) <= *(int *)(iVar2 + 0x2494)) {
        *(int *)(param_1 + 0x23fc) = *(int *)(iVar2 + 0x2494);
        *(undefined4 *)(iVar2 + 0x2494) = 0xffffffff;
        if ((*(uint *)(param_1 + 0x1168) & 1) == 0) {
          *(undefined4 *)(param_1 + 0x115c) = 0;
          *(undefined4 *)(param_1 + 0x1158) = 0xfff0bdc1;
          *(undefined4 *)(param_1 + 0x1160) = 0;
          *(undefined4 **)(param_1 + 0x1164) = &DAT_00476f78;
          *(uint *)(param_1 + 0x1168) = *(uint *)(param_1 + 0x1168) | 1;
        }
        *(undefined4 *)(param_1 + 0x115c) = 0;
        *(undefined4 *)(param_1 + 0x1160) = 0;
        *(undefined4 *)(param_1 + 0x1158) = 0xffffffff;
        *(uint *)(param_1 + 0x2480) = *(uint *)(param_1 + 0x2480) & 0xfffeffff;
        return *(undefined4 *)(iVar2 + 0x249c);
      }
      break;
    }
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 4;
  } while (uVar3 < 8);
  uVar3 = 0;
  piVar4 = (int *)(param_1 + 0x2498);
  while ((piVar4[-1] < 0 || (*piVar4 < 1))) {
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 4;
    if (7 < uVar3) {
      return 0;
    }
  }
  iVar2 = uVar3 * 0x10 + param_1;
  iVar5 = ((*(int *)(uVar3 * 0x10 + 0x2498 + param_1) - *(int *)(param_1 + 0x115c)) + 0x3b) / 0x3c;
  if (99 < iVar5) {
    iVar5 = 99;
  }
  *(int *)(DAT_0047770c + 0x9ec0) = iVar5;
  if (*(int *)(param_1 + 0x115c) < *(int *)(iVar2 + 0x2498)) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x23fc) = *(undefined4 *)(iVar2 + 0x2494);
  *(undefined4 *)(iVar2 + 0x2494) = 0xffffffff;
  if ((*(uint *)(param_1 + 0x1168) & 1) == 0) {
    *(undefined4 *)(param_1 + 0x115c) = 0;
    *(undefined4 *)(param_1 + 0x1158) = 0xfff0bdc1;
    *(undefined4 *)(param_1 + 0x1160) = 0;
    *(undefined4 **)(param_1 + 0x1164) = &DAT_00476f78;
    *(uint *)(param_1 + 0x1168) = *(uint *)(param_1 + 0x1168) | 1;
  }
  *(undefined4 *)(param_1 + 0x115c) = 0;
  *(undefined4 *)(param_1 + 0x1160) = 0;
  *(undefined4 *)(param_1 + 0x1158) = 0xffffffff;
  *(uint *)(param_1 + 0x2480) = *(uint *)(param_1 + 0x2480) | 0x10000;
  iVar2 = DAT_004776f4;
  DAT_00474c4c = DAT_00474c4c + -3000;
  if (DAT_00474c4c < 5000) {
    DAT_00474c4c = 5000;
  }
  puVar1 = (uint *)(DAT_004776f4 + 0x378c);
  if (((*puVar1 & 8) == 0) && (0x3b < *(int *)(DAT_004776f4 + 0x3738))) {
    *(undefined4 *)(DAT_004776f4 + 0x3790) = 0;
    *(uint *)(iVar2 + 0x378c) = *puVar1 & 0xfffffffd;
    *(uint *)(iVar2 + 0xad4) = *(uint *)(iVar2 + 0xad4) & 0xfffffffd;
    *(uint *)(iVar2 + 0xe80) = *(uint *)(iVar2 + 0xe80) & 0xfffffffd;
    *(uint *)(iVar2 + 0x15d8) = *(uint *)(iVar2 + 0x15d8) & 0xfffffffd;
    *(uint *)(iVar2 + 0x1984) = *(uint *)(iVar2 + 0x1984) & 0xfffffffd;
    *(uint *)(iVar2 + 0x1d30) = *(uint *)(iVar2 + 0x1d30) & 0xfffffffd;
    *(uint *)(iVar2 + 0x20dc) = *(uint *)(iVar2 + 0x20dc) & 0xfffffffd;
    *(uint *)(iVar2 + 0x2488) = *(uint *)(iVar2 + 0x2488) & 0xfffffffd;
  }
  return *(undefined4 *)((uVar3 + 0x24a) * 0x10 + param_1);
}

