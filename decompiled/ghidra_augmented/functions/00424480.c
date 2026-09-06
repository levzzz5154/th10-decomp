/* Raw Ghidra reference; not compilable reconstruction. Address: 00424480 */

undefined8 __thiscall
FUN_00424480(void *this,int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            uint param_5)

{
  int iVar1;
  int unaff_ESI;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  iVar1 = FUN_004491c0(this,(int)g_pGameStateManager,param_1);
  uVar2 = FUN_00463b2c();
  uVar3 = FUN_00463b2c();
  uVar4 = FUN_00463b2c();
  uVar5 = FUN_00463b2c();
  if (-1 < *(int *)(unaff_ESI + 4)) {
    return CONCAT44((int)(uVar5 >> 0x20),0xffffffff);
  }
  *(undefined4 *)(unaff_ESI + 4) = **(undefined4 **)(iVar1 + 0x308);
  *(undefined4 *)(unaff_ESI + 8) = param_2;
  *(int *)(unaff_ESI + 0x18) = (int)uVar5;
  *(undefined4 *)(unaff_ESI + 0xc) = param_3;
  *(undefined4 *)(unaff_ESI + 0x10) = param_4;
  *(int *)(unaff_ESI + 0x24) = (int)uVar2;
  *(int *)(unaff_ESI + 0x1c) = (int)uVar4;
  *(uint *)(unaff_ESI + 0x14) = param_5;
  *(int *)(unaff_ESI + 0x20) = (int)uVar3;
  *(undefined4 *)(unaff_ESI + 0x28) = 0;
  return (ulonglong)param_5 << 0x20;
}

