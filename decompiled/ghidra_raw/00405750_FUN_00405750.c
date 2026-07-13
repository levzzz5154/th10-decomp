/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405750
 * Tracking name: FUN_00405750
 * Ghidra name: FUN_00405750
 * Tracked span: 272 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00405750(undefined4 param_1)

{
  int iVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  int unaff_EDI;
  
  pvVar3 = g_pGameStateManager;
  if (*(int *)(unaff_EDI + 0x28) != 0) {
    if (*(int *)(unaff_EDI + 0x28) == 1) {
      iVar4 = FUN_004491c0(param_1,(int)g_pGameStateManager,*(int *)(unaff_EDI + 0x2c));
      if (iVar4 == 0) {
        *(undefined4 *)(unaff_EDI + 0x2c) = 0;
        *(undefined4 *)(unaff_EDI + 0x28) = 0;
        return 1;
      }
      if (((*(byte *)(DAT_004776f4 + 0x378c) & 1) == 0) ||
         (((iVar1 = *(int *)(DAT_004776f4 + 0x3788), iVar1 < 0x5d || (0x60 < iVar1)) &&
          (iVar1 != 0x6d)))) {
        if (DAT_00474c68 == 0) {
          fVar2 = *(float *)(unaff_EDI + 0x34) - _DAT_00470afc;
        }
        else {
          fVar2 = *(float *)(unaff_EDI + 0x34) - _DAT_00470d34;
        }
      }
      else {
        fVar2 = *(float *)(unaff_EDI + 0x34) - _DAT_00470b0c;
      }
      *(float *)(unaff_EDI + 0x34) = fVar2;
      FUN_004492f0(*(undefined4 *)(unaff_EDI + 0x38),(int)pvVar3,*(int *)(unaff_EDI + 0x2c));
      *(undefined4 *)(unaff_EDI + 0x3c) = *(undefined4 *)(iVar4 + 0x40);
      FUN_00405ac0();
    }
    FUN_00404ed0();
  }
  return 1;
}

