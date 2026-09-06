/* Raw Ghidra reference; not compilable reconstruction. Address: 0042B1E0 */

undefined4 FUN_0042b1e0(void)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  undefined4 *puVar5;
  DWORD nNumberOfBytesToWrite;
  uint uVar6;
  undefined4 *_Memory;
  uint *puVar7;
  byte *pbVar8;
  uint uVar9;
  int iVar10;
  uint *puVar11;
  int iVar12;
  int *unaff_EBX;
  int iVar13;
  int *piVar14;
  uint *puVar15;
  int *piVar16;
  int local_8;
  DWORD local_4;
  
  if (*unaff_EBX == 0) {
    return 0xffffffff;
  }
  _Memory = _malloc(0x200000);
  puVar5 = (undefined4 *)*unaff_EBX;
  *_Memory = *puVar5;
  _Memory[1] = puVar5[1];
  _Memory[2] = puVar5[2];
  _Memory[3] = puVar5[3];
  _Memory[4] = puVar5[4];
  _Memory[5] = puVar5[5];
  iVar13 = 0x18;
  local_8 = 0x18;
  local_4 = 0;
  puVar11 = (uint *)(unaff_EBX + 5);
  do {
    if ((short)puVar11[-3] == 0x5243) {
      *puVar11 = local_4;
      uVar9 = 0;
      iVar13 = 0xb3e;
      puVar7 = puVar11;
      do {
        pbVar8 = (byte *)((int)puVar7 + -3);
        puVar15 = puVar7 + -1;
        pbVar1 = (byte *)((int)puVar7 + -2);
        pbVar2 = (byte *)((int)puVar7 + -1);
        pbVar3 = (byte *)((int)puVar7 + 1);
        uVar6 = *puVar7;
        puVar7 = (uint *)((int)puVar7 + 6);
        iVar13 = iVar13 + -1;
        uVar9 = (uint)(byte)*puVar15 + (uint)*pbVar8 + (uint)*pbVar1 + (uint)*pbVar2 + (uint)*pbVar3
                + (byte)uVar6 + uVar9;
      } while (iVar13 != 0);
      puVar11[-2] = uVar9;
      iVar13 = local_8 + 0x437c;
      puVar7 = puVar11 + -3;
      puVar15 = (uint *)((int)_Memory + local_8);
      for (iVar10 = 0x10df; local_8 = iVar13, iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar15 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar15 = puVar15 + 1;
      }
    }
    local_4 = local_4 + 1;
    puVar11 = puVar11 + 0x10df;
  } while (local_4 < 7);
  iVar10 = 0;
  pbVar8 = (byte *)((int)unaff_EBX + 0x1d876);
  iVar12 = 0x110;
  do {
    pbVar1 = pbVar8 + -1;
    pbVar2 = pbVar8 + -2;
    pbVar3 = pbVar8 + 1;
    bVar4 = *pbVar8;
    pbVar8 = pbVar8 + 4;
    iVar12 = iVar12 + -1;
    iVar10 = (uint)bVar4 + iVar10 + (uint)*pbVar2 + (uint)*pbVar1 + (uint)*pbVar3;
  } while (iVar12 != 0);
  unaff_EBX[0x761c] = iVar10;
  piVar14 = unaff_EBX + 0x761b;
  piVar16 = (int *)((int)_Memory + iVar13);
  for (iVar10 = 0x112; iVar10 != 0; iVar10 = iVar10 + -1) {
    *piVar16 = *piVar14;
    piVar14 = piVar14 + 1;
    piVar16 = piVar16 + 1;
  }
  *(int *)(*unaff_EBX + 0x14) = iVar13 + 0x430;
  pbVar8 = (byte *)FUN_004359b0((byte *)(_Memory + 6),*(int *)(*unaff_EBX + 0x14),
                                (int *)(*unaff_EBX + 0x10));
  *(int *)(*unaff_EBX + 4) = *(int *)(*unaff_EBX + 0x10) + 0x18;
  EncryptDatBuffer(pbVar8,*(uint *)(*unaff_EBX + 0x10),'5',0x10,*(uint *)(*unaff_EBX + 0x10));
  iVar13 = OpenSharedFileWrite("scoreth10.dat");
  if (iVar13 == 0) {
    if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
       (WriteFile(DAT_00474c38,(LPCVOID)*unaff_EBX,0x18,&local_4,(LPOVERLAPPED)0x0), local_4 != 0x18
       )) {
      CloseHandle(DAT_00474c38);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
      DAT_0049231e = DAT_0049231e + -1;
    }
    nNumberOfBytesToWrite = *(DWORD *)(*unaff_EBX + 0x10);
    if (DAT_00474c38 != (HANDLE)0xffffffff) {
      WriteFile(DAT_00474c38,pbVar8,nNumberOfBytesToWrite,&local_4,(LPOVERLAPPED)0x0);
      if (nNumberOfBytesToWrite != local_4) {
        CloseHandle(DAT_00474c38);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
        DAT_0049231e = DAT_0049231e + -1;
      }
      if (DAT_00474c38 != (HANDLE)0xffffffff) {
        CloseHandle(DAT_00474c38);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
        DAT_0049231e = DAT_0049231e + -1;
      }
    }
    if (pbVar8 != (byte *)0x0) {
      _free(pbVar8);
    }
    _free(_Memory);
    return 0;
  }
  return 0xffffffff;
}

