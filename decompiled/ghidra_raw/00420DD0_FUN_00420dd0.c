/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00420DD0
 * Tracking name: FUN_00420dd0
 * Ghidra name: FUN_00420dd0
 * Tracked span: 208 bytes
 */


undefined4 FUN_00420dd0(char *param_1,int param_2,int param_3)

{
  int in_EAX;
  int iVar1;
  uint *puVar2;
  uint *_Str2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  int local_8;
  int local_4;
  
  _Str2 = *(uint **)(in_EAX + 0x764);
  if (_Str2 == (uint *)0x0) {
    return 0;
  }
  iVar3 = *(int *)(in_EAX + 0x760);
  iVar1 = _strncmp(param_1,"debug",5);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = 6;
  bVar6 = true;
  pcVar4 = "0100a";
  pcVar5 = "debug";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar6 = *pcVar4 == *pcVar5;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return 0;
  }
  do {
    if (iVar3 == 0) {
      return 0xffffffff;
    }
    iVar1 = _strncmp(param_1,(char *)_Str2,5);
    if (iVar1 == 0) {
      _Str2 = (uint *)((int)_Str2 + 6);
      _sscanf((char *)_Str2,"%d %d",&local_8,&local_4);
      if ((local_8 == param_2) && (local_4 == param_3)) {
        return 0;
      }
    }
    puVar2 = FUN_00452730(_Str2,'\n');
    iVar3 = (int)_Str2 + (iVar3 - ((int)puVar2 + 1));
    _Str2 = (uint *)((int)puVar2 + 1);
  } while( true );
}

