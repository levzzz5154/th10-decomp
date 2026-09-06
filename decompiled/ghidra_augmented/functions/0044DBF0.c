/* Raw Ghidra reference; not compilable reconstruction. Address: 0044DBF0 */

undefined4 __fastcall FUN_0044dbf0(LPCSTR param_1,int param_2)

{
  int in_EAX;
  HANDLE hFile;
  int unaff_ESI;
  
  *(int *)(unaff_ESI + 0x78) = in_EAX;
  *(undefined4 *)(unaff_ESI + 0x7c) = 0;
  if (in_EAX == 1) {
    if (param_1 == (LPCSTR)0x0) {
      return 0x80070057;
    }
    hFile = CreateFileA(param_1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000080,(HANDLE)0x0);
    *(HANDLE *)(unaff_ESI + 0x8c) = hFile;
    if (hFile == (HANDLE)0xffffffff) {
      return 0x80004005;
    }
    *(int *)(unaff_ESI + 0x90) = param_2;
    if (*(int *)(unaff_ESI + 0x7c) == 0) {
      if (hFile != (HANDLE)0x0) {
        SetFilePointer(hFile,*(int *)(param_2 + 0x10) + DAT_004977a4,(PLONG)0x0,0);
        *(undefined4 *)(unaff_ESI + 8) = *(undefined4 *)(*(int *)(unaff_ESI + 0x90) + 0x1c);
      }
    }
    else {
      *(undefined4 *)(unaff_ESI + 0x84) = *(undefined4 *)(unaff_ESI + 0x80);
      if (0 < *(int *)(param_2 + 0x1c)) {
        *(int *)(unaff_ESI + 0x88) = *(int *)(param_2 + 0x1c);
        *(undefined4 *)(unaff_ESI + 0x2c) = *(undefined4 *)(unaff_ESI + 8);
        return 0;
      }
    }
    *(undefined4 *)(unaff_ESI + 0x2c) = *(undefined4 *)(unaff_ESI + 8);
  }
  return 0;
}

