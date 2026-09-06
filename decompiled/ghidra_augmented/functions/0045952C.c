/* Raw Ghidra reference; not compilable reconstruction. Address: 0045952C */

/* Library Function - Single Match
    __ioinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __ioinit(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  DWORD DVar6;
  HANDLE hFile;
  int iVar7;
  uint uVar8;
  UINT *pUVar9;
  UINT UVar10;
  UINT UVar11;
  byte *local_48;
  _STARTUPINFOA local_44;
  
  puVar3 = _malloc(0x480);
  if (puVar3 == (undefined4 *)0x0) {
    iVar4 = -1;
  }
  else {
    DAT_004991e4 = 0x20;
    DAT_00499200 = puVar3;
    for (; puVar3 < DAT_00499200 + 0x120; puVar3 = puVar3 + 9) {
      *puVar3 = 0xffffffff;
      puVar3[2] = 0;
      *(undefined1 *)(puVar3 + 1) = 0;
      *(undefined1 *)((int)puVar3 + 5) = 10;
    }
    GetStartupInfoA(&local_44);
    if ((local_44.cbReserved2 != 0) && ((UINT *)local_44.lpReserved2 != (UINT *)0x0)) {
      UVar10 = *(UINT *)local_44.lpReserved2;
      pUVar9 = (UINT *)((int)local_44.lpReserved2 + 4);
      local_48 = (byte *)(UVar10 + (int)pUVar9);
      if (0x7ff < (int)UVar10) {
        UVar10 = 0x800;
      }
      UVar11 = UVar10;
      if ((int)DAT_004991e4 < (int)UVar10) {
        puVar3 = &DAT_00499204;
        do {
          puVar5 = _malloc(0x480);
          UVar11 = DAT_004991e4;
          if (puVar5 == (undefined4 *)0x0) break;
          DAT_004991e4 = DAT_004991e4 + 0x20;
          *puVar3 = puVar5;
          puVar2 = puVar5;
          for (; puVar5 < puVar2 + 0x120; puVar5 = puVar5 + 9) {
            *puVar5 = 0xffffffff;
            puVar5[2] = 0;
            *(undefined1 *)(puVar5 + 1) = 0;
            *(undefined1 *)((int)puVar5 + 5) = 10;
            puVar2 = (undefined4 *)*puVar3;
          }
          puVar3 = puVar3 + 1;
          UVar11 = UVar10;
        } while ((int)DAT_004991e4 < (int)UVar10);
      }
      uVar8 = 0;
      if (0 < (int)UVar11) {
        do {
          if (((*(HANDLE *)local_48 != (HANDLE)0xffffffff) && ((*pUVar9 & 1) != 0)) &&
             (((*pUVar9 & 8) != 0 || (DVar6 = GetFileType(*(HANDLE *)local_48), DVar6 != 0)))) {
            puVar3 = (undefined4 *)((int)(&DAT_00499200)[(int)uVar8 >> 5] + (uVar8 & 0x1f) * 0x24);
            *puVar3 = *(undefined4 *)local_48;
            *(byte *)(puVar3 + 1) = (byte)*pUVar9;
            iVar4 = ___crtInitCritSecAndSpinCount(puVar3 + 3,4000);
            if (iVar4 == 0) {
              return -1;
            }
            puVar3[2] = puVar3[2] + 1;
          }
          local_48 = local_48 + 4;
          uVar8 = uVar8 + 1;
          pUVar9 = (UINT *)((int)pUVar9 + 1);
        } while ((int)uVar8 < (int)UVar11);
      }
    }
    iVar4 = 0;
    do {
      piVar1 = DAT_00499200 + iVar4 * 9;
      if (*piVar1 == -1) {
        *(undefined1 *)(piVar1 + 1) = 0x81;
        if (iVar4 == 0) {
          DVar6 = 0xfffffff6;
        }
        else {
          DVar6 = 0xfffffff5 - (iVar4 != 1);
        }
        hFile = GetStdHandle(DVar6);
        if ((hFile == (HANDLE)0xffffffff) || (DVar6 = GetFileType(hFile), DVar6 == 0)) {
          *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x40;
        }
        else {
          *piVar1 = (int)hFile;
          if ((DVar6 & 0xff) == 2) {
            *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x40;
          }
          else if ((DVar6 & 0xff) == 3) {
            *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 8;
          }
          iVar7 = ___crtInitCritSecAndSpinCount(piVar1 + 3,4000);
          if (iVar7 == 0) {
            return -1;
          }
          piVar1[2] = piVar1[2] + 1;
        }
      }
      else {
        *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x80;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 3);
    SetHandleCount(DAT_004991e4);
    iVar4 = 0;
  }
  return iVar4;
}

