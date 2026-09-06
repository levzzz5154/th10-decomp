/* Raw Ghidra reference; not compilable reconstruction. Address: 00423570 */

void FUN_00423570(int param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  
  if ((DAT_00474c7c == 7) && (*(int *)(param_1 + 0x1e4) != 0)) {
    DAT_00477848 = &PTR_DAT_00474908;
    DAT_00474c7c = 8;
    DAT_00474c80 = 8;
  }
  iVar4 = FUN_00421fa0();
  if ((DAT_00474c7c == 7) && (*(int *)(param_1 + 0x1e4) != 0)) {
    DAT_00477848 = (undefined **)&DAT_004748d8;
    DAT_00474c7c = 7;
    DAT_00474c80 = 7;
  }
  if (iVar4 < 0) {
    *(undefined4 *)(param_1 + 0x1e8) = 1;
    return;
  }
  *(undefined4 *)(param_1 + 0x2c) = 0x19;
  *(undefined4 *)(param_1 + 0xf4) = 1;
  iVar3 = *(int *)(param_1 + 0x2c);
  if ((iVar3 != 0) && (iVar3 <= iVar4)) {
    iVar4 = iVar3 + -1;
  }
  piVar1 = (int *)(param_1 + 0xfc);
  *(int *)(param_1 + 0x24) = iVar4;
  iVar4 = *(int *)(param_1 + 0x104);
  if (iVar4 == 0) {
    *piVar1 = 0;
  }
  else if (iVar4 < 1) {
    *piVar1 = iVar4 + -1;
  }
  else {
    *piVar1 = 0;
  }
  pcVar5 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
  do {
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  *(int *)(param_1 + 0x104) =
       (int)pcVar5 - (int)(PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1);
  iVar4 = DAT_0047783c;
  *(undefined4 *)(param_1 + 0x1cc) = 1;
  pcVar5 = (char *)(iVar4 + 0x1d878);
  iVar4 = (param_1 + 0x2b4) - (int)pcVar5;
  do {
    cVar2 = *pcVar5;
    pcVar5[iVar4] = cVar2;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  iVar4 = 9;
  bVar7 = true;
  *(undefined4 *)(param_1 + 0x1e0) = 0;
  pcVar5 = (char *)(param_1 + 0x2b4);
  pcVar6 = "        ";
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar7 = *pcVar5 == *pcVar6;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  } while (bVar7);
  if (!bVar7) {
    FUN_0044bea0(-1);
  }
  iVar4 = 8;
  do {
    if (*(char *)(iVar4 + 0x2b3 + param_1) != ' ') break;
    iVar4 = iVar4 + -1;
  } while (0 < iVar4);
  *(int *)(param_1 + 0x1e0) = iVar4;
  *(undefined4 *)(param_1 + 0x1e8) = 0;
  return;
}

