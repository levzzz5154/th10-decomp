/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00449450
 * Tracking name: FUN_00449450
 * Ghidra name: FUN_00449450
 * Tracked span: 32 bytes
 */


void __fastcall FUN_00449450(undefined4 param_1)

{
  int iVar1;
  int *unaff_ESI;
  
  iVar1 = FUN_004491c0(param_1,(int)g_pGameStateManager,*unaff_ESI);
  if (iVar1 == 0) {
    *unaff_ESI = 0;
  }
  return;
}

