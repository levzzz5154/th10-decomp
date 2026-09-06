/* Raw Ghidra reference; not compilable reconstruction. Address: 00435610 */

void __fastcall FUN_00435610(char *param_1)

{
  uint *in_EAX;
  uint *puVar1;
  char *pcVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  uint *puVar6;
  
  puVar1 = FUN_00452730(in_EAX,':');
  if (puVar1 != (uint *)0x0) {
    iVar5 = (int)param_1 - (int)in_EAX;
    do {
      uVar3 = *in_EAX;
      *(char *)(iVar5 + (int)in_EAX) = (char)uVar3;
      in_EAX = (uint *)((int)in_EAX + 1);
    } while ((char)uVar3 != '\0');
    return;
  }
  GetModuleFileNameA((HMODULE)0x0,param_1,0x104);
  pcVar2 = _strrchr(param_1,0x5c);
  if (pcVar2 == (char *)0x0) {
    *param_1 = '\0';
  }
  pcVar2[1] = '\0';
  puVar1 = in_EAX;
  do {
    uVar3 = *puVar1;
    puVar1 = (uint *)((int)puVar1 + 1);
  } while ((char)uVar3 != '\0');
  puVar6 = (uint *)(param_1 + -1);
  do {
    pcVar2 = (char *)((int)puVar6 + 1);
    puVar6 = (uint *)((int)puVar6 + 1);
  } while (*pcVar2 != '\0');
  puVar4 = in_EAX;
  for (uVar3 = (uint)((int)puVar1 - (int)in_EAX) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  for (uVar3 = (int)puVar1 - (int)in_EAX & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(char *)puVar6 = (char)*puVar4;
    puVar4 = (uint *)((int)puVar4 + 1);
    puVar6 = (uint *)((int)puVar6 + 1);
  }
  return;
}

