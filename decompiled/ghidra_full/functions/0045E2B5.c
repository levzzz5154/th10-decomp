/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E2B5 */

/* Library Function - Single Match
    ___mbtowc_mt
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl ___mbtowc_mt(int param_1,LPWSTR param_2,byte *param_3,uint param_4)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  
  if ((param_3 != (byte *)0x0) && (param_4 != 0)) {
    bVar1 = *param_3;
    if (bVar1 != 0) {
      if (*(int *)(param_1 + 0x14) == 0) {
        if (param_2 != (LPWSTR)0x0) {
          *param_2 = (ushort)bVar1;
        }
        return 1;
      }
      if ((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (uint)bVar1 * 2) & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(*(UINT *)(param_1 + 4),9,(LPCSTR)param_3,1,param_2,
                                    (uint)(param_2 != (LPWSTR)0x0));
        if (iVar2 != 0) {
          return 1;
        }
      }
      else {
        iVar2 = *(int *)(param_1 + 0x28);
        if ((((1 < iVar2) && (iVar2 <= (int)param_4)) &&
            (iVar2 = MultiByteToWideChar(*(UINT *)(param_1 + 4),9,(LPCSTR)param_3,iVar2,param_2,
                                         (uint)(param_2 != (LPWSTR)0x0)), iVar2 != 0)) ||
           ((*(uint *)(param_1 + 0x28) <= param_4 && (param_3[1] != 0)))) {
          return *(undefined4 *)(param_1 + 0x28);
        }
      }
      piVar3 = FUN_00456af2();
      *piVar3 = 0x2a;
      return 0xffffffff;
    }
    if (param_2 != (LPWSTR)0x0) {
      *param_2 = L'\0';
    }
  }
  return 0;
}

