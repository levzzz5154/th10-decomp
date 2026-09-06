/* Raw Ghidra reference; not compilable reconstruction. Address: 00418930 */

bool __thiscall FUN_00418930(void *this,short param_1)

{
  int iVar1;
  void *pvVar2;
  short sVar3;
  int in_EAX;
  undefined4 *puVar4;
  
  if (99 < *(short *)(in_EAX + 8)) {
    return false;
  }
  sVar3 = *(short *)(in_EAX + 8) + param_1;
  *(short *)(in_EAX + 8) = sVar3;
  pvVar2 = g_pGameStateManager;
  iVar1 = DAT_0047770c;
  if (100 < sVar3) {
    *(undefined2 *)(in_EAX + 8) = 100;
    FUN_004492a0(this,(int)pvVar2,*(int *)(iVar1 + 0x9e18));
    *(undefined4 *)(iVar1 + 0x9e18) = 0;
    puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)(iVar1 + 0x9ec8),0x49,0xf);
    *(undefined4 *)(iVar1 + 0x9e18) = *puVar4;
  }
  return ((int)*(short *)(in_EAX + 8) - (int)param_1) / 0x14 != (int)*(short *)(in_EAX + 8) / 0x14;
}

