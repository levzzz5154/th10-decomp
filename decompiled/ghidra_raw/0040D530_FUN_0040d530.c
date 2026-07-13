/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040D530
 * Tracking name: FUN_0040d530
 * Ghidra name: FUN_0040d530
 * Tracked span: 336 bytes
 */


void __fastcall FUN_0040d530(void *param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  int local_4;
  
  FUN_00409f90(param_1,in_EAX);
  iVar4 = DAT_00491be4;
  pvVar2 = *(void **)(in_EAX + 8);
  if (pvVar2 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar4 = DAT_00491be4;
  pvVar2 = *(void **)(in_EAX + 0xc);
  if (pvVar2 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar4 = 0xc;
  do {
    pvVar2 = *(void **)(iVar4 + *(int *)(in_EAX + 0x54));
    if (pvVar2 != (void *)0x0) {
      _free(pvVar2);
    }
    iVar4 = iVar4 + 4;
  } while (iVar4 < 0x8c);
  pvVar2 = *(void **)(in_EAX + 0x54);
  if (pvVar2 != (void *)0x0) {
    FUN_0040d680();
    _free(pvVar2);
  }
  *(undefined4 *)(in_EAX + 0x54) = 0;
  if (((byte)DAT_00474ca0 & 9) == 0) {
    uVar3 = 9;
    iVar4 = 0x3ad090;
    local_4 = 4;
    do {
      if ((-1 < (int)uVar3) && (uVar3 < 0x21)) {
        puVar1 = (undefined4 *)(iVar4 + (int)g_pGameStateManager);
        if (*(int *)(iVar4 + (int)g_pGameStateManager) != 0) {
          FUN_00447810(g_pGameStateManager);
          _free((void *)*puVar1);
          *puVar1 = 0;
        }
      }
      iVar4 = iVar4 + 4;
      uVar3 = uVar3 + 1;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
    DAT_00477704 = 0;
    return;
  }
  DAT_00477704 = 0;
  return;
}

