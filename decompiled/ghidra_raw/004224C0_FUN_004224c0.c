/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004224C0
 * Tracking name: FUN_004224c0
 * Ghidra name: FUN_004224c0
 * Tracked span: 416 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_004224c0(int param_1)

{
  undefined *puVar1;
  char cVar2;
  char *pcVar3;
  void *pvVar4;
  uint uVar5;
  uint uVar6;
  float fStack0000000c;
  undefined4 uStack00000010;
  
  puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
  pcVar3 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
  do {
    cVar2 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar2 != '\0');
  FUN_00401630((int)g_pGameThread,"%s");
  pvVar4 = g_pGameThread;
  *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffff00;
  FUN_00401630((int)pvVar4,"_");
  pvVar4 = g_pGameThread;
  uVar6 = 0;
  *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  fStack0000000c = 320.0;
  uStack00000010 = 0;
  if ((int)pcVar3 - (int)puVar1 < 1) {
    *(undefined4 *)((int)pvVar4 + 0x8974) = 0xffffffff;
    return (uint)pvVar4;
  }
  do {
    *(uint *)((int)pvVar4 + 0x8974) =
         ((*(uint *)(param_1 + 0xfc) != uVar6) - 1 & 0x7f7e80) - 0x7f7f80;
    FUN_00401630((int)pvVar4,"%c");
    uVar5 = uVar6 / 0xd;
    if (uVar6 % 0xd == 0xc) {
      fStack0000000c = fStack0000000c + _DAT_00470b48;
    }
    uVar6 = uVar6 + 1;
    pvVar4 = g_pGameThread;
  } while ((int)uVar6 < (int)pcVar3 - (int)puVar1);
  *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  return uVar5;
}

