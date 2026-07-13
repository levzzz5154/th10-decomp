/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00447BB0
 * Tracking name: FUN_00447bb0
 * Ghidra name: FUN_00447bb0
 * Tracked span: 960 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00447bb0(undefined4 param_1,COLORREF param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  int unaff_ESI;
  ulonglong uVar6;
  char local_84 [128];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_84;
  uVar5 = 0x11;
  if (*(byte *)(unaff_ESI + 0x3a0) != 0) {
    uVar5 = (uint)*(byte *)(unaff_ESI + 0x3a0);
  }
  _vsprintf(local_84,param_3,&stack0x00000010);
  pcVar3 = local_84;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar2 = *(int *)(unaff_ESI + 0x394);
  uVar4 = *(uint *)(unaff_ESI + 0x360) >> 1 & 1;
  uVar6 = FUN_00463b2c();
  FUN_004479d0(*(int **)(iVar2 + 4),
               (int)uVar6 / 2 - ((uVar5 - 1) * ((int)pcVar3 - (int)(local_84 + 1)) >> 2),param_2,
               uVar4);
  *(uint *)(unaff_ESI + 0x35c) = *(uint *)(unaff_ESI + 0x35c) | 1;
  return;
}

