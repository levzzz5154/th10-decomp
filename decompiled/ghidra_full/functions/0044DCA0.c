/* Raw Ghidra reference; not compilable reconstruction. Address: 0044DCA0 */

undefined4 __fastcall SelectStreamRecord(int param_1)

{
  HANDLE hFile;
  int unaff_ESI;
  
  if ((*(int *)(unaff_ESI + 0x7c) == 0) &&
     (hFile = *(HANDLE *)(unaff_ESI + 0x8c), hFile != (HANDLE)0xffffffff)) {
    *(int *)(unaff_ESI + 0x90) = param_1;
    if (hFile != (HANDLE)0x0) {
      SetFilePointer(hFile,*(int *)(param_1 + 0x10) + DAT_004977a4,(PLONG)0x0,0);
      *(undefined4 *)(unaff_ESI + 8) = *(undefined4 *)(*(int *)(unaff_ESI + 0x90) + 0x1c);
    }
    *(undefined4 *)(unaff_ESI + 0x2c) = *(undefined4 *)(unaff_ESI + 8);
    return 0;
  }
  return 0x80004005;
}

