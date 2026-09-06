/* Raw Ghidra reference; not compilable reconstruction. Address: 0044C150 */

void FUN_0044c150(void)

{
  DWORD DVar1;
  int unaff_ESI;
  
  if (*(HANDLE *)(unaff_ESI + 4) != (HANDLE)0x0) {
    *(undefined4 *)(unaff_ESI + 0xc) = 1;
    *(undefined4 *)(unaff_ESI + 0x10) = 0;
    DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 4),200);
    while (DVar1 == 0x102) {
      *(undefined4 *)(unaff_ESI + 0xc) = 1;
      *(undefined4 *)(unaff_ESI + 0x10) = 0;
      Sleep(1);
      DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 4),200);
    }
    CloseHandle(*(HANDLE *)(unaff_ESI + 4));
    *(undefined4 *)(unaff_ESI + 4) = 0;
    *(undefined4 *)(unaff_ESI + 0x18) = 0;
  }
  return;
}

