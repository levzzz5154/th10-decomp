/* Raw Ghidra reference; not compilable reconstruction. Address: 0043CC40 */

undefined4 FUN_0043cc40(void)

{
  DWORD DVar1;
  int unaff_ESI;
  
  if (*(HANDLE *)(unaff_ESI + 0x5218) != (HANDLE)0x0) {
    if (*(int *)(unaff_ESI + 0x5224) == 0) {
      *(undefined4 *)(unaff_ESI + 0x5224) = 1;
    }
    DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 0x5218),100);
    while (DVar1 == 0x102) {
      Sleep(1);
      DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 0x5218),100);
    }
    DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 0x521c),100);
    while (DVar1 == 0x102) {
      Sleep(1);
      DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 0x521c),100);
    }
    CloseHandle(*(HANDLE *)(unaff_ESI + 0x5218));
    CloseHandle(*(HANDLE *)(unaff_ESI + 0x521c));
    *(undefined4 *)(unaff_ESI + 0x5218) = 0;
    *(undefined4 *)(unaff_ESI + 0x521c) = 0;
  }
  return 0;
}

