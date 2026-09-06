/* Raw Ghidra reference; not compilable reconstruction. Address: 00429A70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00429a70(undefined4 param_1,int param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  
  pvVar1 = g_pGameThread;
  if (((DAT_00477810 != 0) && (*(int *)(param_2 + 0x10) != 0)) && (*(int *)(param_2 + 0x10) == 1)) {
    if (_DAT_00470c30 <= (float)*(byte *)(param_2 + 0x1c4)) {
      if (_DAT_00470c2c <= (float)*(byte *)(param_2 + 0x1c4)) {
        uVar2 = 0xffffffff;
      }
      else {
        uVar2 = 0xffa0a0ff;
      }
    }
    else {
      uVar2 = 0xff5050ff;
    }
    *(undefined4 *)((int)g_pGameThread + 0x8974) = uVar2;
    AppendFormattedGameThreadRecord((int)pvVar1,"%3d");
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  }
  return 1;
}

