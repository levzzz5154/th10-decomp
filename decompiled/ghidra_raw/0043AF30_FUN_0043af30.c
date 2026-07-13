/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043AF30
 * Tracking name: FUN_0043af30
 * Ghidra name: FUN_0043af30
 * Tracked span: 480 bytes
 */


/* WARNING: Removing unreachable block (ram,0x0043b043) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0043af30(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  ulonglong uVar3;
  bool bVar4;
  int iVar5;
  longlong lVar6;
  ulonglong uVar7;
  int local_c;
  
  iVar5 = 0;
  bVar4 = false;
  lVar6 = __allmul(*(uint *)(param_1 + 0x120),(int)*(uint *)(param_1 + 0x120) >> 0x1f,
                   *(uint *)(param_1 + 0x128),*(int *)(param_1 + 300));
  lVar6 = __allmul((uint)lVar6,(int)((ulonglong)lVar6 >> 0x20),1000,0);
  lVar6 = __aulldiv((uint)lVar6,(uint)((ulonglong)lVar6 >> 0x20),*(uint *)(param_1 + 0x124),
                    (int)*(uint *)(param_1 + 0x124) >> 0x1f);
  uVar3 = lVar6 + *(longlong *)(param_1 + 0x130);
  if (*(int *)(param_1 + 0x2e0) != 0) {
    if (*(int *)(param_1 + 0x2e4) <= *(int *)(param_1 + 0x2e8)) {
      *(undefined4 *)(param_1 + 0x2c8) = 0;
      return;
    }
    *(float *)(param_1 + 0x2c8) =
         _DAT_00470afc - (float)*(int *)(param_1 + 0x2e8) / (float)*(int *)(param_1 + 0x2e4);
    uVar7 = FUN_00463b2c();
    if ((int)uVar7 != *(int *)(param_1 + 0x2cc)) {
      FUN_0043b7a0(0);
    }
    uVar7 = FUN_00463b2c();
    *(int *)(param_1 + 0x2cc) = (int)uVar7;
    *(int *)(param_1 + 0x2e8) = *(int *)(param_1 + 0x2e8) + 1;
  }
  local_c = 0;
  if (0 < *(int *)(param_1 + 0x118)) {
    do {
      if (*(int *)(*(int *)(param_1 + 0x138) + iVar5) != 0) {
        bVar4 = true;
        uVar7 = uVar3;
        do {
          uVar3 = uVar7;
          puVar1 = (undefined4 *)(*(int *)(param_1 + 0x138) + iVar5);
          if (uVar3 < (ulonglong)(longlong)(int)puVar1[1]) break;
          FUN_0043b110(param_1,puVar1);
          lVar6 = __allmul(*(uint *)(param_1 + 0x120),(int)*(uint *)(param_1 + 0x120) >> 0x1f,
                           *(uint *)(param_1 + 0x128),*(int *)(param_1 + 300));
          lVar6 = __allmul((uint)lVar6,(int)((ulonglong)lVar6 >> 0x20),1000,0);
          lVar6 = __aulldiv((uint)lVar6,(uint)((ulonglong)lVar6 >> 0x20),*(uint *)(param_1 + 0x124),
                            (int)*(uint *)(param_1 + 0x124) >> 0x1f);
          uVar3 = lVar6 + *(longlong *)(param_1 + 0x130);
          uVar7 = lVar6 + *(longlong *)(param_1 + 0x130);
        } while (*(int *)(*(int *)(param_1 + 0x138) + iVar5) != 0);
      }
      local_c = local_c + 1;
      iVar5 = iVar5 + 0x20;
    } while (local_c < *(int *)(param_1 + 0x118));
  }
  uVar2 = *(uint *)(param_1 + 0x128);
  *(uint *)(param_1 + 0x128) = uVar2 + 1;
  *(uint *)(param_1 + 300) = *(int *)(param_1 + 300) + (uint)(0xfffffffe < uVar2);
  if (!bVar4) {
    FUN_0043ace0();
  }
  return;
}

