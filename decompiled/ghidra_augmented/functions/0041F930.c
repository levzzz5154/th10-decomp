/* Raw Ghidra reference; not compilable reconstruction. Address: 0041F930 */

undefined4 __fastcall ReleaseResourcePair(undefined4 param_1)

{
  undefined4 extraout_ECX;
  int *piVar1;
  undefined4 *puVar2;
  
  piVar1 = (int *)((int)g_pGameStateManager + 0x3ad084);
  if (*piVar1 != 0) {
    FUN_00447810(param_1);
    _free((void *)*piVar1);
    *piVar1 = 0;
    param_1 = extraout_ECX;
  }
  puVar2 = (undefined4 *)((int)g_pGameStateManager + 0x3ad088);
  if (*(int *)((int)g_pGameStateManager + 0x3ad088) != 0) {
    FUN_00447810(param_1);
    _free((void *)*puVar2);
    *puVar2 = 0;
  }
  return 0;
}

