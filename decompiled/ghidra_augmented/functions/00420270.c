/* Raw Ghidra reference; not compilable reconstruction. Address: 00420270 */

undefined4 FUN_00420270(void)

{
  UINT *pUVar1;
  int *piVar2;
  UINT uTimerID;
  void *pvVar3;
  int in_EAX;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  FUN_0044c150();
  DAT_004977b4 = 2;
  FUN_0044c150();
  if (DAT_0049238c != (void *)0x0) {
    _free(DAT_0049238c);
    DAT_0049238c = (void *)0x0;
  }
  FUN_004203f0();
  ReleasePlatformOwnedHandle();
  piVar2 = *(int **)((int)g_pGameStateManager + 0x3ada74);
  puVar5 = (undefined4 *)((int)g_pGameStateManager + 0x3ada74);
  uVar4 = extraout_ECX;
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 8))(piVar2);
    *puVar5 = 0;
    uVar4 = extraout_ECX_00;
  }
  FUN_0043e460(uVar4,"dummy",4,0);
  FUN_00437d10();
  piVar2 = *(int **)(in_EAX + 0x10);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x20))(piVar2);
    piVar2 = *(int **)(in_EAX + 0x10);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
      *(undefined4 *)(in_EAX + 0x10) = 0;
    }
  }
  piVar2 = *(int **)(in_EAX + 0x14);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x20))(piVar2);
    piVar2 = *(int **)(in_EAX + 0x14);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
      *(undefined4 *)(in_EAX + 0x14) = 0;
    }
  }
  piVar2 = *(int **)(in_EAX + 0xc);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 8))(piVar2);
    *(undefined4 *)(in_EAX + 0xc) = 0;
  }
  pvVar3 = DAT_00491d44;
  if (DAT_00491d44 != (void *)0x0) {
    pUVar1 = (UINT *)((int)DAT_00491d44 + 4);
    uTimerID = *pUVar1;
    if (uTimerID != 0) {
      timeKillEvent(uTimerID);
    }
    timeEndPeriod(*(UINT *)((int)pvVar3 + 8));
    *pUVar1 = 0;
    pvVar3 = DAT_00491d44;
    if (DAT_00491d44 != (void *)0x0) {
      FUN_004203c0();
      _free(pvVar3);
    }
    DAT_00491d44 = (void *)0x0;
  }
  FUN_00434d10();
  return 0;
}

