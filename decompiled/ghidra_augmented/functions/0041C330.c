/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C330 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041c330(void)

{
  int *piVar1;
  float *pfVar2;
  float fVar3;
  int *_Memory;
  byte bVar4;
  int iVar5;
  int unaff_EDI;
  ulonglong uVar6;
  
  _Memory = *(int **)(unaff_EDI + 0x18);
  do {
    while( true ) {
      if (_Memory == (int *)0x0) {
        return 1;
      }
      piVar1 = (int *)_Memory[2];
      if (((char)_Memory[0x14] == '\0') ||
         (bVar4 = (char)_Memory[0x14] + 1, *(byte *)(_Memory + 0x14) = bVar4, bVar4 < 2)) break;
      iVar5 = *_Memory;
LAB_0041c363:
      (**(code **)(iVar5 + 0x10))();
      *(int *)(unaff_EDI + 0x438) = *(int *)(unaff_EDI + 0x438) + -1;
      *(int *)(_Memory[1] + 8) = _Memory[2];
      if (_Memory[2] != 0) {
        *(int *)(_Memory[2] + 4) = _Memory[1];
      }
      if (*(int **)(unaff_EDI + 0x434) == _Memory) {
        *(int *)(unaff_EDI + 0x434) = _Memory[1];
      }
      _free(_Memory);
      _Memory = piVar1;
    }
    iVar5 = *_Memory;
    if (_Memory[3] == 1) goto LAB_0041c363;
    iVar5 = (**(code **)(iVar5 + 8))();
    if (iVar5 == 0) {
      pfVar2 = (float *)_Memory[7];
      _Memory[4] = _Memory[5];
      if ((*pfVar2 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar2)) {
        _Memory[6] = (int)(*pfVar2 + (float)_Memory[6]);
        uVar6 = FUN_00463b2c();
        _Memory[5] = (int)uVar6;
        _Memory = piVar1;
      }
      else {
        fVar3 = (float)_Memory[6] + _DAT_00470afc;
        _Memory[5] = _Memory[5] + 1;
        _Memory[6] = (int)fVar3;
        _Memory = piVar1;
      }
    }
    else {
      (**(code **)(*_Memory + 0x10))();
      *(int *)(unaff_EDI + 0x438) = *(int *)(unaff_EDI + 0x438) + -1;
      *(int *)(_Memory[1] + 8) = _Memory[2];
      if (_Memory[2] != 0) {
        *(int *)(_Memory[2] + 4) = _Memory[1];
      }
      if (*(int **)(unaff_EDI + 0x434) == _Memory) {
        *(int *)(unaff_EDI + 0x434) = _Memory[1];
      }
      _free(_Memory);
      _Memory = piVar1;
    }
  } while( true );
}

