/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C8C0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0041c8c0(void *this,undefined4 *param_1)

{
  float fVar1;
  void *this_00;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  uint extraout_EDX;
  uint extraout_EDX_00;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)((int)this + 0x424);
  for (iVar2 = 0x77; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)((int)this + 0xc) = 2;
  FUN_00404f30(*(void **)((int)DAT_0047781c + 0x458),*(void **)((int)DAT_0047781c + 0x458));
  *(undefined2 *)((int)this + 0x904) = 2;
  FUN_0043ee30(extraout_ECX,extraout_EDX,(int)this + 0x600);
  if ((*(byte *)((int)this + 0x44c) & 1) != 0) {
    *(uint *)((int)this + 0x95c) = *(uint *)((int)this + 0x95c) & 0xffffffdf | 0x10;
  }
  this_00 = DAT_0047781c;
  *(uint *)((int)this + 0x95c) = *(uint *)((int)this + 0x95c) & 0xfc63ffff | 0x600000;
  FUN_00404f30(this_00,*(undefined2 **)((int)this_00 + 0x458));
  *(undefined2 *)((int)this + 0xcb0) = 2;
  FUN_0043ee30(extraout_ECX_00,extraout_EDX_00,(int)this + 0x9ac);
  *(uint *)((int)this + 0xd08) = *(uint *)((int)this + 0xd08) & 0xffffffdf | 0x10;
  *(uint *)((int)this + 0xd08) = *(uint *)((int)this + 0xd08) & 0xfc7fffff | 0x400000;
  if ((*(uint *)((int)this + 0x420) & 1) == 0) {
    *(undefined4 *)((int)this + 0x414) = 0;
    *(undefined4 *)((int)this + 0x410) = 0xfff0bdc1;
    *(undefined4 *)((int)this + 0x418) = 0;
    *(undefined4 **)((int)this + 0x41c) = &DAT_00476f78;
    *(uint *)((int)this + 0x420) = *(uint *)((int)this + 0x420) | 1;
  }
  *(undefined4 *)((int)this + 0x414) = 0x1e;
  *(undefined4 *)((int)this + 0x418) = 0x41f00000;
  *(undefined4 *)((int)this + 0x410) = 0x1d;
  *(float *)((int)this + 0x40) = *(float *)((int)this + 0x438);
  *(undefined4 *)((int)this + 0x24) = *(undefined4 *)((int)this + 0x424);
  *(float *)((int)this + 0x48) = *(float *)((int)this + 0x444);
  *(undefined4 *)((int)this + 0x28) = *(undefined4 *)((int)this + 0x428);
  *(float *)((int)this + 0x3c) = *(float *)((int)this + 0x430);
  *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)((int)this + 0x42c);
  fVar1 = _DAT_00470b04;
  *(undefined4 *)((int)this + 0x40c) = 0x18;
  *(undefined4 *)((int)this + 0x44) = *(undefined4 *)((int)this + 0x440);
  if (*(float *)((int)this + 0x438) <= fVar1) {
    *(undefined4 *)((int)this + 0x4c) = 0;
  }
  else {
    *(undefined4 *)((int)this + 0x4c) = 0x3c23d70a;
  }
  FUN_0041f800((void *)((int)this + 0x30),*(float *)((int)this + 0x430),
               *(float *)((int)this + 0x444));
  return 0;
}

