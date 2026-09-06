/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B740 */

undefined4 __fastcall WriteSharedFile(DWORD param_1,LPCVOID param_2)

{
  DWORD unaff_ESI;
  DWORD local_4;
  
  if (DAT_00474c38 == (HANDLE)0xffffffff) {
    return 0xffffffff;
  }
  local_4 = param_1;
  WriteFile(DAT_00474c38,param_2,unaff_ESI,&local_4,(LPOVERLAPPED)0x0);
  if (unaff_ESI != local_4) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
    return 0xfffffffe;
  }
  return 0;
}

