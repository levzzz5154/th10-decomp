/* Raw Ghidra reference; not compilable reconstruction. Address: 00437160 */

int __thiscall FUN_00437160(void *this,int param_1)

{
  int iVar1;
  uint3 uVar3;
  uint uVar2;
  int iVar4;
  ushort *puVar5;
  
  puVar5 = *(ushort **)((int)this + 0x120);
  iVar1 = *(int *)((int)this + 0x110) * param_1;
  iVar4 = *(int *)((int)this + 0x100);
  uVar3 = (uint3)((uint)iVar1 >> 8);
  if (iVar4 == 0x15) {
    iVar4 = 3;
    if (3 < iVar1) {
      do {
        *(byte *)(iVar4 + (int)puVar5) = ~*(byte *)(iVar4 + (int)puVar5);
        iVar4 = iVar4 + 4;
      } while (iVar4 < iVar1);
    }
  }
  else if (iVar4 == 0x19) {
    if (0 < iVar1) {
      iVar4 = (iVar1 - 1U >> 1) + 1;
      do {
        uVar2 = ~(uint)*puVar5 ^ 0x7fff;
        *puVar5 = (ushort)uVar2;
        if (-1 < (char)(uVar2 >> 8)) {
          uVar2 = uVar2 & 0x8000;
          *puVar5 = (ushort)uVar2;
        }
        puVar5 = puVar5 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      return CONCAT31((int3)(uVar2 >> 8),1);
    }
  }
  else {
    if (iVar4 != 0x1a) {
      return (uint)uVar3 << 8;
    }
    iVar4 = 1;
    if (1 < iVar1) {
      do {
        *(byte *)(iVar4 + (int)puVar5) = *(byte *)(iVar4 + (int)puVar5) ^ 0xf0;
        iVar4 = iVar4 + 2;
      } while (iVar4 < iVar1);
      return CONCAT31(uVar3,1);
    }
  }
  return CONCAT31(uVar3,1);
}

