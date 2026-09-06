/* Raw Ghidra reference; not compilable reconstruction. Address: 0041E5C0 */

undefined4 __thiscall FUN_0041e5c0(void *this,undefined4 *param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  uint extraout_EDX;
  uint extraout_EDX_00;
  undefined4 *puVar3;
  
  pvVar1 = DAT_0047781c;
  puVar3 = (undefined4 *)((int)this + 0x424);
  for (iVar2 = 0x7e; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)((int)this + 0xc) = 3;
  FUN_00404f30(*(void **)((int)pvVar1 + 0x458),*(void **)((int)pvVar1 + 0x458));
  *(undefined2 *)((int)this + 0x920) = 2;
  FUN_0043ee30(extraout_ECX,extraout_EDX,(int)this + 0x61c);
  if ((*(byte *)((int)this + 0x468) & 2) != 0) {
    *(uint *)((int)this + 0x978) = *(uint *)((int)this + 0x978) & 0xffffffdf | 0x10;
  }
  pvVar1 = DAT_0047781c;
  *(uint *)((int)this + 0x978) = *(uint *)((int)this + 0x978) & 0xfc63ffff | 0x600000;
  FUN_00404f30(pvVar1,*(undefined2 **)((int)pvVar1 + 0x458));
  *(undefined2 *)((int)this + 0xccc) = 2;
  FUN_0043ee30(extraout_ECX_00,extraout_EDX_00,(int)this + 0x9c8);
  *(uint *)((int)this + 0xd24) = *(uint *)((int)this + 0xd24) & 0xffffffdf | 0x10;
  *(undefined4 *)((int)this + 0x24) = *(undefined4 *)((int)this + 0x424);
  *(uint *)((int)this + 0xd24) = *(uint *)((int)this + 0xd24) & 0xfc7fffff | 0x400000;
  *(undefined4 *)((int)this + 0x28) = *(undefined4 *)((int)this + 0x428);
  *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)((int)this + 0x42c);
  *(undefined4 *)((int)this + 0x3c) = *(undefined4 *)((int)this + 0x43c);
  *(undefined4 *)((int)this + 0x40c) = 0x18;
  *(undefined4 *)((int)this + 0x40) = *(undefined4 *)((int)this + 0x448);
  *(undefined4 *)((int)this + 0x44) = 0x40000000;
  *(undefined4 *)((int)this + 0x48) = *(undefined4 *)((int)this + 0x450);
  return 0;
}

