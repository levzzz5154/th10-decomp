/* Raw Ghidra reference; not compilable reconstruction. Address: 004354D0 */

bool __thiscall FUN_004354d0(void *this,LPCVOID param_1,DWORD param_2)

{
  DWORD local_4;
  
  local_4 = 0;
  if (*(int *)((int)this + 8) != 0x40000000) {
    return false;
  }
  WriteFile(*(HANDLE *)((int)this + 4),param_1,param_2,&local_4,(LPOVERLAPPED)0x0);
  return param_2 == local_4;
}

