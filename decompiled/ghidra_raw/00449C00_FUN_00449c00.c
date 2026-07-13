/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00449C00
 * Tracking name: FUN_00449c00
 * Ghidra name: FUN_00449c00
 * Tracked span: 320 bytes
 */


int FUN_00449c00(int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int local_8;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
  DAT_0049231c = DAT_0049231c + '\x01';
switchD_00449c8f_caseD_6:
  local_8 = 0;
  puVar3 = *(undefined4 **)(param_1 + 0x18);
LAB_00449c40:
  do {
    do {
      if (puVar3 == (undefined4 *)0x0) {
LAB_00449cf0:
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
        DAT_0049231c = DAT_0049231c + -1;
        return local_8;
      }
      puVar1 = (undefined4 *)puVar3[1];
      pvVar2 = (void *)*puVar3;
      puVar3 = puVar1;
    } while (*(int *)((int)pvVar2 + 8) == 0);
    if ((*(byte *)((int)pvVar2 + 4) & 2) != 0) {
LAB_00449c60:
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + -1;
      uVar4 = (**(code **)((int)pvVar2 + 8))();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
      DAT_0049231c = DAT_0049231c + '\x01';
      switch(uVar4) {
      case 0:
        FUN_00449f60(pvVar2,param_1);
        local_8 = local_8 + 1;
        goto LAB_00449c40;
      default:
        break;
      case 2:
        goto switchD_00449c8f_caseD_2;
      case 3:
        local_8 = 1;
        goto LAB_00449cf0;
      case 4:
        local_8 = 0;
        goto LAB_00449cf0;
      case 5:
        local_8 = -1;
        goto LAB_00449cf0;
      case 6:
        goto switchD_00449c8f_caseD_6;
      case 7:
        if (*(code **)((int)pvVar2 + 0x10) != (code *)0x0) {
          (**(code **)((int)pvVar2 + 0x10))();
        }
      }
    }
    local_8 = local_8 + 1;
  } while( true );
switchD_00449c8f_caseD_2:
  if ((*(byte *)((int)pvVar2 + 4) & 2) == 0) goto code_r0x00449c9c;
  goto LAB_00449c60;
code_r0x00449c9c:
  local_8 = local_8 + 1;
  goto LAB_00449c40;
}

