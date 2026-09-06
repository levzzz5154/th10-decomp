/* Raw Ghidra reference; not compilable reconstruction. Address: 00461F31 */

undefined4 __cdecl FUN_00461f31(undefined4 *param_1,int param_2)

{
  uint *_Str;
  uint *puVar1;
  int iVar2;
  int *piVar3;
  size_t sVar4;
  uint *lpName;
  undefined1 *puVar5;
  BOOL BVar6;
  int *piVar7;
  bool bVar8;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 == (undefined4 *)0x0) {
    return 0xffffffff;
  }
  _Str = (uint *)*param_1;
  if (_Str == (uint *)0x0) {
    return 0xffffffff;
  }
  puVar1 = FUN_0046227b(_Str,0x3d);
  if (puVar1 == (uint *)0x0) {
    return 0xffffffff;
  }
  if (_Str == puVar1) {
    return 0xffffffff;
  }
  bVar8 = *(char *)((int)puVar1 + 1) == '\0';
  if (DAT_00477490 == DAT_00477494) {
    DAT_00477490 = copy_environ();
  }
  if (DAT_00477490 == (int *)0x0) {
    if ((param_2 != 0) && (DAT_00477498 != (undefined4 *)0x0)) {
      iVar2 = ___wtomb_environ();
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      goto LAB_00461fe6;
    }
    if (!bVar8) {
      DAT_00477490 = _malloc(4);
      if (DAT_00477490 == (int *)0x0) {
        return 0xffffffff;
      }
      *DAT_00477490 = 0;
      if (DAT_00477498 == (undefined4 *)0x0) {
        DAT_00477498 = _malloc(4);
        if (DAT_00477498 == (undefined4 *)0x0) {
          return 0xffffffff;
        }
        *DAT_00477498 = 0;
      }
      goto LAB_00461fe6;
    }
LAB_00461fb4:
    local_14 = 0;
  }
  else {
LAB_00461fe6:
    piVar3 = DAT_00477490;
    iVar2 = findenv((uchar *)_Str);
    if ((iVar2 < 0) || (*piVar3 == 0)) {
      if (bVar8) {
        _free(_Str);
        *param_1 = 0;
        goto LAB_00461fb4;
      }
      if (iVar2 < 0) {
        iVar2 = -iVar2;
      }
      piVar3 = FUN_00457395(DAT_00477490,(uint *)(iVar2 * 4 + 8));
      if (piVar3 == (int *)0x0) {
        return 0xffffffff;
      }
      (piVar3 + iVar2)[1] = 0;
      piVar3[iVar2] = (int)_Str;
      *param_1 = 0;
LAB_00462089:
      DAT_00477490 = piVar3;
    }
    else {
      piVar7 = piVar3 + iVar2;
      _free((void *)*piVar7);
      if (bVar8) {
        while (*piVar7 != 0) {
          iVar2 = iVar2 + 1;
          *piVar7 = piVar7[1];
          piVar7 = piVar3 + iVar2;
        }
        piVar3 = FUN_00457395(DAT_00477490,(uint *)(iVar2 << 2));
        if (piVar3 != (int *)0x0) goto LAB_00462089;
      }
      else {
        *piVar7 = (int)_Str;
        *param_1 = 0;
      }
    }
    if (param_2 != 0) {
      sVar4 = _strlen((char *)_Str);
      lpName = _malloc(sVar4 + 2);
      if (lpName != (uint *)0x0) {
        FUN_0045bd80(lpName,_Str);
        puVar5 = (undefined1 *)(((int)lpName - (int)_Str) + (int)puVar1);
        *puVar5 = 0;
        BVar6 = SetEnvironmentVariableA((LPCSTR)lpName,(LPCSTR)(~-(uint)bVar8 & (uint)(puVar5 + 1)))
        ;
        if (BVar6 == 0) {
          local_14 = 0xffffffff;
        }
        _free(lpName);
      }
    }
    if (bVar8) {
      _free(_Str);
    }
  }
  return local_14;
}

