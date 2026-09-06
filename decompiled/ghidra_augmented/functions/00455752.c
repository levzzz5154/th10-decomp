/* Raw Ghidra reference; not compilable reconstruction. Address: 00455752 */

/* Library Function - Single Match
    ___isctype_mt
   
   Library: Visual Studio 2003 Release */

uint __thiscall ___isctype_mt(void *this,int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  LPCSTR _LpSrcStr;
  BOOL BVar2;
  undefined4 local_8;
  
  if (param_2 + 1U < 0x101) {
    param_2._2_2_ = *(ushort *)(*(int *)(param_1 + 0x48) + param_2 * 2);
  }
  else {
    local_8._2_2_ = (undefined2)((uint)this >> 0x10);
    if ((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (param_2 >> 8 & 0xffU) * 2) & 0x80) == 0) {
      local_8._0_2_ = (ushort)(byte)param_2;
      _LpSrcStr = (LPCSTR)0x1;
    }
    else {
      local_8 = CONCAT31(CONCAT21(local_8._2_2_,(byte)param_2),(char)((uint)param_2 >> 8));
      uVar1 = local_8;
      local_8._3_1_ = (undefined1)((uint)this >> 0x18);
      local_8._0_2_ = (ushort)uVar1;
      local_8._0_3_ = (uint3)(ushort)local_8;
      _LpSrcStr = (LPCSTR)0x2;
    }
    BVar2 = ___crtGetStringTypeA
                      ((_locale_t)0x1,(DWORD)&local_8,_LpSrcStr,(int)&param_2 + 2,
                       *(LPWORD *)(param_1 + 4),*(int *)(param_1 + 0x14),1);
    if (BVar2 == 0) {
      return 0;
    }
  }
  return param_2._2_2_ & param_3;
}

