/* Raw Ghidra reference; not compilable reconstruction. Address: 0045B5BC */

/* Library Function - Single Match
    ___free_lconv_num
   
   Library: Visual Studio 2003 Release */

void __cdecl ___free_lconv_num(undefined4 *param_1)

{
  undefined *puVar1;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined *)*param_1;
    if ((puVar1 != *(undefined **)PTR_PTR_00473ad4) && (puVar1 != PTR_DAT_00473aa4)) {
      _free(puVar1);
    }
    puVar1 = (undefined *)param_1[1];
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 4)) && (puVar1 != PTR_DAT_00473aa8)) {
      _free(puVar1);
    }
    puVar1 = (undefined *)param_1[2];
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 8)) && (puVar1 != PTR_DAT_00473aac)) {
      _free(puVar1);
    }
  }
  return;
}

