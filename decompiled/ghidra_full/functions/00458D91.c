/* Raw Ghidra reference; not compilable reconstruction. Address: 00458D91 */

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* Library Function - Single Match
    __resetstkoflw
   
   Library: Visual Studio 2003 Release */

int __cdecl __resetstkoflw(void)

{
  SIZE_T SVar1;
  BOOL BVar2;
  LPCVOID pvVar3;
  LPCVOID pvVar4;
  undefined4 uStack_60;
  _SYSTEM_INFO local_50;
  _MEMORY_BASIC_INFORMATION local_2c;
  DWORD local_10;
  SIZE_T local_c;
  LPCVOID local_8;
  
  uStack_60 = 0x458da2;
  SVar1 = VirtualQuery(&uStack_60,&local_2c,0x1c);
  if (SVar1 != 0) {
    GetSystemInfo(&local_50);
    pvVar4 = (LPCVOID)((~(local_50.dwPageSize - 1) & (uint)&uStack_60) - local_50.dwPageSize);
    pvVar3 = (LPCVOID)(((-(uint)(DAT_00477470 != 1) & 0xfffffff1) + 0x11) * local_50.dwPageSize +
                      (int)local_2c.AllocationBase);
    local_c = local_50.dwPageSize;
    if (pvVar3 <= pvVar4) {
      local_8 = pvVar4;
      if (DAT_00477470 != 1) {
        local_8 = local_2c.AllocationBase;
        do {
          SVar1 = VirtualQuery(local_8,&local_2c,0x1c);
          if (SVar1 == 0) {
            return 0;
          }
          local_8 = (LPCVOID)((int)local_8 + local_2c.RegionSize);
        } while ((local_2c.State & 0x1000) == 0);
        local_8 = local_2c.BaseAddress;
        if ((local_2c.Protect._1_1_ & 1) != 0) {
          return 1;
        }
        if (pvVar4 < local_2c.BaseAddress) {
          return 0;
        }
        if (local_2c.BaseAddress < pvVar3) {
          local_8 = pvVar3;
        }
        VirtualAlloc(local_8,local_c,0x1000,4);
      }
      BVar2 = VirtualProtect(local_8,local_c,(-(uint)(DAT_00477470 != 1) & 0x103) + 1,&local_10);
      return BVar2;
    }
  }
  return 0;
}

