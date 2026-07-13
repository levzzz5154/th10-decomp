/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00428160
 * Tracking name: FUN_00428160
 * Ghidra name: FUN_00428160
 * Tracked span: 112 bytes
 */


undefined4 FUN_00428160(void)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int unaff_EBX;
  char *pcVar4;
  int unaff_EDI;
  
  uVar3 = DAT_00474c48 / 0x14;
  if (4 < uVar3) {
    uVar3 = 4;
  }
  if (*(int *)(unaff_EDI + 0x4474) != 0) {
    uVar3 = uVar3 + 5;
  }
  pcVar4 = *(char **)(*(int *)(unaff_EDI + 0x45c) + 0x110 + uVar3 * 8);
  cVar2 = *pcVar4;
  while (-1 < cVar2) {
    if (unaff_EBX % (int)cVar2 == (int)pcVar4[1]) {
      FUN_00427e90(unaff_EDI,(int)pcVar4,unaff_EBX);
    }
    pcVar1 = pcVar4 + 0x34;
    pcVar4 = pcVar4 + 0x34;
    cVar2 = *pcVar1;
  }
  return 0;
}

