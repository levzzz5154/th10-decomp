/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043D7D0
 * Tracking name: FUN_0043d7d0
 * Ghidra name: FUN_0043d7d0
 * Tracked span: 384 bytes
 */


undefined4 FUN_0043d7d0(int param_1)

{
  byte bVar1;
  byte *in_EAX;
  byte *pbVar2;
  int iVar3;
  HANDLE hFile;
  void *pvVar4;
  int unaff_ESI;
  byte *pbVar5;
  bool bVar6;
  DWORD local_4;
  
  if (*(int *)(unaff_ESI + 0x1ec0 + param_1 * 4) != 0) {
    pbVar5 = (byte *)(param_1 * 0x100 + 0x4108 + unaff_ESI);
    pbVar2 = in_EAX;
    do {
      bVar1 = *pbVar2;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_0043d817:
        iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_0043d81c;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_0043d817;
      pbVar2 = pbVar2 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_0043d81c:
    if (iVar3 == 0) {
      return 0;
    }
  }
  pbVar5 = in_EAX;
  do {
    bVar1 = *pbVar5;
    pbVar5[(int)(&DAT_00496698 + (param_1 * 0x100 - (int)in_EAX))] = bVar1;
    pbVar5 = pbVar5 + 1;
  } while (bVar1 != 0);
  if ((((byte)DAT_00491d78 & 0x10) != 0) && (*(int *)(unaff_ESI + 0x610) != 0)) {
    pvVar4 = *(void **)(unaff_ESI + 0x1ec0 + param_1 * 4);
    if (pvVar4 != (void *)0x0) {
      _free(pvVar4);
      *(undefined4 *)(unaff_ESI + 0x1ec0 + param_1 * 4) = 0;
    }
    hFile = CreateFileA((LPCSTR)(unaff_ESI + 0x5108),0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,
                        0x8000080,(HANDLE)0x0);
    if (hFile != (HANDLE)0xffffffff) {
      iVar3 = FUN_0043d2a0(in_EAX,unaff_ESI);
      iVar3 = iVar3 * 0x34;
      SetFilePointer(hFile,*(LONG *)(*(int *)(unaff_ESI + 0x1f84) + 0x10 + iVar3),(PLONG)0x0,0);
      pvVar4 = _malloc(*(size_t *)(*(int *)(unaff_ESI + 0x1f84) + 0x14 + iVar3));
      if (pvVar4 != (void *)0x0) {
        ReadFile(hFile,pvVar4,*(DWORD *)(*(int *)(unaff_ESI + 0x1f84) + 0x14 + iVar3),&local_4,
                 (LPOVERLAPPED)0x0);
        CloseHandle(hFile);
        iVar3 = *(int *)(unaff_ESI + 0x1f84) + iVar3;
        *(int *)(unaff_ESI + 0x1e80 + param_1 * 4) = iVar3;
        *(void **)(unaff_ESI + 0x1ec0 + param_1 * 4) = pvVar4;
        *(void **)(unaff_ESI + 0x1f00 + param_1 * 4) = pvVar4;
        *(undefined4 *)(unaff_ESI + 8000 + param_1 * 4) = *(undefined4 *)(iVar3 + 0x14);
        return 0;
      }
      CloseHandle(hFile);
    }
    return 0xffffffff;
  }
  return 0;
}

