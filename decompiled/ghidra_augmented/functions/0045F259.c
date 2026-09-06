/* Raw Ghidra reference; not compilable reconstruction. Address: 0045F259 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_0045f259(int param_1)

{
  DWORD DVar1;
  size_t sVar2;
  uint *_Str;
  char *pcVar3;
  uint *local_12c;
  uint local_128 [65];
  undefined1 local_24;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046c810;
  uStack_c = 0x45f268;
  local_20 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  if (DAT_00477698 == (code *)0x0) {
    if (param_1 == 1) {
      pcVar3 = "Buffer overrun detected!";
      local_12c = (uint *)0x46c678;
    }
    else {
      pcVar3 = "Unknown security failure detected!";
      local_12c = (uint *)0x46c738;
    }
    local_24 = 0;
    DVar1 = GetModuleFileNameA((HMODULE)0x0,(LPSTR)local_128,0x104);
    if (DVar1 == 0) {
      FUN_0045bd80(local_128,(uint *)"<program name unknown>");
    }
    _Str = local_128;
    sVar2 = _strlen((char *)_Str);
    if (0x3c < sVar2 + 0xb) {
      sVar2 = _strlen((char *)_Str);
      _Str = (uint *)(&stack0xfffffea7 + sVar2);
      _strncpy((char *)_Str,"...",3);
    }
    _strlen((char *)_Str);
    local_1c = &stack0xfffffec8;
    FUN_0045bd80((uint *)&stack0xfffffec8,(uint *)pcVar3);
    FUN_0045bd90((uint *)&stack0xfffffec8,(uint *)&DAT_0046b008);
    FUN_0045bd90((uint *)&stack0xfffffec8,(uint *)"Program: ");
    FUN_0045bd90((uint *)&stack0xfffffec8,_Str);
    FUN_0045bd90((uint *)&stack0xfffffec8,(uint *)&DAT_0046b008);
    FUN_0045bd90((uint *)&stack0xfffffec8,local_12c);
    ___crtMessageBoxA(&stack0xfffffec8,"Microsoft Visual C++ Runtime Library",0x12010);
  }
  else {
    local_8 = (undefined *)0x0;
    (*DAT_00477698)();
    local_8 = (undefined *)0xffffffff;
  }
                    /* WARNING: Subroutine does not return */
  __exit(3);
}

