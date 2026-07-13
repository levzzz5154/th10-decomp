/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00449D40
 * Tracking name: FUN_00449d40
 * Ghidra name: FUN_00449d40
 * Tracked span: 272 bytes
 */


int FUN_00449d40(int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int local_8;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
  DAT_0049231c = DAT_0049231c + '\x01';
  local_8 = 0;
  puVar3 = *(undefined4 **)(param_1 + 0x3c);
  do {
    do {
      if (puVar3 == (undefined4 *)0x0) {
LAB_00449e12:
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
        DAT_0049231c = DAT_0049231c + -1;
        return local_8;
      }
      puVar1 = (undefined4 *)puVar3[1];
      pvVar2 = (void *)*puVar3;
      puVar3 = puVar1;
    } while (*(int *)((int)pvVar2 + 8) == 0);
    if ((*(byte *)((int)pvVar2 + 4) & 2) != 0) {
LAB_00449d96:
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + -1;
      uVar4 = (**(code **)((int)pvVar2 + 8))();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + '\x01';
      switch(uVar4) {
      case 0:
        FUN_00449f60(pvVar2,param_1);
      default:
        break;
      case 2:
        goto switchD_00449dc5_caseD_2;
      case 3:
        local_8 = 1;
        goto LAB_00449e12;
      case 4:
        local_8 = 0;
        goto LAB_00449e12;
      case 5:
        local_8 = -1;
        goto LAB_00449e12;
      }
    }
switchD_00449dc5_caseD_1:
    local_8 = local_8 + 1;
  } while( true );
switchD_00449dc5_caseD_2:
  if ((*(byte *)((int)pvVar2 + 4) & 2) == 0) goto switchD_00449dc5_caseD_1;
  goto LAB_00449d96;
}

