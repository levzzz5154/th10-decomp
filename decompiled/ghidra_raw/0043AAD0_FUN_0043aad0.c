/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043AAD0
 * Tracking name: FUN_0043aad0
 * Ghidra name: FUN_0043aad0
 * Tracked span: 528 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_0043aad0(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 *puVar5;
  void *pvVar6;
  int iVar7;
  uint uVar8;
  int unaff_EBX;
  undefined1 *puVar9;
  undefined4 *puVar10;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_18;
  FUN_0043aa60();
  puVar5 = *(undefined4 **)(unaff_EBX + 0x98 + param_1 * 4);
  if (puVar5 != (undefined4 *)0x0) {
    local_8 = puVar5[1];
    local_c = *puVar5;
    uVar2 = CONCAT11((char)local_8,(char)((uint)local_8 >> 8));
    uVar1 = *(undefined2 *)(puVar5 + 2);
    local_18 = CONCAT31(CONCAT21(uVar2,(char)((uint)local_8 >> 0x10)),(char)((uint)local_8 >> 0x18))
    ;
    iVar7 = local_18;
    local_18._0_2_ = CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8));
    *(uint *)(unaff_EBX + 0x11c) = (uint)(ushort)local_18;
    local_18._0_2_ =
         CONCAT11((char)*(undefined2 *)(puVar5 + 3),(char)((ushort)*(undefined2 *)(puVar5 + 3) >> 8)
                 );
    *(uint *)(unaff_EBX + 0x120) = (uint)(ushort)local_18;
    local_18._0_2_ =
         CONCAT11((char)*(undefined2 *)((int)puVar5 + 10),
                  (char)((ushort)*(undefined2 *)((int)puVar5 + 10) >> 8));
    local_18 = CONCAT22(uVar2,(ushort)local_18);
    *(uint *)(unaff_EBX + 0x118) = (uint)(ushort)local_18;
    puVar9 = (undefined1 *)((int)(puVar5 + 2) + iVar7);
    puVar5 = _malloc((uint)(ushort)local_18 << 5);
    *(undefined4 **)(unaff_EBX + 0x138) = puVar5;
    for (iVar7 = (*(uint *)(unaff_EBX + 0x118) & 0x7ffffff) << 3; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined1 *)puVar5 = 0;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    local_c = 0;
    if (0 < *(int *)(unaff_EBX + 0x118)) {
      local_14 = 0;
      do {
        iVar7 = local_14;
        local_10 = *(undefined4 *)(puVar9 + 4);
        local_18._0_2_ = CONCAT11((char)((uint)local_10 >> 0x10),(char)((uint)local_10 >> 0x18));
        uVar3 = (ushort)local_18;
        local_18 = CONCAT22(CONCAT11((char)local_10,(char)((uint)local_10 >> 8)),(ushort)local_18);
        uVar4 = local_18;
        *(uint *)(local_14 + 8 + *(int *)(unaff_EBX + 0x138)) = local_18;
        pvVar6 = _malloc(local_18);
        *(void **)(iVar7 + 0x10 + *(int *)(unaff_EBX + 0x138)) = pvVar6;
        *(undefined4 *)(iVar7 + *(int *)(unaff_EBX + 0x138)) = 1;
        puVar5 = (undefined4 *)(puVar9 + 8);
        puVar10 = *(undefined4 **)(iVar7 + 0x10 + *(int *)(unaff_EBX + 0x138));
        for (uVar8 = uVar4 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar10 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar10 = puVar10 + 1;
        }
        for (uVar8 = uVar3 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined1 *)puVar10 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
        puVar9 = (undefined1 *)((int)(puVar9 + 8) + uVar4);
        local_c = local_c + 1;
        local_14 = local_14 + 0x20;
      } while (local_c < *(int *)(unaff_EBX + 0x118));
    }
    *(int *)(unaff_EBX + 0x10) = param_1;
    *(undefined4 *)(unaff_EBX + 0x124) = 1000000;
    return 0;
  }
  return 0xffffffff;
}

