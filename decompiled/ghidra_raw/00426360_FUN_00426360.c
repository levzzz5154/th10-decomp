/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00426360
 * Tracking name: FUN_00426360
 * Ghidra name: FUN_00426360
 * Tracked span: 448 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00426360(void)

{
  void *pvVar1;
  int in_EAX;
  int iVar2;
  undefined4 *puVar3;
  
  pvVar1 = g_pGameStateManager;
  if (*(int *)(in_EAX + 0x458) != 2) {
    *(float *)(in_EAX + 0x354) = *(float *)(in_EAX + 0x3c0) + _DAT_00470b4c;
    *(float *)(in_EAX + 0x358) = *(float *)(in_EAX + 0x3c4) + _DAT_00470b48;
    *(undefined4 *)(in_EAX + 0x35c) = *(undefined4 *)(in_EAX + 0x3c8);
    FUN_004451c0(pvVar1);
    puVar3 = (undefined4 *)(in_EAX + 0x3334);
    iVar2 = 4;
    do {
      if ((code *)*puVar3 != (code *)0x0) {
        (*(code *)*puVar3)();
      }
      puVar3 = puVar3 + 0x26;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (((((DAT_00477810 != 0) && (*(char *)(DAT_00477810 + 0x54) < '\0')) && (DAT_00477704 != 0))
        && ((DAT_0047770c != 0 && (*(int *)(DAT_00477704 + 0x10) == 0)))) &&
       ((*(int *)(DAT_0047770c + 0x9eb8) == 0 &&
        ((*(int *)(DAT_00477830 + 4) == 0 && (DAT_00474c58 != 0)))))) {
      FUN_00427c50((*(float *)(in_EAX + 0x3c0) + _DAT_00470cbc) - _DAT_00470b48);
      FUN_00427c50((*(float *)(in_EAX + 0x3c4) + _DAT_00470cb4) - _DAT_00470be8);
      FUN_0043bda0();
      FUN_0043bda0();
    }
  }
  return 1;
}

