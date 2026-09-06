/* Raw Ghidra reference; not compilable reconstruction. Address: 0042CD50 */

undefined4 * FUN_0042cd50(void)

{
  undefined4 *puVar1;
  uintptr_t uVar2;
  undefined4 extraout_ECX;
  
  puVar1 = operator_new(0x5acc);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = FUN_0042c920(extraout_ECX,puVar1);
  }
  FUN_0044c150();
  puVar1[0x16b2] = &LAB_0042c9f0;
  puVar1[0x16b0] = 1;
  puVar1[0x16af] = 0;
  uVar2 = __beginthreadex((void *)0x0,0,(_StartAddress *)&LAB_0042c9f0,puVar1,0,puVar1 + 0x16ae);
  puVar1[0x16ad] = uVar2;
  return puVar1;
}

