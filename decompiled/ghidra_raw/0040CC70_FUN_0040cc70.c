/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CC70
 * Tracking name: FUN_0040cc70
 * Ghidra name: FUN_0040cc70
 * Tracked span: 176 bytes
 */


int __fastcall FUN_0040cc70(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *(uint *)(param_2 + 300) = *(uint *)(param_2 + 300) & 0xfffffffe;
  *(uint *)(param_2 + 0x17c) = *(uint *)(param_2 + 0x17c) & 0xfffffffe;
  *(uint *)(param_2 + 0x1c8) = *(uint *)(param_2 + 0x1c8) & 0xfffffffe;
  *(uint *)(param_2 + 0x204) = *(uint *)(param_2 + 0x204) & 0xfffffffe;
  *(uint *)(param_2 + 0x240) = *(uint *)(param_2 + 0x240) & 0xfffffffe;
  *(uint *)(param_2 + 0x27c) = *(uint *)(param_2 + 0x27c) & 0xfffffffe;
  *(uint *)(param_2 + 0x2b8) = *(uint *)(param_2 + 0x2b8) & 0xfffffffe;
  puVar3 = (undefined4 *)(param_2 + 0x2c4);
  iVar2 = 8;
  do {
    puVar4 = puVar3;
    for (iVar1 = 0x84; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    puVar3[0x81] = 0xffffffff;
    puVar3 = puVar3 + 0x84;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(uint *)(param_2 + 0x142c) = *(uint *)(param_2 + 0x142c) & 0xfffffffe;
  *(uint *)(param_2 + 0x1440) = *(uint *)(param_2 + 0x1440) & 0xfffffffe;
  return param_2;
}

