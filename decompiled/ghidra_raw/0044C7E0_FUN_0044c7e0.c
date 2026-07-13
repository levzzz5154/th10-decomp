/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044C7E0
 * Tracking name: FUN_0044c7e0
 * Ghidra name: FUN_0044c7e0
 * Tracked span: 272 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int __thiscall FUN_0044c7e0(ushort param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  short unaff_BX;
  undefined4 uStack_4c;
  undefined4 local_40;
  undefined2 uStack_3c;
  int local_28 [10];
  
  local_28[9] = DAT_00473660 ^ (uint)&local_40;
  piVar1 = (int *)*param_2;
  local_40 = 0;
  if (piVar1 == (int *)0x0) {
    return -0x7ffbfe10;
  }
  local_28[3] = 0;
  local_28[5] = 0;
  local_28[6] = 0;
  local_28[7] = 0;
  local_28[8] = 0;
  local_28[2] = 0;
  local_28[4] = 0;
  uStack_4c = &local_40;
  local_28[0] = 0x24;
  local_28[1] = 1;
  iVar2 = (**(code **)(*piVar1 + 0xc))(piVar1);
  if (-1 < iVar2) {
    uStack_3c = 0;
    uStack_4c = (undefined4 *)CONCAT22(unaff_BX,1);
    local_40 = CONCAT22(param_1,(param_1 >> 3) * unaff_BX);
    iVar2 = (**(code **)(local_28[0] + 0x38))(local_28,&uStack_4c);
    if (-1 < iVar2) {
      if (local_28 != (int *)0x0) {
        (**(code **)(local_28[0] + 8))(local_28);
      }
      iVar2 = 0;
    }
  }
  return iVar2;
}

