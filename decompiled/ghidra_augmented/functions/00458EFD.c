/* Raw Ghidra reference; not compilable reconstruction. Address: 00458EFD */

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl FUN_00458efd(int param_1)

{
  int iVar1;
  uint uVar2;
  DWORD DVar3;
  size_t sVar4;
  size_t sVar5;
  HANDLE hFile;
  int iVar6;
  uint *_Str;
  undefined4 uStackY_150;
  undefined1 auStackY_14c [4];
  UINT aUStackY_148 [2];
  undefined4 auStackY_140 [2];
  undefined4 uStackY_138;
  LPCVOID lpBuffer;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  DWORD local_114;
  uint local_110 [31];
  undefined1 local_94 [136];
  undefined1 local_c;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_94;
  uVar2 = 0;
  do {
    if (param_1 == (&DAT_00473670)[uVar2 * 2]) break;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x13);
  iVar6 = uVar2 * 8;
  if (param_1 == (&DAT_00473670)[uVar2 * 2]) {
    if ((DAT_0047720c == 1) || ((DAT_0047720c == 0 && (DAT_00473074 == 1)))) {
      lpOverlapped = (LPOVERLAPPED)0x0;
      lpNumberOfBytesWritten = &local_114;
      sVar4 = _strlen(*(char **)(iVar6 + 0x473674));
      lpBuffer = *(LPCVOID *)(iVar6 + 0x473674);
      uStackY_138 = 0x459050;
      hFile = GetStdHandle(0xfffffff4);
      uStackY_138 = 0x459057;
      WriteFile(hFile,lpBuffer,sVar4,lpNumberOfBytesWritten,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      local_c = 0;
      DVar3 = GetModuleFileNameA((HMODULE)0x0,(LPSTR)local_110,0x104);
      if (DVar3 == 0) {
        FUN_0045bd80(local_110,(uint *)"<program name unknown>");
      }
      _Str = local_110;
      sVar4 = _strlen((char *)_Str);
      if (0x3c < sVar4 + 1) {
        sVar4 = _strlen((char *)_Str);
        _Str = (uint *)(auStackY_14c + sVar4 + 1);
        _strncpy((char *)_Str,"...",3);
      }
      sVar4 = _strlen((char *)_Str);
      sVar5 = _strlen(*(char **)(iVar6 + 0x473674));
      iVar1 = -(sVar4 + sVar5 + 0x1f & 0xfffffffc);
      *(char **)((int)local_110 + iVar1 + -0x14) = "Runtime Error!\n\nProgram: ";
      *(int *)((int)local_110 + iVar1 + -0x18) = (int)local_110 + iVar1 + -0x10;
      *(undefined4 *)((int)local_110 + iVar1 + -0x1c) = 0x458fff;
      FUN_0045bd80(*(uint **)((int)local_110 + iVar1 + -0x18),
                   *(uint **)((int)local_110 + iVar1 + -0x14));
      *(uint **)((int)local_110 + iVar1 + -0x1c) = _Str;
      *(int *)((int)local_110 + iVar1 + -0x20) = (int)local_110 + iVar1 + -0x10;
      *(undefined4 *)(&stack0xfffffecc + iVar1) = 0x459006;
      FUN_0045bd90(*(uint **)((int)local_110 + iVar1 + -0x20),
                   *(uint **)((int)local_110 + iVar1 + -0x1c));
      *(undefined **)(&stack0xfffffecc + iVar1) = &DAT_0046b008;
      *(int *)((int)&uStackY_138 + iVar1) = (int)local_110 + iVar1 + -0x10;
      *(undefined4 *)((int)auStackY_140 + iVar1 + 4) = 0x459011;
      FUN_0045bd90(*(uint **)((int)&uStackY_138 + iVar1),*(uint **)(&stack0xfffffecc + iVar1));
      *(undefined4 *)((int)auStackY_140 + iVar1 + 4) = *(undefined4 *)(iVar6 + 0x473674);
      *(int *)((int)auStackY_140 + iVar1) = (int)local_110 + iVar1 + -0x10;
      *(undefined4 *)((int)aUStackY_148 + iVar1 + 4) = 0x45901d;
      FUN_0045bd90(*(uint **)((int)auStackY_140 + iVar1),*(uint **)((int)auStackY_140 + iVar1 + 4));
      *(undefined4 *)((int)aUStackY_148 + iVar1 + 4) = 0x12010;
      *(char **)((int)aUStackY_148 + iVar1) = "Microsoft Visual C++ Runtime Library";
      *(int *)((int)auStackY_14c + iVar1) = (int)local_110 + iVar1 + -0x10;
      *(undefined4 *)((int)&uStackY_150 + iVar1) = 0x45902d;
      ___crtMessageBoxA(*(LPCSTR *)(auStackY_14c + iVar1),*(LPCSTR *)((int)aUStackY_148 + iVar1),
                        *(UINT *)((int)aUStackY_148 + iVar1 + 4));
    }
  }
  return;
}

