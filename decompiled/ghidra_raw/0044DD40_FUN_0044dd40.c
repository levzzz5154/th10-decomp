/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044DD40
 * Tracking name: FUN_0044dd40
 * Ghidra name: FUN_0044dd40
 * Tracked span: 208 bytes
 */


undefined4 FUN_0044dd40(void)

{
  int iVar1;
  HANDLE hFile;
  char in_AL;
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 0x7c) == 0) {
    hFile = *(HANDLE *)(unaff_ESI + 0x8c);
    if (hFile == (HANDLE)0x0) {
      return 0x800401f0;
    }
    if (in_AL != '\0') {
      iVar1 = *(int *)(*(int *)(unaff_ESI + 0x90) + 0x18);
      if (0 < iVar1) {
        SetFilePointer(hFile,*(int *)(*(int *)(unaff_ESI + 0x90) + 0x10) + iVar1 + DAT_004977a4,
                       (PLONG)0x0,0);
        *(int *)(unaff_ESI + 8) =
             *(int *)(*(int *)(unaff_ESI + 0x90) + 0x1c) -
             *(int *)(*(int *)(unaff_ESI + 0x90) + 0x18);
        return 0;
      }
    }
    SetFilePointer(hFile,*(int *)(*(int *)(unaff_ESI + 0x90) + 0x10) + DAT_004977a4,(PLONG)0x0,0);
    *(undefined4 *)(unaff_ESI + 8) = *(undefined4 *)(*(int *)(unaff_ESI + 0x90) + 0x1c);
  }
  else {
    *(int *)(unaff_ESI + 0x84) = *(int *)(unaff_ESI + 0x80);
    iVar1 = *(int *)(*(int *)(unaff_ESI + 0x90) + 0x1c);
    if (0 < iVar1) {
      *(int *)(unaff_ESI + 0x88) = iVar1;
    }
    if ((in_AL != '\0') && (iVar1 = *(int *)(*(int *)(unaff_ESI + 0x90) + 0x18), 0 < iVar1)) {
      *(int *)(unaff_ESI + 0x84) = iVar1 + *(int *)(unaff_ESI + 0x80);
      return 0;
    }
  }
  return 0;
}

