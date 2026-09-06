/* Raw Ghidra reference; not compilable reconstruction. Address: 0042ACB0 */

void FUN_0042acb0(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  puVar2 = param_1;
  for (iVar5 = 0x10df; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)param_1 = 0x5243;
  *(undefined2 *)((int)param_1 + 2) = 0;
  param_1[2] = 0x437c;
  puVar2 = param_1 + 5;
  iVar5 = 5;
  do {
    iVar6 = 1000000;
    puVar3 = puVar2;
    do {
      puVar3[-1] = iVar6;
      *(undefined1 *)puVar3 = 1;
      *(undefined4 *)((int)puVar3 + 2) = s__________0046e858._0_4_;
      *(undefined4 *)((int)puVar3 + 6) = s__________0046e858._4_4_;
      cVar1 = s__________0046e858[8];
      puVar3[3] = 0;
      *(undefined1 *)((int)puVar3 + 1) = 0;
      iVar6 = iVar6 + -100000;
      puVar2 = puVar3 + 6;
      *(char *)((int)puVar3 + 10) = cVar1;
      puVar3 = puVar2;
    } while (0 < iVar6);
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar7 = 0;
  iVar6 = 3;
  iVar5 = 1;
  piVar4 = param_1 + 0x18a;
  do {
    piVar4[-1] = iVar7;
    *piVar4 = (int)*(char *)(iVar5 + 0x4743bf);
    piVar4[0x23] = iVar5;
    piVar4[0x24] = (int)(char)(&DAT_004743c0)[iVar5];
    piVar4[0x47] = iVar6 + -1;
    piVar4[0x48] = (int)*(char *)(iVar6 + 0x4743bf);
    piVar4[0x6b] = iVar6;
    piVar4[0x6c] = (int)(char)(&DAT_004743c0)[iVar6];
    piVar4[0x8f] = iVar7 + 4;
    piVar4[0x90] = (int)(char)(&DAT_004743c4)[iVar7];
    iVar5 = iVar5 + 5;
    iVar7 = iVar7 + 5;
    iVar6 = iVar6 + 5;
    piVar4 = piVar4 + 0xb4;
  } while (iVar5 < 0x6f);
  return;
}

