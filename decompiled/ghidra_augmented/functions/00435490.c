/* Raw Ghidra reference; not compilable reconstruction. Address: 00435490 */

undefined4 __thiscall FUN_00435490(void *this,LPVOID param_1,DWORD param_2)

{
  DWORD local_4;
  
  local_4 = 0;
  if (*(int *)((int)this + 8) != -0x80000000) {
    return 0;
  }
  ReadFile(*(HANDLE *)((int)this + 4),param_1,param_2,&local_4,(LPOVERLAPPED)0x0);
  return local_4;
}

