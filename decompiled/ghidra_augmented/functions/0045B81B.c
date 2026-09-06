/* Raw Ghidra reference; not compilable reconstruction. Address: 0045B81B */

/* Library Function - Single Match
    ___free_lconv_mon
   
   Library: Visual Studio 2003 Release */

void __cdecl ___free_lconv_mon(int param_1)

{
  undefined *puVar1;
  
  if (param_1 != 0) {
    puVar1 = *(undefined **)(param_1 + 0xc);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0xc)) && (puVar1 != PTR_DAT_00473ab0)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x10);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0x10)) && (puVar1 != PTR_DAT_00473ab4)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x14);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0x14)) && (puVar1 != PTR_DAT_00473ab8)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x18);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0x18)) && (puVar1 != PTR_DAT_00473abc)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x1c);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0x1c)) && (puVar1 != PTR_DAT_00473ac0)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x20);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0x20)) && (puVar1 != PTR_DAT_00473ac4)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x24);
    if ((puVar1 != *(undefined **)(PTR_PTR_00473ad4 + 0x24)) && (puVar1 != PTR_DAT_00473ac8)) {
      _free(puVar1);
    }
  }
  return;
}

