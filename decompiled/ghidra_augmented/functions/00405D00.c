/* Raw Ghidra reference; not compilable reconstruction. Address: 00405D00 */

int __fastcall FUN_00405d00(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(uint *)(param_1 + 0x74) = *(uint *)(param_1 + 0x74) & 0xfffffffe;
  *(uint *)(param_1 + 0xb8) = *(uint *)(param_1 + 0xb8) & 0xfffffffe;
  *(uint *)(param_1 + 0x104) = *(uint *)(param_1 + 0x104) & 0xfffffffe;
  *(uint *)(param_1 + 0x130) = *(uint *)(param_1 + 0x130) & 0xfffffffe;
  *(uint *)(param_1 + 0x17c) = *(uint *)(param_1 + 0x17c) & 0xfffffffe;
  *(uint *)(param_1 + 0x1b8) = *(uint *)(param_1 + 0x1b8) & 0xfffffffe;
  *(uint *)(param_1 + 0x204) = *(uint *)(param_1 + 0x204) & 0xfffffffe;
  *(uint *)(param_1 + 0x230) = *(uint *)(param_1 + 0x230) & 0xfffffffe;
  *(uint *)(param_1 + 0x380) = *(uint *)(param_1 + 0x380) & 0xfffffffe;
  puVar2 = (undefined4 *)(param_1 + 8);
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(param_1 + 0x38c) = 0xffff;
  *(uint *)(param_1 + 0x408) = *(uint *)(param_1 + 0x408) & 0xfffffffe;
  *(uint *)(param_1 + 0x41c) = *(uint *)(param_1 + 0x41c) & 0xfffffffe;
  *(uint *)(param_1 + 0x624) = *(uint *)(param_1 + 0x624) & 0xfffffffe;
  *(uint *)(param_1 + 0x658) = *(uint *)(param_1 + 0x658) & 0xfffffffe;
  *(uint *)(param_1 + 0x68c) = *(uint *)(param_1 + 0x68c) & 0xfffffffe;
  *(uint *)(param_1 + 0x6c0) = *(uint *)(param_1 + 0x6c0) & 0xfffffffe;
  *(uint *)(param_1 + 0x6f4) = *(uint *)(param_1 + 0x6f4) & 0xfffffffe;
  *(uint *)(param_1 + 0x728) = *(uint *)(param_1 + 0x728) & 0xfffffffe;
  *(uint *)(param_1 + 0x75c) = *(uint *)(param_1 + 0x75c) & 0xfffffffe;
  *(uint *)(param_1 + 0x790) = *(uint *)(param_1 + 0x790) & 0xfffffffe;
  *(uint *)(param_1 + 0x7c4) = *(uint *)(param_1 + 0x7c4) & 0xfffffffe;
  return param_1;
}

