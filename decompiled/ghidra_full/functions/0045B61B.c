/* Raw Ghidra reference; not compilable reconstruction. Address: 0045B61B */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___init_numeric
   
   Library: Visual Studio 2003 Release */

int __cdecl ___init_numeric(threadlocinfo *_LocInfo)

{
  char *pcVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  undefined **_Memory;
  _locale_t plVar8;
  char *pcVar9;
  undefined **ppuVar10;
  
  if ((DAT_0047765c == 0) && (DAT_00477658 == 0)) {
    if (((DAT_004981cc != (int *)0x0) && (*DAT_004981cc == 0)) &&
       (DAT_004981cc != *(int **)(PTR_DAT_0047320c + 0x2c))) {
      _free(DAT_004981cc);
      _free(DAT_00477624);
    }
    DAT_004981d0 = (undefined4 *)0x0;
    DAT_004981cc = (int *)0x0;
    _Memory = &PTR_DAT_00473aa4;
    DAT_00477624 = (undefined **)0x0;
    ppuVar10 = DAT_00477624;
    piVar3 = DAT_004981cc;
LAB_0045b7c8:
    DAT_004981cc = piVar3;
    DAT_00477624 = ppuVar10;
    DAT_00473af4 = **_Memory;
    _DAT_00473af8 = 1;
    iVar7 = 0;
    PTR_PTR_00473ad4 = (undefined *)_Memory;
  }
  else {
    _Memory = (undefined **)FUN_0045794d(1,0x30);
    if (_Memory != (undefined **)0x0) {
      piVar3 = (int *)PTR_PTR_00473ad4;
      ppuVar10 = _Memory;
      for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
        *ppuVar10 = (undefined *)*piVar3;
        piVar3 = piVar3 + 1;
        ppuVar10 = ppuVar10 + 1;
      }
      piVar3 = _malloc(4);
      if (piVar3 != (int *)0x0) {
        *piVar3 = 0;
        if (DAT_0047765c == 0) {
          DAT_004981d0 = (undefined4 *)0x0;
          *_Memory = PTR_DAT_00473aa4;
          _Memory[1] = PTR_DAT_00473aa8;
          _Memory[2] = PTR_DAT_00473aac;
        }
        else {
          DAT_004981d0 = _malloc(4);
          if (DAT_004981d0 == (undefined4 *)0x0) {
            iVar7 = 1;
LAB_0045b726:
            _free(_Memory);
            _free(piVar3);
            return iVar7;
          }
          *DAT_004981d0 = 0;
          plVar8 = (_locale_t)(uint)DAT_00477686;
          iVar7 = FUN_0046041e(1,plVar8,(LPCWSTR)0xe,(char *)_Memory);
          iVar4 = FUN_0046041e(1,plVar8,(LPCWSTR)0xf,(char *)(_Memory + 1));
          iVar5 = FUN_0046041e(1,plVar8,(LPCWSTR)0x10,(char *)(_Memory + 2));
          if (iVar5 != 0 || (iVar7 != 0 || iVar4 != 0)) {
            ___free_lconv_num(_Memory);
            iVar7 = -1;
            goto LAB_0045b726;
          }
          pcVar6 = _Memory[2];
          while (*pcVar6 != '\0') {
            cVar2 = *pcVar6;
            if ((cVar2 < '0') || ('9' < cVar2)) {
              pcVar9 = pcVar6;
              if (cVar2 != ';') goto LAB_0045b752;
              do {
                pcVar1 = pcVar9 + 1;
                *pcVar9 = *pcVar1;
                pcVar9 = pcVar1;
              } while (*pcVar1 != '\0');
            }
            else {
              *pcVar6 = cVar2 + -0x30;
LAB_0045b752:
              pcVar6 = pcVar6 + 1;
            }
          }
        }
        ppuVar10 = _Memory;
        if (((DAT_004981cc != (int *)0x0) && (*DAT_004981cc == 0)) &&
           (DAT_004981cc != *(int **)(PTR_DAT_0047320c + 0x2c))) {
          _free(DAT_004981cc);
          _free(DAT_00477624);
        }
        goto LAB_0045b7c8;
      }
      _free(_Memory);
    }
    iVar7 = 1;
  }
  return iVar7;
}

