/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004180E0
 * Tracking name: FUN_004180e0
 * Ghidra name: FUN_004180e0
 * Tracked span: 112 bytes
 */


undefined4 * FUN_004180e0(void)

{
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  int iVar2;
  undefined4 *puVar3;
  undefined4 unaff_retaddr;
  
  puVar1 = operator_new(0x60);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[8] = puVar1[8] & 0xfffffffe;
    FUN_00418c40(extraout_ECX,puVar1 + 9);
    puVar3 = puVar1;
    for (iVar2 = 0x18; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
  }
  (**(code **)(*(int *)g_pD3DDevice + 0x14))(g_pD3DDevice);
  puVar1[0x17] = unaff_retaddr;
  DAT_00477810 = puVar1;
  puVar1[0x16] = puVar1[0x16] | 4;
  FUN_00420ea0((_StartAddress *)&LAB_00417c70,(void *)0x0);
  return puVar1;
}

