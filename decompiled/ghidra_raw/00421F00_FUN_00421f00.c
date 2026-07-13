/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421F00
 * Tracking name: FUN_00421f00
 * Ghidra name: FUN_00421f00
 * Tracked span: 96 bytes
 */


void __fastcall FUN_00421f00(undefined4 param_1)

{
  int iVar1;
  undefined4 *unaff_ESI;
  undefined4 *puVar2;
  
  FUN_00418c40(param_1,unaff_ESI + 0x48);
  unaff_ESI[0x18c] = 0;
  unaff_ESI[0x18d] = 0;
  unaff_ESI[0x18e] = 0;
  unaff_ESI[399] = 0;
  unaff_ESI[0x18b] = &PTR_FUN_004703e4;
  puVar2 = unaff_ESI;
  for (iVar1 = 0x1e1; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[0xf3] = unaff_ESI[0xf3] | 0x140;
  return;
}

