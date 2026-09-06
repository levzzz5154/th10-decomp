/* Raw Ghidra reference; not compilable reconstruction. Address: 00401110 */

undefined4 LoadGameThreadResources(void)

{
  int iVar1;
  int in_EAX;
  int *piVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  piVar2 = FUN_00447280(2,(int)g_pGameStateManager,"ascii.anm");
  *(int **)(in_EAX + 0x8994) = piVar2;
  if (piVar2 != (int *)0x0) {
    piVar2 = FUN_00447280(0,(int)g_pGameStateManager,"text.anm");
    *(int **)(in_EAX + 0x899c) = piVar2;
    if (piVar2 != (int *)0x0) {
      piVar2 = FUN_00447280(3,(int)g_pGameStateManager,"capture.anm");
      *(int **)(in_EAX + 0x8998) = piVar2;
      if (piVar2 != (int *)0x0) {
        iVar3 = FUN_00449ed0(FUN_004014f0);
        iVar1 = DAT_00491be4;
        *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
        *(int *)(iVar3 + 0x20) = in_EAX;
        FUN_00449ae0(iVar1);
        *(int *)(in_EAX + 0xc) = iVar3;
        iVar3 = FUN_00449ed0(FUN_00401510);
        iVar1 = DAT_00491be4;
        *(int *)(iVar3 + 0x20) = in_EAX;
        *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
        FUN_00449b70(iVar1);
        *(int *)(in_EAX + 0x10) = iVar3;
        iVar3 = FUN_00449ed0(RunGameThreadQueue);
        iVar1 = DAT_00491be4;
        *(int *)(iVar3 + 0x20) = in_EAX;
        *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
        FUN_00449b70(iVar1);
        iVar1 = *(int *)(in_EAX + 0x8994);
        *(int *)(in_EAX + 0x89a8) = iVar3;
        InitializeEntity(extraout_ECX,(undefined4 *)(in_EAX + 0x14));
        *(int *)(in_EAX + 0x31c) = iVar1;
        FUN_0043e5a0(iVar1,0);
        iVar1 = *(int *)(in_EAX + 0x8994);
        InitializeEntity(extraout_ECX_00,(undefined4 *)(in_EAX + 0x3c0));
        *(int *)(in_EAX + 0x6c8) = iVar1;
        FUN_0043e5a0(iVar1,0x62);
        return 0;
      }
    }
  }
  FUN_0044b810(&DAT_00474f70,&DAT_0046cb68);
  return 0xffffffff;
}

