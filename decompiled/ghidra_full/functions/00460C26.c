/* Raw Ghidra reference; not compilable reconstruction. Address: 00460C26 */

/* Library Function - Single Match
    ___tolower_mt
   
   Library: Visual Studio 2003 Release */

uint __thiscall ___tolower_mt(void *this,int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_8;
  
  uVar3 = param_2;
  iVar1 = param_1;
  if ((*(int *)(param_1 + 0x14) == 0) || ((*(int *)(param_1 + 0x24) != 0 && (param_2 < 0x80)))) {
    if ((0x40 < (int)param_2) && ((int)param_2 < 0x5b)) {
      return param_2 + 0x20;
    }
  }
  else {
    local_8 = this;
    if (param_2 < 0x100) {
      if (*(int *)(param_1 + 0x28) < 2) {
        uVar4 = *(byte *)(*(int *)(param_1 + 0x48) + param_2 * 2) & 1;
      }
      else {
        uVar4 = ___isctype_mt(this,param_1,param_2,1);
      }
      if (uVar4 == 0) {
        return uVar3;
      }
    }
    iVar2 = param_1;
    if ((*(byte *)(*(int *)(iVar1 + 0x48) + 1 + ((int)uVar3 >> 8 & 0xffU) * 2) & 0x80) == 0) {
      param_1._0_2_ = (ushort)(byte)uVar3;
      uVar4 = 1;
    }
    else {
      param_1._0_2_ = CONCAT11((byte)uVar3,(char)(uVar3 >> 8));
      param_1._3_1_ = SUB41(iVar2,3);
      param_1._0_3_ = (uint3)(ushort)param_1;
      uVar4 = 2;
    }
    uVar4 = FUN_0045ee1d(*(LCID *)(iVar1 + 0x14),0x100,(LPCSTR)&param_1,uVar4,&local_8,3,
                         *(UINT *)(iVar1 + 4),1);
    if (uVar4 != 0) {
      if (uVar4 != 1) {
        return (uint)CONCAT11((undefined1)local_8,local_8._1_1_);
      }
      return (uint)local_8 & 0xff;
    }
  }
  return uVar3;
}

