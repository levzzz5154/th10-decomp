/* Raw Ghidra reference; not compilable reconstruction. Address: 004188A0 */

void __fastcall FUN_004188a0(int param_1)

{
  undefined4 *puVar1;
  int in_EAX;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  int iVar3;
  
  iVar3 = *(int *)(in_EAX + 0x30) + param_1;
  *(int *)(in_EAX + 0x30) = iVar3;
  if (9 < iVar3) {
    *(undefined4 *)(in_EAX + 0x30) = 9;
    SetAnimationActiveCount(DAT_00474c70);
    return;
  }
  FUN_0043dc90(&DAT_00492590,0);
  iVar3 = DAT_0047770c;
  puVar1 = (undefined4 *)(DAT_0047770c + 0x9e18);
  FUN_004492a0(extraout_ECX,(int)g_pGameStateManager,*(int *)(DAT_0047770c + 0x9e18));
  *puVar1 = 0;
  puVar2 = (undefined4 *)FUN_00448d00(*(undefined4 *)(iVar3 + 0x9ec8),0x4b,0xf);
  *puVar1 = *puVar2;
  SetAnimationActiveCount(DAT_00474c70);
  return;
}

