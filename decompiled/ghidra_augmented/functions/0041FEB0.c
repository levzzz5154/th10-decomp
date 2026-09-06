/* Raw Ghidra reference; not compilable reconstruction. Address: 0041FEB0 */

undefined4 __fastcall FUN_0041feb0(uint *param_1)

{
  uint *puVar1;
  void *pvVar2;
  
  pvVar2 = g_pGameThread;
  if ((*param_1 & 2) != 0) {
    puVar1 = (uint *)(*(int *)((int)g_pGameThread + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
    puVar1 = (uint *)(*(int *)((int)pvVar2 + 0x10) + 4);
    *puVar1 = *puVar1 | 2;
    puVar1 = (uint *)(*(int *)((int)pvVar2 + 0x89a8) + 4);
    *puVar1 = *puVar1 | 2;
    DAT_00491ff4 = DAT_00491ff4 & 0xffffefff;
    DAT_00491fb8 = 4;
    *param_1 = *param_1 & 0xfffffffd;
  }
  return 1;
}

