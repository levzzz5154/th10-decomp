/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D690 */

int FUN_0043d690(LPCSTR param_1)

{
  char cVar1;
  ushort uVar2;
  int *in_EAX;
  LPCSTR pCVar3;
  HANDLE pvVar4;
  int iVar5;
  uint uVar6;
  
  pCVar3 = param_1;
  do {
    cVar1 = *pCVar3;
    pCVar3[(int)in_EAX + (0x5108 - (int)param_1)] = cVar1;
    pCVar3 = pCVar3 + 1;
  } while (cVar1 != '\0');
  if ((in_EAX[0x184] != 0) && (*in_EAX != 0)) {
    FUN_0043dab0();
    iVar5 = in_EAX[0x7e1];
    uVar2 = *(ushort *)(iVar5 + 0x2c);
    uVar6 = (*(int *)(iVar5 + 0x24) * (uint)uVar2 & 0x3fffffff) >> 2;
    pvVar4 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    in_EAX[0x1483] = (int)pvVar4;
    pvVar4 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_0043e3a0,DAT_00491c70,0,
                          (LPDWORD)(in_EAX + 0x185));
    in_EAX[0x186] = (int)pvVar4;
    iVar5 = FUN_0044c8f0(in_EAX + 0x1482,0x10100,(int *)in_EAX[0x184],param_1,DAT_0046a67c,
                         DAT_0046a680,DAT_0046a684,DAT_0046a688,0x10,uVar6 - uVar6 % (uint)uVar2,
                         in_EAX[0x1483],iVar5);
    return (-1 < iVar5) - 1;
  }
  return -1;
}

