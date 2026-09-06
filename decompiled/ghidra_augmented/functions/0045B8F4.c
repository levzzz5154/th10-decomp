/* Raw Ghidra reference; not compilable reconstruction. Address: 0045B8F4 */

/* Library Function - Single Match
    ___init_monetary
   
   Library: Visual Studio 2003 Release */

int __cdecl ___init_monetary(threadlocinfo *_LocInfo)

{
  char *pcVar1;
  char cVar2;
  int *_Memory;
  undefined4 *_Memory_00;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  char *pcVar17;
  int iVar18;
  _locale_t plVar19;
  char *pcVar20;
  undefined **ppuVar21;
  int *piVar22;
  
  if ((DAT_00477658 == 0) && (DAT_0047765c == 0)) {
    DAT_004981c8 = (undefined4 *)0x0;
    DAT_004981cc = (undefined4 *)0x0;
    PTR_PTR_00473ad4 = (undefined *)&PTR_DAT_00473aa4;
    DAT_00477624 = (int *)0x0;
LAB_0045bb2c:
    iVar18 = 0;
  }
  else {
    _Memory = FUN_0045794d(1,0x30);
    if (_Memory != (int *)0x0) {
      _Memory_00 = _malloc(4);
      if (_Memory_00 == (undefined4 *)0x0) {
        _free(_Memory);
      }
      else {
        *_Memory_00 = 0;
        if (DAT_00477658 == 0) {
          ppuVar21 = &PTR_DAT_00473aa4;
          piVar22 = _Memory;
          for (iVar18 = 0xc; iVar18 != 0; iVar18 = iVar18 + -1) {
            *piVar22 = (int)*ppuVar21;
            ppuVar21 = ppuVar21 + 1;
            piVar22 = piVar22 + 1;
          }
          DAT_004981c8 = (undefined4 *)0x0;
LAB_0045baf9:
          *_Memory = *(int *)PTR_PTR_00473ad4;
          _Memory[1] = *(int *)(PTR_PTR_00473ad4 + 4);
          _Memory[2] = *(int *)(PTR_PTR_00473ad4 + 8);
          PTR_PTR_00473ad4 = (undefined *)_Memory;
          DAT_00477624 = _Memory;
          DAT_004981cc = _Memory_00;
          goto LAB_0045bb2c;
        }
        DAT_004981c8 = _malloc(4);
        if (DAT_004981c8 == (undefined4 *)0x0) {
          _free(_Memory);
          _free(_Memory_00);
        }
        else {
          *DAT_004981c8 = 0;
          plVar19 = (_locale_t)(uint)DAT_00477680;
          iVar18 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000015,(char *)(_Memory + 3));
          iVar3 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000014,(char *)(_Memory + 4));
          iVar4 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000016,(char *)(_Memory + 5));
          iVar5 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000017,(char *)(_Memory + 6));
          iVar6 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000018,(char *)(_Memory + 7));
          iVar7 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000050,(char *)(_Memory + 8));
          iVar8 = FUN_0046041e(1,plVar19,(LPCWSTR)&DAT_00000051,(char *)(_Memory + 9));
          iVar9 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_0000001a,(char *)(_Memory + 10));
          iVar10 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000019,(char *)((int)_Memory + 0x29));
          iVar11 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000054,(char *)((int)_Memory + 0x2a));
          iVar12 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000055,(char *)((int)_Memory + 0x2b));
          iVar13 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000056,(char *)(_Memory + 0xb));
          iVar14 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000057,(char *)((int)_Memory + 0x2d));
          iVar15 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000052,(char *)((int)_Memory + 0x2e));
          iVar16 = FUN_0046041e(0,plVar19,(LPCWSTR)&DAT_00000053,(char *)((int)_Memory + 0x2f));
          if (iVar16 == 0 &&
              (((((((((((((iVar18 == 0 && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) && iVar6 == 0)
                      && iVar7 == 0) && iVar8 == 0) && iVar9 == 0) && iVar10 == 0) && iVar11 == 0)
                 && iVar12 == 0) && iVar13 == 0) && iVar14 == 0) && iVar15 == 0)) {
            pcVar17 = (char *)_Memory[7];
            while (*pcVar17 != '\0') {
              cVar2 = *pcVar17;
              if ((cVar2 < '0') || ('9' < cVar2)) {
                pcVar20 = pcVar17;
                if (cVar2 != ';') goto LAB_0045bac7;
                do {
                  pcVar1 = pcVar20 + 1;
                  *pcVar20 = *pcVar1;
                  pcVar20 = pcVar1;
                } while (*pcVar1 != '\0');
              }
              else {
                *pcVar17 = cVar2 + -0x30;
LAB_0045bac7:
                pcVar17 = pcVar17 + 1;
              }
            }
            goto LAB_0045baf9;
          }
          ___free_lconv_mon((int)_Memory);
          _free(_Memory);
          _free(_Memory_00);
        }
      }
    }
    iVar18 = 1;
  }
  return iVar18;
}

